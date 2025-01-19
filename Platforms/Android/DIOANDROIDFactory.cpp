/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOANDROIDFactory.cpp
* 
* @class      DIOANDROIDFACTORY
* @brief      ANDROID Data Input/Output Factory class
* @ingroup    PLATFORM_ANDROID
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


#ifdef DIO_ACTIVE


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIOANDROIDFactory.h"

#ifdef DIO_STREAMUART_ACTIVE
#include "DIOStreamUARTConfig.h"
#include "DIOANDROIDStreamUARTLocalEnumDevices.h"
#include "DIOANDROIDStreamUART.h"
#endif

#ifdef DIO_STREAMUSB_ACTIVE
#include "DIOStreamUSBConfig.h"
#include "DIOANDROIDStreamUSBLocalEnumDevices.h"
#include "DIOANDROIDStreamUSB.h"
#endif

#if defined(DIO_STREAMICMP_ACTIVE) || defined(DIO_STREAMUDP_ACTIVE) || defined(DIO_STREAMTCPIP_ACTIVE)
#include "DIOANDROIDStreamIPLocalEnumDevices.h"
#endif

#ifdef DIO_STREAMICMP_ACTIVE
#include "DIOStreamICMPConfig.h"
#include "DIOANDROIDStreamICMP.h"
#endif

#ifdef DIO_STREAMUDP_ACTIVE
#include "DIOStreamUDPConfig.h"
#include "DIOANDROIDStreamUDP.h"
#endif

#ifdef DIO_STREAMTCPIP_ACTIVE
#include "DIOStreamTCPIPConfig.h"
#include "DIOANDROIDStreamTCPIP.h"
#endif

#ifdef DIO_STREAMBLUETOOTH_ACTIVE
#include "DIOStreamBluetoothConfig.h"
#include "DIOANDROIDStreamBluetoothLocalEnumDevices.h"
#include "DIOANDROIDStreamBluetoothRemoteEnumDevices.h"
#include "DIOANDROIDStreamBluetooth.h"
#endif

#ifdef DIO_STREAMTWIFI_ACTIVE
#include "DIOANDROIDStreamWifiRemoteEnumDevices.h"
#endif

#ifdef DIO_STREAMSPI_ACTIVE
#include "DIOStreamSPIConfig.h"
#include "DIOANDROIDStreamSPI.h"
#endif

#ifdef DIO_STREAMI2C_ACTIVE
#include "DIOStreamI2CConfig.h"
#include "DIOANDROIDStreamI2C.h"
#endif

#ifdef DIO_PING_ACTIVE
#include "DIOANDROIDPing.h"
#endif

#ifdef DIO_PCAP_ACTIVE
#include "DIOANDROIDPCap.h"
#endif

#ifdef DIO_GPIO_ACTIVE
#include "DIOANDROIDGPIO.h"
#endif

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


