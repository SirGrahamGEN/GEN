/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XFileDBF.cpp
* 
* @class      XFILEDBF
* @brief      eXtended Utils DBF file class
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

#include "XFileDBF.h"

#include <string.h>

#include "XFactory.h"
#include "XDateTime.h"

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


#pragma region CLASS_XFILEDBF_FIELD


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEDBF_FIELD::XFILEDBF_FIELD()
* @brief      Constructor of class
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEDBF_FIELD::XFILEDBF_FIELD()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEDBF_FIELD::~XFILEDBF_FIELD()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEDBF_FIELD::~XFILEDBF_FIELD()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILEDBF_FIELD::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFILEDBF_FIELD::Clean()
{
  name.Empty();

  type = XFILEDBF_FIELDTYPE_UNKNOWN;
  size = 0;
}


#pragma endregion


#pragma region CLASS_XFILEDBF_RECORD


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEDBF_RECORD::XFILEDBF_RECORD(XVECTOR<XFILEDBF_FIELD*>* fields)
* @brief      Constructor of class
* @ingroup    XUTILS
*
* @param[in]  fields :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEDBF_RECORD::XFILEDBF_RECORD(XVECTOR<XFILEDBF_FIELD*>* fields)
{
  Clean();

  size=0;

  this->fields = fields;

  for(XDWORD c=0;c<fields->GetSize();c++)
    {
      XFILEDBF_FIELD* field = fields->Get(c);
      if(field) size+=field->size;
    }

  size++;

  if(size)
    {
      datarec = new XBYTE [size];
      if(datarec) memset(datarec,' ',size);
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEDBF_RECORD::~XFILEDBF_RECORD()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEDBF_RECORD::~XFILEDBF_RECORD()
{
  delete[] datarec;
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEDBF_RECORD::IsDelete()
* @brief      Is delete
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEDBF_RECORD::IsDelete()
{
  if(!datarec) return true;

  if(datarec[0]==' ') return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEDBF_RECORD::IsFieldEmpty(int indexfield)
* @brief      Is field empty
* @ingroup    XUTILS
*
* @param[in]  indexfield :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEDBF_RECORD::IsFieldEmpty(int indexfield)
{
  if(!fields) return true;
  int nfields=(fields->GetSize()-1);

  if(indexfield>nfields) return true;

  XFILEDBF_FIELD* field = (XFILEDBF_FIELD*)fields->Get(indexfield);
  if(!field) return true;

  XBYTE* data = GetData(indexfield);
  if(!data) return true;

  for(int c=0; c<field->size; c++)
    {
      if(data[c]!=0x20) return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE* XFILEDBF_RECORD::GetData(int indexfield)
* @brief      Get data
* @ingroup    XUTILS
*
* @param[in]  indexfield :
*
* @return     XBYTE* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE* XFILEDBF_RECORD::GetData(int indexfield)
{
  if(!fields)  return NULL;
  int nfields=(fields->GetSize()-1);

  if(indexfield>nfields) return NULL;

  XFILEDBF_FIELD* field = (XFILEDBF_FIELD*)fields->Get(indexfield);
  if(!field) return NULL;

  if(!field->size) return NULL;

  int offset = GetOffset(indexfield);
  if(offset==-1) return NULL;

  return (XBYTE*)(&datarec[offset]);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEDBF_RECORD::SetData(int indexfield, XBYTE* data, int limitsize)
* @brief      Set data
* @ingroup    XUTILS
*
* @param[in]  indexfield :
* @param[in]  data :
* @param[in]  limitsize :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEDBF_RECORD::SetData(int indexfield, XBYTE* data, int limitsize)
{
  if(!data) return false;

  int offset = GetOffset(indexfield);
  if(offset==-1) return false;

  XFILEDBF_FIELD* field = (XFILEDBF_FIELD*)fields->Get(indexfield);
  if(!field)     return false;
  XDWORD size = field->size;

  memset((XBYTE*)(&datarec[offset]), ' '  , field->size);
  memcpy((XBYTE*)(&datarec[offset]), data , (limitsize==-1)?size:limitsize);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEDBF_RECORD::GetDataString(int indexfield, XSTRING& string)
* @brief      Get data string
* @ingroup    XUTILS
*
* @param[in]  indexfield :
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEDBF_RECORD::GetDataString(int indexfield, XSTRING& string)
{
  string.Empty();

  if(!fields)  return false;
  int nfields=(fields->GetSize()-1);

  if(indexfield>nfields) return false;

  XFILEDBF_FIELD* field = (XFILEDBF_FIELD*)fields->Get(indexfield);
  if(!field) return false;

  if(!field->size)                                return false;
  if(field->type != XFILEDBF_FIELDTYPE_CHARACTER) return false;

  int offset = GetOffset(indexfield);
  if(offset==-1) return false;

  char  value[_MAXSTR];
  int   size = field->size;

  memset(value, 0, _MAXSTR);
  if(size>_MAXSTR) size = _MAXSTR;

  memcpy((XBYTE*)(value), (XBYTE*)(&datarec[offset]), size);

  string = value;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEDBF_RECORD::SetDataString(int indexfield, XSTRING& string)
* @brief      Set data string
* @ingroup    XUTILS
*
* @param[in]  indexfield :
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEDBF_RECORD::SetDataString(int indexfield, XSTRING& string)
{
  int offset = GetOffset(indexfield);
  if(offset==-1) return false;

  XFILEDBF_FIELD* field = (XFILEDBF_FIELD*)fields->Get(indexfield);
  if(!field)     return false;

  if(!field->size)                                return false;
  if(field->type != XFILEDBF_FIELDTYPE_CHARACTER) return false;

  XDWORD sizestring = string.GetSize();
  if(sizestring > field->size) sizestring = field->size;


  XBUFFER charstr;
  
  string.ConvertToASCII(charstr);

  memset((XBYTE*)(&datarec[offset]), ' ', field->size);

  for(XDWORD c=0; c<sizestring; c++)
    {
      datarec[offset+c] = charstr.Get()[c];
    }
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEDBF_RECORD::SetCharacterType(int indexfield,XCHAR* data)
* @brief      Set character type
* @ingroup    XUTILS
*
* @param[in]  indexfield :
* @param[in]  data :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEDBF_RECORD::SetCharacterType(int indexfield,XCHAR* data)
{
  int offset = GetOffset(indexfield);
  if(offset==-1) return false;

  XFILEDBF_FIELD* field = (XFILEDBF_FIELD*)fields->Get(indexfield);
  if(!field)     return false;

  XSTRING _data(data);
  int        size = field->size;
  
  XBUFFER charstr;
  
  _data.ConvertToASCII(charstr);
  
  memset((XBYTE*)(&datarec[offset]), ' ', size);
  memcpy((char*)(&datarec[offset]), charstr.GetPtrChar(), _data.GetSize());

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEDBF_RECORD::SetData(XBYTE* data,XDWORD size)
* @brief      Set data
* @ingroup    XUTILS
*
* @param[in]  data :
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEDBF_RECORD::SetData(XBYTE* data,XDWORD size)
{
  memcpy(datarec,data,size);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XFILEDBF_RECORD::GetSize()
* @brief      Get size
* @ingroup    XUTILS
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XFILEDBF_RECORD::GetSize()
{
  return size;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XFILEDBF_RECORD::GetSizeField(int indexfield)
* @brief      Get size field
* @ingroup    XUTILS
*
* @param[in]  indexfield :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XFILEDBF_RECORD::GetSizeField(int indexfield)
{
  if(!fields) return 0;
  int nfields=(fields->GetSize()-1);
  if(indexfield>nfields) return 0;

  XFILEDBF_FIELD* field = (XFILEDBF_FIELD*)fields->Get(indexfield);
  if(!field)              return 0;

  return field->size;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XFILEDBF_RECORD::GetOffset(int indexfield)
* @brief      Get offset
* @ingroup    XUTILS
*
* @param[in]  indexfield :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XFILEDBF_RECORD::GetOffset(int indexfield)
{
  if(!fields)             return -1;

  int nfields=(fields->GetSize()-1);
  if(indexfield>nfields)  return -1;

  XFILEDBF_FIELD* field = (XFILEDBF_FIELD*)fields->Get(indexfield);
  if(!field)              return -1;
  if(!field->size)        return -1;

  int offset=1;

  for(int c=0;c<indexfield;c++)
    {
      field = (XFILEDBF_FIELD*)fields->Get(c);
      if(field)  offset+=field->size;
    }

  return offset;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILEDBF_RECORD::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFILEDBF_RECORD::Clean()
{
  size    = 0;
  datarec = NULL;
}


#pragma endregion


#pragma region CLASS_XFILEDBF_HEADER


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEDBF_HEADER::XFILEDBF_HEADER()
* @brief      Constructor of class
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEDBF_HEADER::XFILEDBF_HEADER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEDBF_HEADER::XFILEDBF_HEADER(XFILE* fileb)
* @brief      Constructor of class
* @ingroup    XUTILS
*
* @param[in]  fileb :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEDBF_HEADER::XFILEDBF_HEADER(XFILE* fileb)
{
  Clean();

  Load(fileb);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEDBF_HEADER::~XFILEDBF_HEADER()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEDBF_HEADER::~XFILEDBF_HEADER()
{
  if(headerdata)
    {
      delete[] headerdata;
      headerdata = NULL;
    }

  DeleteAllFields();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEDBF_HEADER::Load(XFILE* xfile)
* @brief      Load
* @ingroup    XUTILS
*
* @param[in]  xfile :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEDBF_HEADER::Load(XFILE* xfile)
{
  // ---------------------------
  // Read header
  if(!xfile->SetPosition(8)) return false;

  if(!xfile->Read((XBYTE*)&headersize,2)) return false;
  if(!headersize) return 0;

  if(headerdata)
    {
      delete[] headerdata;
      headerdata = NULL;
    }

  headerdata = new XBYTE[headersize];
  if(!headerdata) return false;

  if(!xfile->SetPosition(0)) return false;
  if(!xfile->Read(headerdata,headersize)) return false;

  int index=XFILEDBF_FIELDSTART;

  while(headerdata[index]!=0x0D)
    {
      XFILEDBF_FIELDTYPE type;

      switch(headerdata[index+11])
        {
          case 'C' : type=XFILEDBF_FIELDTYPE_CHARACTER; break;
          case 'D' : type=XFILEDBF_FIELDTYPE_DATE;      break;
          case 'F' : type=XFILEDBF_FIELDTYPE_FLOATING;  break;
          case 'N' : type=XFILEDBF_FIELDTYPE_BINARYHEX; break;
          case 'L' : type=XFILEDBF_FIELDTYPE_LOGICAL;   break;
          case 'M' : type=XFILEDBF_FIELDTYPE_MEMO;      break;
          case 'V' : type=XFILEDBF_FIELDTYPE_VARIABLE;  break;
          case 'P' : type=XFILEDBF_FIELDTYPE_PICTURE;   break;
          case 'B' : type=XFILEDBF_FIELDTYPE_BINARY;    break;
          case 'G' : type=XFILEDBF_FIELDTYPE_GENERAL;   break;
          case '2' : type=XFILEDBF_FIELDTYPE_SHORTINT;  break;
          case '4' : type=XFILEDBF_FIELDTYPE_LONGINT;   break;
          case '8' : type=XFILEDBF_FIELDTYPE_DOUBLE;    break;
          default  : type=XFILEDBF_FIELDTYPE_UNKNOWN;   break;
        }

      if(type!=XFILEDBF_FIELDTYPE_UNKNOWN)
        {
          XSTRING name((char*)&headerdata[index]);

          if(!CreateField(type, name.Get(), headerdata[index+16])) return false;
        }

      index+=XFILEDBF_FIELDSIZE;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEDBF_HEADER::Create(XFILE* fileb)
* @brief      Create
* @ingroup    XUTILS
*
* @param[in]  fileb :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEDBF_HEADER::Create(XFILE* fileb)
{
  headersize = (XWORD)(XFILEDBF_FIELDSTART + fields.GetSize()*XFILEDBF_FIELDSIZE+ 1);

  headerdata = new XBYTE [headersize];
  if(!headerdata) return false;

  memset(headerdata,0,headersize);

  headerdata[0] = 0x03;

  XDATETIME* GEN_XFACTORY_CREATE(xdatetime, CreateDateTime())
  if(xdatetime)
    {
      xdatetime->Read();

      headerdata[1] = xdatetime->GetYear()-1900;
      headerdata[2] = xdatetime->GetMonth();
      headerdata[3] = xdatetime->GetDay();

      delete xdatetime;
    }

  XDWORD* nf = (XDWORD*)&headerdata[4];
  (*nf)=0;

  XWORD* hs  = (XWORD*)(&headerdata[8]);
  (*hs)=headersize;

  XWORD* rs  = (XWORD*)(&headerdata[10]);
  (*rs)=GetSizeRecord();


  int index=XFILEDBF_FIELDSTART;

  for(XDWORD c=0;c<fields.GetSize();c++)
    {
      XFILEDBF_FIELD* field  = (XFILEDBF_FIELD*)fields.Get(c);
      char            type   = ' ';

      if(field)
        {
          memset(&headerdata[index],0,XFILEDBF_FIELDSIZE);


          XBUFFER charstr;
          
          field->name.ConvertToASCII(charstr);
         
          XDWORD size = (int)strlen(charstr);
          if(size>XFILEDBF_FIELDSIZE) size = XFILEDBF_FIELDSIZE;

          memcpy((char*)(&headerdata[index]), charstr.Get(), size);
                  
          switch(field->type)
            {
              case XFILEDBF_FIELDTYPE_CHARACTER : type='C'; break;
              case XFILEDBF_FIELDTYPE_DATE      : type='D'; break;
              case XFILEDBF_FIELDTYPE_FLOATING  : type='F'; break;
              case XFILEDBF_FIELDTYPE_BINARYHEX : type='N'; break;
              case XFILEDBF_FIELDTYPE_LOGICAL   : type='L'; break;
              case XFILEDBF_FIELDTYPE_MEMO      : type='M'; break;
              case XFILEDBF_FIELDTYPE_VARIABLE  : type='V'; break;
              case XFILEDBF_FIELDTYPE_PICTURE   : type='P'; break;
              case XFILEDBF_FIELDTYPE_BINARY    : type='B'; break;
              case XFILEDBF_FIELDTYPE_GENERAL   : type='G'; break;
              case XFILEDBF_FIELDTYPE_SHORTINT  : type='2'; break;
              case XFILEDBF_FIELDTYPE_LONGINT   : type='4'; break;
              case XFILEDBF_FIELDTYPE_DOUBLE    : type='8'; break;
            }

          headerdata[index+11]=type;
          headerdata[index+16]=field->size;

          index+=XFILEDBF_FIELDSIZE;
        }
    }

  headerdata[headersize-1] = 0x0D;

  if(!fileb->SetPosition(0)) return false;
  if(!fileb->Write(headerdata,headersize)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEDBF_HEADER::Update(XFILE* fileb)
* @brief      Update
* @ingroup    XUTILS
*
* @param[in]  fileb :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEDBF_HEADER::Update(XFILE* fileb)
{
  XDWORD nrecords = GetNRecords();

  if(!fileb->SetPosition(4)) return false;
  if(!fileb->Write((XBYTE*)&nrecords,sizeof(XDWORD)))               return false;

  if(!fileb->SetPosition(12)) return false;
  if(!fileb->Write((XBYTE*)&headerdata[12],XFILEDBF_HEADRESERVED)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEDBF_TYPE XFILEDBF_HEADER::GetType()
* @brief      Get type
* @ingroup    XUTILS
*
* @return     XFILEDBF_TYPE :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEDBF_TYPE XFILEDBF_HEADER::GetType()
{
  if(!headerdata) return XFILEDBF_TYPE_UNKNOWN;

  switch(headerdata[0])
    {
      case 0x03:
      case 0x83: return XFILEDBF_TYPE_DBASEIII;
/*
      case 0x00: return XFILEDBF_TYPE_DBASEIV;
      case 0x00: return XFILEDBF_TYPE_DBASEV;
      case 0x00: return XFILEDBF_TYPE_FOXPRO;
      case 0x00: return XFILEDBF_TYPE_CLIPPER;
*/
    }

  return XFILEDBF_TYPE_UNKNOWN;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWORD XFILEDBF_HEADER::GetHeaderSize()
* @brief      Get header size
* @ingroup    XUTILS
*
* @return     XWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XWORD XFILEDBF_HEADER::GetHeaderSize()
{
  if(!headerdata) return 0;

  return headersize;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE* XFILEDBF_HEADER::GetHeaderData()
* @brief      Get header data
* @ingroup    XUTILS
*
* @return     XBYTE* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE* XFILEDBF_HEADER::GetHeaderData()
{
  return headerdata;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XFILEDBF_HEADER::GetReservedData()
* @brief      Get reserved data
* @ingroup    XUTILS
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XFILEDBF_HEADER::GetReservedData()
{
  if(!headerdata) return 0;

  XDWORD* reserved = (XDWORD*)(&headerdata[12]);

  return (*reserved);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEDBF_HEADER::SetReservedData(XDWORD data)
* @brief      Set reserved data
* @ingroup    XUTILS
*
* @param[in]  data :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEDBF_HEADER::SetReservedData(XDWORD data)
{
  if(!headerdata) return false;

  XDWORD* reserved = (XDWORD*)(&headerdata[12]);

  (*reserved) = data;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XFILEDBF_HEADER::GetNFields()
* @brief      Get N fields
* @ingroup    XUTILS
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XFILEDBF_HEADER::GetNFields()
{
  return fields.GetSize();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XFILEDBF_HEADER::GetNRecords()
* @brief      Get N records
* @ingroup    XUTILS
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XFILEDBF_HEADER::GetNRecords()
{
  if(!headerdata) return 0;

  XDWORD *nrec = (XDWORD*)((&headerdata[4]));

  return (XDWORD)(*nrec);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEDBF_HEADER::SetNRecords(XDWORD nrecords)
* @brief      Set N records
* @ingroup    XUTILS
*
* @param[in]  nrecords :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEDBF_HEADER::SetNRecords(XDWORD nrecords)
{
  if(!headerdata) return false;

  XDWORD* nr=(XDWORD*)(&headerdata[4]);
  (*nr)=nrecords;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XFILEDBF_HEADER::GetSizeRecord()
* @brief      Get size record
* @ingroup    XUTILS
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XFILEDBF_HEADER::GetSizeRecord()
{
  XDWORD size=0;

  if(fields.IsEmpty()) return size;

  int nfields=fields.GetSize();

  for(int c=0;c<nfields;c++)
    {
      XFILEDBF_FIELD* field = (XFILEDBF_FIELD*)fields.Get(c);

      if(field) size+=field->size;
    }

  size++;

  return size;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XVECTOR<XFILEDBF_FIELD*>* XFILEDBF_HEADER::GetFields()
* @brief      Get fields
* @ingroup    XUTILS
*
* @return     XVECTOR<XFILEDBF_FIELD*>* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<XFILEDBF_FIELD*>* XFILEDBF_HEADER::GetFields()
{
  return &fields;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEDBF_FIELD* XFILEDBF_HEADER::GetField(int indexfield)
* @brief      Get field
* @ingroup    XUTILS
*
* @param[in]  indexfield :
*
* @return     XFILEDBF_FIELD* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEDBF_FIELD* XFILEDBF_HEADER::GetField(int indexfield)
{
  int nfields=(fields.GetSize()-1);

  if(indexfield>nfields) return NULL;

  return (XFILEDBF_FIELD*)fields.Get(indexfield);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEDBF_HEADER::CreateField(XFILEDBF_FIELDTYPE type,XCHAR* name,XBYTE size)
* @brief      Create field
* @ingroup    XUTILS
*
* @param[in]  type :
* @param[in]  name :
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEDBF_HEADER::CreateField(XFILEDBF_FIELDTYPE type,XCHAR* name,XBYTE size)
{
  XFILEDBF_FIELD* field;

  field = new XFILEDBF_FIELD();
  if(!field) return false;

  field->name = name;
  field->type = type;
  field->size = size;

  if(!field->size)
    {
      switch(type)
        {
          case XFILEDBF_FIELDTYPE_UNKNOWN   : field->size=0;   break;
          case XFILEDBF_FIELDTYPE_CHARACTER : field->size=0;   break;
          case XFILEDBF_FIELDTYPE_DATE      : field->size=0;   break;
          case XFILEDBF_FIELDTYPE_FLOATING  : field->size=32;  break;
          case XFILEDBF_FIELDTYPE_BINARYHEX : field->size=32;  break;
          case XFILEDBF_FIELDTYPE_LOGICAL   : field->size=0;   break;
          case XFILEDBF_FIELDTYPE_MEMO      : field->size=0;   break;
          case XFILEDBF_FIELDTYPE_VARIABLE  : break;
          case XFILEDBF_FIELDTYPE_PICTURE   : break;
          case XFILEDBF_FIELDTYPE_BINARY    : break;
          case XFILEDBF_FIELDTYPE_GENERAL   : break;
          case XFILEDBF_FIELDTYPE_SHORTINT  : break;
          case XFILEDBF_FIELDTYPE_LONGINT   : break;
          case XFILEDBF_FIELDTYPE_DOUBLE    : break;
        }
    }

  fields.Add(field);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEDBF_HEADER::CopyFrom(XFILEDBF_HEADER* header)
* @brief      Copy from
* @ingroup    XUTILS
*
* @param[in]  header :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEDBF_HEADER::CopyFrom(XFILEDBF_HEADER* header)
{
  headersize = header->GetHeaderSize();

  if(headerdata) delete [] headerdata;

  headerdata = new XBYTE[headersize];
  if(!headerdata) return false;

  memcpy(headerdata, header->GetHeaderData(), headersize);

  for(int c=0; c<header->GetNFields(); c++)
    {
      XFILEDBF_FIELD* field = new XFILEDBF_FIELD();
      if(field)
        {
          field->name = header->GetField(c)->name;
          field->size = header->GetField(c)->size;
          field->type = header->GetField(c)->type;

          fields.Add(field);
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEDBF_HEADER::DeleteAllFields()
* @brief      Delete all fields
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEDBF_HEADER::DeleteAllFields()
{
  if(fields.IsEmpty()) return false;

  fields.DeleteContents();
  fields.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILEDBF_HEADER::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFILEDBF_HEADER::Clean()
{
  headerdata  = NULL;
  headersize  = 0;
}


#pragma endregion


#pragma region CLASS_XFILEDBF


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEDBF::XFILEDBF()
* @brief      Constructor of class
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEDBF::XFILEDBF()
{
  Clean();

  if(!CreatePrimaryFile()) return;

  CreateHeader();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEDBF::XFILEDBF(XPATH& xpath)
* @brief      Constructor of class
* @ingroup    XUTILS
*
* @param[in]  xpath :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEDBF::XFILEDBF(XPATH& xpath)
{
  Clean();

  if(!CreatePrimaryFile()) return;

  CreateHeader();

  this->xpath = xpath;

  Open(xpath);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEDBF::XFILEDBF(XFILE* fileb)
* @brief      Constructor of class
* @ingroup    XUTILS
*
* @param[in]  fileb :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEDBF::XFILEDBF(XFILE* fileb)
{
  Clean();

  this->xpath = fileb->GetPathNameFile();

  file = fileb;

  CreateHeader();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEDBF::~XFILEDBF()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEDBF::~XFILEDBF()
{
  Close();

  if(!DeletePrimaryFile()) return;

  delete header;

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEDBF::Open(XPATH& xpath,bool readonly)
* @brief      Open
* @ingroup    XUTILS
*
* @param[in]  xpath :
* @param[in]  readonly :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEDBF::Open(XPATH& xpath,bool readonly)
{
  if(!header)         return false;
  if(!file)           return false;
  if(xpath.IsEmpty()) return false;

  this->xpath = xpath;

  if(!file->Open(xpath,readonly)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEDBF::Create(XPATH& xpath)
* @brief      Create
* @ingroup    XUTILS
*
* @param[in]  xpath :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEDBF::Create(XPATH& xpath)
{
  if(!header)         return false;
  if(!file)           return false;
  if(xpath.IsEmpty()) return false;

  this->xpath = xpath;

  if(!file->Create(xpath))  return false;
  if(!header->Create(file)) return false;

  file->Flush();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEDBF::IsOpen()
* @brief      Is open
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEDBF::IsOpen()
{
  if(!file) return false;

  return file->IsOpen();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEDBF::Close()
* @brief      Close
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEDBF::Close()
{
  if(header)
    {
      delete header;
      CreateHeader();
    }

  if(!file->Close()) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPATH* XFILEDBF::GetXPath()
* @brief      Get X path
* @ingroup    XUTILS
*
* @return     XPATH* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XPATH* XFILEDBF::GetXPath()
{
  return &xpath;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEDBF_HEADER* XFILEDBF::GetHeader()
* @brief      Get header
* @ingroup    XUTILS
*
* @return     XFILEDBF_HEADER* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEDBF_HEADER* XFILEDBF::GetHeader()
{
  return header;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEDBF_RECORD* XFILEDBF::ReadRecord(XDWORD nrecord)
* @brief      Read record
* @ingroup    XUTILS
*
* @param[in]  nrecord :
*
* @return     XFILEDBF_RECORD* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEDBF_RECORD* XFILEDBF::ReadRecord(XDWORD nrecord)
{
  if(!IsOpen()) return NULL;
  if(!header)   return NULL;

  XFILEDBF_RECORD* record;
  if(nrecord>=header->GetNRecords()) return NULL;

  XDWORD sizerecord = header->GetSizeRecord();

  if(!sizerecord) return NULL;

  record = new XFILEDBF_RECORD(header->GetFields());
  if(!record) return NULL;

  XBYTE* data = new XBYTE [sizerecord];
  if(!data)
    {
      delete record;
      return NULL;
    }

  int position=header->GetHeaderSize()+(sizerecord*nrecord);

  file->SetPosition(position);

  if(!file->Read(data,sizerecord))
    {
      delete record;
      delete[] data;

      return NULL;
    }

  record->SetData(data,sizerecord);

  delete[] data;

  return record;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEDBF::WriteRecord(XDWORD nrecord,XFILEDBF_RECORD* record)
* @brief      Write record
* @ingroup    XUTILS
*
* @param[in]  nrecord :
* @param[in]  record :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEDBF::WriteRecord(XDWORD nrecord,XFILEDBF_RECORD* record)
{
  if(!IsOpen()) return false;
  if(!header)   return false;

  int position = header->GetHeaderSize()+(header->GetSizeRecord()*nrecord);

  file->SetPosition(position);

  XBYTE delflag=record->IsDelete()?'*':' ';

  if(!file->Write(&delflag,1)) return false;
  if(!file->Write(record->GetData(0),header->GetSizeRecord()-1)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEDBF::InsertRecord(XDWORD nrecord, XFILEDBF_RECORD* record)
* @brief      Insert record
* @ingroup    XUTILS
*
* @param[in]  nrecord :
* @param[in]  record :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEDBF::InsertRecord(XDWORD nrecord, XFILEDBF_RECORD* record)
{
  if(!IsOpen()) return false;
  if(!header)   return false;

  int position = header->GetHeaderSize()+(header->GetSizeRecord()*nrecord);

  file->SetPosition(position);

  XBYTE delflag=record->IsDelete()?'*':' ';

  XBUFFER xbuffer;

  xbuffer.Add(delflag);
  xbuffer.Add(record->GetData(0), (header->GetSizeRecord()-1));

  if(!file->InsertBlock(xbuffer.Get(), xbuffer.GetSize()))   return false;

  header->SetNRecords(header->GetNRecords()+1);
  header->Update(file);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEDBF::AddRecord(XFILEDBF_RECORD* record)
* @brief      Add record
* @ingroup    XUTILS
*
* @param[in]  record :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEDBF::AddRecord(XFILEDBF_RECORD* record)
{
  if(!IsOpen()) return false;
  if(!header)   return false;

  XDWORD size = header->GetSizeRecord()-1;

  XBYTE   specialend;
  XQWORD  position;

  file->SetPosition((XDWORD)XFILE_SEEKEND);
  file->GetPosition(position);
  file->SetPosition(position-1);

  if(file->Read(&specialend,1))
    {
      if(specialend == 0x1A) file->SetPosition(position-1);
    }

  XBYTE delflag=record->IsDelete()?'*':' ';

  if(!file->Write(&delflag,1)) return false;
  if(!file->Write(record->GetData(0),size)) return false;

  specialend = 0x1A;
  if(!file->Write(&specialend, 1)) return false;

  header->SetNRecords(header->GetNRecords()+1);

  header->Update(file);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEDBF::DeleteRecord(XDWORD nrecord)
* @brief      Delete record
* @ingroup    XUTILS
*
* @param[in]  nrecord :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEDBF::DeleteRecord(XDWORD nrecord)
{
  if(!IsOpen()) return false;
  if(!header)   return false;

  char*  data;
  int    size = header->GetSizeRecord()-1;

  data = new char[size+10];
  if(!data) return false;

  memset(data,0,size+10);

  int position = header->GetHeaderSize()+(header->GetSizeRecord()*nrecord);

  file->SetPosition(position);

  XBYTE delflag='*';

  if(!file->Write(&delflag,1)) return false;
  if(!file->Write((XBYTE*)data,size)) return false;

  delete[] data;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEDBF::Pack()
* @brief      Pack
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEDBF::Pack()
{
  if(!IsOpen()) return false;
  if(!header)   return false;

  XPATH xpathtmp;

  xpathtmp  = GetXPath()->Get();
  xpathtmp += __L(".tmp");

  XFILEDBF* dbftmp = new XFILEDBF();
  if(!dbftmp) return false;

  dbftmp->GetHeader()->CopyFrom(header);
  dbftmp->GetHeader()->SetNRecords(0);

  delete dbftmp->GetHeader()->GetHeaderData();

  if(!dbftmp->Create(xpathtmp))
    {
      delete dbftmp;
      return false;
    }

  for(XDWORD c=0; c< header->GetNRecords(); c++)
    {
      XFILEDBF_RECORD* record = ReadRecord(c);
      if(record)
        {
          if(!record->IsDelete())
            {
              dbftmp->AddRecord(record);
            }

          delete record;
        }
    }

  dbftmp->Close();

  delete dbftmp;

  Close();


  XFILE* GEN_XFACTORY_CREATE(xfile, Create_File())
  if(!xfile) return false;

  bool status = true;

  if(xfile->Erase(GetXPath()->Get()))
    {
      if(!xfile->Rename(xpathtmp.Get(), GetXPath()->Get())) status = false;

    } else status = false;

  GEN_XFACTORY.Delete_File(xfile);

  if(status)
    {
      status = Open((*GetXPath()), GetPrimaryFile()->IsReadOnly());
      if(status)
        {
          delete GetHeader();
          CreateHeader();
          GetHeader()->Load(GetPrimaryFile());
        }
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEDBF::Reduction(int maxrecords, int reductionpercent)
* @brief      Reduction
* @ingroup    XUTILS
*
* @param[in]  maxrecords :
* @param[in]  reductionpercent :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEDBF::Reduction(int maxrecords, int reductionpercent)
{
  if(!IsOpen()) return false;
  if(!header)   return false;

  int nrecords  = header->GetNRecords();
  if(nrecords<maxrecords) return true;

  int nrectosave = (nrecords*reductionpercent)/100;

  for(int c=0;c<(nrecords-nrectosave);c++)
    {
      DeleteRecord(c);
    }

  if(!Pack()) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEDBF::CreateHeader()
* @brief      Create header
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEDBF::CreateHeader()
{
  header = new XFILEDBF_HEADER();
  if(!header)  return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILEDBF::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFILEDBF::Clean()
{
  header    = NULL;
}


#pragma endregion


#pragma endregion

