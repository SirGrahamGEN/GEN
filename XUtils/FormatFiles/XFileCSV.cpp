/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XFileCSV.cpp
* 
* @class      XFILECSV
* @brief      eXtended Utils CSV file class (Comma Separate Value file)
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

#include "XFileCSV.h"

#include <stdio.h>
#include <string.h>

#include "XFactory.h"
#include "XPath.h"

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


#pragma region CLASS_XFILECSV_RECORD


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILECSV_RECORD::XFILECSV_RECORD()
* @brief      Constructor of class
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILECSV_RECORD::XFILECSV_RECORD()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILECSV_RECORD::~XFILECSV_RECORD()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILECSV_RECORD::~XFILECSV_RECORD()
{
  DeleteAllElements();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XFILECSV_RECORD::GetNElements()
* @brief      Get N elements
* @ingroup    XUTILS
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XFILECSV_RECORD::GetNElements()
{
  return elements.GetSize();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECSV_RECORD::GetElement(int index, XSTRING& element)
* @brief      Get element
* @ingroup    XUTILS
*
* @param[in]  index :
* @param[in]  element :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECSV_RECORD::GetElement(int index, XSTRING& element)
{
  XSTRING* string = (XSTRING*)elements.Get(index);
  if(!string) return false;

  //if(string->IsEmpty()) return false;

  element = (*string);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XCHAR* XFILECSV_RECORD::GetElement(int index)
* @brief      Get element
* @ingroup    XUTILS
*
* @param[in]  index :
*
* @return     XCHAR* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR* XFILECSV_RECORD::GetElement(int index)
{
  XSTRING* string = (XSTRING*)elements.Get(index);
  if(!string) return NULL;

  //if(string->IsEmpty()) return NULL;

  return string->Get();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECSV_RECORD::AddElement(XSTRING& element)
* @brief      Add element
* @ingroup    XUTILS
*
* @param[in]  element :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECSV_RECORD::AddElement(XSTRING& element)
{
  //if(element.IsEmpty()) return false;

  XSTRING* string = new XSTRING();
  if(!string) return false;

  (*string) = element;

  elements.Add(string);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECSV_RECORD::AddElement(XCHAR* element)
* @brief      Add element
* @ingroup    XUTILS
*
* @param[in]  element :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECSV_RECORD::AddElement(XCHAR* element)
{
  if(!element)    return false;
  //if(!element[0]) return false;

  XSTRING* string = new XSTRING();
  if(!string) return false;

  (*string) = element;

  elements.Add(string);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECSV_RECORD::Copy(XFILECSV_RECORD* header)
* @brief      Copy
* @ingroup    XUTILS
*
* @param[in]  header :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECSV_RECORD::Copy(XFILECSV_RECORD* header)
{
  if(!header)                return false;
  if(!header->GetNElements()) return false;

  for(int c=0;c<header->GetNElements();c++)
    {
      XSTRING* string = new XSTRING();
      if(string)
        {
          XCHAR* string2 =  header->GetElement(c);
          (*string) = string2;
        }
       else
        {
          DeleteAllElements();
          return false;
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECSV_RECORD::DeleteElement(int index)
* @brief      Delete element
* @ingroup    XUTILS
*
* @param[in]  index :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECSV_RECORD::DeleteElement(int index)
{
  XSTRING* string = (XSTRING*)elements.Get(index);
  if(!string) return false;

  elements.Delete(string);

  delete string;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECSV_RECORD::DeleteAllElements()
* @brief      Delete all elements
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECSV_RECORD::DeleteAllElements()
{
  if(elements.IsEmpty())  return false;

  elements.DeleteContents();

  elements.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILECSV_RECORD::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFILECSV_RECORD::Clean()
{

}


#pragma endregion


#pragma region CLASS_XFILECSV


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILECSV::XFILECSV()
* @brief      Constructor of class
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILECSV::XFILECSV(): XFILETXT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILECSV::XFILECSV(XPATH& xpath)
* @brief      Constructor of class
* @ingroup    XUTILS
*
* @param[in]  xpath :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILECSV::XFILECSV(XPATH& xpath) : XFILETXT()
{
  Clean();

  Open(xpath, true);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILECSV::XFILECSV(XFILE* file)
* @brief      Constructor of class
* @ingroup    XUTILS
*
* @param[in]  file :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILECSV::XFILECSV(XFILE* file) : XFILETXT()
{
  Clean();

  this->file = file;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILECSV::~XFILECSV()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILECSV::~XFILECSV()
{
  DeleteAllRecords();

  Close();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECSV::Open(XPATH& xpath, bool readonly)
* @brief      Open
* @ingroup    XUTILS
*
* @param[in]  xpath : 
* @param[in]  readonly : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECSV::Open(XPATH& xpath, bool readonly)
{
  if(!XFILETXT::Open(xpath, readonly)) return false;

  Serialization(true, HaveHeader());

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECSV::Close()
* @brief      Close
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECSV::Close()
{
  bool status[2] = { false , false };

  status[0] = Serialization(false,HaveHeader());
  status[1] = XFILETXT::Close();

  if(status[0] && status[1]) return true;

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XCHAR XFILECSV::GetSeparator()
* @brief      Get separator
* @ingroup    XUTILS
*
* @return     XCHAR :
*
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR XFILECSV::GetSeparator()
{
  return separator;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECSV::SetSeparator(XCHAR separator)
* @brief      Set separator
* @ingroup    XUTILS
*
* @param[in]  separator :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECSV::SetSeparator(XCHAR separator)
{
  if((separator!=__C(','))&&(separator!=__C(';'))) return false;

  this->separator = separator;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECSV::HaveHeader()
* @brief      Have header
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECSV::HaveHeader()
{
  if(header.GetNElements()) return true;

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILECSV_RECORD* XFILECSV::GetHeader()
* @brief      Get header
* @ingroup    XUTILS
*
* @return     XFILECSV_RECORD* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILECSV_RECORD* XFILECSV::GetHeader()
{
  return &header;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECSV::SetHeader(XFILECSV_RECORD* header)
* @brief      Set header
* @ingroup    XUTILS
*
* @param[in]  header :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECSV::SetHeader(XFILECSV_RECORD* header)
{
  if(!header) return false;

  return this->header.Copy(header);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XFILECSV::GetNRecords()
* @brief      Get N records
* @ingroup    XUTILS
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XFILECSV::GetNRecords()
{
  return records.GetSize();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILECSV_RECORD* XFILECSV::ReadRecord(XDWORD nrecord)
* @brief      Read record
* @ingroup    XUTILS
*
* @param[in]  nrecord :
*
* @return     XFILECSV_RECORD* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILECSV_RECORD* XFILECSV::ReadRecord(XDWORD nrecord)
{
  if(records.IsEmpty())           return NULL;
  if(nrecord>=records.GetSize())  return NULL;

  XFILECSV_RECORD* record = (XFILECSV_RECORD*)records.Get(nrecord);
  if(!record) return NULL;

  return record;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECSV::WriteRecord(XDWORD nrecord,XFILECSV_RECORD* record)
* @brief      Write record
* @ingroup    XUTILS
*
* @param[in]  nrecord :
* @param[in]  record :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECSV::WriteRecord(XDWORD nrecord,XFILECSV_RECORD* record)
{
  if(records.IsEmpty())           return false;
  if(nrecord>=records.GetSize())  return false;

  XFILECSV_RECORD* _record = (XFILECSV_RECORD*)records.Get(nrecord);
  if(!_record) return false;

  delete _record;

  records.Set(nrecord,record);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECSV::AddRecord(XFILECSV_RECORD* record)
* @brief      Add record
* @ingroup    XUTILS
*
* @param[in]  record :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECSV::AddRecord(XFILECSV_RECORD* record)
{
  if(!record) return false;

  records.Add(record);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECSV::DeleteRecord(XDWORD nrecord)
* @brief      Delete record
* @ingroup    XUTILS
*
* @param[in]  nrecord :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECSV::DeleteRecord(XDWORD nrecord)
{
  XFILECSV_RECORD* record = (XFILECSV_RECORD*)records.Get(nrecord);
  if(!record) return false;

  records.Delete(record);

  delete record;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECSV::DeleteAllRecords()
* @brief      Delete all records
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECSV::DeleteAllRecords()
{
  if(records.IsEmpty())  return false;

  records.DeleteContents();
  records.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECSV::Serialization(bool read,bool haveheader)
* @brief      Serialization
* @ingroup    XUTILS
*
* @param[in]  read :
* @param[in]  haveheader :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECSV::Serialization(bool read, bool haveheader)
{
  file->SetPosition(XFILE_SEEKINI);

  DeleteAllLines();

  if(read)
    {
      int c = 0;

      DeleteAllRecords();

      ReadAllFile();

      if(haveheader)
        {
          XSTRING line;

          if(lines.GetSize()>0)
          if(GetLine(0))
            {
              line = GetLine(0)->Get();
              if(!line.IsEmpty())
                {
                  if(CreateRecordOfLine(line,&header)) c++;
                }
            }
        }

      for(;c<GetNLines();c++)
        {
          XFILECSV_RECORD* record;
          XSTRING      line;

          if(GetLine(c))
            {
              line = GetLine(c)->Get();
              if(!line.IsEmpty())
                {
                  record = new XFILECSV_RECORD();
                  if(record)
                    {
                      CreateRecordOfLine(line,record);
                      AddRecord(record);
                    }
                }
            }
        }
    }
   else
    {
      if(!records.IsEmpty())
        {
          XSTRING line;

          if(haveheader)
            {
              if(CreateLineOfRecord(&header,line)) AddLine(line);
            }

          for(int c=0;c<(int)records.GetSize();c++)
            {
              XFILECSV_RECORD* record = (XFILECSV_RECORD*)records.Get(c);
              if(record)
                {
                  if(CreateLineOfRecord(record,line)) AddLine(line);
                }
            }

          WriteAllFile();

          XQWORD pos;
          file->GetPosition(pos);

          if(pos) file->SetSize(pos);
        }
    }

  DeleteAllLines();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECSV::CreateRecordOfLine(XSTRING& line,XFILECSV_RECORD* record)
* @brief      Create record of line
* @ingroup    XUTILS
*
* @param[in]  line :
* @param[in]  record :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECSV::CreateRecordOfLine(XSTRING& line, XFILECSV_RECORD* record)
{
  if(line.IsEmpty()) return false;

  int start = 0;
  int end   = 0;

  do{ end = line.Find(__L(";"),true,start);
      if(end == XSTRING_NOTFOUND)
        {
          end = line.Find(__L(","),true,start);
          if(end != XSTRING_NOTFOUND) SetSeparator(__C(','));

        } else SetSeparator(__C(';'));

      XSTRING element;

      if(end != XSTRING_NOTFOUND)
        {
          line.Copy(start,end,element);

          record->AddElement(element);

          start = end+1;
        }
       else
        {
          line.Copy(start,element);
          record->AddElement(element);

          break;
        }

    } while(1);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECSV::CreateLineOfRecord(XFILECSV_RECORD* record,XSTRING& line)
* @brief      Create line of record
* @ingroup    XUTILS
*
* @param[in]  record :
* @param[in]  line :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECSV::CreateLineOfRecord(XFILECSV_RECORD* record,XSTRING& line)
{
  line.Empty();

  XCHAR separatorstring[2] = { 0, 0 };
  separatorstring[0]= separator;

  for(int c=0;c<record->GetNElements();c++)
    {
      XSTRING element;

      record->GetElement(c,element);
      line += element;
      if(c<(record->GetNElements()-1)) line += separatorstring;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILECSV::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFILECSV::Clean()
{
  separator = __C(';');
}


#pragma endregion


#pragma endregion

