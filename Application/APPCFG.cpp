/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       APPCFG.cpp
* 
* @class      APPCFG
* @brief      Application Config class
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

#include "APPCFG.h"

#include "Common_DefaultXTraceCFG.h"

#include "XTrace.h"
#include "XLog.h"
#include "DIODNSResolver.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPCFG::APPCFG(XCHAR* namefile)
* @brief      Constructor
* @ingroup    APPLICATION
*
* @param[in]  XCHAR* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
APPCFG::APPCFG(XCHAR* namefile)
#ifdef APP_CFG_REMOTEFILE_ACTIVE
 : DIOREMOTEFILECFG(namefile)
#else
 : XFILECFG(namefile)
#endif
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPCFG::~APPCFG()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    APPLICATION
*
* --------------------------------------------------------------------------------------------------------------------*/
APPCFG::~APPCFG()
{
  End();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPCFG::DoVariableMapping()
* @brief      DoVariableMapping
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPCFG::DoVariableMapping()
{
  if(!XFILECFG::DoVariableMapping())
    {
      return false;
    }

  //---------------------------------------------------------------------------------------------------------------------------------------------------------------

  #ifdef APP_CFG_GENERAL_ACTIVE  
  AddRemark(APP_CFG_SECTION_GENERAL, __L("--------------------------------------------------------------------------------------------------------------------------------------------"), 0, 1);
  AddRemark(APP_CFG_SECTION_GENERAL, __L(" General section of configuration"), 0, 2);

  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_GENERAL                   , APP_CFG_SCRAPERWEBSCRIPTURLDOWNLOAD                         , &scraperwebscripturldownload                                        , __L("Scrapper WEB Script URL download")                                   , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_GENERAL                   , APP_CFG_SHOWDETAILINFO                                      , &showdetailinfo                                                     , __L("Show Detail info")                                                   , APP_CFG_DEFAULT_REMARK_COLUMN);

  #ifdef XTRACE_ACTIVE
  XFILECFGVALUE* CFGvalue = AddValueSecuence<XSTRING>(XFILECFG_VALUETYPE_STRING, APP_CFG_SECTION_GENERAL, APP_CFG_TRACETARGET, __L("%02d"), XTRACE_MINNTARGETS
                                                                                                                , XTRACE_MAXNTARGETS
                                                                                                                , tracetargets
                                                                                                                , ntracetargets                                                                                       , __L("eXtended Trace Aim ")                                                , APP_CFG_DEFAULT_REMARK_COLUMN);
  if(CFGvalue) 
    { 
      CFGvalue->SetModeRemoteMix((XFILECFG_MODEREMOTEMIX)(CFGvalue->GetModeRemoteMix() | XFILECFG_MODEREMOTEMIX_NOTDELADDKEYS));
    }
  #endif  
  #endif

  //---------------------------------------------------------------------------------------------------------------------------------------------------------------

  #ifdef APP_CFG_CHECKRESOURCESHARDWARE_ACTIVE
  AddRemark(APP_CFG_SECTION_CHECKRESOURCESHARDWARE, __L("--------------------------------------------------------------------------------------------------------------------------------------------"), 0, 1);
  AddRemark(APP_CFG_SECTION_CHECKRESOURCESHARDWARE, __L(" Check resources section of configuration"), 0, 2);

  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_CHECKRESOURCESHARDWARE    , APP_CFG_CHECKRESOURCESHARDWARE_MEMSTATUSCHECKCADENCE              , &checkresourceshardware_memstatuscheckcadence                 , __L("System Memory status check cadence")                                 , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_CHECKRESOURCESHARDWARE    , APP_CFG_CHECKRESOURCESHARDWARE_MEMSTATUSLIMITPERCENT              , &checkresourceshardware_memstatuslimitpercent                 , __L("System Memory free Limit percent")                                   , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_CHECKRESOURCESHARDWARE    , APP_CFG_CHECKRESOURCESHARDWARE_TOTALCPUUSAGECHECKCADENCE          , &checkresourceshardware_totalcpuusagecheckcadence             , __L("System Total CPU usage cadence")                                     , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_CHECKRESOURCESHARDWARE    , APP_CFG_CHECKRESOURCESHARDWARE_TOTALCPUUSAGELIMITPERCENT          , &checkresourceshardware_totalcpuusagelimitpercent             , __L("System Total CPU limit percent")                                     , APP_CFG_DEFAULT_REMARK_COLUMN);  
  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_CHECKRESOURCESHARDWARE    , APP_CFG_CHECKRESOURCESHARDWARE_APPCPUUSAGEPROCESSNAME             , &checkresourceshardware_appcpuusageprocessname                , __L("System App CPU usage process name")                                  , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_CHECKRESOURCESHARDWARE    , APP_CFG_CHECKRESOURCESHARDWARE_APPCPUUSAGECHECKCADENCE            , &checkresourceshardware_appcpuusagecheckcadence               , __L("System App CPU usage cadence")                                       , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_CHECKRESOURCESHARDWARE    , APP_CFG_CHECKRESOURCESHARDWARE_APPCPUUSAGELIMITPERCENT            , &checkresourceshardware_appcpuusagelimitpercent               , __L("System App CPU limit percent")                                       , APP_CFG_DEFAULT_REMARK_COLUMN);    
  #endif

  //---------------------------------------------------------------------------------------------------------------------------------------------------------------

  #ifdef APP_CFG_INTERNETSERVICES_ACTIVE

  AddRemark(APP_CFG_SECTION_INTERNETSERVICES, __L("--------------------------------------------------------------------------------------------------------------------------------------------"), 0, 1);
  AddRemark(APP_CFG_SECTION_INTERNETSERVICES, __L(" Internet services section of configuration"), 0, 2);

  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_INTERNETSERVICES          , APP_CFG_INTERNETSERVICES_CHECKINTERNETSTATUSCADENCE               , &internetservices_checkinternetstatuscadence                  , __L("Internet connection status cadence")                                 , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_BOOLEAN , APP_CFG_SECTION_INTERNETSERVICES          , APP_CFG_INTERNETSERVICES_DONOTLETINTERNETCONNECTIONMATTER         , &internetservices_donotletinternetconnectionmatter            , __L("Do not let Internet connection matter")                              , APP_CFG_DEFAULT_REMARK_COLUMN); 
  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_INTERNETSERVICES          , APP_CFG_INTERNETSERVICES_CHECKIPSCHANGECADENCE                    , &internetservices_checkipschangecadence                       , __L("Internet IP Change Cadence")                                         , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_INTERNETSERVICES          , APP_CFG_INTERNETSERVICES_UPDATETIMEBYNTPCADENCE                   , &internetservices_updatetimebyntpcadence                      , __L("Internet update time by NTP cadence")                                , APP_CFG_DEFAULT_REMARK_COLUMN);

  AddValueSecuence<XSTRING>(XFILECFG_VALUETYPE_STRING, APP_CFG_SECTION_INTERNETSERVICES,  APP_CFG_INTERNETSERVICES_UPDATETIMENTPSERVER, __L("%02d"), 3, XFILECFG_DEFAULTMAXSECUENCEENTRYS
                                                                                                                                                      , internetservices_updatetimentpservers
                                                                                                                                                      , internetservices_nupdatetimentpservers                        , __L("Internet update NTP Server")                                         , APP_CFG_DEFAULT_REMARK_COLUMN); 

  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_INTERNETSERVICES          , APP_CFG_INTERNETSERVICES_UPDATETIMENTPMERIDIANDIFFERENCE          , &internetservices_updatetimentpmeridiandifference             , __L("Internet update meridian difference")                                , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_BOOLEAN , APP_CFG_SECTION_INTERNETSERVICES          , APP_CFG_INTERNETSERVICES_UPDATETIMENTPUSEDAYLIGHTSAVING           , &internetservices_updatetimentpusedaylightsaving              , __L("Internet update time day light saving")                              , APP_CFG_DEFAULT_REMARK_COLUMN);

  #ifdef APP_CFG_DNSRESOLVER_ACTIVE
  AddRemark(APP_CFG_SECTION_DNSRESOLVER, __L("--------------------------------------------------------------------------------------------------------------------------------------------"), 0, 1);
  AddRemark(APP_CFG_SECTION_DNSRESOLVER, __L(" DNS resolved section of configuration"), 0, 2); 

  AddValueSecuence<XSTRING>(XFILECFG_VALUETYPE_STRING, APP_CFG_SECTION_DNSRESOLVER, APP_CFG_DNSRESOLVER_HOSTRESOLVED, __L("%02d"), 3, XFILECFG_DEFAULTMAXSECUENCEENTRYS
                                                                                                                                    , hostsresolved
                                                                                                                                    , nhostsresolved                                                                  , __L("Host resolved for DNS ")                                     , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValueSecuence<XSTRING>(XFILECFG_VALUETYPE_STRING, APP_CFG_SECTION_DNSRESOLVER, APP_CFG_DNSRESOLVER_DNSSERVER   , __L("%02d"), 3, XFILECFG_DEFAULTMAXSECUENCEENTRYS
                                                                                                                                    , DNSservers, nDNSservers                                                         , __L("Server for DNS ")                                            , APP_CFG_DEFAULT_REMARK_COLUMN);
  #endif

  #ifdef APP_CFG_DYNDNSMANAGER_ACTIVE
  AddRemark(APP_CFG_DYNDNSMANAGER_URL, __L("--------------------------------------------------------------------------------------------------------------------------------------------"), 0, 1);
  AddRemark(APP_CFG_DYNDNSMANAGER_URL, __L(" DynDNS Manager section of iguration"), 0, 2);

  AddValueSecuence<XSTRING>(XFILECFG_VALUETYPE_STRING, APP_CFG_SECTION_DYNDNSMANAGER,  APP_CFG_DYNDNSMANAGER_URL, __L("%02d")    , 3, XFILECFG_DEFAULTMAXSECUENCEENTRYS
                                                                                                                                    , dnsmanager_urls
                                                                                                                                    , dnsmanager_nurls                                                                , __L("DynDNS Manager URL to assign")                                       , APP_CFG_DEFAULT_REMARK_COLUMN);
  #endif
  #endif

  //---------------------------------------------------------------------------------------------------------------------------------------------------------------

  #ifdef APP_CFG_DIOLOCATION_ACTIVE
  AddRemark(APP_CFG_SECTION_LOCATION, __L("--------------------------------------------------------------------------------------------------------------------------------------------"), 0, 1);
  AddRemark(APP_CFG_SECTION_LOCATION, __L(" Location info section of configuration"), 0, 2);
  
  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_LOCATION                  , APP_CFG_LOCATION_STREET                                     , &location_street                                                    , __L("Location street")                                                    , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_LOCATION                  , APP_CFG_LOCATION_TOWN                                       , &location_city                                                      , __L("Location city")                                                      , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_LOCATION                  , APP_CFG_LOCATION_STATE                                      , &location_state                                                     , __L("Location state")                                                     , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_LOCATION                  , APP_CFG_LOCATION_COUNTRY                                    , &location_country                                                   , __L("Location country")                                                   , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_LOCATION                  , APP_CFG_LOCATION_POSTALCODE                                 , &location_postalcode                                                , __L("Location postal code")                                               , APP_CFG_DEFAULT_REMARK_COLUMN);
  #endif

  //---------------------------------------------------------------------------------------------------------------------------------------------------------------

  #ifdef APP_CFG_APPUPDATE_ACTIVE
  AddRemark(APP_CFG_SECTION_APPLICATIONUPDATE, __L("--------------------------------------------------------------------------------------------------------------------------------------------"), 0, 1);
  AddRemark(APP_CFG_SECTION_APPLICATIONUPDATE, __L(" Application Update section of configuration"), 0, 2);

  AddValue(XFILECFG_VALUETYPE_BOOLEAN , APP_CFG_SECTION_APPLICATIONUPDATE         , APP_CFG_APPLICATIONUPDATE_ISACTIVE                          , &applicationupdate_isactive                                         , __L("Application Update is active")                                       , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_APPLICATIONUPDATE         , APP_CFG_APPLICATIONUPDATE_URL                               , &applicationupdate_URL                                              , __L("Application Update URL")                                             , APP_CFG_DEFAULT_REMARK_COLUMN);      
  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_APPLICATIONUPDATE         , APP_CFG_APPLICATIONUPDATE_PORT                              , &applicationupdate_port                                             , __L("Application Update port")                                            , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_APPLICATIONUPDATE         , APP_CFG_APPLICATIONUPDATE_CHECKCADENCE                      , &applicationupdate_checkcadence                                     , __L("Application Update check cadence")                                   , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_APPLICATIONUPDATE         , APP_CFG_APPLICATIONUPDATE_CHECKTIME                         , &applicationupdate_checktime                                        , __L("Application Update check time")                                      , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_APPLICATIONUPDATE         , APP_CFG_APPLICATIONUPDATE_MAXRESTORATIONS                   , &applicationupdate_maxrestorations                                  , __L("Application Update maximum number of restorations")                  , APP_CFG_DEFAULT_REMARK_COLUMN);
  #endif


  #ifdef APP_CFG_WEBSERVER_ACTIVE
  AddRemark(APP_CFG_SECTION_WEBSERVER, __L("--------------------------------------------------------------------------------------------------------------------------------------------"), 0, 1);
  AddRemark(APP_CFG_SECTION_WEBSERVER, __L(" Web server section of configuration"), 0, 2);

  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_WEBSERVER                 , APP_CFG_WEBSERVER_LOCALADDR                                 , &webserver_localaddr                                                , __L("Local IP for the WEB server")                                        , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_WEBSERVER                 , APP_CFG_WEBSERVER_PORT                                      , &webserver_port                                                     , __L("Port for the WEB server")                                            , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_WEBSERVER                 , APP_CFG_WEBSERVER_TIMEOUTTOSERVERPAGE                       , &webserver_timeouttoserverpage                                      , __L("Timeout for the WEB server")                                         , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_BOOLEAN , APP_CFG_SECTION_WEBSERVER                 , APP_CFG_WEBSERVER_AUTHENTICATEDACCESS                       , &webserver_isauthenticatedaccess                                    , __L("Authenticate access for the WEB server")                             , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_WEBSERVER                 , APP_CFG_WEBSERVER_PASSWORD                                  , &webserver_password                                                 , __L("Password for the WEB server")                                        , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_WEBSERVER                 , APP_CFG_WEBSERVER_PATH_RESOURCES                            , &webserver_path_resources                                           , __L("Path resources for the WEB server")                                  , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_WEBSERVER                 , APP_CFG_WEBSERVER_PATH_PHP                                  , &webserver_path_PHP                                                 , __L("Path instalation PHP for the WEB server")                            , APP_CFG_DEFAULT_REMARK_COLUMN);
  #endif


  #ifdef APP_CFG_ALERTS_ACTIVE
  AddRemark(APP_CFG_SECTION_ALERTS, __L("--------------------------------------------------------------------------------------------------------------------------------------------"), 0, 1);
  AddRemark(APP_CFG_SECTION_ALERTS, __L(" Alerts section of configuration"), 0, 2);
  
  AddValue(XFILECFG_VALUETYPE_BOOLEAN , APP_CFG_SECTION_ALERTS                    , APP_CFG_ALERTS_ISACTIVE                                     , &alerts_isactive                                                    , __L("De/Activate all alerts")                                             , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValueSecuence<XSTRING>(XFILECFG_VALUETYPE_STRING, APP_CFG_SECTION_ALERTS,  APP_CFG_ALERTS_CONDITION, __L("%02d"), 3, XFILECFG_DEFAULTMAXSECUENCEENTRYS
                                                                                                                        , alerts_conditions
                                                                                                                        , alerts_nconditions                                                                          , __L("Conditions for alerts")                                              , APP_CFG_DEFAULT_REMARK_COLUMN);

  AddValue(XFILECFG_VALUETYPE_BOOLEAN , APP_CFG_SECTION_ALERTS                    , APP_CFG_ALERTS_SMTP_ISACTIVE                                , &alerts_SMTP_isactive                                               , __L("De/Activate alerts by SMTP")                                         , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_ALERTS                    , APP_CFG_ALERTS_SMTP_URL                                     , &alerts_SMTP_URL                                                    , __L("URL for the SMTP server")                                            , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_ALERTS                    , APP_CFG_ALERTS_SMTP_PORT                                    , &alerts_SMTP_port                                                   , __L("Port for the SMTP server")                                           , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_ALERTS                    , APP_CFG_ALERTS_SMTP_LOGIN                                   , &alerts_SMTP_login                                                  , __L("Login for the SMTP server")                                          , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_ALERTS                    , APP_CFG_ALERTS_SMTP_PASSWORD                                , &alerts_SMTP_password                                               , __L("Password for the SMTP server")                                       , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_ALERTS                    , APP_CFG_ALERTS_SMTP_SENDER                                  , &alerts_SMTP_sender                                                 , __L("Sender for the SMTP server")                                         , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValueSecuence<XSTRING>(XFILECFG_VALUETYPE_STRING, APP_CFG_SECTION_ALERTS, APP_CFG_ALERTS_SMTP_RECIPIENT, __L("%02d"), 3, XFILECFG_DEFAULTMAXSECUENCEENTRYS
                                                                                                                            , alerts_SMTP_recipients
                                                                                                                            , alerts_SMTP_nrecipients                                                                 , __L("Recipient for sending by SMTP")                                      , APP_CFG_DEFAULT_REMARK_COLUMN);
  
  AddValue(XFILECFG_VALUETYPE_BOOLEAN , APP_CFG_SECTION_ALERTS                    , APP_CFG_ALERTS_SMS_ISACTIVE                                 , &alerts_SMS_isactive                                                , __L("De/Activate alerts by SMS")                                          , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValueSecuence<XSTRING>(XFILECFG_VALUETYPE_STRING, APP_CFG_SECTION_ALERTS, APP_CFG_ALERTS_SMS_RECIPIENT, __L("%02d"), 3, XFILECFG_DEFAULTMAXSECUENCEENTRYS
                                                                                                                           , alerts_SMS_recipients
                                                                                                                           , alerts_SMS_nrecipients                                                                   , __L("Recipient for sending by SMS")                                       , APP_CFG_DEFAULT_REMARK_COLUMN);

  AddValue(XFILECFG_VALUETYPE_BOOLEAN , APP_CFG_SECTION_ALERTS                    , APP_CFG_ALERTS_WEB_ISACTIVE                                 , &alerts_WEB_isactive                                                , __L("De/Activate alerts by WEB")                                          , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_BOOLEAN , APP_CFG_SECTION_ALERTS                    , APP_CFG_ALERTS_WEB_UISUSEGET                                , &alerts_WEB_isuseget                                                , __L("Use Get for alerts by WEB")                                          , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValueSecuence<XSTRING>(XFILECFG_VALUETYPE_STRING, APP_CFG_SECTION_ALERTS, APP_CFG_ALERTS_WEB_RECIPIENT, __L("%02d"), 3, XFILECFG_DEFAULTMAXSECUENCEENTRYS
                                                                                                                           , alerts_WEB_recipients
                                                                                                                           , alerts_WEB_nrecipients                                                                   , __L("Recipient for sending by WEB")                                       , APP_CFG_DEFAULT_REMARK_COLUMN);

  AddValue(XFILECFG_VALUETYPE_BOOLEAN , APP_CFG_SECTION_ALERTS                    , APP_CFG_ALERTS_UDP_ISACTIVE                                 , &alerts_UDP_isactive                                                , __L("De/Activate alerts by UDP")                                          , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_ALERTS                    , APP_CFG_ALERTS_UDP_PORT                                     , &alerts_UDP_port                                                    , __L("Port for the UDP server")                                            , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValueSecuence<XSTRING>(XFILECFG_VALUETYPE_STRING, APP_CFG_SECTION_ALERTS, APP_CFG_ALERTS_UDP_RECIPIENT, __L("%02d"), 3, XFILECFG_DEFAULTMAXSECUENCEENTRYS
                                                                                                                           , alerts_UDP_recipients
                                                                                                                           , alerts_UDP_nrecipients                                                                   , __L("Recipient for sending by UDP")                                       , APP_CFG_DEFAULT_REMARK_COLUMN);
  #endif


  #ifdef APP_CFG_SCRIPTS_ACTIVE

  AddRemark(APP_CFG_SECTION_LOG, __L("--------------------------------------------------------------------------------------------------------------------------------------------"), 0, 1);
  AddRemark(APP_CFG_SECTION_LOG, __L(" Scripts list"), 0, 2);

  AddValueSecuence<XSTRING>(XFILECFG_VALUETYPE_STRING, APP_CFG_SECTION_SCRIPTS    , APP_CFG_SCRIPTS_SCRIPT                 , __L("%03d"), 3, 999 
                                                                                                                           , scripts_list
                                                                                                                           , scripts_nscripts                                                                         , __L("Scripts")                                                            , APP_CFG_DEFAULT_REMARK_COLUMN);



  #endif


  #ifdef APP_CFG_LOG_ACTIVE

  AddRemark(APP_CFG_SECTION_LOG, __L("--------------------------------------------------------------------------------------------------------------------------------------------"), 0, 1);
  AddRemark(APP_CFG_SECTION_LOG, __L(" Log section of configuration"), 0, 2);
  
  AddValue(XFILECFG_VALUETYPE_BOOLEAN , APP_CFG_SECTION_LOG                     , APP_CFG_LOG_ISACTIVE                                          , &log_isactive                                                       , __L("De/Activate log generation")                                         , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_BOOLEAN , APP_CFG_SECTION_LOG                     , APP_CFG_LOG_BACKUPISACTIVE                                    , &log_backupisactive                                                 , __L("De/Activate backup for the log")                                     , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_LOG                     , APP_CFG_LOG_BACKUPMAXFILES                                    , &log_backupmaxfiles                                                 , __L("Maximum number of backup files (ZIP)")                               , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_BOOLEAN , APP_CFG_SECTION_LOG                     , APP_CFG_LOG_BACKUPISCOMPRESS                                  , &log_backupiscompress                                               , __L("De/Activate compression in log backup")                              , APP_CFG_DEFAULT_REMARK_COLUMN);   
  AddValue(XFILECFG_VALUETYPE_STRING  , APP_CFG_SECTION_LOG                     , APP_CFG_LOG_ACTIVESECTIONSID                                  , &log_activesectionsID                                               , __L("Section filter by ID in the log")                                    , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_MASK    , APP_CFG_SECTION_LOG                     , APP_CFG_LOG_LEVELMASK                                         , &log_levelmask                                                      , __L("Filter by level mask")                                               , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_LOG                     , APP_CFG_LOG_MAXSIZE                                           , &log_maxsize                                                        , __L("Limit of the main file to perform the backup (in Kb)")               , APP_CFG_DEFAULT_REMARK_COLUMN);
  AddValue(XFILECFG_VALUETYPE_INT     , APP_CFG_SECTION_LOG                     , APP_CFG_LOG_REDUCTIONPERCENT                                  , &log_reductionpercent                                               , __L("Reduction (percentage) of the main file when performing backup")     , APP_CFG_DEFAULT_REMARK_COLUMN);
  #endif

  return true;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPCFG::DoDefault()
* @brief      DoDefault
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPCFG::DoDefault()
{
  if(!XFILECFG::DoDefault())
    {
      return false;
    }
  

  #ifdef APP_CFG_GENERAL_ACTIVE
  showdetailinfo = __L("0000");
  #ifdef XTRACE_ACTIVE
  SetDefaultTraceTargets();
  #endif
  #endif


  #ifdef APP_CFG_CHECKRESOURCESHARDWARE_ACTIVE
  checkresourceshardware_memstatuscheckcadence      = 30;
  checkresourceshardware_memstatuslimitpercent      = 5;
  checkresourceshardware_totalcpuusagecheckcadence  = 20;
  checkresourceshardware_totalcpuusagelimitpercent  = 70;  
  checkresourceshardware_appcpuusageprocessname.Empty();
  checkresourceshardware_appcpuusagecheckcadence    = 20;
  checkresourceshardware_appcpuusagelimitpercent    = 70;  
  #endif


  #ifdef APP_CFG_INTERNETSERVICES_ACTIVE
  internetservices_checkinternetstatuscadence       = 30;
  internetservices_donotletinternetconnectionmatter = false;
  internetservices_checkipschangecadence            = 3600;
  internetservices_updatetimebyntpcadence           = 4;
  internetservices_updatetimentpservers.Get(0)->Set(__L("1.es.pool.ntp.org")); 
  internetservices_updatetimentpservers.Get(1)->Set(__L("1.europe.pool.ntp.org")); 
  internetservices_updatetimentpservers.Get(2)->Set(__L("3.europe.pool.ntp.org")); 
  internetservices_updatetimentpmeridiandifference  = APP_CFG_INTERNETSERVICES_UPDATETIMENTPMERIDIANDIFFERENCE_AUTO;
  internetservices_updatetimentpusedaylightsaving   = true;
  #endif


  #ifdef APP_CFG_WEBSERVER_ACTIVE
  webserver_timeouttoserverpage                     = 30;
  #endif


  #ifdef APP_CFG_APPUPDATE_ACTIVE
  applicationupdate_maxrestorations                 = 12;
  #endif


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

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPCFG::End()
* @brief      End
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPCFG::End()
{ 

  #ifdef APP_CFG_GENERAL_ACTIVE
  showdetailinfo.Empty();
  #ifdef XTRACE_ACTIVE
  tracetargets.DeleteContents();
  tracetargets.DeleteAll();
  #endif
  #endif

  #ifdef APP_CFG_INTERNETSERVICES_ACTIVE
  internetservices_updatetimentpservers.DeleteContents();
  internetservices_updatetimentpservers.DeleteAll();

  #ifdef APP_CFG_DNSRESOLVER_ACTIVE
  hostsresolved.DeleteContents();
  hostsresolved.DeleteAll();
  DNSservers.DeleteContents();
  DNSservers.DeleteAll();
  #endif

  #ifdef APP_CFG_DYNDNSMANAGER_ACTIVE
  dnsmanager_urls.DeleteContents();  
  dnsmanager_urls.DeleteAll();
  #endif
  #endif

  #ifdef APP_CFG_ALERTS_ACTIVE
  alerts_conditions.DeleteContents();
  alerts_conditions.DeleteAll();
  alerts_SMTP_recipients.DeleteContents();
  alerts_SMTP_recipients.DeleteAll();
  alerts_SMS_recipients.DeleteContents();
  alerts_SMS_recipients.DeleteAll();
  alerts_WEB_recipients.DeleteContents();
  alerts_WEB_recipients.DeleteAll();
  alerts_UDP_recipients.DeleteContents();
  alerts_UDP_recipients.DeleteAll();
  #endif  

  #ifdef APP_CFG_SCRIPTS_ACTIVE
  scripts_list.DeleteContents();
  scripts_list.DeleteAll();
  #endif

  #ifdef APP_CFG_REMOTEFILE_ACTIVE
  return DIOREMOTEFILECFG::End();
  #else
  return XFILECFG::End();
  #endif
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::GetTraceTarget(int index)
{
  if(index <  0)                   return NULL;
  if(index >= XTRACE_MAXNTARGETS)  return NULL;

  return tracetargets.Get(index);
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
* --------------------------------------------------------------------------------------------------------------------*/
bool APPCFG::SetTraceTarget(int index, XSTRING& target)
{
  if(index <  0)                   return false;
  if(index >= XTRACE_MAXNTARGETS)  return false;

  tracetargets.Get(index)->Set(target.Get());

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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
int APPCFG::CheckResourcesHardware_GetMemStatusLimitPercent()
{
  return checkresourceshardware_memstatuslimitpercent;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int APPCFG::CheckResourcesHardware_GetTotalCPUUsageCheckCadence()
* @brief      CheckResourcesHardware_GetTotalCPUUsageCheckCadence
* @ingroup    APPLICATION
*
* @return     int : 
*
* --------------------------------------------------------------------------------------------------------------------*/
int APPCFG::CheckResourcesHardware_GetTotalCPUUsageCheckCadence()
{
  return checkresourceshardware_totalcpuusagecheckcadence;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int APPCFG::CheckResourcesHardware_GetTotalCPUUsageLimitPercent()
* @brief      CheckResourcesHardware_GetTotalCPUUsageLimitPercent
* @ingroup    APPLICATION
*
* @return     int : 
*
* --------------------------------------------------------------------------------------------------------------------*/
int APPCFG::CheckResourcesHardware_GetTotalCPUUsageLimitPercent()
{
  return checkresourceshardware_totalcpuusagelimitpercent;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPCFG::CheckResourcesHardware_GetAppCPUUsageProcessName()
* @brief      CheckResourcesHardware_GetAppCPUUsageProcessName
* @ingroup    APPLICATION
*
* @return     XSTRING* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::CheckResourcesHardware_GetAppCPUUsageProcessName()
{
  return &checkresourceshardware_appcpuusageprocessname;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int APPCFG::CheckResourcesHardware_GetAppCPUUsageCheckCadence()
* @brief      CheckResourcesHardware_GetAppCPUUsageCheckCadence
* @ingroup    APPLICATION
*
* @return     int : 
*
* --------------------------------------------------------------------------------------------------------------------*/
int APPCFG::CheckResourcesHardware_GetAppCPUUsageCheckCadence()
{
  return checkresourceshardware_appcpuusagecheckcadence;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int APPCFG::CheckResourcesHardware_GetAppCPUUsageLimitPercent()
* @brief      CheckResourcesHardware_GetAppCPUUsageLimitPercent
* @ingroup    APPLICATION
*
* @return     int : 
*
* --------------------------------------------------------------------------------------------------------------------*/
int APPCFG::CheckResourcesHardware_GetAppCPUUsageLimitPercent()
{
  return checkresourceshardware_appcpuusagelimitpercent;
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
* --------------------------------------------------------------------------------------------------------------------*/
int APPCFG::InternetServices_GetCheckInternetStatusCadence()
{
  return internetservices_checkinternetstatuscadence;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPCFG::InternetServices_DoNotLetInternetConnectionMatter()
* @brief      InternetServices_DoNotLetInternetConnectionMatter
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPCFG::InternetServices_DoNotLetInternetConnectionMatter()
{
  return internetservices_donotletinternetconnectionmatter;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int APPCFG::InternetServices_GetCheckIPsChangeCadence()
* @brief      InternetServices_GetCheckIPsChangeCadence
* @ingroup    APPLICATION
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int APPCFG::InternetServices_GetCheckIPsChangeCadence()
{
  return internetservices_checkipschangecadence;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int APPCFG::InternetServices_GetUpdateTimeByNTPCadence()
* @brief      Get cadence for update time by NTP (in hours)
* @ingroup    APPLICATION
*
* @return     int : check cadence in seconds
*
* --------------------------------------------------------------------------------------------------------------------*/
int APPCFG::InternetServices_GetUpdateTimeByNTPCadence()
{
  return (internetservices_updatetimebyntpcadence*3600);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<XSTRING*>* APPCFG::InternetServices_GetUpdateTimeNTPServers()
* @brief      InternetServices_GetUpdateTimeNTPServers
* @ingroup    APPLICATION
* 
* @return     XVECTOR<XSTRING*>* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<XSTRING*>* APPCFG::InternetServices_GetUpdateTimeNTPServers()
{
  return &internetservices_updatetimentpservers;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPCFG::InternetServices_GetUpdateTimeNTPServer(int index)
* @brief      Get Update Time NTP Server by Index from a List
* @ingroup    APPLICATION
*
* @param[in]  index :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::InternetServices_GetUpdateTimeNTPServer(int index)
{  
  if(index < 0)                                                      return NULL;
  if(index >= (int)internetservices_updatetimentpservers.GetSize())  return NULL;

  return internetservices_updatetimentpservers.Get(index);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int APPCFG::InternetServices_GetUpdateTimeNTPMeridianDifference()
* @brief      InternetServices_GetUpdateTimeNTPMeridianDifference
* @ingroup    APPLICATION
*
* @return     int : 
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
bool APPCFG::InternetServices_GetUpdateTimeNTPUseDayLightSaving()
{
  return internetservices_updatetimentpusedaylightsaving;
}


#ifdef APP_CFG_DNSRESOLVER_ACTIVE

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPCFG::DNSResolver_GetHost(int index, XSTRING& host, XSTRING& IPresolved)
* @brief      DNSResolver_GetHost
* @ingroup    APPLICATION
*
* @param[in]  index :
* @param[in]  host :
* @param[in]  IPresolved :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPCFG::DNSResolver_GetHost(int index, XSTRING& host, XSTRING& IPresolved)
{
  if(index < 0)                       return false;
  if(index >= hostsresolved.GetSize()) return false;

  host.AdjustSize(_MAXSTR);
  IPresolved.AdjustSize(_MAXSTR);

  hostsresolved.Get(index)->UnFormat(__L("%s,%s"), host.Get(), IPresolved.Get());

  host.AdjustSize();
  IPresolved.AdjustSize();

  return (host.GetSize() && IPresolved.GetSize())?true:false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPCFG::DNSResolver_GetDNSserver(int index)
* @brief      DNSResolver_GetDNSserver
* @ingroup    APPLICATION
*
* @param[in]  index :
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::DNSResolver_GetDNSserver(int index)
{
  if(index < 0)                       return NULL;
  if(index >= DNSservers.GetSize())   return NULL;

  if(!DNSservers.GetSize()) return NULL;

  return DNSservers.Get(index);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPCFG::SetAutomaticDNSResolver()
* @brief      SetAutomaticDNSResolver
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPCFG::SetAutomaticDNSResolver()
{
  for(XDWORD c=0; c<nhostsresolved; c++)
    {
      XSTRING  host;
      XSTRING  IPresolved;

      if(DNSResolver_GetHost(c, host, IPresolved))
        {
          GEN_DIODNSRESOLVER.Host_Add(host, IPresolved);
        }
    }

  for(XDWORD c=0; c<nDNSservers; c++)
    {
      XSTRING* dnsserver = DNSResolver_GetDNSserver(c);
      if(dnsserver)
        {
          GEN_DIODNSRESOLVER.DNSServer_AddDNSServer(dnsserver->Get());
        }
    }

  return true;
}

#endif


#ifdef APP_CFG_DYNDNSMANAGER_ACTIVE


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<XSTRING*>* APPCFG::DNSManager_GetURLs()
* @brief      DNSManager_GetURLs
* @ingroup    APPLICATION
* 
* @return     XVECTOR<XSTRING*>* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<XSTRING*>* APPCFG::DNSManager_GetURLs()
{
  return &dnsmanager_urls;

}


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
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::DNSManager_GetURL(int index)
{
  if(index < 0)                          return NULL;
  if(index >= dnsmanager_urls.GetSize()) return NULL;

  return dnsmanager_urls.Get(index);
}

#endif

#endif


#ifdef APP_CFG_DIOLOCATION_ACTIVE

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPCFG::Location_GetStreet()
* @brief      Location_GetStreet
* @ingroup    APPLICATION
*
* @return     XSTRING* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
bool APPCFG::Alerts_IsActive()
{
  return alerts_isactive;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<XSTRING*>* APPCFG::Alerts_GetConditions()
* @brief      Alerts_GetConditions
* @ingroup    APPLICATION
* 
* @return     XVECTOR<XSTRING*>* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<XSTRING*>* APPCFG::Alerts_GetConditions()
{
  return &alerts_conditions;
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
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::Alerts_GetCondition(int index)
{
  if(index < 0)                              return NULL;
  if(index >= alerts_conditions.GetSize())   return NULL;

  return alerts_conditions.Get(index);
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::Alerts_GetSMTPSender()
{
  return &alerts_SMTP_sender;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<XSTRING*>* APPCFG::Alerts_GetSMTPRecipients()
* @brief      Alerts_GetSMTPRecipients
* @ingroup    APPLICATION
* 
* @return     XVECTOR<XSTRING*>* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<XSTRING*>* APPCFG::Alerts_GetSMTPRecipients()
{
  return &alerts_SMTP_recipients;
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
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::Alerts_GetSMTPRecipient(int index)
{
  if(index < 0)                                  return NULL;
  if(index >= alerts_SMTP_recipients.GetSize())  return NULL;

  return alerts_SMTP_recipients.Get(index);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPCFG::Alerts_IsActiveSMS()
* @brief      Alerts_IsActiveSMS
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPCFG::Alerts_IsActiveSMS()
{
  return alerts_SMS_isactive;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<XSTRING*>* APPCFG::Alerts_GetSMSRecipients()
* @brief      Alerts_GetSMSRecipients
* @ingroup    APPLICATION
* 
* @return     XVECTOR<XSTRING*>* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<XSTRING*>* APPCFG::Alerts_GetSMSRecipients()
{
  return &alerts_SMS_recipients;
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
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::Alerts_GetSMSRecipient(int index)
{
  if(index < 0)                                 return NULL;
  if(index >= alerts_SMS_recipients.GetSize())  return NULL;

  return alerts_SMS_recipients.Get(index);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPCFG::Alerts_IsActiveWEB()
* @brief      Alerts_IsActiveWEB
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
bool APPCFG::Alerts_GetWEBIsUseGet()
{
  return alerts_WEB_isuseget;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<XSTRING*>* APPCFG::Alerts_GetWEBRecipients()
* @brief      Alerts_GetWEBRecipients
* @ingroup    APPLICATION
* 
* @return     XVECTOR<XSTRING*>* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<XSTRING*>* APPCFG::Alerts_GetWEBRecipients()
{
  return &alerts_WEB_recipients;
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
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::Alerts_GetWEBRecipient(int index)
{
  if(index <  0)                               return NULL;
  if(index >= alerts_WEB_recipients.GetSize()) return NULL;

  return alerts_WEB_recipients.Get(index);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPCFG::Alerts_IsActiveUDP()
* @brief      Alerts_IsActiveUDP
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
int APPCFG::Alerts_GetUDPPort()
{
  return alerts_UDP_port;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<XSTRING*>* APPCFG::Alerts_GetUDPRecipients()
* @brief      Alerts_GetUDPRecipients
* @ingroup    APPLICATION
* 
* @return     XVECTOR<XSTRING*>* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<XSTRING*>* APPCFG::Alerts_GetUDPRecipients()
{
  return &alerts_UDP_recipients;
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
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::Alerts_GetUDPRecipient(int index)
{
  if(index <  0)                                return NULL;
  if(index >= alerts_UDP_recipients.GetSize())  return NULL;

  return alerts_UDP_recipients.Get(index);
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
XPATH* APPCFG::WebServer_PathPHP()
{
  return &webserver_path_PHP;
}

#endif


#ifdef APP_CFG_SCRIPTS_ACTIVE

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<XSTRING*>* CBUILDER_CFG::Scripts_GetAll()
* @brief      Scripts_GetAll
* @ingroup    APPLICATION
* 
* @return     XVECTOR<XSTRING*>* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<XSTRING*>* APPCFG::Scripts_GetAll()
{
  return &scripts_list;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* CBUILDER_CFG::Scripts_GetScript(int index)
* @brief      Scripts_GetScript
* @ingroup    APPLICATION
* 
* @param[in]  index : 
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPCFG::Scripts_GetScript(int index)
{
  if(index <  0)                        return NULL;
  if(index >= scripts_list.GetSize())   return NULL;

  return scripts_list.Get(index);
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
void APPCFG::Clean()
{  
  //-----------------------------------------------------------------------------------------------------

  #ifdef APP_CFG_GENERAL_ACTIVE
  scraperwebscripturldownload.Empty();
  showdetailinfo.Empty();
  #ifdef XTRACE_ACTIVE
  ntracetargets = 0;
  #endif
  #endif

  //-----------------------------------------------------------------------------------------------------

  #ifdef APP_CFG_CHECKRESOURCESHARDWARE_ACTIVE
  checkresourceshardware_memstatuscheckcadence      = 0;
  checkresourceshardware_memstatuslimitpercent      = 0;
  checkresourceshardware_totalcpuusagecheckcadence  = 0;                      
  checkresourceshardware_totalcpuusagelimitpercent  = 0;  
  checkresourceshardware_appcpuusageprocessname.Empty();
  checkresourceshardware_appcpuusagecheckcadence    = 0;                      
  checkresourceshardware_appcpuusagelimitpercent    = 0;  
  #endif

  //-----------------------------------------------------------------------------------------------------

  #ifdef APP_CFG_INTERNETSERVICES_ACTIVE
  internetservices_checkinternetstatuscadence       = 0;
  internetservices_donotletinternetconnectionmatter = false;
  internetservices_checkipschangecadence            = 0;
  internetservices_updatetimebyntpcadence           = 0;
  internetservices_nupdatetimentpservers            = 0;
  internetservices_updatetimentpmeridiandifference  = 0;
  internetservices_updatetimentpusedaylightsaving   = false;
  #ifdef APP_CFG_DNSRESOLVER_ACTIVE
  nhostsresolved = 0; 
  nDNSservers    = 0;  
  #endif
  #ifdef APP_CFG_DYNDNSMANAGER_ACTIVE
  dnsmanager_nurls = 0;   
  #endif
  #endif

  //-----------------------------------------------------------------------------------------------------

  #ifdef APP_CFG_DIOLOCATION_ACTIVE
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
  alerts_nconditions                                = 0;
  alerts_SMTP_isactive                              = false;
  alerts_SMTP_port                                  = 0; 
  alerts_SMTP_nrecipients                           = 0;
  alerts_SMS_isactive                               = false;
  alerts_SMS_nrecipients                            = 0;  
  alerts_WEB_isactive                               = false;
  alerts_WEB_isuseget                               = false;
  alerts_WEB_nrecipients                            = 0;
  alerts_UDP_isactive                               = false;
  alerts_UDP_port                                   = 0;
  alerts_UDP_nrecipients                            = 0;
  #endif

  //-----------------------------------------------------------------------------------------------------

  #ifdef APP_CFG_SCRIPTS_ACTIVE
  scripts_nscripts                                  = 0;  
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


#pragma endregion