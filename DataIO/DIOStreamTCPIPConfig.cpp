/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOStreamTCPIPConfig.cpp
*
* @class      DIOSTREAMTCPIPCONFIG
* @brief      Data Input/Output Stream TCP/IP Config class
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @copyright  Copyright(c) 2008 - 2016 GEN Group.
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

#include "XFactory.h"

#include "DIOFactory.h"

#include "DIOStreamTCPIPConfig.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMTCPIPCONFIG ::DIOSTREAMTCPIPCONFIG()
* @brief      ::DIOSTREAMTCPIPCONFIG
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     DIOSTREAMTCPIPCONFIG :
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMTCPIPCONFIG ::DIOSTREAMTCPIPCONFIG(): DIOSTREAMCONFIG(), DIOSTREAMCONFIGSTRING()
{
  Clean();

  type  = DIOSTREAMTYPE_TCPIP;

  xmutexmultiserver = GEN_XFACTORY.Create_Mutex();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMTCPIPCONFIG::~DIOSTREAMTCPIPCONFIG()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMTCPIPCONFIG::~DIOSTREAMTCPIPCONFIG()
{
  if(xmutexmultiserver) GEN_XFACTORY.Delete_Mutex(xmutexmultiserver);

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOIP* DIOSTREAMTCPIPCONFIG ::GetLocalIP()
* @brief      GetLocalIP
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     DIOIP* :
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOIP* DIOSTREAMTCPIPCONFIG ::GetLocalIP()
{
  return &localIP;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOURL* DIOSTREAMTCPIPCONFIG ::GetRemoteURL()
* @brief      GetRemoteURL
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     DIOURL* :
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOURL* DIOSTREAMTCPIPCONFIG ::GetRemoteURL()
{
  return &remoteURL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOSTREAMTCPIPCONFIG ::GetRemotePort()
* @brief      GetRemotePort
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int DIOSTREAMTCPIPCONFIG ::GetRemotePort()
{
  return remoteport;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMTCPIPCONFIG ::SetRemotePort(int port)
* @brief      SetRemotePort
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  port :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMTCPIPCONFIG ::SetRemotePort(int port)
{
  this->remoteport = port;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOSTREAMTCPIPCONFIG::GetCounterMultiServer()
* @brief      GetCounterMultiServer
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int DIOSTREAMTCPIPCONFIG::GetCounterMultiServer()
{
  return countermultiserver;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMTCPIPCONFIG::SetCounterMultiServer(int countermultiserver)
* @brief      DIOSTREAMTCPIPCONFIG::SetCounterMultiServer
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  countermultiserver :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMTCPIPCONFIG::SetCounterMultiServer(int countermultiserver)
{
  this->countermultiserver = countermultiserver;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XMUTEX* DIOSTREAMTCPIPCONFIG::GetXMutexMultiServer()
* @brief      GetXMutexMultiServer
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XMUTEX* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XMUTEX* DIOSTREAMTCPIPCONFIG::GetXMutexMultiServer()
{
  return xmutexmultiserver;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOSTREAMTCPIPCONFIG::GetHandleMultiServer()
* @brief      GetHandleMultiServer
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int DIOSTREAMTCPIPCONFIG::GetHandleMultiServer()
{
  return handlemultiserver;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMTCPIPCONFIG::SetHandleMultiServer(int handlemultiserver)
* @brief      SetHandleMultiServer
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  handlemultiserver :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMTCPIPCONFIG::SetHandleMultiServer(int handlemultiserver)
{
  this->handlemultiserver = handlemultiserver;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMTCPIPCONFIG::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMTCPIPCONFIG::Clean()
{
  type                    = DIOSTREAMTYPE_TCPIP;

  xmutexmultiserver       = NULL;

  countermultiserver      = 0;
  handlemultiserver       = -1;
}


