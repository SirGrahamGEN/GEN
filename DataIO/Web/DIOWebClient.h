/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOWebClient.h
* 
* @class      DIOWEBCLIENT
* @brief      Data Input/Output Web Client class
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

#ifndef _DIOWEBCLIENT_H_
#define _DIOWEBCLIENT_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XBuffer.h"
#include "XPath.h"
#include "XSubject.h"

#include "DIOURL.h"
#include "DIOWebHeader.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


#define DIOWEBCLIENT_TIMEOUT            8
#define DIOWEBCLIENT_MAXSIZEBUFFER      (64*1024)
#define DIOWEBCLIENT_DEFAULTPORT        80

#define DIOWEBCLIENT_DEFAULTUSERAGENT   __L("User-Agent: Mozilla 5.0\r\n")

enum DIOWEBCLIENT_AUTHENTICATION_METHOD
{
  DIOWEBCLIENT_AUTHENTICATION_METHOD_UNKNOWN               = 0 ,
  DIOWEBCLIENT_AUTHENTICATION_METHOD_BASIC                     ,
  DIOWEBCLIENT_AUTHENTICATION_METHOD_DIGEST                    ,      
};


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class XTIMER;
class XFILE;
class DIOSTREAMTCPIPCONFIG;
class DIOSTREAMTCPIP;


class DIOWEBCLIENT_HEADER : public DIOWEBHEADER
{
  public:
                                              DIOWEBCLIENT_HEADER               ();
    virtual                                  ~DIOWEBCLIENT_HEADER               ();

    bool                                      GetMethod                         (XSTRING& method);
    bool                                      GetResource                       (XSTRING& resource);
    int                                       GetVersion                        ();
    int                                       GetSubVersion                     ();
    int                                       GetResultServer                   ();

    XQWORD                                    GetContentLength                  ();
    bool                                      GetETag                           (XSTRING& etag);
    bool                                      GetWWWAuthenticate                (XSTRING& authenticate);

  private:

    void                                      Clean                             ();
};


class DIOWEBCLIENT : public XSUBJECT
{
  public:
                                              DIOWEBCLIENT                      (XDWORD maxsizebuffer = DIOWEBCLIENT_MAXSIZEBUFFER);
    virtual                                  ~DIOWEBCLIENT                      ();

    int                                       Get_Port                          ();
    void                                      Set_Port                          (int port);



    DIOURL*                                   GetProxyURL                       ();
    int                                       GetProxyPort                      ();
    void                                      SetProxyPort                      (int port);


    DIOWEBCLIENT_AUTHENTICATION_METHOD        GetAuthenticationMethod           ();
    void                                      SetAuthenticationMethod           (DIOWEBCLIENT_AUTHENTICATION_METHOD authenticationmethod);

    XSTRING*                                  GetLogin                          ();
    XSTRING*                                  GetPassword                       ();

    DIOSTREAMTCPIPCONFIG*                     GetStreamCFG                      ();

    DIOWEBCLIENT_HEADER*                      GetHeader                         ();
    
    bool                                      IsActiveDoStopHTTPError           ();
    void                                      DoStopHTTPError                   (bool activate);

    bool                                      Get                               (DIOURL& url, XBUFFER& tobuffer , XCHAR* addheader = NULL, int timeout = DIOWEBCLIENT_TIMEOUT, XSTRING* localIP = NULL);
    bool                                      Get                               (XCHAR*  url, XBUFFER& tobuffer , XCHAR* addheader = NULL, int timeout = DIOWEBCLIENT_TIMEOUT, XSTRING* localIP = NULL);
    bool                                      Get                               (DIOURL& url, XPATH& pathfile   , XCHAR* addheader = NULL, int timeout = DIOWEBCLIENT_TIMEOUT, XSTRING* localIP = NULL);
    bool                                      Get                               (XCHAR*  url, XPATH& pathfile   , XCHAR* addheader = NULL, int timeout = DIOWEBCLIENT_TIMEOUT, XSTRING* localIP = NULL);

    bool                                      Put                               (DIOURL& url, XBUFFER& tobuffer , XCHAR* addheader = NULL, int timeout = DIOWEBCLIENT_TIMEOUT, XSTRING* localIP = NULL);
    bool                                      Put                               (XCHAR*  url, XBUFFER& tobuffer , XCHAR* addheader = NULL, int timeout = DIOWEBCLIENT_TIMEOUT, XSTRING* localIP = NULL);
    bool                                      Put                               (DIOURL& url, XPATH& pathfile   , XCHAR* addheader = NULL, int timeout = DIOWEBCLIENT_TIMEOUT, XSTRING* localIP = NULL);
    bool                                      Put                               (XCHAR*  url, XPATH& pathfile   , XCHAR* addheader = NULL, int timeout = DIOWEBCLIENT_TIMEOUT, XSTRING* localIP = NULL);

    bool                                      Post                              (DIOURL& url, XBUFFER& tobuffer , XBUFFER* postdata = NULL, XCHAR* addheader = NULL, int timeout = DIOWEBCLIENT_TIMEOUT, XSTRING* localIP = NULL);
    bool                                      Post                              (XCHAR*  url, XBUFFER& tobuffer , XBUFFER* postdata = NULL, XCHAR* addheader = NULL, int timeout = DIOWEBCLIENT_TIMEOUT, XSTRING* localIP = NULL);
    bool                                      Post                              (DIOURL& url, XPATH& pathfile   , XBUFFER* postdata = NULL, XCHAR* addheader = NULL, int timeout = DIOWEBCLIENT_TIMEOUT, XSTRING* localIP = NULL);
    bool                                      Post                              (XCHAR*  url, XPATH& pathfile   , XBUFFER* postdata = NULL, XCHAR* addheader = NULL, int timeout = DIOWEBCLIENT_TIMEOUT, XSTRING* localIP = NULL);
   
  private:

    bool                                      MakeOperation                     (DIOWEBHEADER_METHOD method, DIOURL& url, XBUFFER* postdata, XCHAR* addhead, int timeout, XSTRING* localIP, bool istobuffer, void* to);

    bool                                      GetSubStringWWWWAuthenticate      (XSTRING& www_authenticate, XCHAR* field, XSTRING& value, bool betweenquotation = true);

    void                                      Clean                             ();

    XDWORD                                    maxsizebuffer;

    XTIMER*                                   timerout;

    DIOSTREAMTCPIPCONFIG*                     diostreamcfg;
    DIOSTREAMTCPIP*                           diostream;

    int                                       port;

    DIOURL                                    proxyurl;
    int                                       proxyport;

    DIOWEBCLIENT_AUTHENTICATION_METHOD        authenticationmethod;

    XSTRING                                   login;
    XSTRING                                   password;

    DIOWEBCLIENT_HEADER                       header;
    bool                                      dostophttperror;
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

