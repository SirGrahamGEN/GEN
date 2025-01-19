/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOWebServer_XEvent.cpp
* 
* @class      DIOWEBSERVER_XEVENT
* @brief      Data Input/Output Web Server eXtended Event class
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

#include "DIOWebServer_XEvent.h"

#include "XEvent.h"
#include "XString.h"

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
* @fn         DIOWEBSERVER_XEVENT::DIOWEBSERVER_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family)
* @brief      Constructor of class
* @ingroup    DATAIO
*
* @param[in]  subject :
* @param[in]  type :
* @param[in]  family :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_XEVENT::DIOWEBSERVER_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family): XEVENT(subject, type, family)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_XEVENT::~DIOWEBSERVER_XEVENT()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_XEVENT::~DIOWEBSERVER_XEVENT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER* DIOWEBSERVER_XEVENT::GetServer()
* @brief      Get server
* @ingroup    DATAIO
*
* @return     DIOWEBSERVER* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER* DIOWEBSERVER_XEVENT::GetServer()
{
  return server;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_XEVENT::SetServer(DIOWEBSERVER* server)
* @brief      Set server
* @ingroup    DATAIO
*
* @param[in]  server :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_XEVENT::SetServer(DIOWEBSERVER* server)
{
  this->server = server;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_CONNECTION* DIOWEBSERVER_XEVENT::GetConnection()
* @brief      Get connection
* @ingroup    DATAIO
*
* @return     DIOWEBSERVER_CONNECTION* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_CONNECTION* DIOWEBSERVER_XEVENT::GetConnection()
{
  return connection;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_XEVENT::SetConnection(DIOWEBSERVER_CONNECTION* connection)
* @brief      Set connection
* @ingroup    DATAIO
*
* @param[in]  connection :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_XEVENT::SetConnection(DIOWEBSERVER_CONNECTION* connection)
{
  this->connection = connection;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_REQUEST* DIOWEBSERVER_XEVENT::GetRequest()
* @brief      Get request
* @ingroup    DATAIO
*
* @return     DIOWEBSERVER_REQUEST* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_REQUEST* DIOWEBSERVER_XEVENT::GetRequest()
{
  return request;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_XEVENT::SetRequest(DIOWEBSERVER_REQUEST* request)
* @brief      Set request
* @ingroup    DATAIO
*
* @param[in]  request :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_XEVENT::SetRequest(DIOWEBSERVER_REQUEST* request)
{
  this->request = request;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOWEBSERVER_XEVENT::GetTimeOut()
* @brief      Get time out
* @ingroup    DATAIO
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOWEBSERVER_XEVENT::GetTimeOut()
{
  return timeout;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_XEVENT::SetTimeOut(int timeout)
* @brief      Set time out
* @ingroup    DATAIO
*
* @param[in]  timeout :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_XEVENT::SetTimeOut(int timeout)
{
  this->timeout = timeout;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_QUERYSTRINGS* DIOWEBSERVER_XEVENT::GetQueryString()
* @brief      Get query string
* @ingroup    DATAIO
*
* @return     DIOWEBSERVER_QUERYSTRINGS* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_QUERYSTRINGS*  DIOWEBSERVER_XEVENT::GetQueryString()
{
  return querystring;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_XEVENT::SetQueryString(DIOWEBSERVER_QUERYSTRINGS* querystring)
* @brief      Set query string
* @ingroup    DATAIO
*
* @param[in]  querystring :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_XEVENT::SetQueryString(DIOWEBSERVER_QUERYSTRINGS* querystring)
{
  this->querystring = querystring;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBUFFER* DIOWEBSERVER_XEVENT::GetReadDataWebSocket()
* @brief      Get read data web socket
* @ingroup    DATAIO
*
* @return     XBUFFER* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XBUFFER* DIOWEBSERVER_XEVENT::GetReadDataWebSocket()
{
  return &readdatawebsocket;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOWEBSERVER_XEVENT::GetOutputString()
* @brief      Get output string
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOWEBSERVER_XEVENT::GetOutputString()
{
  return &outputstring;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBUFFER* DIOWEBSERVER_XEVENT::GetOutputBuffer()
* @brief      Get output buffer
* @ingroup    DATAIO
* 
* @return     XBUFFER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBUFFER* DIOWEBSERVER_XEVENT::GetOutputBuffer()
{
  return &outputbuffer;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_XEVENT::IsRequestAuthenticate()
* @brief      Is request authenticate
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_XEVENT::IsRequestAuthenticate()
{
  return isrequestauthenticate;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_XEVENT::SetIsRequestAuthenticate(bool isrequestauthenticate)
* @brief      Set is request authenticate
* @ingroup    DATAIO
*
* @param[in]  isrequestauthenticate :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_XEVENT::SetIsRequestAuthenticate(bool isrequestauthenticate)
{
  this->isrequestauthenticate = isrequestauthenticate;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBHEADER_RESULT DIOWEBSERVER_XEVENT::GetResult()
* @brief      Get result
* @ingroup    DATAIO
*
* @return     DIOWEBHEADER_RESULT :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBHEADER_RESULT DIOWEBSERVER_XEVENT::GetResult()
{
  return result;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_XEVENT::SetResult(DIOWEBHEADER_RESULT result)
* @brief      Set result
* @ingroup    DATAIO
*
* @param[in]  result :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_XEVENT::SetResult(DIOWEBHEADER_RESULT result)
{
  this->result = result;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_XEVENT::GetStatus()
* @brief      Get status
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_XEVENT::GetStatus()
{
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_XEVENT::SetStatus(bool status)
* @brief      Set status
* @ingroup    DATAIO
*
* @param[in]  status :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_XEVENT::SetStatus(bool status)
{
  this->status = status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_XEVENT::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
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


#pragma endregion




