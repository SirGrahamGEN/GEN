/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       CipherKey.h
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

#ifndef _CIPHERKEY_H_
#define _CIPHERKEY_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XBuffer.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum CIPHERKEYTYPE
{
  CIPHERKEYTYPE_UNKNOWN         = 0 ,
  CIPHERKEYTYPE_SYMMETRICAL         ,
  CIPHERKEYTYPE_PUBLIC              ,
  CIPHERKEYTYPE_PRIVATE             ,
  CIPHERKEYTYPE_CERTIFICATE   
};


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class CIPHERKEY
{
  public:
                          CIPHERKEY                 ();
    virtual              ~CIPHERKEY                 ();

    CIPHERKEYTYPE         GetType                   ();
    void                  SetType                   (CIPHERKEYTYPE type);

    virtual int           GetSizeInBytes            ();
    int                   GetSizeInBits             ();

    bool                  CopyFrom                  (CIPHERKEY* key);

  protected:

    CIPHERKEYTYPE         type;

private:

    void                  Clean                     ();
};



class CIPHERKEYSYMMETRICAL : public CIPHERKEY
{
  public:
                          CIPHERKEYSYMMETRICAL      ();
    virtual              ~CIPHERKEYSYMMETRICAL      ();

    XBYTE*                Get                       (int& size);
    XBUFFER*              Get                       ();

    bool                  Set                       (XBYTE* key, XDWORD size);
    bool                  Set                       (XBUFFER& key);

    int                   GetSizeInBytes            ();

    bool                  CopyFrom                  (CIPHERKEYSYMMETRICAL* key);                          

  private:

    void                  Clean                     ();
    
    XBUFFER*              xbufferkey;
};


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif
