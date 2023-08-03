/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       Script_Lib_Process.cpp
* 
* @class      SCRIPT_LIB_PROCESS
* @brief      Script Lib Process class
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

#include "Script_Lib_Process.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "APPBase.h"
#include "APPMain.h"

#include "XProcessManager.h"
#include "XVariant.h"

#include "Script.h"

#include "XMemory_Control.h"


#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE


#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SCRIPT_LIB_PROCESS::SCRIPT_LIB_PROCESS()
* @brief      Constructor
* @ingroup    SCRIPT
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LIB_PROCESS::SCRIPT_LIB_PROCESS() : SCRIPT_LIB(SCRIPT_LIB_NAME_PROCESS)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SCRIPT_LIB_PROCESS::~SCRIPT_LIB_PROCESS()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    SCRIPT
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LIB_PROCESS::~SCRIPT_LIB_PROCESS()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT_LIB_PROCESS::AddLibraryFunctions(SCRIPT* script)
* @brief      AddLibraryFunctions
* @ingroup    SCRIPT
* 
* @param[in]  script : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LIB_PROCESS::AddLibraryFunctions(SCRIPT* script)
{
  if(!script) return false;

  this->script = script;

  script->AddLibraryFunction(this, __L("OpenURL")                            , Call_OpenURL);
  script->AddLibraryFunction(this, __L("ExecApplication")                    , Call_ExecApplication);
  script->AddLibraryFunction(this, __L("Call_MakeCommand")                   , Call_MakeCommand);
  script->AddLibraryFunction(this, __L("TerminateAplication")                , Call_TerminateApplication);
  script->AddLibraryFunction(this, __L("TerminateAplicationWithWindow")      , Call_TerminateApplicationWithWindow);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SCRIPT_LIB_PROCESS::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    SCRIPT
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LIB_PROCESS::Clean()
{

}


/*--------------------------------------------------------------------------------------------------------------------*/
/* Library Functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void Call_OpenURL(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
* @brief      Call_OpenURL
* @ingroup    SCRIPT
* 
* @param[in]  library : 
* @param[in]  script : 
* @param[in]  params : 
* @param[in]  returnvalue : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void Call_OpenURL(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
{
  if(!library)      return;
  if(!script)       return;
  if(!params)       return;
  if(!returnvalue)  return;

  returnvalue->Set();

  if(!params->GetSize())
    {
      script->HaveError(SCRIPT_ERRORCODE_INSUF_PARAMS);
      return;
    }

  XSTRING* string1 = (XSTRING*)params->Get(0)->GetData();
  bool     status  = false;
  
  if(string1)
    {      
      status = GEN_XPROCESSMANAGER.OpenURL(string1->Get());      
    }

  (*returnvalue) = status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void Call_MakeCommand(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
* @brief      Call_MakeCommand
* @ingroup    SCRIPT
* 
* @param[in]  library : 
* @param[in]  script : 
* @param[in]  params : 
* @param[in]  returnvalue : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void Call_MakeCommand(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
{
  if(!library)      return;
  if(!script)       return;
  if(!params)       return;
  if(!returnvalue)  return;

  returnvalue->Set();

  if(!params->GetSize())
    {
      script->HaveError(SCRIPT_ERRORCODE_INSUF_PARAMS);
      return;
    }

  XSTRING* command    = NULL;
  bool     status     = false;
  
  if(params->Get(0))
    {
      command = (XSTRING*)params->Get(0)->GetData();
    }
  
  if(command)
    {      
      status = GEN_XPROCESSMANAGER.MakeCommand(command->Get());                       
    }

  (*returnvalue) = status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void Call_ExecApplication(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
* @brief      Call_ExecApplication
* @ingroup    SCRIPT
* 
* @param[in]  library : 
* @param[in]  script : 
* @param[in]  params : 
* @param[in]  returnvalue : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void Call_ExecApplication(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
{
  if(!library)      return;
  if(!script)       return;
  if(!params)       return;
  if(!returnvalue)  return;

  returnvalue->Set();

  if(!params->GetSize())
    {
      script->HaveError(SCRIPT_ERRORCODE_INSUF_PARAMS);
      return;
    }

  XSTRING* app_path   = NULL;
  XSTRING* app_params = NULL;
  bool     status     = false;
  
  if(params->Get(0))
    {
      app_path = (XSTRING*)params->Get(0)->GetData();
    }

  if(params->Get(1))
    {
      app_params = (XSTRING*)params->Get(1)->GetData();
    }
  
  if(app_path)
    {      
      status = GEN_XPROCESSMANAGER.Application_Execute(app_path->Get(), app_params?app_params->Get():__L(""));                       
    }

  (*returnvalue) = status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void Call_TerminateApplication(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
* @brief      Call_TerminateApplication
* @ingroup    SCRIPT
* 
* @param[in]  library : 
* @param[in]  script : 
* @param[in]  params : 
* @param[in]  returnvalue : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void Call_TerminateApplication(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
{  
  if(!library)      return;
  if(!script)       return;
  if(!params)       return;
  if(!returnvalue)  return;

  returnvalue->Set();

  if(!params->GetSize())
    {
      script->HaveError(SCRIPT_ERRORCODE_INSUF_PARAMS);
      return;
    }

  XSTRING* string  = NULL;
  bool     status  = false;
  
  if(params->Get(0))
    {
      string = (XSTRING*)params->Get(0)->GetData();
    }
  
  if(string)
    {      
      status = GEN_XPROCESSMANAGER.Application_Terminate(string->Get());                       
    }

  (*returnvalue) = status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void Call_TerminateApplicationWithWindow(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
* @brief      Call_TerminateApplicationWithWindow
* @ingroup    SCRIPT
* 
* @param[in]  library : 
* @param[in]  script : 
* @param[in]  params : 
* @param[in]  returnvalue : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void Call_TerminateApplicationWithWindow(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
{   
  if(!library)      return;
  if(!script)       return;
  if(!params)       return;
  if(!returnvalue)  return;

  returnvalue->Set();

  if(params->GetSize()<2)
    {
      script->HaveError(SCRIPT_ERRORCODE_INSUF_PARAMS);
      return;
    }
 
  XVECTOR<XPROCESS*>  applist;
  XSTRING             appname       = (*params->Get(0));
  XSTRING             windowstitle  = (*params->Get(1));
  int                 windowsposx   = 0; 
  bool                status        = false;

  if(GEN_XPROCESSMANAGER.Application_GetRunningList(applist, true))
    {
      for(XDWORD c=0; c<applist.GetSize(); c++)
        {                              
          if(applist.Get(c)->GetName()->Find(appname, true)!= XSTRING_NOTFOUND) 
            {  
              if(applist.Get(c)->GetWindowTitle()->Find(windowstitle, false) != XSTRING_NOTFOUND)
                {
                  status = GEN_XPROCESSMANAGER.Application_Terminate((*applist.Get(c)));                     
                  break;
                }
            }
        }
    }
    
  applist.DeleteContents();
  applist.DeleteAll();
   
  (*returnvalue) = status;
}

#pragma endregion

