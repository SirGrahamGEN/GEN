/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       APPLog.cpp
* 
* @class      APPLOG
* @brief      Application Log class
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

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "APPLog.h"

#include "XLog.h"
#include "XSystem.h"
#include "XTranslation.h"
#include "XTranslation_GEN.h"
#include "XTranslation.h"
#include "XLanguage_ISO_639_3.h"

#include "APPBase.h"
#include "APPCFG.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

APPLOG* APPLOG::instance = NULL;

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPLOG::GetIsInstanced()
* @brief      GetIsInstanced
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPLOG::GetIsInstanced()
{
  return instance != NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPLOG& APPLOG::GetInstance()
* @brief      GetInstance
* @ingroup    APPLICATION
*
* @return     APPLOG& : 
*
* --------------------------------------------------------------------------------------------------------------------*/
APPLOG& APPLOG::GetInstance()
{
  if(!instance) instance = new APPLOG();

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPLOG::DelInstance()
* @brief      DelInstance
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPLOG::DelInstance()
{
  if(instance)
    {
      instance->End();

      delete instance;
      instance = NULL;

      return true;
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPLOG::Ini(APPCFG* cfg, XCHAR* applicationname, int appversion, int appsubversion, int appversionerror)
* @brief      Ini
* @ingroup    APPLICATION
*
* @param[in]  cfg :
* @param[in]  applicationname :
* @param[in]  appversion :
* @param[in]  appsubversion :
* @param[in]  appsubversionerror :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPLOG::Ini(APPCFG* cfg, XCHAR* applicationname, int appversion, int appsubversion, int appsubversionerror)
{
  if(!cfg) return false;

  XPATH xpathsection;
  XPATH xpath;
  bool  status;

  this->cfg = cfg;

  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathsection);
  xpath.Create(3 , xpathsection.Get(), applicationname, __L(".log"));

  status = GEN_XLOG.Ini(xpath, applicationname, true);
  if(status)
    {     
      GEN_XLOG.SetLimit(XLOGTYPELIMIT_SIZE, cfg->Log_MaxSize()*1000, cfg->Log_ReductionPercent());
      GEN_XLOG.SetFilters(cfg->Log_ActiveSectionsID()->Get(), cfg->Log_LevelMask());
      GEN_XLOG.SetBackup(cfg->Log_Backup_IsActive(), cfg->Log_Backup_GetMaxFiles(),  cfg->Log_Backup_IsCompress());
      
      /*
      APP_LOG_ENTRY(XLOGLEVEL_INFO, APP_CFG_LOG_SECTIONID_INITIATION, false, APP_LOG_SEPARATOR);

      XSTRING appstatusstring;
      #ifdef _DEBUG
      appstatusstring = __L("Debug");
      #endif
                                                                                                                        
      if(appversion < 1)
        {
          if(appstatusstring.GetSize() > 1) appstatusstring.AddFormat(__L(" + "));
          appstatusstring.AddFormat(__L("Beta"));
        }
      

      APP_LOG_ENTRY(XLOGLEVEL_INFO, APP_CFG_LOG_SECTIONID_INITIATION, false, XT_L(XTRANSLATION_GEN_ID_APPLOG_INITMSG) , appversion, appsubversion, appsubversionerror
                                                                                                                      , appstatusstring.Get());
      XDWORD total = 0;
      XDWORD free  = 0;

      GEN_XSYSTEM.GetMemoryInfo(total,free);

      APP_LOG_ENTRY(XLOGLEVEL_INFO, APP_CFG_LOG_SECTIONID_INITIATION, false, XT_L(XTRANSLATION_GEN_ID_APPLOG_TOTALMEMORY), total, free, GEN_XSYSTEM.GetFreeMemoryPercent());
      */   
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPLOG::End()
* @brief      End
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPLOG::End()
{
  GEN_XLOG.End();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPLOG::APPLOG()
* @brief      Constructor
* @ingroup    APPLICATION
*
* @return     Does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
APPLOG::APPLOG()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPLOG::~APPLOG()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    APPLICATION
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
APPLOG::~APPLOG()
{
  End();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPLOG::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    APPLICATION
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void APPLOG::Clean()
{
  cfg = NULL;
}


#pragma endregion
