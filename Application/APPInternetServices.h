/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       APPInternetServices.h
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

#ifndef _APPINTERNETSERVICES_H_
#define _APPINTERNETSERVICES_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XString.h"
#include "XObserver.h"
#include "XSubject.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

enum APPINTERNETSERVICES_TASKID
{
  APPINTERNETSERVICES_TASKID_UNKNOWN                      = 0 ,
  APPINTERNETSERVICES_TASKID_CHECKCONNECTIONINTERNET          ,
  APPINTERNETSERVICES_TASKID_GETIPS                           ,  
  APPINTERNETSERVICES_TASKID_CHECKNTPDATETIME                 ,
};

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

class XSCHEDULER;
class XSCHEDULER_XEVENT;
class XDATETIME;
class DIOCHECKTCPIPCONNECTIONS;
class DIOCHECKINTERNETCONNECTION;
class DIOSCRAPERWEBPUBLICIP;
class DIONTP;
class DIODYNDNS_MANAGER;
class APPCFG;
class XMUTEX;

class APPINTERNETSERVICES : public XOBSERVER, public XSUBJECT
{
  public:
                                    APPINTERNETSERVICES             ();
    virtual                        ~APPINTERNETSERVICES             ();

    bool                            Ini                             (APPCFG* cfg, XDWORD timeoutgetpublicip = 0);

    bool                            HaveInternetConnection          ();

    XSTRING*                        GetAutomaticLocalIP             ();
    XSTRING*                        GetAllLocalIP                   ();
    XSTRING*                        GetPublicIP                     ();

    bool                            ChangeCadenceCheckInternet      (bool faster);
    bool                            ForceCheckIPs                   ();
    bool                            DeactiveCheckIPs                ();

    XDATETIME*                      DateTime_GetLocal               (bool active_daylightsave =  true, bool active_meridian = true);
    XDATETIME*                      DateTime_GetUTC                 ();
    int                             DateTime_GetMeridian            ();
    

    DIOCHECKTCPIPCONNECTIONS*       GetCheckTCPIPConnections        ();
    DIOCHECKINTERNETCONNECTION*     GetCheckInternetConnection      ();
    DIODYNDNS_MANAGER*              GetDynDNSManager                ();

    XSCHEDULER*                     GetXScheduler                   ();

    bool                            End                             ();

  private:

    bool                            CheckInternetConnection         ();
    bool                            CheckInternetStatus             ();
    
    bool                            UpdateIPs                       (XSTRING& actualpublicIP);
    bool                            UpdateDynDNSURLs                (XSTRING& actualpublicIP);
    bool                            AdjustTimerByNTP                (XVECTOR<XSTRING*>* servers);

    void                            HandleEvent_Scheduler           (XSCHEDULER_XEVENT* xevent);
    void                            HandleEvent                     (XEVENT* xevent);

    void                            Clean                           ();

    APPCFG*                         cfg;

    XSCHEDULER*                     xscheduler;

    XSTRING                         automaticlocalIP;
    XSTRING                         alllocalIP;
    
    DIOCHECKINTERNETCONNECTION*     checkinternetconnection;

    bool                            haveinternetconnection;

    bool                            endservices;

    DIOSCRAPERWEBPUBLICIP*          scraperwebpublicIP;
    XSTRING                         publicIP;

    XVECTOR<XSTRING*>               NTPservers;

    XMUTEX*                         xmutex_datetime_local;
    XDATETIME*                      xdatetime_local;

    XMUTEX*                         xmutex_datetime_UTC;
    XDATETIME*                      xdatetime_UTC;

    DIODYNDNS_MANAGER*              dyndnsmanager;
};

#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

