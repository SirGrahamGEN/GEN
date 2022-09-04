/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       CipherKey.cpp
* 
* @class      CIPHERKEY
* @brief      Cipher Key interface class
* @ingroup    CIPHER
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

#include <string.h>

#include "XFactory.h"

#include "CipherKey.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#pragma region CIPHERKEY


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         CIPHERKEY::CIPHERKEY()
* @brief      Constructor
* @ingroup    CIPHER
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
CIPHERKEY::CIPHERKEY()
{ 
  Clean();                                          
}


       
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         CIPHERKEY::~CIPHERKEY()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    CIPHER
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
CIPHERKEY::~CIPHERKEY()
{ 
  Clean();                                          
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         CIPHERKEYTYPE CIPHERKEY::GetType()
* @brief      GetType
* @ingroup    CIPHER
* 
* @return     CIPHERKEYTYPE : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
CIPHERKEYTYPE CIPHERKEY::GetType()
{ 
  return type;                                      
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void CIPHERKEY::SetType(CIPHERKEYTYPE type)
* @brief      SetType
* @ingroup    CIPHER
* 
* @param[in]  type : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void CIPHERKEY::SetType(CIPHERKEYTYPE type)
{ 
  this->type = type;                                
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int CIPHERKEY::GetSizeInBytes()
* @brief      GetSizeInBytes
* @ingroup    CIPHER
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int CIPHERKEY::GetSizeInBytes()
{ 
  return 0;                                         
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int CIPHERKEY::GetSizeInBits()
* @brief      GetSizeInBits
* @ingroup    CIPHER
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int CIPHERKEY::GetSizeInBits()
{ 
  return (GetSizeInBytes()*8);                      
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHERKEY::CopyFrom(CIPHERKEY* key)
* @brief      CopyFrom
* @ingroup    CIPHER
* 
* @param[in]  key : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHERKEY::CopyFrom(CIPHERKEY* key)
{
  if(!key) return false;
  type = key->GetType();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void CIPHERKEY::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    CIPHER
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void CIPHERKEY::Clean()
{
  type = CIPHERKEYTYPE_UNKNOWN;
}


#pragma endregion


#pragma region CIPHERKEYSYMMETRICAL


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         CIPHERKEYSYMMETRICAL::CIPHERKEYSYMMETRICAL() : CIPHERKEY()
* @brief      Constructor
* @ingroup    CIPHER
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
CIPHERKEYSYMMETRICAL::CIPHERKEYSYMMETRICAL() : CIPHERKEY()
{
  Clean();

  type = CIPHERKEYTYPE_SYMMETRICAL;

  xbufferkey = new XBUFFER();
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         CIPHERKEYSYMMETRICAL::~CIPHERKEYSYMMETRICAL()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    CIPHER
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
CIPHERKEYSYMMETRICAL::~CIPHERKEYSYMMETRICAL()
{
  if(xbufferkey)  delete xbufferkey;

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBYTE* CIPHERKEYSYMMETRICAL::Get(int& size)
* @brief      Get
* @ingroup    CIPHER
* 
* @param[in]  size : 
* 
* @return     XBYTE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE* CIPHERKEYSYMMETRICAL::Get(int& size)
{
  if(!xbufferkey) return NULL;

  size = xbufferkey->GetSize();

  return xbufferkey->Get();
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBUFFER* CIPHERKEYSYMMETRICAL::Get()
* @brief      Get
* @ingroup    CIPHER
* 
* @return     XBUFFER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBUFFER* CIPHERKEYSYMMETRICAL::Get()
{
  return xbufferkey;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHERKEYSYMMETRICAL::Set(XBYTE* key, XDWORD size)
* @brief      Set
* @ingroup    CIPHER
* 
* @param[in]  key : 
* @param[in]  size : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHERKEYSYMMETRICAL::Set(XBYTE* key, XDWORD size)
{
  if(!key) return false;

  this->xbufferkey->Delete();

  this->xbufferkey->Add(key, (XDWORD)size);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHERKEYSYMMETRICAL::Set(XBUFFER& key)
* @brief      Set
* @ingroup    CIPHER
* 
* @param[in]  key : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHERKEYSYMMETRICAL::Set(XBUFFER& key)
{
  return Set(key.Get(), key.GetSize());
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int CIPHERKEYSYMMETRICAL::GetSizeInBytes()
* @brief      GetSizeInBytes
* @ingroup    CIPHER
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int CIPHERKEYSYMMETRICAL::GetSizeInBytes()
{ 
  return xbufferkey->GetSize();                     
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHERKEYSYMMETRICAL::CopyFrom(CIPHERKEYSYMMETRICAL* key)
* @brief      CopyFrom
* @ingroup    CIPHER
* 
* @param[in]  key : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHERKEYSYMMETRICAL::CopyFrom(CIPHERKEYSYMMETRICAL* key)
{
  if(!key) return false;

  if(!CIPHERKEY::CopyFrom((CIPHERKEY*)key)) return false;

  xbufferkey->Delete();
  xbufferkey->Add(key->Get()->Get(), key->Get()->GetSize());

  return true;
}

  
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void CIPHERKEYSYMMETRICAL::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    CIPHER
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void CIPHERKEYSYMMETRICAL::Clean()
{
  xbufferkey = NULL;
}

#pragma endregion
