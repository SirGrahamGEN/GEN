/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOLINUXStreamBluetoothLocalEnumDevices.cpp
*
* @class      DIOLINUXSTREAMBLUETOOTHLOCALENUMDEVICES
* @brief      LINUX Data Input/Output Stream Bluetooth Local Enum Devices class
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @copyright  Copyright(c) 2005 - 2020 GEN Group.
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


#if defined(DIO_ACTIVE) && (defined(DIOBLUETOOTH_ACTIVE) || defined(DIOBLUETOOTHLE_ACTIVE))

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

#include "DIOStreamDeviceBluetooth.h"
#include "DIOLINUXStreamBluetoothLocalEnumDevices.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOLINUXSTREAMBLUETOOTHLOCALENUMDEVICES::DIOLINUXSTREAMBLUETOOTHLOCALENUMDEVICES()
* @brief      Constructor
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     Does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOLINUXSTREAMBLUETOOTHLOCALENUMDEVICES::DIOLINUXSTREAMBLUETOOTHLOCALENUMDEVICES() : DIOSTREAMBLUETOOTHLOCALENUMDEVICES()
{

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOLINUXSTREAMBLUETOOTHLOCALENUMDEVICES::~DIOLINUXSTREAMBLUETOOTHLOCALENUMDEVICES()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     Does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOLINUXSTREAMBLUETOOTHLOCALENUMDEVICES::~DIOLINUXSTREAMBLUETOOTHLOCALENUMDEVICES()
{

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOLINUXSTREAMBLUETOOTHLOCALENUMDEVICES::Search()
* @brief      Search
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXSTREAMBLUETOOTHLOCALENUMDEVICES::Search()
{
  DelAllDevices();

  struct hci_dev_info di;
  int                 indexdev = 0;

  while(hci_devinfo(indexdev, &di)>=0)
    {
      DIOSTREAMDEVICEBLUETOOTH* device = new DIOSTREAMDEVICEBLUETOOTH();
      if(device)
        {
          char addr[32];

          device->GetName()->Set(di.name);

          ba2str(&di.bdaddr, addr);
          device->GetMAC()->Set(addr);

          devices.Add(device);
        }

      indexdev++;
    }

  return true;
}


#endif