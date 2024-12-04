/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOCoreProtocol_ConnectionsManager.cpp
* 
* @class      DIOCOREPROTOCOL_CONNECTIONSMANAGER
* @brief      Data Input/Output Core Protocol Connections Manager class
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

#include "DIOCoreProtocol_ConnectionsManager.h"

#include "XFactory.h"
#include "XSystem.h"
#include "XRand.h"

#include "DIOStream.h"
#include "DIOStreamEnumServers.h"

#include "DIOCoreProtocol.h"
#include "DIOCoreProtocol_CFG.h"
#include "DIOCoreProtocol_Connection.h"
#include "DIOCoreProtocol_ConnectionsManager_XEvent.h"
#include "DIOCoreProtocol_Messages.h"

#include "HashSHA2.h"

#include "XMemory_Control.h"


#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#pragma region CLASS_DIOCOREPROTOCOL_CONNECTIONSMANAGER


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_CONNECTIONSMANAGER::DIOCOREPROTOCOL_CONNECTIONSMANAGER(DIOCOREPROTOCOL_CFG* protocolCFG)
* @brief      Constructor
* @ingroup    DATAIO
* 
* @param[in]  DIOCOREPROTOCOL_CFG* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_CONNECTIONSMANAGER::DIOCOREPROTOCOL_CONNECTIONSMANAGER()
{
  Clean(); 

  diostreams.SetIsMulti(false);

  CreateIDMachine(ID_machine);

  RegisterEvent(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_READMSG);
 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_CONNECTIONSMANAGER::~DIOCOREPROTOCOL_CONNECTIONSMANAGER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_CONNECTIONSMANAGER::~DIOCOREPROTOCOL_CONNECTIONSMANAGER()
{
  DeRegisterEvent(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_READMSG);
 
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::Ini()
* @brief      Ini
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::Ini()
{ 
  bool status = false;

  if(!diostreams.GetSize())
    {
      return false;
    } 

  for(XDWORD c=0; c<diostreams.GetSize(); c++)
    {      
      DIOSTREAM* diostream = diostreams.GetElement(c);
      if(diostream)
        {      
          SubscribeEvent(DIOSTREAM_XEVENT_TYPE_CONNECTED    , diostream);
          SubscribeEvent(DIOSTREAM_XEVENT_TYPE_DISCONNECTED , diostream);
  
          if(diostream->Open())
            {
              if(!diostream->WaitToConnected(3))
                {
                  if(diostream->GetConfig()->IsServer())
                    {
                      return false;
                    }
                   else 
                    {
                      diostream->Close();
                    } 
                }            
            }
        }
    }
  
  GEN_XFACTORY_CREATE(connections_xmutex, Create_Mutex())
  if(connections_xmutex) 
    {
      connections_xthread = CREATEXTHREAD(XTHREADGROUPID_DIOPROTOCOL_CONNECTIONMANAGER, __L("DIOPROTOCOL_CONNECTIONSMANAGER::Ini"), ThreadConnections, (void*)this);
      if(connections_xthread)
        {
          if(connections_xthread->Ini()) 
            {
              return true;
            }
        }      
    }

  End();

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::End()
* @brief      End
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::End()
{ 
  Connections_DeleteAll();

  if(connections_xthread)
    {
      connections_xthread->End();
      DELETEXTHREAD(XTHREADGROUPID_DIOPROTOCOL_CONNECTIONMANAGER, connections_xthread);
      connections_xthread = NULL;
    }  

  if(connections_xmutex)
    {
      GEN_XFACTORY.Delete_Mutex(connections_xmutex);
      connections_xmutex = NULL;
    }

  for(XDWORD c=0; c<diostreams.GetSize(); c++)
    {      
      DIOSTREAM* diostream = diostreams.GetElement(c);
      if(diostream)
        {        
          UnSubscribeEvent(DIOSTREAM_XEVENT_TYPE_CONNECTED    , diostream);
          UnSubscribeEvent(DIOSTREAM_XEVENT_TYPE_DISCONNECTED , diostream);
  
          diostream->Close();          
        }
    }
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_CFG* DIOCOREPROTOCOL_CONNECTIONSMANAGER::GetProtocolCFG()
* @brief      GetProtocolCFG
* @ingroup    DATAIO
* 
* @return     DIOCOREPROTOCOL_CFG* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_CFG* DIOCOREPROTOCOL_CONNECTIONSMANAGER::GetProtocolCFG()
{
  return &protocolCFG;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XMAP<DIOSTREAMCONFIG*, DIOSTREAM*>* DIOCOREPROTOCOL_CONNECTIONSMANAGER::DIOStream_GetAll()
* @brief      DIOStream_GetAll
* @ingroup    DATAIO
* 
* @return     XMAP<DIOSTREAMCONFIG*, : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XMAP<DIOSTREAMCONFIG*, DIOSTREAM*>* DIOCOREPROTOCOL_CONNECTIONSMANAGER::DIOStream_GetAll()
{
  return &diostreams;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::DIOStream_Add(DIOSTREAMCONFIG* diostreamCFG, DIOSTREAM* diostream)
* @brief      DIOStream_Add
* @ingroup    DATAIO
* 
* @param[in]  diostreamCFG : 
* @param[in]  diostream : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::DIOStream_Add(DIOSTREAMCONFIG* diostreamCFG, DIOSTREAM* diostream)
{
  if(!diostreamCFG || !diostream)
    {
      return false;
    }

  return diostreams.Add(diostreamCFG, diostream);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::DIOStream_Delete(DIOSTREAMCONFIG* diostreamCFG)
* @brief      DIOStream_Delete
* @ingroup    DATAIO
* 
* @param[in]  diostreamCFG : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::DIOStream_Delete(DIOSTREAMCONFIG* diostreamCFG)
{
  if(!diostreamCFG)
    {
      return false;
    }

  DIOSTREAM* diostream = diostreams.Get(diostreamCFG);
  if(!diostream)
    {
      return false;
    }

  diostreams.Delete(diostreamCFG);

  delete diostreamCFG;
  delete diostream;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::DIOStream_DeleteAll()
* @brief      DIOStream_DeleteAll
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::DIOStream_DeleteAll()
{
  if(!diostreams.GetSize())
    {
      return false;
    }

  diostreams.DeleteKeyContents();
  diostreams.DeleteElementContents();
  
  diostreams.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL* DIOCOREPROTOCOL_CONNECTIONSMANAGER::CreateProtocol(DIOSTREAM* diostream)
* @brief      CreateProtocol
* @ingroup    DATAIO
* 
* @param[in]  diostream : 
* 
* @return     DIOCOREPROTOCOL* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL* DIOCOREPROTOCOL_CONNECTIONSMANAGER::CreateProtocol(DIOSTREAM* diostream, XUUID* ID_machine)
{  
  DIOCOREPROTOCOL* protocol = new DIOCOREPROTOCOL(&protocolCFG, diostream, ID_machine);

  return protocol;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::DoCommand(DIOCOREPROTOCOL_CONNECTION* connection, XDWORD command_type, XBYTE message_priority, XBUFFER& param, XBUFFER& result, XDWORD timeout)
* @brief      DoCommand
* @ingroup    DATAIO
* 
* @param[in]  connection : 
* @param[in]  command_type : 
* @param[in]  message_priority : 
* @param[in]  param : 
* @param[in]  result : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::DoCommand(DIOCOREPROTOCOL_CONNECTION* connection, XDWORD command_type, XBYTE message_priority, XBUFFER& param, XBUFFER& result, XDWORD timeout)
{
  if(!connection)
    {
      return false;
    }

  if(!connection->DoCommand(NULL, command_type, message_priority, param))
    {
      return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<DIOCOREPROTOCOL_CONNECTION*>* DIOCOREPROTOCOL_CONNECTIONSMANAGER::Connections_GetAll()
* @brief      Connections_GetAll
* @ingroup    DATAIO
* 
* @return     XVECTOR<DIOCOREPROTOCOL_CONNECTION*>* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<DIOCOREPROTOCOL_CONNECTION*>* DIOCOREPROTOCOL_CONNECTIONSMANAGER::Connections_GetAll()
{
  return &connections;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XMUTEX* DIOCOREPROTOCOL_CONNECTIONSMANAGER::Connections_GetXMutex()
* @brief      Connections_GetXMutex
* @ingroup    DATAIO
* 
* @return     XMUTEX* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XMUTEX* DIOCOREPROTOCOL_CONNECTIONSMANAGER::Connections_GetXMutex()
{
  return connections_xmutex;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::Connections_Add(DIOSTREAM* diostream)
* @brief      Connections_Add
* @ingroup    DATAIO
* 
* @param[in]  diostream : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_CONNECTION* DIOCOREPROTOCOL_CONNECTIONSMANAGER::Connections_Add(DIOSTREAM* diostream)
{
  if(!diostream)
    {
      return NULL;
    }

  DIOCOREPROTOCOL_CONNECTION* connection = Connections_Get(diostream);
  if(!connection)
    {
      connection = new DIOCOREPROTOCOL_CONNECTION();
      if(!connection)
        {
          return NULL;
        }      
    }

  if(connections_xmutex)
    {
      connections_xmutex->Lock();
    }

  bool status = connections.Add(connection);

  if(connections_xmutex)
    {
      connections_xmutex->UnLock();
    }

  return connection;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_CONNECTION* DIOCOREPROTOCOL_CONNECTIONSMANAGER::Connections_Get(DIOSTREAM* diostream)
* @brief      Connections_Get
* @ingroup    DATAIO
* 
* @param[in]  diostream : 
* 
* @return     DIOCOREPROTOCOL_CONNECTION* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_CONNECTION* DIOCOREPROTOCOL_CONNECTIONSMANAGER::Connections_Get(DIOSTREAM* diostream)
{ 
  if(!connections.GetSize())
    {
      return NULL;
    }

  if(connections_xmutex)
    {
      connections_xmutex->Lock();
    }

  for(XDWORD c=0; c<connections.GetSize(); c++)
    {
      DIOCOREPROTOCOL_CONNECTION* connection = connections.Get(c);
      if(connection)  
        {
          if(connection->GetCoreProtocol()->GetDIOStream() == diostream)
            {
              if(connections_xmutex)
                  {
                    connections_xmutex->UnLock();
                  }

              return connection;
            }
        }
    }

  if(connections_xmutex)
    {
      connections_xmutex->UnLock();
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_CONNECTION* DIOCOREPROTOCOL_CONNECTIONSMANAGER::Connections_Get(XDWORD index)
* @brief      Connections_Get
* @ingroup    DATAIO
* 
* @param[in]  index : 
* 
* @return     DIOCOREPROTOCOL_CONNECTION* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_CONNECTION* DIOCOREPROTOCOL_CONNECTIONSMANAGER::Connections_Get(XDWORD index)
{ 
  DIOCOREPROTOCOL_CONNECTION* connection = NULL;

  if(!connections.GetSize())
    {
      return NULL;
    }

  if(connections_xmutex)
    {
      connections_xmutex->Lock();
    }

  connection = connections.Get(index);
  
  if(connections_xmutex)
    {
      connections_xmutex->UnLock();
    }

  return connection;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::Connections_Delete(DIOCOREPROTOCOL_CONNECTION* connection)
* @brief      Connections_Delete
* @ingroup    DATAIO
* 
* @param[in]  connection : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::Connections_Delete(DIOCOREPROTOCOL_CONNECTION* connection)
{
  if(!connection)
    {
      return false;
    }

  if(connections_xmutex)
    {
      connections_xmutex->Lock();
    }

  connections.Delete(connection);
  delete connection;

  if(connections_xmutex)
    {
      connections_xmutex->UnLock();
    }
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::Connections_DeleteAllDisconnected()
* @brief      Connections_DeleteAllDisconnected
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::Connections_DeleteAllDisconnected()
{
  if(!connections.GetSize())
    {
      return false;
    }

  int index = 0;

  do{ DIOCOREPROTOCOL_CONNECTION* connection = connections.Get(index);
      if(connection)  
        {
          if(connection->Status_Get() == DIOCOREPROTOCOL_CONNECTION_STATUS_DISCONNECTED)
            {
              if(connection->GetXTimerStatus()->GetMeasureSeconds() >= connection->GetCoreProtocol()->GetProtocolCFG()->GetTimeToEliminateConnectionDisconnect())
                {
                  Connections_Delete(connection);
                  continue;
                }
            }

          index++;
        }

    } while(index < connections.GetSize());

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::Connections_DeleteAll()
* @brief      Connections_DeleAll
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::Connections_DeleteAll()
{
  if(!connections.GetSize())
    {
      return false;
    }

  if(connections_xmutex)
    {
      connections_xmutex->Lock();
    }

  connections.DeleteContents();
  connections.DeleteAll();

  if(connections_xmutex)
    {
      connections_xmutex->UnLock();
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::Received_AdditionsCommand(DIOCOREPROTOCOL_CONNECTION* connection, DIOCOREPROTOCOL_MESSAGE* message)
* @brief      Received_AdditionsCommand
* @ingroup    DATAIO
* 
* @param[in]  connection : 
* @param[in]  message : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::Received_AdditionsCommand(DIOCOREPROTOCOL_CONNECTION* connection, DIOCOREPROTOCOL_MESSAGE* message)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::Connections_SendAllHeartBet()
* @brief      Connections_SendAllHeartBet
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::Connections_SendAllHeartBet()
{
  if(!connections.GetSize())
    {
      return false;
    }

  int index = 0;

  do{ DIOCOREPROTOCOL_CONNECTION* connection = connections.Get(index);
      if(connection)  
        {               
          //if(connection->IsServer())
            {         
              if((connection->Status_Get() == DIOCOREPROTOCOL_CONNECTION_STATUS_READY) ||
                 (connection->Status_Get() == DIOCOREPROTOCOL_CONNECTION_STATUS_INSTABILITY))
                {       
                  DIOCOREPROTOCOL* protocol = connection->GetCoreProtocol();
                  if(protocol)
                    {                          
                      if(protocol->GetProtocolCFG()->GetNTrysToCheckConnection() >=1 )
                        {
                          if(connection->GetXTimerWithoutConnexion()->GetMeasureSeconds() >= protocol->GetProtocolCFG()->GetTimeToCheckConnection())
                            {
                              XSTRING content = DIOCOREPROTOCOL_HEARTBEAT_REQUEST_CONTENT;
                              connection->DoCommand(NULL, DIOCOREPROTOCOL_COMMAND_TYPE_HEARTBEAT, 10, content);  
                            
                              if(connection->GetHeartBetsCounter() > protocol->GetProtocolCFG()->GetNTrysToCheckConnection())
                                {
                                  connection->SetEvent(DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_DISCONNECTED);   
                                }
                               else
                                {
                                  if(connection->GetHeartBetsCounter() == 1)
                                    {
                                      connection->SetEvent(DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_INSTABILITY);   
                                    }
                           
                                  //protocol->GetProtocolCFG()->SetNTrysToCheckConnection(0);

                                  connection->SetHeartBetsCounter(connection->GetHeartBetsCounter()+1);                                  
                                  connection->GetXTimerWithoutConnexion()->Reset();
                                }
                            }                                     
                        }
                    }
                }
            }
          
          index++;
        }

    } while(index < connections.GetSize());

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::Connections_ReadMessages()
* @brief      Connections_ReadMessages
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::Connections_ReadMessages()
{
  if(!connections.GetSize())
    {
      return false;
    }

  int index = 0;

  do{ DIOCOREPROTOCOL_CONNECTION* connection = connections.Get(index);
      if(connection)  
        {  
          if((connection->Status_Get() == DIOCOREPROTOCOL_CONNECTION_STATUS_READY) ||
             (connection->Status_Get() == DIOCOREPROTOCOL_CONNECTION_STATUS_INSTABILITY))
            {              
              if(connection->GetCoreProtocol())
                {          
                  DIOCOREPROTOCOL_MESSAGES* messages = connection->Messages_GetAll();
                  if(messages)
                    {
                      int indexmsg = 0;
   
                      while(indexmsg < messages->GetAll()->GetSize())
                        {
                          DIOCOREPROTOCOL_MESSAGE* message[2] = { NULL, NULL };

                          message[0] = messages->GetAll()->GetKey(indexmsg);
                          message[1] = messages->GetAll()->GetElement(indexmsg);
                          
                          if(message[0])
                            {
                              if(!message[0]->IsConsumed())
                                {
                                  if(message[0]->GetHeader()->GetMessageType() == DIOCOREPROTOCOL_HEADER_MESSAGETYPE_REQUEST) 
                                    {                                                                             
                                      switch(message[0]->GetHeader()->GetOperation())
                                        {
                                          case DIOCOREPROTOCOL_HEADER_OPERATION_UNKNOWN : break;

                                          case DIOCOREPROTOCOL_HEADER_OPERATION_COMMAND : if(Received_AllCommandMessages(connection, message[0]))
                                                                                            {                                                                                                       
                                                                                              message[1] = messages->GetAll()->GetElement(indexmsg);                                                                                     
                                                                                              if(message[1]) 
                                                                                                {
                                                                                                  message[1]->SetIsConsumed(true);                                                                                                  
                                                                                                }
                                                                                            }

                                                                                          //messages->ShowDebug(connection->IsServer());                                                                                              
                                                                                          break;

                                          case DIOCOREPROTOCOL_HEADER_OPERATION_UPDATE  : break;   
                                        }                                       
                                    }
                                }
                            }
                           //else
                            {           
                              if(message[0] && message[1])
                                {
                                  if(message[0]->IsConsumed() && !message[1]->IsConsumed())
                                    {
                                      if((message[1]->GetAcquisitionType() == DIOCOREPROTOCOL_MESSAGE_TYPE_ACQUISITION_READ) && (message[1]->GetHeader()->GetMessageType() == DIOCOREPROTOCOL_HEADER_MESSAGETYPE_RESPONSE))
                                        {                                                                             
                                          switch(message[1]->GetHeader()->GetOperation())
                                            {
                                              case DIOCOREPROTOCOL_HEADER_OPERATION_UNKNOWN : break;

                                              case DIOCOREPROTOCOL_HEADER_OPERATION_COMMAND : if(message[1]) 
                                                                                                {
                                                                                                  message[1]->SetIsConsumed(true);                                                                                                  
                                                                                                }
                                                                                          
                                                                                              //messages->ShowDebug(connection->IsServer());                                                                                              
                                                                                              break;

                                              case DIOCOREPROTOCOL_HEADER_OPERATION_UPDATE  : break;   
                                            }                                       
                                        }
                                    }
                                }
                            }
                             
                          indexmsg++;
                        }                                      
                    }
                }
            }
            
          index++;
        }

    } while(index < connections.GetSize());

   
  index = 0;

  do{ DIOCOREPROTOCOL_CONNECTION* connection = connections.Get(index);
      if(connection)  
        {  
          if((connection->Status_Get() == DIOCOREPROTOCOL_CONNECTION_STATUS_READY) ||
             (connection->Status_Get() == DIOCOREPROTOCOL_CONNECTION_STATUS_INSTABILITY))
            {        
              DIOCOREPROTOCOL_MESSAGES* messages = connection->Messages_GetAll();
              if(messages)
                {
                  int   indexmsg  = 0;
                  bool  deletemsg = false;

                  while(indexmsg < messages->GetAll()->GetSize())
                    {
                      DIOCOREPROTOCOL_MESSAGE* message[2];

                      message[0] = messages->GetAll()->GetKey(indexmsg);
                      message[1] = messages->GetAll()->GetElement(indexmsg);

                      deletemsg = false;
                          
                      if(message[0] && message[1])
                        {
                          if(message[0]->IsConsumed() && message[1]->IsConsumed())
                            {                              
                              if(messages->Delete(message[0]->GetHeader()->GetIDMessage()))
                                {
                                  deletemsg = true;            
                                }                              
                            }
                        }

                      if(!deletemsg)
                        {
                          indexmsg++;
                        }
                    }
                }
            }

          index++;
        }

    } while(index < connections.GetSize());
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::Received_AllCommandMessages(DIOCOREPROTOCOL_CONNECTION* connection, DIOCOREPROTOCOL_MESSAGE* message)
* @brief      Received_AllCommandMessages
* @ingroup    DATAIO
* 
* @param[in]  connection : 
* @param[in]  message : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::Received_AllCommandMessages(DIOCOREPROTOCOL_CONNECTION* connection, DIOCOREPROTOCOL_MESSAGE* message)
{
  if(!connection)
    {
      return false;
    }  

  if(!message)
    {
      return false;
    }

  if(message->GetHeader()->GetOperation() != DIOCOREPROTOCOL_HEADER_OPERATION_COMMAND)
    {
      return false;
    }

  DIOCOREPROTOCOL* protocol = connection->GetCoreProtocol();
  if(!protocol)
    {
      return false;
    }

  bool managermessage = false;
  bool status         = false;
  
  if(!message->GetHeader()->GetOperationParam()->Compare(protocol->Commands_Get(DIOCOREPROTOCOL_COMMAND_TYPE_HEARTBEAT), true))
    {
      managermessage = true;
      
      XSTRING content = DIOCOREPROTOCOL_HEARTBEAT_RESPONSE_CONTENT;

      message->SetIsConsumed(true);

      managermessage = connection->DoCommand(message->GetHeader()->GetIDMessage(), DIOCOREPROTOCOL_COMMAND_TYPE_HEARTBEAT, 10, content);  
      if(managermessage)
        {
          connection->SetHeartBetsCounter(0);    
          connection->SetEvent(DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_READY);        
        }      
    }

  if(managermessage)
    {
      // More internal messages
    }

  if(!managermessage)
    {
      status = Received_AdditionsCommand(connection, message);
    }
   else
    {
      status = true;
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::CreateIDMachine(XUUID& ID)
* @brief      CreateIDMachine
* @ingroup    DATAIO
* 
* @param[in]  ID : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::CreateIDMachine(XUUID& ID)
{ 
  XSTRING   origin; 
  XBUFFER   originbuffer; 
  HASHSHA2* sha2        = NULL;
  XBUFFER*  result      = NULL;

  ID.Empty();

  GEN_XSYSTEM.GetOperativeSystemID(origin);
  
  origin.AddFormat(__L(" %s"), GEN_XSYSTEM.GetBIOSSerialNumber()->Get());
  origin.AddFormat(__L(" %s"), GEN_XSYSTEM.GetCPUSerialNumber()->Get());

  origin.ConvertToUTF8(originbuffer);
    
  sha2 = new HASHSHA2(HASHSHA2TYPE_256);
  if(!sha2)
    {
      return false;
    }

  sha2->Do(originbuffer);
  result = sha2->GetResult();

  if(!result)
    {
      return false;
    }

  if(!result->GetSize())
    {
      return false;
    }

  XDWORD data1 = 0; 
  XWORD  data2 = 0;
  XWORD  data3 = 0;
  XBYTE  data4 = 0;
  XBYTE  data5 = 0; 
  XBYTE* data6 = &result->Get()[12];

  result->Get((XDWORD&)data1);  
  result->Get((XWORD&)data2);  
  result->Get((XWORD&)data3);  
  result->Get((XBYTE&)data4);  
  result->Get((XBYTE&)data5);  

  ID.Set(data1, data2, data3, data4, data5, data6);

  ID.GetToString(origin);

  delete sha2;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_CONNECTIONSMANAGER::HandleEvent_CoreProtocolConnection(DIOCOREPROTOCOL_CONNECTION_XEVENT* event)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    DATAIO
* 
* @param[in]  event : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_CONNECTIONSMANAGER::HandleEvent_CoreProtocolConnectionsManager(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT* event)
{
  if(!event) 
    {
      return;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_CONNECTIONSMANAGER::HandleEvent_DIOStream(DIOSTREAM_XEVENT* event)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    DATAIO
* 
* @param[in]  event : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_CONNECTIONSMANAGER::HandleEvent_DIOStream(DIOSTREAM_XEVENT* event)
{
  if(!event) 
    {
      return;
    }

  switch(event->GetEventType())
    {
      case DIOSTREAM_XEVENT_TYPE_CONNECTED      : { DIOCOREPROTOCOL_CONNECTION* connection = Connections_Add(event->GetDIOStream());                                                                                                      
                                                    if(connection)          
                                                      {
                                                        if(!connection->GetCoreProtocol())
                                                          { 
                                                            DIOCOREPROTOCOL* protocol = CreateProtocol(event->GetDIOStream(), &ID_machine);
                                                            if(protocol)
                                                              { 
                                                                connection->SetCoreProtocol(protocol); 

                                                                SubscribeEvent(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_CHANGESTATUS, connection);
                                                                SubscribeEvent(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_READMSG     , this);
                                                                SubscribeEvent(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_WRITEMSG    , connection);

                                                                if(connection->IsServer())
                                                                  {
                                                                    if(protocol->GenerateAuthenticationChallenge((*connection->GetAuthenticationChallenge())))
                                                                      {
                                                                        protocol->GenerateAuthenticationResponse((*connection->GetAuthenticationChallenge()), (*connection->GetAuthenticationResponse()));                                                                                                                              
                                                                      }                                                             
                                                                  }
                                                              }  
                                                          }
                                                      }
                                                  }
                                                  break;

      case DIOSTREAM_XEVENT_TYPE_DISCONNECTED   : { DIOCOREPROTOCOL_CONNECTION* connection = Connections_Get(event->GetDIOStream());
                                                    if(connection)
                                                      {
                                                        if(connections_xmutex)
                                                          {
                                                            connections_xmutex->Lock();
                                                          }

                                                        connection->SetEvent(DIOCOREPROTOCOL_CONNECTION_XFSMEVENT_DISCONNECTED);

                                                        if(connection->GetCoreProtocol())
                                                          {                                                           
                                                            connection->GetCoreProtocol()->SetDIOStream(NULL);                                                                                                                           
                                                          }

                                                        UnSubscribeEvent(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_CHANGESTATUS, connection);
                                                        UnSubscribeEvent(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_READMSG     , this);
                                                        UnSubscribeEvent(DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_WRITEMSG    , connection);

                                                        if(connections_xmutex)
                                                          {
                                                            connections_xmutex->UnLock();
                                                          }
                                                      }
                                                  }
                                                  break;
    }

}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_CONNECTIONSMANAGER::HandleEvent(XEVENT* xevent)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    DATAIO
* 
* @param[in]  xevent : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_CONNECTIONSMANAGER::HandleEvent(XEVENT* xevent)
{
  if(!xevent) 
    {
      return;
    }

  switch(xevent->GetEventFamily())
    {
      case XEVENT_TYPE_DIOSTREAM                      : { DIOSTREAM_XEVENT* event = (DIOSTREAM_XEVENT*)xevent;
                                                          if(!event) return;

                                                          HandleEvent_DIOStream(event);
                                                        }
                                                        break;

      case XEVENT_TYPE_COREPROTOCOLCONNECTIONSMANAGER : { DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT* event = (DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT*)xevent;
                                                          if(!event) return;

                                                          HandleEvent_CoreProtocolConnectionsManager(event);
                                                        }
                                                        break; 
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_CONNECTIONSMANAGER::ThreadConnections(void* param)
* @brief      ThreadConnections
* @ingroup    DATAIO
* 
* @param[in]  param : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_CONNECTIONSMANAGER::ThreadConnections(void* param)
{
  DIOCOREPROTOCOL_CONNECTIONSMANAGER* connectionsmanager = (DIOCOREPROTOCOL_CONNECTIONSMANAGER*)param;
  if(!connectionsmanager) 
    {
      return;
    }

  if(!connectionsmanager->GetProtocolCFG())
    {
      return;
    }

  if(connectionsmanager->connections_xmutex)
    {
      connectionsmanager->connections_xmutex->Lock();
    }
  
  for(XDWORD c=0; c< connectionsmanager->DIOStream_GetAll()->GetSize(); c++)
    {
      DIOSTREAM* diostream = connectionsmanager->DIOStream_GetAll()->GetElement(c);
      if(diostream)  
        {              
          if(diostream->GetConfig())
            {
              if(diostream->GetConfig()->GetMode() != DIOSTREAMMODE_SERVERMULTISOCKET)
                {
                  if(diostream->GetStatus() == DIOSTREAMSTATUS_DISCONNECTED) 
                    {
                      diostream->Close();
                      diostream->Open();                     
                    }  
                }
            }
        }                
    }  

  XDWORD c = 0;  
  while(c < connectionsmanager->Connections_GetAll()->GetSize())
    {
      DIOCOREPROTOCOL_CONNECTION* connection = connectionsmanager->Connections_GetAll()->Get(c);
      if(connection)
        {
          if(connection->GetCoreProtocol())
            {
              DIOCOREPROTOCOL_HEADER  header;
              XBUFFER                 content;

              if(connection->GetCoreProtocol()->ReceivedMsg(header, content))
                {
                  DIOCOREPROTOCOL_MESSAGE*  message = NULL;
                  bool                      status  = false;

                  switch(header.GetMessageType())
                    {
                      case DIOCOREPROTOCOL_HEADER_MESSAGETYPE_REQUEST   : { message = new DIOCOREPROTOCOL_MESSAGE();
                                                                            if(message)
                                                                              {
                                                                                message->SetAcquisitionType(DIOCOREPROTOCOL_MESSAGE_TYPE_ACQUISITION_READ);
                                                                                message->GetHeader()->CopyFrom(&header);
                                                                                message->GetContent()->CopyFrom(content);  

                                                                                status = connection->Messages_GetAll()->AddRequest(message);
                                                                              }                                                                            
                                                                          } 
                                                                          break;

                      case DIOCOREPROTOCOL_HEADER_MESSAGETYPE_RESPONSE  : { message = new DIOCOREPROTOCOL_MESSAGE();
                                                                            if(message)
                                                                              {                                                                               
                                                                                message->SetAcquisitionType(DIOCOREPROTOCOL_MESSAGE_TYPE_ACQUISITION_READ);
                                                                                message->GetHeader()->CopyFrom(&header);
                                                                                message->GetContent()->CopyFrom(content);  

                                                                                status = connection->Messages_GetAll()->AddResponse(message);                                                                                
                                                                              }                                                                            
                                                                          } 
                                                                          break;                                            
                    }
                                    
                  if(status)
                    {
                      DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT xevent(connectionsmanager, DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_READMSG);
                      xevent.SetConnection(connection);
                      xevent.SetActualStatus(connection->Status_Get());                      
                      xevent.SetNextStatus(DIOCOREPROTOCOL_CONNECTION_STATUS_NONE);
                      xevent.SetMsg(message);
 
                      connectionsmanager->PostEvent(&xevent);    

                      connection->GetXTimerWithoutConnexion()->Reset();                                                     
                    }
                   else 
                    {                   
                      delete message;
                    }                       
                }

              connection->Update();
            }        
        }

      c++;
    }

  connectionsmanager->Connections_ReadMessages();

  connectionsmanager->Connections_SendAllHeartBet();

  if(connectionsmanager->connections_xmutex)
    {
      connectionsmanager->connections_xmutex->UnLock();
    }

  connectionsmanager->Connections_DeleteAllDisconnected();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_CONNECTIONSMANAGER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_CONNECTIONSMANAGER::Clean()
{  
  connections_xmutex          = NULL;
  connections_xthread         = NULL;
}


#pragma endregion


