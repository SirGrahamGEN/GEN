/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       Cipher.cpp
* 
* @class      CIPHER
* @brief      Cipher interface class
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

#include "Cipher.h"

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


#pragma region CIPHER


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         CIPHER::CIPHER()
* @brief      Constructor
* @ingroup    CIPHER
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
CIPHER::CIPHER()
{
  Clean();

  type             = CIPHERTYPE_XOR;
  paddingadjustsize = 0;

  inivector = new XBUFFER();
  result    = new XBUFFER();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         CIPHER::~CIPHER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    CIPHER
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
CIPHER::~CIPHER()
{

  if(inivector)
    {
      delete inivector;
      inivector = NULL;
    }

  if(result)
    {
      delete result;
      result = NULL;
    }

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         CIPHERTYPE CIPHER::GetType()
* @brief      GetType
* @ingroup    CIPHER
* 
* @return     CIPHERTYPE : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
CIPHERTYPE CIPHER::GetType()
{ 
  return type;                                      
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void CIPHER::SetType(CIPHERTYPE type)
* @brief      SetType
* @ingroup    CIPHER
* 
* @param[in]  type : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void CIPHER::SetType(CIPHERTYPE type)
{ 
  this->type = type;                                
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         CIPHERCHAININGMODE CIPHER::GetChainingMode()
* @brief      GetChainingMode
* @ingroup    CIPHER
* 
* @return     CIPHERCHAININGMODE : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
CIPHERCHAININGMODE CIPHER::GetChainingMode()
{ 
  return chainingmode;                              
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void CIPHER::SetChainingMode(CIPHERCHAININGMODE chainingmode)
* @brief      SetChainingMode
* @ingroup    CIPHER
* 
* @param[in]  chainingmode : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void CIPHER::SetChainingMode(CIPHERCHAININGMODE chainingmode)
{ 
  this->chainingmode = chainingmode;                
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBUFFER_PADDINGTYPE CIPHER::GetPaddingType()
* @brief      GetPaddingType
* @ingroup    CIPHER
* 
* @return     XBUFFER_PADDINGTYPE : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBUFFER_PADDINGTYPE CIPHER::GetPaddingType()
{ 
  return paddingtype;                               
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void CIPHER::SetPaddingType(XBUFFER_PADDINGTYPE paddingtype)
* @brief      SetPaddingType
* @ingroup    CIPHER
* 
* @param[in]  paddingtype : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void CIPHER::SetPaddingType(XBUFFER_PADDINGTYPE paddingtype)
{ 
  this->paddingtype = paddingtype;                  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int CIPHER::GetPaddingAdjustSize()
* @brief      GetPaddingAdjustSize
* @ingroup    CIPHER
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int CIPHER::GetPaddingAdjustSize()
{ 
  return paddingadjustsize;                         
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void CIPHER::SetPaddingAdjustSize(int paddingadjustsize)
* @brief      SetPaddingAdjustSize
* @ingroup    CIPHER
* 
* @param[in]  paddingadjustsize : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void CIPHER::SetPaddingAdjustSize(int paddingadjustsize)
{ 
  this->paddingadjustsize = paddingadjustsize;      
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         CIPHERKEY* CIPHER::GetKey(CIPHERKEYTYPE type)
* @brief      GetKey
* @ingroup    CIPHER
* 
* @param[in]  type : 
* 
* @return     CIPHERKEY* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
CIPHERKEY* CIPHER::GetKey(CIPHERKEYTYPE type)
{
  int index;

  switch(type)
    {
      case CIPHERKEYTYPE_SYMMETRICAL :
      case CIPHERKEYTYPE_PUBLIC      : index = 0;   break;
      case CIPHERKEYTYPE_PRIVATE     : index = 1;   break;
                      default        : return NULL;
    }

  return keys[index];
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHER::SetKey(CIPHERKEY* key, bool integritycheck)
* @brief      SetKey
* @ingroup    CIPHER
* 
* @param[in]  key : 
* @param[in]  integritycheck : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHER::SetKey(CIPHERKEY* key, bool integritycheck)
{
  if(!key) return false;

  int index;

  switch(key->GetType())
    {
      case CIPHERKEYTYPE_SYMMETRICAL :
      case CIPHERKEYTYPE_PUBLIC      : index = 0;   break;
      case CIPHERKEYTYPE_PRIVATE     : index = 1;   break;
                default              : return false;
    }

  return SetKey(index, key);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBYTE* CIPHER::GetInitVector()
* @brief      GetInitVector
* @ingroup    CIPHER
* 
* @return     XBYTE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE* CIPHER::GetInitVector()
{
  if(!inivector) return NULL;

  return inivector->Get();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHER::SetInitVector(XBYTE* vector, XDWORD size)
* @brief      SetInitVector
* @ingroup    CIPHER
* 
* @param[in]  vector : 
* @param[in]  size : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHER::SetInitVector(XBYTE* vector, XDWORD size)
{
  if(!vector)    return false;
  if(!inivector) return false;

  inivector->Delete();
  inivector->Add(vector,size);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHER::SetInitVector(XBUFFER& vector)
* @brief      SetInitVector
* @ingroup    CIPHER
* 
* @param[in]  vector : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHER::SetInitVector(XBUFFER& vector)
{
  inivector->Delete();
  inivector->Add(vector);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHER::Cipher(XBYTE* input,XDWORD size)
* @brief      Cipher
* @ingroup    CIPHER
* 
* @param[in]  input : 
* @param[in]  size : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHER::Cipher(XBYTE* input,XDWORD size)
{
  result->Delete();
  result->Add(input, size);

  CIPHERKEYSYMMETRICAL* key = (CIPHERKEYSYMMETRICAL*)GetKey(0);
  if(!key)                return false;
  if(!key->Get()->Get())  return false;

  int indexkey = 0;

  for(XDWORD c=0; c<size; c++)
    {
      result->Get()[c] ^= key->Get()->GetByte(indexkey);

      indexkey++;
      if(indexkey >= (int)key->Get()->GetSize()) indexkey = 0;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHER::Cipher(XBUFFER& input)
* @brief      Cipher
* @ingroup    CIPHER
* 
* @param[in]  input : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHER::Cipher(XBUFFER& input)
{
  return Cipher(input.Get(), input.GetSize());
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHER::Uncipher(XBYTE* input,XDWORD size)
* @brief      Uncipher
* @ingroup    CIPHER
* 
* @param[in]  input : 
* @param[in]  size : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHER::Uncipher(XBYTE* input,XDWORD size)
{
  return Cipher(input,size);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHER::Uncipher(XBUFFER& input)
* @brief      Uncipher
* @ingroup    CIPHER
* 
* @param[in]  input : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHER::Uncipher(XBUFFER& input)
{
  return Uncipher(input.Get(), input.GetSize());
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBYTE* CIPHER::GetResult(int& resultsize)
* @brief      GetResult
* @ingroup    CIPHER
* 
* @param[in]  resultsize : 
* 
* @return     XBYTE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE* CIPHER::GetResult(int& resultsize)
{
  if(!result) return NULL;

  resultsize = result->GetSize();

  return result->Get();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBUFFER* CIPHER::GetResult()
* @brief      GetResult
* @ingroup    CIPHER
* 
* @return     XBUFFER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBUFFER* CIPHER::GetResult()
{
  return result;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHER::GetResultString(XSTRING& stringhex)
* @brief      GetResultString
* @ingroup    CIPHER
* 
* @param[in]  stringhex : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHER::GetResultString(XSTRING& stringhex)
{
  stringhex.Empty();

  XBUFFER* xbuffer = GetResult();
  if(!xbuffer) return false;

  if(!xbuffer->GetSize()) return false;

  for(int c=0;c<(int)xbuffer->GetSize();c++)
    {
      XSTRING strbyte;

      strbyte.Format(__L("%02x"),xbuffer->GetByte(c));

      stringhex += strbyte;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         CIPHERKEY* CIPHER::GetKey(int index)
* @brief      GetKey
* @ingroup    CIPHER
* 
* @param[in]  index : 
* 
* @return     CIPHERKEY* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
CIPHERKEY* CIPHER::GetKey(int index)
{
  if(index < 0)              return NULL;
  if(index >= CIPHERMAXKEYS) return NULL;

  return keys[index];
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHER::SetKey(int index, CIPHERKEY* key)
* @brief      SetKey
* @ingroup    CIPHER
* 
* @param[in]  index : 
* @param[in]  key : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHER::SetKey(int index, CIPHERKEY* key)
{
  if(index < 0)               return false;
  if(index >= CIPHERMAXKEYS) return false;

  this->keys[index] = key;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void CIPHER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    CIPHER
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void CIPHER::Clean()
{
  paddingtype  = XBUFFER_PADDINGTYPE_NONE;
  chainingmode = CIPHERCHAININGMODE_UNKNOWN;

  for(int c=0; c<CIPHERMAXKEYS; c++)
    {
      keys[c] = NULL;
    }

  inivector = NULL;
  result    = NULL;
}


#pragma endregion
