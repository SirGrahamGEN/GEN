/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOWINDOWSFactory.cpp
*
* @class      DIOWINDOWSFACTORY
* @brief      WINDOWS Data Input/Output Factory class
* @ingroup    PLATFORM_WINDOWS
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


#ifdef DIO_ACTIVE

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#ifndef BUILDER
#if(_MSC_VER >= 1700) && defined(_USING_V110_SDK71_)

#else

  #include <string>
  #include <vector>
  #include <new>

  #include <atlpath.h>
  #include <Shlobj.h>
  #include <propkey.h>
  #include <wrl.h>

#endif
#endif

#include <winsock2.h>
#include <windows.h>

#include "XFactoryMacros.h"


#ifdef DIO_STREAMUART_ACTIVE
#include "DIOStreamUARTConfig.h"
#include "DIOWINDOWSStreamUARTLocalEnumDevices.h"
#include "DIOWINDOWSStreamUART.h"
#endif

#ifdef DIO_STREAMUSB_ACTIVE
#include "DIOStreamUSBConfig.h"
#include "DIOWINDOWSStreamUSBLocalEnumDevices.h"
#include "DIOWINDOWSStreamUSB.h"
#endif

#if defined(DIO_STREAMUDP_ACTIVE) || defined(DIO_STREAMTCPIP_ACTIVE)
#include "DIOWINDOWSStreamIPLocalEnumDevices.h"
#endif

#ifdef DIO_STREAMICMP_ACTIVE
#include "DIOStreamICMPConfig.h"
#include "DIOWINDOWSStreamICMP.h"
#endif

#ifdef DIO_STREAMUDP_ACTIVE
#include "DIOStreamUDPConfig.h"
#include "DIOWINDOWSStreamUDP.h"
#endif

#ifdef DIO_STREAMTCPIP_ACTIVE
#include "DIOStreamTCPIPConfig.h"
#include "DIOWINDOWSStreamTCPIP.h"
#endif

#if (defined(DIO_STREAMBLUETOOTH_ACTIVE) || defined(DIO_STREAMBLUETOOTHLE_ACTIVE))
#include "DIOStreamBluetoothConfig.h"
#include "DIOWINDOWSStreamBluetoothLocalEnumDevices.h"
#include "DIOWINDOWSStreamBluetooth.h"
#endif

#ifdef DIO_STREAMBLUETOOTH_ACTIVE
#include "DIOWINDOWSStreamBluetoothRemoteEnumDevices.h"
#endif

#ifdef DIO_STREAMBLUETOOTHLE_ACTIVE
#include "DIOWINDOWSStreamBluetoothLERemoteEnumDevices.h"
#endif

#ifdef DIO_STREAMTWIFI_ACTIVE
#include "DIOWINDOWSStreamWifiRemoteEnumDevices.h"
#endif

#ifdef DIO_STREAMTWIFIMANAGERMODE_ACTIVE
#include "DIOWINDOWSWifiManagerMode.h"
#endif

#ifdef DIO_STREAMSPI_ACTIVE
#include "DIOStreamSPIConfig.h"
#include "DIOWINDOWSStreamSPI.h"
#endif

#ifdef DIO_STREAMI2C_ACTIVE
#include "DIOStreamI2CConfig.h"
#include "DIOWINDOWSStreamI2C.h"
#endif

#ifdef DIO_PING_ACTIVE
#include "DIOWINDOWSPing.h"
#endif

#ifdef DIO_PCAP_ACTIVE
#include "DIOWINDOWSPCap.h"
#endif

#ifndef BUILDER
#include "DIOWINDOWSNotificationsManager.h"
#endif

