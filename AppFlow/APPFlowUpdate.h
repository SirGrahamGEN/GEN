/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       APPFlowUpdate.h
* 
* @class      APPFLOWUPDATE
* @brief      Application Flow Update class
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

#ifndef _APPFLOWUPDATE_H_
#define _APPFLOWUPDATE_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XPath.h"
#include "XObserver.h"
#include "XSubject.h"
#include "XString.h"

#include "DIOURL.h"
#include "DIOApplicationUpdate_XEvent.h"
#include "DIOApplicationUpdate.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

enum APPFLOWUPDATE_TASKID
{
  APPFLOWUPDATE_TASKID_UNKNOWN                      = 0 ,
  APPFLOWUPDATE_TASKID_CHECKUPDATEAPPLICATION           ,
};

enum APPFLOWUPDATE_EVENTOPERATION
{
  APPFLOWUPDATE_EVENTOPERATION_NONE                 = 0 ,
  APPFLOWUPDATE_EVENTOPERATION_REGISTER                 ,
  APPFLOWUPDATE_EVENTOPERATION_DEREGISTER               ,
  APPFLOWUPDATE_EVENTOPERATION_SUBSCRIBE                ,
  APPFLOWUPDATE_EVENTOPERATION_UNSUBSCRIBE              ,
};

#define APPFLOW_UPDATE   APPFLOWUPDATE::GetInstance()

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

class XEVENT;
class XSCHEDULER;
class XSCHEDULER_XEVENT;
class DIOAPPLICATIONUPDATE_XEVENT;
class APPFLOWCFG;

class APPFLOWUPDATE_CFG
{
  public:

                                        APPFLOWUPDATE_CFG               ();
    virtual                            ~APPFLOWUPDATE_CFG               ();

    DIOURL*                             GetURL                          ();

    XDWORD                              Get_Port                        ();
    void                                Set_Port                        (XDWORD port);

    DIOAPPLICATIONUPDATE_VERSIONDATA*   GetAppVersion                   ();

    XSTRING*                            GetAppName                      ();
    XPATH*                              GetPathRootApp                  ();

    bool                                GetDolog                        ();
    void                                SetDolog                        (bool dolog);

    bool                                CopyFrom                        (APPFLOWUPDATE_CFG* updatecfg);
    bool                                CopyTo                          (APPFLOWUPDATE_CFG* updatecfg);

  private:

    void                                Clean                           ();

    DIOURL                              URL;
    XDWORD                              port;
    DIOAPPLICATIONUPDATE_VERSIONDATA    appversion;
    XSTRING                             appname;
    XPATH                               xpathrootapp;
    bool                                dolog;
};


class APPFLOWUPDATE : public XOBSERVER, public XSUBJECT
{
  public:

    static bool                         GetIsInstanced                  ();
    static APPFLOWUPDATE&               GetInstance                     ();
    static bool                         DelInstance                     ();

    bool                                Ini                             (APPFLOWCFG* cfg, APPFLOWUPDATE_CFG* appcfg);

    bool                                EventManager                    (APPFLOWUPDATE_EVENTOPERATION eventoperation, XSUBJECT* xsubject = NULL, XOBSERVER* observer = NULL);

    bool                                Do                              ();

    bool                                RestorePrevious                 ();
    bool                                Restore                         (DIOAPPLICATIONUPDATE_VERSIONDATA& applicationversiondata);

    bool                                End                             ();

    bool                                LogOfEvent                      (DIOAPPLICATIONUPDATE_XEVENT* event);
    DIOAPPLICATIONUPDATE*               GetDIOAPPFlowUpdate             ();

  private:
                                        APPFLOWUPDATE                   ();
                                        APPFLOWUPDATE                   (APPFLOWUPDATE const&);        // Don't implement
    virtual                            ~APPFLOWUPDATE                   ();

    void                                operator =                      (APPFLOWUPDATE const&);        // Don't implement

    bool                                CreateTaskUpdate                (bool doajust = true);

    void                                HandleEvent_Scheduler           (XSCHEDULER_XEVENT* event);
    void                                HandleEvent_ApplicationUpdate   (DIOAPPLICATIONUPDATE_XEVENT* event);
    void                                HandleEvent                     (XEVENT* xevent);

    void                                Clean                           ();

    static APPFLOWUPDATE*               instance;

    XSCHEDULER*                         xscheduler;
    DIOAPPLICATIONUPDATE*               dioappupdate;

    APPFLOWCFG*                         cfg;
    APPFLOWUPDATE_CFG                   update_cfg;
    
};

#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

