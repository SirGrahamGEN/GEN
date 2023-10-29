/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       SNDNote.cpp
* 
* @class      SNDNOTE
* @brief      Sound Note class
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

#include "SNDNote.h"

#include "XFactory.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDNOTE::SNDNOTE()
* @brief      Constructor
* @ingroup    SOUND
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDNOTE::SNDNOTE()
{
  Clean();

  timerplay = GEN_XFACTORY.CreateTimer();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDNOTE::~SNDNOTE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    SOUND
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDNOTE::~SNDNOTE()
{
  if(timerplay)
    {
      GEN_XFACTORY.DeleteTimer(timerplay);
    }

  Clean();  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         float SNDNOTE::GetFrequency()
* @brief      GetFrequency
* @ingroup    SOUND
* 
* @return     float : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
float SNDNOTE::GetFrequency()
{
  return frequency;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDNOTE::SetFrequency(float frequency)
* @brief      SetFrequency
* @ingroup    SOUND
* 
* @param[in]  frequency : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDNOTE::SetFrequency(float frequency)
{
  this->frequency = frequency;

  return true;
}

  
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         float SNDNOTE::GetDuration()
* @brief      GetDuration
* @ingroup    SOUND
* 
* @return     float : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
float SNDNOTE::GetDuration()
{
  return duration;
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         float SNDNOTE::SetDuration(float duration)
* @brief      SetDuration
* @ingroup    SOUND
* 
* @param[in]  duration : 
* 
* @return     float : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
float SNDNOTE::SetDuration(float duration)
{
  this->duration = duration;
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XTIMER* SNDNOTE::GetTimerPlay()
* @brief      GetTimerPlay
* @ingroup    SOUND
* 
* @return     XTIMER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XTIMER* SNDNOTE::GetTimerPlay()
{
  return timerplay;  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDNOTE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    SOUND
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDNOTE::Clean()
{
  frequency   = 0.0f;
  duration    = 0.0f;

  timerplay   = NULL;
}


#pragma endregion


