/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XFString.cpp
* 
* @class      XFSTRING
* @brief      Unicode Fast String class
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

#include "XFString.h"

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
* @fn         XFSTRING::XFSTRING()
* @brief      Constructor of class
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XFSTRING::XFSTRING(): XSTRING()
{

}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFSTRING::XFSTRING(int n) : XSTRING(n)
* @brief      Constructor of class
* @ingroup    XUTILS
*
* @param[in]  n :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFSTRING::XFSTRING(int n) : XSTRING(n)
{

}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFSTRING::XFSTRING(const XCHAR* string) : XSTRING(string)
* @brief      Constructor of class
* @ingroup    XUTILS
*
* @param[in]  string :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFSTRING::XFSTRING(const XCHAR* string) : XSTRING(string)
{

}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFSTRING::XFSTRING(XCHAR* string) : XSTRING(string)
* @brief      Constructor of class
* @ingroup    XUTILS
*
* @param[in]  string :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFSTRING::XFSTRING(XCHAR* string) : XSTRING(string)
{

}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFSTRING::XFSTRING(const char* string) : XSTRING(string)
* @brief      Constructor of class
* @ingroup    XUTILS
*
* @param[in]  string :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFSTRING::XFSTRING(const char* string) : XSTRING(string)
{

}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFSTRING::XFSTRING(XSTRING& string) : XSTRING(string)
* @brief      Constructor of class
* @ingroup    XUTILS
*
* @param[in]  string :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFSTRING::XFSTRING(XSTRING& string) : XSTRING(string)
{

}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XFSTRING::Fast_ConvertToInt(int index)
* @brief      Fast convert to int
* @ingroup    XUTILS
*
* @param[in]  index :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XFSTRING::Fast_ConvertToInt(int index)
{
  int result = 0;

  swscanf(&text[index], __L("%d"), &result);
  return result;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XFSTRING::Fast_ConvertToDWord(int index)
* @brief      Fast convert to D word
* @ingroup    XUTILS
*
* @param[in]  index :
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XFSTRING::Fast_ConvertToDWord(int index)
{
  XDWORD result = 0;

  swscanf(&text[index], __L("%u"), &result);

  return result;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XQWORD XFSTRING::Fast_ConvertToQWord(int index)
* @brief      Fast convert to Q word
* @ingroup    XUTILS
*
* @param[in]  index :
*
* @return     XQWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XQWORD XFSTRING::Fast_ConvertToQWord(int index)
{
  XQWORD result = 0;

  swscanf(&text[index], __L("%lld"), &result);

  return result;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XQWORDSIG XFSTRING::Fast_ConvertToSQWord(int index)
* @brief      Fast convert to SQ word
* @ingroup    XUTILS
*
* @param[in]  index :
*
* @return     XQWORDSIG :
*
* --------------------------------------------------------------------------------------------------------------------*/
XQWORDSIG XFSTRING::Fast_ConvertToSQWord(int index)
{
  XQWORDSIG result = 0;

  swscanf(&text[index], __L("%lld"), &result);

  return result;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float XFSTRING::Fast_ConvertToFloat(int index)
* @brief      Fast convert to float
* @ingroup    XUTILS
*
* @param[in]  index :
*
* @return     float :
*
* --------------------------------------------------------------------------------------------------------------------*/
float XFSTRING::Fast_ConvertToFloat(int index)
{
  float result = 0;

  swscanf(&text[index], __L("%f"), &result);

  return result;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         double XFSTRING::Fast_ConvertToDouble(int index)
* @brief      Fast convert to double
* @ingroup    XUTILS
*
* @param[in]  index :
*
* @return     double :
*
* --------------------------------------------------------------------------------------------------------------------*/
double XFSTRING::Fast_ConvertToDouble(int index)
{
  double result = 0;

  swscanf(&text[index], __L("%lf"), &result);

  return result;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFSTRING::Fast_AddCharacter(XCHAR character)
* @brief      Fast add character
* @ingroup    XUTILS
*
* @param[in]  character :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFSTRING::Fast_AddCharacter(XCHAR character)
{
  if (!ReAllocBuffer(size + 1)) return false;

  memcpy(&text[size - 1], &character, sizeof(XCHAR));

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFSTRING::Fast_Empty()
* @brief      Fast empty
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFSTRING::Fast_Empty()
{
  if(!size) return true;

  memset(&text[0], 0, size * sizeof(XCHAR));
  size = 0;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFSTRING::operator = (const char* string)
* @brief      operator = 
* @ingroup    XUTILS
*
* @param[in]  string :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFSTRING::operator =  (const char* string)
{
  Set(string);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFSTRING::operator = (const XCHAR* string)
* @brief      operator = 
* @ingroup    XUTILS
*
* @param[in]  string :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFSTRING::operator =  (const XCHAR* string)
{
  Set(string);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFSTRING::operator = (const XSTRING& string)
* @brief      operator = 
* @ingroup    XUTILS
*
* @param[in]  string :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFSTRING::operator =  (const XSTRING& string)
{
  Set(string);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFSTRING::operator = (XWORD* string)
* @brief      operator = 
* @ingroup    XUTILS
*
* @param[in]  string :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFSTRING::operator =  (XWORD* string)
{
  Set(string);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFSTRING::operator = (XBUFFER& string)
* @brief      operator = 
* @ingroup    XUTILS
*
* @param[in]  string :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFSTRING::operator =  (XBUFFER& string)
{
  Set(string);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFSTRING::operator += (const char* string)
* @brief      operator += 
* @ingroup    XUTILS
*
* @param[in]  string :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFSTRING::operator += (const char* string)
{
  Add(string);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFSTRING::operator += (const XCHAR* string)
* @brief      operator += 
* @ingroup    XUTILS
*
* @param[in]  string :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFSTRING::operator += (const XCHAR* string)
{
  Add(string);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFSTRING::operator += (XSTRING& string)
* @brief      operator += 
* @ingroup    XUTILS
*
* @param[in]  string :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFSTRING::operator += (XSTRING& string)
{
  Add(string);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFSTRING::operator += (XCHAR character)
* @brief      operator += 
* @ingroup    XUTILS
*
* @param[in]  character :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFSTRING::operator += (XCHAR character)
{
  Add(character);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFSTRING::operator < (const XSTRING& string) const
* @brief      operator < 
* @ingroup    XUTILS
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFSTRING::operator <  (const XSTRING& string) const
{
  return (bool)(Compare(string) == -1);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFSTRING::operator > (XSTRING& string)
* @brief      operator > 
* @ingroup    XUTILS
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFSTRING::operator >  (XSTRING& string)
{
  return (bool)(Compare(string) == 1);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFSTRING::operator <= (XSTRING& string)
* @brief      operator <= 
* @ingroup    XUTILS
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFSTRING::operator <= (XSTRING& string)
{
  return (bool)(Compare(string) != 1);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFSTRING::operator >= (XSTRING& string)
* @brief      operator >= 
* @ingroup    XUTILS
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFSTRING::operator >= (XSTRING& string)
{
  return (bool)(Compare(string) != -1);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFSTRING::operator == (const XSTRING& string) const
* @brief      operator == 
* @ingroup    XUTILS
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFSTRING::operator == (const XSTRING& string) const
{
  return (bool)(Compare(string) == 0);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFSTRING::operator != (XSTRING& string)
* @brief      operator != 
* @ingroup    XUTILS
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFSTRING::operator != (XSTRING& string)
{
  return (bool)(Compare(string) != 0);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XCHAR XFSTRING::operator [] (int position)
* @brief      operator [] 
* @ingroup    XUTILS
*
* @param[in]  position :
*
* @return     XCHAR :
*
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR XFSTRING::operator [] (int position)
{
  return text[position];
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XFSTRING::Scan(const XCHAR* mask, ...)
* @brief      Scan
* @ingroup    XUTILS
*
* @param[in]  mask :
* @param[in]  ... :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XFSTRING::Scan(const XCHAR* mask, ...)
{
  va_list ap;

  va_start(ap, mask);
  int n = vswscanf(this->text, mask, ap);
  va_end(ap);

  return n;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFSTRING::Explode(XCHAR token, XVECTOR<XFSTRING*>* receive)
* @brief      Explode
* @ingroup    XUTILS
*
* @param[in]  token :
* @param[in]  receive :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFSTRING::Explode(XCHAR token, XVECTOR<XFSTRING*>* receive)
{
  int start = 0;

  do{ int end = this->FindCharacter(token, start);
      if(end == NOTFOUND) end = size;

      if((end - start) > 0)
        {
          XFSTRING* tok = new XFSTRING();
          if(!tok) return false;

          Copy(start, end, (*tok));

          if(!receive->Add(tok))
            {
              delete(tok);
              return false;
            }
        }

      start = end + 1;

    } while(start < (int)size);

  return true;
}


#pragma endregion

