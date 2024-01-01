/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       CipherKeysFilePEM.h
* 
* @class      CIPHERKEYSFILEPEM
* @brief      Cipher File Keys PEM (GEN Key File) class
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

#ifndef _CIPHERKEYSFILEPEM_H_
#define _CIPHERKEYSFILEPEM_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XVector.h"
#include "XDateTime.h"
#include "XASN1.h"

#include "CipherKey.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

#define CIPHERKEYSFILEPEM_EXT           __L(".PEM")
#define CIPHERKEYSFILEKEY_EXT           __L(".KEY")
#define CIPHERKEYSFILECER_EXT           __L(".CER")

#define CIPHERKEYSFILEPEM_BEGINKEY      __L("-----BEGIN ")
#define CIPHERKEYSFILEPEM_ENDKEY        __L("-----END ")
#define CIPHERKEYSFILEPEM_FINISH        __L("-----")

#define CIPHERKEYSFILEPEM_PUBLIC        __L("PUBLIC")
#define CIPHERKEYSFILEPEM_PRIVATE       __L("PRIVATE")
#define CIPHERKEYSFILEPEM_CERTIFICATE   __L("CERTIFICATE")

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

class XFACTORY;
class CIPHERKEY;
class XFILETXT;

    
class CIPHERKEYSFILEPEM_TYPECERTIFICATE
{
  public:
                            CIPHERKEYSFILEPEM_TYPECERTIFICATE   ();
    virtual                ~CIPHERKEYSFILEPEM_TYPECERTIFICATE   ();

    void                    Clean                               ();

    XWORD                   version;
    XDWORD                  algorithm;
    XDWORD                  key_algorithm;
    XDWORD                  ec_algorithm;
    XBYTE*                  exponent;
    XDWORD                  exponent_len;
    XBYTE*                  pk;
    XDWORD                  pk_len;
    XBYTE*                  priv;
    XDWORD                  priv_len;
    XBYTE*                  issuer_country;
    XBYTE*                  issuer_state;
    XBYTE*                  issuer_location;
    XBYTE*                  issuer_entity;
    XBYTE*                  issuer_subject;
    XBYTE*                  not_before;
    XBYTE*                  not_after;
    XBYTE*                  country;
    XBYTE*                  state;
    XBYTE*                  location;
    XBYTE*                  entity;
    XBYTE*                  subject;
    XBYTE**                 san;
    XWORD                   san_length;
    XBYTE*                  ocsp;
    XBYTE*                  serial_number;
    XDWORD                  serial_len;
    XBYTE*                  sign_key;
    XDWORD                  sign_len;
    XBYTE*                  fingerprint;
    XBYTE*                  der_bytes;
    XDWORD                  der_len;
    XBYTE*                  bytes;
    XDWORD                  len;    
};


class CIPHERKEYSFILEPEM
{
  public:
                            CIPHERKEYSFILEPEM                   (XPATH& xpath);
    virtual                ~CIPHERKEYSFILEPEM                   ();
   
    bool                    HaveKey                             (CIPHERKEYTYPE type);
    CIPHERKEY*              GetKey                              (CIPHERKEYTYPE type);
    bool                    AddKey                              (CIPHERKEY& key);
    bool                    DeleteKey                           (CIPHERKEYTYPE type);
    bool                    DeleteAllKeys                       ();

    XPATH&                  GetXPath                            ();
    XFILETXT*               GetXFileTXT                         ();

  private:

    bool                    ReadAllFile                         ();

    void                    Clean                               ();
                           
    XPATH                   xpath;
    XFILETXT*               xfiletxt;
    
    XVECTOR<CIPHERKEY*>     keys;
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

