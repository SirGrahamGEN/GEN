/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       Script.cpp
* 
* @class      SCRIPT
* @brief      Script base class
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

#include "Script.h"

#include <stdio.h>
#include <ctype.h>

#include "XPath.h"
#include "XFactory.h"
#include "XFileTXT.h"
#include "XTrace.h"

#ifdef SCRIPT_G_ACTIVE
#include "Script_Language_G.h"
#endif

#ifdef SCRIPT_LUA_ACTIVE
#include "Script_Language_Lua.h"
#endif

#ifdef SCRIPT_JAVASCRIPT_ACTIVE
#include "Script_Language_Javascript.h"
#endif

#ifdef SCRIPT_CACHE_ACTIVE
#include "Script_Cache.h"
#endif

#include "Script_XEvent.h"

#include "Script_Lib_Math.h"
#include "Script_Lib_Rand.h"
#include "Script_Lib_Timer.h"
#include "Script_Lib_String.h"
#include "Script_Lib_Path.h"
#include "Script_Lib_Dir.h"
#include "Script_Lib_Trace.h"

#include "Script_Lib_System.h"
#include "Script_Lib_Process.h"
#include "Script_Lib_Log.h"
#include "Script_Lib_Console.h"
#include "Script_Lib_CFG.h"
#include "Script_Lib_Window.h"
#include "Script_Lib_InputSimulate.h"
#include "Script_Lib_DevTest.h"

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



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SCRIPT::SCRIPT()
* @brief      Constructor of class
* @ingroup    SCRIPT
* 
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT::SCRIPT()
{
  Clean();

  GEN_XFACTORY_CREATE(xtimer, CreateTimer())
  if(!xtimer) return;

  xfiletxt = new XFILETXT();
  if(!xfiletxt) return;

  RegisterEvent(SCRIPT_XEVENT_TYPE_ERROR);
  RegisterEvent(SCRIPT_XEVENT_TYPE_BREAK);

  thread = CREATEXTHREAD(XTHREADGROUPID_SCRIPT, __L("SCRIPT::SCRIPT"),ThreadFunction,(void*)this);

  AddInternalLibraries();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SCRIPT::~SCRIPT()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    SCRIPT
* 
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT::~SCRIPT()
{
  DeRegisterEvent(SCRIPT_XEVENT_TYPE_ERROR);
  DeRegisterEvent(SCRIPT_XEVENT_TYPE_BREAK);

  if(xtimer) GEN_XFACTORY.DeleteTimer(xtimer);

  if(thread)
    {
      thread->End();
      DELETEXTHREAD(XTHREADGROUPID_SCRIPT, thread);
    }

  if(xfiletxt)
    {
      delete xfiletxt;
    }

  DeleteLibraryFuncions();

  DeleteAllLibrarys();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SCRIPT_TYPE SCRIPT::GetType()
* @brief      Get type
* @ingroup    SCRIPT
* 
* @return     SCRIPT_TYPE : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_TYPE SCRIPT::GetType()
{
  return type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SCRIPT_TYPE SCRIPT::GetTypeByExtension(XCHAR* namefilescript)
* @brief      Get type by extension
* @ingroup    SCRIPT
* 
* @param[in]  namefilescript : 
* 
* @return     SCRIPT_TYPE : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_TYPE SCRIPT::GetTypeByExtension(XCHAR* namefilescript)
{
  XSTRING       ext;
  SCRIPT_TYPE   type            = SCRIPT_TYPE_UNKNOWN;
  XPATH         _namefilescript;

  _namefilescript = namefilescript;
                                                                                        
  if(!_namefilescript.IsEmpty())
    {
      _namefilescript.GetExt(ext);

      #ifdef SCRIPT_G_ACTIVE
      if(!ext.Compare(__L(".g")   , true))  
        {
          type = SCRIPT_TYPE_G;
        }
      #endif

      #ifdef SCRIPT_LUA_ACTIVE
      if(!ext.Compare(__L(".lua") , true))
        {
          type = SCRIPT_TYPE_LUA;
        }
      #endif

      #ifdef SCRIPT_JAVASCRIPT_ACTIVE
      if(!ext.Compare(__L(".js")  , true)) 
        {
          type = SCRIPT_TYPE_JAVASCRIPT;
        }
      #endif
    }

  return type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SCRIPT* SCRIPT::Create(XCHAR* namefilescript)
* @brief      Create
* @ingroup    SCRIPT
* 
* @param[in]  namefilescript : 
* 
* @return     SCRIPT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT* SCRIPT::Create(XCHAR* namefilescript)
{
  return Create(GetTypeByExtension(namefilescript));  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SCRIPT* SCRIPT::Create(SCRIPT_TYPE type)
* @brief      Create
* @ingroup    SCRIPT
* 
* @param[in]  type : 
* 
* @return     SCRIPT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT* SCRIPT::Create(SCRIPT_TYPE type)
{
  SCRIPT* script = NULL;

  switch(type)
    {
      case SCRIPT_TYPE_UNKNOWN      : break;

      case SCRIPT_TYPE_G            : 
                                      #ifdef SCRIPT_G_ACTIVE
                                      script = new SCRIPT_LNG_G();
                                      #endif
                                      break;  

      case SCRIPT_TYPE_LUA          : 
                                      #ifdef SCRIPT_LUA_ACTIVE
                                      script = new SCRIPT_LNG_LUA();
                                      #endif
                                      break;

      case SCRIPT_TYPE_JAVASCRIPT   :  
                                      #ifdef SCRIPT_JAVASCRIPT_ACTIVE
                                      script = new SCRIPT_LNG_JAVASCRIPT();
                                      #endif
                                      break;     
    }


  return script;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT::Load(XPATH& xpath)
* @brief      Load
* @ingroup    SCRIPT
* 
* @param[in]  xpath : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT::Load(XPATH& xpath)
{
  #ifdef SCRIPT_CACHE_ACTIVE

  xpath.Slash_Normalize(false);

  XDWORD ID = GEN_SCRIPT_CACHE.GenerateID(xpath);

  XSTRING* _script = GEN_SCRIPT_CACHE.Cache_Get(ID);
  if(_script)
    {
      script.Empty();
      script += _script->Get();  

      GetNameScript()->Format(__L("ID%08X"), ID);

      return true;
    }

  #endif

  if(!xfiletxt) return false;

  bool status = false;

  this->xpath = xpath;

  xpath.GetNamefileExt(namescript);

  if(xfiletxt->Open(xpath))
    {
      if(xfiletxt->ReadAllFile()) status = true;

      script.Empty();

      for(int c=0; c<xfiletxt->GetNLines(); c++)
        {
          script += xfiletxt->GetLine(c)->Get();
      
          AddReturnByType();
        }

      xfiletxt->Close();
    }

  #ifdef SCRIPT_CACHE_ACTIVE
  if(status)
    {
      ID = GEN_SCRIPT_CACHE.GenerateID(xpath);      
      GEN_SCRIPT_CACHE.Cache_Add(ID, &script);      
    }
  #endif

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT::LoadAdd(XPATH& xpath)
* @brief      Load add
* @ingroup    SCRIPT
* 
* @param[in]  xpath : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT::LoadAdd(XPATH& xpath)
{  
  if(!xfiletxt) return false;

  bool status = false;

  AddReturnByType();
  AddReturnByType();
  
  this->xpath = xpath;

  xpath.GetNamefileExt(namescript);

  if(xfiletxt->Open(xpath))
    {
      if(xfiletxt->ReadAllFile()) status = true;

      for(int c=0; c<xfiletxt->GetNLines(); c++)
        {
          script += xfiletxt->GetLine(c)->Get();
      
          AddReturnByType();
        }

      xfiletxt->Close();
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT::Save(XPATH& xpath)
* @brief      Save
* @ingroup    SCRIPT
* 
* @param[in]  xpath : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT::Save(XPATH& xpath)
{
  if(!xfiletxt) return false;

  bool status = false;

  this->xpath = xpath;

  if(xfiletxt->Create(xpath))
    {
      if(xfiletxt->WriteAllFile()) status = true;
      xfiletxt->Close();
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT::LoadScriptAndRun(XVECTOR<XSTRING*>* listscripts, SCRFUNCADJUSTLIBRARYS adjustlibrarys)
* @brief      Load script and run
* @ingroup    SCRIPT
* 
* @param[in]  listscripts : 
* @param[in]  adjustlibrarys : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT::LoadScriptAndRun(XVECTOR<XSTRING*>* listscripts, SCRFUNCADJUSTLIBRARYS adjustlibrarys)
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

                      if(adjustlibrarys)
                        {
                          adjustlibrarys(script);
                        }
                 
                      GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_SCRIPTS, allpath);
    
                      for(XDWORD d=0; d<namescripts.GetSize(); d++)
                        {  
                          allpath += __C(',');  
                          allpath += namescript->Get();  
                        }
                                       
                      #ifdef SCRIPT_CACHE_ACTIVE

                      allpath.Slash_Normalize(false);
                      ID = GEN_SCRIPT_CACHE.GenerateID(allpath);
                      XSTRING* _script = GEN_SCRIPT_CACHE.Cache_Get(ID);
                      if(_script)
                        {                         
                          (*script->GetScript()) += _script->Get();      

                          incache = true;
                          status  = !_script->IsEmpty();

                          script->GetNameScript()->Format(__L("ID%08X"), ID);
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

                      if(status)
                        {                               
                          script->Run();                                       
                        }
                      
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
* @fn         bool SCRIPT::AddReturnByType()
* @brief      Add return by type
* @ingroup    SCRIPT
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT::AddReturnByType()
{
  switch(type)
    {
      case SCRIPT_TYPE_UNKNOWN       : 
                           default   : script += __L("\r\n"); break;
      case SCRIPT_TYPE_G             : script += __L("\r\n"); break;
      case SCRIPT_TYPE_LUA           : script += __L("\r");   break;
      case SCRIPT_TYPE_JAVASCRIPT    : script += __L("\r");   break;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT::IsScript(XPATH& xpath, XCHAR* extension)
* @brief      Is script
* @ingroup    SCRIPT
* 
* @param[in]  xpath : 
* @param[in]  extension : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT::IsScript(XPATH& xpath, XCHAR* extension)
{
  if(xpath.IsEmpty()) return false;

  if(!xpath.Find(extension, true)) return true;

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* SCRIPT::GetNameScript()
* @brief      Get name script
* @ingroup    SCRIPT
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* SCRIPT::GetNameScript()
{
  return &namescript;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* SCRIPT::GetScript()
* @brief      Get script
* @ingroup    SCRIPT
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* SCRIPT::GetScript()
{
  return &script;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XPATH* SCRIPT::GetPath()
* @brief      Get path
* @ingroup    SCRIPT
* 
* @return     XPATH* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XPATH* SCRIPT::GetPath()
{
  return &xpath;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int SCRIPT::Run(int* returnval)
* @brief      Run
* @ingroup    SCRIPT
* 
* @param[in]  returnval : 
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int SCRIPT::Run(int* returnval)
{
  if(script.IsEmpty()) 
    {
      return SCRIPT_ERRORCODE_INTERNALERROR;
    }

  isrunwiththread = false;
  if(thread) isrunwiththread = thread->IsRunning();

  errorcode  = 0;
  iscancelexec = false;
 
  return errorcode;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT::RunWithThread()
* @brief      Run with thread
* @ingroup    SCRIPT
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT::RunWithThread()
{
  if(!thread) return false;

  return thread->Ini();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT::IsRunWithThread()
* @brief      Is run with thread
* @ingroup    SCRIPT
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT::IsRunWithThread()
{
  return isrunwiththread;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT::IsRunThread(SCRIPT_G_ERRORCODE* error,int* returnvalue)
* @brief      Is run thread
* @ingroup    SCRIPT
*
* @param[in]  error :
* @param[in]  returnvalue :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT::IsRunThread(int* error,int* returnvalue)
{
  if(!thread) return false;

  bool isrun = thread->IsRunning();

  if(!isrun)
    {
      if(error) (*error) = errorcode;

      if(!errorcode)
        {
          if(returnvalue) (*returnvalue) = returnvaluescript;
        }

       thread->End();
    }

  return isrun;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT::CancelExecution()
* @brief      Cancel execution
* @ingroup    SCRIPT
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT::CancelExecution()
{
  if(script.IsEmpty()) return false;

  iscancelexec = true;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XTIMER* SCRIPT::GetTimer()
* @brief      Get timer
* @ingroup    SCRIPT
* 
* @return     XTIMER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XTIMER* SCRIPT::GetTimer()
{
  return xtimer;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XTHREADCOLLECTED* SCRIPT::GetThread()
* @brief      Get thread
* @ingroup    SCRIPT
* 
* @return     XTHREADCOLLECTED* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XTHREADCOLLECTED* SCRIPT::GetThread()
{
  return thread;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_LIB* SCRIPT::GetLibrary(XCHAR* ID)
* @brief      Get library
* @ingroup    SCRIPT
*
* @param[in]  ID :
*
* @return     SCRIPT_LIB* :
*
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LIB* SCRIPT::GetLibrary(XCHAR* ID)
{
  if(librarys.IsEmpty()) return NULL;

  for(int c=0;c<(int)librarys.GetSize();c++)
    {
      SCRIPT_LIB* scriptlib = (SCRIPT_LIB*)librarys.Get(c);
      if(scriptlib)
        {
          XSTRING* IDlib = scriptlib->GetID();
          if(IDlib)
            {
              if(!IDlib->Compare(ID)) 
                {
                  return scriptlib;
                }
            }
        }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT::AddLibrary(SCRIPT_LIB* scriptlib)
* @brief      Add library
* @ingroup    SCRIPT
*
* @param[in]  scriptlib :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT::AddLibrary(SCRIPT_LIB* scriptlib)
{
  if(!scriptlib) return false;

  librarys.Add(scriptlib);

  return scriptlib->AddLibraryFunctions(this);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT::DeleteAllLibrarys()
* @brief      Delete all librarys
* @ingroup    SCRIPT
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT::DeleteAllLibrarys()
{
  if(librarys.IsEmpty()) return false;

  librarys.DeleteContents();
  librarys.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SCRIPT_LIB_FUNCTION* SCRIPT::GetLibraryFunction(XCHAR* name)
* @brief      Get library function
* @ingroup    SCRIPT
* 
* @param[in]  name : 
* 
* @return     SCRIPT_LIB_FUNCTION* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LIB_FUNCTION* SCRIPT::GetLibraryFunction(XCHAR* name)
{
  for(XDWORD c=0;c<libraryfunctions.GetSize(); c++)
    {
      SCRIPT_LIB_FUNCTION* function = (SCRIPT_LIB_FUNCTION*)libraryfunctions.Get(c);
      if(function)
        {
          if(!function->GetName()->Compare(name)) return function;
        }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SCRIPT_LIB_FUNCTION* SCRIPT::GetLibraryFunction(void* ptrfunction)
* @brief      Get library function
* @ingroup    SCRIPT
* 
* @param[in]  ptrfunction : 
* 
* @return     SCRIPT_LIB_FUNCTION* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LIB_FUNCTION* SCRIPT::GetLibraryFunction(void* ptrfunction)
{
  for(XDWORD c=0;c<libraryfunctions.GetSize(); c++)
    {
      SCRIPT_LIB_FUNCTION* function = (SCRIPT_LIB_FUNCTION*)libraryfunctions.Get(c);
      if(function)
        {
          if((void*)(function->GetFunctionLibrary()) == ptrfunction) return function;
        }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT::AddLibraryFunction(SCRIPT_LIB* library, XCHAR* name, SCRFUNCIONLIBRARY libfunction)
* @brief      Add library function
* @ingroup    SCRIPT
* 
* @param[in]  library : 
* @param[in]  name : 
* @param[in]  libfunction : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT::AddLibraryFunction(SCRIPT_LIB* library, XCHAR* name, SCRFUNCIONLIBRARY libfunction)
{
  SCRIPT_LIB_FUNCTION* function = new SCRIPT_LIB_FUNCTION(library, name, libfunction);
  if(!function) return false;

  libraryfunctions.Add(function);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT::DeleteLibraryFuncions()
* @brief      Delete library funcions
* @ingroup    SCRIPT
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT::DeleteLibraryFuncions()
{
  if(libraryfunctions.IsEmpty()) return false;

  libraryfunctions.DeleteContents();
  libraryfunctions.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT::AddInternalLibraries()
* @brief      Add internal libraries
* @ingroup    SCRIPT
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT::AddInternalLibraries()
{  
  SCRIPT_LIB* lib;

  for(int c=0; c<15; c++)
    {
      lib = NULL;

      switch(c)
        {
          // Standard 
          case  0 : lib = new SCRIPT_LIB_MATH();        break;
          case  1 : lib = new SCRIPT_LIB_RAND();        break;
          case  2 : lib = new SCRIPT_LIB_TIMER();       break;
          case  3 : lib = new SCRIPT_LIB_STRING();      break;
          case  4 : lib = new SCRIPT_LIB_PATH();        break;
          case  5 : lib = new SCRIPT_LIB_DIR();         break;
          case  6 : lib = new SCRIPT_LIB_TRACE();       break;

          // Optionals
          case  7 :
                    #ifdef SCRIPT_LIB_SYSTEM_ACTIVE
                    lib = new SCRIPT_LIB_SYSTEM();        
                    #endif
                    break;
          case  8 :
                    #ifdef SCRIPT_LIB_PROCESS_ACTIVE
                    lib = new SCRIPT_LIB_PROCESS();        
                    #endif
                    break;
          case  9 :
                    #ifdef SCRIPT_LIB_LOG_ACTIVE
                    lib = new SCRIPT_LIB_LOG();        
                    #endif
                    break;
          case 10 :
                    #ifdef SCRIPT_LIB_CONSOLE_ACTIVE
                    lib = new SCRIPT_LIB_CONSOLE();        
                    #endif
                    break;
          case 11 :
                    #ifdef SCRIPT_LIB_CFG_ACTIVE
                    lib = new SCRIPT_LIB_CFG();                                
                    #endif
                    break;
          case 12 :
                    #ifdef SCRIPT_LIB_WINDOW_ACTIVE
                    lib = new SCRIPT_LIB_WINDOW();        
                    #endif
                    break;
          case 13 :
                    #ifdef SCRIPT_LIB_INPUTSIMULATE_ACTIVE
                    lib = new SCRIPT_LIB_INPUTSIMULATE();        
                    #endif
                    break;
          case 14 :
                    #ifdef SCRIPT_LIB_DEVTEST_ACTIVE
                    lib = new SCRIPT_LIB_DEVTEST();        
                    #endif
                    break;
        } 

      if(lib)
        {
          AddLibrary(lib);
        }           
    }      

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int SCRIPT::GetErrorScript()
* @brief      Get error script
* @ingroup    SCRIPT
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int SCRIPT::GetErrorScript()
{
  return errorcode;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT::SetErrorScript(int errorcode)
* @brief      Set error script
* @ingroup    SCRIPT
* 
* @param[in]  errorcode : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT::SetErrorScript(int errorcode)
{
  this->errorcode = errorcode;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT::HaveError(int errorcode)
* @brief      Have error
* @ingroup    SCRIPT
* 
* @param[in]  errorcode : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT::HaveError(int errorcode)
{
  return (!errorcode)?false:true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT::EliminateExtraChars(XSTRING* namescript)
* @brief      Eliminate extra chars
* @ingroup    SCRIPT
* 
* @param[in]  namescript : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT::EliminateExtraChars(XSTRING* namescript)
{
  if(!namescript)
    {
      return false;
    }

  if(namescript->IsEmpty())
    {
      return false;
    }

  namescript->DeleteCharacter(__C(' '), XSTRINGCONTEXT_FROM_FIRST);
  namescript->DeleteCharacter(__C(' '), XSTRINGCONTEXT_TO_END);

  namescript->DeleteCharacter(__C('\t'), XSTRINGCONTEXT_FROM_FIRST);
  namescript->DeleteCharacter(__C('\t'), XSTRINGCONTEXT_TO_END);
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SCRIPT::HandleEvent(XEVENT* xevent)
* @brief      Handle event
* @note       INTERNAL
* @ingroup    SCRIPT
* 
* @param[in]  xevent : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT::HandleEvent(XEVENT* xevent)
{
  if(!xevent) return;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SCRIPT::ThreadFunction(void* data)
* @brief      Thread function
* @ingroup    SCRIPT
* 
* @param[in]  data : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT::ThreadFunction(void* data)
{
  SCRIPT* script = (SCRIPT*)data;
  if(!script) return;

  int returnvaluescript;

  script->SetErrorScript(script->Run(&returnvaluescript));

  script->GetThread()->Run(false);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SCRIPT::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    SCRIPT
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT::Clean()
{
  type                = SCRIPT_TYPE_UNKNOWN;

  xpath.Empty();

  xfiletxt            = NULL;
  namescript          = __L("");
  script.Empty();

  xtimer              = NULL;
  errorcode           = 0;

  thread              = NULL;
  isrunwiththread     = false;

  returnvaluescript   = 0;

  iscancelexec        = false;
}


#pragma endregion


