/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOStreamDeviceBluetoothLE.cpp
*
* @class      DIOSTREAMDEVICEBLUETOOTHLE
* @brief      Data Input/Output Stream Device Bluetooth LE class
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

#include <string.h>

#include "XFactory.h"
#include "XString.h"
#include "XTimer.h"

#include "DIOStreamDeviceBluetoothLE.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMDEVICEBLUETOOTHLE:: DIOSTREAMDEVICEBLUETOOTHLE()
* @brief      IOSTREAMDEVICEBLUETOOTH
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     DIOSTREAMDEVICEBLUETOOTHLE:: :
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMDEVICEBLUETOOTHLE:: DIOSTREAMDEVICEBLUETOOTHLE()
{
  Clean();
  
  lastscantimer = GEN_XFACTORY.CreateTimer();  
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMDEVICEBLUETOOTHLE::~ DIOSTREAMDEVICEBLUETOOTHLE()
* @brief      IOSTREAMDEVICEBLUETOOTH
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     DIOSTREAMDEVICEBLUETOOTHLE::~ :
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMDEVICEBLUETOOTHLE::~ DIOSTREAMDEVICEBLUETOOTHLE()
{

  if(lastscantimer) 
    {
      GEN_XFACTORY.DeleteTimer(lastscantimer);
      lastscantimer = NULL;
    } 

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBUFFER* DIOSTREAMDEVICEBLUETOOTHLE::GetAdvertisingData()
* @brief      GetAdvertisingData
* @ingroup    DATAIO
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     XBUFFER* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XBUFFER* DIOSTREAMDEVICEBLUETOOTHLE::GetAdvertisingData()
{
  return &advertisingdata;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTIMER* DIOSTREAMDEVICEBLUETOOTHLE::GetLastScanTimer()
* @brief      GetLastScanTimer
* @ingroup    DATAIO
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     XTIMER* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XTIMER* DIOSTREAMDEVICEBLUETOOTHLE::GetLastScanTimer()
{
  return lastscantimer;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMDEVICEBLUETOOTHLE::IsReadLastScan()
* @brief      IsReadLastScan
* @ingroup    DATAIO
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMDEVICEBLUETOOTHLE::IsReadLastScan()
{
  return isreadlastscan;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMDEVICEBLUETOOTHLE::SetIsReadLastScan(bool isreadlastscan)
* @brief      SetIsReadLastScan
* @ingroup    DATAIO
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  isreadlastscan : 
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMDEVICEBLUETOOTHLE::SetIsReadLastScan(bool isreadlastscan)
{
  this->isreadlastscan = isreadlastscan;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMDEVICEBLUETOOTHLE::DebugPrintInfo()
* @brief      DebugPrintInfo
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMDEVICEBLUETOOTHLE::DebugPrintInfo()
{
  DIOSTREAMDEVICE::DebugPrintInfo();

  XSTRING line;
  XSTRING data;

  GetMAC()->GetXString(data);
  line.Format(__L("MAC           : %s") , data.Get());                          XTRACE_PRINTCOLOR(2, line.Get());



  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMDEVICEBLUETOOTHLE::Clean()
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
void DIOSTREAMDEVICEBLUETOOTHLE::Clean()
{
  type            = DIOSTREAMDEVICE_TYPE_BLUETOOTHLE;

  rssi            = 0;
  lastscantimer   = NULL;
  isreadlastscan  = false;
  isvisible       = false;
}



