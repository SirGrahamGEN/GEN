/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XSAMD5xE5xSleep.cpp
*
* @class      XSAMD5XE5XSLEEP
* @brief      SAMD5xE5x Sleep class
* @ingroup    PLATFORM_SAMD5XE5X
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

#include "XSAMD5xE5x_HAL.h"

#include "XSAMD5xE5xSleep.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSAMD5XE5XSLEEP::XSAMD5XE5XSLEEP()
* @brief      Constructor
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XSAMD5XE5XSLEEP::XSAMD5XE5XSLEEP()
{

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSAMD5XE5XSLEEP::~XSAMD5XE5XSLEEP()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XSAMD5XE5XSLEEP::~XSAMD5XE5XSLEEP()
{

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSAMD5XE5XSLEEP::Seconds(int seconds)
* @brief      Seconds
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  seconds :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XSAMD5XE5XSLEEP::Seconds(int seconds)
{
  for(int c=0; c<seconds; c++)
    {
      delay_ms(1000);
    }
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSAMD5XE5XSLEEP::MilliSeconds(int milliseconds)
* @brief      MilliSeconds
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  milliseconds :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XSAMD5XE5XSLEEP::MilliSeconds(int milliseconds)
{
  delay_ms(milliseconds);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSAMD5XE5XSLEEP::MicroSeconds(int microseconds)
* @brief      MicroSeconds
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  microseconds :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XSAMD5XE5XSLEEP::MicroSeconds(int microseconds)
{
  delay_us(microseconds);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSAMD5XE5XSLEEP::NanoSeconds(int nanoseconds)
* @brief      NanoSeconds
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  nanoseconds :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XSAMD5XE5XSLEEP::NanoSeconds(int nanoseconds)
{

}




