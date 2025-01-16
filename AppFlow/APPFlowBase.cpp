/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       APPFlowBase.cpp
* 
* @class      APPFLOWBASE
* @brief      Application Flow Base class
* @ingroup    APPFLOW
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

#include "APPFlowBase.h"

#include <stdio.h>

#include "XFactory.h"
#include "XSystem.h"
#include "XTimer.h"
#include "XPath.h"
#include "XTrace.h"
#include "XTranslation.h"
#include "XTranslation_GEN.h"
#include "XLanguage_ISO_639_3.h"
#include "XObserver.h"
#include "XSubject.h"

#include "APPFlow_XEvent.h"
#include "APPFlowLog.h"

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
* @fn         APPFLOWBASE::APPFLOWBASE()
* @brief      Constructor
* @ingroup    APPFLOW
*
* --------------------------------------------------------------------------------------------------------------------*/
APPFLOWBASE::APPFLOWBASE()
{
  Clean();

  RegisterEvent(APPFLOW_XEVENT_TYPE_CHANGESTATUSTYPE); 
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPFLOWBASE::~APPFLOWBASE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    APPFLOW
*
* --------------------------------------------------------------------------------------------------------------------*/
APPFLOWBASE::~APPFLOWBASE()
{
  DeRegisterEvent(APPFLOW_XEVENT_TYPE_CHANGESTATUSTYPE);

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPFLOWBASE::Ini(XVECTOR<XSTRING*>* execparams)
* @brief      Ini
* @ingroup    APPFLOW
*
* @param[in]  execparams :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWBASE::Ini(XVECTOR<XSTRING*>* execparams)
{
  this->execparams  = execparams;

  GEN_XFACTORY_CREATE(xtimerglobal, CreateTimer())
  if(!xtimerglobal) return false;
    
  xtimerglobal->Reset();

  firstupdate = false;

  XDWORD code = GEN_XSYSTEM.GetLanguageSO();

  if(code != XLANGUAGE_ISO_639_3_CODE_INVALID) XTRANSLATION_GEN::GetInstance().Sentences_AddToTranslation(code);

  if(!AppProc_Ini()) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPFLOWBASE::UpdateStep()
* @brief      Update Step application
* @ingroup    APPFLOW
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWBASE::UpdateStep()
{  
  if(!firstupdate)
    {
      if(!AppProc_FirstUpdate()) return false;
      firstupdate = true;
    }

  if(!AppProc_Update()) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPFLOWBASE::End()
* @brief      End application function
* @ingroup    APPFLOW
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWBASE::End()
{
  bool status;

  status = AppProc_LastUpdate();
  if(status) status = AppProc_End();

  GEN_XPUBLISHER.DeRegisterAllEvents();

  if(xtimerglobal)
    {
      GEN_XFACTORY.DeleteTimer(xtimerglobal);
      xtimerglobal = NULL;
    }

  application_name.Empty();
  application_executable.Empty();
  application_ID.Empty();

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XVECTOR<XSTRING*>* APPFLOWBASE::GetExecParams()
* @brief      Obtain the parameters of the application in command line (all on strings)
* @ingroup    APPFLOW
*
* @return     XVECTOR<XSTRING*>* : Vector of strings with the params
*
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<XSTRING*>*  APPFLOWBASE::GetExecParams()
{
  return execparams;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPFLOWBASE_MODE_TYPE APPFLOWBASE::Application_GetMode()
* @brief      Application_GetMode
* @ingroup    APPFLOW
*
* @return     APPFLOWBASE_MODE_TYPE : 
*
* --------------------------------------------------------------------------------------------------------------------*/
APPFLOWBASE_MODE_TYPE APPFLOWBASE::Application_GetMode()
{
  return application_mode;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPFLOWBASE::Application_SetMode(APPFLOWBASE_MODE_TYPE application_mode)
* @brief      application  set mode
* @ingroup    APPFLOW
* 
* @param[in]  application_mode : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APPFLOWBASE::Application_SetMode(APPFLOWBASE_MODE_TYPE application_mode)
{
  this->application_mode = application_mode;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void* APPFLOWBASE::Application_GetHandle()
* @brief      Application_GetHandle
* @ingroup    APPFLOW
*
* @return     void* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
void* APPFLOWBASE::Application_GetHandle()
{
  return application_handle;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPFLOWBASE::Application_SetHandle(void* handle)
* @brief      Application_SetHandle
* @ingroup    APPFLOW
*
* @param[in]  handle : 
*
* --------------------------------------------------------------------------------------------------------------------*/
void APPFLOWBASE::Application_SetHandle(void* handle)
{
  this->application_handle = handle;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPFLOWBASE::Application_GetName()
* @brief      Application_GetName
* @ingroup    APPFLOW
*
* @return     XSTRING* : String pointer with the name of the application
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPFLOWBASE::Application_GetName()
{
  return &application_name;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPFLOWBASE::Application_SetName(XCHAR* name)
* @brief      Application_SetName
* @ingroup    APPFLOW
*
* @param[in]  name : name of the application
*
* --------------------------------------------------------------------------------------------------------------------*/
void APPFLOWBASE::Application_SetName(XCHAR* name)
{
  application_name.Set(name);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* APPFLOWBASE::Application_GetExecutable()
* @brief      application  get executable
* @ingroup    APPFLOW
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPFLOWBASE::Application_GetExecutable()
{
  return &application_executable;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPFLOWBASE::Application_SetExecutable(XCHAR* name)
* @brief      Application_SetExecutable
* @ingroup    APPFLOW
*
* @param[in]  name : 
*
* --------------------------------------------------------------------------------------------------------------------*/
void APPFLOWBASE::Application_SetExecutable(XCHAR* name)
{
  application_executable.Set(name);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPFLOWBASE::Application_GetID()
* @brief      Application_GetID
* @ingroup    APPFLOW
*
* @return     XSTRING* : String with the ID of the aplication
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPFLOWBASE::Application_GetID()
{
  return &application_ID;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTIMER* APPFLOWBASE::GetTimerGlobal()
* @brief      Get timer global for the application
* @ingroup    APPFLOW
*
* @return     XTIMER* : XTIMER class global
*
* --------------------------------------------------------------------------------------------------------------------*/
XTIMER* APPFLOWBASE::GetTimerGlobal()
{
  return xtimerglobal;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPFLOWBASEEXITTYPE APPFLOWBASE::GetExitType()
* @brief      Ge the exit type for the application
* @ingroup    APPFLOW
*
* @return     APPFLOWBASE_EXITTYPE : status of the exit
*
* --------------------------------------------------------------------------------------------------------------------*/
APPFLOWBASE_EXITTYPE APPFLOWBASE::GetExitType()
{
  return exittype;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPFLOWBASE::SetExitType(APPFLOWBASE_EXITTYPE exittype)
* @brief      SetExitType
* @ingroup    APPFLOW
* 
* @param[in]  exittype : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APPFLOWBASE::SetExitType(APPFLOWBASE_EXITTYPE exittype)
{
  if(this->exittype != APPFLOWBASE_EXITTYPE_UNKNOWN) return;

  this->exittype = exittype;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPFLOWBASE::GetExitTypeString(XSTRING exittypestring)
* @brief      GetExitTypeString
* @ingroup    APPFLOW
*
* @param[in]  exittypestring :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWBASE::GetExitTypeString(XSTRING& exittypestring)
{
  exittypestring.Empty();

  switch(GetExitType())
    {
      case APPFLOWBASE_EXITTYPE_UNKNOWN             : exittypestring = XT_L(XTRANSLATION_GEN_ID_APPFLOWCONSOLE_EXIT_NOTINFO);             break;
      case APPFLOWBASE_EXITTYPE_BY_SERIOUSERROR     : exittypestring = XT_L(XTRANSLATION_GEN_ID_APPFLOWCONSOLE_EXIT_BY_SERIOUSERROR);     break;
      case APPFLOWBASE_EXITTYPE_BY_UPDATE           : exittypestring = XT_L(XTRANSLATION_GEN_ID_APPFLOWCONSOLE_EXIT_BY_UPDATE);           break;
      case APPFLOWBASE_EXITTYPE_BY_APPLICATION      : exittypestring = XT_L(XTRANSLATION_GEN_ID_APPFLOWCONSOLE_EXIT_BY_APPLICATION);      break;
      case APPFLOWBASE_EXITTYPE_BY_USER             : exittypestring = XT_L(XTRANSLATION_GEN_ID_APPFLOWCONSOLE_EXIT_BY_USER);             break;
      case APPFLOWBASE_EXITTYPE_BY_SHUTDOWN         : exittypestring = XT_L(XTRANSLATION_GEN_ID_APPFLOWCONSOLE_EXIT_BY_SHUTDOWN);         break;
      case APPFLOWBASE_EXITTYPE_BY_INVALIDLICENSE   : exittypestring = XT_L(XTRANSLATION_GEN_ID_APPFLOWCONSOLE_EXIT_BY_INVALIDLICENSE);   break;
      case APPFLOWBASE_EXITTYPE_BY_EXPIREDLICENSE   : exittypestring = XT_L(XTRANSLATION_GEN_ID_APPFLOWCONSOLE_EXIT_BY_EXPIREDLICENSE) ;  break;
                                      default   : return false;                                                                   
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSYSTEM_CHANGESTATUSTYPE APPFLOWBASE::GetSystemChangeStatus()
* @brief      GetSystemChangeStatus
* @ingroup    APPFLOW
*
* @return     XSYSTEM_CHANGESTATUSTYPE :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSYSTEM_CHANGESTATUSTYPE APPFLOWBASE::GetSystemChangeStatus()
{
  return systemchangestatustype;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPFLOWBASE::SetSystemChangeStatus(XSYSTEM_CHANGESTATUSTYPE systemchangestatustype)
* @brief      SetSystemChangeStatus
* @ingroup    APPFLOW
* 
* @param[in]  systemchangestatustype : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APPFLOWBASE::SetSystemChangeStatus(XSYSTEM_CHANGESTATUSTYPE systemchangestatustype)
{
  if(this->systemchangestatustype == systemchangestatustype) 
    {
      return;
    }

  this->systemchangestatustype = systemchangestatustype;

  
  XSTRING statusstr;  

  switch(systemchangestatustype)
    {
      case XSYSTEM_CHANGESTATUSTYPE_NONE                :
                                  default               : statusstr = __L("normal");                break;
      case XSYSTEM_CHANGESTATUSTYPE_REBOOT              : statusstr = __L("reboot");                break;
      case XSYSTEM_CHANGESTATUSTYPE_CONSOLE_CONNECT     : statusstr = __L("console connect");       break;
      case XSYSTEM_CHANGESTATUSTYPE_CONSOLE_DISCONNECT  : statusstr = __L("console disconnect");    break;
      case XSYSTEM_CHANGESTATUSTYPE_SESSION_LOGON       : statusstr = __L("session logon");         break;
      case XSYSTEM_CHANGESTATUSTYPE_SESSION_LOGOFF      : statusstr = __L("session logooff");       break;
      case XSYSTEM_CHANGESTATUSTYPE_SESSION_LOCK        : statusstr = __L("session lock");          break;
      case XSYSTEM_CHANGESTATUSTYPE_SESSION_UNLOCK      : statusstr = __L("session unlock");        break;
      case XSYSTEM_CHANGESTATUSTYPE_POWEROFF            : statusstr = __L("power off");             break;
      case XSYSTEM_CHANGESTATUSTYPE_SUSPEND             : statusstr = __L("suspend");               break;
    }

  //XTRACE_PRINTCOLOR(XTRACE_COLOR_GREEN, __L("[APP Base System] Mode change to [%s]"), statusstr.Get());

  APPFLOW_XEVENT  xevent(this, APPFLOW_XEVENT_TYPE_CHANGESTATUSTYPE);      
  xevent.SetChangeStatusType(systemchangestatustype);
  PostEvent(&xevent); 
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPFLOWBASE::AppProc_PlatformIni()
* @brief      AppProc_PlatformIni
* @ingroup    APPFLOW
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWBASE::AppProc_PlatformIni()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPFLOWBASE::AppProc_Ini()
* @brief      Ini callback for this class to use for the application class real
* @note       VIRTUAL
* @ingroup    APPFLOW
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWBASE::AppProc_Ini()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPFLOWBASE::AppProc_FirstUpdate()
* @brief      First Update callback for this class to use for the application class real
* @note       VIRTUAL
* @ingroup    APPFLOW
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWBASE::AppProc_FirstUpdate()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPFLOWBASE::AppProc_Update()
* @brief      Update callback for this class to use for the application class real
* @note       VIRTUAL
* @ingroup    APPFLOW
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWBASE::AppProc_Update()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPFLOWBASE::AppProc_LastUpdate()
* @brief      Last Update callback for this class to use for the application class real
* @note       VIRTUAL
* @ingroup    APPFLOW
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWBASE::AppProc_LastUpdate()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPFLOWBASE::AppProc_EndBlockedResources()
* @brief      AppProc_EndBlockedResources
* @ingroup    APPFLOW
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWBASE::AppProc_EndBlockedResources()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPFLOWBASE::AppProc_End()
* @brief      End callback for this class to use for the application class real
* @note       VIRTUAL
* @ingroup    APPFLOW
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWBASE::AppProc_End()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPFLOWBASE::AppProc_PlatformEnd()
* @brief      AppProc_PlatformEnd
* @ingroup    APPFLOW
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWBASE::AppProc_PlatformEnd()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPFLOWBASE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    APPFLOW
*
* --------------------------------------------------------------------------------------------------------------------*/
void APPFLOWBASE::Clean()
{  
  execparams              = NULL;

  application_mode        = APPFLOWBASE_MODE_TYPE_UNKNOWN;
  application_handle      = NULL;

  xtimerglobal            = NULL;

  firstupdate             = false;

  exittype                = APPFLOWBASE_EXITTYPE_UNKNOWN;
  systemchangestatustype  = XSYSTEM_CHANGESTATUSTYPE_NONE;
}


#pragma endregion