/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XSharedMemoryManager.cpp
* 
* @class      XSHAREDMEMORYMANAGER
* @brief      eXtended Utils Shared memory Manager class
* @ingroup    XUTILS
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

#include "XSharedMemoryManager.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

XSHAREDMEMORYMANAGER* XSHAREDMEMORYMANAGER::instance = NULL;

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSHAREDMEMORYMANAGER::XSHAREDMEMORYMANAGER()
* @brief      Constructor of class
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XSHAREDMEMORYMANAGER::XSHAREDMEMORYMANAGER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSHAREDMEMORYMANAGER::~XSHAREDMEMORYMANAGER()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XSHAREDMEMORYMANAGER::~XSHAREDMEMORYMANAGER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSHAREDMEMORYMANAGER::GetIsInstanced()
* @brief      Get is instanced
* @note       STATIC
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSHAREDMEMORYMANAGER::GetIsInstanced()
{
  return instance!=NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSHAREDMEMORYMANAGER& XSHAREDMEMORYMANAGER::GetInstance()
* @brief      Get instance
* @note       STATIC
* @ingroup    XUTILS
*
* @return     XSHAREDMEMORYMANAGER& :
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* @fn         bool XSHAREDMEMORYMANAGER::SetInstance(XSHAREDMEMORYMANAGER* _instance)
* @brief      Set instance
* @note       STATIC
* @ingroup    XUTILS
*
* @param[in]  _instance : new instance
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSHAREDMEMORYMANAGER::SetInstance(XSHAREDMEMORYMANAGER* _instance)
{
  if(!_instance) return false;

  instance = _instance;

  return (instance)?true:false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSHAREDMEMORYMANAGER::DelInstance()
* @brief      Del instance
* @note       STATIC
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* @ingroup    XUTILS
*
* @param[in]  ID :
* @param[in]  size :
* @param[in]  ispublic :
*
* @return     XBYTE* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE* XSHAREDMEMORYMANAGER::Create(XCHAR* ID, XDWORD size, bool ispublic)
{
  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE* XSHAREDMEMORYMANAGER::Create(XSTRING& ID, XDWORD size, bool ispublic)
* @brief      Create
* @ingroup    XUTILS
*
* @param[in]  ID :
* @param[in]  size :
* @param[in]  ispublic :
*
* @return     XBYTE* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE* XSHAREDMEMORYMANAGER::Create(XSTRING& ID, XDWORD size, bool ispublic)
{
  return Create(ID.Get(), size, ispublic);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE* XSHAREDMEMORYMANAGER::Open(XCHAR* ID, XDWORD& size)
* @brief      Open
* @ingroup    XUTILS
*
* @param[in]  ID : ID of Shared memory
* @param[in]  size : size of shared memory
*
* @return     XBYTE* : Pointer to shared memory
*
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE* XSHAREDMEMORYMANAGER::Open(XCHAR* ID, XDWORD& size)
{
  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE* XSHAREDMEMORYMANAGER::Open(XSTRING& ID, XDWORD& size)
* @brief      Open
* @ingroup    XUTILS
*
* @param[in]  ID : ID of Shared memory
* @param[in]  size : size of shared memory
*
* @return     XBYTE* : Pointer to shared memory
*
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE* XSHAREDMEMORYMANAGER::Open(XSTRING& ID, XDWORD& size)
{
  return Open(ID.Get(), size);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE* XSHAREDMEMORYMANAGER::GetPointer()
* @brief      Get pointer
* @ingroup    XUTILS
*
* @return     XBYTE* : Pointer to shared memory
*
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE* XSHAREDMEMORYMANAGER::GetPointer()
{
  return pointer;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSHAREDMEMORYMANAGER::Close()
* @brief      Close
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSHAREDMEMORYMANAGER::Close()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSHAREDMEMORYMANAGER::IsServer()
* @brief      Is server
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSHAREDMEMORYMANAGER::IsServer()
{
  return isserver;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSHAREDMEMORYMANAGER::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XSHAREDMEMORYMANAGER::Clean()
{
  instance  = NULL;

  ID.Empty();

  base      = NULL;
  pointer   = NULL;
  size      = 0;
  isserver  = false;
}


#pragma endregion

