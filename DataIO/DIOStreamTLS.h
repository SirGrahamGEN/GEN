/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOStreamTLS.h
*
* @class      DIOSTREAMTLS
* @brief      Data Input/Output Stream TLS (Transport Layer Security) class
* @ingroup    DATAIO
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

#ifndef _DIOSTREAMTLS_H_
#define _DIOSTREAMTLS_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XBuffer.h"

#include "DIOIP.h"
#include "DIOStreamTCPIP.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
      

#define DIOSTREAMTLS_VERSION_SSL_3_0                                      0x0300    // SSL v3.0
#define DIOSTREAMTLS_VERSION_TLS_1_0                                      0x0301    // TLS v1.0 
#define DIOSTREAMTLS_VERSION_TLS_1_1                                      0x0302    // TLS v1.1 
#define DIOSTREAMTLS_VERSION_TLS_1_2                                      0x0303    // TLS v1.2 

#define DIOSTREAMTLS_RANDOM_SIZE                                          32
#define DIOSTREAMTLS_SESSION_ID_SIZE                                      32

#define DIOSTREAMTLS_CIPHERSUITE_TLS_AES_128_GCM_SHA256                   0x1301    // TLSv1.3 
#define DIOSTREAMTLS_CIPHERSUITE_TLS_AES_256_GCM_SHA384                   0x1302    // TLSv1.3 
#define DIOSTREAMTLS_CIPHERSUITE_TLS_CHACHA20_POLY1305_SHA256             0x1303    // TLSv1.3 
#define DIOSTREAMTLS_CIPHERSUITE_ECDHE_ECDSA_AES128_GCM_SHA256            0xC02B    // TLSv1.2 
#define DIOSTREAMTLS_CIPHERSUITE_ECDHE_RSA_AES128_GCM_SHA256              0xC02F    // TLSv1.2 
#define DIOSTREAMTLS_CIPHERSUITE_ECDHE_ECDSA_AES256_GCM_SHA384            0xC02C    // TLSv1.2 
#define DIOSTREAMTLS_CIPHERSUITE_ECDHE_RSA_AES256_GCM_SHA384              0xC030    // TLSv1.2 
#define DIOSTREAMTLS_CIPHERSUITE_ECDHE_ECDSA_CHACHA20_POLY1305            0xCCA9    // TLSv1.2 
#define DIOSTREAMTLS_CIPHERSUITE_ECDHE_RSA_CHACHA20_POLY1305              0xCCA8    // TLSv1.2 
#define DIOSTREAMTLS_CIPHERSUITE_DHE_RSA_AES128_GCM_SHA256                0x009E    // TLSv1.2 
#define DIOSTREAMTLS_CIPHERSUITE_DHE_RSA_AES256_GCM_SHA384                0x009F    // TLSv1.2 
#define DIOSTREAMTLS_CIPHERSUITE_DHE_RSA_CHACHA20_POLY1305                0xCCAA    // TLSv1.2 
#define DIOSTREAMTLS_CIPHERSUITE_ECDHE_ECDSA_AES128_SHA256                0xC023    // TLSv1.2 
#define DIOSTREAMTLS_CIPHERSUITE_ECDHE_RSA_AES128_SHA256                  0xC027    // TLSv1.2 
#define DIOSTREAMTLS_CIPHERSUITE_ECDHE_ECDSA_AES128_SHA                   0xC009    // TLSv1   
#define DIOSTREAMTLS_CIPHERSUITE_ECDHE_RSA_AES128_SHA                     0xC013    // TLSv1   
#define DIOSTREAMTLS_CIPHERSUITE_ECDHE_ECDSA_AES256_SHA384                0xC024    // TLSv1.2 
#define DIOSTREAMTLS_CIPHERSUITE_ECDHE_RSA_AES256_SHA384                  0xC028    // TLSv1.2 
#define DIOSTREAMTLS_CIPHERSUITE_ECDHE_ECDSA_AES256_SHA                   0xC00A    // TLSv1   
#define DIOSTREAMTLS_CIPHERSUITE_ECDHE_RSA_AES256_SHA                     0xC014    // TLSv1   
#define DIOSTREAMTLS_CIPHERSUITE_DHE_RSA_AES128_SHA256                    0x0067    // TLSv1.2 
#define DIOSTREAMTLS_CIPHERSUITE_DHE_RSA_AES256_SHA256                    0x006B    // TLSv1.2 
#define DIOSTREAMTLS_CIPHERSUITE_AES128_GCM_SHA256                        0x009C    // TLSv1.2 
#define DIOSTREAMTLS_CIPHERSUITE_AES256_GCM_SHA384                        0x009D    // TLSv1.2 
#define DIOSTREAMTLS_CIPHERSUITE_AES128_SHA256                            0x003C    // TLSv1.2 
#define DIOSTREAMTLS_CIPHERSUITE_AES256_SHA256                            0x003D    // TLSv1.2 
#define DIOSTREAMTLS_CIPHERSUITE_AES128_SHA                               0x002F    // SSLv3   
#define DIOSTREAMTLS_CIPHERSUITE_AES256_SHA                               0x0035    // SSLv3   
#define DIOSTREAMTLS_CIPHERSUITE_DES_CBC3_SHA                             0x000A    // SSLv3   



