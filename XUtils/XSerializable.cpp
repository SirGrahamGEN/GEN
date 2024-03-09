/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XSerializable.cpp
* 
* @class      XSERIALIZABLE
* @brief      eXtended Utils Serializable class
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

#include "XSerializable.h"

#ifdef XSERIALIZABLE_BINARY_ACTIVE
#include "XSerializationMethodBinary.h"
#endif

#ifdef XSERIALIZABLE_JSON_ACTIVE
#include "XSerializationMethodJSON.h"
#endif

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSERIALIZABLE::XSERIALIZABLE()
* @brief      Constructor
* @ingroup    XUTILS
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSERIALIZABLE::XSERIALIZABLE()
{
  Clean();
}
 
    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSERIALIZABLE::~XSERIALIZABLE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSERIALIZABLE::~XSERIALIZABLE()
{
  Clean();
}


#ifdef XSERIALIZABLE_BINARY_ACTIVE
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSERIALIZATIONMETHOD* XSERIALIZATIONMETHOD::CreateInstance(XBUFFER& databinary)
* @brief      CreateInstance
* @ingroup    XUTILS
* 
* @param[in]  databinary : 
* 
* @return     XSERIALIZATIONMETHOD* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSERIALIZATIONMETHOD* XSERIALIZABLE::CreateInstance(XBUFFER& databinary)
{
  XSERIALIZATIONMETHODBINARY* serializable  = new XSERIALIZATIONMETHODBINARY();
  if(serializable)
    {
      serializable->SetBufferData(&databinary);
    }

  return (XSERIALIZATIONMETHOD*)serializable;
}
#endif


#ifdef XSERIALIZABLE_JSON_ACTIVE
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSERIALIZATIONMETHOD* XSERIALIZABLE::CreateInstance(XFILEJSON& fileJSON)
* @brief      CreateInstance
* @ingroup    XUTILS
* 
* @param[in]  fileJSON : 
* 
* @return     XSERIALIZATIONMETHOD* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSERIALIZATIONMETHOD* XSERIALIZABLE::CreateInstance(XFILEJSON& fileJSON)
{
  XSERIALIZATIONMETHODJSON* serializable  = new XSERIALIZATIONMETHODJSON();
  if(serializable)
    {
      serializable->SetFileJSON(&fileJSON);
    }

  XFILEJSONOBJECT* root =  fileJSON.GetRoot();
  if(!root)
    {
      root = new XFILEJSONOBJECT();
      if(root) 
        {
          fileJSON.SetRoot(root);
        }
    }

  if(!root) 
    {
      delete serializable;
      serializable = NULL;
    }
   else
    {      
      serializable->SetActualObject(root);
    }

  return (XSERIALIZATIONMETHOD*)serializable;
}
#endif


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSERIALIZATIONMETHOD* XSERIALIZABLE::GetSerializationMethod()
* @brief      GetSerializationMethod
* @ingroup    XUTILS
* 
* @return     XSERIALIZATIONMETHOD* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSERIALIZATIONMETHOD* XSERIALIZABLE::GetSerializationMethod()
{
  return serializationmethod; 
}
    
    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XSERIALIZABLE::SetSerializationMethod(XSERIALIZATIONMETHOD* serializationmethod)
* @brief      SetSerializationMethod
* @ingroup    XUTILS
* 
* @param[in]  serializationmethod : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XSERIALIZABLE::SetSerializationMethod(XSERIALIZATIONMETHOD* serializationmethod)
{
  this->serializationmethod = serializationmethod;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZABLE::InitSerialize(XSERIALIZATIONMETHOD* serializationmethod)
* @brief      InitSerialize
* @ingroup    XUTILS
* 
* @param[in]  serializationmethod : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZABLE::InitSerialize(XSERIALIZATIONMETHOD* serializationmethod)
{
  SetSerializationMethod(serializationmethod);

  return Serialize();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZABLE::InitDeserialize(XSERIALIZATIONMETHOD* serializationmethod)
* @brief      InitDeserialize
* @ingroup    XUTILS
* 
* @param[in]  serializationmethod : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZABLE::InitDeserialize(XSERIALIZATIONMETHOD* serializationmethod)
{
  SetSerializationMethod(serializationmethod);

  return Deserialize();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZABLE::Serialize()
* @brief      Serialize
* @ingroup    XUTILS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZABLE::Serialize()
{
  if(!serializationmethod) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZABLE::Deserialize()
* @brief      Deserialize
* @ingroup    XUTILS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZABLE::Deserialize()
{
  if(!serializationmethod) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XSERIALIZABLE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XSERIALIZABLE::Clean()
{
  serializationmethod = NULL;
}


#pragma endregion

