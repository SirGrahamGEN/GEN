/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XFileCFG.cpp
*
* @class      XFILECFG
* @brief      eXtended CFG (Config) file class
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

#include <stdio.h>
#include <string.h>

#include "XPath.h"
#include "XFileINI.h"
#include "XVector.h"
#include "XVariant.h"

#include "XFileCFG.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#pragma region XFILECFGVALUE

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILECFGVALUE::XFILECFGVALUE()
* @brief      Constructor
* @ingroup    XUTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILECFGVALUE::XFILECFGVALUE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILECFGVALUE::~XFILECFGVALUE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILECFGVALUE::~XFILECFGVALUE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILECFG_VALUETYPE XFILECFGVALUE::GetType()
* @brief      Get Type
* @ingroup    XUTILS
*
* @return     XFILECFG_VALUETYPE : Type of value
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILECFG_VALUETYPE XFILECFGVALUE::GetType()
{
  return type;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECFGVALUE::SetType(XFILECFG_VALUETYPE type)
* @brief      Set Type
* @ingroup    XUTILS
*
* @param[in]  type : new type of value
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECFGVALUE::SetType(XFILECFG_VALUETYPE type)
{
  this->type = type;
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* XFILECFGVALUE::GetGroup()
* @brief      Get Group
* @ingroup    XUTILS
*
* @return     XSTRING* : group of value
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* XFILECFGVALUE::GetGroup()
{
  return &group;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* XFILECFGVALUE::GetID()
* @brief      Get ID
* @ingroup    XUTILS
*
* @return     XSTRING* : ID df vlaue
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* XFILECFGVALUE::GetID()
{
  return &ID;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void* XFILECFGVALUE::GetValue()
* @brief      Get Value
* @ingroup    XUTILS
*
* @return     void* : data of value
*
* --------------------------------------------------------------------------------------------------------------------*/
void* XFILECFGVALUE::GetValue()
{
  return value;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECFGVALUE::SetValue(void* value)
* @brief      Set Value
* @ingroup    XUTILS
*
* @param[in]  value : new data of value
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECFGVALUE::SetValue(void* value)
{
  this->value = value;
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILECFGVALUE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFILECFGVALUE::Clean()
{
  type = XFILECFG_VALUETYPE_UNKNOWN;
  value = NULL;
}

#pragma endregion 


#pragma region XFILECFG

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILECFG::XFILECFG(XCHAR* namefile)
* @brief      Constructor
* @ingroup    XUTILS
*
* @param[in]  XCHAR* : name file of config
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILECFG::XFILECFG(XCHAR* namefile)
{
  Clean();

  fileini = new XFILEINI();

  if(namefile) 
    {
      this->namefile = namefile;
      if(this->namefile.IsEmpty()) return;

      XPATH xpathroot;
      GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathroot);

      xpathfile.Add(xpathroot.Get());
      if(!xpathfile.IsEmpty()) xpathfile.Slash_Add();

      xpathfile.Add(this->namefile.Get());
      xpathfile.Add(XFILECFG_EXTENSIONFILE);
    }
 }


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILECFG::~XFILECFG()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILECFG::~XFILECFG()
{
  if(fileini) delete fileini;

  DeleteAllRemarks();

  DeleteAllValues();
  
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn          XPATH* XFILECFG::GetPathFile()
* @brief       GetPathFile
* @ingroup     XUTILS
* 
* @return      XPATH* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XPATH* XFILECFG::GetPathFile()
{
   return &xpathfile;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECFG::Ini()
* @brief      Ini xfile Config
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECFG::Ini()
{ 
  bool status[2];

  status[0] = Load();  
  status[1] = Save();

  return (status[0] && status[1]);  
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECFG::Load()
* @brief      Load xfile config
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECFG::Load()
{
  if(xpathfile.IsEmpty()) return false;

  return Load(xpathfile);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECFG::Load(XPATH& xpath)
* @brief      Load xfile config
* @ingroup    XUTILS
*
* @param[in]  xpath : path to file config
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECFG::Load(XPATH& xpath)
{
  bool status = false;

  if(values.IsEmpty()) return status;
    
  if(IniFile(xpath)) 
    {
      AjustRemarks();

      for(int c=0;c<(int)values.GetSize();c++)
        {
          XFILECFGVALUE* cfgvalue = (XFILECFGVALUE*)values.Get(c);
          if(cfgvalue)
            {
              XSTRING strvalue;

              if(fileini->ReadValue(cfgvalue->GetGroup()->Get(), cfgvalue->GetID()->Get() , strvalue))
                {
                  switch(cfgvalue->GetType())
                    {
                      case XFILECFG_VALUETYPE_UNKNOWN : break;

                      case XFILECFG_VALUETYPE_INT     : { int* value = (int*)cfgvalue->GetValue();
                                                          if(!value) return false;

                                                          (*value) = strvalue.ConvertToInt();
                                                        }
                                                        break;

                      case XFILECFG_VALUETYPE_MASK    : { XWORD* value = (XWORD*)cfgvalue->GetValue();
                                                          if(!value) return false;

                                                          strvalue.UnFormat(__L("%04X"), value);
                                                        }
                                                        break;

                      case XFILECFG_VALUETYPE_FLOAT   : { float* value = (float*)cfgvalue->GetValue();
                                                          if(!value) return false;

                                                          (*value) = strvalue.ConvertToFloat();
                                                        }
                                                        break;

                      case XFILECFG_VALUETYPE_STRING  : { XSTRING* value = (XSTRING*)cfgvalue->GetValue();
                                                          if(!value) return false;

                                                          (*value) = strvalue.Get();

                                                          value->DeleteCharacter(__C('\t'));
                                                          value->DeleteCharacter(__C('\n'));
                                                          value->DeleteCharacter(__C('\r'));

                                                          value->DeleteCharacter(__C(' '), XSTRINGCONTEXT_TO_END);
                                                        }
                                                        break;

                      case XFILECFG_VALUETYPE_BOOLEAN : { bool* value = (bool*)cfgvalue->GetValue();
                                                          if(!value) return false;

                                                          (*value) = strvalue.ConvertToBoolean();
                                                        }
                                                        break;
                    }
                }
            }
        }

      status = EndFile();
    } 

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECFG::Save()
* @brief      Save xfile config
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECFG::Save()
{
  if(xpathfile.IsEmpty()) return false;
  return Save(xpathfile);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECFG::Save(XPATH& xpath)
* @brief      Save file config
* @ingroup    XUTILS
*
* @param[in]  xpath : path to file config
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECFG::Save(XPATH& xpath)
{
  bool status = false;

  if(!values.IsEmpty())
    {
      if(IniFile(xpath))
        {
          AjustRemarks();    

          fileini->DeleteAllSections();

          for(int c=0;c<(int)values.GetSize();c++)
            {
              XSTRING strvalue;

              XFILECFGVALUE* cfgvalue = (XFILECFGVALUE*)values.Get(c);
              if(cfgvalue)
                {
                  switch(cfgvalue->GetType())
                    {
                      case XFILECFG_VALUETYPE_UNKNOWN : break;

                      case XFILECFG_VALUETYPE_INT     : { int* value = (int*)cfgvalue->GetValue();
                                                          if(!value) return false;

                                                          strvalue.Format(__L("%d"), (*value));
                                                        }
                                                        break;

                      case XFILECFG_VALUETYPE_MASK    : { XWORD* value = (XWORD*)cfgvalue->GetValue();
                                                          if(!value) return false;

                                                          strvalue.Format(__L("%04X"), (*value));
                                                        }
                                                        break;

                      case XFILECFG_VALUETYPE_FLOAT   : { float* value = (float*)cfgvalue->GetValue();
                                                          if(!value) return false;

                                                          strvalue.Format(__L("%f"), (*value));
                                                        }
                                                        break;

                      case XFILECFG_VALUETYPE_STRING  : { XSTRING* value = (XSTRING*)cfgvalue->GetValue();
                                                          if(!value) return false;

                                                          strvalue = value->Get();
                                                        }
                                                        break;

                      case XFILECFG_VALUETYPE_BOOLEAN : { bool* value = (bool*)cfgvalue->GetValue();
                                                          if(!value) return false;

                                                          strvalue = (*value)?__L("yes"):__L("no");
                                                        }
                                                        break;
                    }

                  status = fileini->WriteValue(cfgvalue->GetGroup()->Get(), cfgvalue->GetID()->Get() , strvalue);
                  if(!status) break;

                }
            }

          status = EndFile();
        }
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECFG::End()
* @brief      End file config
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECFG::End()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECFG::AddValue(XFILECFG_VALUETYPE type, XCHAR* group, XCHAR* ID, void* value)
* @brief      Add Value to file config
* @ingroup    XUTILS
*
* @param[in]  type : type of value
* @param[in]  group : group of value
* @param[in]  ID : ID of value
* @param[in]  value : data value
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECFG::AddValue(XFILECFG_VALUETYPE type, XCHAR* group, XCHAR* ID, void* value, XCHAR* remark_text, XDWORD remark_xpos)
{
  XFILECFGVALUE* cfgvalue = new XFILECFGVALUE();
  if(!cfgvalue) return false;

  cfgvalue->SetType(type);
  cfgvalue->GetGroup()->Set(group);
  cfgvalue->GetID()->Set(ID);
  cfgvalue->SetValue(value);

  if(values.Add(cfgvalue))
    {
      if(remark_text)
        {
          AddRemark(group, ID, remark_text, remark_xpos, 0);
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn          XVECTOR<XFILECFGVALUE*>* XFILECFG::GetValues()
* @brief       GetValues
* @ingroup     UTILS
* 
* @return      XVECTOR<XFILECFGVALUE*>* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<XFILECFGVALUE*>* XFILECFG::GetValues()
{
  return &values;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVARIANT* XFILECFG::GetValue(XCHAR* group, XCHAR* ID)
* @brief      GetValue
* @ingroup    XUTILS
* 
* @param[in]  group : 
* @param[in]  ID : 
* 
* @return     XVARIANT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT* XFILECFG::GetValue(XCHAR* group, XCHAR* ID)
{
  XVARIANT* value = NULL;

  if((!group) || (!ID))
    {
      return NULL;
    }

  for(XDWORD c=0; c<values.GetSize(); c++)
    {
      XFILECFGVALUE* cfgvalue = values.Get(c);
      if(cfgvalue)
        {
          if((!cfgvalue->GetGroup()->Compare(group, true)) && (!cfgvalue->GetID()->Compare(ID, true)))
            {
              value = new XVARIANT();
              if(value)
                {
                  switch(cfgvalue->GetType())
                    {
                      case XFILECFG_VALUETYPE_UNKNOWN :
                                             default  : delete value; 
                                                        value = NULL;
                                                        break;

                      case XFILECFG_VALUETYPE_INT     : (*value) = (*(int*)(cfgvalue->GetValue()));     break; 
                      case XFILECFG_VALUETYPE_MASK    : (*value) = (*(XWORD*)(cfgvalue->GetValue()));   break;
                      case XFILECFG_VALUETYPE_FLOAT   : (*value) = (*(float*)(cfgvalue->GetValue()));   break;                                                        

                      case XFILECFG_VALUETYPE_STRING  : { XSTRING* _value = (XSTRING*)(cfgvalue->GetValue());                                                        
                                                          (*value) = _value->Get(); 
                                                        }
                                                        break;

                      case XFILECFG_VALUETYPE_BOOLEAN : (*value) = (*(bool*)(cfgvalue->GetValue()));    break; 
                    }
                }    
            }
        }
    }
  
  return value;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECFG::DeleteAllValues()
* @brief      Delete All Values
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECFG::DeleteAllValues()
{
  if(values.IsEmpty()) return false;

  values.DeleteContents();
  values.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILECFG::AddRemark(XCHAR* group, XCHAR* text, XDWORD xpos, XDWORD relativeypos)
* @brief      AddRemark
* @ingroup    XUTILS
*
* @param[in]  group : 
* @param[in]  text : 
* @param[in]  xpos : 
* @param[in]  relativeypos : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XFILECFG::AddRemark(XCHAR* group, XCHAR* text, XDWORD xpos, XDWORD relativeypos)
{
  if(!fileini) return false;

  XFILEINIREMARK* remark =  new XFILEINIREMARK();
  if(!remark) return false;
  
  remark->SetType(XFILEINI_TYPEREMARK_ALL_LINE);
  remark->GetRelativeSection()->Set(group);
  remark->GetRelativeKey()->Empty();
  remark->SetXPos(xpos);
  remark->SetRelativeYPos(relativeypos);
  remark->GetTextRemark()->Empty();
  remark->GetTextRemark()->Add(text);

  remarks.Add(remark);

  return true;
}



    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILECFG::AddRemark(XCHAR* group, XCHAR* ID, XCHAR* text, XDWORD xpos, XDWORD relativeypos)
* @brief      AddRemark
* @ingroup    XUTILS
*
* @param[in]  group : 
* @param[in]  ID : 
* @param[in]  text : 
* @param[in]  xpos : 
* @param[in]  relativeypos : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XFILECFG::AddRemark(XCHAR* group, XCHAR* ID, XCHAR* text, XDWORD xpos, XDWORD relativeypos)
{
  if(!fileini) return false;

  XFILEINIREMARK* remark =  new XFILEINIREMARK();
  if(!remark) return false;
  
  remark->SetType(XFILEINI_TYPEREMARK_IN_KEY);
  remark->GetRelativeSection()->Set(group);
  remark->GetRelativeKey()->Set(ID);
  remark->SetXPos(xpos);
  remark->SetRelativeYPos(relativeypos);
  remark->GetTextRemark()->Empty();
  remark->GetTextRemark()->Add(text);

  remarks.Add(remark);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn          XVECTOR<XFILEINIREMARK*>* XFILECFG::GetRemarks()
* @brief       GetRemarks
* @ingroup     UTILS
* 
* @return      XVECTOR<XFILEINIREMARK*>* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<XFILEINIREMARK*>* XFILECFG::GetRemarks()
{
  return &remarks;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILECFG::DeleteAllRemarks()
* @brief      DeleteAllRemarks
* @ingroup    XUTILS
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XFILECFG::DeleteAllRemarks()
{
  if(remarks.IsEmpty()) return false;

  remarks.DeleteContents();
  remarks.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECFG::IniFile(XPATH& xpath)
* @brief      Ini File
* @note       INTERNAL
* @ingroup    XUTILS
*
* @param[in]  xpath :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECFG::IniFile(XPATH& xpath)
{
  if(!fileini)           return false;
  if(xpath.IsEmpty())    return false;

  bool status = false;

  if(!fileini->Open(xpath, false)) fileini->Create(xpath);

  if(fileini->IsOpen())
    {
      if(fileini->GetFormatCharFromFile()==XFILETXTFORMATCHAR_UNKNOWN) fileini->SetFormatChar(XFILETXTFORMATCHAR_ASCII);
      if(fileini->GetTypeLF()==XFILETXTTYPELF_UNKNOWN)                 fileini->SetTypeLF(XFILETXTTYPELF_DEFAULT);

      status = true;
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECFG::EndFile()
* @brief      End File
* @note       INTERNAL
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECFG::EndFile()
{
  if(!fileini) return false;

  return fileini->Close();
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILECFG::AjustRemarks()
* @brief      AjustRemarks
* @ingroup    XUTILS
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XFILECFG::AjustRemarks()
{
  if(!fileini) return false;

  XVECTOR<XFILEINIREMARK*>* ini_remarks = fileini->GetRemarks();
  if(!ini_remarks) return false;
  
  for(XDWORD d=0; d<remarks.GetSize(); d++)
    {
      XFILEINIREMARK* remark = remarks.Get(d);
      if(remark)
        {
          bool found  = false;

          for(XDWORD c=0; c<ini_remarks->GetSize(); c++)
            {
              XFILEINIREMARK* ini_remark = ini_remarks->Get(c);
              if(ini_remark)
                {
                  if(ini_remark->Compare(remark))  
                    {
                      found = true;
                      break;
                    }                    
                }  
            }

          if(!found)
            {
              XFILEINIREMARK* add_remark = new XFILEINIREMARK();
              if(add_remark)
                {
                  remark->CopyTo(add_remark);
                  ini_remarks->Add(add_remark);  
                }
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILEINI* XFILECFG::GetFileINI()
* @brief      GetFileINI
* @ingroup    XUTILS
* 
* @return     XFILEINI* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XFILEINI* XFILECFG::GetFileINI()
{
  return fileini;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILECFG::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFILECFG::Clean()
{
  fileini     = NULL;

  namefile.Empty();
}

#pragma endregion
