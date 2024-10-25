/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       APPExtended.cpp
* 
* @class      APPEXTENDED
* @brief      Application Extended class
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "APPExtended.h"

#include "XFactory.h"
#include "XLog.h"
#include "XSystem.h"
#include "XConsole.h"
#include "XSleep.h"
#include "XThread.h"
#include "XTranslation.h"
#include "XTranslation_GEN.h"
#include "XTranslation.h"
#include "XLanguage_ISO_639_3.h"

#include "VersionFrameWork.h"

#include "APPBase.h"
#include "APPCFG.h"
#include "APPLOG.h"
#include "APPConsole.h"
#ifdef APP_EXTENDED_APPLICATIONSTATUS_ACTIVE
#include "APPExtended_ApplicationStatus.h"
#endif
#ifdef APP_EXTENDED_INTERNETSTATUS_ACTIVE
#include "APPExtended_InternetStatus.h"
#endif

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

APPEXTENDED* APPEXTENDED::instance = NULL;

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPEXTENDED::GetIsInstanced()
* @brief      GetIsInstanced
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPEXTENDED::GetIsInstanced()
{
  return instance != NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPEXTENDED& APPEXTENDED::GetInstance()
* @brief      GetInstance
* @ingroup    APPLICATION
*
* @return     APPEXTENDED& : 
*
* --------------------------------------------------------------------------------------------------------------------*/
APPEXTENDED& APPEXTENDED::GetInstance()
{
  if(!instance) instance = new APPEXTENDED();

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPEXTENDED::DelInstance()
* @brief      DelInstance
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPEXTENDED::DelInstance()
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
* @fn         bool APPEXTENDED::APPStart(APPCFG* appcfg, APPCONSOLE* appconsole)
* @brief      APPStart
* @ingroup    APPLICATION
* 
* @param[in]  appcfg : 
* @param[in]  appconsole : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPEXTENDED::APPStart(APPCFG* appcfg, APPCONSOLE* appconsole)
{  
  XSTRING   string;
  XSTRING   stringresult;
  bool      status;

  if(!appcfg)
    { 
      return false;
    }

  if(!appcfg->Log_IsActive())
    {
      return false;
    }  

 //---------------------------------------------------------------------------------------------------------------------------------

  updatemutex = GEN_XFACTORY.Create_Mutex();  
  if(!updatemutex)
    {
      return false;
    }
      
  updatethread = GEN_XFACTORY.CreateThread(XTHREADGROUPID_APPEXTENDED, __L("APPEXTENDED::APPEXTENDED"), ThreadFunction_Update, this);
  if(!updatethread) 
    {
      return false;
    }

  updatethread->Ini();   

  //---------------------------------------------------------------------------------------------------------------------------------

  this->appcfg      = appcfg;
  this->appconsole  = appconsole;

  XSTRING SO_ID;
  status = GEN_XSYSTEM.GetOperativeSystemID(SO_ID);

  XTRACE_PRINT(__L(" "));

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("%s"),  GEN_VERSION.GetAppVersion()->Get()); 
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("%s: %s"), XT_L(XTRANSLATION_GEN_ID_APPEXTENDED_APPROOTPATH),  GEN_XPATHSMANAGER.GetPathSection(XPATHSMANAGERSECTIONTYPE_ROOT)->xpath->Get()); 

  XTRACE_PRINT(__L(" "));
  
  XTRACE_PRINTMSGSTATUS(XT_L(XTRANSLATION_GEN_ID_APPEXTENDED_APPVERSION),  GEN_VERSION.GetAppVersion()->Get()); 
  XTRACE_PRINTMSGSTATUS(XT_L(XTRANSLATION_GEN_ID_APPEXTENDED_SOVERSION),  SO_ID.Get()); 

  status = APP_LOG.Ini(appcfg, GEN_VERSION.GetAppExecName()->Get()); 

  string.Format(APPCONSOLE_DEFAULTMESSAGEMASK, XT_L(XTRANSLATION_GEN_ID_APPEXTENDED_INILOG));  
  stringresult.Format(__L("%s."), (status)?XT_L(XTRANSLATION_GEN_ID_OK):XT_L(XTRANSLATION_GEN_ID_ERROR));

  if(status)
    { 
      XDWORD total = 0;
      XDWORD free  = 0;

      GEN_XSYSTEM.GetMemoryInfo(total,free);

      APP_LOG_ENTRY(XLOGLEVEL_INFO, APP_CFG_LOG_SECTIONID_INITIATION, false, __L("-------------------------------------------------------------------------------------------------------------"));    
      APP_LOG_ENTRY(XLOGLEVEL_INFO, APP_CFG_LOG_SECTIONID_INITIATION, false,  __L("%s: %s"), XT_L(XTRANSLATION_GEN_ID_APPEXTENDED_SOVERSION), SO_ID.Get());
      APP_LOG_ENTRY(XLOGLEVEL_INFO, APP_CFG_LOG_SECTIONID_INITIATION, false, XT_L(XTRANSLATION_GEN_ID_APPEXTENDED_TOTALMEMORY), total, free, GEN_XSYSTEM.GetFreeMemoryPercent());

      APP_LOG_ENTRY(((status)?XLOGLEVEL_INFO:XLOGLEVEL_ERROR), APP_CFG_LOG_SECTIONID_INITIATION, false, __L("%s: %s") , string.Get(), stringresult.Get());       
    }
  
  #ifdef APP_CONSOLE_ACTIVE
  if(appconsole)
    {     
      appconsole->GetConsole()->Clear();

      #ifdef APP_EXTENDED_APPLICATIONHEADER_ACTIVE
      appconsole->Show_Header(true);
      #endif

      appconsole->GetConsole()->PrintMessage(string.Get(), 1, true, false);
      appconsole->GetConsole()->PrintMessage(stringresult.Get(), 0, false, true);      
    }
  #endif 


  #ifdef APP_EXTENDED_APPLICATIONSTATUS_ACTIVE
  applicationstatus = new APPEXTENDED_APPLICATIONSTATUS(appcfg);
  if(!applicationstatus)
    {
      return false;
    }
   else 
    {
      status = true;
    }

  string.Format(APPCONSOLE_DEFAULTMESSAGEMASK, XT_L(XTRANSLATION_GEN_ID_APPEXTENDED_INIAPPSTATUS));  
  stringresult.Format(__L("%s."), (status)?XT_L(XTRANSLATION_GEN_ID_OK):XT_L(XTRANSLATION_GEN_ID_ERROR));

  APP_LOG_ENTRY(((status)?XLOGLEVEL_INFO:XLOGLEVEL_ERROR), APP_CFG_LOG_SECTIONID_INITIATION, false, __L("%s: %s") , string.Get(), stringresult.Get());       

    #ifdef APP_CONSOLE_ACTIVE
    if(appconsole)
      {          
        appconsole->GetConsole()->PrintMessage(string.Get(), 1, true, false);
        appconsole->GetConsole()->PrintMessage(stringresult.Get(), 0, false, true);      
      }
    #endif  

  #endif


  #ifdef APP_EXTENDED_INTERNETSTATUS_ACTIVE
  internetstatus = new APPEXTENDED_INTERNETSTATUS(appcfg);
  if(!internetstatus)
    {
      return false;
    }
   else 
    {
      status = true;
    }

  string.Format(APPCONSOLE_DEFAULTMESSAGEMASK, XT_L(XTRANSLATION_GEN_ID_APPEXTENDED_INIINTERNETSTATUS));  
  stringresult.Format(__L("%s."), (status)?XT_L(XTRANSLATION_GEN_ID_OK):XT_L(XTRANSLATION_GEN_ID_ERROR));

  APP_LOG_ENTRY(((status)?XLOGLEVEL_INFO:XLOGLEVEL_ERROR), APP_CFG_LOG_SECTIONID_INITIATION, false, __L("%s: %s") , string.Get(), stringresult.Get());       

    #ifdef APP_CONSOLE_ACTIVE
    if(appconsole)
      {          
        appconsole->GetConsole()->PrintMessage(string.Get(), 1, true, false);
        appconsole->GetConsole()->PrintMessage(stringresult.Get(), 0, false, true);      
      }
    #endif  

  #endif

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPEXTENDED::APPEnd()
* @brief      APPEnd
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPEXTENDED::APPEnd()
{
  XSTRING   string;
  XSTRING   stringresult;
  
  if(!appcfg)
    { 
      return false;
    }

  if(!appcfg->Log_IsActive())
    {
      return false;
    } 
 

  #ifdef APP_EXTENDED_INTERNETSTATUS_ACTIVE
  if(internetstatus)
    {
      delete internetstatus;
      internetstatus = NULL;  
    
      string.Format(APPCONSOLE_DEFAULTMESSAGEMASK, XT_L(XTRANSLATION_GEN_ID_APPEXTENDED_ENDINTERNETSTATUS));
      stringresult.Format(__L("%s."), XT_L(XTRANSLATION_GEN_ID_OK));    

      APP_LOG_ENTRY(XLOGLEVEL_INFO, APP_CFG_LOG_SECTIONID_ENDING, false, __L("%s: %s") , string.Get(), stringresult.Get()); 

      #ifdef APP_CONSOLE_ACTIVE
      if(appconsole)
        {        
          appconsole->GetConsole()->PrintMessage(string.Get()       , 1, true, false);
          appconsole->GetConsole()->PrintMessage(stringresult.Get() , 0, false, true);     
        }
      #endif
    }
  #endif 


  #ifdef APP_EXTENDED_APPLICATIONSTATUS_ACTIVE
  if(applicationstatus)
    {
      delete applicationstatus;
      applicationstatus = NULL;  

      string.Format(APPCONSOLE_DEFAULTMESSAGEMASK, XT_L(XTRANSLATION_GEN_ID_APPEXTENDED_ENDAPPSTATUS));
      stringresult.Format(__L("%s."), XT_L(XTRANSLATION_GEN_ID_OK));    

      APP_LOG_ENTRY(XLOGLEVEL_INFO, APP_CFG_LOG_SECTIONID_ENDING, false, __L("%s: %s") , string.Get(), stringresult.Get()); 

      #ifdef APP_CONSOLE_ACTIVE
      if(appconsole)
        {        
          appconsole->GetConsole()->PrintMessage(string.Get()       , 1, true, false);
          appconsole->GetConsole()->PrintMessage(stringresult.Get() , 0, false, true);     
        }
      #endif
    }
  #endif

     
  string.Format(APPCONSOLE_DEFAULTMESSAGEMASK,  XT_L(XTRANSLATION_GEN_ID_APPEXTENDED_ENDLOG));
  stringresult.Format(__L("%s."), XT_L(XTRANSLATION_GEN_ID_OK));
  
  APP_LOG_ENTRY(XLOGLEVEL_INFO, APP_CFG_LOG_SECTIONID_ENDING, false, __L("%s: %s") , string.Get(), stringresult.Get());       
  APP_LOG_ENTRY(XLOGLEVEL_INFO, APP_CFG_LOG_SECTIONID_ENDING, false, __L("-------------------------------------------------------------------------------------------------------------"));

  APP_LOG.DelInstance();

  #ifdef APP_CONSOLE_ACTIVE
  if(appconsole)
    {     
      appconsole->GetConsole()->PrintMessage(string.Get()       , 1, true, false);
      appconsole->GetConsole()->PrintMessage(stringresult.Get() , 0, false, true);     
    }
  #endif

  if(updatethread)
    {
      updatethread->End();

      GEN_XFACTORY.DeleteThread(XTHREADGROUPID_APPEXTENDED, updatethread);

      updatethread = NULL;
    }

  if(updatemutex)
    {
      GEN_XFACTORY.Delete_Mutex(updatemutex);
      updatemutex = NULL;
    }
 
  appcfg      = NULL;
  appconsole  = NULL;
      
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         APPCFG* APPEXTENDED::GetAppCFG()
* @brief      GetAppCFG
* @ingroup    APPLICATION
* 
* @return     APPCFG* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
APPCFG* APPEXTENDED::GetAppCFG()
{
  return appcfg;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         APPCONSOLE* APPEXTENDED::GetAppConsole()
* @brief      GetAppConsole
* @ingroup    APPLICATION
* 
* @return     APPCONSOLE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
APPCONSOLE* APPEXTENDED::GetAppConsole()
{
  return appconsole;
}


#ifdef APP_EXTENDED_APPLICATIONSTATUS_ACTIVE
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         APPEXTENDED_APPLICATIONSTATUS* APPEXTENDED::GetApplicationStatus()
* @brief      GetApplicationStatus
* @ingroup    APPLICATION
* 
* @return     APPEXTENDED_APPLICATIONSTATUS* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
APPEXTENDED_APPLICATIONSTATUS* APPEXTENDED::GetApplicationStatus()
{
  return applicationstatus;
}
#endif


#ifdef APP_EXTENDED_INTERNETSTATUS_ACTIVE
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         APPEXTENDED_INTERNETSTATUS* APPEXTENDED::GetInternetStatus()
* @brief      GetInternetStatus
* @ingroup    APPLICATION
* 
* @return     APPEXTENDED_INTERNETSTATUS* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
APPEXTENDED_INTERNETSTATUS* APPEXTENDED::GetInternetStatus()
{
  return internetstatus;
}    
#endif


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPEXTENDED::ShowAll()
* @brief      ShowAll
* @ingroup    APPLICATION
* 
* @param[in]  console : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPEXTENDED::ShowAll()
{
  #ifdef APP_CONSOLE_ACTIVE

  if(!appconsole)
    { 
      return false;
    }

  if(updatemutex) 
    {
      updatemutex->Lock();
    }

  XCONSOLE* console = appconsole->GetConsole();
  if(!console)
    {
      return false;
    }

  console->Clear();

  #ifdef APP_EXTENDED_APPLICATIONHEADER_ACTIVE
  if(appconsole->Show_Header(false))      
    {
      console->PrintMessage(__L(""),0, false, true);
    }
  #endif

  #ifdef APP_EXTENDED_APPLICATIONSTATUS_ACTIVE
  if(APP_EXTENDED.GetApplicationStatus()->Show(console))
    {
      console->PrintMessage(__L(""),0, false, true);
    }
  #endif

  #ifdef APP_EXTENDED_INTERNETSTATUS_ACTIVE
  if(APP_EXTENDED.GetInternetStatus()->Show(console))
    {
      console->PrintMessage(__L(""),0, false, true);
    }
  #endif
 
  if(updatemutex) 
    {
      updatemutex->UnLock();
    }

  #endif

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPEXTENDED::APPEXTENDED()
* @brief      Constructor
* @ingroup    APPLICATION
*
* --------------------------------------------------------------------------------------------------------------------*/
APPEXTENDED::APPEXTENDED()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPEXTENDED::~APPEXTENDED()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    APPLICATION
*
* --------------------------------------------------------------------------------------------------------------------*/
APPEXTENDED::~APPEXTENDED()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPEXTENDED::ThreadFunction_Update(void* param)
* @brief      ThreadFunction_Update
* @ingroup    APPLICATION
* 
* @param[in]  param : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APPEXTENDED::ThreadFunction_Update(void* param)
{
  APPEXTENDED* appextended = (APPEXTENDED*)param;
  if(!appextended)
    {
      return;
    }

  if(appextended->exitincurse)
    {
      return;
    }

  if(appextended->updatemutex) 
    {
      appextended->updatemutex->Lock();
    }

  #ifdef APP_EXTENDED_APPLICATIONSTATUS_ACTIVE
  if(appextended->GetApplicationStatus())
    {
      appextended->GetApplicationStatus()->Update();
    }  
  #endif

  #ifdef APP_EXTENDED_INTERNETSTATUS_ACTIVE
  if(appextended->GetInternetStatus())
    {
      appextended->GetInternetStatus()->Update();
    }  
  #endif  

  for(int c=0; c<100; c++) 
    {
      if(appextended->exitincurse)
        {
          return;
        }

      GEN_XSLEEP.MilliSeconds(10);
    }

  if(appextended->updatemutex) 
    {
      appextended->updatemutex->UnLock();
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPEXTENDED::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    APPLICATION
*
* --------------------------------------------------------------------------------------------------------------------*/
void APPEXTENDED::Clean()
{
  appcfg            = NULL;
  appconsole        = NULL;

  updatemutex       = NULL;
  updatethread      = NULL;  
  exitincurse       = false;
  
  #ifdef APP_EXTENDED_APPLICATIONSTATUS_ACTIVE
  applicationstatus = NULL;
  #endif

  #ifdef APP_EXTENDED_INTERNETSTATUS_ACTIVE
  internetstatus    = NULL;
  #endif
}


#pragma endregion
