/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XSAMD5xE5xDateTime.cpp
*
* @class      XSAMD5XE5XDATETIME
* @brief      SAMD5xE5x Date Time class
* @ingroup    PLATFORM_SAMD5XE5X
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

#include "XSAMD5xE5xDateTime.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSAMD5XE5XDATETIME::XSAMD5XE5XDATETIME()
* @brief      Constructor
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XSAMD5XE5XDATETIME::XSAMD5XE5XDATETIME()
{

}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSAMD5XE5XDATETIME::~XSAMD5XE5XDATETIME()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XSAMD5XE5XDATETIME::~XSAMD5XE5XDATETIME()
{

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSAMD5XE5XDATETIME::Read()
* @brief      Read
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSAMD5XE5XDATETIME::Read()
{
  //GetActualDateTime(this);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSAMD5XE5XDATETIME::Write()
* @brief      Write
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSAMD5XE5XDATETIME::Write()
{
  //SetActualDateTime(this);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XSAMD5XE5XDATETIME::GetMeridianDifference()
* @brief      GetMeridianDifference
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XSAMD5XE5XDATETIME::GetMeridianDifference()
{
  return (int)0;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSAMD5XE5XDATETIME::IsDayLigthSavingTime(int* bias)
* @brief      IsDayLigthSavingTime
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  bias :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSAMD5XE5XDATETIME::IsDayLigthSavingTime(int* bias)
{
  return false;
}



