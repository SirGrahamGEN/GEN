/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       CipherKeyCertificate.h
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

#ifndef _CIPHERKEYCERTIFICATE_H_
#define _CIPHERKEYCERTIFICATE_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XString.h"
#include "XBuffer.h"
#include "XDateTime.h"
#include "XMPInteger.h"

#include "CipherKey.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


enum CIPHERKEYSFILEPEM_ALGORITHM_TYPE
{
  CIPHERKEYCERTIFICATE_ALGORITHM_TYPE_UNKNOWN             = 0x00  ,

  CIPHERKEYCERTIFICATE_ALGORITHM_TYPE_RSA_SIGN_RSA        = 0x01  ,
  CIPHERKEYCERTIFICATE_ALGORITHM_TYPE_RSA_SIGN_MD5        = 0x04  ,
  CIPHERKEYCERTIFICATE_ALGORITHM_TYPE_RSA_SIGN_SHA1       = 0x05  ,
  CIPHERKEYCERTIFICATE_ALGORITHM_TYPE_RSA_SIGN_SHA256     = 0x0B  ,
  CIPHERKEYCERTIFICATE_ALGORITHM_TYPE_RSA_SIGN_SHA384     = 0x0C  ,
  CIPHERKEYCERTIFICATE_ALGORITHM_TYPE_RSA_SIGN_SHA512     = 0x0D  ,
  CIPHERKEYCERTIFICATE_ALGORITHM_TYPE_ECDSA_SIGN_SHA256   = 0x0E  ,
                                
  CIPHERKEYCERTIFICATE_ALGORITHM_TYPE_EC_PUBLIC_KEY       = 0x11  ,
  CIPHERKEYCERTIFICATE_ALGORITHM_TYPE_EC_PRIME192V1       = 0x12  ,
  CIPHERKEYCERTIFICATE_ALGORITHM_TYPE_EC_PRIME192V2       = 0x13  ,
  CIPHERKEYCERTIFICATE_ALGORITHM_TYPE_EC_PRIME192V3       = 0x14  ,
  CIPHERKEYCERTIFICATE_ALGORITHM_TYPE_EC_PRIME239V1       = 0x15  ,
  CIPHERKEYCERTIFICATE_ALGORITHM_TYPE_EC_PRIME239V2       = 0x16  ,
  CIPHERKEYCERTIFICATE_ALGORITHM_TYPE_EC_PRIME239V3       = 0x17  ,
  CIPHERKEYCERTIFICATE_ALGORITHM_TYPE_EC_PRIME256V1       = 0x18  ,
  
  /*                              
  CIPHERKEYCERTIFICATE_ALGORITHM_TYPE_EC_SECP224R1        = 21    ,
  CIPHERKEYCERTIFICATE_ALGORITHM_TYPE_EC_SECP256R1        = 23    ,
  CIPHERKEYCERTIFICATE_ALGORITHM_TYPE_EC_SECP384R1        = 24    , 
  CIPHERKEYCERTIFICATE_ALGORITHM_TYPE_EC_SECP521R1        = 25    ,  
  */
};


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class CIPHERKEYCERTIFICATE : public CIPHERKEY
{
  public:
                                            CIPHERKEYCERTIFICATE              ();
    virtual                                ~CIPHERKEYCERTIFICATE              ();

    XWORD                                   GetVersion                        ();
    void                                    SetVersion                        (XWORD version);

    XBUFFER*                                GetSerial                         ();  

    CIPHERKEYSFILEPEM_ALGORITHM_TYPE        GetAlgorithmType                  ();
    bool                                    SetAlgorithmType                  (XCHAR* OID);

    XSTRING*                                GetCountryName                    ();    
    XSTRING*                                GetOrganizationName               ();
    XSTRING*                                GetOrganizationalUnitName         ();
    XSTRING*                                GetCommonName                     ();

    XDATETIME*                              GetDateNotBefore                  ();
    XDATETIME*                              GetDateNotAfter                   ();

    bool                                    ConvertDateTime                   (XCHAR* datestr, XDATETIME* datetime);
    
  private:
  
    void                                    Clean                             ();  

    XWORD                                   version;
    XBUFFER                                 serial;

    CIPHERKEYSFILEPEM_ALGORITHM_TYPE        algorithmtype;

    XSTRING                                 countryname;    
    XSTRING                                 organizationame;
    XSTRING                                 organizationalunitname;
    XSTRING                                 commonname;

    XDATETIME                               datenotbefore;
    XDATETIME                               datenotafter;
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif


