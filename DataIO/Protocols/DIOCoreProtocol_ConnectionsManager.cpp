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

#include "DIOStream.h"
#include "DIOStreamEnumServers.h"

#include "DIOCoreProtocol.h"
#include "DIOCoreProtocol_CFG.h"
#include "DIOCoreProtocol_Connection.h"

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

  CreateIDMachine(ID_machine);
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
bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::Ini(DIOCOREPROTOCOL_CFG* protocolCFG)
{ 
  bool status = false;
 
  if(!protocolCFG)
    {
      return false;
    }

  this->protocolCFG = protocolCFG;  

  if(!protocolCFG->DIOStream_GetAll()->GetSize())
    {
      return false;
    } 

  for(XDWORD c=0; c<protocolCFG->DIOStream_GetAll()->GetSize(); c++)
    {      
      DIOSTREAM* diostream = protocolCFG->DIOStream_GetAll()->GetElement(c);
      if(diostream)
        {      

          SubscribeEvent(DIOSTREAM_XEVENT_TYPE_CONNECTED    , diostream);
          SubscribeEvent(DIOSTREAM_XEVENT_TYPE_DISCONNECTED , diostream);
  
          if(diostream->Open())
            {
              if(!diostream->WaitToConnected(5))
                {
                  return false;
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
  Connection_DeleAll();

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

  for(XDWORD c=0; c<protocolCFG->DIOStream_GetAll()->GetSize(); c++)
    {      
      DIOSTREAM* diostream = protocolCFG->DIOStream_GetAll()->GetElement(c);
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
  return protocolCFG;
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
DIOCOREPROTOCOL* DIOCOREPROTOCOL_CONNECTIONSMANAGER::CreateProtocol(DIOSTREAM* diostream)
{
  if(!protocolCFG)
    {
      return NULL;
    }

  DIOCOREPROTOCOL* protocol = new DIOCOREPROTOCOL(protocolCFG, diostream);

  return protocol;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<DIOCOREPROTOCOL_CONNECTION*>* DIOCOREPROTOCOL_CONNECTIONSMANAGER::Connection_GetAll()
* @brief      Connection_GetAll
* @ingroup    DATAIO
* 
* @return     XVECTOR<DIOCOREPROTOCOL_CONNECTION*>* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<DIOCOREPROTOCOL_CONNECTION*>* DIOCOREPROTOCOL_CONNECTIONSMANAGER::Connection_GetAll()
{
  return &connections;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XMUTEX* DIOCOREPROTOCOL_CONNECTIONSMANAGER::Connection_GetXMutex()
* @brief      Connection_GetXMutex
* @ingroup    DATAIO
* 
* @return     XMUTEX* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XMUTEX* DIOCOREPROTOCOL_CONNECTIONSMANAGER::Connection_GetXMutex()
{
  return connections_xmutex;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::Connection_Add(DIOSTREAM* diostream)
* @brief      Connection_Add
* @ingroup    DATAIO
* 
* @param[in]  diostream : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_CONNECTION* DIOCOREPROTOCOL_CONNECTIONSMANAGER::Connection_Add(XUUID* ID_machine, DIOSTREAM* diostream)
{
  if(!diostream)
    {
      return NULL;
    }

  DIOCOREPROTOCOL_CONNECTION* connection = Connection_Get(diostream);
  if(!connection)
    {
      connection = new DIOCOREPROTOCOL_CONNECTION(ID_machine, protocolCFG);
      if(!connection)
        {
          return NULL;
        }      
    }

  connection->SetDIOStream(diostream);  
  connection->SetStatus(DIOCOREPROTOCOL_CONNECTION_STATUS_CONNECTED);

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
* @fn         DIOCOREPROTOCOL_CONNECTION* DIOCOREPROTOCOL_CONNECTIONSMANAGER::Connection_Get(DIOSTREAM* diostream)
* @brief      Connection_Get
* @ingroup    DATAIO
* 
* @param[in]  diostream : 
* 
* @return     DIOCOREPROTOCOL_CONNECTION* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_CONNECTION* DIOCOREPROTOCOL_CONNECTIONSMANAGER::Connection_Get(DIOSTREAM* diostream)
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
          if(connection->GetDIOStream() == diostream)
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
* @fn         bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::Connection_Delete(DIOCOREPROTOCOL_CONNECTION* connection)
* @brief      Connection_Delete
* @ingroup    DATAIO
* 
* @param[in]  connection : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::Connection_Delete(DIOCOREPROTOCOL_CONNECTION* connection)
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
* @fn         bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::Connection_DeleAll()
* @brief      Connection_DeleAll
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::Connection_DeleAll()
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
      case DIOSTREAM_XEVENT_TYPE_CONNECTED      : { DIOCOREPROTOCOL_CONNECTION* connection = Connection_Add(&ID_machine, event->GetDIOStream());                                                                                                      
                                                    if(connection)          
                                                      {
                                                        if(!connection->GetCoreProtocol())
                                                          { 
                                                            DIOCOREPROTOCOL* protocol = CreateProtocol(event->GetDIOStream());
                                                            if(protocol)
                                                              {
                                                                connection->SetCoreProtocol(protocol);
                                                              }  
                                                          }
                                                      }
                                                  }
                                                  break;

      case DIOSTREAM_XEVENT_TYPE_DISCONNECTED   : { DIOCOREPROTOCOL_CONNECTION* connection = Connection_Get(event->GetDIOStream());
                                                    if(connection)
                                                      {
                                                        connection->SetStatus(DIOCOREPROTOCOL_CONNECTION_STATUS_DISCONNECTED);
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
      case XEVENT_TYPE_DIOSTREAM        : { DIOSTREAM_XEVENT* event = (DIOSTREAM_XEVENT*)xevent;
                                            if(!event) return;

                                            HandleEvent_DIOStream(event);
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
  protocolCFG                 = NULL;

  connections_xmutex          = NULL;
  connections_xthread         = NULL;
}


#pragma endregion


