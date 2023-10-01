/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       APPCFG.h
* 
* @class      APPCFG
* @brief      Application Config class
* @ingroup    APPLICATION
*
* @note       if use defines to active for the blocks of the config.
*
*               APP_CFG_REMOTEFILE_ACTIVE        : Active the remote file CFG
*
*             Active the block of CFG
*
*               APP_CFG_GENERAL_ACTIVE           : Default general (debug trace, memory check, etc..
*               APP_CFG_INTERNETSERVICES_ACTIVE  : Inter
*               APP_CFG_LOCATION_ACTIVE          : Location info (street, postal code, etc..)
*               APP_CFG_APPUPDATE_ACTIVE         : Application update
*               APP_CFG_ALERTS_ACTIVE            : Alerts
*               APP_CFG_LOG_ACTIVE               : Log
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

#ifndef _APPCFG_H_
#define _APPCFG_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XTrace.h"
#include "XFileCFG.h"

#ifdef APP_CFG_REMOTEFILE_ACTIVE
#include "DIORemoteFileCFG.h"
#endif

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

#define APP_CFG_DEFAULT_REMARK_COLUMN                                             64


#ifdef APP_CFG_GENERAL_ACTIVE

#define APP_CFG_SECTION_GENERAL                                                   __L("general")
#define APP_CFG_SCRAPERWEBSCRIPTURLDOWNLOAD                                       __L("scraperwebscripturldownload")
#define APP_CFG_SHOWDETAILINFO                                                    __L("showdetailinfo")
#ifdef  XTRACE_ACTIVE
#define APP_CFG_TRACETARGET                                                       __L("trace_target")
#endif

#endif


#ifdef APP_CFG_CHECKRESOURCESHARDWARE_ACTIVE

#define APP_CFG_SECTION_CHECKRESOURCESHARDWARE                                    __L("check resources hardware")
#define APP_CFG_CHECKRESOURCESHARDWARE_MEMSTATUSCHECKCADENCE                      __L("memstatuscheckcadenceseconds")
#define APP_CFG_CHECKRESOURCESHARDWARE_MEMSTATUSLIMITPERCENT                      __L("memstatuslimitpercent")
#define APP_CFG_CHECKRESOURCESHARDWARE_CPUUSAGECHECKCADENCE                       __L("cpuusagecheckcadenceseconds")
#define APP_CFG_CHECKRESOURCESHARDWARE_CPUUSAGELIMITPERCENT                       __L("cpuusagelimitpercent")
#define APP_CFG_CHECKRESOURCESHARDWARE_CPUUSAGEPROCESSNAME                        __L("cpuusageprocessname")

#endif


#ifdef APP_CFG_INTERNETSERVICES_ACTIVE

#define APP_CFG_SECTION_INTERNETSERVICES                                          __L("internet services")
#define APP_CFG_INTERNETSERVICES_CHECKINTERNETSTATUSCADENCE                       __L("checkinternetstatuscadenceseconds")
#define APP_CFG_INTERNETSERVICES_CHECKIPSCHANGECADENCE                            __L("checkipschangecadenceminutes")
#define APP_CFG_INTERNETSERVICES_UPDATETIMEBYNTPCADENCE                           __L("updatetimebyntpcadencehours")
#define APP_CFG_INTERNETSERVICES_UPDATETIMENTPSERVER                              __L("updatetimentpserver")
#define APP_CFG_INTERNETSERVICES_UPDATETIMENTPMERIDIANDIFFERENCE                  __L("updatetimentpmeridiandifference")
#define APP_CFG_INTERNETSERVICES_UPDATETIMENTPUSEDAYLIGHTSAVING                   __L("updatetimentpusedaylightsaving")

#define APP_CFG_INTERNETSERVICES_UPDATETIMENTPMERIDIANDIFFERENCE_AUTO             25


#ifdef APP_CFG_DNSRESOLVED_ACTIVE

#define APP_CFG_SECTION_DNSRESOLVED                                               __L("dns resolved")
#define APP_CFG_DNSRESOLVED_HOSTRESOLVED                                          __L("host_resolved")
#define APP_CFG_DNSRESOLVED_DNSSERVER                                             __L("dns_server")

#endif


#ifdef APP_CFG_DYNDNSMANAGER_ACTIVE

#define APP_CFG_SECTION_DYNDNSMANAGER                                             __L("dyndns manager")
#define APP_CFG_DYNDNSMANAGER_URL                                                 __L("url")

#endif

#endif


#ifdef APP_CFG_LOCATION_ACTIVE

#define APP_CFG_SECTION_LOCATION                                                  __L("location")
#define APP_CFG_CENTERNAME                                                        __L("name")
#define APP_CFG_LOCATION_STREET                                                   __L("street")
#define APP_CFG_LOCATION_TOWN                                                     __L("city")
#define APP_CFG_LOCATION_STATE                                                    __L("state")
#define APP_CFG_LOCATION_COUNTRY                                                  __L("country")
#define APP_CFG_LOCATION_POSTALCODE                                               __L("postalcode")

#endif


#ifdef APP_CFG_APPUPDATE_ACTIVE

#define APP_CFG_SECTION_APPLICATIONUPDATE                                         __L("applicationupdate")
#define APP_CFG_APPLICATIONUPDATE_ISACTIVE                                        __L("isactive")
#define APP_CFG_APPLICATIONUPDATE_URL                                             __L("url")
#define APP_CFG_APPLICATIONUPDATE_PORT                                            __L("port")
#define APP_CFG_APPLICATIONUPDATE_CHECKCADENCE                                    __L("checkcadenceminutes")
#define APP_CFG_APPLICATIONUPDATE_CHECKTIME                                       __L("checktime")
#define APP_CFG_APPLICATIONUPDATE_MAXRESTORATIONS                                 __L("maxrestorations")

#endif


#ifdef APP_CFG_WEBSERVER_ACTIVE

#define APP_CFG_SECTION_WEBSERVER                                                 __L("webserver")
#define APP_CFG_WEBSERVER_LOCALADDR                                               __L("localaddr")
#define APP_CFG_WEBSERVER_PORT                                                    __L("port")
#define APP_CFG_WEBSERVER_TIMEOUTTOSERVERPAGE                                     __L("timeouttoserverpage")
#define APP_CFG_WEBSERVER_AUTHENTICATEDACCESS                                     __L("isauthenticatedaccess")
#define APP_CFG_WEBSERVER_PASSWORD                                                __L("password")
#define APP_CFG_WEBSERVER_PATH_RESOURCES                                          __L("path_resources")
#define APP_CFG_WEBSERVER_PATH_PHP                                                __L("path_php")

#endif


#ifdef APP_CFG_ALERTS_ACTIVE

#define APP_CFG_SECTION_ALERTS                                                    __L("alerts")
#define APP_CFG_ALERTS_ISACTIVE                                                   __L("isactive")
#define APP_CFG_ALERTS_CONDITION                                                  __L("condition")
#define APP_CFG_ALERTS_SMTP_ISACTIVE                                              __L("smtp_isactive")
#define APP_CFG_ALERTS_SMTP_URL                                                   __L("smtp_url")
#define APP_CFG_ALERTS_SMTP_PORT                                                  __L("smtp_port")
#define APP_CFG_ALERTS_SMTP_LOGIN                                                 __L("smtp_login")
#define APP_CFG_ALERTS_SMTP_PASSWORD                                              __L("smtp_password")
#define APP_CFG_ALERTS_SMTP_SENDER                                                __L("smtp_sender")
#define APP_CFG_ALERTS_SMTP_RECIPIENT                                             __L("smtp_recipient")

#define APP_CFG_ALERTS_SMS_ISACTIVE                                               __L("sms_isactive")
#define APP_CFG_ALERTS_SMS_RECIPIENT                                              __L("sms_recipient")

#define APP_CFG_ALERTS_WEB_ISACTIVE                                               __L("web_isactive")
#define APP_CFG_ALERTS_WEB_UISUSEGET                                              __L("web_isuseget")
#define APP_CFG_ALERTS_WEB_RECIPIENT                                              __L("web_recipient")

#define APP_CFG_ALERTS_UDP_ISACTIVE                                               __L("udp_isactive")
#define APP_CFG_ALERTS_UDP_PORT                                                   __L("udp_port")
#define APP_CFG_ALERTS_UDP_RECIPIENT                                              __L("udp_recipient")

#endif


#ifdef APP_CFG_SCRIPTS_ACTIVE

#define APP_CFG_SECTION_SCRIPTS                                                   __L("scriptslist")
#define APP_CFG_SCRIPTS_SCRIPT                                                    __L("scripts")  

#endif


#ifdef APP_CFG_LOG_ACTIVE

#define APP_CFG_SECTION_LOG                                                       __L("log")
#define APP_CFG_LOG_ISACTIVE                                                      __L("isactive")
#define APP_CFG_LOG_BACKUPISACTIVE                                                __L("backupisactive")
#define APP_CFG_LOG_BACKUPMAXFILES                                                __L("backupmaxfiles")
#define APP_CFG_LOG_BACKUPISCOMPRESS                                              __L("backupiscompress")
#define APP_CFG_LOG_ACTIVESECTIONSID                                              __L("activesectionsID")
#define APP_CFG_LOG_LEVELMASK                                                     __L("levelmask")
#define APP_CFG_LOG_MAXSIZE                                                       __L("maxsize")
#define APP_CFG_LOG_REDUCTIONPERCENT                                              __L("reductionpercent")

// ID Sections "generic" of LOG
#define APP_CFG_LOG_SECTIONID_INITIATION                                          __L("Ini")
#define APP_CFG_LOG_SECTIONID_GENERIC                                             __L("General")
#define APP_CFG_LOG_SECTIONID_CONNEXIONS                                          __L("Connexions")
#define APP_CFG_LOG_SECTIONID_STATUSAPP                                           __L("Status")
#define APP_CFG_LOG_SECTIONID_ENDING                                              __L("End")

#endif



#ifdef XTRACE_ACTIVE
  #define   APP_CFG_SETAUTOMATICTRACETARGETS                                      APP_CFG.SetAutomaticTraceTargets();
#else
  #define   APP_CFG_SETAUTOMATICTRACETARGETS             
#endif

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

class XFACTORY;
class XPATHS;
class XSYSTEM;
class XLOG;

class APPCFG
#ifdef APP_CFG_REMOTEFILE_ACTIVE
  : public DIOREMOTEFILECFG
#else
  : public XFILECFG
#endif
{
  public:
                         APPCFG                                                   (XCHAR* namefile);
    virtual             ~APPCFG                                                   ();

    virtual bool         DoVariableMapping                                        (); 
    virtual bool         DoDefault                                                ();

    virtual bool         End                                                      ();  


    #ifdef APP_CFG_GENERAL_ACTIVE
    XSTRING*             GetScraperWebScriptURLDownload                           ();
    XWORD                GetShowDetailInfo                                        ();
    void                 SetShowDetailInfo                                        (XWORD detail);
    #ifdef XTRACE_ACTIVE
    XSTRING*             GetTraceTarget                                           (int index);
    bool                 SetTraceTarget                                           (int index, XSTRING& target);
    bool                 SetAutomaticTraceTargets                                 ();
    bool                 SetDefaultTraceTargets                                   ();
    #endif
    #endif


    #ifdef APP_CFG_CHECKRESOURCESHARDWARE_ACTIVE
    int                  CheckResourcesHardware_GetMemStatusCheckCadence          ();
    int                  CheckResourcesHardware_GetMemStatusLimitPercent          ();

    int                  CheckResourcesHardware_GetCPUUsageCheckCadence           ();
    int                  CheckResourcesHardware_GetCPUUsageLimitPercent           ();
    XSTRING*             CheckResourcesHardware_GetCPUUsageProcessName            ();
    #endif


    #ifdef APP_CFG_INTERNETSERVICES_ACTIVE
    int                  InternetServices_GetCheckInternetStatusCadence           ();
    int                  InternetServices_GetCheckIPsChangeCadence                ();
    int                  InternetServices_GetUpdateTimeByNTPCadence               ();
    XVECTOR<XSTRING*>*   InternetServices_GetUpdateTimeNTPServers                 (); 
    XSTRING*             InternetServices_GetUpdateTimeNTPServer                  (int index);
    int                  InternetServices_GetUpdateTimeNTPMeridianDifference      ();
    bool                 InternetServices_GetUpdateTimeNTPUseDayLightSaving       ();
    #ifdef APP_CFG_DNSRESOLVED_ACTIVE
    bool                 DNSResolved_GetHostResolved                              (int index, XSTRING& host, XSTRING& IPresolved);
    XSTRING*             DNSResolved_GetDNSserver                                 (int index);
    bool                 SetAutomaticDNSResolved                                  ();
    #endif
    #ifdef APP_CFG_DYNDNSMANAGER_ACTIVE
    XVECTOR<XSTRING*>*   DNSManager_GetURLs                                       ();      
    XSTRING*             DNSManager_GetURL                                        (int index);
    #endif
    #endif


    #ifdef APP_CFG_LOCATION_ACTIVE
    XSTRING*             Location_GetStreet                                       ();
    XSTRING*             Location_GetCity                                         ();
    XSTRING*             Location_GetState                                        ();
    XSTRING*             Location_GetCountry                                      ();
    int                  Location_GetPostalCode                                   ();
    #endif


    #ifdef APP_CFG_APPUPDATE_ACTIVE
    bool                 ApplicationUpdate_IsActive                               ();
    int                  ApplicationUpdate_GetPort                                ();
    XSTRING*             ApplicationUpdate_GetURL                                 ();
    int                  ApplicationUpdate_GetCheckCadence                        ();
    XSTRING*             ApplicationUpdate_GetCheckTime                           ();
    int                  ApplicationUpdate_GetMaxRestorations                     ();
    #endif


    #ifdef APP_CFG_ALERTS_ACTIVE
    bool                 Alerts_IsActive                                          ();
    XVECTOR<XSTRING*>*   Alerts_GetConditions                                     ();
    XSTRING*             Alerts_GetCondition                                      (int index);
    bool                 Alerts_GetCondition                                      (int index, XDWORD& conditionID, int& timelimitforrepeat, int& numberoftimesrepeat);
    bool                 Alerts_IsActiveSMTP                                      ();
    XSTRING*             Alerts_GetSMTPURL                                        ();
    int                  Alerts_GetSMTPPort                                       ();
    XSTRING*             Alerts_GetSMTPLogin                                      ();
    XSTRING*             Alerts_GetSMTPPassword                                   ();
    XSTRING*             Alerts_GetSMTPSender                                     ();
    XVECTOR<XSTRING*>*   Alerts_GetSMTPRecipients                                 ();
    XSTRING*             Alerts_GetSMTPRecipient                                  (int index);
    bool                 Alerts_IsActiveSMS                                       ();
    XVECTOR<XSTRING*>*   Alerts_GetSMSRecipients                                  ();
    XSTRING*             Alerts_GetSMSRecipient                                   (int index);
    bool                 Alerts_IsActiveWEB                                       ();
    bool                 Alerts_GetWEBIsUseGet                                    ();
    XVECTOR<XSTRING*>*   Alerts_GetWEBRecipients                                  ();
    XSTRING*             Alerts_GetWEBRecipient                                   (int index);
    bool                 Alerts_IsActiveUDP                                       ();
    int                  Alerts_GetUDPPort                                        ();
    XVECTOR<XSTRING*>*   Alerts_GetUDPRecipients                                  ();
    XSTRING*             Alerts_GetUDPRecipient                                   (int index);
    #endif


    #ifdef APP_CFG_WEBSERVER_ACTIVE
    XSTRING*             WebServer_GetLocalAddress                                ();
    int                  WebServer_GetPort                                        ();
    int                  WebServer_GetTimeoutToServerPage                         ();
    bool                 WebServer_IsAuthenticatedAccess                          ();
    XSTRING*             WebServer_GetPassword                                    ();
    XPATH*               WebServer_PathResources                                  ();
    XPATH*               WebServer_PathPHP                                        ();
    #endif

    #ifdef APP_CFG_SCRIPTS_ACTIVE
    XVECTOR<XSTRING*>*   Scripts_GetAll                                           ();
    XSTRING*             Scripts_GetScript                                        (int index);
    #endif

    #ifdef APP_CFG_LOG_ACTIVE
    bool                 Log_IsActive                                             ();
    bool                 Log_Backup_IsActive                                      ();
    int                  Log_Backup_GetMaxFiles                                   ();
    bool                 Log_Backup_IsCompress                                    ();
    XSTRING*             Log_ActiveSectionsID                                     ();
    XBYTE                Log_LevelMask                                            ();
    int                  Log_MaxSize                                              ();
    int                  Log_ReductionPercent                                     ();
    #endif

  protected:


    #ifdef APP_CFG_GENERAL_ACTIVE
    XSTRING              scraperwebscripturldownload;
    XSTRING              showdetailinfo;
    #ifdef XTRACE_ACTIVE
    int                  ntracetargets;
    XVECTOR<XSTRING*>    tracetargets;
    #endif
    #endif


    #ifdef APP_CFG_CHECKRESOURCESHARDWARE_ACTIVE
    int                  checkresourceshardware_memstatuscheckcadence;
    int                  checkresourceshardware_memstatuslimitpercent;
    int                  checkresourceshardware_cpuusagecheckcadence;
    int                  checkresourceshardware_cpuusagelimitpercent;
    XSTRING              checkresourceshardware_cpuusageprocessname; 
    #endif


    #ifdef APP_CFG_INTERNETSERVICES_ACTIVE
    int                  internetservices_checkinternetstatuscadence;
    int                  internetservices_checkipschangecadence;
    int                  internetservices_updatetimebyntpcadence;
    int                  internetservices_nupdatetimentpservers;
    XVECTOR<XSTRING*>    internetservices_updatetimentpservers;    
    int                  internetservices_updatetimentpmeridiandifference;
    bool                 internetservices_updatetimentpusedaylightsaving;
    #ifdef APP_CFG_DNSRESOLVED_ACTIVE
    int                  nhostsresolved; 
    XVECTOR<XSTRING*>    hostsresolved;
    int                  nDNSservers;
    XVECTOR<XSTRING*>    DNSservers;
    #endif
    #ifdef APP_CFG_DYNDNSMANAGER_ACTIVE
    int                  dnsmanager_nurls;
    XVECTOR<XSTRING*>    dnsmanager_urls;      
    #endif
    #endif


    #ifdef APP_CFG_LOCATION_ACTIVE
    XSTRING              location_street;
    XSTRING              location_city;
    XSTRING              location_state;
    XSTRING              location_country;
    int                  location_postalcode;
    #endif


    #ifdef APP_CFG_APPUPDATE_ACTIVE
    bool                 applicationupdate_isactive;
    XSTRING              applicationupdate_URL;
    int                  applicationupdate_port;
    int                  applicationupdate_checkcadence;
    XSTRING              applicationupdate_checktime;
    int                  applicationupdate_maxrestorations;
    #endif


    #ifdef APP_CFG_WEBSERVER_ACTIVE
    XSTRING              webserver_localaddr;
    int                  webserver_port;
    int                  webserver_timeouttoserverpage;
    bool                 webserver_isauthenticatedaccess;
    XSTRING              webserver_password;
    XPATH                webserver_path_resources;
    XPATH                webserver_path_PHP;
    #endif


    #ifdef APP_CFG_ALERTS_ACTIVE
    bool                 alerts_isactive;
    int                  alerts_nconditions;
    XVECTOR<XSTRING*>    alerts_conditions;
    bool                 alerts_SMTP_isactive;
    XSTRING              alerts_SMTP_URL;
    int                  alerts_SMTP_port;
    XSTRING              alerts_SMTP_login;
    XSTRING              alerts_SMTP_password;
    XSTRING              alerts_SMTP_sender;
    int                  alerts_SMTP_nrecipients;
    XVECTOR<XSTRING*>    alerts_SMTP_recipients;
    bool                 alerts_SMS_isactive;
    int                  alerts_SMS_nrecipients;
    XVECTOR<XSTRING*>    alerts_SMS_recipients;
    bool                 alerts_WEB_isactive;
    bool                 alerts_WEB_isuseget;
    int                  alerts_WEB_nrecipients;
    XVECTOR<XSTRING*>    alerts_WEB_recipients;
    bool                 alerts_UDP_isactive;
    int                  alerts_UDP_port;
    int                  alerts_UDP_nrecipients;
    XVECTOR<XSTRING*>    alerts_UDP_recipients;
    #endif


    #ifdef APP_CFG_SCRIPTS_ACTIVE
    int                  scripts_nscripts;
    XVECTOR<XSTRING*>    scripts_list;
    #endif


    #ifdef APP_CFG_LOG_ACTIVE
    bool                 log_isactive;
    bool                 log_backupisactive;
    int                  log_backupmaxfiles;
    bool                 log_backupiscompress;
    XSTRING              log_activesectionsID;
    int                  log_levelmask;
    int                  log_maxsize;
    int                  log_reductionpercent;
    #endif

  private:

    void                 Clean                                                    ();
};

#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

