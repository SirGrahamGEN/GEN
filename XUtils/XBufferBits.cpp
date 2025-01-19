/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XBufferBits.cpp
* 
* @class      XBUFFERBITS
* @brief      eXtended Utils Reads a bit stream from a xbuffer
* @ingroup    XUTILS
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

#include "XBufferBits.h"

#include "XBuffer.h"

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
* @fn         XBUFFERBITS::XBUFFERBITS(XBUFFER* xbuffer)
* @brief      Constructor of class
* @ingroup    XUTILS
*
* @param[in]  xbuffer : buffer of origin
*
* --------------------------------------------------------------------------------------------------------------------*/
XBUFFERBITS::XBUFFERBITS(XBUFFER* xbuffer)
{
  Clean();

  this->xbuffer = xbuffer;
  this->p = xbuffer->Get();
  this->bits_left = 8;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBUFFERBITS::~XBUFFERBITS()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XBUFFERBITS::~XBUFFERBITS()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFERBITS::IsByteAligned()
* @brief      Is byte aligned
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFERBITS::IsByteAligned()
{
  return (bits_left == 8);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFERBITS::IsEOF()
* @brief      Is EOF
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFERBITS::IsEOF()
{
  return p >= (xbuffer->Get()+xbuffer->GetSize());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XBUFFERBITS::IsOverrun()
* @brief      Is overrun
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XBUFFERBITS::IsOverrun()
{
  return (p >= (xbuffer->Get()+xbuffer->GetSize())) && (bits_left < 8);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XBUFFERBITS::GetBytePosition()
* @brief      Get byte position
* @ingroup    XUTILS
*
* @return     XDWORD : position byte into buffer
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XBUFFERBITS::GetBytePosition()
{
  return (XDWORD)(xbuffer->Get() - p);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XBUFFERBITS::GetBitPosition()
* @brief      Get bit position
* @ingroup    XUTILS
*
* @return     XDWORD : position bit into buffer
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XBUFFERBITS::GetBitPosition()
{
  return 8 - bits_left;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XBUFFERBITS::SetPosition(XDWORD index, XDWORD bitindex)
* @brief      Set position
* @ingroup    XUTILS
*
* @param[in]  index : index into buffer
* @param[in]  bitindex : bit index into buffer
*
* --------------------------------------------------------------------------------------------------------------------*/
void XBUFFERBITS::SetPosition(XDWORD index, XDWORD bitindex)
{
  p = xbuffer->Get() + index;
  bits_left = 8 - ((bitindex >= 8) ? 7 : 0); // zero base index, can't be 8
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XBUFFERBITS::SkipU1()
* @brief      Skip U1
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XBUFFERBITS::SkipU1()
{
  bits_left--;

  if(bits_left == 0)
    {
      p++;
      bits_left = 8;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XBUFFERBITS::PeekU1()
* @brief      Peek U1
* @ingroup    XUTILS
*
* @return     XDWORD : bit peek.
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XBUFFERBITS::PeekU1()
{
  XDWORD r = 0;

  if(!IsEOF())
    {
      r = ((*(p)) >> ( bits_left - 1 )) & 0x01;
    }

  return r;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XBUFFERBITS::ReadU1()
* @brief      Read U1
* @ingroup    XUTILS
*
* @return     XDWORD : Read U1
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XBUFFERBITS::ReadU1()
{
  XDWORD r = 0;

  bits_left--;

  if (! IsEOF())
    {
      r = ((*(p)) >> bits_left) & 0x01;
    }

  if (bits_left == 0)
    {
      p++;
      bits_left = 8;
    }

  return r;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XBUFFERBITS::SkipU(XDWORD n)
* @brief      Skip u
* @ingroup    XUTILS
*
* @param[in]  n : n bits
*
* --------------------------------------------------------------------------------------------------------------------*/
void XBUFFERBITS::SkipU(XDWORD n)
{
  XDWORD i;
  for(i = 0; i < n; i++)
    {
      SkipU1();
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XBUFFERBITS::PeekU(XDWORD n)
* @brief      Peek u
* @ingroup    XUTILS
*
* @param[in]  n : n bits
*
* @return     XDWORD : n bits Peek (max 32 bits)
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XBUFFERBITS::PeekU(XDWORD n)
{
  XBYTE* orig_byte = p;
  XDWORD origin_bits_left = bits_left;

  XDWORD r = 0;

  r = ReadU(n);

  p = orig_byte;
  bits_left = origin_bits_left;

  return r;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XBUFFERBITS::ReadU(XDWORD n)
* @brief      Read u
* @ingroup    XUTILS
*
* @param[in]  n : n bits
*
* @return     XDWORD : n bits read (max 32 bits)
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XBUFFERBITS::ReadU(XDWORD n)
{
  XDWORD r = 0;
  XDWORD i;
  for (i = 0; i < n; i++)
    {
      r |= ( ReadU1() << ( n - i - 1 ) );
    }

  return r;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XBUFFERBITS::ReadUE()
* @brief
* @ingroup    XUTILS
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XBUFFERBITS::ReadUE()
{
  XDWORD r = 0;
  int i = 0;

  while( (ReadU1() == 0) && (i < 32) && (!IsEOF()) )
    {
      i++;
    }

  r = ReadU(i);
  r += (1 << i) - 1;

  return r;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XBUFFERBITS::ReadSE()
* @brief      Read SE
* @ingroup    XUTILS
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XBUFFERBITS::ReadSE()
{
  int r = ReadUE();
  if (r & 0x01)
    {
      r = (r+1)/2;
    }
  else
    {
      r = -(r/2);
    }

  return r;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XBUFFERBITS::WriteU1(XDWORD v)
* @brief      Write U1
* @ingroup    XUTILS
*
* @param[in]  v : bit to write
*
* --------------------------------------------------------------------------------------------------------------------*/
void XBUFFERBITS::WriteU1(XDWORD v)
{
  bits_left--;

  if(! IsEOF())
    {
      // FIXME this is slow, but we must clear bit first
      // is it better to memset(0) the whole buffer during bs_init() instead?
      // if we don't do either, we introduce pretty nasty bugs
      (*(p)) &= ~(0x01 << bits_left);
      (*(p)) |= ((v & 0x01) << bits_left);
    }

  if(bits_left == 0)
    {
      p++;
      bits_left = 8;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XBUFFERBITS::WriteU(XDWORD n, XDWORD v)
* @brief      Write u
* @ingroup    XUTILS
*
* @param[in]  n : n bits
* @param[in]  v : bits to write
*
* --------------------------------------------------------------------------------------------------------------------*/
void XBUFFERBITS::WriteU(XDWORD n, XDWORD v)
{
  XDWORD i;
  for(i = 0; i < n; i++)
    {
      WriteU1((v >> ( n - i - 1 ))&0x01);
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XBUFFERBITS::WriteUE(XDWORD v)
* @brief
* @ingroup    XUTILS
*
* @param[in]  v :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XBUFFERBITS::WriteUE(XDWORD v)
{
  static const int len_table[256] =
  {
    1,
    1,
    2,2,
    3,3,3,3,
    4,4,4,4,4,4,4,4,
    5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
    6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
    6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
    7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
    7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
    7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
    7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  };

  XDWORD len;

  if (v == 0)
    {
      WriteU1(1);
    }
  else
    {
      v++;

      if (v >= 0x01000000)
        {
          len = 24 + len_table[ v >> 24 ];
        }
      else if(v >= 0x00010000)
        {
          len = 16 + len_table[ v >> 16 ];
        }
      else if(v >= 0x00000100)
        {
          len =  8 + len_table[ v >>  8 ];
        }
      else
        {
          len = len_table[ v ];
        }

      WriteU(2*len-1, v);
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XBUFFERBITS::WriteSE(int v)
* @brief
* @ingroup    XUTILS
*
* @param[in]  v :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XBUFFERBITS::WriteSE(int v)
{
  if (v <= 0)
    {
      WriteUE(-v*2);
    }
    else
    {
      WriteUE(v*2 - 1);
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XBUFFERBITS::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XBUFFERBITS::Clean()
{
  xbuffer     = NULL;
  p           = NULL;
  bits_left   = 0;
}


#pragma endregion

