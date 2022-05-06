/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       CipherFileKeys.h
* 
* @class      CIPHERFILEKEYS
* @brief      Cipher File Keys class
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

#ifndef _CIPHERFILEKEYS_H_
#define _CIPHERFILEKEYS_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XVector.h"
#include "XDateTime.h"

#include "Cipher.h"


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define CIPHERFILEKEYS_EXT                            __L(".key")

#define CIPHERFILEKEYS_NODENAME_ROOT                  __L("CIPHERKEYSFILE")
#define CIPHERFILEKEYS_NODENAME_CREATOR               __L("CREATOR")
#define CIPHERFILEKEYS_ATTRNAME_CREATOR_CREATENAME    __L("NAME")
#define CIPHERFILEKEYS_ATTRNAME_CREATOR_CREATEDATE    __L("CREATED")
#define CIPHERFILEKEYS_ATTRNAME_CREATOR_LASTMODDATE   __L("LASTMODIFIED")

#define CIPHERFILEKEYS_NODENAME_CIPHERKEY             __L("CIPHERKEY")
#define CIPHERFILEKEYS_ATTRNAME_CIPHERKEY_TYPEKEY     __L("TYPE")
#define CIPHERFILEKEYS_ATTRNAME_CIPHERKEY_TYPECIPHER  __L("TYPECIPHER")
#define CIPHERFILEKEYS_ATTRNAME_CIPHERKEY_SIZEBITS    __L("SIZEBITS")
#define CIPHERFILEKEYS_ATTRNAME_CIPHERKEY_KEY         __L("KEY")
#define CIPHERFILEKEYS_ATTRNAME_CIPHERKEY_MODULUS     __L("MODULUS")
#define CIPHERFILEKEYS_ATTRNAME_CIPHERKEY_EXPONENT    __L("EXPONENT")
#define CIPHERFILEKEYS_ATTRNAME_CIPHERKEY_FACTOR1     __L("1STPRIMEFACTOR")
#define CIPHERFILEKEYS_ATTRNAME_CIPHERKEY_FACTOR2     __L("2NDPRIMEFACTOR")

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XFACTORY;
class CIPHERKEY;
class XFILEXML;

class CIPHERFILEKEYS
{
  public:
                           CIPHERFILEKEYS                 (XPATH& xpath);
    virtual               ~CIPHERFILEKEYS                 ();

    XSTRING*               GetCreatorName                 ();
    XDATETIME*             GetCreatorDateTime             ();
    XDATETIME*             GetCreatorLastModifiedDateTime ();

    bool                   HaveKey                        (CIPHERKEYTYPE type);
    CIPHERKEY*             GetKey                         (CIPHERKEYTYPE type);
    bool                   AddKey                         (CIPHERKEY& key);
    bool                   DeleteKey                      (CIPHERKEYTYPE type);
    bool                   DeleteAllKeys                  ();

    bool                   UpdateFile                     ();

    bool                   ExportToPEMFile                (CIPHERKEY* key, XSTRING& publicPEM);
    bool                   ExportToPEMFile                (CIPHERKEY* key, XPATH& xpath);

    XPATH&                 GetXPath                       ();
    XFILEXML*              GetXFileXML                    ();


  private:

    bool                   ReadAllFile                    ();

    void                   Clean                          ();
                           
    XPATH                  xpath;
    XFILEXML*              xfilexml;

    XSTRING                creatorname;
    XDATETIME              creatordatetime;
    XDATETIME              creatorlastmodifieddatetime;
    XVECTOR<CIPHERKEY*>    keys;
};


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif
