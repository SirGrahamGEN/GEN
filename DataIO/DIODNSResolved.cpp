/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIODNSRESOLVED.cpp
*
* @class      DIODNSRESOLVED
* @brief      Data Input/Output Domain Network System (DNS) resolved class
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
#include "XDateTime.h"
#include "XTrace.h"
#include "XTimer.h"

#include "DIOFactory.h"
#include "DIOStreamUDPConfig.h"
#include "DIOStreamUDP.h"
#include "DIODNSProtocol.h"

#include "DIODNSResolved.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

DIODNSRESOLVED* DIODNSRESOLVED::instance = NULL;

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------*/
/*  DIODNSRESOLVED_HOSTRESOLVED                                                                                       */
/*--------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIODNSRESOLVED_HOSTRESOLVED::DIODNSRESOLVED_HOSTRESOLVED()
* @brief      Constructor
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIODNSRESOLVED_HOSTRESOLVED::DIODNSRESOLVED_HOSTRESOLVED()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIODNSRESOLVED_HOSTRESOLVED::~DIODNSRESOLVED_HOSTRESOLVED()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIODNSRESOLVED_HOSTRESOLVED::~DIODNSRESOLVED_HOSTRESOLVED()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIODNSRESOLVED_HOSTRESOLVED::GetHost()
* @brief      GetHost
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIODNSRESOLVED_HOSTRESOLVED::GetHost()
{
  return &host;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIODNSRESOLVED_HOSTRESOLVED::GetIPResolved()
* @brief      GetIPResolved
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIODNSRESOLVED_HOSTRESOLVED::GetIPResolved()
{
  return &IPresolved;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIODNSRESOLVED_HOSTRESOLVED::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIODNSRESOLVED_HOSTRESOLVED::Clean()
{

}



/*--------------------------------------------------------------------------------------------------------------------*/
/*  DIODNSRESOLVED_DNSSERVER                                                                                          */
/*--------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIODNSRESOLVED_DNSSERVER::DIODNSRESOLVED_DNSSERVER()
* @brief      Constructor
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIODNSRESOLVED_DNSSERVER::DIODNSRESOLVED_DNSSERVER()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIODNSRESOLVED_DNSSERVER::~DIODNSRESOLVED_DNSSERVER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIODNSRESOLVED_DNSSERVER::~DIODNSRESOLVED_DNSSERVER()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOIP* DIODNSRESOLVED_DNSSERVER::GetIP()
* @brief      GetIP
* @ingroup    DATAIO
*
* @return     DIOIP* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOIP* DIODNSRESOLVED_DNSSERVER::GetIP()
{
  return &IP;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWORD DIODNSRESOLVED_DNSSERVER::GetPort()
* @brief      GetPort
* @ingroup    DATAIO
*
* @return     XWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XWORD DIODNSRESOLVED_DNSSERVER::GetPort()
{
  return port;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIODNSRESOLVED_DNSSERVER::SetPort(XWORD port)
* @brief      SetPort
* @ingroup    DATAIO
*
* @param[in]  port :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIODNSRESOLVED_DNSSERVER::SetPort(XWORD port)
{
  this->port = port;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIODNSRESOLVED_DNSSERVER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIODNSRESOLVED_DNSSERVER::Clean()
{
  port = 0;
}



/*--------------------------------------------------------------------------------------------------------------------*/
/*  DIODNSRESOLVED                                                                                                    */
/*--------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIODNSRESOLVED::GetIsInstanced()
* @brief      GetIsInstanced
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIODNSRESOLVED::GetIsInstanced()
{
  return instance!=NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIODNSRESOLVED& DIODNSRESOLVED::GetInstance()
* @brief      GetInstance
* @ingroup    DATAIO
*
* @return     DIODNSRESOLVED& :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIODNSRESOLVED& DIODNSRESOLVED::GetInstance()
{
  if(!instance) instance = new DIODNSRESOLVED();

  return (*instance);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIODNSRESOLVED::DelInstance()
* @brief      DelInstance
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIODNSRESOLVED::DelInstance()
{
  if(instance)
    {
      delete instance;
      instance = NULL;

      return true;
    }

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIODNSRESOLVED::ResolveURL(XCHAR* URL, DIOIP& IPresolved, int querytype, XDWORD timeout)
* @brief      ResolveURL
* @ingroup    DATAIO
*
* @param[in]  URL :
* @param[in]  IPresolved :
* @param[in]  querytype :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIODNSRESOLVED::ResolveURL(XCHAR* URL, DIOIP& IPresolved, int querytype, XDWORD timeout)
{
  if(HostResolved_FindIP(URL, IPresolved)) return true;

  if(!listhostresolved.GetSize())
    {
      GEN_DIODNSRESOLVED.HostResolved_Add(__L("localhost"), __L("127.0.0.1"));
    }

  DIOURL url;
  url = URL;  

  if(url.IsAURLResolved())
    {  
      IPresolved.Set(URL);  
    }
   else
    { 
      XTIMER* GEN_XFACTORY_CREATE(xtimerout, CreateTimer());
      if(xtimerout) 
        { 
          bool status;

          if(!listDNSservers.GetSize())
            {
              GEN_DIODNSRESOLVED.DNSServer_AddDNSServer(__L("8.8.8.8"));
              GEN_DIODNSRESOLVED.DNSServer_AddDNSServer(__L("8.8.4.4"));
            }

          DIODNSPROTOCOL* dnsprotocol = new DIODNSPROTOCOL();
          if(dnsprotocol)
            {
              for(XDWORD c=0; c<listDNSservers.GetSize(); c++)
                {
                  if(xtimerout->GetMeasureSeconds() > (timeout * listDNSservers.GetSize()))
                    {
                      status = false;
                      break;
                    }

                  DIODNSRESOLVED_DNSSERVER* serverDNS = listDNSservers.Get(c);
                  if(serverDNS)
                    {
                      XSTRING serverIP;

                      serverDNS->GetIP()->GetXString(serverIP);

                      dnsprotocol->SetServer(serverIP.Get(), serverDNS->GetPort());

                      status = dnsprotocol->ResolveURL(URL, IPresolved, querytype, timeout);
                      if(status) break;
                    }
                }

              delete dnsprotocol;
            }

          GEN_XFACTORY.DeleteTimer(xtimerout);
        }
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIODNSRESOLVED::ResolveURL(DIOURL& URL, DIOIP& IPresolved, int querytype, XDWORD timeout)
* @brief      ResolveURL
* @ingroup    DATAIO
*
* @param[in]  URL :
* @param[in]  IPresolved :
* @param[in]  querytype :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIODNSRESOLVED::ResolveURL(DIOURL& URL, DIOIP& IPresolved, int querytype, XDWORD timeout)
{
  return ResolveURL(URL.Get(), IPresolved, querytype, timeout);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIODNSRESOLVED::ResolveURL(XSTRING& URL, DIOIP& IPresolved, int querytype, XDWORD timeout)
* @brief      ResolveURL
* @ingroup    DATAIO
*
* @param[in]  URL :
* @param[in]  IPresolved :
* @param[in]  querytype :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIODNSRESOLVED::ResolveURL(XSTRING& URL, DIOIP& IPresolved, int querytype, XDWORD timeout)
{
  return ResolveURL(URL.Get(), IPresolved, querytype, timeout);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIODNSRESOLVED::DNSServer_AddDNSServer(XCHAR* server)
* @brief      DNSServer_AddDNSServer
* @ingroup    DATAIO
*
* @param[in]  server :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIODNSRESOLVED::DNSServer_AddDNSServer(XCHAR* server)
{
  if(!server) return false;

  DIODNSRESOLVED_DNSSERVER* DNSserver = new DIODNSRESOLVED_DNSSERVER();
  if(!DNSserver) return false;

  XSTRING string;
  XSTRING IPstring;
  int     port = 0;

  string = server;
  IPstring.AdjustSize(_MAXSTR);
  string.UnFormat(__L("%s:%d"), IPstring.Get(), &port);
  IPstring.AdjustSize();

  DNSserver->GetIP()->Set(IPstring);
  DNSserver->SetPort(port);

  return listDNSservers.Add(DNSserver);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIODNSRESOLVED::DNSServer_AddDNSServer(XSTRING& server)
* @brief      DNSServer_AddDNSServer
* @ingroup    DATAIO
*
* @param[in]  server :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIODNSRESOLVED::DNSServer_AddDNSServer(XSTRING& server)
{
  return DNSServer_AddDNSServer(server.Get());
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIODNSRESOLVED::DNSServer_AddDNSServer(XBYTE* serverIP, XWORD port)
* @brief      DNSServer_AddDNSServer
* @ingroup    DATAIO
*
* @param[in]  serverIP :
* @param[in]  port :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIODNSRESOLVED::DNSServer_AddDNSServer(XBYTE* serverIP, XWORD port)
{
  DIODNSRESOLVED_DNSSERVER* DNSserver = new DIODNSRESOLVED_DNSSERVER();
  if(!DNSserver) return false;

  DNSserver->GetIP()->Set(serverIP);
  DNSserver->SetPort(port);

  return listDNSservers.Add(DNSserver);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIODNSRESOLVED::DNSServer_AddDNSServer(DIOIP& serverIP, XWORD port)
* @brief      DNSServer_AddDNSServer
* @ingroup    DATAIO
*
* @param[in]  serverIP :
* @param[in]  port :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIODNSRESOLVED::DNSServer_AddDNSServer(DIOIP& serverIP, XWORD port)
{
  DIODNSRESOLVED_DNSSERVER* DNSserver = new DIODNSRESOLVED_DNSSERVER();
  if(!DNSserver) return false;

  DNSserver->GetIP()->Set(serverIP.Get());
  DNSserver->SetPort(port);

  return listDNSservers.Add(DNSserver);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XVECTOR<DIOIP*>* DIODNSRESOLVED::DNSServer_GetList()
* @brief      DNSServer_GetList
* @ingroup    DATAIO
*
* @return     XVECTOR<DIOIP*>* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<DIODNSRESOLVED_DNSSERVER*>* DIODNSRESOLVED::DNSServer_GetList()
{
  return &listDNSservers;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIODNSRESOLVED::HostResolved_FindIP(XCHAR* host, DIOIP& IPresolved)
* @brief      HostResolved_FindIP
* @ingroup    DATAIO
*
* @param[in]  host :
* @param[in]  IPresolved :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIODNSRESOLVED::HostResolved_FindIP(XCHAR* host, DIOIP& IPresolved)
{
  bool status = false;

  for(XDWORD c=0; c<listhostresolved.GetSize(); c++)
    {
      DIODNSRESOLVED_HOSTRESOLVED* hostresolved = listhostresolved.Get(c);
      if(hostresolved)
        {
          if(!hostresolved->GetHost()->Compare(host, true))
            {
              IPresolved.Set(hostresolved->GetIPResolved()->Get());
              status = true;
              break;
            }
        }
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIODNSRESOLVED::HostResolved_FindIP(XSTRING& host, DIOIP& IPresolved)
* @brief      HostResolved_FindIP
* @ingroup    DATAIO
*
* @param[in]  host :
* @param[in]  IPresolved :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIODNSRESOLVED::HostResolved_FindIP(XSTRING& host, DIOIP& IPresolved)
{
  return HostResolved_FindIP(host.Get(), IPresolved);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIODNSRESOLVED::DNSServer_DeleteAllList()
* @brief      DNSServer_DeleteAllList
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIODNSRESOLVED::DNSServer_DeleteAllList()
{
  listDNSservers.DeleteContents();
  listDNSservers.DeleteAll();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIODNSRESOLVED::HostResolved_Add(XCHAR* host, XCHAR* IPresolved)
* @brief      HostResolved_Add
* @ingroup    DATAIO
*
* @param[in]  host :
* @param[in]  IPresolved :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIODNSRESOLVED::HostResolved_Add(XCHAR* host, XCHAR* IPresolved)
{
  DIODNSRESOLVED_HOSTRESOLVED* hostresolved = new DIODNSRESOLVED_HOSTRESOLVED();
  if(!hostresolved) return false;

  hostresolved->GetHost()->Set(host);
  hostresolved->GetIPResolved()->Set(IPresolved);

  return listhostresolved.Add(hostresolved);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIODNSRESOLVED::HostResolved_Add(XSTRING& host, XSTRING& IPresolved)
* @brief      HostResolved_Add
* @ingroup    DATAIO
*
* @param[in]  host :
* @param[in]  IPresolved :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIODNSRESOLVED::HostResolved_Add(XSTRING& host, XSTRING& IPresolved)
{
  return HostResolved_Add(host.Get(), IPresolved.Get());
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XVECTOR<DIODNSRESOLVED_HOSTRESOLVED*>* DIODNSRESOLVED::HostResolved_GetList()
* @brief      HostResolved_GetList
* @ingroup    DATAIO
*
* @return     XVECTOR<DIODNSRESOLVED_HOSTRESOLVED*>* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<DIODNSRESOLVED_HOSTRESOLVED*>*  DIODNSRESOLVED::HostResolved_GetList()
{
  return &listhostresolved;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIODNSRESOLVED::HostResolved_DeleteAllList()
* @brief      HostResolved_DeleteAllList
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIODNSRESOLVED::HostResolved_DeleteAllList()
{
  listhostresolved.DeleteContents();
  listhostresolved.DeleteAll();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIODNSRESOLVED::DIODNSRESOLVED()
* @brief      Constructor
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIODNSRESOLVED::DIODNSRESOLVED()
{
  Clean();

  xmutexresolved = GEN_XFACTORY.Create_Mutex();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIODNSRESOLVED::~DIODNSRESOLVED()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIODNSRESOLVED::~DIODNSRESOLVED()
{
  if(xmutexresolved)
    {
      GEN_XFACTORY.Delete_Mutex(xmutexresolved);       
    }

  DNSServer_DeleteAllList();
  HostResolved_DeleteAllList();

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIODNSRESOLVED::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIODNSRESOLVED::Clean()
{
  xmutexresolved = NULL;
}
