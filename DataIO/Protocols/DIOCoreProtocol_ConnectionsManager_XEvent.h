/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOCoreProtocol_ConnectionsManager_XEvent.h
* 
* @class      DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT
* @brief      Data Input/Output Core Protocol Connections Manager eXtended Event class
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

#ifndef _DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_H_
#define _DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XEvent.h"

#include "DIOCoreProtocol.h"
#include "DIOCoreProtocol_Connection.h"
#include "DIOCoreProtocol_ConnectionsManager.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


enum DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE
{
  DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_UNKNOWN         = XEVENT_TYPE_COREPROTOCOLCONNECTIONSMANAGER ,
  DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_CHANGESTATUS                                                 ,  
  DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_READMSG                                                      ,
  DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_WRITEMSG
};


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT : public XEVENT
{
  public:
                                              DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT       (XSUBJECT* subject, XDWORD type = DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_UNKNOWN, XDWORD family = XEVENT_TYPE_COREPROTOCOLCONNECTIONSMANAGER);
    virtual                                  ~DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT       ();

    DIOCOREPROTOCOL_CONNECTION*               GetConnection                                   ();
    bool                                      SetConnection                                   (DIOCOREPROTOCOL_CONNECTION* connection);

    DIOCOREPROTOCOL_CONNECTION_STATUS         GetActualStatus                                 ();  
    void                                      SetActualStatus                                 (DIOCOREPROTOCOL_CONNECTION_STATUS actualstatus);  

    DIOCOREPROTOCOL_CONNECTION_STATUS         GetNextStatus                                   ();  
    void                                      SetNextStatus                                   (DIOCOREPROTOCOL_CONNECTION_STATUS nextstatus);  

    DIOCOREPROTOCOL_MESSAGE*                  GetMsg                                          ();
    void                                      SetMsg                                          (DIOCOREPROTOCOL_MESSAGE* message);
          
  private:

    void                                      Clean                                           ();

    DIOCOREPROTOCOL_CONNECTION*               connection;
    DIOCOREPROTOCOL_CONNECTION_STATUS         actualstatus;  
    DIOCOREPROTOCOL_CONNECTION_STATUS         nextstatus; 
    DIOCOREPROTOCOL_MESSAGE*                  message;
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

