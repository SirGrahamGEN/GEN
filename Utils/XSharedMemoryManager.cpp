/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XSharedMemoryManager.cpp
*
* @class      XSHAREDMEMORYMANAGER
* @brief      eXtended Shared memory manager (Exchange between applications)
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

#include "XSharedMemoryManager.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

XSHAREDMEMORYMANAGER* XSHAREDMEMORYMANAGER::instance = NULL;

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSHAREDMEMORYMANAGER::XSHAREDMEMORYMANAGER()
* @brief      Constructor
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XSHAREDMEMORYMANAGER::XSHAREDMEMORYMANAGER()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSHAREDMEMORYMANAGER::~XSHAREDMEMORYMANAGER()
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
XSHAREDMEMORYMANAGER::~XSHAREDMEMORYMANAGER()
{
  Clean();
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSHAREDMEMORYMANAGER::GetIsInstanced()
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
bool XSHAREDMEMORYMANAGER::GetIsInstanced()
{
  return instance!=NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSHAREDMEMORYMANAGER& XSHAREDMEMORYMANAGER::GetInstance()
* @brief      Get Instance of XSHAREDMEMORYMANAGER
* @note       STATIC
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XSHAREDMEMORYMANAGER& :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSHAREDMEMORYMANAGER& XSHAREDMEMORYMANAGER::GetInstance()
{
  if(!instance) 
    {
      instance = new XSHAREDMEMORYMANAGER();
    }

  return (*instance);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSHAREDMEMORYMANAGER::SetInstance(XSHAREDMEMORYMANAGER* instance)
* @brief      Set Instance of XSHAREDMEMORY
* @note       STATIC
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  _instance : new instance
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XSHAREDMEMORYMANAGER::SetInstance(XSHAREDMEMORYMANAGER* _instance)
{
  if(!_instance) return false;

  instance = _instance;

  return (instance)?true:false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSHAREDMEMORYMANAGER::DelInstance()
* @brief      Delete Instance of XSHAREDMEMORY
* @note       STATIC
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XSHAREDMEMORYMANAGER::DelInstance()
{
  if(instance)
    {
      delete instance;
      instance = NULL;

      return true;
    }

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE* XSHAREDMEMORYMANAGER::Create(XCHAR* ID, XDWORD size, bool ispublic)
* @brief      Create
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  ID :
* @param[in]  size :
* @param[in]  ispublic :
*
* @return     XBYTE* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XBYTE* XSHAREDMEMORYMANAGER::Create(XCHAR* ID, XDWORD size, bool ispublic)
{
  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE* XSHAREDMEMORYMANAGER::Create(XSTRING& ID, XDWORD size, bool ispublic)
* @brief      Create
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  ID :
* @param[in]  size :
* @param[in]  ispublic :
*
* @return     XBYTE* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XBYTE* XSHAREDMEMORYMANAGER::Create(XSTRING& ID, XDWORD size, bool ispublic)
{
  return Create(ID.Get(), size, ispublic);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE* XSHAREDMEMORYMANAGER::Open(XCHAR* ID, XDWORD& size)
* @brief      Open Shared Memory (other task or application must create the shared memory)
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  ID : ID of Shared memory
* @param[in]  size : size of shared memory
*
* @return     XBYTE* : Pointer to shared memory
*
*---------------------------------------------------------------------------------------------------------------------*/
XBYTE* XSHAREDMEMORYMANAGER::Open(XCHAR* ID, XDWORD& size)
{
  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE* XSHAREDMEMORYMANAGER::Open(XSTRING& ID, XDWORD& size)
* @brief      Open Shared Memory (other task or application must create the shared memory)
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  ID : ID of Shared memory
* @param[in]  size : size of shared memory
*
* @return     XBYTE* : Pointer to shared memory
*
*---------------------------------------------------------------------------------------------------------------------*/
XBYTE* XSHAREDMEMORYMANAGER::Open(XSTRING& ID, XDWORD& size)
{
  return Open(ID.Get(), size);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE* XSHAREDMEMORYMANAGER::GetPointer()
* @brief      Get Pointer of Shared Memory
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XBYTE* : Pointer to shared memory
*
*---------------------------------------------------------------------------------------------------------------------*/
XBYTE* XSHAREDMEMORYMANAGER::GetPointer()
{
  return pointer;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSHAREDMEMORYMANAGER::Close()
* @brief      Close Shared Memory (for create or open)
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XSHAREDMEMORYMANAGER::Close()
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSHAREDMEMORYMANAGER::IsServer()
* @brief      IsServer
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XSHAREDMEMORYMANAGER::IsServer()
{
  return isserver;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSHAREDMEMORYMANAGER::Clean()
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
void XSHAREDMEMORYMANAGER::Clean()
{
  instance  = NULL;

  ID.Empty();

  base      = NULL;
  pointer   = NULL;
  size      = 0;
  isserver  = false;
}

