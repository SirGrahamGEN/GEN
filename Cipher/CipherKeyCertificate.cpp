/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       CipherKeyCertificate.cpp
* 
* @class      CIPHERKEYCERTIFICATE
* @brief      Cipher Key Certificate class
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

#include "CipherKeyCertificate.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         CIPHERKEYCERTIFICATE::CIPHERKEYCERTIFICATE()
* @brief      Constructor
* @ingroup    CIPHER
* 
* --------------------------------------------------------------------------------------------------------------------*/
CIPHERKEYCERTIFICATE::CIPHERKEYCERTIFICATE() : CIPHERKEY()
{
  Clean();

  type = CIPHERKEYTYPE_CERTIFICATE;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         CIPHERKEYCERTIFICATE::~CIPHERKEYCERTIFICATE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    CIPHER
* 
* --------------------------------------------------------------------------------------------------------------------*/
CIPHERKEYCERTIFICATE::~CIPHERKEYCERTIFICATE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XWORD CIPHERKEYCERTIFICATE::GetVersion()
* @brief      GetVersion
* @ingroup    CIPHER
* 
* @return     XWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XWORD CIPHERKEYCERTIFICATE::GetVersion()
{
  return version;
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void CIPHERKEYCERTIFICATE::SetVersion(XWORD version)
* @brief      SetVersion
* @ingroup    CIPHER
* 
* @param[in]  version : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void CIPHERKEYCERTIFICATE::SetVersion(XWORD version)
{
  this->version = version;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBUFFER* CIPHERKEYCERTIFICATE::GetSerial()
* @brief      GetSerial
* @ingroup    CIPHER
* 
* @return     XBUFFER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBUFFER* CIPHERKEYCERTIFICATE::GetSerial()
{
  return &serial;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void CIPHERKEYCERTIFICATE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    CIPHER
* 
* --------------------------------------------------------------------------------------------------------------------*/
void CIPHERKEYCERTIFICATE::Clean()
{                                         
  version  = 0;
}


#pragma endregion


