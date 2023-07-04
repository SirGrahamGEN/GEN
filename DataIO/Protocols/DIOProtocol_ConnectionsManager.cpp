/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOProtocol_ConnectionsManager.cpp
*
* @class      DIOPROTOCOL_CONNECTIONSMANAGER
* @brief      Data Input/Output  Protocol Connections Manager class
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XFactory.h"
#include "XSleep.h"
#include "XTimer.h"
#include "XTrace.h"
#include "XThreadCollected.h"

#include "DIOFactory.h"
#include "DIOIP.h"
#include "DIOURL.h"
#include "DIOStreamXEvent.h"
#include "DIOStreamDeviceIP.h"
#include "DIOStreamUDPLocalEnumServers.h"
#include "DIOStreamTCPIPConfig.h"
#include "DIOStreamTCPIP.h"
#include "DIOProtocolConnectionsInUseDefinitions.h"

#include "DIOProtocol_ConnectionsManager.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------*/
/* DIOPROTOCOL_CONNECTION                                                                                              */
/*--------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOPROTOCOL_CONNECTION::DIOPROTOCOL_CONNECTION(DIOSTREAMCONFIG* diostreamcfg)
* @brief      Constructor
* @ingroup    DATAIO
*
* @param[in]  DIOSTREAMCONFIG* :
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOL_CONNECTION::DIOPROTOCOL_CONNECTION(DIOSTREAMCONFIG* diostreamcfg)
{
  Clean();

  this->diostreamcfg  = diostreamcfg;

  GEN_XFACTORY_CREATE(xmutexinuseID, Create_Mutex())

  inuseID.SetIsMulti(true);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOPROTOCOL_CONNECTION::~DIOPROTOCOL_CONNECTION()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOL_CONNECTION::~DIOPROTOCOL_CONNECTION()
{
  GEN_XFACTORY.Delete_Mutex(xmutexinuseID);

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMCONFIG* DIOPROTOCOL_CONNECTION::GetDIOStreamConfig()
* @brief      GetDIOStreamConfig
* @ingroup    DATAIO
*
* @return     DIOSTREAMCONFIG* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMCONFIG* DIOPROTOCOL_CONNECTION::GetDIOStreamConfig()
{
  return diostreamcfg;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOPROTOCOL* DIOPROTOCOL_CONNECTION::GetDIOProtocol()
* @brief      GetDIOProtocol
* @ingroup    DATAIO
*
* @return     DIOPROTOCOL* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOL* DIOPROTOCOL_CONNECTION::GetDIOProtocol()
{
  return dioprotocol;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOPROTOCOL_CONNECTION::SetDIOProtocol(DIOPROTOCOL* protocol)
* @brief      SetDIOProtocol
* @ingroup    DATAIO
*
* @param[in]  protocol :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_CONNECTION::SetDIOProtocol(DIOPROTOCOL* protocol)
{
  this->dioprotocol = protocol;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOPROTOCOL_CONNECTION::Connect()
* @brief      Connect
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOL_CONNECTION::Connect()
{
  if(!dioprotocol) return false;

  return dioprotocol->Connect();
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOPROTOCOL_CONNECTION::Disconected()
* @brief      Disconected
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOL_CONNECTION::Disconected()
{
  if(!dioprotocol)  return false;

  if(dioprotocol->IsConnected())
    {
      dioprotocol->Disconnect();
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOPROTOCOL_CONNECTION::SetInUse(bool inuse, XDWORD ID)
* @brief      SetInUse
* @ingroup    DATAIO
*
* @param[in]  inuse :
* @param[in]  ID :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOL_CONNECTION::SetInUse(bool inuse, XDWORD ID)
{
  if(!xmutexinuseID)  return false;

  xmutexinuseID->Lock();

  if(inuse)
        inuseID.Add(ID);
    else inuseID.Delete(ID);

  xmutexinuseID->UnLock();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOPROTOCOL_CONNECTION::IsInUse()
* @brief      IsInUse
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOL_CONNECTION::IsInUse()
{
  bool inuse = false;

  if(!xmutexinuseID)

  xmutexinuseID->Lock();
  inuse = (inuseID.GetSize()?true:false);
  xmutexinuseID->UnLock();

  return inuse;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOPROTOCOL_CONNECTION::IsSendEventConnected()
* @brief      IsSendEventConnected
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOL_CONNECTION::IsSendEventConnected()
{
  return issendeventconnected;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOPROTOCOL_CONNECTION::SetIsSendEventConnected(bool issendeventconnected)
* @brief      SetIsSendEventConnected
* @ingroup    DATAIO
*
* @param[in]  issendeventconnected :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_CONNECTION::SetIsSendEventConnected(bool issendeventconnected)
{
  this->issendeventconnected = issendeventconnected;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOPROTOCOL_CONNECTION::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_CONNECTION::Clean()
{
  diostreamcfg            = NULL;
  dioprotocol             = NULL;
  issendeventconnected    = false;

  xmutexinuseID           = NULL;
}



/*--------------------------------------------------------------------------------------------------------------------*/
/* DIOPROTOCOL_CONNECTIONSMANAGER                                                                                      */
/*--------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOPROTOCOL_CONNECTIONSMANAGER::DIOPROTOCOL_CONNECTIONSMANAGER()
* @brief      Constructor
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOL_CONNECTIONSMANAGER::DIOPROTOCOL_CONNECTIONSMANAGER()
{
  Clean();

  protocolconnectionsnlimit  = DIOPROTOCOL_CONNECTIONS_UNLIMITEDNCONNECTIONS;

  RegisterEvent(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_CONNECTEDCONNECTION);
  RegisterEvent(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_INITPROTOCOL);
  RegisterEvent(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_DISCONNECTEDCONNECTION);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOPROTOCOL_CONNECTIONSMANAGER::~DIOPROTOCOL_CONNECTIONSMANAGER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOL_CONNECTIONSMANAGER::~DIOPROTOCOL_CONNECTIONSMANAGER()
{
  DeRegisterEvent(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_CONNECTEDCONNECTION);
  DeRegisterEvent(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_INITPROTOCOL);
  DeRegisterEvent(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_DISCONNECTEDCONNECTION);

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOPROTOCOL_CONNECTIONSMANAGER::Ini(bool isserver, DIOSTREAMCONFIG* diostreamcfg, DIOSTREAMENUMSERVERS* diostreamenumservers)
* @brief      Ini
* @ingroup    DATAIO
*
* @param[in]  isserver :
* @param[in]  diostreamcfg :
* @param[in]  diostreamenumservers :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOL_CONNECTIONSMANAGER::Ini(bool isserver, DIOSTREAMCONFIG* diostreamcfg, DIOSTREAMENUMSERVERS* diostreamenumservers)
{
  if(!diostreamcfg) return false;

  this->isserver              = isserver;
  this->diostreamcfg          = diostreamcfg;
  this->diostreamenumservers  = diostreamenumservers;

  this->diostreamcfg->SetMode(isserver?DIOSTREAMMODE_SERVER:DIOSTREAMMODE_CLIENT);

  GEN_XFACTORY_CREATE(xtimerout, CreateTimer())
  if(!xtimerout)  return false;
  
  GEN_XFACTORY_CREATE(xmutexprocotolconnections, Create_Mutex())
  if(!xmutexprocotolconnections) return false;

  GEN_XFACTORY_CREATE(xtimerconnections, CreateTimer())
  if(xtimerconnections)
    {      
      xthreadconnections = CREATEXTHREAD(XTHREADGROUPID_DIOPROTOCOL_CONNECTIONMANAGER, __L("DIOPROTOCOL_CONNECTIONSMANAGER::Ini"), ThreadProtocolConnections, (void*)this);
      if(xthreadconnections)
        {
          if(!xthreadconnections->Ini()) return false;
        }
    }

  GEN_XFACTORY_CREATE(xtimerclienttry, CreateTimer())
  if(!xtimerclienttry) return false;
  
  xtimerclienttry->AddSeconds(DIOPROTOCOL_CONNECTIONS_DEFAULTIMETRYCONNECTIONS+1);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOPROTOCOL_CONNECTIONSMANAGER::End()
* @brief      End
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOL_CONNECTIONSMANAGER::End()
{
  WaitToAllConnectionsCanBeDeleted();

  if(xthreadconnections)
    {
      xthreadconnections->End();
      DELETEXTHREAD(XTHREADGROUPID_DIOPROTOCOL_CONNECTIONMANAGER, xthreadconnections);
      xthreadconnections = NULL;
    }

  ProtocolConnections_DeleteAllWaitConnections();

  ProtocolConnections_DisconnectAll();

  ProtocolConnections_DeleteAll();

  if(xtimerclienttry)
    {
      GEN_XFACTORY.DeleteTimer(xtimerclienttry);
      xtimerclienttry = NULL;
    }

  if(xtimerconnections)
    {
      GEN_XFACTORY.DeleteTimer(xtimerconnections);
      xtimerconnections = NULL;
    }

  if(xtimerout)
    {
      GEN_XFACTORY.DeleteTimer(xtimerout);
      xtimerout = NULL;
    }

  if(xmutexprocotolconnections)
    {
      GEN_XFACTORY.Delete_Mutex(xmutexprocotolconnections);
      xmutexprocotolconnections = NULL;
    }

  TargetURL_DeleteAll();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOPROTOCOL_CONNECTIONSMANAGER::TargetURL_GetNTargets()
* @brief      TargetURL_GetNTargets
* @ingroup    DATAIO
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOPROTOCOL_CONNECTIONSMANAGER::TargetURL_GetNTargets()
{
  return targetURLs.GetSize();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOPROTOCOL_CONNECTIONSMANAGER::TargetURL_Add(XCHAR* URL)
* @brief      TargetURL_Add
* @ingroup    DATAIO
*
* @param[in]  URL :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOL_CONNECTIONSMANAGER::TargetURL_Add(XCHAR* URL)
{
  if(!URL)    return false;

  DIOURL* _URL = new DIOURL();
  if(!_URL) return false;

  (*_URL) = URL;

  targetURLs.Add(_URL);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOPROTOCOL_CONNECTIONSMANAGER::TargetURL_Add(XSTRING& URL)
* @brief      TargetURL_Add
* @ingroup    DATAIO
*
* @param[in]  URL :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOL_CONNECTIONSMANAGER::TargetURL_Add(XSTRING& URL)
{
  return TargetURL_Add(URL.Get());
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOPROTOCOL_CONNECTIONSMANAGER::TargetURL_Add(DIOURL& URL)
* @brief      TargetURL_Add
* @ingroup    DATAIO
*
* @param[in]  URL :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOL_CONNECTIONSMANAGER::TargetURL_Add(DIOURL& URL)
{
  return TargetURL_Add(URL.Get());
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOPROTOCOL_CONNECTIONSMANAGER::TargetURL_Get(int index)
* @brief      TargetURL_Get
* @ingroup    DATAIO
*
* @param[in]  index :
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOPROTOCOL_CONNECTIONSMANAGER::TargetURL_Get(int index)
{
  return (XSTRING*)targetURLs.Get(index);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOPROTOCOL_CONNECTIONSMANAGER::TargetURL_Delete(int index)
* @brief      TargetURL_Delete
* @ingroup    DATAIO
*
* @param[in]  index :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOL_CONNECTIONSMANAGER::TargetURL_Delete(int index)
{
  DIOURL* URL = (DIOURL*)targetURLs.Get(index);
  if(!URL) return false;

  targetURLs.Delete(URL);

  delete URL;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOPROTOCOL_CONNECTIONSMANAGER::TargetURL_DeleteAll()
* @brief      TargetURL_DeleteAll
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOL_CONNECTIONSMANAGER::TargetURL_DeleteAll()
{
  if(targetURLs.IsEmpty())  return false;

  targetURLs.DeleteContents();
  targetURLs.DeleteAll();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOPROTOCOL_CONNECTIONSMANAGER::ProtocolConnections_GetNLimit()
* @brief      ProtocolConnections_GetNLimit
* @ingroup    DATAIO
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOPROTOCOL_CONNECTIONSMANAGER::ProtocolConnections_GetNLimit()
{
  return protocolconnectionsnlimit;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOPROTOCOL_CONNECTIONSMANAGER::ProtocolConnections_SetNLimit(int protocolconnectionsnlimit)
* @brief      ProtocolConnections_SetNLimit
* @ingroup    DATAIO
*
* @param[in]  protocolconnectionsnlimit :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_CONNECTIONSMANAGER::ProtocolConnections_SetNLimit(int protocolconnectionsnlimit)
{
  this->protocolconnectionsnlimit = protocolconnectionsnlimit;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOPROTOCOL_CONNECTIONSMANAGER::ProtocolConnections_GetNAvailable()
* @brief      ProtocolConnections_GetNAvailable
* @ingroup    DATAIO
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOPROTOCOL_CONNECTIONSMANAGER::ProtocolConnections_GetNAvailable()
{
  return protocolconnections.GetSize();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOPROTOCOL_CONNECTION* DIOPROTOCOL_CONNECTIONSMANAGER::ProtocolConnections_Get(int index)
* @brief      ProtocolConnections_Get
* @ingroup    DATAIO
*
* @param[in]  index :
*
* @return     DIOPROTOCOL_CONNECTION* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOL_CONNECTION* DIOPROTOCOL_CONNECTIONSMANAGER::ProtocolConnections_Get(int index)
{
  if(!xmutexprocotolconnections)  return NULL;

  xmutexprocotolconnections->Lock();

  DIOPROTOCOL_CONNECTION* protocolconnection = NULL;

  if(!protocolconnections.IsEmpty())
    {
      if(index<(int)ProtocolConnections_GetNAvailable())
        {
          protocolconnection = protocolconnections.Get(index);
        }
    }

  xmutexprocotolconnections->UnLock();

  return protocolconnection;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOPROTOCOL_CONNECTION* DIOPROTOCOL_CONNECTIONSMANAGER::ProtocolConnections_GetFirstConnected()
* @brief      ProtocolConnections_GetFirstConnected
* @ingroup    DATAIO
*
* @return     DIOPROTOCOL_CONNECTION* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOL_CONNECTION* DIOPROTOCOL_CONNECTIONSMANAGER::ProtocolConnections_GetFirstConnected()
{
  if(!xmutexprocotolconnections)  return NULL;

  xmutexprocotolconnections->Lock();

  DIOPROTOCOL_CONNECTION* protocolconnection = NULL;
  if(!protocolconnections.IsEmpty())
    {
      for(int c=0; c<(int)ProtocolConnections_GetNAvailable(); c++)
        {
          protocolconnection = protocolconnections.Get(c);
          if(protocolconnection)
            {
              DIOPROTOCOL* protocol = protocolconnection->GetDIOProtocol();
              if(protocol)
                {
                  if(protocol->IsConnected())
                    {
                      protocolconnection = protocolconnections.Get(c);
                      break;

                    } else protocolconnection = NULL;

                } else protocolconnection = NULL;
            }
        }
    }

  xmutexprocotolconnections->UnLock();

  return protocolconnection;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOPROTOCOL_CONNECTION* DIOPROTOCOL_CONNECTIONSMANAGER::ProtocolConnections_GetFirstOperative()
* @brief      ProtocolConnections_GetFirstOperative
* @ingroup    DATAIO
*
* @return     DIOPROTOCOL_CONNECTION* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOL_CONNECTION* DIOPROTOCOL_CONNECTIONSMANAGER::ProtocolConnections_GetFirstOperative()
{
  if(!xmutexprocotolconnections)  return NULL;

  xmutexprocotolconnections->Lock();

  DIOPROTOCOL_CONNECTION* protocolconnection = NULL;
  if(!protocolconnections.IsEmpty())
    {
      for(int c=0; c<(int)ProtocolConnections_GetNAvailable(); c++)
        {
          protocolconnection = protocolconnections.Get(c);
          if(protocolconnection)
            {
              DIOPROTOCOL* protocol = protocolconnection->GetDIOProtocol();
              if(protocol)
                {
                  if(protocol->IsOperational())
                    {
                      protocolconnection = protocolconnections.Get(c);
                      break;

                    } else protocolconnection = NULL;

                } else protocolconnection = NULL;
            }
        }
    }

  xmutexprocotolconnections->UnLock();

  return protocolconnection;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOPROTOCOL_CONNECTION* DIOPROTOCOL_CONNECTIONSMANAGER::ProtocolConnections_GetByDIOStream(DIOSTREAM* diostream)
* @brief      ProtocolConnections_GetByDIOStream
* @ingroup    DATAIO
*
* @param[in]  diostream :
*
* @return     DIOPROTOCOL_CONNECTION* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOL_CONNECTION* DIOPROTOCOL_CONNECTIONSMANAGER::ProtocolConnections_GetByDIOStream(DIOSTREAM* diostream)
{
  DIOPROTOCOL_CONNECTION* protocolconnection = NULL;

  if(!xmutexprocotolconnections)  return NULL;

  xmutexprocotolconnections->Lock();

  if(!protocolconnections.IsEmpty())
    {
      for(int index=0; index< ProtocolConnections_GetNAvailable(); index++)
        {
          DIOPROTOCOL_CONNECTION* _protocolconnection = (DIOPROTOCOL_CONNECTION*)protocolconnections.Get(index);
          if(_protocolconnection)
            {
              if(_protocolconnection->GetDIOProtocol())
                {
                  if(_protocolconnection->GetDIOProtocol()->GetDIOStream() == diostream)
                    {
                      protocolconnection = _protocolconnection;
                      break;
                    }
                }
            }
        }
    }

  xmutexprocotolconnections->UnLock();

  return protocolconnection;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOPROTOCOL* DIOPROTOCOL_CONNECTIONSMANAGER::ProtocolConnections_GetProtocol(int index)
* @brief      ProtocolConnections_GetProtocol
* @ingroup    DATAIO
*
* @param[in]  index :
*
* @return     DIOPROTOCOL* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOL* DIOPROTOCOL_CONNECTIONSMANAGER::ProtocolConnections_GetProtocol(int index)
{
  DIOPROTOCOL* protocol = NULL;

  if(!xmutexprocotolconnections)  return NULL;

  xmutexprocotolconnections->Lock();

  if(index<(int)ProtocolConnections_GetNAvailable())
    {
      DIOPROTOCOL_CONNECTION* protocolconnection = (DIOPROTOCOL_CONNECTION*)protocolconnections.Get(index);
      if(protocolconnection)
        {
          if(protocolconnection->GetDIOProtocol())
            {
              if(protocolconnection->GetDIOProtocol()->IsConnected())
                {
                  protocol = protocolconnection->GetDIOProtocol();
                }
            }
        }
    }

  xmutexprocotolconnections->UnLock();

  return protocol;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOPROTOCOL_CONNECTIONSMANAGER::ProtocolConnections_GetNConnected()
* @brief      ProtocolConnections_GetNConnected
* @ingroup    DATAIO
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOPROTOCOL_CONNECTIONSMANAGER::ProtocolConnections_GetNConnected()
{
  if(!xmutexprocotolconnections)  return false;

  xmutexprocotolconnections->Lock();

  int nconnections      = 0;
  int ntotalconnections = ProtocolConnections_GetNAvailable();

  for(int index=0; index < ntotalconnections; index++)
    {
      DIOPROTOCOL_CONNECTION* connection = (DIOPROTOCOL_CONNECTION*)protocolconnections.Get(index);
      if(connection)
        {
          if(connection->GetDIOProtocol())
            {
              if(connection->GetDIOProtocol()->IsConnected()) nconnections++;
            }
        }
    }

  xmutexprocotolconnections->UnLock();

  return nconnections;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOPROTOCOL_CONNECTIONSMANAGER::ProtocolConnections_GetNFreeToConnect()
* @brief      ProtocolConnections_GetNFreeToConnect
* @ingroup    DATAIO
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOPROTOCOL_CONNECTIONSMANAGER::ProtocolConnections_GetNFreeToConnect()
{
  if(!xmutexprocotolconnections)  return 0;

  xmutexprocotolconnections->Lock();

  int nconnections      = 0;
  int ntotalconnections = ProtocolConnections_GetNAvailable();

  for(int index=0; index < ntotalconnections; index++)
    {
      DIOPROTOCOL_CONNECTION* connection = (DIOPROTOCOL_CONNECTION*)protocolconnections.Get(index);
      if(connection)
        {
          if(connection->GetDIOProtocol())
            {
              if(connection->GetDIOProtocol()->IsConnecting()) nconnections++;
            }
        }
    }

  xmutexprocotolconnections->UnLock();

  return nconnections;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOPROTOCOL_CONNECTIONSMANAGER::ProtocolConnections_SendEventConnected()
* @brief      ProtocolConnections_SendEventConnected
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOL_CONNECTIONSMANAGER::ProtocolConnections_SendEventConnected()
{
  if(!xmutexprocotolconnections)  return false;

  xmutexprocotolconnections->Lock();

  int ntotalconnections = ProtocolConnections_GetNAvailable();

  for(int index = 0; index < ntotalconnections; index++)
    {
      DIOPROTOCOL_CONNECTION* connection = (DIOPROTOCOL_CONNECTION*)protocolconnections.Get(index);
      if(connection)
        {
          if(!connection->IsSendEventConnected())
            {
              if(connection->GetDIOProtocol())
                {
                  if(connection->GetDIOProtocol()->IsConnected())
                    {
                      bool sendeventconnected = SendEvent(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_CONNECTEDCONNECTION, connection);

                      connection->SetIsSendEventConnected(sendeventconnected);
                    }
                }
            }
        }
    }

  xmutexprocotolconnections->UnLock();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOPROTOCOL_CONNECTIONSMANAGER::ProtocolConnections_DeleteAllWaitConnections()
* @brief      ProtocolConnections_DeleteAllWaitConnections
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOL_CONNECTIONSMANAGER::ProtocolConnections_DeleteAllWaitConnections()
{
  int index = 0;

  if(!xmutexprocotolconnections)  return false;

  xmutexprocotolconnections->Lock();

  while(index < ProtocolConnections_GetNAvailable())
    {
      DIOPROTOCOL_CONNECTION* protocolconnection = (DIOPROTOCOL_CONNECTION*)protocolconnections.Get(index);
      if(protocolconnection)
        {
          if(protocolconnection->GetDIOProtocol())
            {
              if(protocolconnection->GetDIOProtocol()->GetDIOStream())
                {
                  if(protocolconnection->GetDIOProtocol()->GetDIOStream()->GetConnectStatus() == DIOSTREAMSTATUS_GETTINGCONNECTION)
                    {
                      DeleteProtocol(protocolconnection->GetDIOProtocol());
                      protocolconnection->SetDIOProtocol(NULL);

                      protocolconnections.Delete(protocolconnection);
                      delete protocolconnection;

                    } else index++;

                } else index++;

            } else index++;
        }
    }

  xmutexprocotolconnections->UnLock();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOPROTOCOL_CONNECTIONSMANAGER::ProtocolConnections_DeleteDisconnected()
* @brief      ProtocolConnections_DeleteDisconnected
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOL_CONNECTIONSMANAGER::ProtocolConnections_DeleteDisconnected()
{
  int index = 0;

  if(!xmutexprocotolconnections)  return false;

  xmutexprocotolconnections->Lock();

  while(index < ProtocolConnections_GetNAvailable())
    {
      DIOPROTOCOL_CONNECTION* protocolconnection = (DIOPROTOCOL_CONNECTION*)protocolconnections.Get(index);
      if(protocolconnection)
        {
          if(protocolconnection->GetDIOProtocol())
            {
              if((protocolconnection->GetDIOProtocol()->IsDisconnected())  && (!protocolconnection->IsInUse()))
                {
                  SendEvent(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_DISCONNECTEDCONNECTION, protocolconnection);
                  protocolconnection->Disconected();

                  DeleteProtocol(protocolconnection->GetDIOProtocol());
                  protocolconnection->SetDIOProtocol(NULL);

                  protocolconnections.Delete(protocolconnection);
                  delete protocolconnection;

                } else index++;

            } else index++;
        }
    }

  xmutexprocotolconnections->UnLock();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOPROTOCOL_CONNECTIONSMANAGER::ProtocolConnections_Disconnect(int index)
* @brief      ProtocolConnections_Disconnect
* @ingroup    DATAIO
*
* @param[in]  index :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOL_CONNECTIONSMANAGER::ProtocolConnections_Disconnect(int index)
{
  bool status = false;

  if(!xmutexprocotolconnections)  return false;

  xmutexprocotolconnections->Lock();

  if(index<(int)ProtocolConnections_GetNAvailable())
    {
      DIOPROTOCOL_CONNECTION* protocolconnection = (DIOPROTOCOL_CONNECTION*)protocolconnections.Get(index);
      if(protocolconnection)
        {
          if(protocolconnection->GetDIOProtocol())
            {
              if(protocolconnection->GetDIOProtocol()->IsConnected())
                {
                  SendEvent(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_DISCONNECTEDCONNECTION, protocolconnection);
                  protocolconnection->Disconected();

                  status = true;
                }
            }
        }
    }

  xmutexprocotolconnections->UnLock();

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOPROTOCOL_CONNECTIONSMANAGER::ProtocolConnections_DisconnectAll()
* @brief      ProtocolConnections_DisconnectAll
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOL_CONNECTIONSMANAGER::ProtocolConnections_DisconnectAll()
{
  if(!xmutexprocotolconnections)  return false;

  xmutexprocotolconnections->Lock();

  if(!protocolconnections.IsEmpty())
    {
      int ntotalconnections = ProtocolConnections_GetNAvailable();

      for(int index=0; index < ntotalconnections; index++)
        {
          DIOPROTOCOL_CONNECTION* protocolconnection = (DIOPROTOCOL_CONNECTION*)protocolconnections.Get(index);
          if(protocolconnection)
            {
              if(protocolconnection->GetDIOProtocol())
                {
                  if(protocolconnection->GetDIOProtocol()->IsConnected())
                    {
                      SendEvent(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_DISCONNECTEDCONNECTION, protocolconnection);
                      protocolconnection->Disconected();
                    }
                }
            }
        }
    }

  xmutexprocotolconnections->UnLock();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOPROTOCOL_CONNECTIONSMANAGER::ProtocolConnections_Delete(int index)
* @brief      ProtocolConnections_Delete
* @ingroup    DATAIO
*
* @param[in]  index :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOL_CONNECTIONSMANAGER::ProtocolConnections_Delete(int index)
{
  bool status = false;

  if(!xmutexprocotolconnections)  return false;

  xmutexprocotolconnections->Lock();

  if(index<(int)ProtocolConnections_GetNAvailable())
    {
      DIOPROTOCOL_CONNECTION* protocolconnection = (DIOPROTOCOL_CONNECTION*)protocolconnections.Get(index);
      if(protocolconnection)
        {
          if(protocolconnection->GetDIOProtocol())
            {
              if(!protocolconnection->IsInUse())
                {
                  DIOPROTOCOL* protocol = protocolconnection->GetDIOProtocol();

                  protocolconnections.Delete(protocolconnection);
                  delete protocolconnection;

                  DeleteProtocol(protocol);

                  status = true;
                }
            }
        }
    }

  xmutexprocotolconnections->UnLock();

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOPROTOCOL_CONNECTIONSMANAGER::ProtocolConnections_DeleteAll()
* @brief      ProtocolConnections_DeleteAll
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOL_CONNECTIONSMANAGER::ProtocolConnections_DeleteAll()
{
  if(!xmutexprocotolconnections)  return false;

  xmutexprocotolconnections->Lock();

  int index = 0;

  while(index < ProtocolConnections_GetNAvailable())
    {
      DIOPROTOCOL_CONNECTION* protocolconnection = (DIOPROTOCOL_CONNECTION*)protocolconnections.Get(index);
      if(protocolconnection)
        {
          if((!protocolconnection->IsInUse()))
            {
              DIOPROTOCOL* protocol = protocolconnection->GetDIOProtocol();

              protocolconnections.Delete(protocolconnection);
              delete protocolconnection;

              DeleteProtocol(protocol);

            } else index++;

        } else index++;
    }

  xmutexprocotolconnections->UnLock();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOPROTOCOL_CONNECTIONSMANAGER::WaitToAnyConnectionIsConnected(int timeout)
* @brief      WaitToAnyConnectionIsConnected
* @ingroup    DATAIO
*
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOL_CONNECTIONSMANAGER::WaitToAnyConnectionIsConnected(int timeout)
{
  int  index  = 0;
  bool status = true;

  xtimerout->Reset();

  while(1)
    {
      if(ProtocolConnections_GetNConnected())
        {
          status = false;
          break;
        }

      GEN_XSLEEP.MilliSeconds(10);

      if(xtimerout->GetMeasureSeconds() >= (XDWORD)timeout)
        {
          status = false;
          break;
        }
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOPROTOCOL_CONNECTIONSMANAGER::WaitToAllConnectionsCanBeDeleted(int timeout)
* @brief      WaitToAllConnectionsCanBeDeleted
* @ingroup    DATAIO
*
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOL_CONNECTIONSMANAGER::WaitToAllConnectionsCanBeDeleted(int timeout)
{
  if(!xmutexprocotolconnections)  return false;

  xmutexprocotolconnections->Lock();

  int  index  = 0;
  bool status = true;

  if(timeout) xtimerout->Reset();

  while(1)
    {
      bool candelete = true;

      for(int index=0; index< ProtocolConnections_GetNAvailable(); index++)
        {
          DIOPROTOCOL_CONNECTION* protocolconnection = (DIOPROTOCOL_CONNECTION*)protocolconnections.Get(index);
          if(protocolconnection)
            {
              if(protocolconnection->IsInUse()) candelete = false;
            }
        }

      if(candelete) break;

      GEN_XSLEEP.MilliSeconds(10);

      if(timeout)
        {
          if(xtimerout->GetMeasureSeconds() > 0)
            {
              if(xtimerout->GetMeasureSeconds() >= (XDWORD)timeout)
                {
                  status = false;
                  break;
                }
            }
        }
    }

  xmutexprocotolconnections->UnLock();

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOPROTOCOL_CONNECTIONSMANAGER::SendEvent(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE type, DIOPROTOCOL_CONNECTION* protocolconnection)
* @brief      SendEvent
* @ingroup    DATAIO
*
* @param[in]  type :
* @param[in]  protocolconnection :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOL_CONNECTIONSMANAGER::SendEvent(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE type, DIOPROTOCOL_CONNECTION* protocolconnection)
{
  if(!protocolconnection) return false;

  DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT xevent(this,type);

  xevent.SetDIOStreamEnumServers(diostreamenumservers);
  xevent.SetDIOStreamConfig(protocolconnection->GetDIOStreamConfig());
  xevent.SetDIOProtocol(protocolconnection->GetDIOProtocol());
  xevent.SetProtocolConnection(protocolconnection);
  xevent.SetProtocolConnectionsManager(this);

  return PostEvent(&xevent);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOPROTOCOL_CONNECTIONSMANAGER::GetApplicationVersion(XDWORD& version, XDWORD& subversion, XDWORD& subversionerr)
* @brief      GetApplicationVersion
* @ingroup    DATAIO
*
* @param[in]  version :
* @param[in]  subversion :
* @param[in]  subversionerr :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_CONNECTIONSMANAGER::GetApplicationVersion(XDWORD& version, XDWORD& subversion, XDWORD& subversionerr)
{
  version         = this->applicationversion;
  subversion      = this->applicationsubversion;
  subversionerr   = this->applicationsubversionerr;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOPROTOCOL_CONNECTIONSMANAGER::SetApplicationVersion(XDWORD version, XDWORD subversion, XDWORD subversionerr)
* @brief      SetApplicationVersion
* @ingroup    DATAIO
*
* @param[in]  version :
* @param[in]  subversion :
* @param[in]  subversionerr :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_CONNECTIONSMANAGER::SetApplicationVersion(XDWORD version, XDWORD subversion, XDWORD subversionerr)
{
  this->applicationversion        = version;
  this->applicationsubversion     = subversion;
  this->applicationsubversionerr  = subversionerr;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOPROTOCOL_CONNECTIONSMANAGER::GetApplicationName()
* @brief      GetApplicationName
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOPROTOCOL_CONNECTIONSMANAGER::GetApplicationName()
{
  return &applicationname;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOPROTOCOL_CONNECTIONSMANAGER::ManageProtocolConnectionsServer()
* @brief      ManageProtocolConnectionsServer
* @ingroup    DATAIO
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_CONNECTIONSMANAGER::ManageProtocolConnectionsServer()
{
  if(!xthreadconnections)              return;
  if(!xthreadconnections->IsRunning()) return;

  xtimerconnections->Reset();

  ProtocolConnections_DeleteDisconnected();

  if(protocolconnectionsnlimit != DIOPROTOCOL_CONNECTIONS_UNLIMITEDNCONNECTIONS)
    {
      if(!protocolconnectionsnlimit) return;

      if(ProtocolConnections_GetNConnected() >= protocolconnectionsnlimit)
        {
          return;
        }
    }

  ProtocolConnections_SendEventConnected();

  if(!ProtocolConnections_GetNFreeToConnect())
    {
      DIOPROTOCOL_CONNECTION* protocolconnection = new DIOPROTOCOL_CONNECTION(diostreamcfg);
      if(protocolconnection)
        {
          DIOPROTOCOL* protocol = CreateProtocol();
          if(protocol)
            {
              protocolconnection->SetDIOProtocol(protocol);

              if(protocolconnection->Connect())
                {
                  if(xmutexprocotolconnections) xmutexprocotolconnections->Lock();

                  protocol->SetConnection(protocolconnection);

                  protocolconnections.Add(protocolconnection);

                  if(xmutexprocotolconnections) xmutexprocotolconnections->UnLock();
                }
            }
           else
            {
              DeleteProtocol(protocol);
              protocol = NULL;

              delete protocolconnection;
              protocolconnection = NULL;
            }
        }
       else
        {
          delete protocolconnection;
          protocolconnection = NULL;
        }
    }
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOPROTOCOL_CONNECTIONSMANAGER::ManageProtocolConnectionsClient()
* @brief      ManageProtocolConnectionsClient
* @ingroup    DATAIO
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_CONNECTIONSMANAGER::ManageProtocolConnectionsClient()
{
  if(!xmutexprocotolconnections)       return;
  if(!xthreadconnections)              return;
  if(!xthreadconnections->IsRunning()) return;
  if(!xtimerconnections)               return;
  if(!xtimerclienttry)                return;

  ProtocolConnections_DeleteDisconnected();

  if(protocolconnectionsnlimit != DIOPROTOCOL_CONNECTIONS_UNLIMITEDNCONNECTIONS)
    {
      if(!protocolconnectionsnlimit) return;

      if(ProtocolConnections_GetNConnected() >= protocolconnectionsnlimit)
        {
          return;
        }
    }

  if(xtimerclienttry->GetMeasureSeconds() <= DIOPROTOCOL_CONNECTIONS_DEFAULTIMETRYCONNECTIONS) return;

  //DEBUG_PRINT(__L("---------------------------------------------------------------"));

  for(int c=0;c<(int)targetURLs.GetSize();c++)
    {
      if(!xthreadconnections->IsRunning()) break;

      DIOURL* URLclient = (DIOURL*)targetURLs.Get(c);
      if(URLclient)
        {
          bool haveservervalid = false;

          switch(diostreamcfg->GetType())
            {
              case DIOSTREAMTYPE_UNKNOWN    : break;
              case DIOSTREAMTYPE_UART       : break;
              case DIOSTREAMTYPE_USB        : break;
              case DIOSTREAMTYPE_BLUETOOTH  : break;

              case DIOSTREAMTYPE_TCPIP      : { DIOSTREAMTCPIPCONFIG* scfg = (DIOSTREAMTCPIPCONFIG*)diostreamcfg;
                                                XSTRING               address;
                                                if(scfg)
                                                  {
                                                    if(URLclient->IsEmpty() && diostreamenumservers)
                                                      {
                                                        diostreamenumservers->Search();

                                                        while(diostreamenumservers->IsSearching())
                                                          {
                                                            GEN_XSLEEP.MilliSeconds(1);
                                                          }

                                                        diostreamenumservers->StopSearch(true);

                                                        if(diostreamenumservers->AreDevicesAvailable())
                                                          {
                                                            DIOSTREAMDEVICEIP* device = (DIOSTREAMDEVICEIP*)diostreamenumservers->GetDevices()->Get(0);
                                                            if(device) device->GetIP()->GetXString(address);
                                                          }

                                                      } else address = URLclient->Get();

                                                    if(!address.IsEmpty())
                                                      {
                                                        DIOURL* url= new DIOURL();
                                                        if(url)
                                                          {
                                                            (*url) = address.Get();

                                                            url->ResolveURL();
                                                            scfg->GetRemoteURL()->Set(address);
                                                            delete url;

                                                            haveservervalid = true;
                                                          }
                                                      }
                                                  }

                                                break;
                                              }

            }

          if(haveservervalid)
            {
              DIOPROTOCOL_CONNECTION* protocolconnection = new DIOPROTOCOL_CONNECTION(diostreamcfg);
              if(protocolconnection)
                {
                  DIOPROTOCOL* protocol = CreateProtocol();
                  if(protocol)
                    {
                      protocolconnection->SetDIOProtocol(protocol);

                      if(protocolconnection->Connect())
                        {
                          xtimerconnections->Reset();

                          DIOSTREAMTCPIPCONFIG* scfg = (DIOSTREAMTCPIPCONFIG*)diostreamcfg;

                          while(1)
                            {
                              if(protocolconnection->GetDIOProtocol()->IsConnected())
                                {
                                  if(xmutexprocotolconnections) xmutexprocotolconnections->Lock();

                                  protocol->SetConnection(protocolconnection);
                                  protocolconnections.Add(protocolconnection);

                                  if(xmutexprocotolconnections) xmutexprocotolconnections->UnLock();

                                  SendEvent(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_CONNECTEDCONNECTION, protocolconnection);

                                  break;
                                }

                              if((xtimerconnections->GetMeasureSeconds()>=5) || (!xthreadconnections->IsRunning()))
                                {
                                  DeleteProtocol(protocol);
                                  protocol = NULL;

                                  delete protocolconnection;
                                  protocolconnection = NULL;

                                  break;
                                }

                              GEN_XSLEEP.MilliSeconds(50);
                            }

                         XTRACE_PRINTCOLOR(1, __L("Trying to connect to %s [%s]: %s (%d) seconds."),  URLclient->Get(), scfg->GetRemoteURL()->Get(), protocolconnection?__L("Connected!."):__L("Not Connected!."), xtimerconnections->GetMeasureSeconds());
                        }
                       else
                        {
                          DeleteProtocol(protocol);
                          protocol = NULL;

                          delete protocolconnection;
                          protocolconnection = NULL;
                        }
                    }
                   else
                    {
                      delete protocolconnection;
                      protocolconnection = NULL;
                    }
                }
            }
        }
    }

  xtimerclienttry->Reset();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOPROTOCOL_CONNECTIONSMANAGER::ThreadProtocolConnections(void* param)
* @brief      ThreadProtocolConnections
* @ingroup    DATAIO
*
* @param[in]  param :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_CONNECTIONSMANAGER::ThreadProtocolConnections(void* param)
{
  DIOPROTOCOL_CONNECTIONSMANAGER* protocolconnections = (DIOPROTOCOL_CONNECTIONSMANAGER*)param;
  if(!protocolconnections) return;

  if(protocolconnections->isserver)
    {
      protocolconnections->ManageProtocolConnectionsServer();
    }
   else
    {
      protocolconnections->ManageProtocolConnectionsClient();
    }

  int c=0;
  while(c < protocolconnections->ProtocolConnections_GetNAvailable())
    {
      DIOPROTOCOL_CONNECTION* protocolconnection = (DIOPROTOCOL_CONNECTION*)protocolconnections->protocolconnections.Get(c);
      if(protocolconnection)
        {
          DIOPROTOCOL* protocol = protocolconnection->GetDIOProtocol();
          if(protocol)
            {
              if(protocol->IsConnected())
                {
                  if(!protocol->IsInitialized())
                    {
                      if(protocolconnections->isserver)
                        {
                          protocolconnection->SetInUse(true, DIOPROTOCOL_CONNECTIONSINUSEID_INIPROTOCOL);

                          protocol->GetDIOStream()->GetXTimerNotActivity()->Reset();
                          protocolconnections->SendEvent(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_INITPROTOCOL, protocolconnection);
                          if(protocol->IsInitialized()) protocol->CMD_SendIsInitServerProtocol(true);

                          protocolconnection->SetInUse(false, DIOPROTOCOL_CONNECTIONSINUSEID_INIPROTOCOL);
                        }
                       else
                        {
                          XTIMER* GEN_XFACTORY_CREATE(timerout, CreateTimer())
                          
                          while(1)
                            {
                              if(protocolconnection->GetDIOProtocol()->IsDisconnected()) break;
                              if(protocol->IsServerInitialized())                       break;

                              if(timerout)
                                {
                                  if(timerout->GetMeasureSeconds() > 5) break;
                                }

                              GEN_XSLEEP.MilliSeconds(10);
                            }

                          GEN_XFACTORY.DeleteTimer(timerout);


                          if(protocol->IsServerInitialized())
                            {
                              protocolconnection->SetInUse(true, DIOPROTOCOL_CONNECTIONSINUSEID_INIPROTOCOL);

                              protocol->GetDIOStream()->GetXTimerNotActivity()->Reset();
                              protocolconnections->SendEvent(DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT_TYPE_INITPROTOCOL, protocolconnection);

                              protocolconnection->SetInUse(false, DIOPROTOCOL_CONNECTIONSINUSEID_INIPROTOCOL);
                            }
                        }

                     XTRACE_PRINTCOLOR((protocol->IsInitialized()?2:4), __L("Protocol Connection Manager: %s Init Protocol %s") , protocolconnections->isserver?__L("Server"):__L("Client"), protocol->IsInitialized()?__L("Ok!"):__L("ERROR!"));

                      if(!protocol->IsInitialized())
                        {
                          protocolconnections->ProtocolConnections_Disconnect(c);
                        }
                    }
                   else
                    {
                      if(protocol->GetDIOStream()->GetXTimerNotActivity()->GetMeasureSeconds() > DIOPROTOCOL_CONNECTIONS_DEFAULTIMECHECKCONNECTIONS)
                        {
                          XDWORD milliseconds;

                          bool status = protocol->CMD_Ping(milliseconds);
                          if(!status)
                            {
                              protocolconnections->ProtocolConnections_Disconnect(c);

                             XTRACE_PRINTCOLOR(status?1:4, __L("Protocol Connection Manager: Check connection protocol %s"), status?__L("Ok!"):__L("ERROR!"));
                            }
                        }
                    }
                }
            }
        }

      c++;
    }
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOPROTOCOL_CONNECTIONSMANAGER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_CONNECTIONSMANAGER::Clean()
{
  diostreamenumservers            = NULL;
  diostreamcfg                    = NULL;

  applicationversion              = 0;
  applicationsubversion           = 0;
  applicationsubversionerr        = 0;

  isserver                        = false;
  protocolconnectionsnlimit       = 0;

  xthreadconnections              = NULL;
  xtimerconnections               = NULL;
  xtimerclienttry                 = NULL;
  xtimerout                       = NULL;

  xmutexprocotolconnections       = NULL;
}

