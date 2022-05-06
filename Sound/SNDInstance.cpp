/**-------------------------------------------------------------------------------------------------------------------
*
* @file       SNDInstance.cpp
*
* @class      SNDINSTANCE
* @brief      Sound instance of a playing sound class
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "SNDSource.h"
#include "SNDElement.h"
#include "SND_XEvent.h"


#include "SNDInstance.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/








/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDINSTANCE::SNDINSTANCE(SNDSOURCE* source, SNDELEMENT* element)
* @brief      Constructor
* @ingroup    SOUND
*
* @param[in]  SNDSOURCE* : 
* @param[in]   SNDELEMENT* element : 
*
* @return     Does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDINSTANCE::SNDINSTANCE(SNDSOURCE* source, SNDELEMENT* element)
{
  Clean();

  this->source    = source;
  this->element   = element;

  ismanaged       = true;           // if managed it will mark itself for deletion
  isplaying       = true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDINSTANCE::~SNDINSTANCE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    SOUND
*
* @return     Does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDINSTANCE::~SNDINSTANCE()
{
  Clean();
}




SNDSOURCE* SNDINSTANCE::GetSource()
{
  return source;
}



SNDELEMENT* SNDINSTANCE::GetElement()
{
  return element;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SNDINSTANCE::IsPlaying()
* @brief      IsPlaying
* @ingroup    SOUND
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDINSTANCE::IsPlaying()
{
  return isplaying;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SNDINSTANCE::IsPaused()
* @brief      IsPaused
* @ingroup    SOUND
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDINSTANCE::IsPaused()
{
  return ispaused;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SNDINSTANCE::Stop()
* @brief      Stop
* @ingroup    SOUND
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDINSTANCE::Stop()
{
  if(isplaying)
    {
      source->Stop();
    }
  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SNDINSTANCE::Pause()
* @brief      Pause
* @ingroup    SOUND
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDINSTANCE::Pause()
{
  if(ispaused && isplaying)
    {
      source->Pause();
    }
  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SNDINSTANCE::UnPause()
* @brief      UnPause
* @ingroup    SOUND
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDINSTANCE::UnPause()
{
  if(!ispaused && isplaying)
    {
      source->UnPause();
    }
  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float SNDINSTANCE::GetVolume()
* @brief      GetVolume
* @ingroup    SOUND
*
* @return     float : 
*
* --------------------------------------------------------------------------------------------------------------------*/
float SNDINSTANCE::GetVolume()
{
  if(isplaying)
    {
      return source->GetVolume();
    }

  return 0.0f;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDINSTANCE::SetVolume(float volume)
* @brief      SetVolume
* @ingroup    SOUND
*
* @param[in]  volume : 
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDINSTANCE::SetVolume(float volume)
{
  if(isplaying)
    {
      source->SetVolume(volume);
    }
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float SNDINSTANCE::GetPitch()
* @brief      GetPitch
* @ingroup    SOUND
*
* @return     float : 
*
* --------------------------------------------------------------------------------------------------------------------*/
float SNDINSTANCE::GetPitch()
{
  if(isplaying)
    {
      return source->GetPitch();
    }

  return 0.0f;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDINSTANCE::SetPitch(float pitch)
* @brief      SetPitch
* @ingroup    SOUND
*
* @param[in]  pitch : 
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDINSTANCE::SetPitch(float pitch)
{
  if(isplaying)
    {
      source->SetPitch(pitch);
    }
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SNDINSTANCE::GetIsManaged()
* @brief      GetIsManaged
* @ingroup    SOUND
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDINSTANCE::GetIsManaged()
{
  return ismanaged;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDINSTANCE::SetIsManaged(bool ismanaged)
* @brief      SetIsManaged
* @ingroup    SOUND
*
* @param[in]  ismanaged : 
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDINSTANCE::SetIsManaged(bool ismanaged)
{
  this->ismanaged = ismanaged;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDINSTANCE::HandleEvent(XEVENT* xevent)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    SOUND
*
* @param[in]  xevent : 
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDINSTANCE::HandleEvent(XEVENT* xevent)
{
  if(xevent->GetEventType() == XEVENT_TYPE_SOUND)
    {
      SND_XEVENT* event = (SND_XEVENT*)xevent;

      if(SND_XEVENT_TYPE_PLAY != event->GetType())
        {
          //isplaying = source->IsPLaying();

          isplaying = false;
          ispaused = source->IsPaused();

          if(!isplaying && ismanaged)
            {
              //source->SetInstance(NULL); // this breaks element instance and my logic, need to find new ways to handle it

              // abraham.
              //sndsystem->MarkInstanceForDeletion(this);
            }

        }
    }
}


 
/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDINSTANCE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    SOUND
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDINSTANCE::Clean()
{
  source      = NULL;
  element     = NULL;

  isplaying   = false;
  ispaused    = false;
  ismanaged   = false;
}
;

