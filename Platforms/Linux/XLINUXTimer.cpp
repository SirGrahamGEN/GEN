/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XLINUXTimer.cpp
*
* @class      XLINUXTIMER
* @brief      eXtended LINUX Timer class
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @copyright  Copyright(c) 2008 - 2016 GEN Group.
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

#include "XLINUXTimer.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLINUXTIMER::XLINUXTIMER()
* @brief      Constructor
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XLINUXTIMER::XLINUXTIMER()
{
  Reset();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLINUXTIMER::~XLINUXTIMER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XLINUXTIMER::~XLINUXTIMER()

{

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XQWORD XLINUXTIMER::GetMicroSecondsTickCounter()
* @brief      Get MicroSeconds Tick Counter
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XQWORD : micro seconds
*
*---------------------------------------------------------------------------------------------------------------------*/
XQWORD XLINUXTIMER::GetMicroSecondsTickCounter()
{
  /*
  struct timeval t1;
  XQWORD         elapsedtime;

  gettimeofday(&t1, NULL);

  elapsedtime  = (t1.tv_sec * 1000000.0);    // sec to ms
  elapsedtime += (t1.tv_usec / 1000.0);      // us to ms

  return elapsedtime;
  */

  XQWORD elapsedtime = 0;
  struct timespec t1;

  #ifdef CLOCK_MONOTONIC
  clock_gettime(CLOCK_MONOTONIC, &t1);
  #else
  clock_gettime(CLOCK_REALTIME, &t1);
  #endif

  elapsedtime = (XQWORD)(((double)(t1.tv_sec) * 1000000) + (double)(t1.tv_nsec/1000)); // to us

  return elapsedtime;
}



