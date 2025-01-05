/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOLINUXFactory.cpp
* 
* @class      DIOLINUXFACTORY
* @brief      LINUX Data Input/Output Factory class
* @ingroup    PLATFORM_LINUX
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

#include "DIOLINUXFactory.h"

#include "XFactoryMacros.h"
#include "XTrace.h"

#ifdef DIO_STREAMUART_ACTIVE
#include "DIOStreamUARTConfig.h"
#include "DIOLINUXStreamUARTLocalEnumDevices.h"
#include "DIOLINUXStreamUART.h"
#endif

#ifdef DIO_STREAMUSB_ACTIVE
#include "DIOStreamUSBConfig.h"
#include "DIOLINUXStreamUSBLocalEnumDevices.h"
#include "DIOLINUXStreamUSB.h"
#endif

#if defined(DIO_STREAMICMP_ACTIVE) || defined(DIO_STREAMUDP_ACTIVE) || defined(DIO_STREAMTCPIP_ACTIVE)
#include "DIOLINUXStreamIPLocalEnumDevices.h"
#endif

#ifdef DIO_STREAMICMP_ACTIVE
#include "DIOStreamICMPConfig.h"
#include "DIOLINUXStreamICMP.h"
#endif

#ifdef DIO_STREAMUDP_ACTIVE
#include "DIOStreamUDPConfig.h"
#include "DIOLINUXStreamUDP.h"
#endif

#ifdef DIO_STREAMTCPIP_ACTIVE
#include "DIOStreamTCPIPConfig.h"
#include "DIOLINUXStreamTCPIP.h"
#include "DIOLINUXStreamTCPIPServer.h"
#endif

#if defined(DIO_STREAMBLUETOOTH_ACTIVE) || defined(DIO_STREAMBLUETOOTHLE_ACTIVE)
#include "DIOStreamBluetoothConfig.h"
#include "DIOLINUXStreamBluetooth.h"
#include "DIOLINUXStreamBluetoothLocalEnumDevices.h"
#endif

#ifdef DIO_STREAMBLUETOOTH_ACTIVE
#include "DIOLINUXStreamBluetoothRemoteEnumDevices.h"
#endif

#ifdef DIO_STREAMBLUETOOTHLE_ACTIVE
#include "DIOLINUXStreamBluetoothLERemoteEnumDevices.h"
#endif

#ifdef DIO_STREAMTWIFI_ACTIVE
#include "DIOLINUXStreamWifiRemoteEnumDevices.h"
#endif


#ifdef DIO_WIFIMANAGERMODE_ACTIVE
#include "DIOLINUXWifiManagerMode.h"
#endif

#ifdef DIO_STREAMSPI_ACTIVE
#include "DIOStreamSPIConfig.h"
#include "DIOLINUXStreamSPI.h"
#endif

#ifdef DIO_STREAMI2C_ACTIVE
#include "DIOStreamI2CConfig.h"
#include "DIOLINUXStreamI2C.h"
#endif

#ifdef DIO_PING_ACTIVE
#include "DIOLINUXPing.h"
#endif

#ifdef DIO_PCAP_ACTIVE
#include "DIOLINUXPCap.h"
#endif


#ifdef DIO_LEDNEOPIXELWS2812B_ACTIVE 

