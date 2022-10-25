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
#include "XSerializable.h"
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
* @fn         XVARIANT::XVARIANT(const XVARIANT& variant)
* @brief      Constructor
* @ingroup    XUTILS
*
* @param[in]  const :
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::XVARIANT(const XVARIANT& variant)
{
  Clean();

  (*this) = variant;
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
* @fn         const XVARIANT& XVARIANT::operator=(const XSERIALIZABLE& serializable)
* @brief      operator=
* @ingroup    XUTILS
*
* @param[in]  XSERIALIZABLE& serializable :
*
* @return     const :
*
* --------------------------------------------------------------------------------------------------------------------*/
const XVARIANT& XVARIANT::operator=(const XSERIALIZABLE& serializable)
{
  XBUFFER xbuffer;

  serializable.DeSerialize(&xbuffer);

  if(data) Destroy();

  size = xbuffer.GetSize();
  if(size)
    {
      data = new XBYTE[size];
      if(data)
        {
          type = XVARIANT_TYPE_SERIALIZABLE;
          xbuffer.Get((XBYTE*)data, size, 0);
        }
    }

  return (*this);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         const XVARIANT& XVARIANT::operator = (bool boolean)
* @brief      operator =
* @ingroup    XUTILS
* 
* @param[in]  boolean : 
* 
* @return     const : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
const XVARIANT& XVARIANT::operator = (bool boolean)
{
  if(data) Destroy();

  type  = XVARIANT_TYPE_BOOLEAN;
  size  = sizeof(bool);
  data  = (void*)new bool;

  if(data)
    {
      *((bool*)data) = boolean;
    }

  return *this;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         const XVARIANT& XVARIANT::operator = (int integer)
* @brief      operator =
* @ingroup    XUTILS
*
* @param[in]  integer :
*
* @return     const :
*
* --------------------------------------------------------------------------------------------------------------------*/
const XVARIANT& XVARIANT::operator = (int integer)
{
  if(data) Destroy();

  type  = XVARIANT_TYPE_INTEGER;
  size  = sizeof(int);
  data  = (void*)new int;

  if(data)
    {
      *((int*)data) = integer;
    }

  return *this;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         const XVARIANT& XVARIANT::operator = (XDWORD integer)
* @brief      operator =
* @ingroup    XUTILS
*
* @param[in]  integer :
*
* @return     const :
*
* --------------------------------------------------------------------------------------------------------------------*/
const XVARIANT& XVARIANT::operator = (XDWORD integer)
{
  if(data)  Destroy();

  type = XVARIANT_TYPE_INTEGER;
  size = sizeof(XDWORD);

  data= (void*)new XDWORD;
  if(data)
    {
      *((XDWORD*)data)  = integer;
    }

  return (*this);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         const XVARIANT& XVARIANT::operator = (XQWORD integer)
* @brief      operator =
* @ingroup    XUTILS
*
* @param[in]  integer :
*
* @return     const :
*
* --------------------------------------------------------------------------------------------------------------------*/
const XVARIANT& XVARIANT::operator = (XQWORD integer)
{
  if(data) Destroy();

  type = XVARIANT_TYPE_DOUBLEINTEGER;
  size = sizeof(XQWORD);

  data= (void*)new XQWORD;
  if(data)
    {
      *((XQWORD*)data)  = integer;
    }

  return (*this);
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
  if(data)  Destroy();

  type = XVARIANT_TYPE_FLOAT;

  size = sizeof(float);

  data = (void*)new float;
  if(data!=NULL)
    {
      *((float*)data)=value;
    }

  return (*this);
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
  if(data)  Destroy();

  type = XVARIANT_TYPE_DOUBLE;

  size = sizeof(double);

  data = (void*)new double;
  if(data!=NULL)
    {
      *((double*)data)=value;
    }

  return (*this);
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
  if(data)  Destroy();

  type = XVARIANT_TYPE_XCHAR;
  size = sizeof(XCHAR);

  data= (void*)new XCHAR;
  if(data)
    {
      *((XCHAR*)data) = value;
    }

  return (*this);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         const XVARIANT& XVARIANT::operator = (XCHAR* string)
* @brief      operator =
* @ingroup    XUTILS
*
* @param[in]  string :
*
* @return     const :
*
* --------------------------------------------------------------------------------------------------------------------*/
const XVARIANT& XVARIANT::operator = (XCHAR* string)
{
  GetDataFromString(string);

  return (*this);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         const XVARIANT& XVARIANT::operator = (XSTRING& string)
* @brief      operator =
* @ingroup    XUTILS
*
* @param[in]  string :
*
* @return     const :
*
* --------------------------------------------------------------------------------------------------------------------*/
const XVARIANT& XVARIANT::operator = (XSTRING& string)
{
  GetDataFromString(string.Get());

  return (*this);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         const XVARIANT& XVARIANT::operator = (char* string)
* @brief      operator =
* @ingroup    XUTILS
*
* @param[in]  string :
*
* @return     const :
*
* --------------------------------------------------------------------------------------------------------------------*/
const XVARIANT& XVARIANT::operator = (char* string)
{
  if(data) Destroy();

  data = new XSTRING();
  if(data)
    {
      type = XVARIANT_TYPE_STRING;
      size = sizeof(XSTRING);

      if (static_cast<XSTRING*>(data)) static_cast<XSTRING*>(data)->Set(string);
    }

  return (*this);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         const XVARIANT& XVARIANT::operator = (char character)
* @brief      operator =
* @ingroup    XUTILS
*
* @param[in]  character :
*
* @return     const :
*
* --------------------------------------------------------------------------------------------------------------------*/
const XVARIANT& XVARIANT::operator = (char character)
{
  if(data) Destroy();

  type = XVARIANT_TYPE_CHAR;
  size = sizeof(char);

  data=(void*)new char;
  if(data)
    {
      *((char*)data) = character;
    }

  return (*this);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         const XVARIANT& XVARIANT::operator = (const XVARIANT& origin)
* @brief      operator =
* @ingroup    XUTILS
*
* @param[in]  XVARIANT& origin :
*
* @return     const :
*
* --------------------------------------------------------------------------------------------------------------------*/
const XVARIANT& XVARIANT::operator = (const XVARIANT& origin)
{
  if(&origin==this) return (*this);

  if(origin.data==this->data)  return (*this);

  if(data) Destroy();

  size    = origin.size;
  type    = origin.type;
  switch(type)
    {
      case XVARIANT_TYPE_BOOLEAN        : (*this) = (bool)(XVARIANT&)origin;      break;
      case XVARIANT_TYPE_INTEGER        : (*this) = (int)(XVARIANT&)origin;       break;
      case XVARIANT_TYPE_DOUBLEINTEGER  : (*this) = (XQWORD)(XVARIANT&)origin;    break;
      case XVARIANT_TYPE_CHAR           : (*this) = (char)(XVARIANT&)origin;      break;
      case XVARIANT_TYPE_FLOAT          : (*this) = (float)(XVARIANT&)origin;     break;
      case XVARIANT_TYPE_DOUBLE         : (*this) = (double)(XVARIANT&)origin;    break;
      case XVARIANT_TYPE_XCHAR          : (*this) = (XCHAR)(XVARIANT&)origin;     break;
      case XVARIANT_TYPE_STRING         : (*this) = (XCHAR*)(XVARIANT&)origin;    break;
      case XVARIANT_TYPE_SERIALIZABLE   : {
                                            data = new XBYTE[size];
                                            memcpy(data, origin.data, size);
                                          }
                                          break;
      case XVARIANT_TYPE_TIME           :
      case XVARIANT_TYPE_DATETIME       :
      case XVARIANT_TYPE_DATE           : {
                                            (*this) = (XDATETIME)(XVARIANT&)origin;
                                            type    = origin.type;
                                          }
                                          break;

                              default   : break;
    }

  return (*this);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         const XVARIANT& XVARIANT::operator = (XDATETIME datetime)
* @brief      operator =
* @ingroup    XUTILS
*
* @param[in]  datetime :
*
* @return     const :
*
* --------------------------------------------------------------------------------------------------------------------*/
const XVARIANT& XVARIANT::operator = (XDATETIME datetime)
{
  if(data) Destroy();

  data = (void*)new XDATETIME;
  if(data)
    {
      type = (XVARIANT_TYPE)XVARIANT_TYPE_DATETIME;
      size = sizeof(XDATETIME);
      *((XDATETIME*)data) = datetime;
    }

  return *this;
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
  if(IsNull())  return 0;

  return *(bool*)data;
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
  if (!IsNull())
  switch(type)
    {
      case XVARIANT_TYPE_STRING : if (static_cast<XSTRING*>(data)) return static_cast<XSTRING*>(data)->Get();
                                  break;

                        default : break;

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
* @fn         XVARIANT::operator const XCHAR*()
* @brief      onst XCHAR*
* @ingroup    XUTILS
*
* @return     XVARIANT::operator :
*
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT::operator const XCHAR*()
{
  if (!IsNull())
  switch (type)
    {
      case XVARIANT_TYPE_STRING : if(static_cast<XSTRING*>(data)) return (const XCHAR*)static_cast<XSTRING*>(data)->Get();
                                  break;
                        default : break;
    }

  return (const XCHAR*)NULL;
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
* @fn         void XVARIANT::GetSerializable(XSERIALIZABLE& serializable)
* @brief      GetSerializable
* @ingroup    XUTILS
*
* @param[in]  serializable :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XVARIANT::GetSerializable(XSERIALIZABLE& serializable)
{
  XBUFFER xbuffer;

  xbuffer.Resize(size);
  xbuffer.Set((XBYTE*)data, size, 0);

  serializable.Serialize(&xbuffer);
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XVARIANT::GetSerializable(XSERIALIZABLE* serializable)
* @brief      GetSerializable
* @ingroup    XUTILS
*
* @param[in]  serializable :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XVARIANT::GetSerializable(XSERIALIZABLE* serializable)
{
  XBUFFER xbuffer;

  xbuffer.Resize(size);
  xbuffer.Set((XBYTE*)data, size, 0);

  serializable->Serialize(&xbuffer);
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

      case XVARIANT_TYPE_SERIALIZABLE     : to.Format(__L("[Object]"));                                                                                           break;

      case XVARIANT_TYPE_BOOLEAN          : to.Format(__L("%s"), (*(bool*)this->data)?__L("true"):__L("false"));                                                  break;                                                                                           break;
      case XVARIANT_TYPE_INTEGER          : to.Format(__L("%d"),*(int*)this->data);                                                                               break;
      case XVARIANT_TYPE_DOUBLEINTEGER    : to.Format(__L("%d"),*(XQWORD*)this->data);                                                                            break;
      case XVARIANT_TYPE_CHAR             : to.Format(__L("%c"),*(int*)this->data);                                                                               break;
      case XVARIANT_TYPE_FLOAT            : to.Format(__L("%f"),*(float*)this->data);                                                                             break;
      case XVARIANT_TYPE_DOUBLE           : to.Format(__L("%lf"),*(double*)this->data);                                                                           break;
      case XVARIANT_TYPE_STRING           : to.Format(__L("%s"),((XSTRING*)this->data)->Get());                                                                   break;

      case XVARIANT_TYPE_TIME             : ((XDATETIME*)this->data)->GetDateTimeToString(XDATETIME_FORMAT_ADDTIME | XDATETIME_FORMAT_TIMEWITHSECONDS,  to);      break;
      case XVARIANT_TYPE_DATE             : ((XDATETIME*)this->data)->GetDateTimeToString(XDATETIME_FORMAT_YMD,                                         to);      break;
      case XVARIANT_TYPE_DATETIME         : ((XDATETIME*)this->data)->GetDateTimeToString(XDATETIME_FORMAT_STANDARD,                                    to);      break;      
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
          case XVARIANT_TYPE_BOOLEAN        : delete (bool*)data;           break;
          case XVARIANT_TYPE_INTEGER        : delete (int*)data;            break;
          case XVARIANT_TYPE_DOUBLEINTEGER  : delete (XQWORD*)data;         break;
          case XVARIANT_TYPE_CHAR           : delete (char*)(data);         break;
          case XVARIANT_TYPE_XCHAR          : delete (char*)(data);         break;
          case XVARIANT_TYPE_FLOAT          : delete (float*)(data);        break;
          case XVARIANT_TYPE_DOUBLE         : delete (float*)(data);        break;
          case XVARIANT_TYPE_STRING         : delete (XSTRING*)(data);      break;

          case XVARIANT_TYPE_SERIALIZABLE   : delete [] (XBYTE*)data;       break;

          case XVARIANT_TYPE_DATE           :
          case XVARIANT_TYPE_TIME           :
          case XVARIANT_TYPE_DATETIME       : delete (XDATETIME*)(data);    break;

          case XVARIANT_TYPE_NULL           :                               break;
                                  default   : //delete (void*)(data);       break;
                                              break;
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



