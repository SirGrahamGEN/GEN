/**-------------------------------------------------------------------------------------------------------------------
*
* @file       SNDSource_OpenAL.cpp
*
* @class      SNDSOURCE_OPENAL
* @brief      Sound Open AL source class
* @ingroup    PLATFORM_COMMON
*
* @copyright  GEN Group. All right reserved.
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
*---------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XTrace.h"

#include "SNDFactory_OpenAL.h"
#include "SNDInstance.h"
#include "SNDBuffer_OpenAL.h"
#include "SNDElement_OpenAL.h"

#include "SNDSource_OpenAL.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSOURCE_OPENAL::Stop()
* @brief      Stop
* @ingroup    PLATFORM_COMMON
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SNDSOURCE_OPENAL::Stop()
{
  alSourceStop(source);
  isplaying = false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSOURCE_OPENAL::Pause()
* @brief      Pause
* @ingroup    PLATFORM_COMMON
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SNDSOURCE_OPENAL::Pause()
{
  alSourcePause(source);
  isplaying = true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSOURCE_OPENAL::UnPause()
* @brief      UnPause
* @ingroup    PLATFORM_COMMON
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SNDSOURCE_OPENAL::UnPause()
{
  alSourcePlay(source);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSOURCE_OPENAL::SetLoop(bool loop)
* @brief      SetLoop
* @ingroup    PLATFORM_COMMON
*
* @param[in]  loop : 
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SNDSOURCE_OPENAL::SetLoop(bool loop)
{
  alSourcei(source, AL_LOOPING, loop);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SNDSOURCE_OPENAL::IsPLaying()
* @brief      IsPLaying
* @ingroup    PLATFORM_COMMON
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SNDSOURCE_OPENAL::IsPLaying()
{
  if(isplaying)
    {
      ALint source_state;

      alGetSourcei(source, AL_SOURCE_STATE, &source_state);

      bool oldisplaying = isplaying;

      isplaying = ((source_state == AL_PLAYING) || (source_state == AL_PAUSED));

      if((oldisplaying == true) && (isplaying == false))
      {
        if(instance)
          {
            /*
            SND_XEVENT  event(this, SND_XEVENT_TYPE_STOP);

            event.SetType(SND_XEVENT_TYPE_STOP);

            instance->HandleEvent(&event);
            */
          }
      }

      return isplaying;
    }

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SNDSOURCE_OPENAL::IsStopped()
* @brief      IsStopped
* @ingroup    PLATFORM_COMMON
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SNDSOURCE_OPENAL::IsStopped()
{
  ALint source_state;
  alGetSourcei(source, AL_SOURCE_STATE, &source_state);

  return (source_state == AL_STOPPED) || (source_state == AL_INITIAL);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SNDSOURCE_OPENAL::IsPaused()
* @brief      IsPaused
* @ingroup    PLATFORM_COMMON
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SNDSOURCE_OPENAL::IsPaused()
{
  ALint source_state;

  alGetSourcei(source, AL_SOURCE_STATE, &source_state);

  return source_state == AL_PAUSED;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float SNDSOURCE_OPENAL::GetVolume()
* @brief      GetVolume
* @ingroup    PLATFORM_COMMON
*
* @return     float : 
*
*---------------------------------------------------------------------------------------------------------------------*/
float SNDSOURCE_OPENAL::GetVolume()
{
  
  float volume;

  alGetSourcef(source, AL_GAIN, &volume);

  return volume /  GEN_SNDFACTORY.GetMasterVolume();  
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSOURCE_OPENAL::SetVolume(float volume)
* @brief      SetVolume
* @ingroup    PLATFORM_COMMON
*
* @param[in]  volume : 
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SNDSOURCE_OPENAL::SetVolume(float volume)
{  
  alSourcef(source, AL_GAIN, volume * GEN_SNDFACTORY.GetMasterVolume());
  
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float SNDSOURCE_OPENAL::GetPitch()
* @brief      GetPitch
* @ingroup    PLATFORM_COMMON
*
* @return     float : 
*
*---------------------------------------------------------------------------------------------------------------------*/
float SNDSOURCE_OPENAL::GetPitch()
{
  float pitch;

  alGetSourcef(source, AL_PITCH, &pitch);

  return pitch;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSOURCE_OPENAL::SetPitch(float pitch)
* @brief      SetPitch
* @ingroup    PLATFORM_COMMON
*
* @param[in]  pitch : 
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SNDSOURCE_OPENAL::SetPitch(float pitch)
{
  alSourcef(source, AL_PITCH, pitch);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDELEMENT* SNDSOURCE_OPENAL::GetElement()
* @brief      GetElement
* @ingroup    PLATFORM_COMMON
*
* @return     SNDELEMENT* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
SNDELEMENT* SNDSOURCE_OPENAL::GetElement()                              
{ 
  return this->element;     
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSOURCE_OPENAL::SetElement(SNDELEMENT* element)
* @brief      SetElement
* @ingroup    PLATFORM_COMMON
*
* @param[in]  element : 
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SNDSOURCE_OPENAL::SetElement(SNDELEMENT* element)           
{ 
  this->element = element;  
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSOURCE_OPENAL::SetSecondsOffset(float seconds)
* @brief      SetSecondsOffset
* @ingroup    PLATFORM_COMMON
*
* @param[in]  seconds : 
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SNDSOURCE_OPENAL::SetSecondsOffset(float seconds)
{
  if(element)
    {
      if(seconds <= element->GetDuration())
        {
          alSourcef(source, AL_SEC_OFFSET, seconds);
        }
    }
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSOURCE_OPENAL::SetSamplesOffset(int samples)
* @brief      SetSamplesOffset
* @ingroup    PLATFORM_COMMON
*
* @param[in]  samples : 
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SNDSOURCE_OPENAL::SetSamplesOffset(int samples)
{
  if(element)
    {
      if(samples > element->GetSamples())
        {
          samples = element->GetSamples();
        }

      alSourcei(source, AL_SAMPLE_OFFSET, samples);
    }
}


    
/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSOURCE_OPENAL::SetAquired(bool aquired)
* @brief      SetAquired
* @ingroup    PLATFORM_COMMON
*
* @param[in]  aquired : 
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SNDSOURCE_OPENAL::SetAquired(bool aquired)                  
{ 
  this->aquired = aquired;  
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SNDSOURCE_OPENAL::IsAquired()
* @brief      IsAquired
* @ingroup    PLATFORM_COMMON
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SNDSOURCE_OPENAL::IsAquired()                              
{ 
  return this->aquired;     
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSOURCE_OPENAL::Aquire()
* @brief      Aquire
* @ingroup    PLATFORM_COMMON
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SNDSOURCE_OPENAL::Aquire()                            
{ 
  this->aquired = true;     
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSOURCE_OPENAL::Release()
* @brief      Release
* @ingroup    PLATFORM_COMMON
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SNDSOURCE_OPENAL::Release()                              
{ 
  this->aquired = false;    
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDSOURCE_OPENAL::SNDSOURCE_OPENAL()
* @brief      Constructor
* @ingroup    PLATFORM_COMMON
*
* @return     Does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
SNDSOURCE_OPENAL::SNDSOURCE_OPENAL()
{
  Clean();

  alGenSources(1, &source);
  alSourcef(source, AL_PITCH, 1);
  alSourcef(source, AL_GAIN, 1);
  alSource3f(source, AL_POSITION, 0, 0, 0);
  alSource3f(source, AL_VELOCITY, 0, 0, 0);
  alSourcei(source, AL_LOOPING, AL_FALSE);
  //alSourcef(source, AL_MAX_GAIN, 1000.0f);  
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDSOURCE_OPENAL::~SNDSOURCE_OPENAL()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_COMMON
*
* @return     Does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
SNDSOURCE_OPENAL::~SNDSOURCE_OPENAL()
{
  alDeleteSources(1, &source);

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSOURCE_OPENAL::Play()
* @brief      Play
* @ingroup    PLATFORM_COMMON
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SNDSOURCE_OPENAL::Play()
{
  if(!IsPLaying())
    {
      alSourcePlay(source);
      isplaying = true;
    }
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSOURCE_OPENAL::Play(SNDBUFFER_OPENAL* buffer)
* @brief      Play
* @ingroup    PLATFORM_COMMON
*
* @param[in]  buffer : 
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SNDSOURCE_OPENAL::Play(SNDBUFFER_OPENAL* buffer)
{
  if(!IsPLaying())
    {
      
      alSourcei(source, AL_BUFFER, buffer->buffer);
      alSourcePlay(source);

      isplaying = true;      
    }
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSOURCE_OPENAL::Queue(SSNDBUFFER_OPENAL* buffer)
* @brief      Queue
* @ingroup    PLATFORM_COMMON
*
* @param[in]  buffer : 
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SNDSOURCE_OPENAL::Queue(SNDBUFFER_OPENAL* buffer)
{
  if(buffer)
    {
      
      alSourceQueueBuffers(source, 1, &(buffer->buffer));
      
      //bufferlist.Add(buffer);
    }
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSOURCE_OPENAL::UnQueue(SNDBUFFER_OPENAL* buffer)
* @brief      UnQueue
* @ingroup    PLATFORM_COMMON
*
* @param[in]  buffer : 
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SNDSOURCE_OPENAL::UnQueue(SNDBUFFER_OPENAL* buffer)
{
  alSourceStop(source);

  ALuint ID = 0;

  alSourceUnqueueBuffers(source, 1, &ID);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int SNDSOURCE_OPENAL::GetQueueLength()
* @brief      GetQueueLength
* @ingroup    PLATFORM_COMMON
*
* @return     int : 
*
*---------------------------------------------------------------------------------------------------------------------*/
int SNDSOURCE_OPENAL::GetQueueLength()
{
  int queue = 0;
  alGetSourcei(source, AL_BUFFERS_QUEUED, &queue);
  return queue;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int SNDSOURCE_OPENAL::GetProcessedBuffers()
* @brief      GetProcessedBuffers
* @ingroup    PLATFORM_COMMON
*
* @return     int : 
*
*---------------------------------------------------------------------------------------------------------------------*/
int SNDSOURCE_OPENAL::GetProcessedBuffers()
{
  int processed = 0;
  alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);
  return processed;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSOURCE_OPENAL::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_COMMON
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SNDSOURCE_OPENAL::Clean()
{
  source        = 0;
  element       = NULL;
 
  isplaying     = false;
  aquired       = false;
}