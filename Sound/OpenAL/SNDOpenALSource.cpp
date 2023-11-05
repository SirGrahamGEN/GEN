/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       SNDOpenALSource.cpp
* 
* @class      SNDOPENALSOURCE
* @brief      Sound OpenAL Source class
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

#include "SNDOpenALSource.h"

#include "XTrace.h"

#include "SNDFactory_XEvent.h"
#include "SNDOpenALFactory.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDOPENALSOURCE::SNDOPENALSOURCE()
* @brief      Constructor
* @ingroup    SOUND
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDOPENALSOURCE::SNDOPENALSOURCE()
{
  Clean();

  alGenSources(1    , &source);
  alSourcef(source  , AL_PITCH, 1);
  alSourcef(source  , AL_GAIN, 1);
  alSource3f(source , AL_POSITION, 0, 0, 0);
  alSource3f(source , AL_VELOCITY, 0, 0, 0);
  alSourcei(source  , AL_LOOPING, AL_FALSE);
//alSourcef(source  , AL_MAX_GAIN, 1000.0f); 

  albuffer.Create();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDOPENALSOURCE::~SNDOPENALSOURCE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    SOUND
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDOPENALSOURCE::~SNDOPENALSOURCE()
{
  alDeleteSources(1, &source); 

  albuffer.Delete();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDOPENALBUFFER* SNDOPENALSOURCE::GetBuffer()
* @brief      GetBuffer
* @ingroup    SOUND
* 
* @return     SNDOPENALBUFFER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDOPENALBUFFER* SNDOPENALSOURCE::GetBuffer()
{
  return &albuffer;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALSOURCE::Stop()
* @brief      Stop
* @ingroup    SOUND
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALSOURCE::Stop()
{
  alSourceStopv(1, &source);
  isplaying = false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALSOURCE::Pause()
* @brief      Pause
* @ingroup    SOUND
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALSOURCE::Pause()
{
  alSourcePause(source);
  isplaying = true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALSOURCE::UnPause()
* @brief      UnPause
* @ingroup    SOUND
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALSOURCE::UnPause()
{
  alSourcePlay(source);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDOPENALSOURCE::IsPLaying()
* @brief      IsPLaying
* @ingroup    SOUND
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDOPENALSOURCE::IsPLaying()
{
  if(isplaying)
    {
      ALint source_state;

      alGetSourcei(source, AL_SOURCE_STATE, &source_state);

      bool _isplaying = isplaying;

      isplaying = ((source_state == AL_PLAYING) || (source_state == AL_PAUSED));

      return isplaying;
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDOPENALSOURCE::IsStopped()
* @brief      IsStopped
* @ingroup    SOUND
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDOPENALSOURCE::IsStopped()
{
  ALint source_state;
  alGetSourcei(source, AL_SOURCE_STATE, &source_state);

  return (source_state == AL_STOPPED) || (source_state == AL_INITIAL);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDOPENALSOURCE::IsPaused()
* @brief      IsPaused
* @ingroup    SOUND
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDOPENALSOURCE::IsPaused()
{
  ALint source_state;

  alGetSourcei(source, AL_SOURCE_STATE, &source_state);

  return source_state == AL_PAUSED;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALSOURCE::SetInLoop(bool inloop)
* @brief      SetInLoop
* @ingroup    SOUND
* 
* @param[in]  inloop : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALSOURCE::SetInLoop(bool inloop)
{
  alSourcei(source, AL_LOOPING, inloop);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int SNDOPENALSOURCE::GetVolume()
* @brief      GetVolume
* @ingroup    SOUND
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int SNDOPENALSOURCE::GetVolume()
{  
  float fvolume = 0.0f;
  int   rvolume = 0;
  int   volume  = 0;

  alGetSourcef(source, AL_GAIN, &fvolume);

  volume = (int)(fvolume * 100);

  rvolume = (volume * GEN_SNDFACTORY.MasterVolume_Get())/100;

  return rvolume;  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALSOURCE::SetVolume(int volume)
* @brief      SetVolume
* @ingroup    SOUND
* 
* @param[in]  volume : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDOPENALSOURCE::SetVolume(int volume)
{  
  int   rvolume = (volume * GEN_SNDFACTORY.MasterVolume_Get())/100;
  float fvolume = (rvolume /100.0f);

  alSourcef(source, AL_GAIN, fvolume); 

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         float SNDOPENALSOURCE::GetPitch()
* @brief      GetPitch
* @ingroup    SOUND
* 
* @return     float : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
float SNDOPENALSOURCE::GetPitch()
{
  float pitch;

  alGetSourcef(source, AL_PITCH, &pitch);

  return pitch;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALSOURCE::SetPitch(float pitch)
* @brief      SetPitch
* @ingroup    SOUND
* 
* @param[in]  pitch : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALSOURCE::SetPitch(float pitch)
{
  alSourcef(source, AL_PITCH, pitch);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALSOURCE::Play()
* @brief      Play
* @ingroup    SOUND
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALSOURCE::Play()
{
  if(!IsPLaying())
    {     
      alSourcei(source, AL_BUFFER, albuffer.GetHandle());
      alSourcePlay(source);

      isplaying = true;      
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALSOURCE::ResetPlay()
* @brief      ResetPlay
* @ingroup    SOUND
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALSOURCE::ResetPlay()
{
  alSourcef(source, AL_SEC_OFFSET, 0.0f);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALSOURCE::SetSecondsOffset(float seconds)
* @brief      SetSecondsOffset
* @ingroup    SOUND
* 
* @param[in]  seconds : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALSOURCE::SetSecondsOffset(float seconds)
{
  /*
  if(element)
    {
      if(seconds <= element->GetDuration())
        {
          alSourcef(source, AL_SEC_OFFSET, seconds);
        }
    }
  */
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALSOURCE::SetSamplesOffset(int samples)
* @brief      SetSamplesOffset
* @ingroup    SOUND
* 
* @param[in]  samples : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALSOURCE::SetSamplesOffset(int samples)
{
  /*
  if(element)
    {
      if(samples > element->GetSamples())
        {
          samples = element->GetSamples();
        }

      alSourcei(source, AL_SAMPLE_OFFSET, samples);
    }
  */
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALSOURCE::SetAquired(bool aquired)
* @brief      SetAquired
* @ingroup    SOUND
* 
* @param[in]  aquired : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALSOURCE::SetAquired(bool aquired)
{ 
  this->aquired = aquired;  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDOPENALSOURCE::IsAquired()
* @brief      IsAquired
* @ingroup    SOUND
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDOPENALSOURCE::IsAquired()
{ 
  return this->aquired;     
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALSOURCE::Aquire()
* @brief      Aquire
* @ingroup    SOUND
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALSOURCE::Aquire()
{ 
  this->aquired = true;     
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALSOURCE::Release()
* @brief      Release
* @ingroup    SOUND
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALSOURCE::Release()
{ 
  this->aquired = false;    
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALSOURCE::Queue(SNDOPENALBUFFER* buffer)
* @brief      Queue
* @ingroup    SOUND
* 
* @param[in]  buffer : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALSOURCE::Queue()
{
  ALuint handle = albuffer.GetHandle();
  alSourceQueueBuffers(source, 1, &handle);             

  albuffer.SetHandle(handle);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALSOURCE::UnQueue(SNDOPENALBUFFER* buffer)
* @brief      UnQueue
* @ingroup    SOUND
* 
* @param[in]  buffer : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALSOURCE::UnQueue()
{
  alSourceStop(source);

  ALuint ID = 0;
  alSourceUnqueueBuffers(source, 1, &ID);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int SNDOPENALSOURCE::GetQueueLength()
* @brief      GetQueueLength
* @ingroup    SOUND
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int SNDOPENALSOURCE::GetQueueLength()
{
  int queue = 0;
  alGetSourcei(source, AL_BUFFERS_QUEUED, &queue);
  return queue;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int SNDOPENALSOURCE::GetProcessedBuffers()
* @brief      GetProcessedBuffers
* @ingroup    SOUND
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int SNDOPENALSOURCE::GetProcessedBuffers()
{
  int processed = 0;
  alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);
  return processed;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALSOURCE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    SOUND
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALSOURCE::Clean()
{
  source        = 0;
  
  isplaying     = false;
  aquired       = false;
}


#pragma endregion

