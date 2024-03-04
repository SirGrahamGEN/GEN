/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XFileJSON.cpp
* 
* @class      XFILEJSON
* @brief      eXtended Utils JSON (JavaScript Object Notation) file class
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

#include "XFileJSON.h"

#include <stdio.h>
#include <string.h>

#include "XTrace.h"
#include "XVariant.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


#pragma region CLASS_XFILEJSONVALUE


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEJSONVALUE::XFILEJSONVALUE()
* @brief      Constructor
* @ingroup    XUTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEJSONVALUE::XFILEJSONVALUE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEJSONVALUE::~XFILEJSONVALUE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEJSONVALUE::~XFILEJSONVALUE()
{
  Delete();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEJSONVALUETYPE XFILEJSONVALUE::GetType()
* @brief      GetType
* @ingroup    XUTILS
*
* @return     XFILEJSONVALUETYPE :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEJSONVALUETYPE XFILEJSONVALUE::GetType()
{
  return type;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILEJSONVALUE::SetType(XFILEJSONVALUETYPE type)
* @brief      SetType
* @ingroup    XUTILS
*
* @param[in]  type : 
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFILEJSONVALUE::SetType(XFILEJSONVALUETYPE type)
{
  this->type = type;  
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* XFILEJSONVALUE::GetName()
* @brief      GetName
* @ingroup    XUTILS
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* XFILEJSONVALUE::GetName()
{
  return name;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEJSONVALUE::SetName(XSTRING& name)
* @brief      SetName
* @ingroup    XUTILS
*
* @param[in]  name :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSONVALUE::SetName(XSTRING& name)
{
  XSTRING* _name = new XSTRING(name);
  if(!_name) return false;

  this->name = _name;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEJSONVALUE::SetName(XCHAR* name)
* @brief      SetName
* @ingroup    XUTILS
*
* @param[in]  name :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSONVALUE::SetName(XCHAR* name)
{
  XSTRING* _name = new XSTRING(name);
  if(!_name) return false;

  this->name = _name;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVARIANT* XFILEJSONVALUE::GetValue()
* @brief      GetValue
* @ingroup    XUTILS
* 
* @return     XVARIANT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT* XFILEJSONVALUE::GetValue()
{
  return &value;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEJSONVALUE::GetValueBoolean()
* @brief      GetValueBoolean
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSONVALUE::GetValueBoolean()
{
  return (bool)(value);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         short XFILEJSONVALUE::GetValueShort()
* @brief      GetValueShort
* @ingroup    XUTILS
* 
* @return     short : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
short XFILEJSONVALUE::GetValueShort()
{
  return (short)(value);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XWORD XFILEJSONVALUE::GetValueWord()
* @brief      GetValueWord
* @ingroup    XUTILS
* 
* @return     XWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XWORD XFILEJSONVALUE::GetValueWord()
{
  return (XWORD)(value);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XFILEJSONVALUE::GetValueInteger()
* @brief      GetValueInteger
* @ingroup    XUTILS
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XFILEJSONVALUE::GetValueInteger()
{
  return (int)(value);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         long XFILEJSONVALUE::GetValueDoubleInteger()
* @brief      GetValueDoubleInteger
* @ingroup    XUTILS
* 
* @return     long : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XFILEJSONVALUE::GetValueDWord()
{
  return (XDWORD)(value);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         long long XFILEJSONVALUE::GetValueDoubleInteger()
* @brief      GetValueDoubleInteger
* @ingroup    XUTILS
* 
* @return     long : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
long long XFILEJSONVALUE::GetValueDoubleInteger()
{
  return (long long)(value);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XQWORD XFILEJSONVALUE::GetValueQWord()
* @brief      GetValueQWord
* @ingroup    XUTILS
* 
* @return     XQWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XQWORD XFILEJSONVALUE::GetValueQWord()
{
  return (XQWORD)(value);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float XFILEJSONVALUE::GetValueFloating()
* @brief      GetValueFloating
* @ingroup    XUTILS
*
* @return     float :
*
* --------------------------------------------------------------------------------------------------------------------*/
float XFILEJSONVALUE::GetValueFloating()
{
  return (float)(value);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double XFILEJSONVALUE::GetValueDoubleFloat()
* @brief      GetValueDoubleFloat
* @ingroup    XUTILS
* 
* @return     double : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
double XFILEJSONVALUE::GetValueDoubleFloat()
{
  return (double)(value);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* XFILEJSONVALUE::GetValueString()
* @brief      GetValueString
* @ingroup    XUTILS
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING XFILEJSONVALUE::GetValueString()
{  
  XSTRING string = (const XSTRING&)value;
  
  return string;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILEJSONOBJECT* XFILEJSONVALUE::GetValueObject()
* @brief      GetValueObject
* @ingroup    XUTILS
*
* @return     XFILEJSONOBJECT* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XFILEJSONOBJECT* XFILEJSONVALUE::GetValueObject()
{
  return (XFILEJSONOBJECT*)GetValuePointer();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILEJSONARRAY* XFILEJSONVALUE::GetValueArray()
* @brief      GetValueArray
* @ingroup    XUTILS
*
* @return     XFILEJSONARRAY* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XFILEJSONARRAY* XFILEJSONVALUE::GetValueArray()
{
  return (XFILEJSONARRAY*)GetValuePointer();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void* XFILEJSONVALUE::GetValuePointer()
* @brief      GetValuePointer
* @ingroup    XUTILS
*
* @return     void* :
*
* --------------------------------------------------------------------------------------------------------------------*/
void* XFILEJSONVALUE::GetValuePointer()
{
  return (void*)(value);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILEJSONVALUE::Set(void)
* @brief      Set
* @ingroup    XUTILS
* 
* @param[in]  void : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSONVALUE::Set(void)
{
  value.Set(XVARIANT_TYPE_NULL);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEJSONVALUE::Set(bool boolean)
* @brief      Set
* @ingroup    XUTILS
*
* @param[in]  boolean :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSONVALUE::Set(bool boolean)
{
  type = XFILEJSONVALUETYPE_BOOLEAN;
  value = (bool)boolean;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILEJSONVALUE::Set(short number)
* @brief      Set
* @ingroup    XUTILS
* 
* @param[in]  number : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSONVALUE::Set(short number)
{
  type  =  XFILEJSONVALUETYPE_SHORT;
  value = (short)number;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILEJSONVALUE::Set(XWORD number)
* @brief      Set
* @ingroup    XUTILS
* 
* @param[in]  number : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSONVALUE::Set(XWORD number)
{
  type  =  XFILEJSONVALUETYPE_WORD;
  value = (XWORD)number;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEJSONVALUE::Set(int number)
* @brief      Set
* @ingroup    XUTILS
*
* @param[in]  number :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSONVALUE::Set(int number)
{
  type  =  XFILEJSONVALUETYPE_INTEGER;
  value = (int)number;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILEJSONVALUE::Set(XDWORD number)
* @brief      Set
* @ingroup    XUTILS
* 
* @param[in]  number : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSONVALUE::Set(XDWORD number)
{
  type  = XFILEJSONVALUETYPE_DWORD;
  value = (XDWORD)number;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILEJSONVALUE::Set(long long number)
* @brief      Set
* @ingroup    XUTILS
* 
* @param[in]  long number : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSONVALUE::Set(long long number)
{
  type =  XFILEJSONVALUETYPE_DOUBLEINTEGER;
  value = number;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILEJSONVALUE::Set(XQWORD number)
* @brief      Set
* @ingroup    XUTILS
* 
* @param[in]  number : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSONVALUE::Set(XQWORD number)
{
  type =  XFILEJSONVALUETYPE_QWORD;
  value = number;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILEJSONVALUE::Set(float number)
* @brief      Set
* @ingroup    XUTILS
* 
* @param[in]  number : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSONVALUE::Set(float number)
{
  type  =  XFILEJSONVALUETYPE_FLOAT;
  value = number;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILEJSONVALUE::Set(double number)
* @brief      Set
* @ingroup    XUTILS
* 
* @param[in]  number : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSONVALUE::Set(double number)
{  
  type =  XFILEJSONVALUETYPE_DOUBLEFLOAT;
  value = number;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILEJSONVALUE::Set(XSTRING& string)
* @brief      Set
* @ingroup    XUTILS
* 
* @param[in]  string : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSONVALUE::Set(XSTRING& string)
{
  return Set(string.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILEJSONVALUE::Set(XCHAR* string)
* @brief      Set
* @ingroup    XUTILS
* 
* @param[in]  string : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSONVALUE::Set(XCHAR* string)
{  
  type =  XFILEJSONVALUETYPE_STRING;
  value = (XCHAR*)(string);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILEJSONVALUE::Set(XFILEJSONOBJECT* object)
* @brief      Set
* @ingroup    XUTILS
* 
* @param[in]  object : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSONVALUE::Set(XFILEJSONOBJECT* object)
{
  if(!object) return false;

  type = XFILEJSONVALUETYPE_OBJECT; 
  value.Set(XVARIANT_TYPE_POINTER, (void*)object, sizeof(void*));

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILEJSONVALUE::Set(XFILEJSONARRAY* array)
* @brief      Set
* @ingroup    XUTILS
* 
* @param[in]  array : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSONVALUE::Set(XFILEJSONARRAY* array)
{
  if(!array) return false;

  type = XFILEJSONVALUETYPE_ARRAY;
  value.Set(XVARIANT_TYPE_POINTER, (void*)array, sizeof(void*));

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILEJSONVALUE::Set(XVARIANT* variant)
* @brief      Set
* @ingroup    XUTILS
* 
* @param[in]  variant : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSONVALUE::Set(XVARIANT* variant)
{
  if(!variant) return false;

  XSTRING tempostr;
  
  switch(variant->GetType())
    {
      case XVARIANT_TYPE_NULL           : type = XFILEJSONVALUETYPE_NULL;   
                                          value = (*variant);        
                                          break;

      case XVARIANT_TYPE_BOOLEAN        : type = XFILEJSONVALUETYPE_BOOLEAN;        
                                          value = (*variant);
                                          break;

      case XVARIANT_TYPE_SHORT          : type = XFILEJSONVALUETYPE_SHORT;          
                                          value = (*variant);
                                          break;

      case XVARIANT_TYPE_WORD           : type = XFILEJSONVALUETYPE_WORD;           
                                          value = (*variant);
                                          break;

      case XVARIANT_TYPE_INTEGER        : type = XFILEJSONVALUETYPE_INTEGER;        
                                          value = (*variant);
                                          break;

      case XVARIANT_TYPE_DWORD          : type = XFILEJSONVALUETYPE_DWORD;          
                                          value = (*variant);
                                          break;

      case XVARIANT_TYPE_DOUBLEINTEGER  : type = XFILEJSONVALUETYPE_DOUBLEINTEGER;  
                                          value = (*variant);
                                          break;

      case XVARIANT_TYPE_QWORD          : type = XFILEJSONVALUETYPE_QWORD;          
                                          value = (*variant);
                                          break;

      case XVARIANT_TYPE_FLOAT          : type = XFILEJSONVALUETYPE_FLOAT;          
                                          value = (*variant);
                                          break;

      case XVARIANT_TYPE_DOUBLE         : type = XFILEJSONVALUETYPE_DOUBLEFLOAT;    
                                          value = (*variant);
                                          break;

      case XVARIANT_TYPE_CHAR           : type = XFILEJSONVALUETYPE_STRING;                                                    
                                          variant->ToString(tempostr);
                                          value = tempostr;
                                          break;

      case XVARIANT_TYPE_XCHAR          : type = XFILEJSONVALUETYPE_STRING;         
                                          variant->ToString(tempostr);
                                          value = tempostr;
                                          break;  

      case XVARIANT_TYPE_STRING         : type = XFILEJSONVALUETYPE_STRING;         
                                          value = (*variant);
                                          break;

      case XVARIANT_TYPE_DATE           : type = XFILEJSONVALUETYPE_STRING;         
                                          variant->ToString(tempostr);
                                          value = tempostr;
                                          break;

      case XVARIANT_TYPE_TIME           : type = XFILEJSONVALUETYPE_STRING;         
                                          variant->ToString(tempostr);
                                          value = tempostr;
                                          break;

      case XVARIANT_TYPE_DATETIME       : type = XFILEJSONVALUETYPE_STRING;         
                                          variant->ToString(tempostr);
                                          value = tempostr;
                                          break;

      case XVARIANT_TYPE_BUFFER         : type = XFILEJSONVALUETYPE_STRING;         
                                          variant->ToString(tempostr);
                                          value = tempostr;
                                          break;

      case XVARIANT_TYPE_POINTER        : type = XFILEJSONVALUETYPE_STRING;         
                                          variant->ToString(tempostr);
                                          value = tempostr;
                                          break;                     
    }
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEJSONVALUE::Delete()
* @brief      Delete
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSONVALUE::Delete()
{
  if(name)
    {
      delete name;
      name = NULL;
    }

  switch(type)
    {      
      case XFILEJSONVALUETYPE_NULL            :
      case XFILEJSONVALUETYPE_BOOLEAN         :
      case XFILEJSONVALUETYPE_SHORT           :
      case XFILEJSONVALUETYPE_WORD            :
      case XFILEJSONVALUETYPE_INTEGER         :
      case XFILEJSONVALUETYPE_DWORD           :
      case XFILEJSONVALUETYPE_DOUBLEINTEGER   :
      case XFILEJSONVALUETYPE_QWORD           :
      case XFILEJSONVALUETYPE_FLOAT           :
      case XFILEJSONVALUETYPE_DOUBLEFLOAT     : value.Destroy();
                                                break;

      case XFILEJSONVALUETYPE_STRING          : { //void* pointer = value;
                                                  //XSTRING* string = (XSTRING*)pointer;
                                                  //delete string;
                                                  value.Destroy();
                                                }                                                
                                                break;

      case XFILEJSONVALUETYPE_OBJECT          : { void* pointer = value;
                                                  XFILEJSONOBJECT* object = (XFILEJSONOBJECT*)pointer;
                                                  delete object;
                                                  value.Destroy();
                                                }
                                                break;

      case XFILEJSONVALUETYPE_ARRAY           : { void* pointer = value;
                                                  XFILEJSONARRAY* array = (XFILEJSONARRAY*)pointer;
                                                  delete array;
                                                  value.Destroy();
                                                }
                                                break;

    }  

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEJSONVALUE* XFILEJSONVALUE::Clone()
* @brief      Clone
* @ingroup    XUTILS
*
* @return     XFILEJSONVALUE* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEJSONVALUE* XFILEJSONVALUE::Clone()
{
  XFILEJSONVALUE* newvalue = new XFILEJSONVALUE();
  if(!newvalue) return NULL;  

  newvalue->SetType(type);
  newvalue->SetName(name->Get());

  (*newvalue->GetValue()) = value;

  return newvalue;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILEJSONVALUE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFILEJSONVALUE::Clean()
{
  type                  = XFILEJSONVALUETYPE_NULL;
  name                  = NULL;
}


#pragma endregion


#pragma region CLASS_XFILEJSONOBJECT


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEJSONOBJECT::XFILEJSONOBJECT()
* @brief      Constructor
* @ingroup    XUTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEJSONOBJECT::XFILEJSONOBJECT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEJSONOBJECT::~XFILEJSONOBJECT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEJSONOBJECT::~XFILEJSONOBJECT()
{
  DeleteAllValues();

  Clean();
}


bool XFILEJSONOBJECT::IsArray()
{
  return isarray;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILEJSONOBJECT::SetIsArray(bool isarray)
* @brief      SetIsArray
* @ingroup    XUTILS
*
* @param[in]  isarray : 
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFILEJSONOBJECT::SetIsArray(bool isarray)
{
  this->isarray = isarray;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEJSONOBJECT::Add(XFILEJSONVALUE* value)
* @brief      Add
* @ingroup    XUTILS
*
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSONOBJECT::Add(XFILEJSONVALUE* value)
{
  if(!value) return false;

  values.Add(value);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEJSONOBJECT::Add(XCHAR* name,XFILEJSONARRAY* array)
* @brief      Add
* @ingroup    XUTILS
*
* @param[in]  name :
* @param[in]  array :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSONOBJECT::Add(XCHAR* name, XFILEJSONARRAY* array)
{
  if(!array) return false;

  array->SetFather(this);

  XFILEJSONVALUE* value = new XFILEJSONVALUE();
  if(!value) return false;

  value->SetName(name);
  value->Set(array);

  values.Add(value);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEJSONOBJECT::Add(XSTRING& name,XFILEJSONARRAY* array)
* @brief      Add
* @ingroup    XUTILS
*
* @param[in]  name :
* @param[in]  array :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSONOBJECT::Add(XSTRING& name, XFILEJSONARRAY* array)
{
  return Add(name.Get(), array);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEJSONOBJECT::Add(XCHAR* name,XFILEJSONOBJECT* object)
* @brief      Add
* @ingroup    XUTILS
*
* @param[in]  name :
* @param[in]  object :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSONOBJECT::Add(XCHAR* name, XFILEJSONOBJECT* object)
{
  if(!object) return false;

  object->SetFather(this);

  XFILEJSONVALUE* value = new XFILEJSONVALUE();
  if(!value) return false;

  value->SetName(name);
  value->Set(object);

  values.Add(value);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEJSONOBJECT::Add(XSTRING& name, XFILEJSONOBJECT* object)
* @brief      Add
* @ingroup    XUTILS
*
* @param[in]  name :
* @param[in]  object :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSONOBJECT::Add(XSTRING& name, XFILEJSONOBJECT* object)
{
  return Add(name.Get(),object);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILEJSONOBJECT* XFILEJSONOBJECT::GetFather()
* @brief      GetFather
* @ingroup    XUTILS
* 
* @return     XFILEJSONOBJECT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XFILEJSONOBJECT* XFILEJSONOBJECT::GetFather()
{
  return father;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XFILEJSONOBJECT::SetFather(XFILEJSONOBJECT* father)
* @brief      SetFather
* @ingroup    XUTILS
* 
* @param[in]  father : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XFILEJSONOBJECT::SetFather(XFILEJSONOBJECT* father)
{
  this->father = father;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XVECTOR<XFILEJSONVALUE*>* XFILEJSONOBJECT::GetValues()
* @brief      GetValues
* @ingroup    XUTILS
*
* @return     XVECTOR<XFILEJSONVALUE*>* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<XFILEJSONVALUE*>* XFILEJSONOBJECT::GetValues()
{
  return &values;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEJSONOBJECT::DeleteAllValues()
* @brief      DeleteAllValues
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSONOBJECT::DeleteAllValues()
{
  if(values.IsEmpty())  return false;

  values.DeleteContents();
  values.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEJSONOBJECT* XFILEJSONOBJECT::Clone()
* @brief      Clone
* @ingroup    XUTILS
*
* @return     XFILEJSONOBJECT* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEJSONOBJECT* XFILEJSONOBJECT::Clone()
{
  XFILEJSONOBJECT* cloneobj = new XFILEJSONOBJECT();
  if(!cloneobj) return NULL;

  cloneobj->SetFather(father);
  cloneobj->SetIsArray(isarray);

  for(XDWORD c=0; c<GetValues()->GetSize(); c++)
    {      
      XFILEJSONVALUE* value    = GetValues()->Get(c); 
      XFILEJSONVALUE* newvalue = NULL;  
     
      if(value)
        {
          newvalue =  value->Clone();
          if(newvalue) cloneobj->Add(newvalue);
        }
    }

  return cloneobj;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILEJSONOBJECT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFILEJSONOBJECT::Clean()
{
  father  = NULL;
  isarray = false;
}


#pragma endregion


#pragma region CLASS_XFILEJSONARRAY


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILEJSONARRAY::XFILEJSONARRAY()
* @brief      Constructor
* @ingroup    XUTILS
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XFILEJSONARRAY::XFILEJSONARRAY() : XFILEJSONOBJECT()
{
  Clean();

  isarray = true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEJSONARRAY::~XFILEJSONARRAY()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEJSONARRAY::~XFILEJSONARRAY()
{
  DeleteAllValues();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* XFILEJSONARRAY::GetName()
* @brief      GetName
* @ingroup    XUTILS
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* XFILEJSONARRAY::GetName()
{
  return &name;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEJSONARRAY::SetName(XSTRING& name)
* @brief      SetName
* @ingroup    XUTILS
*
* @param[in]  name :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSONARRAY::SetName(XSTRING& name)
{
  this->name = name.Get();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEJSONARRAY::SetName(XCHAR* name)
* @brief      SetName
* @ingroup    XUTILS
*
* @param[in]  name :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSONARRAY::SetName(XCHAR* name)
{
  this->name = name;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILEJSONARRAY* XFILEJSONARRAY::Clone()
* @brief      Clone
* @ingroup    XUTILS
* 
* @return     XFILEJSONARRAY* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XFILEJSONARRAY* XFILEJSONARRAY::Clone()
{
  XFILEJSONARRAY* clonearray = new XFILEJSONARRAY();
  if(!clonearray) return NULL;

  clonearray->SetName(name.Get());

  return clonearray;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILEJSONARRAY::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFILEJSONARRAY::Clean()
{

};


#pragma endregion


#pragma region CLASS_XFILEJSON


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEJSON::XFILEJSON()
* @brief      Constructor
* @ingroup    XUTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEJSON::XFILEJSON(): XFILETXT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEJSON::~XFILEJSON()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEJSON::~XFILEJSON()
{
  DeleteAllLines();

  DeleteAllObjects();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEJSONOBJECT* XFILEJSON::GetRoot()
* @brief      GetRoot
* @ingroup    XUTILS
*
* @return     XFILEJSONOBJECT* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEJSONOBJECT* XFILEJSON::GetRoot()
{
  return root;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEJSON::SetRoot(XFILEJSONOBJECT* root)
* @brief      SetRoot
* @ingroup    XUTILS
*
* @param[in]  root :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSON::SetRoot(XFILEJSONOBJECT* root)
{
  DeleteAllObjects();

  this->root = root;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEJSON::DecodeAllLines()
* @brief      DecodeAllLines
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSON::DecodeAllLines()
{
  if(root) delete root;

  if(!GetAllInOneLine(all)) return false;

  DeleteAllLines();

  //--------------------------------------------------------
  // Search Object Root

  int positionbracket = 0;
  int positionbrace   = 0;
  int position        = 0;

  if(!SearchControlCharacter(XFILEJSONCONTROLCHAR_OPENBRACKET, positionbracket)) positionbracket = 100000000;
  if(!SearchControlCharacter(XFILEJSONCONTROLCHAR_OPENBRACE  , positionbrace))   positionbrace   = 100000000;

  if(positionbracket > positionbrace)  position = positionbrace + 1;  else position =  positionbracket;

  root = new XFILEJSONOBJECT();
  if(!root) return false;

  bool status = DecodeObject(position, true, root);

  all.Empty();

  if(!status)
    {
      delete root;
      root = NULL;
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEJSON::EncodeAllLines(bool istabulatedline)
* @brief      EncodeAllLines
* @ingroup    XUTILS
*
* @param[in]  istabulatedline :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSON::EncodeAllLines(bool istabulatedline)
{
  if(!root) return false;

  encodelevel  = 0;

  return EncodeObject(true, root, istabulatedline);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEJSON::ReadAndDecodeAllLines()
* @brief      ReadAndDecodeAllLines
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSON::ReadAndDecodeAllLines()
{
  if(!IsOpen())      return false;

  if(!ReadAllFile()) return false;

  return DecodeAllLines();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEJSON::WriteAndEncodeAllLines(bool istabulatedline,XFILETXTFORMATCHAR formatchar, XFILETXTTYPELF typeLF)
* @brief      WriteAndEncodeAllLines
* @ingroup    XUTILS
*
* @param[in]  istabulatedline :
* @param[in]  formatchar :
* @param[in]  typeLF :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSON::WriteAndEncodeAllLines(bool istabulatedline,XFILETXTFORMATCHAR formatchar, XFILETXTTYPELF typeLF)
{
  SetFormatChar(formatchar);
  SetTypeLF(typeLF);

  return WriteAndEncodeAllLines(istabulatedline);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEJSON::WriteAndEncodeAllLines(bool istabulatedline)
* @brief      WriteAndEncodeAllLines
* @ingroup    XUTILS
*
* @param[in]  istabulatedline :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSON::WriteAndEncodeAllLines(bool istabulatedline)
{
  if(!IsOpen()) return false;

  file->SetPosition(0);

  EncodeAllLines(istabulatedline);

  bool status = WriteAllFile();

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEJSON::DeleteAllObjects()
* @brief      DeleteAllObjects
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSON::DeleteAllObjects()
{
  if(!root) return false;

  delete root;

  root = NULL;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEJSONOBJECT* XFILEJSON::GetObject(XCHAR* name, XFILEJSONOBJECT* startobject)
* @brief      GetObject
* @ingroup    XUTILS
*
* @param[in]  name :
* @param[in]  startobject :
*
* @return     XFILEJSONOBJECT* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEJSONOBJECT* XFILEJSON::GetObject(XCHAR* name, XFILEJSONOBJECT* startobject)
{  
  XFILEJSONOBJECT* _startobject  = startobject?startobject:GetRoot();
  if(!_startobject)  return NULL;

  if(_startobject->IsArray())
    {
      XFILEJSONARRAY* array = (XFILEJSONARRAY*)(_startobject);
      if(!array) return NULL;

      if(!array->GetValues()) return NULL;

      for(int c=0; c<(int)array->GetValues()->GetSize();c++)
        {
          XFILEJSONVALUE* value = (XFILEJSONVALUE*)array->GetValues()->Get(c);
          if(value)
            {
              switch(value->GetType())
                {
                  case XFILEJSONVALUETYPE_OBJECT  :
                  case XFILEJSONVALUETYPE_ARRAY   : { XFILEJSONOBJECT* subobject = GetObjectSubValue(name, value);
                                                      if(subobject) return subobject;
                                                    }
                                                    break;
                                        default   : break;
                }
            }
        }
    }
   else
    {
      XFILEJSONOBJECT* object = _startobject;
      if(!object) return NULL;

      if(!object->GetValues()) return NULL;

      for(int c=0; c<(int)object->GetValues()->GetSize();c++)
        {
          XFILEJSONVALUE* value = (XFILEJSONVALUE*)object->GetValues()->Get(c);
          if(value)
            {
              switch(value->GetType())
                {
                  case XFILEJSONVALUETYPE_OBJECT  :
                  case XFILEJSONVALUETYPE_ARRAY   : { XFILEJSONOBJECT* subobject = GetObjectSubValue(name, value);
                                                      if(subobject) return subobject;
                                                    }
                                                    break;
                                        default   : break;
                }
            }
        }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILEJSONOBJECT* XFILEJSON::GetObject(XSTRING& name, XFILEJSONOBJECT* startobject)
* @brief      GetObject
* @ingroup    XUTILS
* 
* @param[in]  name : 
* @param[in]  startobject : 
* 
* @return     XFILEJSONOBJECT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XFILEJSONOBJECT* XFILEJSON::GetObject(XSTRING& name, XFILEJSONOBJECT* startobject)
{
  return GetObject(name.Get(), startobject);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEJSONVALUE* XFILEJSON::GetValue(XCHAR* name, XFILEJSONOBJECT* startobject)
* @brief      GetValue
* @ingroup    XUTILS
*
* @param[in]  name :
* @param[in]  startobject :
*
* @return     XFILEJSONVALUE* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEJSONVALUE* XFILEJSON::GetValue(XCHAR* name, XFILEJSONOBJECT* startobject)
{
  XFILEJSONOBJECT* object = startobject?startobject:GetRoot();
  if(!object) return NULL;

  if(!object->GetValues()) return NULL;

  for(int c=0; c<(int)object->GetValues()->GetSize();c++)
    {
      XFILEJSONVALUE* value = (XFILEJSONVALUE*)object->GetValues()->Get(c);
      if(value)
        {
          XFILEJSONVALUETYPE type = value->GetType();
          if((type == XFILEJSONVALUETYPE_OBJECT) || (type ==  XFILEJSONVALUETYPE_ARRAY))
            {
              value = GetValue(name, (XFILEJSONOBJECT*)value->GetValuePointer());
              if(value) return value;
            }
           else
            {
              if(value->GetName())
                {
                  if(!value->GetName()->Compare(name)) return value;
                }
            }
        }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEJSONVALUE* XFILEJSON::GetValue(XSTRING& name, XFILEJSONOBJECT* startobject)
* @brief      GetValue
* @ingroup    XUTILS
*
* @param[in]  name :
* @param[in]  startobject :
*
* @return     XFILEJSONVALUE* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEJSONVALUE* XFILEJSON::GetValue(XSTRING& name, XFILEJSONOBJECT* startobject)
{
  return GetValue(name.Get(), startobject);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILEJSONVALUE* XFILEJSON::GetValue(int index, XFILEJSONOBJECT* startobject)
* @brief      GetValue
* @ingroup    XUTILS
* 
* @param[in]  index : 
* @param[in]  startobject : 
* 
* @return     XFILEJSONVALUE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XFILEJSONVALUE* XFILEJSON::GetValue(int index, XFILEJSONOBJECT* startobject)
{
  XFILEJSONOBJECT* object = startobject?startobject:GetRoot();
  if(!object) return NULL;

  if(!object->GetValues()) return NULL;

  return (XFILEJSONVALUE*)object->GetValues()->Get(index);  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILEJSON::ShowTraceJSON(XBYTE color, bool istabulatedline, XFILETXTTYPELF typeLF)
* @brief      ShowTraceJSON
* @ingroup    XUTILS
* 
* @param[in]  color : 
* @param[in]  istabulatedline : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSON::ShowTraceJSON(XBYTE color, bool istabulatedline)
{
  DeleteAllLines();

  EncodeAllLines(istabulatedline);
  
  for(int c=0; c<GetNLines(); c++)
    {      
      XSTRING* line = GetLine(c);
      if(line) 
        {
          XTRACE_PRINTCOLOR(color, line->Get(), NULL);          
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEJSONOBJECT* XFILEJSON::GetObjectSubValue(XCHAR* name, XFILEJSONVALUE* value)
* @brief      GetObjectSubValue
* @ingroup    XUTILS
*
* @param[in]  name :
* @param[in]  value :
*
* @return     XFILEJSONOBJECT* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEJSONOBJECT* XFILEJSON::GetObjectSubValue(XCHAR* name, XFILEJSONVALUE* value)
{
  XFILEJSONVALUETYPE type = value->GetType();
  if(value->GetName())
    {
      if(!value->GetName()->Compare(name))
        {
          switch(type)
            {
              case XFILEJSONVALUETYPE_OBJECT  :
              case XFILEJSONVALUETYPE_ARRAY   : return (XFILEJSONOBJECT*)value->GetValuePointer();

                                    default   : return NULL;
          }
        }
    }

  switch(type)
    {
      case XFILEJSONVALUETYPE_OBJECT  : { XFILEJSONOBJECT* subobject = GetObject(name, (XFILEJSONOBJECT*)value->GetValuePointer());
                                          if(subobject) return subobject;
                                        }
                                        break;

      case XFILEJSONVALUETYPE_ARRAY   : { XFILEJSONARRAY* subarray = (XFILEJSONARRAY*)value->GetValuePointer();
                                          if(subarray)
                                            {
                                              for(XDWORD d=0; d<subarray->GetValues()->GetSize(); d++)
                                                {
                                                  XFILEJSONVALUE* subvalue = (XFILEJSONVALUE*)subarray->GetValues()->Get(d);
                                                  if(subvalue)
                                                    {
                                                      XFILEJSONOBJECT* subobject = GetObjectSubValue(name, subvalue);
                                                      if(subobject) return subobject;
                                                    }
                                                }
                                            }
                                        }
                                        break;

                            default   : return NULL;
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEJSON::DecodeObject(int& position, bool isobject, XFILEJSONOBJECT* object)
* @brief      DecodeObject
* @ingroup    XUTILS
*
* @param[in]  position :
* @param[in]  isobject :
* @param[in]  object :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSON::DecodeObject(int& position, bool isobject, XFILEJSONOBJECT* object)
{
  if(!object) return false;

  while(1)
    {
      XFILEJSONCONTROLCHAR ctrlchar;

      XFILEJSONVALUE* value = new XFILEJSONVALUE();
      if(!value) return false;

      if(isobject)
        {
          XSTRING name;
          int     checkposition = position;

          ctrlchar = SearchNextControlCharacter(checkposition);
          if(ctrlchar == XFILEJSONCONTROLCHAR_QUOTE)         
            {
              if(GetString(checkposition, name))
                {

                }

              position = checkposition;
            }

          value->SetName(name);

          if(!name.IsEmpty())
            {
              ctrlchar = SearchNextControlCharacter(position);
              if(ctrlchar == XFILEJSONCONTROLCHAR_NOTCONTROL)
                {
                  delete value;
                  return false;
                }

              position++;
            }
        }

      ctrlchar = SearchNextControlCharacter(position);
      switch(ctrlchar)
        {
          case XFILEJSONCONTROLCHAR_OPENBRACE     : { XFILEJSONOBJECT* newobject = new XFILEJSONOBJECT();
                                                      if(!object) return false;

                                                      value->Set(newobject);

                                                      position++;

                                                      if(!DecodeObject(position, true, newobject))
                                                        {
                                                          delete value;
                                                          return false;
                                                        }

                                                      object->GetValues()->Add(value);
                                                    }
                                                    break;

          case XFILEJSONCONTROLCHAR_OPENBRACKET   : { XFILEJSONARRAY* newarray = new XFILEJSONARRAY();
                                                      if(!object) return false;

                                                      value->Set(newarray);

                                                      position++;

                                                      if(!DecodeObject(position,false,(XFILEJSONOBJECT*)newarray))
                                                        {
                                                          delete value;
                                                          return false;
                                                        }

                                                      object->GetValues()->Add(value);
                                                    }
                                                    break;

          case XFILEJSONCONTROLCHAR_NUMBER        : { XSTRING valuestring;
                                                      bool    special = false;

                                                      GetNumber(position, valuestring, special);

                                                      if(!special)
                                                        {
                                                          int integer = 0;

                                                          valuestring.UnFormat(__L("%d"),&integer);
                                                          value->Set(integer);
                                                        }
                                                       else
                                                        {
                                                          double floating = 0.0f;

                                                          valuestring.UnFormat(__L("%f"), &floating);

                                                          value->Set((float)floating);
                                                        }

                                                      object->GetValues()->Add(value);
                                                    }
                                                    break;

          case XFILEJSONCONTROLCHAR_TEXT          : { XSTRING valuestring;

                                                      GetText(position, valuestring);

                                                      valuestring.ToUpperCase();
                                                      
                                                      value->Set();

                                                      if(!valuestring.Compare(__L("TRUE")))  value->Set(true);
                                                      if(!valuestring.Compare(__L("FALSE"))) value->Set(false);
                                                      
                                                      if(!valuestring.Compare(__L("null")))  value->Set();

                                                      object->GetValues()->Add(value);
                                                    }
                                                    break;

          case XFILEJSONCONTROLCHAR_QUOTE         : { XSTRING valuestring;

                                                      GetString(position,valuestring);

                                                      value->Set(valuestring);

                                                      object->GetValues()->Add(value);
                                                    }
                                                    break;

          case XFILEJSONCONTROLCHAR_CLOSEBRACE    :
          case XFILEJSONCONTROLCHAR_CLOSEBRACKET  : delete value;
                                                    break;

          case XFILEJSONCONTROLCHAR_NOTCONTROL    :
                                        default   : delete value;
                                                    return false;

        }


      ctrlchar = SearchNextControlCharacter(position);
      if(position != -1)
        {
          if(isobject)
            {
              if(ctrlchar==XFILEJSONCONTROLCHAR_CLOSEBRACE)
                {
                  position++;
                  break;
                }
               else
                {
                  if(ctrlchar == XFILEJSONCONTROLCHAR_NOTCONTROL)
                    {
                      return false;
                    }
                }
            }
           else
            {
              if(ctrlchar==XFILEJSONCONTROLCHAR_CLOSEBRACKET)
                {
                  position++;
                  break;
                }
               else
                {
                  if(ctrlchar == XFILEJSONCONTROLCHAR_NOTCONTROL)
                    {
                      return false;
                    }
                }
            }

          ctrlchar = SearchNextControlCharacter(position);
          if(ctrlchar!=XFILEJSONCONTROLCHAR_COMMA)
            {
              return false;
            }
           else
            {
              //-----------------------------------
              // COMMA is ADD to end (BAD JSON format)

              position++;

              ctrlchar = SearchNextControlCharacter(position);
              if(isobject)
                {
                  if(ctrlchar==XFILEJSONCONTROLCHAR_CLOSEBRACE)
                    {
                      position++;
                      break;
                    }
                   else
                    {
                      if(ctrlchar == XFILEJSONCONTROLCHAR_NOTCONTROL)
                        {
                          return false;
                        }
                    }
                }
               else
                {
                  if(ctrlchar==XFILEJSONCONTROLCHAR_CLOSEBRACKET)
                    {
                      position++;
                      break;
                    }
                   else
                    {
                      if(ctrlchar == XFILEJSONCONTROLCHAR_NOTCONTROL)
                        {
                          return false;
                        }
                    }
                }
            }
        }
       else
        {
          break;
        }
    }

  //XTRACE_PRINTCOLOR(2, __L("%d"), position);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEJSONCONTROLCHAR XFILEJSON::CheckControlCharacter(XCHAR character)
* @brief      CheckControlCharacter
* @ingroup    XUTILS
*
* @param[in]  character :
*
* @return     XFILEJSONCONTROLCHAR :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEJSONCONTROLCHAR XFILEJSON::CheckControlCharacter(XCHAR character)
{
  XFILEJSONCONTROLCHAR ctrlchar;

  switch(character)
    {
      case __C('{')  : ctrlchar = XFILEJSONCONTROLCHAR_OPENBRACE;     break;
      case __C('}')  : ctrlchar = XFILEJSONCONTROLCHAR_CLOSEBRACE;    break;
      case __C('[')  : ctrlchar = XFILEJSONCONTROLCHAR_OPENBRACKET;   break;
      case __C(']')  : ctrlchar = XFILEJSONCONTROLCHAR_CLOSEBRACKET;  break;
      case __C('\"') : ctrlchar = XFILEJSONCONTROLCHAR_QUOTE;         break;
      case __C(',')  : ctrlchar = XFILEJSONCONTROLCHAR_COMMA;         break;
      case __C(':')  : ctrlchar = XFILEJSONCONTROLCHAR_COLON;         break;
      case __C('\\') : ctrlchar = XFILEJSONCONTROLCHAR_BLACKSLASH;    break;

      case __C('0')  :
      case __C('1')  :
      case __C('2')  :
      case __C('3')  :
      case __C('4')  :
      case __C('5')  :
      case __C('6')  :
      case __C('7')  :
      case __C('8')  :
      case __C('9')  :
      case __C('-')  : ctrlchar = XFILEJSONCONTROLCHAR_NUMBER;        break;

      case __C('.')  :
      case __C('+')  :
      case __C('e')  :
      case __C('E')  : ctrlchar = XFILEJSONCONTROLCHAR_NUMBERSPECIAL; break;

      case __C('\t') :
      case __C('\r') :
      case __C('\n') :
      case __C(' ')  : ctrlchar = XFILEJSONCONTROLCHAR_NOTCONTROL;    break;

           default   : ctrlchar = XFILEJSONCONTROLCHAR_TEXT;          break;
    }

  return ctrlchar;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XCHAR XFILEJSON::GetControlCharacter(XFILEJSONCONTROLCHAR ctrlchar)
* @brief      GetControlCharacter
* @ingroup    XUTILS
*
* @param[in]  ctrlchar :
*
* @return     XCHAR :
*
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR XFILEJSON::GetControlCharacter(XFILEJSONCONTROLCHAR ctrlchar)
{
  switch(ctrlchar)
    {
      case XFILEJSONCONTROLCHAR_OPENBRACE     : return __C('{');
      case XFILEJSONCONTROLCHAR_CLOSEBRACE    : return __C('}');
      case XFILEJSONCONTROLCHAR_OPENBRACKET   : return __C('[');
      case XFILEJSONCONTROLCHAR_CLOSEBRACKET  : return __C(']');
      case XFILEJSONCONTROLCHAR_QUOTE         : return __C('\"');
      case XFILEJSONCONTROLCHAR_COMMA         : return __C(',');
      case XFILEJSONCONTROLCHAR_COLON         : return __C(':');
      case XFILEJSONCONTROLCHAR_BLACKSLASH    : return __C('\\');
                                     default  : break;
    }

  return 0;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEJSON::AddControlCharacter(XFILEJSONCONTROLCHAR ctrlchar, XSTRING& line)
* @brief      AddControlCharacter
* @ingroup    XUTILS
*
* @param[in]  ctrlchar :
* @param[in]  line :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSON::AddControlCharacter(XFILEJSONCONTROLCHAR ctrlchar, XSTRING& line)
{
  XCHAR character = GetControlCharacter(ctrlchar);
  if(character)
    {
      line += character;
      return true;
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEJSONCONTROLCHAR XFILEJSON::SearchNextControlCharacter(int& position)
* @brief      SearchNextControlCharacter
* @ingroup    XUTILS
*
* @param[in]  position :
*
* @return     XFILEJSONCONTROLCHAR :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEJSONCONTROLCHAR XFILEJSON::SearchNextControlCharacter(int& position)
{
  for(int c=position;c<(int)all.GetSize();c++)
    {
      XFILEJSONCONTROLCHAR ctrlchar;

      ctrlchar = CheckControlCharacter(all.Get()[c]);
      if(ctrlchar != XFILEJSONCONTROLCHAR_NOTCONTROL)
        {
          position = c;
          return ctrlchar;
        }
    }

  position = XSTRING_NOTFOUND;

  return XFILEJSONCONTROLCHAR_NOTCONTROL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEJSON::SearchControlCharacter(XFILEJSONCONTROLCHAR ctrlchar,int& position)
* @brief      SearchControlCharacter
* @ingroup    XUTILS
*
* @param[in]  ctrlchar :
* @param[in]  position :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSON::SearchControlCharacter(XFILEJSONCONTROLCHAR ctrlchar, int& position)
{
  for(int c=position;c<(int)all.GetSize();c++)
    {
      XFILEJSONCONTROLCHAR _ctrlchar;

      _ctrlchar = CheckControlCharacter(all.Get()[c]);
      if(_ctrlchar == ctrlchar)
        {
          position = c;
          return true;
        }
    }

  position = XSTRING_NOTFOUND;
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEJSON::GetNumber(int& position,XSTRING& string,bool& special)
* @brief      GetNumber
* @ingroup    XUTILS
*
* @param[in]  position :
* @param[in]  string :
* @param[in]  special :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSON::GetNumber(int& position, XSTRING& string, bool& special)
{
  string.Empty();

  special = false;

  for(int c=position;c<(int)all.GetSize();c++)
    {
      XFILEJSONCONTROLCHAR ctrlchar;

      ctrlchar = CheckControlCharacter(all.Get()[c]);
      if((ctrlchar == XFILEJSONCONTROLCHAR_NUMBER)||(ctrlchar == XFILEJSONCONTROLCHAR_NUMBERSPECIAL))
        {
          string += all.Get()[c];
          if(ctrlchar == XFILEJSONCONTROLCHAR_NUMBERSPECIAL) special = true;

        }
       else
        {
          position = c;
          break;
        }
    }

  return string.IsEmpty()?false:true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEJSON::GetText(int& position,XSTRING& string)
* @brief      GetText
* @ingroup    XUTILS
*
* @param[in]  position :
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSON::GetText(int& position, XSTRING& string)
{
  string.Empty();

  for(int c=position;c<(int)all.GetSize();c++)
    {
      XFILEJSONCONTROLCHAR ctrlchar;

      ctrlchar = CheckControlCharacter(all.Get()[c]);
      if((ctrlchar == XFILEJSONCONTROLCHAR_TEXT) ||(ctrlchar == XFILEJSONCONTROLCHAR_NUMBERSPECIAL))
        {
          string += all.Get()[c];
        }
       else
        {
          position = c;
          break;
        }
    }

  return string.IsEmpty()?false:true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEJSON::GetString(int& position, XSTRING& string)
* @brief      GetString
* @ingroup    XUTILS
*
* @param[in]  position :
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSON::GetString(int& position, XSTRING& string)
{
  string.Empty();

  XFILEJSONCONTROLCHAR ctrlchar;

  //----------------------------------
  // First Quote
  ctrlchar = CheckControlCharacter(all.Get()[position]);
  if(ctrlchar != XFILEJSONCONTROLCHAR_QUOTE) return false;

  position++;

  bool slashcontrol = false;
  bool exit         = false;

  for(int c=position;c<(int)all.GetSize();c++)
    {
      ctrlchar = CheckControlCharacter(all.Get()[c]);

      switch(ctrlchar)
        {
          case XFILEJSONCONTROLCHAR_NOTCONTROL    :
          case XFILEJSONCONTROLCHAR_OPENBRACE     :
          case XFILEJSONCONTROLCHAR_CLOSEBRACE    :
          case XFILEJSONCONTROLCHAR_OPENBRACKET   :
          case XFILEJSONCONTROLCHAR_CLOSEBRACKET  :
          case XFILEJSONCONTROLCHAR_COMMA         :
          case XFILEJSONCONTROLCHAR_COLON         :
          case XFILEJSONCONTROLCHAR_NUMBER        :
          case XFILEJSONCONTROLCHAR_NUMBERSPECIAL :
          case XFILEJSONCONTROLCHAR_TEXT          : string += all.Get()[c];
                                                    slashcontrol = false;
                                                    break;

          case XFILEJSONCONTROLCHAR_QUOTE         : if(slashcontrol)
                                                      {
                                                        string += all.Get()[c];
                                                        slashcontrol = false;

                                                      }
                                                     else exit = true;
                                                    break;

          case XFILEJSONCONTROLCHAR_BLACKSLASH    : slashcontrol = true;
                                                    string += all.Get()[c];
                                                    break;
        }

      if(exit)
        {
          position = (c + 1);
          break;
        }
    }

  return string.IsEmpty()?false:true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEJSON::AddTabs(int level, int spacetabs, XSTRING& string)
* @brief      AddTabs
* @ingroup    XUTILS
*
* @param[in]  level :
* @param[in]  spacetabs :
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSON::AddTabs(int level, int spacetabs, XSTRING& string)
{
  if(spacetabs<=0) return false;

  for(int c=0;c<level;c++)
    {
      for(int d=0;d<spacetabs;d++)
        {
          string += __L(" ");
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEJSON::EncodeObject(bool isobject, XFILEJSONOBJECT* object, bool istabulatedline)
* @brief      EncodeObject
* @ingroup    XUTILS
*
* @param[in]  isobject :
* @param[in]  object :
* @param[in]  istabulatedline :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEJSON::EncodeObject(bool isobject, XFILEJSONOBJECT* object, bool istabulatedline)
{
  if(!object) return false;

  XSTRING line;

  if(istabulatedline)
    {
      AddTabs(encodelevel,XFILEJSON_SPACETABS,line);
      encodelevel++;
    }

  AddControlCharacter(isobject?XFILEJSONCONTROLCHAR_OPENBRACE:XFILEJSONCONTROLCHAR_OPENBRACKET, line);
  AddLine(line);
  //XTRACE_PRINTCOLOR(0,line.Get());

  for(int c=0;c<(int)object->GetValues()->GetSize();c++)
    {
      XFILEJSONVALUE* value = (XFILEJSONVALUE*)(object->GetValues()->Get(c));
      if(value)
        {
          line.Empty();
          AddTabs(encodelevel, XFILEJSON_SPACETABS, line);

          XSTRING* name = value->GetName();
          if(name)
            {
              if(!name->IsEmpty())
                {
                  XSTRING line2;

                  line2.Format(__L("%c%s%c : "), GetControlCharacter(XFILEJSONCONTROLCHAR_QUOTE), name->Get() , GetControlCharacter(XFILEJSONCONTROLCHAR_QUOTE));
                  line+=line2;
                }
            }
    
          switch(value->GetType())
            {              
              case XFILEJSONVALUETYPE_NULL            : line += __L("null");
                                                        break;



              case XFILEJSONVALUETYPE_STRING          : { XSTRING  ptrvaluestring = value->GetValueString();
                                                          XSTRING  valuestring;
                                                         
                                                          valuestring.Format(__L("%c%s%c"), GetControlCharacter(XFILEJSONCONTROLCHAR_QUOTE), ptrvaluestring.Get(), GetControlCharacter(XFILEJSONCONTROLCHAR_QUOTE));
                                                          line += valuestring.Get();
                                                        }
                                                        break;              

              case XFILEJSONVALUETYPE_OBJECT          : { XFILEJSONOBJECT* newobject = (XFILEJSONOBJECT*)(value->GetValuePointer());
                                                          if(newobject)
                                                            {
                                                              if((!line.IsEmpty()) && line.HaveCharacters())
                                                                {
                                                                  AddLine(line);
                                                                  //XTRACE_PRINTCOLOR(0,line.Get());
                                                                }

                                                              if(!EncodeObject(true,newobject,istabulatedline)) return false;
                                                              line.Empty();
                                                            }
                                                        }
                                                        break;

              case XFILEJSONVALUETYPE_ARRAY           : { XFILEJSONARRAY* newarray = (XFILEJSONARRAY*)(value->GetValuePointer());
                                                          if(newarray)
                                                            {
                                                              if((!line.IsEmpty()) && line.HaveCharacters())
                                                                {
                                                                  AddLine(line);
                                                                  //XTRACE_PRINTCOLOR(0,line.Get());
                                                                }

                                                              if(!EncodeObject(false,(XFILEJSONOBJECT*)newarray,istabulatedline)) return false;
                                                              line.Empty();
                                                            }
                                                        }
                                                        break;  

                                    default           : { XSTRING valuestring;

                                                          value->GetValue()->ToString(valuestring);

                                                          line += valuestring.Get();   
                                                        }
                                                        break;  
        
            }
        }

      if(c!=(int)(object->GetValues()->GetSize()-1))
        {
          if(line.IsEmpty()) AddTabs(encodelevel,XFILEJSON_SPACETABS,line);

          AddControlCharacter(XFILEJSONCONTROLCHAR_COMMA, line);
        }

      if(!line.IsEmpty())
        {
          AddLine(line);
          //XTRACE_PRINTCOLOR(0,line.Get());
        }

      line.Empty();
    }

  line.Empty();

  if(istabulatedline)
    {
      encodelevel--;
      AddTabs(encodelevel,XFILEJSON_SPACETABS,line);
    }

  AddControlCharacter(isobject?XFILEJSONCONTROLCHAR_CLOSEBRACE:XFILEJSONCONTROLCHAR_CLOSEBRACKET, line);
  AddLine(line);

  //XTRACE_PRINTCOLOR(0,line.Get());

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILEJSON::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFILEJSON::Clean()
{
   root         = NULL;
   encodelevel  = 0;
}


#pragma endregion


#pragma endregion



