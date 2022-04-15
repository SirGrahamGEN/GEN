/**-------------------------------------------------------------------------------------------------------------------
*
* @file       APPInternetServices_XEvent.h
*
* @class      APPINTERNETSERVICES_XEVENT
* @brief      Application Internet Services eXtended Event class
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


#ifndef _APPINTERNETSERVICES_XEVENT_H_
#define _APPINTERNETSERVICES_XEVENT_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XEvent.h"
#include "XSubject.h"


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/


enum APPINTERNETSERVICES_XEVENT_TYPE
{
  APPINTERNETSERVICES_XEVENT_TYPE_UNKNOWN                           = XEVENT_TYPE_APPLICATIONINTERNETSERVICES ,
  APPINTERNETSERVICES_XEVENT_TYPE_CHECKINTERNETCONNEXION                                                      ,
  APPINTERNETSERVICES_XEVENT_TYPE_CHANGEIP                                                                    , 
  APPINTERNETSERVICES_XEVENT_TYPE_ADJUSTDATETIME                                                    
};


enum APPINTERNETSERVICES_CHECKINTERNETCONNEXION_STATE
{ 
  APPINTERNETSERVICES_CHECKINTERNETCONNEXION_STATE_NONE              = 0                                       ,
  APPINTERNETSERVICES_CHECKINTERNETCONNEXION_STATE_CHECKING                                                    ,
  APPINTERNETSERVICES_CHECKINTERNETCONNEXION_STATE_CHECKED                                                     ,  
  APPINTERNETSERVICES_CHECKINTERNETCONNEXION_STATE_CUT                                                         ,      
  APPINTERNETSERVICES_CHECKINTERNETCONNEXION_STATE_RESTORE                                                     ,        
};


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XTIMER;
class XPUBLISHER;
class DIOCHECKTCPIPCONNECTION_CUT;


class APPINTERNETSERVICES_XEVENT : public XEVENT
{
  public:
                                                        APPINTERNETSERVICES_XEVENT             (XSUBJECT* subject, XDWORD type = APPINTERNETSERVICES_XEVENT_TYPE_UNKNOWN, XDWORD family = XEVENT_TYPE_APPLICATIONINTERNETSERVICES);
    virtual                                            ~APPINTERNETSERVICES_XEVENT             ();

    APPINTERNETSERVICES_CHECKINTERNETCONNEXION_STATE    GetInternetConnexionState              ();
    void                                                SetInternetConnexionState              (APPINTERNETSERVICES_CHECKINTERNETCONNEXION_STATE internetconnexionstate);

    DIOCHECKTCPIPCONNECTION_CUT*                        GetInternetConnextionCut               ();
    void                                                SetInternetConnextionCut               (DIOCHECKTCPIPCONNECTION_CUT* internetconnectioncut);

    bool                                                IsChangeLocalIP                        ();     
    void                                                SetIsChangeLocalIP                     (bool ischangelocalIP);     

    XSTRING*                                            GetChangeIP                            ();     

    
  private:

    void                                                Clean                                  ();  

    APPINTERNETSERVICES_CHECKINTERNETCONNEXION_STATE    internetconnexionstate;
    DIOCHECKTCPIPCONNECTION_CUT*                        internetconnectioncut;

    bool                                                ischangelocalIP;
    XSTRING                                             changeIP;     
};


/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/



#endif