#ifdef ANYTYPEOFDIOSTREAMIO
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOSTREAMENUMDEVICES* DIOANDROIDFACTORY::CreateStreamEnumDevices(DIOSTREAMENUMTYPE type)
* @brief      Create stream enum devices
* @ingroup    PLATFORM_ANDROID
* 
* @param[in]  type : 
* 
* @return     DIOSTREAMENUMDEVICES* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMENUMDEVICES* DIOANDROIDFACTORY::CreateStreamEnumDevices(DIOSTREAMENUMTYPE type)
{
  DIOSTREAMENUMDEVICES* _class = NULL;

  switch(type)
    {
      #ifdef DIO_STREAMUART_ACTIVE
      case DIOSTREAMENUMTYPE_UART_LOCAL         : _class = new DIOANDROIDSTREAMUARTLOCALENUMDEVICES();                break;
      #endif

      #ifdef DIO_STREAMUSB_ACTIVE
      case DIOSTREAMENUMTYPE_USB_LOCAL          : _class = new DIOANDROIDSTREAMUSBLOCALENUMDEVICES();                 break;
      #endif

      #if defined(DIO_STREAMUDP_ACTIVE) || defined(DIO_STREAMTCPIP_ACTIVE)
      case DIOSTREAMENUMTYPE_IP_LOCAL           : _class = new DIOANDROIDSTREAMIPLOCALENUMDEVICES();                  break;
      #endif

      #ifdef DIO_STREAMBLUETOOTH_ACTIVE
      case DIOSTREAMENUMTYPE_BLUETOOTH_LOCAL    : _class = new DIOANDROIDSTREAMBLUETOOTHLOCALENUMDEVICES();           break;
      case DIOSTREAMENUMTYPE_BLUETOOTH_REMOTE   : _class = new DIOANDROIDSTREAMBLUETOOTHREMOTEENUMDEVICES();          break;
      #endif

      #ifdef DIO_STREAMTWIFI_ACTIVE
      case DIOSTREAMENUMTYPE_WIFI_REMOTE        : _class = new DIOANDROIDSTREAMWIFIREMOTEENUMDEVICES();               break;
      #endif
    }

  if(_class)_class->SetType(type);

  return _class;
};


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOANDROIDFACTORY::DeleteStreamEnumDevices(DIOSTREAMENUMDEVICES* enumdevices)
* @brief      Delete stream enum devices
* @ingroup    PLATFORM_ANDROID
* 
* @param[in]  enumdevices : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOANDROIDFACTORY::DeleteStreamEnumDevices(DIOSTREAMENUMDEVICES* enumdevices)
{
  if(!enumdevices)  return false;

  delete enumdevices;

  return true;
};


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOSTREAM* DIOANDROIDFACTORY::CreateStreamIO(DIOSTREAMCONFIG* config)
* @brief      Create stream IO
* @ingroup    PLATFORM_ANDROID
* 
* @param[in]  config : 
* 
* @return     DIOSTREAM* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAM* DIOANDROIDFACTORY::CreateStreamIO(DIOSTREAMCONFIG* config)
{
  if(!config) return NULL;

  DIOSTREAM*_class = NULL;

  switch(config->GetType())
    {
      case DIOSTREAMTYPE_UNKNOWN    : return NULL;

      #ifdef DIO_STREAMUART_ACTIVE
      case DIOSTREAMTYPE_UART       : _class = new DIOANDROIDSTREAMUART();        break;
      #endif

      #ifdef DIO_STREAMUSB_ACTIVE
      case DIOSTREAMTYPE_USB        : _class = new DIOANDROIDSTREAMUSB();         break;
      #endif

      #ifdef DIO_STREAMICMP_ACTIVE
      case DIOSTREAMTYPE_ICMP       : _class = new DIOANDROIDSTREAMICMP();        break;
      #endif

      #ifdef DIO_STREAMUDP_ACTIVE
      case DIOSTREAMTYPE_UDP        : _class = new DIOANDROIDSTREAMUDP();         break;
      #endif

      #ifdef DIO_STREAMTCPIP_ACTIVE
      case DIOSTREAMTYPE_TCPIP      : _class = new DIOANDROIDSTREAMTCPIP();       break;
      #endif

      #ifdef DIO_STREAMBLUETOOTH_ACTIVE
      case DIOSTREAMTYPE_BLUETOOTH  : _class = new DIOANDROIDSTREAMBLUETOOTH();   break;
      #endif

      #ifdef DIO_STREAMSPI_ACTIVE
      case DIOSTREAMTYPE_SPI        : _class = new DIOANDROIDSTREAMSPI();         break;
      #endif

      #ifdef DIO_STREAMI2C_ACTIVE
      case DIOSTREAMTYPE_I2C        : _class = new DIOANDROIDSTREAMI2C();         break;
      #endif
    }

  if(_class)
    {
      _class->SetType(config->GetType());
      _class->SetConfig(config);
    }

  return  _class;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOANDROIDFACTORY::DeleteStreamIO(DIOSTREAM* diostream)
* @brief      Delete stream IO
* @ingroup    PLATFORM_ANDROID
* 
* @param[in]  diostream : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOANDROIDFACTORY::DeleteStreamIO(DIOSTREAM* diostream)
{
  if(!diostream) return false;
  delete diostream;
  return true;
}
#endif


#ifdef DIO_PING_ACTIVE
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPING* DIOANDROIDFACTORY::CreatePing()
* @brief      Create ping
* @ingroup    PLATFORM_ANDROID
* 
* @return     DIOPING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOPING* DIOANDROIDFACTORY::CreatePing()
{
  DIOANDROIDPING* _class = new DIOANDROIDPING();

  return (DIOPING*)_class;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOANDROIDFACTORY::DeletePing(DIOPING* ping)
* @brief      Delete ping
* @ingroup    PLATFORM_ANDROID
* 
* @param[in]  ping : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOANDROIDFACTORY::DeletePing(DIOPING* ping)
{
  if(!ping) return false;

  DIOANDROIDPING* _ping = (DIOANDROIDPING*)ping;
  delete _ping;

  return true;

}
#endif


#ifdef DIO_PCAP_ACTIVE
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPCAP* DIOANDROIDFACTORY::CreatePCap()
* @brief      Create P cap
* @ingroup    PLATFORM_ANDROID
* 
* @return     DIOPCAP* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOPCAP* DIOANDROIDFACTORY::CreatePCap()
{
  DIOANDROIDPCAP* _class = new DIOANDROIDPCAP();

  return (DIOPCAP*)_class;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOANDROIDFACTORY::DeletePCap(DIOPCAP* pcap)
* @brief      Delete P cap
* @ingroup    PLATFORM_ANDROID
* 
* @param[in]  pcap : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOANDROIDFACTORY::DeletePCap(DIOPCAP* pcap)
{
  if(!pcap) return false;

  DIOANDROIDPCAP* _pcap = (DIOANDROIDPCAP*)pcap;
  delete _pcap;

  return true;
}
#endif




#ifdef DIO_GPIO_ACTIVE
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOGPIO* DIOANDROIDFACTORY::CreateGPIO()
* @brief      Create GPIO
* @ingroup    PLATFORM_ANDROID
* 
* @return     DIOGPIO* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOGPIO* DIOANDROIDFACTORY::CreateGPIO()
{
  DIOANDROIDGPIO* _class = new DIOANDROIDGPIO();

  return (DIOGPIO*)_class;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOANDROIDFACTORY::DeleteGPIO(DIOGPIO* port)
* @brief      Delete GPIO
* @ingroup    PLATFORM_ANDROID
* 
* @param[in]  port : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOANDROIDFACTORY::DeleteGPIO(DIOGPIO* port)
{
  if(!port) return false;

  DIOANDROIDGPIO* _port = (DIOANDROIDGPIO*)port;
  delete _port;

  return true;
}
#endif


#endif


#pragma endregion









