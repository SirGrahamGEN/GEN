/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOStreamBluetoothLocalEnumDevices.cpp
*
* @class      DIOSTREAMBLUETOOTHLOCALENUMDEVICES
* @brief      Data Input/Output Stream Bluetooth Local Enum Devices class
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "DIOStreamBluetoothLocalEnumDevices.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMBLUETOOTHLOCALENUMDEVICES::DIOSTREAMBLUETOOTHLOCALENUMDEVICES() 
* @brief      Constructor
* @ingroup    DATAIO
*
* @param[in]  ) : 
*
* @return     Does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMBLUETOOTHLOCALENUMDEVICES::DIOSTREAMBLUETOOTHLOCALENUMDEVICES() : DIOSTREAMENUMDEVICES()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMBLUETOOTHLOCALENUMDEVICES::~DIOSTREAMBLUETOOTHLOCALENUMDEVICES()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @return     Does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMBLUETOOTHLOCALENUMDEVICES::~DIOSTREAMBLUETOOTHLOCALENUMDEVICES()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMBLUETOOTHLOCALENUMDEVICES::Search()
* @brief      Search
* @ingroup    DATAIO
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMBLUETOOTHLOCALENUMDEVICES::Search()
{ 
  return false;         
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMBLUETOOTHLOCALENUMDEVICES::StopSearch(bool waitend)
* @brief      StopSearch
* @ingroup    DATAIO
*
* @param[in]  waitend : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMBLUETOOTHLOCALENUMDEVICES::StopSearch(bool waitend)                      
{ 
  return false;         
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMBLUETOOTHLOCALENUMDEVICES::IsSearching()
* @brief      IsSearching
* @ingroup    DATAIO
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMBLUETOOTHLOCALENUMDEVICES::IsSearching()                                  
{ 
  return issearching;   
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMBLUETOOTHLOCALENUMDEVICES::IsDeviceAvailable(XCHAR* resource)
* @brief      IsDeviceAvailable
* @ingroup    DATAIO
*
* @param[in]  resource : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMBLUETOOTHLOCALENUMDEVICES::IsDeviceAvailable(XCHAR* resource)                   
{ 
  return false;         
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMBLUETOOTHLOCALENUMDEVICES::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMBLUETOOTHLOCALENUMDEVICES::Clean()
{
  type        = DIOSTREAMENUMTYPE_BLUETOOTH_LOCAL;
  issearching = false;
}


