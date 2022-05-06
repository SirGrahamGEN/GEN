/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XString.cpp
*
* @class      XSTRING
* @brief      eXtended Unicode String class
* @ingroup    UTILS
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


#if defined(APPMODE_API_LIB_EXPORT_ACTIVE) || !defined(APPMODE_API_LIB_ACTIVE)

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include "XBase.h"
#include "XBuffer.h"
#include "XTrace.h"

#include "XString.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

XCHAR XSTRING::table64bits[XSTRING_SIZETABLE64BITS];
bool  XSTRING::istable64bitsinit = false;

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING::XSTRING()
* @brief      Constructor
* @ingroup    UTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING::XSTRING()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING::XSTRING(XDWORD size)
* @brief      Constructor
* @ingroup    UTILS
*
* @param[in]  XDWORD :
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING::XSTRING(XDWORD size)
{
  Clean();

  ReAllocBuffer(size);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING::XSTRING(const char* string)
* @brief      Constructor
* @ingroup    UTILS
*
* @param[in]  :
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING::XSTRING(const char* string)
{
  Clean();

  Set(string);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING::XSTRING(const XCHAR* string)
* @brief      Constructor
* @ingroup    UTILS
*
* @param[in]  :
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING::XSTRING(const XCHAR* string)
{
  Clean();

  Set(string);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING::XSTRING(const XCHAR* string,XDWORD size)
* @brief      Constructor
* @ingroup    UTILS
*
* @param[in]  :
* @param[in]  XDWORD :
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING::XSTRING(const XCHAR* string,XDWORD size)
{
  Clean();

  Set(string,size);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING::XSTRING(const XSTRING& string)
* @brief      Constructor
* @ingroup    UTILS
*
* @param[in]  const :
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING::XSTRING(const XSTRING& string)
{
  Clean();

  Set(string);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING::XSTRING(XWORD* string)
* @brief      Constructor
* @ingroup    UTILS
*
* @param[in]  XWORD* :
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING::XSTRING(XWORD* string)
{
  Clean();

  Set(string);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING::~XSTRING()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    UTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING::~XSTRING()
{
  FreeBuffer();

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XCHAR* XSTRING::Get() const
* @brief      Get
* @ingroup    UTILS
*
* @param[in]  cons :
*
* @return     XCHAR* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR* XSTRING::Get() const
{
  if(!text) return __L("");

  return text;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XSTRING::GetSize() const
* @brief      GetSize
* @ingroup    UTILS
*
* @param[in]  cons :
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XSTRING::GetSize() const
{
  if(!text) return 0;

  return size;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XSTRING::GetSize(const XCHAR* string)
* @brief      GetSize
* @ingroup    UTILS
*
* @param[in]  XCHAR* string :
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XSTRING::GetSize(const XCHAR* string)
{
  XDWORD size = 0;

  while(string[size])
    {
      size++;
    }

  return size;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XSTRING::GetSize(XWORD* string)
* @brief      GetSize
* @ingroup    UTILS
*
* @param[in]  string :
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XSTRING::GetSize(XWORD* string)
{
  XDWORD size = 0;

  while(string[size])
    {
      size++;
    }

  return size;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::IsOEM()
* @brief      IsOEM
* @ingroup    UTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::IsOEM()
{
  for(int c=0;c<(int)size;c++)
    {
      if((text[c]<0x20) || (text[c]>0x7F)) return false;
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::CreateOEM(char*& _textOEM) const
* @brief      CreateOEM
* @ingroup    UTILS
*
* @param[in]  _textOEM) cons :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::CreateOEM(char*& _textOEM) const
{
  XDWORD sizeOEM = GetSize();

  _textOEM = new char[sizeOEM+1];
  if(!_textOEM) return false;

  for(int c=sizeOEM-1;c>=0;c--)
    {
      _textOEM[c] = (XBYTE)text[c];
    }

  _textOEM[sizeOEM]=0;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSTRING::DeleteOEM(char* text)
* @brief      DeleteOEM
* @ingroup    UTILS
*
* @param[in]  text : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::DeleteOEM(char* text)
{
  if(!text) return false;

  delete [] text; 

  return true;                                                 
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::CreateNormalize(XWORD*& _textnormalize, bool inverse)
* @brief      CreateNormalize
* @ingroup    UTILS
*
* @param[in]  _textnormalize :
* @param[in]  inverse :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::CreateNormalize(XWORD*& _textnormalize, bool inverse)
{
  XDWORD sizenormalize = GetSize()+1;

  _textnormalize = new XWORD[sizenormalize];
  if(!_textnormalize) return false;

  memset(_textnormalize, 0, (sizenormalize)*sizeof(XWORD));

  if(sizenormalize>1)
    {
      for(XDWORD c=0; c<sizenormalize; c++)
        {
          if(inverse)
            {
              _textnormalize[c]  = (text[c]>>8);
              _textnormalize[c] |= ((text[c]&0x00FF)<<8);

            }
           else
            {
              _textnormalize[c] = (XWORD)text[c];
            }
        }
    }

  return true;

}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSTRING::DeleteNormalize(XWORD*& _textnormalize)
* @brief      DeleteNormalize
* @ingroup    UTILS
*
* @param[in]  _textnormalize : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::DeleteNormalize(XWORD*& _textnormalize)
{
  if(!_textnormalize) return false;

  delete [] _textnormalize;
  
  return true; 
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::Set(XDWORD size)
* @brief      Set
* @ingroup    UTILS
*
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::Set(XDWORD size)
{
  if(!ReAllocBuffer(size)) return false;

  FillChar(0);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::Set(const char* string)
* @brief      Set
* @ingroup    UTILS
*
* @param[in]  char* string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::Set(const char* string)
{
  Empty();
  if(!string) return false;

  XDWORD tsize = (XDWORD)strlen(string);

  if(!ReAllocBuffer(tsize)) return false;

  if(tsize)
    {
      for(XDWORD c=0;c<tsize;c++)
        {
          text[c] = (XCHAR)string[c];
        }
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::Set(const XCHAR* string)
* @brief      Set
* @ingroup    UTILS
*
* @param[in]  XCHAR* string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::Set(const XCHAR* string)
{
  if(!string)
    {
      Empty();
      return false;
    }

  XDWORD c     = XSTRING::GetSize((XCHAR*)string);
  XDWORD tsize = c;

  if(tsize)
    {
      FreeBuffer();

      if(!ReAllocBuffer(tsize)) return false;

      memcpy(text, string, sizeof(XCHAR)*tsize);
    }
   else Empty();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::Set(const XCHAR* string, XDWORD size)
* @brief      Set
* @ingroup    UTILS
*
* @param[in]  XCHAR* string :
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::Set(const XCHAR* string, XDWORD size)
{
  Empty();
  if(!string) return false;

  XDWORD tsize = size;

  if(!tsize) Empty();

  if(!ReAllocBuffer(tsize)) return false;

  if(tsize)
    {
      memcpy(text, string, sizeof(XCHAR)*tsize);
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::Set(const XSTRING& string)
* @brief      Set
* @ingroup    UTILS
*
* @param[in]  XSTRING& string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::Set(const XSTRING& string)
{
  XDWORD tsize = string.GetSize();

  if(!tsize) Empty();

  if(!ReAllocBuffer(tsize)) return false;

  XCHAR* _text = string.Get();

  if(tsize)
    {
      memcpy(text, _text, sizeof(XCHAR)*tsize);
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::Set(XWORD* string)
* @brief      Set
* @ingroup    UTILS
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::Set(XWORD* string)
{
  if(!string)
    {
      Empty();
      return false;
    }

  XDWORD tsize = GetSize(string);
  if(!tsize) Empty();

  if(!ReAllocBuffer(tsize)) return false;

  if(tsize)
    {
      for(XDWORD c=0;c<tsize;c++)
        {
          text[c] = (XCHAR)string[c];
        }
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::Set(XCHAR character)
* @brief      Set
* @ingroup    UTILS
*
* @param[in]  character :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::Set(XCHAR character)
{
  XCHAR characters[2] = { 0, 0};

  characters[0] = character;

  return Set(characters);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::Set(XCHAR* str1, const XCHAR* str2)
* @brief      Set
* @ingroup    UTILS
*
* @param[in]  str1 :
* @param[in]  XCHAR* str2 :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::Set(XCHAR* str1, const XCHAR* str2)
{
  if(!str1) return false;
  if(!str2) return false;

  int c=0;
  while(str2[c])
    {
      str1[c] = str2[c];
      c++;
    }

  str1[c] = 0;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::Set(const XBYTE* buffer, XDWORD size)
* @brief      Set
* @ingroup    UTILS
*
* @param[in]  XBYTE* buffer :
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::Set(const XBYTE* buffer, XDWORD size)
{
  Empty();
  if(!buffer) return false;

  XDWORD tsize = size;

  if(!tsize) Empty();

  if(!ReAllocBuffer(tsize)) return false;

  if(tsize)
    {
      for(int c=0;c<(int)tsize;c++)
        {
          text[c] = buffer[c];
        }
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::Set(const XDWORD* buffer, XDWORD size)
* @brief      Set
* @ingroup    UTILS
*
* @param[in]  XDWORD* buffer :
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::Set(const XDWORD* buffer, XDWORD size)
{
  Empty();

  if(!buffer) return false;

  XDWORD tsize = size;

  if(!tsize) Empty();

  if(!ReAllocBuffer(tsize)) return false;

  if(tsize)
    {
      for(int c = 0; c<(int)tsize; c++)
        {
          text[c] = buffer[c];
        }
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::Set(XBUFFER& buffer)
* @brief      Set
* @ingroup    UTILS
*
* @param[in]  buffer :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::Set(XBUFFER& buffer)
{
  return Set(buffer.Get(), buffer.GetSize());
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::Add(const char* string)
* @brief      Add
* @ingroup    UTILS
*
* @param[in]  char* string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::Add(const char* string)
{
  if(!string)    return false;
  if(!string[0]) return false;

  XDWORD tsize  = (XDWORD)strlen(string);
  XDWORD ssize  = GetSize();
  XDWORD  ini;

  if(!tsize) return false;

  ini = 0;

  if(text)
    {
      while(text[ini])
        {
          ini++;
          if(ini>=(ssize+tsize))
            {
              ini--;
              break;
            }
        }
    }

  if(!ReAllocBuffer(ssize+tsize)) return false;

  int d=0;
  for(XDWORD c=0;c<tsize;c++)
    {
      text[c+ini] = (XCHAR)string[d];
      d++;
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::Add(const XCHAR* string)
* @brief      Add
* @ingroup    UTILS
*
* @param[in]  XCHAR* string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::Add(const XCHAR* string)
{
  if(!string)     return false;
  if(!string[0]) return false;

  XSTRING* xstring = new XSTRING(string);
  if(!xstring) return false;

  Add((*xstring));

  delete xstring;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::Add(XSTRING& string)
* @brief      Add
* @ingroup    UTILS
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::Add(XSTRING& string)
{
  XDWORD tsize = string.GetSize();
  XDWORD ssize = GetSize();
  XDWORD ini;

  if(string.IsEmpty()) return false;

  if(string.Get())
    {
      if(!string.Get()[0]) return false;
    }

  if(!tsize) return false;

  ini = 0;

  if(text)
    {
      while(text[ini])
        {
          ini++;
          if(ini>=(ssize+tsize))
            {
              ini--;
              break;
            }
        }
  }

  if(!ReAllocBuffer(ssize+tsize)) return false;

  memcpy(&text[ini], string.Get(), sizeof(XCHAR)*tsize);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::Add(XCHAR character)
* @brief      Add
* @ingroup    UTILS
*
* @param[in]  character :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::Add(XCHAR character)
{
  XCHAR characters[2] = { 0, 0};

  characters[0] = character;

  return Add(characters);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::Add(XCHAR* str1, const XCHAR* str2)
* @brief      Add
* @ingroup    UTILS
*
* @param[in]  str1 :
* @param[in]  XCHAR* str2 :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::Add(XCHAR* str1, const XCHAR* str2)
{
  if(!str1) return false;
  if(!str2) return false;

  XDWORD sizestr1 = XSTRING::GetSize(str1);
  int c        = 0;

  while(str2[c])
    {
      str1[sizestr1+c] = str2[c];
      c++;
    }

  str1[sizestr1+c] = 0;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::Add(const XBYTE* buffer, XDWORD size)
* @brief      Add
* @ingroup    UTILS
*
* @param[in]  XBYTE* buffer :
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::Add(const XBYTE* buffer, XDWORD size)
{
  int ini   = this->size;
  int tsize = this->size + size;

  AdjustSize(tsize);

  for(XDWORD c=0; c<size; c++)
    {
      text[ini+c] = (XCHAR)buffer[c];
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::Add(XBUFFER& buffer)
* @brief      Add
* @ingroup    UTILS
*
* @param[in]  buffer :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::Add(XBUFFER& buffer)
{
  return Add(buffer.Get(), buffer.GetSize());
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSTRING::operator = (const char* string)
* @brief      operator =
* @ingroup    UTILS
*
* @param[in]  char* string :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XSTRING::operator =  (const char* string)
{
  Set(string);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSTRING::operator = (const XCHAR* string)
* @brief      operator =
* @ingroup    UTILS
*
* @param[in]  XCHAR* string :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XSTRING::operator =  (const XCHAR* string)
{
  Set(string);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSTRING::operator = (XSTRING& string)
* @brief      operator =
* @ingroup    UTILS
*
* @param[in]  XSTRING& string :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XSTRING::operator =  (const XSTRING& string)
{
  Set(string);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSTRING::operator = (XWORD* string)
* @brief      operator =
* @ingroup    UTILS
*
* @param[in]  string :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XSTRING::operator =  (XWORD* string)
{
  Set(string);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSTRING::operator = (XBUFFER& string)
* @brief      operator =
* @ingroup    UTILS
*
* @param[in]  string :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XSTRING::operator =  (XBUFFER& string)
{
  Set(string);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSTRING::operator += (const char* string)
* @brief      operator +=
* @ingroup    UTILS
*
* @param[in]  char* string :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XSTRING::operator += (const char* string)
{
  Add(string);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSTRING::operator += (const XCHAR* string)
* @brief      operator +=
* @ingroup    UTILS
*
* @param[in]  XCHAR* string :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XSTRING::operator += (const XCHAR* string)
{
  Add(string);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSTRING::operator += (XSTRING& string)
* @brief      operator +=
* @ingroup    UTILS
*
* @param[in]  string :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XSTRING::operator += (XSTRING& string)
{
  Add(string);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSTRING::operator += (XCHAR character)
* @brief      operator +=
* @ingroup    UTILS
*
* @param[in]  character :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XSTRING::operator += (XCHAR character)
{
  Add(character);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::operator < (XSTRING& string) const
* @brief      operator <
* @ingroup    UTILS
*
* @param[in]  XSTRING& string) cons :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::operator <  (const XSTRING& string) const
{
  return (bool)(Compare(string) == -1);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::operator > (XSTRING& string)
* @brief      operator >
* @ingroup    UTILS
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::operator >  (XSTRING& string)
{
  return (bool)(Compare(string) ==  1);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::operator <= (XSTRING& string)
* @brief      operator <=
* @ingroup    UTILS
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::operator <= (XSTRING& string)
{
  return (bool)(Compare(string) !=  1);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::operator >= (XSTRING& string)
* @brief      operator >=
* @ingroup    UTILS
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::operator >= (XSTRING& string)
{
  return (bool)(Compare(string) != -1);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::operator == (XSTRING& string)
* @brief      operator ==
* @ingroup    UTILS
*
* @param[in]  XSTRING& string) cons :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::operator == (const XSTRING& string) const
{
  return (bool)(Compare(string) ==  0);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::operator != (XSTRING& string)
* @brief      operator !=
* @ingroup    UTILS
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::operator != (XSTRING& string)
{
  return (bool)(Compare(string) !=  0);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XCHAR XSTRING::operator [] (int position)
* @brief      operator []
* @ingroup    UTILS
*
* @param[in]  position :
*
* @return     XCHAR :
*
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR XSTRING::operator [] (int position)
{
  if(IsEmpty())           return 0;
  if(position<0)          return text[0];
  if(position>=(int)size) return text[size-1];

  return text[position];
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::FillChar(XCHAR character)
* @brief      FillChar
* @ingroup    UTILS
*
* @param[in]  character :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::FillChar(XCHAR character)
{
  if(IsEmpty()) return false;

  for(XDWORD c=0;c<size;c++)
    {
      text[c] = character;
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::Empty()
* @brief      Empty
* @ingroup    UTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::Empty()
{
  if(IsEmpty()) return false;

  FreeBuffer();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::IsEmpty()
* @brief      IsEmpty
* @ingroup    UTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::IsEmpty()
{
  if((!text)||(!size)) return true;
  if(!text[0])         return true;

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::HaveCharacters()
* @brief      HaveCharacters
* @ingroup    UTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::HaveCharacters()
{
  if(IsEmpty()) return false;

  for(XDWORD c=0;c<size;c++)
    {
      if(!text[c]) break;
      if(!Character_IsNOT(text[c])) return true;
    }

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::HaveOnlyNumbers()
* @brief      HaveOnlyNumbers
* @ingroup    UTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::HaveOnlyNumbers()
{
  if(IsEmpty()) return false;

  for(XDWORD c=0;c<size;c++)
    {
      if(!text[c]) break;
      if(!Character_IsNumber(text[c])) return false;
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::DeleteCharacters(XDWORD index, XDWORD ncharacteres)
* @brief      DeleteCharacters
* @ingroup    UTILS
*
* @param[in]  index :
* @param[in]  ncharacteres :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::DeleteCharacters(XDWORD index, XDWORD ncharacteres)
{
  if(!ncharacteres)  return true;
  if(IsEmpty())      return false;

  if(index >= size)  return false;

  int nchar = ncharacteres;
  if((index + nchar) > size) nchar = (int)size-index;

  int c = index;
  while(text[c+nchar])
    {
      text[c] = text[c+nchar];
      c++;
    }
  text[c] = text[c + nchar];

  return ReAllocBuffer(size - nchar);
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSTRING::DeleteCharactersToEnd(XDWORD index)
* @brief      DeleteCharactersToEnd
* @ingroup    UTILS
*
* @param[in]  index : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::DeleteCharactersToEnd(XDWORD index)
{
  if(IsEmpty())      return false;

  if(index >= size)  return false;

  int nchar = (int)size-index;
  int c     = index;

  while(text[c+nchar])
    {
      text[c] = text[c+nchar];
      c++;
    }
  text[c] = text[c + nchar];

  return ReAllocBuffer(size - nchar);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::DeleteCharacter(XCHAR character,XSTRINGCONTEXT context)
* @brief      DeleteCharacter
* @ingroup    UTILS
*
* @param[in]  character :
* @param[in]  context :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::DeleteCharacter(XCHAR character,XSTRINGCONTEXT context)
{
  if(IsEmpty()) return false;

  switch(context)
    {
      case XSTRINGCONTEXT_FROM_FIRST  : { XDWORD n=0;
                                          while(character == text[n] && n<size)
                                            {
                                              n++;
                                            }
                                          if(n) DeleteCharacters(0,n);
                                        }
                                        break;

      case XSTRINGCONTEXT_TO_END      : { XDWORD n=size-1;
                                          while(character == text[n] && n)
                                            {
                                              n--;
                                            }

                                          if(size!=n+1)  ReAllocBuffer(n+1);
                                        }
                                        break;

      case XSTRINGCONTEXT_ALLSTRING   : { XDWORD c = 0;
                                          XDWORD a = 0;

                                          while (c < size)
                                            {
                                              while(text[c]==character)
                                                {
                                                  c++;
                                                }

                                              text[a] = text[c];
                                              c++;

                                              if(!text[a]) break;
                                              a++;
                                            }

                                          ReAllocBuffer(a);
                                          size = a;
                                        }
                                        break;
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::DeleteNoCharacters(XSTRINGCONTEXT context)
* @brief      DeleteNoCharacters
* @ingroup    UTILS
*
* @param[in]  context :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::DeleteNoCharacters(XSTRINGCONTEXT context)
{
  bool status = DeleteCharacter(__C('\x09'),context);

  if(status) status = DeleteCharacter(__C('\x0A'),context);
  if(status) status = DeleteCharacter(__C('\x0D'),context);
  if(status) status = DeleteCharacter(__C('\x20'),context);

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XSTRING::DeleteNoCharacters(XCHAR* n, int start, XSTRINGCONTEXT context)
* @brief      DeleteNoCharacters
* @ingroup    UTILS
*
* @param[in]  n :
* @param[in]  start :
* @param[in]  context :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XSTRING::DeleteNoCharacters(XCHAR* n, int start, XSTRINGCONTEXT context)
{
  int a= 0;

  XSTRING needle;
  needle.Set(n);

  if(!this->GetSize()) return 0;

  switch(context)
    {
      case XSTRINGCONTEXT_FROM_FIRST    : { XDWORD n;
                                            for(n=start; n<size; n++)
                                              {
                                                XCHAR character = text[n];
                                                bool  found     = false;

                                                for(XDWORD e=0; needle.Get()[e] != __C('\0'); e++)
                                                  {
                                                    if(character == needle.Get()[e])
                                                      {
                                                        found = true;
                                                        break;
                                                      }
                                                  }

                                                if(!found) break;
                                              }

                                            this->DeleteCharacters(0, n);
                                            return n;
                                          }
                                          //break;

      case XSTRINGCONTEXT_TO_END        : { int n;
                                            for(n = size- start-1; n >=0; n--)
                                              {
                                                XCHAR character = text[n];
                                                bool found = false;

                                                for(XDWORD e = 0;  needle.Get()[e] != __C('\0'); e++)
                                                  {
                                                    if(character == needle.Get()[e])
                                                      {
                                                        found = true;
                                                        break;
                                                      }
                                                  }

                                                if(!found) break;
                                              }
                                            this->DeleteCharacters(n+1, size -1 - n);
                                            return n;
                                          }
                                          //break;

      case XSTRINGCONTEXT_ALLSTRING     : { for(XDWORD n = start; n < size; n++)
                                              {
                                                XCHAR character = text[n];
                                                bool found = false;

                                                for(XDWORD e=0; needle.Get()[e] != __C('\0'); e++)
                                                  {
                                                    if(character == needle.Get()[e])
                                                      {
                                                        found = true;
                                                        break;
                                                      }
                                                  }

                                                if(found) continue;

                                                text[a] = character;
                                                a++;
                                              }

                                            text[a] = __C('\0');

                                            this->AdjustSize();

                                            return 1;
                                          }
                                          //break;

    }

  return 0;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSTRING::DeleteLastCharacter()
* @brief      DeleteLastCharacter
* @ingroup    UTILS
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::DeleteLastCharacter()
{
  return DeleteCharacters(GetSize()-1, 1);  
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::Character_IsAlpha(XCHAR character) const
* @brief      Character_IsAlpha
* @ingroup    UTILS
*
* @param[in]  character) cons :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::Character_IsAlpha(XCHAR character) const
{
  XBYTE _char = (XBYTE)character;

  if(((_char>='a') && (_char<='z')) ||
     ((_char>='A') && (_char<='Z'))) return true;

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::Character_IsUpperCase(XCHAR character)
* @brief      Character_IsUpperCase
* @ingroup    UTILS
*
* @param[in]  character :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::Character_IsUpperCase(XCHAR character)
{
  XBYTE _char = (XBYTE)character;

  if(((_char>='A') && (_char<='Z'))) return true;

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::Character_IsLowerCase(XCHAR character)
* @brief      Character_IsLowerCase
* @ingroup    UTILS
*
* @param[in]  character :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::Character_IsLowerCase(XCHAR character)
{
  XBYTE _char = (XBYTE)character;

  if(((_char>='a') && (_char<='z'))) return true;

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::Character_IsNumber(XCHAR character)
* @brief      Character_IsNumber
* @ingroup    UTILS
*
* @param[in]  character :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::Character_IsNumber(XCHAR character)
{
  XBYTE _char = (XBYTE)character;

  if((_char>='0') && (_char<='9'))  return true;

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::Character_IsNOT(XCHAR character)
* @brief      Character_IsNOT
* @ingroup    UTILS
*
* @param[in]  character :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::Character_IsNOT(XCHAR character)
{
  switch(character)
    {
      case 0x0000: return true;
      case 0x0009: return true; // Tab
      case 0x000A: return true; // Return
      case 0x000D: return true; // Return
      case 0x0020: return true; // Space
    }

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XCHAR XSTRING::Character_ToUpper(XCHAR character) const
* @brief      Character_ToUpper
* @ingroup    UTILS
*
* @param[in]  character) cons :
*
* @return     XCHAR :
*
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR XSTRING::Character_ToUpper(XCHAR character) const
{

  XCHAR _character = character;
  XBYTE _char      = (XBYTE)_character;

  if((_char>='a')&&(_char<='z'))
    {
       _char      -= 32;
       _character  = (XCHAR)_char;
    }

  return _character;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XCHAR XSTRING::Character_ToLower(XCHAR character) const
* @brief      Character_ToLower
* @ingroup    UTILS
*
* @param[in]  character) cons :
*
* @return     XCHAR :
*
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR XSTRING::Character_ToLower(XCHAR character) const
{
  XCHAR _character = character;
  XBYTE _char      = (XBYTE)_character;

  if((_char>='A')&&(_char<='Z'))
    {
       _char      += 32;
       _character  = (XCHAR)_char;
    }

  return _character;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XCHAR XSTRING::Character_GetFirst()
* @brief      Character_GetFirst
* @ingroup    UTILS
*
* @return     XCHAR :
*
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR XSTRING::Character_GetFirst()
{
  if(IsEmpty()) return 0;

  return text[0];
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XCHAR XSTRING::Character_GetLast()
* @brief      Character_GetLast
* @ingroup    UTILS
*
* @return     XCHAR :
*
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR XSTRING::Character_GetLast()
{
  int c;

  if(IsEmpty()) return 0;

  for(c=0;c<(int)size;c++)
    {
      if(!text[c]) break;
    }

  if((c-1) >=0) return text[c-1];

  return 0;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::Character_Change(XCHAR source,XCHAR target)
* @brief      Character_Change
* @ingroup    UTILS
*
* @param[in]  source :
* @param[in]  target :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::Character_Change(XCHAR source, XCHAR target)
{
  if(IsEmpty()) return false;

  bool status = false;

  for(XDWORD c=0;c<size;c++)
    {
      if(text[c]==source)
        {
          text[c] = target;
          status  = true;
        }
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ToUpperCase()
* @brief      ToUpperCase
* @ingroup    UTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ToUpperCase()
{
  if(IsEmpty()) return false;

  for(XDWORD c=0;c<size;c++)
    {
      XCHAR _char = text[c];

      if(Character_IsAlpha(text[c])) _char = Character_ToUpper(text[c]);

      text[c] = _char;
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ToLowerCase()
* @brief      ToLowerCase
* @ingroup    UTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ToLowerCase()
{
  if(IsEmpty()) return false;

  for(XDWORD c=0;c<size;c++)
    {
      XCHAR _char = text[c];

      if(Character_IsAlpha(text[c])) _char = Character_ToLower(text[c]);

      text[c] = _char;
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XSTRING::Compare(const XCHAR* string, int csize, bool ignorecase)
* @brief      Compare
* @ingroup    UTILS
*
* @param[in]  XCHAR* string :
* @param[in]  csize :
* @param[in]  ignorecase :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XSTRING::Compare(const XCHAR* string, int csize, bool ignorecase)
{
  XDWORD stringsize=csize;

  if(size!=stringsize)
    {
      if(size>stringsize) return  1;
      if(size<stringsize) return -1;
    }

  if(!size && !stringsize) return 0;

  XCHAR* _text = (XCHAR*)string;

  if(ignorecase)
    {
      for(int c=size-1;c>=0;c--)
        {
          XCHAR a=_text[c];
          XCHAR b=text[c];

          if(Character_IsAlpha(a))
            {
              XCHAR c1 = Character_ToUpper(a);
              XCHAR c2 = Character_ToUpper(b);

              if(c1 == c2) continue;
              if(c1 < c2) return  1;
              if(c1 > c2) return -1;
            }
           else
            {
              if(a == b)  continue;
              if(a < b)   return  1;
              if(a > b)   return -1;
            }
        }
    }
   else
    {
      for(int c=size-1;c>=0;c--)
        {
          if(_text[c] == text[c]) continue;
          if(_text[c] < text[c])  return  1;
          if(_text[c] > text[c])  return -1;
        }
    }

  return 0;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XSTRING::Compare(const XCHAR* string, bool ignorecase)
* @brief      Compare
* @ingroup    UTILS
*
* @param[in]  XCHAR* string :
* @param[in]  ignorecase :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XSTRING::Compare(const XCHAR* string, bool ignorecase)
{
  XDWORD stringsize = XSTRING::GetSize(string);

  if(size != stringsize)
    {
      if(size>stringsize) return  1;
      if(size<stringsize) return -1;
    }

  if(!size && !stringsize) return 0;

  XCHAR* _text = (XCHAR*)string;

  if(ignorecase)
    {
      for(int c=size-1;c>=0;c--)
        {
          XCHAR a=_text[c];
          XCHAR b=text[c];

          if(Character_IsAlpha(a))
            {
              XCHAR c1 = Character_ToUpper(a);
              XCHAR c2 = Character_ToUpper(b);

              if(c1 == c2) continue;
              if(c1 < c2) return  1;
              if(c1 > c2) return -1;
            }
           else
            {
              if(a == b)  continue;
              if(a < b)   return  1;
              if(a > b)   return -1;
            }
        }
    }
   else
    {
      for(int c=size-1;c>=0;c--)
        {
          if(_text[c] == text[c]) continue;
          if(_text[c] < text[c])  return  1;
          if(_text[c] > text[c])  return -1;
        }
    }

  return 0;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XSTRING::Compare(const char* string, bool ignorecase)
* @brief      Compare
* @ingroup    UTILS
*
* @param[in]  char* string :
* @param[in]  ignorecase :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XSTRING::Compare(const char* string, bool ignorecase)
{
  XSTRING stringtemp(string);

  return Compare(stringtemp, ignorecase);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XSTRING::Compare(const XCHAR* string, const XCHAR* string2, bool ignorecase)
* @brief      Compare
* @ingroup    UTILS
*
* @param[in]  XCHAR* string :
* @param[in]  XCHAR* string2 :
* @param[in]  ignorecase :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XSTRING::Compare(const XCHAR* string, const XCHAR* string2, bool ignorecase)
{
  XSTRING a;

  a.Set(string);

  return a.Compare(string2,ignorecase);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XSTRING::Compare(const XSTRING& string, bool ignorecase) const
* @brief      Compare
* @ingroup    UTILS
*
* @param[in]  XSTRING& string :
* @param[in]  ignorecase) cons :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XSTRING::Compare(const XSTRING& string, bool ignorecase) const
{
  XDWORD stringsize = string.GetSize();

  if(size != stringsize)
    {
      if(size > stringsize) return  1;
      if(size < stringsize) return -1;
    }

  if(!size && !stringsize) return 0;

  XCHAR* _text = string.Get();

  if(ignorecase)
    {
      for(int c=size-1;c>=0;c--)
        {
          if(Character_IsAlpha(_text[c]))
            {
              XCHAR c1 = Character_ToUpper(_text[c]);
              XCHAR c2 = Character_ToUpper(text[c]);

              if(c1 == c2) continue;
              if(c1 < c2) return  1;
              if(c1 > c2) return -1;
            }
           else
            {
              if(_text[c] == text[c]) continue;
              if(_text[c] < text[c]) return  1;
              if(_text[c] > text[c]) return -1;
            }
        }
    }
   else
    {
      for(int c=size-1;c>=0;c--)
        {
          if(_text[c] == text[c]) continue;
          if(_text[c] < text[c])  return  1;
          if(_text[c] > text[c])  return -1;
        }
    }

  return 0;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XSTRING::Find(const XCHAR* string, bool ignorecase, int startindex)
* @brief      Find
* @ingroup    UTILS
*
* @param[in]  XCHAR* string :
* @param[in]  ignorecase :
* @param[in]  startindex :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XSTRING::Find(const XCHAR* string, bool ignorecase, int startindex)
{
  XSTRING unistring(string);

  return Find(unistring,ignorecase,startindex);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XSTRING::Find(XSTRING& string, bool ignorecase,int startindex)
* @brief      Find
* @ingroup    UTILS
*
* @param[in]  string :
* @param[in]  ignorecase :
* @param[in]  startindex :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XSTRING::Find(XSTRING& string, bool ignorecase,int startindex)
{
  if(IsEmpty())                      return XSTRING_NOTFOUND;
  if(string.IsEmpty())               return XSTRING_NOTFOUND;

  XCHAR* _text = string.Get();
  XDWORD _size = string.GetSize();

  if(_size > size)                    return XSTRING_NOTFOUND;
  if(startindex>=(int)(size-_size)+1) return XSTRING_NOTFOUND;
  if(startindex<0)                    return XSTRING_NOTFOUND;

  bool found;

  for(XDWORD c=startindex;c<(size-_size)+1;c++)
    {
      found = true;

      for(XDWORD d=0;d<_size;d++)
        {
          if(ignorecase && Character_IsAlpha(_text[d]))
            {
              XCHAR c1 = Character_ToUpper(_text[d]);
              XCHAR c2 = Character_ToUpper(text[c+d]);

              if(c1!=c2)
                {
                  found = false;
                  break;
                }
            }
           else
            {
              if(_text[d]!=text[c+d])
                {
                  found = false;
                  break;
                }
            }
        }

      if(found) return c;
    }

  return XSTRING_NOTFOUND;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XSTRING::FindCharacter(XCHAR character, XDWORD startindex, bool endtostart)
* @brief      FindCharacter
* @ingroup    UTILS
*
* @param[in]  character :
* @param[in]  startindex :
* @param[in]  endtostart :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XSTRING::FindCharacter(XCHAR character, XDWORD startindex, bool endtostart)
{
  if(startindex >= (XDWORD)size)  return XSTRING_NOTFOUND;

  if(endtostart)
    {
      for(int c=size-startindex-1; c>=0; c--)
        {
          if(text[c]==character) return c;
        }
    }
   else
    {
      for(XDWORD c=startindex; c<size; c++)
        {
          if(text[c] == character) return c;
        }
    }

  return XSTRING_NOTFOUND;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XSTRING::CountCharacter(XCHAR character, int startindex, bool endtostart)
* @brief      CountCharacter
* @ingroup    UTILS
*
* @param[in]  character :
* @param[in]  startindex :
* @param[in]  endtostart :
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XSTRING::CountCharacter(XCHAR character, int startindex, bool endtostart)
{
  XDWORD count = 0;
  XDWORD c;

  if(startindex>=(int)size) return 0;
  if(startindex<0)          return 0;

  if(endtostart)
    {
      for(c=size-startindex; c>0; c--)
        {
          if(text[c]==character) count++;
        }
    }
   else
    {
      for(c=startindex; c<size; c++)
        {
          if(text[c]==character) count++;
        }
    }

  return count;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XSTRING::FindDiferentCharacter(XCHAR character, int startindex, bool endtostart)
* @brief      FindDiferentCharacter
* @ingroup    UTILS
*
* @param[in]  character :
* @param[in]  startindex :
* @param[in]  endtostart :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XSTRING::FindDiferentCharacter(XCHAR character, int startindex, bool endtostart)
{
  XDWORD c;

  if(startindex>=(int)size) return XSTRING_NOTFOUND;
  if(startindex<0)          return XSTRING_NOTFOUND;

  if(endtostart)
    {
      for(c=size-startindex;c>0;c--)
        {
          if(text[c]!=character) return c;
        }
    }
   else
    {
      for(c=startindex;c<size;c++)
        {
          if(text[c]!=character) return c;
        }
    }

  return XSTRING_NOTFOUND;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XSTRING::GetNCharacters(XCHAR character)
* @brief      GetNCharacters
* @ingroup    UTILS
*
* @param[in]  character :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XSTRING::GetNCharacters(XCHAR character)
{
  int count = 0;

  for(XDWORD c=0; c<GetSize(); c++)
    {
      if(text[c]==character) count++;
    }

  return count;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::AreValidCharacters(XCHAR* validcharacterslist)
* @brief      AreValidCharacters
* @ingroup    UTILS
*
* @param[in]  validcharacterslist :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::AreValidCharacters(XCHAR* validcharacterslist)
{
  if(!validcharacterslist) return false;

  XSTRING vcl;

  vcl = validcharacterslist;

  for(int d=0; d<(int)GetSize(); d++)
    {
      bool isvalid = false;

      for(int c=0; c<(int)vcl.GetSize(); c++)
        {
          if(Get()[d] == vcl.Get()[c])
            {
              isvalid = true;
              break;
            }
        }

      if(!isvalid) return false;
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XSTRING::Copy(const XCHAR* startmark, const XCHAR* endmark, bool ignorecase, int addstartindex, XSTRING& string)
* @brief      Copy
* @ingroup    UTILS
*
* @param[in]  XCHAR* startmark :
* @param[in]  XCHAR* endmark :
* @param[in]  ignorecase :
* @param[in]  addstartindex :
* @param[in]  string :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XSTRING::Copy(const XCHAR* startmark, const XCHAR* endmark, bool ignorecase, int addstartindex, XSTRING& string)
{
  int startindex  = 0;
  int endindex    = GetSize();
  XDWORD sizeendmark = 0;

  string.Empty();

  if(startmark)
    {
      XSTRING mark;

      mark = startmark;
      startindex = Find(startmark, ignorecase, addstartindex);
      if(startindex==XSTRING_NOTFOUND) return XSTRING_NOTFOUND;

      startindex+= mark.GetSize();
    }

  if(endmark)
    {
      XSTRING mark;

      mark = endmark;
      endindex = Find(endmark, ignorecase, startindex);
      if(endindex==XSTRING_NOTFOUND) endindex = size;

      sizeendmark = mark.GetSize();
    }

  for(int c=startindex;c<endindex;c++)
    {
      XCHAR str[2] = { text[c], 0 };

      string+=str;
    }

  int indexnext = (endindex+sizeendmark);

  if(indexnext>(int)size) indexnext = (int)size;

  return indexnext;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XSTRING::Copy(int startindex, const XCHAR* endmark, bool ignorecase, XSTRING& string)
* @brief      Copy
* @ingroup    UTILS
*
* @param[in]  startindex :
* @param[in]  XCHAR* endmark :
* @param[in]  ignorecase :
* @param[in]  string :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XSTRING::Copy(int startindex, const XCHAR* endmark, bool ignorecase, XSTRING& string)
{
  int endindex    = GetSize();
  XDWORD sizeendmark = 0;

  string.Empty();

  if(endmark)
    {
      XSTRING mark;

      mark = endmark;
      endindex = Find(endmark, ignorecase, startindex);
      if(endindex==XSTRING_NOTFOUND) endindex = size;

      sizeendmark = mark.GetSize();
    }

  if(startindex>=endindex) return XSTRING_NOTFOUND;

  for(int c=startindex;c<endindex;c++)
    {
      XCHAR str[2] = { text[c], 0 };

      string+=str;
    }

  int indexnext = (endindex+sizeendmark);

  if(indexnext>(int)size) indexnext = (int)size;

  return indexnext;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XSTRING::Copy(const XCHAR* startmark, int endindex, bool ignorecase, int addstartindex, XSTRING& string)
* @brief      Copy
* @ingroup    UTILS
*
* @param[in]  XCHAR* startmark :
* @param[in]  endindex :
* @param[in]  ignorecase :
* @param[in]  addstartindex :
* @param[in]  string :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XSTRING::Copy(const XCHAR* startmark, int endindex, bool ignorecase, int addstartindex, XSTRING& string)
{
  int startindex    = 0;
  XDWORD sizeendmark = 0;

  string.Empty();

  if(startmark)
    {
      XSTRING mark;

      mark = startmark;
      startindex = Find(startmark, ignorecase, addstartindex);
      if(startindex==XSTRING_NOTFOUND) return XSTRING_NOTFOUND;

      startindex+= mark.GetSize();
    }

  if(startindex>=endindex) return XSTRING_NOTFOUND;

  for(int c=startindex;c<endindex;c++)
    {
      XCHAR str[2] = { text[c], 0 };

      string+=str;
    }

  int indexnext = (endindex+sizeendmark);

  if(indexnext>(int)size) indexnext = (int)size;

  return indexnext;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XSTRING::Copy(int startindex, int endindex, XSTRING& string)
* @brief      Copy
* @ingroup    UTILS
*
* @param[in]  startindex :
* @param[in]  endindex :
* @param[in]  string :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XSTRING::Copy(int startindex, int endindex, XSTRING& string)
{
  if(startindex>=endindex) return XSTRING_NOTFOUND;

  string.ReAllocBuffer(endindex-startindex);
  memcpy(string.Get(),&(this->text[startindex]),(endindex-startindex)*sizeof(XCHAR));

  return size;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XSTRING::Copy(int startindex, XSTRING& string)
* @brief      Copy
* @ingroup    UTILS
*
* @param[in]  startindex :
* @param[in]  string :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XSTRING::Copy(int startindex, XSTRING& string)
{
  return Copy(startindex, GetSize(), string);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XSTRING::Replace(XCHAR* findwhat, XCHAR* replaceby)
* @brief      Replace
* @ingroup    UTILS
*
* @param[in]  findwhat :
* @param[in]  replaceby :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XSTRING::Replace(XCHAR* findwhat, XCHAR* replaceby)
{
  XSTRING what;
  XSTRING replace;

  what.Set(findwhat);

  replace.Set(replaceby);

  int found;
  int coincidences = 0;

  do{ found = ReplaceFirst(what.Get(),replace.Get());

      if (found!=NOTFOUND)
        coincidences++;
      else
        break;
    } while(1);

  return coincidences;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XSTRING::ReplaceFirst(XCHAR* findwhat, XCHAR* replaceby)
* @brief      ReplaceFirst
* @ingroup    UTILS
*
* @param[in]  findwhat :
* @param[in]  replaceby :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XSTRING::ReplaceFirst(XCHAR* findwhat, XCHAR* replaceby)
{
  XSTRING what;
  XSTRING replace;

  what.Set(findwhat);
  replace.Set(replaceby);

  int whatsize = what.GetSize();
  int found    = 0;

  found         = this->Find(findwhat, false, found);
  if(found!=NOTFOUND)
    {
      DeleteCharacters(found, whatsize);
      Insert(replace, found);
    }

  return found;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::Insert(XSTRING str,XDWORD position)
* @brief      Insert
* @ingroup    UTILS
*
* @param[in]  str :
* @param[in]  position :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::Insert(XSTRING str,XDWORD position)
{
  XSTRING tmp;

  if(position > size)
    {
      return this->Add(str);
    }

  Copy(0,position,tmp);

  tmp.Add(str);

  XSTRING trail;

  Copy(position, trail);
  tmp.Add(trail);

  Set(tmp);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ConvertFromInt(int value, const XCHAR* mask)
* @brief      ConvertFromInt
* @ingroup    UTILS
*
* @param[in]  value :
* @param[in]  mask :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertFromInt(int value, const XCHAR* mask)
{
  char*     str;
  XSTRING  _mask;

  str = new char[XSTRING_MAXTEMPOSTR];
  if(!str) return false;

  memset(str,0,XSTRING_MAXTEMPOSTR);

  if(mask) _mask = mask; else _mask = __L("%d");

  XSTRING_CREATEOEM(_mask, charstr)
  SPRINTF(str, charstr, value);
  XSTRING_DELETEOEM(_mask, charstr)

  Set(str);

  delete [] str;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ConvertFromDWord(XDWORD value, const XCHAR* mask)
* @brief      ConvertFromDWord
* @ingroup    UTILS
*
* @param[in]  value :
* @param[in]  mask :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertFromDWord(XDWORD value, const XCHAR* mask)
{
  char*    str;
  XSTRING  _mask;

  str = new char[XSTRING_MAXTEMPOSTR];
  if(!str) return false;

  memset(str,0,XSTRING_MAXTEMPOSTR);

  if(mask) _mask = mask; else _mask = __L("%d");

  XSTRING_CREATEOEM(_mask, charstr)
  SPRINTF(str, charstr, (XDWORD)value);
  XSTRING_DELETEOEM(_mask, charstr)

  Set(str);

  delete [] str;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ConvertFromQWord(XQWORD value, const XCHAR* mask)
* @brief      ConvertFromQWord
* @ingroup    UTILS
*
* @param[in]  value :
* @param[in]  mask :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertFromQWord(XQWORD value, const XCHAR* mask)
{
  char*    str;
  XSTRING  _mask;

  str = new char[XSTRING_MAXTEMPOSTR];
  if(!str) return false;

  memset(str,0,XSTRING_MAXTEMPOSTR);

  if(mask) _mask = mask; else _mask = __L("%u");

  XSTRING_CREATEOEM(_mask, charstr)
  SPRINTF(str, charstr, (XDWORD)value);
  XSTRING_DELETEOEM(_mask, charstr)

  Set(str);

  delete [] str;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ConvertFromLongLong(long long value, const XCHAR* mask)
* @brief      ConvertFromLongLong
* @ingroup    UTILS
*
* @param[in]  value :
* @param[in]  mask :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertFromLongLong(long long value, const XCHAR* mask)
{
  char*    str;
  XSTRING  _mask;

  str = new char[XSTRING_MAXTEMPOSTR];
  if(!str) return false;

  memset(str,0,XSTRING_MAXTEMPOSTR);

  if(mask) _mask = mask; else _mask = __L("%lld");

  XSTRING_CREATEOEM(_mask, charstr)
  SPRINTF(str, charstr, (long long)value);
  XSTRING_DELETEOEM(_mask, charstr)

  Set(str);

  delete [] str;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ConvertFromFloat(float value, const XCHAR* mask)
* @brief      ConvertFromFloat
* @ingroup    UTILS
*
* @param[in]  value :
* @param[in]  mask :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertFromFloat(float value, const XCHAR* mask)
{
  char*    str;
  XSTRING  _mask;

  str = new char[XSTRING_MAXTEMPOSTR];
  if(!str) return false;

  memset(str,0,XSTRING_MAXTEMPOSTR);

  if(mask) _mask = mask; else _mask = __L("%f");

  XSTRING_CREATEOEM(_mask, charstr);
  SPRINTF(str, charstr, value);
  XSTRING_DELETEOEM(_mask, charstr)

  Set(str);

  delete [] str;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ConvertFromDouble(double value, const XCHAR* mask)
* @brief      ConvertFromDouble
* @ingroup    UTILS
*
* @param[in]  value :
* @param[in]  mask :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertFromDouble(double value, const XCHAR* mask)
{
  char*    str;
  XSTRING  _mask;

  str = new char[XSTRING_MAXTEMPOSTR];
  if(!str) return false;

  memset(str,0,XSTRING_MAXTEMPOSTR);

  if(mask) _mask = mask; else _mask = __L("%g");

  XSTRING_CREATEOEM(_mask, charstr)
  SPRINTF(str, charstr, value);
  XSTRING_DELETEOEM(_mask, charstr)

  Set(str);

  delete [] str;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ConvertFromBoolean(bool boolean, bool uppercase)
* @brief      ConvertFromBoolean
* @ingroup    UTILS
*
* @param[in]  boolean :
* @param[in]  uppercase :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertFromBoolean(bool boolean, bool uppercase)
{
  if(boolean)
        Set(uppercase? __L("YES") : __L("yes"));
   else Set(uppercase? __L("NO")  : __L("no"));

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ConvertFromXBUFFER(XBUFFER& buffer)
* @brief      ConvertFromXBUFFER
* @ingroup    UTILS
*
* @param[in]  buffer :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertFromXBUFFER(XBUFFER& buffer)
{
  if(!this->AdjustSize(buffer.GetSize()/sizeof(XDWORD))) return false;
  if(!buffer.Get(*this, this->size, 0)) return false;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ConvertHexFormatChars()
* @brief      ConvertHexFormatChars
* @ingroup    UTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertHexFormatChars()
{
  XSTRING string;

  string.Empty();

  if(IsEmpty()) return false;

  for(int c=0;c<(int)GetSize();c++)
    {
      XCHAR character[3] = { 0 , 0 , 0 };

      character[0] = Get()[c];
      character[1] = Get()[c+1];

      if((character[0]==__C('\\')) && (character[1]==__C('x')))
        {
          XSTRING   numberhex;
          XCHAR part[2] = { 0 , 0 };

          c+=2;

          for(int d=0;d<2;d++)
            {
              part[0] = Get()[c+d];
              numberhex.Add(part);
            }

          numberhex.UnFormat(__L("%02X"),&part[0]);

          part[0]&=0x00FF;
          string.Add(part);

          c++;
        }
       else string.Add((XCHAR)character[0]);
    }

  if(string.IsEmpty()) return false;

  Set(string);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ConvertToHexString(XSTRING& string, bool uppercase)
* @brief      ConvertToHexString
* @ingroup    UTILS
*
* @param[in]  string :
* @param[in]  uppercase :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertToHexString(XSTRING& string, bool uppercase)
{
  XSTRING datastr;

  string.Empty();

  for(int c=0;c<(int)GetSize(); c++)
    {
      datastr.Format(uppercase?__L("%02X"):__L("%02x"), Get()[c]);
      string.Add(datastr);
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ConvertHexStringToBuffer(XBUFFER& xbuffer)
* @brief      ConvertHexStringToBuffer
* @ingroup    UTILS
*
* @param[in]  xbuffer :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertHexStringToBuffer(XBUFFER& xbuffer)
{
  xbuffer.Delete();

  for(int c=0; c<(int)GetSize(); c+=2)
    {
      XCHAR    hexbytechar[3] = { 0, 0, 0 };
      XSTRING  hexbytestr;
      int      data;

      hexbytechar[0] = Get()[c];
      hexbytechar[1] = Get()[c+1];

      hexbytestr = hexbytechar;

      hexbytestr.UnFormat(__L("%02X"), &data);
      xbuffer.Add((XBYTE)data);
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ConvertHexStringFromBuffer(XBUFFER& xbuffer, bool uppercase)
* @brief      ConvertHexStringFromBuffer
* @ingroup    UTILS
*
* @param[in]  xbuffer :
* @param[in]  uppercase :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertHexStringFromBuffer(XBUFFER& xbuffer, bool uppercase)
{
  Empty();

  for(int c=0; c<(int)xbuffer.GetSize(); c++)
    {
      XSTRING  hexbytestr;

      hexbytestr.Format(uppercase?__L("%02X"):__L("%02x"), xbuffer.Get()[c]);
      Add(hexbytestr);
    }

  return true;

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XSTRING::ConvertToInt(int index, const XCHAR* mask, bool checkvalidchars)
* @brief      ConvertToInt
* @ingroup    UTILS
*
* @param[in]  index :
* @param[in]  mask :
* @param[in]  checkvalidchars :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XSTRING::ConvertToInt(int index, const XCHAR* mask, bool checkvalidchars)
{
  if(IsEmpty()) return 0;

  if(checkvalidchars)
    {
      XSTRING  validcharacters;
      validcharacters  = XSTRING_VALIDCHARSINT;
      if(!AreValidCharacters(validcharacters.Get())) return 0;
    }

  XSTRING  _mask;
  int      data = 0;

  if(mask)
         _mask = mask;
    else _mask = __L("%d");

  XSTRING_CREATEOEM(_mask, charstr)
  XSTRING_CREATEOEM((*this), charstr2)

  SSCANF(&charstr2[index], charstr, &data);

  XSTRING_DELETEOEM((*this), charstr2)
  XSTRING_DELETEOEM(_mask, charstr)

  return data;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XSTRING::ConvertToDWord(int index, const XCHAR* mask, bool checkvalidchars)
* @brief      ConvertToDWord
* @ingroup    UTILS
*
* @param[in]  index :
* @param[in]  mask :
* @param[in]  checkvalidchars :
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XSTRING::ConvertToDWord(int index, const XCHAR* mask, bool checkvalidchars)
{
  if(IsEmpty()) return 0;

  if(checkvalidchars)
    {
      XSTRING  validcharacters;
      validcharacters  = XSTRING_VALIDCHARSINT
      if(!AreValidCharacters(validcharacters.Get())) return 0;
    }

  XSTRING  _mask;
  XDWORD   data = 0;

  if(mask) _mask = mask; else _mask = __L("%d");

  XSTRING_CREATEOEM(_mask, charstr)
  XSTRING_CREATEOEM((*this), charstr2)

  SSCANF(&charstr2[index], charstr, &data);

  XSTRING_DELETEOEM((*this), charstr2)
  XSTRING_DELETEOEM(_mask, charstr)

  return data;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XQWORD XSTRING::ConvertToQWord(int index, const XCHAR* mask, bool checkvalidchars)
* @brief      ConvertToQWord
* @ingroup    UTILS
*
* @param[in]  index :
* @param[in]  mask :
* @param[in]  checkvalidchars :
*
* @return     XQWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XQWORD XSTRING::ConvertToQWord(int index, const XCHAR* mask, bool checkvalidchars)
{
  if(IsEmpty()) return 0;

  if(checkvalidchars)
    {
      XSTRING  validcharacters;
      validcharacters  = XSTRING_VALIDCHARSINT
      if(!AreValidCharacters(validcharacters.Get())) return 0;
    }

  XSTRING  _mask;
  long long  data = 0;

  if(mask) _mask = mask; else _mask = __L("%lld");

  XSTRING_CREATEOEM(_mask, charstr)
  XSTRING_CREATEOEM((*this), charstr2)

  SSCANF(&charstr2[index], charstr, &data);

  XSTRING_DELETEOEM((*this), charstr2)
  XSTRING_DELETEOEM(_mask, charstr)

  return data;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float XSTRING::ConvertToFloat(int index, const XCHAR* mask, bool checkvalidchars)
* @brief      ConvertToFloat
* @ingroup    UTILS
*
* @param[in]  index :
* @param[in]  mask :
* @param[in]  checkvalidchars :
*
* @return     float :
*
* --------------------------------------------------------------------------------------------------------------------*/
float XSTRING::ConvertToFloat(int index, const XCHAR* mask, bool checkvalidchars)
{
  if(IsEmpty()) return 0.0f;

  if(checkvalidchars)
    {
      XSTRING  validcharacters;
      validcharacters  = XSTRING_VALIDCHARSFLOAT;
      if(!AreValidCharacters(validcharacters.Get())) return .0f;
    }

  XSTRING  _mask;
  float  data = 0;

  if(mask) _mask = mask; else _mask = __L("%f");

  XSTRING_CREATEOEM(_mask, charstr)
  XSTRING_CREATEOEM((*this), charstr2)

  SSCANF(&charstr2[index], charstr, &data);

  XSTRING_DELETEOEM((*this), charstr2)
  XSTRING_DELETEOEM(_mask, charstr)

  return data;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         double XSTRING::ConvertToDouble(int index, const XCHAR* mask, bool checkvalidchars)
* @brief      ConvertToDouble
* @ingroup    UTILS
*
* @param[in]  index :
* @param[in]  mask :
* @param[in]  checkvalidchars :
*
* @return     double :
*
* --------------------------------------------------------------------------------------------------------------------*/
double XSTRING::ConvertToDouble(int index, const XCHAR* mask, bool checkvalidchars)
{
  if(IsEmpty()) return 0;

  if(checkvalidchars)
    {
      XSTRING  validcharacters;
      validcharacters  = XSTRING_VALIDCHARSFLOAT;
      if(!AreValidCharacters(validcharacters.Get())) return .0f;
    }

  XSTRING  _mask;
  double     data = 0;

  if(mask) _mask = mask; else _mask = __L("%lf");

  XSTRING_CREATEOEM(_mask, charstr)
  XSTRING_CREATEOEM((*this), charstr2)

  SSCANF(&charstr2[index], charstr, &data);

  XSTRING_DELETEOEM((*this), charstr2)
  XSTRING_DELETEOEM(_mask, charstr)

  return data;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ConvertToXBUFFER(XBUFFER& buffer)
* @brief      ConvertToXBUFFER
* @ingroup    UTILS
*
* @param[in]  buffer :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertToXBUFFER(XBUFFER& buffer)
{
  if(IsEmpty()) return true;

  if(!buffer.Resize(GetSize()*sizeof(XDWORD))) return false;
  if(!buffer.Set(*this)) return false;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ConvertToBoolean()
* @brief      ConvertToBoolean
* @ingroup    UTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertToBoolean()
{
  bool result = false;

  if(!Compare(__L("yes") , true) || !Compare(__L("true") , true))
    {
      result = true;
    }
   else
    {
      if(!Compare(__L("no") , true) || !Compare(__L("false") , true))
        {
          result = false;
        }
       else
        {
          if(Compare(__L("0")  , true)) result = true;
        }
    }

  return result;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSTRING::ConvertFromWide(XWORD* widechars, XDWORD maxsize)
* @brief      ConvertFromWide
* @ingroup    UTILS
*
* @param[in]  widechars : 
* @param[in]  maxsize : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertFromWide(XWORD* widechars, XDWORD maxsize)
{
  Empty();

  for(XDWORD c=0; c<maxsize; c++)
    {
      if(!(XCHAR)widechars[c]) break;

      Add((XCHAR)widechars[c]);
    }
  
  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ConvertFromUTF8(XBYTE* data,XDWORD size)
* @brief      ConvertFromUTF8
* @ingroup    UTILS
*
* @param[in]  data :
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertFromUTF8(XBYTE* data,XDWORD size)
{
  XDWORD  sizeutf8  = 0;
  XDWORD  index     = 0;
  XBYTE*  ptr;
  XDWORD  c;

  c   = 0;
  ptr = data;
  while(c<size)
    {
      if(((XBYTE)*ptr)<128 || (*ptr&192)==192) sizeutf8++;
      ptr++;
      c++;
    }

  if(!sizeutf8) return false;

  if(sizeutf8>size)  sizeutf8 = size;

  if(!ReAllocBuffer(sizeutf8)) return false;

  c   = 0;
  ptr = data;
  while(c < size)
    {
      XBYTE b=*ptr;
      //Byte represents an ASCII character. Direct copy will do.
      if(!(b&128))
        {
          text[index]=b;
        }
       else
        {
           //Byte is the middle of an encoded character. Ignore.
           if((b&192)==128)
             {
               ptr++;
               continue;
             }
            else
             {
               //Byte represents the start of an encoded character in the range
               //U+0080 to U+07FF
               if((b&224)==192)
                 {
                   text[index]=((*ptr&31)<<6)|(ptr[1]&63);
                 }
                else
                 {
                    //Byte represents the start of an encoded character in the range
                    //U+07FF to U+FFFF
                    if((b&240)==224)
                      {
                        text[index]=((*ptr&15)<<12)|((ptr[1]&63)<<6)|(ptr[2]&63);
                      }
                     else
                      {
                        //Byte represents the start of an encoded character beyond the
                        //U+FFFF limit of 16-bit integers
                        if((b&248)==240)
                          {
                            text[index]='?';
                          }
                      }
                 }
             }
        }

      index++;
      ptr++;
      c++;

      if(index>=sizeutf8) break;
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ConvertFromUTF8(XBUFFER& xbuffer)
* @brief      ConvertFromUTF8
* @ingroup    UTILS
*
* @param[in]  xbuffer :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertFromUTF8(XBUFFER& xbuffer)
{
  return ConvertFromUTF8(xbuffer.Get(), xbuffer.GetSize());
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XSTRING::GetSizeConvertToUTF8()
* @brief      GetSizeConvertToUTF8
* @ingroup    UTILS
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XSTRING::GetSizeConvertToUTF8()
{
  XDWORD size = 0;

  if(IsEmpty()) return size;

  int i = 0;
  int j = 0;
  int c = (int)text[i++];

  while(c)
    {
      if(c<0)
        {
          j++;
        }
       else
        {
          if(c<128)
            {
              j++;
            }
           else
            {
                if(c< 2048)
                  {
                    j++;
                    j++;
                  }
                 else
                  {
                    if(c<65536)
                      {
                        j++;
                        j++;
                        j++;
                      }
                     else
                      {
                        j++;
                        j++;
                        j++;
                        j++;
                      }
                  }
            }
        }

      c = text[i++];
    }


  size = j;

  return size;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ConvertToUTF8(XBYTE* data, int& size)
* @brief      ConvertToUTF8
* @ingroup    UTILS
*
* @param[in]  data :
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertToUTF8(XBYTE* data, int& size)
{
  size = 0;
  if(!data) return false;

  if(IsEmpty()) return false;

  int i = 0;
  int j = 0;
  int c = (int)text[i++];

  while(c)
    {
      if(c<0)
        {
          data[j++]=1;
        }
       else
        {
          if(c<128)
            {
              data[j++] = (XBYTE)c;
            }
           else
            {
                if(c< 2048)
                  {
                    data[j++]= (XBYTE)(192+ c/64);
                    data[j++]= (XBYTE)(128+(c&63));
                  }
                 else
                  {
                    if(c<65536)
                      {
                        data[j++]=  (XBYTE)(224+ c/4096);
                        data[j++]=  (XBYTE)(128+(c&4095)/64);
                        data[j++]=  (XBYTE)(128+(c&63));
                      }
                     else
                      {
                        data[j++]=  (XBYTE)(240+ c/262144);
                        data[j++]=  (XBYTE)(128+(c&262143)/4096);
                        data[j++]=  (XBYTE)(128+(c&4095)/64);
                        data[j++]=  (XBYTE)(128+(c&63));
                      }


                  }
            }
        }

      c = text[i++];
    }

  data[j]=0;

  size = j;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ConvertToUTF8(XBUFFER& xbuffer)
* @brief      ConvertToUTF8
* @ingroup    UTILS
*
* @param[in]  xbuffer :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertToUTF8(XBUFFER& xbuffer)
{
  if(IsEmpty()) return false;

  XDWORD sizeUTF8 = GetSizeConvertToUTF8()+1;

  xbuffer.Delete();
  xbuffer.Resize(sizeUTF8);
  xbuffer.FillBuffer();

  int _size  = xbuffer.GetSize();

  return ConvertToUTF8(xbuffer.Get(),  _size);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ConvertToBase64(XSTRING& string)
* @brief      ConvertToBase64
* @ingroup    UTILS
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertToBase64(XSTRING& string)
{
  XDWORD sizebase64  = 4 * ((GetSize() + 2) / 3);
  int mod_table[] = { 0, 2, 1 };

  string.Empty();
  string.ReAllocBuffer(sizebase64);

  for(int i=0, j=0; i<(int)GetSize();)
    {
      XDWORD octetA = (i < (int)GetSize()) ? (XBYTE)Get()[i++] : 0;
      XDWORD octetB = (i < (int)GetSize()) ? (XBYTE)Get()[i++] : 0;
      XDWORD octetC = (i < (int)GetSize()) ? (XBYTE)Get()[i++] : 0;

      XDWORD triple = (octetA << 0x10) + (octetB << 0x08) + octetC;

      string.Get()[j++] = (ConvertIndexBase64ToXCHAR((triple >> 3 * 6) & 0x3F));
      string.Get()[j++] = (ConvertIndexBase64ToXCHAR((triple >> 2 * 6) & 0x3F));
      string.Get()[j++] = (ConvertIndexBase64ToXCHAR((triple >> 1 * 6) & 0x3F));
      string.Get()[j++] = (ConvertIndexBase64ToXCHAR((triple >> 0 * 6) & 0x3F));
    }

  for(int i = 0; i < mod_table[GetSize() % 3]; i++)
    {
      string.Get()[sizebase64 - 1 - i] = __C('=');
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ConvertFromBase64(XSTRING& string)
* @brief      ConvertFromBase64
* @ingroup    UTILS
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertFromBase64(XSTRING& string)
{
  XDWORD  data;
  int     size  = string.GetSize();
  int     c     = 0;
  int     d;

  Empty();

  if(!size) return false;

  XSTRING_CREATEOEM(string, charstr)

  do{ data = 0;

      for(d=0;d<4;d++)
        {
          data |= XSTRING::ConvertXCHARToBase64((char)charstr[c+d]);
          if(d!=3) data<<=6;
        }


      data<<=8;

      for(d=0;d<3;d++)
        {
          XCHAR character[2] = { 0 , 0 };

          character[0]  = ((data & 0xFF000000)>>24);
          data<<=8;

          Add(character);
        }

      c+=4;

    } while(c<size);

  XSTRING_DELETEOEM(string, charstr)

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ConvertToPascal(SHORTSTRING& pascalstring)
* @brief      ConvertToPascal
* @ingroup    UTILS
*
* @param[in]  pascalstring :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertToPascal(SHORTSTRING& pascalstring)
{
  memset(&pascalstring, 0, sizeof(SHORTSTRING));

  pascalstring.size = (XBYTE)(GetSize()>255)?255:GetSize();

  XSTRING_CREATEOEM((*this), charstr)
  memcpy(&pascalstring.data, charstr, pascalstring.size);
  XSTRING_DELETEOEM((*this), charstr)

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ConvertFromPascal(SHORTSTRING& pascalstring)
* @brief      ConvertFromPascal
* @ingroup    UTILS
*
* @param[in]  pascalstring :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertFromPascal(SHORTSTRING& pascalstring)
{
  if(!pascalstring.size) return false;

  Set(pascalstring.data);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ConvertFromDoubleToSpanishText(double value, bool withintegerpart, bool withdecimalpart, double& integerpart, double& decimalpart)
* @brief      ConvertFromDoubleToSpanishText
* @ingroup    UTILS
*
* @param[in]  value :
* @param[in]  withintegerpart :
* @param[in]  withdecimalpart :
* @param[in]  integerpart :
* @param[in]  decimalpart :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertFromDoubleToSpanishText(double value, bool withintegerpart, bool withdecimalpart, double& integerpart, double& decimalpart)
{
  Empty();

  integerpart = Truncate(value);
  decimalpart = Fraction(value);

  XSTRING tmp;

  if(withintegerpart)
    {
      double _integerpart;
      double _decimalpart;

      if(integerpart == 0) Set(__L("cero"));
        else if(integerpart ==  1) Set(__L("uno"));
        else if(integerpart ==  2) Set(__L("dos"));
        else if(integerpart ==  3) Set(__L("tres"));
        else if(integerpart ==  4) Set(__L("cuatro"));
        else if(integerpart ==  5) Set(__L("cinco"));
        else if(integerpart ==  6) Set(__L("seis"));
        else if(integerpart ==  7) Set(__L("siete"));
        else if(integerpart ==  8) Set(__L("ocho"));
        else if(integerpart ==  9) Set(__L("nueve"));
        else if(integerpart == 10) Set(__L("diez"));
        else if(integerpart == 11) Set(__L("once"));
        else if(integerpart == 12) Set(__L("doce"));
        else if(integerpart == 13) Set(__L("trece"));
        else if(integerpart == 14) Set(__L("catorce"));
        else if(integerpart == 15) Set(__L("quince"));
        else if(integerpart < 20)
               {
                  Set(__L("dieci"));
                  tmp.ConvertFromDoubleToSpanishText(integerpart - 10, true, false, _integerpart, _decimalpart);
                  Add(tmp);
                }
               else if(integerpart == 20) Set(__L("veinte"));
                      else if(integerpart < 30)
                            {
                              Set(__L("veinti"));
                              tmp.ConvertFromDoubleToSpanishText(integerpart - 20, true, false, _integerpart, _decimalpart);
                              Add(tmp);
                             }
                            else if(integerpart == 30) Set(__L("treinta"));
                            else if(integerpart == 40) Set(__L("cuarenta"));
                            else if(integerpart == 50) Set(__L("cincuenta"));
                            else if(integerpart == 60) Set(__L("sesenta"));
                            else if(integerpart == 70) Set(__L("setenta"));
                            else if(integerpart == 80) Set(__L("ochenta"));
                            else if(integerpart == 90) Set(__L("noventa"));
                            else if(integerpart < 100)
                                   {
                                     ConvertFromDoubleToSpanishText(Truncate(integerpart/10) * 10, true, false, _integerpart, _decimalpart);
                                     Add(__L(" y "));
                                     tmp.ConvertFromDoubleToSpanishText(fmod(integerpart, (double)10), true, false, _integerpart, _decimalpart);
                                     Add(tmp);
                                   }
                                  else if(integerpart == 100) Set(__L("cien"));
                                  else if(integerpart < 200)
                                         {
                                           Set(__L("ciento "));
                                           tmp.ConvertFromDoubleToSpanishText(integerpart - 100, true, false, _integerpart, _decimalpart);
                                           Add(tmp);
                                         }
                                        else if((integerpart == 200) || (integerpart == 300) || (integerpart == 400) || (integerpart == 600) || (integerpart == 800))
                                               {
                                                 ConvertFromDoubleToSpanishText(Truncate(integerpart / 100), true, false, _integerpart, _decimalpart);
                                                 Add(__L("cientos"));
                                               }
                                              else if(integerpart == 500) Set(__L("quinientos"));
                                              else if(integerpart == 700) Set(__L("setecientos"));
                                              else if(integerpart == 900) Set(__L("novecientos"));
                                              else if(integerpart < 1000)
                                                   {
                                                     ConvertFromDoubleToSpanishText(Truncate(integerpart / 100) * 100, true, false, _integerpart, _decimalpart);
                                                     Add(__L(" "));
                                                     tmp.ConvertFromDoubleToSpanishText(fmod(integerpart, (double)100), true, false, _integerpart, _decimalpart);
                                                     Add(tmp);
                                                   }
                                                  else if(integerpart == 1000) Set(__L("mil"));
                                                  else if(integerpart < 2000)
                                                        {
                                                          Set(__L("mil "));
                                                          tmp.ConvertFromDoubleToSpanishText(fmod(integerpart, (double)1000), true, false, _integerpart, _decimalpart);
                                                          Add(tmp);
                                                        }
                                                      else if(integerpart < 1000000)
                                                              {
                                                                ConvertFromDoubleToSpanishText(Truncate(integerpart / 1000), true, false, _integerpart, _decimalpart);
                                                                Add(__L(" mil"));
                                                                if((fmod(integerpart, (double)1000)) > 0)
                                                                  {
                                                                    Add(" ");
                                                                    tmp.ConvertFromDoubleToSpanishText(fmod(integerpart, (double)1000), true, false, _integerpart, _decimalpart);
                                                                    Add(tmp);
                                                                  }
                                                              }
                                                            else if(integerpart == 1000000) Set(__L("un millon"));
                                                            else if(integerpart < 2000000)
                                                                    {
                                                                      Set(__L("un millon"));
                                                                      tmp.ConvertFromDoubleToSpanishText(fmod(integerpart, (double)1000000), true, false, _integerpart, _decimalpart);
                                                                      Add(tmp);
                                                                    }
                                                                   else if(integerpart < 1000000000000LL)
                                                                          {
                                                                             ConvertFromDoubleToSpanishText((integerpart / 1000000), true, false, _integerpart, _decimalpart);
                                                                             Add(__L(" millones"));
                                                                             if((integerpart - Truncate(integerpart / 1000000) * 1000000) > 0)
                                                                               {
                                                                                 Add(__L(" "));
                                                                                 tmp.ConvertFromDoubleToSpanishText(integerpart - Truncate(integerpart / 1000000) * 1000000, true, false, _integerpart, _decimalpart);
                                                                                 Add(tmp);
                                                                               }
                                                                          }
                                                                         else
                                                                          {
                                                                            if(integerpart == 1000000000000LL) Set(__L("un billon"));
                                                                              else if(integerpart < 2000000000000LL)
                                                                                {
                                                                                  Set(__L("un billon"));
                                                                                  tmp.ConvertFromDoubleToSpanishText(Truncate(integerpart / 1000000000000LL) * 1000000000000LL, true, false, _integerpart, _decimalpart);
                                                                                  Add(tmp);
                                                                                }
                                                                               else
                                                                                {
                                                                                   ConvertFromDoubleToSpanishText(Truncate(integerpart / 1000000000000LL), true, false, _integerpart, _decimalpart);
                                                                                   Add(__L(" billones"));

                                                                                   if((integerpart - Truncate(integerpart / 1000000000000LL) * 1000000000000LL) > 0)
                                                                                     {
                                                                                       Add(__L(" "));
                                                                                       tmp.ConvertFromDoubleToSpanishText(integerpart - Truncate(integerpart / 1000000000000LL) * 1000000000000LL, true, false, _integerpart, _decimalpart);
                                                                                       Add(tmp);
                                                                                     }
                                                                                }
                                                                          }
      if(!integerpart) return false;
    }

  if(withdecimalpart)
    {
      double _integerpart;
      double _decimalpart;

      double ipart = Truncate(decimalpart*100);
      double dpart = Fraction(decimalpart*100);

      if(dpart>=0.9f) ipart++;

      if(ipart)
        {
          if(withintegerpart) Add(__L(" con "));
          tmp.ConvertFromDoubleToSpanishText(ipart, true, false, _integerpart, _decimalpart);
          Add(tmp);

        } else return false;
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::Swab()
* @brief      Swab
* @ingroup    UTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::Swab()
{
  if(IsEmpty()) return false;

  for(int c=0;c<(int)GetSize();c+=2)
    {
      XCHAR data;

      data      = text[c+1];
      text[c+1] = text[c];
      text[c]   = data;
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::Split(XCHAR separator, XVECTOR<XSTRING*>& results, bool addsubstringempty)
* @brief      Split
* @ingroup    UTILS
*
* @param[in]  separator :
* @param[in]  results :
* @param[in]  addsubstringempty :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::Split(XCHAR separator, XVECTOR<XSTRING*>& results, bool addsubstringempty)
{
  if(IsEmpty()) return false;

  int start = 0;

  for(XDWORD c=0; c<sizemem; c++)
    {
      if((text[c] == separator) || (!text[c]))
        {
          XSTRING* string = new XSTRING();
          if(string)
            {
              Copy(start, (*string));

              for(XDWORD d=0; d<string->GetSize(); d++)
                {
                  if((string->Get()[d] == separator) || (!string->Get()[d]))
                    {
                      string->Get()[d] = 0;
                      break;
                    }
                }

              string->AdjustSize();

              if(addsubstringempty)
                {
                  if(c)
                        results.Add(string);
                   else delete string;
                }
               else
                {
                  if(string->GetSize())
                        results.Add(string);
                   else delete string;
                }

              start = c+1;

              if((XDWORD)start >= size) break;
            }
        }
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::FormatArg(const XCHAR* mask, va_list* arg, bool isspecialweb)
* @brief      FormatArg
* @ingroup    UTILS
*
* @param[in]  mask :
* @param[in]  arg :
* @param[in]  isspecialweb :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::FormatArg(const XCHAR* mask, va_list* arg, bool isspecialweb)
{
  XSTRING str;
  bool    openlabel = false;

  Empty();

  if(!mask) return false;

  int c  = 0;

  XCHAR* param = new XCHAR[16];
  if(param)
    {
      while(mask[c])
        {
          switch(mask[c])
            {
              case __C('%')   : {
                                  int  nparam = 1;
                                  bool end    = false;

                                  memset(param,0, 16*sizeof(XCHAR));
                                  param[0] = __C('%');

                                  c++;

                                  do{ param[nparam] = mask[c];

                                      nparam++;

                                      switch(mask[c])
                                        {
                                          case __C('c')   :
                                          case __C('C')   : { XCHAR character;

                                                              #if defined(LINUX) || defined(ANDROID) || defined(MICROCONTROLLER)
                                                              character = (XCHAR)va_arg((*arg), XDWORD);
                                                              #else
                                                              character = (XCHAR)va_arg((*arg), XCHAR);
                                                              #endif

                                                              str.Set(character);
                                                              end  = true ;
                                                            }
                                                            break;

                                          case __C('d')   :
                                          case __C('i')   :
                                          case __C('o')   :
                                          case __C('u')   :
                                          case __C('x')   :
                                          case __C('X')   : { bool large = false;
                                                              for(int l=0; l<(int)XSTRING::GetSize(param); l++)
                                                                {
                                                                  if(param[l] == __C('l')) large = true;
                                                                }

                                                              if(!large)
                                                                {
                                                                  int value = (int)va_arg((*arg), int);

                                                                  str.ConvertFromInt(value, param);
                                                                }
                                                               else
                                                                {
                                                                  str.ConvertFromLongLong((long long)va_arg((*arg), long long), param);
                                                                }
                                                              end  = true;
                                                            }
                                                            break;

                                          case __C('f')   : { double data = va_arg((*arg), double);

                                                              str.ConvertFromFloat((float)(data), param);
                                                              end  = true;
                                                            }
                                                            break;

                                          case __C('g')   :
                                          case __C('G')   : { double data = va_arg((*arg), double);

                                                              str.ConvertFromDouble(data, param);
                                                              end  = true;
                                                            }
                                                            break;

                                          case __C('e')   :
                                          case __C('E')   :

                                          case __C('n')   :
                                          case __C('p')   : end = true;
                                                            break;

                                          case __C('s')   :
                                          case __C('S')   : { str = (XCHAR*)va_arg((*arg),XCHAR*);

                                                              XSTRING sizestr;

                                                              sizestr = param;
                                                              if(sizestr.GetSize()>2)
                                                                {
                                                                  sizestr.ToUpperCase();
                                                                  sizestr.DeleteCharacter(__C('%'));
                                                                  sizestr.DeleteCharacter(__C('S'));

                                                                  if(!sizestr.IsEmpty())
                                                                    {
                                                                      int sizeadjust = sizestr.ConvertToInt();
                                                                      if(abs((int)sizeadjust) > (int)str.GetSize())
                                                                        {
                                                                          str.AdjustSize(abs((int)sizeadjust),(sizeadjust>0)?true:false, isspecialweb?__L("&nbsp"):__L(" "), isspecialweb);
                                                                        }
                                                                    }
                                                                }

                                                              end = true;
                                                            }
                                                            break;

                                          case __C('%')   : str = __L("%");
                                                            end = true;
                                                            break;

                                          case __C('\x0') : end = true;
                                                            break;

                                              default     : break;
                                        }

                                      c++;

                                    } while(!end);
                                }
                                break;

              case __C('<')   : { openlabel = true;
                                  XCHAR character[2]={ mask[c], 0 };
                                  str.Set(character);
                                  c++;
                                }
                                break;

              case __C('>')   : { openlabel = false;
                                  XCHAR character[2]={ mask[c], 0 };
                                  str.Set(character);
                                  c++;
                                }
                                break;

              case 0x0A       : if(isspecialweb && (!openlabel))
                                  {
                                    str = __L("<br />");
                                  }
                                 else
                                  {
                                    XCHAR character[2]={ mask[c], 0 };
                                    str.Set(character);
                                  }
                                c++;
                                break;

              case 0x20       : if(isspecialweb && (!openlabel))
                                  {
                                    str = __L("&nbsp");
                                  }
                                 else
                                  {
                                    XCHAR character[2]={ mask[c], 0 };
                                    str.Set(character);
                                  }
                                c++;
                                break;

                 default      : { XCHAR   character[2]={ mask[c], 0 };
                                  XDWORD  value       = (XDWORD)mask[c];

                                  if(isspecialweb && (!openlabel) && (value > 128))
                                        str.Format(__L("&#%d"), value);
                                   else str.Set(character);

                                  c++;
                                }
                                break;
            }

          Add(str);
        }

      delete [] param;
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::Format(const XCHAR* mask, ...)
* @brief      Format
* @ingroup    UTILS
*
* @param[in]  mask :
* @param[in]  ... :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::Format(const XCHAR* mask, ...)
{
  va_list arg;

  va_start(arg, mask);

  FormatArg(mask, &arg);

  va_end(arg);

  return 0;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::AddFormat(const XCHAR* mask, ...)
* @brief      AddFormat
* @ingroup    UTILS
*
* @param[in]  mask :
* @param[in]  ... :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::AddFormat(const XCHAR* mask, ...)
{
  XSTRING concat;
  va_list arg;

  va_start(arg, mask);

  concat.FormatArg(mask, &arg);

  va_end(arg);

  Add(concat.Get());

  return 0;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::UnFormat(const XCHAR* mask,...)
* @brief      UnFormat
* @ingroup    UTILS
*
* @param[in]  mask :
* @param[in]  ... :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::UnFormat(const XCHAR* mask,...)
{
  if(!size)    return false;
  if(!mask)    return false;
  if(!mask[0]) return false;
  if(!text)    return false;
  if(!text[0]) return false;

  va_list arg;
  va_start(arg, mask);

  XCHAR* param = new XCHAR[16];
  if(param)
    {
      int   nparam;
      bool  end;
      int   indextext = 0;
      int   c         = 0;
      bool  inbrackets  = false;

      while(mask[c])
        {
          switch(mask[c])
            {
              case __C('%')   : memset(param,0,16*sizeof(XCHAR));
                                param[0] = __C('%');

                                nparam = 1;
                                end    = false;

                                c++;

                                do{ param[nparam] = mask[c];

                                    nparam++;

                                    switch(mask[c])
                                      {
                                        case __C('c')   :
                                        case __C('C')   : { xcharvalue = (XCHAR*)va_arg(arg, XCHAR*);
                                                            if(xcharvalue) (*xcharvalue) = Get()[indextext];
                                                            indextext++;
                                                            end  = true;
                                                          }
                                                          break;

                                        case __C('d')   :
                                        case __C('i')   :
                                        case __C('o')   :
                                        case __C('u')   :
                                        case __C('x')   :
                                        case __C('X')   : { intvalue = (int*)va_arg(arg, int*);

                                                            if(intvalue) (*intvalue) = ConvertToInt(indextext,(XCHAR*)param, false);
                                                            end  = true;
                                                          }
                                                          break;

                                        case __C('f')   : { doublevalue = (double*)va_arg(arg, double*);

                                                            if(doublevalue) (*doublevalue) = ConvertToFloat(indextext,(XCHAR*)param, false);

                                                            end  = true;
                                                          }
                                                          break;

                                        case __C('g')   :
                                        case __C('G')   : { doublevalue = (double*)va_arg(arg, double*);

                                                            if(doublevalue) (*doublevalue) = ConvertToDouble(indextext,(XCHAR*)param, false);

                                                            end  = true;
                                                          }
                                                          break;

                                        case __C('e')   :
                                        case __C('E')   :

                                        case __C('n')   :
                                        case __C('p')   : end = true;
                                                          break;


                                        case __C('s')   :
                                        case __C('S')   : { xcharvalue = (XCHAR*)va_arg(arg,XCHAR*);
                                                            if(!xcharvalue) break;

                                                            XSTRING string;

                                                            int d = 0;
                                                            while(text[d+indextext]!=mask[c+1] /*&& text[d+indextext]!=__C(' ')*/)
                                                              {
                                                                if(!text[indextext+d]) break;
                                                                d++;
                                                              }

                                                            Copy(indextext, indextext+d, string);

                                                            if(nparam>2)
                                                              {
                                                                XSTRING strsizeparam = param;
                                                                int     sizeparam;

                                                                strsizeparam.DeleteCharacters(0,1);
                                                                strsizeparam.DeleteCharacters(strsizeparam.GetSize()-1,1);

                                                                sizeparam = abs((int)strsizeparam.ConvertToInt());
                                                                if(sizeparam)
                                                                  {
                                                                    if(string.GetSize()>(XDWORD)sizeparam)  string.DeleteCharacters(sizeparam, (string.GetSize()-sizeparam));
                                                                  }
                                                              }

                                                            memcpy((XBYTE*)xcharvalue, (XBYTE*)string.Get(), (string.GetSize()*sizeof(XCHAR)));
                                                            xcharvalue[string.GetSize()] = 0;

                                                            indextext += string.GetSize();

                                                            end = true;
                                                          }
                                                          break;

                                        case __C('%')   : end = true;
                                                          break;

                                        case __C('[')   : inbrackets  = true;
                                                          break;

                                        case __C(']')   : if(inbrackets)
                                                            {
                                                              xcharvalue = (XCHAR*)va_arg(arg, XCHAR*);

                                                              ConvertStringWithMask(param, &text[indextext], xcharvalue);
                                                              indextext += GetSize(xcharvalue);

                                                              if((mask[c+1] == __C('s')) || (mask[c+1] == __C('S'))) c++;
                                                              end = true;
                                                            }
                                                          break;

                                        case __C('\x0') : end = true;
                                                          break;

                                            default     : break;
                                      }

                                    c++;

                                    if(end)
                                      {
                                        if(mask[c]!=__C('%'))
                                          {
                                            while(text[indextext] != mask[c])
                                              {
                                                if(!text[indextext]) break;
                                                indextext++;
                                              }
                                          }
                                         else
                                          {
                                            //if(text[indextext] ==__C(' ')) indextext++;
                                          }
                                      }

                                  } while(!end);

                              break;

                    default : c++;
                              indextext++;
                              break;
            }
        }

     delete [] param;
   }

  va_end(arg);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::IsSpace(XCHAR xchar)
* @brief      IsSpace
* @ingroup    UTILS
*
* @param[in]  xchar :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::IsSpace(XCHAR xchar)
{
  if(xchar == 0x20) return true;  //  space
  if(xchar == 0x09) return true;  //  horizontal tab(TAB)
  if(xchar == 0x0a) return true;  //  newline(LF)
  if(xchar == 0x0b) return true;  //  vertical tab(VT)
  if(xchar == 0x0c) return true;  //  feed(FF)
  if(xchar == 0x0d) return true;  //  carriage return (CR)

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::IsDigit(XCHAR xchar)
* @brief      IsDigit
* @ingroup    UTILS
*
* @param[in]  xchar :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::IsDigit(XCHAR xchar)
{
  return (xchar >= __C('0') && xchar <= __C('9'));
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XSTRING::FindCharacterFromSet(const XCHAR* chars)
* @brief      FindCharacterFromSet
* @ingroup    UTILS
*
* @param[in]  XCHAR* chars :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XSTRING::FindCharacterFromSet(const XCHAR* chars)
{
  XCHAR   c;
  XCHAR*  s;
  XCHAR*  p;

  for(s = text, c = *s; c != 0; s++, c = *s)
    {
      for(p = (XCHAR*)chars; *p != 0; p++)
        {
          if(c == *p)
            {
              return (int)(s - text);
            }
        }
    }

  return (int)(s - text);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::AdjustSize(XDWORD size,bool ahead, XCHAR* characters, bool addstring)
* @brief      AdjustSize
* @ingroup    UTILS
*
* @param[in]  size :
* @param[in]  ahead :
* @param[in]  characters :
* @param[in]  addstring :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::AdjustSize(XDWORD size, bool ahead, XCHAR* characters, bool addstring)
{
  if(this->size == size) return false;

  int diference;

  if(this->size > size)
    {
       diference = (this->size- size);
       DeleteCharacters(size,diference);
    }
   else
    {
      if(characters)
        {
          if(ahead)
            {
              XSTRING string;

              diference = (size-this->size);
              for(int c=0;c<diference;c++)
                {
                  if(addstring) string.Add(characters); else string.Add(characters[0]);
                }

              string+=Get();

              Set(string);

            }
           else
            {
              diference = ((size)-this->size);
              for(int c=0;c<diference;c++)
                {
                  if(addstring) Add(characters);  else Add(characters[0]);
                }
            }
        }
       else
        {
          diference = ((size)-this->size);

          ReAllocBuffer(size);
          if(ahead)
            {
              for(int c=0;c<diference;c++)
                {
                  text[c+diference] = text[c];
                  text[c] = __C('-');
                }
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::AdjustSize()
* @brief      AdjustSize
* @ingroup    UTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::AdjustSize()
{
  int c;

  for(c=0;c<(int)size;c++)
    {
      if(!text[c]) break;
    }

  if(!c)
    {
      return FreeBuffer();
    }

  return AdjustSize(c, false, __L(" "), false);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::BinaryCompare(XSTRING& string)
* @brief      BinaryCompare
* @ingroup    UTILS
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::BinaryCompare(XSTRING& string)
{
  if(size != string.size)
    {
      return false;
    }

  return memcmp(text, string.text, size*sizeof(XCHAR)) == 0;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::Explode(XCHAR token, XVECTOR<XSTRING*>* receive)
* @brief      Explode
* @ingroup    UTILS
*
* @param[in]  token :
* @param[in]  receive :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::Explode(XCHAR token, XVECTOR<XSTRING*>* receive)
{
  int start = 0;

  do{ int end = FindCharacter(token,start);
      if(end==NOTFOUND) end = size;

      if((end-start)>0)
        {
          XSTRING* tok=new XSTRING();
          if(!tok)  return false;

          Copy(start, end, (*tok));

          if(!receive->Add(tok))
            {
              delete(tok);
              return false;
            }
        }

      start=end+1;

    } while(start < (int)size);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::GetTypeOfLineEnd(XSTRING& lineend)
* @brief      GetTypeOfLineEnd
* @ingroup    UTILS
*
* @param[in]  lineend :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::GetTypeOfLineEnd(XSTRING& lineend)
{
  //----------------
  // \n      x        0
  // \r      x        1
  // \n      \r       2
  // \r      \n       3

  int combinations[4] = { 0, 0, 0, 0 };

  if(GetSize()<2) return false;

  for(XDWORD c=0; c<GetSize()-1; c++)
    {
      if(Get()[c] == __C('\n'))
        {
          if(Get()[c+1] == __C('\r'))
            {
              combinations[2]++;
              c+=2;

            } else combinations[0]++;
        }
       else
        {
          if(Get()[c] == __C('\r'))
            {
              if(Get()[c+1] == __C('\n'))
                {
                  combinations[3]++;
                  c+=2;
                }
               else combinations[1]++;
            }
        }
    }

  if((combinations[0] >= combinations[1]) && (combinations[0] >= combinations[2]) && (combinations[0] >= combinations[3]))
    {
      lineend = __L("\n");
    }
   else
    {
      if((combinations[1] >= combinations[0]) && (combinations[1] >= combinations[2]) && (combinations[1] >= combinations[3]))
        {
          lineend = __L("\r");
        }
       else
        {
          if((combinations[2] >= combinations[0]) && (combinations[2] >= combinations[1]) && (combinations[2] >= combinations[3]))
            {
              lineend = __L("\n\r");
            }
           else
            {
              if((combinations[3] >= combinations[0]) && (combinations[3] >= combinations[1]) && (combinations[3] >= combinations[2]))
                {
                  lineend = __L("\r\n");
                }
            }
        }
    }

  return lineend.GetSize()?true:false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE XSTRING::ConvertXCHARToBase64(XCHAR character)
* @brief      ConvertXCHARToBase64
* @ingroup    UTILS
*
* @param[in]  character : 
*
* @return     XBYTE : 
*
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE XSTRING::ConvertXCHARToBase64(XCHAR character)
{
  for(XBYTE c=0;c<(XBYTE)XSTRING_SIZETABLE64BITS;c++)
    {
      if(table64bits[c]==character) return c;
    }

  return 0;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ReAllocBuffer(XDWORD size)
* @brief      ReAllocBuffer
* @ingroup    UTILS
*
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
/*
bool XSTRING::ReAllocBuffer(XDWORD size)
{
  if(!size)
    {
      FreeBuffer();
    }
   else
    {
      int nblocks  = (size / XSTRING_BLOCKMEM) + 1;

      XDWORD sizemem = (nblocks * XSTRING_BLOCKMEM);

      if(!text)
        {
          text = new XCHAR[sizemem+1];
          if(!text) return false;

          memset(text, 0, (sizemem+1) * sizeof(XCHAR));

          this->sizemem = sizemem;
        }
       else
        {
          if(size >= this->sizemem)
            {
              XCHAR* ttext = new XCHAR[sizemem+1];
              if(!ttext) return false;

              memset(ttext, 0, (sizemem+1) * sizeof(XCHAR));

              XDWORD tsize = size;
              if(tsize>this->size) tsize = this->size;

              memcpy(ttext, text, tsize * sizeof(XCHAR));

              FreeBuffer();

              text = ttext;

              this->sizemem = sizemem;
            }
           else
            {
              // culd we have an off by one error here?
              // size is index zero, not reall an off by one problem here
               memset(&text[size], 0, (this->sizemem - size)* sizeof(XCHAR));
               text[size] = '\0';
            }
        }

      this->size    = size;
    }

  return true;
}
*/
bool XSTRING::ReAllocBuffer(XDWORD size)
{
  if(!size)
    {
      FreeBuffer();
    }
   else
    {
      XDWORD nblocks  = (XDWORD)(size / XSTRING_BLOCKMEM);
      
      nblocks++;

      XDWORD _sizemem = (nblocks * XSTRING_BLOCKMEM);
      
      _sizemem++;

      if(!text)
        {
          text = new XCHAR[_sizemem];
          if(!text) return false;

          memset(text, 0, (_sizemem * sizeof(XCHAR)));

          this->sizemem = _sizemem;
        }
       else
        {
          if(size >= this->sizemem)
            {
              XCHAR* ttext = new XCHAR[_sizemem];
              if(!ttext) return false;

              memset(ttext, 0, (_sizemem * sizeof(XCHAR)));

              XDWORD tsize = size;
              if(tsize>this->size) tsize = this->size;

              memcpy(ttext, text, tsize * sizeof(XCHAR));

              FreeBuffer();

              text = ttext;

              this->sizemem = _sizemem;
            }
           else
            {
              // culd we have an off by one error here?
              // size is index zero, not reall an off by one problem here
               memset(&text[size], 0, (this->sizemem - size)* sizeof(XCHAR));
               text[size] = '\0';
            }
        }

      this->size    = size;
    }

  return true;
}







/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::FreeBuffer()
* @brief      FreeBuffer
* @ingroup    UTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::FreeBuffer()
{
  if(!text) return false;

  delete [] text;

  text    = NULL;
  size    = 0;
  sizemem = 0;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XCHAR XSTRING::ConvertIndexBase64ToXCHAR(int index)
* @brief      ConvertIndexBase64ToXCHAR
* @ingroup    UTILS
*
* @param[in]  index :
*
* @return     XCHAR :
*
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR XSTRING::ConvertIndexBase64ToXCHAR(int index)
{
  if(index>=(int)XSTRING_SIZETABLE64BITS) return 0;
  if(index<0)                             return 0;

  return table64bits[index];
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ConvertStringWithMask(XCHAR* mask, XCHAR* string, XCHAR* result)
* @brief      ConvertStringWithMask
* @ingroup    UTILS
*
* @param[in]  mask :
* @param[in]  string :
* @param[in]  result :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertStringWithMask(XCHAR* mask, XCHAR* string, XCHAR* result)
{
  XSTRING  _mask;
  XSTRING  _string;
  XSTRING  _result;

  _mask   = mask;
  _string = string;


  char* resultchar = new char[XSTRING_MAXTEMPOSTR];
  if(!resultchar) return false;

  memset(resultchar, 0, XSTRING_MAXTEMPOSTR);

  XSTRING_CREATEOEM(_mask   , maskchar)
  XSTRING_CREATEOEM(_string , stringchar)

  SSCANF(stringchar, maskchar, resultchar, XSTRING_MAXTEMPOSTR);

  XSTRING_DELETEOEM(_mask, maskchar)
  XSTRING_DELETEOEM(_string, stringchar)

  _result = resultchar;

  memcpy(result, _result.Get(), ((_result.GetSize()+1)*sizeof(XCHAR)));

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSTRING::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    UTILS
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XSTRING::Clean()
{
  text        = NULL;
  size        = 0;

  sizemem     = 0;

  intvalue    = NULL;
  doublevalue = NULL;
  xcharvalue  = NULL;

  if(!istable64bitsinit)
    {
      istable64bitsinit = true;
      memcpy(table64bits, (XCHAR*)XSTRING_TABLE64BITS, XSTRING_SIZETABLE64BITS * sizeof(XCHAR));
    }
}

#endif

