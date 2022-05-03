//------------------------------------------------------------------------------------------
//  CIPHERRSA.H
//
/**
// \class
//
//  Cipher / Uncipher RSA Class
//
//  ""
//  @version 25/04/2002
*/
//  GEN  Copyright (C).  All right reserved.
//------------------------------------------------------------------------------------------

#ifndef _CIPHERRSA_H_
#define _CIPHERRSA_H_


//---- INCLUDES ----------------------------------------------------------------------------

#include "XMPInteger.h"

#include "Cipher.h"


//---- DEFINES & ENUMS  --------------------------------------------------------------------

enum CIPHERRSAPKCS1VERSION
{
  CIPHERRSAPKCS1VERSIONV15    = 0 ,
  CIPHERRSAPKCS1VERSIONV21
};

#define CIPHERRSA_SINGDATA        1
#define CIPHERRSA_CIPHERDATA      2


//#define CIPHERRSA_RSANOCRT

//---- CLASS -------------------------------------------------------------------------------

class XRAND;
class HASH;


class CIPHERKEYRSAPUBLIC : public CIPHERKEY
{
  public:
                                    CIPHERKEYRSAPUBLIC                ();
    virtual                        ~CIPHERKEYRSAPUBLIC                ();

    bool                            Get                               (XMPINTEGER& modulus, XMPINTEGER& exponent);
    bool                            Set                               (XMPINTEGER& modulus, XMPINTEGER& exponent);

    int                             GetSizeInBytes                    ();

    bool                            CopyFrom                          (CIPHERKEYRSAPUBLIC* key);
    
    bool                            Check                             ();


  private:

    void                            Clean                             ();

    XMPINTEGER                      modulus;
    XMPINTEGER                      exponent;
};


class CIPHERKEYRSAPRIVATE : public CIPHERKEY
{
  public:
                                    CIPHERKEYRSAPRIVATE               ();
    virtual                        ~CIPHERKEYRSAPRIVATE               ();

    bool                            Get                               (XMPINTEGER& prime1factor, XMPINTEGER& prime2factor, XMPINTEGER& exponent);
    bool                            Set                               (XMPINTEGER& prime1factor, XMPINTEGER& prime2factor, XMPINTEGER& exponent);

    int                             GetSizeInBytes                    ();

    bool                            CopyFrom                          (CIPHERKEYRSAPRIVATE* key);
    
    bool                            Check                             (CIPHERKEYRSAPUBLIC& publickey);

  private:

    void                            Clean                             ();

    XMPINTEGER                      prime1factor;
    XMPINTEGER                      prime2factor;
    XMPINTEGER                      exponent;
};


class CIPHERRSA_CONTEXT
{
  public:
                                    CIPHERRSA_CONTEXT                 ();  
    virtual                        ~CIPHERRSA_CONTEXT                 ();
                                    
    void                            Ini                               ();
    
    void                            End                               ();
    

    void                            Clean                             ();
                                    
    size_t                          len;                              // size(N) in chars

    XMPINTEGER                      N;                                // public modulus
    XMPINTEGER                      E;                                // public exponent

    XMPINTEGER                      D;                                // private exponent
    XMPINTEGER                      P;                                // 1st prime factor
    XMPINTEGER                      Q;                                // 2nd prime factor
    XMPINTEGER                      DP;                               // D % (P - 1)
    XMPINTEGER                      DQ;                               // D % (Q - 1)
    XMPINTEGER                      QP;                               // 1 / (Q % P)

    XMPINTEGER                      RN;                               // cached R^2 mod N
    XMPINTEGER                      RP;                               // cached R^2 mod P
    XMPINTEGER                      RQ;                               // cached R^2 mod Q

    #if !defined(CIPHERRSA_RSANOCRT)
    XMPINTEGER                      Vi;                               // cached blinding value
    XMPINTEGER                      Vf;                               // cached un-blinding value
    #endif

