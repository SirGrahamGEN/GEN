/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XFileHEX.cpp
*
* @class      XFILEHEX
* @brief      eXtended HEX file class (hex ASCII format)
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

#include <stdio.h>
#include <string.h>

#include "XFileHEX.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------*/
/*  XFILEHEX_ENTRY                                                                                                    */
/*--------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEHEX_ENTRY::XFILEHEX_ENTRY()
* @brief      Constructor
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XFILEHEX_ENTRY::XFILEHEX_ENTRY()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEHEX_ENTRY::~XFILEHEX_ENTRY()
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
XFILEHEX_ENTRY::~XFILEHEX_ENTRY()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE XFILEHEX_ENTRY::GetSizeData()
* @brief      GetSizeData
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XBYTE :
*
*---------------------------------------------------------------------------------------------------------------------*/
XBYTE XFILEHEX_ENTRY::GetSizeData()
{
  return sizedata;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILEHEX_ENTRY::SetSizeData(XBYTE size)
* @brief      SetSizeData
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  size :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XFILEHEX_ENTRY::SetSizeData(XBYTE sizedata)
{
  this->sizedata = sizedata;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWORD XFILEHEX_ENTRY::GetAddress()
* @brief      GetAddress
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XWORD XFILEHEX_ENTRY::GetAddress()
{
  return address;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILEHEX_ENTRY::SetAddress(XWORD address)
* @brief      SetAddress
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  address :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XFILEHEX_ENTRY::SetAddress(XWORD address)
{
  this->address = address;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEHEX_ENTRYTYPE XFILEHEX_ENTRY::GetEntryType()
* @brief      GetEntryType
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XFILEHEX_ENTRYTYPE :
*
*---------------------------------------------------------------------------------------------------------------------*/
XFILEHEX_ENTRYTYPE XFILEHEX_ENTRY::GetEntryType()
{
  return (XFILEHEX_ENTRYTYPE)entrytype;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILEHEX_ENTRY::SetEntryType(XFILEHEX_ENTRYTYPE entrytype)
* @brief      SetEntryType
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  entrytype :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XFILEHEX_ENTRY::SetEntryType(XFILEHEX_ENTRYTYPE entrytype)
{
  this->entrytype = entrytype;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBUFFER* XFILEHEX_ENTRY::GetData()
* @brief      GetData
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XBUFFER* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XBUFFER* XFILEHEX_ENTRY::GetData()
{
  return &data;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE XFILEHEX_ENTRY::CalculeCRC(XBUFFER data)
* @brief      CalculeCRC
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
XBYTE XFILEHEX_ENTRY::CalculeCRC(XBUFFER& data)
{
  XDWORD CRC = 0;

  for(XDWORD c=0; c<data.GetSize(); c++)
    {
      CRC += data.Get()[c];
    }

  XBYTE _CRC = CRC;

  return (XBYTE)~_CRC + 1;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILEHEX_ENTRY::Clean()
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
void XFILEHEX_ENTRY::Clean()
{
  sizedata  = 0;
  address   = 0;
  entrytype = XFILEHEX_ENTRYTYPE_NODEFINED;

  data.Empty();
}



/*--------------------------------------------------------------------------------------------------------------------*/
/*  XFILEHEX                                                                                                          */
/*--------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEHEX::XFILEHEX()
* @brief      Constructor
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XFILEHEX::XFILEHEX(): XFILETXT()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEHEX::~XFILEHEX()
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
XFILEHEX::~XFILEHEX()
{
  Entry_DeleteAll();

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEHEX::DecodeAllLines()
* @brief      DecodeAllLines
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEHEX::DecodeAllLines()
{
  if(!IsOpen())      return false;
  if(!ReadAllFile()) return false;

  bool status = false;

  for(int c=0; c<GetNLines(); c++)
    {
      XSTRING* line = GetLine(c);
      if(line)
        {
          if(!line->IsEmpty())
            {
              status = Entry_Add(line);
              if(!status)
                {
                  break;
                }
            }
        }
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEHEX::EncodeAllLines()
* @brief      EncodeAllLines
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEHEX::EncodeAllLines()
{
  if(!IsOpen())      return false;

  DeleteAllLines();

  for(XDWORD c=0; c<entrys.GetSize(); c++)
    {
      XFILEHEX_ENTRY* entry = entrys.Get(c);
      if(entry)
        {
          XSTRING line;

           if(!EncodeLine(entry, line)) return false;

           AddLine(line);
        }
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEHEX::DecodeLine(XSTRING* line, XFILEHEX_ENTRY& entry)
* @brief      DecodeLine
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  line :
* @param[in]  entry :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEHEX::DecodeLine(XSTRING* line, XFILEHEX_ENTRY& entry)
{
  if(!line)            return false;
  if(line->IsEmpty())  return false;

  if(line->Get()[0] !=__C(':')) return false;

  int     sizedata;
  int     address;
  int     entrytype;
  XSTRING string;
  int     CRC;
  XBUFFER dataCRC;

  line->ToUpperCase();

  line->Copy( 1, 3, string);
  string.UnFormat(__L("%02X"), &sizedata);
  entry.SetSizeData((XBYTE)sizedata);

  line->Copy( 3, 7, string);
  string.UnFormat(__L("%04X"), &address);
  entry.SetAddress((XWORD)address);

  line->Copy( 7, 9, string);
  string.UnFormat(__L("%02X"), &entrytype);
  entry.SetEntryType((XFILEHEX_ENTRYTYPE)entrytype);

  if(sizedata)
    {
      line->Copy(9, line->GetSize()-2, string);
      string.ConvertHexStringToBuffer((*entry.GetData()));
    }

  line->Copy(line->GetSize()-2, string);
  string.UnFormat(__L("%02X"), &CRC);

  line->Copy(1, line->GetSize()-2, string);
  string.ConvertHexStringToBuffer(dataCRC);

  XBYTE calculeCRC = entry.CalculeCRC(dataCRC);

  if((XBYTE)CRC != calculeCRC)  return false;


  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEHEX::EncodeLine(XFILEHEX_ENTRY* entry, XSTRING& line)
* @brief      EncodeLine
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  entry :
* @param[in]  line :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEHEX::EncodeLine(XFILEHEX_ENTRY* entry, XSTRING& line)
{
  if(!entry)  return false;

  XSTRING string;

  string.Format(__L("%02X"), entry->GetSizeData());                    line.Add(string);
  string.Format(__L("%04X"), entry->GetAddress());                     line.Add(string);
  string.Format(__L("%02X"), (XWORD)entry->GetEntryType());            line.Add(string);

  if(entry->GetSizeData())
    {
      string.ConvertHexStringFromBuffer((*entry->GetData()), true);
      line.Add(string);
    }

  XBUFFER dataCRC;

  line.ConvertHexStringToBuffer(dataCRC);
  string.Format(__L("%02X"), entry->CalculeCRC(dataCRC));  line.Add(string);

  line.Insert(__L(":"), 0);
  line.ToUpperCase();

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XFILEHEX::GetNEntrys()
* @brief      GetNEntrys
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD XFILEHEX::GetNEntrys()
{
  return entrys.GetSize();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEHEX::Entry_Add(XSTRING* line)
* @brief      Entry_Add
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  line :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEHEX::Entry_Add(XSTRING* line)
{
  if(!line)             return false;
  if(line->IsEmpty())   return false;

  XFILEHEX_ENTRY* entry = new XFILEHEX_ENTRY();
  if(!entry) return false;

  if(!DecodeLine(line, (*entry)))
    {
      delete entry;
      return false;
    }

  entrys.Add(entry);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEHEX_ENTRY* XFILEHEX::Entry_Get(XWORD address, XFILEHEX_ENTRYTYPE type)
* @brief      Entry_Get
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  address :
* @param[in]  type :
*
* @return     XFILEHEX_ENTRY* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XFILEHEX_ENTRY* XFILEHEX::Entry_Get(XWORD address, XFILEHEX_ENTRYTYPE type)
{
  if(entrys.IsEmpty()) return NULL;

  for(XDWORD c=0; c<entrys.GetSize(); c++)
    {
      XFILEHEX_ENTRY* entry = entrys.Get(c);
      if(entry)
        {
          if((entry->GetAddress() == address) && (entry->GetEntryType() == type))
            {
              return entry;
            }
        }
    }

  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEHEX_ENTRY* XFILEHEX::Entry_Get(int index)
* @brief      Entry_Get
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  index :
*
* @return     XFILEHEX_ENTRY* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XFILEHEX_ENTRY* XFILEHEX::Entry_Get(int index)
{
  return entrys.Get(index);
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEHEX::Entry_Delete(XWORD address, XFILEHEX_ENTRYTYPE type)
* @brief      Entry_Delete
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  address :
* @param[in]  type :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEHEX::Entry_Delete(XWORD address, XFILEHEX_ENTRYTYPE type)
{
  XFILEHEX_ENTRY* entry = Entry_Get(address, type);
  if(!entry) return false;

  if(!entrys.Delete(entry)) return false;

  delete entry;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEHEX::Entry_Delete(int index)
* @brief      Entry_Delete
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  index :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEHEX::Entry_Delete(int index)
{
  XFILEHEX_ENTRY* entry = Entry_Get(index);
  if(!entry) return false;

  if(!entrys.Delete(entry)) return false;

  delete entry;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEHEX::Entry_DeleteAll()
* @brief      Entry_DeleteAll
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEHEX::Entry_DeleteAll()
{
  if(entrys.IsEmpty())  return false;

  entrys.DeleteContents();
  entrys.DeleteAll();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILEHEX::Clean()
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
void XFILEHEX::Clean()
{

}



