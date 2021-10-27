/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XFileINI.cpp
*
* @class      XFILEINI
* @brief      eXtended INI (Windows INItialization file) file class
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

#include "XPath.h"

#include "XFileINI.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEINIKEY::XFILEINIKEY()
* @brief      Constructor
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XFILEINIKEY::XFILEINIKEY()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEINIKEY::~XFILEINIKEY()
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
XFILEINIKEY::~XFILEINIKEY()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* XFILEINIKEY::GetKey()
* @brief      GetKey
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* XFILEINIKEY::GetKey()
{
  return &key;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINIKEY::SetKey(XSTRING& key)
* @brief      SetKey
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  key :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINIKEY::SetKey(XSTRING& key)
{
  this->key = key;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* XFILEINIKEY::GetValue()
* @brief      GetValue
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* XFILEINIKEY::GetValue()
{
  return &value;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINIKEY::SetValue(XSTRING& value)
* @brief      SetValue
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINIKEY::SetValue(XSTRING& value)
{
  this->value = value;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILEINIKEY::Clean()
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
void XFILEINIKEY::Clean()
{

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEINISECTION::XFILEINISECTION()
* @brief      Constructor
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XFILEINISECTION::XFILEINISECTION()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEINISECTION::~XFILEINISECTION()
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
XFILEINISECTION::~XFILEINISECTION()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* XFILEINISECTION::GetName()
* @brief      GetName
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* XFILEINISECTION::GetName()
{
  return &section;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINISECTION::SetName(XSTRING& section)
* @brief      SetName
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  section :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINISECTION::SetName(XSTRING& section)
{
  this->section = section;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEINIKEY* XFILEINISECTION::FindKey(XSTRING& key)
* @brief      FindKey
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  key :
*
* @return     XFILEINIKEY* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XFILEINIKEY* XFILEINISECTION::FindKey(XSTRING& key)
{
  if(keys.IsEmpty()) return NULL;

  for(XDWORD c=0;c<keys.GetSize();c++)
    {
      XFILEINIKEY* okey = (XFILEINIKEY*)keys.Get(c);
      if(okey)
        {
          if(okey->GetKey())
            {
              if(!okey->GetKey()->Compare(key, true)) return okey;
            }
        }
    }

  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINISECTION::GetKey(XSTRING& key,XSTRING& value)
* @brief      GetKey
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  key :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINISECTION::GetKey(XSTRING& key,XSTRING& value)
{
  XFILEINIKEY* okey=FindKey(key);

  if(!okey) return false;

  if(okey->GetValue()) value = (*okey->GetValue()); else return false;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINISECTION::SetKey(XSTRING& key,XSTRING& value)
* @brief      SetKey
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  key :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINISECTION::SetKey(XSTRING& key,XSTRING& value)
{
  XFILEINIKEY* okey  = FindKey(key);
  bool         isnew = false;

  if(!okey) isnew=true;

  if(isnew)
    {
      okey = new XFILEINIKEY();
      if(!okey) return false;
    }

  okey->SetKey(key);
  okey->SetValue(value);

  if(isnew) keys.Add(okey);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINISECTION::DeleteKey(XSTRING& key)
* @brief      DeleteKey
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  key :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINISECTION::DeleteKey(XSTRING& key)
{
  XFILEINIKEY* okey  = FindKey(key);
  if(!okey) return false;

  keys.Delete(okey);
  delete okey;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINISECTION::GetNextKey(XSTRING& key,XSTRING& value)
* @brief      GetNextKey
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  key :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINISECTION::GetNextKey(XSTRING& key,XSTRING& value)
{
  if(selectkey>=keys.GetSize()) return false;

  XFILEINIKEY* skey = (XFILEINIKEY*)keys.Get(selectkey);
  if(!skey) return false;

  if(skey->GetKey())    key   = (*skey->GetKey());
  if( skey->GetValue()) value = (* skey->GetValue());

  selectkey++;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINISECTION::ResetSelectionKey()
* @brief      ResetSelectionKey
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINISECTION::ResetSelectionKey()
{
  selectkey = 0;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILEINISECTION::Clean()
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
void XFILEINISECTION::Clean()
{
  section.Empty();

  ResetSelectionKey();

  if(keys.IsEmpty()) return;

  keys.DeleteContents();
  keys.DeleteAll();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEINI::XFILEINI()
* @brief      Constructor
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XFILEINI::XFILEINI(): XFILETXT()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEINI::XFILEINI(XPATH& xpath)
* @brief      Constructor
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  XPATH& :
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XFILEINI::XFILEINI(XPATH& xpath): XFILETXT()
{
  Clean();

  Open(xpath);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEINI::XFILEINI(XFILE* file)
* @brief      Constructor
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  XFILE* :
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XFILEINI::XFILEINI(XFILE* file): XFILETXT()
{
  Clean();

  this->file = file;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEINI::~XFILEINI()
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
XFILEINI::~XFILEINI()
{
  Close();

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINI::Open(XPATH& xpath,bool readonly)
* @brief      Open
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  xpath :
* @param[in]  readonly :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINI::Open(XPATH& xpath,bool readonly)
{
  if(!XFILETXT::Open(xpath,readonly)) return false;

  Serialization(true);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINI::Close()
* @brief      Close
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINI::Close()
{
  bool status[2] = { false , false };

  status[0] = Serialization(false);
  status[1] = XFILETXT::Close();

  if(status[0] && status[1]) return true;

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINI::SelectSection(XSTRING& section)
* @brief      SelectSection
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  section :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINI::SelectSection(XSTRING& section)
{
  if(sections.IsEmpty()) return false;

  for(XDWORD c=0;c<sections.GetSize();c++)
    {
      XFILEINISECTION* osection=(XFILEINISECTION*)sections.Get(c);
      if(osection)
        {
          if(osection->GetName())
            {
              if(!osection->GetName()->Compare(section, true))
                {
                  selectsection = c;
                  osection->ResetSelectionKey();

                  return true;
                }
            }
        }
    }

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINI::SelectSection(XCHAR* section)
* @brief      SelectSection
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  section :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINI::SelectSection(XCHAR* section)
{
  XSTRING _section(section);

  return SelectSection(_section);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINI::CreateSection(XSTRING& section)
* @brief      CreateSection
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  section :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINI::CreateSection(XSTRING& section)
{
  if(SelectSection(section)) return false;

  XFILEINISECTION* osection;

  osection = new XFILEINISECTION();
  if(!osection) return false;

  if(!osection->SetName(section)) return false;

  sections.Add(osection);
  selectsection = sections.GetSize()-1;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINI::CreateSection(XCHAR* section)
* @brief      CreateSection
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  section :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINI::CreateSection(XCHAR* section)
{
  XSTRING _section(section);

  return CreateSection(_section);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINI::DeleteSection(XSTRING& section)
* @brief      DeleteSection
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  section :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINI::DeleteSection(XSTRING& section)
{
  if(sections.IsEmpty()) return false;

  for(XDWORD c=0;c<sections.GetSize();c++)
    {
      XFILEINISECTION* osection=(XFILEINISECTION*)sections.Get(c);

      if(osection)
        {
          if(osection->GetName())
            {
              if(!osection->GetName()->Compare(section, true))
                {
                  sections.Delete(osection);

                  osection->Clean();
                  delete osection;

                  return true;
                }
            }
        }
    }

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINI::DeleteSection(XCHAR* section)
* @brief      DeleteSection
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  section :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINI::DeleteSection(XCHAR* section)
{
  XSTRING _section(section);

  return DeleteSection(_section);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINI::DeleteKey(XSTRING& section,XSTRING& key)
* @brief      DeleteKey
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  section :
* @param[in]  key :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINI::DeleteKey(XSTRING& section,XSTRING& key)
{
  if(!SelectSection(section)) return false;

  XFILEINISECTION* ssection = (XFILEINISECTION*)sections.Get(selectsection);
  if(!ssection) return false;

  return ssection->DeleteKey(key);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINI::DeleteKey(XCHAR* section,XSTRING& key)
* @brief      DeleteKey
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  section :
* @param[in]  key :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINI::DeleteKey(XCHAR* section,XSTRING& key)
{
  XSTRING _section(section);

  return DeleteKey(_section,key);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINI::DeleteKey(XSTRING& section,XCHAR* key)
* @brief      DeleteKey
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  section :
* @param[in]  key :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINI::DeleteKey(XSTRING& section,XCHAR* key)
{
  XSTRING _key;

  _key = key;

  return DeleteKey(section,_key);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINI::DeleteKey(XCHAR* section,XCHAR* key)
* @brief      DeleteKey
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  section :
* @param[in]  key :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINI::DeleteKey(XCHAR* section,XCHAR* key)
{
  XSTRING _section(section);
  XSTRING _key(key);

  return DeleteKey(_section,_key);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINI::ReadValue(XSTRING& section,XSTRING& key,XSTRING& value)
* @brief      ReadValue
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  section :
* @param[in]  key :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINI::ReadValue(XSTRING& section,XSTRING& key,XSTRING& value)
{
  value.Empty();

  if(!SelectSection(section)) return false;

  XFILEINISECTION* ssection = (XFILEINISECTION*)sections.Get(selectsection);
  if(!ssection) return false;

  XFILEINIKEY* okey=ssection->FindKey(key);
  if(!okey) return false;

  if(okey->GetValue()) value = (*okey->GetValue());

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINI::ReadValue(XCHAR* section,XSTRING& key,XSTRING& value)
* @brief      ReadValue
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  section :
* @param[in]  key :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINI::ReadValue(XCHAR* section,XSTRING& key,XSTRING& value)
{
  XSTRING _section(section);

  return ReadValue(_section,key,value);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINI::ReadValue(XSTRING& section,XCHAR* key,XSTRING& value)
* @brief      ReadValue
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  section :
* @param[in]  key :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINI::ReadValue(XSTRING& section,XCHAR* key,XSTRING& value)
{
  XSTRING _key(key);

  return ReadValue(section,_key,value);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINI::ReadValue(XCHAR* section,XCHAR* key,XSTRING& value)
* @brief      ReadValue
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  section :
* @param[in]  key :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINI::ReadValue(XCHAR* section,XCHAR* key,XSTRING& value)
{
  XSTRING _section(section);
  XSTRING _key(key);

  return ReadValue(_section,_key,value);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINI::ReadValue(XSTRING& key,XSTRING& value)
* @brief      ReadValue
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  key :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINI::ReadValue(XSTRING& key,XSTRING& value)
{
  value.Empty();

  if(sections.IsEmpty()) return false;

  selectsection=0;

  XFILEINISECTION* ssection = (XFILEINISECTION*)sections.Get(selectsection);
  if(!ssection)            return false;
  if(!ssection->GetName()) return false;

  return ReadValue((*ssection->GetName()),key,value);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINI::ReadValue(XCHAR* key,XSTRING& value)
* @brief      ReadValue
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  key :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINI::ReadValue(XCHAR* key,XSTRING& value)
{
  XSTRING _key(key);

  return ReadValue(_key,value);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINI::WriteValue(XSTRING& section,XSTRING& key,XSTRING& value)
* @brief      WriteValue
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  section :
* @param[in]  key :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINI::WriteValue(XSTRING& section,XSTRING& key,XSTRING& value)
{
  if(!SelectSection(section))
    {
      if(!CreateSection(section)) return false;
      if(!SelectSection(section)) return false;
    }

  XFILEINISECTION* ssection = (XFILEINISECTION*)sections.Get(selectsection);
  if(!ssection) return false;

  return ssection->SetKey(key,value);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINI::WriteValue(XCHAR* section,XSTRING& key,XSTRING& value)
* @brief      WriteValue
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  section :
* @param[in]  key :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINI::WriteValue(XCHAR* section,XSTRING& key,XSTRING& value)
{
  XSTRING _section(section);

  return WriteValue(_section,key,value);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINI::WriteValue(XSTRING& section,XCHAR* key,XSTRING& value)
* @brief      WriteValue
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  section :
* @param[in]  key :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINI::WriteValue(XSTRING& section,XCHAR* key,XSTRING& value)
{
  XSTRING _key(key);

  return WriteValue(section,_key,value);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINI::WriteValue(XCHAR* section,XCHAR* key,XSTRING& value)
* @brief      WriteValue
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  section :
* @param[in]  key :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINI::WriteValue(XCHAR* section,XCHAR* key,XSTRING& value)
{
  XSTRING _section(section);
  XSTRING _key(key);

  return WriteValue(_section,_key,value);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINI::WriteValue(XSTRING& key,XSTRING& value)
* @brief      WriteValue
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  key :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINI::WriteValue(XSTRING& key,XSTRING& value)
{
  if(sections.IsEmpty()) return false;

  selectsection=0;

  XFILEINISECTION* ssection = (XFILEINISECTION*)sections.Get(selectsection);
  if(!ssection)            return false;
  if(!ssection->GetName()) return false;

  return WriteValue((*ssection->GetName()),key,value);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINI::WriteValue(XCHAR* key,XSTRING& value)
* @brief      WriteValue
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  key :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINI::WriteValue(XCHAR* key,XSTRING& value)
{
  XSTRING _key(key);

  return ReadValue(_key,value);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINI::GetNextKey(XSTRING& key,XSTRING& value)
* @brief      GetNextKey
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  key :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINI::GetNextKey(XSTRING& key,XSTRING& value)
{
  if(sections.IsEmpty()) return false;

  selectsection=0;

  XFILEINISECTION* ssection = (XFILEINISECTION*)sections.Get(selectsection);
  if(!ssection) return false;

  return ssection->GetNextKey(key,value);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINI::ReadKeyMap(XSTRING& section,XFILEINIKEYMAP* keymap,int nkeymap)
* @brief      ReadKeyMap
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  section :
* @param[in]  keymap :
* @param[in]  nkeymap :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINI::ReadKeyMap(XSTRING& section,XFILEINIKEYMAP* keymap,int nkeymap)
{
  if(!nkeymap)                return false;
  if(!SelectSection(section)) return false;

  XSTRING value;

  for(int c=0;c<nkeymap;c++)
    {
      if(ReadValue(keymap[c].key,value)) keymap[c].value = value;
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINI::ReadKeyMap(XCHAR* section,XFILEINIKEYMAP* keymap,int nkeymap)
* @brief      ReadKeyMap
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  section :
* @param[in]  keymap :
* @param[in]  nkeymap :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINI::ReadKeyMap(XCHAR* section,XFILEINIKEYMAP* keymap,int nkeymap)
{
  XSTRING _section(section);

  return ReadKeyMap(_section,keymap,nkeymap);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINI::ConvertFromLines()
* @brief      ConvertFromLines
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINI::ConvertFromLines()
{
  XSTRING section;
  XSTRING actualsection;

  DeleteAllSections();

  for(int c=0;c<GetNLines();c++)
    {
      XSTRING* line = GetLine(c);

      if(line)
        {
          if(LineIsSection((*line),section))
            {
              actualsection = section;
              CreateSection(actualsection);
            }
           else
            {
              XSTRING key;
              XSTRING value;

              if(LineIsKey((*line),key,value))
                {
                  WriteValue(actualsection,key,value);
                }
            }
        }
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINI::ConvertToLines()
* @brief      ConvertToLines
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINI::ConvertToLines()
{
  if(sections.IsEmpty()) return false;

  for(XDWORD c=0;c<sections.GetSize();c++)
    {
      XFILEINISECTION* section = (XFILEINISECTION*)sections.Get(c);

      if(section)
        {
          XSTRING line(__L(" "));
          XSTRING key;
          XSTRING value;

          AddLine(line.Get());

          line.Format(__L("[%s]"),section->GetName()->Get());
          AddLine(line.Get());

          section->ResetSelectionKey();

          while(section->GetNextKey(key,value))
            {
              line.Format(__L("%s=%s"),key.Get(),value.Get());
              AddLine(line.Get());
            }
        }
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINI::Serialization(bool read)
* @brief      Serialization
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  read :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINI::Serialization(bool read)
{
  bool status;

  file->SetPosition(XFILE_SEEKINI);

  DeleteAllLines();

  if(read)
    {
      ReadAllFile();
      status = ConvertFromLines();
    }
   else
    {
      status = ConvertToLines();
      if(status)
        {
          WriteAllFile();

          XQWORD pos = 0;
          file->GetPosition(pos);

          if(pos) file->SetSize(pos);
        }
    }

  DeleteAllLines();

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINI::DeleteAllSections()
* @brief      DeleteAllSections
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINI::DeleteAllSections()
{
  selectsection = 0;

  if(sections.IsEmpty()) return false;

  sections.DeleteContents();
  sections.DeleteAll();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILEINI::Clean()
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
void XFILEINI::Clean()
{
  DeleteAllSections();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINI::LineIsSection(XSTRING& line,XSTRING& section)
* @brief      LineIsSection
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  line :
* @param[in]  section :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINI::LineIsSection(XSTRING& line,XSTRING& section)
{
  section.Empty();

  if(line.IsEmpty()) return false;

  line.Copy(__L("["),__L("]"),true,0,section);

  if(section.IsEmpty()) return false;

  section.ToUpperCase();
  section.DeleteCharacter(__C(' '),XSTRINGCONTEXT_ATFIRST);
  section.DeleteCharacter(__C(' '),XSTRINGCONTEXT_ATEND);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEINI::LineIsKey(XSTRING& line,XSTRING& key,XSTRING& value)
* @brief      LineIsKey
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  line :
* @param[in]  key :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILEINI::LineIsKey(XSTRING& line,XSTRING& key,XSTRING& value)
{
  key.Empty();
  value.Empty();

  if(line.IsEmpty()) return false;

  if((line.Find(__L("["),true)!=XSTRING_NOTFOUND) &&
     (line.Find(__L("]"),true)!=XSTRING_NOTFOUND))  return false;

  int indexvalue = line.Find(__L("="),true);
  if(indexvalue == XSTRING_NOTFOUND) return false;

  line.Copy(0,indexvalue,key);
  line.Copy(indexvalue+1,line.GetSize(),value);

  if(key.IsEmpty()) return false;

  //key.ToUpperCase();
  key.DeleteCharacter(__C(' '),XSTRINGCONTEXT_ATFIRST);
  key.DeleteCharacter(__C(' '),XSTRINGCONTEXT_ATEND);

  value.DeleteCharacter(__C(' '),XSTRINGCONTEXT_ATFIRST);
  value.DeleteCharacter(__C(' '),XSTRINGCONTEXT_ATEND);

  return true;
}

