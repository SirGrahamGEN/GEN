/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XWINDOWSTimer.cpp
* 
* @class      XWINDOWSTIMER
* @brief      WINDOWS eXtended Utils Timer class
* @ingroup    PLATFORM_WINDOWS
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

#include "XWINDOWSTimer.h"

#include <math.h>

#include "XString.h"
#include "XTrace.h"
#include "XPath.h"

#include "XWINDOWSTimer.h"

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
* @fn         XWINDOWSTIMER::XWINDOWSTIMER()
* @brief      Constructor of class
* @ingroup    PLATFORM_WINDOWS
*
* --------------------------------------------------------------------------------------------------------------------*/
XWINDOWSTIMER::XWINDOWSTIMER()
{
  Clean();

  QueryPerformanceFrequency(&frequency);

  PCfrequencymilliseconds = (double)(frequency.QuadPart) / 1000.0;
  PCfrequencymicroseconds = (double)(frequency.QuadPart) / 1000000.0;

  Reset();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWINDOWSTIMER::~XWINDOWSTIMER()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    PLATFORM_WINDOWS
*
* --------------------------------------------------------------------------------------------------------------------*/
XWINDOWSTIMER::~XWINDOWSTIMER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XQWORD XWINDOWSTIMER::GetMicroSecondsTickCounter()
* @brief      Get micro seconds tick counter
* @ingroup    PLATFORM_WINDOWS
*
* @return     XQWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XQWORD XWINDOWSTIMER::GetMicroSecondsTickCounter()
{
  #ifdef XTRACE_ACTIVE_VIRTUALCLOCKTICK
  if(!xtimerclock) return 0;
  return xtimerclock->GetClockTicks();
  #else

  if(!PCfrequencymilliseconds) return 0;

  LARGE_INTEGER ticks;
  XQWORD        microseconds = 0;

  QueryPerformanceCounter(&ticks);
  if(frequency.QuadPart) microseconds = (XQWORD)(ticks.QuadPart / PCfrequencymicroseconds);

  return microseconds;

  #endif
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XWINDOWSTIMER::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    PLATFORM_WINDOWS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XWINDOWSTIMER::Clean()
{
  PCfrequencymilliseconds = 0.0;
  PCfrequencymicroseconds = 0.0;
}


#pragma endregion
