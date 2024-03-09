/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XFileCFG.cpp
* 
* @class      XFILECFG
* @brief      eXtended Utils CFG (Config) file class
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

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XFileCFG.h"

#include <stdio.h>
#include <string.h>

#include "XPath.h"
#include "XFileINI.h"
#include "XVector.h"
#include "XVariant.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


#pragma region CLASS_XFILECFGVALUE


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILECFGVALUE::XFILECFGVALUE()
* @brief      Constructor
* @ingroup    XUTILS
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
* @fn         XSTRING* XFILECFGVALUE::GetIDBasic()
* @brief      GetIDBasic
* @ingroup    XUTILS
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* XFILECFGVALUE::GetIDBasic()
{
  return &IDbasic;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* XFILECFGVALUE::GetMask()
* @brief      GetMask
* @ingroup    XUTILS
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* XFILECFGVALUE::GetMask()
{
  return &mask;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD XFILECFGVALUE::GetMinSecuences()
* @brief      GetMinSecuences
* @ingroup    XUTILS
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XFILECFGVALUE::GetMinSecuences()
{
  return minsecuences;
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XFILECFGVALUE::SetMinSecuences(XDWORD minsecuences)
* @brief      SetMinSecuences
* @ingroup    XUTILS
* 
* @param[in]  minsecuences : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XFILECFGVALUE::SetMinSecuences(XDWORD minsecuences)
{
  this->minsecuences = minsecuences;
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD XFILECFGVALUE::GetMaxSecuences()
* @brief      GetMaxSecuences
* @ingroup    XUTILS
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XFILECFGVALUE::GetMaxSecuences()
{
  return maxsecuences;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XFILECFGVALUE::SetMaxSecuences(XDWORD maxsecuences)
* @brief      SetMaxSecuences
* @ingroup    XUTILS
* 
* @param[in]  maxsecuences : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XFILECFGVALUE::SetMaxSecuences(XDWORD maxsecuences)
{
  this->maxsecuences = maxsecuences;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int XFILECFGVALUE::GetIndexSecuence()
* @brief      GetIndexSecuence
* @ingroup    XUTILS
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int XFILECFGVALUE::GetIndexSecuence()
{
  return indexsecuence;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XFILECFGVALUE::SetIndexSecuence(int index)
* @brief      SetIndexSecuence
* @ingroup    XUTILS
* 
* @param[in]  index : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XFILECFGVALUE::SetIndexSecuence(int index)
{
  this->indexsecuence = index;
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD XFILECFGVALUE::GetNSecuences()
* @brief      GetNSecuences
* @ingroup    XUTILS
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XFILECFGVALUE::GetNSecuences()
{
  return nsecuences;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XFILECFGVALUE::SetNSecuences(XDWORD nsecuences)
* @brief      SetNSecuences
* @ingroup    XUTILS
* 
* @param[in]  nsecuences : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XFILECFGVALUE::SetNSecuences(XDWORD nsecuences)
{
  this->nsecuences = nsecuences;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* XFILECFGVALUE::GetRemarkText()
* @brief      GetRemarkText
* @ingroup    XUTILS
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* XFILECFGVALUE::GetRemarkText()
{
  return &remark_text;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD XFILECFGVALUE::GetRemarkXPos()
* @brief      GetRemarkXPos
* @ingroup    XUTILS
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XFILECFGVALUE::GetRemarkXPos()
{
  return remark_xpos;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XFILECFGVALUE::SetRemarkXPos(XDWORD remark_xpos)
* @brief      SetRemarkXPos
* @ingroup    XUTILS
* 
* @param[in]  remark_xpos : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XFILECFGVALUE::SetRemarkXPos(XDWORD remark_xpos)
{
  this->remark_xpos = remark_xpos;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void* XFILECFGVALUE::GetValuesVector()
* @brief      GetValuesVector
* @ingroup    XUTILS
* 
* @return     void* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void* XFILECFGVALUE::GetValuesVector()
{
  return valuesvector;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XFILECFGVALUE::SetValuesVector(void* valuesvector)
* @brief      SetValuesVector
* @ingroup    XUTILS
* 
* @param[in]  valuesvector : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XFILECFGVALUE::SetValuesVector(void* valuesvector)
{
  this->valuesvector = valuesvector;  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILECFG_MODEREMOTEMIX XFILECFGVALUE::GetModeRemoteMix()
* @brief      GetModeRemoteMix
* @ingroup    XUTILS
* 
* @return     XFILECFG_MODEREMOTEMIX : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XFILECFG_MODEREMOTEMIX XFILECFGVALUE::GetModeRemoteMix()
{
  return moderemotemix;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XFILECFGVALUE::SetModeRemoteMix(XFILECFG_MODEREMOTEMIX moderemotemix)
* @brief      SetModeRemoteMix
* @ingroup    XUTILS
* 
* @param[in]  moderemotemix : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XFILECFGVALUE::SetModeRemoteMix(XFILECFG_MODEREMOTEMIX moderemotemix)
{
  this->moderemotemix = moderemotemix;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILECFGVALUE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFILECFGVALUE::Clean()
{
  type            = XFILECFG_VALUETYPE_UNKNOWN;;
  group.Empty();
  ID.Empty();
  value           = NULL;
    
  IDbasic.Empty();
  mask.Empty();
  minsecuences    = 0;    
  maxsecuences    = 0;    
  indexsecuence   = XFILECFG_INVALIDINDEXSECUENCE;
  nsecuences      = 0;
  remark_text.Empty();
  remark_xpos     = 0;
  valuesvector    = NULL;  

  moderemotemix   = XFILECFG_MODEREMOTEMIX_NONE;
}


#pragma endregion


#pragma region CLASS_XFILECFG


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILECFG::XFILECFG(XCHAR* namefile)
* @brief      Constructor
* @ingroup    XUTILS
*
* @param[in]  XCHAR* : name file of config
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
* @fn         bool XFILECFG::DoVariableMapping()
* @brief      DoVariableMapping
* @ingroup    XUTILS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECFG::DoVariableMapping()
{
  return true;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILECFG::DoDefault()
* @brief      DoDefault
* @ingroup    XUTILS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECFG::DoDefault()
{
  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILECFG::LoadReadjustment()
* @brief      LoadReadjustment
* @ingroup    XUTILS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECFG::LoadReadjustment()
{
  return true;
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

  if(fileini->IsOpen())
    {
      EndFile();
    }
    
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

  if(values.IsEmpty()) return status;
  
  if(fileini->IsOpen())
    {
      EndFile();
    }

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

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILECFG::End()
* @brief      End
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
* @fn         XPATH* XFILECFG::GetPathFile()
* @brief      GetPathFile
* @ingroup    XUTILS
* 
* @return     XPATH* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XPATH* XFILECFG::GetPathFile()
{
   return &xpathfile;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILECFGVALUE* XFILECFG::AddValue(XFILECFG_VALUETYPE type, XCHAR* group, XCHAR* ID, void* value, XCHAR* remark_text, XDWORD remark_xpos)
* @brief      AddValue
* @ingroup    XUTILS
* 
* @param[in]  type : 
* @param[in]  group : 
* @param[in]  ID : 
* @param[in]  value : 
* @param[in]  remark_text : 
* @param[in]  remark_xpos : 
* 
* @return     XFILECFGVALUE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XFILECFGVALUE* XFILECFG::AddValue(XFILECFG_VALUETYPE type, XCHAR* group, XCHAR* ID, void* value, XCHAR* remark_text, XDWORD remark_xpos)
{
  XFILECFGVALUE* CFGvalue = new XFILECFGVALUE();
  if(!CFGvalue) return NULL;

  CFGvalue->SetType(type);
  CFGvalue->GetGroup()->Set(group);
  CFGvalue->GetID()->Set(ID);
  CFGvalue->SetValue(value);

  if(values.Add(CFGvalue))
    {
      if(remark_text)
        {
          AddRemark(group, ID, remark_text, remark_xpos, 0);
        }
    }

  return CFGvalue;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<XFILECFGVALUE*>* XFILECFG::GetValues()
* @brief      GetValues
* @ingroup    XUTILS
* 
* @return     XVECTOR<XFILECFGVALUE*>* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<XFILECFGVALUE*>* XFILECFG::GetValues()
{
  return &values;
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
* @fn         XVARIANT* XFILECFG::GetValue(XFILECFGVALUE* cfgvalue)
* @brief      GetValue
* @ingroup    XUTILS
* 
* @param[in]  cfgvalue : 
* 
* @return     XVARIANT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT* XFILECFG::GetValue(XFILECFGVALUE* CFGvalue)
{
  XVARIANT* value = NULL;

  if(!CFGvalue)
    {
      return NULL;
    }

  value = new XVARIANT();
  if(!value) return NULL;
      
  switch(CFGvalue->GetType())
    {
      case XFILECFG_VALUETYPE_UNKNOWN :
                              default : delete value; 
                                        value = NULL;
                                        break;

      case XFILECFG_VALUETYPE_INT     : (*value) = (*(int*)  (CFGvalue->GetValue()));     break; 
      case XFILECFG_VALUETYPE_MASK    : (*value) = (*(XWORD*)(CFGvalue->GetValue()));   break;
      case XFILECFG_VALUETYPE_FLOAT   : (*value) = (*(float*)(CFGvalue->GetValue()));   break;                                                        

      case XFILECFG_VALUETYPE_STRING  : { XSTRING* _value = (XSTRING*)(CFGvalue->GetValue());                                                        
                                          (*value) = _value->Get(); 
                                        }
                                        break;

      case XFILECFG_VALUETYPE_BOOLEAN : (*value) = (*(bool*)(CFGvalue->GetValue()));    break; 
    }
 
  return value;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILECFGVALUE* XFILECFG::GetCFGValue(XCHAR* group, XCHAR* ID)
* @brief      GetCFGValue
* @ingroup    XUTILS
* 
* @param[in]  group : 
* @param[in]  ID : 
* 
* @return     XFILECFGVALUE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XFILECFGVALUE* XFILECFG::GetCFGValue(XCHAR* group, XCHAR* ID)
{
  if((!group) || (!ID))
    {
      return NULL;
    }

  for(XDWORD c=0; c<values.GetSize(); c++)
    {
      XFILECFGVALUE* CFGvalue = values.Get(c);
      if(CFGvalue)
        {
          if( (!CFGvalue->GetGroup()->Compare(group, true)) &&
              (!CFGvalue->GetID()->Compare(ID, true)))
           {
              return CFGvalue;
           }          
        }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILECFG::SetValue(XFILECFGVALUE* CFGvalue, XVARIANT* value)
* @brief      SetValue
* @ingroup    XUTILS
* 
* @param[in]  CFGvalue : 
* @param[in]  value : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECFG::SetValue(XFILECFGVALUE* CFGvalue, XVARIANT* value)
{
  if((!CFGvalue) || (!value))
    {
      return false;
    }

   switch(CFGvalue->GetType())
    {
      case XFILECFG_VALUETYPE_UNKNOWN :
                              default : { delete (XBYTE*)(CFGvalue->GetValue());
                                          CFGvalue->SetValue(NULL);                                          
                                        }
                                        break;

      case XFILECFG_VALUETYPE_INT     : (*(int*)  CFGvalue->GetValue()) = (*(int*)  (value->GetData()));   break; 
      case XFILECFG_VALUETYPE_MASK    : (*(XWORD*)CFGvalue->GetValue()) = (*(XWORD*)(value->GetData()));   break;
      case XFILECFG_VALUETYPE_FLOAT   : (*(float*)CFGvalue->GetValue()) = (*(float*)(value->GetData()));   break;                                                        

      case XFILECFG_VALUETYPE_STRING  : { XSTRING* _value = (XSTRING*)(CFGvalue->GetValue());                                                        
                                          (*_value) = ((XSTRING*)value->GetData())->Get();
                                        }
                                        break;

      case XFILECFG_VALUETYPE_BOOLEAN : (*(bool*)CFGvalue->GetValue()) = (*(bool*)(value->GetData()));    break; 
    }

  return true;
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
* @fn         XVECTOR<XFILEINIREMARK*>* XFILECFG::GetRemarks()
* @brief      GetRemarks
* @ingroup    XUTILS
* 
* @return     XVECTOR<XFILEINIREMARK*>* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<XFILEINIREMARK*>* XFILECFG::GetRemarks()
{
  return &remarks;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILECFG::DelCFGValue(XCHAR* group, XCHAR* ID)
* @brief      DelCFGValue
* @ingroup    XUTILS
* 
* @param[in]  group : 
* @param[in]  ID : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECFG::DelCFGValue(XCHAR* group, XCHAR* ID)
{
  XFILECFGVALUE* CFGvalue = XFILECFG::GetCFGValue(group, ID);
  if(!CFGvalue) return false;

  values.Delete(CFGvalue);

  delete CFGvalue;
  
  return true;
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
* @fn         int XFILECFG::GetCountKeys(XCHAR* group, XCHAR* IDbase, XCHAR* mask, int maxcount)
* @brief      GetCountKeys
* @ingroup    XUTILS
* 
* @param[in]  group : 
* @param[in]  IDbase : 
* @param[in]  mask : 
* @param[in]  maxcount : 
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int XFILECFG::GetCountKeys(XCHAR* group, XCHAR* IDbasic, XCHAR* mask, int maxcount)
{
  XSTRING   section       = group;      
  int       enumeratekeys = -1;
  
  if(!fileini->IsOpen())
    {
      if(!fileini->Open(xpathfile, true))
        {
          return 0;
        }
    }

  enumeratekeys = 0;

  for(int c=1; c<maxcount+1; c++)
    {    
      XSTRING key;       
      GenerateKeySecuence(IDbasic, mask, c, key);
      
      XFILEINIKEY* inikey = GetFileINI()->GetKey(section, key);
      if(inikey) enumeratekeys++;
    }      

  return enumeratekeys;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILECFG::GenerateKeySecuence(XCHAR* IDbase, XCHAR* mask, int index, XSTRING& key)
* @brief      GenerateKeySecuence
* @ingroup    XUTILS
* 
* @param[in]  IDbase : 
* @param[in]  mask : 
* @param[in]  index : 
* @param[in]  key : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECFG::GenerateKeySecuence(XCHAR* IDbase, XCHAR* mask, int index, XSTRING& key)
{
  XSTRING keymask;      
  
  key.Empty();     
  
  if(!IDbase) return false;
    
  if(mask)  
    {
      keymask.Format(__L("%s%s"), IDbase, mask);
      key.Format(keymask.Get(), index);

    } else key.Format(__L("%s%d"), IDbase, index);
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILECFG::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFILECFG::Clean()
{
  fileini     = NULL;

  namefile.Empty();
}


#pragma endregion

