/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOWINDOWSStreamBluetoothLERemoteEnumDevices.cpp
* 
* @class      DIOWINDOWSSTREAMBLUETOOTHLEREMOTEENUMDEVICES
* @brief      WINDOWS Data Input/Output Bluetooth LE REMOTE Enum Devices class
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


#if defined(DIO_ACTIVE) && defined(DIO_STREAMBLUETOOTHLE_ACTIVE)


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIOWINDOWSStreamBluetoothLERemoteEnumDevices.h"

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
* @fn         DIOWINDOWSSTREAMBLUETOOTHLEREMOTEENUMDEVICES::DIOWINDOWSSTREAMBLUETOOTHLEREMOTEENUMDEVICES()
* @brief      Constructor of class
* @ingroup    PLATFORM_WINDOWS
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWINDOWSSTREAMBLUETOOTHLEREMOTEENUMDEVICES::DIOWINDOWSSTREAMBLUETOOTHLEREMOTEENUMDEVICES(): DIOSTREAMBLUETOOTHLEREMOTEENUMDEVICES()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWINDOWSSTREAMBLUETOOTHLEREMOTEENUMDEVICES::~DIOWINDOWSSTREAMBLUETOOTHLEREMOTEENUMDEVICES()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    PLATFORM_WINDOWS
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWINDOWSSTREAMBLUETOOTHLEREMOTEENUMDEVICES::~DIOWINDOWSSTREAMBLUETOOTHLEREMOTEENUMDEVICES()
{
  StopSearch(true);

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWINDOWSSTREAMBLUETOOTHLEREMOTEENUMDEVICES::Search()
* @brief      Search
* @ingroup    PLATFORM_WINDOWS
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWINDOWSSTREAMBLUETOOTHLEREMOTEENUMDEVICES::Search()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWINDOWSSTREAMBLUETOOTHLEREMOTEENUMDEVICES::StopSearch(bool waitend)
* @brief      Stop search
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  waitend : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWINDOWSSTREAMBLUETOOTHLEREMOTEENUMDEVICES::StopSearch(bool waitend)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWINDOWSSTREAMBLUETOOTHLEREMOTEENUMDEVICES::IsSearching()
* @brief      Is searching
* @ingroup    PLATFORM_WINDOWS
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWINDOWSSTREAMBLUETOOTHLEREMOTEENUMDEVICES::IsSearching()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWINDOWSSTREAMBLUETOOTHLEREMOTEENUMDEVICES::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    PLATFORM_WINDOWS
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWINDOWSSTREAMBLUETOOTHLEREMOTEENUMDEVICES::Clean()
{

}


#pragma endregion


#endif