#include "DIOLedNeoPixelWS2812B.h"

  #ifdef HW_PC    
  #endif  
  
  #ifdef HW_RASPBERRYPI
  #include "DIOLINUXLedNeoPixelWS2812BRPi.h"
  #endif
  
  #if defined(HW_ARM) || defined(HW_ARM64)  
  #endif

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
* @fn         DIOSTREAMENUMDEVICES* DIOLINUXFACTORY::CreateStreamEnumDevices(DIOSTREAMENUMTYPE type)
* @brief      Create Stream Enum Devices
* @ingroup    PLATFORM_LINUX
*
* @param[in]  type : type of enum to create
*
* @return     DIOSTREAMENUMDEVICES* : enum created
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMENUMDEVICES* DIOLINUXFACTORY::CreateStreamEnumDevices(DIOSTREAMENUMTYPE type)
{
  DIOSTREAMENUMDEVICES* _class = NULL;

  switch(type)
    {
      #ifdef DIO_STREAMUART_ACTIVE
      case DIOSTREAMENUMTYPE_UART_LOCAL           : _class = new DIOLINUXSTREAMUARTLOCALENUMDEVICES();                      break;
      #endif

      #ifdef DIO_STREAMUSB_ACTIVE
      case DIOSTREAMENUMTYPE_USB_LOCAL            : _class = new DIOLINUXSTREAMUSBLOCALENUMDEVICES();                       break;
      #endif

      #if defined(DIO_STREAMUDP_ACTIVE) || defined(DIO_STREAMTCPIP_ACTIVE)
      case DIOSTREAMENUMTYPE_IP_LOCAL             :  _class = new DIOLINUXSTREAMIPLOCALENUMDEVICES();                       break;
      #endif

      #if defined(DIO_STREAMBLUETOOTH_ACTIVE) || defined(DIO_STREAMBLUETOOTHLE_ACTIVE)
      case DIOSTREAMENUMTYPE_BLUETOOTH_LOCAL      :  _class = new DIOLINUXSTREAMBLUETOOTHLOCALENUMDEVICES();                break;
      #endif

      #if DIO_STREAMBLUETOOTH_ACTIVE
      case DIOSTREAMENUMTYPE_BLUETOOTH_REMOTE     :  _class = new DIOLINUXSTREAMBLUETOOTHREMOTEENUMDEVICES();               break;
      #endif

      #if DIO_STREAMBLUETOOTHLE_ACTIVE
      case DIOSTREAMENUMTYPE_BLUETOOTHLE_REMOTE   :  _class = new DIOLINUXSTREAMBLUETOOTHLEREMOTEENUMDEVICES();             break;
      #endif

      #ifdef DIO_STREAMTWIFI_ACTIVE
      case DIOSTREAMENUMTYPE_WIFI_REMOTE          :  _class = new DIOLINUXSTREAMWIFIREMOTEENUMDEVICES();                    break;
      #endif
                                        default   : break;
    }

  if(_class) _class->SetType(type);

  return _class;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOLINUXFACTORY::DeleteStreamEnumDevices(DIOSTREAMENUMDEVICES* enumdevices)
* @brief      Delete Stream Enum Devices
* @ingroup    PLATFORM_LINUX
*
* @param[in]  enumdevices : enumdevices to delete
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXFACTORY::DeleteStreamEnumDevices(DIOSTREAMENUMDEVICES* enumdevices)
{
  if(!enumdevices)  return false;

  delete enumdevices;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOSTREAM* DIOLINUXFACTORY::CreateStreamIO(DIOSTREAMCONFIG* config)
* @brief      CreateStreamIO
* @ingroup    PLATFORM_LINUX
* 
* @param[in]  config : 
* 
* @return     DIOSTREAM* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAM* DIOLINUXFACTORY::CreateStreamIO(DIOSTREAMCONFIG* config)
{
  if(!config) 
    {
      return NULL;
    }

  DIOSTREAM* _class=NULL;

  switch(config->GetType())
    {
      case DIOSTREAMTYPE_UNKNOWN    : return NULL;

      #ifdef DIO_STREAMUART_ACTIVE
      case DIOSTREAMTYPE_UART       : _class = new DIOLINUXSTREAMUART();        
                                      break;
      #endif

      #ifdef DIO_STREAMUSB_ACTIVE
      case DIOSTREAMTYPE_USB        : _class = new DIOLINUXSTREAMUSB();         
                                      break;
      #endif

      #ifdef DIO_STREAMICMP_ACTIVE
      case DIOSTREAMTYPE_ICMP       : _class = new DIOLINUXSTREAMICMP();        
                                      break;
      #endif

      #ifdef DIO_STREAMUDP_ACTIVE
      case DIOSTREAMTYPE_UDP        : _class = new DIOLINUXSTREAMUDP();         
                                      break;
      #endif

      #ifdef DIO_STREAMTCPIP_ACTIVE
      case DIOSTREAMTYPE_TCPIP      : if(config->GetMode() == DIOSTREAMMODE_SERVERMULTISOCKET)
                                        {
                                          _class = new DIOLINUXSTREAMTCPIPSERVER();
                                        }                                      
                                       else
                                        {
                                          _class = new DIOLINUXSTREAMTCPIP();
                                        } 
                                      break;
      #endif

      #if (defined(DIO_STREAMBLUETOOTH_ACTIVE) || defined(DIO_STREAMBLUETOOTHLE_ACTIVE))
      case DIOSTREAMTYPE_BLUETOOTH  : _class = new DIOLINUXSTREAMBLUETOOTH();   break;
      #endif

      #ifdef DIO_STREAMSPI_ACTIVE
      case DIOSTREAMTYPE_SPI        : _class = new DIOLINUXSTREAMSPI();         break;
      #endif

      #ifdef DIO_STREAMI2C_ACTIVE
      case DIOSTREAMTYPE_I2C        : _class = new DIOLINUXSTREAMI2C();         break;
      #endif
                          default   : break;
    }

  if(_class)
    {
      _class->SetType   (config->GetType());
      _class->SetConfig (config);
    }

  return  _class;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOLINUXFACTORY::DeleteStreamIO(DIOSTREAM* diostream)
* @brief      Delete Stream IO
* @ingroup    PLATFORM_LINUX
*
* @param[in]  diostream : diostream to delete
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXFACTORY::DeleteStreamIO(DIOSTREAM* diostream)
{
  if(!diostream) return false;

  delete(diostream);

  return true;
}


#endif


#ifdef DIO_WIFIMANAGERMODE_ACTIVE

CREATEFUNC(DIOLINUXFACTORY, DIOWIFIMANAGERMODE  , DIOLINUXWIFIMANAGERMODE    , CreateWifiManagerMode)
DELETEFUNC(DIOLINUXFACTORY, DIOWIFIMANAGERMODE  , DIOLINUXWIFIMANAGERMODE    , DeleteWifiManagerMode)

#endif


#ifdef DIO_PCAP_ACTIVE

CREATEFUNC(DIOLINUXFACTORY, DIOPCAP   , DIOLINUXPCAP    , CreatePCap)
DELETEFUNC(DIOLINUXFACTORY, DIOPCAP   , DIOLINUXPCAP    , DeletePCap)

#endif


#ifdef DIO_LEDNEOPIXELWS2812B_ACTIVE 

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOLEDNEOPIXELWS2812B* DIOLINUXFACTORY::CreateLedNeopixelWS2812B()
* @brief      CreateLedNeopixelWS2812B
* @ingroup    PLATFORM_LINUX
*
* @return     DIOLEDNEOPIXELWS2812B* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOLEDNEOPIXELWS2812B* DIOLINUXFACTORY::CreateLedNeopixelWS2812B()
{
  #ifdef HW_RASPBERRYPI
  DIOLINUXLEDNEOPIXELWS2812BRPI* ledneopixelws2812b = new DIOLINUXLEDNEOPIXELWS2812BRPI();
  return ledneopixelws2812b;
  #else
  DIOLEDNEOPIXELWS2812B* ledneopixelws2812b = new DIOLEDNEOPIXELWS2812B();
  return ledneopixelws2812b;
  #endif
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOLINUXFACTORY::DeleteLedNeopixelWS2812B(DIOLEDNEOPIXELWS2812B* ledneopixelws2812b)
* @brief      DeleteLedNeopixelWS2812B
* @ingroup    PLATFORM_LINUX
*
* @param[in]  ledneopixelws2812b : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXFACTORY::DeleteLedNeopixelWS2812B(DIOLEDNEOPIXELWS2812B* ledneopixelws2812b)
{
  if(!ledneopixelws2812b) return false;
  
  delete ledneopixelws2812b;
  ledneopixelws2812b = NULL;
  
  return true;
}


#endif


#pragma endregion

