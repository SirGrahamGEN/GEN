/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XString.cpp
* 
* @class      XSTRING
* @brief      eXtended Utils Unicode String class
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

#if defined(APPMODE_API_LIB_EXPORT_ACTIVE) || !defined(APPMODE_API_LIB_ACTIVE)

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XString.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include "XFactory.h"
#include "XBase.h"
#include "XBuffer.h"
#include "XTrace.h"
#include "XThread.h"
#include "XTranslation.h"
#include "XTranslation_GEN.h"
#include "XTranslation.h"
#include "XLanguage_ISO_639_3.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

const char XSTRING::codetablebase64[]   = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const char XSTRING::decodetablebase64[] = "|$$$}rstuvwxyz{$$$$$$$>?@ABCDEFGHIJKLMNOPQRSTUVW$$$$$$XYZ[\\]^_`abcdefghijklmnopq";

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING::XSTRING()
* @brief      Constructor of class
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING::XSTRING()
{
  Clean();

  GEN_XFACTORY_CREATE(xmutexfreemen, Create_Mutex());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING::XSTRING(XDWORD size)
* @brief      Constructor of class
* @ingroup    XUTILS
*
* @param[in]  size :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING::XSTRING(XDWORD size)
{
  Clean();

  GEN_XFACTORY_CREATE(xmutexfreemen, Create_Mutex());

  ReAllocBuffer(size);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING::XSTRING(const char* string)
* @brief      Constructor of class
* @ingroup    XUTILS
*
* @param[in]  string :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING::XSTRING(const char* string)
{
  Clean();

  GEN_XFACTORY_CREATE(xmutexfreemen, Create_Mutex());

  Set(string);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING::XSTRING(const XCHAR* string)
* @brief      Constructor of class
* @ingroup    XUTILS
* 
* @param[in]  string : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING::XSTRING(const XCHAR* string)
{
  Clean();

  GEN_XFACTORY_CREATE(xmutexfreemen, Create_Mutex());

  Set(string);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING::XSTRING(const XCHAR* string, XDWORD size)
* @brief      Constructor of class
* @ingroup    XUTILS
*
* @param[in]  string :
* @param[in]  size :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING::XSTRING(const XCHAR* string, XDWORD size)
{
  Clean();

  GEN_XFACTORY_CREATE(xmutexfreemen, Create_Mutex());

  Set(string,size);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING::XSTRING(const XSTRING& string)
* @brief      Constructor of class
* @ingroup    XUTILS
*
* @param[in]  string :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING::XSTRING(const XSTRING& string)
{
  Clean();

  GEN_XFACTORY_CREATE(xmutexfreemen, Create_Mutex());

  Set(string);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING::XSTRING(XWORD* string)
* @brief      Constructor of class
* @ingroup    XUTILS
*
* @param[in]  string :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING::XSTRING(XWORD* string)
{
  Clean();

  GEN_XFACTORY_CREATE(xmutexfreemen, Create_Mutex());

  Set(string);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING::~XSTRING()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING::~XSTRING()
{
  FreeBuffer();

  GEN_XFACTORY.Delete_Mutex(xmutexfreemen);
  
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XCHAR* XSTRING::Get() const
* @brief      Get
* @ingroup    XUTILS
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
* @brief      Get size
* @ingroup    XUTILS
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
* @brief      Get size
* @ingroup    XUTILS
*
* @param[in]  string :
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
* @brief      Get size
* @ingroup    XUTILS
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
* @fn         XSTRINGCODING XSTRING::GetTypeCoding()
* @brief      Get type coding
* @ingroup    XUTILS
* 
* @return     XSTRINGCODING : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRINGCODING XSTRING::GetTypeCoding()
{
  XSTRINGCODING coding = XSTRINGCODING_UNKWOWN;

  switch(sizeof(XCHAR)) 
    {
      case 02 : coding = XSTRINGCODING_UTF16; 
                break;

      case 04 : coding = XSTRINGCODING_UTF32; 
                break;
    }

  return coding;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::Set(XDWORD size)
* @brief      Set
* @ingroup    XUTILS
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
* @ingroup    XUTILS
*
* @param[in]  string :
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
* @ingroup    XUTILS
*
* @param[in]  string :
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
* @ingroup    XUTILS
*
* @param[in]  string :
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
* @ingroup    XUTILS
*
* @param[in]  string :
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
* @ingroup    XUTILS
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
* @ingroup    XUTILS
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
* @ingroup    XUTILS
*
* @param[in]  str1 :
* @param[in]  str2 :
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
* @ingroup    XUTILS
*
* @param[in]  buffer :
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
* @ingroup    XUTILS
*
* @param[in]  buffer :
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
* @ingroup    XUTILS
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
* @ingroup    XUTILS
*
* @param[in]  string :
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
* @ingroup    XUTILS
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::Add(const XCHAR* string)
{
  if(!string)     
    {
      return false;
    }

  if(!string[0]) 
    {
      return false;
    }

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
* @ingroup    XUTILS
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

  if(string.IsEmpty()) 
    {
      return false;
    }

  if(string.Get())
    {
      if(!string.Get()[0]) 
        {
          return false;
        }
    }

  if(!tsize) 
    {
      return false;
    }

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
* @ingroup    XUTILS
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
* @ingroup    XUTILS
*
* @param[in]  str1 :
* @param[in]  str2 :
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
* @ingroup    XUTILS
*
* @param[in]  buffer :
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
* @ingroup    XUTILS
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
* @ingroup    XUTILS
*
* @param[in]  string :
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
* @ingroup    XUTILS
*
* @param[in]  string :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XSTRING::operator =  (const XCHAR* string)
{
  Set(string);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XSTRING::operator = (const XSTRING& string)
* @brief      operator = 
* @ingroup    XUTILS
* 
* @param[in]  string : 
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
* @ingroup    XUTILS
*
* @param[in]  string :
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
* @ingroup    XUTILS
*
* @param[in]  string :
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
* @ingroup    XUTILS
*
* @param[in]  string :
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
* @ingroup    XUTILS
*
* @param[in]  string :
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
* @ingroup    XUTILS
*
* @param[in]  string :
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
* @ingroup    XUTILS
*
* @param[in]  character :
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
* @ingroup    XUTILS
*
* @param[in]  string :
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
* @ingroup    XUTILS
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
* @ingroup    XUTILS
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
* @ingroup    XUTILS
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
* @ingroup    XUTILS
*
* @param[in]  string :
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
* @ingroup    XUTILS
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
* @ingroup    XUTILS
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
* @brief      Fill char
* @ingroup    XUTILS
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
* @ingroup    XUTILS
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
* @brief      Is empty
* @ingroup    XUTILS
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
* @brief      Have characters
* @ingroup    XUTILS
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
* @brief      Have only numbers
* @ingroup    XUTILS
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
* @fn         bool XSTRING::HaveNumbers()
* @brief      Have numbers
* @ingroup    XUTILS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::HaveNumbers()
{
  if(IsEmpty()) return false;

  for(XDWORD c=0;c<size;c++)
    {
      if(!text[c]) break;
      if(Character_IsNumber(text[c])) return true;
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::DeleteCharacters(XDWORD index, XDWORD ncharacteres)
* @brief      Delete characters
* @ingroup    XUTILS
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
* @brief      Delete characters to end
* @ingroup    XUTILS
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
* @brief      Delete character
* @ingroup    XUTILS
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
* @brief      Delete no characters
* @ingroup    XUTILS
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
* @brief      Delete no characters
* @ingroup    XUTILS
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
* @brief      Delete last character
* @ingroup    XUTILS
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
* @fn         bool XSTRING::DeleteLastZeros()
* @brief      Delete last zeros
* @ingroup    XUTILS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::DeleteLastZeros()
{
  int  index  = GetSize()-1;
  bool status = false;

  if(index <= 0) 
    {
      return false;
    }

  while(Character_GetLast () == __C('0'))
    {
      DeleteLastCharacter();
      status = true;
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::Character_IsAlpha(XCHAR character) const
* @brief      Character is alpha
* @ingroup    XUTILS
*
* @param[in]  character :
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
* @brief      Character is upper case
* @ingroup    XUTILS
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
* @brief      Character is lower case
* @ingroup    XUTILS
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
* @fn         bool XSTRING::Character_IsNumber(XCHAR character, bool isextended)
* @brief      Character is number
* @ingroup    XUTILS
* 
* @param[in]  character : 
* @param[in]  isextended : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::Character_IsNumber(XCHAR character, bool isextended)
{  
  if((character >= __C('0')) && (character <= '9'))  return true;

  if(!isextended)
    {
      return false;
    }

  if(character == __C('.')) return true;
  if(character == __C(',')) return true;
  if(character == __C('-')) return true;
  if(character == __C('E')) return true;
  if(character == __C('+')) return true;

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::Character_IsNOT(XCHAR character)
* @brief      Character is NOT
* @ingroup    XUTILS
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
* @brief      Character to upper
* @ingroup    XUTILS
*
* @param[in]  character :
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
* @brief      Character to lower
* @ingroup    XUTILS
*
* @param[in]  character :
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
* @brief      Character get first
* @ingroup    XUTILS
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
* @brief      Character get last
* @ingroup    XUTILS
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
* @brief      Character change
* @ingroup    XUTILS
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
* @fn         bool XSTRING::IsNumber()
* @brief      Is number
* @ingroup    XUTILS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::IsNumber()
{
  if(IsEmpty()) return false;

  for(XDWORD c=0;c<size;c++)
    {      
      if(!Character_IsNumber(text[c])) return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSTRING::IsDecimalNumber(int* ndecimals)
* @brief      Is decimal number
* @ingroup    XUTILS
* 
* @param[in]  ndecimals : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::IsDecimalNumber(int* ndecimals)
{
  if(ndecimals)
    {
      (*ndecimals) = 0;
    }

  if(IsEmpty()) 
    {
      return false;
    }

  if(!IsNumber())
    {
      return false;
    }
  
  bool found = false;

  for(XDWORD c=0;c<size;c++)
    {      
      if((text[c] == __C('.')) || (text[c] == __C(',')))
        {          
          (*ndecimals) = (size - c);

          found = true;
          break;
        }
    }

  return found;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ToUpperCase()
* @brief      To upper case
* @ingroup    XUTILS
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
* @brief      To lower case
* @ingroup    XUTILS
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
* @ingroup    XUTILS
*
* @param[in]  string :
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
* @ingroup    XUTILS
*
* @param[in]  string :
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
* @ingroup    XUTILS
*
* @param[in]  string :
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
* @ingroup    XUTILS
*
* @param[in]  string :
* @param[in]  string2 :
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
* @ingroup    XUTILS
*
* @param[in]  string :
* @param[in]  ignorecase :
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
* @ingroup    XUTILS
*
* @param[in]  string :
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
* @ingroup    XUTILS
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
* @brief      Find character
* @ingroup    XUTILS
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
* @brief      Count character
* @ingroup    XUTILS
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
* @brief      Find diferent character
* @ingroup    XUTILS
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
* @brief      Get N characters
* @ingroup    XUTILS
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
* @brief      Are valid characters
* @ingroup    XUTILS
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
* @ingroup    XUTILS
*
* @param[in]  startmark :
* @param[in]  endmark :
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
* @ingroup    XUTILS
*
* @param[in]  startindex :
* @param[in]  endmark :
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
* @ingroup    XUTILS
*
* @param[in]  startmark :
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
* @ingroup    XUTILS
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
* @ingroup    XUTILS
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
* @ingroup    XUTILS
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

      if (found!=XSTRING_NOTFOUND)
        coincidences++;
      else
        break;
    } while(1);

  return coincidences;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XSTRING::ReplaceFirst(XCHAR* findwhat, XCHAR* replaceby)
* @brief      Replace first
* @ingroup    XUTILS
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

  found = Find(findwhat, false, found);
  if(found != XSTRING_NOTFOUND)
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
* @ingroup    XUTILS
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
* @fn         bool XSTRING::ConvertFromNULL(bool uppercase)
* @brief      Convert from NULL
* @ingroup    XUTILS
* 
* @param[in]  uppercase : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertFromNULL(bool uppercase)
{
  Set(uppercase? __L("NULL") : __L("null"));

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSTRING::ConvertFromBoolean(bool boolean, XBYTE mode)
* @brief      Convert from boolean
* @ingroup    XUTILS
* 
* @param[in]  boolean : 
* @param[in]  mode : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertFromBoolean(bool boolean, XBYTE mode)
{
  Empty();

  if((mode & XSTRINGBOOLEANMODE_COMPUTER) == XSTRINGBOOLEANMODE_COMPUTER)
    {
      Set(boolean?XT_L(XTRANSLATION_GEN_ID_TRUE):XT_L(XTRANSLATION_GEN_ID_FALSE));
    }
    
  if((mode & XSTRINGBOOLEANMODE_HUMAN) == XSTRINGBOOLEANMODE_HUMAN)
    {
      Set(boolean?XT_L(XTRANSLATION_GEN_ID_YES):XT_L(XTRANSLATION_GEN_ID_NO));
    }

  if((mode & XSTRINGBOOLEANMODE_UPPERCASE) == XSTRINGBOOLEANMODE_UPPERCASE)
    {
      ToUpperCase();
    }

  if((mode & XSTRINGBOOLEANMODE_LOWERCASE) == XSTRINGBOOLEANMODE_LOWERCASE)
    {
      ToLowerCase();
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSTRING::ConvertFromShort(short value, const XCHAR* mask)
* @brief      Convert from short
* @ingroup    XUTILS
* 
* @param[in]  value : 
* @param[in]  mask : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertFromShort(short value, const XCHAR* mask)
{
  char*     str;
  XSTRING  _mask;

  str = new char[XSTRING_MAXTEMPOSTR];
  if(!str) return false;

  memset(str,0,XSTRING_MAXTEMPOSTR);

  if(mask) _mask = mask; else _mask = __L("%hd");

  XBUFFER charstr;
  
  _mask.ConvertToASCII(charstr);
  SPRINTF(str, charstr.GetPtrChar(), value);
  
  Set(str);

  delete [] str;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSTRING::ConvertFromWord(XWORD value, const XCHAR* mask)
* @brief      Convert from word
* @ingroup    XUTILS
* 
* @param[in]  value : 
* @param[in]  mask : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertFromWord(XWORD value, const XCHAR* mask)
{
  char*     str;
  XSTRING  _mask;

  str = new char[XSTRING_MAXTEMPOSTR];
  if(!str) return false;

  memset(str,0,XSTRING_MAXTEMPOSTR);

  if(mask) _mask = mask; else _mask = __L("%hu");

  XBUFFER charstr;
  
  _mask.ConvertToASCII(charstr);
  SPRINTF(str, charstr.GetPtrChar(), value);
  
  Set(str);

  delete [] str;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ConvertFromInt(int value, const XCHAR* mask)
* @brief      Convert from int
* @ingroup    XUTILS
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


  XBUFFER charstr;
  
  _mask.ConvertToASCII(charstr);
  SPRINTF(str, charstr.GetPtrChar(), value);
  
  Set(str);

  delete [] str;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ConvertFromDWord(XDWORD value, const XCHAR* mask)
* @brief      Convert from D word
* @ingroup    XUTILS
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

  XBUFFER charstr;
  
  _mask.ConvertToASCII(charstr);
  SPRINTF(str, charstr.GetPtrChar(), value);

  Set(str);

  delete [] str;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ConvertFromLongLong(long long value, const XCHAR* mask)
* @brief      Convert from long long
* @ingroup    XUTILS
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

  XBUFFER charstr;
  
  _mask.ConvertToASCII(charstr); 
  SPRINTF(str, charstr.GetPtrChar(), (long long)value);
  
  Set(str);

  delete [] str;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ConvertFromQWord(XQWORD value, const XCHAR* mask)
* @brief      Convert from Q word
* @ingroup    XUTILS
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

  if(mask) _mask = mask; else _mask = __L("%llu");

  XBUFFER charstr;
  
  _mask.ConvertToASCII(charstr);
  SPRINTF(str, charstr.GetPtrChar(), value);

  Set(str);

  delete [] str;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ConvertFromFloat(float value, const XCHAR* mask)
* @brief      Convert from float
* @ingroup    XUTILS
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

  XBUFFER charstr;
  
  _mask.ConvertToASCII(charstr); 
  SPRINTF(str, charstr.GetPtrChar(), value);
  
  Set(str);

  delete [] str;

  if(_mask.GetSize() == 2)
    {
      DeleteLastZeros();
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ConvertFromDouble(double value, const XCHAR* mask)
* @brief      Convert from double
* @ingroup    XUTILS
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

  if(mask) _mask = mask; else _mask = __L("%lf");
  
  XBUFFER charstr;
  
  _mask.ConvertToASCII(charstr); 
  SPRINTF(str, charstr.GetPtrChar(), value);
  
  Set(str);

  delete [] str;

  if(_mask.GetSize() == 2)
    {
      DeleteLastZeros();
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ConvertHexFormatChars()
* @brief      Convert hex format chars
* @ingroup    XUTILS
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
* @brief      Convert to hex string
* @ingroup    XUTILS
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
* @brief      Convert hex string to buffer
* @ingroup    XUTILS
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
* @brief      Convert hex string from buffer
* @ingroup    XUTILS
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
* @fn         bool XSTRING::ConvertToBoolean()
* @brief      Convert to boolean
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertToBoolean()
{
  bool result = false;

  if(!Compare(XT_L(XTRANSLATION_GEN_ID_YES)    , true)  || 
     !Compare(XT_L(XTRANSLATION_GEN_ID_TRUE)   , true))
    {
      result = true;
    }
   else
    {
      if(!Compare(XT_L(XTRANSLATION_GEN_ID_NO)    , true) || 
         !Compare(XT_L(XTRANSLATION_GEN_ID_FALSE) , true) || 
         !Compare(__L("0")     , true))                   
        {
          result = false;
        }
       else
        {
          if(!IsEmpty()) 
            {
              result = true;
            }
        }
    }

  return result;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XSTRING::ConvertToInt(int index, const XCHAR* mask, bool checkvalidchars)
* @brief      Convert to int
* @ingroup    XUTILS
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
    
    
  XBUFFER charstr;
  XBUFFER charstr2;
  
  _mask.ConvertToASCII(charstr);     
  (*this).ConvertToASCII(charstr2);         
  
  SSCANF(&charstr2.GetPtrChar()[index], charstr.GetPtrChar(), &data);
 
  return data;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XSTRING::ConvertToDWord(int index, const XCHAR* mask, bool checkvalidchars)
* @brief      Convert to D word
* @ingroup    XUTILS
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
  
  XBUFFER charstr;
  XBUFFER charstr2;
  
  _mask.ConvertToASCII(charstr);     
  (*this).ConvertToASCII(charstr2);   

  SSCANF(&charstr2.GetPtrChar()[index], charstr.GetPtrChar(), &data);

  return data;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         long long XSTRING::ConvertToLongLong(int index, const XCHAR* mask, bool checkvalidchars)
* @brief      Convert to long long
* @ingroup    XUTILS
* 
* @param[in]  index : 
* @param[in]  mask : 
* @param[in]  checkvalidchars : 
* 
* @return     long : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
long long XSTRING::ConvertToLongLong(int index, const XCHAR* mask, bool checkvalidchars)
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

  XBUFFER charstr;
  XBUFFER charstr2;
  
  _mask.ConvertToASCII(charstr);     
  (*this).ConvertToASCII(charstr2);   

  SSCANF(&charstr2.GetPtrChar()[index], charstr.GetPtrChar(), &data);

  return data;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XQWORD XSTRING::ConvertToQWord(int index, const XCHAR* mask, bool checkvalidchars)
* @brief      Convert to Q word
* @ingroup    XUTILS
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
  XQWORD   data = 0;

  if(mask) _mask = mask; else _mask = __L("%lld");

  XBUFFER charstr;
  XBUFFER charstr2;
  
  _mask.ConvertToASCII(charstr);     
  (*this).ConvertToASCII(charstr2);   

  SSCANF(&charstr2.GetPtrChar()[index], charstr.GetPtrChar(), &data);

  return data;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float XSTRING::ConvertToFloat(int index, const XCHAR* mask, bool checkvalidchars)
* @brief      Convert to float
* @ingroup    XUTILS
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

  XBUFFER charstr;
  XBUFFER charstr2;
  
  _mask.ConvertToASCII(charstr);     
  (*this).ConvertToASCII(charstr2);   

  SSCANF(&charstr2.GetPtrChar()[index], charstr.GetPtrChar(), &data);

  return data;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         double XSTRING::ConvertToDouble(int index, const XCHAR* mask, bool checkvalidchars)
* @brief      Convert to double
* @ingroup    XUTILS
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

  XBUFFER charstr;
  XBUFFER charstr2;
  
  _mask.ConvertToASCII(charstr);     
  (*this).ConvertToASCII(charstr2);   

  SSCANF(&charstr2.GetPtrChar()[index], charstr.GetPtrChar(), &data);

  return data;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSTRING::IsValidASCII()
* @brief      Is valid ASCII
* @ingroup    XUTILS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::IsValidASCII()
{
  for(int c=0;c<(int)size;c++)
    {
      if((text[c]<0x20) || (text[c]>0x7F)) return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSTRING::ConvertToASCII(XBUFFER& xbuffer)
* @brief      Convert to ASCII
* @ingroup    XUTILS
* 
* @param[in]  xbuffer : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertToASCII(XBUFFER& xbuffer)
{   
  xbuffer.Empty();

  for(XDWORD c=0; c<size; c++)
    {    
      if(text[c]<0x80) 
        {                    
          xbuffer.Add((XBYTE)(text[c]));
        }
       else
        {
          xbuffer.Add((XBYTE)'_');
        } 
    }

  xbuffer.Add((XBYTE)0x00);

  return true;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSTRING::ConvertFromASCII(XBUFFER& xbuffer)
* @brief      Convert from ASCII
* @ingroup    XUTILS
* 
* @param[in]  xbuffer : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertFromASCII(XBUFFER& xbuffer)
{
  if(xbuffer.IsEmpty()) return false;

  Empty();

  for(XDWORD c=0; c<xbuffer.GetSize()-1; c++)
    {
      XCHAR character = (XCHAR)(xbuffer.Get()[c]);

      Add((XCHAR)character);      
    }
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSTRING::ConvertToXBuffer(XBUFFER& xbuffer)
* @brief      Convert to X buffer
* @ingroup    XUTILS
* 
* @param[in]  xbuffer : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertToXBuffer(XBUFFER& xbuffer)
{
  bool status = false;

  if(IsEmpty()) return size;

  xbuffer.Empty();

  switch(GetTypeCoding())
    {
      case XSTRINGCODING_UTF16  : { for(XDWORD c=0; c<size; c++)
                                      {
                                        xbuffer.Add((XWORD)text[c]);
                                      }
                                  
                                    status = true;  
                                  }
                                  break;  

      case XSTRINGCODING_UTF32  : { for(XDWORD c=0; c<size; c++)
                                      {
                                        xbuffer.Add((XDWORD)text[c]);
                                      }
                                  
                                    status = true;  
                                  }
                                  break;  
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSTRING::ConvertFromXBuffer(XBUFFER& xbuffer, XSTRINGCODING buffercoding)
* @brief      Convert from X buffer
* @ingroup    XUTILS
* 
* @param[in]  xbuffer : 
* @param[in]  buffercoding : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertFromXBuffer(XBUFFER& xbuffer, XSTRINGCODING buffercoding)
{  
  bool status = false;

  if(xbuffer.IsEmpty()) return false;

  Empty();

  switch(GetTypeCoding())
    {
      case XSTRINGCODING_UTF16  : switch(buffercoding)
                                    {
                                      case XSTRINGCODING_UNKWOWN  : 
                                      case XSTRINGCODING_ASCII    : 
                                                                    { xbuffer.ResetPosition();

                                                                      for(XDWORD c=0; c<xbuffer.GetSize(); c++)
                                                                        {
                                                                          XBYTE character;

                                                                          xbuffer.Get(character);
                                                                          Add((XCHAR)character);
                                                                        }                                                                                                        
                                                                    }
                                                                    status = true; 
                                                                    break;

                                      case XSTRINGCODING_UTF8     : ConvertFromUTF8(xbuffer);
                                                                    status = true;
                                                                    break;

                                      case XSTRINGCODING_UTF16    : { xbuffer.ResetPosition();

                                                                      for(XDWORD c=0; c<xbuffer.GetSize(); c++)
                                                                        {
                                                                          XWORD character;

                                                                          xbuffer.Get(character);
                                                                          Add((XCHAR)character);
                                                                        }                                                                                                        
                                                                    }
                                                                    status = true;  
                                                                    break;

                                      case XSTRINGCODING_UTF32    : { xbuffer.ResetPosition();

                                                                      for(size_t c=0; c<xbuffer.GetSize(); c++) 
                                                                        {
                                                                          XDWORD value = 0;

                                                                          xbuffer.Get(value);
                                                                          if (value > 0xFFFF) 
                                                                            {
                                                                              value -= 0x10000;

                                                                              XDWORD lo = ((XWORD)(0xD800 | (value >> 10)));   
                                                                              XDWORD hi = ((XWORD)(0xDC00 | (value & 0x3FF)));

                                                                              //XCHAR character = ((hi<<16) | lo);  
                                                                              //Add((XCHAR)character);

                                                                              Add((XCHAR)(0xD800 | (value >> 10)));
                                                                              Add((XCHAR)(0xDC00 | (value & 0x3FF)));
                                                                            } 
                                                                           else 
                                                                            {
                                                                              Add((XCHAR)value);
                                                                            }
                                                                        }                                                                       
                                                                    } 
                                                                    status = true;              
                                                                    break;

                                    }
                                  break;
  
      case XSTRINGCODING_UTF32  : switch(buffercoding)
                                    {
                                      case XSTRINGCODING_UNKWOWN  :
                                      case XSTRINGCODING_ASCII    : { xbuffer.ResetPosition();

                                                                      for(XDWORD c=0; c<xbuffer.GetSize(); c++)
                                                                        {
                                                                          XBYTE character;

                                                                          xbuffer.Get(character);
                                                                          Add((XCHAR)character);
                                                                        }                                                                                                        
                                                                    }
                                                                    status = true;  
                                                                    break;    

                                      case XSTRINGCODING_UTF8     : ConvertFromUTF8(xbuffer);
                                                                    status = true;  
                                                                    break;

                                      case XSTRINGCODING_UTF16    : { xbuffer.ResetPosition();

                                                                      for(size_t c=0; c<xbuffer.GetSize(); c++) 
                                                                        {
                                                                          XWORD value;
                                                                          xbuffer.Get(value);

                                                                          if(value >= 0xD800 && value <= 0xDBFF && c + 1 < xbuffer.GetSize()) 
                                                                            {
                                                                              XWORD low;
                                                                              xbuffer.Get(low);

                                                                              if(low >= 0xDC00 && low <= 0xDFFF) 
                                                                                {
                                                                                  XDWORD value2 = ((value - 0xD800) << 10) + (low - 0xDC00) + 0x10000;
                                                                                  Add((XCHAR)value2);
                                                                                  c++;
                                                                                } 
                                                                               else 
                                                                                {
                                                                                  Add((XCHAR)value);
                                                                                }
                                                                            } 
                                                                           else 
                                                                            {
                                                                              Add((XCHAR)value);
                                                                            }
                                                                        }
                                                                    }
                                                                    status = true;  
                                                                    break;                                                                    

                                      case XSTRINGCODING_UTF32    : { xbuffer.ResetPosition();

                                                                      for(XDWORD c=0; c<xbuffer.GetSize(); c++)
                                                                        {
                                                                          XDWORD character;

                                                                          xbuffer.Get(character);
                                                                          Add((XCHAR)character);
                                                                        }                                                                                                          
                                                                    }
                                                                    status = true;
                                                                    break;

                                    }
                                  break;
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSTRING::ConvertToExchangeXBuffer(XBUFFER& xbuffer, bool addzeroatend, bool inverse)
* @brief      Convert to exchange X buffer
* @ingroup    XUTILS
* 
* @param[in]  xbuffer : 
* @param[in]  addzeroatend : 
* @param[in]  inverse : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertToExchangeXBuffer(XBUFFER& xbuffer, bool addzeroatend, bool inverse)
{
  if(!ConvertToUTF16(xbuffer)) return false;

  if(addzeroatend)
    {
      xbuffer.Add((XWORD)0);
    }

  if(inverse)
    {
      XWORD* data = (XWORD*)xbuffer.Get();
      if(data)
        {
          for(XDWORD c=0; c<(xbuffer.GetSize()/2); c++)
            {
              SWAPWORD(data[c])  
            }
        }
    }

  return true;

}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XSTRING::GetSizeConvertToUTF8()
* @brief      Get size convert to UTF8
* @ingroup    XUTILS
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
* @fn         bool XSTRING::ConvertFromUTF8(XBYTE* data,XDWORD size)
* @brief      Convert from UTF8
* @ingroup    XUTILS
*
* @param[in]  data :
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertFromUTF8(XBYTE* data, XDWORD size)
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
* @brief      Convert from UTF8
* @ingroup    XUTILS
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
* @fn         bool XSTRING::ConvertToUTF8(XBYTE* data, int& size, bool addzeroatend)
* @brief      Convert to UTF8
* @ingroup    XUTILS
* 
* @param[in]  data : 
* @param[in]  size : 
* @param[in]  addzeroatend : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertToUTF8(XBYTE* data, int& size, bool addzeroatend)
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

  if(addzeroatend)
    {
      data[j]=0;     
    }
   else 
    {
      j--;
    }
 
  size = j;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSTRING::ConvertToUTF8(XBUFFER& xbuffer, bool addzeroatend)
* @brief      Convert to UTF8
* @ingroup    XUTILS
* 
* @param[in]  xbuffer : 
* @param[in]  addzeroatend : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertToUTF8(XBUFFER& xbuffer, bool addzeroatend)
{
  if(IsEmpty()) return false;

  XDWORD sizeUTF8 = GetSizeConvertToUTF8();

  if(addzeroatend) 
    {
      sizeUTF8++;
    }

  xbuffer.Delete();
  xbuffer.Resize(sizeUTF8);
  xbuffer.FillBuffer();

  int _size  = xbuffer.GetSize();

  return ConvertToUTF8(xbuffer.Get(),  _size, addzeroatend);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSTRING::ConvertFromUTF16(XBUFFER& xbuffer)
* @brief      Convert from UTF16
* @ingroup    XUTILS
* 
* @param[in]  xbuffer : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertFromUTF16(XBUFFER& xbuffer)
{
  return ConvertFromXBuffer(xbuffer, XSTRINGCODING_UTF16);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSTRING::ConvertToUTF16(XBUFFER& xbuffer)
* @brief      Convert to UTF16
* @ingroup    XUTILS
* 
* @param[in]  xbuffer : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertToUTF16(XBUFFER& xbuffer)
{
  if(IsEmpty()) return false;

  bool status = false;

  xbuffer.Empty();

  switch(GetTypeCoding())
    {
      case XSTRINGCODING_UTF16  : { for(XDWORD c=0; c<size; c++)
                                      {
                                        xbuffer.Add((XWORD)text[c]);
                                      }
                                  
                                    status = true;  
                                  }
                                  break;  
  
      case XSTRINGCODING_UTF32  : { for(size_t c=0; c<size; c++) 
                                      {
                                        XDWORD value = text[c];
                                        if (value > 0xFFFF) 
                                          {
                                            value -= 0x10000;
                                            xbuffer.Add((XWORD)(0xD800 | (value >> 10)));
                                            xbuffer.Add((XWORD)(0xDC00 | (value & 0x3FF)));
                                          } 
                                         else 
                                          {
                                            xbuffer.Add((XWORD)value);
                                          }
                                      }

                                    status = true;  
                                  }                               
                                  break;
    }
 
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSTRING::ConvertFromUTF32(XBUFFER& xbuffer)
* @brief      Convert from UTF32
* @ingroup    XUTILS
* 
* @param[in]  xbuffer : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertFromUTF32(XBUFFER& xbuffer)
{
  return ConvertFromXBuffer(xbuffer, XSTRINGCODING_UTF32);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSTRING::ConvertToUTF32(XBUFFER& xbuffer)
* @brief      Convert to UTF32
* @ingroup    XUTILS
* 
* @param[in]  xbuffer : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertToUTF32(XBUFFER& xbuffer)
{
  bool status = false;

  xbuffer.Empty();

  switch(GetTypeCoding())
    {
      case XSTRINGCODING_UTF16  : { for(size_t c=0; c<size; c++) 
                                      {
                                        XDWORD value = text[c];
                                        if(value >= 0xD800 && value <= 0xDBFF && c + 1 < size) 
                                          {
                                            XWORD low = text[c + 1];
                                            if(low >= 0xDC00 && low <= 0xDFFF) 
                                              {
                                                value = ((value - 0xD800) << 10) + (low - 0xDC00) + 0x10000;
                                                xbuffer.Add((XDWORD)value);
                                                c++;
                                              } 
                                             else 
                                              {
                                                xbuffer.Add((XDWORD)value);
                                              }
                                          } 
                                         else 
                                          {
                                            xbuffer.Add((XDWORD)value);
                                          }
                                      }
                                  }
                                  status = true;  
                                  break;
  
      case XSTRINGCODING_UTF32  : { for(XDWORD c=0; c<size; c++)
                                      {
                                        xbuffer.Add((XDWORD)text[c]);
                                      }
                                  }
                                  status = true;  
                                  break;
    }
   
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSTRING::ConvertToBase64(XSTRING& string)
* @brief      Convert to base64
* @ingroup    XUTILS
* 
* @param[in]  string : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertToBase64(XSTRING& string)
{
  XBUFFER data;
  XBUFFER charstr;

  string.Empty();
 
  (*this).ConvertToASCII(charstr);  
  data.Add((XBYTE*)charstr.Get(), GetSize());  
  
  string.ConvertBinaryToBase64(data);

  return string.GetSize()?true:false;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSTRING::ConvertBinaryToBase64(XBUFFER& inbuffer)
* @brief      Convert binary to base64
* @ingroup    XUTILS
* 
* @param[in]  inbuffer : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertBinaryToBase64(XBUFFER& inbuffer)
{  
  return Base64_Encode(inbuffer.Get(), inbuffer.GetSize(), (*this));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSTRING::ConvertBase64ToBinary(XBUFFER& outbuffer)
* @brief      Convert base64 to binary
* @ingroup    XUTILS
* 
* @param[in]  outbuffer : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ConvertBase64ToBinary(XBUFFER& outbuffer)
{
  int size  = GetSize();
  
  if(!size) return false;
  
  XBUFFER charstr;
 
  (*this).ConvertToASCII(charstr); 
  
  return Base64_Decode(charstr.GetPtrChar(), GetSize(), outbuffer); 
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ConvertToPascal(SHORTSTRING& pascalstring)
* @brief      Convert to pascal
* @ingroup    XUTILS
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

  XBUFFER charstr;
  
  (*this).ConvertToASCII(charstr); 
  memcpy(&pascalstring.data, charstr.Get(), pascalstring.size);
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ConvertFromPascal(SHORTSTRING& pascalstring)
* @brief      Convert from pascal
* @ingroup    XUTILS
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
* @brief      Convert from double to spanish text
* @ingroup    XUTILS
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
* @ingroup    XUTILS
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
* @ingroup    XUTILS
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
* @brief      Format arg
* @ingroup    XUTILS
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
              case __C('%')   : { int  nparam = 1;
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
                                                              character = (XCHAR)va_arg((*arg), int /*XCHAR*/);
                                                              #endif

                                                              str.Set(character);
                                                              end  = true ;
                                                            }
                                                            break;
   
                                          case __C('i')   :
                                          case __C('o')   :                                         
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

                                          case __C('d')   :                                       
                                          case __C('u')   : { bool large    = false;
                                                              bool shortint = false;
    
                                                              for(int d=0; d<(int)XSTRING::GetSize(param); d++)
                                                                {
                                                                  if(param[d] == __C('l')) 
                                                                    {
                                                                      large = true;
                                                                    }

                                                                  if(param[d] == __C('h')) 
                                                                    {
                                                                      shortint = true;
                                                                    }
                                                                }

                                                              if(shortint)
                                                                {
                                                                  if(mask[c] == __C('d')) 
                                                                    {
                                                                      short value = (short)va_arg((*arg), int);
                                                                      str.ConvertFromShort(value, param);
                                                                      end  = true;
                                                                    }

                                                                  if(mask[c] == __C('u')) 
                                                                    {
                                                                      XWORD value = (XWORD)va_arg((*arg), int);
                                                                      str.ConvertFromWord(value, param);
                                                                      end  = true;
                                                                    }
                                                                }  

                                                              if((!shortint) && (!large))
                                                                {
                                                                  if(mask[c] == __C('d')) 
                                                                    {
                                                                      int value = (int)va_arg((*arg), int);
                                                                      str.ConvertFromInt(value, param);
                                                                      end  = true;
                                                                    }

                                                                  if(mask[c] == __C('u')) 
                                                                    {
                                                                      XDWORD value = (XDWORD)va_arg((*arg), int);
                                                                      str.ConvertFromDWord(value, param);
                                                                      end  = true;
                                                                    }
                                                                }  

                                                              if(large)
                                                                {
                                                                  if(mask[c] == __C('d')) 
                                                                    {
                                                                      long long value = (long long)va_arg((*arg), long long);
                                                                      str.ConvertFromLongLong(value, param);
                                                                      end  = true;
                                                                    }
                                                              
                                                                  if(mask[c] == __C('u')) 
                                                                    {
                                                                      XQWORD value = va_arg((*arg), long long);
                                                                      str.ConvertFromLongLong(value, param);  
                                                                      end  = true;
                                                                    }
                                                                }                                                                                                                                                                                       
                                                            }
                                                            break;

                                          case __C('f')   : { bool large = false;
                                                              for(int d=0; d<(int)XSTRING::GetSize(param); d++)
                                                                {
                                                                  if(param[d] == __C('l')) large = true;
                                                                }

                                                              if(!large)
                                                                {  
                                                                  double data = va_arg((*arg), double);
                                                                  str.ConvertFromFloat((float)(data), param);
                                                                  end  = true;
                                                                }
                                                               else                                                                
                                                                { 
                                                                  double data = va_arg((*arg), double);
                                                                  str.ConvertFromDouble((double)data, param);
                                                                  end  = true;
                                                                }                                                                   
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
* @ingroup    XUTILS
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
* @brief      Add format
* @ingroup    XUTILS
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
* @brief      Un format
* @ingroup    XUTILS
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
                                        case __C('C')   : { value_xchar = (XCHAR*)va_arg(arg, XCHAR*);
                                                            if(value_xchar) (*value_xchar) = Get()[indextext];
                                                            indextext++;
                                                            end  = true;
                                                          }
                                                          break;

                                        case __C('i')   :
                                        case __C('o')   :
                                        case __C('x')   :
                                        case __C('X')   : { value_int = (int*)va_arg(arg, int*);

                                                            if(value_int) (*value_int) = ConvertToInt(indextext,(XCHAR*)param, false);
                                                            end  = true;
                                                          }              
                                                          break;

                                        case __C('d')   :                                       
                                        case __C('u')   : { bool large    = false;
                                                            bool shortint = false;
    
                                                            for(int d=0; d<(int)XSTRING::GetSize(param); d++)
                                                              {
                                                                if(param[d] == __C('l')) 
                                                                  {
                                                                    large = true;
                                                                  }

                                                                if(param[d] == __C('h')) 
                                                                  {
                                                                    shortint = true;
                                                                  }
                                                              }

                                                            if(shortint)
                                                              {
                                                                if(mask[c] == __C('d')) 
                                                                  {
                                                                    value_short = (short*)va_arg(arg, int*);

                                                                    if(value_short) (*value_short) = ConvertToInt(indextext,(XCHAR*)param, false);
                                                                    end  = true;
                                                                  }

                                                                if(mask[c] == __C('u')) 
                                                                  {
                                                                    value_word = (XWORD*)va_arg(arg, int*);

                                                                    if(value_word) (*value_word) = ConvertToDWord(indextext,(XCHAR*)param, false);
                                                                    end  = true;
                                                                  }
                                                              }  

                                                            if((!shortint) && (!large))
                                                              {
                                                                if(mask[c] == __C('d')) 
                                                                  {
                                                                    value_int = (int*)va_arg(arg, int*);

                                                                    if(value_int) (*value_int) = ConvertToInt(indextext,(XCHAR*)param, false);
                                                                    end  = true;
                                                                  }

                                                                if(mask[c] == __C('u')) 
                                                                  {
                                                                    value_dword = (XDWORD*)va_arg(arg, int*);

                                                                    if(value_dword) (*value_dword) = ConvertToDWord(indextext,(XCHAR*)param, false);
                                                                    end  = true;
                                                                  }
                                                              }  

                                                            if(large)
                                                              {
                                                                if(mask[c] == __C('d')) 
                                                                  {
                                                                    value_longlong = (long long*)va_arg(arg, long long*);

                                                                    if(value_longlong) (*value_longlong) = ConvertToInt(indextext,(XCHAR*)param, false);
                                                                    end  = true;
                                                                  }

                                                                if(mask[c] == __C('u')) 
                                                                  {
                                                                    value_qword = (XQWORD*)va_arg(arg, long long*);

                                                                    if(value_qword) (*value_qword) = ConvertToDWord(indextext,(XCHAR*)param, false);
                                                                    end  = true;
                                                                  }
                                                              }                                                                                                                                                                                    
                                                          }
                                                          break;

                                        case __C('f')   : { bool large = false;
                                                            for(int d=0; d<(int)XSTRING::GetSize(param); d++)
                                                              {
                                                                if(param[d] == __C('l')) large = true;
                                                              }

                                                            if(!large)
                                                              {  
                                                                value_float = (float*)va_arg(arg, double*);
                                                                if(value_float) (*value_float) = ConvertToFloat(indextext,(XCHAR*)param, false);
                                                                end  = true;
                                                              }
                                                              else                                                                
                                                              { 
                                                                value_double = (double*)va_arg(arg, double*);
                                                                if(value_double) (*value_double) = ConvertToDouble(indextext,(XCHAR*)param, false);
                                                                end  = true;
                                                              }                                                                   
                                                          }
                                                          break;

                                        case __C('g')   :
                                        case __C('G')   : { value_double = (double*)va_arg(arg, double*);

                                                            if(value_double) (*value_double) = ConvertToDouble(indextext,(XCHAR*)param, false);

                                                            end  = true;
                                                          }
                                                          break;

                                        case __C('e')   :
                                        case __C('E')   :

                                        case __C('n')   :
                                        case __C('p')   : end = true;
                                                          break;

                                        case __C('s')   :
                                        case __C('S')   : { value_xchar = (XCHAR*)va_arg(arg,XCHAR*);
                                                            if(!value_xchar) break;

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

                                                            memcpy((XBYTE*)value_xchar, (XBYTE*)string.Get(), (string.GetSize()*sizeof(XCHAR)));
                                                            value_xchar[string.GetSize()] = 0;

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
                                                              value_xchar = (XCHAR*)va_arg(arg, XCHAR*);

                                                              ConvertStringWithMask(param, &text[indextext], value_xchar);
                                                              indextext += GetSize(value_xchar);

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
* @fn         int XSTRING::FindCharacterFromSet(const XCHAR* chars)
* @brief      Find character from set
* @ingroup    XUTILS
*
* @param[in]  chars :
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
* @brief      Adjust size
* @ingroup    XUTILS
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
* @brief      Adjust size
* @ingroup    XUTILS
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
* @brief      Binary compare
* @ingroup    XUTILS
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
* @ingroup    XUTILS
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
      if(end==XSTRING_NOTFOUND) end = size;

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
* @brief      Get type of line end
* @ingroup    XUTILS
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
* @fn         bool XSTRING::ReAllocBuffer(XDWORD size)
* @brief      Re alloc buffer
* @ingroup    XUTILS
*
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::ReAllocBuffer(XDWORD sizechar)
{
  if(!sizechar)
    {
      FreeBuffer();

      return true;
    }

  XDWORD newsizechar      = (sizechar + XSTRING_EXCESSCHARS);
  XDWORD newsizecharbytes = (newsizechar * sizeof(XCHAR));
  XCHAR* newtext          = (XCHAR*)new XBYTE[newsizecharbytes];
  if(!newtext) 
    {
      return false;
    }

  memset(newtext, 0, newsizecharbytes);

  if(text)
    {
      if(this->size >= sizechar)
        { 
          memcpy(newtext, text, sizechar * sizeof(XCHAR));
        }
       else
        {
          memcpy(newtext, text, size * sizeof(XCHAR));
        } 

      FreeBuffer();
    }

  text          = newtext;
  this->size    = sizechar;
  this->sizemem = newsizechar;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::FreeBuffer()
* @brief      Free buffer
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::FreeBuffer()
{
  if(xmutexfreemen) 
    {
      xmutexfreemen->Lock();
    }

  bool status = false;

  if(text) 
    {
      delete [] text;

      text    = NULL;
      size    = 0;
      sizemem = 0;

      status = true;
    }

  if(xmutexfreemen) 
    {
      xmutexfreemen->UnLock();
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSTRING::ConvertStringWithMask(XCHAR* mask, XCHAR* string, XCHAR* result)
* @brief      Convert string with mask
* @ingroup    XUTILS
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
  
  XBUFFER maskchar;
  XBUFFER stringchar;
 
  _mask.ConvertToASCII(maskchar);
  _string.ConvertToASCII(stringchar);
 
  SSCANF(stringchar.GetPtrChar(), maskchar.GetPtrChar(), resultchar, XSTRING_MAXTEMPOSTR);

  _result = resultchar;

  memcpy(result, _result.Get(), ((_result.GetSize()+1)*sizeof(XCHAR)));

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XSTRING::Base64_EncodeBlock(XBYTE* in, XBYTE* out, int len)
* @brief      Base64 encode block
* @ingroup    XUTILS
* 
* @param[in]  in : 
* @param[in]  out : 
* @param[in]  len : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XSTRING::Base64_EncodeBlock(XBYTE *in, XBYTE *out, int len)
{
  out[0] = (XBYTE) codetablebase64[ (int)(in[0] >> 2) ];  
  out[1] = (XBYTE) codetablebase64[ (int)(((in[0] & 0x03) << 4) | ((in[1] & 0xf0) >> 4)) ];
  out[2] = (XBYTE) (len > 1 ? codetablebase64[ (int)(((in[1] & 0x0f) << 2) | ((in[2] & 0xc0) >> 6)) ] : '=');
  out[3] = (XBYTE) (len > 2 ? codetablebase64[ (int)(in[2] & 0x3f) ] : '=');
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSTRING::Base64_Encode(XBYTE* buffer, XDWORD buffersize, XSTRING& line)
* @brief      Base64 encode
* @ingroup    XUTILS
* 
* @param[in]  buffer : 
* @param[in]  buffersize : 
* @param[in]  line : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::Base64_Encode(XBYTE* buffer, XDWORD buffersize, XSTRING& line)
{
  XBYTE in[3]     = { 0 };
	XBYTE out[4]    = { 0 };
  int   i;
  int   len;
  int   cin       = 0;
  
	*in   = (XBYTE) 0;
	*out  = (XBYTE) 0;

  while((XDWORD)cin < buffersize) 
    {
      len = 0;
      for(i = 0; i < 3; i++) 
        {
          in[i] = (XBYTE)buffer[cin++];

          if((XDWORD)cin <= buffersize) 
            {
              len++;
            }
           else 
            {
              in[i] = (XBYTE)0;
            }
        }

      if(len > 0) 
        {
          Base64_EncodeBlock(in, out, len );
          line.Add(out, 4);	                
        }      
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XSTRING::Base64_DecodeBlock(XBYTE in[4], XBYTE out[3])
* @brief      Base64 decode block
* @ingroup    XUTILS
* 
* @param[in]  in : 
* @param[in]  out : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XSTRING::Base64_DecodeBlock(XBYTE in[4], XBYTE out[3]) 
{
  out[0] = (XBYTE)(in[0] << 2 | in[1] >> 4);
  out[1] = (XBYTE)(in[1] << 4 | in[2] >> 2);
  out[2] = (XBYTE)(((in[2] << 6) & 0xc0) | in[3]);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSTRING::Base64_Decode(const char* in_buffer, int in_buffer_size, XBUFFER& outbuffer)
* @brief      Base64 decode
* @ingroup    XUTILS
* 
* @param[in]  in_buffer : 
* @param[in]  in_buffer_size : 
* @param[in]  outbuffer : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSTRING::Base64_Decode(const char* in_buffer, int in_buffer_size, XBUFFER& outbuffer) 
{
  XBYTE       in[4]; 
  XBYTE       out[3];
  XBYTE       v;
  int         i;
  int         len;    
  const char* ptr  = in_buffer;
    
  while (ptr <= in_buffer + in_buffer_size) 
    {
      for(len = 0, i = 0; i < 4 && (ptr <= in_buffer + in_buffer_size); i++) 
        {
          v = 0;
          while((ptr <= in_buffer + in_buffer_size) && v == 0) 
            {
              v = (XBYTE)ptr[0];
              ptr++;
              v = (XBYTE)((v < 43 || v > 122) ? 0 : decodetablebase64[v - 43]);
              if(v) v = (XBYTE)((v == '$') ? 0 : v - 61);
            }

          if(ptr <= in_buffer + in_buffer_size) 
            {
              len++;
              if(v) in[i] = (XBYTE)(v - 1);
            } 
           else 
            {
              in[i] = 0;
            }
        }

      if(len) 
        {
          Base64_DecodeBlock(in, out);

          for(i = 0; i < len - 1; i++) 
            {
              outbuffer.Add(out[i]);              
            }
        }
    }
    
  return outbuffer.GetSize()?true:false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSTRING::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XSTRING::Clean()
{
  text            = NULL;
  size            = 0;
  sizemem         = 0;

  xmutexfreemen   = NULL;

  value_short     = NULL;
  value_word      = NULL;
  value_int       = NULL;
  value_dword     = NULL;
  value_longlong  = NULL;
  value_qword     = NULL;
  value_float     = NULL;
  value_double    = NULL;
  value_xchar     = NULL;
}


#pragma endregion


#endif

