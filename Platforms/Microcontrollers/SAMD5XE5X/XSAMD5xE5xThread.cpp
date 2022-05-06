/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XSAMD5xE5xThread.cpp
*
* @class      XSAMD5XE5XTHREAD
* @brief      SAMD5xE5x thread class
* @ingroup    PLATFORM_SAMD5XE5X
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XSleep.h"
#include "XTrace.h"
#include "XThreadListNonPreemptive.h"
#include "XSAMD5xE5x_HAL.h"

#include "XSAMD5xE5xThread.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------*/
/*  XSAMD5XE5XMUTEX                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSAMD5XE5XMUTEX::XSAMD5XE5XMUTEX()
* @brief      Constructor
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XSAMD5XE5XMUTEX::XSAMD5XE5XMUTEX()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSAMD5XE5XMUTEX::~XSAMD5XE5XMUTEX()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XSAMD5XE5XMUTEX::~XSAMD5XE5XMUTEX()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSAMD5XE5XMUTEX::Lock()
* @brief      Lock
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSAMD5XE5XMUTEX::Lock()
{
  counterlock++;
  if(counterlock) islock = true;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSAMD5XE5XMUTEX::UnLock()
* @brief      UnLock
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSAMD5XE5XMUTEX::UnLock()
{
  if(!counterlock) return false;

  counterlock--;
  if(!counterlock)  islock = false;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSAMD5XE5XMUTEX::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XSAMD5XE5XMUTEX::Clean()
{
  counterlock  = 0;
}




/*--------------------------------------------------------------------------------------------------------------------*/
/*  XSAMD5XE5XTHREAD                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSAMD5XE5XTHREAD::XSAMD5XE5XTHREAD(XTHREADGROUPID groupID, XCHAR* ID, XTHREADFUNCTION function, void* data)
* @brief      Constructor
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  XTHREADGROUPID :
* @param[in]   XCHAR* ID :
* @param[in]   XTHREADFUNCTION function :
* @param[in]   void* data :
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XSAMD5XE5XTHREAD::XSAMD5XE5XTHREAD(XTHREADGROUPID groupID, XCHAR* ID, XTHREADFUNCTION function, void* data): XTHREAD(groupID, ID, function, data)
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSAMD5XE5XTHREAD::~XSAMD5XE5XTHREAD()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XSAMD5XE5XTHREAD::~XSAMD5XE5XTHREAD()
{
  End();

  Clean();
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSAMD5XE5XTHREAD::Ini(bool run)
* @brief      Ini
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  run :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSAMD5XE5XTHREAD::Ini(bool run)
{
  if(run)
    {
      if(!Run(true)) return false;
    }
   else statusfunc = XTHREADSTATUS_STOP;

  return XTHREADLISTNONPREEMPTIVE::GetInstance().AddThread(this);
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSAMD5XE5XTHREAD::Wait(int miliseconds)
* @brief      Wait
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  miliseconds :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSAMD5XE5XTHREAD::Wait(int miliseconds)
{
  GEN_XSLEEP.MilliSeconds(miliseconds);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSAMD5XE5XTHREAD::End()
* @brief      End
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSAMD5XE5XTHREAD::End()
{
  if(statusfunc == XTHREADSTATUS_END) return false;

  statusfunc = XTHREADSTATUS_EXIT;

  //WaitToEnd();

  return XTHREADLISTNONPREEMPTIVE::GetInstance().DeleteThread(this);
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSAMD5XE5XTHREAD::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XSAMD5XE5XTHREAD::Clean()
{

}
