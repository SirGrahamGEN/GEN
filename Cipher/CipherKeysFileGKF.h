/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       CipherKeysFileGKF.h
* 
* @class      CIPHERKEYSFILEGKF
* @brief      Cipher File Keys GKF (GEN Key File) class
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

#ifndef _CIPHERKEYSFILEGKF_H_
#define _CIPHERKEYSFILEGKF_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XVector.h"
#include "XDateTime.h"

#include "Cipher.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

#define CIPHERKEYSFILEGKF_EXT                            __L(".gkf")

#define CIPHERKEYSFILEGKF_NODENAME_ROOT                  __L("CIPHERKEYSFILE")
#define CIPHERKEYSFILEGKF_NODENAME_CREATOR               __L("CREATOR")
#define CIPHERKEYSFILEGKF_ATTRNAME_CREATOR_CREATENAME    __L("NAME")
#define CIPHERKEYSFILEGKF_ATTRNAME_CREATOR_CREATEDATE    __L("CREATED")
#define CIPHERKEYSFILEGKF_ATTRNAME_CREATOR_LASTMODDATE   __L("LASTMODIFIED")

#define CIPHERKEYSFILEGKF_NODENAME_CIPHERKEY             __L("CIPHERKEY")
#define CIPHERKEYSFILEGKF_ATTRNAME_CIPHERKEY_TYPEKEY     __L("TYPE")
#define CIPHERKEYSFILEGKF_ATTRNAME_CIPHERKEY_TYPECIPHER  __L("TYPECIPHER")
#define CIPHERKEYSFILEGKF_ATTRNAME_CIPHERKEY_SIZEBITS    __L("SIZEBITS")
#define CIPHERKEYSFILEGKF_ATTRNAME_CIPHERKEY_KEY         __L("KEY")
#define CIPHERKEYSFILEGKF_ATTRNAME_CIPHERKEY_MODULUS     __L("MODULUS")
#define CIPHERKEYSFILEGKF_ATTRNAME_CIPHERKEY_EXPONENT    __L("EXPONENT")
#define CIPHERKEYSFILEGKF_ATTRNAME_CIPHERKEY_FACTOR1     __L("1STPRIMEFACTOR")
#define CIPHERKEYSFILEGKF_ATTRNAME_CIPHERKEY_FACTOR2     __L("2NDPRIMEFACTOR")

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

class XFACTORY;
class CIPHERKEY;
class XFILEXML;

class CIPHERKEYSFILEGKF
{
  public:
                           CIPHERKEYSFILEGKF                (XPATH& xpath);
    virtual               ~CIPHERKEYSFILEGKF                ();

    XSTRING*               GetCreatorName                   ();
    XDATETIME*             GetCreatorDateTime               ();
    XDATETIME*             GetCreatorLastModifiedDateTime   ();

    bool                   HaveKey                          (CIPHERKEYTYPE type);
    CIPHERKEY*             GetKey                           (CIPHERKEYTYPE type);
    bool                   AddKey                           (CIPHERKEY& key);
    bool                   DeleteKey                        (CIPHERKEYTYPE type);
    bool                   DeleteAllKeys                    ();

    bool                   UpdateFile                       ();

    bool                   ExportToPEMFile                  (CIPHERKEY* key, XSTRING& publicPEM);
    bool                   ExportToPEMFile                  (CIPHERKEY* key, XPATH& xpath);

    XPATH&                 GetXPath                         ();
    XFILEXML*              GetXFileXML                      ();


  private:

    bool                   ReadAllFile                      ();

    void                   Clean                            ();
                           
    XPATH                  xpath;
    XFILEXML*              xfilexml;

    XSTRING                creatorname;
    XDATETIME              creatordatetime;
    XDATETIME              creatorlastmodifieddatetime;
    XVECTOR<CIPHERKEY*>    keys;
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

