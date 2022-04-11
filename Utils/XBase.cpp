/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XBase.cpp
*
* @class      XBASE
* @brief      Basic functions and defines
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @copyright  Copyright(c) 2008 - 2016 GEN Group.
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

#include <math.h>

#include "XBase.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBASE::XBASE()
* @brief      Constructor
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XBASE::XBASE()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBASE::~XBASE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XBASE::~XBASE()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XBASE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XBASE::Clean()
{

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         double Truncate(double value)
* @brief      Trucate double
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  value : double to truncate
*
* @return     double : double truncate
*
*---------------------------------------------------------------------------------------------------------------------*/
double Truncate(double value)
{
  double truncate = 0;

  modf(value, &truncate);

  return truncate;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         double Fraction(double value)
* @brief      Return the fractional part of double
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  value : double value to obtain fractional part
*
* @return     double : fractional part of value
*
*---------------------------------------------------------------------------------------------------------------------*/
double Fraction(double value)
{
  double truncate = 0;

  return modf(value, &truncate);
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         float RoundOff(float value, XBYTE prec)
* @brief      oundOff
* @ingroup    UTILS
* 
* @author     Abraham J. Velez 
* @date       15/03/2022 9:51:11
* 
* @param[in]  value : 
* @param[in]  prec : 
* 
* @return     float :
* 
* ---------------------------------------------------------------------------------------------------------------------*/
float RoundOff(float value, XBYTE prec)
{
  #ifdef BUILDER
  return 0.0f;
  #else
  double pow_10 = pow(10.0f, (double)prec);
  return (float)(round(value * pow_10) / pow_10);
  #endif
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         double RoundOff(double value, XBYTE prec)
* @brief      oundOff
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       15/03/2022 9:52:36
*
* @param[in]  value :
* @param[in]  prec :
*
* @return     double :
*
* ---------------------------------------------------------------------------------------------------------------------*/
double RoundOff(double value, XBYTE prec)
{
  #ifdef BUILDER
  return 0.0f;
  #else
  double pow_10 = pow(10.0f, (float)prec);
  return round(value * pow_10) / pow_10;
  #endif
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE High_WORD(XWORD data)
* @brief      igh_WORD
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  data :
*
* @return     XBYTE :
*
*---------------------------------------------------------------------------------------------------------------------*/
XBYTE High_WORD(XWORD data)
{
  return ((data & 0xFF00) >> 8);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWORD High_DWORD(XDWORD data)
* @brief      igh_DWORD
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  data :
*
* @return     XWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XWORD High_DWORD(XDWORD data)
{
  return ((data & 0xFFFF0000) >> 16);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD High_QWORD(XQWORD data)
* @brief      igh_QWORD
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  data :
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD High_QWORD(XQWORD data)
{
  return ((data & 0xFFFFFFFF00000000) >> 32);
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE Low_WORD(XWORD data)
* @brief      ow_WORD
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  data :
*
* @return     XBYTE :
*
*---------------------------------------------------------------------------------------------------------------------*/
XBYTE Low_WORD(XWORD  data)
{
  return (XBYTE)(data & 0x00FF);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWORD Low_DWORD(XDWORD data)
* @brief      ow_DWORD
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  data :
*
* @return     XWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XWORD Low_DWORD(XDWORD data)
{
  return (XWORD)(data & 0x0000FFFF);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD Low_QWORD(XQWORD data);
* @brief      ow_QWORD
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  data) :
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD Low_QWORD(XQWORD data)
{
  return (XDWORD)(data & 0x00000000FFFFFFFF);
}





/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWORD SwapWORD(XWORD data)
* @brief      Return the swap of word (2 bytes) hi-lo  > lo-hi
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  data : word to swap
*
* @return     XWORD : word swaped
*
*---------------------------------------------------------------------------------------------------------------------*/
XWORD SwapWORD(XWORD data)
{
  const XWORD hi = (XWORD)((data&0xFF00)>>8);
  const XWORD lo = (XWORD)((data&0x00FF)<<8);

  return (XWORD)(hi|lo);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD SwapDWORD(XDWORD data)
* @brief      Swap double word (4 bytes) hi1 lo1 h2 lo2 >  lo2 hi2 lo1 hi1
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  data :  dword to swap
*
* @return     XDWORD : double word swaped
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD SwapDWORD(XDWORD data)
{
  const XDWORD hi1 = (data&0xFF000000)>>24;
  const XDWORD lo1 = (data&0x00FF0000)>>8;
  const XDWORD hi2 = (data&0x0000FF00)<<8;
  const XDWORD lo2 = (data&0x000000FF)<<24;

  return (hi1|lo1|hi2|lo2);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XQWORD SwapQWORD(XQWORD data)
* @brief      Swap quad word (8 bytes) hi1 lo1 h2 lo2 hi3 lo3 h4 lo4  > lo3 hi3 lo4 hi4 lo2 hi2 lo1 hi1
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  data : quad word to swap
*
* @return     XQWORD : quad word swaped
*
*---------------------------------------------------------------------------------------------------------------------*/
XQWORD SwapQWORD(XQWORD data)
{
  const XQWORD hi1 = (data&0xFF00000000000000ULL) >> (24 + 32);
  const XQWORD lo1 = (data&0x00FF000000000000ULL) >> ( 8 + 32);
  const XQWORD hi2 = (data&0x0000FF0000000000ULL) >> (     24);
  const XQWORD lo2 = (data&0x000000FF00000000ULL) >> (      8);

  const XQWORD hi3 = (data&0x00000000FF000000ULL) << (      8);
  const XQWORD lo3 = (data&0x0000000000FF0000ULL) << (     24);
  const XQWORD hi4 = (data&0x000000000000FF00ULL) << ( 8 + 32);
  const XQWORD lo4 = (data&0x00000000000000FFULL) << (24 + 32);

  return (hi1|lo1|hi2|lo2|hi3|lo3|hi4|lo4);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float RoundFloat(float x)
* @brief      Round float
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  x : float to round
*
* @return     float : rounded float
*
*---------------------------------------------------------------------------------------------------------------------*/
float RoundFloat(float x)
{
  return float(x >= 0.0f ? floor(x + 0.5f) : ceil(x - 0.5f));
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XQWORD DWORDToBCD(XDWORD dword)
* @brief      Convert double word to BCD
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  dword : double word to convert
*
* @return     XQWORD : Quad word converted BCD
*
*---------------------------------------------------------------------------------------------------------------------*/
XQWORD DWORDToBCD(XDWORD dword)
{
  XQWORD shift  = 16;
  XQWORD result = (dword % 10);

  while((dword = (dword/10)))
    {
      result += (dword % 10) * shift;
      shift *= 16; // weirdly, it's not possible to left shift more than 32 bits
    }

  return result;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD BCDToDWORD(XQWORD bcd)
* @brief      Convert BCD to double word
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  bcd : BCD to convert
*
* @return     XDWORD : doble word converted
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD BCDToDWORD(XQWORD bcd)
{
  XQWORD mask = 0x000f;
  XQWORD pwr  = 1;
  XQWORD i    = (bcd & mask);

  while((bcd = (bcd >> 4)))
    {
      pwr *= 10;
      i += (bcd & mask) * pwr;
    }

  return (XDWORD)i;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE RotateBitLeft(XBYTE byte)
* @brief      otateBitLeft
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  byte :
*
* @return     XBYTE :
*
*---------------------------------------------------------------------------------------------------------------------*/
XBYTE RotateBitLeft(XBYTE byte)
{
  return (byte << 1) | (byte >> 7);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE RotateBitRight(XBYTE byte)
* @brief      otateBitRight
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  byte :
*
* @return     XBYTE :
*
*---------------------------------------------------------------------------------------------------------------------*/
XBYTE RotateBitRight(XBYTE byte)
{
  return (byte >> 1) | (byte << 7);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE RotateBitReverse(XBYTE byte)
* @brief      otateBitReverse
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  byte :
*
* @return     XBYTE :
*
*---------------------------------------------------------------------------------------------------------------------*/
XBYTE RotateBitReverse(XBYTE byte)
{
  byte = (byte & 0xF0) >> 4 | (byte & 0x0F) << 4;
  byte = (byte & 0xCC) >> 2 | (byte & 0x33) << 2;
  byte = (byte & 0xAA) >> 1 | (byte & 0x55) << 1;

  return byte;
}



