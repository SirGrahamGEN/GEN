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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "SNDNote.h"

#include "XFactory.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDNOTE::SNDNOTE()
* @brief      Constructor of class
* @ingroup    SOUND
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDNOTE::SNDNOTE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDNOTE::~SNDNOTE()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    SOUND
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDNOTE::~SNDNOTE()
{
  Clean();  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD SNDNOTE::GetFrequency()
* @brief      Get frequency
* @ingroup    SOUND
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD SNDNOTE::GetFrequency()
{
  return frequency;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDNOTE::SetFrequency(XDWORD frequency)
* @brief      Set frequency
* @ingroup    SOUND
* 
* @param[in]  frequency : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDNOTE::SetFrequency(XDWORD frequency)
{
  this->frequency = frequency;

  return true;
}

  
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD SNDNOTE::GetDuration()
* @brief      Get duration
* @ingroup    SOUND
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD SNDNOTE::GetDuration()
{
  return duration;
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD SNDNOTE::SetDuration(XDWORD duration)
* @brief      Set duration
* @ingroup    SOUND
* 
* @param[in]  duration : 
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD SNDNOTE::SetDuration(XDWORD duration)
{
  this->duration = duration;
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDNOTE::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    SOUND
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDNOTE::Clean()
{
  frequency   = 0;
  duration    = 0;
}


#pragma endregion


