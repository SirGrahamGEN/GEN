/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XESP32DateTime.cpp
* 
* @class      XESP32DATETIME
* @brief      eXtended Utils ESP32 date time class
* @ingroup    PLATFORM_ESP32
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

#include "XESP32DateTime.h"

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
* @fn         XESP32DATETIME::XESP32DATETIME()
* @brief      Constructor of class
* @ingroup    PLATFORM_ESP32
*
* --------------------------------------------------------------------------------------------------------------------*/
XESP32DATETIME::XESP32DATETIME()
{
  
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XESP32DATETIME::~XESP32DATETIME()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    PLATFORM_ESP32
*
* --------------------------------------------------------------------------------------------------------------------*/
XESP32DATETIME::~XESP32DATETIME()
{

}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XESP32DATETIME::Read()
* @brief      Read
* @ingroup    PLATFORM_ESP32
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XESP32DATETIME::Read()
{
  //GetActualDateTime(this);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XESP32DATETIME::Write()
* @brief      Write
* @ingroup    PLATFORM_ESP32
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XESP32DATETIME::Write()
{
  //SetActualDateTime(this);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XESP32DATETIME::GetMeridianDifference()
* @brief      Get meridian difference
* @ingroup    PLATFORM_ESP32
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XESP32DATETIME::GetMeridianDifference()
{
  return (int)0;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XESP32DATETIME::IsDayLigthSavingTime(int* bias)
* @brief      Is day ligth saving time
* @ingroup    PLATFORM_ESP32
*
* @param[in]  bias :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XESP32DATETIME::IsDayLigthSavingTime(int* bias)
{
  return false;
}


#pragma endregion

