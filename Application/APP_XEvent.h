/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       APP_XEvent.h
* 
* @class      APP_XEVENT
* @brief      Application eXtended Event class
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

#ifndef _APP_XEVENT_H_
#define _APP_XEVENT_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XEvent.h"
#include "XSubject.h"
#include "XSystem.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

enum APP_XEVENT_TYPE
{
  APP_XEVENT_TYPE_UNKNOWN              = XEVENT_TYPE_APPLICATION  ,
  APP_XEVENT_TYPE_CHANGESTATUSTYPE                                                      
};

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

class XTIMER;
class XPUBLISHER;

class APP_XEVENT : public XEVENT
{
  public:
                                  APP_XEVENT              (XSUBJECT* subject, XDWORD type = APP_XEVENT_TYPE_UNKNOWN, XDWORD family = XEVENT_TYPE_APPLICATION);
    virtual                      ~APP_XEVENT              ();

    XSYSTEM_CHANGESTATUSTYPE      GetChangeStatusType     ();
    void                          SetChangeStatusType     (XSYSTEM_CHANGESTATUSTYPE systemchangestatustype);

  private:

    void                          Clean                   ();
    
    XSYSTEM_CHANGESTATUSTYPE      changestatustype;
};

#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

