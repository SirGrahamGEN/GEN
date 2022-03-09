/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XTimer.cpp
*
* @class      XTIMER
* @brief
* @ingroup    UTILS
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
#include <string.h>
#include <math.h>

#include "XBase.h"
#include "XFactory.h"
#include "XDateTime.h"

#include "XTimer.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

#ifdef XTRACE_ACTIVE_VIRTUALCLOCKTICK
XTIMERCLOCK*  xtimerclock = NULL;
#endif


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



#ifdef XTRACE_ACTIVE_VIRTUALCLOCKTICK


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTIMERCLOCK::XTIMERCLOCK()
* @brief      Constructor
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XTIMERCLOCK::XTIMERCLOCK()

{
  Clean();

  xmutexclock = GEN_XFACTORY.CreateMutex();
  if(xmutexclock)
    {
      threadclock = CREATEXTHREAD(XTHREADGROUPID_XTIMERCLOCK, __L("XTIMERCLOCK::XTIMERCLOCK"),ThreadClockFunction,(void*)this);
      if(threadclock) threadclock->Ini();
    }
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTIMERCLOCK::~XTIMERCLOCK()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XTIMERCLOCK::~XTIMERCLOCK()

{
  if(threadclock)
    {
      threadclock->End();
      DELETEXTHREAD(XTHREADGROUPID_XTIMERCLOCK, threadclock);
    }

  if(xmutexclock) GEN_XFACTORY.DeleteMutex(xmutexclock);

  Clean();
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XQWORD XTIMERCLOCK::GetClockTicks()
* @brief      GetClockTicks
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XQWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XQWORD XTIMERCLOCK::GetClockTicks()
{
  if(!xmutexclock) return 0;

  xmutexclock->Lock();

  XQWORD clktks = clockticks;

  xmutexclock->UnLock();

  return clktks;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XTIMERCLOCK::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XTIMERCLOCK::Clean()
{
  clockticks  = 0;

  xmutexclock = NULL;
  threadclock = NULL;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XTIMERCLOCK::ThreadClockFunction(void* data)
* @brief      ThreadClockFunction
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  data :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XTIMERCLOCK::ThreadClockFunction(void* data)
{
  XTIMERCLOCK* timerclock = (XTIMERCLOCK*)data;
  if(!data) return;

  if(timerclock->xmutexclock)
    {
      timerclock->xmutexclock->Lock();

      timerclock->clockticks+=17;

      timerclock->xmutexclock->UnLock();
    }
}


#endif



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTIMER::XTIMER()
* @brief      Constructor
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XTIMER::XTIMER()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTIMER::~XTIMER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XTIMER::~XTIMER()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XTIMER::AddMilliSeconds(XQWORD milliseconds)
* @brief      AddMilliSeconds
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  milliseconds :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XTIMER::AddMilliSeconds(XQWORD milliseconds)
{
  this->more += (milliseconds*1000);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XTIMER::AddSeconds(XQWORD seconds)
* @brief      AddSeconds
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  seconds :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XTIMER::AddSeconds(XQWORD seconds)
{
  AddMilliSeconds(seconds * 1000);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XTIMER::SetMilliSeconds(XQWORD milliseconds)
* @brief      SetMilliSeconds
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  milliseconds :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XTIMER::SetMilliSeconds(XQWORD milliseconds)
{
  Reset();

  AddMilliSeconds(milliseconds);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XTIMER::Reset()
* @brief      Reset
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XTIMER::Reset()
{
  more      = 0;
  last      = GetMicroSecondsTickCounter();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XTIMER::GetMeasureHours()
* @brief      GetMeasureHours
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD XTIMER::GetMeasureHours()
{
  XQWORD hours = GetMeasureMilliSeconds();

  hours/=1000;
  hours/=60;
  hours/=60;

  return (XDWORD)hours;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XTIMER::GetMeasureMinutes()
* @brief      GetMeasureMinutes
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD XTIMER::GetMeasureMinutes()
{
  XQWORD minutes = GetMeasureMilliSeconds();

  minutes/=1000;
  minutes/=60;

  return (XDWORD)minutes;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XTIMER::GetMeasureSeconds()
* @brief      GetMeasureSeconds
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD XTIMER::GetMeasureSeconds()
{
  XQWORD seconds = GetMeasureMilliSeconds();

  seconds/=1000L;

  return (XDWORD)seconds;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XQWORD XTIMER::GetMeasureMilliSeconds()
* @brief      GetMeasureMilliSeconds
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XQWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XQWORD XTIMER::GetMeasureMilliSeconds()
{
  XQWORD milliseconds = GetMeasureMicroSeconds();

  milliseconds/=1000L;

  return (XDWORD)milliseconds;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XQWORD XTIMER::GetMeasureMicroSeconds()
* @brief      GetMeasureMicroSeconds
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XQWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XQWORD XTIMER::GetMeasureMicroSeconds()
{
  XQWORD  elapsed;
  XQWORD  current = GetMicroSecondsTickCounter();

  elapsed = (XQWORD)((current-last) + more);

  return elapsed;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTIMER::GetMeasureToDate(XDATETIME* xdatetime)
* @brief      GetMeasureToDate
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  xdatetime :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XTIMER::GetMeasureToDate(XDATETIME* xdatetime)
{
  if(!xdatetime) return false;

  XQWORD allseconds = GetMeasureSeconds();

  xdatetime->SetDateFromSeconds(0);
  xdatetime->AddSeconds(allseconds);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTIMER::GetMeasureString(XSTRING& measure,bool large)
* @brief      GetMeasureString
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  measure :
* @param[in]  large :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XTIMER::GetMeasureString(XSTRING& measure,bool large)
{
  XQWORD allseconds = GetMeasureSeconds();

  XDWORD years   = XDATETIME_SECONDSYEARS(allseconds);
  XDWORD months  = XDATETIME_SECONDSMONTHS(allseconds);
  XDWORD days    = XDATETIME_SECONDSDAYS(allseconds);

  XDWORD hours   = XDATETIME_SECONDSHOURS(allseconds);
  XDWORD minutes = XDATETIME_SECONDSMINUTES(allseconds);
  XDWORD seconds = XDATETIME_SECONDSSECONDS(allseconds);

  measure.Empty();

  XSTRING string;

  for(int c=0;c<6;c++)
    {
      string.Empty();

      switch(c)
        {
          case 0: if(!years) break;
                  if(years>1) string.Format(__L("%d a\xf1os"), years); else string.Format(__L("un a\xf1o"));
                  break;

          case 1: if(!months) break;
                  if(months>1) string.Format(__L("%d meses"), months);  else string.Format(__L("un mes"));
                  break;

          case 2: if(!days) break;
                  if(days>1) string.Format(__L("%d dias"), days); else string.Format(__L("un dia"));
                  break;

          case 3: if(large)
                    {
                      if(!hours) break;
                      if(hours>1) string.Format(__L("%d horas"), hours); else string.Format(__L("una hora"));
                    }
                   else
                    {
                      string.Format(__L("%02d"), hours);
                    }
                  break;

          case 4: if(large)
                    {
                      if(!minutes) break;
                      if(minutes>1) string.Format(__L("%d minutos"), minutes); else string.Format(__L("un minuto"));
                    }
                   else
                    {
                      string.Format(__L("%02d"), minutes);
                    }
                  break;

          case 5: if(large)
                    {
                      if(!seconds) break;
                      if(seconds>1) string.Format(__L("%d segundos"), seconds); else string.Format(__L("un segundo"));
                    }
                   else
                    {
                      string.Format(__L("%02d"), seconds);
                    }
                  break;

        }

      if((large)||(c<=3))
        {
          if(!string.IsEmpty())
            {
              if(!measure.IsEmpty()) measure += ", ";
              measure += string;
            }
        }
       else
        {
          if(!string.IsEmpty())
            {
              if(!measure.IsEmpty()) measure += ":";
              measure += string;
            }
        }
    }

  if(measure.IsEmpty())
    {
      measure.Format(__L("0 segundos"));
      return false;
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XQWORD XTIMER::GetMicroSecondsTickCounter()
* @brief      GetMicroSecondsTickCounter
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XQWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XQWORD XTIMER::GetMicroSecondsTickCounter()
{
  return 0;
}




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XTIMER::GetModule(char* module)
* @brief      GetModule
* @ingroup    UTILS
* 
* @author     Abraham J. Velez 
* @date       08/03/2022 20:21:09
* 
* @param[in]  module : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
#ifdef _DEBUG
void XTIMER::GetModule(char* module)
{
  this->module = module;
}
#endif


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XTIMER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XTIMER::Clean()
{
  last = 0L;
  more = 0L;
}



