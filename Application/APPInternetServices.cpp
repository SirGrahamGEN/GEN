/**-------------------------------------------------------------------------------------------------------------------
*
* @file       APPInternetServices.cpp
*
* @class      APPINTERNETSERVICES
* @brief      Application Internet Connection Services class
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

#include "XLog.h"
#include "XScheduler.h"
#include "XScheduler_XEvent.h"
#include "XSystem.h"
#include "XTranslation.h"
#include "XTranslation_GEN.h"
#include "XTranslation.h"
#include "XLanguage_ISO_639_3.h"

#include "DIOFactory.h"
#include "DIOStreamDeviceIP.h"
#include "DIOStreamIPLocalEnumDevices.h"
#include "DIOCheckTCPIPConnections.h"
#include "DIOCheckInternetConnection.h"
#include "DIOScraperWebPublicIP.h"
#include "DIONTP.h"
#include "DIODynDNS_Manager.h"
#include "APPLog.h"

#include "APPCFG.h"

#include "APPInternetServices_XEvent.h"

#include "APPInternetServices.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPINTERNETSERVICES::APPINTERNETSERVICES()
* @brief      Constructor
* @ingroup    APPLICATION
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
APPINTERNETSERVICES::APPINTERNETSERVICES()
{
  Clean();

  RegisterEvent(APPINTERNETSERVICES_XEVENT_TYPE_CHECKINTERNETCONNEXION);
  RegisterEvent(APPINTERNETSERVICES_XEVENT_TYPE_CHANGEIP);  
  RegisterEvent(APPINTERNETSERVICES_XEVENT_TYPE_ADJUSTDATETIME);
  
  GEN_XFACTORY_CREATE(xmutex_datetime_actual, Create_Mutex())
  if(!xmutex_datetime_actual) return;

  GEN_XFACTORY_CREATE(xmutex_datetime_utc, Create_Mutex())
  if(!xmutex_datetime_utc) return;

  GEN_XFACTORY_CREATE(xdatetime_actual, CreateDateTime())
  if(xdatetime_actual) xdatetime_actual->Read();

  GEN_XFACTORY_CREATE(xdatetime_utc, CreateDateTime())
  if(xdatetime_utc) xdatetime_utc->Read();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPINTERNETSERVICES::~APPINTERNETSERVICES()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    APPLICATION
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
APPINTERNETSERVICES::~APPINTERNETSERVICES()
{
  End();

  NTPservers.DeleteAll();

  if(xdatetime_actual)
    {
      GEN_XFACTORY.DeleteDateTime(xdatetime_actual);
      xdatetime_actual = NULL;
    }

  if(xdatetime_utc)
    {
      GEN_XFACTORY.DeleteDateTime(xdatetime_utc);
      xdatetime_utc = NULL;
    }

  if(xmutex_datetime_actual) 
    {
      GEN_XFACTORY.Delete_Mutex(xmutex_datetime_actual);
      xmutex_datetime_actual = NULL;
    }

  if(xmutex_datetime_utc) 
    {
      GEN_XFACTORY.Delete_Mutex(xmutex_datetime_utc);
      xmutex_datetime_utc = NULL;
    }

  DeRegisterEvent(APPINTERNETSERVICES_XEVENT_TYPE_CHECKINTERNETCONNEXION);
  DeRegisterEvent(APPINTERNETSERVICES_XEVENT_TYPE_CHANGEIP);
  DeRegisterEvent(APPINTERNETSERVICES_XEVENT_TYPE_ADJUSTDATETIME);

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPINTERNETSERVICES::Ini(APPCFG* cfg, XDWORD timeoutgetpublicip = 0)
* @brief      Ini
* @ingroup    APPLICATION
*
* @param[in]  cfg : 
* @param[in]  timeoutgetpublicip : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool APPINTERNETSERVICES::Ini(APPCFG* cfg, XDWORD timeoutgetpublicip)
{
  bool status = false;

  this->cfg = cfg;

  xscheduler = new XSCHEDULER();
  if(!xscheduler) return false;

  XDATETIME       xdatetimecadence;
  XTIMER          xtimercadence;
  XSCHEDULERTASK* xtask;

  //-------------------------------------------------------------------

  if(cfg->InternetServices_GetCheckInternetStatusCadence() > 0)
    {
      xtask = new XSCHEDULERTASK( xscheduler);
      if(!xtask) return false;

      xdatetimecadence.SetToZero();

      xtimercadence.Reset();
      xtimercadence.AddSeconds(cfg->InternetServices_GetCheckInternetStatusCadence());

      xtimercadence.GetMeasureToDate(&xdatetimecadence);

      xtask->SetNCycles(XSCHEDULER_CYCLEFOREVER, &xdatetimecadence);
      xtask->SetID(APPINTERNETSERVICES_TASKID_CHECKCONNECTIONINTERNET);
      xtask->SetIsStartImmediatelyCycles(true);
      xtask->SetIsActive(true);

      xscheduler->Task_Add(xtask);

      checkinternetconnection = new DIOCHECKINTERNETCONNECTION(cfg->InternetServices_GetCheckInternetStatusCadence()/2);
      status =(checkinternetconnection)?true:false;

      /*
      if(status) 
        { 
          haveinternetconnection = checkinternetconnection->Check();
        }
       else return false; 
      */
    }

  //-------------------------------------------------------------------

  if(cfg->InternetServices_GetCheckIPsChangeCadence() > 0)
    {
      scraperwebpublicIP = new DIOSCRAPERWEBPUBLICIP();
      status = (scraperwebpublicIP?true:false);

      if(status)
        {
          xtask = new XSCHEDULERTASK(xscheduler);
          if(!xtask) return false;

          xdatetimecadence.SetToZero();

          xtimercadence.Reset();
          xtimercadence.AddSeconds(cfg->InternetServices_GetCheckIPsChangeCadence());

          xtimercadence.GetMeasureToDate(&xdatetimecadence);

          xtask->SetNCycles(XSCHEDULER_CYCLEFOREVER, &xdatetimecadence);
          xtask->SetID(APPINTERNETSERVICES_TASKID_GETPUBLICIP);
          xtask->SetIsStartImmediatelyCycles(true);
          xtask->SetIsActive(true);

          xscheduler->Task_Add(xtask);      
           
          #ifdef APP_CFG_DYNDNSMANAGER_ACTIVE
          dyndnsmanager = new DIODYNDNS_MANAGER();
          if(dyndnsmanager)
            {
              for(XDWORD c=0; c<cfg->DNSManager_GetURLs()->GetSize(); c++)
                {
                  dyndnsmanager->AddDNS((*cfg->DNSManager_GetURL(c)));
                }

            }
           else return true;
          #endif  
        }
       else return false; 
    }

  //-------------------------------------------------------------------

  if(cfg->InternetServices_GetUpdateTimeByNTPCadence() > 0)
    {
      for(XDWORD c=0; c<cfg->InternetServices_GetUpdateTimeNTPServers()->GetSize(); c++)
        {
          this->NTPservers.Add(cfg->InternetServices_GetUpdateTimeNTPServer(c));
        }

      xtask = new XSCHEDULERTASK( xscheduler);
      if(!xtask) return false;

      xdatetimecadence.SetToZero();

      xtimercadence.Reset();
      xtimercadence.AddSeconds(cfg->InternetServices_GetUpdateTimeByNTPCadence());

      xtimercadence.GetMeasureToDate(&xdatetimecadence);

      xtask->SetNCycles(XSCHEDULER_CYCLEFOREVER, &xdatetimecadence);
      xtask->SetID(APPINTERNETSERVICES_TASKID_CHECKNTPDATETIME);
      xtask->SetIsStartImmediatelyCycles(true);
      xtask->SetIsActive(true);

      xscheduler->Task_Add(xtask);
    }

  //-------------------------------------------------------------------

  SubscribeEvent(XEVENT_TYPE_SCHEDULER, xscheduler);
  if(!xscheduler->Ini()) return false;

  //-------------------------------------------------------------------

  if(timeoutgetpublicip)  
    {
      if(cfg->InternetServices_GetCheckIPsChangeCadence() > 0)
        {
          XTIMER* GEN_XFACTORY_CREATE(timeout, CreateTimer())
          if(timeout)
            {              
              do{ if(!publicIP.IsEmpty()) break;

                  GEN_XSLEEP.MilliSeconds(50);    

                } while(timeout->GetMeasureSeconds() <= timeoutgetpublicip);
            } 

          GEN_XFACTORY.DeleteTimer(timeout);    
        }         
    }
   
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPINTERNETSERVICES::HaveInternetConnection()
* @brief      HaveInternetConnection
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPINTERNETSERVICES::HaveInternetConnection()
{
  return haveinternetconnection;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPINTERNETSERVICES::GetAutomaticLocalIP()
* @brief      GetAutomaticLocalIP
* @ingroup    APPLICATION
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPINTERNETSERVICES::GetAutomaticLocalIP()
{
  return &automaticlocalIP;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* APPINTERNETSERVICES::GetAlLLocalIP()
* @brief      GetAlLLocalIP
* @ingroup    APPLICATION
*
* @return     XSTRING* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPINTERNETSERVICES::GetAlLLocalIP()
{
  return &alllocalIP;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPINTERNETSERVICES::GetPublicIP()
* @brief      GetPublicIP
* @ingroup    APPLICATION
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPINTERNETSERVICES::GetPublicIP()
{
  return &publicIP;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDATETIME* APPINTERNETSERVICES::DateTime_GetActual(bool active_daylightsave, bool active_meridian)
* @brief      DateTime_GetActual
* @ingroup    APPLICATION
*
* @param[in]  active_daylightsave : 
* @param[in]  active_meridian : 
*
* @return     XDATETIME* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
XDATETIME* APPINTERNETSERVICES::DateTime_GetActual(bool active_daylightsave, bool active_meridian)
{
  if(!xdatetime_actual) return NULL;

  if(xmutex_datetime_actual)  xmutex_datetime_actual->Lock();

  xdatetime_actual->Read();

  XQWORD seconds = xdatetime_actual->GetSeconsFromDate(false);
  if(seconds)
    {
      if(!active_meridian)
        {
          seconds -= (DateTime_GetMeridian() * 3600);           
        }

      if(!active_daylightsave)
        {
          if(cfg->InternetServices_GetUpdateTimeNTPUseDayLightSaving())
            {
               if(xdatetime_actual->IsDayLigthSavingTime()) 
                 {
                   seconds -= 3600;
                 }
            }
        }

       xdatetime_actual->SetDateToZero();
       xdatetime_actual->SetDateFromSeconds(seconds, false);                  
    }

  if(xmutex_datetime_actual)  xmutex_datetime_actual->UnLock();

  return xdatetime_actual;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDATETIME* APPINTERNETSERVICES::DateTime_GetUTC()
* @brief      DateTime_GetUTC
* @ingroup    APPLICATION
*
* @return     XDATETIME* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
XDATETIME* APPINTERNETSERVICES::DateTime_GetUTC()
{
  if(!xdatetime_utc) return NULL;

  if(xmutex_datetime_utc)  xmutex_datetime_utc->Lock();

  xdatetime_utc->Read();

  XQWORD seconds = xdatetime_utc->GetSeconsFromDate(false);
  if(seconds)
    {
        int meridian;

       if(cfg->InternetServices_GetUpdateTimeNTPMeridianDifference() == APP_CFG_INTERNETSERVICES__UPDATETIMENTPMERIDIANDIFFERENCE_AUTO)
         {
           meridian = xdatetime_utc->GetMeridianDifference();  
         }
        else 
         {
           meridian = cfg->InternetServices_GetUpdateTimeNTPMeridianDifference();
         } 

       seconds -= (meridian * 3600);           
    
       if(cfg->InternetServices_GetUpdateTimeNTPUseDayLightSaving())
         {
           if(xdatetime_utc->IsDayLigthSavingTime()) 
             {
               seconds -= 3600;
             }            
         }

       xdatetime_utc->SetDateToZero();
       xdatetime_utc->SetDateFromSeconds(seconds, false);                  
    }

 if(xmutex_datetime_utc)  xmutex_datetime_utc->UnLock();

 return xdatetime_utc;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int APPINTERNETSERVICES::DateTime_GetMeridian()
* @brief      DateTime_GetMeridian
* @ingroup    APPLICATION
*
* @return     int : 
*
* --------------------------------------------------------------------------------------------------------------------*/
int APPINTERNETSERVICES::DateTime_GetMeridian()
{
  int meridian = 0;
  
  if(cfg->InternetServices_GetUpdateTimeNTPMeridianDifference() == APP_CFG_INTERNETSERVICES__UPDATETIMENTPMERIDIANDIFFERENCE_AUTO)
    {
      meridian = xdatetime_actual->GetMeridianDifference();  
    }
   else 
    {
      meridian = cfg->InternetServices_GetUpdateTimeNTPMeridianDifference();
    }
  
  return meridian;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOCHECKTCPIPCONNECTIONS* APPINTERNETSERVICES::GetCheckTCPIPConnections()
* @brief      GetCheckTCPIPConnections
* @ingroup    APPLICATION
*
* @return     DIOCHECKTCPIPCONNECTIONS* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOCHECKTCPIPCONNECTIONS* APPINTERNETSERVICES::GetCheckTCPIPConnections()
{
  return  checkinternetconnection->GetCheckConnections();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOCHECKINTERNETCONNECTION* APPINTERNETSERVICES::GetCheckInternetConnection()
* @brief      GetCheckInternetConnection
* @ingroup    APPLICATION
*
* @return     DIOCHECKINTERNETCONNECTION* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOCHECKINTERNETCONNECTION* APPINTERNETSERVICES::GetCheckInternetConnection()
{
  return checkinternetconnection;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIODYNDNS_MANAGER* APPINTERNETSERVICES::GetDynDNSManager()
* @brief      GetDynDNSManager
* @ingroup    APPLICATION
*
* @return     DIODYNDNS_MANAGER* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIODYNDNS_MANAGER* APPINTERNETSERVICES::GetDynDNSManager()
{
  return dyndnsmanager;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSCHEDULER* APPINTERNETSERVICES::GetXScheduler()
* @brief      GetXScheduler
* @ingroup    APPLICATION
* 
* @return     XSCHEDULER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSCHEDULER* APPINTERNETSERVICES::GetXScheduler()
{
  return xscheduler;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPINTERNETSERVICES::End()
* @brief      End
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPINTERNETSERVICES::End()
{
  if(xscheduler)
    {
      delete xscheduler;
      xscheduler = NULL;
    }

  #ifdef APP_CFG_DYNDNSMANAGER_ACTIVE
  if(dyndnsmanager)
    {
      delete dyndnsmanager;
      dyndnsmanager = NULL;
    }
  #endif


  if(scraperwebpublicIP)
    {
      delete scraperwebpublicIP;
      scraperwebpublicIP = NULL;
    }

  if(checkinternetconnection)
    {
      delete checkinternetconnection;
      checkinternetconnection = NULL;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPINTERNETSERVICES::CheckInternetStatus()
* @brief      CheckInternetStatus
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPINTERNETSERVICES::CheckInternetStatus()
{
  APPINTERNETSERVICES_XEVENT xevent(this, APPINTERNETSERVICES_XEVENT_TYPE_CHECKINTERNETCONNEXION);      

  xevent.SetInternetConnexionState(APPINTERNETSERVICES_CHECKINTERNETCONNEXION_STATE_CHECKING);  
  PostEvent(&xevent);

  haveinternetconnection = checkinternetconnection->Check();

  if(checkinternetconnection->IsChangeConnectionStatus())
    {
      if(haveinternetconnection)
        {
          DIOCHECKTCPIPCONNECTION_CUT*  connectioncut =  checkinternetconnection->GetLastConnectionsCut();
          XSTRING                       measuretime;

          if(connectioncut)
            {
              connectioncut->GetMeasureTimeString(measuretime, true);
              
              xevent.SetInternetConnexionState(APPINTERNETSERVICES_CHECKINTERNETCONNEXION_STATE_RESTORE);
              xevent.SetInternetConnextionCut(connectioncut);
            }
           else
            {
              xevent.SetInternetConnexionState(APPINTERNETSERVICES_CHECKINTERNETCONNEXION_STATE_CHECKED); 
            }
        }
       else
        {
          xevent.SetInternetConnexionState(APPINTERNETSERVICES_CHECKINTERNETCONNEXION_STATE_CUT);
        }              
    }
   else
    {
      xevent.SetInternetConnexionState(APPINTERNETSERVICES_CHECKINTERNETCONNEXION_STATE_CHECKED); 
    }

  PostEvent(&xevent);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPINTERNETSERVICES::AdjustTimerByNTP(XVECTOR<XSTRING*>* servers)
* @brief      AdjustTimerByNTP
* @ingroup    APPLICATION
*
* @param[in]  servers :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPINTERNETSERVICES::AdjustTimerByNTP(XVECTOR<XSTRING*>* servers)
{
  if(!servers) return false;

  bool    status = false;

  DIONTP* ntp = new DIONTP();
  if(ntp)
    {
      DIOURL* url = new DIOURL();
      if(url)
        {

          for(XDWORD c=0; c<servers->GetSize(); c++)
            {
              (*url) = servers->Get(c)->Get();

              xdatetime_actual->Read();

              status = ntp->GetTime((*url), 15, GEN_XSYSTEM.HardwareUseLittleEndian(), (*xdatetime_actual));
              if(status)
                {                        
                  if(cfg->InternetServices_GetUpdateTimeNTPMeridianDifference() == APP_CFG_INTERNETSERVICES__UPDATETIMENTPMERIDIANDIFFERENCE_AUTO)
                    {                      
                      xdatetime_actual->AddSeconds(xdatetime_actual->GetMeridianDifference()*3600);  
                    }
                   else 
                    {
                      xdatetime_actual->AddSeconds(cfg->InternetServices_GetUpdateTimeNTPMeridianDifference()*3600);  
                    }
                    
                  if(cfg->InternetServices_GetUpdateTimeNTPUseDayLightSaving())
                    {
                      if(xdatetime_actual->IsDayLigthSavingTime()) 
                        {                      
                          xdatetime_actual->AddSeconds(3600);
                        }
                    }
                 
                  status = xdatetime_actual->Write();

                  break;
                } 
            }

          delete url;
        }

      delete ntp;
    } 

  if(status)
    {
      APPINTERNETSERVICES_XEVENT xevent(this, APPINTERNETSERVICES_XEVENT_TYPE_ADJUSTDATETIME);            
      PostEvent(&xevent);
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPINTERNETSERVICES::HandleEvent_Scheduler(XSCHEDULER_XEVENT* event)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    APPLICATION
*
* @param[in]  event : 
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void APPINTERNETSERVICES::HandleEvent_Scheduler(XSCHEDULER_XEVENT* event)
{
  switch(event->GetTask()->GetID())
    {
      case APPINTERNETSERVICES_TASKID_CHECKCONNECTIONINTERNET : { CheckInternetStatus();
                                                                  
                                                                  //-------------------------------------------------------------------------------                                                              
                                                                  #ifdef XTRACE_ACTIVE                                                                   
                                                                  if(haveinternetconnection)
                                                                    {
                                                                      static int counter = 0;

                                                                      counter++;
                                                                      
                                                                      if(counter > 100)
                                                                        {
                                                                          XTRACE_RESOLVEALLRESOURCES; 
                                                                          counter = 0;
                                                                        }
                                                                    }                                                                  
                                                                  #endif    
                                                                  //-------------------------------------------------------------------------------                                                              
                                                                }

                                                                break;

      case APPINTERNETSERVICES_TASKID_GETPUBLICIP             : { XSTRING                       actualautomaticlocalIP;
                                                                  DIOSTREAMIPLOCALENUMDEVICES*  enumdevices     = (DIOSTREAMIPLOCALENUMDEVICES*)GEN_DIOFACTORY.CreateStreamEnumDevices(DIOSTREAMENUMTYPE_IP_LOCAL);
                                                                  bool                          sendchangeevent = false;
                                                                      
                                                                  if(enumdevices)
                                                                    {
                                                                      DIOSTREAMDEVICEIP* device = (DIOSTREAMDEVICEIP*)enumdevices->GetFirstActiveDevice();
                                                                      if(device)  device->GetIP()->GetXString(actualautomaticlocalIP);

                                                                      alllocalIP.Empty();

                                                                      for(XDWORD c=0; c<enumdevices->GetDevices()->GetSize(); c++)
                                                                        {
                                                                          device = (DIOSTREAMDEVICEIP*)enumdevices->GetDevices()->Get(c);
                                                                          if(device)
                                                                            {
                                                                              if((!device->GetIP()->IsEmpty()) && 
                                                                                 (!device->GetIP()->IsAPIPA()) &&
                                                                                 ((device->GetIPType() == DIOSTREAMIPDEVICE_TYPE_ETHERNET) ||
                                                                                  (device->GetIPType() == DIOSTREAMIPDEVICE_TYPE_WIFI)     ||
                                                                                  (device->GetIPType() == DIOSTREAMIPDEVICE_TYPE_PPP)))
                                                                                  {
                                                                                    XSTRING locaIPstring;

                                                                                    if(!alllocalIP.IsEmpty()) alllocalIP.Add(",");                                                                                      

                                                                                    device->GetIP()->GetXString(locaIPstring); 
                                                                                    alllocalIP.Add(locaIPstring.Get());                                                                                      
                                                                                  }
                                                                            }  
                                                                        }    

                                                                      GEN_DIOFACTORY.DeleteStreamEnumDevices(enumdevices);
                                                                    }

                                                                  APPINTERNETSERVICES_XEVENT xevent(this, APPINTERNETSERVICES_XEVENT_TYPE_CHANGEIP);  

                                                                  // Check Local IP changed
                                                                  if(automaticlocalIP.Compare(actualautomaticlocalIP))
                                                                    {                                                                      
                                                                      xevent.SetIsChangeLocalIP(true);          
                                                                      xevent.GetChangeLocalIP()->Set(actualautomaticlocalIP);

                                                                      automaticlocalIP  = actualautomaticlocalIP;
                                                                      sendchangeevent   = true;
                                                                    }  
                                                                  
                                                                  if(haveinternetconnection)
                                                                    {
                                                                      DIOIP     ip;
                                                                      XSTRING   actualpublicIP;                                                                  

                                                                      if(scraperwebpublicIP->Get(ip, 5, NULL, false)) ip.GetXString(actualpublicIP);

                                                                      // Check Public IP changed
                                                                      if(publicIP.Compare(actualpublicIP))
                                                                        {
                                                                          xevent.SetIsChangePublicIP(true);          
                                                                          xevent.GetChangePublicIP()->Set(actualpublicIP);

                                                                          publicIP        = actualpublicIP;                                                                          
                                                                          sendchangeevent = true;
                                                                        }
                                                                
                                                                      #ifdef APP_CFG_DYNDNSMANAGER_ACTIVE
                                                                      if(dyndnsmanager) dyndnsmanager->AssingAll();
                                                                      #endif                                                                      
                                                                    } 

                                                                  if(sendchangeevent)
                                                                    {
                                                                      PostEvent(&xevent);                                                                      
                                                                    }
                                                                }
                                                                break;

      case APPINTERNETSERVICES_TASKID_CHECKNTPDATETIME        : if(haveinternetconnection) AdjustTimerByNTP(&NTPservers);                                                                  
                                                                break;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPINTERNETSERVICES::HandleEvent(XEVENT* xevent)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    APPLICATION
*
* @param[in]  xevent :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void APPINTERNETSERVICES::HandleEvent(XEVENT* xevent)
{
  if(!xevent) return;

  switch(xevent->GetEventFamily())
    {
      case XEVENT_TYPE_SCHEDULER       : {  XSCHEDULER_XEVENT* event = (XSCHEDULER_XEVENT*)xevent;
                                            if(!event) return;

                                            HandleEvent_Scheduler(event);
                                         }
                                         break;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPINTERNETSERVICES::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    APPLICATION
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void APPINTERNETSERVICES::Clean()
{
  xscheduler              = NULL;

  automaticlocalIP.Empty();
  alllocalIP.Empty();

  checkinternetconnection = NULL;

  haveinternetconnection  = false;

  scraperwebpublicIP      = NULL;

  xdatetime_actual        = NULL;
  xdatetime_utc           = NULL;

  dyndnsmanager           = NULL;
}
