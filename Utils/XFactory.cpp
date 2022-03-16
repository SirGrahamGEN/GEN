/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XFactory.cpp
*
* @class      XFACTORY
* @brief      eXtended platform Factory
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

#include "XFactory.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

XFACTORY* XFACTORY::instance = NULL;

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFACTORY::XFACTORY()
* @brief      Constructor
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XFACTORY::XFACTORY()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFACTORY::~XFACTORY()
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
XFACTORY::~XFACTORY()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFACTORY::GetIsInstanced()
* @brief      Get if Is Instanced
* @note       STATIC
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFACTORY::GetIsInstanced()
{
  return instance!=NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFACTORY& XFACTORY::GetInstance()
* @brief      Get Instance of XFACTORY
* @note       STATIC
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XFACTORY& :
*
*---------------------------------------------------------------------------------------------------------------------*/
XFACTORY& XFACTORY::GetInstance()
{
  if(!instance)
    {
      instance = new XFACTORY();
    }

  return (*instance);
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFACTORY::SetInstance(XFACTORY* _instance)
* @brief      SetInstance
* @ingroup    UTILS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  _instance : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFACTORY::SetInstance(XFACTORY* _instance)
{
  if(!_instance) return false;

  instance = _instance;

  return (instance)?true:false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFACTORY::DelInstance()
* @brief      Delete Instance of XFACTORY
* @note       STATIC
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFACTORY::DelInstance()
{
  if(!instance) return false;

  delete instance;
  instance = NULL;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTIMER* XFACTORY::CreateTimer()
* @brief      Create Timer
* @note       VIRTUAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XTIMER* : Timer Created
*
*---------------------------------------------------------------------------------------------------------------------*/
XTIMER* XFACTORY::CreateTimer()
{
  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFACTORY::DeleteTimer(XTIMER* timer)
* @brief      Delete Timer
* @note       VIRTUAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  timer : timer to delete
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFACTORY::DeleteTimer(XTIMER* timer)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDATETIME* XFACTORY::CreateDateTime()
* @brief      Create DateTime
* @note       VIRTUAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XDATETIME* : datetime created
*
*---------------------------------------------------------------------------------------------------------------------*/
XDATETIME* XFACTORY::CreateDateTime()
{
  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFACTORY::DeleteDateTime(XDATETIME* datetime)
* @brief      Delete DateTime
* @note       VIRTUAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  datetime : datetime to delete
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFACTORY::DeleteDateTime(XDATETIME* datetime)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XRAND* XFACTORY::CreateRand()
* @brief      Create Rand
* @note       VIRTUAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XRAND* : Rand created
*
*---------------------------------------------------------------------------------------------------------------------*/
XRAND* XFACTORY::CreateRand()
{
  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFACTORY::DeleteRand(XRAND* rand)
* @brief      Delete Rand
* @note       VIRTUAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  rand : rand to delete
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFACTORY::DeleteRand(XRAND* rand)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILE* XFACTORY::Create_File()
* @brief      Create File
* @note       VIRTUAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XFILE* : File created
*
*---------------------------------------------------------------------------------------------------------------------*/
XFILE* XFACTORY::Create_File()
{
  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFACTORY::Delete_File(XFILE* file)
* @brief      Delete_File
* @note       VIRTUAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  file : file to delete
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFACTORY::Delete_File(XFILE* file)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDIR* XFACTORY::Create_Dir()
* @brief      Create_Dir
* @note       VIRTUAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XDIR* : dir created
*
*---------------------------------------------------------------------------------------------------------------------*/
XDIR* XFACTORY::Create_Dir()
{
  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFACTORY::Delete_Dir(XDIR* dir)
* @brief      Delete_Dir
* @note       VIRTUAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  dir : dir to delete
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFACTORY::Delete_Dir(XDIR* dir)
{
  return false;
}


#ifdef XCONSOLE_ACTIVE
/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XCONSOLE* XFACTORY::CreateConsole()
* @brief      Create Console
* @note       VIRTUAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XCONSOLE* : console created
*
*---------------------------------------------------------------------------------------------------------------------*/
XCONSOLE* XFACTORY::CreateConsole()
{
  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFACTORY::DeleteConsole(XCONSOLE* xconsole)
* @brief      DeleteConsole
* @note       VIRTUAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  xconsole : xconsole to delete
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFACTORY::DeleteConsole(XCONSOLE* xconsole)
{
  return false;
}
#endif


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XMUTEX* XFACTORY::Create_Mutex()
* @brief      Create Mutex
* @note       VIRTUAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XMUTEX* : mutex created
*
*---------------------------------------------------------------------------------------------------------------------*/
XMUTEX* XFACTORY::Create_Mutex()
{
  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFACTORY::Delete_Mutex(XMUTEX* mutex)
* @brief      Delete Mutex
* @note       VIRTUAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  mutex : mutex to delete
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFACTORY::Delete_Mutex(XMUTEX* phone)
{
  return false;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTHREAD* XFACTORY::CreateThread(XTHREADGROUPID groupID, XCHAR* ID,XTHREADFUNCTION function, void* param)
* @brief      CreateThread
* @ingroup    UTILS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  groupID : 
* @param[in]  ID : 
* @param[in]  function : 
* @param[in]  param : 
*
* @return     XTHREAD* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XTHREAD* XFACTORY::CreateThread(XTHREADGROUPID groupID, XCHAR* ID,XTHREADFUNCTION function, void* param)
{
  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFACTORY::DeleteThread(XTHREADGROUPID groupID, XTHREAD* xthread)
* @brief      Delete Thread
* @note       VIRTUAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  groupID : group ID of threads
* @param[in]  xthread : thread to delete
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFACTORY::DeleteThread(XTHREADGROUPID groupID, XTHREAD* xthread)
{
  return false;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFACTORY::Clean()
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
void XFACTORY::Clean()
{

}


