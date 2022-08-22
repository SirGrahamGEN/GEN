/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       CipherCurve25519.h
* 
* @class      CIPHERCURVE25519
* @brief      Cipher Curve25519 class
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

#ifndef _CIPHERCURVE25519_H_
#define _CIPHERCURVE25519_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum CIPHERCURVE25519_TYPEKEY  
{
  CIPHERCURVE25519_TYPEKEY_PRIVATE    = 0 ,
  CIPHERCURVE25519_TYPEKEY_PUBLIC         ,
  CIPHERCURVE25519_TYPEKEY_SHARED         ,

  CIPHERCURVE25519_MAXKEYS
};  

#define CIPHERCURVE25519_MAXKEY  32

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class CIPHERCURVE25519
{
  public:
                            CIPHERCURVE25519          ();
    virtual                ~CIPHERCURVE25519          ();

    bool                    GenerateRandomPrivateKey  ();
    bool                    CreatePublicKey           ();
    bool                    CreateSharedKey           (XBYTE publickey[CIPHERCURVE25519_MAXKEY]);

    XBYTE*                  GetKey                    (CIPHERCURVE25519_TYPEKEY typekey);
    bool                    IsKeyCreated              (CIPHERCURVE25519_TYPEKEY typekey);
    void                    CleanAllKeys              ();
    
  private:

    static void             fsum                      (XQWORDSIG* output, const XQWORDSIG* in);
    static void             fdifference               (XQWORDSIG* output, const XQWORDSIG* in); 
    static void             fscalar_product           (XQWORDSIG* output, const XQWORDSIG* in, const XQWORDSIG scalar);
    static void             fproduct                  (XQWORDSIG* output, const XQWORDSIG* in2, const XQWORDSIG* in);
    static void             freduce_degree            (XQWORDSIG* output);

    static XQWORDSIG        div_by_2_26               (const XQWORDSIG v);
    static XQWORDSIG        div_by_2_25               (const XQWORDSIG v);
    static XDWORDSIG        div_s32_by_2_25           (const XDWORDSIG v);

    static void             freduce_coefficients      (XQWORDSIG* output);
    static void             fmul                      (XQWORDSIG* output, const XQWORDSIG* in, const XQWORDSIG* in2);
    static void             fsquare_inner             (XQWORDSIG* output, const XQWORDSIG* in);
    static void             fsquare                   (XQWORDSIG* output, const XQWORDSIG* in);
    static void             fexpand                   (XQWORDSIG* output, const XBYTE* input);
    static void             fcontract                 (XBYTE *output, XQWORDSIG* input);

    static void             fmonty                    (XQWORDSIG* x2, XQWORDSIG* z2,          // output 2Q 
                                                       XQWORDSIG* x3, XQWORDSIG* z3,          // output Q + Q' 
                                                       XQWORDSIG* x, XQWORDSIG* z,            // input Q 
                                                       XQWORDSIG* xprime, XQWORDSIG* zprime,  // input Q' 
                                                       const XQWORDSIG* qmqp                  // input Q - Q'
                                                      ); 

    static void             swap_conditional          (XQWORDSIG a[19], XQWORDSIG b[19], XQWORDSIG iswap);
    static void             cmult                     (XQWORDSIG* resultx, XQWORDSIG* resultz, const XBYTE* n, const XQWORDSIG* q);
    static void             crecip                    (XQWORDSIG* out, const XQWORDSIG* z); 

    void                    curve25519                (XBYTE* mypublic, const XBYTE* secret, const XBYTE* basepoint);


    void                    Clean                     ();  

    static const XBYTE      basepoint[CIPHERCURVE25519_MAXKEY]; 

    XBYTE                   keys[CIPHERCURVE25519_MAXKEYS][CIPHERCURVE25519_MAXKEY];    
};

/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif


