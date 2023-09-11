/**-------------------------------------------------------------------------------------------------------------------
*
* @file       SNDFactory_OpenAL.cpp
*
* @class      SNDFACTORY_OPENAL
* @brief      Sound OpenAL factory class
* @ingroup    PLATFORM_COMMON
*
* @copyright  GEN Group. All rights reserved.
*
* @cond
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
* documentation files(the "Software"), to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense, and/ or sell copies of the Software,
* and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of
* the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
* THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
* @endcond
*
* --------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <math.h>

#include "XFactory.h"
#include "XTimer.h"
#include "XTrace.h"
#include "XThread.h"
#include "XSleep.h"

#include "SNDFileOGG.h"
#include "SND_XEvent.h"
#include "SNDInstance.h"
#include "SNDStreamInstance.h"

#include "SNDSource_OpenAL.h"
#include "SNDElement_OpenAL.h"
#include "SNDStreamElement_OpenAL.h"

#include "SNDFactory_OpenAL.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDFACTORY_OPENAL::SNDFACTORY_OPENAL()
* @brief      Constructor
* @ingroup    PLATFORM_COMMON
*
* @return     Does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDFACTORY_OPENAL::SNDFACTORY_OPENAL()
{
  Clean();

  GEN_XFACTORY_CREATE(streammutex, Create_Mutex())

  //const ALCchar *defaultDeviceName;
  //defaultDeviceName = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);

  // OpenAL Initialization
  //device = alcOpenDevice(defaultDeviceName);

  device = alcOpenDevice("");
  if(!device) return;
    
  ALCenum error = alGetError();
  context = alcCreateContext(device, NULL);
  error = alGetError();

  if(!alcMakeContextCurrent(context)) return;
    
  maxchannels = 32;

  // Create 16 sources as who could possibly want more
  sources.SetAddInLimit(16);
  sources.Resize(maxchannels);

  for(XDWORD i = 0; i < maxchannels; i++)
    {
      SNDSOURCE_OPENAL* src = new SNDSOURCE_OPENAL();
      if(!src) return;
        
      sources.Set(i, src);
    }

  mastervolume = 1.0f;

  // create the streaming thread
  GEN_XFACTORY_CREATE(streamthread, CreateThread(XTHREADGROUPID_UNGROUP, __L("SNDFACTORY_OPENAL::SNDFACTORY_OPENAL"), SNDFACTORY_OPENAL::ThreadStreaming, this));
  streamthread->Ini();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDFACTORY_OPENAL::~SNDFACTORY_OPENAL()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_COMMON
*
* @return     Does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDFACTORY_OPENAL::~SNDFACTORY_OPENAL()
{
  if(streamthread)
    {
      streamthread->End();
      GEN_XFACTORY.DeleteThread(XTHREADGROUPID_UNGROUP, streamthread);
      streamthread = NULL;
    }
  
  StopAll();

  // destroy all sources, elements
  XDWORD elements = loadedfiles.GetSize();
  for(XDWORD i = 0; i < elements; i++)
    {
      delete loadedfiles.Get(i);
    }


  XDWORD streamers = streamelements.GetSize();
  for(XDWORD i = 0; i < streamers; i++)
    {
      delete streamelements.Get(i);
    }

  XDWORD sourcesnum = sources.GetSize();
  for(XDWORD i = 0; i < sourcesnum; i++)
    {
      if(sources.Get(i)->GetInstance() != NULL)
        {
          delete sources.Get(i)->GetInstance();
          sources.Get(i)->SetInstance(NULL);
        }
      delete sources.Get(i);
    }

  alcMakeContextCurrent(NULL);
  alcDestroyContext(context);
  alcCloseDevice(device);

  if(streammutex)
    {
      GEN_XFACTORY.Delete_Mutex(streammutex);
      streammutex = NULL;
    }

  Clean();
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SNDFACTORY_OPENAL::Beep(float frecuency, float duration)
* @brief      Beep
* @ingroup    PLATFORM_COMMON
*
* @param[in]  frecuency : 
* @param[in]  duration : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDFACTORY_OPENAL::Beep(float frequency, float duration)
{
  ALuint       buffer;     
  unsigned int sample_rate = 10000;
  size_t       buffer_size = (size_t)(duration * sample_rate);
  short*       samples     = NULL;

  alGenBuffers(1, &buffer);
   
  samples = new short[buffer_size];
  if(!samples) return false;
      
  for(unsigned c=0; c<buffer_size; c++)
    {
      samples[c] = (short)(32760 * sin(2 * PI * c * frequency/sample_rate));
    }

  alBufferData(buffer, AL_FORMAT_MONO16, samples, buffer_size, sample_rate);

  ALuint source;

  alGenSources(1,&source);
  alSourcei(source, AL_BUFFER, buffer);
  alSourcePlay(source);
 
  GEN_XSLEEP.MilliSeconds((int)(duration*1000));

  delete[] samples;

  alSourceStopv(1, &source);    
  alDeleteSources(1, &source);  
  alDeleteBuffers(1, &buffer);  

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDELEMENT* SNDFACTORY_OPENAL::Element_Add(XPATH& xpath, XCHAR* ID, bool instream)
* @brief      Element_Add
* @ingroup    PLATFORM_COMMON
*
* @param[in]  xpath : 
* @param[in]  ID : 
* @param[in]  instream : 
*
* @return     SNDELEMENT* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDELEMENT* SNDFACTORY_OPENAL::Element_Add(XPATH& xpath, XCHAR* ID, bool instream)
{
  XSTRING _ID;

  if(!ID)
    {      
      xpath.GetNamefile(_ID);  
      _ID.ToUpperCase();        

    } else _ID = ID;

  SNDELEMENT_OPENAL* element = NULL;

  element = (SNDELEMENT_OPENAL*)Element_Get(_ID.Get(), instream);
  if(element != NULL) return element;

  if(!instream)
    {
      SNDFILE* filesound = new SNDFILEOGG();
      if(filesound) 
        {
          bool status = filesound->LoadFile(xpath, _ID.Get(), instream);
          if(status)
            {              
              element = new SNDELEMENT_OPENAL(&xpath);
              if(element)
                {                  
                  element->SetFile(filesound);
                  element->SetDuration(filesound->GetDuration());

                  if(filesound->GetChannels() !=0)        
                    {
                      element->SetSamples(filesound->GetNSamples() / filesound->GetChannels());
                    }

                  if(loadedfiles.Add(element))
                    {
                      delete filesound;
                      return element;
                    }

                  delete element;
                }
              
              delete filesound;               
              return NULL;  
            }
        }
    }




  /*
  XPATH xpathfull;

  xpathfull = xpath;
  xpathfull.Slash_Add();
  xpathfull.Add(ID);

  if(!instream)
    {
      // create sndfileogg
      SNDELEMENT_OPENAL* element = (SNDELEMENT_OPENAL*)Element_Get(ID, instream);
      if(element != NULL)
        {
          //XTRACE_PRINTCOLOR(0,__L("File already Loaded:  %s"), file);
          return element;
        }

      SNDFILE* fileogg = sndsystem->CreateSNDFile(); // need xfactory in the system
      if(!fileogg)
        {
          return NULL;
        }

      // Change to use any Path in sounds
      //XPATH xpath;
      //xpath.Create(XPATHSMANAGERSECTIONTYPE_SOUNDS, 1 ,file);

      // load and decode file
      // for this the system needs to get xpaths
      if(!fileogg->LoadFile(xpathfull, ID, instream))
        {
         XTRACE_PRINTCOLOR(4,__L("Couldn't load %s"), xpath.Get());
          delete fileogg;
          return NULL;
        }


      // create the element but do not assign source to it
      // upload the data from the fileogg

      element = new SNDELEMENT_OPENAL(&xpathfull);
      if(!element)
        {
         XTRACE_PRINTCOLOR(4,__L("Couldn't load %s"), xpathfull.Get());
          delete fileogg;
          return NULL;
        }

      element->SetFile(fileogg);


      element->SetDuration(fileogg->GetDuration());

      if (fileogg->GetChannels()==0)
        {
         XTRACE_PRINTCOLOR(4,__L(" SNDFACTORY_OPENAL::AddFile: Exception using 0 channels to set samples"));
        }
      else
        {
          element->SetSamples(fileogg->samples/fileogg->GetChannels());
        }


      if (!loadedfiles.Add(element))
        {
          return NULL;
        }

      delete fileogg;

      //XTRACE_PRINTCOLOR(1,__L("File %s Loaded"), file);

      //return it
      return element;
    }
  else
    {
      SNDSTREAMELEMENT_OPENAL* streamelement = (SNDSTREAMELEMENT_OPENAL*)Element_Get(ID, instream);

      if(streamelement != NULL)
        {
          return streamelement;
        }

      streamelement = new SNDSTREAMELEMENT_OPENAL();

      SNDFILE* fileogg = sndsystem->CreateSNDFile();
      if(!fileogg)
        {
          return NULL;
        }

      //XPATH xpath;
      //xpath.Create(XPATHSMANAGERSECTIONTYPE_SOUNDS, 1, namefile);

      // load and decode file
      // for this the system needs to get xpaths
      if(!fileogg->LoadFile(xpathfull, ID, instream))
        {
          XTRACE_PRINTCOLOR(4,__L("Couldn't load %s"), ID);
          delete fileogg;
          return NULL;
        }

      // need to add this to an appropiate list !!
      streamelement->SetFile(fileogg);

      // careful, as I'm treting this array as files being currently played
      streammutex->Lock();
      if (!streamelements.Add(streamelement))
        {
          streammutex->UnLock();
          return NULL;
        }
      streammutex->UnLock();

      return streamelement;
    }
*/

  return NULL;
}





/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDELEMENT* SNDFACTORY_OPENAL::Element_Get(XCHAR* ID, bool instream)
* @brief      Element_Get
* @ingroup    PLATFORM_COMMON
*
* @param[in]  ID : 
* @param[in]  instream : 
*
* @return     SNDELEMENT* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDELEMENT* SNDFACTORY_OPENAL::Element_Get(XCHAR* ID, bool instream)
{
  if(!instream)
    {
      XDWORD numberoffiles = loadedfiles.GetSize();
      for(XDWORD c=0; c<numberoffiles; c++)
        {
          // compare the element file name with the one being requested
          if(loadedfiles.FastGet(c)->GetID()->Compare(ID) == 0)
            {
              return loadedfiles.Get(c);
            }
        }
    }


  /*
  if(!instream)
    {
      XDWORD numberoffiles = loadedfiles.GetSize();
      for(XDWORD i = 0; i < numberoffiles; i++)
        {
          // compare the element file name with the one being requested
          if(loadedfiles.FastGet(i)->GetID()->Compare(ID) == 0)
            {
              return loadedfiles.Get(i);
            }
        }
    }
  else
    {
      // look for the file on the stream elements
      streammutex->Lock();
      XDWORD numberoffiles = streamelements.GetSize();
      for(XDWORD i = 0; i < numberoffiles; i++)
        {
          // compare the element file name with the one being requested
          if(streamelements.FastGet(i)->GetID()->Compare(ID) == 0)
            {
              SNDSTREAMELEMENT* ret = streamelements.Get(i);
              streammutex->UnLock();
              return ret;
            }
        }
      streammutex->UnLock();
    }
  */

  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SNDFACTORY_OPENAL::Element_Del(SNDELEMENT* element)
* @brief      Element_Del
* @ingroup    PLATFORM_COMMON
*
* @param[in]  element : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDFACTORY_OPENAL::Element_Del(SNDELEMENT* element)
{
  this->StopSound(element);

  deletequeue.Add(element);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDSTREAMELEMENT* SNDFACTORY_OPENAL::GetStreamer()
* @brief      GetStreamer
* @ingroup    PLATFORM_COMMON
*
* @return     SNDSTREAMELEMENT* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDSTREAMELEMENT* SNDFACTORY_OPENAL::GetStreamer()
{
  // create a streaming element and aquire a free source

  SNDSTREAMELEMENT_OPENAL* streamer = NULL;

  
  streamer = new SNDSTREAMELEMENT_OPENAL(); // store the streamer somewhere and delete it when destroying openal?
  if(!streamer)
    {
      return NULL;
    }

  streammutex->Lock();
  streamelements.Add(streamer);
  streammutex->UnLock();


  return streamer;

  //for(int i = (maxchannels-1); i >= 0; i--)
  //  {
  //    SNDOPENALSOURCE* source = sources.Get(i);
  //    if(!source->IsPLaying())
  //      {
  //        if(!source->GetElement())
  //          {
  //            source->Aquire();
  //            SNDSTREAMELEMENT_OPENAL* streamer = new SNDSTREAMELEMENT_OPENAL(); // store the streamer somewhere and delete it when destroying openal?
  //            if(!streamer)
  //              {
  //                return NULL;
  //              }
  //
  //            //streamer->aquiredsource = source;
  //            source->SetElement(streamer);
  //            streamer->SetSource(source);
  //            streamelements.Add(streamer);
  //            return streamer;
  //          }
  //      }
  //  }
  //
  //return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDINSTANCE* SNDFACTORY_OPENAL::PlaySound(SNDELEMENT* element)
* @brief      PlaySound
* @ingroup    PLATFORM_COMMON
*
* @param[in]  element : 
*
* @return     SNDINSTANCE* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDINSTANCE* SNDFACTORY_OPENAL::PlaySound(SNDELEMENT* element)
{
  if(!element) return NULL;

  if(!element->IsStream())
    {
      // need to know if it's a stream or a regular element to know what to do !!
      SNDELEMENT_OPENAL* openalelement = (SNDELEMENT_OPENAL*)element;
      if(!openalelement) return NULL;
      
      for(XDWORD c=0; c<maxchannels; c++)
        {
          SNDSOURCE_OPENAL* source = sources.FastGet(c);
          if(source == NULL) return NULL;
            
          if(source->IsStopped())
            {
              if(source->GetElement() == NULL)
                {
                  openalelement->SetSource(source);

                  source->SetElement(openalelement);
                  source->SetVolume(element->GetVolume());

                  openalelement->Queue();

                  source->SetLoop(openalelement->GetLoop());
                  source->SetPitch(openalelement->GetPitch());

                  SNDINSTANCE* instance = new SNDINSTANCE(source, openalelement);
                  if(!instance) return NULL;

                  source->SetInstance(instance);

                  /*  
                  SND_XEVENT event(this, XEVENT_TYPE_SOUND, XEVENT_TYPE_SOUND);  // need to make a specific event type for this
                  event.SetType(SND_XEVENT_TYPE_PLAY);

                  ins->HandleEvent(&event);    // direct call to avoid performance penalty
                  */

                  return instance;
                }
            }
        }
    }


  /*
  if(!element->IsStream())
    {
      // need to know if it's a stream or a regular element to know what to do !!
      SNDELEMENT_OPENAL* openalelement = (SNDELEMENT_OPENAL*)element;

      if(!openalelement)
        {
          return NULL;
        }

      for(XDWORD i = 0; i < maxchannels; i++)
        {
          SNDOPENALSOURCE* source = sources.FastGet(i);

          if (source==NULL)
            {
             XTRACE_PRINTCOLOR(4,__L("SNDFACTORY_OPENAL::PlaySound : Executing a NULL source"));
            }

          if(source->IsStopped())
            {
              if(source->GetElement() == NULL)
                {
                  openalelement->SetSource(source);
                  source->SetElement(openalelement);
                  source->SetVolume(element->GetVolume());
                  openalelement->Queue();
                  source->SetLoop(openalelement->GetLoop());
                  source->SetPitch(openalelement->GetPitch());

                  SNDINSTANCE* ins = new SNDINSTANCE(source, openalelement);
                  if(!ins) return NULL;
                  source->SetInstance(ins);

                  SND_XEVENT event(this, XEVENT_TYPE_SOUND, XEVENT_TYPE_SOUND);  // need to make a specific event type for this
                  event.SetType(SND_XEVENT_TYPE_PLAY);

                  ins->HandleEvent(&event);    // direct call to avoid performance penalty

                  return ins;
                }
            }
        }
    }
  else
    {
      SNDSTREAMELEMENT_OPENAL* streamelement = (SNDSTREAMELEMENT_OPENAL*)element;

      for(XDWORD i = 0; i < maxchannels; i++)
        {
          SNDOPENALSOURCE* source = sources.FastGet(i);

          if (source==NULL)
            {
             XTRACE_PRINTCOLOR(4,__L("SNDFACTORY_OPENAL::PlaySound : Executing a NULL source"));
            }

          if(source->IsStopped())
            {
              if(source->GetElement() == NULL)
                {
                  streamelement->SetSource(source);
                  source->SetElement(streamelement);
                  source->SetVolume(element->GetVolume());

                  source->SetLoop(streamelement->GetLoop());
                  source->SetPitch(streamelement->GetPitch());
                  source->SetAquired(true);

                  SNDSTREAMINSTANCE* streaminstance = new SNDSTREAMINSTANCE(source, streamelement);

                  if(!streaminstance) return NULL;
                  source->SetInstance(streaminstance);
                  streaminstance->SetIsManaged(false);

                  SND_XEVENT event(this, XEVENT_TYPE_SOUND, XEVENT_TYPE_SOUND);  // need to make a specific event type for this
                  event.SetType(SND_XEVENT_TYPE_PLAY);

                  streaminstance->HandleEvent(&event);   // direct call to avoid performance penalty

                  return streaminstance;
                }
            }
        }
    }

  if(element)
    {  
      if(element->GetID())
        {
          XTRACE_PRINTCOLOR(4,__L("No available Source : %s"), element->GetID()->Get());
        }
    }
  */

  return NULL;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDFACTORY_OPENAL::StopSound(SNDELEMENT* element)
* @brief      StopSound
* @ingroup    PLATFORM_COMMON
*
* @param[in]  element : 
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDFACTORY_OPENAL::StopSound(SNDELEMENT* element)
{ 
  SNDELEMENT_OPENAL* openalelement = (SNDELEMENT_OPENAL*)element;
  if(!openalelement) return false;
  
  if(openalelement->GetSource())
    {
      // make sure the element is actually assigned to a source
      if(openalelement->GetSource()->GetElement() == openalelement)
        {
          openalelement->GetSource()->Stop();

        
          /*
          // not sure if deattach source and element here, or wait for update
          SND_XEVENT  sndevent(this, XEVENT_TYPE_SOUND, XEVENT_TYPE_SOUND); // need to make a specific event type for this
          
          sndevent.SetElement(element);
          sndevent.SetType(SND_XEVENT_TYPE_STOP);
          
          if(openalelement->GetSource()->GetInstance())
            {
              openalelement->GetSource()->GetInstance()->HandleEvent(&sndevent);   // direct call to avoid performance penalty
              openalelement->GetSource()->SetInstance(NULL);
            }
          */
        }
    }
 
  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDINSTANCE* SNDFACTORY_OPENAL::PauseSound(SNDELEMENT* element)
* @brief      PauseSound
* @ingroup    PLATFORM_COMMON
*
* @param[in]  element : 
*
* @return     SNDINSTANCE* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDINSTANCE* SNDFACTORY_OPENAL::PauseSound(SNDELEMENT* element)
{
  SNDELEMENT_OPENAL* openalelement = (SNDELEMENT_OPENAL*)element;
  
  if(!openalelement) return NULL;
   
  if(openalelement->GetSource())
    {
      if(openalelement->GetSource()->GetElement() == openalelement)
        {
          if(openalelement->GetSource()->IsPLaying())
            {
              openalelement->GetSource()->Pause();

              return openalelement->GetSource()->GetInstance();
            }
        }
    }

  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SNDFACTORY_OPENAL::IsAnyPlaying()
* @brief      IsAnyPlaying
* @ingroup    PLATFORM_COMMON
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDFACTORY_OPENAL::IsAnyPlaying()
{  
  for(XDWORD c=0; c<maxchannels; c++)
    {
      if(sources.Get(c)->IsPLaying())
        {
          return true;
        }
    }
 
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDFACTORY_OPENAL::StopAll()
* @brief      StopAll
* @ingroup    PLATFORM_COMMON
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDFACTORY_OPENAL::StopAll()
{
  playqueue.DeleteAll();

  for(XDWORD c=0; c<maxchannels; c++)
    {
      sources.Get(c)->Stop();
    }

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float SNDFACTORY_OPENAL::GetMasterVolume()
* @brief      GetMasterVolume
* @ingroup    PLATFORM_COMMON
*
* @return     float : 
*
* --------------------------------------------------------------------------------------------------------------------*/
float SNDFACTORY_OPENAL::GetMasterVolume()                                                      
{ 
  return mastervolume;                
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SNDFACTORY_OPENAL::SetMasterVolume(float mastervolume)
* @brief      SetMasterVolume
* @ingroup    PLATFORM_COMMON
*
* @param[in]  mastervolume : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDFACTORY_OPENAL::SetMasterVolume(float mastervolume)
{  
  
  //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L(" Master volumen: %f"), mastervolume);

  // reset the volume of all sources
  for(XDWORD c=0; c<maxchannels; c++)
    {
      SNDSOURCE_OPENAL* source  = sources.Get(c);
      float             volume  = 0.0f;

      if(source)
        {
          alGetSourcef(source->source, AL_GAIN, &volume);
          volume /= this->mastervolume;

          volume *= mastervolume;
          alSourcef(source->source, AL_GAIN, volume);
        }
    }

  this->mastervolume = mastervolume;
  
  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDFACTORY_OPENAL::Update()
* @brief      Update
* @ingroup    PLATFORM_COMMON
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDFACTORY_OPENAL::Update()
{
  
  for(int i = (maxchannels-1); i >= 0; i--)
    {
      SNDSOURCE_OPENAL* source = sources.Get(i);

      // an element has exclusive access(probably because of streaming), ignore it
      // but if it's aquired I can't really check when it finished!!

      // need to unify both cases
      if(source->IsAquired() && !source->IsInstancePlaying())
        {
          if(source->GetElement())
            {
              SNDSTREAMELEMENT_OPENAL* element = (SNDSTREAMELEMENT_OPENAL*)source->GetElement();

              streammutex->Lock();
              int proc = source->GetProcessedBuffers();
              element->ClearBuffers();
              ((SNDELEMENT_OPENAL*)source->GetElement())->SetSource(NULL);
              proc = source->GetProcessedBuffers();


              source->SetLoop(false);
              source->SetPitch(1.0f);

              // need to have stored the quaued buffers to unqueue them
              //XLIST<SNDOPENALBUFFER*>::XITERATOR it;



              //for(it = source->bufferlist.Begin(); it != source->bufferlist.End(); it++)
              //  {
              //    source->UnQueue(*it);
              //    (*it)->Destroy();
              //    delete (*it);
              //  }

              //source->bufferlist.DeleteAll();

              source->Release();

              if(source->GetElement())
                {
                  SND_XEVENT event(this, XEVENT_TYPE_SOUND, XEVENT_TYPE_SOUND);  // need to make a specific event type for this
                  event.SetElement(element);

                  event.SetInstance(source->GetInstance());
                  event.SetElement(element);
                  event.SetSource(NULL); // because it's NULL for element
                  event.SetType(SND_XEVENT_TYPE_STOP);
                  PostEvent(&event);

                  if(source->GetInstance())
                    {
                      source->GetInstance()->HandleEvent(&event);    // direct call to avoid performance penalty
                      source->SetInstance(NULL);
                    }
                }

                source->SetElement(NULL);
                source->Stop();

                if(element->GetFile())
                  {
                    element->GetFile()->Reset();
                  }

                //// send an event telling which sound stopped playing
                //SND_XEVENT* event = new SND_XEVENT(this, XEVENT_TYPE_SOUND, XEVENT_TYPE_SOUND);
                //if(event)
                //  {
                //    event->SetSNDType(SND_XEVENT_TYPE_STOP);
                //    event->SetSound(element->GetNameFile()->Get());
                //    event->SetSNDElement(element);
                //
                //    PostEvent(event);
                //
                //    delete event;
                //  }

                streammutex->UnLock();
            }

          continue;
        }

      if(source->IsAquired())
        {
          continue;// need to detect when a streaming instance finishes !!
        }

      // !! important if element is a streamer we need to clear the stored buffers
      if(!source->IsPLaying() && !source->IsAquired()) // also check if not aquired? can help with the checks, but update needs to know when a sound stopped to clean up
      //if(!source->IsPLaying() && !source->IsInstancePlaying())
        {
          if(source->GetElement())
            {
              // check if element is a streamer

              // we need to stop the source
              source->SetLoop(false);
              source->SetPitch(1.0f);
              SNDELEMENT* element = source->GetElement();
              if(element)
                {
                  //// clear up the completed queued buffers
                  //if(element->IsStreamer())
                  //  {
                  //    // need to have stored the quaued buffers to unqueue them
                  //    XLIST<SNDOPENALBUFFER*>::XITERATOR it;
                  //
                  //    for(it = source->bufferlist.Begin(); it != source->bufferlist.End(); it++)
                  //      {
                  //        source->UnQueue(*it);
                  //        delete *it;
                  //      }
                  //
                  //    source->bufferlist.DeleteAll();
                  //
                  //    source->Release();
                  //  }

                  ((SNDELEMENT_OPENAL*)source->GetElement())->SetSource(NULL);
                }
              if(source->GetElement())
                {
                  SND_XEVENT event(this, XEVENT_TYPE_SOUND, XEVENT_TYPE_SOUND);  // need to make a specific event type for this
                  event.SetElement(element);
                  if(source->GetInstance())
                    {
                      event.SetInstance(source->GetInstance());
                      event.SetElement(element);
                      event.SetSource(NULL);
                      event.SetType(SND_XEVENT_TYPE_STOP);

                      PostEvent(&event);

                      if(source->GetInstance())
                        {
                          source->GetInstance()->HandleEvent(&event);    // direct call to avoid performance penalty


                          delete source->GetInstance();
                          source->SetInstance(NULL);
                        }
                    }
                }

              source->SetElement(NULL);
              source->Stop();

              //// send an event telling which sound stopped playing
              //SND_XEVENT* event = new SND_XEVENT(this, XEVENT_TYPE_SOUND, XEVENT_TYPE_SOUND);
              //if(event)
              //  {
              //    event->SetSNDType(SND_XEVENT_TYPE_STOP);
              //    event->SetSound(element->GetNameFile()->Get());
              //    event->SetSNDElement(element);
              //
              //    PostEvent(event);
              //
              //    delete event;
              //  }
            }
        }
    }


  XDWORD size = deletequeue.GetSize();
  for(XDWORD i = 0; i < size; i++)
  {
    SNDELEMENT_OPENAL* e = (SNDELEMENT_OPENAL*)deletequeue.FastGet(i);

    if(e->IsStream())
      {
        streammutex->Lock();
        XDWORD index = streamelements.Find((SNDSTREAMELEMENT_OPENAL*)e);
        if(index != NOTFOUND)
          {
            streamelements.DeleteIndex(index);
            delete e;
          }
        streammutex->UnLock();
      }
    else
      {
        XDWORD index = loadedfiles.Find(e);
        if(index != NOTFOUND)
          {
            loadedfiles.DeleteIndex(index);
            delete e;
          }
      }
  }

  deletequeue.DeleteAll();

  //XDWORD totalstream = streamelements.GetSize();
  //for(XDWORD i = 0; i < totalstream; i++)
  //  {
  //    SNDSTREAMELEMENT_OPENAL* element = streamelements.FastGet(i);
  //    //SNDSTREAMINSTANCE* instance = streamelements.FastGet(i); // WANT INSTANCES !!
  //    SNDSTREAMINSTANCE* instance = (SNDSTREAMINSTANCE*)element->GetSource()->GetInstance();
  //    if(instance)
  //      {
  //        instance->Update();
  //      }
  //  }

  
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDFACTORY_OPENAL::ThreadStreaming(void* param)
* @brief      ThreadStreaming
* @ingroup    PLATFORM_COMMON
*
* @param[in]  param : 
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDFACTORY_OPENAL::ThreadStreaming(void* param)
{
  SNDFACTORY_OPENAL* sndopenal = (SNDFACTORY_OPENAL*)param;
  if(!sndopenal) return;

  sndopenal->streammutex->Lock();


  sndopenal->Update();

  XDWORD totalstream = sndopenal->streamelements.GetSize();
  for(XDWORD i = 0; i < totalstream; i++)
    {
      SNDSTREAMELEMENT_OPENAL* element = sndopenal->streamelements.FastGet(i);
      //SNDSTREAMINSTANCE* instance = streamelements.FastGet(i); // WANT INSTANCES !!
      if(element->GetSource())
        {
          if(element->GetSource()->IsInstancePlaying()) // but same crash as below, instance is no longer a valid pointer
            {
              SNDSTREAMINSTANCE* instance = (SNDSTREAMINSTANCE*)element->GetSource()->GetInstance();
              if(instance)
                {
                  instance->Update();
                }
            }
        }
    }

  sndopenal->streammutex->UnLock();

}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDFACTORY_OPENAL::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_COMMON
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDFACTORY_OPENAL::Clean()
{                                                
  device        = NULL;
 
  context       = NULL;
  maxchannels   = 0;
  mastervolume  = 0.0f;

  streamthread  = NULL;
  streammutex   = NULL;

  isinit        = false;
}