    int                             padding;                          // RSA_PKCS_V15 for 1.5 padding and RSA_PKCS_v21 for OAEP/PSS
    int                             hashID;                           // Hash identifier of md_type_t as specified in the md.h header file for the EME-OAEP and EMSA-PSS encoding

};




class CIPHERRSA : public CIPHER
{
  public:

                                    CIPHERRSA                         ();
    virtual                        ~CIPHERRSA                         ();

    using                           CIPHER::Cipher;
    using                           CIPHER::Uncipher;

    bool                            SetKey                            (CIPHERKEY* key, bool integritycheck = false);

    bool                            Cipher                            (XBYTE* input, XDWORD size, CIPHERKEYTYPE keytouse, CIPHERRSAPKCS1VERSION pkcs1version = CIPHERRSAPKCS1VERSIONV15);
    bool                            Cipher                            (XBUFFER& input, CIPHERKEYTYPE keytouse, CIPHERRSAPKCS1VERSION pkcs1version = CIPHERRSAPKCS1VERSIONV15);

    bool                            Uncipher                          (XBYTE* input, XDWORD size, CIPHERKEYTYPE keytouse, CIPHERRSAPKCS1VERSION pkcs1version = CIPHERRSAPKCS1VERSIONV15);
    bool                            Uncipher                          (XBUFFER& input, CIPHERKEYTYPE keytouse, CIPHERRSAPKCS1VERSION pkcs1version = CIPHERRSAPKCS1VERSIONV15);

    bool                            Sign                              (XBYTE* input, XDWORD size, CIPHERKEYTYPE keytouse, HASH* hash, CIPHERRSAPKCS1VERSION pkcs1version = CIPHERRSAPKCS1VERSIONV15);
    bool                            Sign                              (XBUFFER& input, CIPHERKEYTYPE keytouse, HASH* hash, CIPHERRSAPKCS1VERSION pkcs1version = CIPHERRSAPKCS1VERSIONV15);


    static CIPHERRSA*               GetInstance                       ();
    XRAND*                          GetXRand                          ();
    bool                            GenerateKeys                      (XDWORD nbits, int exponent, CIPHERKEYRSAPUBLIC& publickey, CIPHERKEYRSAPRIVATE& privatekey, XMPINTEGER_FUNCRANDOM funcrandom = NULL, void* paramrandom = NULL);

  private:


    bool                            CheckContextPublicKey             ();
    bool                            CheckContextPrivateKey            ();

    bool                            Cipher_PKCS1_V15                  (XBYTE* buffer, XDWORD size, XBUFFER& output, CIPHERKEYTYPE keytypetouse, CIPHERRSAPKCS1VERSION pkcs1version,  XMPINTEGER_FUNCRANDOM funcrandom, void* paramrandom);
    bool                            Uncipher_PKCS1_V15                (XBYTE* buffer, XDWORD size, XBUFFER& output, CIPHERKEYTYPE keytypetouse, CIPHERRSAPKCS1VERSION pkcs1version,  XMPINTEGER_FUNCRANDOM funcrandom, void* paramrandom);

    bool                            DoRSAPublicOperation              (XBUFFER& input, XBUFFER& output);
    bool                            DoRSAPrivateOperation             (XBUFFER& input, XBUFFER& output, XMPINTEGER_FUNCRANDOM funcrandom, void* paramrandom);

    #if !defined(CIPHERRSA_RSANOCRT)
    bool                            PrepareBlinding                   (XMPINTEGER* Vi, XMPINTEGER* Vf, XMPINTEGER_FUNCRANDOM funcrandom, void* paramrandom);
    #endif

    int                             GetKeySizeInBytes                 (CIPHERKEYTYPE keytouse);

    static bool                     GenerateRandom                    (XBYTE* buffer, XDWORD size, void* param);    

    void                            Clean                             ();


    static CIPHERRSA*               instance;
    CIPHERRSA_CONTEXT               context;
    XRAND*                          xrand;
};



//---- INLINE FUNCTIONS --------------------------------------------------------------------



#endif

