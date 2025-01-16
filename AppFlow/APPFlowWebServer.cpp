/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       APPFlowWebServer.cpp
* 
* @class      APPFLOWWEBSERVER
* @brief      Application Flow Web Server class
* @ingroup    APPFLOW
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

#include "APPFlowWebServer.h"

#include "XFile.h"
#include "XPath.h"
#include "XLog.h"

#include "HashMD5.h"

#include "DIOStreamTCPIP.h"
#include "DIOWebServer_Plugin_PHP.h"
#include "DIOWebServer_XEvent.h"

#include "APPFlowCFG.h"
#include "APPFlowLog.h"

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


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPFLOWWEBSERVER::APPFLOWWEBSERVER()
* @brief      Constructor
* @ingroup    APPFLOW
*
* --------------------------------------------------------------------------------------------------------------------*/
APPFLOWWEBSERVER::APPFLOWWEBSERVER()
{
  Clean();

  webserver = new DIOWEBSERVER();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPFLOWWEBSERVER::~APPFLOWWEBSERVER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    APPFLOW
*
* --------------------------------------------------------------------------------------------------------------------*/
APPFLOWWEBSERVER::~APPFLOWWEBSERVER()
{
  End();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPFLOWWEBSERVER::Ini(APPFLOWCFG* cfg, bool doinitialconnectitivitytest, bool isapirestonly, bool chekuseragentid)
* @brief      Ini
* @ingroup    APPFLOW
*
* @param[in]  cfg : 
* @param[in]  doinitialconnectitivitytest : 
* @param[in]  isapirestonly : 
* @param[in]  chekuseragentid : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWWEBSERVER::Ini(APPFLOWCFG* cfg, bool doinitialconnectitivitytest,  bool isapirestonly, bool chekuseragentid)
{
  if(!cfg) return false;

  this->cfg = cfg;

  if(!webserver)  return false;

  /*
  if(chekuseragentid)
    {
      useragentID = new DIOSCRAPERWEBUSERAGENTID();
      if(!useragentID) return false;
    }
  */

  if(!cfg->WebServer_PathPHP()->IsEmpty())
    {
      pluginPHP = new DIOWEBSERVER_PLUGIN_PHP();
      if(pluginPHP)
        {
          pluginPHP->Config(cfg->WebServer_PathPHP());

          if(!webserver->GetPluginsManager()->Plugins_Add(pluginPHP)) return false;
        }
    }

  return Ini(cfg->WebServer_GetPort(), doinitialconnectitivitytest, cfg->WebServer_GetTimeoutToServerPage(), cfg->WebServer_GetLocalAddress());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPFLOWWEBSERVER::Ini(XDWORD port, , bool doinitialconnectitivitytest, int timeoutserverpage, XSTRING* addrlocal)
* @brief      Ini
* @ingroup    APPFLOW
*
* @param[in]  port : 
* @param[in]  doinitialconnectitivitytest : 
* @param[in]  timeoutserverpage : 
* @param[in]  addrlocal : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWWEBSERVER::Ini(XDWORD port, bool doinitialconnectitivitytest, int timeoutserverpage, XSTRING* addrlocal)
{
  if(!webserver)  return false;

  bool status = webserver->Ini(port, doinitialconnectitivitytest, timeoutserverpage, addrlocal);
  if(status)
    {
      RegisterEvent(DIOWEBSERVER_XEVENT_TYPE_REQUEST);
      SubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_REQUEST                , (XSUBJECT *)webserver);

      if(isauthenticatedaccess)
        {
          RegisterEvent(DIOWEBSERVER_XEVENT_TYPE_DOAUTHENTICATE);
          RegisterEvent(DIOWEBSERVER_XEVENT_TYPE_CHECKAUTHENTICATE);
        }

      RegisterEvent(DIOWEBSERVER_XEVENT_TYPE_REQUEST_ENDPOINT);
      SubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_REQUEST_ENDPOINT       , (XSUBJECT *)webserver);

      RegisterEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_CONNECTED);
      SubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_CONNECTED    , (XSUBJECT *)webserver);

      RegisterEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_READDATA);
      SubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_READDATA     , (XSUBJECT *)webserver);

      RegisterEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_PONG);
      SubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_PONG         , (XSUBJECT *)webserver);

      RegisterEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_DISCONNECTED);
      SubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_DISCONNECTED , (XSUBJECT *)webserver);
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER* APPFLOWWEBSERVER::GetWebServer()
* @brief      GetWebServer
* @ingroup    APPFLOW
*
* @return     DIOWEBSERVER* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER* APPFLOWWEBSERVER::GetWebServer()
{
  return webserver;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPFLOWWEBSERVER::GetIsAuthenticatedAccess()
* @brief      GetIsAuthenticatedAccess
* @ingroup    APPFLOW
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWWEBSERVER::GetIsAuthenticatedAccess()
{
  return isauthenticatedaccess;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPFLOWWEBSERVER::GetIsApiRestOnly()
* @brief      GetIsApiRestOnly
* @ingroup    APPFLOW
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWWEBSERVER::GetIsApiRestOnly()
{
  return isapirestonly;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPFLOWWEBSERVER::SendRequest(DIOWEBSERVER_CONNECTION* connection, DIOWEBHEADER_RESULT headerresult, XBUFFER* data, int timeout, XSTRING* addhead)
* @brief      SendRequest
* @ingroup    APPFLOW
* 
* @param[in]  connection : 
* @param[in]  headerresult : 
* @param[in]  data : 
* @param[in]  timeout : 
* @param[in]  addhead : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWWEBSERVER::SendRequest(DIOWEBSERVER_CONNECTION* connection, DIOWEBHEADER_RESULT headerresult, XBUFFER* data, int timeout, XSTRING* addhead)
{
  DIOWEBSERVER_HEADER webserverheader;
  XSTRING             entitytag;
  HASHMD5             hashmd5;
  bool                iscached = false;
  bool                status   = false;

  if(!connection)                                return false;
  if(!connection->GetDIOStream())                return false;
  if(!connection->GetDIOStream()->IsConnected()) return false;

  if(data)
    {
      hashmd5.Do((*data));
      hashmd5.GetResultString(entitytag);
      iscached = connection->GetRequest()->GetIfNoneMatch()->Compare(entitytag)?false:true;
    }

  if(iscached)
    {
      webserverheader.Create(connection->GetRequest()->GetResource(), 1, 1, DIOWEBHEADER_RESULT_NOTMODIFIED, connection->GetRequest()->GetSize());
      status = webserverheader.Write(connection->GetDIOStream(), 5);
    }
   else
    {
      XPATH resourceext;
      int   size = (data ?(int)data->GetSize():-1);

      resourceext = connection->GetRequest()->GetResource()->Get();
      resourceext.SetOnlyExt();

      webserverheader.Create(connection->GetRequest()->GetResource(), 1, 1, headerresult, size, &entitytag, connection->GetServer()->IsPlayablePage(resourceext));
      if(addhead) webserverheader.AddLine(addhead->Get());
      status = webserverheader.Write(connection->GetDIOStream(), 5);
      if(status)
        {
          if(size > 0) status = connection->Send((*data), timeout);
        }
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPFLOWWEBSERVER::SendRequest(DIOWEBSERVER_CONNECTION* connection, DIOWEBHEADER_RESULT headerresult, XSTRING& data, int timeout, XSTRING* addhead)
* @brief      SendRequest
* @ingroup    APPFLOW
* 
* @param[in]  connection : 
* @param[in]  headerresult : 
* @param[in]  data : 
* @param[in]  timeout : 
* @param[in]  addhead : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWWEBSERVER::SendRequest(DIOWEBSERVER_CONNECTION* connection, DIOWEBHEADER_RESULT headerresult, XSTRING& data, int timeout, XSTRING* addhead)
{
  XDWORD size = data.GetSize();
  if(!size) return false;

  XBUFFER xbuffer(size);
  bool    status = false;

  
  XBUFFER charstr;
  data.ConvertToASCII(charstr);
  memcpy(xbuffer.Get(), charstr.Get(), size);
  status = SendRequest(connection, headerresult, &xbuffer, timeout, addhead);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPFLOWWEBSERVER::SendRequest(DIOWEBSERVER_CONNECTION* connection, DIOWEBHEADER_RESULT headerresult, XPATH& xpathfile, int timeout, XSTRING* addhead)
* @brief      SendRequest
* @ingroup    APPFLOW
* 
* @param[in]  connection : 
* @param[in]  headerresult : 
* @param[in]  xpathfile : 
* @param[in]  timeout : 
* @param[in]  addhead : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWWEBSERVER::SendRequest(DIOWEBSERVER_CONNECTION* connection, DIOWEBHEADER_RESULT headerresult, XPATH& xpathfile, int timeout, XSTRING* addhead)
{
  XBUFFER xbuffer;
  bool    status = false;

  XFILE* GEN_XFACTORY_CREATE(xfile, Create_File())
  if(!xfile) return false;

  if(xfile->Open(xpathfile))
    {
      XQWORD size = xfile->GetSize();
      if(size)
        {
          xbuffer.Resize((XDWORD)size);
          status = xfile->Read(xbuffer.Get(), (XDWORD)size);
        }

      xfile->Close();
    }

  GEN_XFACTORY.Delete_File(xfile);

  if(status) status = SendRequest(connection, headerresult, &xbuffer, timeout, addhead);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPFLOWWEBSERVER::ResolveRequest(DIOWEBSERVER* server, DIOWEBSERVER_CONNECTION* connection, DIOWEBSERVER_REQUEST* request)
* @brief      ResolveRequest
* @ingroup    APPFLOW
* 
* @param[in]  server : 
* @param[in]  connection : 
* @param[in]  request : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWWEBSERVER::ResolveRequest(DIOWEBSERVER* server, DIOWEBSERVER_CONNECTION* connection, DIOWEBSERVER_REQUEST* request)
{
  if(!server)     return false;
  if(!connection) return false;
  if(!request)    return false;

  XSTRING* resource = request->GetResource();
  if(!resource) return false;

  if(!cfg) return false;

  DIOWEBSERVER_HEADER         webserverheader;
  DIOURL                      resourceconv;
  int                         nparams               = 0;
  DIOWEBSERVER_QUERYSTRINGS   querystring;
  XSTRING                     extension;
  bool                        ispagepluging         = false;
  bool                        status                = false;

  resourceconv.Set(resource->Get());
  resourceconv.DecodeUnsafeChars();

  if(isauthenticatedaccess)
    {
      if(!cfg->WebServer_GetPassword()->IsEmpty())
        {
          if(!request->GetLoginPassword(page_login, page_password))
            {
              SendRequest(connection, DIOWEBHEADER_RESULT_UNAUTHORIZED, NULL, 5);

              return true;
            }
           else
            {
              bool ispasswordvalid;

              ispasswordvalid = !page_password.Compare(cfg->WebServer_GetPassword()->Get(), true);
              if(!ispasswordvalid)
                {
                  XSTRING leyend;

                  leyend = __L("Invalid user or password!");
                  GenerateResponse_Error(connection, DIOWEBHEADER_RESULT_NOTFOUND, leyend);
                }  

              XSTRING IPstring;
              connection->GetDIOStream()->GetClientIP()->GetXString(IPstring);           

              APPFLOW_LOG_ENTRY(XLOGLEVEL_ERROR, DIOWEBSERVER_LOGSECTIONID, false, __L("Request from [%s] to the web server password [%s]: %s"), IPstring.Get(), cfg->WebServer_GetPassword()->Get(), (ispasswordvalid)? __L("Ok."): __L("INVALID!") );

              if(!ispasswordvalid) return true;
            }
        }
       else
        {
          bool invalidpassword = false;

          if(page_login.IsEmpty() || page_password.IsEmpty())
            {
              DIOWEBSERVER_XEVENT xevent(this, DIOWEBSERVER_XEVENT_TYPE_DOAUTHENTICATE);

              xevent.SetServer(server);
              xevent.SetConnection(connection);
              xevent.SetRequest(request);

              PostEvent(&xevent);

              if(xevent.IsRequestAuthenticate())
                {
                  page_login    = __L("usr");
                  page_password = __L("pwd");

                } else invalidpassword = true;
            }
           else
            {
              DIOWEBSERVER_XEVENT xevent(this, DIOWEBSERVER_XEVENT_TYPE_CHECKAUTHENTICATE);

              xevent.SetServer(server);
              xevent.SetConnection(connection);
              xevent.SetRequest(request);

              PostEvent(&xevent);

              if(!xevent.IsRequestAuthenticate()) invalidpassword = true;
            }

          if(invalidpassword)
            {
              XSTRING leyend;

              leyend = __L("Invalid user or password!");
              GenerateResponse_Error(connection, DIOWEBHEADER_RESULT_NOTFOUND, leyend);

              APPFLOW_LOG_ENTRY(XLOGLEVEL_ERROR, DIOWEBSERVER_LOGSECTIONID, false, leyend.Get());

              return true;
            }
        }
    }

  //-------------------------------------------------------------------------------------------------------------------------------
  /*
  if(useragentID)
    {
      XSTRING browser;
      XSTRING SO;

      if(useragentID->Get(request->GetUserAgent()->Get(), browser, SO, 5))
        {
          APPFLOW_LOG_ENTRY(XLOGLEVEL_INFO, DIOWEBSERVER_LOGSECTIONID_VERBOSE, false, __L("Web browser    : %s, with: %s."), browser.Get(), SO.Get());
        }
    }
  */  

  //-------------------------------------------------------------------------------------------------------------------------------

  status  = false;
  nparams = querystring.GetParamsFromURL(resourceconv.Get())?true:false;

  querystring.DeleteParamsFromURL(resourceconv);

  if(!resourceconv.Compare(__L("/"),true)) resourceconv.Set(__L("/index.html"));


  //-------------------------------------------------------------------------------------------------------------------------------


  XPATH xpathfile;

  if(cfg->WebServer_PathResources()->IsEmpty())
         GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_WEB, xpathfile);
    else xpathfile = cfg->WebServer_PathResources()->Get();

  xpathfile.Slash_Delete();
  xpathfile += resourceconv.Get();

  //-------------------------------------------------------------------------------------------------------------------------------

  if(resourceconv.GetExtension(extension))
    {
      int nplugins = webserver->GetPluginsManager()->Plugins_GetNPlugins();
      for(int c=0; c<nplugins; c++)
        {
          DIOWEBSERVER_PLUGIN* plugin = webserver->GetPluginsManager()->Plugins_Get(c);
          if(plugin)
            {
              if(plugin->PageExtension_IsContent(extension))
                {
                  DIOWEBHEADER_RESULT    headerresult = DIOWEBHEADER_RESULT_OK;
                  XSTRING                result;

                  status = plugin->PageExtension(xpathfile, request, &querystring, headerresult, result);
                  if(status)
                    {
                      XSTRING head;
                      XSTRING data;

                      plugin->SeparedResult(result, head, data);

                      status = SendRequest(connection, headerresult, data, 5, &head);
                    }
                   else
                    {
                      XSTRING leyend;

                      leyend.Format(__L("Error to execute the %s."), plugin->GetName()->Get());

                      GenerateResponse_Error(connection, DIOWEBHEADER_RESULT_NOTFOUND, leyend);
                      APPFLOW_LOG_ENTRY(XLOGLEVEL_ERROR, DIOWEBSERVER_LOGSECTIONID, false, leyend.Get());
                    }

                  XSTRING IPstring;
                  connection->GetDIOStream()->GetClientIP()->GetXString(IPstring);           

                  if(!status)
                    {
                      APPFLOW_LOG_ENTRY((status?XLOGLEVEL_INFO:XLOGLEVEL_ERROR), DIOWEBSERVER_LOGSECTIONID, false, __L("Request from [%s] to the web server \"%s\" %s."), IPstring.Get(), resourceconv.Get(), status?__L("sent"):__L("not send"));
                    }

                  ispagepluging = true;
                }
            }
        }
    }

  if(!ispagepluging)
    {
      if(!nparams && !isapirestonly)
        {
          status = SendRequest(connection, DIOWEBHEADER_RESULT_OK, xpathfile, 5);
          if(!status)
            {
              // Brower close the conextion in thread
              if(!connection->GetDIOStream()->IsConnected()) status = true;
            }
        }

      if(!status)
        {
          if(!nparams && !isapirestonly)
            {
              DIOWEBSERVER_XEVENT xevent(this, DIOWEBSERVER_XEVENT_TYPE_REQUEST);

              xevent.SetServer(server);
              xevent.SetConnection(connection);
              xevent.SetRequest(request);

              PostEvent(&xevent);

              status = xevent.GetStatus();
            }          
        }

      //-------------------------------------------------------------------------------------------------------------------------------

      if(!status)
        {
          DIOWEBPAGEHTMLCREATOR* webHTMLpage = new DIOWEBPAGEHTMLCREATOR();
          if(webHTMLpage)
            {
              DIOWEBSERVER_XEVENT xevent(this, DIOWEBSERVER_XEVENT_TYPE_REQUEST_ENDPOINT);

              xevent.SetServer(server);
              xevent.SetConnection(connection);
              xevent.SetRequest(request);
              xevent.SetQueryString(&querystring);

              PostEvent(&xevent);

              //DIOWEBHEADER_RESULT result = xevent.GetResult();

              status = xevent.GetStatus();
              if(status)
                {
                  if(!xevent.GetOutputString()->IsEmpty())
                    {
                      webHTMLpage->Set(xevent.GetOutputString()->Get());
                      status = SendRequest(connection, DIOWEBHEADER_RESULT_OK, (*webHTMLpage), 5);
                    }
                   else
                    {
                      status = SendRequest(connection, DIOWEBHEADER_RESULT_OK, xevent.GetOutputBuffer(), 5);
                    } 
                }
               else
                {
                  XSTRING leyend;

                  leyend = __L("Error: command or erroneous parameters.");
                  GenerateMessagePage(leyend, (*webHTMLpage));

                  GenerateResponse_Error(connection,  DIOWEBHEADER_RESULT_NOTFOUND, leyend);

                  APPFLOW_LOG_ENTRY(XLOGLEVEL_ERROR,  DIOWEBSERVER_LOGSECTIONID, false, leyend.Get());
                }

              XSTRING IPstring;
              connection->GetDIOStream()->GetClientIP()->GetXString(IPstring);   

              if(!status)
                {
                  APPFLOW_LOG_ENTRY((status?XLOGLEVEL_INFO:XLOGLEVEL_ERROR), DIOWEBSERVER_LOGSECTIONID, false, __L("Request from [%s] to the web server\"%s\" %s."), IPstring.Get(), resourceconv.Get(), status?__L("sent"):__L("not send"));
                }

              delete webHTMLpage;
            }
        }
       else 
        {
          XSTRING IPstring;
          connection->GetDIOStream()->GetClientIP()->GetXString(IPstring);  

          // APPFLOW_LOG_ENTRY(XLOGLEVEL_INFO, DIOWEBSERVER_LOGSECTIONID, false, __L("Request from [%s] to the web server of file \"%s\" sent."), IPstring.Get(), xpathfile.Get());
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPFLOWWEBSERVER::GenerateMessagePage(XCHAR* leyend, DIOWEBPAGEHTMLCREATOR& webHTMLpage)
* @brief      GenerateMessagePage
* @ingroup    APPFLOW
*
* @param[in]  leyend :
* @param[in]  webHTMLpage :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWWEBSERVER::GenerateMessagePage(XCHAR* leyend, DIOWEBPAGEHTMLCREATOR& webHTMLpage)
{
  webHTMLpage.Printf(__L("<font color=\"red\" face=\"Courier New\" size=\"2\">"));
  webHTMLpage.Printf(__L("<b>%s.</b>\n"), leyend);
  webHTMLpage.Printf(__L("</font>"));

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPFLOWWEBSERVER::GenerateMessagePage(XSTRING& leyend, DIOWEBPAGEHTMLCREATOR& webHTMLpage)
* @brief      GenerateMessagePage
* @ingroup    APPFLOW
*
* @param[in]  leyend :
* @param[in]  webHTMLpage :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWWEBSERVER::GenerateMessagePage(XSTRING& leyend, DIOWEBPAGEHTMLCREATOR& webHTMLpage)
{
  return GenerateMessagePage(leyend.Get(), webHTMLpage);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPFLOWWEBSERVER::GenerateResponse_Error(DIOWEBSERVER_CONNECTION* connection, DIOWEBHEADER_RESULT result, XCHAR* leyend)
* @brief      GenerateResponse_Error
* @ingroup    APPFLOW
*
* @param[in]  connection :
* @param[in]  result :
* @param[in]  leyend :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWWEBSERVER::GenerateResponse_Error(DIOWEBSERVER_CONNECTION* connection,  DIOWEBHEADER_RESULT result, XCHAR* leyend)
{
  DIOWEBPAGEHTMLCREATOR* webHTMLpage = new DIOWEBPAGEHTMLCREATOR();
  if(!webHTMLpage) return false;

  GenerateMessagePage(leyend, (*webHTMLpage));

  connection->GetRequest()->GetResource()->Set("error.html");

  bool status = SendRequest(connection, result, (*webHTMLpage), 5);

  delete webHTMLpage;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPFLOWWEBSERVER::GenerateResponse_Error(DIOWEBSERVER_CONNECTION* connection, DIOWEBHEADER_RESULT result, XSTRING& leyend)
* @brief      GenerateResponse_Error
* @ingroup    APPFLOW
*
* @param[in]  connection :
* @param[in]  result :
* @param[in]  leyend :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWWEBSERVER::GenerateResponse_Error(DIOWEBSERVER_CONNECTION* connection,  DIOWEBHEADER_RESULT result, XSTRING& leyend)
{
  return GenerateResponse_Error(connection, result, leyend.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPFLOWWEBSERVER::End()
* @brief      End
* @ingroup    APPFLOW
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWWEBSERVER::End()
{
  if(!webserver) return false;

  UnSubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_REQUEST                , (XSUBJECT *)webserver);
  DeRegisterEvent(DIOWEBSERVER_XEVENT_TYPE_REQUEST);

  if(isauthenticatedaccess)
    {
      DeRegisterEvent(DIOWEBSERVER_XEVENT_TYPE_DOAUTHENTICATE);
      DeRegisterEvent(DIOWEBSERVER_XEVENT_TYPE_CHECKAUTHENTICATE);
    }

  UnSubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_REQUEST_ENDPOINT       , (XSUBJECT *)webserver);
  DeRegisterEvent(DIOWEBSERVER_XEVENT_TYPE_REQUEST_ENDPOINT);

  UnSubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_CONNECTED    , (XSUBJECT *)webserver);
  DeRegisterEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_CONNECTED);

  UnSubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_READDATA     , (XSUBJECT *)webserver);
  DeRegisterEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_READDATA);

  UnSubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_PONG         , (XSUBJECT *)webserver);
  DeRegisterEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_PONG);

  UnSubscribeEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_DISCONNECTED , (XSUBJECT *)webserver);
  DeRegisterEvent(DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_DISCONNECTED);

  if(webserver)
    {
      delete webserver;
      webserver = NULL;
    }

  if(pluginPHP)
    {
      delete pluginPHP;
      pluginPHP = NULL;
    }

  /*
  if(useragentID)
    {
      delete useragentID;
      useragentID = NULL;
    }
  */

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPFLOWWEBSERVER::HandleEvent_WebServer(DIOWEBSERVER_XEVENT* event)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    APPFLOW
*
* @param[in]  event :
*
* --------------------------------------------------------------------------------------------------------------------*/
void APPFLOWWEBSERVER::HandleEvent_WebServer(DIOWEBSERVER_XEVENT* event)
{
  switch(event->GetEventType())
    {
      case DIOWEBSERVER_XEVENT_TYPE_REQUEST                : ResolveRequest(event->GetServer(), event->GetConnection(), event->GetRequest());
                                                             break;

      case DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_CONNECTED    : if(!PostEvent(event))
                                                              {
                                                                // Accept connection with any version, protocol o resources.
                                                                event->SetStatus(true);
                                                                break;
                                                              }
                                                             break;

      case DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_READDATA     : PostEvent(event);
                                                             break;

      case DIOWEBSERVER_XEVENT_TYPE_WEBSOCKET_DISCONNECTED : PostEvent(event);
                                                             break;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPFLOWWEBSERVER::HandleEvent(XEVENT* xevent)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    APPFLOW
*
* @param[in]  xevent :
*
* --------------------------------------------------------------------------------------------------------------------*/
void APPFLOWWEBSERVER::HandleEvent(XEVENT* xevent)
{
  if(!xevent) return;

  switch(xevent->GetEventFamily())
    {
      case XEVENT_TYPE_WEBSERVER       : { DIOWEBSERVER_XEVENT* event = (DIOWEBSERVER_XEVENT*)xevent;
                                          if(!event) return;

                                          HandleEvent_WebServer(event);
                                        }
                                        break;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPFLOWWEBSERVER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    APPFLOW
*
* --------------------------------------------------------------------------------------------------------------------*/
void APPFLOWWEBSERVER::Clean()
{
  cfg                        = NULL;

  webserver                  = NULL;

  isauthenticatedaccess      = false;
  isapirestonly              = false;

//useragentID                = NULL;

  pluginPHP                  = NULL;
}


#pragma endregion