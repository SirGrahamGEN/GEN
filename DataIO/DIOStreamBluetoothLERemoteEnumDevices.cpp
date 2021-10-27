/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOStreamBluetoothLERemoteEnumDevices.cpp
*
* @class      DIOSTREAMBLUETOOTHLEREMOTEENUMDEVICES
* @brief      Data Input/Output Stream Bluetooth LE REMOTE Enum Devices class
* @ingroup    DATAIO
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


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "DIOStreamBluetoothLERemoteEnumDevices.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMBLUETOOTHLEREMOTEENUMDEVICES::DIOSTREAMBLUETOOTHLEREMOTEENUMDEVICES()
* @brief      Constructor
* @ingroup    DATAIO
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     Does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMBLUETOOTHLEREMOTEENUMDEVICES::DIOSTREAMBLUETOOTHLEREMOTEENUMDEVICES() 
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMBLUETOOTHLEREMOTEENUMDEVICES::~DIOSTREAMBLUETOOTHLEREMOTEENUMDEVICES()
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
DIOSTREAMBLUETOOTHLEREMOTEENUMDEVICES::~DIOSTREAMBLUETOOTHLEREMOTEENUMDEVICES()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMBLUETOOTHLEREMOTEENUMDEVICES::Search()
* @brief      Search
* @ingroup    DATAIO
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMBLUETOOTHLEREMOTEENUMDEVICES::Search()
{ 
  return false;   
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMBLUETOOTHLEREMOTEENUMDEVICES::StopSearch(bool waitend)
* @brief      StopSearch
* @ingroup    DATAIO
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  waitend : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMBLUETOOTHLEREMOTEENUMDEVICES::StopSearch(bool waitend)                      
{ 
  return false;   
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMBLUETOOTHLEREMOTEENUMDEVICES::IsSearching()
* @brief      IsSearching
* @ingroup    DATAIO
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMBLUETOOTHLEREMOTEENUMDEVICES::IsSearching()                                  
{ 
  return false;   
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMBLUETOOTHLEREMOTEENUMDEVICES::IsDeviceAvailable(XCHAR* resource)
* @brief      IsDeviceAvailable
* @ingroup    DATAIO
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  resource : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMBLUETOOTHLEREMOTEENUMDEVICES::IsDeviceAvailable(XCHAR* resource)                   
{ 
  return false;   
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOSTREAMBLUETOOTHLEREMOTEENUMDEVICES::GetSearchMode()
* @brief      GetSearchMode
* @ingroup    DATAIO
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     XDWORD : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSTREAMBLUETOOTHLEREMOTEENUMDEVICES::GetSearchMode()
{
  return searchmode;
}


    
/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMBLUETOOTHLEREMOTEENUMDEVICES::SetSearchMode(XDWORD searchmode)
* @brief      SetSearchMode
* @ingroup    DATAIO
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  searchmode : 
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMBLUETOOTHLEREMOTEENUMDEVICES::SetSearchMode(XDWORD searchmode)
{
  this->searchmode |= searchmode;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMBLUETOOTHLEREMOTEENUMDEVICES::Clean()
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
void DIOSTREAMBLUETOOTHLEREMOTEENUMDEVICES::Clean()
{
  type        = DIOSTREAMENUMTYPE_BLUETOOTHLE_REMOTE;

  searchmode  = DIOSTREAMBLUETOOTHLEREMOTEENUMDEVICES_SEARCHMODE_NONE;
}


