/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOLINUXFactory.cpp
*
* @class      DIOLINUXFACTORY
* @brief      Linux Data Input/Output eXtended class
* @ingroup    PLATFORM_LINUX
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

#include "XFactoryMacros.h"
#include "XTrace.h"

#ifdef DIOUART_ACTIVE
#include "DIOStreamUARTConfig.h"
#include "DIOLINUXStreamUARTLocalEnumDevices.h"
#include "DIOLINUXStreamUART.h"
#endif

#ifdef DIOUSB_ACTIVE
#include "DIOStreamUSBConfig.h"
#include "DIOLINUXStreamUSBLocalEnumDevices.h"
#include "DIOLINUXStreamUSB.h"
#endif

#if defined(DIOICMP_ACTIVE) || defined(DIOUDP_ACTIVE) || defined(DIOTCPIP_ACTIVE)
#include "DIOLINUXStreamIPLocalEnumDevices.h"
#endif

#ifdef DIOICMP_ACTIVE
#include "DIOStreamICMPConfig.h"
#include "DIOLINUXStreamICMP.h"
#endif

#ifdef DIOUDP_ACTIVE
#include "DIOStreamUDPConfig.h"
#include "DIOLINUXStreamUDP.h"
#endif

#ifdef DIOTCPIP_ACTIVE
#include "DIOStreamTCPIPConfig.h"
#include "DIOLINUXStreamTCPIP.h"
#endif

#if defined(DIOBLUETOOTH_ACTIVE) || defined(DIOBLUETOOTHLE_ACTIVE)
#include "DIOStreamBluetoothConfig.h"
#include "DIOLINUXStreamBluetooth.h"
#include "DIOLINUXStreamBluetoothLocalEnumDevices.h"
#endif

#ifdef DIOBLUETOOTH_ACTIVE
#include "DIOLINUXStreamBluetoothRemoteEnumDevices.h"
#endif

#ifdef DIOBLUETOOTHLE_ACTIVE
#include "DIOLINUXStreamBluetoothLERemoteEnumDevices.h"
#endif

#ifdef DIOWIFI_ACTIVE
#include "DIOLINUXStreamWifiRemoteEnumDevices.h"
#endif


#ifdef DIOWIFIMANAGERMODE_ACTIVE
#include "DIOLINUXWifiManagerMode.h"
#endif

#ifdef DIOSPI_ACTIVE
#include "DIOStreamSPIConfig.h"
#include "DIOLINUXStreamSPI.h"
#endif

#ifdef DIOI2C_ACTIVE
#include "DIOStreamI2CConfig.h"
#include "DIOLINUXStreamI2C.h"
#endif

#ifdef DIOPING_ACTIVE
#include "DIOLINUXPing.h"
#endif

#ifdef DIOPCAP_ACTIVE
#include "DIOLINUXPCap.h"
#endif


#ifdef DIOLEDNEOPIXELWS2812B_ACTIVE 

#include "DIOLedNeoPixelWS2812B.h"

  #ifdef HW_PC    
  #endif  
  
  #ifdef HW_RASPBERRYPI
  #include "DIOLINUXLedNeoPixelWS2812BRaspberryPi.h"
  #endif
  
  #if defined(HW_NXP_IMX6) || defined(HW_NXP_IMX8)  
  #endif

#endif


