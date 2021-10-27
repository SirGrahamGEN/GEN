/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XFileCFG.cpp
*
* @class      XFILECFG
* @brief      eXtended CFG (Config) file class
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
#include "XVector.h"

#include "XFileCFG.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILECFGVALUE::XFILECFGVALUE()
* @brief      Constructor
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XFILECFGVALUE::XFILECFGVALUE()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILECFGVALUE::~XFILECFGVALUE()
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
XFILECFGVALUE::~XFILECFGVALUE()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILECFG_VALUETYPE XFILECFGVALUE::GetType()
* @brief      Get Type
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XFILECFG_VALUETYPE : Type of value
*
*---------------------------------------------------------------------------------------------------------------------*/
XFILECFG_VALUETYPE XFILECFGVALUE::GetType()
{
  return type;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECFGVALUE::SetType(XFILECFG_VALUETYPE type)
* @brief      Set Type
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  type : new type of value
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILECFGVALUE::SetType(XFILECFG_VALUETYPE type)
{
  this->type = type;
  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* XFILECFGVALUE::GetGroup()
* @brief      Get Group
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XSTRING* : group of value
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* XFILECFGVALUE::GetGroup()
{
  return &group;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* XFILECFGVALUE::GetID()
* @brief      Get ID
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XSTRING* : ID df vlaue
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* XFILECFGVALUE::GetID()
{
  return &ID;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void* XFILECFGVALUE::GetValue()
* @brief      Get Value
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void* : data of value
*
*---------------------------------------------------------------------------------------------------------------------*/
void* XFILECFGVALUE::GetValue()
{
  return value;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECFGVALUE::SetValue(void* value)
* @brief      Set Value
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  value : new data of value
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XFILECFGVALUE::Clean()
{
  type = XFILECFG_VALUETYPE_UNKNOWN;
  value = NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* XFILECFG  eXtended file Config
*
*---------------------------------------------------------------------------------------------------------------------*/




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILECFG::XFILECFG(XCHAR* namefile)
* @brief      Constructor
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  XCHAR* : name file of config
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XFILECFG::XFILECFG(XCHAR* namefile)
{
  Clean();

  if(!namefile) return;

  this->namefile = namefile;

  if(this->namefile.IsEmpty()) return;

  XPATH xpathroot;
  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathroot);

  xpathfile.Add(xpathroot.Get());
  if(!xpathfile.IsEmpty()) xpathfile.Slash_Add();

  xpathfile.Add(this->namefile.Get());
  xpathfile.Add(XFILECFG_EXTENSIONFILE);

  fileini = new XFILEINI();

 }



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILECFG::~XFILECFG()
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
XFILECFG::~XFILECFG()
{
  if(!namefile.IsEmpty())
    {
      if(fileini) delete fileini;
    }

  DeleteAllValues();
  
  Clean();
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECFG::Ini()
* @brief      Ini xfile Config
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILECFG::Ini()
{
  if(namefile.IsEmpty())   return false;
  if(xpathfile.IsEmpty())  return false;

  bool status[2];

  status[0] = Load();
  status[1] = Save();

  return (status[0] && status[1]);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECFG::Load()
* @brief      Load xfile config
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILECFG::Load()
{
  if(xpathfile.IsEmpty()) return false;

  return Load(xpathfile);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECFG::Load(XPATH& xpath)
* @brief      Load xfile config
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  xpath : path to file config
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILECFG::Load(XPATH& xpath)
{
  bool status = false;

  if(!values.IsEmpty())
    {
      if(IniFile(xpath)) 
        {
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

                                                              value->DeleteCharacter(__C(' '), XSTRINGCONTEXT_ATEND);
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

    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECFG::Save()
* @brief      Save xfile config
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILECFG::Save()
{
  if(xpathfile.IsEmpty()) return false;
  return Save(xpathfile);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECFG::Save(XPATH& xpath)
* @brief      Save file config
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  xpath : path to file config
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILECFG::Save(XPATH& xpath)
{
  bool status = false;

  if(!values.IsEmpty())
    {
      if(IniFile(xpath))
        {
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
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILECFG::End()
{
  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECFG::AddValue(XFILECFG_VALUETYPE type, XCHAR* group, XCHAR* ID, void* value)
* @brief      Add Value to file config
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  type : type of value
* @param[in]  group : group of value
* @param[in]  ID : ID of value
* @param[in]  value : data value
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILECFG::AddValue(XFILECFG_VALUETYPE type, XCHAR* group, XCHAR* ID, void* value)
{
  XFILECFGVALUE* cfgvalue = new XFILECFGVALUE();
  if(!cfgvalue) return false;

  cfgvalue->SetType(type);
  cfgvalue->GetGroup()->Set(group);
  cfgvalue->GetID()->Set(ID);
  cfgvalue->SetValue(value);

  values.Add(cfgvalue);

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECFG::DeleteAllValues()
* @brief      Delete All Values
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILECFG::DeleteAllValues()
{
  if(values.IsEmpty()) return false;

  values.DeleteContents();
  values.DeleteAll();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILECFG::Clean()
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
void XFILECFG::Clean()
{
  fileini     = NULL;
  namefile.Empty();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECFG::IniFile(XPATH& xpath)
* @brief      Ini File
* @note       INTERNAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  xpath :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XFILECFG::EndFile()
{
  if(!fileini) return false;

  return fileini->Close();
}


