/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XESP32Thread.cpp
* 
* @class      XESP32THREAD
* @brief      eXtended utils ESP32 mutex & thread class
* @ingroup    PLATFORM_ESP32
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

#include "XESP32Thread.h"

#include "XSleep.h"
#include "XTrace.h"
#include "XThreadListNonPreemptive.h"

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


/*---- CLASS ESP32MUTEX ----------------------------------------------------------------------------------------------*/
#pragma region CLASS_ESP32MUTEX


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XESP32MUTEX::XESP32MUTEX()
* @brief      Constructor of class
* @ingroup    PLATFORM_ESP32
*
* --------------------------------------------------------------------------------------------------------------------*/
XESP32MUTEX::XESP32MUTEX()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XESP32MUTEX::~XESP32MUTEX()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    PLATFORM_ESP32
*
* --------------------------------------------------------------------------------------------------------------------*/
XESP32MUTEX::~XESP32MUTEX()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XESP32MUTEX::Lock()
* @brief      Lock
* @ingroup    PLATFORM_ESP32
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XESP32MUTEX::Lock()
{
  counterlock++;
  if(counterlock) islock = true;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XESP32MUTEX::UnLock()
* @brief      Un lock
* @ingroup    PLATFORM_ESP32
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XESP32MUTEX::UnLock()
{
  if(!counterlock) return false;

  counterlock--;
  if(!counterlock)  islock = false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XESP32MUTEX::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    PLATFORM_ESP32
*
* --------------------------------------------------------------------------------------------------------------------*/
void XESP32MUTEX::Clean()
{
  counterlock  = 0;
}

#pragma endregion


/*---- CLASS ESP32THREAD ---------------------------------------------------------------------------------------------*/
#pragma region CLASS_ESP32THREAD


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XESP32THREAD::XESP32THREAD(XTHREADGROUPID groupID, XCHAR* ID, XTHREADFUNCTION function, void* data)
* @brief      Constructor of class
* @ingroup    PLATFORM_ESP32
*
* @param[in]  groupID :
* @param[in]  ID :
* @param[in]  function :
* @param[in]  data :
*
* --------------------------------------------------------------------------------------------------------------------*/
XESP32THREAD::XESP32THREAD(XTHREADGROUPID groupID, XCHAR* ID, XTHREADFUNCTION function, void* data) : XTHREAD(groupID, ID, function, data)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XESP32THREAD::~XESP32THREAD()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    PLATFORM_ESP32
*
* --------------------------------------------------------------------------------------------------------------------*/
XESP32THREAD::~XESP32THREAD()
{
  End();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XESP32THREAD::Ini(bool run)
* @brief      Ini
* @ingroup    PLATFORM_ESP32
*
* @param[in]  run :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XESP32THREAD::Ini(bool run)
{
  if(run)
    {
      if(!Run(true)) return false;
    }
   else statusfunc = XTHREADSTATUS_STOP;

  return false; //XTHREADLISTNONPREEMPTIVE::GetInstance().AddThread(this);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XESP32THREAD::Wait(int miliseconds)
* @brief      Wait
* @ingroup    PLATFORM_ESP32
*
* @param[in]  miliseconds :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XESP32THREAD::Wait(int miliseconds)
{
  GEN_XSLEEP.MilliSeconds(miliseconds);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XESP32THREAD::End()
* @brief      End
* @ingroup    PLATFORM_ESP32
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XESP32THREAD::End()
{
  if(statusfunc == XTHREADSTATUS_END) return false;

  statusfunc = XTHREADSTATUS_EXIT;

  return false; //XTHREADLISTNONPREEMPTIVE::GetInstance().DeleteThread(this);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XESP32THREAD::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    PLATFORM_ESP32
*
* --------------------------------------------------------------------------------------------------------------------*/
void XESP32THREAD::Clean()
{

}


#pragma endregion


#pragma endregion





