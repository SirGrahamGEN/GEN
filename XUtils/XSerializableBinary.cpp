/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XSerializableBinary.cpp
* 
* @class      XSERIALIZABLEBINARY
* @brief      eXtended Serializable Binary class
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

#include "XSerializableBinary.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSERIALIZATIONMETHODBINARY::XSERIALIZATIONMETHODBINARY()
* @brief      Constructor
* @ingroup    XUTILS
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSERIALIZATIONMETHODBINARY::XSERIALIZATIONMETHODBINARY()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSERIALIZATIONMETHODBINARY::~XSERIALIZATIONMETHODBINARY()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSERIALIZATIONMETHODBINARY::~XSERIALIZATIONMETHODBINARY()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Add(bool var)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Add(bool var)
{
  if(!bufferdata) 
    {
      return false;
    }

  bufferdata->Add(var);  

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Add(char var)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Add(char var)
{
  if(!bufferdata) 
    {
      return false;
    }

  bufferdata->Add((XBYTE)var); 

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Add(int var)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Add(int var)
{
  if(!bufferdata) 
    {
      return false;
    }

  bufferdata->Add((XDWORD)var); 

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Add(float var)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Add(float var)  
{
  if(!bufferdata) 
    {
      return false;
    }

  bufferdata->Add((float)var); 

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Add(double var)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Add(double var) 
{
  if(!bufferdata) 
    {
      return false;
    }

  bufferdata->Add((double)var); 

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Add(long var)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Add(long var) 
{
  if(!bufferdata) 
    {
      return false;
    }

  bufferdata->Add((XDWORD)var); 
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Add(long long var)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  long var : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Add(long long var) 
{
  if(!bufferdata) 
    {
      return false;
    }

  bufferdata->Add((XQWORD)var); 

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Add(XBYTE var)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Add(XBYTE var)
{
  if(!bufferdata) 
    {
      return false;
    }

  bufferdata->Add(var); 

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Add(XWORD var)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Add(XWORD var)
{
  if(!bufferdata) 
    {
      return false;
    }

  bufferdata->Add((XWORD)var); 

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Add(XDWORD var)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Add(XDWORD var)
{

  if(!bufferdata) 
    {
      return false;
    }

  bufferdata->Add((XDWORD)var); 

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Add(XQWORD var)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Add(XQWORD var)
{
  if(!bufferdata) 
    {
      return false;
    }

  bufferdata->Add((XQWORD)var); 

  return true;
}


    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Add(XSTRING& var)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Add(XSTRING& var)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Add(XBUFFER& var)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  var : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Add(XBUFFER& var)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Extract(bool var)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Extract(bool var)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Extract(char var)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Extract(char var)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Extract(int var)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Extract(int var)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Extract(float var)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Extract(float var)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Extract(double var)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Extract(double var)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Extract(long var)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Extract(long var)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Extract(long long var)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  long var : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Extract(long long var)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Extract(XBYTE var)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Extract(XBYTE var)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Extract(XWORD var)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Extract(XWORD var)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Extract(XDWORD var)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Extract(XDWORD var)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Extract(XQWORD var)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Extract(XQWORD var)
{
  return true;
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Extract(XSTRING& var)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Extract(XSTRING& var)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZATIONMETHODBINARY::Extract(XBUFFER& var)
* @brief      Extract
* @ingroup    XUTILS
* 
* @param[in]  var : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZATIONMETHODBINARY::Extract(XBUFFER& var)
{
   return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBUFFER* XSERIALIZATIONMETHODBINARY::GetBufferData()
* @brief      GetBufferData
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
* @brief      SetBufferData
* @ingroup    XUTILS
* 
* @param[in]  bufferdata : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XSERIALIZATIONMETHODBINARY::SetBufferData(XBUFFER* bufferdata)
{
  this->bufferdata = bufferdata;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XSERIALIZATIONMETHODBINARY::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XSERIALIZATIONMETHODBINARY::Clean()
{
  bufferdata = NULL;
}
