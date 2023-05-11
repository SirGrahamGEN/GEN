/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XVariant.cpp
*
* @class      XVARIANT
* @brief      Variant class (any type of data)
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XFactory.h"
#include "XTrace.h"

#include "XVariant.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XVARIANT::XVARIANT()
* @brief      Constructor
* @ingroup    XUTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::XVARIANT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVARIANT::XVARIANT(const bool value)
* @brief      Constructor
* @ingroup    XUTILS
* 
* @param[in]  const bool: 
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::XVARIANT(const bool value)
{
  XVARIANT_CONSTRUCTOR
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVARIANT::XVARIANT(const short value)
* @brief      Constructor
* @ingroup    XUTILS
* 
* @param[in]  const short: 
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::XVARIANT(const short value) 
{
  XVARIANT_CONSTRUCTOR
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVARIANT::XVARIANT(const XWORD value)
* @brief      Constructor
* @ingroup    XUTILS
* 
* @param[in]  const XWORD: 
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::XVARIANT(const XWORD value)
{
  XVARIANT_CONSTRUCTOR
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVARIANT::XVARIANT(const int value)
* @brief      Constructor
* @ingroup    XUTILS
* 
* @param[in]  const int: 
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::XVARIANT(const int value)
{
  XVARIANT_CONSTRUCTOR
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVARIANT::XVARIANT(const XDWORD value)
* @brief      Constructor
* @ingroup    XUTILS
* 
* @param[in]  const XDWORD: 
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::XVARIANT(const XDWORD value)
{
  XVARIANT_CONSTRUCTOR
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVARIANT::XVARIANT(const long long value)
* @brief      Constructor
* @ingroup    XUTILS
* 
* @param[in]  const long long: 
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::XVARIANT(const long long value)
{
  XVARIANT_CONSTRUCTOR
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVARIANT::XVARIANT(const XQWORD value)
* @brief      Constructor
* @ingroup    XUTILS
* 
* @param[in]  const XQWORD: 
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::XVARIANT(const XQWORD value)
{
  XVARIANT_CONSTRUCTOR
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVARIANT::XVARIANT(const float value)
* @brief      Constructor
* @ingroup    XUTILS
* 
* @param[in]  const float: 
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::XVARIANT(const float value)
{
  XVARIANT_CONSTRUCTOR  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVARIANT::XVARIANT(const double value)
* @brief      Constructor
* @ingroup    XUTILS
* 
* @param[in]  const double: 
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::XVARIANT(const double value)
{
  XVARIANT_CONSTRUCTOR  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVARIANT::XVARIANT(const XCHAR value)
* @brief      Constructor
* @ingroup    XUTILS
* 
* @param[in]  const XCHAR: 
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::XVARIANT(const XCHAR value)
{
  XVARIANT_CONSTRUCTOR  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVARIANT::XVARIANT(const XCHAR* value)
* @brief      Constructor
* @ingroup    XUTILS
* 
* @param[in]  const  XCHAR*: 
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::XVARIANT(const XCHAR* value)
{
  XVARIANT_CONSTRUCTOR  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVARIANT::XVARIANT(const XSTRING& value)
* @brief      Constructor
* @ingroup    XUTILS
* 
* @param[in]  const XSTRING&: 
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::XVARIANT(const XSTRING& value)
{
  XVARIANT_CONSTRUCTOR  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVARIANT::XVARIANT(const char* value)
* @brief      Constructor
* @ingroup    XUTILS
* 
* @param[in]  const char*: 
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::XVARIANT(const char* value)
{
  XVARIANT_CONSTRUCTOR  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVARIANT::XVARIANT(const char value)
* @brief      Constructor
* @ingroup    XUTILS
* 
* @param[in]  const char: 
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::XVARIANT(const char value)
{
  XVARIANT_CONSTRUCTOR  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVARIANT::XVARIANT(const XDATETIME& value)
* @brief      Constructor
* @ingroup    XUTILS
* 
* @param[in]  const XDATETIME: 
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::XVARIANT(const XDATETIME& value)
{
  XVARIANT_CONSTRUCTOR  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVARIANT::XVARIANT(const XBUFFER& value)
* @brief      Constructor
* @ingroup    XUTILS
* 
* @param[in]  const : 
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::XVARIANT(const XBUFFER& value)
{
  XVARIANT_CONSTRUCTOR
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVARIANT::XVARIANT(const XVARIANT& value)
* @brief      Constructor
* @ingroup    XUTILS
* 
* @param[in]  const XVARIANT: 
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::XVARIANT(const XVARIANT& value)
{
  XVARIANT_CONSTRUCTOR  
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XVARIANT::~XVARIANT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::~XVARIANT()
{
  if(data) Destroy();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         const XVARIANT& XVARIANT::operator = (bool value)
* @brief      operator =
* @ingroup    XUTILS
* 
* @param[in]  value : 
* 
* @return     const : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
const XVARIANT& XVARIANT::operator = (bool value)
{
  XVARIANT_ASSIGN(XVARIANT_TYPE_BOOLEAN, bool)
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         const XVARIANT& XVARIANT::operator = (short value)
* @brief      operator =
* @ingroup    XUTILS
* 
* @param[in]  value : 
* 
* @return     const : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
const XVARIANT& XVARIANT::operator = (short value)
{
  XVARIANT_ASSIGN(XVARIANT_TYPE_SHORT, short)
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         const XVARIANT& XVARIANT::operator = (XWORD ushortinteger)
* @brief      operator =
* @ingroup    XUTILS
* 
* @param[in]  ushortinteger : 
* 
* @return     const : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
const XVARIANT& XVARIANT::operator = (XWORD value)
{
  XVARIANT_ASSIGN(XVARIANT_TYPE_XWORD, XWORD)
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         const XVARIANT& XVARIANT::operator = (int value)
* @brief      operator =
* @ingroup    XUTILS
* 
* @param[in]  value : 
* 
* @return     const : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
const XVARIANT& XVARIANT::operator = (int value)
{
  XVARIANT_ASSIGN(XVARIANT_TYPE_INTEGER, int)
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         const XVARIANT& XVARIANT::operator = (XDWORD value)
* @brief      operator =
* @ingroup    XUTILS
* 
* @param[in]  value : 
* 
* @return     const : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
const XVARIANT& XVARIANT::operator = (XDWORD value)
{
  XVARIANT_ASSIGN(XVARIANT_TYPE_XDWORD, XDWORD)
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         const XVARIANT& XVARIANT::operator = (long long value)
* @brief      operator =
* @ingroup    XUTILS
* 
* @param[in]  long value : 
* 
* @return     const : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
const XVARIANT& XVARIANT::operator = (long long value)
{
  XVARIANT_ASSIGN(XVARIANT_TYPE_DOUBLEINTEGER, long long)  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         const XVARIANT& XVARIANT::operator = (XQWORD value)
* @brief      operator =
* @ingroup    XUTILS
* 
* @param[in]  value : 
* 
* @return     const : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
const XVARIANT& XVARIANT::operator = (XQWORD value)
{
  XVARIANT_ASSIGN(XVARIANT_TYPE_XQWORD, XQWORD)  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         const XVARIANT& XVARIANT::operator = (float value)
* @brief      operator =
* @ingroup    XUTILS
* 
* @param[in]  value : 
* 
* @return     const : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
const XVARIANT& XVARIANT::operator = (float value)
{
  XVARIANT_ASSIGN(XVARIANT_TYPE_FLOAT, float)  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         const XVARIANT& XVARIANT::operator = (double value)
* @brief      operator =
* @ingroup    XUTILS
* 
* @param[in]  value : 
* 
* @return     const : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
const XVARIANT& XVARIANT::operator = (double value)
{
  XVARIANT_ASSIGN(XVARIANT_TYPE_DOUBLE, double)  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         const XVARIANT& XVARIANT::operator = (XCHAR value)
* @brief      operator =
* @ingroup    XUTILS
* 
* @param[in]  value : 
* 
* @return     const : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
const XVARIANT& XVARIANT::operator = (XCHAR value)
{
  XVARIANT_ASSIGN(XVARIANT_TYPE_XCHAR, XCHAR)  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         const XVARIANT& XVARIANT::operator = (XCHAR* value)
* @brief      operator =
* @ingroup    XUTILS
* 
* @param[in]  value : 
* 
* @return     const : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
const XVARIANT& XVARIANT::operator = (XCHAR* value)
{
  GetDataFromString(value);

  return (*this);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         const XVARIANT& XVARIANT::operator = (const XSTRING& value)
* @brief      operator =
* @ingroup    XUTILS
* 
* @param[in]  XSTRING& value : 
* 
* @return     const : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
const XVARIANT& XVARIANT::operator = (const XSTRING& value)
{
  GetDataFromString(value.Get());

  return (*this);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         const XVARIANT& XVARIANT::operator = (char* value)
* @brief      operator =
* @ingroup    XUTILS
* 
* @param[in]  value : 
* 
* @return     const : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
const XVARIANT& XVARIANT::operator = (char* value)
{
  if(data) Destroy();

  data = new XSTRING();
  if(data)
    {
      type = XVARIANT_TYPE_STRING;
      size = sizeof(XSTRING);

      if (static_cast<XSTRING*>(data)) static_cast<XSTRING*>(data)->Set(value);
    }

  return (*this);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         const XVARIANT& XVARIANT::operator = (char value)
* @brief      operator =
* @ingroup    XUTILS
* 
* @param[in]  value : 
* 
* @return     const : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
const XVARIANT& XVARIANT::operator = (char value)
{
  XVARIANT_ASSIGN(XVARIANT_TYPE_CHAR, char)  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         const XVARIANT& XVARIANT::operator = (const XDATETIME& value)
* @brief      operator =
* @ingroup    XUTILS
* 
* @param[in]  XDATETIME& value : 
* 
* @return     const : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
const XVARIANT& XVARIANT::operator = (const XDATETIME& value)
{
  XVARIANT_ASSIGN(XVARIANT_TYPE_DATETIME, XDATETIME)  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         const XVARIANT& XVARIANT::operator = (const XBUFFER& value)
* @brief      operator =
* @ingroup    XUTILS
* 
* @param[in]  XBUFFER& value : 
* 
* @return     const : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
const XVARIANT& XVARIANT::operator = (const XBUFFER& value)
{
  XVARIANT_ASSIGN(XVARIANT_TYPE_BUFFER, XBUFFER)  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         const XVARIANT& XVARIANT::operator = (const XVARIANT& value)
* @brief      operator =
* @ingroup    XUTILS
* 
* @param[in]  XVARIANT& value : 
* 
* @return     const : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
const XVARIANT& XVARIANT::operator = (const XVARIANT& value)
{
  if(&value==this) return (*this);

  if(value.data==this->data)  return (*this);

  if(data) Destroy();

  size    = value.size;
  type    = value.type;
  switch(type)
    {
      case XVARIANT_TYPE_BOOLEAN        : (*this) = (bool)(XVARIANT&)value;        break;
      case XVARIANT_TYPE_SHORT          : (*this) = (int)(XVARIANT&)value;         break;
      case XVARIANT_TYPE_XWORD          : (*this) = (XWORD)(XVARIANT&)value;       break;
      case XVARIANT_TYPE_INTEGER        : (*this) = (int)(XVARIANT&)value;         break;
      case XVARIANT_TYPE_XDWORD         : (*this) = (XDWORD)(XVARIANT&)value;      break;
      case XVARIANT_TYPE_DOUBLEINTEGER  : (*this) = (long long)(XVARIANT&)value;   break;      
      case XVARIANT_TYPE_XQWORD         : (*this) = (XQWORD)(XVARIANT&)value;      break;      
      case XVARIANT_TYPE_CHAR           : (*this) = (char)(XVARIANT&)value;        break;
      case XVARIANT_TYPE_FLOAT          : (*this) = (float)(XVARIANT&)value;       break;
      case XVARIANT_TYPE_DOUBLE         : (*this) = (double)(XVARIANT&)value;      break;
      case XVARIANT_TYPE_XCHAR          : (*this) = (XCHAR)(XVARIANT&)value;       break;
      case XVARIANT_TYPE_STRING         : (*this) = (XCHAR*)(XVARIANT&)value;      break;

      case XVARIANT_TYPE_TIME           :     
      case XVARIANT_TYPE_DATE           :  
      case XVARIANT_TYPE_DATETIME       : (*this) = (XDATETIME)(XVARIANT&)value;
                                          type    = value.type;                                          
                                          break;

      case XVARIANT_TYPE_BUFFER         : (*this) = (const XBUFFER&)value;
                                          type    = value.type;                                          
                                          break;      

                              default   : break;
    }

  return (*this);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVARIANT::operator bool()
* @brief      bool
* @ingroup    XUTILS
* 
* @return     XVARIANT::operator : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::operator bool()
{
  if(IsNull()) return 0;

  return *(bool*)data;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVARIANT::operator short()
* @brief      hort
* @ingroup    XUTILS
* 
* @return     XVARIANT::operator : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::operator short()
{
  if(IsNull()) return 0;

  return *(short*)data;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVARIANT::operator XWORD()
* @brief      WORD
* @ingroup    XUTILS
* 
* @return     XVARIANT::operator : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::operator XWORD()
{
  if(IsNull()) return 0;

  return *(XWORD*)data;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XVARIANT::operator int()
* @brief      nt
* @ingroup    XUTILS
*
* @return     XVARIANT::operator :
*
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::operator int()
{
  if(IsNull())  return 0;

  return *(int*)data;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XVARIANT::operator XDWORD()
* @brief      DWORD
* @ingroup    XUTILS
*
* @return     XVARIANT::operator :
*
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::operator XDWORD()
{
  if(IsNull()) return 0;

  return *(XDWORD*)data;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVARIANT::operator long long()
* @brief      ong long
* @ingroup    XUTILS
* 
* @return     XVARIANT::operator : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::operator long long()
{
  if(IsNull()) return 0;

  return *(long long*)data;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XVARIANT::operator XQWORD()
* @brief      QWORD
* @ingroup    XUTILS
*
* @return     XVARIANT::operator :
*
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::operator XQWORD()
{
  if(IsNull()) return 0;

  return *(XQWORD*)data;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XVARIANT::operator float()
* @brief      loat
* @ingroup    XUTILS
*
* @return     XVARIANT::operator :
*
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::operator float()
{
  if(IsNull()) return float(0);

  return *(float*)data;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XVARIANT::operator double()
* @brief      ouble
* @ingroup    XUTILS
*
* @return     XVARIANT::operator :
*
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::operator double()
{
  if(IsNull()) return double(0);

  return *(double*)data;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XVARIANT::operator XCHAR()
* @brief      CHAR
* @ingroup    XUTILS
*
* @return     XVARIANT::operator :
*
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::operator XCHAR()
{
  if(IsNull()) return XCHAR(0);

  return *(XCHAR*)data;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XVARIANT::operator XCHAR*()
* @brief      CHAR*
* @ingroup    XUTILS
*
* @return     XVARIANT::operator :
*
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::operator XCHAR*()
{
  if(!IsNull())
    {
      switch(type)
        {
          case XVARIANT_TYPE_STRING : if (static_cast<XSTRING*>(data)) return static_cast<XSTRING*>(data)->Get();
                                      break;

                            default : break;

        }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XVARIANT::operator char()
* @brief      har
* @ingroup    XUTILS
*
* @return     XVARIANT::operator :
*
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::operator char()
{
  if(data) return *(char*)data;

  return 0;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVARIANT::operator char*()
* @brief      har*
* @ingroup    XUTILS
* 
* @return     XVARIANT::operator : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::operator char*()
{
  if(data) return (char*)data;

  return 0;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVARIANT::operator XSTRING()
* @brief      STRING
* @ingroup    XUTILS
* 
* @return     XVARIANT::operator : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::operator XSTRING()
{
  XSTRING string;

  if(static_cast<XSTRING*>(data))
    {
      string = *(static_cast<XSTRING*>(this->data));
    }

  return string;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XVARIANT::operator XDATETIME()
* @brief      DATETIME
* @ingroup    XUTILS
*
* @return     XVARIANT::operator :
*
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::operator XBUFFER()
{
  XBUFFER buffer;

  if(static_cast<XBUFFER*>(data))
  buffer = *(static_cast<XBUFFER*>(this->data));

  return buffer;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XVARIANT::operator XDATETIME()
* @brief      DATETIME
* @ingroup    XUTILS
*
* @return     XVARIANT::operator :
*
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::operator XDATETIME()
{
  XDATETIME time;

  if(static_cast<XDATETIME*>(data))
  time=*(static_cast<XDATETIME*>(this->data));

  return time;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XVARIANT::GetDataFromString(XCHAR* string)
* @brief      GetDataFromString
* @ingroup    XUTILS
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XVARIANT::GetDataFromString(XCHAR* string)
{
  if(data) Destroy();

  data=new XSTRING();
  if(!data) return false;

  type = XVARIANT_TYPE_STRING;
  size = sizeof(XSTRING);


  if(static_cast<XSTRING*>(data))
    {
      return static_cast<XSTRING*>(data)->Set(string);
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XVARIANT_TYPE XVARIANT::GetType()
* @brief      GetType
* @ingroup    XUTILS
*
* @return     XVARIANT_TYPE :
*
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT_TYPE XVARIANT::GetType()
{
  return type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XVARIANT::GetType(XSTRING& typestr)
* @brief      GetType
* @ingroup    XUTILS
* 
* @param[in]  typestr : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XVARIANT::GetType(XSTRING& typestr)
{
  switch(type)
    {
      case XVARIANT_TYPE_NULL             : typestr = __L("null");            break;      
      case XVARIANT_TYPE_BOOLEAN          : typestr = __L("boolean");         break;    
      case XVARIANT_TYPE_SHORT            : typestr = __L("short");           break;
      case XVARIANT_TYPE_XWORD            : typestr = __L("word");            break;
      case XVARIANT_TYPE_INTEGER          : typestr = __L("integer");         break;
      case XVARIANT_TYPE_XDWORD           : typestr = __L("double word");     break;
      case XVARIANT_TYPE_DOUBLEINTEGER    : typestr = __L("double integer");  break;      
      case XVARIANT_TYPE_XQWORD           : typestr = __L("quad word");       break;      
      case XVARIANT_TYPE_CHAR             : typestr = __L("char");            break;
      case XVARIANT_TYPE_FLOAT            : typestr = __L("float");           break;
      case XVARIANT_TYPE_DOUBLE           : typestr = __L("double");          break;
      case XVARIANT_TYPE_STRING           : typestr = __L("string");          break;
      case XVARIANT_TYPE_TIME             : typestr = __L("time");            break;
      case XVARIANT_TYPE_DATE             : typestr = __L("date");            break;
      case XVARIANT_TYPE_DATETIME         : typestr = __L("date/time");       break;
      case XVARIANT_TYPE_BUFFER           : typestr = __L("buffer");          break;      
                        default           : return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XVARIANT::SetType(XVARIANT_TYPE type)
* @brief      SetType
* @ingroup    XUTILS
*
* @param[in]  type :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XVARIANT::SetType(XVARIANT_TYPE type)
{
  this->type = type;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XVARIANT::GetSize()
* @brief      GetSize
* @ingroup    XUTILS
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XVARIANT::GetSize()
{
  return size;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void* XVARIANT::GetData()
* @brief      GetData
* @ingroup    XUTILS
*
* @return     void* :
*
* --------------------------------------------------------------------------------------------------------------------*/
void* XVARIANT::GetData()
{
  return (void*)data;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XVARIANT::Set(XVARIANT_TYPE type, void* data, XDWORD size)
* @brief      Set
* @ingroup    XUTILS
*
* @param[in]  type :
* @param[in]  data :
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XVARIANT::Set(XVARIANT_TYPE type, void* data, XDWORD size)
{
  if(this->data)  Destroy();

  if(type == XVARIANT_TYPE_NULL)
    return true;

  if(size)
    {
      this->data = new XBYTE[size];
      if(!this->data)
        return false;
      this->type    = type;
    }

  this->size    = size;

  if(data && size)
    memcpy(this->data, data, size);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XVARIANT::ToString(XSTRING& to)
* @brief      ToString
* @ingroup    XUTILS
*
* @param[in]  to :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XVARIANT::ToString(XSTRING& to)
{
  switch(type)
    {
      case XVARIANT_TYPE_NULL             : to.Format(__L("NULL"));                                                                                               break;      
      case XVARIANT_TYPE_BOOLEAN          : to.Format(__L("%s"), (*(bool*)this->data)?__L("true"):__L("false"));                                                  break;                                                                                           break;
      case XVARIANT_TYPE_SHORT            : to.Format(__L("%hd"),*(short*)this->data);                                                                            break;
      case XVARIANT_TYPE_XWORD            : to.Format(__L("%hu"),*(XWORD*)this->data);                                                                            break;
      case XVARIANT_TYPE_INTEGER          : to.Format(__L("%d"),*(int*)this->data);                                                                               break;
      case XVARIANT_TYPE_XDWORD           : to.Format(__L("%u"),*(XDWORD*)this->data);                                                                            break;
      case XVARIANT_TYPE_DOUBLEINTEGER    : to.Format(__L("%lld"),*(long long*)this->data);                                                                       break;      
      case XVARIANT_TYPE_XQWORD           : to.Format(__L("%llu"),*(XQWORD*)this->data);                                                                          break;      
      case XVARIANT_TYPE_CHAR             : to.Format(__L("%c"),*(int*)this->data);                                                                               break;
      case XVARIANT_TYPE_FLOAT            : to.Format(__L("%f"),*(float*)this->data);                                                                             break;
      case XVARIANT_TYPE_DOUBLE           : to.Format(__L("%lf"),*(double*)this->data);                                                                           break;
      case XVARIANT_TYPE_STRING           : to.Format(__L("%s"),((XSTRING*)this->data)->Get());                                                                   break;
      case XVARIANT_TYPE_TIME             : ((XDATETIME*)this->data)->GetDateTimeToString(XDATETIME_FORMAT_ADDTIME | XDATETIME_FORMAT_TIMEWITHSECONDS,  to);      break;
      case XVARIANT_TYPE_DATE             : ((XDATETIME*)this->data)->GetDateTimeToString(XDATETIME_FORMAT_YMD,                                         to);      break;
      case XVARIANT_TYPE_DATETIME         : ((XDATETIME*)this->data)->GetDateTimeToString(XDATETIME_FORMAT_STANDARD,                                    to);      break;
      case XVARIANT_TYPE_BUFFER           : to.Format(__L("[Object]"));                                                                                           break;      
                        default           : return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XVARIANT::IsNull()
* @brief      IsNull
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XVARIANT::IsNull()
{
  return (data == NULL);
}


#ifdef XTRACE_ACTIVE
/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XVARIANT::PrintDebug()
* @brief      PrintDebug
* @ingroup    XUTILS
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XVARIANT::PrintDebug()
{
  XSTRING string;

  ToString(string);
  
  if(!string.IsEmpty())
    {
      XTRACE_PRINTCOLOR(XTRACE_COLOR_INFO, __L("%s"), string.Get());  
    }
}

#endif


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XVARIANT::Destroy()
* @brief      Destroy
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XVARIANT::Destroy()
{
  if(data)
    {
      switch(this->type)
        { 
          case XVARIANT_TYPE_NULL           :                               break;
          case XVARIANT_TYPE_BOOLEAN        : delete (bool*)data;           break;
          case XVARIANT_TYPE_SHORT          : delete (short*)data;          break;
          case XVARIANT_TYPE_XWORD          : delete (XWORD*)data;          break;          
          case XVARIANT_TYPE_INTEGER        : delete (int*)data;            break;
          case XVARIANT_TYPE_XDWORD         : delete (XDWORD*)data;         break;          
          case XVARIANT_TYPE_DOUBLEINTEGER  : delete (long long*)data;      break;
          case XVARIANT_TYPE_XQWORD         : delete (XQWORD*)data;         break;
          case XVARIANT_TYPE_CHAR           : delete (char*)(data);         break;
          case XVARIANT_TYPE_XCHAR          : delete (char*)(data);         break;
          case XVARIANT_TYPE_FLOAT          : delete (float*)(data);        break;
          case XVARIANT_TYPE_DOUBLE         : delete (float*)(data);        break;
          case XVARIANT_TYPE_STRING         : delete (XSTRING*)(data);      break;      
          case XVARIANT_TYPE_DATE           :
          case XVARIANT_TYPE_TIME           :
          case XVARIANT_TYPE_DATETIME       : delete (XDATETIME*)(data);    break;
          case XVARIANT_TYPE_BUFFER         : delete (XBUFFER*)(data);      break;
         
                                  default   : break;
        }
    }

  type    = XVARIANT_TYPE_NULL;
  size    = 0;
  data    = NULL;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XVARIANT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XVARIANT::Clean()
{
  type      = XVARIANT_TYPE_NULL;
  size      = 0;
  data      = NULL;
}

