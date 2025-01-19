/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XSerializationMethodJSON.cpp
* 
* @class      XSERIALIZATIONMETHODJSON
* @brief      eXtended Utils Serializable method JSON class
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

#include "XSerializationMethodJSON.h"

#include <stdio.h>
#include <string.h>

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


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSERIALIZATIONMETHODJSON::XSERIALIZATIONMETHODJSON()
* @brief      Constructor of class
* @ingroup    XUTILS
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSERIALIZATIONMETHODJSON::XSERIALIZATIONMETHODJSON()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSERIALIZATIONMETHODJSON::~XSERIALIZATIONMETHODJSON()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    XUTILS
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSERIALIZATIONMETHODJSON::~XSERIALIZATIONMETHODJSON()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Add(bool var, XCHAR* name)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Add(bool var, XCHAR* name)
{
  if(!fileJSON) 
    {
      return false;
    }

  XFILEJSON_ADDVALUE(GetActualObject(), name, (bool)var);
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Add(char var, XCHAR* name)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Add(char var, XCHAR* name)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  XFILEJSON_ADDVALUE(GetActualObject(), name, (char)var);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Add(int var, XCHAR* name)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Add(int var, XCHAR* name)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  XFILEJSON_ADDVALUE(GetActualObject(), name, (int)var);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Add(float var, XCHAR* name)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Add(float var, XCHAR* name)  
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  XFILEJSON_ADDVALUE(GetActualObject(), name, (float)var);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Add(double var, XCHAR* name)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Add(double var, XCHAR* name) 
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  XFILEJSON_ADDVALUE(GetActualObject(), name, (double)var);
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Add(long long var, XCHAR* name)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Add(long long var, XCHAR* name) 
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  XFILEJSON_ADDVALUE(GetActualObject(), name, (long long)var);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Add(XBYTE var, XCHAR* name)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Add(XBYTE var, XCHAR* name)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  XFILEJSON_ADDVALUE(GetActualObject(), name, (XBYTE)var);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Add(XWORD var, XCHAR* name)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Add(XWORD var, XCHAR* name)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  XFILEJSON_ADDVALUE(GetActualObject(), name, (XWORD)var);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Add(XDWORD var, XCHAR* name)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Add(XDWORD var, XCHAR* name)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  XFILEJSON_ADDVALUE(GetActualObject(), name, (XDWORD)var);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Add(XQWORD var, XCHAR* name)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Add(XQWORD var, XCHAR* name)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  XFILEJSON_ADDVALUE(GetActualObject(), name, (XQWORD)var);

  return true;
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Add(XSTRING* var, XCHAR* name)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Add(XSTRING* var, XCHAR* name)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  XFILEJSON_ADDVALUE(GetActualObject(), name, (XCHAR*)var->Get());

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Add(XBUFFER* var, XCHAR* name)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Add(XBUFFER* var, XCHAR* name)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  //XFILEJSON_ADDVALUE(GetActualObject(), name, (XBYTE*)var.Get());

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Add(XVARIANT* var, XCHAR* name)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Add(XVARIANT* var, XCHAR* name)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  XFILEJSON_ADDVALUE(GetActualObject(), name, (XVARIANT*)(var));

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::AddStruct(XCHAR* name, bool open)
* @brief      Add struct
* @ingroup    XUTILS
* 
* @param[in]  name : 
* @param[in]  open : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::AddStruct(XCHAR* name, bool open)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  if(open)
    {
      XFILEJSONOBJECT* structnode =  new XFILEJSONOBJECT();
      if(!structnode)
        {
          return false;
        }

      fathers.Add(GetActualObject());      
      SetActualObject(structnode);
    }
   else
    {
      fathers.GetLast()->Add(name, (XFILEJSONOBJECT*)GetActualObject());  
      SetActualObject(fathers.GetLast());      
      fathers.DeleteLast();
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::AddArray(XDWORD nelements, XCHAR* name, bool open)
* @brief      Add array
* @ingroup    XUTILS
* 
* @param[in]  nelements : 
* @param[in]  name : 
* @param[in]  open : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::AddArray(XDWORD nelements, XCHAR* name, bool open)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }  

  if(open)
    {
      XFILEJSONARRAY* arraynode =  new XFILEJSONARRAY();
      if(!arraynode)
        {
          return false;
        }

      fathers.Add(GetActualObject());      
      SetActualObject(arraynode);
    }
   else
    {
      fathers.GetLast()->Add(name, (XFILEJSONARRAY*)GetActualObject());  
      SetActualObject(fathers.GetLast());      
      fathers.DeleteLast();
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Extract(bool& var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Extract(bool& var, XCHAR* name)
{ 
  if(!CheckHandleActive()) 
    {
      return false;
    }

  XFILEJSONVALUE* jsonvalue = fileJSON->GetValue(name);
  if(jsonvalue)
    {
      var = jsonvalue->GetValueBoolean();
      return true;  
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Extract(char& var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Extract(char& var, XCHAR* name)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  XFILEJSONVALUE* jsonvalue = fileJSON->GetValue(name);
  if(jsonvalue)
    {
      var = (char)jsonvalue->GetValueDWord();
      return true;  
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Extract(int& var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Extract(int& var, XCHAR* name)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  XFILEJSONVALUE* jsonvalue = fileJSON->GetValue(name);
  if(jsonvalue)
    {
      var = jsonvalue->GetValueInteger();
      return true;  
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Extract(float& var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Extract(float& var, XCHAR* name)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  XFILEJSONVALUE* jsonvalue = fileJSON->GetValue(name);
  if(jsonvalue)
    {
      var = jsonvalue->GetValueFloating();
      return true;  
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Extract(double& var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Extract(double& var, XCHAR* name)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  XFILEJSONVALUE* jsonvalue = fileJSON->GetValue(name);
  if(jsonvalue)
    {
      var = jsonvalue->GetValueDoubleFloat();
      return true;  
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Extract(long& var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Extract(long& var, XCHAR* name)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  XFILEJSONVALUE* jsonvalue = fileJSON->GetValue(name);
  if(jsonvalue)
    {
      var = jsonvalue->GetValueInteger();
      return true;  
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Extract(long long& var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Extract(long long& var, XCHAR* name)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  XFILEJSONVALUE* jsonvalue = fileJSON->GetValue(name);
  if(jsonvalue)
    {
      var = jsonvalue->GetValueDoubleInteger();
      return true;  
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Extract(XBYTE& var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Extract(XBYTE& var, XCHAR* name)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  XFILEJSONVALUE* jsonvalue = fileJSON->GetValue(name);
  if(jsonvalue)
    {
      var = (XBYTE)jsonvalue->GetValueDWord();
      return true;  
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Extract(XWORD& var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Extract(XWORD& var, XCHAR* name)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  XFILEJSONVALUE* jsonvalue = fileJSON->GetValue(name);
  if(jsonvalue)
    {
      var = jsonvalue->GetValueWord();
      return true;  
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Extract(XDWORD& var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Extract(XDWORD& var, XCHAR* name)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  XFILEJSONVALUE* jsonvalue = fileJSON->GetValue(name);
  if(jsonvalue)
    {
      var = jsonvalue->GetValueDWord();
      return true;  
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Extract(XQWORD& var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Extract(XQWORD& var, XCHAR* name)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  XFILEJSONVALUE* jsonvalue = fileJSON->GetValue(name);
  if(jsonvalue)
    {
      var = jsonvalue->GetValueQWord();
      return true;  
    }

  return true;
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Extract(XSTRING& var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Extract(XSTRING& var, XCHAR* name)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  XFILEJSONVALUE* jsonvalue = fileJSON->GetValue(name);
  if(jsonvalue)
    {
      var = jsonvalue->GetValueString();
      return true;  
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Extract(XBUFFER& var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Extract(XBUFFER& var, XCHAR* name)
{ 
  if(!CheckHandleActive()) 
    {
      return false;
    }

  XFILEJSONVALUE* jsonvalue = fileJSON->GetValue(name);
  if(jsonvalue)
    {
      //var = jsonvalue->
      return true;  
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Extract(XVARIANT& var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Extract(XVARIANT& var, XCHAR* name)
{ 
  if(!CheckHandleActive()) 
    {
      return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::ExtractStruct(XCHAR* name)
* @brief      Extract struct
* @ingroup    XUTILS
* 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::ExtractStruct(XCHAR* name)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::ExtractArray(XDWORD nelements, XCHAR* name)
* @brief      Extract array
* @ingroup    XUTILS
* 
* @param[in]  nelements : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::ExtractArray(XDWORD nelements, XCHAR* name)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILEJSON* XSERIALIZATIONMETHODJSON::GetFileJSON()
* @brief      Get file JSON
* @ingroup    XUTILS
* 
* @return     XFILEJSON* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XFILEJSON* XSERIALIZATIONMETHODJSON::GetFileJSON()
{
  return fileJSON;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XSERIALIZATIONMETHODJSON::SetFileJSON(XFILEJSON* fileJSON)
* @brief      Set file JSON
* @ingroup    XUTILS
* 
* @param[in]  fileJSON : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XSERIALIZATIONMETHODJSON::SetFileJSON(XFILEJSON* fileJSON)
{
  this->fileJSON = fileJSON;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILEJSONOBJECT* XSERIALIZATIONMETHODJSON::GetActualObject()
* @brief      Get actual object
* @ingroup    XUTILS
* 
* @return     XFILEJSONOBJECT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XFILEJSONOBJECT* XSERIALIZATIONMETHODJSON::GetActualObject()
{
  return actualobject;
}
    
    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XSERIALIZATIONMETHODJSON::SetActualObject(XFILEJSONOBJECT* actualobject)
* @brief      Set actual object
* @ingroup    XUTILS
* 
* @param[in]  actualobject : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XSERIALIZATIONMETHODJSON::SetActualObject(XFILEJSONOBJECT* actualobject)
{
  this->actualobject = actualobject;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::CheckHandleActive()
* @brief      Check handle active
* @ingroup    XUTILS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::CheckHandleActive()
{
  if(!fileJSON)
    {
      return false;
    }

  if(!actualobject)
    {
      return false;    
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XSERIALIZATIONMETHODJSON::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    XUTILS
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XSERIALIZATIONMETHODJSON::Clean()
{
  fileJSON      = NULL;

  fathers.DeleteAll();

  actualobject  = NULL;
}


#pragma endregion

