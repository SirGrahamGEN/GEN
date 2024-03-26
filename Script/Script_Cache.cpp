/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       Script_Cache.cpp
* 
* @class      SCRIPT_CACHE
* @brief      Script Cache class
* @ingroup    SCRIPT
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

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "Script_Cache.h"

#include "XBuffer.h"

#include "HashCRC32.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

SCRIPT_CACHE*  SCRIPT_CACHE::instance = NULL;

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_CACHE::GetIsInstanced()
* @brief      GetIsInstanced
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_CACHE::GetIsInstanced()
{
  return instance!=NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_CACHE& SCRIPT_CACHE::GetInstance()
* @brief      GetInstance
* @ingroup    XUTILS
*
* @return     SCRIPT_CACHE& :
*
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_CACHE& SCRIPT_CACHE::GetInstance()
{
  if(!instance) instance = new SCRIPT_CACHE();
  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_CACHE::DelInstance()
* @brief      DelInstance
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_CACHE::DelInstance()
{
  if(!instance) return false;

  delete instance;
  instance = NULL;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD SCRIPT_CACHE::GenerateID(XSTRING& stringID)
* @brief      GenerateID
* @ingroup    SCRIPT
* 
* @param[in]  stringID : 
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD SCRIPT_CACHE::GenerateID(XSTRING& stringID)
{
  HASHCRC32 crc32;
  XBUFFER   buffer;

  buffer.Add(stringID);

  crc32.Do(buffer);

  XDWORD CRC32 = crc32.GetResultCRC32();

  return CRC32;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT_CACHE::AddCache(XDWORD ID, XSTRING* script)
* @brief      AddCache
* @ingroup    SCRIPT
* 
* @param[in]  ID : 
* @param[in]  script : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_CACHE::AddCache(XDWORD ID, XSTRING* script)
{
  if(!ID)
    {
      return false;
    }

  if(!script)
    {
      return false;
    }

  if(SCRIPT_CACHE::GetCache(ID))
    {
      SetCache(ID, script);
      return true;
    }

  XSTRING* _script;   

  _script = new XSTRING();

  if(!_script)
    {
      delete _script;
      return false;
    }
  
  (*_script) = script->Get();

  cache.Add(ID, _script);
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* SCRIPT_CACHE::GetCache(XDWORD ID, int* index)
* @brief      GetCache
* @ingroup    SCRIPT
* 
* @param[in]  ID : 
* @param[in]  index : 
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* SCRIPT_CACHE::GetCache(XDWORD ID, int* index)
{
  if(!ID)
    {
      return NULL;
    }

  if(index)
    {
      (*index) = -1;
    }

  for(int c=0; c<cache.GetSize(); c++)
    {
      XDWORD _ID = cache.GetKey(c);
      if(_ID)
        {
          if(ID == _ID)
            {
              XSTRING* script = cache.GetElement(c);
              if(index && script)
                {
                  (*index) = c;
                }

              return script;    
            }         
        }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT_CACHE::SetCache(XDWORD ID, XSTRING* script)
* @brief      SetCache
* @ingroup    SCRIPT
* 
* @param[in]  ID : 
* @param[in]  script : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_CACHE::SetCache(XDWORD ID, XSTRING* script)
{
  if(!ID)
    {
      return false;
    }

  if(!script)
    {
      return false;
    }

  int index = 0;

  if(!SCRIPT_CACHE::GetCache(ID, &index))
    {
      return false;
    }

  if(index == SCRIPT_CACHE_NOTFOUND)
    {
      return false;
    }

  XSTRING* _script = cache.GetElement(index);
  if(!_script)
    {
      return false;    
    }

  (*_script) = script->Get();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT_CACHE::DelCache(XDWORD ID)
* @brief      DelCache
* @ingroup    SCRIPT
* 
* @param[in]  ID : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_CACHE::DelCache(XDWORD ID)
{
  if(!ID)
    {
      return NULL;
    }
  
  if(!SCRIPT_CACHE::GetCache(ID))
    {
      return false;
    }

  return cache.Delete(ID);
}
    
    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XMAP<XSTRING*, XSTRING*> SCRIPT_CACHE::GetCache()
* @brief      GetCache
* @ingroup    SCRIPT
* 
* @return     XMAP<XSTRING*, XSTRING*> : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XMAP<XDWORD, XSTRING*>* SCRIPT_CACHE::GetAllCache()
{
  return &cache;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT_CACHE::DeleteAllCache()
* @brief      DeleteAllCache
* @ingroup    SCRIPT
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_CACHE::DeleteAllCache()
{
  if(!cache.GetSize())
    {
      return false;
    }

  cache.DeleteElementContents();
  cache.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SCRIPT_CACHE::SCRIPT_CACHE()
* @brief      Constructor
* @ingroup    SCRIPT
* 
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_CACHE::SCRIPT_CACHE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SCRIPT_CACHE::~SCRIPT_CACHE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    SCRIPT
* 
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_CACHE::~SCRIPT_CACHE()
{
  DeleteAllCache();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SCRIPT_CACHE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    SCRIPT
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_CACHE::Clean()
{

}


#pragma endregion


