/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOCoreProtocol_Connection.h
* 
* @class      DIOCOREPROTOCOL_CONNECTION
* @brief      Data Input/Output Core Protocol Connection class
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

#ifndef _DIOCOREPROTOCOL_CONNECTION_H_
#define _DIOCOREPROTOCOL_CONNECTION_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES


enum DIOCOREPROTOCOL_CONNECTION_XFSMEVENTS
{
  DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_NONE                 = 0 ,
  DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_CONNECTED                ,
  DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_KEYEXCHANGE              ,
  DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_AUTHENTICATION           ,
  DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_REGISTRATION             ,  
  DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_READY                    ,
  DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_INSTABILITY              ,
  DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_DISCONNECTED             ,

  DIOCOREPROTOCOL_CONNECTION_LASTEVENT
};


enum DIOCOREPROTOCOL_CONNECTION_XFSMSTATES
{
  DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_NONE                 = 0 ,
  DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_CONNECTED                ,
  DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_KEYEXCHANGE              ,
  DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_AUTHENTICATION           , 
  DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_REGISTRATION             ,  
  DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_READY                    , 
  DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_INSTABILITY              ,  
  DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_DISCONNECTED             ,

  DIOCOREPROTOCOL_CONNECTION_LASTSTATE
};


enum DIOCOREPROTOCOL_CONNECTION_STATUS
{
  DIOCOREPROTOCOL_CONNECTION_STATUS_NONE                    = 0 , 
  DIOCOREPROTOCOL_CONNECTION_STATUS_CONNECTED                   , 
  DIOCOREPROTOCOL_CONNECTION_STATUS_KEYEXCHANGE                 , 
  DIOCOREPROTOCOL_CONNECTION_STATUS_AUTHENTICATED               ,   
  DIOCOREPROTOCOL_CONNECTION_STATUS_REGISTERED                  ,   
  DIOCOREPROTOCOL_CONNECTION_STATUS_READY                       ,
  DIOCOREPROTOCOL_CONNECTION_STATUS_INSTABILITY                 ,
  DIOCOREPROTOCOL_CONNECTION_STATUS_DISCONNECTED                ,
};

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

#include "XFSMachine.h"

#include "CipherKey.h"
#include "CipherAES.h"
#include "CipherCurve25519.h"


#include "DIOCoreProtocol_Messages.h"
#include "DIOCoreProtocol_RegisterData.h"

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class DIOCOREPROTOCOL_CFG;
class DIOCOREPROTOCOL;


class DIOCOREPROTOCOL_CONNECTION : public XFSMACHINE, public XSUBJECT
{
  public:
                                          DIOCOREPROTOCOL_CONNECTION            ();
    virtual                              ~DIOCOREPROTOCOL_CONNECTION            ();

    bool                                  InitFSMachine                         (); 
    
    bool                                  IsServer                              ();

    XUUID*                                GetIDConnection                       ();
    
    DIOCOREPROTOCOL*                      GetCoreProtocol                       ();
    bool                                  SetCoreProtocol                       (DIOCOREPROTOCOL* protocol);

    XBUFFER*                              GetAuthenticationChallenge            ();
    XBUFFER*                              GetAuthenticationResponse             ();

    CIPHERKEYSYMMETRICAL*                 GetCipherKey                          ();

    DIOCOREPROTOCOL_CONNECTION_STATUS     Status_Get                            ();  
    void                                  Status_Set                            (DIOCOREPROTOCOL_CONNECTION_STATUS status);
    bool                                  Status_GetString                      (DIOCOREPROTOCOL_CONNECTION_STATUS status, XSTRING& statusstring);
    bool                                  Status_GetString                      (XSTRING& statusstring); 

    XTIMER*                               GetXTimerStatus                       ();
    XTIMER*                               GetXTimerWithoutConnexion             ();
       
    DIOCOREPROTOCOL_MESSAGES*             Messages_GetAll                       ();
    
    bool                                  DoCommand                             (XUUID* ID_message, XBYTE message_priority, XDWORD command_type);
    bool                                  DoCommand                             (XUUID* ID_message, XBYTE message_priority, XDWORD command_type, XBUFFER* params);
    bool                                  DoCommand                             (XUUID* ID_message, XBYTE message_priority, XDWORD command_type, XSTRING* params);
    bool                                  DoCommand                             (XUUID* ID_message, XBYTE message_priority, XDWORD command_type, XFILEJSON* params);

    bool                                  DoUpdateClass                         (XUUID* ID_message, XBYTE message_priority, XCHAR* classname, XFILEJSON* classcontent = NULL); 
    bool                                  DoAskUpdateClass                      (XUUID* ID_message, XBYTE message_priority, XCHAR* classname, XSTRING* classcontent = NULL);
    
    bool                                  Update                                ();  

    XDWORD                                GetHeartBetsCounter                   ();
    void                                  SetHeartBetsCounter                   (XDWORD heartbetscounter = 0);

    DIOCOREPROTOCOL_REGISTERDATA*         GetRegisterData                       ();
    void                                  SetRegisterData                       (DIOCOREPROTOCOL_REGISTERDATA* registerdata);

  private:

    bool                                  CreateIDConnection                    (XUUID& ID);

    bool                                  SendMsg                               (XUUID* ID_message, XBYTE message_priority, DIOCOREPROTOCOL_HEADER_OPERATION operation, XCHAR* operation_param);
    bool                                  SendMsg                               (XUUID* ID_message, XBYTE message_priority, DIOCOREPROTOCOL_HEADER_OPERATION operation, XCHAR* operation_param, XBUFFER* content);
    bool                                  SendMsg                               (XUUID* ID_message, XBYTE message_priority, DIOCOREPROTOCOL_HEADER_OPERATION operation, XCHAR* operation_param, XSTRING* content);
    bool                                  SendMsg                               (XUUID* ID_message, XBYTE message_priority, DIOCOREPROTOCOL_HEADER_OPERATION operation, XCHAR* operation_param, XFILEJSON* content);   

    bool                                  GetMsg                                (bool isrequest, DIOCOREPROTOCOL_HEADER_OPERATION operation, XCHAR* operation_param, DIOCOREPROTOCOL_HEADER& header, XBUFFER& content);
    bool                                  GetMsg                                (bool isrequest, DIOCOREPROTOCOL_HEADER_OPERATION operation, XCHAR* operation_param, DIOCOREPROTOCOL_HEADER& header, XSTRING& content);
    bool                                  GetMsg                                (bool isrequest, DIOCOREPROTOCOL_HEADER_OPERATION operation, XCHAR* operation_param, DIOCOREPROTOCOL_HEADER& header, XFILEJSON& content);

    void                                  Clean                                 ();    
    
    DIOCOREPROTOCOL*                      protocol;   

    XUUID                                 ID_connection;

    XBUFFER                               authentication_challenge;  
    XBUFFER                               authentication_response;
    CIPHERCURVE25519                      ciphercurve;
    CIPHERKEYSYMMETRICAL                  cipherkey;     

    DIOCOREPROTOCOL_CONNECTION_STATUS     status;
    XTIMER*                               xtimerstatus;  
    XTIMER*                               xtimerwithoutconnexion;  
    XDWORD                                heartbetscounter;

    DIOCOREPROTOCOL_MESSAGES              messages; 

    DIOCOREPROTOCOL_REGISTERDATA*         registerdata;
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif



