/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XSerializationMethodJSON.cpp
* 
* @class      XSERIALIZATIONMETHODJSON
* @brief      eXtended Serialization method JSON class
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

#include "XSerializationMethodJSON.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSERIALIZATIONMETHODJSON::XSERIALIZATIONMETHODJSON()
* @brief      Constructor
* @ingroup    XUTILS
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSERIALIZATIONMETHODJSON::XSERIALIZATIONMETHODJSON()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSERIALIZATIONMETHODJSON::~XSERIALIZATIONMETHODJSON()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
* 
* @return     Does not return anything. 
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
* @param[in]  long var : 
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
* @brief      AddStruct
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
* @brief      AddArray
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
* @fn         bool XSERIALIZATIONMETHODJSON::Extract(bool var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Extract(bool var, XCHAR* name)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Extract(char var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Extract(char var, XCHAR* name)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Extract(int var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Extract(int var, XCHAR* name)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Extract(float var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Extract(float var, XCHAR* name)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Extract(double var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Extract(double var, XCHAR* name)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Extract(long var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Extract(long var, XCHAR* name)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Extract(long long var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  long var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Extract(long long var, XCHAR* name)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Extract(XBYTE var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Extract(XBYTE var, XCHAR* name)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Extract(XWORD var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Extract(XWORD var, XCHAR* name)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Extract(XDWORD var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Extract(XDWORD var, XCHAR* name)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Extract(XQWORD var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Extract(XQWORD var, XCHAR* name)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  return true;
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Extract(XSTRING* var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Extract(XSTRING* var, XCHAR* name)
{
  if(!CheckHandleActive()) 
    {
      return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Extract(XBUFFER* var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Extract(XBUFFER* var, XCHAR* name)
{ 
  if(!CheckHandleActive()) 
    {
      return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::Extract(XVARIANT* var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODJSON::Extract(XVARIANT* var, XCHAR* name)
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
* @brief      ExtractStruct
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
* @brief      ExtractArray
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
* @brief      GetFileJSON
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
* @brief      SetFileJSON
* @ingroup    XUTILS
* 
* @param[in]  fileJSON : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XSERIALIZATIONMETHODJSON::SetFileJSON(XFILEJSON* fileJSON)
{
  this->fileJSON = fileJSON;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILEJSONOBJECT* XSERIALIZATIONMETHODJSON::GetActualObject()
* @brief      GetActualObject
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
* @brief      SetActualObject
* @ingroup    XUTILS
* 
* @param[in]  actualobject : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XSERIALIZATIONMETHODJSON::SetActualObject(XFILEJSONOBJECT* actualobject)
{
  this->actualobject = actualobject;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODJSON::CheckHandleActive()
* @brief      CheckHandleActive
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
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XSERIALIZATIONMETHODJSON::Clean()
{
  fileJSON      = NULL;

  fathers.DeleteAll();

  actualobject  = NULL;
}
