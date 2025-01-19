/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XLINUXSleep.cpp
* 
* @class      XLINUXSLEEP
* @brief      LINUX eXtended Utils Sleep class
* @ingroup    PLATFORM_LINUX
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

#include "XLINUXSleep.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/rtc.h>

#include "XTrace.h"
#include "XLINUXFile.h"

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
* @fn         XLINUXSLEEP::XLINUXSLEEP()
* @brief      Constructor of class
* @ingroup    PLATFORM_LINUX
*
* --------------------------------------------------------------------------------------------------------------------*/
XLINUXSLEEP::XLINUXSLEEP()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLINUXSLEEP::~XLINUXSLEEP()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    PLATFORM_LINUX
*
* --------------------------------------------------------------------------------------------------------------------*/
XLINUXSLEEP::~XLINUXSLEEP()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XLINUXSLEEP::Seconds(int seconds)
* @brief      Seconds
* @ingroup    PLATFORM_LINUX
*
* @param[in]  seconds : n seconds to sleep
*
* --------------------------------------------------------------------------------------------------------------------*/
void XLINUXSLEEP::Seconds(int seconds)
{
  sleep(seconds);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XLINUXSLEEP::MilliSeconds(int milliseconds)
* @brief      Milli seconds
* @ingroup    PLATFORM_LINUX
*
* @param[in]  milliseconds : n milliseconds to sleep
*
* --------------------------------------------------------------------------------------------------------------------*/
void XLINUXSLEEP::MilliSeconds(int milliseconds)
{
  usleep(milliseconds*1000);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XLINUXSLEEP::MicroSeconds(int microseconds)
* @brief      Micro seconds
* @ingroup    PLATFORM_LINUX
*
* @param[in]  microseconds : n microseconds to sleep
*
* --------------------------------------------------------------------------------------------------------------------*/
void XLINUXSLEEP::MicroSeconds(int microseconds)
{
  usleep(microseconds);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XLINUXSLEEP::NanoSeconds(int nanoseconds)
* @brief      Nano seconds
* @ingroup    PLATFORM_LINUX
*
* @param[in]  nanoseconds : n nanoseconds to sleep
*
* --------------------------------------------------------------------------------------------------------------------*/
void XLINUXSLEEP::NanoSeconds(int nanoseconds)
{
  struct timespec time  = { 0, nanoseconds };
  struct timespec time2 = { 0, 0           };

  nanosleep(&time , &time2);

  /*
  struct timespec delay = { nanoseconds / 1000000000, nanoseconds % 1000000000 };

  pselect(0, NULL, NULL, NULL, &delay, NULL);
  */
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XLINUXSLEEP::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    PLATFORM_LINUX
*
* --------------------------------------------------------------------------------------------------------------------*/
void XLINUXSLEEP::Clean()
{

}


#pragma endregion

