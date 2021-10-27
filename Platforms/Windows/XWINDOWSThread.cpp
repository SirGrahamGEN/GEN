/**-------------------------------------------------------------------------------------------------------------------
*
* @file        XWINDOWSThread.cpp
*
* @class       XWINDOWSTHREAD
* @brief       eXtended WINDOWS Thread class
* @ingroup     PLATFORM_WINDOWS
*
* @author      Abraham J. Velez
* @date       01/03/2016 12:00
*
* @copyright   Copyright(c) 2008 - 2016 GEN Group.
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

#include <windows.h>
#include <process.h>

#include "XTimer.h"
#include "XTrace.h"

#ifndef BUILDER
#include "MainProcWINDOWS.h"
#endif

#include "XWINDOWSThread.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWINDOWSMUTEX::XWINDOWSMUTEX()
* @brief      Constructor
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XWINDOWSMUTEX::XWINDOWSMUTEX()
{
  Clean();

  mxhandle = CreateMutex( NULL, FALSE, NULL );
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWINDOWSMUTEX::~XWINDOWSMUTEX()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XWINDOWSMUTEX::~XWINDOWSMUTEX()
{
  if(mxhandle) CloseHandle(mxhandle);

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSMUTEX::Lock()
* @brief      Lock
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSMUTEX::Lock()
{
  if(!mxhandle) return false;

  DWORD status = WaitForSingleObject(mxhandle, INFINITE);
  if(status != WAIT_OBJECT_0) return false;

  islock = true;

  //HANDLE handles[1]= { mxhandle };
  //if(MsgWaitForMultipleObjects(1,handles,FALSE, INFINITE, QS_ALLINPUT) != WAIT_OBJECT_0) return false;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSMUTEX::UnLock()
* @brief      UnLock
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSMUTEX::UnLock()
{
  if(!mxhandle)               return false;
  if(!ReleaseMutex(mxhandle)) return false;

  islock = false;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XWINDOWSMUTEX::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XWINDOWSMUTEX::Clean()
{
  mxhandle = 0;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWINDOWSTHREAD::XWINDOWSTHREAD(XTHREADGROUPID groupID, XCHAR* ID,XTHREADFUNCTION function,void* data)
* @brief      Constructor
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  groupID :
* @param[in]  ID :
* @param[in]  function :
* @param[in]  data :
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XWINDOWSTHREAD::XWINDOWSTHREAD(XTHREADGROUPID groupID, XCHAR* ID, XTHREADFUNCTION function, void* data) : XTHREAD(groupID, ID,function,data)
{
  Clean();
}



/*---------------------------------------------------------------------------------------------------------------------*/
/* XWINDOWSTHREAD                                                                                                      */
/*---------------------------------------------------------------------------------------------------------------------*/




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWINDOWSTHREAD::~XWINDOWSTHREAD()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XWINDOWSTHREAD::~XWINDOWSTHREAD()
{
  End();

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSTHREAD::Ini(bool run)
* @brief      Ini
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  run :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSTHREAD::Ini(bool run)
{
  statusfunc = XTHREADSTATUS_STOP;

  thhandle = CreateThread( NULL, stacksize, Callback, this, 0, NULL);
  if(thhandle == NULL)
    {
      return false;
    }

  if(run)
    {
      if(!Run(true))
        {
          CloseHandle(thhandle);
          return false;
        }
    }

  if((priority != XTHREADPRIORITY_UNKNOWN) && (priority != XTHREADPRIORITY_NORMAL))
    {
      switch(priority)
        {
          case XTHREADPRIORITY_LOW       : SetThreadPriority(thhandle, THREAD_PRIORITY_LOWEST);         break;
          case XTHREADPRIORITY_HIGH      : SetThreadPriority(thhandle, THREAD_PRIORITY_HIGHEST);        break;
          case XTHREADPRIORITY_REALTIME  : SetThreadPriority(thhandle, THREAD_PRIORITY_TIME_CRITICAL);  break;
        }
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSTHREAD::Wait(int miliseconds)
* @brief      Wait
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  miliseconds :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSTHREAD::Wait(int miliseconds)
{
  //WaitForMultipleObjects(1,&thhandle, FALSE, miliseconds?miliseconds:1);

  Sleep(miliseconds?miliseconds:1);

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSTHREAD::End()
* @brief      End
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSTHREAD::End()
{
  if(statusfunc == XTHREADSTATUS_END) return false;

  statusfunc = XTHREADSTATUS_EXIT;

  WaitToEnd();

  if(thhandle)
    {
      CloseHandle(thhandle);
      thhandle = NULL;
    }

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DWORD WINAPI XWINDOWSTHREAD::Callback(LPVOID thread)
* @brief      Callback
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  thread :
*
* @return     DWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
DWORD WINAPI XWINDOWSTHREAD::Callback(LPVOID thread)
{
  XWINDOWSTHREAD*  th;
  XTHREADFUNCTION  func;
  void*            param;

  th = (XWINDOWSTHREAD*)thread;
  if(!th) return 0;

  #ifndef BUILDER
  __try
  #endif
    {
      th = (XWINDOWSTHREAD*)thread;
      if(!th) return 0;

      func = (XTHREADFUNCTION)th->GetFunction();
      if(!func) return 0;

      param = th->GetParam();

      th->gotofunction = true;

      while(1)
        {
          if(!th) break;

          if(th->statusfunc == XTHREADSTATUS_EXIT)     break;
          if(th->statusfunc == XTHREADSTATUS_END)      break;

          if(th->statusfunc == XTHREADSTATUS_RUN)
            {
              if(func)
                {
                  th->isinfunction = true;
                  func(param);
                  th->isinfunction = false;

                } else break;
            }

          if(!th) break;

          if(th->waityield) Sleep(th->waityield);
        }

      if(th) th->statusfunc = XTHREADSTATUS_END;
    }

  #ifndef BUILDER
  __except(Exception_Filter(GetExceptionCode(), GetExceptionInformation()))
  {
    if(th)
      {
        if(th->thhandle)
          {
            CloseHandle(th->thhandle);
            th->thhandle = NULL;
          }
      }
  }
  #endif

  return 0;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XWINDOWSTHREAD::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XWINDOWSTHREAD::Clean()
{
  thhandle = NULL;
}


