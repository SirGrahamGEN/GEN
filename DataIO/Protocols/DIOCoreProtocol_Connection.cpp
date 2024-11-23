/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOCoreProtocol_Connection.cpp
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIOCoreProtocol_Connection.h"

#include "XFactory.h"
#include "XTimer.h"
#include "XThreadCollected.h"

#include "DIOStream.h"
#include "DIOStreamEnumServers.h"

#include "DIOCoreProtocol_Header.h"
#include "DIOCoreProtocol.h"
#include "DIOCoreProtocol_CFG.h"
#include "DIOCoreProtocol_ConnectionsManager_XEvent.h"

#include "XMemory_Control.h"


#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#pragma region CLASS_DIOCOREPROTOCOL_CONNECTION


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_CONNECTION::DIOCOREPROTOCOL_CONNECTION()
* @brief      Constructor
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_CONNECTION::DIOCOREPROTOCOL_CONNECTION() : XFSMACHINE(0)
{
  Clean();

  xtimerstatus            = GEN_XFACTORY.CreateTimer();
  xtimerwithoutconnexion  = GEN_XFACTORY.CreateTimer();

  InitFSMachine();

  ciphercurve.GenerateRandomPrivateKey();
  ciphercurve.CreatePublicKey();

  RegisterEvent(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_CHANGESTATUS);
  RegisterEvent(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_WRITEMSG);

  SetEvent(DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_CONNECTED); 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_CONNECTION::~DIOCOREPROTOCOL_CONNECTION()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_CONNECTION::~DIOCOREPROTOCOL_CONNECTION()
{
  DeRegisterEvent(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_CHANGESTATUS);
  RegisterEvent(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_WRITEMSG);

  if(protocol)
    {
      delete protocol;
    }

  if(xtimerstatus)
    {
      GEN_XFACTORY.DeleteTimer(xtimerstatus);
    }

  if(xtimerwithoutconnexion)
    {
      GEN_XFACTORY.DeleteTimer(xtimerwithoutconnexion);
    }

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool NETCONN::InitFSMachine()
* @brief      InitFSMachine
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTION::InitFSMachine()
{
  if(!AddState( DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_NONE               ,
                DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_CONNECTED          ,  DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_CONNECTED           ,
                DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_DISCONNECTED       ,  DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_DISCONNECTED        ,                
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  if(!AddState( DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_CONNECTED          ,
                DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_AUTHENTICATION     ,  DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_AUTHENTICATION      ,
                DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_DISCONNECTED       ,  DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_DISCONNECTED        ,                
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  if(!AddState( DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_AUTHENTICATION     ,
                DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_KEYEXCHANGE        ,  DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_KEYEXCHANGE         ,
                DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_DISCONNECTED       ,  DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_DISCONNECTED        ,                
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  if(!AddState( DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_KEYEXCHANGE        ,
                DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_READY              ,  DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_READY               ,
                DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_DISCONNECTED       ,  DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_DISCONNECTED        ,                
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  if(!AddState( DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_READY              ,
                DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_DISCONNECTED       ,  DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_DISCONNECTED        ,                
                XFSMACHINESTATE_EVENTDEFEND)) return false;
  
  if(!AddState( DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_DISCONNECTED       ,
                DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_NONE               ,  DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_NONE                ,                
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTION::IsServer()
* @brief      IsServer
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTION::IsServer()
{
  if(!protocol)
    {
      return false;
    }

  if(!protocol->GetProtocolCFG())
    {
      return false;
    }

  return protocol->GetProtocolCFG()->GetIsServer();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL* DIOCOREPROTOCOL_CONNECTION::GetCoreProtocol()
* @brief      GetCoreProtocol
* @ingroup    DATAIO
* 
* @return     DIOCOREPROTOCOL* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL* DIOCOREPROTOCOL_CONNECTION::GetCoreProtocol()
{
  return protocol;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTION::SetCoreProtocol(DIOCOREPROTOCOL* protocol)
* @brief      SetCoreProtocol
* @ingroup    DATAIO
* 
* @param[in]  protocol : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTION::SetCoreProtocol(DIOCOREPROTOCOL* protocol)
{
  this->protocol = protocol;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBUFFER* DIOCOREPROTOCOL_CONNECTION::GetAuthenticationChallenge()
* @brief      GetAuthenticationChallenge
* @ingroup    DATAIO
* 
* @return     XBUFFER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBUFFER* DIOCOREPROTOCOL_CONNECTION::GetAuthenticationChallenge()
{
  return &authentication_challenge;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBUFFER* DIOCOREPROTOCOL_CONNECTION::GetAuthenticationResponse()
* @brief      GetAuthenticationResponse
* @ingroup    DATAIO
* 
* @return     XBUFFER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBUFFER* DIOCOREPROTOCOL_CONNECTION::GetAuthenticationResponse()
{
  return &authentication_response;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         CIPHERKEYSYMMETRICAL* DIOCOREPROTOCOL_CONNECTION::GetCipherKey()
* @brief      GetCipherKey
* @ingroup    DATAIO
* 
* @return     CIPHERKEYSYMMETRICAL* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
CIPHERKEYSYMMETRICAL* DIOCOREPROTOCOL_CONNECTION::GetCipherKey()
{
  return &cipherkey;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_CONNECTION_STATUS DIOCOREPROTOCOL_CONNECTION::Status_Get()
* @brief      Status_Get
* @ingroup    DATAIO
* 
* @return     DIOCOREPROTOCOL_CONNECTION_STATUS : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_CONNECTION_STATUS DIOCOREPROTOCOL_CONNECTION::Status_Get()
{
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_CONNECTION::Status_Set(DIOCOREPROTOCOL_CONNECTION_STATUS status)
* @brief      Status_Set
* @ingroup    DATAIO
* 
* @param[in]  status : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_CONNECTION::Status_Set(DIOCOREPROTOCOL_CONNECTION_STATUS status)
{
  if(this->status != status)
    {
      if(xtimerstatus)
        {
          xtimerstatus->Reset();
        }

      DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT xevent(this, DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_CHANGESTATUS);
      xevent.SetConnection(this);
      xevent.SetActualStatus(this->status);
      xevent.SetNextStatus(status);

      PostEvent(&xevent);
    }

  this->status = status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTION::Status_GetString(XSTRING status)
* @brief      Status_GetString
* @ingroup    DATAIO
* 
* @param[in]  status : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTION::Status_GetString(DIOCOREPROTOCOL_CONNECTION_STATUS status, XSTRING& statusstring)
{
  statusstring.Empty();

  switch(status)
    {
      case DIOCOREPROTOCOL_CONNECTION_STATUS_NONE           : statusstring = __L("None");                 break;
      case DIOCOREPROTOCOL_CONNECTION_STATUS_CONNECTED      : statusstring = __L("Connected");            break;     
      case DIOCOREPROTOCOL_CONNECTION_STATUS_AUTHENTICATED  : statusstring = __L("Authenticated");        break;
      case DIOCOREPROTOCOL_CONNECTION_STATUS_KEYEXCHANGE    : statusstring = __L("Key exchange");         break;
      case DIOCOREPROTOCOL_CONNECTION_STATUS_READY          : statusstring = __L("Ready");                break;
      case DIOCOREPROTOCOL_CONNECTION_STATUS_DISCONNECTED   : statusstring = __L("Disconnected");         break;
    }

  if(statusstring.IsEmpty())
    {
      return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTION::Status_GetString(XSTRING& statusstring)
* @brief      Status_GetString
* @ingroup    DATAIO
* 
* @param[in]  statusstring : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTION::Status_GetString(XSTRING& statusstring)
{  
  return Status_GetString(status, statusstring);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XTIMER* DIOCOREPROTOCOL_CONNECTION::GetXTimerStatus()
* @brief      GetXTimerStatus
* @ingroup    DATAIO
* 
* @return     XTIMER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XTIMER* DIOCOREPROTOCOL_CONNECTION::GetXTimerStatus()
{
  return xtimerstatus;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XTIMER* DIOCOREPROTOCOL_CONNECTION::GetXTimerWithoutConnexion()
* @brief      GetXTimerWithoutConnexion
* @ingroup    DATAIO
* 
* @return     XTIMER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XTIMER* DIOCOREPROTOCOL_CONNECTION::GetXTimerWithoutConnexion()
{
  return xtimerwithoutconnexion;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_MESSAGES* DIOCOREPROTOCOL_CONNECTION::GetMessages()
* @brief      GetMessages
* @ingroup    DATAIO
* 
* @return     DIOCOREPROTOCOL_MESSAGES* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_MESSAGES* DIOCOREPROTOCOL_CONNECTION::GetMessages()
{
  return &messages;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTION::DoCommand(XUUID* ID_message, XDWORD command_type, XBYTE message_priority, XBUFFER& param)
* @brief      DoCommand
* @ingroup    DATAIO
* 
* @param[in]  ID_message : 
* @param[in]  command_type : 
* @param[in]  message_priority : 
* @param[in]  param : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTION::DoCommand(XUUID* ID_message, XDWORD command_type, XBYTE message_priority, XBUFFER& param)
{
  XSTRING commandstr;
  bool    status;
  
  if(!protocol)
    {
      return false;
    }

  XCHAR* commmandptr = protocol->Commands_Get(command_type);
  if(!commmandptr)
    {
      return false;    
    }

  commandstr.Set(commmandptr);

  status = SendMsg(ID_message, message_priority, DIOCOREPROTOCOL_HEADER_OPERATION_COMMAND, commandstr.Get(), param);
 
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTION::DoCommand(XUUID* ID_message, XDWORD command_type, XBYTE message_priority, XSTRING& param)
* @brief      DoCommand
* @ingroup    DATAIO
* 
* @param[in]  ID_message : 
* @param[in]  command_type : 
* @param[in]  message_priority : 
* @param[in]  param : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTION::DoCommand(XUUID* ID_message, XDWORD command_type, XBYTE message_priority, XSTRING& param)
{
  XSTRING commandstr;
  bool    status;
  
  if(!protocol)
    {
      return false;
    }

  XCHAR* commmandptr = protocol->Commands_Get(command_type);
  if(!commmandptr)
    {
      return false;    
    }

  commandstr.Set(commmandptr);

  status = SendMsg(ID_message, message_priority, DIOCOREPROTOCOL_HEADER_OPERATION_COMMAND, commandstr.Get(), param);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTION::DoCommand(XUUID* ID_message, XDWORD command_type, XBYTE message_priority, XFILEJSON& param)
* @brief      DoCommand
* @ingroup    DATAIO
* 
* @param[in]  ID_message : 
* @param[in]  command_type : 
* @param[in]  message_priority : 
* @param[in]  param : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTION::DoCommand(XUUID* ID_message, XDWORD command_type, XBYTE message_priority, XFILEJSON& param)
{
  XSTRING commandstr;
  bool    status;
  
  if(!protocol)
    {
      return false;
    }

  XCHAR* commmandptr = protocol->Commands_Get(command_type);
  if(!commmandptr)
    {
      return false;    
    }

  commandstr.Set(commmandptr);

  status = SendMsg(ID_message, message_priority, DIOCOREPROTOCOL_HEADER_OPERATION_COMMAND, commandstr.Get(), param);

  return status; 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTION::UpdateMsgReceived()
* @brief      UpdateMsgReceived
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTION::Update()
{
  if(GetEvent() == DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_NONE) // Not new event
    {
      switch(GetCurrentState())
        {
          case DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_NONE                  : break; 

          case DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_CONNECTED             : break; 

          case DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_AUTHENTICATION        : { DIOCOREPROTOCOL_HEADER  header;
                                                                              XBUFFER                 content;    

                                                                              if(IsServer())
                                                                                {      
                                                                                  if(GetMsg(false, DIOCOREPROTOCOL_HEADER_OPERATION_AUTHENTICATE, DIOCOREPROTOCOL_AUTHENTICATION_RESPONSE_OPERATION_PARAM, header, content))
                                                                                    {
                                                                                      if(GetAuthenticationResponse()->Compare(content))
                                                                                        {
                                                                                          SetEvent(DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_KEYEXCHANGE);                                                                                                           
                                                                                        }
                                                                                       else
                                                                                        {
                                                                                          if(protocol)
                                                                                            {   
                                                                                              if(protocol->GetDIOStream())
                                                                                                {
                                                                                                  protocol->GetDIOStream()->Disconnect();
                                                                                                }
                                                                                            }
                                                                                        }                                                                                                       
                                                                                    }                                     
                                                                                
                                                                                }
                                                                               else 
                                                                                {
                                                                                  if(GetMsg(true, DIOCOREPROTOCOL_HEADER_OPERATION_AUTHENTICATE, DIOCOREPROTOCOL_AUTHENTICATION_CHALLENGE_OPERATION_PARAM, header, content))
                                                                                    {
                                                                                      static bool sended =  false;
                                                                                      if(!sended)
                                                                                        {
                                                                                          GetAuthenticationChallenge()->CopyFrom(content);

                                                                                          if(protocol)
                                                                                            {
                                                                                              protocol->GenerateAuthenticationResponse((*GetAuthenticationChallenge()), (*GetAuthenticationResponse()));                                                                                                                                                                                                                     
                                                                                              sended = SendMsg(header.GetIDMessage(), 100, DIOCOREPROTOCOL_HEADER_OPERATION_AUTHENTICATE, DIOCOREPROTOCOL_AUTHENTICATION_RESPONSE_OPERATION_PARAM, (*GetAuthenticationResponse()));                                                                                                            
                                                                                              if(sended)
                                                                                                {
                                                                                                  SetEvent(DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_KEYEXCHANGE);  
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }                                                                                     
                                                                                }
                                                                            }
                                                                            break; 

          case DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_KEYEXCHANGE           : { DIOCOREPROTOCOL_HEADER  header;
                                                                              XBUFFER                 content;    

                                                                              if(IsServer())
                                                                                {                                                                                                                                  
                                                                                  if(GetMsg(false, DIOCOREPROTOCOL_HEADER_OPERATION_KEYEXCHANGE, DIOCOREPROTOCOL_KEYEXCHANGE_CLIENT_OPERATION_PARAM, header, content))
                                                                                    {                                                                                   
                                                                                      if(header.GetContentType() == DIOCOREPROTOCOL_HEADER_CONTENTTYPE_BINARY)
                                                                                        {
                                                                                          if(content.GetSize() == CIPHERCURVE25519_MAXKEY) 
                                                                                            {
                                                                                              ciphercurve.CreateSharedKey(content.Get());
                                                                                              cipherkey.Set(ciphercurve.GetKey(CIPHERCURVE25519_TYPEKEY_SHARED), CIPHERCURVE25519_MAXKEY); 

                                                                                              SetEvent(DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_READY);  
                                                                                              Status_Set(DIOCOREPROTOCOL_CONNECTION_STATUS_KEYEXCHANGE);       
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }                                                                                                                                                                                                                                                                                             
                                                                               else   
                                                                                {                                                                                     
                                                                                  if(GetMsg(true, DIOCOREPROTOCOL_HEADER_OPERATION_KEYEXCHANGE, DIOCOREPROTOCOL_KEYEXCHANGE_SERVER_OPERATION_PARAM, header, content))
                                                                                    {                                                                                      
                                                                                      if(header.GetContentType() == DIOCOREPROTOCOL_HEADER_CONTENTTYPE_BINARY)
                                                                                        {
                                                                                          if(content.GetSize() == CIPHERCURVE25519_MAXKEY) 
                                                                                            {  
                                                                                              ciphercurve.CreateSharedKey(content.Get());
                                                                                              cipherkey.Set(ciphercurve.GetKey(CIPHERCURVE25519_TYPEKEY_SHARED), CIPHERCURVE25519_MAXKEY); 

                                                                                              static bool sended =  false;
                                                                                              if(!sended)     
                                                                                                {        
                                                                                                  XBUFFER publickey;

                                                                                                  publickey.Add(ciphercurve.GetKey(CIPHERCURVE25519_TYPEKEY_PUBLIC), CIPHERCURVE25519_MAXKEY);

                                                                                                  sended = SendMsg(header.GetIDMessage(), 100, DIOCOREPROTOCOL_HEADER_OPERATION_KEYEXCHANGE, DIOCOREPROTOCOL_KEYEXCHANGE_CLIENT_OPERATION_PARAM, publickey);                                                                                                            
                                                                                                  if(sended)
                                                                                                    {
                                                                                                      SetEvent(DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_READY);
                                                                                                      Status_Set(DIOCOREPROTOCOL_CONNECTION_STATUS_KEYEXCHANGE);    
                                                                                                    } 
                                                                                                }                                                                                                                                                                                                       
                                                                                            }
                                                                                        }                                                                                        
                                                                                    }                                                                                  
                                                                                }  
                                                                            }                                                                                                                                                       
                                                                            break;
             
          case DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_READY                 : break; 
          
          case DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_DISCONNECTED          : break;         
        }
    }
   else //  New event
    {
      if(GetEvent()<DIOCOREPROTOCOL_CONNECTION_LASTEVENT)
        {
          CheckTransition();

          switch(GetCurrentState())
            {
              case DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_NONE                  : break; 

              case DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_CONNECTED             : Status_Set(DIOCOREPROTOCOL_CONNECTION_STATUS_CONNECTED);    
                                                                                SetEvent(DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_AUTHENTICATION);                                                                          
                                                                                break; 

              case DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_AUTHENTICATION        : if(IsServer())
                                                                                  {                                                                                    
                                                                                    SendMsg(NULL, 100, DIOCOREPROTOCOL_HEADER_OPERATION_AUTHENTICATE, DIOCOREPROTOCOL_AUTHENTICATION_CHALLENGE_OPERATION_PARAM, (*GetAuthenticationChallenge()));
                                                                                  }
                                                                                break; 

              case DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_KEYEXCHANGE           : if(IsServer())
                                                                                  {                                                                                    
                                                                                    XBUFFER publickey;

                                                                                    publickey.Add(ciphercurve.GetKey(CIPHERCURVE25519_TYPEKEY_PUBLIC), CIPHERCURVE25519_MAXKEY);

                                                                                    SendMsg(NULL, 100, DIOCOREPROTOCOL_HEADER_OPERATION_KEYEXCHANGE, DIOCOREPROTOCOL_KEYEXCHANGE_SERVER_OPERATION_PARAM, publickey);
                                                                                  }
                                                                                break;
                
              case DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_READY                 : messages.DeleteAll();
                                                                                Status_Set(DIOCOREPROTOCOL_CONNECTION_STATUS_READY); 
                                                                                break; 

              case DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_DISCONNECTED          : Status_Set(DIOCOREPROTOCOL_CONNECTION_STATUS_DISCONNECTED);   
                                                                                if(protocol)
                                                                                  {   
                                                                                    if(protocol->GetDIOStream())
                                                                                      {
                                                                                        protocol->GetDIOStream()->Disconnect();
                                                                                      }
                                                                                  }                                                                                                                                                              
                                                                                break;         
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTION::SendMsg(XUUID* ID_message, XBYTE message_priority, DIOCOREPROTOCOL_HEADER_OPERATION operation, XCHAR* operation_param, XBUFFER& content)
* @brief      SendMsg
* @ingroup    DATAIO
* 
* @param[in]  ID_message : 
* @param[in]  message_priority : 
* @param[in]  operation : 
* @param[in]  operation_param : 
* @param[in]  content : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTION::SendMsg(XUUID* ID_message, XBYTE message_priority, DIOCOREPROTOCOL_HEADER_OPERATION operation, XCHAR* operation_param, XBUFFER& content)
{
  DIOCOREPROTOCOL_HEADER* header          = NULL;
  XBUFFER                 contentresult;
  bool                    status          = false;

  if(!protocol)
    {
      return false;  
    }   

  header = protocol->CreateHeader(ID_message, message_priority, operation, operation_param, content, contentresult);
  if(!header)
    {      
      return false;
    }

  status = protocol->SendMsg(header, contentresult);
  if(status)
    {
      DIOCOREPROTOCOL_MESSAGE* message = new DIOCOREPROTOCOL_MESSAGE();
      if(message)
        {
          message->SetAcquisitionType(DIOCOREPROTOCOL_MESSAGE_TYPE_ACQUISITION_WRITE);
          message->GetHeader()->CopyFrom(header);
          message->GetContent()->Add(contentresult);  

          DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT xevent(this, DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_WRITEMSG);
          xevent.SetConnection(this);
          xevent.SetActualStatus(Status_Get());                      
          xevent.SetNextStatus(DIOCOREPROTOCOL_CONNECTION_STATUS_NONE);
          xevent.SetMsg(message);

          PostEvent(&xevent);

          if(!ID_message)
            {
              GetMessages()->AddRequest(message);
            }
           else
            {
              GetMessages()->AddResponse(message);
            }       
        }                                                                                                                                                       
    }

  delete header;
           
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTION::SendMsg(XUUID* ID_message, XBYTE message_priority, DIOCOREPROTOCOL_HEADER_OPERATION operation, XCHAR* operation_param, XSTRING& content)
* @brief      SendMsg
* @ingroup    DATAIO
* 
* @param[in]  ID_message : 
* @param[in]  message_priority : 
* @param[in]  operation : 
* @param[in]  operation_param : 
* @param[in]  content : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTION::SendMsg(XUUID* ID_message, XBYTE message_priority, DIOCOREPROTOCOL_HEADER_OPERATION operation, XCHAR* operation_param, XSTRING& content)
{
  DIOCOREPROTOCOL_HEADER* header          = NULL;
  XBUFFER                 contentresult;
  bool                    status          = false;

  if(!protocol)
    {
      return false;  
    }   

  header = protocol->CreateHeader(ID_message, message_priority, operation, operation_param, content, contentresult);
  if(!header)
    {      
      return false;
    }
  
  status = protocol->SendMsg(header, contentresult);
  if(status)
    {
      DIOCOREPROTOCOL_MESSAGE* message = new DIOCOREPROTOCOL_MESSAGE();
      if(message)
        {
          message->SetAcquisitionType(DIOCOREPROTOCOL_MESSAGE_TYPE_ACQUISITION_WRITE);
          message->GetHeader()->CopyFrom(header);
          message->GetContent()->Add(contentresult);  

          DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT xevent(this, DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_WRITEMSG);
          xevent.SetConnection(this);
          xevent.SetActualStatus(Status_Get());                      
          xevent.SetNextStatus(DIOCOREPROTOCOL_CONNECTION_STATUS_NONE);
          xevent.SetMsg(message);

          PostEvent(&xevent);

          if(!ID_message)
            {
              GetMessages()->AddRequest(message);
            }
           else
            {
              GetMessages()->AddResponse(message);
            }       
        }                                                                                                                                                       
    }

  delete header;
   
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTION::SendMsg(XUUID* ID_message, XBYTE message_priority, DIOCOREPROTOCOL_HEADER_OPERATION operation, XCHAR* operation_param, XFILEJSON& content)
* @brief      SendMsg
* @ingroup    DATAIO
* 
* @param[in]  ID_message : 
* @param[in]  message_priority : 
* @param[in]  operation : 
* @param[in]  operation_param : 
* @param[in]  content : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTION::SendMsg(XUUID* ID_message, XBYTE message_priority, DIOCOREPROTOCOL_HEADER_OPERATION operation, XCHAR* operation_param, XFILEJSON& content)
{
  DIOCOREPROTOCOL_HEADER* header          = NULL;  
  XBUFFER                 contentresult;  
  bool                    status          = false;

  if(!protocol)
    {
      return false;  
    }   

  header = protocol->CreateHeader(ID_message, message_priority, operation, operation_param, content, contentresult);
  if(!header)
    {      
      return false;
    }

  status = protocol->SendMsg(header, contentresult);
  if(status)
    {     
      DIOCOREPROTOCOL_MESSAGE* message = new DIOCOREPROTOCOL_MESSAGE();
      if(message)
        {
          message->SetAcquisitionType(DIOCOREPROTOCOL_MESSAGE_TYPE_ACQUISITION_WRITE);
          message->GetHeader()->CopyFrom(header);
          message->GetContent()->Add(contentresult);  

          DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT xevent(this, DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_WRITEMSG);
          xevent.SetConnection(this);
          xevent.SetActualStatus(Status_Get());                      
          xevent.SetNextStatus(DIOCOREPROTOCOL_CONNECTION_STATUS_NONE);
          xevent.SetMsg(message);
 
          PostEvent(&xevent);

          if(!ID_message)
            {
              GetMessages()->AddRequest(message);
            }
           else
            {
              GetMessages()->AddResponse(message);
            }       
        }                                                                                                                                                       
    }

  delete header;
               
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTION::GetMsg(bool isrequest, DIOCOREPROTOCOL_HEADER_OPERATION operation, XCHAR* operation_param, DIOCOREPROTOCOL_HEADER& header, XBUFFER& content)
* @brief      GetMsg
* @ingroup    DATAIO
* 
* @param[in]  isrequest : 
* @param[in]  operation : 
* @param[in]  operation_param : 
* @param[in]  header : 
* @param[in]  content : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTION::GetMsg(bool isrequest, DIOCOREPROTOCOL_HEADER_OPERATION operation, XCHAR* operation_param, DIOCOREPROTOCOL_HEADER& header, XBUFFER& content)
{
  int index           = NOTFOUND;
  int timeoutresponse = DIOCOREPROTOCOL_CFG_DEFAULT_TIMEOUTNORESPONSE;

  if(!protocol)
    {
      return false;  
    }   
 
  if(protocol->GetProtocolCFG())
    {
      timeoutresponse = protocol->GetProtocolCFG()->GetTimeOutNoResponse();
    }
 
  if(isrequest)
    {
      index = GetMessages()->FindRequest(operation, operation_param);                                                                        
    }
   else
    {
      index = GetMessages()->FindResponse(operation, operation_param);                                                                        
    }
 
  if(index != NOTFOUND)
    { 
      DIOCOREPROTOCOL_MESSAGE* message = NULL;

      if(isrequest)
        {
          message = GetMessages()->GetAll()->GetKey(index); 
        }
       else 
        {
          message = GetMessages()->GetAll()->GetElement(index); 
        }

      if(message)
        {
          header.CopyFrom(message->GetHeader());
          content.Add(message->GetContent());
            
          return true;
        }
    }
   else
    {
      if(xtimerstatus)
        {
          if(xtimerstatus->GetMeasureSeconds() >= timeoutresponse)
            {
              SetEvent(DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_DISCONNECTED);  
            }
        }                                                                                            
    }  

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_CONNECTION::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_CONNECTION::Clean()
{
  protocol                = NULL;

  status                  = DIOCOREPROTOCOL_CONNECTION_STATUS_NONE; 

  xtimerstatus            = NULL;
  xtimerwithoutconnexion  = NULL;
}


#pragma endregion

