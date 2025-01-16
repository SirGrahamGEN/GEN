/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       APPFlowExtended_ApplicationStatus.cpp
* 
* @class      APPFLOWEXTENDED_APPLICATIONSTATUS
* @brief      Application Flow Extended Application Status class
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

#include "APPFlowExtended_ApplicationStatus.h"

#include "VersionFrameWork.h"

#include "XFactory.h"
#include "XSystem.h"
#include "XDateTime.h"
#include "XSleep.h"
#include "XThread.h"

#include "APPFlowCheckResourcesHardware.h"
#include "APPFlowCFG.h"
#include "APPFlowConsole.h"
#include "APPFlowExtended.h"

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
* @fn         APPFLOWEXTENDED_APPLICATIONSTATUS::APPFLOWEXTENDED_APPLICATIONSTATUS(APPFLOWCFG* cfg) : DIOWEBSERVER_RESOLVEENDPOINT()
* @brief      Constructor
* @ingroup    APPFLOW
* 
* @param[in]  cfg : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
APPFLOWEXTENDED_APPLICATIONSTATUS::APPFLOWEXTENDED_APPLICATIONSTATUS(APPFLOWCFG* cfg) : DIOWEBSERVER_RESOLVEENDPOINT()
{
  Clean();

  this->cfg = cfg;

  GEN_XSYSTEM.GetOperativeSystemID(osversion);

  XDWORD app_version      = 0;
  XDWORD app_subversion   = 0;
  XDWORD app_versionerror = 0;

  GEN_VERSION.GetAppVersions(app_version, app_subversion, app_versionerror);
  GEN_VERSION.GetAppVersion(app_version, app_subversion, app_versionerror, appversion);

  xtimeroperatingtime = GEN_XFACTORY.CreateTimer();
  checkresourceshardware = new APPFLOWCHECKRESOURCESHARDWARE();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         APPFLOWEXTENDED_APPLICATIONSTATUS::~APPFLOWEXTENDED_APPLICATIONSTATUS()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    APPFLOW
* 
* --------------------------------------------------------------------------------------------------------------------*/
APPFLOWEXTENDED_APPLICATIONSTATUS::~APPFLOWEXTENDED_APPLICATIONSTATUS()
{  
  if(xtimeroperatingtime)
    {
      GEN_XFACTORY.DeleteTimer(xtimeroperatingtime);
    }

  if(checkresourceshardware)
    {
      checkresourceshardware->End();

      delete checkresourceshardware;
    }

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         APPCHECKRESOURCESHARDWARE* APPFLOWEXTENDED_APPLICATIONSTATUS::GetCheckResourcesHardware()
* @brief      GetAPPCheckResourcesHardware
* @ingroup    APPFLOW
* 
* @return     APPCHECKRESOURCESHARDWARE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
APPFLOWCHECKRESOURCESHARDWARE* APPFLOWEXTENDED_APPLICATIONSTATUS::GetCheckResourcesHardware()
{
  return checkresourceshardware; 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* APPFLOWEXTENDED_APPLICATIONSTATUS::GetOSVersion()
* @brief      GetOSVersion
* @ingroup    APPFLOW
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPFLOWEXTENDED_APPLICATIONSTATUS::GetOSVersion()
{
  return &osversion;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* APPFLOWEXTENDED_APPLICATIONSTATUS::GetAppVersion()
* @brief      GetAppVersion
* @ingroup    APPFLOW
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPFLOWEXTENDED_APPLICATIONSTATUS::GetAppVersion()
{
  return &appversion;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD APPFLOWEXTENDED_APPLICATIONSTATUS::GetMemoryTotal()
* @brief      GetMemoryTotal
* @ingroup    APPFLOW
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD APPFLOWEXTENDED_APPLICATIONSTATUS::GetMemoryTotal()
{
  return memory_total;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPFLOWEXTENDED_APPLICATIONSTATUS::SetMemoryTotal(XDWORD memory_total)
* @brief      SetMemoryTotal
* @ingroup    APPFLOW
* 
* @param[in]  memory_total : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APPFLOWEXTENDED_APPLICATIONSTATUS::SetMemoryTotal(XDWORD memory_total)
{
  this->memory_total = memory_total;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD APPFLOWEXTENDED_APPLICATIONSTATUS::GetMemoryFree()
* @brief      GetMemoryFree
* @ingroup    APPFLOW
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD APPFLOWEXTENDED_APPLICATIONSTATUS::GetMemoryFree()
{
  return memory_free;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPFLOWEXTENDED_APPLICATIONSTATUS::SetMemoryFree(XDWORD memory_free)
* @brief      SetMemoryFree
* @ingroup    APPFLOW
* 
* @param[in]  memory_free : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APPFLOWEXTENDED_APPLICATIONSTATUS::SetMemoryFree(XDWORD memory_free)
{
  this->memory_free = memory_free;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD APPFLOWEXTENDED_APPLICATIONSTATUS::GetMemoryFreePercent()
* @brief      GetMemoryFreePercent
* @ingroup    APPFLOW
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD APPFLOWEXTENDED_APPLICATIONSTATUS::GetMemoryFreePercent()
{
  return memory_freepercent;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPFLOWEXTENDED_APPLICATIONSTATUS::SetMemoryFreePercent(XDWORD memory_freepercent)
* @brief      SetMemoryFreePercent
* @ingroup    APPFLOW
* 
* @param[in]  memory_freepercent : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APPFLOWEXTENDED_APPLICATIONSTATUS::SetMemoryFreePercent(XDWORD memory_freepercent)
{
  this->memory_freepercent = memory_freepercent;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* APPFLOWEXTENDED_APPLICATIONSTATUS::GetAverange()
* @brief      GetAverange
* @ingroup    APPFLOW
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPFLOWEXTENDED_APPLICATIONSTATUS::GetAverange()
{
  return &averange;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* APPFLOWEXTENDED_APPLICATIONSTATUS::GetCurrentDate()
* @brief      GetCurrentDate
* @ingroup    APPFLOW
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPFLOWEXTENDED_APPLICATIONSTATUS::GetCurrentDate()
{
  return &currentdate;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* APPFLOWEXTENDED_APPLICATIONSTATUS::GetOperatingTime()
* @brief      GetOperatingTime
* @ingroup    APPFLOW
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPFLOWEXTENDED_APPLICATIONSTATUS::GetOperatingTime()
{
  return &operatingtime;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPFLOWEXTENDED_APPLICATIONSTATUS::Update()
* @brief      Update
* @ingroup    APPFLOW
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWEXTENDED_APPLICATIONSTATUS::Update()
{  
  
  if(checkresourceshardware && cfg)
    { 
      static bool iniappcheck = false;           

      if(!iniappcheck)
        {
          checkresourceshardware->Ini(cfg);
          iniappcheck = true;
        }

      bool ischecktotalCPUusage = cfg->CheckResourcesHardware_GetTotalCPUUsageCheckCadence()?true:false;
      bool ischeckappCPUusage   = cfg->CheckResourcesHardware_GetAppCPUUsageCheckCadence()?true:false;

      if(ischecktotalCPUusage || ischeckappCPUusage)
        {  
          averange.Empty();
  
          if(ischecktotalCPUusage)
            {
              averange.AddFormat(__L("avg. %d%% (max. %d%%)") , checkresourceshardware->GetCPUTotalCPUUsageAverange()
                                                              , checkresourceshardware->GetCPUTotalCPUUsageMax());  
            }

          if(ischeckappCPUusage)
            {
              if(ischecktotalCPUusage)
                {
                  averange.AddFormat(__L(", "));
                }

              if(ischeckappCPUusage)
                {         
                  averange.AddFormat(__L("app %s avg. %d%% (max. %d%%)") , cfg->CheckResourcesHardware_GetAppCPUUsageProcessName()->Get()
                                                                         , checkresourceshardware->GetCPUAppCPUUsageAverange()
                                                                         , checkresourceshardware->GetCPUAppCPUUsageMax());
                }
            } 
        }         
    }

  GEN_XSYSTEM.GetMemoryInfo(memory_total, memory_free);
  memory_freepercent = GEN_XSYSTEM.GetFreeMemoryPercent();

  XDATETIME* datetime = GEN_XFACTORY.CreateDateTime();
  if(datetime)
    { 
      datetime->Read();
      datetime->GetDateTimeToString(XDATETIME_FORMAT_STANDARD | XDATETIME_FORMAT_TEXTMONTH | XDATETIME_FORMAT_ADDDAYOFWEEK, currentdate);

      GEN_XFACTORY.DeleteDateTime(datetime);
    }
  
  if(xtimeroperatingtime)
    {
      xtimeroperatingtime->GetMeasureString(operatingtime, true);
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPFLOWEXTENDED_APPLICATIONSTATUS::Show(XCONSOLE* console)
* @brief      Show
* @ingroup    APPFLOW
* 
* @param[in]  console : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWEXTENDED_APPLICATIONSTATUS::Show(XCONSOLE* console)
{
  XSTRING string;
  XSTRING string2;

  if(!APPFLOW_EXTENDED.GetConsole())
    { 
      return false;
    }

  string  = __L("O.S Version");
  string2 = GetOSVersion()->Get();
  APPFLOW_EXTENDED.GetConsole()->Show_Line(string, string2);

  // string  = __L("Application Version");
  // string2 = GetAppVersion()->Get();
  // APPFLOW_EXTENDED.ShowLine(console, string, string2);
  
  string  = __L("CPU Memory");
  string2.Format(__L("%d Kb, free %d Kb (%d%%)"), GetMemoryTotal(), GetMemoryFree(), GetMemoryFreePercent());
  APPFLOW_EXTENDED.GetConsole()->Show_Line(string, string2);

  string  = __L("Averange");
  string2 = GetAverange()->Get();
  APPFLOW_EXTENDED.GetConsole()->Show_Line(string, string2);

  string  = __L("Current date");
  string2 = GetCurrentDate()->Get();
  APPFLOW_EXTENDED.GetConsole()->Show_Line(string, string2);

  string  = __L("Operating time");
  string2 = GetOperatingTime()->Get();
  APPFLOW_EXTENDED.GetConsole()->Show_Line(string, string2);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPFLOWEXTENDED_APPLICATIONSTATUS::Serialize()
* @brief      Serialize
* @ingroup    APPFLOW
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWEXTENDED_APPLICATIONSTATUS::Serialize()
{
  Primitive_Add<XSTRING*>(&osversion      , __L("osversion"));
  Primitive_Add<XSTRING*>(&appversion     , __L("appversion"));

  Primitive_Add<int>(memory_total         , __L("memorytotal"));
  Primitive_Add<int>(memory_free          , __L("memoryfree"));
  Primitive_Add<int>(memory_freepercent   , __L("memoryfreepercent"));

  Primitive_Add<XSTRING*>(&averange       , __L("averange"));

  Primitive_Add<XSTRING*>(&currentdate    , __L("currentdate"));
  Primitive_Add<XSTRING*>(&operatingtime  , __L("operatingtime"));

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPFLOWEXTENDED_APPLICATIONSTATUS::Deserialize()
* @brief      Deserialize
* @ingroup    APPFLOW
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWEXTENDED_APPLICATIONSTATUS::Deserialize()
{ 
  Primitive_Extract<XSTRING&>(osversion       , __L("osversion"));  
  Primitive_Extract<XSTRING&>(appversion      , __L("appversion"));

  Primitive_Extract<int>(memory_total         , __L("memorytotal"));
  Primitive_Extract<int>(memory_free          , __L("memoryfree"));
  Primitive_Extract<int>(memory_freepercent   , __L("memoryfreepercent"));  

  Primitive_Extract<XSTRING&>(averange        , __L("averange"));

  Primitive_Extract<XSTRING&>(currentdate     , __L("currentdate"));
  Primitive_Extract<XSTRING&>(operatingtime   , __L("operatingtime"));

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPFLOWEXTENDED_APPLICATIONSTATUS::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    APPFLOW
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APPFLOWEXTENDED_APPLICATIONSTATUS::Clean()
{
  cfg                         = NULL;
  xtimeroperatingtime         = NULL;
  checkresourceshardware      = NULL;
 
  osversion.Empty();
  appversion.Empty();

  memory_total                = 0;
  memory_free                 = 0;
  memory_freepercent          = 0;

  averange.Empty();

  currentdate.Empty();
  operatingtime.Empty();
}


#pragma endregion