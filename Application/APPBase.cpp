/**-------------------------------------------------------------------------------------------------------------------
*
* @file       APPBase.cpp
*
* @class      APPBASE
* @brief      Application Base class
* @ingroup    APPLICATION
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

#include "XFactory.h"
#include "XSystem.h"
#include "XTimer.h"
#include "XPath.h"
#include "XTrace.h"
#include "XTranslation.h"
#include "XTranslation_GEN.h"
#include "XTranslation.h"
#include "XLanguage_ISO_639_3.h"
#include "XObserver.h"
#include "XSubject.h"

#include "APPLog.h"

#include "APPBase.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPBASE::APPBASE()
* @brief      Constructor
* @ingroup    APPLICATION
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
APPBASE::APPBASE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPBASE::~APPBASE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    APPLICATION
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
APPBASE::~APPBASE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPBASE::Ini(XVECTOR<XSTRING*>* execparams)
* @brief      Ini
* @ingroup    APPLICATION
*
* @param[in]  execparams :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPBASE::Ini(XVECTOR<XSTRING*>* execparams)
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
* @fn         bool APPBASE::UpdateStep()
* @brief      Update Step application
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPBASE::UpdateStep()
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
* @fn         bool APPBASE::End()
* @brief      End application function
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPBASE::End()
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

  applicationname.Empty();
  applicationexecutable.Empty();
  applicationID.Empty();

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XVECTOR<XSTRING*>* APPBASE::GetExecParams()
* @brief      Obtain the parameters of the application in command line (all on strings)
* @ingroup    APPLICATION
*
* @return     XVECTOR<XSTRING*>* : Vector of strings with the params
*
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<XSTRING*>*  APPBASE::GetExecParams()
{
  return execparams;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPBASE_APPLICATIONMODE_TYPE APPBASE::GetApplicationMode()
* @brief      GetApplicationMode
* @ingroup    APPLICATION
*
* @return     APPBASE_APPLICATIONMODE_TYPE : 
*
* --------------------------------------------------------------------------------------------------------------------*/
APPBASE_APPLICATIONMODE_TYPE APPBASE::GetApplicationMode()
{
  return applicationmode;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPBASE::SetApplicationMode(APPBASE_APPLICATIONMODE_TYPE applicationmode)
* @brief      SetApplicationMode
* @ingroup    APPLICATION
*
* @param[in]  applicationmode : 
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void APPBASE::SetApplicationMode(APPBASE_APPLICATIONMODE_TYPE applicationmode)
{
  this->applicationmode = applicationmode;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void* APPBASE::GetApplicationHandle()
* @brief      GetApplicationHandle
* @ingroup    APPLICATION
*
* @return     void* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
void* APPBASE::GetApplicationHandle()
{
  return applicationhandle;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPBASE::SetApplicationHandle(void* handle)
* @brief      SetApplicationHandle
* @ingroup    APPLICATION
*
* @param[in]  handle : 
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void  APPBASE::SetApplicationHandle(void* handle)
{
  this->applicationhandle = handle;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPBASE::GetApplicationName()
* @brief      Get Application name
* @ingroup    APPLICATION
*
* @return     XSTRING* : String pointer with the name of the application
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPBASE::GetApplicationName()
{
  return &applicationname;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPBASE::SetApplicationName(XCHAR* name)
* @brief      Set name of the application
* @ingroup    APPLICATION
*
* @param[in]  name : name of the application
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void APPBASE::SetApplicationName(XCHAR* name)
{
  applicationname.Set(name);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPBASE::GetApplicationExecutable()
* @brief      GetApplicationExecutable
* @ingroup    APPLICATION
*
* @return     XSTRING* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPBASE::GetApplicationExecutable()
{
  return &applicationexecutable;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPBASE::SetApplicationExecutable(XCHAR* name)
* @brief      SetApplicationExecutable
* @ingroup    APPLICATION
*
* @param[in]  name : 
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void APPBASE::SetApplicationExecutable(XCHAR* name)
{
  applicationexecutable.Set(name);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPBASE::GetApplicationID()
* @brief      Get Application ID
* @ingroup    APPLICATION
*
* @return     XSTRING* : String with the ID of the aplication
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPBASE::GetApplicationID()
{
  return &applicationID;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTIMER* APPBASE::GetTimerGlobal()
* @brief      Get timer global for the application
* @ingroup    APPLICATION
*
* @return     XTIMER* : XTIMER class global
*
* --------------------------------------------------------------------------------------------------------------------*/
XTIMER* APPBASE::GetTimerGlobal()
{
  return xtimerglobal;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPBASEEXITTYPE APPBASE::GetExitType()
* @brief      Ge the exit type for the application
* @ingroup    APPLICATION
*
* @return     APPBASE_EXITTYPE : status of the exit
*
* --------------------------------------------------------------------------------------------------------------------*/
APPBASE_EXITTYPE APPBASE::GetExitType()
{
  return exittype;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPBASE::SetExittype(APPBASEEXITTYPE exitstatus)
* @brief      Set the exit type for the application
* @ingroup    APPLICATION
*
* @param[in]  exitstatus : status of the exit (APPBASEEXITTYPE enum)
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void APPBASE::SetExitType(APPBASE_EXITTYPE exittype)
{
  if(this->exittype != APPBASE_EXITTYPE_UNKNOWN) return;

  this->exittype = exittype;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPBASE::GetExitTypeString(XSTRING exittypestring)
* @brief      GetExitTypeString
* @ingroup    APPLICATION
*
* @param[in]  exittypestring :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPBASE::GetExitTypeString(XSTRING& exittypestring)
{
  exittypestring.Empty();

  switch(GetExitType())
    {
      case APPBASE_EXITTYPE_UNKNOWN             : exittypestring = XT_L(XTRANSLATION_GEN_ID_APPCONSOLE_EXIT_NOTINFO);             break;
      case APPBASE_EXITTYPE_BY_SERIOUSERROR     : exittypestring = XT_L(XTRANSLATION_GEN_ID_APPCONSOLE_EXIT_BY_SERIOUSERROR);     break;
      case APPBASE_EXITTYPE_BY_UPDATE           : exittypestring = XT_L(XTRANSLATION_GEN_ID_APPCONSOLE_EXIT_BY_UPDATE);           break;
      case APPBASE_EXITTYPE_BY_APPLICATION      : exittypestring = XT_L(XTRANSLATION_GEN_ID_APPCONSOLE_EXIT_BY_APPLICATION);      break;
      case APPBASE_EXITTYPE_BY_USER             : exittypestring = XT_L(XTRANSLATION_GEN_ID_APPCONSOLE_EXIT_BY_USER);             break;
      case APPBASE_EXITTYPE_BY_SHUTDOWN         : exittypestring = XT_L(XTRANSLATION_GEN_ID_APPCONSOLE_EXIT_BY_SHUTDOWN);         break;
      case APPBASE_EXITTYPE_BY_INVALIDLICENSE   : exittypestring = XT_L(XTRANSLATION_GEN_ID_APPCONSOLE_EXIT_BY_INVALIDLICENSE);   break;
      case APPBASE_EXITTYPE_BY_EXPIREDLICENSE   : exittypestring = XT_L(XTRANSLATION_GEN_ID_APPCONSOLE_EXIT_BY_EXPIREDLICENSE) ;  break;
                                      default   : return false;                                                                   
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSYSTEM_CHANGESTATUSTYPE APPBASE::GetSystemChangeStatus()
* @brief      GetSystemChangeStatus
* @ingroup    APPLICATION
*
* @return     XSYSTEM_CHANGESTATUSTYPE :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSYSTEM_CHANGESTATUSTYPE APPBASE::GetSystemChangeStatus()
{
  return systemchangestatustype;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPBASE::SetSystemChangeStatus(XSYSTEM_CHANGESTATUSTYPE type)
* @brief      SetSystemChangeStatus
* @ingroup    APPLICATION
*
* @param[in]  type :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void APPBASE::SetSystemChangeStatus(XSYSTEM_CHANGESTATUSTYPE systemchangestatustype)
{
  this->systemchangestatustype = systemchangestatustype;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPBASE::AppProc_PlatformIni()
* @brief      AppProc_PlatformIni
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPBASE::AppProc_PlatformIni()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPBASE::AppProc_Ini()
* @brief      Ini callback for this class to use for the application class real
* @note       VIRTUAL
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPBASE::AppProc_Ini()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPBASE::AppProc_FirstUpdate()
* @brief      First Update callback for this class to use for the application class real
* @note       VIRTUAL
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPBASE::AppProc_FirstUpdate()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPBASE::AppProc_Update()
* @brief      Update callback for this class to use for the application class real
* @note       VIRTUAL
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPBASE::AppProc_Update()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPBASE::AppProc_LastUpdate()
* @brief      Last Update callback for this class to use for the application class real
* @note       VIRTUAL
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPBASE::AppProc_LastUpdate()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPBASE::AppProc_EndBlockedResources()
* @brief      AppProc_EndBlockedResources
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPBASE::AppProc_EndBlockedResources()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPBASE::AppProc_End()
* @brief      End callback for this class to use for the application class real
* @note       VIRTUAL
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPBASE::AppProc_End()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPBASE::AppProc_PlatformEnd()
* @brief      AppProc_PlatformEnd
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPBASE::AppProc_PlatformEnd()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPBASE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    APPLICATION
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void APPBASE::Clean()
{  
  execparams              = NULL;

  applicationmode         = APPBASE_APPLICATIONMODE_TYPE_UNKNOWN;
  applicationhandle       = NULL;

  xtimerglobal            = NULL;

  firstupdate             = false;

  exittype                = APPBASE_EXITTYPE_UNKNOWN;
  systemchangestatustype  = XSYSTEM_CHANGESTATUSTYPE_UNKNOWN;
}
