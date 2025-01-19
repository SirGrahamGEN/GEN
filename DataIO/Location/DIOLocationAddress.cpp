/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOLocationAddress.cpp
* 
* @class      DIOLOCATIONADDRESS
* @brief      Data Input/Output Location Address class  (container)
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

#include "DIOLocationAddress.h"

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
* @fn         DIOLOCATIONADDRESS::DIOLOCATIONADDRESS()
* @brief      Constructor of class
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOLOCATIONADDRESS::DIOLOCATIONADDRESS()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOLOCATIONADDRESS::~DIOLOCATIONADDRESS()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOLOCATIONADDRESS::~DIOLOCATIONADDRESS()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* DIOLOCATIONADDRESS::GetStreet()
* @brief      Get street
* @ingroup    DATAIO
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOLOCATIONADDRESS::GetStreet()
{
  return &street;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* DIOLOCATIONADDRESS::GetCity()
* @brief      Get city
* @ingroup    DATAIO
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOLOCATIONADDRESS::GetCity()
{
  return &city;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* DIOLOCATIONADDRESS::GetState()
* @brief      Get state
* @ingroup    DATAIO
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOLOCATIONADDRESS::GetState()
{
  return &state;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* DIOLOCATIONADDRESS::GetCountry()
* @brief      Get country
* @ingroup    DATAIO
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOLOCATIONADDRESS::GetCountry()
{
  return &country;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIOLOCATIONADDRESS::GetPostalCode()
* @brief      Get postal code
* @ingroup    DATAIO
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOLOCATIONADDRESS::GetPostalCode()
{
  return postalcode;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOLOCATIONADDRESS::SetPostalCode(XDWORD postalcode)
* @brief      Set postal code
* @ingroup    DATAIO
* 
* @param[in]  postalcode : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOLOCATIONADDRESS::SetPostalCode(XDWORD postalcode)
{
  this->postalcode = postalcode;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOLOCATIONADDRESS::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOLOCATIONADDRESS::Clean()
{
  postalcode  = 0;
}


#pragma endregion
