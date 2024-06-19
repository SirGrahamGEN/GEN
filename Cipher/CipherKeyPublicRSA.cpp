/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       CipherKeyPublicRSA.cpp
* 
* @class      CIPHERKEYPUBLICRSA
* @brief      Cipher Key Public RSA class
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "CipherKeyPublicRSA.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         CIPHERKEYPUBLICRSA::CIPHERKEYPUBLICRSA()
* @brief      Constructor
* @ingroup    CIPHER
* 
* --------------------------------------------------------------------------------------------------------------------*/
CIPHERKEYPUBLICRSA::CIPHERKEYPUBLICRSA() : CIPHERKEY()
{
  Clean();

  type = CIPHERKEYTYPE_PUBLIC;

  modulus.Ini();
  exponent.Ini();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         CIPHERKEYPUBLICRSA::~CIPHERKEYPUBLICRSA()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    CIPHER
* 
* --------------------------------------------------------------------------------------------------------------------*/
CIPHERKEYPUBLICRSA::~CIPHERKEYPUBLICRSA()
{
  modulus.End();
  exponent.End();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHERKEYPUBLICRSA::Get(XMPINTEGER& modulus, XMPINTEGER& exponent)
* @brief      Get
* @ingroup    CIPHER
* 
* @param[in]  modulus : 
* @param[in]  exponent : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHERKEYPUBLICRSA::Get(XMPINTEGER& modulus, XMPINTEGER& exponent)
{
  modulus.CopyFrom(&this->modulus);
  exponent.CopyFrom(&this->exponent);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHERKEYPUBLICRSA::Set(XMPINTEGER& modulus, XMPINTEGER& exponent)
* @brief      Set
* @ingroup    CIPHER
* 
* @param[in]  modulus : 
* @param[in]  exponent : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHERKEYPUBLICRSA::Set(XMPINTEGER& modulus, XMPINTEGER& exponent)
{
  this->modulus.CopyFrom(&modulus);
  this->exponent.CopyFrom(&exponent);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int CIPHERKEYPUBLICRSA::GetSizeInBytes()
* @brief      GetSizeInBytes
* @ingroup    CIPHER
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int CIPHERKEYPUBLICRSA::GetSizeInBytes()
{ 
  return this->modulus.GetSize();         
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHERKEYPUBLICRSA::CopyFrom(CIPHERKEYPUBLICRSA* key)
* @brief      CopyFrom
* @ingroup    CIPHER
* 
* @param[in]  key : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHERKEYPUBLICRSA::CopyFrom(CIPHERKEYPUBLICRSA* key)
{
  if(!key) return false;

  if(!CIPHERKEY::CopyFrom((CIPHERKEY*)key)) return false;

  return key->Get(modulus, exponent);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHERKEYPUBLICRSA::Check()
* @brief      Check
* @ingroup    CIPHER
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHERKEYPUBLICRSA::Check()
{
  if(!modulus.GetLimbs()              || !exponent.GetLimbs())                      return false;
  if((modulus.GetLimbs()[0] & 1) == 0 || (exponent.GetLimbs()[0] & 1 ) == 0)        return false;
  if((modulus.GetMSB() < 128)         || (modulus.GetMSB() >  XMPINTEGER_MAXBITS )) return false;
  if((exponent.GetMSB() < 2)          || (exponent.GetMSB() >  64 ))                return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void CIPHERKEYPUBLICRSA::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    CIPHER
* 
* --------------------------------------------------------------------------------------------------------------------*/
void CIPHERKEYPUBLICRSA::Clean()
{                                         

}


#pragma endregion


