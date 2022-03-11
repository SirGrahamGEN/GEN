/**-------------------------------------------------------------------------------------------------------------------
*
* @file       Script.cpp
*
* @class      SCRIPT
* @brief
* @ingroup    SCRIPT
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

#include <stdio.h>
#include <ctype.h>

#include "XPath.h"
#include "XFactory.h"
#include "XFileTXT.h"
#include "XThread.h"
#include "XTrace.h"
#include "XThreadCollected.h"

#include "Script_XEvent.h"
#include "Script_Lib.h"

#include "Script.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT::SCRIPT()
* @brief      Constructor
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT::~SCRIPT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
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

  librarys.DeleteAll();

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT::Load(XPATH& xpath)
* @brief      Load
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  xpath :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT::Load(XPATH& xpath)
{
  if(!xfiletxt) return false;

  bool status = false;

  this->xpath = xpath;

  xpath.GetNamefileExt(namescript);

  if(xfiletxt->Open(xpath))
    {
      if(xfiletxt->ReadAllFile()) status = true;

      script.Empty();

      for(int c=0;c<xfiletxt->GetNLines();c++)
        {
          script += xfiletxt->GetLine(c)->Get();
          script += __L("\n");
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  xpath :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @fn         bool SCRIPT::IsScript(XPATH& xpath, XCHAR* extension)
* @brief      IsScript
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  xpath :
* @param[in]  extension :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT::IsScript(XPATH& xpath, XCHAR* extension)
{
  if(xpath.IsEmpty()) return false;

  if(!xpath.Find(extension, true)) return true;

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* SCRIPT::GetNameScript()
* @brief      GetNameScript
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* SCRIPT::GetNameScript()
{
  return &namescript;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* SCRIPT::GetScript()
* @brief      GetScript
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* SCRIPT::GetScript()
{
  return &script;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPATH* SCRIPT::GetPath()
* @brief      GetPath
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XPATH* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XPATH* SCRIPT::GetPath()
{
  return &xpath;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_G_ERRORCODE SCRIPT::Run(int* returnval)
* @brief      Run
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  returnval :
*
* @return     SCRIPT_G_ERRORCODE :
*
*---------------------------------------------------------------------------------------------------------------------*/
int  SCRIPT::Run(int* returnval)
{
  if(script.IsEmpty()) return SCRIPT_ERRORCODE_INTERNALERROR;

  isrunwiththread = false;
  if(thread) isrunwiththread = thread->IsRunning();

  errorcode  = 0;
  iscancelexec = false;
 //breakfound  = false;

  return errorcode;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT::RunWithThread()
* @brief      RunWithThread
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT::RunWithThread()
{
  if(!thread) return false;

  return thread->Ini();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT::IsRunWithThread()
* @brief      IsRunWithThread
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT::IsRunWithThread()
{
  return isrunwiththread;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT::IsRunThread(SCRIPT_G_ERRORCODE* error,int* returnvalue)
* @brief      IsRunThread
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  error :
* @param[in]  returnvalue :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @brief      CancelExecution
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT::CancelExecution()
{
  if(script.IsEmpty()) return false;

  iscancelexec = true;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTIMER* SCRIPT::GetTimer()
* @brief      GetTimer
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XTIMER* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XTIMER* SCRIPT::GetTimer()
{
  return xtimer;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTHREADCOLLECTED* SCRIPT::GetThread()
* @brief      GetThread
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XTHREADCOLLECTED* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XTHREADCOLLECTED* SCRIPT::GetThread()
{
  return thread;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_LIB* SCRIPT::GetLibrary(XCHAR* ID)
* @brief      GetLibrary
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  ID :
*
* @return     SCRIPT_LIB* :
*
*---------------------------------------------------------------------------------------------------------------------*/
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
              if(!IDlib->Compare(ID)) return scriptlib;
            }
        }
    }

  return NULL;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT::AddLibrary(SCRIPT_LIB* scriptlib)
* @brief      AddLibrary
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  scriptlib :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT::AddLibrary(SCRIPT_LIB* scriptlib)
{
  if(!scriptlib) return false;

  librarys.Add(scriptlib);

   return scriptlib->AddLibraryFunctions(this);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT::DeleteAllLibrarys()
* @brief      DeleteAllLibrarys
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT::DeleteAllLibrarys()
{
  if(librarys.IsEmpty()) return false;

  librarys.DeleteContents();
  librarys.DeleteAll();

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_LIBFUNCTION* SCRIPT::GetLibraryFunction(XCHAR* name)
* @brief      GetLibraryFunction
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  name :
*
* @return     SCRIPT_LIBFUNCTION* :
*
*---------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LIBFUNCTION* SCRIPT::GetLibraryFunction(XCHAR* name)
{
  for(XDWORD c=0;c<libraryfunctions.GetSize(); c++)
    {
      SCRIPT_LIBFUNCTION* function = (SCRIPT_LIBFUNCTION*)libraryfunctions.Get(c);
      if(function)
        {
          if(!function->GetName()->Compare(name)) return function;
        }
    }

  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_LIBFUNCTION* SCRIPT::GetLibraryFunction(void* ptrfunction)
* @brief      GetLibraryFunction
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  ptrfunction :
*
* @return     SCRIPT_LIBFUNCTION* :
*
*---------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LIBFUNCTION* SCRIPT::GetLibraryFunction(void* ptrfunction)
{
  for(XDWORD c=0;c<libraryfunctions.GetSize(); c++)
    {
      SCRIPT_LIBFUNCTION* function = (SCRIPT_LIBFUNCTION*)libraryfunctions.Get(c);
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
* @brief      AddLibraryFunction
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  library :
* @param[in]  name :
* @param[in]  libfunction :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT::AddLibraryFunction(SCRIPT_LIB* library, XCHAR* name, SCRFUNCIONLIBRARY libfunction)
{
  SCRIPT_LIBFUNCTION* function = new SCRIPT_LIBFUNCTION(library, name, libfunction);
  if(!function) return false;

  libraryfunctions.Add(function);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT::DeleteLibraryFuncions()
* @brief      DeleteLibraryFuncions
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT::DeleteLibraryFuncions()
{
  if(libraryfunctions.IsEmpty()) return false;

  libraryfunctions.DeleteContents();
  libraryfunctions.DeleteAll();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_G_ERRORCODE SCRIPT::GetErrorScript()
* @brief      GetErrorScript
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int SCRIPT::GetErrorScript()
{
  return errorcode;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT::SetErrorScript(int errorcode)
* @brief      SetErrorScript
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  errorcode :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT::SetErrorScript(int errorcode)
{
  this->errorcode = errorcode;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT::HaveError(SCRIPT_G_ERRORCODE errorcode)
* @brief      HaveError
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  errorcode :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT::HaveError(int errorcode)
{
  return (!errorcode)?false:true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPT::ThreadFunction(void* data)
* @brief      ThreadFunction
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  data :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void SCRIPT::ThreadFunction(void* data)
{
  SCRIPT* script = (SCRIPT*)data;
  if(!script) return;

  int returnvaluescript;

  script->SetErrorScript(script->Run(&returnvaluescript));

  //script->SetReturnValueScript(returnvaluescript);

  script->GetThread()->Run(false);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void SCRIPT::Clean()
{
  xpath.Empty();
  xfiletxt            = NULL;
  namescript          = __L("N/A");
  script.Empty();

  xtimer              = NULL;
  errorcode           = 0;

  thread              = NULL;
  isrunwiththread     = false;

  returnvaluescript   = 0;

  iscancelexec        = false;
}




