/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOStreamBluetoothConfig.cpp
* 
* @class      DIOSTREAMBLUETOOTHCONFIG
* @brief      Data Input/Output Stream Bluetooth Config class
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

#include "DIOStreamBluetoothConfig.h"

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
* @fn         DIOSTREAMBLUETOOTHCONFIG::DIOSTREAMBLUETOOTHCONFIG()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMBLUETOOTHCONFIG::DIOSTREAMBLUETOOTHCONFIG(): DIOSTREAMCONFIG()
{
  Clean();

  type = DIOSTREAMTYPE_BLUETOOTH;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMBLUETOOTHCONFIG::~DIOSTREAMBLUETOOTHCONFIG()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMBLUETOOTHCONFIG::~DIOSTREAMBLUETOOTHCONFIG()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOSTREAMBLUETOOTHCONFIG::GetDeviceSelect()
* @brief      Get device select
* @ingroup    DATAIO
*
* @return     int : 
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOSTREAMBLUETOOTHCONFIG::GetDeviceSelect()
{
  return deviceselect;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMBLUETOOTHCONFIG::SetDeviceSelect(int deviceselect)
* @brief      Set device select
* @ingroup    DATAIO
*
* @param[in]  deviceselect : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMBLUETOOTHCONFIG::SetDeviceSelect(int deviceselect)
{
  this->deviceselect = deviceselect;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOMAC* DIOSTREAMBLUETOOTHCONFIG::GetLocalMAC()
* @brief      Get local MAC
* @ingroup    DATAIO
*
* @return     DIOMAC* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOMAC* DIOSTREAMBLUETOOTHCONFIG::GetLocalMAC()
{
  return &localMAC;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOMAC* DIOSTREAMBLUETOOTHCONFIG::GetRemoteMAC()
* @brief      Get remote MAC
* @ingroup    DATAIO
*
* @return     DIOMAC* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOMAC* DIOSTREAMBLUETOOTHCONFIG::GetRemoteMAC()
{
  return &remoteMAC;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOSTREAMBLUETOOTHCONFIG::GetRemoteChannel()
* @brief      Get remote channel
* @ingroup    DATAIO
*
* @return     int : 
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOSTREAMBLUETOOTHCONFIG::GetRemoteChannel()
{
  return channel;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMBLUETOOTHCONFIG::SetRemoteChannel(int channel)
* @brief      Set remote channel
* @ingroup    DATAIO
*
* @param[in]  channel : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMBLUETOOTHCONFIG::SetRemoteChannel(int channel)
{
  this->channel = channel;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOSTREAMBLUETOOTHCONFIG::GetPIN()
* @brief      Get PIN
* @ingroup    DATAIO
*
* @return     XSTRING* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOSTREAMBLUETOOTHCONFIG::GetPIN()
{
  return &pin;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void* DIOSTREAMBLUETOOTHCONFIG::GetServerPropertys(int index)
* @brief      Get server propertys
* @ingroup    DATAIO
*
* @param[in]  index : 
*
* @return     void* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
void* DIOSTREAMBLUETOOTHCONFIG::GetServerPropertys(int index)
{
  if(index <  0) return NULL;
  if(index >= 3) return NULL;

  return serverproperties[index];
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMBLUETOOTHCONFIG::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMBLUETOOTHCONFIG::Clean()
{
  type                = DIOSTREAMTYPE_BLUETOOTH;
  deviceselect        = -1;

  channel             = 0;

  serverproperties[0] = NULL;
  serverproperties[1] = NULL;
  serverproperties[2] = NULL;
}


#pragma endregion

