/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       CipherFileKeys.h
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

#include "XVector.h"
#include "XDateTime.h"

#include "CipherKey.h"


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define CIPHERKEYSFILEPEM_EXT           __L(".PEM")

#define CIPHERKEYSFILEPEM_BEGINKEY      __L("-----BEGIN ")
#define CIPHERKEYSFILEPEM_ENDKEY        __L("-----END ")
#define CIPHERKEYSFILEPEM_FINISH        __L("-----")

#define CIPHERKEYSFILEPEM_PUBLIC        __L("PUBLIC")
#define CIPHERKEYSFILEPEM_PRIVATE       __L("PRIVATE")
#define CIPHERKEYSFILEPEM_CERTIFICATE   __L("CERTIFICATE")


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XFACTORY;
class CIPHERKEY;
class XFILEXML;

class CIPHERKEYSFILEPEM
{
  public:
                           CIPHERKEYSFILEPEM                (XPATH& xpath);
    virtual               ~CIPHERKEYSFILEPEM                ();
   
    bool                   HaveKey                          (CIPHERKEYTYPE type);
    CIPHERKEY*             GetKey                           (CIPHERKEYTYPE type);
    bool                   AddKey                           (CIPHERKEY& key);
    bool                   DeleteKey                        (CIPHERKEYTYPE type);
    bool                   DeleteAllKeys                    ();

    XPATH&                 GetXPath                         ();
    XFILETXT*              GetXFileTXT                      ();

  private:

    bool                   ReadAllFile                      ();

    void                   Clean                            ();
                           
    XPATH                  xpath;
    XFILETXT*              xfiletxt;
    
    XVECTOR<CIPHERKEY*>    keys;
};


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif
