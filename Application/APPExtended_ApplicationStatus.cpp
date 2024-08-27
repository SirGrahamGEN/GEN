/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       APPExtended_ApplicationStatus.cpp
* 
* @class      APPEXTENDED_APPLICATIONSTATUS
* @brief      Application Extended Application Status class
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

#include "APPExtended_ApplicationStatus.h"

#include "VersionFrameWork.h"

#include "XFactory.h"
#include "XSystem.h"
#include "XDateTime.h"
#include "XSleep.h"
#include "XThread.h"

#include "APPCheckResourcesHardware.h"
#include "APPCFG.h"
#include "APPExtended.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         APPEXTENDED_APPLICATIONSTATUS::APPEXTENDED_APPLICATIONSTATUS(APPCFG* cfg)
* @brief      Constructor
* @ingroup    APPLICATION
* 
* @param[in]  APPCFG* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
APPEXTENDED_APPLICATIONSTATUS::APPEXTENDED_APPLICATIONSTATUS(APPCFG* cfg) : DIOWEBSERVER_RESOLVEENDPOINT()
{
  Clean();

  this->cfg = cfg;

  updatemutex = GEN_XFACTORY.Create_Mutex();
  xtimeroperatingtime = GEN_XFACTORY.CreateTimer();

  appcheckresourceshardware = new APPCHECKRESOURCESHARDWARE();

  updatethread = GEN_XFACTORY.CreateThread(XTHREADGROUPID_APPEXTENDEDAPPLICATIONSTATUS, __L("APPEXTENDED_APPLICATIONSTATUS::APPEXTENDED_APPLICATIONSTATUS"), ThreadFunction_Update, this);
  if(updatethread) 
    {
      updatethread->Ini();
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         APPEXTENDED_APPLICATIONSTATUS::~APPEXTENDED_APPLICATIONSTATUS()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
APPEXTENDED_APPLICATIONSTATUS::~APPEXTENDED_APPLICATIONSTATUS()
{
  if(updatethread)
    {
      updatethread->End();

      GEN_XFACTORY.DeleteThread(XTHREADGROUPID_APPEXTENDEDAPPLICATIONSTATUS, updatethread);

      updatethread = NULL;
    }

  if(updatemutex)
    {
      GEN_XFACTORY.Delete_Mutex(updatemutex);
    }

  if(xtimeroperatingtime)
    {
      GEN_XFACTORY.DeleteTimer(xtimeroperatingtime);
    }

  if(appcheckresourceshardware)
    {
      appcheckresourceshardware->End();

      delete appcheckresourceshardware;
    }

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* APPEXTENDED_APPLICATIONSTATUS::GetOSVersion()
* @brief      GetOSVersion
* @ingroup    APPLICATION
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPEXTENDED_APPLICATIONSTATUS::GetOSVersion()
{
  return &osversion;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* APPEXTENDED_APPLICATIONSTATUS::GetAppVersion()
* @brief      GetAppVersion
* @ingroup    APPLICATION
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPEXTENDED_APPLICATIONSTATUS::GetAppVersion()
{
  return &appversion;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD APPEXTENDED_APPLICATIONSTATUS::GetMemoryTotal()
* @brief      GetMemoryTotal
* @ingroup    
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD APPEXTENDED_APPLICATIONSTATUS::GetMemoryTotal()
{
  return memory_total;
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPEXTENDED_APPLICATIONSTATUS::SetMemoryTotal(XDWORD memory_total)
* @brief      SetMemoryTotal
* @ingroup    
* 
* @param[in]  memory_total : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APPEXTENDED_APPLICATIONSTATUS::SetMemoryTotal(XDWORD memory_total)
{
  this->memory_total = memory_total;
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD APPEXTENDED_APPLICATIONSTATUS::GetMemoryFree()
* @brief      GetMemoryFree
* @ingroup    
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD APPEXTENDED_APPLICATIONSTATUS::GetMemoryFree()
{
  return memory_free;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPEXTENDED_APPLICATIONSTATUS::SetMemoryFree(XDWORD memory_free)
* @brief      SetMemoryFree
* @ingroup    
* 
* @param[in]  memory_free : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APPEXTENDED_APPLICATIONSTATUS::SetMemoryFree(XDWORD memory_free)
{
  this->memory_free = memory_free;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD APPEXTENDED_APPLICATIONSTATUS::GetMemoryFreePercent()
* @brief      GetMemoryFreePercent
* @ingroup    
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD APPEXTENDED_APPLICATIONSTATUS::GetMemoryFreePercent()
{
  return memory_freepercent;
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPEXTENDED_APPLICATIONSTATUS::SetMemoryFreePercent(XDWORD memory_freepercent)
* @brief      SetMemoryFreePercent
* @ingroup    
* 
* @param[in]  memory_freepercent : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APPEXTENDED_APPLICATIONSTATUS::SetMemoryFreePercent(XDWORD memory_freepercent)
{
  this->memory_freepercent = memory_freepercent;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* APPEXTENDED_APPLICATIONSTATUS::GetAverange()
* @brief      GetAverange
* @ingroup    APPLICATION
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPEXTENDED_APPLICATIONSTATUS::GetAverange()
{
  return &averange;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* APPEXTENDED_APPLICATIONSTATUS::GetCurrentDate()
* @brief      GetCurrentDate
* @ingroup    
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPEXTENDED_APPLICATIONSTATUS::GetCurrentDate()
{
  return &currentdate;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* APPEXTENDED_APPLICATIONSTATUS::GetOperatingTime()
* @brief      GetOperatingTime
* @ingroup    
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPEXTENDED_APPLICATIONSTATUS::GetOperatingTime()
{
  return &operatingtime;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XMUTEX* APPEXTENDED_APPLICATIONSTATUS::GetUpdateMutex()
* @brief      GetUpdateMutex
* @ingroup    
* 
* @return     XMUTEX* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XMUTEX* APPEXTENDED_APPLICATIONSTATUS::GetUpdateMutex()
{
  return updatemutex;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPEXTENDED_APPLICATIONSTATUS::Update()
* @brief      Update
* @ingroup    
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPEXTENDED_APPLICATIONSTATUS::Update()
{  
  if(updatemutex) 
    {
      updatemutex->Lock();
    }

  GEN_XSYSTEM.GetOperativeSystemID(osversion);

  XDWORD app_version      = 0;
  XDWORD app_subversion   = 0;
  XDWORD app_versionerror = 0;

  GEN_VERSION.GetAppVersions(app_version, app_subversion, app_versionerror);
  GEN_VERSION.GetAppVersion(app_version, app_subversion, app_versionerror, appversion);

 if(appcheckresourceshardware && cfg)
    { 
      static bool iniappcheck = false;           

      if(!iniappcheck)
        {
          appcheckresourceshardware->Ini(cfg);
          iniappcheck = true;
        }

      bool ischecktotalCPUusage = cfg->CheckResourcesHardware_GetTotalCPUUsageCheckCadence()?true:false;
      bool ischeckappCPUusage   = cfg->CheckResourcesHardware_GetAppCPUUsageCheckCadence()?true:false;

      if(ischecktotalCPUusage || ischeckappCPUusage)
        {  
          averange.Empty();
  
          if(ischecktotalCPUusage)
            {
              averange.AddFormat(__L("avg. %d%% (max. %d%%)") , appcheckresourceshardware->GetCPUTotalCPUUsageAverange()
                                                              , appcheckresourceshardware->GetCPUTotalCPUUsageMax());  
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
                                                                         , appcheckresourceshardware->GetCPUAppCPUUsageAverange()
                                                                         , appcheckresourceshardware->GetCPUAppCPUUsageMax());
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
  
  if(updatemutex) 
    {
      updatemutex->UnLock();
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPEXTENDED_APPLICATIONSTATUS::Show(XCONSOLE* console)
* @brief      Show
* @ingroup    APPLICATION
* 
* @param[in]  console : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPEXTENDED_APPLICATIONSTATUS::Show(XCONSOLE* console)
{
  XSTRING   string;
  XSTRING   string2;

  if(updatemutex) 
    {
      updatemutex->Lock();
    }

  string  = __L("O.S Version");
  string2 = GetOSVersion()->Get();
  APP_EXTENDED.ShowLine(console, string, string2);

  // string  = __L("Application Version");
  // string2 = GetAppVersion()->Get();
  // APP_EXTENDED.ShowLine(console, string, string2);
  
  string  = __L("CPU Memory");
  string2.Format(__L("%d Kb, free %d Kb (%d%%)"), GetMemoryTotal(), GetMemoryFree(), GetMemoryFreePercent());
  APP_EXTENDED.ShowLine(console, string, string2);

  string  = __L("Averange");
  string2 = GetAverange()->Get();
  APP_EXTENDED.ShowLine(console, string, string2);

  string  = __L("Current date");
  string2 = GetCurrentDate()->Get();
  APP_EXTENDED.ShowLine(console, string, string2);

  string  = __L("Operating time");
  string2 = GetOperatingTime()->Get();
  APP_EXTENDED.ShowLine(console, string, string2);

  if(updatemutex) 
    {
      updatemutex->UnLock();
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPEXTENDED_APPLICATIONSTATUS::Serialize()
* @brief      Serialize
* @ingroup    
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPEXTENDED_APPLICATIONSTATUS::Serialize()
{
  Primitive_Add<XSTRING*>(&osversion      , __L("osversion"));
  Primitive_Add<XSTRING*>(&appversion     , __L("appversion"));

  Primitive_Add<int>(memory_total         , __L("memory_total"));
  Primitive_Add<int>(memory_free          , __L("memory_free"));
  Primitive_Add<int>(memory_freepercent   , __L("memory_freepercent"));

  Primitive_Add<XSTRING*>(&averange       , __L("averange"));

  Primitive_Add<XSTRING*>(&currentdate    , __L("current_date"));
  Primitive_Add<XSTRING*>(&operatingtime  , __L("operating_time"));

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPEXTENDED_APPLICATIONSTATUS::Deserialize()
* @brief      Deserialize
* @ingroup    
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPEXTENDED_APPLICATIONSTATUS::Deserialize()
{ 
  Primitive_Extract<XSTRING&>(osversion       , __L("osversion"));  
  Primitive_Extract<XSTRING&>(appversion      , __L("appversion"));

  Primitive_Extract<int>(memory_total         , __L("memory_total"));
  Primitive_Extract<int>(memory_free          , __L("memory_free"));
  Primitive_Extract<int>(memory_freepercent   , __L("memory_freepercent"));  

  Primitive_Extract<XSTRING&>(averange        , __L("averange"));

  Primitive_Extract<XSTRING&>(currentdate     , __L("current_date"));
  Primitive_Extract<XSTRING&>(operatingtime   , __L("operating_time"));

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPEXTENDED_APPLICATIONSTATUS::ThreadFunction_Update(void* param)
* @brief      ThreadFunction_Update
* @ingroup    APPLICATION
* 
* @param[in]  param : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APPEXTENDED_APPLICATIONSTATUS::ThreadFunction_Update(void* param)
{
  APPEXTENDED_APPLICATIONSTATUS* appstatus = (APPEXTENDED_APPLICATIONSTATUS*)param;
  if(!appstatus)
    {
       return;
    }

  appstatus->Update();

  GEN_XSLEEP.Seconds(1);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPEXTENDED_APPLICATIONSTATUS::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APPEXTENDED_APPLICATIONSTATUS::Clean()
{
  cfg                         = NULL;

  updatemutex                 = NULL;
  xtimeroperatingtime         = NULL;
  appcheckresourceshardware   = NULL;;
  updatethread                = NULL;

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