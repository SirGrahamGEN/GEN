/**-------------------------------------------------------------------------------------------------------------------
*
* @file       APPCFG.cpp
*
* @class      APPCFG
* @brief      Application Config class
* @ingroup    APPLICATION
*
* @copyright  GEN Group. All right reserved.
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

#include "GEN_DefaultXTraceCFG.h"

#include "XTrace.h"
#include "XLog.h"
#include "DIODNSResolved.h"

#include "APPCFG.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/



/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPCFG::APPCFG(XCHAR* namefile)
* @brief      Constructor
* @ingroup    APPLICATION
*
* @param[in]  XCHAR* : 
*
* @return     Does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
APPCFG::APPCFG(XCHAR* namefile)
#ifdef APP_CFG_REMOTEFILE_ACTIVE
 : DIOREMOTEFILECFG(namefile)
#else
 : XFILECFG(namefile)
#endif
{
  XSTRING section;
  XSTRING key;

  Clean();


  #ifdef APP_CFG_GENERAL_ACTIVE
  //-----------------------------------------------------
  // GENERAL

  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_GENERAL                   , APP_CFG_SCRAPERWEBSCRIPTURLDOWNLOAD                         , &scraperwebscripturldownload);
  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_GENERAL                   , APP_CFG_SHOWDETAILINFO                                      , &showdetailinfo);

  #ifdef XTRACE_ACTIVE
  for(int c=0; c<XTRACE_MAXNTARGETS; c++)
    {
      key.Format(__L("%s%02d"), APP_CFG_TRACETARGET, c+1);
      AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_GENERAL, key.Get(), &tracetarget[c]);
    }
  #endif
  #endif


  //-----------------------------------------------------
  // CHECH RESOURCES HARWARE
  #ifdef APP_CFG_CHECKRESOURCESHARDWARE_ACTIVE

  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_CHECKRESOURCESHARDWARE    , APP_CFG_CHECKRESOURCESHARDWARE_MEMSTATUSCHECKCADENCE        , &checkresourceshardware_memstatuscheckcadence);
  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_CHECKRESOURCESHARDWARE    , APP_CFG_CHECKRESOURCESHARDWARE_MEMSTATUSLIMITPERCENT        , &checkresourceshardware_memstatuslimitpercent);
  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_CHECKRESOURCESHARDWARE    , APP_CFG_CHECKRESOURCESHARDWARE_CPUUSAGECHECKCADENCE         , &checkresourceshardware_cpuusagecheckcadence);
  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_CHECKRESOURCESHARDWARE    , APP_CFG_CHECKRESOURCESHARDWARE_CPUUSAGELIMITPERCENT         , &checkresourceshardware_cpuusagelimitpercent);  
  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_CHECKRESOURCESHARDWARE    , APP_CFG_CHECKRESOURCESHARDWARE_CPUUSAGEPROCESSNAME          , &checkresourceshardware_cpuusageprocessname);

  #endif


  #ifdef APP_CFG_INTERNETSERVICES_ACTIVE
  //-----------------------------------------------------
  // INTERNET SERVICES

  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_INTERNETSERVICES          , APP_CFG_INTERNETSERVICES_CHECKINTERNETSTATUSCADENCE         , &internetservices_checkinternetstatuscadence);
  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_INTERNETSERVICES          , APP_CFG_INTERNETSERVICES_CHECKIPPUBLICCHANGECADENCE         , &internetservices_checkippublicchangecadence);
  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_INTERNETSERVICES          , APP_CFG_INTERNETSERVICES_UPDATETIMEBYNTPCADENCE             , &internetservices_updatetimebyntpcadence);

  for(int c=0; c<APP_CFG_INTERNETSERVICES_UPDATETIMENTPMAXSERVERS; c++)
    {
      key.Format(__L("%s%02d"), APP_CFG_INTERNETSERVICES_UPDATETIMENTPSERVER, c+1);
      AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_INTERNETSERVICES, key.Get(), &internetservices_updatetimentpservers[c]);
    }

  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_INTERNETSERVICES          , APP_CFG_INTERNETSERVICES_UPDATETIMENTPMERIDIANDIFFERENCE    , &internetservices_updatetimentpmeridiandifference);
  AddValue(XFILECFG_VALUETYPE_BOOLEAN , APP_CFG_SECTION_INTERNETSERVICES          , APP_CFG_INTERNETSERVICES_UPDATETIMENTPUSEDAYLIGHTSAVING     , &internetservices_updatetimentpusedaylightsaving);




  #ifdef APP_CFG_DNSRESOLVED_ACTIVE
  //-----------------------------------------------------
  // DNS RESOLVED

  for(int c=0; c<APP_CFG_DNSRESOLVED_MAXHOSTRESOLVED; c++)
    {
      key.Format(__L("%s%02d"), APP_CFG_DNSRESOLVED_HOSTRESOLVED, c+1);
      AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_DNSRESOLVED, key.Get(), &hostresolved[c]);
    }

  for(int c=0; c<APP_CFG_DNSRESOLVED_MAXDNSSERVERS; c++)
    {
      key.Format(__L("%s%02d"), APP_CFG_DNSRESOLVED_DNSSERVER, c+1);
      AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_DNSRESOLVED, key.Get(), &DNSserver[c]);
    }

  #endif



  #ifdef APP_CFG_DYNDNSMANAGER_ACTIVE
  //-----------------------------------------------------
  // DYNDNS MANAGER

  for(int c=0; c<APP_CFG_DYNDNSMANAGER_MAXURL; c++)
    {
      key.Format(__L("%s%02d"), APP_CFG_DYNDNSMANAGER_URL, c+1);
      AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_DYNDNSMANAGER, key.Get(), &dnsmanager_url[c]);
    }
  #endif

  #endif



  #ifdef APP_CFG_LOCATION_ACTIVE
  //-----------------------------------------------------
  // LOCATION

  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_LOCATION                  , APP_CFG_LOCATION_STREET                                     , &location_street);
  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_LOCATION                  , APP_CFG_LOCATION_TOWN                                       , &location_city);
  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_LOCATION                  , APP_CFG_LOCATION_STATE                                      , &location_state);
  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_LOCATION                  , APP_CFG_LOCATION_COUNTRY                                    , &location_country);
  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_LOCATION                  , APP_CFG_LOCATION_POSTALCODE                                 , &location_postalcode);
  #endif



  #ifdef APP_CFG_APPUPDATE_ACTIVE
  //-----------------------------------------------------
  // APPLICATION UPDATE

  AddValue(XFILECFG_VALUETYPE_BOOLEAN , APP_CFG_SECTION_APPLICATIONUPDATE         , APP_CFG_APPLICATIONUPDATE_ISACTIVE                          , &applicationupdate_isactive);
  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_APPLICATIONUPDATE         , APP_CFG_APPLICATIONUPDATE_URL                               , &applicationupdate_URL);
  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_APPLICATIONUPDATE         , APP_CFG_APPLICATIONUPDATE_PORT                              , &applicationupdate_port);
  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_APPLICATIONUPDATE         , APP_CFG_APPLICATIONUPDATE_CHECKCADENCE                      , &applicationupdate_checkcadence);
  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_APPLICATIONUPDATE         , APP_CFG_APPLICATIONUPDATE_CHECKTIME                         , &applicationupdate_checktime);
  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_APPLICATIONUPDATE         , APP_CFG_APPLICATIONUPDATE_MAXRESTORATIONS                   , &applicationupdate_maxrestorations);
  #endif





  #ifdef APP_CFG_WEBSERVER_ACTIVE
  //-----------------------------------------------------
  // WEBSERVER

  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_WEBSERVER                 , APP_CFG_WEBSERVER_LOCALADDR                                 , &webserver_localaddr);
  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_WEBSERVER                 , APP_CFG_WEBSERVER_PORT                                      , &webserver_port);
  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_WEBSERVER                 , APP_CFG_WEBSERVER_TIMEOUTTOSERVERPAGE                       , &webserver_timeouttoserverpage);
  AddValue(XFILECFG_VALUETYPE_BOOLEAN , APP_CFG_SECTION_WEBSERVER                 , APP_CFG_WEBSERVER_AUTHENTICATEDACCESS                       , &webserver_isauthenticatedaccess);
  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_WEBSERVER                 , APP_CFG_WEBSERVER_PASSWORD                                  , &webserver_password);
  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_WEBSERVER                 , APP_CFG_WEBSERVER_PATH_RESOURCES                            , &webserver_path_resources);
  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_WEBSERVER                 , APP_CFG_WEBSERVER_PATH_PHP                                  , &webserver_path_PHP);
  #endif



  #ifdef APP_CFG_ALERTS_ACTIVE
  //-----------------------------------------------------
  // ALERTS

  AddValue(XFILECFG_VALUETYPE_BOOLEAN , APP_CFG_SECTION_ALERTS                    , APP_CFG_ALERTS_ISACTIVE                                     , &alerts_isactive);

  //------------------------------------

  AddValue(XFILECFG_VALUETYPE_BOOLEAN , APP_CFG_SECTION_ALERTS                    , APP_CFG_ALERTS_SMTP_ISACTIVE                                , &alerts_SMTP_isactive);

   for(int c=0; c<APP_CFG_ALERTS_MAXCONDITIONS; c++)
    {
      key.Format(__L("%s%02d"), APP_CFG_ALERTS_CONDITION, c+1);
      AddValue(XFILECFG_VALUETYPE_STRING, APP_CFG_SECTION_ALERTS, key.Get(),  &alerts_conditions[c]);
    }

  //------------------------------------

  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_ALERTS                    , APP_CFG_ALERTS_SMTP_URL                                     , &alerts_SMTP_URL);
  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_ALERTS                    , APP_CFG_ALERTS_SMTP_PORT                                    , &alerts_SMTP_port);
  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_ALERTS                    , APP_CFG_ALERTS_SMTP_LOGIN                                   , &alerts_SMTP_login);
  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_ALERTS                    , APP_CFG_ALERTS_SMTP_PASSWORD                                , &alerts_SMTP_password);
  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_ALERTS                    , APP_CFG_ALERTS_SMTP_SENDER                                  , &alerts_SMTP_sender);
  for(int c=0; c<APP_CFG_ALERTS_MAXRECIPIENTS; c++)
    {
      key.Format(__L("%s%02d"), APP_CFG_ALERTS_SMTP_RECIPIENT, c+1);
      AddValue(XFILECFG_VALUETYPE_STRING, APP_CFG_SECTION_ALERTS, key.Get(),  &alerts_SMTP_recipient[c]);
    }

  //------------------------------------

  AddValue(XFILECFG_VALUETYPE_BOOLEAN , APP_CFG_SECTION_ALERTS                    , APP_CFG_ALERTS_SMS_ISACTIVE                                 , &alerts_SMS_isactive);
  for(int c=0; c<APP_CFG_ALERTS_MAXRECIPIENTS; c++)
    {
      key.Format(__L("%s%02d"), APP_CFG_ALERTS_SMS_RECIPIENT, c+1);
      AddValue(XFILECFG_VALUETYPE_STRING, APP_CFG_SECTION_ALERTS, key.Get(),  &alerts_SMS_recipient[c]);
    }

  //------------------------------------

  AddValue(XFILECFG_VALUETYPE_BOOLEAN , APP_CFG_SECTION_ALERTS                    , APP_CFG_ALERTS_WEB_ISACTIVE                                 , &alerts_WEB_isactive);
  AddValue(XFILECFG_VALUETYPE_BOOLEAN , APP_CFG_SECTION_ALERTS                    , APP_CFG_ALERTS_WEB_UISUSEGET                                , &alerts_WEB_isuseget);
  for(int c=0; c<APP_CFG_ALERTS_MAXRECIPIENTS; c++)
    {
      key.Format(__L("%s%02d"), APP_CFG_ALERTS_WEB_RECIPIENT, c+1);
      AddValue(XFILECFG_VALUETYPE_STRING, APP_CFG_SECTION_ALERTS, key.Get(),  &alerts_WEB_recipient[c]);
    }

  //------------------------------------

  AddValue(XFILECFG_VALUETYPE_BOOLEAN , APP_CFG_SECTION_ALERTS                    , APP_CFG_ALERTS_UDP_ISACTIVE                                 , &alerts_UDP_isactive);
  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_ALERTS                    , APP_CFG_ALERTS_UDP_PORT                                     , &alerts_UDP_port);
  for(int c=0; c<APP_CFG_ALERTS_MAXRECIPIENTS; c++)
    {
      key.Format(__L("%s%02d"), APP_CFG_ALERTS_UDP_RECIPIENT, c+1);
      AddValue(XFILECFG_VALUETYPE_STRING, APP_CFG_SECTION_ALERTS, key.Get(),  &alerts_UDP_recipient[c]);
    }

  #endif



  #ifdef APP_CFG_LOG_ACTIVE
  //-----------------------------------------------------
  // LOG

  AddValue(XFILECFG_VALUETYPE_BOOLEAN , APP_CFG_SECTION_LOG                     , APP_CFG_LOG_ISACTIVE                                          , &log_isactive);
  AddValue(XFILECFG_VALUETYPE_BOOLEAN , APP_CFG_SECTION_LOG                     , APP_CFG_LOG_BACKUPISACTIVE                                    , &log_backupisactive);
  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_LOG                     , APP_CFG_LOG_BACKUPMAXFILES                                    , &log_backupmaxfiles);
  AddValue(XFILECFG_VALUETYPE_BOOLEAN , APP_CFG_SECTION_LOG                     , APP_CFG_LOG_BACKUPISCOMPRESS                                  , &log_backupiscompress);
  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_LOG                     , APP_CFG_LOG_ACTIVESECTIONSID                                  , &log_activesectionsID);
  AddValue(XFILECFG_VALUETYPE_MASK    , APP_CFG_SECTION_LOG                     , APP_CFG_LOG_LEVELMASK                                         , &log_levelmask);
  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_LOG                     , APP_CFG_LOG_MAXSIZE                                           , &log_maxsize);
  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_LOG                     , APP_CFG_LOG_REDUCTIONPERCENT                                  , &log_reductionpercent);
  #endif

  Default();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPCFG::~APPCFG()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    APPLICATION
*
* @return     Does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
APPCFG::~APPCFG()
{
  End();

  Clean();
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPCFG::Default()
* @brief      Default CFG
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool APPCFG::Default()
{
  //------------------------------------------------------------------------------------------------------

  #ifdef APP_CFG_GENERAL_ACTIVE

  #ifdef XTRACE_ACTIVE
  SetDefaultTraceTargets();
  #endif

  #endif

  //------------------------------------------------------------------------------------------------------

  #ifdef APP_CFG_CHECKRESOURCESHARDWARE_ACTIVE

  checkresourceshardware_memstatuscheckcadence      = 30;
  checkresourceshardware_memstatuslimitpercent      = 5;

  checkresourceshardware_cpuusagecheckcadence       = 20;
  checkresourceshardware_cpuusagelimitpercent       = 70;  
  checkresourceshardware_cpuusageprocessname.Empty();

  #endif

  //------------------------------------------------------------------------------------------------------

  #ifdef APP_CFG_INTERNETSERVICES_ACTIVE

  internetservices_checkinternetstatuscadence       = 30;
  internetservices_checkippublicchangecadence       = 60;
  internetservices_updatetimebyntpcadence           = 4;

  internetservices_updatetimentpservers[0]          = __L("1.es.pool.ntp.org");
  internetservices_updatetimentpservers[1]          = __L("1.europe.pool.ntp.org");
  internetservices_updatetimentpservers[2]          = __L("3.europe.pool.ntp.org");

  internetservices_updatetimentpmeridiandifference  = APP_CFG_INTERNETSERVICES__UPDATETIMENTPMERIDIANDIFFERENCE_AUTO;
  internetservices_updatetimentpusedaylightsaving   = true;


  #ifdef APP_CFG_DYNDNSMANAGER_ACTIVE

  #endif

  #endif

  //------------------------------------------------------------------------------------------------------

  #ifdef APP_CFG_WEBSERVER_ACTIVE

  webserver_timeouttoserverpage                     = 30;

  #endif

  //------------------------------------------------------------------------------------------------------

  #ifdef APP_CFG_APPUPDATE_ACTIVE

  applicationupdate_maxrestorations                 = 12;

  #endif

  //------------------------------------------------------------------------------------------------------

  #ifdef APP_CFG_LOG_ACTIVE

  log_isactive                                      = true;
  log_backupisactive                                = true;
  log_backupmaxfiles                                = 10;
  log_backupiscompress                              = true;

  log_activesectionsID.Empty();

  log_activesectionsID                             += APP_CFG_LOG_SECTIONID_INITIATION;
  log_activesectionsID                             += __L(",");
  log_activesectionsID                             += APP_CFG_LOG_SECTIONID_GENERIC;
  log_activesectionsID                             += __L(",");
  log_activesectionsID                             += APP_CFG_LOG_SECTIONID_STATUSAPP;
  log_activesectionsID                             += __L(",");
  log_activesectionsID                             += APP_CFG_LOG_SECTIONID_ENDING;

  log_levelmask                                     = XLOGLEVEL_ALL;
  log_maxsize                                       = 3000;
  log_reductionpercent                              = 10;

  #endif

  //------------------------------------------------------------------------------------------------------


  return true;
}




#ifdef APP_CFG_GENERAL_ACTIVE
/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPCFG::GetScraperWebScriptURLDownload()
* @brief      GetScraperWebScriptURLDownload
* @ingroup    APPLICATION
*
* @return     XSTRING* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::GetScraperWebScriptURLDownload()
{
  return &scraperwebscripturldownload;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWORD APPCFG::GetShowDetailInfo()
* @brief      GetShowDetailInfo
* @ingroup    APPLICATION
*
* @return     XWORD : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XWORD APPCFG::GetShowDetailInfo()
{
  XDWORD detail = 0x0000;

  showdetailinfo.ToUpperCase();
  showdetailinfo.UnFormat(__L("%04X"), &detail);

  return detail;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPCFG::SetShowDetailInfo(XWORD detail)
* @brief      SetShowDetailInfo
* @ingroup    APPLICATION
*
* @param[in]  detail : 
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void APPCFG::SetShowDetailInfo(XWORD detail)
{
  showdetailinfo.Format(__L("%04X"), detail);
}




#ifdef XTRACE_ACTIVE
/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPCFG::GetTraceTarget(int index)
* @brief      GetTraceTarget
* @ingroup    APPLICATION
*
* @param[in]  index : 
*
* @return     XSTRING* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::GetTraceTarget(int index)
{
  if(index <  0)                   return NULL;
  if(index >= XTRACE_MAXNTARGETS)  return NULL;

  return &tracetarget[index];
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPCFG::SetTraceTarget(int index, XSTRING& target)
* @brief      SetTraceTarget
* @ingroup    APPLICATION
*
* @param[in]  index :
* @param[in]  target :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool APPCFG::SetTraceTarget(int index, XSTRING& target)
{
  if(index <  0)                   return false;
  if(index >= XTRACE_MAXNTARGETS)  return false;

  tracetarget[index] = target.Get();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPCFG::SetAutomaticTraceTargets()
* @brief      SetAutomaticTraceTargets
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool APPCFG::SetAutomaticTraceTargets()
{
  bool status = false;

  for(int c=0;c<XTRACE_MAXNTARGETS; c++)
    {
      XSTRING* debugcfg = GetTraceTarget(c);
      if(debugcfg)
        {
          if(!debugcfg->IsEmpty())
            {
              int      type;
              XSTRING  aim;

              aim.AdjustSize(_MAXSTR);
              debugcfg->UnFormat(__L("%d,%s"), &type, aim.Get());
              aim.AdjustSize();

              XTRACE_SETTARGET(c, (XTRACE_TYPE)type, aim.Get());

              status = true;
            }
        }
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPCFG::SetDefaultTraceTargets()
* @brief      SetDefaultTraceTargets
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool APPCFG::SetDefaultTraceTargets()
{
  GEN_XTRACE_NET_CFG_DEFAULT_01

  return true;
}



#endif

#endif




#ifdef APP_CFG_CHECKRESOURCESHARDWARE_ACTIVE

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int APPCFG::CheckResourcesHardware_GetMemStatusCheckCadence()
* @brief      CheckResourcesHardware_GetMemStatusCheckCadence
* @ingroup    APPLICATION
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int APPCFG::CheckResourcesHardware_GetMemStatusCheckCadence()
{
  return checkresourceshardware_memstatuscheckcadence;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int APPCFG::CheckResourcesHardware_GetMemStatusLimitPercent()
* @brief      CheckResourcesHardware_GetMemStatusLimitPercent
* @ingroup    APPLICATION
*
* @return     int : 
*
*---------------------------------------------------------------------------------------------------------------------*/
int APPCFG::CheckResourcesHardware_GetMemStatusLimitPercent()
{
  return checkresourceshardware_memstatuslimitpercent;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int APPCFG::CheckResourcesHardware_GetCPUUsageCheckCadence()
* @brief      CheckResourcesHardware_GetCPUUsageCheckCadence
* @ingroup    APPLICATION
*
* @return     int : 
*
*---------------------------------------------------------------------------------------------------------------------*/
int APPCFG::CheckResourcesHardware_GetCPUUsageCheckCadence()
{
  return checkresourceshardware_cpuusagecheckcadence;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int APPCFG::CheckResourcesHardware_GetCPUUsageLimitPercent()
* @brief      CheckResourcesHardware_GetCPUUsageLimitPercent
* @ingroup    APPLICATION
*
* @return     int : 
*
*---------------------------------------------------------------------------------------------------------------------*/
int APPCFG::CheckResourcesHardware_GetCPUUsageLimitPercent()
{
  return checkresourceshardware_cpuusagelimitpercent;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPCFG::CheckResourcesHardware_GetCPUUsageProcessName()
* @brief      CheckResourcesHardware_GetCPUUsageProcessName
* @ingroup    APPLICATION
*
* @return     XSTRING* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::CheckResourcesHardware_GetCPUUsageProcessName()
{
  return &checkresourceshardware_cpuusageprocessname;
}



#endif





#ifdef APP_CFG_INTERNETSERVICES_ACTIVE


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int APPCFG::InternetServices_GetCheckInternetStatusCadence()
* @brief      Get cadence for check Internet Status (in seconds)
* @ingroup    APPLICATION
*
* @return     int : check cadence in seconds
*
*---------------------------------------------------------------------------------------------------------------------*/
int APPCFG::InternetServices_GetCheckInternetStatusCadence()
{
  return internetservices_checkinternetstatuscadence;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int APPCFG::InternetServices_GetCheckIPPublicChangeCadence()
* @brief      Get cadence for check IP public status (in minutes)
* @ingroup    APPLICATION
*
* @return     int : check cadence in seconds
*
*---------------------------------------------------------------------------------------------------------------------*/
int APPCFG::InternetServices_GetCheckIPPublicChangeCadence()
{
  return (internetservices_checkippublicchangecadence*60);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int APPCFG::InternetServices_GetUpdateTimeByNTPCadence()
* @brief      Get cadence for update time by NTP (in hours)
* @ingroup    APPLICATION
*
* @return     int : check cadence in seconds
*
*---------------------------------------------------------------------------------------------------------------------*/
int APPCFG::InternetServices_GetUpdateTimeByNTPCadence()
{
  return (internetservices_updatetimebyntpcadence*3600);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPCFG::InternetServices_GetUpdateTimeNTPServer(int index)
* @brief      Get Update Time NTP Server by Index from a List
* @ingroup    APPLICATION
*
* @param[in]  index :
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::InternetServices_GetUpdateTimeNTPServer(int index)
{
  if((index>=0) && (index<APP_CFG_INTERNETSERVICES_UPDATETIMENTPMAXSERVERS)) return &internetservices_updatetimentpservers[index];

  static XSTRING empty;
  return &empty;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int APPCFG::InternetServices_GetUpdateTimeNTPMeridianDifference()
* @brief      InternetServices_GetUpdateTimeNTPMeridianDifference
* @ingroup    APPLICATION
*
* @return     int : 
*
*---------------------------------------------------------------------------------------------------------------------*/
int APPCFG::InternetServices_GetUpdateTimeNTPMeridianDifference()
{
  return internetservices_updatetimentpmeridiandifference;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPCFG::InternetServices_GetUpdateTimeNTPUseDayLightSaving()
* @brief      InternetServices_GetUpdateTimeNTPUseDayLightSaving
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool APPCFG::InternetServices_GetUpdateTimeNTPUseDayLightSaving()
{
  return internetservices_updatetimentpusedaylightsaving;
}





#ifdef APP_CFG_DNSRESOLVED_ACTIVE


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPCFG::DNSResolved_GetHostResolved(int index, XSTRING& host, XSTRING& IPresolved)
* @brief      DNSResolved_GetHostResolved
* @ingroup    APPLICATION
*
* @param[in]  index :
* @param[in]  host :
* @param[in]  IPresolved :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool APPCFG::DNSResolved_GetHostResolved(int index, XSTRING& host, XSTRING& IPresolved)
{
  if(index < 0)                                    return false;
  if(index >= APP_CFG_DNSRESOLVED_MAXHOSTRESOLVED) return false;

  host.AdjustSize(_MAXSTR);
  IPresolved.AdjustSize(_MAXSTR);

  hostresolved[index].UnFormat(__L("%s,%s"), host.Get(), IPresolved.Get());

  host.AdjustSize();
  IPresolved.AdjustSize();

  return (host.GetSize() && IPresolved.GetSize())?true:false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPCFG::DNSResolved_GetDNSserver(int index)
* @brief      DNSResolved_GetDNSserver
* @ingroup    APPLICATION
*
* @param[in]  index :
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::DNSResolved_GetDNSserver(int index)
{
  if(index < 0)                                    return NULL;
  if(index >= APP_CFG_DNSRESOLVED_MAXDNSSERVERS)   return NULL;

  if(!DNSserver[index].GetSize()) return NULL;

  return &DNSserver[index];
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPCFG::SetAutomaticDNSResolved()
* @brief      SetAutomaticDNSResolved
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool APPCFG::SetAutomaticDNSResolved()
{
  for(XDWORD c=0; c<APP_CFG_DNSRESOLVED_MAXHOSTRESOLVED; c++)
    {
      XSTRING  host;
      XSTRING  IPresolved;

      if(DNSResolved_GetHostResolved(c, host, IPresolved))
        {
          GEN_DIODNSRESOLVED.HostResolved_Add(host, IPresolved);
        }
    }

  for(XDWORD c=0; c<APP_CFG_DNSRESOLVED_MAXDNSSERVERS; c++)
    {
      XSTRING* dnsserver = DNSResolved_GetDNSserver(c);
      if(dnsserver)
        {
          GEN_DIODNSRESOLVED.DNSServer_AddDNSServer(dnsserver->Get());
        }
    }

  return true;
}




#endif



#ifdef APP_CFG_DYNDNSMANAGER_ACTIVE

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPCFG::DNSManager_GetURL(int index)
* @brief
* @ingroup    APPLICATION
*
* @param[in]  index :
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::DNSManager_GetURL(int index)
{
  if(index < 0)                                        return NULL;
  if(index >= APP_CFG_DYNDNSMANAGER_MAXURL) return NULL;

  return &dnsmanager_url[index];
}

#endif



#endif



#ifdef APP_CFG_LOCATION_ACTIVE


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPCFG::Location_GetStreet()
* @brief      Location_GetStreet
* @ingroup    APPLICATION
*
* @return     XSTRING* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::Location_GetStreet()
{
  return &location_street;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPCFG::Location_GetCity()
* @brief      Location_GetCity
* @ingroup    APPLICATION
*
* @return     XSTRING* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::Location_GetCity()
{
  return &location_city;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPCFG::Location_GetState()
* @brief      Location_GetState
* @ingroup    APPLICATION
*
* @return     XSTRING* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::Location_GetState()
{
  return &location_state;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPCFG::Location_GetCountry()
* @brief      Location_GetCountry
* @ingroup    APPLICATION
*
* @return     XSTRING* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::Location_GetCountry()
{
  return &location_country;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int APPCFG::Location_GetPostalCode()
* @brief      Location_GetPostalCode
* @ingroup    APPLICATION
*
* @return     int : 
*
*---------------------------------------------------------------------------------------------------------------------*/
int APPCFG::Location_GetPostalCode()
{
  return location_postalcode;
}

#endif



#ifdef APP_CFG_APPUPDATE_ACTIVE

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPCFG::ApplicationUpdate_IsActive()
* @brief      ApplicationUpdate_IsActive
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool APPCFG::ApplicationUpdate_IsActive()
{
  return applicationupdate_isactive;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int APPCFG::ApplicationUpdate_GetPort()
* @brief      ApplicationUpdate_GetPort
* @ingroup    APPLICATION
*
* @return     int : 
*
*---------------------------------------------------------------------------------------------------------------------*/
int APPCFG::ApplicationUpdate_GetPort()
{
  return applicationupdate_port;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPCFG::ApplicationUpdate_GetURL()
* @brief      ApplicationUpdate_GetURL
* @ingroup    APPLICATION
*
* @return     XSTRING* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::ApplicationUpdate_GetURL()
{
  return &applicationupdate_URL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int APPCFG::ApplicationUpdate_GetCheckCadence()
* @brief      ApplicationUpdate_GetCheckCadence
* @ingroup    APPLICATION
*
* @return     int : 
*
*---------------------------------------------------------------------------------------------------------------------*/
int APPCFG::ApplicationUpdate_GetCheckCadence()
{
  return applicationupdate_checkcadence;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPCFG::ApplicationUpdate_GetCheckTime()
* @brief      Get CFG Check time to Update
* @ingroup    APPLICATION
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::ApplicationUpdate_GetCheckTime()
{
  return &applicationupdate_checktime;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int APPCFG::ApplicationUpdate_GetMaxRestorations()
* @brief      ApplicationUpdate_GetMaxRestorations
* @ingroup    APPLICATION
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int APPCFG::ApplicationUpdate_GetMaxRestorations()
{
  return applicationupdate_maxrestorations;
}


#endif



#ifdef APP_CFG_ALERTS_ACTIVE


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPCFG::Alerts_IsActive()
* @brief      Alerts_IsActive
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool APPCFG::Alerts_IsActive()
{
  return alerts_isactive;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPCFG::Alerts_GetCondition(int index)
* @brief      Alerts_GetCondition
* @ingroup    APPLICATION
*
* @param[in]  index : 
*
* @return     XSTRING* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::Alerts_GetCondition(int index)
{
  if(index<0)                               return NULL;
  if(index>=APP_CFG_ALERTS_MAXCONDITIONS)   return NULL;

  return &alerts_conditions[index];
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPCFG::Alerts_GetCondition(int index, XDWORD& conditionID, int& timelimitforrepeat, int& everynumberoftimes)
* @brief      Alerts_GetCondition
* @ingroup    APPLICATION
*
* @param[in]  index : 
* @param[in]  conditionID : 
* @param[in]  timelimitforrepeat : 
* @param[in]  everynumberoftimes : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool APPCFG::Alerts_GetCondition(int index, XDWORD& conditionID, int& timelimitforrepeat, int& everynumberoftimes)
{
  XSTRING* string = Alerts_GetCondition(index);
  if(!string)             return false;
  if(string->IsEmpty())   return false;

  conditionID          = 0; 
  timelimitforrepeat   = 0;
  everynumberoftimes   = 0;

  string->UnFormat(__L("%d,%d,%d"), &conditionID, &timelimitforrepeat, &everynumberoftimes);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPCFG::Alerts_IsActiveSMTP()
* @brief      Alerts_IsActiveSMTP
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool APPCFG::Alerts_IsActiveSMTP()
{
  return alerts_SMTP_isactive;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPCFG::Alerts_GetSMTPURL()
* @brief      Alerts_GetSMTPURL
* @ingroup    APPLICATION
*
* @return     XSTRING* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::Alerts_GetSMTPURL()
{
  return &alerts_SMTP_URL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int APPCFG::Alerts_GetSMTPPort()
* @brief      Alerts_GetSMTPPort
* @ingroup    APPLICATION
*
* @return     int : 
*
*---------------------------------------------------------------------------------------------------------------------*/
int APPCFG::Alerts_GetSMTPPort()
{
  return alerts_SMTP_port;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPCFG::Alerts_GetSMTPLogin()
* @brief      Alerts_GetSMTPLogin
* @ingroup    APPLICATION
*
* @return     XSTRING* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::Alerts_GetSMTPLogin()
{
  return &alerts_SMTP_login;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPCFG::Alerts_GetSMTPPassword()
* @brief      Alerts_GetSMTPPassword
* @ingroup    APPLICATION
*
* @return     XSTRING* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::Alerts_GetSMTPPassword()
{
  return &alerts_SMTP_password;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPCFG::Alerts_GetSMTPSender()
* @brief      Alerts_GetSMTPSender
* @ingroup    APPLICATION
*
* @return     XSTRING* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::Alerts_GetSMTPSender()
{
  return &alerts_SMTP_sender;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPCFG::Alerts_GetSMTPRecipient(int index)
* @brief      Alerts_GetSMTPRecipient
* @ingroup    APPLICATION
*
* @param[in]  index : 
*
* @return     XSTRING* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::Alerts_GetSMTPRecipient(int index)
{
  if(index<0)                             return NULL;
  if(index>=APP_CFG_ALERTS_MAXRECIPIENTS) return NULL;

  return &alerts_SMTP_recipient[index];
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPCFG::Alerts_IsActiveSMS()
* @brief      Alerts_IsActiveSMS
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool APPCFG::Alerts_IsActiveSMS()
{
  return alerts_SMS_isactive;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPCFG::Alerts_GetSMSRecipient(int index)
* @brief      Alerts_GetSMSRecipient
* @ingroup    APPLICATION
*
* @param[in]  index : 
*
* @return     XSTRING* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::Alerts_GetSMSRecipient(int index)
{
  if(index<0)                                return NULL;
  if(index>=APP_CFG_ALERTS_MAXRECIPIENTS)    return NULL;

  return &alerts_SMS_recipient[index];
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPCFG::Alerts_IsActiveWEB()
* @brief      Alerts_IsActiveWEB
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool APPCFG::Alerts_IsActiveWEB()
{
  return alerts_WEB_isactive;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPCFG::Alerts_GetWEBIsUseGet()
* @brief      Alerts_GetWEBIsUseGet
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool APPCFG::Alerts_GetWEBIsUseGet()
{
  return alerts_WEB_isuseget;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPCFG::Alerts_GetWEBRecipient(int index)
* @brief      Alerts_GetWEBRecipient
* @ingroup    APPLICATION
*
* @param[in]  index : 
*
* @return     XSTRING* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::Alerts_GetWEBRecipient(int index)
{
  if(index<0)                                  return NULL;
  if(index>=APP_CFG_ALERTS_MAXRECIPIENTS)    return NULL;

  return &alerts_WEB_recipient[index];
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPCFG::Alerts_IsActiveUDP()
* @brief      Alerts_IsActiveUDP
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool APPCFG::Alerts_IsActiveUDP()
{
  return alerts_UDP_isactive;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int APPCFG::Alerts_GetUDPPort()
* @brief      Alerts_GetUDPPort
* @ingroup    APPLICATION
*
* @return     int : 
*
*---------------------------------------------------------------------------------------------------------------------*/
int APPCFG::Alerts_GetUDPPort()
{
  return alerts_UDP_port;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPCFG::Alerts_GetUDPRecipient(int index)
* @brief      Alerts_GetUDPRecipient
* @ingroup    APPLICATION
*
* @param[in]  index : 
*
* @return     XSTRING* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::Alerts_GetUDPRecipient(int index)
{
  if(index<0)                                                 return NULL;
  if(index>=APP_CFG_ALERTS_MAXRECIPIENTS)    return NULL;

  return &alerts_UDP_recipient[index];
}


#endif




#ifdef APP_CFG_WEBSERVER_ACTIVE


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPCFG::WebServer_GetLocalAddress()
* @brief      Get Local Address for Web Server
* @ingroup    APPLICATION
*
* @return     XSTRING* : local address
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::WebServer_GetLocalAddress()
{
  return &webserver_localaddr;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int APPCFG::WebServer_GetPort()
* @brief      Get Port for Web Server
* @ingroup    APPLICATION
*
* @return     int : port number
*
*---------------------------------------------------------------------------------------------------------------------*/
int APPCFG::WebServer_GetPort()
{
  return webserver_port;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int APPCFG::WebServer_GetTimeoutToServerPage()
* @brief      WebServer_GetTimeoutToServerPage
* @ingroup    APPLICATION
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int APPCFG::WebServer_GetTimeoutToServerPage()
{
  return webserver_timeouttoserverpage;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPCFG::WebServer_AuthenticatedAccess()
* @brief      WebServer_AuthenticatedAccess
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool APPCFG::WebServer_IsAuthenticatedAccess()
{
  return webserver_isauthenticatedaccess;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPCFG::WebServer_GetPassword()
* @brief      Get Password for Web Server
* @ingroup    APPLICATION
*
* @return     XSTRING* : Password web server
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::WebServer_GetPassword()
{
  return &webserver_password;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPATH* APPCFG::WebServer_PathResources()
* @brief      WebServer_DirResources
* @ingroup    APPLICATION
*
* @return     XPATH* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XPATH* APPCFG::WebServer_PathResources()
{
  return &webserver_path_resources;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPATH* APPCFG::WebServer_PathPHP()
* @brief      WebServer_PathPHP
* @ingroup    APPLICATION
*
* @return     XPATH* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XPATH* APPCFG::WebServer_PathPHP()
{
  return &webserver_path_PHP;
}

#endif


#ifdef APP_CFG_LOG_ACTIVE

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPCFG::Log_IsActive()
* @brief      Is Active Log
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool APPCFG::Log_IsActive()
{
  return log_isactive;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPCFG::Log_Backup_IsActive()
* @brief      Is Active Log Backup
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool APPCFG::Log_Backup_IsActive()
{
  return log_backupisactive;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int APPCFG::Log_Backup_GetMaxFiles()
* @brief      Get Max Files to Log Backup
* @ingroup    APPLICATION
*
* @return     int : max files number
*
*---------------------------------------------------------------------------------------------------------------------*/
int APPCFG::Log_Backup_GetMaxFiles()
{
  return log_backupmaxfiles;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPCFG::Log_Backup_IsCompress()
* @brief      Is Backup Compress
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool APPCFG::Log_Backup_IsCompress()
{
  return log_backupiscompress;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPCFG::Log_ActiveSectionsID()
* @brief      Active Sections ID of log
* @ingroup    APPLICATION
*
* @return     XSTRING* : string with the secctions active (separated by comma ',')
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::Log_ActiveSectionsID()
{
  return &log_activesectionsID;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE APPCFG::Log_LevelMask()
* @brief      Level Mask for Log
* @ingroup    APPLICATION
*
* @return     XBYTE : Mask of log
*
*---------------------------------------------------------------------------------------------------------------------*/
XBYTE APPCFG::Log_LevelMask()
{
  return (XBYTE)log_levelmask;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int APPCFG::Log_MaxSize()
* @brief      Max Size of Log
* @ingroup    APPLICATION
*
* @return     int : size in bytes
*
*---------------------------------------------------------------------------------------------------------------------*/
int APPCFG::Log_MaxSize()
{
  return log_maxsize;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int APPCFG::Log_ReductionPercent()
* @brief      Reduction Percent to Log file
* @ingroup    APPLICATION
*
* @return     int : percent reduction (what remains)
*
*---------------------------------------------------------------------------------------------------------------------*/
int APPCFG::Log_ReductionPercent()
{
  return log_reductionpercent;
}


#endif





/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPCFG::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    APPLICATION
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void APPCFG::Clean()
{
  //-----------------------------------------------------------------------------------------------------

  #ifdef APP_CFG_GENERAL_ACTIVE

  scraperwebscripturldownload.Empty();
  showdetailinfo                                    = __L("0000");

  #ifdef XTRACE_ACTIVE
  for(int c=0; c<XTRACE_MAXNTARGETS; c++)
    {
      tracetarget[c].Empty();
    }
  #endif

  #endif

  //-----------------------------------------------------------------------------------------------------

  #ifdef APP_CFG_CHECKRESOURCESHARDWARE_ACTIVE

  checkresourceshardware_memstatuscheckcadence      = 0;
  checkresourceshardware_memstatuslimitpercent      = 0;
  checkresourceshardware_cpuusagecheckcadence       = 0;                      
  checkresourceshardware_cpuusagelimitpercent       = 0;  
  checkresourceshardware_cpuusageprocessname.Empty();

  #endif

  //-----------------------------------------------------------------------------------------------------

  #ifdef APP_CFG_INTERNETSERVICES_ACTIVE

  internetservices_checkinternetstatuscadence       = 0;
  internetservices_checkippublicchangecadence       = 0;
  internetservices_updatetimebyntpcadence           = 0;

  for(int c=0; c<APP_CFG_INTERNETSERVICES_UPDATETIMENTPMAXSERVERS; c++)
    {
      internetservices_updatetimentpservers[c].Empty();
    }

  internetservices_updatetimentpmeridiandifference  = 0;
  internetservices_updatetimentpusedaylightsaving   = false;

  #endif

  //-----------------------------------------------------------------------------------------------------

  #ifdef APP_CFG_LOCATION_ACTIVE

  location_street.Empty();
  location_city.Empty();
  location_state.Empty();
  location_country.Empty();
  location_postalcode                               = 0;

  #endif

  //-----------------------------------------------------------------------------------------------------

  #ifdef APP_CFG_APPUPDATE_ACTIVE

  applicationupdate_isactive                        = false;
  applicationupdate_port                            = 0;
  applicationupdate_checkcadence                    = 0;
  applicationupdate_checktime.Empty();
  applicationupdate_maxrestorations                 = 0;

  #endif

  //-----------------------------------------------------------------------------------------------------

  #ifdef APP_CFG_WEBSERVER_ACTIVE

  webserver_localaddr.Empty();
  webserver_port                                    = 0;
  webserver_timeouttoserverpage                     = 0;
  webserver_isauthenticatedaccess                   = false;

  #endif

  //-----------------------------------------------------------------------------------------------------

  #ifdef APP_CFG_ALERTS_ACTIVE

  alerts_isactive                                   = false;

  alerts_SMTP_isactive                              = false;
  alerts_SMTP_port                                  = 0;
  for(int c=0; c<APP_CFG_ALERTS_MAXRECIPIENTS; c++)
    {
      alerts_SMTP_recipient[c].Empty();
    }

  alerts_SMS_isactive                               = false;
  for(int c=0; c<APP_CFG_ALERTS_MAXRECIPIENTS; c++)
    {
      alerts_SMS_recipient[c].Empty();
    }

  alerts_WEB_isactive                                = false;
  alerts_WEB_isuseget                                = false;
  for(int c=0; c<APP_CFG_ALERTS_MAXRECIPIENTS; c++)
    {
      alerts_WEB_recipient[c].Empty();
    }

  alerts_UDP_isactive                                = false;
  alerts_UDP_port                                     = 0;
  for(int c=0; c<APP_CFG_ALERTS_MAXRECIPIENTS; c++)
    {
      alerts_UDP_recipient[c].Empty();
    }

  #endif

  //-----------------------------------------------------------------------------------------------------

  #ifdef APP_CFG_LOG_ACTIVE

  log_isactive                                      = false;
  log_backupisactive                                = false;
  log_backupmaxfiles                                = 0;
  log_backupiscompress                              = false;
  log_activesectionsID.Empty();
  log_levelmask                                     = 0;
  log_maxsize                                       = 0;
  log_reductionpercent                              = 0;

  #endif

  //-----------------------------------------------------------------------------------------------------
}



