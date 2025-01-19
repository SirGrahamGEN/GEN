/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOWebClient.cpp
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIOWebClient.h"

#include "XFactory.h"
#include "XTimer.h"
#include "XPath.h"
#include "XFile.h"
#include "XTrace.h"

#include "HashMD5.h"

#include "DIOFactory.h"
#include "DIOURL.h"
#include "DIOStreamTCPIPConfig.h"
#include "DIOStreamTCPIP.h"
#include "DIOWebClient_XEvent.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


#pragma region CLASS_DIOWEBCLIENT_HEADER


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBCLIENT_HEADER::DIOWEBCLIENT_HEADER()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBCLIENT_HEADER::DIOWEBCLIENT_HEADER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBCLIENT_HEADER::~DIOWEBCLIENT_HEADER()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBCLIENT_HEADER::~DIOWEBCLIENT_HEADER()
{
  DeleteAllLines();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBCLIENT_HEADER::GetMethod(XSTRING& method)
* @brief      Get method
* @ingroup    DATAIO
*
* @param[in]  method :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBCLIENT_HEADER::GetMethod(XSTRING& method)
{
  if(!GetFormat(false, 0, &method)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBCLIENT_HEADER::GetResource(XSTRING& resource)
* @brief      Get resource
* @ingroup    DATAIO
*
* @param[in]  resource :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBCLIENT_HEADER::GetResource(XSTRING& resource)
{
  if(!GetFormat(false, 1, &resource)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOWEBCLIENT_HEADER::GetVersion()
* @brief      Get version
* @ingroup    DATAIO
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOWEBCLIENT_HEADER::GetVersion()
{
  int data = 0;

  if(!GetFormat(false, 2, &data)) return false;

  return data;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOWEBCLIENT_HEADER::GetSubVersion()
* @brief      Get sub version
* @ingroup    DATAIO
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOWEBCLIENT_HEADER::GetSubVersion()
{
  int data = 0;

  if(!GetFormat(false, 3, &data)) return false;

  return data;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOWEBCLIENT_HEADER::GetResultServer()
* @brief      Get result server
* @ingroup    DATAIO
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOWEBCLIENT_HEADER::GetResultServer()
{
  int data = 0;

  if(!GetFormat(true, 2, &data)) return false;

  return data;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XQWORD DIOWEBCLIENT_HEADER::GetContentLength()
* @brief      Get content length
* @ingroup    DATAIO
*
* @return     XQWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XQWORD DIOWEBCLIENT_HEADER::GetContentLength()
{
  XQWORD contentlength = 0;

  for(XDWORD c=0; c<lines.GetSize(); c++)
    {
      XSTRING* line = lines.Get(c);
      if(line)
        {
          if(line->Find(DIOWEBHEADER_CONTENT_LENGTH, true) != XSTRING_NOTFOUND)
            {
              XSTRING sizestr;

              int index = line->Find(__L(":"), true);
              if(index != XSTRING_NOTFOUND)  line->Copy(index+1, sizestr);

              sizestr.DeleteCharacter(__C(' '));

              contentlength = sizestr.ConvertToQWord();

              if(contentlength !=-1) break;
            }
        }
    }

  return contentlength;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBCLIENT_HEADER::GetETag(XSTRING& etag)
* @brief      Get E tag
* @ingroup    DATAIO
*
* @param[in]  etag :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBCLIENT_HEADER::GetETag(XSTRING& etag)
{
  etag.Empty();

  XCHAR* string = GetFieldValue(DIOWEBHEADER_ETAG);
  if(string)  etag = string;

  return etag.GetSize()?true:false;

  /*
  for(XDWORD c=0; c<lines.GetSize(); c++)
    {
      XSTRING* line = lines.Get(c);
      if(line)
        {
          if(line.Find(DIOWEBHEADER_ETAG, true) != XSTRING_NOTFOUND)
            {
              int index = line.Find(__L(":"), true);
              if(index != XSTRING_NOTFOUND)  line.Copy(index+1, etag);
            }
        }
    }

  return etag.GetSize()?true:false;
  */
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOWEBCLIENT_HEADER::GetWWWAuthenticate(XSTRING& authenticate)
* @brief      Get WWW authenticate
* @ingroup    DATAIO
* 
* @param[in]  authenticate : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBCLIENT_HEADER::GetWWWAuthenticate(XSTRING& authenticate)
{
  authenticate.Empty();

  XCHAR* string = GetFieldValue(DIOWEBHEADER_WWW_AUTHENTICATE);
  if(string)  authenticate = string;

  return authenticate.GetSize()?true:false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBCLIENT_HEADER::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBCLIENT_HEADER::Clean()
{

}


#pragma endregion


#pragma region CLASS_DIOWEBCLIENT


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBCLIENT::DIOWEBCLIENT(XDWORD maxsizebuffer)
* @brief      Constructor of class
* @ingroup    DATAIO
*
* @param[in]  maxsizebuffer :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBCLIENT::DIOWEBCLIENT(XDWORD maxsizebuffer)
{
  Clean();

  this->maxsizebuffer = maxsizebuffer;

  RegisterEvent(DIOWEBCLIENT_XEVENT_TYPE_OPENWEB);
  RegisterEvent(DIOWEBCLIENT_XEVENT_TYPE_WRITEHEADER);
  RegisterEvent(DIOWEBCLIENT_XEVENT_TYPE_SENDPOSTDATA);
  RegisterEvent(DIOWEBCLIENT_XEVENT_TYPE_READHEADER);
  RegisterEvent(DIOWEBCLIENT_XEVENT_TYPE_READBODYBLOCK);
  RegisterEvent(DIOWEBCLIENT_XEVENT_TYPE_CLOSEWEB);

  GEN_XFACTORY_CREATE(timerout, CreateTimer())
  
  diostreamcfg = new DIOSTREAMTCPIPCONFIG();
  if(diostreamcfg) diostream = (DIOSTREAMTCPIP*)GEN_DIOFACTORY.CreateStreamIO(diostreamcfg);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBCLIENT::~DIOWEBCLIENT()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBCLIENT::~DIOWEBCLIENT()
{
  DeRegisterEvent(DIOWEBCLIENT_XEVENT_TYPE_OPENWEB);
  DeRegisterEvent(DIOWEBCLIENT_XEVENT_TYPE_WRITEHEADER);
  DeRegisterEvent(DIOWEBCLIENT_XEVENT_TYPE_SENDPOSTDATA);
  DeRegisterEvent(DIOWEBCLIENT_XEVENT_TYPE_READHEADER);
  DeRegisterEvent(DIOWEBCLIENT_XEVENT_TYPE_READBODYBLOCK);
  DeRegisterEvent(DIOWEBCLIENT_XEVENT_TYPE_CLOSEWEB);

  if(diostream)
    {
      GEN_DIOFACTORY.DeleteStreamIO(diostream);
      diostream = NULL;
    }

  if(diostreamcfg)
    {
      delete diostreamcfg;
      diostreamcfg = NULL;
    }

  if(timerout)
    {
      GEN_XFACTORY.DeleteTimer(timerout);
      timerout = NULL;
    }

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOWEBCLIENT::Get_Port()
* @brief      Get port
* @ingroup    DATAIO
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOWEBCLIENT::Get_Port()
{
  return port;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBCLIENT::Set_Port(int port)
* @brief      Set port
* @ingroup    DATAIO
*
* @param[in]  port :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBCLIENT::Set_Port(int port)
{
  this->port = port;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOURL* DIOWEBCLIENT::GetProxyURL()
* @brief      Get proxy URL
* @ingroup    DATAIO
*
* @return     DIOURL* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOURL* DIOWEBCLIENT::GetProxyURL()
{
  return &proxyurl;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOWEBCLIENT::GetProxyPort()
* @brief      Get proxy port
* @ingroup    DATAIO
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOWEBCLIENT::GetProxyPort()
{
  return proxyport;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBCLIENT::SetProxyPort(int port)
* @brief      Set proxy port
* @ingroup    DATAIO
*
* @param[in]  port :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBCLIENT::SetProxyPort(int port)
{
  proxyport = port;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBCLIENT_AUTHENTICATION_METHOD DIOWEBCLIENT::GetAuthenticationMethod()
* @brief      Get authentication method
* @ingroup    DATAIO
*
* @return     DIOWEBCLIENT_AUTHENTICATION_METHOD : 
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBCLIENT_AUTHENTICATION_METHOD DIOWEBCLIENT::GetAuthenticationMethod()
{
  return authenticationmethod;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBCLIENT::SetAuthenticationMethod(DIOWEBCLIENT_AUTHENTICATION_METHOD authenticationmethod)
* @brief      Set authentication method
* @ingroup    DATAIO
*
* @param[in]  authenticationmethod : 
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBCLIENT::SetAuthenticationMethod(DIOWEBCLIENT_AUTHENTICATION_METHOD authenticationmethod)
{
  this->authenticationmethod = authenticationmethod;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOWEBCLIENT::GetLogin()
* @brief      Get login
* @ingroup    DATAIO
*
* @return     XSTRING* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING*  DIOWEBCLIENT::GetLogin()
{
  return &login;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOWEBCLIENT::GetPassword()
* @brief      Get password
* @ingroup    DATAIO
*
* @return     XSTRING* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING*  DIOWEBCLIENT::GetPassword()
{
  return &password;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMTCPIPCONFIG* DIOWEBCLIENT::GetStreamCFG()
* @brief      Get stream CFG
* @ingroup    DATAIO
*
* @return     DIOSTREAMTCPIPCONFIG* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMTCPIPCONFIG* DIOWEBCLIENT::GetStreamCFG()
{
  return diostreamcfg;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBCLIENT_HEADER* DIOWEBCLIENT::GetHeader()
* @brief      Get header
* @ingroup    DATAIO
*
* @return     DIOWEBCLIENT_HEADER* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBCLIENT_HEADER* DIOWEBCLIENT::GetHeader()
{
  return &header;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBCLIENT::IsActiveDoStopHTTPError()
* @brief      Is active do stop HTTP error
* @ingroup    DATAIO
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBCLIENT::IsActiveDoStopHTTPError()
{
  return dostophttperror;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOWEBCLIENT::DoStopHTTPError(bool activate)
* @brief      Do stop HTTP error
* @ingroup    DATAIO
* 
* @param[in]  activate : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBCLIENT::DoStopHTTPError(bool activate)
{
  dostophttperror = activate;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBCLIENT::Get(DIOURL& url, XBUFFER& tobuffer, XCHAR* addheader, int timeout, XSTRING* localIP)
* @brief      Get
* @ingroup    DATAIO
*
* @param[in]  url :
* @param[in]  tobuffer :
* @param[in]  addheader :
* @param[in]  timeout :
* @param[in]  localIP :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBCLIENT::Get(DIOURL& url, XBUFFER& tobuffer, XCHAR* addheader, int timeout, XSTRING* localIP)
{
  return MakeOperation(DIOWEBHEADER_METHOD_GET, url, NULL, addheader, timeout, localIP, true, (void*)&tobuffer);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBCLIENT::Get(XCHAR* url, XBUFFER& tobuffer, XCHAR* addheader, int timeout, XSTRING* localIP)
* @brief      Get
* @ingroup    DATAIO
*
* @param[in]  url :
* @param[in]  tobuffer :
* @param[in]  addheader :
* @param[in]  timeout :
* @param[in]  localIP :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBCLIENT::Get(XCHAR* url, XBUFFER& tobuffer, XCHAR* addheader, int timeout, XSTRING* localIP)
{
  DIOURL _url;
  _url = url;

  return MakeOperation(DIOWEBHEADER_METHOD_GET, _url, NULL, addheader, timeout, localIP, true, (void*)&tobuffer);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBCLIENT::Get(DIOURL& url, XPATH& pathfile, XCHAR* addheader, int timeout, XSTRING* localIP)
* @brief      Get
* @ingroup    DATAIO
*
* @param[in]  url :
* @param[in]  pathfile :
* @param[in]  addheader :
* @param[in]  timeout :
* @param[in]  localIP :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBCLIENT::Get(DIOURL& url, XPATH& pathfile, XCHAR* addheader, int timeout, XSTRING* localIP)
{
  XFILE* GEN_XFACTORY_CREATE(file, Create_File())
  if(!file) return false;
  
  bool status  = false;

  if(!file->Open(pathfile, false))
    {
      if(file->Create(pathfile))
        {
          status = true;
        }

    } else status = true;

  if(status)
    {      
      status = MakeOperation(DIOWEBHEADER_METHOD_GET, url, NULL, addheader, timeout, localIP, false, (void*)file);

      file->Close();

      if(!status)  file->Erase(pathfile);
    }

  GEN_XFACTORY.Delete_File(file);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBCLIENT::Get(XCHAR* url, XPATH& pathfile, XCHAR* addheader, int timeout, XSTRING* localIP)
* @brief      Get
* @ingroup    DATAIO
*
* @param[in]  url :
* @param[in]  pathfile :
* @param[in]  addheader :
* @param[in]  timeout :
* @param[in]  localIP :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBCLIENT::Get(XCHAR* url, XPATH& pathfile, XCHAR* addheader, int timeout, XSTRING* localIP)
{
  DIOURL _url;
  _url = url;

  return Get(_url, pathfile, addheader, timeout, localIP);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBCLIENT::Put(DIOURL& url, XBUFFER& tobuffer, XCHAR* addheader, int timeout, XSTRING* localIP)
* @brief      Put
* @ingroup    DATAIO
*
* @param[in]  url :
* @param[in]  tobuffer :
* @param[in]  addheader :
* @param[in]  timeout :
* @param[in]  localIP :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBCLIENT::Put(DIOURL& url, XBUFFER& tobuffer, XCHAR* addheader, int timeout, XSTRING* localIP)
{
  return MakeOperation(DIOWEBHEADER_METHOD_PUT, url, NULL, addheader, timeout, localIP, true, (void*)&tobuffer);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBCLIENT::Put(XCHAR* url, XBUFFER& tobuffer, XCHAR* addheader, int timeout, XSTRING* localIP)
* @brief      Put
* @ingroup    DATAIO
*
* @param[in]  url :
* @param[in]  tobuffer :
* @param[in]  addheader :
* @param[in]  timeout :
* @param[in]  localIP :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBCLIENT::Put(XCHAR* url, XBUFFER& tobuffer, XCHAR* addheader, int timeout, XSTRING* localIP)
{
  DIOURL _url;
  _url = url;

  return MakeOperation(DIOWEBHEADER_METHOD_PUT, _url, NULL, addheader, timeout, localIP, true, (void*)&tobuffer);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBCLIENT::Put(DIOURL& url, XPATH& pathfile, XCHAR* addheader, int timeout, XSTRING* localIP)
* @brief      Put
* @ingroup    DATAIO
*
* @param[in]  url :
* @param[in]  pathfile :
* @param[in]  addheader :
* @param[in]  timeout :
* @param[in]  localIP :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBCLIENT::Put(DIOURL& url, XPATH& pathfile, XCHAR* addheader, int timeout, XSTRING* localIP)
{
  XFILE* GEN_XFACTORY_CREATE(file, Create_File())
  if(!file) return false;

  XBUFFER buffer;
  bool    status  = false;

  if(!file->Open(pathfile, false))
    {
      if(file->Create(pathfile))
        {
          status = true;
        }

    } else status = true;

  if(status)
    {
      status = MakeOperation(DIOWEBHEADER_METHOD_PUT, url, &buffer, addheader, timeout, localIP, false, (void*)file);
      if(status) file->Write(buffer);

      file->Close();

      if(!status)  file->Erase(pathfile);
    }

  GEN_XFACTORY.Delete_File(file);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBCLIENT::Put(XCHAR* url, XPATH& pathfile, XCHAR* addheader, int timeout, XSTRING* localIP)
* @brief      Put
* @ingroup    DATAIO
*
* @param[in]  url :
* @param[in]  pathfile :
* @param[in]  addheader :
* @param[in]  timeout :
* @param[in]  localIP :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBCLIENT::Put(XCHAR* url, XPATH& pathfile, XCHAR* addheader, int timeout, XSTRING* localIP)
{
  DIOURL _url;
  _url = url;

  return Put(_url, pathfile, addheader, timeout, localIP);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBCLIENT::Post(DIOURL& url, XBUFFER& tobuffer, XBUFFER* postdata, XCHAR* addheader, int timeout, XSTRING* localIP)
* @brief      Post
* @ingroup    DATAIO
*
* @param[in]  url :
* @param[in]  tobuffer :
* @param[in]  postdata :
* @param[in]  addheader :
* @param[in]  timeout :
* @param[in]  localIP :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBCLIENT::Post(DIOURL& url, XBUFFER& tobuffer, XBUFFER* postdata, XCHAR* addheader, int timeout, XSTRING* localIP)
{
  return MakeOperation(DIOWEBHEADER_METHOD_POST, url, postdata, addheader, timeout, localIP, true, (void*)&tobuffer);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBCLIENT::Post(XCHAR* url, XBUFFER& tobuffer, XBUFFER* postdata, XCHAR* addheader, int timeout, XSTRING* localIP)
* @brief      Post
* @ingroup    DATAIO
*
* @param[in]  url :
* @param[in]  tobuffer :
* @param[in]  postdata :
* @param[in]  addheader :
* @param[in]  timeout :
* @param[in]  localIP :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBCLIENT::Post(XCHAR* url, XBUFFER& tobuffer, XBUFFER* postdata, XCHAR* addheader, int timeout, XSTRING* localIP)
{
  DIOURL _url;
  _url = url;

  return MakeOperation(DIOWEBHEADER_METHOD_POST, _url, postdata, addheader, timeout, localIP, true, (void*)&tobuffer);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBCLIENT::Post(DIOURL& url, XPATH& pathfile, XBUFFER* postdata, XCHAR* addheader, int timeout, XSTRING* localIP)
* @brief      Post
* @ingroup    DATAIO
*
* @param[in]  url :
* @param[in]  pathfile :
* @param[in]  postdata :
* @param[in]  addheader :
* @param[in]  timeout :
* @param[in]  localIP :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBCLIENT::Post(DIOURL& url, XPATH& pathfile, XBUFFER* postdata, XCHAR* addheader, int timeout, XSTRING* localIP)
{
  XFILE* GEN_XFACTORY_CREATE(file, Create_File())
  if(!file) return false;

  XBUFFER buffer;
  bool    status  = false;

  if(file->Create(pathfile))
    {
      status = Post(url, buffer, postdata, addheader, timeout, localIP);

      if(status) file->Write(buffer.Get(), buffer.GetSize());

      file->Close();

      if(!status) file->Erase(pathfile);
    }

  GEN_XFACTORY.Delete_File(file);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBCLIENT::Post(XCHAR* url, XPATH& pathfile, XBUFFER* postdata, XCHAR* addheader, int timeout, XSTRING* localIP)
* @brief      Post
* @ingroup    DATAIO
*
* @param[in]  url :
* @param[in]  pathfile :
* @param[in]  postdata :
* @param[in]  addheader :
* @param[in]  timeout :
* @param[in]  localIP :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBCLIENT::Post(XCHAR* url, XPATH& pathfile, XBUFFER* postdata, XCHAR* addheader, int timeout, XSTRING* localIP)
{
  DIOURL _url;
  _url = url;

  return Post(_url, pathfile, postdata, addheader, timeout, localIP);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBCLIENT::MakeOperation(DIOWEBHEADER_METHOD method, DIOURL& url, XBUFFER* postdata, XCHAR* addhead, int timeout, XSTRING* localIP, bool istobuffer, void* to)
* @brief      Make operation
* @ingroup    DATAIO
*
* @param[in]  method :
* @param[in]  url :
* @param[in]  postdata :
* @param[in]  addhead :
* @param[in]  timeout :
* @param[in]  localIP :
* @param[in]  istobuffer :
* @param[in]  to :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBCLIENT::MakeOperation(DIOWEBHEADER_METHOD method, DIOURL& url, XBUFFER* postdata, XCHAR* addhead, int timeout, XSTRING* localIP, bool istobuffer, void* to)
{
  if(!diostreamcfg)     return false;
  if(!diostream)        return false;
  if(!timerout)         return false;

  bool status = true;

  if(!url.HaveHTTPID()) url.AddHTTPID();

  XSTRING               server; 
  DIOURL                resource;
  XSTRING               methodstring;
  DIOWEBCLIENT_XEVENT   xevent(this, XEVENT_TYPE_NONE);

  xevent.GetURL()->Set(url.Get());
  xevent.SetMethod(method);

  diostreamcfg->SetFromString(url.Get());

  url  = diostreamcfg->GetRemoteURL()->Get();
  if(diostreamcfg->GetRemotePort()) port = diostreamcfg->GetRemotePort();

  url.GetHTTPServer(server, login, password);
  url.GetHTTPResource(resource);

  if(resource.IsEmpty()) resource.Slash_Add();

  diostreamcfg->SetMode(DIOSTREAMMODE_CLIENT);
  if(localIP)
    {
      if(!localIP->IsEmpty()) diostreamcfg->GetLocalIP()->Set(localIP->Get());
    }

  if(proxyurl.IsEmpty())
    {
      diostreamcfg->GetRemoteURL()->Set(server.Get());
      diostreamcfg->SetRemotePort(port);
    }
   else
    {
      diostreamcfg->GetRemoteURL()->Set(proxyurl.Get());
      diostreamcfg->SetRemotePort(proxyport);
    }

  //--- Connection WEB server -------------------

  if(!diostream->Open())
    {
      diostream->Close();
      return false;
    }

  if(!diostream->WaitToConnected(timeout))
    {
      diostream->Close();
      return false;
    }

  xevent.SetEventType(DIOWEBCLIENT_XEVENT_TYPE_OPENWEB);
  PostEvent(&xevent);

  //--- Send Header ----------------------------

  XSTRING sendheader;

  //resource.EncodeUnsafeChars();

  switch(method)
    {
      case DIOWEBHEADER_METHOD_GET  : methodstring = __L("GET");     break;
      case DIOWEBHEADER_METHOD_PUT  : methodstring = __L("PUT");     break;
      case DIOWEBHEADER_METHOD_POST : methodstring = __L("POST");    break;

                            default : { xevent.SetEventType(DIOWEBCLIENT_XEVENT_TYPE_HEADERERROR);
                                        PostEvent(&xevent);

                                        diostream->Close();
                                      }
                                      return false;
    }


  sendheader.AddFormat(__L("%s %s HTTP/1.0\r\n"), methodstring.Get(), resource.Get());

  sendheader += __L("Host: ");
  sendheader += server.Get();

  if(port!=DIOWEBCLIENT_DEFAULTPORT)
    {
      XSTRING stringport;

      stringport.ConvertFromInt(port);

      sendheader += __L(":");
      sendheader += stringport.Get();
    }
  sendheader += __L("\r\n");

  if(addhead) sendheader += addhead;


  switch(authenticationmethod)
    {
      case DIOWEBCLIENT_AUTHENTICATION_METHOD_UNKNOWN : if(password.IsEmpty()) break;
                                                        authenticationmethod = DIOWEBCLIENT_AUTHENTICATION_METHOD_BASIC;
      
      case DIOWEBCLIENT_AUTHENTICATION_METHOD_BASIC   : { XSTRING loginpassword;
                                                          XSTRING loginpasswordbase64;

                                                          loginpassword.Format(__L("%s:%s"), login.Get(), password.Get());
                                                          loginpassword.ConvertToBase64(loginpasswordbase64);   

                                                          sendheader += __L("Authorization: Basic ");
                                                          sendheader += loginpasswordbase64;
                                                          sendheader += __L("\r\n");
                                                        }
                                                        break;

      case DIOWEBCLIENT_AUTHENTICATION_METHOD_DIGEST  : break;
    }
  

  if(postdata)
    {
      XSTRING stringlenght;
      stringlenght.Format(__L("%s: %d\r\n"), DIOWEBHEADER_CONTENT_LENGTH, postdata->GetSize());

      sendheader += stringlenght;
    }

  sendheader += __L("Connection: close\r\n");
  sendheader += __L("\r\n");

  diostream->WriteStr(sendheader);

  //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("%s"), sendheader.Get());

  xevent.SetEventType(DIOWEBCLIENT_XEVENT_TYPE_WRITEHEADER);
  PostEvent(&xevent);

  //--- Send Post data -------------------------

  if(postdata)
    {
      diostream->Write(postdata->Get(), postdata->GetSize());

      xevent.SetEventType(DIOWEBCLIENT_XEVENT_TYPE_SENDPOSTDATA);
      PostEvent(&xevent);
    }

  diostream->WaitToFlushOutXBuffer(timeout);

  //--- Read Header ----------------------------

  if(!header.Read(diostream, timeout))
    {
      diostream->Close();
      return false;
    }

  //--- Read Content ---------------------------

  if(header.GetResultServer() == 301)
    {

    
    }

  if((header.GetResultServer() == 401) && (authenticationmethod == DIOWEBCLIENT_AUTHENTICATION_METHOD_DIGEST))
    {
      XSTRING   www_authenticate;
      HASHMD5   md5;
      XSTRING   HA1;
      XSTRING   HA2;
      XSTRING   calculatehash;
      XSTRING   realm_str;
      XSTRING   nonce_str;
      XSTRING   auth_str;
      XDWORD    nc;
      XDWORD    cnonce;
      XSTRING   nc_str;
      XSTRING   cnonce_str;
      XSTRING   opaque_str;
      XSTRING   algorithm_str;
      XSTRING   response;
      
      sendheader.DeleteCharacters(sendheader.GetSize()-2, 2);

      diostream->Close();

      if(!diostream->Open())
        {
          diostream->Close();
          return false;
        }

      if(!diostream->WaitToConnected(timeout))
        {
          diostream->Close();
          return false;
        }

      xevent.SetEventType(DIOWEBCLIENT_XEVENT_TYPE_OPENWEB);
      PostEvent(&xevent);


      auth_str    = __L("auth");
      nc          = 0x0000001;
      cnonce      = 0x0AF113B;

      nc_str.Format(__L("%08x"), nc);
      cnonce_str.Format(__L("%08x"), cnonce);
      
       
      header.GetWWWAuthenticate(www_authenticate);
      
      //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("%s"), www_authenticate.Get());

      GetSubStringWWWWAuthenticate(www_authenticate, __L("realm")     , realm_str);
      GetSubStringWWWWAuthenticate(www_authenticate, __L("nonce")     , nonce_str);
      GetSubStringWWWWAuthenticate(www_authenticate, __L("opaque")    , opaque_str);
      GetSubStringWWWWAuthenticate(www_authenticate, __L("algorithm") , algorithm_str, false);

      /*
      if(algorithm_str.Compare(__L("MD5"), true))
        {
          diostream->Close();
          return false;
        }    
      */
     
      { calculatehash.Format(__L("%s:%s:%s"), login.Get(), realm_str.Get(), password.Get());
       
        XBUFFER charhash;
        
        calculatehash.ConvertToASCII(charhash);       
        md5.Do((XBYTE*)charhash.Get(), calculatehash.GetSize());
        
        md5.GetResultString(HA1);
      }

      md5.ResetResult();

      { calculatehash.Format(__L("%s:%s"), methodstring.Get(), resource.Get());
  
        XBUFFER charhash;
        
        calculatehash.ConvertToASCII(charhash);       
        md5.Do((XBYTE*)charhash.Get(), calculatehash.GetSize());
        
        md5.GetResultString(HA2);
      }

      md5.ResetResult();  

      { calculatehash.Format(__L("%s:%s:%s:%s:%s:%s"), HA1.Get(), nonce_str.Get(), nc_str.Get(), cnonce_str.Get(), auth_str.Get(), HA2.Get());
  
        XBUFFER charhash;
        
        calculatehash.ConvertToASCII(charhash);       
        md5.Do((XBYTE*)charhash.Get(), calculatehash.GetSize());
        
        md5.GetResultString(response);
      }
     
   
      sendheader.AddFormat(__L("Authorization: Digest "));     
      sendheader.AddFormat(__L("username=\"%s\", "), login.Get());           
      sendheader.AddFormat(__L("realm=\"%s\", "), realm_str.Get());           
      sendheader.AddFormat(__L("nonce=\"%s\", "), nonce_str.Get());           
      sendheader.AddFormat(__L("uri=\"%s\", "), resource.Get());     
      sendheader.AddFormat(__L("algorithm=%s, "), algorithm_str.Get());
      sendheader.AddFormat(__L("response=\"%s\", "), response.Get());   
      sendheader.AddFormat(__L("qop=%s, "), auth_str.Get());     
      sendheader.AddFormat(__L("nc=%s, "), nc_str.Get());     
      sendheader.AddFormat(__L("cnonce=\"%s\" "), cnonce_str.Get());   
      if(opaque_str.GetSize()) sendheader.AddFormat(__L(", opaque=\"%s\""), opaque_str.Get());           
      sendheader += __L("\r\n");

      sendheader += __L("\r\n");
      
      //XTRACE_PRINTCOLOR(XTRACE_COLOR_PURPLE, __L("%s"), sendheader.Get());

      diostream->WriteStr(sendheader);

      xevent.SetEventType(DIOWEBCLIENT_XEVENT_TYPE_WRITEHEADER);
      PostEvent(&xevent);

      //--- Send Post data -------------------------

      if(postdata)
        {
          diostream->Write(postdata->Get(), postdata->GetSize());

          xevent.SetEventType(DIOWEBCLIENT_XEVENT_TYPE_SENDPOSTDATA);
          PostEvent(&xevent);
        }

      diostream->WaitToFlushOutXBuffer(timeout);

      //--- Read Header ----------------------------

      if(!header.Read(diostream, timeout))
        {
          diostream->Close();
          return false;
        }
    }


  if((header.GetResultServer()>=400)||(!header.GetResultServer()))
    {     
      xevent.SetEventType(DIOWEBCLIENT_XEVENT_TYPE_HEADERERROR);
      PostEvent(&xevent);

      if(IsActiveDoStopHTTPError())
        {
          diostream->Close();
          return false;
        }
    }

  XQWORD   contentlength;
  XSTRING  etag;

  contentlength = header.GetContentLength();
  header.GetETag(etag);

  xevent.SetContentLenght(contentlength);
  xevent.GetEtag()->Set(etag);

  xevent.SetEventType(DIOWEBCLIENT_XEVENT_TYPE_READHEADER);

  PostEvent(&xevent);

  //--- Read Content ---------------------------

  XBUFFER* _tobuffer     = NULL;
  XFILE*   _tofile       = NULL;
 
  XTIMER* GEN_XFACTORY_CREATE(timerdownload, CreateTimer())
  if(!timerdownload)
    {     
      diostream->Close();
      return false;
    }
       
  if(istobuffer)
    {
      _tobuffer = (XBUFFER*)to;
      if(_tobuffer) _tobuffer->Delete();
    }
   else
    {
      _tofile = (XFILE*)to;
    }

  XBYTE* buffer = new XBYTE[maxsizebuffer];
  if(buffer)
    {
      XQWORD  totalsizeread = 0;
      int     br;

      timerout->Reset();

      do{ memset(buffer, 0, maxsizebuffer);

          br = diostream->Read(buffer, maxsizebuffer);
          if(br)
            {
              timerout->Reset();

              if(istobuffer)
                {
                  if(_tobuffer) _tobuffer->Add(buffer, br);
                }
               else
                {
                  if(_tofile) _tofile->Write(buffer, br);
                }

              totalsizeread += br;

              xevent.SetEventType(DIOWEBCLIENT_XEVENT_TYPE_READBODYBLOCK);
              xevent.SetDownloadSize(totalsizeread);
              xevent.SetContentLenght((XQWORD)contentlength);

              if(contentlength) xevent.SetOperationPercent((float)((totalsizeread * 100.0f) / contentlength));

              if(timerdownload->GetMeasureSeconds()) xevent.SetMBPSSpeed((XDWORD)(((totalsizeread * 8) / timerdownload->GetMeasureSeconds()) / 1000));

              PostEvent(&xevent);
            }
           else
            {
              if(timerout->GetMeasureSeconds()>(XDWORD)timeout)
                {
                  if(!totalsizeread) status = false;
                  break;
                }

              if(diostream->GetStatus() != DIOSTREAMSTATUS_CONNECTED)
                {
                  if(!diostream->GetInXBuffer()->GetSize())
                    {
                      break;
                    }
                }
            }

        } while(1);

      delete [] buffer;
    }

  GEN_XFACTORY.DeleteTimer(timerdownload);

  //--- Close ----------------------------------

  diostream->Close();

  xevent.SetEventType(DIOWEBCLIENT_XEVENT_TYPE_CLOSEWEB);
  PostEvent(&xevent);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBCLIENT::GetSubStringWWWWAuthenticate(XSTRING& www_authenticate, XCHAR* field, XSTRING& value, bool betweenquotation)
* @brief      Get sub string WWWW authenticate
* @ingroup    DATAIO
*
* @param[in]  www_authenticate : 
* @param[in]  field : 
* @param[in]  value : 
* @param[in]  betweenquotation : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBCLIENT::GetSubStringWWWWAuthenticate(XSTRING& www_authenticate, XCHAR* field, XSTRING& value, bool betweenquotation)
{
  if(www_authenticate.IsEmpty()) return false;

  XSTRING sfield;

  sfield = field;

  int index = www_authenticate.Find(field, true);
  if(index == XSTRING_NOTFOUND) return false;
  index +=  sfield.GetSize();

  index = www_authenticate.Find(__L("="), true, index);
  if(index == XSTRING_NOTFOUND) return false;

  int start = 0;
  int end   = 0;

  if(betweenquotation)
    {
      start = www_authenticate.Find(__L("\""), true, index+1);
      if(start == XSTRING_NOTFOUND) return false;

      end = www_authenticate.Find(__L("\""), true, start+1);
      if(end == XSTRING_NOTFOUND) return false;
    }
   else
    { 
      start = index;

      end = www_authenticate.Find(__L(","), true, start+1);
      if(end == XSTRING_NOTFOUND) return false;
    }

  return www_authenticate.Copy(start+1, end, value)?true:false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBCLIENT::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBCLIENT::Clean()
{
  maxsizebuffer           = 0;

  timerout                = NULL;

  diostreamcfg            = NULL;
  diostream               = NULL;

  proxyport               = 0;

  port                    = DIOWEBCLIENT_DEFAULTPORT;

  authenticationmethod    = DIOWEBCLIENT_AUTHENTICATION_METHOD_UNKNOWN;

  dostophttperror         = true;
}


#pragma endregion


#pragma endregion