enum DIOSTREAMTLS_CONTENTTYPE
{
   DIOSTREAMTLS_CONTENTTYPE_CHANGE_CIPHER_SPEC        =   20  , 
   DIOSTREAMTLS_CONTENTTYPE_ALERT                     =   21  , 
   DIOSTREAMTLS_CONTENTTYPE_HANDSHAKE                 =   22  ,
   DIOSTREAMTLS_CONTENTTYPE_APPLICATION_DATA          =   23        
};


enum DIOSTREAMTLS_HANDSHAKETYPE
{
  DIOSTREAMTLS_HANDSHAKETYPE_HELLO_REQUEST            =    0  , 
  DIOSTREAMTLS_HANDSHAKETYPE_CLIENT_HELLO             =    1  , 
  DIOSTREAMTLS_HANDSHAKETYPE_SERVER_HELLO             =    2  ,
  DIOSTREAMTLS_HANDSHAKETYPE_CERTIFICATE              =   11  , 
  DIOSTREAMTLS_HANDSHAKETYPE_SERVER_KEY_EXCHANGE      =   12  ,
  DIOSTREAMTLS_HANDSHAKETYPE_CERTIFICATE_REQUEST      =   13  , 
  DIOSTREAMTLS_HANDSHAKETYPE_SERVER_HELLO_DONE        =   14  ,
  DIOSTREAMTLS_HANDSHAKETYPE_CERTIFICATE_VERIFY       =   15  , 
  DIOSTREAMTLS_HANDSHAKETYPE_CLIENT_KEY_EXCHANGE      =   16  ,
  DIOSTREAMTLS_HANDSHAKETYPE_FINISHED                 =   20  , 
  DIOSTREAMTLS_HANDSHAKETYPE_KEY_UPDATE               =   24  ,
  DIOSTREAMTLS_HANDSHAKETYPE_message_hash             =  254  ,      
 };


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class DIOSTREAMTLSCONFIG;


class DIOSTREAMTLS : public DIOSTREAM
{
  public:
                                            DIOSTREAMTLS                  (DIOSTREAMTLSCONFIG* config);
    virtual                                ~DIOSTREAMTLS                  ();

    DIOSTREAMCONFIG*                        GetConfig                     ();
    bool                                    SetConfig                     (DIOSTREAMCONFIG* config);  

    bool                                    Open                          ();    

    XDWORD                                  Read                          (XBYTE* buffer, XDWORD size);
    XDWORD                                  Write                         (XBYTE* buffer, XDWORD size);

    bool                                    Disconnect                    ();

    bool                                    Close                         ();

    DIOSTREAMSTATUS                         GetConnectStatus              ();  

    bool                                    HandShake_Client_Hello        ();

    DIOSTREAMTCPIP*                         GetDIOStreamTCPIP             ();
    
  private:

    void                                    Clean                         ();

    DIOSTREAMTLSCONFIG*                     config;
    DIOSTREAMTCPIP*                         diostream;

    XBYTE                                   random[DIOSTREAMTLS_RANDOM_SIZE];
    XBYTE                                   sessionID[DIOSTREAMTLS_SESSION_ID_SIZE];
};



/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif


