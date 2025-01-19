/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOStreamEnumDevices.cpp
* 
* @class      DIOSTREAMENUMDEVICES
* @brief      Data Input/Output Stream Enum Devices class
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

#include "DIOStreamEnumDevices.h"

#include "XFactory.h"
#include "XPublisher.h"

#include "DIOStreamDevice.h"

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
* @fn         DIOSTREAMENUMDEVICES::DIOSTREAMENUMDEVICES()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMENUMDEVICES::DIOSTREAMENUMDEVICES()
{
  Clean();

  GEN_XFACTORY_CREATE(xtimerout, CreateTimer()) 
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMENUMDEVICES::~DIOSTREAMENUMDEVICES()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMENUMDEVICES::~DIOSTREAMENUMDEVICES()
{
  if(xtimerout) GEN_XFACTORY.DeleteTimer(xtimerout);

  DelAllDevices();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMENUMTYPE DIOSTREAMENUMDEVICES::GetType()
* @brief      Get type
* @ingroup    DATAIO
*
* @return     DIOSTREAMENUMTYPE :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMENUMTYPE DIOSTREAMENUMDEVICES::GetType()
{
  return type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSTREAMENUMDEVICES::SetType(DIOSTREAMENUMTYPE type)
* @brief      Set type
* @ingroup    DATAIO
* 
* @param[in]  type : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMENUMDEVICES::SetType(DIOSTREAMENUMTYPE type)
{
  this->type = type;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMENUMDEVICES::Search()
* @brief      Search
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMENUMDEVICES::Search()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMENUMDEVICES::StopSearch(bool waitend)
* @brief      Stop search
* @ingroup    DATAIO
*
* @param[in]  waitend :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMENUMDEVICES::StopSearch(bool waitend)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMENUMDEVICES::IsSearching()
* @brief      Is searching
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMENUMDEVICES::IsSearching()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMENUMDEVICES::AddDevice(DIOSTREAMDEVICE* device)
* @brief      Add device
* @ingroup    DATAIO
*
* @param[in]  device :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMENUMDEVICES::AddDevice(DIOSTREAMDEVICE* device)
{
  devices.Add(device);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XVECTOR<DIOSTREAMDEVICE*>* DIOSTREAMENUMDEVICES::GetDevices()
* @brief      Get devices
* @ingroup    DATAIO
*
* @return     XVECTOR<DIOSTREAMDEVICE*>* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<DIOSTREAMDEVICE*>* DIOSTREAMENUMDEVICES::GetDevices()
{
  return &devices;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMENUMDEVICES::DelAllDevices()
* @brief      Del all devices
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMENUMDEVICES::DelAllDevices()
{
  if(devices.IsEmpty()) return false;

  devices.DeleteContents();
  devices.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMENUMDEVICES::IsDeviceAvailable(XCHAR* string)
* @brief      Is device available
* @ingroup    DATAIO
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMENUMDEVICES::IsDeviceAvailable(XCHAR* string)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMENUMDEVICES::IsDeviceAvailable(XSTRING& string)
* @brief      Is device available
* @ingroup    DATAIO
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMENUMDEVICES::IsDeviceAvailable(XSTRING& string)
{
  return IsDeviceAvailable(string.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMENUMDEVICES::AreDevicesAvailable()
* @brief      Are devices available
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMENUMDEVICES::AreDevicesAvailable()
{
  return devices.GetSize()?true:false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMDEVICE* DIOSTREAMENUMDEVICES::GetDeviceByName(XCHAR* name)
* @brief      Get device by name
* @ingroup    DATAIO
*
* @param[in]  name :
*
* @return     DIOSTREAMDEVICE* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMDEVICE* DIOSTREAMENUMDEVICES::GetDeviceByName(XCHAR* name)
{
  if(devices.IsEmpty()) return NULL;

  for(XDWORD c=0; c<devices.GetSize(); c++)
    {
      DIOSTREAMDEVICE* device = devices.Get(c);
      if(device)
        {
          if(!device->GetName()->Compare(name)) return device;
        }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMDEVICE* DIOSTREAMENUMDEVICES::GetDeviceByName(XSTRING& name)
* @brief      Get device by name
* @ingroup    DATAIO
*
* @param[in]  name :
*
* @return     DIOSTREAMDEVICE* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMDEVICE* DIOSTREAMENUMDEVICES::GetDeviceByName(XSTRING& name)
{
  return GetDeviceByName(name.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMDEVICE* DIOSTREAMENUMDEVICES::GetDeviceByIndex(int index)
* @brief      Get device by index
* @ingroup    DATAIO
*
* @param[in]  index :
*
* @return     DIOSTREAMDEVICE* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMDEVICE* DIOSTREAMENUMDEVICES::GetDeviceByIndex(int index)
{
  for(int c=0;c<(int)devices.GetSize();c++)
    {
      DIOSTREAMDEVICE* device = devices.Get(c);
      if(device)
        {
          if(device->GetIndex() == index) return device;
        }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMENUMDEVICES::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMENUMDEVICES::Clean()
{
  xtimerout       = NULL;
}


#pragma endregion

