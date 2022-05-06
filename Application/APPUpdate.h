/**-------------------------------------------------------------------------------------------------------------------
*
* @file       APPUpdate.h
*
* @class      APPUPDATE
* @brief      Application Update class
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

#ifndef _APPUPDATE_H_
#define _APPUPDATE_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XPath.h"
#include "XObserver.h"
#include "XSubject.h"
#include "XString.h"

#include "DIOURL.h"
#include "DIOApplicationUpdate_XEvent.h"
#include "DIOApplicationUpdate.h"


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum APPUPDATE_TASKID
{
  APPUPDATE_TASKID_UNKNOWN                      = 0 ,
  APPUPDATE_TASKID_CHECKUPDATEAPPLICATION           ,
};


enum APPUPDATE_EVENTOPERATION
{
  APPUPDATE_EVENTOPERATION_NONE                 = 0 ,
  APPUPDATE_EVENTOPERATION_REGISTER                 ,
  APPUPDATE_EVENTOPERATION_DEREGISTER               ,
  APPUPDATE_EVENTOPERATION_SUBSCRIBE                ,
  APPUPDATE_EVENTOPERATION_UNSUBSCRIBE              ,
};


#define APP_UPDATE   APPUPDATE::GetInstance()

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XEVENT;
class XSCHEDULER;
class XSCHEDULER_XEVENT;
class DIOAPPLICATIONUPDATE_XEVENT;
class APPCFG;

class APPUPDATE_CFG
{
  public:

                                        APPUPDATE_CFG                   ();
    virtual                            ~APPUPDATE_CFG                   ();

    DIOURL*                             GetURL                          ();

    XDWORD                              Get_Port                        ();
    void                                Set_Port                        (XDWORD port);

    DIOAPPLICATIONUPDATE_VERSIONDATA*   GetAppVersion                   ();

    XSTRING*                            GetAppName                      ();
    XPATH*                              GetPathRootApp                  ();

    bool                                GetDolog                        ();
    void                                SetDolog                        (bool dolog);

    bool                                CopyFrom                        (APPUPDATE_CFG* updatecfg);
    bool                                CopyTo                          (APPUPDATE_CFG* updatecfg);

  private:

    void                                Clean                           ();

    DIOURL                              URL;
    XDWORD                              port;
    DIOAPPLICATIONUPDATE_VERSIONDATA    appversion;
    XSTRING                             appname;
    XPATH                               xpathrootapp;
    bool                                dolog;
};


class APPUPDATE : public XOBSERVER, public XSUBJECT
{
  public:

    static bool                         GetIsInstanced                  ();
    static APPUPDATE&                   GetInstance                     ();
    static bool                         DelInstance                     ();

    bool                                Ini                             (APPCFG* cfg, APPUPDATE_CFG* appcfg);

    bool                                EventManager                    (APPUPDATE_EVENTOPERATION eventoperation, XSUBJECT* xsubject = NULL, XOBSERVER* observer = NULL);

    bool                                Do                              ();

    bool                                RestorePrevious                 ();
    bool                                Restore                         (DIOAPPLICATIONUPDATE_VERSIONDATA& applicationversiondata);

    bool                                End                             ();

    bool                                LogOfEvent                      (DIOAPPLICATIONUPDATE_XEVENT* event);
    DIOAPPLICATIONUPDATE*               GetDIOAPPUpdate                 ();

  private:
                                        APPUPDATE                       ();
                                        APPUPDATE                       (APPUPDATE const&);        // Don't implement
    virtual                            ~APPUPDATE                       ();

    void                                operator =                      (APPUPDATE const&);        // Don't implement

    bool                                CreateTaskUpdate                (bool doajust = true);

    void                                HandleEvent_Scheduler           (XSCHEDULER_XEVENT* event);
    void                                HandleEvent_ApplicationUpdate   (DIOAPPLICATIONUPDATE_XEVENT* event);
    void                                HandleEvent                     (XEVENT* xevent);

    void                                Clean                           ();

    static APPUPDATE*                   instance;

    XSCHEDULER*                         xscheduler;
    DIOAPPLICATIONUPDATE*               dioappupdate;

    APPCFG*                             app_cfg;
    APPUPDATE_CFG                       update_cfg;
    
};

/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif


