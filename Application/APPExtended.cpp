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

#include "XLog.h"
#include "XSystem.h"
#include "XConsole.h"
#include "XTranslation.h"
#include "XTranslation_GEN.h"
#include "XTranslation.h"
#include "XLanguage_ISO_639_3.h"

#include "VersionFrameWork.h"

#include "APPBase.h"
#include "APPCFG.h"
#include "APPLOG.h"
#include "APPConsole.h"

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
* @fn         bool APPEXTENDED::APPStart(APPCFG* cfg, XCONSOLE* console)
* @brief      APPStart
* @ingroup    APPLICATION
* 
* @param[in]  cfg : 
* @param[in]  console : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPEXTENDED::APPStart(APPCFG* cfg, XCONSOLE* console)
{  
  XSTRING   string;
  XSTRING   stringresult;
  bool      status;

  if(!cfg)
    { 
      return false;
    }

  if(!cfg->Log_IsActive())
    {
      return false;
    }      

  XSTRING SO_ID;
  status = GEN_XSYSTEM.GetOperativeSystemID(SO_ID);

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("%s"),  GEN_VERSION.GetAppVersion()->Get()); 
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Application ROOT path: %s"),  GEN_XPATHSMANAGER.GetPathSection(XPATHSMANAGERSECTIONTYPE_ROOT)->xpath->Get()); 
  
  XTRACE_PRINTMSGSTATUS(__L("Version App")  ,  GEN_VERSION.GetAppVersion()->Get()); 
  XTRACE_PRINTMSGSTATUS(__L("S.O. version") , SO_ID.Get()); 

  status = APP_LOG.Ini(cfg, GEN_VERSION.GetAppName()->Get()); 

  string.Format(APPCONSOLE_DEFAULTMESSAGEMASK, __L("Activando sistema LOG"));  
  stringresult.Format((status)?__L("Ok."):__L("ERROR!"));

  if(status)
    { 
      XDWORD total = 0;
      XDWORD free  = 0;

      GEN_XSYSTEM.GetMemoryInfo(total,free);

      APP_LOG_ENTRY(((status)?XLOGLEVEL_INFO:XLOGLEVEL_ERROR), APP_CFG_LOG_SECTIONID_INITIATION, false, __L("-------------------------------------------------------------------------------------------------------------"));    
      APP_LOG_ENTRY(((status)?XLOGLEVEL_INFO:XLOGLEVEL_ERROR), APP_CFG_LOG_SECTIONID_INITIATION, false,  __L("S.O. version: %s"), SO_ID.Get());
      APP_LOG_ENTRY(XLOGLEVEL_INFO, APP_CFG_LOG_SECTIONID_INITIATION, false, XT_L(XTRANSLATION_GEN_ID_APPLOG_TOTALMEMORY), total, free, GEN_XSYSTEM.GetFreeMemoryPercent());

      APP_LOG_ENTRY(((status)?XLOGLEVEL_INFO:XLOGLEVEL_ERROR), APP_CFG_LOG_SECTIONID_INITIATION, false, __L("%s: %s") , string.Get(), stringresult.Get());       
    }
  
  #ifdef APP_CONSOLE_ACTIVE
  if(console)
    {     
      console->PrintMessage(string.Get(), 1, true, false);
      console->PrintMessage(stringresult.Get(), 0, false, true);      
    }
  #endif

  return status;
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
* @fn         void APPEXTENDED::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    APPLICATION
*
* --------------------------------------------------------------------------------------------------------------------*/
void APPEXTENDED::Clean()
{
 
}


#pragma endregion
