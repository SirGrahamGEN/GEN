/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOStreamEnumBluetoothDevices.cpp
* 
* @class      DIOSTREAMENUMBLUETOOTHDEVICES
* @brief      Data Input/Output Stream Enum Bluetooth Devices class
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

#include "DIOStreamEnumBluetoothDevices.h"

#include "DIOStreamDeviceBluetooth.h"

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
* @fn         DIOSTREAMENUMBLUETOOTHDEVICES::DIOSTREAMENUMBLUETOOTHDEVICES()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMENUMBLUETOOTHDEVICES::DIOSTREAMENUMBLUETOOTHDEVICES()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMENUMBLUETOOTHDEVICES::~DIOSTREAMENUMBLUETOOTHDEVICES()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMENUMBLUETOOTHDEVICES::~DIOSTREAMENUMBLUETOOTHDEVICES()
{  
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOMAC* DIOSTREAMENUMBLUETOOTHDEVICES::GetDeviceSelect()
* @brief      Get device select
* @ingroup    DATAIO
*
* @return     DIOMAC* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOMAC* DIOSTREAMENUMBLUETOOTHDEVICES::GetDeviceSelect()
{
  return &deviceselectMAC;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMENUMBLUETOOTHDEVICES::SetDeviceSelect(XBYTE* MAC)
* @brief      Set device select
* @ingroup    DATAIO
*
* @param[in]  MAC : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMENUMBLUETOOTHDEVICES::SetDeviceSelect(XBYTE* MAC)
{
  return deviceselectMAC.Set(MAC);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMENUMBLUETOOTHDEVICES::SetDeviceSelect(XCHAR* MAC)
* @brief      Set device select
* @ingroup    DATAIO
*
* @param[in]  MAC : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMENUMBLUETOOTHDEVICES::SetDeviceSelect(XCHAR* MAC)
{
  XSTRING _MAC;

  _MAC = MAC;

  return SetDeviceSelect(_MAC);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMENUMBLUETOOTHDEVICES::SetDeviceSelect(XSTRING& MAC)
* @brief      Set device select
* @ingroup    DATAIO
*
* @param[in]  MAC : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMENUMBLUETOOTHDEVICES::SetDeviceSelect(XSTRING& MAC)
{
  return deviceselectMAC.Set(MAC);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMDEVICEBLUETOOTH* DIOSTREAMENUMBLUETOOTHDEVICES::GetDeviceByMAC(XCHAR* MAC)
* @brief      Get device by MAC
* @ingroup    DATAIO
*
* @param[in]  MAC : 
*
* @return     DIOSTREAMDEVICEBLUETOOTH* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMDEVICEBLUETOOTH* DIOSTREAMENUMBLUETOOTHDEVICES::GetDeviceByMAC(XCHAR* MAC)
{ 
  if(devices.IsEmpty()) return NULL;

  XSTRING MACstring;

  MACstring = MAC;
  if(MACstring.IsEmpty())  return NULL;

  for(XDWORD c=0; c<devices.GetSize(); c++)
    {      
      DIOSTREAMDEVICEBLUETOOTH* device = (DIOSTREAMDEVICEBLUETOOTH*)devices.Get(c);
      if(device)
        {
          DIOMAC* MAC = device->GetMAC();
          if(MAC)
            {
              XSTRING MACdevicestr;
  
              MAC->GetXString(MACdevicestr);

              if(!MACdevicestr.Compare(MACstring, true)) return device;
            }
        }      
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMDEVICEBLUETOOTH* DIOSTREAMENUMBLUETOOTHDEVICES::GetDeviceByMAC(DIOMAC* MAC)
* @brief      Get device by MAC
* @ingroup    DATAIO
*
* @param[in]  MAC : 
*
* @return     DIOSTREAMDEVICEBLUETOOTH* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMDEVICEBLUETOOTH* DIOSTREAMENUMBLUETOOTHDEVICES::GetDeviceByMAC(DIOMAC* MAC)
{
  if(devices.IsEmpty()) return NULL;

  if(!MAC) return NULL;

  for(XDWORD c=0; c<devices.GetSize(); c++)
    {      
      DIOSTREAMDEVICEBLUETOOTH* device = (DIOSTREAMDEVICEBLUETOOTH*)devices.Get(c);
      if(device)
        {
          DIOMAC* MACdev = device->GetMAC();
          if(MACdev)
            {
              if(MACdev->IsEqual(MAC)) return device;
            }
        }      
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMENUMBLUETOOTHDEVICES::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMENUMBLUETOOTHDEVICES::Clean()
{
  
}


#pragma endregion

