/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOStreamUSBLocalEnumDevices.cpp
* 
* @class      DIOSTREAMUSBLOCALENUMDEVICES
* @brief      Data Input/Output Stream USB local enum class
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

#include "DIOStreamUSBLocalEnumDevices.h"

#include "DIOStreamDeviceUSB.h"
#include "DIOStreamUSBConfig.h"

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
* @fn         DIOSTREAMUSBLOCALENUMDEVICES::DIOSTREAMUSBLOCALENUMDEVICES()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMUSBLOCALENUMDEVICES::DIOSTREAMUSBLOCALENUMDEVICES() : DIOSTREAMENUMDEVICES()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMUSBLOCALENUMDEVICES::~DIOSTREAMUSBLOCALENUMDEVICES()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMUSBLOCALENUMDEVICES::~DIOSTREAMUSBLOCALENUMDEVICES()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUSBLOCALENUMDEVICES::Search()
* @brief      Search
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUSBLOCALENUMDEVICES::Search()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUSBLOCALENUMDEVICES::StopSearch(bool waitend)
* @brief      Stop search
* @ingroup    DATAIO
*
* @param[in]  waitend :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUSBLOCALENUMDEVICES::StopSearch(bool waitend)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUSBLOCALENUMDEVICES::IsSearching()
* @brief      Is searching
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUSBLOCALENUMDEVICES::IsSearching()
{
  return issearching;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUSBLOCALENUMDEVICES::IsDeviceAvailable(XCHAR* resource)
* @brief      Is device available
* @ingroup    DATAIO
*
* @param[in]  resource :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUSBLOCALENUMDEVICES::IsDeviceAvailable(XCHAR* resource)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMDEVICEUSB* DIOSTREAMUSBLOCALENUMDEVICES::FindDevice(XCHAR* location)
* @brief      Find device
* @ingroup    DATAIO
*
* @param[in]  location :
*
* @return     DIOSTREAMDEVICEUSB* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMDEVICEUSB* DIOSTREAMUSBLOCALENUMDEVICES::FindDevice(XCHAR* location)
{
  if(devices.IsEmpty()) return NULL;

  for(XDWORD c=0; c<devices.GetSize(); c++)
    {
      DIOSTREAMDEVICEUSB* device = (DIOSTREAMDEVICEUSB*)devices.Get(c);
      if(device)
        {
          if(!device->GetLocation()->Compare(location))
            return (DIOSTREAMDEVICEUSB*)device;
        }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMDEVICEUSB* DIOSTREAMUSBLOCALENUMDEVICES::FindDevice(XSTRING& location)
* @brief      Find device
* @ingroup    DATAIO
*
* @param[in]  location :
*
* @return     DIOSTREAMDEVICEUSB* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMDEVICEUSB* DIOSTREAMUSBLOCALENUMDEVICES::FindDevice(XSTRING& location)
{
  return FindDevice(location.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMDEVICEUSB* DIOSTREAMUSBLOCALENUMDEVICES::FindDevice(XCHAR* location, DIOSTREAMDEVICEUSBCLASS classdev)
* @brief      Find device
* @ingroup    DATAIO
*
* @param[in]  location :
* @param[in]  classdev :
*
* @return     DIOSTREAMDEVICEUSB* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMDEVICEUSB* DIOSTREAMUSBLOCALENUMDEVICES::FindDevice(XCHAR* location, DIOSTREAMDEVICEUSBCLASS classdev)
{
  if(devices.IsEmpty()) return NULL;

  for(XDWORD c=0; c<devices.GetSize(); c++)
    {
      DIOSTREAMDEVICEUSB* device = (DIOSTREAMDEVICEUSB*)devices.Get(c);
      if(device)
        {
          if(!device->GetLocation()->Compare(location))
            {
              if(device->GetClass() == classdev)  return (DIOSTREAMDEVICEUSB*)device;
            }
        }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMDEVICEUSB* DIOSTREAMUSBLOCALENUMDEVICES::FindDevice(XSTRING& location, DIOSTREAMDEVICEUSBCLASS classdev)
* @brief      Find device
* @ingroup    DATAIO
*
* @param[in]  location :
* @param[in]  classdev :
*
* @return     DIOSTREAMDEVICEUSB* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMDEVICEUSB* DIOSTREAMUSBLOCALENUMDEVICES::FindDevice(XSTRING& location, DIOSTREAMDEVICEUSBCLASS classdev)
{
  return FindDevice(location.Get(), classdev);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMDEVICEUSB* DIOSTREAMUSBLOCALENUMDEVICES::FindDevice(XDWORD vendorID, XDWORD productID)
* @brief      Find device
* @ingroup    DATAIO
*
* @param[in]  vendorID :
* @param[in]  productID :
*
* @return     DIOSTREAMDEVICEUSB* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMDEVICEUSB* DIOSTREAMUSBLOCALENUMDEVICES::FindDevice(XDWORD vendorID, XDWORD productID)
{
  if(devices.IsEmpty()) return NULL;

  for(XDWORD c=0; c<devices.GetSize(); c++)
    {
      DIOSTREAMDEVICEUSB* device = (DIOSTREAMDEVICEUSB*)devices.Get(c);
      if(device)
        {
          if(((XDWORD)device->GetVendorID() == vendorID) && ((XDWORD)device->GetProductID() == productID)) return (DIOSTREAMDEVICEUSB*)device;
        }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMDEVICEUSB* DIOSTREAMUSBLOCALENUMDEVICES::FindDevice(XDWORD vendorID, XDWORD productID, DIOSTREAMDEVICEUSBCLASS classdev)
* @brief      Find device
* @ingroup    DATAIO
*
* @param[in]  vendorID :
* @param[in]  productID :
* @param[in]  classdev :
*
* @return     DIOSTREAMDEVICEUSB* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMDEVICEUSB* DIOSTREAMUSBLOCALENUMDEVICES::FindDevice(XDWORD vendorID, XDWORD productID, DIOSTREAMDEVICEUSBCLASS classdev)
{
  if(devices.IsEmpty()) return NULL;

  for(XDWORD c=0; c<devices.GetSize(); c++)
    {
      DIOSTREAMDEVICEUSB* device = (DIOSTREAMDEVICEUSB*)devices.Get(c);
      if(device)
        {
          if(((XDWORD)device->GetVendorID() == vendorID) && ((XDWORD)device->GetProductID() == productID) && (device->GetClass() == classdev))  return (DIOSTREAMDEVICEUSB*)device;
        }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMDEVICEUSB* DIOSTREAMUSBLOCALENUMDEVICES::FindDevice(DIOSTREAMUSBCONFIG& config)
* @brief      Find device
* @ingroup    DATAIO
*
* @param[in]  config :
*
* @return     DIOSTREAMDEVICEUSB* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMDEVICEUSB* DIOSTREAMUSBLOCALENUMDEVICES::FindDevice(DIOSTREAMUSBCONFIG& config)
{
  if(devices.IsEmpty()) return NULL;

  if(config.GetVendorID()  && config.GetProductID())
    {
      return FindDevice(config.GetVendorID(), config.GetProductID(), config.GetClass());
    }

  if(!config.GetLocation()->IsEmpty())
    {
      return FindDevice(config.GetLocation()->Get(), config.GetClass());
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMUSBLOCALENUMDEVICES::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMUSBLOCALENUMDEVICES::Clean()
{
  type        = DIOSTREAMENUMTYPE_USB_LOCAL;
  issearching = false;
}


#pragma endregion

