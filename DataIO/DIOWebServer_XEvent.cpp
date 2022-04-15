/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOWebServer_XEvent.cpp
*
* @class      DIOWEBSERVER_XEVENT
* @brief      Data Input/Output Web Server eXtended Event class
* @ingroup    DATAIO
*
* @copyright  GEN Group. All right reserved.
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
*---------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XEvent.h"
#include "XString.h"

#include "DIOWebServer_XEvent.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_XEVENT::DIOWEBSERVER_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family)
* @brief      Constructor
* @ingroup    DATAIO
*
* @param[in]  subject :
* @param[in]  type :
* @param[in]  family :
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_XEVENT::DIOWEBSERVER_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family): XEVENT(subject, type, family)
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_XEVENT::~DIOWEBSERVER_XEVENT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_XEVENT::~DIOWEBSERVER_XEVENT()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER* DIOWEBSERVER_XEVENT::GetServer()
* @brief      GetServer
* @ingroup    DATAIO
*
* @return     DIOWEBSERVER* :
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER* DIOWEBSERVER_XEVENT::GetServer()
{
  return server;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_XEVENT::SetServer(DIOWEBSERVER* server)
* @brief      SetServer
* @ingroup    DATAIO
*
* @param[in]  server :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_XEVENT::SetServer(DIOWEBSERVER* server)
{
  this->server = server;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_CONNECTION* DIOWEBSERVER_XEVENT::GetConnection()
* @brief      GetConnection
* @ingroup    DATAIO
*
* @return     DIOWEBSERVER_CONNECTION* :
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_CONNECTION* DIOWEBSERVER_XEVENT::GetConnection()
{
  return connection;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_XEVENT::SetConnection(DIOWEBSERVER_CONNECTION* connection)
* @brief      SetConnection
* @ingroup    DATAIO
*
* @param[in]  connection :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_XEVENT::SetConnection(DIOWEBSERVER_CONNECTION* connection)
{
  this->connection = connection;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_REQUEST* DIOWEBSERVER_XEVENT::GetRequest()
* @brief      GetRequest
* @ingroup    DATAIO
*
* @return     DIOWEBSERVER_REQUEST* :
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_REQUEST* DIOWEBSERVER_XEVENT::GetRequest()
{
  return request;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_XEVENT::SetRequest(DIOWEBSERVER_REQUEST* request)
* @brief      SetRequest
* @ingroup    DATAIO
*
* @param[in]  request :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_XEVENT::SetRequest(DIOWEBSERVER_REQUEST* request)
{
  this->request = request;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOWEBSERVER_XEVENT::GetTimeOut()
* @brief      GetTimeOut
* @ingroup    DATAIO
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int DIOWEBSERVER_XEVENT::GetTimeOut()
{
  return timeout;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_XEVENT::SetTimeOut(int timeout)
* @brief      SetTimeOut
* @ingroup    DATAIO
*
* @param[in]  timeout :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_XEVENT::SetTimeOut(int timeout)
{
  this->timeout = timeout;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_QUERYSTRINGS* DIOWEBSERVER_XEVENT::GetQueryString()
* @brief      GetQueryString
* @ingroup    DATAIO
*
* @return     DIOWEBSERVER_QUERYSTRINGS* :
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_QUERYSTRINGS*  DIOWEBSERVER_XEVENT::GetQueryString()
{
  return querystring;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_XEVENT::SetQueryString(DIOWEBSERVER_QUERYSTRINGS* querystring)
* @brief      SetQueryString
* @ingroup    DATAIO
*
* @param[in]  querystring :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_XEVENT::SetQueryString(DIOWEBSERVER_QUERYSTRINGS* querystring)
{
  this->querystring = querystring;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBUFFER* DIOWEBSERVER_XEVENT::GetReadDataWebSocket()
* @brief      GetReadDataWebSocket
* @ingroup    DATAIO
*
* @return     XBUFFER* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XBUFFER* DIOWEBSERVER_XEVENT::GetReadDataWebSocket()
{
  return &readdatawebsocket;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOWEBSERVER_XEVENT::GetOutput()
* @brief      GetOutput
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOWEBSERVER_XEVENT::GetOutput()
{
  return &output;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_XEVENT::IsRequestAuthenticate()
* @brief      IsRequestAuthenticate
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_XEVENT::IsRequestAuthenticate()
{
  return isrequestauthenticate;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_XEVENT::SetIsRequestAuthenticate(bool isrequestauthenticate)
* @brief      SetIsRequestAuthenticate
* @ingroup    DATAIO
*
* @param[in]  isrequestauthenticate :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_XEVENT::SetIsRequestAuthenticate(bool isrequestauthenticate)
{
  this->isrequestauthenticate = isrequestauthenticate;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBHEADER_RESULT DIOWEBSERVER_XEVENT::GetResult()
* @brief      GetResult
* @ingroup    DATAIO
*
* @return     DIOWEBHEADER_RESULT :
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOWEBHEADER_RESULT DIOWEBSERVER_XEVENT::GetResult()
{
  return result;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_XEVENT::SetResult(DIOWEBHEADER_RESULT result)
* @brief      SetResult
* @ingroup    DATAIO
*
* @param[in]  result :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_XEVENT::SetResult(DIOWEBHEADER_RESULT result)
{
  this->result = result;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_XEVENT::GetStatus()
* @brief      GetStatus
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_XEVENT::GetStatus()
{
  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_XEVENT::SetStatus(bool status)
* @brief      SetStatus
* @ingroup    DATAIO
*
* @param[in]  status :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_XEVENT::SetStatus(bool status)
{
  this->status = status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_XEVENT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_XEVENT::Clean()
{
  server                 = NULL;
  connection             = NULL;
  request                = NULL;

  timeout                = 0;

  querystring            = NULL;

  isrequestauthenticate  = false;

  status                 = false;
}




