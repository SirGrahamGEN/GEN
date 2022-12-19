/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOWebServer.cpp
*
* @class      DIOWEBSERVER
* @brief      Data Input/Output Web Server class
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
#include "XBuffer.h"
#include "XPath.h"
#include "XLog.h"
#include "XFileTXT.h"
#include "XSystem.h"
#include "XTrace.h"

#include "HashSHA1.h"

#include "CompressManager.h"

#include "DIOFactory.h"
#include "DIOURL.h"
#include "DIOStreamXEvent.h"
#include "DIOStreamTCPIPConfig.h"
#include "DIOStreamTCPIP.h"
#include "DIOWebServer_Plugin.h"
#include "DIOWebServer_XEvent.h"

#include "DIOWebServer.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#pragma region DIOWEBSERVER_HEADER

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_HEADER::DIOWEBSERVER_HEADER()
* @brief      Constructor
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_HEADER::DIOWEBSERVER_HEADER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_HEADER::~DIOWEBSERVER_HEADER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_HEADER::~DIOWEBSERVER_HEADER()
{
  DeleteAllLines();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOWEBSERVER_HEADER::GetVersion()
* @brief      GetVersion
* @ingroup    DATAIO
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOWEBSERVER_HEADER::GetVersion()
{
  int data = 0;

  if(!GetFormat(true, 0, &data)) return false;

  return data;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOWEBSERVER_HEADER::GetSubVersion()
* @brief      GetSubVersion
* @ingroup    DATAIO
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOWEBSERVER_HEADER::GetSubVersion()
{
  int data = 0;

  if(!GetFormat(true, 1, &data)) return false;

  return data;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOWEBSERVER_HEADER::GetResult()
* @brief      GetResult
* @ingroup    DATAIO
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOWEBSERVER_HEADER::GetResult()
{
  int data = 0;

  if(!GetFormat(true, 2, &data)) return false;

  return data;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_HEADER::GetResultString(XSTRING& resultstring)
* @brief      GetResultString
* @ingroup    DATAIO
*
* @param[in]  resultstring :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_HEADER::GetResultString(XSTRING& resultstring)
{
  if(!GetFormat(true, 3, &resultstring)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_HEADER::CreateContentType(XSTRING* resource, XSTRING& contenttype)
* @brief      CreateContentType
* @ingroup    DATAIO
*
* @param[in]  resource :
* @param[in]  contenttype :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_HEADER::CreateContentType(XSTRING* resource, XSTRING& contenttype)
{
  contenttype.Empty();

       if(resource->Find(__L(".htm")  , true) != XSTRING_NOTFOUND)  contenttype = __L("text/html");
  else if(resource->Find(__L(".xml")  , true) != XSTRING_NOTFOUND)  contenttype = __L("text/xml");
  else if(resource->Find(__L(".exe")  , true) != XSTRING_NOTFOUND)  contenttype = __L("application/octet-stream");
  else if(resource->Find(__L(".gif")  , true) != XSTRING_NOTFOUND)  contenttype = __L("image/gif");
  else if(resource->Find(__L(".jpg")  , true) != XSTRING_NOTFOUND)  contenttype = __L("image/jpeg");
  else if(resource->Find(__L(".jpeg") , true) != XSTRING_NOTFOUND)  contenttype = __L("image/jpeg");
  else if(resource->Find(__L(".png")  , true) != XSTRING_NOTFOUND)  contenttype = __L("image/png");
  else if(resource->Find(__L(".wav")  , true) != XSTRING_NOTFOUND)  contenttype = __L("audio/x-wav");
  else if(resource->Find(__L(".mp3")  , true) != XSTRING_NOTFOUND)  contenttype = __L("audio/mp3");
  else if(resource->Find(__L(".gz")   , true) != XSTRING_NOTFOUND)  contenttype = __L("application/x-gzip");
  else if(resource->Find(__L(".mpg")  , true) != XSTRING_NOTFOUND)  contenttype = __L("video/mpeg");
  else if(resource->Find(__L(".pdf")  , true) != XSTRING_NOTFOUND)  contenttype = __L("application/pdf");
  else if(resource->Find(__L(".avi")  , true) != XSTRING_NOTFOUND)  contenttype = __L("video/x-msvideof");
  else if(resource->Find(__L(".ogv")  , true) != XSTRING_NOTFOUND)  contenttype = __L("video/ogg");
  else if(resource->Find(__L(".ogg")  , true) != XSTRING_NOTFOUND)  contenttype = __L("video/ogg");
  else if(resource->Find(__L(".css")  , true) != XSTRING_NOTFOUND)  contenttype = __L("text/css");
  else if(resource->Find(__L(".js")   , true) != XSTRING_NOTFOUND)  contenttype = __L("application/javascript");
  else if(resource->Find(__L(".json") , true) != XSTRING_NOTFOUND)  contenttype = __L("application/json");
  else if(resource->Find(__L(".zip")  , true) != XSTRING_NOTFOUND)  contenttype = __L("application/zip");
  else if(resource->Find(__L(".otf")  , true) != XSTRING_NOTFOUND)  contenttype = __L("application/x-font-otf");

  if(!resource->Compare(__L("/") ,  true))  contenttype = __L("text/html");

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_HEADER::Create(XSTRING* resource, int version, int subversion, DIOWEBHEADER_RESULT result, int size, XSTRING* entitytag, bool isplayable, bool password)
* @brief      Create
* @ingroup    DATAIO
*
* @param[in]  resource :
* @param[in]  version :
* @param[in]  subversion :
* @param[in]  result :
* @param[in]  size :
* @param[in]  entitytag :
* @param[in]  isplayable :
* @param[in]  password :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_HEADER::Create(XSTRING* resource, int version, int subversion, DIOWEBHEADER_RESULT result, int size, XSTRING* entitytag, bool isplayable, bool password)
{
  /*
      Accept - Ranges:bytes
      Connection : Keep - Alive
      Content - Length : 6
      Content - Type : text / html
      Date : Mon, 06 Nov 2017 11 : 21 : 24 GMT
      ETag : "6-55d4e3b3b9f20"
      Keep - Alive : timeout = 5, max = 93
      Last - Modified : Mon, 06 Nov 2017 10 : 51 : 06 GMT
      Server : Apache / 2.4.23 (Win64)PHP / 5.6.25
  */

  XSTRING line;
  line.Format(__L("HTTP/%d.%d %d "), version, subversion, result);

  if(password)
    {
      line += __L("Unauthorised");
      AddLine(line);
      AddLine(__L("WWW-Authenticate: Basic"));
    }
   else
    {
      XSTRING description;

      GetDescriptionResult(result, description);

      line += description;
      AddLine(line);
    }


  AddLine(__L("Accept-Ranges: bytes"));

  line.Empty();
  CreateContentType(resource, line);

  if(!line.IsEmpty())
    {
      line.Insert(__L("Content-Type: "), 0);
      AddLine(line.Get());
    }

  XSTRING date;
  XDATETIME* GEN_XFACTORY_CREATE(datetime, CreateDateTime())
  if(datetime)
    {
      XSTRING day;
      XSTRING month;
      XSTRING hour;

      datetime->Read();
      datetime->GetDateTimeToString(XDATETIME_FORMAT_ADDTIME | XDATETIME_FORMAT_TIMEWITHSECONDS, hour);
      datetime->GetMonthString(month);

      switch((int)datetime->GetDayOfWeek())
        {
          case  1:  day.Set(__L("Mon")); break;
          case  2:  day.Set(__L("Tue")); break;
          case  3:  day.Set(__L("Wed")); break;
          case  4:  day.Set(__L("Thu")); break;
          case  5:  day.Set(__L("Fri")); break;
          case  6:  day.Set(__L("Sat")); break;
          case  0:
          case  7:  day.Set(__L("Sun")); break;
          default:  break;
        }

      switch(datetime->GetMonth())
        {
          case  1:  month.Set(__L("Jan")); break;
          case  2:  month.Set(__L("Feb")); break;
          case  3:  month.Set(__L("Mar")); break;
          case  4:  month.Set(__L("Apr")); break;
          case  5:  month.Set(__L("May")); break;
          case  6:  month.Set(__L("Jun")); break;
          case  7:  month.Set(__L("Jul")); break;
          case  8:  month.Set(__L("Aug")); break;
          case  9:  month.Set(__L("Sep")); break;
          case 10:  month.Set(__L("Oct")); break;
          case 11:  month.Set(__L("Nov")); break;
          case 12:  month.Set(__L("Dec")); break;
          default:  break;
        }

      //Date: Wed, 21 Oct 2015 07:28:00 GMT
      date.Format(__L("%s, %d %s %d %s GMT"), day.Get(), datetime->GetDay(), month.Get(), datetime->GetYear(), hour.Get());
      line.Format(__L("Date:%s"), date.Get());  AddLine(line);
      delete(datetime);
   }

  if(entitytag)
    {
      if(!entitytag->IsEmpty())
        {
          line.Format(__L("ETag: \"%s\""), entitytag->Get());
          AddLine(line.Get());
        }
    }

  //---------------------------------------------------------------

  AddLine(__L("Connection: Keep-Alive"));
  line.Format(__L("Keep-Alive: timeout=%d,max=%d"), DIOWEBSERVER_KEEPALIVE
                                                  , DIOWEBSERVER_KEEPALIVE_MAXRESOURCES);
  AddLine(line);

  //---------------------------------------------------------------

  line.Format(__L("Last-Modified: %s"), date.Get());                  AddLine(line);
  line.Format(__L("Server: %s "), DIOWEBSERVER_IDSERVER);   AddLine(line);

  if(size != -1)
    {
      line.Format(__L("Content-Length: %d"), size);
      AddLine(line);

    }

  /*
  AddLine(__L("Access-Control-Allow-Headers: DNT,X-CustomHeader,Keep-Alive,User-Agent,X-Requested-With,If-Modified-Since,Cache-Control,Content-Type,Content-Encoding,Vary"));
  AddLine(__L("Vary : Accept-Encoding"));

  connection->SetActualEncodingFlag(DIOWEBSERVER_ENCODINGFLAGS_NONE);

  bool validsize = false;

  if(size > 100)  validsize = true;
  if(size == -1)  validsize = true;

  if(request->IsAcceptedEncodingFlag(DIOWEBSERVER_ENCODINGFLAGS_GZIP))
    {
      if(webserver->IsIncludedEncodingFlag(DIOWEBSERVER_ENCODINGFLAGS_GZIP))
        {
          if((validsize) && (isplayable))
            {
              connection->SetActualEncodingFlag(DIOWEBSERVER_ENCODINGFLAGS_GZIP);
              AddLine(__L("Content-Encoding: gzip"));

            }
        }
    }
  */

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_HEADER::AddWebSocketKey(XSTRING& websocketaccept);
* @brief      AddWebSocketKey
* @ingroup    DATAIO
*
* @param[in]  websocketaccept :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_HEADER::AddWebSocketKey(XSTRING& websocketaccept, XSTRING& websocketprotocol)
{
  XSTRING line;

  AddLine(__L("Access-Control-Allow-Headers: x-websocket-version"));
  AddLine(__L("Connection: Upgrade"));
  AddLine(__L("Upgrade: websocket"));

  line.Format(__L("Sec-WebSocket-Accept: %s"), websocketaccept.Get());
  AddLine(line.Get());

  if(websocketprotocol.GetSize())
    {
      line.Format(__L("Sec-WebSocket-Protocol: %s"), websocketprotocol.Get());
      AddLine(line.Get());
    }

  return true;
}


/*-------------------------------------------------------------------
//  DIOWEBSERVER_HEADER::GetDescriptionResult
*/
/**
//
//
//  ""
//  @version      13/04/2013 17:02:12
//
//  @return       bool :
//  @param        result :
//  @param        description :
*/
/*-----------------------------------------------------------------*/
bool DIOWEBSERVER_HEADER::GetDescriptionResult(DIOWEBHEADER_RESULT result, XSTRING& description)
{
  typedef struct
  {
    DIOWEBHEADER_RESULT  result;
    XCHAR*               description;

  } DESCRIPTION;

  DESCRIPTION  descriptions[] = { { DIOWEBHEADER_RESULT_CONTINUE                     ,  __L("Continue")                         } ,
                                  { DIOWEBHEADER_RESULT_SWITCHINGPROTOCOLS           ,  __L("Switching Protocols")              } ,

                                  { DIOWEBHEADER_RESULT_OK                           ,  __L("OK")                               } ,
                                  { DIOWEBHEADER_RESULT_CREATED                      ,  __L("Created")                          } ,
                                  { DIOWEBHEADER_RESULT_ACCEPTED                     ,  __L("Accepted")                         } ,
                                  { DIOWEBHEADER_RESULT_NONAUTHORITATIVEINFORMATION  ,  __L("Non-Authoritative Information")    } ,
                                  { DIOWEBHEADER_RESULT_NOCONTENT                    ,  __L("No Content")                       } ,
                                  { DIOWEBHEADER_RESULT_RESETCONTENT                 ,  __L("Reset Content")                    } ,
                                  { DIOWEBHEADER_RESULT_PARTIALCONTENT               ,  __L("Partial Content")                  } ,

                                  { DIOWEBHEADER_RESULT_MULTIPLECHOICES              ,  __L("Multiple Choices")                 } ,
                                  { DIOWEBHEADER_RESULT_MOVEDPERMANENTLY             ,  __L("Moved Permanently")                } ,
                                  { DIOWEBHEADER_RESULT_FOUND                        ,  __L("Found")                            } ,
                                  { DIOWEBHEADER_RESULT_SEEOTHER                     ,  __L("See Other")                        } ,
                                  { DIOWEBHEADER_RESULT_NOTMODIFIED                  ,  __L("Not Modified")                     } ,
                                  { DIOWEBHEADER_RESULT_USEPROXY                     ,  __L("Use Proxy")                        } ,
                                  { DIOWEBHEADER_RESULT_UNUSED                       ,  __L("(Unused)")                         } ,
                                  { DIOWEBHEADER_RESULT_TEMPORARYREDIRECT            ,  __L("Temporary Redirect")               } ,

                                  { DIOWEBHEADER_RESULT_BADREQUEST                   ,  __L("Bad Request")                      } ,
                                  { DIOWEBHEADER_RESULT_UNAUTHORIZED                 ,  __L("Unauthorized")                     } ,
                                  { DIOWEBHEADER_RESULT_PAYMENTREQUIRED              ,  __L("Payment Required")                 } ,
                                  { DIOWEBHEADER_RESULT_FORBIDDEN                    ,  __L("Forbidden")                        } ,
                                  { DIOWEBHEADER_RESULT_NOTFOUND                     ,  __L("Not Found")                        } ,
                                  { DIOWEBHEADER_RESULT_METHODNOTALLOWED             ,  __L("Method Not Allowed")               } ,
                                  { DIOWEBHEADER_RESULT_NOTACCEPTABLE                ,  __L("Not Acceptable")                   } ,
                                  { DIOWEBHEADER_RESULT_PROXYAUTHENTICATIONREQUIRED  ,  __L("Proxy Authentication Required")    } ,
                                  { DIOWEBHEADER_RESULT_REQUESTTIMEOUT               ,  __L("Request Timeout")                  } ,
                                  { DIOWEBHEADER_RESULT_CONFLICT                     ,  __L("Conflict")                         } ,
                                  { DIOWEBHEADER_RESULT_GONE                         ,  __L("Gone")                             } ,
                                  { DIOWEBHEADER_RESULT_LENGTHREQUIRED               ,  __L("Length Required")                  } ,
                                  { DIOWEBHEADER_RESULT_PRECONDITIONFAILED           ,  __L("Precondition Failed")              } ,
                                  { DIOWEBHEADER_RESULT_REQUESTENTITYTOOLARGE        ,  __L("Request Entity Too Large")         } ,
                                  { DIOWEBHEADER_RESULT_REQUESTURITOOLONG            ,  __L("Request-URI Too Long")             } ,
                                  { DIOWEBHEADER_RESULT_UNSUPPORTEDMEDIATYPE         ,  __L("Unsupported Media Type")           } ,
                                  { DIOWEBHEADER_RESULT_REQUESTEDRANGENOTSATISFIABLE ,  __L("Requested Range Not Satisfiable")  } ,
                                  { DIOWEBHEADER_RESULT_EXPECTATIONFAILED            ,  __L("Expectation Failed")               } ,

                                  { DIOWEBHEADER_RESULT_INTERNALSERVERERROR          ,  __L("Internal Server Error")            } ,
                                  { DIOWEBHEADER_RESULT_NOTIMPLEMENTED               ,  __L("Not Implemented")                  } ,
                                  { DIOWEBHEADER_RESULT_BADGATEWAY                   ,  __L("Bad Gateway")                      } ,
                                  { DIOWEBHEADER_RESULT_SERVICEUNAVAILABLE           ,  __L("Service Unavailable")              } ,
                                  { DIOWEBHEADER_RESULT_GATEWAYTIMEOUT               ,  __L("Gateway Timeout")                  } ,
                                  { DIOWEBHEADER_RESULT_HTTPVERSIONNOTSUPPORTED      ,  __L("HTTP Version Not Supported")       }
                                };

  description.Empty();

  for(int c=0;c<sizeof(descriptions)/sizeof(DESCRIPTION);c++)
    {
      if(result == descriptions[c].result)
        {
          description = descriptions[c].description;

          return true;
        }
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_HEADER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_HEADER::Clean()
{


}

#pragma endregion 


#pragma region DIOWEBSOCKET_HEADER

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSOCKET_HEADER::DIOWEBSOCKET_HEADER()
* @brief      Constructor
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSOCKET_HEADER::DIOWEBSOCKET_HEADER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSOCKET_HEADER::~DIOWEBSOCKET_HEADER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSOCKET_HEADER::~DIOWEBSOCKET_HEADER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSOCKET_HEADER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSOCKET_HEADER::Clean()
{

}

#pragma endregion 


#pragma region DIOWEBSERVER_AUTHENTICATION


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_AUTHENTICATION::DIOWEBSERVER_AUTHENTICATION()
* @brief      Constructor
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_AUTHENTICATION::DIOWEBSERVER_AUTHENTICATION()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_AUTHENTICATION::~DIOWEBSERVER_AUTHENTICATION()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_AUTHENTICATION::~DIOWEBSERVER_AUTHENTICATION()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOWEBSERVER_AUTHENTICATION::GetGuest()
* @brief      GetGuest
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOWEBSERVER_AUTHENTICATION::GetGuest()
{
  return &guest;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOWEBSERVER_AUTHENTICATION::GetLogin()
* @brief      GetLogin
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOWEBSERVER_AUTHENTICATION::GetLogin()
{
  return &login;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOWEBSERVER_AUTHENTICATION::GetPassword()
* @brief      GetPassword
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOWEBSERVER_AUTHENTICATION::GetPassword()
{
  return &password;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_AUTHENTICATION::Set(XSTRING& login, XSTRING& password)
* @brief      DIOWEBSERVER_AUTHENTICATION::Set
* @ingroup    DATAIO
*
* @param[in]  login :
* @param[in]  password :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_AUTHENTICATION::Set(XSTRING& login, XSTRING& password)
{
  this->login    = login;
  this->password = password;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_AUTHENTICATION::Set(XSTRING& guest, XSTRING& login, XSTRING& password)
* @brief      Set
* @ingroup    DATAIO
*
* @param[in]  guest :
* @param[in]  login :
* @param[in]  password :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_AUTHENTICATION::Set(XSTRING& guest, XSTRING& login, XSTRING& password)
{
  this->guest    = guest;
  this->login    = login;
  this->password = password;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_AUTHENTICATION::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_AUTHENTICATION::Clean()
{

}

#pragma endregion


#pragma region DIOWEBSERVER_REQUEST

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_REQUEST::DIOWEBSERVER_REQUEST()
* @brief      Constructor
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_REQUEST::DIOWEBSERVER_REQUEST()

{
  Clean();
  data = new XBUFFER();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_REQUEST::~DIOWEBSERVER_REQUEST()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_REQUEST::~DIOWEBSERVER_REQUEST()
{
  delete data;

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_TYPE DIOWEBSERVER_REQUEST::GetType()
* @brief      GetType
* @ingroup    DATAIO
*
* @return     DIOWEBSERVER_TYPE :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_TYPE DIOWEBSERVER_REQUEST::GetType()
{
  return type;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_REQUEST::SetType(DIOWEBSERVER_TYPE type)
* @brief      SetType
* @ingroup    DATAIO
*
* @param[in]  type :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_REQUEST::SetType(DIOWEBSERVER_TYPE type)
{
  this->type = type;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBHEADER_METHOD DIOWEBSERVER_REQUEST::GetMethod()
* @brief      GetMethod
* @ingroup    DATAIO
*
* @return     DIOWEBHEADER_METHOD :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBHEADER_METHOD DIOWEBSERVER_REQUEST::GetMethod()
{
  return method;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_REQUEST::SetMethod(DIOWEBHEADER_METHOD method)
* @brief      SetMethod
* @ingroup    DATAIO
*
* @param[in]  method :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_REQUEST::SetMethod(DIOWEBHEADER_METHOD method)
{
  this->method = method;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOWEBSERVER_REQUEST::GetResource()
* @brief      GetResource
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOWEBSERVER_REQUEST::GetResource()
{
  return &resource;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOWEBSERVER_REQUEST::GetGuest()
* @brief      GetGuest
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOWEBSERVER_REQUEST::GetGuest()
{
  return &guest;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOWEBSERVER_REQUEST::GetUserAgent()
* @brief      GetUserAgent
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOWEBSERVER_REQUEST::GetUserAgent()
{
  return &useragent;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOWEBSERVER_REQUEST::GetSize()
* @brief      GetSize
* @ingroup    DATAIO
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOWEBSERVER_REQUEST::GetSize()
{
  return size;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_REQUEST::SetSize(XDWORD size)
* @brief      SetSize
* @ingroup    DATAIO
*
* @param[in]  size :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_REQUEST::SetSize(XDWORD size)
{
  this->size = size;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOWEBSERVER_REQUEST::GetIfNoneMatch()
* @brief      GetIfNoneMatch
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOWEBSERVER_REQUEST::GetIfNoneMatch()
{
  return &ifnonematch;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_REQUEST::SetIfNoneMatch(XSTRING& ifnonematch)
* @brief      SetIfNoneMatch
* @ingroup    DATAIO
*
* @param[in]  ifnonematch :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_REQUEST::SetIfNoneMatch(XSTRING& ifnonematch)
{
  XSTRING special;

  special = ifnonematch;

  special.DeleteCharacter(0x20    , XSTRINGCONTEXT_FROM_FIRST);
  special.DeleteCharacter(0x20    , XSTRINGCONTEXT_TO_END);
  special.DeleteCharacter(__C('"'), XSTRINGCONTEXT_FROM_FIRST);
  special.DeleteCharacter(__C('"'), XSTRINGCONTEXT_TO_END);

  this->ifnonematch = special;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOWEBSERVER_REQUEST::GetAcceptedCharset()
* @brief      GetAcceptedCharset
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOWEBSERVER_REQUEST::GetAcceptedCharset()
{
  return &acceptedcharset;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOWEBSERVER_REQUEST::GetAcceptedControlRequestMethod()
* @brief      GetAcceptedControlRequestMethod
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOWEBSERVER_REQUEST::GetAcceptedControlRequestMethod()
{
  return &acceptedcontrolrequestmethod;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOWEBSERVER_REQUEST::GetAcceptedLanguage()
* @brief      GetAcceptedLanguage
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOWEBSERVER_REQUEST::GetAcceptedLanguage()
{
  return &acceptedlanguage;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOWEBSERVER_REQUEST::GetAcceptedAllowHeaders()
* @brief      GetAcceptedAllowHeaders
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOWEBSERVER_REQUEST::GetAcceptedAllowHeaders()
{
  return &acceptedallowheaders;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_REQUEST::ProcessAcceptedEncodingFlags(XSTRING& string)
* @brief      ProcessAcceptedEncodingFlags
* @ingroup    DATAIO
*
* @param[in]  string :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_REQUEST::ProcessAcceptedEncodingFlags(XSTRING& string)
{
  if(string.IsEmpty()) return;

  //DIEGO: Achtung! you have to calculate the Q = 0 of the headers just in case it is a browser Obsolete

  if(string.Find(__L("gzip"),     false) != NOTFOUND)   acceptedencodingflags |= DIOWEBSERVER_ENCODINGFLAGS_GZIP;
  if(string.Find(__L("deflate"),  false) != NOTFOUND)   acceptedencodingflags |= DIOWEBSERVER_ENCODINGFLAGS_DEFLATE;
  if(string.Find(__L("compress"), false) != NOTFOUND)   acceptedencodingflags |= DIOWEBSERVER_ENCODINGFLAGS_COMPRESS;
  if(string.Find(__L("sdhc"),     false) != NOTFOUND)   acceptedencodingflags |= DIOWEBSERVER_ENCODINGFLAGS_SHAREDDICTIONARY;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOWEBSERVER_REQUEST::GetAccessControlAllowOrigin()
* @brief      GetAccessControlAllowOrigin
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOWEBSERVER_REQUEST::GetAccessControlAllowOrigin()
{
  return &accesscontrolalloworigin;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOWEBSERVER_REQUEST::GetAccessControlAllowMethods()
* @brief      GetAccessControlAllowMethods
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOWEBSERVER_REQUEST::GetAccessControlAllowMethods()
{
  return &accesscontrolallowmethods;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOWEBSERVER_REQUEST::GetAccessControlAllowHeaders()
* @brief      GetAccessControlAllowHeaders
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOWEBSERVER_REQUEST::GetAccessControlAllowHeaders()
{
  return &accesscontrolallowheaders;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOWEBSERVER_REQUEST::GetOrigin()
* @brief      GetOrigin
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOWEBSERVER_REQUEST::GetOrigin()
{
  return &origin;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOWEBSERVER_REQUEST::GetConnection()
* @brief      GetConnection
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOWEBSERVER_REQUEST::GetConnection()
{
  return &connection;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOWEBSERVER_REQUEST::GetUpgrade()
* @brief      GetUpgrade
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOWEBSERVER_REQUEST::GetUpgrade()
{
  return &upgrade;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBUFFER* DIOWEBSERVER_REQUEST::GetData()
* @brief      GetData
* @ingroup    DATAIO
*
* @return     XBUFFER* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XBUFFER* DIOWEBSERVER_REQUEST::GetData()
{
  return data;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_REQUEST::HaveLoginPassword()
* @brief      HaveLoginPassword
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_REQUEST::HaveLoginPassword()
{
  return (loginpassword.IsEmpty()?false:true);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_REQUEST::GetLoginPassword(XSTRING& login, XSTRING& password)
* @brief      GetLoginPassword
* @ingroup    DATAIO
*
* @param[in]  login :
* @param[in]  password :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_REQUEST::GetLoginPassword(XSTRING& login, XSTRING& password)
{
  if(loginpassword.IsEmpty()) return false;

  XSTRING lp;

  lp.ConvertToBase64(loginpassword);
  //lp.ConvertFromBase64(loginpassword);

  int index = lp.Find(__L(":"),true);
  if(index ==  XSTRING_NOTFOUND) return false;

  lp.Copy(0,index,login);
  lp.Copy(index+1,password);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_REQUEST::SetLoginPassword(XSTRING& loginpassword)
* @brief      SetLoginPassword
* @ingroup    DATAIO
*
* @param[in]  loginpassword :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_REQUEST::SetLoginPassword(XSTRING& loginpassword)
{
  this->loginpassword = loginpassword;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_REQUEST::ConvertFromWeb(XSTRING& string)
* @brief      ConvertFromWeb
* @ingroup    DATAIO
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_REQUEST::ConvertFromWeb(XSTRING& string)
{
  int c = 0;

  XCHAR* str = string.Get();

  while(str[c])
    {
      if(str[c]==__C('%'))
        {
          XSTRING string2;

          string2.Format(__L("%c%c"),str[c+2],str[c+1]);

          int code = string2.ConvertToInt();
          if(code)
            {
              str[c]=code;

              string.DeleteCharacters(c+1,2);
              str = string.Get();
            }

        } else c++;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_REQUEST::IsAcceptedEncodingFlag(DIOWEBSERVER_ENCODINGFLAGS flag)
* @brief      IsAcceptedEncodingFlag
* @ingroup    DATAIO
*
* @param[in]  flag :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_REQUEST::IsAcceptedEncodingFlag(DIOWEBSERVER_ENCODINGFLAGS flag)
{
  return ((acceptedencodingflags&flag) != 0);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOWEBSERVER_REQUEST::WebSocket_GetKey()
* @brief      WebSocket_GetKey
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOWEBSERVER_REQUEST::WebSocket_GetKey()
{
  return &websocket_key;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOWEBSERVER_REQUEST::WebSocket_GetProtocol()
* @brief      WebSocket_GetProtocol
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOWEBSERVER_REQUEST::WebSocket_GetProtocol()
{
  return &websocket_protocol;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOWEBSERVER_REQUEST::WebSocket_GetVersion()
* @brief      WebSocket_GetVersion
* @ingroup    DATAIO
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOWEBSERVER_REQUEST::WebSocket_GetVersion()
{
  return websocket_version;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_REQUEST::WebSocket_SetVersion(int version)
* @brief      WebSocket_SetVersion
* @ingroup    DATAIO
*
* @param[in]  version :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_REQUEST::WebSocket_SetVersion(int version)
{
  websocket_version = version;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_REQUEST::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_REQUEST::Clean()
{
  type                      = DIOWEBSERVER_TYPE_NONE;
  method                    = DIOWEBHEADER_METHOD_UNKNOWN;

  resource.Empty();
  guest.Empty();
  useragent.Empty();
  loginpassword.Empty();
  ifnonematch.Empty();

  acceptedcharset.Empty();
  acceptedcontrolrequestmethod.Empty();
  acceptedlanguage.Empty();
  acceptedallowheaders.Empty();

  acceptedencodingflags     = DIOWEBSERVER_ENCODINGFLAGS_NONE;

  accesscontrolalloworigin.Empty();
  accesscontrolallowmethods.Empty();
  accesscontrolallowheaders.Empty();

  origin.Empty();

  connection.Empty();
  upgrade.Empty();

  iskeepalive               = false;

  websocket_isrequest       = false;
  websocket_key.Empty();
  websocket_protocol.Empty();
  websocket_version         = 0;

  size                      = -1;
  data                      = NULL;
}

#pragma endregion


#pragma region DIOWEBSERVER_CONNECTION

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_CONNECTION::DIOWEBSERVER_CONNECTION()
* @brief      Constructor
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_CONNECTION::DIOWEBSERVER_CONNECTION()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_CONNECTION::~DIOWEBSERVER_CONNECTION()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_CONNECTION::~DIOWEBSERVER_CONNECTION()
{
  End();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_CONNECTION::Ini(DIOWEBSERVER* webserver, DIOSTREAMTCPIPCONFIG* diostreamcfg)
* @brief      Ini
* @ingroup    DATAIO
*
* @param[in]  webserver :
* @param[in]  diostreamcfg :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_CONNECTION::Ini(DIOWEBSERVER* webserver, DIOSTREAMTCPIPCONFIG* diostreamcfg)
{
  this->webserver     = webserver;
  this->diostreamcfg  = diostreamcfg;

  SetMode(DIOWEBSERVER_CONNECTION_MODE_UNKNOWN);

  GEN_XFACTORY_CREATE(xtimerconnection, CreateTimer())
  if(!xtimerconnection)      return false;
  
  GEN_XFACTORY_CREATE(xtimerdisconnection, CreateTimer())
  if(!xtimerdisconnection)   return false;
    
  nresourcesprocessed = 0;

  diostream = (DIOSTREAMTCPIP*)GEN_DIOFACTORY.CreateStreamIO(diostreamcfg);
  if(!diostream)          return false;

  threadconnection   = CREATEXTHREAD(XTHREADGROUPID_DIOWEBSERVER, __L("DIOWEBSERVER_CONNECTION::Ini"), ThreadRunFunction, (void*)this);
  if(!threadconnection)   return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMTCPIP* DIOWEBSERVER_CONNECTION::GetDIOStream()
* @brief      GetDIOStream
* @ingroup    DATAIO
*
* @return     DIOSTREAMTCPIP* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMTCPIP* DIOWEBSERVER_CONNECTION::GetDIOStream()
{
  return diostream;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTIMER* DIOWEBSERVER_CONNECTION::GetTimerConnection()
* @brief      GetTimerConnection
* @ingroup    DATAIO
*
* @return     XTIMER* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XTIMER* DIOWEBSERVER_CONNECTION::GetTimerConnection()
{
  return xtimerconnection;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_CONNECTION::IsActive()
* @brief      IsActive
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_CONNECTION::IsActive()
{
  return isactive;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_CONNECTION::Activate()
* @brief      Activate
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_CONNECTION::Activate()
{
  if(!threadconnection) return false;
  if(!xtimerconnection) return false;

  isactive = true;

  threadconnection->Ini();

  xtimerconnection->Reset();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_CONNECTION::Deactivate()
* @brief      Deactivate
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_CONNECTION::Deactivate()
{
  if(!GetDIOStream())   return false;
  if(!threadconnection) return false;

 // End Server connection page
  GetDIOStream()->WaitToFlushOutXBuffer(5);
  GetDIOStream()->Disconnect();

  threadconnection->Run(false);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_CONNECTION_MODE DIOWEBSERVER_CONNECTION::GetMode()
* @brief      GetMode
* @ingroup    DATAIO
*
* @return     DIOWEBSERVER_CONNECTION_MODE :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_CONNECTION_MODE DIOWEBSERVER_CONNECTION::GetMode()
{
  return mode;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_CONNECTION::SetMode(DIOWEBSERVER_CONNECTION_MODE mode)
* @brief      SetMode
* @ingroup    DATAIO
*
* @param[in]  mode :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_CONNECTION::SetMode(DIOWEBSERVER_CONNECTION_MODE mode)
{
  this->mode = mode;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_CONNECTION::Receiver(XBYTE* buffer, XDWORD& size, int timeout)
* @brief      Receiver
* @ingroup    DATAIO
*
* @param[in]  buffer :
* @param[in]  size :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_CONNECTION::Receiver(XBYTE* buffer, XDWORD& size, int timeout)
{
  if(!diostream)                return false;
  if(!diostream->IsConnected()) return false;
  if(!size)                     return false;

  XDWORD br;

  XTIMER* GEN_XFACTORY_CREATE(xtimerout, CreateTimer())
  if(!xtimerout)  return false;
  
  bool status = true;

  while(1)
    {
      if(!diostream)
        {
          status = false;
          break;
        }

      if(!diostream->IsConnected())
        {
          status = false;
          break;
        }

      br = diostream->Read(buffer, size);
      if(br) break;

      if(xtimerout->GetMeasureSeconds()>= (XDWORD)timeout) break;
    }

  GEN_XFACTORY.DeleteTimer(xtimerout);

  if(!br) return false;
  size = br;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_CONNECTION::Send(XBYTE* buffer, XDWORD& size, int timeout)
* @brief      Send
* @ingroup    DATAIO
*
* @param[in]  buffer :
* @param[in]  size :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_CONNECTION::Send(XBYTE* buffer, XDWORD& size, int timeout)
{
  if(!diostream) return false;
  if(!size)      return false;

  bool status = true;
  int  bw     = 0;

  bw = diostream->Write(buffer, size);
  if(size != bw) status = false;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_CONNECTION::Send(XBUFFER& xbuffer, int timeout)
* @brief      Send
* @ingroup    DATAIO
*
* @param[in]  xbuffer :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_CONNECTION::Send(XBUFFER& xbuffer, int timeout)
{
  XDWORD size = xbuffer.GetSize();

  return Send(xbuffer.Get(), size, timeout);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_CONNECTION::IsRequestInProgress()
* @brief      IsRequestInProgress
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_CONNECTION::IsRequestInProgress()
{
  return isrequestinprogress;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER* DIOWEBSERVER_CONNECTION::GetServer()
* @brief      GetServer
* @ingroup    DATAIO
*
* @return     DIOWEBSERVER* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER* DIOWEBSERVER_CONNECTION::GetServer()
{
  return this->webserver;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBCLIENT_HEADER* DIOWEBSERVER_CONNECTION::GetHeader()
* @brief      GetHeader
* @ingroup    DATAIO
*
* @return     DIOWEBCLIENT_HEADER* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBCLIENT_HEADER* DIOWEBSERVER_CONNECTION::GetHeader()
{
  return &header;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_REQUEST* DIOWEBSERVER_CONNECTION::GetRequest()
* @brief      GetRequest
* @ingroup    DATAIO
*
* @return     DIOWEBSERVER_REQUEST* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_REQUEST* DIOWEBSERVER_CONNECTION::GetRequest()
{
  return &request;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_ENCODINGFLAGS DIOWEBSERVER_CONNECTION::GetActualEncodingFlag()
* @brief      GetActualEncodingFlag
* @ingroup    DATAIO
*
* @return     DIOWEBSERVER_ENCODINGFLAGS :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_ENCODINGFLAGS DIOWEBSERVER_CONNECTION::GetActualEncodingFlag()
{
  return actualencodingflag;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_CONNECTION::SetActualEncodingFlag(DIOWEBSERVER_ENCODINGFLAGS actualencodingflag)
* @brief      SetActualEncodingFlag
* @ingroup    DATAIO
*
* @param[in]  actualencodingflag :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_CONNECTION::SetActualEncodingFlag(DIOWEBSERVER_ENCODINGFLAGS actualencodingflag)
{
  if(!webserver) return false;

  if(!webserver->IsIncludedEncodingFlag(actualencodingflag))
    {
      actualencodingflag = DIOWEBSERVER_ENCODINGFLAGS_NONE;
      return false;
    }

  this->actualencodingflag = actualencodingflag;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_CONNECTION::WebSocket_Write(XCHAR* string, int timeout)
* @brief      WebSocket_Write
* @ingroup    DATAIO
*
* @param[in]  string :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_CONNECTION::WebSocket_Write(XCHAR* string, int timeout)
{
  XBUFFER  data;
  XSTRING  _string;

  _string = string;

  WebSocket_CreateHeader(DIOWEBSERVER_WEBSOCKET_OPCODE_TEXT_FRAME, _string.GetSize(), data);

  XSTRING_CREATEOEM(_string, charvar);
  data.Add((XBYTE*)charvar, _string.GetSize());
  XSTRING_DELETEOEM(_string, charvar);

  return Send(data, timeout);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_CONNECTION::WebSocket_Write(XSTRING& string, int timeout)
* @brief      WebSocket_Write
* @ingroup    DATAIO
*
* @param[in]  string :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_CONNECTION::WebSocket_Write(XSTRING& string, int timeout)
{
  return WebSocket_Write(string.Get(), timeout);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_CONNECTION::WebSocket_Write(XBYTE* buffer, XDWORD size, int timeout)
* @brief      WebSocket_Write
* @ingroup    DATAIO
*
* @param[in]  buffer :
* @param[in]  size :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_CONNECTION::WebSocket_Write(XBYTE* buffer, XDWORD size, int timeout)
{
  XBUFFER data;

  WebSocket_CreateHeader(DIOWEBSERVER_WEBSOCKET_OPCODE_BINARY_FRAME, size, data);

  data.Add(buffer, size);

  return Send(data, timeout);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_CONNECTION::WebSocket_Write(XBUFFER& buffer, int timeout)
* @brief      WebSocket_Write
* @ingroup    DATAIO
*
* @param[in]  buffer :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_CONNECTION::WebSocket_Write(XBUFFER& buffer, int timeout)
{
  return WebSocket_Write(buffer.Get(), buffer.GetSize(), timeout);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_CONNECTION::WebSocket_WritePingPong(bool isping, XCHAR* string, int timeout)
* @brief      WebSocket_WritePingPong
* @ingroup    DATAIO
*
* @param[in]  isping :
* @param[in]  string :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_CONNECTION::WebSocket_WritePingPong(bool isping, XCHAR* string, int timeout)
{
  XBUFFER  data;
  XSTRING  _string;

  _string = string;

  WebSocket_CreateHeader((isping?DIOWEBSERVER_WEBSOCKET_OPCODE_PING:DIOWEBSERVER_WEBSOCKET_OPCODE_PONG), _string.GetSize(), data);

  XSTRING_CREATEOEM(_string, charvar);
  data.Add((XBYTE*)charvar, _string.GetSize());
  XSTRING_DELETEOEM(_string, charvar);

  return Send(data, timeout);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_CONNECTION::WebSocket_WritePingPong(bool isping, XSTRING& string, int timeout)
* @brief      WebSocket_WritePingPong
* @ingroup    DATAIO
*
* @param[in]  isping :
* @param[in]  string :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_CONNECTION::WebSocket_WritePingPong(bool isping, XSTRING& string, int timeout)
{
  return WebSocket_WritePingPong(isping, string.Get(), timeout);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_CONNECTION::WebSocket_WritePingPong(bool isping, XBUFFER& data, int timeout)
* @brief      WebSocket_WritePingPong
* @ingroup    DATAIO
*
* @param[in]  isping :
* @param[in]  data :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_CONNECTION::WebSocket_WritePingPong(bool isping, XBUFFER& data, int timeout)
{
  XBUFFER _data;

  WebSocket_CreateHeader((isping?DIOWEBSERVER_WEBSOCKET_OPCODE_PING:DIOWEBSERVER_WEBSOCKET_OPCODE_PONG), data.GetSize(), _data);

  _data.Add(data.Get(), data.GetSize());

  return Send(_data, timeout);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTIMER* DIOWEBSERVER_CONNECTION::GetTimerDisconnection()
* @brief      GetTimerDisconnection
* @ingroup    DATAIO
*
* @return     XTIMER* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
XTIMER* DIOWEBSERVER_CONNECTION::GetTimerDisconnection()
{
 return xtimerdisconnection;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_CONNECTION::End()
* @brief      End
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_CONNECTION::End()
{
  if(threadconnection)
    {
      threadconnection->End();
      DELETEXTHREAD(XTHREADGROUPID_DIOWEBSERVER, threadconnection);
      threadconnection = NULL;
    }

  if(diostream)
    {
      diostream->Close();

      GEN_DIOFACTORY.DeleteStreamIO(diostream);
      diostream = NULL;
    }

  if(xtimerconnection)
    {
      GEN_XFACTORY.DeleteTimer(xtimerconnection);
      xtimerconnection = NULL;
    }

  if(xtimerdisconnection)
    {
      GEN_XFACTORY.DeleteTimer(xtimerdisconnection);
      xtimerdisconnection = NULL;
    }

  isactive            = false;
  isrequestinprogress = false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_CONNECTION::RequestRequest(DIOWEBSERVER_REQUEST& request, int timeout)
* @brief      GetRequest
* @ingroup    DATAIO
*
* @param[in]  request :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_CONNECTION::ReadRequest()
{
  if(!diostream) return false;

  if(!diostream->IsConnected())                 return false;
  if(diostream->GetInXBuffer()->GetSize() < 5)  return false;

  if(!header.Read(diostream, DIOWEBSERVER_DEFAULTCONNECTIONTIMEOUT))  return false;

  XSTRING string;

  string = (*(XSTRING*)(header.GetLines()->Get(0)));

  if(string.Find(__L("HTTP/"),true,4)!=XSTRING_NOTFOUND)
    {
      request.SetType(DIOWEBSERVER_TYPE_FULL);

    } else request.SetType(DIOWEBSERVER_TYPE_SYMPLE);

  header.GetMethod(string);

  //XTRACE_PRINTCOLOR(1, __L("method: %s"), string.Get());

  request.SetMethod(DIOWEBHEADER_METHOD_UNKNOWN);

  if(!string.Compare(__L("GET")     , true))  request.SetMethod(DIOWEBHEADER_METHOD_GET);
  if(!string.Compare(__L("HEAD")    , true))  request.SetMethod(DIOWEBHEADER_METHOD_HEAD);
  if(!string.Compare(__L("POST")    , true))  request.SetMethod(DIOWEBHEADER_METHOD_POST);
  if(!string.Compare(__L("PUT")     , true))  request.SetMethod(DIOWEBHEADER_METHOD_PUT);
  if(!string.Compare(__L("DELETE")  , true))  request.SetMethod(DIOWEBHEADER_METHOD_DELETE);
  if(!string.Compare(__L("CONNECT") , true))  request.SetMethod(DIOWEBHEADER_METHOD_CONNECT);
  if(!string.Compare(__L("OPTIONS") , true))  request.SetMethod(DIOWEBHEADER_METHOD_OPTIONS);
  if(!string.Compare(__L("TRACE")   , true))  request.SetMethod(DIOWEBHEADER_METHOD_TRACE);

  header.GetResource(string);
  if(string.GetSize()) request.GetResource()->Set(string);

  string = header.GetFieldValue(__L("Host:"));
  request.GetGuest()->Set(string);

  string = header.GetFieldValue(__L("User-Agent:"));
  request.GetUserAgent()->Set(string);

  string = header.GetFieldValue(__L("Content-Length:"));
  if(!string.IsEmpty()) request.SetSize(string.ConvertToInt());

  string = header.GetFieldValue(__L("If-None-Match:"));
  request.SetIfNoneMatch(string);

  string = header.GetFieldValue(__L("Authorization: basic"));
  request.SetLoginPassword(string);

  string = header.GetFieldValue(__L("Accept-Encoding:"));
  request.ProcessAcceptedEncodingFlags(string);

  string = header.GetFieldValue(__L("Accept-Language:"));
  request.GetAcceptedLanguage()->Set(string);

  string = header.GetFieldValue(__L("Accept-Charset:"));
  request.GetAcceptedCharset()->Set(string);

  string = header.GetFieldValue(__L("Access-Control-Allow-Origin:"));
  request.GetAccessControlAllowOrigin()->Set(string);

  string = header.GetFieldValue(__L("Access-Control-Allow-Methods:"));
  request.GetAcceptedControlRequestMethod()->Set(string);

  string = header.GetFieldValue(__L("Access-Control-Allow-Headers:"));
  request.GetAccessControlAllowHeaders()->Set(string);

  string = header.GetFieldValue(__L("origin:"));
  request.GetOrigin()->Set(string);

  string = header.GetFieldValue(__L("Connection:"));
  request.GetConnection()->Set(string);

  string = header.GetFieldValue(__L("Upgrade:"));
  request.GetUpgrade()->Set(string);

  string = header.GetFieldValue(__L("Sec-WebSocket-Key:"));
  request.WebSocket_GetKey()->Set(string);

  string = header.GetFieldValue(__L("Sec-WebSocket-Protocol:"));
  request.WebSocket_GetProtocol()->Set(string);

  string = header.GetFieldValue(__L("Sec-WebSocket-Version:"));
  request.WebSocket_SetVersion(string.ConvertToInt());

  if(request.GetSize()>0)
    {
      XBUFFER* data = request.GetData();
      if(!data) return false;

      XDWORD size;

      data->Delete();

      XBYTE* buffer = new XBYTE[DIOWEBSERVER_MAXBUFFER];
      if(!buffer) return false;

      do{ memset(buffer,0,DIOWEBSERVER_MAXBUFFER);
          size = (request.GetSize() - data->GetSize());
          if(size>DIOWEBSERVER_MAXBUFFER) size = DIOWEBSERVER_MAXBUFFER;

          if(size)
            {
              Receiver((XBYTE*)buffer,size, DIOWEBSERVER_DEFAULTCONNECTIONTIMEOUT);
              if(size) data->Add((XBYTE*)buffer,size);
            }

        } while(size);

      delete [] buffer;
    }

  //----------------------------------------------------------------------------------

  SetMode(DIOWEBSERVER_CONNECTION_MODE_NORMAL);

  if(!request.GetConnection()->Compare(__L("Keep-Alive"), true))
    {
      SetMode(DIOWEBSERVER_CONNECTION_MODE_KEEPALIVE);
    }

  if(!request.GetConnection()->Compare(__L("Upgrade"), true) &&
     !request.GetUpgrade()->Compare(__L("websocket")))
    {
      SetMode(DIOWEBSERVER_CONNECTION_MODE_WEBSOCKET);
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_CONNECTION::SendRequest()
* @brief      SendRequest
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_CONNECTION::SendRequest()
{
  if(!webserver) return false;
  if(!diostream) return false;

  if(request.GetMethod() == DIOWEBHEADER_METHOD_UNKNOWN) return false;

  GEN_XLOG.AddEntry(XLOGLEVEL_INFO, DIOWEBSERVER_LOGSECTIONID , false, __L("[%08X] Server Page INI [%d] %s"), this, nresourcesprocessed, request.GetResource()->Get());

  DIOWEBSERVER_XEVENT xevent(webserver, DIOWEBSERVER_XEVENT_TYPE_REQUEST);
  xevent.SetServer(webserver);
  xevent.SetConnection(this);
  xevent.SetRequest(&request);

  webserver->PostEvent(&xevent);

  GEN_XLOG.AddEntry(XLOGLEVEL_INFO, DIOWEBSERVER_LOGSECTIONID , false, __L("[%08X] Server Page END [%d] %s"), this, nresourcesprocessed, request.GetResource()->Get());

  nresourcesprocessed++;
 
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_CONNECTION::WebSocket_CreateAcceptKey(XSTRING* key, XSTRING* result)
* @brief      CreateWebSocketAccept
* @ingroup    DATAIO
*
* @param[in]  key :
* @param[in]  result :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_CONNECTION::WebSocket_CreateAcceptKey(XSTRING& key, XSTRING& result)
{
  if(key.IsEmpty()) return false;

  #define DIOWEBSERVER_WEBSOCKET_GUID  __L("258EAFA5-E914-47DA-95CA-C5AB0DC85B11")

  XSTRING resultbrute;
  bool    status;

  result.Empty();

  resultbrute  = key;
  resultbrute += DIOWEBSERVER_WEBSOCKET_GUID;

  result.Empty();

  HASHSHA1* sha1 = new HASHSHA1();
  if(!sha1) return false;

  XSTRING_CREATEOEM(resultbrute, charresult);
  status = sha1->Do((XBYTE*)charresult, resultbrute.GetSize());
  XSTRING_DELETEOEM(resultbrute, charresult);

  sha1->GetResult()->ConvertToBase64(result);

  delete sha1;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_CONNECTION::WebSocket_CreateHeader(DIOWEBSERVER_WEBSOCKET_OPCODE opcode, XDWORD size, XBUFFER& data)
* @brief      WebSocket_CreateHeader
* @ingroup    DATAIO
*
* @param[in]  opcode :
* @param[in]  size :
* @param[in]  data :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_CONNECTION::WebSocket_CreateHeader(DIOWEBSERVER_WEBSOCKET_OPCODE opcode, XDWORD size, XBUFFER& data)
{
  data.Empty();

  XWORD miniheader = 0x8000;

  miniheader |= (opcode << 8);

  if(size >= 65536)
    {
      miniheader |= 127;
      data.Add((XWORD)miniheader);

      XQWORD sizedata = size;
      data.Add((XQWORD)sizedata);
    }
   else
    {
      if(size >= 256)
        {
          miniheader |= 126;
          data.Add((XWORD)miniheader);

          XWORD sizedata = size;
          data.Add((XWORD)sizedata);
        }
       else
        {
          miniheader |=  (XBYTE)size;
          data.Add((XWORD)miniheader);
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_CONNECTION::Websocket_ResolveConnection(DIOWEBSERVER_REQUEST* request)
* @brief      Websocket_ResolveConnection
* @ingroup    DATAIO
*
* @param[in]  request :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_CONNECTION::Websocket_ResolveConnection(DIOWEBSERVER_REQUEST* request)
{
  DIOWEBSERVER_HEADER webserverheader;
  XSTRING             resultwebsocketaccept;
  bool                status = false;

  if(!WebSocket_CreateAcceptKey((*GetRequest()->WebSocket_GetKey()) , resultwebsocketaccept)) return false;

  webserverheader.Create(GetRequest()->GetResource(), 1, 1,  DIOWEBHEADER_RESULT_SWITCHINGPROTOCOLS, -1, NULL, false);
  webserverheader.AddWebSocketKey(resultwebsocketaccept, (*GetRequest()->WebSocket_GetProtocol()));

  status = webserverheader.Write(GetDIOStream(), 5);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_CONNECTION::WebSocket_ReadRequest(DIOWEBSERVER_WEBSOCKET_OPCODE& opcode, XBUFFER& data)
* @brief      WebSocket_ReadRequest
* @ingroup    DATAIO
*
* @param[in]  opcode :
* @param[in]  data :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_CONNECTION::WebSocket_ReadRequest(DIOWEBSERVER_WEBSOCKET_OPCODE& opcode, XBUFFER& data)
{
  opcode = DIOWEBSERVER_WEBSOCKET_OPCODE_RESERVED10;

  if(!diostream)                return false;
  if(!diostream->IsConnected()) return false;

  XDWORD  sizetoread = diostream->GetInXBuffer()->GetSize();
  if(sizetoread <  sizeof(WEBSOCKET_HEADERFRAME))  return false;

   XWORD                 hf          = 0;
   WEBSOCKET_HEADERFRAME headerframe;

   if(!diostream->GetInXBuffer()->Get((XBYTE*)&hf, sizeof(XWORD))) return false;

   if(GEN_XSYSTEM.HardwareUseLittleEndian())  SWAPWORD(hf);

   memcpy(&headerframe, &hf, sizeof(WEBSOCKET_HEADERFRAME));

   XQWORD sizeallmsg      = sizeof(XWORD);
   XBYTE  extpayloadsize  = 0;
   XQWORD sizedata        = headerframe.size;

   if(sizedata == 127)
     {
       if(!diostream->GetInXBuffer()->Get((XBYTE*)&sizedata, 8, 2 )) return false;
       if(GEN_XSYSTEM.HardwareUseLittleEndian())  SWAPQWORD(sizedata);

       extpayloadsize = sizeof(XQWORD);
       sizeallmsg     += sizedata;
     }
    else
     {
       if(sizedata == 126)
         {
            XWORD msize = 0;
            if(!diostream->GetInXBuffer()->Get((XBYTE*)&msize, 2, 2 )) return false;
            if(GEN_XSYSTEM.HardwareUseLittleEndian())  SWAPWORD(msize);

            sizedata       = msize;
            extpayloadsize = sizeof(XWORD);
            sizeallmsg    += sizedata;
         }
        else
         {
           sizeallmsg += headerframe.size;
         }
    }

  sizeallmsg += extpayloadsize;
  if(headerframe.mask) sizeallmsg += sizeof(XDWORD);

  // Have all frame available to Read?
  if(sizetoread < sizeallmsg) return false;

  if(!diostream->GetInXBuffer()->Extract(NULL, 0,  (sizeof(XWORD) + extpayloadsize))) return false;

  XBYTE maskcipher[4];


  if(headerframe.mask)
    {
      if(!diostream->Read(maskcipher, sizeof(maskcipher))) return false;
    }

  data.Empty();

  if(sizedata)
    {
      data.Resize((XDWORD)sizedata);

      if(!diostream->Read(data)) return false;

      if(headerframe.mask)
        {
          for(XDWORD c = 0; c<data.GetSize(); c++)
            {
              data.Get()[c] ^= maskcipher[c % 4];
            }
        }
    }

  opcode = (DIOWEBSERVER_WEBSOCKET_OPCODE)headerframe.opcode;

  websocket_xbufferframepart.Add(data);

  if(opcode == DIOWEBSERVER_WEBSOCKET_OPCODE_CONTINUATION_FRAME)
    {
      return false;
    }

  if(headerframe.final)
    {
      data.Empty();
      data.Add(websocket_xbufferframepart);

      websocket_xbufferframepart.Empty();

      return true;
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_CONNECTION::WebSocket_SendEvent_Connected()
* @brief      WebSocket_SendEvent_Connected
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_CONNECTION::WebSocket_SendEvent_Connected()
{
  if(!webserver) return false;
  if(!diostream) return false;

  if(request.GetMethod() == DIOWEBHEADER_METHOD_UNKNOWN) return false;

  bool status = false;

  DIOWEBSERVER_XEVENT xevent(webserver, DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_CONNECTED);
  xevent.SetServer(webserver);
  xevent.SetConnection(this);
  xevent.SetRequest(&request);
  xevent.SetStatus(false);

  webserver->PostEvent(&xevent);

  if(xevent.GetStatus()) status = Websocket_ResolveConnection(&request);

  GEN_XLOG.AddEntry((status?XLOGLEVEL_INFO:XLOGLEVEL_WARNING), DIOWEBSERVER_LOGSECTIONID  , false, __L("[%08X] Websocket %s %d %s %s")  , this
                                                                                                                                        , (status?__L("Connected"):__L("No connected"))
                                                                                                                                        , request.WebSocket_GetVersion()
                                                                                                                                        , request.WebSocket_GetProtocol()->Get()
                                                                                                                                        , request.GetResource()->Get());

  isrequestinprogress = false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_CONNECTION::WebSocket_SendEvent_ReadData(XBUFFER& data)
* @brief      WebSocket_SendEvent_ReadData
* @ingroup    DATAIO
*
* @param[in]  data :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_CONNECTION::WebSocket_SendEvent_ReadData(XBUFFER& data)
{
  if(!webserver) return false;
  if(!diostream) return false;

  DIOWEBSERVER_XEVENT xevent(webserver, DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_READDATA);
  xevent.SetServer(webserver);
  xevent.SetConnection(this);
  xevent.SetRequest(&request);
  xevent.GetReadDataWebSocket()->Empty();
  xevent.GetReadDataWebSocket()->Add(data);

  webserver->PostEvent(&xevent);

  GEN_XLOG.AddEntry(XLOGLEVEL_INFO, DIOWEBSERVER_LOGSECTIONID , false, __L("[%08X] Websocket read data %d %s %s"), this
                                                                                                                 , request.WebSocket_GetVersion()
                                                                                                                 , request.WebSocket_GetProtocol()->Get()
                                                                                                                 , request.GetResource()->Get());
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_CONNECTION::WebSocket_SendEvent_Pong(XBUFFER& data)
* @brief      WebSocket_SendEvent_Pong
* @ingroup    DATAIO
*
* @param[in]  data :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_CONNECTION::WebSocket_SendEvent_Pong(XBUFFER& data)
{
  if(!webserver) return false;
  if(!diostream) return false;

  DIOWEBSERVER_XEVENT xevent(webserver, DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_PONG);
  xevent.SetServer(webserver);
  xevent.SetConnection(this);
  xevent.SetRequest(&request);
  xevent.GetReadDataWebSocket()->Empty();
  xevent.GetReadDataWebSocket()->Add(data);

  webserver->PostEvent(&xevent);

  GEN_XLOG.AddEntry(XLOGLEVEL_INFO, DIOWEBSERVER_LOGSECTIONID , false, __L("[%08X] Websocket Ping Received %d %s %s"), this
                                                                                                                     , request.WebSocket_GetVersion()
                                                                                                                     , request.WebSocket_GetProtocol()->Get()
                                                                                                                     , request.GetResource()->Get());
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_CONNECTION::WebSocket_SendEvent_Disconnected()
* @brief      WebSocket_SendEvent_Disconnected
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_CONNECTION::WebSocket_SendEvent_Disconnected()
{
  if(!webserver) return false;
  if(!diostream) return false;

  DIOWEBSERVER_XEVENT xevent(webserver, DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_DISCONNECTED);
  xevent.SetServer(webserver);
  xevent.SetConnection(this);
  xevent.SetRequest(&request);
  xevent.GetReadDataWebSocket()->Empty();

  webserver->PostEvent(&xevent);

  GEN_XLOG.AddEntry(XLOGLEVEL_INFO, DIOWEBSERVER_LOGSECTIONID , false, __L("[%08X] Websocket disconnected %d %s %s")  , this
                                                                                                                      , request.WebSocket_GetVersion()
                                                                                                                      , request.WebSocket_GetProtocol()->Get()
                                                                                                                      , request.GetResource()->Get());
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_CONNECTION::ThreadRunFunction(void* param)
* @brief      ThreadRunFunction
* @ingroup    DATAIO
*
* @param[in]  param :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_CONNECTION::ThreadRunFunction(void* param)
{
  DIOWEBSERVER_CONNECTION* wsconn = (DIOWEBSERVER_CONNECTION*)param;
  if(!wsconn) return;

  DIOWEBSERVER_WEBSOCKET_OPCODE opcode      = DIOWEBSERVER_WEBSOCKET_OPCODE_RESERVED10;
  bool                          sendrequest = false;

  switch(wsconn->GetMode())
    {
      case DIOWEBSERVER_CONNECTION_MODE_UNKNOWN       :
      case DIOWEBSERVER_CONNECTION_MODE_NORMAL        :
      case DIOWEBSERVER_CONNECTION_MODE_KEEPALIVE     : if(wsconn->ReadRequest())
                                                          {
                                                            wsconn->isrequestinprogress = true;

                                                            switch(wsconn->GetMode())
                                                              {
                                                                case DIOWEBSERVER_CONNECTION_MODE_UNKNOWN      :
                                                                case DIOWEBSERVER_CONNECTION_MODE_NORMAL       :
                                                                case DIOWEBSERVER_CONNECTION_MODE_KEEPALIVE    : sendrequest = wsconn->SendRequest();
                                                                                                                 if(sendrequest) wsconn->GetTimerDisconnection()->Reset();
                                                                                                                 wsconn->isrequestinprogress = false;
                                                                                                                 break;

                                                                case DIOWEBSERVER_CONNECTION_MODE_WEBSOCKET    : sendrequest = wsconn->WebSocket_SendEvent_Connected();
                                                                                                                 break;
                                                              }                                                          
                                                          }

                                                        wsconn->GetTimerDisconnection()->Reset();
                                                        break;

      case DIOWEBSERVER_CONNECTION_MODE_WEBSOCKET     : { XBUFFER data;
                                                          if(wsconn->WebSocket_ReadRequest(opcode, data))
                                                            {
                                                              switch(opcode)
                                                                {
                                                                  case DIOWEBSERVER_WEBSOCKET_OPCODE_CONTINUATION_FRAME   : break;

                                                                  case DIOWEBSERVER_WEBSOCKET_OPCODE_TEXT_FRAME           :
                                                                  case DIOWEBSERVER_WEBSOCKET_OPCODE_BINARY_FRAME         : wsconn->WebSocket_SendEvent_ReadData(data);
                                                                                                                            break;

                                                                  case DIOWEBSERVER_WEBSOCKET_OPCODE_CONNECTION_CLOSE     : break;

                                                                  case DIOWEBSERVER_WEBSOCKET_OPCODE_PING                 : wsconn->WebSocket_WritePingPong(false, data);
                                                                                                                            break;

                                                                  case DIOWEBSERVER_WEBSOCKET_OPCODE_PONG                 : wsconn->WebSocket_SendEvent_Pong(data);
                                                                                                                            break;

                                                                                                            default       : break;
                                                               }

                                                            }
                                                        }
                                                       break;
    }


  switch(wsconn->GetMode())
    {
      case DIOWEBSERVER_CONNECTION_MODE_UNKNOWN       :
      case DIOWEBSERVER_CONNECTION_MODE_NORMAL        : if((wsconn->xtimerconnection->GetMeasureSeconds() >= DIOWEBSERVER_KEEPALIVE) || (sendrequest)) 
                                                          {
                                                            if(wsconn->GetTimerDisconnection()->GetMeasureSeconds() > 5) wsconn->Deactivate();
                                                          }
                                                        break;

      case DIOWEBSERVER_CONNECTION_MODE_KEEPALIVE     : if((wsconn->xtimerconnection->GetMeasureSeconds() >= DIOWEBSERVER_KEEPALIVE) ||
                                                          (wsconn->nresourcesprocessed                    >= DIOWEBSERVER_KEEPALIVE_MAXRESOURCES))     wsconn->Deactivate();
                                                        break;

      case DIOWEBSERVER_CONNECTION_MODE_WEBSOCKET     : if(opcode == DIOWEBSERVER_WEBSOCKET_OPCODE_CONNECTION_CLOSE)
                                                          {
                                                            wsconn->Deactivate();
                                                            wsconn->WebSocket_SendEvent_Disconnected();
                                                          }
                                                        break;
    }


  return;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_CONNECTION::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_CONNECTION::Clean()
{
  webserver             = NULL;
  diostreamcfg          = NULL;
  diostream             = NULL;

  isactive              = false;
  mode                  =  DIOWEBSERVER_CONNECTION_MODE_UNKNOWN;
  xtimerconnection      = NULL;
  xtimerdisconnection   = NULL;
  nresourcesprocessed   = 0;
  isrequestinprogress   = false;

  threadconnection      = NULL;
  actualencodingflag    = DIOWEBSERVER_ENCODINGFLAGS_NONE;

  origin.Empty();
}

#pragma endregion


#pragma region DIOWEBSERVER

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER::DIOWEBSERVER()
* @brief      Constructor
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER::DIOWEBSERVER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER::~DIOWEBSERVER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER::~DIOWEBSERVER()
{
  End();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER::Ini(int port, bool doinitialconnectitivitytest, int timeoutserverpage, XSTRING* addrlocal)
* @brief      Ini
* @ingroup    DATAIO
*
* @param[in]  port : 
* @param[in]  doinitialconnectitivitytest : 
* @param[in]  timeoutserverpage : 
* @param[in]  addrlocal : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER::Ini(int port, bool doinitialconnectitivitytest, int timeoutserverpage, XSTRING* addrlocal)
{
  isactive        = false;
  doexit          = false;

  diostreamcfg = new DIOSTREAMTCPIPCONFIG();
  if(!diostreamcfg) return false;

  this->port                      = port;
  this->timeoutserverpage         = timeoutserverpage;
  if(addrlocal) this->addrlocal   = (*addrlocal);

  AddPlayablePageExtension(__L(".HTML"));
  AddPlayablePageExtension(__L(".HTM"));

  RegisterEvent(DIOWEBSERVER_XEVENT_TYPE_REQUEST);
  RegisterEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_CONNECTED);
  RegisterEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_READDATA);
  RegisterEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_PONG);
  RegisterEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_DISCONNECTED);

  GEN_XFACTORY_CREATE(xtimercontrol, CreateTimer())
  if(!xtimercontrol) return false;
  
  diostreamcfg->SetMode(DIOSTREAMMODE_SERVER);
  diostreamcfg->GetLocalIP()->Set(this->addrlocal);
  diostreamcfg->SetRemotePort(port);

  isactive = true;

  GEN_XFACTORY_CREATE(xmutexconnections, Create_Mutex())
  if(!xmutexconnections) return false;

  bool status = true;

  // ------------------------------------------------------------------------------------
  // TEST Can open socket for WEB server

  if(doinitialconnectitivitytest)
    {
      xtimercontrol->Reset();

      DIOSTREAMTCPIP* diostream = (DIOSTREAMTCPIP*)GEN_DIOFACTORY.CreateStreamIO(diostreamcfg);
      if(diostream)
        {
          if(diostream->Open())
            {
                    
              while(1)
                {
                  if(diostream->GetConnectStatus() == DIOSTREAMSTATUS_DISCONNECTED)
                    {
                      status = false;
                      break;
                    }

                  if(xtimercontrol->GetMeasureSeconds() > 3) break;
                }

              diostream->Close();
            
          
            } else status = false;

          GEN_DIOFACTORY.DeleteStreamIO(diostream);
        }

      if(!status) return false;
    }

  // ------------------------------------------------------------------------------------

  xtimercontrol->Reset();

  threadserver = CREATEXTHREAD(XTHREADGROUPID_DIOWEBSERVER, __L("DIOWEBSERVER::Ini"),ThreadRunFunction,(void*)this);
  if(!threadserver) return false;

  if(!threadserver->Ini()) return false;

  if(addrlocal) GEN_XLOG.AddEntry(XLOGLEVEL_INFO, DIOWEBSERVER_LOGSECTIONID , false , __L("Web Server [%08X]: %s in %s:%d "), this, status?__L("Active"):__L("Disable"),  addrlocal->IsEmpty()?__L("Default"):addrlocal->Get(), port);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOWEBSERVER::GetPort()
* @brief      GetPort
* @ingroup    DATAIO
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOWEBSERVER::GetPort()
{
  return port;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOWEBSERVER::GetTimeoutServerPage()
* @brief      GetTimeoutServerPage
* @ingroup    DATAIO
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOWEBSERVER::GetTimeoutServerPage()
{
  return timeoutserverpage;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMTCPIPCONFIG* DIOWEBSERVER::GetDIOStreamCFG()
* @brief      GetDIOStreamCFG
* @ingroup    DATAIO
*
* @return     DIOSTREAMTCPIPCONFIG* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMTCPIPCONFIG* DIOWEBSERVER::GetDIOStreamCFG()
{
  return diostreamcfg;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER::IsSendingAnyPage()
* @brief      IsSendingAnyPage
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER::IsSendingAnyPage()
{
  bool sending = false;

  if(!connections.IsEmpty())
    {
      for(XDWORD c=0;c<connections.GetSize();c++)
        {
          DIOWEBSERVER_CONNECTION* connection = (DIOWEBSERVER_CONNECTION*)connections.Get(c);
          if(connection)
            {
              if(connection->IsRequestInProgress())
                {
                  sending = true;
                  break;
                }
            }
        }
    }

  return sending;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER::UnSubscribeAllPages()
* @brief      UnSubscribeAllPages
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER::UnSubscribeAllPages()
{
  if(!connections.IsEmpty())
    {
      for(XDWORD c=0;c<connections.GetSize();c++)
        {
          DIOWEBSERVER_CONNECTION* connection = (DIOWEBSERVER_CONNECTION*)connections.Get(c);
          if(connection)
            {
              UnSubscribeEvent(DIOSTREAMXEVENT_TYPE_CONNECTED    , connection->GetDIOStream());
              UnSubscribeEvent(DIOSTREAMXEVENT_TYPE_DISCONNECTED , connection->GetDIOStream());
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER::AddAuthentication(XSTRING& guest,XSTRING& login,XSTRING& password)
* @brief      AddAuthentication
* @ingroup    DATAIO
*
* @param[in]  guest :
* @param[in]  login :
* @param[in]  password :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER::AddAuthentication(XSTRING& guest, XSTRING& login, XSTRING& password)
{
  DIOWEBSERVER_AUTHENTICATION* authentication = GetAuthentication(guest);
  if(authentication)
    {
      authentication->Set(login,password);
    }
   else
    {
      authentication = new DIOWEBSERVER_AUTHENTICATION();
      if(!authentication) return false;

      authentication->Set(guest,login,password);

      authentications.Add(authentication);
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_AUTHENTICATION* DIOWEBSERVER::GetAuthentication(XSTRING& guest)
* @brief      GetAuthentication
* @ingroup    DATAIO
*
* @param[in]  guest :
*
* @return     DIOWEBSERVER_AUTHENTICATION* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_AUTHENTICATION* DIOWEBSERVER::GetAuthentication(XSTRING& guest)
{
  if(authentications.IsEmpty()) return NULL;

  DIOWEBSERVER_AUTHENTICATION* authentication = NULL;

  for(int c=0;c<(int)authentications.GetSize();c++)
    {
      DIOWEBSERVER_AUTHENTICATION* auth = (DIOWEBSERVER_AUTHENTICATION*)authentications.Get(c);
      if(auth)
        {
          if(auth->GetGuest())
            {
              XSTRING* tguest = auth->GetGuest();
              if(tguest)
                {
                  if((*tguest) == guest)
                    {
                      authentication = auth;
                      break;
                    }
                }
            }
        }
    }

  return authentication;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER::DelAuthentication(XSTRING& guest)
* @brief      DelAuthentication
* @ingroup    DATAIO
*
* @param[in]  guest :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER::DelAuthentication(XSTRING& guest)
{
  DIOWEBSERVER_AUTHENTICATION* authentication = GetAuthentication(guest);
  if(!authentication) return false;

  authentications.Delete(authentication);

  delete authentication;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER::DelAllAuthentication()
* @brief      DelAllAuthentication
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER::DelAllAuthentication()
{
  if(authentications.IsEmpty()) return false;

  authentications.DeleteContents();

  authentications.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER::IsPlayablePage(XCHAR* extension)
* @brief      IsPlayablePage
* @ingroup    DATAIO
*
* @param[in]  extension :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER::IsPlayablePage(XCHAR* extension)
{
  if(playablepageextensions.IsEmpty()) return false;

  for(int c=0;c<(int)playablepageextensions.GetSize();c++)
    {
      XSTRING* _extension = (XSTRING*)playablepageextensions.Get(c);
      if(_extension)
        {
          if(!_extension->Compare(extension,true)) return true;
        }
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER::IsPlayablePage(XSTRING& extension)
* @brief      IsPlayablePage
* @ingroup    DATAIO
*
* @param[in]  extension :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER::IsPlayablePage(XSTRING& extension)
{
  return IsPlayablePage(extension.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER::AddPlayablePageExtension(XCHAR* extension)
* @brief      AddPlayablePageExtension
* @ingroup    DATAIO
*
* @param[in]  extension :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER::AddPlayablePageExtension(XCHAR* extension)
{
  if(!extension) return false;

  XSTRING* _string = new XSTRING(extension);
  if(!_string) return false;

  playablepageextensions.Add(_string);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER::AddPlayablePageExtension(XSTRING& extension)
* @brief      AddPlayablePageExtension
* @ingroup    DATAIO
*
* @param[in]  extension :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER::AddPlayablePageExtension(XSTRING& extension)
{
  XSTRING* _string = new XSTRING(extension);
  if(!_string) return false;

  playablepageextensions.Add(_string);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER::DeleteAllPlayablePageExtensions()
* @brief      DeleteAllPlayablePageExtensions
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER::DeleteAllPlayablePageExtensions()
{
  if(playablepageextensions.IsEmpty()) return false;

  playablepageextensions.DeleteContents();
  playablepageextensions.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER::AddIncludedEncodingFlag(DIOWEBSERVER_ENCODINGFLAGS flag)
* @brief      AddIncludedEncodingFlag
* @ingroup    DATAIO
*
* @param[in]  flag :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER::AddIncludedEncodingFlag(DIOWEBSERVER_ENCODINGFLAGS flag)
{
  includedencodingflags |= flag;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER::IsIncludedEncodingFlag(DIOWEBSERVER_ENCODINGFLAGS flag)
* @brief      IsIncludedEncodingFlag
* @ingroup    DATAIO
*
* @param[in]  flag :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER::IsIncludedEncodingFlag(DIOWEBSERVER_ENCODINGFLAGS flag)
{
  return ((includedencodingflags&flag) != 0);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XMUTEX* DIOWEBSERVER::GetMutextConnections()
* @brief      GetMutextConnections
* @ingroup    DATAIO
*
* @return     XMUTEX* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XMUTEX* DIOWEBSERVER::GetMutextConnections()
{
  return xmutexconnections;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XVECTOR<DIOWEBSERVER_CONNECTION*>* DIOWEBSERVER::GetConnections()
* @brief      GetConnections
* @ingroup    DATAIO
*
* @return     XVECTOR<DIOWEBSERVER_CONNECTION*>* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<DIOWEBSERVER_CONNECTION*>* DIOWEBSERVER::GetConnections()
{
  return &connections;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_CONNECTION* DIOWEBSERVER::Websocket_GetConnection()
* @brief      Websocket_GetConnection
* @ingroup    DATAIO
*
* @return     DIOWEBSERVER_CONNECTION* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_CONNECTION* DIOWEBSERVER::Websocket_GetConnection()
{
  if(connections.IsEmpty()) return NULL;

  websocket_search_indexconnection = 0;
  websocket_search_protocol.Empty();
  websocket_search_version         = 0;
  websocket_search_resource.Empty();

  return Websocket_GetNextConnection();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_CONNECTION* DIOWEBSERVER::Websocket_GetConnection(XCHAR* protocol)
* @brief      Websocket_GetConnection
* @ingroup    DATAIO
*
* @param[in]  protocol :
*
* @return     DIOWEBSERVER_CONNECTION* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_CONNECTION* DIOWEBSERVER::Websocket_GetConnection(XCHAR* protocol)
{
  if(connections.IsEmpty()) return NULL;

  websocket_search_indexconnection = 0;
  websocket_search_protocol        = protocol;
  websocket_search_version         = 0;
  websocket_search_resource.Empty();

  return Websocket_GetNextConnection();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_CONNECTION* DIOWEBSERVER::Websocket_GetConnection(XCHAR* protocol, int version)
* @brief      Websocket_GetConnection
* @ingroup    DATAIO
*
* @param[in]  protocol :
* @param[in]  version :
*
* @return     DIOWEBSERVER_CONNECTION* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_CONNECTION* DIOWEBSERVER::Websocket_GetConnection(XCHAR* protocol, int version)
{
  if(connections.IsEmpty()) return NULL;
 
  websocket_search_indexconnection = 0;
  websocket_search_protocol        = protocol;
  websocket_search_version         = version;
  websocket_search_resource.Empty();

  return Websocket_GetNextConnection();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_CONNECTION* DIOWEBSERVER::Websocket_GetConnection(XCHAR* protocol, int version, XCHAR* resource)
* @brief      Websocket_GetConnection
* @ingroup    DATAIO
*
* @param[in]  protocol :
* @param[in]  version :
* @param[in]  resource :
*
* @return     DIOWEBSERVER_CONNECTION* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_CONNECTION* DIOWEBSERVER::Websocket_GetConnection(XCHAR* protocol, int version, XCHAR* resource)
{
  if(connections.IsEmpty()) return NULL;

  websocket_search_indexconnection = 0;
  websocket_search_protocol        = protocol;
  websocket_search_version         = version;
  websocket_search_resource        = resource;

  return Websocket_GetNextConnection();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_CONNECTION* DIOWEBSERVER::Websocket_GetConnection()
* @brief      Websocket_GetConnection
* @ingroup    DATAIO
*
* @return     DIOWEBSERVER_CONNECTION* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_CONNECTION* DIOWEBSERVER::Websocket_GetNextConnection()
{
  if(connections.IsEmpty()) return NULL;

  if(websocket_search_indexconnection == -1) return NULL;

  DIOWEBSERVER_CONNECTION* connection    = NULL;
  XBYTE                    filter_mask   = 0x00;
  XBYTE                    filter_status = 0x00;

  if(websocket_search_protocol.GetSize())  filter_mask  |= 0x01;
  if(websocket_search_version)             filter_mask  |= 0x02;
  if(websocket_search_resource.GetSize())  filter_mask  |= 0x04;

  if(xmutexconnections) xmutexconnections->Lock();

  for( ; websocket_search_indexconnection<(int)connections.GetSize(); websocket_search_indexconnection++)
    {
      connection = connections.Get(websocket_search_indexconnection);
      if(connection)
        {
          if(connection->GetMode() == DIOWEBSERVER_CONNECTION_MODE_WEBSOCKET)
            {
              if(!filter_mask) break;

              filter_status = 0x00;
              if(!connection->GetRequest()->WebSocket_GetProtocol()->Compare(websocket_search_protocol))   filter_status |= 0x01;
              if(connection->GetRequest()->WebSocket_GetVersion()  == websocket_search_version)            filter_status |= 0x02;
              if(!connection->GetRequest()->GetResource()->Compare(websocket_search_resource))             filter_status |= 0x04;

              if(filter_mask == filter_status) break;

            } else connection = NULL;
        }
    }

  if(xmutexconnections) xmutexconnections->UnLock();

  if(!connection)
         websocket_search_indexconnection = -1;
    else websocket_search_indexconnection++;

  return connection;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER::Websocket_Write(XSTRING& string, int timeout, XCHAR* protocol, int version, XCHAR* resource)
* @brief      Websocket_Write
* @ingroup    DATAIO
*
* @param[in]  string :
* @param[in]  timeout :
* @param[in]  protocol :
* @param[in]  version :
* @param[in]  resource :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER::Websocket_Write(XCHAR* string, int timeout, XCHAR* protocol, int version, XCHAR* resource)
{
  DIOWEBSERVER_CONNECTION* connection;
  bool                     status = true;

  connection = Websocket_GetConnection(protocol, version, resource);
  while(connection)
    {
      if(connection->WebSocket_Write(string, timeout)) status = false;

      connection = Websocket_GetNextConnection();
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER::Websocket_Write(XSTRING& string, int timeout, XCHAR* protocol, int version, XCHAR* resource)
* @brief      Websocket_Write
* @ingroup    DATAIO
*
* @param[in]  string :
* @param[in]  timeout :
* @param[in]  protocol :
* @param[in]  version :
* @param[in]  resource :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER::Websocket_Write(XSTRING& string, int timeout, XCHAR* protocol, int version, XCHAR* resource)
{
  return Websocket_Write(string.Get(), timeout, protocol, version, resource);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER::Websocket_Write(XBUFFER& data, int timeout, XCHAR* protocol, int version, XCHAR* resource)
* @brief      Websocket_Write
* @ingroup    DATAIO
*
* @param[in]  data :
* @param[in]  timeout :
* @param[in]  protocol :
* @param[in]  version :
* @param[in]  resource :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER::Websocket_Write(XBUFFER& data, int timeout, XCHAR* protocol, int version, XCHAR* resource)
{
  DIOWEBSERVER_CONNECTION* connection;
  bool                     status = true;

  connection = Websocket_GetConnection(protocol, version, resource);
  while(connection)
    {
      if(connection->WebSocket_Write(data, timeout)) status = false;

      connection = Websocket_GetNextConnection();
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER::Websocket_Ping(XCHAR* string, int timeout, XCHAR* protocol, int version, XCHAR* resource)
* @brief      Websocket_Ping
* @ingroup    DATAIO
*
* @param[in]  string :
* @param[in]  timeout :
* @param[in]  protocol :
* @param[in]  version :
* @param[in]  resource :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER::Websocket_Ping(XCHAR* string, int timeout, XCHAR* protocol, int version, XCHAR* resource)
{
  DIOWEBSERVER_CONNECTION* connection;
  bool                     status = true;

  connection = Websocket_GetConnection(protocol, version, resource);
  while(connection)
    {
      if(!connection->WebSocket_WritePingPong(true, string, timeout)) status = false;

      connection = Websocket_GetNextConnection();
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER::Websocket_Ping(XSTRING& string, int timeout, XCHAR* protocol, int version, XCHAR* resource)
* @brief      Websocket_Ping
* @ingroup    DATAIO
*
* @param[in]  string :
* @param[in]  timeout :
* @param[in]  protocol :
* @param[in]  version :
* @param[in]  resource :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER::Websocket_Ping(XSTRING& string, int timeout, XCHAR* protocol, int version, XCHAR* resource)
{
  return Websocket_Ping(string.Get(), timeout, protocol, version, resource);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_PLUGINSMANAGER DIOWEBSERVER::GetPluginsManager()
* @brief      GetPluginsManager
* @ingroup    DATAIO
*
* @return     DIOWEBSERVER_PLUGINSMANAGER :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_PLUGINSMANAGER* DIOWEBSERVER::GetPluginsManager()
{
  return &pluginsmanager;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER::IsExit()
* @brief      IsExit
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER::IsExit()
{
  return doexit;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER::End()
* @brief      End
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER::End()
{
  doexit = true;

  GEN_XLOG.AddEntry(XLOGLEVEL_INFO, DIOWEBSERVER_LOGSECTIONID , false , __L("Disable web server [%08X]."), this);

  UnSubscribeAllPages();

  GEN_XLOG.AddEntry(XLOGLEVEL_INFO, NULL , false , __L("Delete main thread ... "));

  if(threadserver)
    {
      threadserver->End();
      DELETEXTHREAD(XTHREADGROUPID_DIOWEBSERVER, threadserver);
      threadserver = NULL;
    }

  GEN_XLOG.AddEntry(XLOGLEVEL_INFO, NULL  , false , __L("Wait to send all pages ..."));
  WaitToSentAllPages();

  GEN_XLOG.AddEntry(XLOGLEVEL_INFO, NULL  , false , __L("Delete connections not use ..."));
  Connections_DeleteUsed();

  GEN_XLOG.AddEntry(XLOGLEVEL_INFO, NULL  , false , __L("Delete connections waiting ..."));
  Connections_DeleteWaiting();

  GEN_XLOG.AddEntry(XLOGLEVEL_INFO, NULL , false , __L("Delete all connections ... "));
  Connections_DeleteAll();

  if(xmutexconnections)
    {
      GEN_XFACTORY.Delete_Mutex(xmutexconnections);
      xmutexconnections = NULL;
    }

  GEN_XLOG.AddEntry(XLOGLEVEL_INFO, NULL , false , __L("Delete resources ... "));

  if(xtimercontrol)
    {
      GEN_XFACTORY.DeleteTimer(xtimercontrol);
      xtimercontrol = NULL;
    }

  DeleteAllPlayablePageExtensions();

  DelAllAuthentication();

  GEN_XLOG.AddEntry(XLOGLEVEL_INFO, NULL , false , __L("Delete events ... "));

  DeRegisterEvent(DIOWEBSERVER_XEVENT_TYPE_REQUEST);
  DeRegisterEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_CONNECTED);
  DeRegisterEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_READDATA);
  DeRegisterEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_PONG);
  DeRegisterEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_DISCONNECTED);

  GEN_XLOG.AddEntry(XLOGLEVEL_INFO, NULL , false , __L("Delete stream config ... "));

  if(diostreamcfg)
    {
      delete diostreamcfg;
      diostreamcfg = NULL;
    }

  GEN_XLOG.AddEntry(XLOGLEVEL_INFO, NULL , false , __L("End web server [%08X]."), this);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER::WaitToSentAllPages()
* @brief      WaitToSentAllPages
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER::WaitToSentAllPages()
{
  if(!connections.IsEmpty())
    {
      if(xtimercontrol)
        {
          do{ GEN_XSLEEP.MilliSeconds(10);

            } while(IsSendingAnyPage());
        }
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOWEBSERVER::Connections_GetNWaiting()
* @brief      Connections_GetNWaiting
* @ingroup    DATAIO
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOWEBSERVER::Connections_GetNWaiting()
{
  if(xmutexconnections) xmutexconnections->Lock();

  int nconnectionswait = 0;

  if(!connections.IsEmpty())
    {
      for(XDWORD c=0;c<connections.GetSize();c++)
        {
          DIOWEBSERVER_CONNECTION* connection = (DIOWEBSERVER_CONNECTION*)connections.Get(c);
          if(connection)
            {
              if((!connection->IsRequestInProgress())  && (connection->GetDIOStream()->GetConnectStatus() == DIOSTREAMSTATUS_GETTINGCONNECTION))
                {
                  nconnectionswait++;
                }
            }
        }
    }

  if(xmutexconnections) xmutexconnections->UnLock();

  return nconnectionswait;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOWEBSERVER::Connections_GetNConnectionsSendingPage()
* @brief      Connections_GetNConnectionsSendingPage
* @ingroup    DATAIO
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOWEBSERVER::Connections_GetNConnectionsSendingPage()
{
  int nconnections = 0;

  if(!connections.IsEmpty())
    {
      for(XDWORD c=0;c<connections.GetSize();c++)
        {
          DIOWEBSERVER_CONNECTION* connection = (DIOWEBSERVER_CONNECTION*)connections.Get(c);
          if(connection)
            {
              if(connection->IsRequestInProgress())
                {
                  nconnections++;
                }
            }
        }
    }

  return nconnections;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER::Connections_CreateNew()
* @brief      Connections_CreateNew
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER::Connections_CreateNew()
{
  XDWORD nwaiting = Connections_GetNWaiting();
  if(nwaiting >= DIOWEBSERVER_MAXPAGECONNECTIONS)  return false;

  if(xmutexconnections) xmutexconnections->Lock();

  DIOWEBSERVER_CONNECTION* connection = new DIOWEBSERVER_CONNECTION();
  if(connection)
    {
      if(connection->Ini(this, diostreamcfg))
        {
          if(connection->GetDIOStream()->Open())
            {
              SubscribeEvent(DIOSTREAMXEVENT_TYPE_CONNECTED    , connection->GetDIOStream());
              SubscribeEvent(DIOSTREAMXEVENT_TYPE_DISCONNECTED , connection->GetDIOStream());

              XTRACE_PRINTCOLOR(1, __L("Create Connexion: [%08X]"), connection);

              connections.Add(connection);

              if(xmutexconnections) xmutexconnections->UnLock();

              return true;
            }
            else
            {
              connection->End();
              delete connection;
            }

        } else delete connection;
    }

  if(xmutexconnections) xmutexconnections->UnLock();

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER::Connections_DeleteUsed()
* @brief      Connections_DeleteUsed
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER::Connections_DeleteUsed()
{
  if(xmutexconnections) xmutexconnections->Lock();

  if(!connections.IsEmpty())
    {
      int c = 0;

      do{ DIOWEBSERVER_CONNECTION* connection = (DIOWEBSERVER_CONNECTION*)connections.Get(c);
          if(connection)
            {
              if((connection->GetDIOStream()->GetConnectStatus() == DIOSTREAMSTATUS_DISCONNECTED) &&  (!connection->IsRequestInProgress()))
                {
                  UnSubscribeEvent(DIOSTREAMXEVENT_TYPE_CONNECTED    , connection->GetDIOStream());
                  UnSubscribeEvent(DIOSTREAMXEVENT_TYPE_DISCONNECTED , connection->GetDIOStream());

                  XTRACE_PRINTCOLOR(1, __L("Delete Connexion: [%08X]"), connection);

                  connections.Delete(connection);
                  delete connection;

                } else c++;
            }

        } while(c<(int)connections.GetSize());
    }

  if(xmutexconnections) xmutexconnections->UnLock();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER::Connections_DeleteWaiting()
* @brief      Connections_DeleteWaiting
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER::Connections_DeleteWaiting()
{
  if(xmutexconnections) xmutexconnections->Lock();

  if(!connections.IsEmpty())
    {
      int c = 0;

      do{ DIOWEBSERVER_CONNECTION* connection = (DIOWEBSERVER_CONNECTION*)connections.Get(c);
          if(connection)
            {
              if((!connection->IsRequestInProgress())  && (connection->GetDIOStream()->GetConnectStatus() == DIOSTREAMSTATUS_GETTINGCONNECTION))
                {
                  connections.Delete(connection);
                  delete connection;

                } else c++;
            }

        } while(c<(int)connections.GetSize());
    }

  if(xmutexconnections) xmutexconnections->UnLock();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER::Connections_DeleteAll()
* @brief      Connections_DeleteAll
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER::Connections_DeleteAll()
{
  if(xmutexconnections) xmutexconnections->Lock();

  if(!connections.IsEmpty())
    {
      connections.DeleteContents();
      connections.DeleteAll();
    }

  if(xmutexconnections) xmutexconnections->UnLock();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER::HandleEvent_DIOStream(DIOSTREAMXEVENT* event)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    DATAIO
*
* @param[in]  event :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER::HandleEvent_DIOStream(DIOSTREAMXEVENT* event)
{
  if(!event) return;

  switch(event->GetEventType())
    {
      case DIOSTREAMXEVENT_TYPE_CONNECTED    : { for(XDWORD c=0; c<connections.GetSize(); c++)
                                                  {
                                                    DIOWEBSERVER_CONNECTION* connection = (DIOWEBSERVER_CONNECTION*)connections.Get(c);
                                                    if(connection)
                                                      {
                                                        if(connection->GetDIOStream() == event->GetDIOStream())
                                                          {
                                                            connection->Activate();

                                                            XSTRING IPstring;
                                                            connection->GetDIOStream()->GetClientIP()->GetXString(IPstring);
                                                            GEN_XLOG.AddEntry(XLOGLEVEL_INFO, DIOWEBSERVER_LOGSECTIONID , false, __L("[%08X] Connection Active [%s]"), connection, IPstring.Get());

                                                            break;
                                                          }
                                                      }
                                                  }
                                              }
                                              break;

      case DIOSTREAMXEVENT_TYPE_DISCONNECTED : { for(XDWORD c=0; c<connections.GetSize(); c++)
                                                  {
                                                    DIOWEBSERVER_CONNECTION* connection = (DIOWEBSERVER_CONNECTION*)connections.Get(c);
                                                    if(connection)
                                                      {
                                                        if(connection->GetDIOStream() == event->GetDIOStream())
                                                          {
                                                            XSTRING IPstring;
                                                            connection->GetDIOStream()->GetClientIP()->GetXString(IPstring);
                                                            GEN_XLOG.AddEntry(XLOGLEVEL_INFO, DIOWEBSERVER_LOGSECTIONID , false, __L("[%08X] Connection Deactive [%s]"), connection, IPstring.Get());

                                                            break;
                                                          }
                                                      }
                                                  }
                                              }
                                              break;
    }

}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER::HandleEvent(XEVENT* xevent)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    DATAIO
*
* @param[in]  xevent :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER::HandleEvent(XEVENT* xevent)
{
  if(!xevent) return;

  switch(xevent->GetEventFamily())
    {
      case XEVENT_TYPE_DIOSTREAM   : { DIOSTREAMXEVENT* event = (DIOSTREAMXEVENT*)xevent;
                                      if(!event) return;

                                      HandleEvent_DIOStream(event);
                                    }
                                    break;

    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER::ThreadRunFunction(void* param)
* @brief      ThreadRunFunction
* @ingroup    DATAIO
*
* @param[in]  param :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER::ThreadRunFunction(void* param)
{
  DIOWEBSERVER* webserver = (DIOWEBSERVER*)param;
  if(!webserver) return;

  if(!webserver->diostreamcfg) return;

  if(webserver->doexit) return;

  webserver->Connections_DeleteUsed();
  webserver->Connections_CreateNew();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER::Clean()
{
  diostreamcfg                      = NULL;
  port                              = DIOWEBSERVER_DEFAULTPORT;
  timeoutserverpage                 = 0;
  xmutexconnections                 = NULL;

  isactive                          = false;
  doexit                            = false;
  xtimercontrol                     = NULL;
  threadserver                      = NULL;

  includedencodingflags             = DIOWEBSERVER_ENCODINGFLAGS_NONE;

  websocket_search_indexconnection  = -1;
  websocket_search_protocol.Empty();
  websocket_search_version          = 0;
  websocket_search_resource.Empty();
}

#pragma endregion 
