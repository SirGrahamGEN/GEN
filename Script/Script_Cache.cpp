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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "Script_Cache.h"

#include "XBuffer.h"
#include "XDir.h"

#include "HashCRC32.h"

#include "Script.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

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
* @brief      Get is instanced
* @ingroup    SCRIPT
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
* @brief      Get instance
* @ingroup    SCRIPT
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
* @brief      Del instance
* @ingroup    SCRIPT
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
* @brief      Generate ID
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
* @fn         bool SCRIPT_CACHE::Cache_Add(XDWORD ID, XSTRING* script)
* @brief      Cache add
* @ingroup    SCRIPT
* 
* @param[in]  ID : 
* @param[in]  script : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_CACHE::Cache_Add(XDWORD ID, XSTRING* script)
{
  if(!ID)
    {
      return false;
    }

  if(!script)
    {
      return false;
    }

  if(SCRIPT_CACHE::Cache_Get(ID))
    {
      Cache_Set(ID, script);
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
* @fn         XSTRING* SCRIPT_CACHE::Cache_Get(XDWORD ID, int* index)
* @brief      Cache get
* @ingroup    SCRIPT
* 
* @param[in]  ID : 
* @param[in]  index : 
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* SCRIPT_CACHE::Cache_Get(XDWORD ID, int* index)
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
* @fn         bool SCRIPT_CACHE::Cache_Set(XDWORD ID, XSTRING* script)
* @brief      Cache set
* @ingroup    SCRIPT
* 
* @param[in]  ID : 
* @param[in]  script : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_CACHE::Cache_Set(XDWORD ID, XSTRING* script)
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

  if(!SCRIPT_CACHE::Cache_Get(ID, &index))
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
* @fn         bool SCRIPT_CACHE::Cache_Del(XDWORD ID)
* @brief      Cache del
* @ingroup    SCRIPT
* 
* @param[in]  ID : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_CACHE::Cache_Del(XDWORD ID)
{
  if(!ID)
    {
      return NULL;
    }
  
  if(!SCRIPT_CACHE::Cache_Get(ID))
    {
      return false;
    }

  return cache.Delete(ID);
}
    
    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XMAP<XSTRING*, XSTRING*> SCRIPT_CACHE::Cache_Get()
* @brief      Cache get
* @ingroup    SCRIPT
* 
* @return     XMAP<XSTRING*, XSTRING*> : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XMAP<XDWORD, XSTRING*>* SCRIPT_CACHE::Cache_GetAll()
{
  return &cache;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT_CACHE::Cache_DelAll()
* @brief      Cache del all
* @ingroup    SCRIPT
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_CACHE::Cache_DelAll()
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
* @fn         bool SCRIPT_CACHE::Cache_AllDirectory(XPATH& xpath)
* @brief      Cache all directory
* @ingroup    SCRIPT
* 
* @param[in]  xpath : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_CACHE::Cache_AllDirectory(XPATH& xpath)
{
  XDIR*         xdir;
  XDIRELEMENT   element;
 
  xdir = GEN_XFACTORY.Create_Dir();
  if(!xdir) 
    {
      return false;
    }
      
  if(xdir->FirstSearch(xpath.Get(), __L("*"), &element))
    {
      do{ SCRIPT_TYPE type = SCRIPT::GetTypeByExtension(element.GetNameFile()->Get());
          if(type != SCRIPT_TYPE_UNKNOWN)
            {  
              SCRIPT* script = SCRIPT::Create(element.GetNameFile()->Get());
              if(script) 
                {
                  XPATH xpathnamefile;

                  xpathnamefile = xpath.Get();
                  xpathnamefile.Slash_Add();  
                  xpathnamefile.Add(element.GetNameFile()->Get());
                    
                  script->Load(xpathnamefile);                                      
                } 

               delete script;
            }
           
        } while(xdir->NextSearch(&element));
    }            
    
  GEN_XFACTORY.Delete_Dir(xdir);

  return true;
}
 

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT_CACHE::Cache_AllList(XVECTOR<XSTRING*>* listscripts)
* @brief      Cache all list
* @ingroup    SCRIPT
* 
* @param[in]  listscripts : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_CACHE::Cache_AllList(XVECTOR<XSTRING*>* listscripts)
{
  if(!listscripts) 
    {
      return false;
    }

  bool status = false;
                                                                                                     
  for(XDWORD c=0; c<listscripts->GetSize(); c++)
    {  
      XSTRING* linescripts = listscripts->Get(c);    
      if(linescripts)
        {
          if(!linescripts->IsEmpty())
            {
              XVECTOR<XSTRING*> namescripts;

              linescripts->Split(__C(','), namescripts);

              XSTRING* namescript = namescripts.Get(0);
              if(namescript)
                {
                  SCRIPT::EliminateExtraChars(namescript);
                  
                  SCRIPT* script = SCRIPT::Create(namescript->Get());
                  if(script) 
                    {
                      XPATH       allpath;
                      XDWORD      ID = 0;
                      bool        incache = false;
                      
                      GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_SCRIPTS, allpath);
    
                      for(XDWORD d=0; d<namescripts.GetSize(); d++)
                        {  
                          allpath += __C(',');  
                          allpath += namescript->Get();  
                        }
                    
                      ID = GEN_SCRIPT_CACHE.GenerateID(allpath);

                      #ifdef SCRIPT_CACHE_ACTIVE

                      XSTRING* _script = GEN_SCRIPT_CACHE.Cache_Get(ID);
                      if(_script)
                        {                         
                          (*script->GetScript()) += _script->Get();      

                          incache = true;
                          status  = !_script->IsEmpty();
                        }

                      #endif

                      if(!incache)
                        {
                          for(XDWORD d=0; d<namescripts.GetSize(); d++)
                            {  
                              namescript = namescripts.Get(d);
                              if(namescript)
                                {                          
                                  XPATH xpath;   

                                  SCRIPT::EliminateExtraChars(namescript);
                  
                                  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_SCRIPTS, xpath);
                                  xpath.Slash_Add();
                                  xpath += namescript->Get();

                                  status = script->LoadAdd(xpath);
                                  if(!status)  
                                    {
                                      break;
                                    }  
                                }
                            }  
                        }
          
                      #ifdef SCRIPT_CACHE_ACTIVE
                      if(status && !incache)
                        {                          
                          GEN_SCRIPT_CACHE.Cache_Add(ID, script->GetScript());
                        }
                      #endif                                          
                      
                      delete script;
                      script = NULL;

                    }                    
                }

              namescripts.DeleteContents();
              namescripts.DeleteAll();              
            
            } 
        } 
    }
  
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SCRIPT_CACHE::SCRIPT_CACHE()
* @brief      Constructor of class
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
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    SCRIPT
* 
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_CACHE::~SCRIPT_CACHE()
{
  Cache_DelAll();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SCRIPT_CACHE::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    SCRIPT
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_CACHE::Clean()
{

}


#pragma endregion


