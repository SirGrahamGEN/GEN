/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       HashSHA1.h
* 
* @class      HASHSHA1
* @brief      Hash SHA1 class
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

#ifndef _HASHSHA1_H_
#define _HASHSHA1_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "Hash.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

class HASHSHA1 : public HASH
{
  public:
                      HASHSHA1                  ();
    virtual          ~HASHSHA1                  ();

    using             HASH::Do;
    bool              Do                        (XBYTE* input, XQWORD size);

    int               GetDefaultSize            ();

  private:
   
    void              Reset                     ();

    void              Input                     (XBYTE* input, XQWORD length);

    void              ProcessMessageBlock       ();
    void              PadMessage                ();
    XDWORD            CircularShift             (int bits, XDWORD word);

    bool              Result                    (XDWORD* msgdigest); 

    void              Clean                     (); 

     XDWORD           H[5];                     // Message digest buffers

     XDWORD           lengthlow;                // Message length in bits
     XDWORD           lengthhigh;               // Message length in bits

     XBYTE            msgblock[64];             // 512-bit message blocks
     int              msgblockindex;            // Index into message block array

     bool             computed;                 // Is the digest computed?
     bool             corrupted;                // Is the message digest corrupe
};

#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif
