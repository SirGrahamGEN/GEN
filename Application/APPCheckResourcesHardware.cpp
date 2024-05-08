/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       APPCheckResourcesHardware.cpp
* 
* @class      APPCHECKRESOURCESHARDWARE
* @brief      Application Check Resources Hardware class
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

#include "APPCheckResourcesHardware.h"

#include "XLog.h"
#include "XScheduler.h"
#include "XScheduler_XEvent.h"
#include "XSystem.h"

#include "APPCFG.h"

#include "APPCheckResourcesHardware_XEvent.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPCHECKRESOURCESHARDWARE::APPCHECKRESOURCESHARDWARE()
* @brief      Constructor
* @ingroup    APPLICATION
*
* --------------------------------------------------------------------------------------------------------------------*/
APPCHECKRESOURCESHARDWARE::APPCHECKRESOURCESHARDWARE()
{
  Clean();

  RegisterEvent(APPCHECKRESOURCESHARDWARE_XEVENT_TYPE_MEMFREELIMIT);
  RegisterEvent(APPCHECKRESOURCESHARDWARE_XEVENT_TYPE_TOTALCPUUSAGELIMIT);
  RegisterEvent(APPCHECKRESOURCESHARDWARE_XEVENT_TYPE_APPCPUUSAGELIMIT);

  // GEN_XFACTORY_CREATE(exitmutex, Create_Mutex());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPCHECKRESOURCESHARDWARE::~APPCHECKRESOURCESHARDWARE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    APPLICATION
*
* --------------------------------------------------------------------------------------------------------------------*/
APPCHECKRESOURCESHARDWARE::~APPCHECKRESOURCESHARDWARE()
{
  End();

  DeRegisterEvent(APPCHECKRESOURCESHARDWARE_XEVENT_TYPE_MEMFREELIMIT);
  DeRegisterEvent(APPCHECKRESOURCESHARDWARE_XEVENT_TYPE_TOTALCPUUSAGELIMIT);
  DeRegisterEvent(APPCHECKRESOURCESHARDWARE_XEVENT_TYPE_APPCPUUSAGELIMIT);

  // GEN_XFACTORY.Delete_Mutex(exitmutex);

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPCHECKRESOURCESHARDWARE::Ini(APPCFG* cfg)
* @brief      Ini
* @ingroup    APPLICATION
*
* @param[in]  cfg :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPCHECKRESOURCESHARDWARE::Ini(APPCFG* cfg)
{
  if(!cfg) 
    {
      return false;
    }

  this->cfg = cfg;

  xscheduler = new XSCHEDULER();
  if(!xscheduler) return false;

  XSCHEDULERTASK* xtask;

  //---------------------------------------------------------

  if(cfg->CheckResourcesHardware_GetMemStatusCheckCadence())
    {
      xtask = new XSCHEDULERTASK(xscheduler);
      if(!xtask) return false;

      xtask->SetNCycles(XSCHEDULER_CYCLEFOREVER, cfg->CheckResourcesHardware_GetMemStatusCheckCadence());
      xtask->SetID(APPCHECKRESOURCESHARDWARE_TASKID_CHECKMEMORY);
      xtask->SetIsStartImmediatelyCycles(true);
      xtask->SetIsActive(true);

      xscheduler->Task_Add(xtask);
    }

  //---------------------------------------------------------
  /*
  for(int c=0; c<100; c++)
    {
      CheckTotalCPUUsageStatus();   
      CheckAppCPUUsageStatus();   
      GEN_XSLEEP.MilliSeconds(10);  
    }
  */
  if(cfg->CheckResourcesHardware_GetTotalCPUUsageCheckCadence())
    {
      xtask = new XSCHEDULERTASK(xscheduler);
      if(!xtask) return false;

      xtask->SetNCycles(XSCHEDULER_CYCLEFOREVER, cfg->CheckResourcesHardware_GetTotalCPUUsageCheckCadence());
      xtask->SetID(APPCHECKRESOURCESHARDWARE_TASKID_TOTALCPUUSAGE);
      xtask->SetIsStartImmediatelyCycles(true);
      xtask->SetIsActive(true);

      xscheduler->Task_Add(xtask);
    }

  if(cfg->CheckResourcesHardware_GetAppCPUUsageCheckCadence())
    {
      xtask = new XSCHEDULERTASK(xscheduler);
      if(!xtask) return false;

      xtask->SetNCycles(XSCHEDULER_CYCLEFOREVER, cfg->CheckResourcesHardware_GetAppCPUUsageCheckCadence());
      xtask->SetID(APPCHECKRESOURCESHARDWARE_TASKID_APPCPUUSAGE);
      xtask->SetIsStartImmediatelyCycles(true);
      xtask->SetIsActive(true);

      xscheduler->Task_Add(xtask);
    }

  //---------------------------------------------------------

  SubscribeEvent(XEVENT_TYPE_SCHEDULER, xscheduler);

  if(!xscheduler->Ini()) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int APPCHECKRESOURCESHARDWARE::GetCPUTotalCPUUsageAverange()
* @brief      GetCPUTotalCPUUsageAverange
* @ingroup    APPLICATION
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int APPCHECKRESOURCESHARDWARE::GetCPUTotalCPUUsageAverange()
{
  if(!ntotalCPUusage) return 0;

  return (ntotalCPUusage / ntotalCPUsamples);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int APPCHECKRESOURCESHARDWARE::GetCPUTotalCPUUsageMax()
* @brief      GetCPUTotalCPUUsageMax
* @ingroup    APPLICATION
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int APPCHECKRESOURCESHARDWARE::GetCPUTotalCPUUsageMax()
{
  return maxtotalCPUusage;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int APPCHECKRESOURCESHARDWARE::GetCPUAppCPUUsageAverange()
* @brief      GetCPUAppCPUUsageAverange
* @ingroup    APPLICATION
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int APPCHECKRESOURCESHARDWARE::GetCPUAppCPUUsageAverange()
{
  if(!nappCPUusage) return 0;

  return (nappCPUusage / nappCPUsamples);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int APPCHECKRESOURCESHARDWARE::GetCPUAppCPUUsageMax()
* @brief      GetCPUAppCPUUsageMax
* @ingroup    APPLICATION
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int APPCHECKRESOURCESHARDWARE::GetCPUAppCPUUsageMax()
{
  return maxappCPUusage;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPCHECKRESOURCESHARDWARE::End()
* @brief      End
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPCHECKRESOURCESHARDWARE::End()
{
  inexit =  true;

  /*
  if(exitmutex)
    {
      exitmutex->Lock();
      exitmutex->UnLock();
    }
  */

  if(xscheduler)
    {
      delete xscheduler;
      xscheduler = NULL;
    } 

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPCHECKRESOURCESHARDWARE::CheckMemoryStatus()
* @brief      CheckMemoryStatus
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPCHECKRESOURCESHARDWARE::CheckMemoryStatus()
{
  if(!cfg) return false;

  XDWORD  total;
  XDWORD  free;
  int     freepercent = 0;

  GEN_XSYSTEM.GetMemoryInfo(total,free);

  freepercent = GEN_XSYSTEM.GetFreeMemoryPercent();

  if(freepercent < cfg->CheckResourcesHardware_GetMemStatusLimitPercent())
    {
      GEN_XSYSTEM.FreeCacheMemory();

      //bool status =  GEN_XSYSTEM.FreeCacheMemory();
      //GEN_XLOG.AddEntry((status?XLOGLEVEL_INFO:XLOGLEVEL_WARNING), APP_CFG_LOG_SECTIONID_STATUSAPP, false, __L("Low free memory: %d Kb (%d%%). Cache memory released: %s"), free,  freepercent, (status?__L("Ok."):__L("Error!")));      
     
      APPCHECKRESOURCESHARDWARE_XEVENT  xevent(this, APPCHECKRESOURCESHARDWARE_XEVENT_TYPE_MEMFREELIMIT);      
      xevent.SetActualMemFree(free, GEN_XSYSTEM.GetFreeMemoryPercent());      
      PostEvent(&xevent);
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPCHECKRESOURCESHARDWARE::CheckTotalCPUUsageStatus()
* @brief      CheckTotalCPUUsageStatus
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPCHECKRESOURCESHARDWARE::CheckTotalCPUUsageStatus()
{
  if(!cfg) return false;

  int cpuusage = GEN_XSYSTEM.GetCPUUsageTotal();

  if(cpuusage > maxtotalCPUusage) 
    {
      maxtotalCPUusage = cpuusage;
    }
  
  ntotalCPUusage  += cpuusage;
  ntotalCPUsamples++;
   
  if(ntotalCPUsamples > 5)
    {
      if(GetCPUTotalCPUUsageAverange() > (XDWORD)cfg->CheckResourcesHardware_GetTotalCPUUsageLimitPercent())
        {      
          APPCHECKRESOURCESHARDWARE_XEVENT  xevent(this, APPCHECKRESOURCESHARDWARE_XEVENT_TYPE_TOTALCPUUSAGELIMIT);        
          xevent.SetActualTotalCPUUsage(cpuusage);      
          PostEvent(&xevent);
        } 
    }
    
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPCHECKRESOURCESHARDWARE::CheckAppCPUUsageStatus()
* @brief      CheckAppCPUUsageStatus
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPCHECKRESOURCESHARDWARE::CheckAppCPUUsageStatus()
{
  if(!cfg) return false;

  int cpuusage = 0;

  if(!cfg->CheckResourcesHardware_GetAppCPUUsageProcessName()->IsEmpty())
    {
      cpuusage = GEN_XSYSTEM.GetCPUUsageForProcessName(cfg->CheckResourcesHardware_GetAppCPUUsageProcessName()->Get());  

      if(cpuusage > maxappCPUusage) 
        {
          maxappCPUusage = cpuusage;
        }
    }

  nappCPUusage  += cpuusage;
  nappCPUsamples++;
   
  if(nappCPUsamples > 5)
    {
      if(GetCPUAppCPUUsageAverange() > (XDWORD)cfg->CheckResourcesHardware_GetAppCPUUsageLimitPercent())
        {      
          APPCHECKRESOURCESHARDWARE_XEVENT  xevent(this, APPCHECKRESOURCESHARDWARE_XEVENT_TYPE_APPCPUUSAGELIMIT);        
          xevent.SetActualAppCPUUsage(cpuusage);      
          PostEvent(&xevent);
        } 
    }
    
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPCHECKRESOURCESHARDWARE::HandleEvent_Scheduler(XSCHEDULER_XEVENT* event)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    APPLICATION
*
* @param[in]  event : 
*
* --------------------------------------------------------------------------------------------------------------------*/
void APPCHECKRESOURCESHARDWARE::HandleEvent_Scheduler(XSCHEDULER_XEVENT* event)
{
  if(inexit) 
    {
      return;
    }   

  switch(event->GetTask()->GetID())
    {
      case APPCHECKRESOURCESHARDWARE_TASKID_CHECKMEMORY       : CheckMemoryStatus();            break;

      case APPCHECKRESOURCESHARDWARE_TASKID_TOTALCPUUSAGE     : CheckTotalCPUUsageStatus();     break;
      case APPCHECKRESOURCESHARDWARE_TASKID_APPCPUUSAGE       : CheckAppCPUUsageStatus();       break;
    } 
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPCHECKRESOURCESHARDWARE::HandleEvent(XEVENT* xevent)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    APPLICATION
*
* @param[in]  xevent :
*
* --------------------------------------------------------------------------------------------------------------------*/
void APPCHECKRESOURCESHARDWARE::HandleEvent(XEVENT* xevent)
{
  if(!xevent) return; 

//  if(exitmutex) exitmutex->Lock();

  switch(xevent->GetEventFamily())
    {
      case XEVENT_TYPE_SCHEDULER      : { XSCHEDULER_XEVENT* event = (XSCHEDULER_XEVENT*)xevent;
                                          if(!event) return;

                                          HandleEvent_Scheduler(event);
                                        }
                                        break;
    } 
  
//  if(exitmutex) exitmutex->UnLock(); 
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPCHECKRESOURCESHARDWARE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    APPLICATION
*
* --------------------------------------------------------------------------------------------------------------------*/
void APPCHECKRESOURCESHARDWARE::Clean()
{
  cfg                     = NULL;

  inexit                  = false;
//exitmutex               = NULL;
  xscheduler              = NULL;

  ntotalCPUusage          = 0;
  ntotalCPUsamples        = 0;
  maxtotalCPUusage        = 0;

  nappCPUusage            = 0;
  nappCPUsamples          = 0;
  maxappCPUusage          = 0;
}


#pragma endregion