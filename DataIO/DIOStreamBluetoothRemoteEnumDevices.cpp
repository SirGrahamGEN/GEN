/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOStreamBluetoothRemoteEnumDevices.cpp
*
* @class      DIOSTREAMBLUETOOTHREMOTEENUMDEVICES
* @brief      
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

#include "DIOStreamBluetoothRemoteEnumDevices.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMBLUETOOTHREMOTEENUMDEVICES::DIOSTREAMBLUETOOTHREMOTEENUMDEVICES()
* @brief      Constructor
* @ingroup    DATAIO
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     Does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMBLUETOOTHREMOTEENUMDEVICES::DIOSTREAMBLUETOOTHREMOTEENUMDEVICES() : DIOSTREAMENUMDEVICES()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMBLUETOOTHREMOTEENUMDEVICES::~DIOSTREAMBLUETOOTHREMOTEENUMDEVICES()
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
DIOSTREAMBLUETOOTHREMOTEENUMDEVICES::~DIOSTREAMBLUETOOTHREMOTEENUMDEVICES()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMBLUETOOTHREMOTEENUMDEVICES::Search()
* @brief      Search
* @ingroup    DATAIO
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMBLUETOOTHREMOTEENUMDEVICES::Search()
{ 
  return false;   
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMBLUETOOTHREMOTEENUMDEVICES::StopSearch(bool waitend)
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
bool DIOSTREAMBLUETOOTHREMOTEENUMDEVICES::StopSearch(bool waitend)                      
{ 
  return false;   
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMBLUETOOTHREMOTEENUMDEVICES::IsSearching()
* @brief      IsSearching
* @ingroup    DATAIO
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMBLUETOOTHREMOTEENUMDEVICES::IsSearching()                                  
{ 
  return false;   
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMBLUETOOTHREMOTEENUMDEVICES::IsDeviceAvailable(XCHAR* resource)
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
bool DIOSTREAMBLUETOOTHREMOTEENUMDEVICES::IsDeviceAvailable(XCHAR* resource)                   
{ 
  return false;   
}



/*-------------------------------------------------------------------
//  DIOSTREAMBLUETOOTHREMOTEENUMDEVICES::Clean
*/
/**
//
//
//  @author      Abraham J. Velez
//  @version      28/04/2013 18:42:16
//
//  @return       void :
//  */
/*-----------------------------------------------------------------*/
void DIOSTREAMBLUETOOTHREMOTEENUMDEVICES::Clean()
{
  type = DIOSTREAMENUMTYPE_BLUETOOTH_REMOTE;
}


