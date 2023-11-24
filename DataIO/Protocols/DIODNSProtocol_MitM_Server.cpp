/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIODNSProtocol_MitM_Server.cpp
* 
* @class      DIODNSPROTOCOL_MITM_SERVER
* @brief      Data Input/Output Domain Network System (DNS) protocol Man-in-the-Middle (MitM) Server class
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

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIODNSProtocol_MitM_Server.h"

#include "DIOFactory.h"
#include "DIODNSProtocol_MitM_Server_XEvent.h"
#include "DIOStreamUDP.h"

#include "XFactory.h"
#include "XSleep.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIODNSPROTOCOL_MITM_SERVER::DIODNSPROTOCOL_MITM_SERVER()
* @brief      Constructor
* @ingroup    DATAIO
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIODNSPROTOCOL_MITM_SERVER::DIODNSPROTOCOL_MITM_SERVER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIODNSPROTOCOL_MITM_SERVER::~DIODNSPROTOCOL_MITM_SERVER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIODNSPROTOCOL_MITM_SERVER::~DIODNSPROTOCOL_MITM_SERVER()
{
  End();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIODNSPROTOCOL_MITM_SERVER::Ini()
* @brief      Ini
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIODNSPROTOCOL_MITM_SERVER::Ini()
{
  RegisterEvent(DIODNSPROTOCOL_MITM_SERVER_XEVENT_TYPE_ASKDNS);

  servermutex = GEN_XFACTORY.Create_Mutex();
  if(!servermutex)
    {
      return false;
    }

  XSTRING servercfgstr;

  diostreamudpcfg.SetMode(DIOSTREAMMODE_SERVER);
  diostreamudpcfg.GetRemoteURL()->Set(__L("localhost"));  
  diostreamudpcfg.SetRemotePort(DIODNSPROTOCOL_DEFAULTPORT);  
  diostreamudpcfg.SetIsUsedDatagrams(true);
  
	diostreamudp = (DIOSTREAMUDP*)GEN_DIOFACTORY.CreateStreamIO(&diostreamudpcfg);
  if(!diostreamudp)
    {
      GEN_XFACTORY.Delete_Mutex(servermutex);
      servermutex = NULL;
      
      return false;
    }

  AddDNSServer(__L("8.8.8.8"));
  AddDNSServer(__L("8.8.4.4"));
  AddDNSServer(__L("64.6.64.6"));
  AddDNSServer(__L("64.6.65.6"));
  
  serverthread = GEN_XFACTORY.CreateThread(XTHREADGROUPID_DIODNSRESOLVED, __L("DIODNSPROTOCOL_MITM_SERVER::Ini"), DIODNSPROTOCOL_MITM_SERVER::ThreadServer, this);  
  if(!serverthread)
    {
      GEN_XFACTORY.Delete_Mutex(servermutex);
      servermutex = NULL;

      GEN_DIOFACTORY.DeleteStreamIO(diostreamudp);
      diostreamudp = NULL;

      return false;
    }

  return serverthread->Ini(false);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIODNSPROTOCOL_MITM_SERVER::Activate(bool active)
* @brief      Activate
* @ingroup    DATAIO
* 
* @param[in]  active : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIODNSPROTOCOL_MITM_SERVER::Activate(bool active)
{
  if(active)
    {  
      if(!diostreamudp->Open())
        {
          return false;
        }

      if(!diostreamudp->WaitToConnected(3000))
        {
          return false;
        }       
    }
   else
    {
      diostreamudp->Close();
    }

  if(!serverthread)
    {
      return false; 
    }

  return serverthread->Run(active);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIODNSPROTOCOL_MITM_SERVER::Update()
* @brief      Update
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIODNSPROTOCOL_MITM_SERVER::Update()
{ 
  if(!diostreamudp)
    {
      return false;
    }

  XSTRING  address;
  XWORD    port;
  XBUFFER  data;
  bool     status = false;

  if(!diostreamudp->ReadDatagram(address, port, data))
    {
      return false;
    }
      
  DIODNSPROTOCOL_HEADER*    header    = NULL;    
  char*                     nameURL   = NULL;     
  XSTRING                   nameURLstr;     
  DIODNSPROTOCOL_QUESTION*  question  = NULL;
  XBUFFER                   sendbuffer;
  XBUFFER                   receivedbuffer;
          
  header      = (DIODNSPROTOCOL_HEADER*)data.Get();
  nameURL     = (char*)data.Get() + sizeof(DIODNSPROTOCOL_HEADER);   
  nameURLstr  = nameURL;
  question    = (DIODNSPROTOCOL_QUESTION*)data.Get() + sizeof(DIODNSPROTOCOL_HEADER) + nameURLstr.GetSize()+1;

  sendbuffer.Add((XBYTE*)header, sizeof(DIODNSPROTOCOL_HEADER)); 
  sendbuffer.Add((XBYTE*)nameURL, nameURLstr.GetSize()+1);   
  sendbuffer.Add((XBYTE*)question, sizeof(DIODNSPROTOCOL_QUESTION));   

  DIODNSPROTOCOL_MITM_SERVER_XEVENT xevent(this, DIODNSPROTOCOL_MITM_SERVER_XEVENT_TYPE_ASKDNS);
  xevent.GetOriginIP()->Set(address);
  xevent.GetAskedBuffer()->CopyFrom(data);
  PostEvent(&xevent);

  for(XDWORD c=0; c<dnsservers.GetSize(); c++)
    {
      DIODNSRESOLVER_DNSSERVER* DNSserver = dnsservers.Get(c);
      if(DNSserver)
        {
          if(Detour(DNSserver, sendbuffer, receivedbuffer))
            {
              if(diostreamudp->WriteDatagram(address, port, receivedbuffer))                        
                {
                  status = true;
                  break;
                }
            }        
        }
    }
    
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIODNSPROTOCOL_MITM_SERVER::End()
* @brief      End
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIODNSPROTOCOL_MITM_SERVER::End()
{
  DeRegisterEvent(DIODNSPROTOCOL_MITM_SERVER_XEVENT_TYPE_ASKDNS);

  if(serverthread)
    {
      serverthread->End();

      GEN_XFACTORY.DeleteThread(XTHREADGROUPID_DIODNSRESOLVED, serverthread);
      serverthread = NULL;
    }

  if(diostreamudp)
    {
      diostreamudp->Close();

      GEN_DIOFACTORY.DeleteStreamIO(diostreamudp);
      diostreamudp = NULL;
    }
    
  if(servermutex)
    {
      GEN_XFACTORY.Delete_Mutex(servermutex);
      servermutex = NULL;
    }

  DeleteAllDNSServers();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIODNSPROTOCOL_MITM_SERVER::AddDNSServer(XCHAR* server, XWORD port)
* @brief      AddDNSServer
* @ingroup    DATAIO
* 
* @param[in]  server : 
* @param[in]  port : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIODNSPROTOCOL_MITM_SERVER::AddDNSServer(XCHAR* server, XWORD port)
{
  if(!server)
    {
      return false;
    }

  DIODNSRESOLVER_DNSSERVER* dnsserver = new DIODNSRESOLVER_DNSSERVER();
  if(!dnsserver)
    {
      return false;
    }

  dnsserver->GetIP()->Set(server);
  dnsserver->SetPort(port);

  return dnsservers.Add(dnsserver);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIODNSPROTOCOL_MITM_SERVER::AddDNSServer(XSTRING& server, XWORD port)
* @brief      AddDNSServer
* @ingroup    DATAIO
* 
* @param[in]  server : 
* @param[in]  port : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIODNSPROTOCOL_MITM_SERVER::AddDNSServer(XSTRING& server, XWORD port)
{
  return AddDNSServer(server.Get(), port);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIODNSPROTOCOL_MITM_SERVER::AddDNSServer(XBYTE* serverIP, XWORD port)
* @brief      AddDNSServer
* @ingroup    DATAIO
* 
* @param[in]  serverIP : 
* @param[in]  port : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIODNSPROTOCOL_MITM_SERVER::AddDNSServer(XBYTE* serverIP, XWORD port)
{
  if(!serverIP)
    {
      return false;
    }

  DIODNSRESOLVER_DNSSERVER* dnsserver = new DIODNSRESOLVER_DNSSERVER();
  if(!dnsserver)
    {
      return false;
    }

  dnsserver->GetIP()->Set(serverIP);
  dnsserver->SetPort(port);

  return dnsservers.Add(dnsserver);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIODNSPROTOCOL_MITM_SERVER::AddDNSServer(DIOIP& serverIP, XWORD port)
* @brief      AddDNSServer
* @ingroup    DATAIO
* 
* @param[in]  serverIP : 
* @param[in]  port : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIODNSPROTOCOL_MITM_SERVER::AddDNSServer(DIOIP& serverIP, XWORD port)
{
  DIODNSRESOLVER_DNSSERVER* dnsserver = new DIODNSRESOLVER_DNSSERVER();
  if(!dnsserver)
    {
      return false;
    }

  dnsserver->GetIP()->Set(serverIP.Get());
  dnsserver->SetPort(port);

  return dnsservers.Add(dnsserver);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIODNSPROTOCOL_MITM_SERVER::DeleteAllDNSServers()
* @brief      DeleteAllDNSServers
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIODNSPROTOCOL_MITM_SERVER::DeleteAllDNSServers()
{
  if(dnsservers.IsEmpty())
    {
      return false;
    }

  dnsservers.DeleteContents();
  dnsservers.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XMUTEX* DIODNSPROTOCOL_MITM_SERVER::GetServerMutex()
* @brief      GetServerMutex
* @ingroup    DATAIO
* 
* @return     XMUTEX* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XMUTEX* DIODNSPROTOCOL_MITM_SERVER::GetServerMutex()
{
  return servermutex;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIODNSPROTOCOL_MITM_SERVER::Detour(DIODNSRESOLVER_DNSSERVER* DNSserver, XBUFFER& sendbuffer, XBUFFER& receivedbuffer)
* @brief      Detour
* @ingroup    DATAIO
* 
* @param[in]  DNSserver : 
* @param[in]  sendbuffer : 
* @param[in]  receivedbuffer : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIODNSPROTOCOL_MITM_SERVER::Detour(DIODNSRESOLVER_DNSSERVER* DNSserver, XBUFFER& sendbuffer, XBUFFER& receivedbuffer)
{
  if(!DNSserver)
    {
      return false;
    }

  DIOSTREAMUDPCONFIG   dioudpcfg;
	DIOSTREAMUDP*				 dioudp;
  XSTRING              remoteIP; 
  bool                 status = false;

  DNSserver->GetIP()->GetXString(remoteIP);

  dioudpcfg.SetMode(DIOSTREAMMODE_CLIENT);
  dioudpcfg.SetIsUsedDatagrams(true);
  
	dioudp = (DIOSTREAMUDP*)GEN_DIOFACTORY.CreateStreamIO(&dioudpcfg);
  if(dioudp)
    {
      if(dioudp->Open())
        {          
          if(dioudp->WaitToConnected(100))
            {            
              dioudp->WriteDatagram(remoteIP, DNSserver->GetPort(), sendbuffer);

              if(dioudp->WaitToFilledReadingBuffer(DIOSTREAM_SOMETHINGTOREAD, 300))
                {
                  XSTRING  address; 
                  XWORD    port;
      
                  status = dioudp->ReadDatagram(address, port, receivedbuffer);   
                }
            }

          dioudp->Close();
        }

      GEN_DIOFACTORY.DeleteStreamIO(dioudp);  
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIODNSPROTOCOL_MITM_SERVER::ThreadServer(void* param)
* @brief      ThreadServer
* @ingroup    DATAIO
* 
* @param[in]  param : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIODNSPROTOCOL_MITM_SERVER::ThreadServer(void* param)
{
  DIODNSPROTOCOL_MITM_SERVER* mitm_server = (DIODNSPROTOCOL_MITM_SERVER*)param;
  if(!mitm_server)
    {
      return;
    }

  if(mitm_server->GetServerMutex())
    {
      mitm_server->GetServerMutex()->Lock();
    }

  mitm_server->Update();
    
  if(mitm_server->GetServerMutex())
    {
      mitm_server->GetServerMutex()->UnLock();
    }

}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIODNSPROTOCOL_MITM_SERVER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIODNSPROTOCOL_MITM_SERVER::Clean()
{
  serverthread    = NULL;
  servermutex     = NULL;   

  diostreamudp    = NULL;
}


#pragma endregion


