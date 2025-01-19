/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XLINUXDateTime.cpp
* 
* @class      XLINUXDATETIME
* @brief      LINUX eXtended Utils Date Time class
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

#include "XLINUXDateTime.h"

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
* @fn         XLINUXDATETIME::XLINUXDATETIME()
* @brief      Constructor of class
* @ingroup    PLATFORM_LINUX
*
* --------------------------------------------------------------------------------------------------------------------*/
XLINUXDATETIME::XLINUXDATETIME()
{
  year          = 0;
  month         = 0;
  day           = 0;
  hours         = 0;
  minutes       = 0;
  seconds       = 0;
  milliseconds  = 0;

  GetActualDateTime(this);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLINUXDATETIME::~XLINUXDATETIME()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    PLATFORM_LINUX
*
* --------------------------------------------------------------------------------------------------------------------*/
XLINUXDATETIME::~XLINUXDATETIME()
{
 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XLINUXDATETIME::Read(bool islocal)
* @brief      Read
* @ingroup    PLATFORM_LINUX
* 
* @param[in]  islocal : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XLINUXDATETIME::Read(bool islocal)
{
  GetActualDateTime(this, islocal);

  bool status = IsValidDate();
  if(status)
    {
       SetIsLocal(islocal);
    }

  return IsValidDate();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXDATETIME::Write()
* @brief      Write
* @ingroup    PLATFORM_LINUX
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLINUXDATETIME::Write(bool islocal)
{
  if(IsValidDate())
    {
      return false;
    }

  SetActualDateTime(this, islocal);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XLINUXDATETIME::GetFileDateTime(XPATH& xpath, void* tmzip, XDWORD* dt)
* @brief      Get file date time
* @ingroup    PLATFORM_LINUX
*
* @param[in]  xpath : 
* @param[in]  tmzip : 
* @param[in]  dt : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XLINUXDATETIME::GetFileDateTime(XPATH& xpath, void* tmzip, XDWORD* dt)
{
  typedef struct tm_zip_s
  {
    XDWORD tm_sec;      // seconds after the minute - [0,59]
    XDWORD tm_min;      // minutes after the hour - [0,59]
    XDWORD tm_hour;     // hours since midnight - [0,23]
    XDWORD tm_mday;     // day of the month - [1,31]
    XDWORD tm_mon;      // months since January - [0,11] 
    XDWORD tm_year;     // years - [1980..2044] 

  } tm_zip;


  XPATH        xpathfile;
  struct stat  s;
  struct tm*   filedate;
  time_t       tm_t       = 0;
  tm_zip*      tmzip2     = (tm_zip*)tmzip;
  bool         status     = false;

  if(xpath.IsEmpty())     return false;
  xpathfile = xpath;

  xpathfile.Slash_Delete();
  
  XBUFFER charstr;
  
  xpathfile.ConvertToASCII(charstr);
  
  if(stat(charstr.GetPtrChar(), &s)==0)
    {
      tm_t = s.st_mtime;
      status = true;
    }

  filedate = localtime(&tm_t);
  
  tmzip2->tm_year = filedate->tm_year + 1900;
  tmzip2->tm_mon  = filedate->tm_mon;
  tmzip2->tm_mday = filedate->tm_mday;
  tmzip2->tm_hour = filedate->tm_hour;
  tmzip2->tm_min  = filedate->tm_min;
  tmzip2->tm_sec  = filedate->tm_sec;
  
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XLINUXDATETIME::GetFileDateTime(XPATH& xpath)
* @brief      Get file date time
* @ingroup    PLATFORM_LINUX
*
* @param[in]  xpath : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XLINUXDATETIME::GetFileDateTime(XPATH& xpath)
{
  XPATH        xpathfile;
  struct stat  s;
  struct tm*   filedate;
  time_t       tm_t       = 0;
  bool         status     = false;

  if(xpath.IsEmpty())     return false;
  xpathfile = xpath;

  xpathfile.Slash_Delete();

  XBUFFER charstr;
  
  xpathfile.ConvertToASCII(charstr);  
  if(stat(charstr.GetPtrChar(), &s)==0)
    {
      tm_t = s.st_mtime;
      status = true;
    }

  filedate = localtime(&tm_t);

  year          = filedate->tm_year + 1900;
  month         = filedate->tm_mon;
  day           = filedate->tm_mday;
  hours         = filedate->tm_hour;
  minutes       = filedate->tm_min;
  seconds       = filedate->tm_sec;
  milliseconds  = 0;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XLINUXDATETIME::GetMeridianDifference()
* @brief      Get meridian difference
* @ingroup    PLATFORM_LINUX
*
* @return     int : 
*
* --------------------------------------------------------------------------------------------------------------------*/
int XLINUXDATETIME::GetMeridianDifference()
{
  time_t    t  = time(NULL);
  struct tm lt = { 0 };

  localtime_r(&t, &lt);

  return (lt.tm_gmtoff/60) + (lt.tm_isdst?-60:0);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXDATETIME::IsDayLigthSavingTime(int* bias)
* @brief      Is day ligth saving time
* @ingroup    PLATFORM_LINUX
*
* @param[out] bias : difference hour
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLINUXDATETIME::IsDayLigthSavingTime(int* bias)
{
  struct tm*  currentdate;
  long        currentdatesecs;

  time(&currentdatesecs);
  currentdate = localtime(&currentdatesecs);

  if(bias) (*bias) = 0;

  bool dls = currentdate->tm_isdst?true:false;

  if(dls)
    {
      if(bias) (*bias) = -60;
    }

  return currentdate->tm_isdst?true:false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XLINUXDATETIME::GetActualDateTime(XLINUXDATETIME* timed, bool islocal)
* @brief      Get actual date time
* @ingroup    PLATFORM_LINUX
* 
* @param[in]  timed : 
* @param[in]  islocal : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XLINUXDATETIME::GetActualDateTime(XLINUXDATETIME* timed, bool islocal)
{
  time_t      now;
  struct tm*  datatime;

  now = time(0);

  if(islocal)
    {
      datatime = localtime(&now);
    }
   else 
    {
      datatime = gmtime(&now);
    }

  if(!datatime) return;

  timed->year           = datatime->tm_year + 1900;
  timed->month          = datatime->tm_mon+1;
  timed->day            = datatime->tm_mday;
  timed->hours          = datatime->tm_hour;
  timed->minutes        = datatime->tm_min;
  timed->seconds        = datatime->tm_sec;

  struct timeval tv;
  gettimeofday(&tv, NULL);

  timed->milliseconds   = (tv.tv_usec /1000);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XLINUXDATETIME::SetActualDateTime(XLINUXDATETIME* timed, bool islocal)
* @brief      Set actual date time
* @ingroup    PLATFORM_LINUX
* 
* @param[in]  timed : 
* @param[in]  islocal : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XLINUXDATETIME::SetActualDateTime(XLINUXDATETIME* timed, bool islocal)
{
  struct tm      mytime;
  struct timeval systime;

  mytime.tm_sec   = timed->seconds;       // Seconds
  mytime.tm_min   = timed->minutes;       // Minutes
  mytime.tm_hour  = timed->hours;         // Hours
  mytime.tm_mday  = timed->day;           // Day of Month
  mytime.tm_mon   = timed->month - 1;     // Month
  mytime.tm_year  = timed->year  - 1900;  // Year
  mytime.tm_isdst = IsDayLigthSavingTime();

  systime.tv_sec  = mktime(&mytime);
  systime.tv_usec = 0;

  settimeofday(&systime, NULL);
}


#pragma endregion

