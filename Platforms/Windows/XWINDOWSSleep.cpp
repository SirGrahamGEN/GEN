/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XWINDOWSSleep.cpp
* 
* @class      XWINDOWSSLEEP
* @brief      WINDOWS eXtended Utils Sleep class
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

#include "XWINDOWSSleep.h"

#include <math.h>

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
* @fn         XWINDOWSSLEEP::XWINDOWSSLEEP()
* @brief      Constructor of class
* @ingroup    PLATFORM_WINDOWS
*
* --------------------------------------------------------------------------------------------------------------------*/
XWINDOWSSLEEP::XWINDOWSSLEEP()
{
  Clean();

  QueryPerformanceFrequency(&frequency);

  PCfrequencymilliseconds = (double)(frequency.QuadPart) / 1000.0;
  PCfrequencymicroseconds = (double)(frequency.QuadPart) / 1000000.0;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWINDOWSSLEEP::~XWINDOWSSLEEP()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    PLATFORM_WINDOWS
*
* --------------------------------------------------------------------------------------------------------------------*/
XWINDOWSSLEEP::~XWINDOWSSLEEP()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XWINDOWSSLEEP::Seconds(int seconds)
* @brief      Seconds
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  seconds : seconds to sleep
*
* --------------------------------------------------------------------------------------------------------------------*/
void XWINDOWSSLEEP::Seconds(int seconds)
{
  Sleep(seconds*1000);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XWINDOWSSLEEP::MilliSeconds(int milliseconds)
* @brief      Milli seconds
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  milliseconds : milliseconds to sleep
*
* --------------------------------------------------------------------------------------------------------------------*/
void XWINDOWSSLEEP::MilliSeconds(int milliseconds)
{
  Sleep(milliseconds);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XWINDOWSSLEEP::MicroSeconds(int microseconds)
* @brief      Micro seconds
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  microseconds : microseconds to sleep
*
* --------------------------------------------------------------------------------------------------------------------*/
void XWINDOWSSLEEP::MicroSeconds(int microseconds)
{
  __int64 timeellapsed;
  __int64 timestart;
  __int64 timedelta;

  QueryPerformanceFrequency((LARGE_INTEGER*)(&timedelta));

  __int64 timetowait = (__int64)((XDWORD)timedelta * ((XDWORD)microseconds / 1000000.0f));

  QueryPerformanceCounter ((LARGE_INTEGER*)(&timestart));

  timeellapsed = timestart;

  while(( timeellapsed - timestart ) < timetowait)
   {
     QueryPerformanceCounter( (LARGE_INTEGER*)(&timeellapsed ) );
   };
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XWINDOWSSLEEP::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    PLATFORM_WINDOWS
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XWINDOWSSLEEP::Clean()
{
  PCfrequencymilliseconds = 0.0;
  PCfrequencymicroseconds = 0.0;
}


#pragma endregion

