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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

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
* @fn         XSERIALIZABLE::XSERIALIZABLE()
* @brief      Constructor of class
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
* @brief      Destructor of class
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
* @brief      Create instance
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
* @brief      Create instance
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
* @brief      Get serialization method
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
* @brief      Set serialization method
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
* @fn         bool XSERIALIZABLE::DoDeserialize()
* @brief      Do deserialize
* @ingroup    XUTILS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZABLE::DoDeserialize()
{
  if(!serializationmethod)
    {
      return false;
    }

  return Deserialize();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZABLE::DoSerialize()
* @brief      Do serialize
* @ingroup    XUTILS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZABLE::DoSerialize()
{
  if(!serializationmethod)
    {
      return false;
    }

  return Serialize();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZABLE::DoSerialize(XSERIALIZATIONMETHOD* serializationmethod)
* @brief      Do serialize
* @ingroup    XUTILS
* 
* @param[in]  serializationmethod : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZABLE::DoSerialize(XSERIALIZATIONMETHOD* serializationmethod)
{
  if(!serializationmethod)
    {
      return false;
    }

  SetSerializationMethod(serializationmethod);

  return Serialize();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZABLE::DoDeserialize(XSERIALIZATIONMETHOD* serializationmethod)
* @brief      Do deserialize
* @ingroup    XUTILS
* 
* @param[in]  serializationmethod : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZABLE::DoDeserialize(XSERIALIZATIONMETHOD* serializationmethod)
{
  if(!serializationmethod)
    {
      return false;
    }

  SetSerializationMethod(serializationmethod);

  return Deserialize();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSERIALIZABLE::HasBeenChanged()
* @brief      Has been changed
* @ingroup    XUTILS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSERIALIZABLE::HasBeenChanged()
{
  if(!hasbeenchanged)
    {
      XFILEJSON               content;
      
      XSERIALIZATIONMETHOD*   serializationmethod = XSERIALIZABLE::CreateInstance(content);             
              
      if(serializationmethod)  
        {
          XSTRING contentstring;         
          XBUFFER contentbinary;   

          SetSerializationMethod(serializationmethod);                            
          Serialize();

          content.EncodeAllLines();
          content.GetAllInOneLine(contentstring);
          contentstring.ConvertToUTF8(contentbinary);

          SetSerializationMethod(NULL);  
          delete serializationmethod;  

          hasbeenchanged = !contentbinary.Compare(cache);
          if(hasbeenchanged)
            {
              cache.Empty();
              cache.Add(contentbinary);    
            }                                 
        }
    }

  return hasbeenchanged;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XSERIALIZABLE::SetHasBeenChanged(bool hasbeenchanged)
* @brief      Set has been changed
* @ingroup    XUTILS
* 
* @param[in]  hasbeenchanged : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XSERIALIZABLE::SetHasBeenChanged(bool hasbeenchanged)
{
  this->hasbeenchanged = hasbeenchanged;
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
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    XUTILS
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XSERIALIZABLE::Clean()
{
  hasbeenchanged      = false;
  serializationmethod = NULL;
}


#pragma endregion

