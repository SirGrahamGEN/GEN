/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOStreamUSBConfig.cpp
* 
* @class      DIOSTREAMUSBCONFIG
* @brief      Data Input/Output Stream USB config class
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

#include "DIOStreamUSBConfig.h"

#include "DIOStreamUSBLocalEnumDevices.h"

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
* @fn         DIOSTREAMUSBCONFIG::DIOSTREAMUSBCONFIG()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMUSBCONFIG::DIOSTREAMUSBCONFIG() : DIOSTREAMCONFIG()
{
  Clean();

  type = DIOSTREAMTYPE_USB;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMUSBCONFIG::~DIOSTREAMUSBCONFIG()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMUSBCONFIG::~DIOSTREAMUSBCONFIG()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOSTREAMUSBCONFIG::GetLocation()
* @brief      Get location
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOSTREAMUSBCONFIG::GetLocation()
{
  return &location;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOSTREAMUSBCONFIG::GetVendorID()
* @brief      Get vendor ID
* @ingroup    DATAIO
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSTREAMUSBCONFIG::GetVendorID()
{
  return vendorID;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMUSBCONFIG::SetVendorID(XDWORD vendorID)
* @brief      Set vendor ID
* @ingroup    DATAIO
*
* @param[in]  vendorID :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMUSBCONFIG::SetVendorID(XDWORD vendorID)
{
  this->vendorID = vendorID;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOSTREAMUSBCONFIG::GetProductID()
* @brief      Get product ID
* @ingroup    DATAIO
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSTREAMUSBCONFIG::GetProductID()
{
  return productID;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMUSBCONFIG::SetProductID(XDWORD productID)
* @brief      Set product ID
* @ingroup    DATAIO
*
* @param[in]  productID :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMUSBCONFIG::SetProductID(XDWORD productID)
{
  this->productID=productID;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMDEVICEUSBCLASS DIOSTREAMUSBCONFIG::GetClass()
* @brief      Get class
* @ingroup    DATAIO
*
* @return     DIOSTREAMDEVICEUSBCLASS :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMDEVICEUSBCLASS DIOSTREAMUSBCONFIG::GetClass()
{
  return classdev;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMUSBCONFIG::SetClass(DIOSTREAMDEVICEUSBCLASS classdev)
* @brief      Set class
* @ingroup    DATAIO
*
* @param[in]  classdev :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMUSBCONFIG::SetClass(DIOSTREAMDEVICEUSBCLASS classdev)
{
  this->classdev = classdev;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOSTREAMUSBCONFIG::GetResource()
* @brief      Get resource
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOSTREAMUSBCONFIG::GetResource()
{
  return &resource;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUSBCONFIG::GetToString(XSTRING* string)
* @brief      Get to string
* @ingroup    DATAIO
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUSBCONFIG::GetToString(XSTRING* string)
{
  if(!string) return false;

  string->Empty();

  if(vendorID && productID && classdev)
    {
      string->Format(__L("0x%04X,0x%04X,%d"), vendorID, productID, classdev);
      return true;
    }

  if(!location.IsEmpty() && classdev)
    {
      string->Format(__L("%s,%d"), location.Get(), classdev);
      return true;
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUSBCONFIG::GetToString(XSTRING& string)
* @brief      Get to string
* @ingroup    DATAIO
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUSBCONFIG::GetToString(XSTRING& string)
{
  return GetToString(&string);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUSBCONFIG::SetFromString(XCHAR* string)
* @brief      Set from string
* @ingroup    DATAIO
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUSBCONFIG::SetFromString(XCHAR* string)
{
  if(!string) return false;

  XSTRING  _string   = string;
  int      _classdev = 0;

  if(_string.Find(DIOSTREAMUSBLOCALENUMDEVICES_PORTKEY, true) != XSTRING_NOTFOUND)
    {
      if(_string.Find(DIOSTREAMUSBLOCALENUMDEVICES_PORTHUB, true) != XSTRING_NOTFOUND)
        {
          XSTRING _location;

          _string.UnFormat(__L("%s,%d"), location.Get(), &classdev);

          location = _location;
          classdev = (DIOSTREAMDEVICEUSBCLASS)_classdev;

          return true;
        }
    }

  XDWORD _vendorID  = 0;
  XDWORD _productID = 0;

  _string.UnFormat(__L("0x%04X,0x%04X,%d"), &_vendorID, &_productID, &_classdev);

  vendorID  = _vendorID;
  productID = _productID;
  classdev  = (DIOSTREAMDEVICEUSBCLASS)_classdev;

  return ((vendorID && productID)?true:false);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUSBCONFIG::SetFromString(XSTRING* string)
* @brief      Set from string
* @ingroup    DATAIO
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUSBCONFIG::SetFromString(XSTRING* string)
{
  if(!string) return false;

  return SetFromString(string->Get());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUSBCONFIG::SetFromString(XSTRING& string)
* @brief      Set from string
* @ingroup    DATAIO
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUSBCONFIG::SetFromString(XSTRING& string)
{
  return SetFromString(&string);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMUSBCONFIG::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMUSBCONFIG::Clean()
{
  vendorID    = 0;
  productID   = 0;
  classdev    = DIOSTREAMDEVICEUSBCLASS_DEVICE_USECLASSINFORMATIONINTERFACEDESCRIPTORS;
}


#pragma endregion
