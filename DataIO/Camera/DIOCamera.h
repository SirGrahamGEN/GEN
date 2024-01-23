/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOCamera.h
* 
* @class      DIOCAMERA
* @brief      Data Input/Output Camera class
* @ingroup    DATAIO
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

#ifndef _DIOCAMERA_H_
#define _DIOCAMERA_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XObserver.h"
#include "XSubject.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


enum DIOCAMERA_TASKID
{
  DIOCAMERA_TASKID_UNKNOWN                      = 0 ,
  DIOCAMERA_TASKID_GETIMAGE                         ,  
};


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class XSCHEDULER;
class XSCHEDULER_XEVENT;


class DIOCAMERA : public XOBSERVER, public XSUBJECT
{
  public:
                            DIOCAMERA         ();
    virtual                ~DIOCAMERA         ();

    bool                    Ini               ();  
    bool                    End               ();  

  private:

    void                    HandleEvent_Scheduler           (XSCHEDULER_XEVENT* xevent);
    void                    HandleEvent                     (XEVENT* xevent);

    void                    Clean             ();

    XSCHEDULER*             xscheduler;
};

#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif



