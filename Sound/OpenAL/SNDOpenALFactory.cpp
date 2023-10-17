/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       SNDOpenALFactory.cpp
* 
* @class      SNDOPENALFACTORY
* @brief      Sound OpenAL Factory class
* @ingroup    SOUND
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

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "SNDOpenALFactory.h"

#include <math.h>

#include "XFactory.h"
#include "XTimer.h"
#include "XTrace.h"
#include "XThread.h"
#include "XSleep.h"

#include "SNDFactory_XEvent.h"
#include "SNDInstance.h"
#include "SNDInstanceStream.h"

#include "SNDOpenALSource.h"
#include "SNDOpenALElement.h"
#include "SNDOpenALElementStream.h"

#include "SNDFile.h"
#include "SNDFileOGG.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDOPENALFACTORY::SNDOPENALFACTORY()
* @brief      Constructor
* @ingroup    SOUND
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDOPENALFACTORY::SNDOPENALFACTORY()
{
  Clean();

  GEN_XFACTORY_CREATE(streammutex, Create_Mutex())

  device = alcOpenDevice("");
  if(!device) 
    {
      return;
    }
    
  ALCenum error;

  context   = alcCreateContext(device, NULL);
  error     = alGetError();

  if(!alcMakeContextCurrent(context)) 
    {
      return;
    }
    
  maxchannels = 32;

  // Create 16 sources as who could possibly want more
  sources.SetAddInLimit(16);
  sources.Resize(maxchannels);

  for(XDWORD i = 0; i < maxchannels; i++)
    {
      SNDOPENALSOURCE* src = new SNDOPENALSOURCE();
      if(!src) return;
        
      sources.Set(i, src);
    }

  mastervolume = 1.0f;

  // create the streaming thread
  GEN_XFACTORY_CREATE(streamthread, CreateThread(XTHREADGROUPID_UNGROUP, __L("SNDOPENALFACTORY::SNDOPENALFACTORY"), SNDOPENALFACTORY::ThreadStreaming, this));
  streamthread->Ini();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDOPENALFACTORY::~SNDOPENALFACTORY()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    SOUND
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDOPENALFACTORY::~SNDOPENALFACTORY()
{
  if(streamthread)
    {
      streamthread->End();
      GEN_XFACTORY.DeleteThread(XTHREADGROUPID_UNGROUP, streamthread);
      streamthread = NULL;
    }
  
  Sound_StopAll();

  // destroy all sources, elements
  XDWORD elements = loadedfiles.GetSize();
  for(XDWORD i = 0; i < elements; i++)
    {
      delete loadedfiles.Get(i);
    }

  XDWORD streamers = elementsstream.GetSize();
  for(XDWORD i = 0; i < streamers; i++)
    {
      delete elementsstream.Get(i);
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
* @fn         float SNDOPENALFACTORY::Volume_Get()
* @brief      Volume_Get
* @ingroup    SOUND
* 
* @return     float : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
float SNDOPENALFACTORY::Volume_Get()
{ 
  return mastervolume;                
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDOPENALFACTORY::Volume_Set(float mastervolume)
* @brief      Volume_Set
* @ingroup    SOUND
* 
* @param[in]  mastervolume : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDOPENALFACTORY::Volume_Set(float mastervolume)
{  
  //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L(" Master volumen: %f"), mastervolume);

  // reset the volume of all sources
  for(XDWORD c=0; c<maxchannels; c++)
    {
      SNDOPENALSOURCE* source  = sources.Get(c);
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
* @fn         SNDELEMENT* SNDOPENALFACTORY::Element_Add(XPATH& xpath, XCHAR* ID, bool instream)
* @brief      Element_Add
* @ingroup    SOUND
* 
* @param[in]  xpath : 
* @param[in]  ID : 
* @param[in]  instream : 
* 
* @return     SNDELEMENT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDELEMENT* SNDOPENALFACTORY::Element_Add(XCHAR* pathfile, XCHAR* ID, bool instream)
{
  XSTRING _ID;
  XPATH   xpath;

  xpath = pathfile;

  if(!ID)
    {      
      xpath.GetNamefile(_ID);  
      _ID.ToUpperCase();        

    } else _ID = ID;

  SNDOPENALELEMENT* element = NULL;

  element = (SNDOPENALELEMENT*)Element_Get(_ID.Get(), instream);
  if(element != NULL) return element;

  if(!instream)
    {
      SNDFILE* filesound = new SNDFILEOGG();
      if(filesound) 
        {
          bool status = filesound->LoadFile(xpath, _ID.Get(), instream);
          if(status)
            {              
              element = new SNDOPENALELEMENT(&xpath);
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
      SNDOPENALELEMENT* element = (SNDOPENALELEMENT*)Element_Get(ID, instream);
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

      element = new SNDOPENALELEMENT(&xpathfull);
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
         XTRACE_PRINTCOLOR(4,__L(" SNDOPENALFACTORY::AddFile: Exception using 0 channels to set samples"));
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
      SNDOPENALELEMENTSTREAM* streamelement = (SNDOPENALELEMENTSTREAM*)Element_Get(ID, instream);

      if(streamelement != NULL)
        {
          return streamelement;
        }

      streamelement = new SNDOPENALELEMENTSTREAM();

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
      if (!elementsstream.Add(streamelement))
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
* @fn         SNDELEMENT* SNDOPENALFACTORY::Element_Get(XCHAR* ID, bool instream)
* @brief      Element_Get
* @ingroup    SOUND
* 
* @param[in]  ID : 
* @param[in]  instream : 
* 
* @return     SNDELEMENT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDELEMENT* SNDOPENALFACTORY::Element_Get(XCHAR* ID, bool instream)
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
      XDWORD numberoffiles = elementsstream.GetSize();
      for(XDWORD i = 0; i < numberoffiles; i++)
        {
          // compare the element file name with the one being requested
          if(elementsstream.FastGet(i)->GetID()->Compare(ID) == 0)
            {
              SNDSTREAMELEMENT* ret = elementsstream.Get(i);
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
* @fn         bool SNDOPENALFACTORY::Element_Del(SNDELEMENT* element)
* @brief      Element_Del
* @ingroup    SOUND
* 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDOPENALFACTORY::Element_Del(SNDELEMENT* element)
{
  Sound_Stop(element);

  deletequeue.Add(element);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDINSTANCE* SNDOPENALFACTORY::Sound_Play(SNDELEMENT* element)
* @brief      Sound_Play
* @ingroup    SOUND
* 
* @param[in]  element : 
* 
* @return     SNDINSTANCE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDINSTANCE* SNDOPENALFACTORY::Sound_Play(SNDELEMENT* element)
{
  if(!element) return NULL;

  if(!element->IsStream())
    {
      // need to know if it's a stream or a regular element to know what to do !!
      SNDOPENALELEMENT* openalelement = (SNDOPENALELEMENT*)element;
      if(!openalelement) return NULL;
      
      for(XDWORD c=0; c<maxchannels; c++)
        {
          SNDOPENALSOURCE* source = sources.FastGet(c);
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
                  SNDFACTORY_XEVENT event(this, XEVENT_TYPE_SOUND, XEVENT_TYPE_SOUND);  // need to make a specific event type for this
                  event.SetType(SNDFACTORY_XEVENT_TYPE_PLAY);

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
      SNDOPENALELEMENT* openalelement = (SNDOPENALELEMENT*)element;

      if(!openalelement)
        {
          return NULL;
        }

      for(XDWORD i = 0; i < maxchannels; i++)
        {
          SNDOPENALSOURCE* source = sources.FastGet(i);

          if (source==NULL)
            {
             XTRACE_PRINTCOLOR(4,__L("SNDOPENALFACTORY::PlaySound : Executing a NULL source"));
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

                  SNDFACTORY_XEVENT event(this, XEVENT_TYPE_SOUND, XEVENT_TYPE_SOUND);  // need to make a specific event type for this
                  event.SetType(SNDFACTORY_XEVENT_TYPE_PLAY);

                  ins->HandleEvent(&event);    // direct call to avoid performance penalty

                  return ins;
                }
            }
        }
    }
  else
    {
      SNDOPENALELEMENTSTREAM* streamelement = (SNDOPENALELEMENTSTREAM*)element;

      for(XDWORD i = 0; i < maxchannels; i++)
        {
          SNDOPENALSOURCE* source = sources.FastGet(i);

          if (source==NULL)
            {
             XTRACE_PRINTCOLOR(4,__L("SNDOPENALFACTORY::PlaySound : Executing a NULL source"));
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

                  SNDFACTORY_XEVENT event(this, XEVENT_TYPE_SOUND, XEVENT_TYPE_SOUND);  // need to make a specific event type for this
                  event.SetType(SNDFACTORY_XEVENT_TYPE_PLAY);

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
* @fn         bool SNDOPENALFACTORY::Sound_Stop(SNDELEMENT* element)
* @brief      Sound_Stop
* @ingroup    SOUND
* 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDOPENALFACTORY::Sound_Stop(SNDELEMENT* element)
{ 
  SNDOPENALELEMENT* openalelement = (SNDOPENALELEMENT*)element;
  if(!openalelement) return false;
  
  if(openalelement->GetSource())
    {
      // make sure the element is actually assigned to a source
      if(openalelement->GetSource()->GetElement() == openalelement)
        {
          openalelement->GetSource()->Stop();

        
          /*
          // not sure if deattach source and element here, or wait for update
          SNDFACTORY_XEVENT  sndevent(this, XEVENT_TYPE_SOUND, XEVENT_TYPE_SOUND); // need to make a specific event type for this
          
          sndevent.SetElement(element);
          sndevent.SetType(SNDFACTORY_XEVENT_TYPE_STOP);
          
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
* @fn         SNDINSTANCE* SNDOPENALFACTORY::Sound_Pause(SNDELEMENT* element)
* @brief      Sound_Pause
* @ingroup    SOUND
* 
* @param[in]  element : 
* 
* @return     SNDINSTANCE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDINSTANCE* SNDOPENALFACTORY::Sound_Pause(SNDELEMENT* element)
{
  SNDOPENALELEMENT* openalelement = (SNDOPENALELEMENT*)element;
  
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
* @fn         bool SNDOPENALFACTORY::Sound_IsAnyPlaying()
* @brief      Sound_IsAnyPlaying
* @ingroup    SOUND
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDOPENALFACTORY::Sound_IsAnyPlaying()
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
* @fn         bool SNDOPENALFACTORY::Sound_StopAll()
* @brief      Sound_StopAll
* @ingroup    SOUND
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDOPENALFACTORY::Sound_StopAll()
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
* @fn         bool SNDOPENALFACTORY::Sound_Note(float frequency, float duration)
* @brief      Sound_Note
* @ingroup    SOUND
* 
* @param[in]  frequency : 
* @param[in]  duration : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDOPENALFACTORY::Sound_Note(float frequency, float duration)
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
* @fn         void SNDOPENALFACTORY::Update()
* @brief      Update
* @ingroup    SOUND
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALFACTORY::Update()
{ 
  for(int i = (maxchannels-1); i >= 0; i--)
    {
      SNDOPENALSOURCE* source = sources.Get(i);

      // an element has exclusive access(probably because of streaming), ignore it
      // but if it's aquired I can't really check when it finished!!

      // need to unify both cases
      if(source->IsAquired() && !source->IsInstancePlaying())
        {
          if(source->GetElement())
            {
              SNDOPENALELEMENTSTREAM* element = (SNDOPENALELEMENTSTREAM*)source->GetElement();

              streammutex->Lock();
              int proc = source->GetProcessedBuffers();
              element->ClearBuffers();
              ((SNDOPENALELEMENT*)source->GetElement())->SetSource(NULL);
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
                  SNDFACTORY_XEVENT event(this, XEVENT_TYPE_SOUND, XEVENT_TYPE_SOUND);  // need to make a specific event type for this
                  event.SetElement(element);

                  event.SetInstance(source->GetInstance());
                  event.SetElement(element);
                  event.SetSource(NULL); // because it's NULL for element
                  event.SetType(SNDFACTORY_XEVENT_TYPE_STOP);
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
                //SNDFACTORY_XEVENT* event = new SNDFACTORY_XEVENT(this, XEVENT_TYPE_SOUND, XEVENT_TYPE_SOUND);
                //if(event)
                //  {
                //    event->SetSNDType(SNDFACTORY_XEVENT_TYPE_STOP);
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

                  ((SNDOPENALELEMENT*)source->GetElement())->SetSource(NULL);
                }
              if(source->GetElement())
                {
                  SNDFACTORY_XEVENT event(this, XEVENT_TYPE_SOUND, XEVENT_TYPE_SOUND);  // need to make a specific event type for this
                  event.SetElement(element);
                  if(source->GetInstance())
                    {
                      event.SetInstance(source->GetInstance());
                      event.SetElement(element);
                      event.SetSource(NULL);
                      event.SetType(SNDFACTORY_XEVENT_TYPE_STOP);

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
              //SNDFACTORY_XEVENT* event = new SNDFACTORY_XEVENT(this, XEVENT_TYPE_SOUND, XEVENT_TYPE_SOUND);
              //if(event)
              //  {
              //    event->SetSNDType(SNDFACTORY_XEVENT_TYPE_STOP);
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
    SNDOPENALELEMENT* e = (SNDOPENALELEMENT*)deletequeue.FastGet(i);

    if(e->IsStream())
      {
        streammutex->Lock();
        XDWORD index = elementsstream.Find((SNDOPENALELEMENTSTREAM*)e);
        if(index != NOTFOUND)
          {
            elementsstream.DeleteIndex(index);
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

  //XDWORD totalstream = elementsstream.GetSize();
  //for(XDWORD i = 0; i < totalstream; i++)
  //  {
  //    SNDOPENALELEMENTSTREAM* element = elementsstream.FastGet(i);
  //    //SNDSTREAMINSTANCE* instance = elementsstream.FastGet(i); // WANT INSTANCES !!
  //    SNDSTREAMINSTANCE* instance = (SNDSTREAMINSTANCE*)element->GetSource()->GetInstance();
  //    if(instance)
  //      {
  //        instance->Update();
  //      }
  //  }  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDSTREAMELEMENT* SNDOPENALFACTORY::GetStreamer()
* @brief      GetStreamer
* @ingroup    SOUND
* 
* @return     SNDSTREAMELEMENT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDSTREAMELEMENT* SNDOPENALFACTORY::GetStreamer()
{
  // create a streaming element and aquire a free source

  SNDOPENALELEMENTSTREAM* streamer = NULL;
  
  streamer = new SNDOPENALELEMENTSTREAM(); // store the streamer somewhere and delete it when destroying openal?
  if(!streamer)
    {
      return NULL;
    }

  streammutex->Lock();
  elementsstream.Add(streamer);
  streammutex->UnLock();

  return (SNDSTREAMELEMENT*)streamer;

  //for(int i = (maxchannels-1); i >= 0; i--)
  //  {
  //    SNDOPENALSOURCE* source = sources.Get(i);
  //    if(!source->IsPLaying())
  //      {
  //        if(!source->GetElement())
  //          {
  //            source->Aquire();
  //            SNDOPENALELEMENTSTREAM* streamer = new SNDOPENALELEMENTSTREAM(); // store the streamer somewhere and delete it when destroying openal?
  //            if(!streamer)
  //              {
  //                return NULL;
  //              }
  //
  //            //streamer->aquiredsource = source;
  //            source->SetElement(streamer);
  //            streamer->SetSource(source);
  //            elementsstream.Add(streamer);
  //            return streamer;
  //          }
  //      }
  //  }
  //
  //return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALFACTORY::ThreadStreaming(void* param)
* @brief      ThreadStreaming
* @ingroup    SOUND
* 
* @param[in]  param : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALFACTORY::ThreadStreaming(void* param)
{
  SNDOPENALFACTORY* sndopenal = (SNDOPENALFACTORY*)param;
  if(!sndopenal) return;

  sndopenal->streammutex->Lock();


  sndopenal->Update();

  XDWORD totalstream = sndopenal->elementsstream.GetSize();
  for(XDWORD i = 0; i < totalstream; i++)
    {
      SNDOPENALELEMENTSTREAM* element = sndopenal->elementsstream.FastGet(i);
      //SNDSTREAMINSTANCE* instance = elementsstream.FastGet(i); // WANT INSTANCES !!
      if(element->GetSource())
        {
          if(element->GetSource()->IsInstancePlaying()) // but same crash as below, instance is no longer a valid pointer
            {
              SNDINSTANCESTREAM* instance = (SNDINSTANCESTREAM*)element->GetSource()->GetInstance();
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
* @fn         void SNDOPENALFACTORY::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    SOUND
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALFACTORY::Clean()
{                                                
  device        = NULL;
 
  context       = NULL;
  maxchannels   = 0;
  mastervolume  = 0.0f;

  streamthread  = NULL;
  streammutex   = NULL;

  isinit        = false;
}


#pragma endregion