#include "DIOLINUXFactory.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef ANYTYPEOFDIOSTREAMIO

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMENUMDEVICES* DIOLINUXFACTORY::CreateStreamEnumDevices(DIOSTREAMENUMTYPE type)
* @brief      Create Stream Enum Devices
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  type : type of enum to create
*
* @return     DIOSTREAMENUMDEVICES* : enum created
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMENUMDEVICES* DIOLINUXFACTORY::CreateStreamEnumDevices(DIOSTREAMENUMTYPE type)
{
  DIOSTREAMENUMDEVICES* _class = NULL;

  switch(type)
    {
      #ifdef DIOUART_ACTIVE
      case DIOSTREAMENUMTYPE_UART_LOCAL           : _class = new DIOLINUXSTREAMUARTLOCALENUMDEVICES();                      break;
      #endif

      #ifdef DIOUSB_ACTIVE
      case DIOSTREAMENUMTYPE_USB_LOCAL            : _class = new DIOLINUXSTREAMUSBLOCALENUMDEVICES();                       break;
      #endif

      #if defined(DIOUDP_ACTIVE) || defined(DIOTCPIP_ACTIVE)
      case DIOSTREAMENUMTYPE_IP_LOCAL             :  _class = new DIOLINUXSTREAMIPLOCALENUMDEVICES();                       break;
      #endif

      #if defined(DIOBLUETOOTH_ACTIVE) || defined(DIOBLUETOOTHLE_ACTIVE)
      case DIOSTREAMENUMTYPE_BLUETOOTH_LOCAL      :  _class = new DIOLINUXSTREAMBLUETOOTHLOCALENUMDEVICES();                break;
      #endif

      #if DIOBLUETOOTH_ACTIVE
      case DIOSTREAMENUMTYPE_BLUETOOTH_REMOTE     :  _class = new DIOLINUXSTREAMBLUETOOTHREMOTEENUMDEVICES();               break;
      #endif

      #if DIOBLUETOOTHLE_ACTIVE
      case DIOSTREAMENUMTYPE_BLUETOOTHLE_REMOTE   :  _class = new DIOLINUXSTREAMBLUETOOTHLEREMOTEENUMDEVICES();             break;
      #endif

      #ifdef DIOWIFI_ACTIVE
      case DIOSTREAMENUMTYPE_WIFI_REMOTE          :  _class = new DIOLINUXSTREAMWIFIREMOTEENUMDEVICES();                    break;
      #endif
    }

  if(_class) _class->SetType(type);

  return _class;
};




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOLINUXFACTORY::DeleteStreamEnumDevices(DIOSTREAMENUMDEVICES* enumdevices)
* @brief      Delete Stream Enum Devices
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  enumdevices : enumdevices to delete
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXFACTORY::DeleteStreamEnumDevices(DIOSTREAMENUMDEVICES* enumdevices)
{
  if(!enumdevices)  return false;

  delete enumdevices;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAM* DIOLINUXFACTORY::CreateStreamIO(DIOSTREAMCONFIG* config)
* @brief      Create Stream IO
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  config : config to create stream  IO
*
* @return     DIOSTREAM* : stream IO created
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSTREAM* DIOLINUXFACTORY::CreateStreamIO(DIOSTREAMCONFIG* config)
{
  if(!config) return NULL;

  DIOSTREAM* _class=NULL;

  switch(config->GetType())
    {
      case DIOSTREAMTYPE_UNKNOWN    : return NULL;

      #ifdef DIOUART_ACTIVE
      case DIOSTREAMTYPE_UART       : _class = new DIOLINUXSTREAMUART();        break;
      #endif

      #ifdef DIOUSB_ACTIVE
      case DIOSTREAMTYPE_USB        : _class = new DIOLINUXSTREAMUSB();         break;
      #endif

      #ifdef DIOICMP_ACTIVE
      case DIOSTREAMTYPE_ICMP       : _class = new DIOLINUXSTREAMICMP();        break;
      #endif

      #ifdef DIOUDP_ACTIVE
      case DIOSTREAMTYPE_UDP        : _class = new DIOLINUXSTREAMUDP();         break;
      #endif

      #ifdef DIOTCPIP_ACTIVE
      case DIOSTREAMTYPE_TCPIP      : _class = new DIOLINUXSTREAMTCPIP();       break;
      #endif

      #if (defined(DIOBLUETOOTH_ACTIVE) || defined(DIOBLUETOOTHLE_ACTIVE))
      case DIOSTREAMTYPE_BLUETOOTH  : _class = new DIOLINUXSTREAMBLUETOOTH();   break;
      #endif

      #ifdef DIOSPI_ACTIVE
      case DIOSTREAMTYPE_SPI        : _class = new DIOLINUXSTREAMSPI();         break;
      #endif

      #ifdef DIOI2C_ACTIVE
      case DIOSTREAMTYPE_I2C        : _class = new DIOLINUXSTREAMI2C();         break;
      #endif
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  diostream : diostream to delete
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXFACTORY::DeleteStreamIO(DIOSTREAM* diostream)
{
  if(!diostream) return false;

  delete(diostream);

  return true;
}


#endif



#ifdef DIOWIFIMANAGERMODE_ACTIVE

CREATEFUNC(DIOLINUXFACTORY, DIOWIFIMANAGERMODE  , DIOLINUXWIFIMANAGERMODE    , CreateWifiManagerMode)
DELETEFUNC(DIOLINUXFACTORY, DIOWIFIMANAGERMODE  , DIOLINUXWIFIMANAGERMODE    , DeleteWifiManagerMode)

#endif



#ifdef DIOPING_ACTIVE

CREATEFUNC(DIOLINUXFACTORY, DIOPING   , DIOLINUXPING    , CreatePing)
DELETEFUNC(DIOLINUXFACTORY, DIOPING   , DIOLINUXPING    , DeletePing)

#endif



#ifdef DIOPCAP_ACTIVE

CREATEFUNC(DIOLINUXFACTORY, DIOPCAP   , DIOLINUXPCAP    , CreatePCap)
DELETEFUNC(DIOLINUXFACTORY, DIOPCAP   , DIOLINUXPCAP    , DeletePCap)

#endif




#ifdef DIOLEDNEOPIXELWS2812B_ACTIVE 


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOLEDNEOPIXELWS2812B* DIOLINUXFACTORY::CreateLedNeopixelWS2812B()
* @brief      CreateLedNeopixelWS2812B
* @ingroup    PLATFORM_LINUX
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     DIOLEDNEOPIXELWS2812B* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOLEDNEOPIXELWS2812B* DIOLINUXFACTORY::CreateLedNeopixelWS2812B()
{
  #ifdef HW_RASPBERRYPI
  DIOLINUXLEDNEOPIXELWS2812BRASPBERRYPI* ledneopixelws2812b = new DIOLINUXLEDNEOPIXELWS2812BRASPBERRYPI();
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
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
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


