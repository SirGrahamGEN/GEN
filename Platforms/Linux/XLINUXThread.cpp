/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XLINUXThread.cpp
* 
* @class      XLINUXTHREAD
* @brief      LINUX eXtended Utils Thread and Mutex class
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

#include "XLINUXThread.h"

#include <stdio.h>
#include <unistd.h>
#include <malloc.h>
#include <errno.h>
#include <pthread.h>

#include "XTrace.h"

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


#pragma region CLASS_XLINUXMUTEX


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLINUXMUTEX::XLINUXMUTEX()
* @brief      Constructor of class
* @ingroup    PLATFORM_LINUX
*
* --------------------------------------------------------------------------------------------------------------------*/
XLINUXMUTEX::XLINUXMUTEX()
{
  Clean();

  pthread_mutexattr_init(&attr);
  pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

  if(!pthread_mutex_init(&mutex, &attr)) init = true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLINUXMUTEX::~XLINUXMUTEX()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    PLATFORM_LINUX
*
* --------------------------------------------------------------------------------------------------------------------*/
XLINUXMUTEX::~XLINUXMUTEX()
{
  if(init)
    {
      pthread_mutex_destroy(&mutex);
      init = false;
    }

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXMUTEX::Lock()
* @brief      Lock
* @ingroup    PLATFORM_LINUX
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLINUXMUTEX::Lock()
{
  if(!init)                      return false;

  if(pthread_mutex_lock(&mutex)) return false;

  islock = true;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXMUTEX::UnLock()
* @brief      Un lock
* @ingroup    PLATFORM_LINUX
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLINUXMUTEX::UnLock()
{
  if(!init)                        return false;
  if(pthread_mutex_unlock(&mutex)) return false;

  islock = false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XLINUXMUTEX::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    PLATFORM_LINUX
*
* --------------------------------------------------------------------------------------------------------------------*/
void XLINUXMUTEX::Clean()
{
  init = false;
}


#pragma endregion


#pragma region CLASS_XLINUXTHREAD


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XLINUXTHREAD::XLINUXTHREAD(XTHREADGROUPID groupID, XCHAR* ID, XTHREADFUNCTION function, void* param)
* @brief      Constructor of class
* @ingroup    PLATFORM_LINUX
* 
* @param[in]  groupID : 
* @param[in]  ID : 
* @param[in]  function : 
* @param[in]  param : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XLINUXTHREAD::XLINUXTHREAD(XTHREADGROUPID groupID, XCHAR* ID, XTHREADFUNCTION function, void* param) : XTHREAD(groupID, ID, function, param)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLINUXTHREAD::~XLINUXTHREAD()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    PLATFORM_LINUX
*
* --------------------------------------------------------------------------------------------------------------------*/
XLINUXTHREAD::~XLINUXTHREAD()
{
  End();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXTHREAD::Ini(bool run)
* @brief      Ini
* @ingroup    PLATFORM_LINUX
*
* @param[in]  run : if run the thread directly
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLINUXTHREAD::Ini(bool run)
{
  statusfunc = XTHREADSTATUS_STOP;

  pthread_attr_t attr;

  if(!stacksize) SetStackSize(1024*1024);

  pthread_attr_init(&attr);
  pthread_attr_setstacksize(&attr, stacksize);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  int _status = pthread_create(&thhandle, &attr, Callback, this);
  if(!_status)
    {
       XBUFFER charstr;
       
       ID.ConvertToASCII(charstr);
            
      // pthread_setname_np(thhandle, charstr.GetPtrChar());
     
      if(run)
        {
          if(!Run(true)) return false;
        }
       else
        {
          statusfunc = XTHREADSTATUS_STOP;
        }

      pthread_attr_destroy(&attr);
    }
   else
    {
      thhandle = 0;
      // If pthread_create() fails, no new thread is created and the contents of the location referenced by thread are UNDEFINED.
    }

  return (!_status)?true:false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXTHREAD::Wait(int miliseconds)
* @brief      Wait
* @ingroup    PLATFORM_LINUX
*
* @param[in]  miliseconds :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLINUXTHREAD::Wait(int miliseconds)
{
  usleep(1000*(miliseconds?miliseconds:1));

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXTHREAD::End()
* @brief      End
* @ingroup    PLATFORM_LINUX
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLINUXTHREAD::End()
{
  if(statusfunc == XTHREADSTATUS_END) return false;

  statusfunc = XTHREADSTATUS_EXIT;

  WaitToEnd();

  if(thhandle)
    {
      pthread_join(thhandle, NULL);
      thhandle = 0;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void* XLINUXTHREAD::Callback(void* thread)
* @brief      Callback
* @ingroup    PLATFORM_LINUX
*
* @param[in]  thread : thread class
*
* @return     void* : NULL always
*
* --------------------------------------------------------------------------------------------------------------------*/
void* XLINUXTHREAD::Callback(void* thread)
{
  XLINUXTHREAD*    th   = NULL;
  XTHREADFUNCTION  func = NULL;
  void*            param;

  th = (XLINUXTHREAD*)thread;
  if(!th) return NULL;

  func = (XTHREADFUNCTION)th->GetFunction();
  if(!func) return NULL;

  param = th->GetParam();

  th->gotofunction = true;

  if((th->priority != XTHREADPRIORITY_UNKNOWN) &&
     (th->priority != XTHREADPRIORITY_NORMAL))
    {
      struct sched_param param;    // scheduling priority

      int policy = SCHED_FIFO;     // scheduling policy

      switch(th->priority)
        {
          #ifdef SCHED_IDLE
          case XTHREADPRIORITY_LOW      : policy = SCHED_IDLE;
                                          param.sched_priority = sched_get_priority_min(policy);
                                          break;
          #endif

          case XTHREADPRIORITY_HIGH     : policy = SCHED_FIFO;
                                          param.sched_priority = sched_get_priority_max(policy)/2;
                                          break;

          case XTHREADPRIORITY_REALTIME : policy = SCHED_FIFO;
                                          param.sched_priority = sched_get_priority_max(policy);
                                          break;

                              default   : break;
        }

      pthread_setschedparam(th->thhandle, policy, &param);
    }

  while(1)
    {
      if(!th) break;

      if(th->statusfunc == XTHREADSTATUS_EXIT)  break;
      if(th->statusfunc == XTHREADSTATUS_END)   break;

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

      if(th->waityield) usleep(th->waityield*1000);
    }

  if(th) th->statusfunc = XTHREADSTATUS_END;

  pthread_exit(0);

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XLINUXTHREAD::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    PLATFORM_LINUX
*
* --------------------------------------------------------------------------------------------------------------------*/
void XLINUXTHREAD::Clean()
{
  thhandle = 0;
}


#pragma endregion


#pragma endregion


