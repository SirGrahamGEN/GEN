/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XLocationAddress.cpp
*
* @class      XLOCATIONADDRESS
* @brief      eXtended Location Address class  (container)
* @ingroup    UTILS
*
* @copyright  GEN Group. All right reserved.
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

#include "XLocationAddress.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLOCATIONADDRESS::XLOCATIONADDRESS()
* @brief      Constructor
* @ingroup
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XLOCATIONADDRESS::XLOCATIONADDRESS()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLOCATIONADDRESS::~XLOCATIONADDRESS()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XLOCATIONADDRESS::~XLOCATIONADDRESS()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* XLOCATIONADDRESS::GetStreet()
* @brief      GetStreet
* @ingroup
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* XLOCATIONADDRESS::GetStreet()
{
  return &street;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* XLOCATIONADDRESS::GetCity()
* @brief      GetCity
* @ingroup
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* XLOCATIONADDRESS::GetCity()
{
  return &city;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* XLOCATIONADDRESS::GetState()
* @brief      GetState
* @ingroup
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* XLOCATIONADDRESS::GetState()
{
  return &state;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* XLOCATIONADDRESS::GetCountry()
* @brief      GetCountry
* @ingroup
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* XLOCATIONADDRESS::GetCountry()
{
  return &country;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XLOCATIONADDRESS::GetPostalCode()
* @brief      GetPostalCode
* @ingroup
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD XLOCATIONADDRESS::GetPostalCode()
{
  return postalcode;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XLOCATIONADDRESS::SetPostalCode(XDWORD postalcode)
* @brief      SetPostalCode
* @ingroup
*
* @param[in]  postalcode :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XLOCATIONADDRESS::SetPostalCode(XDWORD postalcode)
{
  this->postalcode = postalcode;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XLOCATIONADDRESS::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XLOCATIONADDRESS::Clean()
{
  postalcode  = 0;
}

