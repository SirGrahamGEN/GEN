/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIODNSRESOLVED.h
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

#ifndef _DIODNSRESOLVED_H_
#define _DIODNSRESOLVED_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XFactory.h"
#include "XVector.h"

#include "DIOIP.h"
#include "DIOURL.h"

#include "DIODNSProtocol.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/


class DIODNSRESOLVED_HOSTRESOLVED
{
  public:
                                            DIODNSRESOLVED_HOSTRESOLVED     ();
    virtual                                ~DIODNSRESOLVED_HOSTRESOLVED     ();

    XSTRING*                                GetHost                         ();
    XSTRING*                                GetIPResolved                   ();

  private:

    void                                    Clean                           ();

    XSTRING                                 host;
    XSTRING                                 IPresolved;
};



class DIODNSRESOLVED_DNSSERVER
{
  public:
                                            DIODNSRESOLVED_DNSSERVER        ();
    virtual                                ~DIODNSRESOLVED_DNSSERVER        ();

    DIOIP*                                  GetIP                           ();

    XWORD                                   GetPort                         ();
    void                                    SetPort                         (XWORD port);

  private:

    void                                    Clean                           ();

    DIOIP                                   IP;
    XWORD                                   port;
};




class DIODNSRESOLVED
{
  public:

    static bool                             GetIsInstanced                  ();
    static DIODNSRESOLVED&                  GetInstance                     ();
    static bool                             DelInstance                     ();

    bool                                    ResolveURL                      (XCHAR* URL, DIOIP& IPresolved, int querytype = DIODNSPROTOCOL_TYPEQUERY_A, XDWORD timeout = DIODNSPROTOCOL_DEFAULTTIMEOUT);
    bool                                    ResolveURL                      (DIOURL& URL, DIOIP& IPresolved, int querytype = DIODNSPROTOCOL_TYPEQUERY_A, XDWORD timeout = DIODNSPROTOCOL_DEFAULTTIMEOUT);
    bool                                    ResolveURL                      (XSTRING& URL, DIOIP& IPresolved, int querytype = DIODNSPROTOCOL_TYPEQUERY_A, XDWORD timeout = DIODNSPROTOCOL_DEFAULTTIMEOUT);

    bool                                    DNSServer_AddDNSServer          (XCHAR* server);
    bool                                    DNSServer_AddDNSServer          (XSTRING& server);
    bool                                    DNSServer_AddDNSServer          (XBYTE* serverIP, XWORD port);
    bool                                    DNSServer_AddDNSServer          (DIOIP& serverIP, XWORD port);
    bool                                    DNSServer_IsIPonList            (DIOIP& serverIP);
    XVECTOR<DIODNSRESOLVED_DNSSERVER*>*     DNSServer_GetList               ();
    bool                                    DNSServer_DeleteAllList         ();

    bool                                    HostResolved_Add                (XCHAR* host, XCHAR* IPresolved);
    bool                                    HostResolved_Add                (XSTRING& host, XSTRING& IPresolved);
    XVECTOR<DIODNSRESOLVED_HOSTRESOLVED*>*  HostResolved_GetList            ();
    bool                                    HostResolved_FindIP             (XCHAR* host, DIOIP& IPresolved);
    bool                                    HostResolved_FindIP             (XSTRING& host, DIOIP& IPresolved);
    bool                                    HostResolved_DeleteAllList      ();

  private:
                                            DIODNSRESOLVED                  ();
                                            DIODNSRESOLVED                  (DIODNSRESOLVED const&);        // Don't implement
    virtual                                ~DIODNSRESOLVED                  ();

    void                                    operator =                      (DIODNSRESOLVED const&);        // Don't implement

    void                                    Clean                           ();

    static DIODNSRESOLVED*                  instance;

    XVECTOR<DIODNSRESOLVED_DNSSERVER*>      listDNSservers;
    XVECTOR<DIODNSRESOLVED_HOSTRESOLVED*>   listhostresolved;
    
};



/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif



