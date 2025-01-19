/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOStreamTCPIPConfig.cpp
* 
* @class      DIOSTREAMTCPIPCONFIG
* @brief      Data Input/Output Stream TCP/IP Config class
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

#include "DIOStreamTCPIPConfig.h"

#include "XFactory.h"

#include "DIOFactory.h"

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
* @fn         DIOSTREAMTCPIPCONFIG::DIOSTREAMTCPIPCONFIG()
* @brief      Constructor of class
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMTCPIPCONFIG::DIOSTREAMTCPIPCONFIG() : DIOSTREAMCONFIG(), DIOSTREAMCONFIGSTRING()
{
  Clean();

  type  = DIOSTREAMTYPE_TCPIP;

  GEN_XFACTORY_CREATE(xmutexmultiserver, Create_Mutex())
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMTCPIPCONFIG::~DIOSTREAMTCPIPCONFIG()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMTCPIPCONFIG::~DIOSTREAMTCPIPCONFIG()
{
  if(xmutexmultiserver) GEN_XFACTORY.Delete_Mutex(xmutexmultiserver);

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOIP* DIOSTREAMTCPIPCONFIG ::GetLocalIP()
* @brief      Get local IP
* @ingroup    DATAIO
*
* @return     DIOIP* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOIP* DIOSTREAMTCPIPCONFIG ::GetLocalIP()
{
  return &localIP;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOURL* DIOSTREAMTCPIPCONFIG ::GetRemoteURL()
* @brief      Get remote URL
* @ingroup    DATAIO
*
* @return     DIOURL* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOURL* DIOSTREAMTCPIPCONFIG ::GetRemoteURL()
{
  return &remoteURL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOSTREAMTCPIPCONFIG ::GetRemotePort()
* @brief      Get remote port
* @ingroup    DATAIO
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOSTREAMTCPIPCONFIG ::GetRemotePort()
{
  return remoteport;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMTCPIPCONFIG ::SetRemotePort(int port)
* @brief      Set remote port
* @ingroup    DATAIO
*
* @param[in]  port :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMTCPIPCONFIG ::SetRemotePort(int port)
{
  this->remoteport = port;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOSTREAMTCPIPCONFIG::GetCounterMultiServer()
* @brief      Get counter multi server
* @ingroup    DATAIO
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOSTREAMTCPIPCONFIG::GetCounterMultiServer()
{
  return countermultiserver;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMTCPIPCONFIG::SetCounterMultiServer(int countermultiserver)
* @brief      Set counter multi server
* @ingroup    DATAIO
*
* @param[in]  countermultiserver :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMTCPIPCONFIG::SetCounterMultiServer(int countermultiserver)
{
  this->countermultiserver = countermultiserver;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XMUTEX* DIOSTREAMTCPIPCONFIG::GetXMutexMultiServer()
* @brief      Get X mutex multi server
* @ingroup    DATAIO
*
* @return     XMUTEX* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XMUTEX* DIOSTREAMTCPIPCONFIG::GetXMutexMultiServer()
{
  return xmutexmultiserver;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOSTREAMTCPIPCONFIG::GetHandleMultiServer()
* @brief      Get handle multi server
* @ingroup    DATAIO
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOSTREAMTCPIPCONFIG::GetHandleMultiServer()
{
  return handlemultiserver;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMTCPIPCONFIG::SetHandleMultiServer(int handlemultiserver)
* @brief      Set handle multi server
* @ingroup    DATAIO
*
* @param[in]  handlemultiserver :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMTCPIPCONFIG::SetHandleMultiServer(int handlemultiserver)
{
  this->handlemultiserver = handlemultiserver;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMTCPIPCONFIG::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMTCPIPCONFIG::Clean()
{
  type                    = DIOSTREAMTYPE_TCPIP;

  xmutexmultiserver       = NULL;

  countermultiserver      = 0;
  handlemultiserver       = -1;
}


#pragma endregion