#include "DIOWINDOWSFactory.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef ANYTYPEOFDIOSTREAMIO


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMENUMDEVICES* DIOWINDOWSFACTORY::CreateStreamEnumDevices(DIOSTREAMENUMTYPE type)
* @brief      CreateStreamEnumDevices
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  type : enum type to created
*
* @return     DIOSTREAMENUMDEVICES* : enum created
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMENUMDEVICES* DIOWINDOWSFACTORY::CreateStreamEnumDevices(DIOSTREAMENUMTYPE type)
{
  DIOSTREAMENUMDEVICES* _class = NULL;

  switch(type)
    {
      case DIOSTREAMENUMTYPE_UNKNOWN            : return NULL;

      #ifdef DIO_STREAMUART_ACTIVE
      case DIOSTREAMENUMTYPE_UART_LOCAL         : _class = new DIOWINDOWSSTREAMUARTLOCALENUMDEVICES();                break;
      #endif

      #ifdef DIO_STREAMUSB_ACTIVE
      case DIOSTREAMENUMTYPE_USB_LOCAL          : _class = new DIOWINDOWSSTREAMUSBLOCALENUMDEVICES();                 break;
      #endif

      #if defined(DIO_STREAMUDP_ACTIVE) || defined(DIO_STREAMTCPIP_ACTIVE)
      case DIOSTREAMENUMTYPE_IP_LOCAL           : _class = new DIOWINDOWSSTREAMIPLOCALENUMDEVICES();                  break;
      #endif

      #if defined(DIO_STREAMBLUETOOTH_ACTIVE) || defined(DIO_STREAMBLUETOOTHLE_ACTIVE)
      case DIOSTREAMENUMTYPE_BLUETOOTH_LOCAL    : _class = new DIOWINDOWSSTREAMBLUETOOTHLOCALENUMDEVICES();           break;
      #endif

      #ifdef DIO_STREAMBLUETOOTH_ACTIVE
      case DIOSTREAMENUMTYPE_BLUETOOTH_REMOTE   : _class = new DIOWINDOWSSTREAMBLUETOOTHREMOTEENUMDEVICES();          break;
      #endif

      #ifdef DIO_STREAMBLUETOOTHLE_ACTIVE
      case DIOSTREAMENUMTYPE_BLUETOOTHLE_REMOTE : _class = new DIOWINDOWSSTREAMBLUETOOTHLEREMOTEENUMDEVICES();        break;
      #endif

      #ifdef DIO_STREAMTWIFI_ACTIVE
      case DIOSTREAMENUMTYPE_WIFI_REMOTE        : _class = new DIOWINDOWSSTREAMWIFIREMOTEENUMDEVICES();               break;
      #endif

                                      default   : return NULL;
    }

  if(_class)_class->SetType(type);

  return _class;
};




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWINDOWSFACTORY::DeleteStreamEnumDevices(DIOSTREAMENUMDEVICES* enumdevices)
* @brief      Delete Stream Enum Devices
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  enumdevices : enum to delete
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWINDOWSFACTORY::DeleteStreamEnumDevices(DIOSTREAMENUMDEVICES* enumdevices)
{
  if(!enumdevices)  return false;

  delete enumdevices;

  return true;
};



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAM* DIOWINDOWSFACTORY::CreateStreamIO(DIOSTREAMCONFIG* config)
* @brief      Create Stream IO
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  config : config to create the stream IO
*
* @return     DIOSTREAM* : stream IO create
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAM* DIOWINDOWSFACTORY::CreateStreamIO(DIOSTREAMCONFIG* config)
{
  if(!config) return NULL;

  DIOSTREAM* _class = NULL;

  switch(config->GetType())
    {
      case DIOSTREAMTYPE_UNKNOWN    : return NULL;

      #ifdef DIO_STREAMUART_ACTIVE
      case DIOSTREAMTYPE_UART       : _class = new DIOWINDOWSSTREAMUART();        break;
      #endif

      #ifdef DIO_STREAMUSB_ACTIVE
      case DIOSTREAMTYPE_USB        : _class = new DIOWINDOWSSTREAMUSB();         break;
      #endif

      #ifdef DIO_STREAMICMP_ACTIVE
      case DIOSTREAMTYPE_ICMP       : _class = new DIOWINDOWSSTREAMICMP();        break;
      #endif

      #ifdef DIO_STREAMUDP_ACTIVE
      case DIOSTREAMTYPE_UDP        : _class = new DIOWINDOWSSTREAMUDP();         break;
      #endif

      #ifdef DIO_STREAMTCPIP_ACTIVE
      case DIOSTREAMTYPE_TCPIP      : _class = new DIOWINDOWSSTREAMTCPIP();       break;
      #endif

      #if defined(DIO_STREAMBLUETOOTH_ACTIVE) || defined(DIO_STREAMBLUETOOTHLE_ACTIVE)
      case DIOSTREAMTYPE_BLUETOOTH  : _class = new DIOWINDOWSSTREAMBLUETOOTH();   break;
      #endif

      #ifdef DIO_STREAMSPI_ACTIVE
      case DIOSTREAMTYPE_SPI        : _class = new DIOWINDOWSSTREAMSPI();         break;
      #endif

      #ifdef DIO_STREAMI2C_ACTIVE
      case DIOSTREAMTYPE_I2C        : _class = new DIOWINDOWSSTREAMI2C();         break;
      #endif

                        default     : return NULL;
    }

  if(_class)
    {
      _class->SetType(config->GetType());
      _class->SetConfig(config);
    }

  return _class;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWINDOWSFACTORY::DeleteStreamIO(DIOSTREAM* diostream)
* @brief      Delete Stream IO
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  diostream : stream IO to delete
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWINDOWSFACTORY::DeleteStreamIO(DIOSTREAM* diostream)
{
  if(!diostream)  return false;

  delete diostream;

  return true;
}

#endif



#ifdef DIO_STREAMTWIFIMANAGERMODE_ACTIVE

CREATEFUNC(DIOWINDOWSFACTORY, DIOWIFIMANAGERMODE  , DIOWINDOWSWIFIMANAGERMODE    , CreateWifiManagerMode)
DELETEFUNC(DIOWINDOWSFACTORY, DIOWIFIMANAGERMODE  , DIOWINDOWSWIFIMANAGERMODE    , DeleteWifiManagerMode)

#endif



#ifdef DIO_PING_ACTIVE

CREATEFUNC(DIOWINDOWSFACTORY, DIOPING   , DIOWINDOWSPING    , CreatePing)
DELETEFUNC(DIOWINDOWSFACTORY, DIOPING   , DIOWINDOWSPING    , DeletePing)

#endif



#ifdef DIO_PCAP_ACTIVE

CREATEFUNC(DIOWINDOWSFACTORY, DIOPCAP   , DIOWINDOWSPCAP    , CreatePCap)
DELETEFUNC(DIOWINDOWSFACTORY, DIOPCAP   , DIOWINDOWSPCAP    , DeletePCap)

#endif



#ifndef BUILDER

CREATEFUNC(DIOWINDOWSFACTORY, DIONOTIFICATIONSMANAGER   , DIOWINDOWSNOTIFICATIONSMANAGER    , CreateNotificationsManager)
DELETEFUNC(DIOWINDOWSFACTORY, DIONOTIFICATIONSMANAGER   , DIOWINDOWSNOTIFICATIONSMANAGER    , DeleteNotificationsManager)

#endif


#endif
