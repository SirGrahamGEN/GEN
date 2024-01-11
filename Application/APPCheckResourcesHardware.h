/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       APPCheckResourcesHardware.h
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

#ifndef _APPCHECKRESOURCESHARDWARE_H_
#define _APPCHECKRESOURCESHARDWARE_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XString.h"
#include "XObserver.h"
#include "XSubject.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

enum APPCHECKRESOURCESHARDWARE_TASKID
{
  APPCHECKRESOURCESHARDWARE_TASKID_UNKNOWN                   = 0  ,
  APPCHECKRESOURCESHARDWARE_TASKID_CHECKMEMORY                    ,
  APPCHECKRESOURCESHARDWARE_TASKID_TOTALCPUUSAGE                  ,
  APPCHECKRESOURCESHARDWARE_TASKID_APPCPUUSAGE                    ,
};

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

class XSCHEDULER;
class XSCHEDULER_XEVENT;
class XMUTEX;
class APPCFG;

class APPCHECKRESOURCESHARDWARE : public XOBSERVER, public XSUBJECT
{
  public:
                                    APPCHECKRESOURCESHARDWARE       ();
    virtual                        ~APPCHECKRESOURCESHARDWARE       ();

    bool                            Ini                             (APPCFG* cfg);

    int                             GetCPUTotalCPUUsageAverange     ();  
    int                             GetCPUTotalCPUUsageMax          ();  

    int                             GetCPUAppCPUUsageAverange       ();  
    int                             GetCPUAppCPUUsageMax            ();  

    bool                            End                             ();

  private:

    bool                            CheckMemoryStatus               ();

    bool                            CheckTotalCPUUsageStatus        ();
    bool                            CheckAppCPUUsageStatus          ();

    void                            HandleEvent_Scheduler           (XSCHEDULER_XEVENT* xevent);
    void                            HandleEvent                     (XEVENT* xevent);

    void                            Clean                           ();

    APPCFG*                         cfg;

    bool                            inexit;
  //XMUTEX*                         exitmutex;
    XSCHEDULER*                     xscheduler;

    XDWORD                          ntotalCPUusage;
    XDWORD                          ntotalCPUsamples; 
    XDWORD                          maxtotalCPUusage;

    XDWORD                          nappCPUusage;
    XDWORD                          nappCPUsamples;   
    XDWORD                          maxappCPUusage;

};

#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif
