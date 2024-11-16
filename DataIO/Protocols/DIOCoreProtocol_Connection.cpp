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

  xtimerstatus = GEN_XFACTORY.CreateTimer();

  InitFSMachine();

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
  if(protocol)
    {
      delete protocol;
    }

  if(xtimerstatus)
    {
      GEN_XFACTORY.DeleteTimer(xtimerstatus);
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
                DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_INI_AUTHENTICATION ,  DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_INI_AUTHENTICATION  ,
                DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_DISCONNECTED       ,  DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_DISCONNECTED        ,                
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  if(!AddState( DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_INI_AUTHENTICATION ,
                DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_END_AUTHENTICATION ,  DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_END_AUTHENTICATION  ,
                DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_DISCONNECTED       ,  DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_DISCONNECTED        ,                
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  if(!AddState( DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_END_AUTHENTICATION ,
                DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_INI_INITIALIZATION ,  DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_INI_INITIALIZATION  ,
                DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_DISCONNECTED       ,  DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_DISCONNECTED        ,                
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  if(!AddState( DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_INI_INITIALIZATION ,
                DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_END_INITIALIZATION ,  DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_END_INITIALIZATION  ,
                DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_DISCONNECTED       ,  DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_DISCONNECTED        ,                
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  if(!AddState( DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_END_INITIALIZATION ,
                DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_IN_PROGRESS        ,  DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_IN_PROGRESS         ,
                DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_DISCONNECTED       ,  DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_DISCONNECTED        ,                
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  if(!AddState( DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_IN_PROGRESS       ,
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
* @fn         DIOCOREPROTOCOL_CONNECTION_STATUS DIOCOREPROTOCOL_CONNECTION::GetStatus()
* @brief      GetStatus
* @ingroup    DATAIO
* 
* @return     DIOCOREPROTOCOL_CONNECTION_STATUS : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_CONNECTION_STATUS DIOCOREPROTOCOL_CONNECTION::GetStatus()
{
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_CONNECTION::SetStatus(DIOCOREPROTOCOL_CONNECTION_STATUS status)
* @brief      SetStatus
* @ingroup    DATAIO
* 
* @param[in]  status : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_CONNECTION::SetStatus(DIOCOREPROTOCOL_CONNECTION_STATUS status)
{
  if(this->status != status)
    {
      if(xtimerstatus)
        {
          xtimerstatus->Reset();
        }
    }

  this->status = status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTION::GetStatusString(XSTRING status)
* @brief      GetStatusString
* @ingroup    DATAIO
* 
* @param[in]  status : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTION::GetStatusString(XSTRING& statusstring)
{
  statusstring.Empty();

  switch(status)
    {
      case DIOCOREPROTOCOL_CONNECTION_STATUS_NONE           : statusstring = __L("None");
                                                              break;

      case DIOCOREPROTOCOL_CONNECTION_STATUS_CONNECTED      : statusstring = __L("Connected");
                                                              break;
      
      case DIOCOREPROTOCOL_CONNECTION_STATUS_AUTHENTICATED  : statusstring = __L("Authenticated");
                                                              break;

      case DIOCOREPROTOCOL_CONNECTION_STATUS_INITIALIZED    : statusstring = __L("Initialized");
                                                              break;

      case DIOCOREPROTOCOL_CONNECTION_STATUS_DISCONNECTED   : statusstring = __L("Disconnected");
                                                              break;
    }

  if(statusstring.IsEmpty())
    {
      return false;
    }

  return true;
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
          message->GetHeader()->CopyFrom(header);
          message->GetContent()->Add(contentresult);  

          GetMessages()->AddRequest(message);
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
          message->GetHeader()->CopyFrom(header);
          message->GetContent()->Add(contentresult);  

          GetMessages()->AddRequest(message);
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
          message->GetHeader()->CopyFrom(header);
          message->GetContent()->Add(contentresult);  

          GetMessages()->AddRequest(message);
        }                                                                                                                                                       
    }

  delete header;
               
  return header;
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

          case DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_INI_AUTHENTICATION    : if(IsServer())
                                                                              {      
                                                                                int index = GetMessages()->FindResponse(DIOCOREPROTOCOL_HEADER_OPERATION_AUTHENTICATE, DIOCOREPROTOCOL_HEADER_AUTHENTICATION_RESPONSE_OPERATION_PARAM);                                                                        
                                                                                if(index != NOTFOUND)
                                                                                  {                                                                                    
                                                                                    DIOCOREPROTOCOL_MESSAGE* message = GetMessages()->GetAll()->GetElement(index); 
                                                                                    if(message)
                                                                                      {
                                                                                        if(GetAuthenticationResponse()->Compare(message->GetContent()))
                                                                                          {
                                                                                            SetEvent(DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_END_AUTHENTICATION);  
                                                                                            SetStatus(DIOCOREPROTOCOL_CONNECTION_STATUS_AUTHENTICATED);                    
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
                                                                                    if(xtimerstatus)
                                                                                      {
                                                                                        if(xtimerstatus->GetMeasureSeconds() > 10)
                                                                                          {
                                                                                            SetEvent(DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_DISCONNECTED);  
                                                                                          }
                                                                                      }                                                                                            
                                                                                  }  
                                                                              }
                                                                             else 
                                                                              {
                                                                                int index = GetMessages()->FindRequest(DIOCOREPROTOCOL_HEADER_OPERATION_AUTHENTICATE, DIOCOREPROTOCOL_HEADER_AUTHENTICATION_CHALLENGE_OPERATION_PARAM);                                                                        
                                                                                if(index != NOTFOUND)
                                                                                  {
                                                                                    DIOCOREPROTOCOL_MESSAGE* message = GetMessages()->GetAll()->GetKey(index); 
                                                                                    if(message)
                                                                                      {                                                                                            
                                                                                        static bool sended =  false;
                                                                                        if(!sended)
                                                                                          {
                                                                                            GetAuthenticationChallenge()->CopyFrom((*message->GetContent()));

                                                                                            if(protocol)
                                                                                              {
                                                                                                protocol->GenerateAuthenticationResponse((*GetAuthenticationChallenge()), (*GetAuthenticationResponse()));                                                                                                                                                                                                                     
                                                                                                sended = SendMsg(message->GetHeader()->GetIDMessage(), 100, DIOCOREPROTOCOL_HEADER_OPERATION_AUTHENTICATE, DIOCOREPROTOCOL_HEADER_AUTHENTICATION_RESPONSE_OPERATION_PARAM, (*GetAuthenticationResponse()));                                                                                                            
                                                                                                if(sended)
                                                                                                  {
                                                                                                    SetEvent(DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_END_AUTHENTICATION);  
                                                                                                  }
                                                                                              }
                                                                                          }
                                                                                      }
                                                                                  }
                                                                                 else
                                                                                  {
                                                                                    if(xtimerstatus)
                                                                                      {
                                                                                        if(xtimerstatus->GetMeasureSeconds() > 10)
                                                                                          {
                                                                                            SetEvent(DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_DISCONNECTED);  
                                                                                          }
                                                                                      }                                                                                            
                                                                                  }  
                                                                                                                                                                       
                                                                              }
                                                                            break; 

          case DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_END_AUTHENTICATION    : if(!IsServer())
                                                                              {   
                                                                                int index = GetMessages()->FindRequest(DIOCOREPROTOCOL_HEADER_OPERATION_AUTHENTICATE, DIOCOREPROTOCOL_HEADER_AUTHENTICATION_ACCEPTED_OPERATION_PARAM);                                                                        
                                                                                if(index != NOTFOUND)
                                                                                  {
                                                                                    DIOCOREPROTOCOL_MESSAGE* message = GetMessages()->GetAll()->GetKey(index); 
                                                                                    if(message)
                                                                                      {                           
                                                                                        SetEvent(DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_INI_INITIALIZATION);
                                                                                        SetStatus(DIOCOREPROTOCOL_CONNECTION_STATUS_AUTHENTICATED);    
                                                                                      }
                                                                                  }
                                                                                 else
                                                                                  {
                                                                                    if(xtimerstatus)
                                                                                      {
                                                                                        if(xtimerstatus->GetMeasureSeconds() > 10)
                                                                                          {
                                                                                            SetEvent(DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_DISCONNECTED);  
                                                                                          }
                                                                                      }                                                                                            
                                                                                  }  
                                                                              }
                                                                             else
                                                                              {
                                                                                SetEvent(DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_INI_INITIALIZATION);  
                                                                              }
                                                                            break;
    
          case DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_INI_INITIALIZATION    : break; 

          case DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_END_INITIALIZATION    : break; 

          case DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_IN_PROGRESS           : break; 
          
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

              case DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_CONNECTED             : SetStatus(DIOCOREPROTOCOL_CONNECTION_STATUS_CONNECTED);    
                                                                                SetEvent(DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_INI_AUTHENTICATION);                                                                          
                                                                                break; 

              case DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_INI_AUTHENTICATION    : if(IsServer())
                                                                                  {                                                                                    
                                                                                    SendMsg(NULL, 100, DIOCOREPROTOCOL_HEADER_OPERATION_AUTHENTICATE, DIOCOREPROTOCOL_HEADER_AUTHENTICATION_CHALLENGE_OPERATION_PARAM, (*GetAuthenticationChallenge()));
                                                                                  }
                                                                                break; 

              case DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_END_AUTHENTICATION    : if(IsServer())
                                                                                  {                                                                                    
                                                                                    XSTRING accepted_str = __L("hello");
                                                                                    SendMsg(NULL, 100, DIOCOREPROTOCOL_HEADER_OPERATION_AUTHENTICATE, DIOCOREPROTOCOL_HEADER_AUTHENTICATION_ACCEPTED_OPERATION_PARAM, accepted_str);
                                                                                  }
                                                                                break;
  
              case DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_INI_INITIALIZATION    : break; 

              case DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_END_INITIALIZATION    : break; 

              case DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_IN_PROGRESS           : break; 

              case DIOCOREPROTOCOL_CONNECTION_XFSMSTATE_DISCONNECTED          : SetStatus(DIOCOREPROTOCOL_CONNECTION_STATUS_DISCONNECTED);   
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
* @fn         void DIOCOREPROTOCOL_CONNECTION::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_CONNECTION::Clean()
{
  protocol      = NULL;

  status        = DIOCOREPROTOCOL_CONNECTION_STATUS_NONE; 

  xtimerstatus  = NULL;
}


#pragma endregion

