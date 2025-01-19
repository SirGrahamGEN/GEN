/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XSerializationMethodBinary.cpp
* 
* @class      XSERIALIZATIONMETHODBINARY
* @brief      eXtended Utils Serialization binary class
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

#include "XSerializationMethodBinary.h"

#include <stdio.h>
#include <string.h>

#include "XBuffer.h"

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
* @fn         XSERIALIZATIONMETHODBINARY::XSERIALIZATIONMETHODBINARY()
* @brief      Constructor of class
* @ingroup    XUTILS
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSERIALIZATIONMETHODBINARY::XSERIALIZATIONMETHODBINARY()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSERIALIZATIONMETHODBINARY::~XSERIALIZATIONMETHODBINARY()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    XUTILS
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSERIALIZATIONMETHODBINARY::~XSERIALIZATIONMETHODBINARY()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Add(bool var, XCHAR* name)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Add(bool var, XCHAR* name)
{
  if(!bufferdata) 
    {
      return false;
    }
 
  bufferdata->Add((XBYTE)XSERIALIZATIONMETHODBINARY_TYPEELEMENT_BOOLEAN);   
  bufferdata->Add(var);  

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Add(char var, XCHAR* name)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Add(char var, XCHAR* name)
{
  if(!bufferdata) 
    {
      return false;
    }

  bufferdata->Add((XBYTE)XSERIALIZATIONMETHODBINARY_TYPEELEMENT_CHAR);
  bufferdata->Add((XBYTE)var); 

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Add(int var, XCHAR* name)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Add(int var, XCHAR* name)
{
  if(!bufferdata) 
    {
      return false;
    }
  
  bufferdata->Add((XBYTE)XSERIALIZATIONMETHODBINARY_TYPEELEMENT_INTEGER);
  bufferdata->Add((XDWORD)var); 

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Add(float var, XCHAR* name)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Add(float var, XCHAR* name)  
{
  if(!bufferdata) 
    {
      return false;
    }

  bufferdata->Add((XBYTE)XSERIALIZATIONMETHODBINARY_TYPEELEMENT_FLOAT);
  bufferdata->Add((float)var); 

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Add(double var, XCHAR* name)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Add(double var, XCHAR* name) 
{
  if(!bufferdata) 
    {
      return false;
    }

  bufferdata->Add((XBYTE)XSERIALIZATIONMETHODBINARY_TYPEELEMENT_DOUBLE);
  bufferdata->Add((double)var); 

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Add(long var, XCHAR* name)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Add(long var, XCHAR* name) 
{
  if(!bufferdata) 
    {
      return false;
    }

  bufferdata->Add((XBYTE)XSERIALIZATIONMETHODBINARY_TYPEELEMENT_LONG);
  bufferdata->Add((XDWORD)var); 
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Add(long long var, XCHAR* name)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Add(long long var, XCHAR* name) 
{
  if(!bufferdata) 
    {
      return false;
    }

  bufferdata->Add((XBYTE)XSERIALIZATIONMETHODBINARY_TYPEELEMENT_LONGLONG);
  bufferdata->Add((XQWORD)var); 

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Add(XBYTE var, XCHAR* name)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Add(XBYTE var, XCHAR* name)
{
  if(!bufferdata) 
    {
      return false;
    }
 
  bufferdata->Add((XBYTE)XSERIALIZATIONMETHODBINARY_TYPEELEMENT_XBYTE);
  bufferdata->Add(var); 

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Add(XWORD var, XCHAR* name)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Add(XWORD var, XCHAR* name)
{
  if(!bufferdata) 
    {
      return false;
    }

  bufferdata->Add((XBYTE)XSERIALIZATIONMETHODBINARY_TYPEELEMENT_XWORD);
  bufferdata->Add((XWORD)var); 

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Add(XDWORD var, XCHAR* name)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Add(XDWORD var, XCHAR* name)
{
  if(!bufferdata) 
    {
      return false;
    }
    
  bufferdata->Add((XBYTE)XSERIALIZATIONMETHODBINARY_TYPEELEMENT_XDWORD);  
  bufferdata->Add((XDWORD)var); 

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Add(XQWORD var, XCHAR* name)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Add(XQWORD var, XCHAR* name)
{
  if(!bufferdata) 
    {
      return false;
    }

  bufferdata->Add((XBYTE)XSERIALIZATIONMETHODBINARY_TYPEELEMENT_XQWORD);  
  bufferdata->Add((XQWORD)var); 

  return true;
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Add(XSTRING* var, XCHAR* name)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Add(XSTRING* var, XCHAR* name)
{
  if(!bufferdata) 
    {
      return false;
    }

  bufferdata->Add((XBYTE)XSERIALIZATIONMETHODBINARY_TYPEELEMENT_XSTRING);
  
  XBUFFER buffer;
  
  var->ConvertToXBuffer(buffer);

  bufferdata->Add(buffer); 

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Add(XBUFFER* var, XCHAR* name)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Add(XBUFFER* var, XCHAR* name)
{
  bufferdata->Add((XBYTE)XSERIALIZATIONMETHODBINARY_TYPEELEMENT_XBUFFER);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Add(XVARIANT* var, XCHAR* name)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Add(XVARIANT* var, XCHAR* name)
{ 
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::AddStruct(XCHAR* name, bool open)
* @brief      Add struct
* @ingroup    XUTILS
* 
* @param[in]  name : 
* @param[in]  open : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::AddStruct(XCHAR* name, bool open)
{
  if(!bufferdata) 
    {
      return false;
    }
  
  bufferdata->Add((XWORD)XSERIALIZATIONMETHOD_STRUCT_ID); 
  
  return true;
}
   

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::AddArray(XDWORD nelements, XCHAR* name, bool open)
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
bool XSERIALIZATIONMETHODBINARY::AddArray(XDWORD nelements, XCHAR* name, bool open)
{
  if(!bufferdata) 
    {
      return false;
    }
  
  bufferdata->Add((XWORD)XSERIALIZATIONMETHOD_ARRAY_ID); 
  bufferdata->Add((XDWORD)nelements); 

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Extract(bool var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Extract(bool var, XCHAR* name)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Extract(char var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Extract(char var, XCHAR* name)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Extract(int var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Extract(int var, XCHAR* name)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Extract(float var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Extract(float var, XCHAR* name)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Extract(double var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Extract(double var, XCHAR* name)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Extract(long var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Extract(long var, XCHAR* name)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Extract(long long var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Extract(long long var, XCHAR* name)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Extract(XBYTE var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Extract(XBYTE var, XCHAR* name)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Extract(XWORD var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Extract(XWORD var, XCHAR* name)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Extract(XDWORD var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Extract(XDWORD var, XCHAR* name)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Extract(XQWORD var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Extract(XQWORD var, XCHAR* name)
{
  return true;
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Extract(XSTRING* var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Extract(XSTRING* var, XCHAR* name)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Extract(XBUFFER* var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Extract(XBUFFER* var, XCHAR* name)
{
   return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Extract(XVARIANT* var, XCHAR* name)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Extract(XVARIANT* var, XCHAR* name)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::ExtractStruct(XCHAR* name)
* @brief      Extract struct
* @ingroup    XUTILS
* 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::ExtractStruct(XCHAR* name)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::ExtractArray(XDWORD nelements, XCHAR* name)
* @brief      Extract array
* @ingroup    XUTILS
* 
* @param[in]  nelements : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::ExtractArray(XDWORD nelements, XCHAR* name)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBUFFER* XSERIALIZATIONMETHODBINARY::GetBufferData()
* @brief      Get buffer data
* @ingroup    XUTILS
* 
* @return     XBUFFER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBUFFER* XSERIALIZATIONMETHODBINARY::GetBufferData()
{
  return bufferdata;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XSERIALIZATIONMETHODBINARY::SetBufferData(XBUFFER* bufferdata)
* @brief      Set buffer data
* @ingroup    XUTILS
* 
* @param[in]  bufferdata : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XSERIALIZATIONMETHODBINARY::SetBufferData(XBUFFER* bufferdata)
{
  this->bufferdata = bufferdata;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XSERIALIZATIONMETHODBINARY::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    XUTILS
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XSERIALIZATIONMETHODBINARY::Clean()
{
  bufferdata = NULL; 
}


#pragma endregion

