/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XASN1.cpp
* 
* @class      XASN1
* @brief      eXtended ANS.1 format buffer (Abstract Syntax Notation One, defined in X.208)
* @ingroup    XUTILS
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XBer.h"
#include "XTrace.h"

#include "XASN1.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

XASN1_OID_PROPERTY XASN1::OID_properties[] = {  { __L("0.4.0.1862.1.1"),                    __L("QcCompliance")                                   , false },
                                                { __L("0.4.0.1862.1.2"),                    __L("QcLimitValue")                                   , false },
                                                { __L("0.4.0.1862.1.3"),                    __L("QcRetentionPeriod")                              , false },
                                                { __L("0.4.0.1862.1.4"),                    __L("QcSSCD")                                         , false },
                                                { __L("0.4.0.1862.1.5"),                    __L("QcPDS")                                          , false },
                                                { __L("0.4.0.1862.1.6"),                    __L("QcType")                                         , false },
                                                { __L("0.4.0.1862.1.6.1"),                  __L("esign")                                          , false },
                                                { __L("0.4.0.1862.1.6.2"),                  __L("eseal")                                          , false },
                                                { __L("0.4.0.1862.1.6.3"),                  __L("web")                                            , false },
                                                { __L("0.4.0.19495.1"),                     __L("RoleOfPsp")                                      , false },
                                                { __L("0.4.0.19495.1.1"),                   __L("PSP_AS")                                         , false },
                                                { __L("0.4.0.19495.1.2"),                   __L("PSP_PI")                                         , false },
                                                { __L("0.4.0.19495.1.3"),                   __L("PSP_AI")                                         , false },
                                                { __L("0.4.0.19495.1.4"),                   __L("PSP_IC")                                         , false },
                                                { __L("0.4.0.19495.2"),                     __L("PSD2 qcstatement")                               , false },
                                                { __L("0.4.0.194112.1.0"),                  __L("QCP-n")                                          , false },
                                                { __L("0.4.0.194112.1.1"),                  __L("QCP-l")                                          , false },
                                                { __L("0.4.0.194112.1.2"),                  __L("QCP-n-qscd")                                     , false },
                                                { __L("0.4.0.194112.1.3"),                  __L("QCP-l-qscd")                                     , false },
                                                { __L("0.4.0.194112.1.4"),                  __L("QCP-w")                                          , false },
                                                { __L("0.9.2342.19200300.100.1.25"),        __L("domainComponent")                                , false },
                                                { __L("1.2.36.68980861.1.1.10"),            __L("Signet pilot")                                   , false },
                                                { __L("1.2.36.68980861.1.1.11"),            __L("Signet intraNet")                                , false },
                                                { __L("1.2.36.68980861.1.1.2"),             __L("Signet personal")                                , false },
                                                { __L("1.2.36.68980861.1.1.20"),            __L("Signet securityPolicy")                          , false },
                                                { __L("1.2.36.68980861.1.1.3"),             __L("Signet business")                                , false },
                                                { __L("1.2.36.68980861.1.1.4"),             __L("Signet legal")                                   , false },
                                                { __L("1.2.36.75878867.1.100.1.1"),         __L("Certificates Australia policyIdentifier")        , false },
                                                { __L("1.2.752.34.1"),                      __L("seis-cp")                                        , false },
                                                { __L("1.2.752.34.1.1"),                    __L("SEIS certificatePolicy-s10")                     , false },
                                                { __L("1.2.752.34.2"),                      __L("SEIS pe")                                        , false },
                                                { __L("1.2.752.34.3"),                      __L("SEIS at")                                        , false },
                                                { __L("1.2.752.34.3.1"),                    __L("SEIS at-personalIdentifier")                     , false },
                                                { __L("1.2.840.10040.2.1"),                 __L("holdinstruction-none")                           , false },
                                                { __L("1.2.840.10040.2.2"),                 __L("holdinstruction-callissuer")                     , false },
                                                { __L("1.2.840.10040.2.3"),                 __L("holdinstruction-reject")                         , false },
                                                { __L("1.2.840.10040.4.1"),                 __L("dsa")                                            , false },
                                                { __L("1.2.840.10040.4.3"),                 __L("dsaWithSha1")                                    , false },
                                                { __L("1.2.840.10045.1"),                   __L("fieldType")                                      , false },
                                                { __L("1.2.840.10045.1.1"),                 __L("prime-field")                                    , false },
                                                { __L("1.2.840.10045.1.2"),                 __L("characteristic-two-field")                       , false },
                                                { __L("1.2.840.10045.1.2.1"),               __L("ecPublicKey")                                    , false },
                                                { __L("1.2.840.10045.1.2.3"),               __L("characteristic-two-basis")                       , false },
                                                { __L("1.2.840.10045.1.2.3.1"),             __L("onBasis")                                        , false },
                                                { __L("1.2.840.10045.1.2.3.2"),             __L("tpBasis")                                        , false },
                                                { __L("1.2.840.10045.1.2.3.3"),             __L("ppBasis")                                        , false },
                                                { __L("1.2.840.10045.2"),                   __L("publicKeyType")                                  , false },
                                                { __L("1.2.840.10045.2.1"),                 __L("ecPublicKey")                                    , false },
                                                { __L("1.2.840.10046.2.1"),                 __L("dhPublicNumber")                                 , false },
                                                { __L("1.2.840.113533.7"),                  __L("nsn")                                            , false },
                                                { __L("1.2.840.113533.7.65"),               __L("nsn-ce")                                         , false },
                                                { __L("1.2.840.113533.7.65.0"),             __L("entrustVersInfo")                                , false },
                                                { __L("1.2.840.113533.7.66"),               __L("nsn-alg")                                        , false },
                                                { __L("1.2.840.113533.7.66.10"),            __L("cast5CBC")                                       , false },
                                                { __L("1.2.840.113533.7.66.11"),            __L("cast5MAC")                                       , false },
                                                { __L("1.2.840.113533.7.66.12"),            __L("pbeWithMD5AndCAST5-CBC")                         , false },
                                                { __L("1.2.840.113533.7.66.13"),            __L("passwordBasedMac")                               , false },
                                                { __L("1.2.840.113533.7.66.3"),             __L("cast3CBC")                                       , false },
                                                { __L("1.2.840.113533.7.67"),               __L("nsn-oc")                                         , false },
                                                { __L("1.2.840.113533.7.67.0"),             __L("entrustUser")                                    , false },
                                                { __L("1.2.840.113533.7.68"),               __L("nsn-at")                                         , false },
                                                { __L("1.2.840.113533.7.68.0"),             __L("entrustCAInfo")                                  , false },
                                                { __L("1.2.840.113533.7.68.10"),            __L("attributeCertificate")                           , false },
                                                { __L("1.2.840.113549.1.1"),                __L("pkcs-1")                                         , false },
                                                { __L("1.2.840.113549.1.1.1"),              __L("rsaEncryption")                                  , true  },
                                                { __L("1.2.840.113549.1.1.2"),              __L("md2withRSAEncryption")                           , false },
                                                { __L("1.2.840.113549.1.1.3"),              __L("md4withRSAEncryption")                           , false },
                                                { __L("1.2.840.113549.1.1.4"),              __L("md5withRSAEncryption")                           , false },
                                                { __L("1.2.840.113549.1.1.5"),              __L("sha1withRSAEncryption")                          , false },
                                                { __L("1.2.840.113549.1.1.6"),              __L("rsaOAEPEncryptionSET")                           , false },
                                                { __L("1.2.840.113549.1.12"),               __L("pkcs-12")                                        , false },
                                                { __L("1.2.840.113549.1.12.1"),             __L("pkcs-12-PbeIds")                                 , false },
                                                { __L("1.2.840.113549.1.12.1.1"),           __L("pbeWithSHAAnd128BitRC4")                         , false },
                                                { __L("1.2.840.113549.1.12.1.2"),           __L("pbeWithSHAAnd40BitRC4")                          , false },
                                                { __L("1.2.840.113549.1.12.1.3"),           __L("pbeWithSHAAnd3-KeyTripleDES-CBC")                , false },
                                                { __L("1.2.840.113549.1.12.1.4"),           __L("pbeWithSHAAnd2-KeyTripleDES-CBC")                , false },
                                                { __L("1.2.840.113549.1.12.1.5"),           __L("pbeWithSHAAnd128BitRC2-CBC")                     , false },
                                                { __L("1.2.840.113549.1.12.1.6"),           __L("pbeWithSHAAnd40BitRC2-CBC")                      , false },
                                                { __L("1.2.840.113549.1.12.10"),            __L("pkcs-12Version1")                                , false },
                                                { __L("1.2.840.113549.1.12.10.1"),          __L("pkcs-12BadIds")                                  , false },
                                                { __L("1.2.840.113549.1.12.10.1.1"),        __L("pkcs-12-keyBag")                                 , false },
                                                { __L("1.2.840.113549.1.12.10.1.2"),        __L("pkcs-12-pkcs-8ShroudedKeyBag")                   , false },
                                                { __L("1.2.840.113549.1.12.10.1.3"),        __L("pkcs-12-certBag")                                , false },
                                                { __L("1.2.840.113549.1.12.10.1.4"),        __L("pkcs-12-crlBag")                                 , false },
                                                { __L("1.2.840.113549.1.12.10.1.5"),        __L("pkcs-12-secretBag")                              , false },
                                                { __L("1.2.840.113549.1.12.10.1.6"),        __L("pkcs-12-safeContentsBag")                        , false },
                                                { __L("1.2.840.113549.1.12.2"),             __L("pkcs-12-ESPVKID")                                , false },
                                                { __L("1.2.840.113549.1.12.2.1"),           __L("pkcs-12-PKCS8KeyShrouding")                      , false },
                                                { __L("1.2.840.113549.1.12.3"),             __L("pkcs-12-BagIds")                                 , false },
                                                { __L("1.2.840.113549.1.12.3.1"),           __L("pkcs-12-keyBagId")                               , false },
                                                { __L("1.2.840.113549.1.12.3.2"),           __L("pkcs-12-certAndCRLBagId")                        , false },
                                                { __L("1.2.840.113549.1.12.3.3"),           __L("pkcs-12-secretBagId")                            , false },
                                                { __L("1.2.840.113549.1.12.3.4"),           __L("pkcs-12-safeContentsId")                         , false },
                                                { __L("1.2.840.113549.1.12.3.5"),           __L("pkcs-12-pkcs-8ShroudedKeyBagId")                 , false },
                                                { __L("1.2.840.113549.1.12.4"),             __L("pkcs-12-CertBagID")                              , false },
                                                { __L("1.2.840.113549.1.12.4.1"),           __L("pkcs-12-X509CertCRLBagID")                       , false },
                                                { __L("1.2.840.113549.1.12.4.2"),           __L("pkcs-12-SDSICertBagID")                          , false },
                                                { __L("1.2.840.113549.1.12.5"),             __L("pkcs-12-OID")                                    , false },
                                                { __L("1.2.840.113549.1.12.5.1"),           __L("pkcs-12-PBEID")                                  , false },
                                                { __L("1.2.840.113549.1.12.5.1.1"),         __L("pkcs-12-PBEWithSha1And128BitRC4")                , false },
                                                { __L("1.2.840.113549.1.12.5.1.2"),         __L("pkcs-12-PBEWithSha1And40BitRC4")                 , false },
                                                { __L("1.2.840.113549.1.12.5.1.3"),         __L("pkcs-12-PBEWithSha1AndTripleDESCBC")             , false },
                                                { __L("1.2.840.113549.1.12.5.1.4"),         __L("pkcs-12-PBEWithSha1And128BitRC2CBC")             , false },
                                                { __L("1.2.840.113549.1.12.5.1.5"),         __L("pkcs-12-PBEWithSha1And40BitRC2CBC")              , false },
                                                { __L("1.2.840.113549.1.12.5.1.6"),         __L("pkcs-12-PBEWithSha1AndRC4")                      , false },
                                                { __L("1.2.840.113549.1.12.5.1.7"),         __L("pkcs-12-PBEWithSha1AndRC2CBC")                   , false },
                                                { __L("1.2.840.113549.1.12.5.2"),           __L("pkcs-12-EnvelopingID")                           , false },
                                                { __L("1.2.840.113549.1.12.5.2.1"),         __L("pkcs-12-RSAEncryptionWith128BitRC4")             , false },
                                                { __L("1.2.840.113549.1.12.5.2.2"),         __L("pkcs-12-RSAEncryptionWith40BitRC4")              , false },
                                                { __L("1.2.840.113549.1.12.5.2.3"),         __L("pkcs-12-RSAEncryptionWithTripleDES")             , false },
                                                { __L("1.2.840.113549.1.12.5.3"),           __L("pkcs-12-SignatureID")                            , false },
                                                { __L("1.2.840.113549.1.12.5.3.1"),         __L("pkcs-12-RSASignatureWithSHA1Digest")             , false },
                                                { __L("1.2.840.113549.1.3"),                __L("pkcs-3")                                         , false },
                                                { __L("1.2.840.113549.1.3.1"),              __L("dhKeyAgreement")                                 , false },
                                                { __L("1.2.840.113549.1.5"),                __L("pkcs-5")                                         , false },
                                                { __L("1.2.840.113549.1.5.1"),              __L("pbeWithMD2AndDES-CBC")                           , false },
                                                { __L("1.2.840.113549.1.5.10"),             __L("pbeWithSHAAndDES-CBC")                           , false },
                                                { __L("1.2.840.113549.1.5.3"),              __L("pbeWithMD5AndDES-CBC")                           , false },
                                                { __L("1.2.840.113549.1.5.4"),              __L("pbeWithMD2AndRC2-CBC")                           , false },
                                                { __L("1.2.840.113549.1.5.6"),              __L("pbeWithMD5AndRC2-CBC")                           , false },
                                                { __L("1.2.840.113549.1.5.9"),              __L("pbeWithMD5AndXOR")                               , false },
                                                { __L("1.2.840.113549.1.7"),                __L("pkcs-7")                                         , false },
                                                { __L("1.2.840.113549.1.7.1"),              __L("data")                                           , false },
                                                { __L("1.2.840.113549.1.7.2"),              __L("signedData")                                     , false },
                                                { __L("1.2.840.113549.1.7.3"),              __L("envelopedData")                                  , false },
                                                { __L("1.2.840.113549.1.7.4"),              __L("signedAndEnvelopedData")                         , false },
                                                { __L("1.2.840.113549.1.7.5"),              __L("digestData")                                     , false },
                                                { __L("1.2.840.113549.1.7.6"),              __L("encryptedData")                                  , false },
                                                { __L("1.2.840.113549.1.7.7"),              __L("dataWithAttributes")                             , false },
                                                { __L("1.2.840.113549.1.7.8"),              __L("encryptedPrivateKeyInfo")                        , false },
                                                { __L("1.2.840.113549.1.9"),                __L("pkcs-9")                                         , false },
                                                { __L("1.2.840.113549.1.9.1"),              __L("emailAddress")                                   , false },
                                                { __L("1.2.840.113549.1.9.2"),              __L("unstructuredName")                               , false },
                                                { __L("1.2.840.113549.1.9.3"),              __L("contentType")                                    , false },
                                                { __L("1.2.840.113549.1.9.4"),              __L("messageDigest")                                  , false },
                                                { __L("1.2.840.113549.1.9.5"),              __L("signingTime")                                    , false },
                                                { __L("1.2.840.113549.1.9.6"),              __L("countersignature")                               , false },
                                                { __L("1.2.840.113549.1.9.7"),              __L("challengePassword")                              , false },
                                                { __L("1.2.840.113549.1.9.8"),              __L("unstructuredAddress")                            , false },
                                                { __L("1.2.840.113549.1.9.9"),              __L("extendedCertificateAttributes")                  , false },
                                                { __L("1.2.840.113549.1.9.10"),             __L("issuerAndSerialNumber")                          , false },
                                                { __L("1.2.840.113549.1.9.11"),             __L("passwordCheck")                                  , false },
                                                { __L("1.2.840.113549.1.9.12"),             __L("publicKey")                                      , false },
                                                { __L("1.2.840.113549.1.9.13"),             __L("signingDescription")                             , false },
                                                { __L("1.2.840.113549.1.9.14"),             __L("extensionReq")                                   , false },
                                                { __L("1.2.840.113549.1.9.15"),             __L("sMIMECapabilities")                              , false },
                                                { __L("1.2.840.113549.1.9.15.1"),           __L("preferSignedData")                               , false },
                                                { __L("1.2.840.113549.1.9.15.2"),           __L("canNotDecryptAny")                               , false },
                                                { __L("1.2.840.113549.1.9.15.3"),           __L("receiptRequest")                                 , false },
                                                { __L("1.2.840.113549.1.9.15.4"),           __L("receipt")                                        , false },
                                                { __L("1.2.840.113549.1.9.15.5"),           __L("contentHints")                                   , false },
                                                { __L("1.2.840.113549.1.9.15.6"),           __L("mlExpansionHistory")                             , false },
                                                { __L("1.2.840.113549.1.9.16"),             __L("id-sMIME")                                       , false },
                                                { __L("1.2.840.113549.1.9.16.0"),           __L("id-mod")                                         , false },
                                                { __L("1.2.840.113549.1.9.16.0.1"),         __L("id-mod-cms")                                     , false },
                                                { __L("1.2.840.113549.1.9.16.0.2"),         __L("id-mod-ess")                                     , false },
                                                { __L("1.2.840.113549.1.9.16.1"),           __L("id-ct")                                          , false },
                                                { __L("1.2.840.113549.1.9.16.1.1"),         __L("id-ct-receipt")                                  , false },
                                                { __L("1.2.840.113549.1.9.16.1.4"),         __L("Timestamp Token")                                , false },
                                                { __L("1.2.840.113549.1.9.16.2"),           __L("id-aa")                                          , false },
                                                { __L("1.2.840.113549.1.9.16.2.1"),         __L("id-aa-receiptRequest")                           , false },
                                                { __L("1.2.840.113549.1.9.16.2.2"),         __L("id-aa-securityLabel")                            , false },
                                                { __L("1.2.840.113549.1.9.16.2.3"),         __L("id-aa-mlExpandHistory")                          , false },
                                                { __L("1.2.840.113549.1.9.16.2.4"),         __L("id-aa-contentHint")                              , false },
                                                { __L("1.2.840.113549.1.9.16.2.47"),        __L("Signing certificate V2")                         , false },
                                                { __L("1.2.840.113549.1.9.20"),             __L("friendlyName")                                   , false },
                                                { __L("1.2.840.113549.1.9.21"),             __L("localKeyID")                                     , false },
                                                { __L("1.2.840.113549.1.9.22"),             __L("certTypes")                                      , false },
                                                { __L("1.2.840.113549.1.9.22.1"),           __L("x509Certificate")                                , false },
                                                { __L("1.2.840.113549.1.9.22.2"),           __L("sdsiCertificate")                                , false },
                                                { __L("1.2.840.113549.1.9.23"),             __L("crlTypes")                                       , false },
                                                { __L("1.2.840.113549.1.9.23.1"),           __L("x509Crl")                                        , false },
                                                { __L("1.2.840.113549.2"),                  __L("digestAlgorithm")                                , false },
                                                { __L("1.2.840.113549.2.2"),                __L("md2")                                            , false },
                                                { __L("1.2.840.113549.2.4"),                __L("md4")                                            , false },
                                                { __L("1.2.840.113549.2.5"),                __L("md5")                                            , false },
                                                { __L("1.2.840.113549.3"),                  __L("encryptionAlgorithm")                            , false },
                                                { __L("1.2.840.113549.3.10"),               __L("desCDMF")                                        , false },
                                                { __L("1.2.840.113549.3.2"),                __L("rc2CBC")                                         , false },
                                                { __L("1.2.840.113549.3.3"),                __L("rc2ECB")                                         , false },
                                                { __L("1.2.840.113549.3.4"),                __L("rc4")                                            , false },
                                                { __L("1.2.840.113549.3.5"),                __L("rc4WithMAC")                                     , false },
                                                { __L("1.2.840.113549.3.6"),                __L("DESX-CBC")                                       , false },
                                                { __L("1.2.840.113549.3.7"),                __L("DES-EDE3-CBC")                                   , false },
                                                { __L("1.2.840.113549.3.8"),                __L("RC5CBC")                                         , false },
                                                { __L("1.2.840.113549.3.9"),                __L("RC5-CBCPad")                                     , false },
                                                { __L("1.2.840.113556.1.4.319"),            __L("LDAP_PAGED_RESULT_OID_STRING")                   , false },
                                                { __L("1.2.840.113556.1.4.417"),            __L("LDAP_SERVER_SHOW_DELETED_OID")                   , false },
                                                { __L("1.2.840.113556.1.4.473"),            __L("LDAP_SERVER_SORT_OID")                           , false },
                                                { __L("1.2.840.113556.1.4.474"),            __L("LDAP_SERVER_RESP_SORT_OID")                      , false },
                                                { __L("1.2.840.113556.1.4.521"),            __L("LDAP_SERVER_CROSSDOM_MOVE_TARGET_OID")           , false },
                                                { __L("1.2.840.113556.1.4.528"),            __L("LDAP_SERVER_NOTIFICATION_OID")                   , false },
                                                { __L("1.2.840.113556.1.4.529"),            __L("LDAP_SERVER_EXTENDED_DN_OID")                    , false },
                                                { __L("1.2.840.113556.1.4.619"),            __L("LDAP_SERVER_LAZY_COMMIT_OID")                    , false },
                                                { __L("1.2.840.113556.1.4.801"),            __L("LDAP_SERVER_SD_FLAGS_OID")                       , false },
                                                { __L("1.2.840.113556.1.4.802"),            __L("LDAP_SERVER_RANGE_OPTION_OID")                   , false },
                                                { __L("1.2.840.113556.1.4.805"),            __L("LDAP_SERVER_TREE_DELETE_OID")                    , false },
                                                { __L("1.2.840.113556.1.4.841"),            __L("LDAP_SERVER_DIRSYNC_OID")                        , false },
                                                { __L("1.2.840.113556.1.4.970"),            __L("LDAP_SERVER_GET_STATS_OID")                      , false },
                                                { __L("1.2.840.113556.1.4.1338"),           __L("LDAP_SERVER_VERIFY_NAME_OID")                    , false },
                                                { __L("1.2.840.113556.1.4.1339"),           __L("LDAP_SERVER_DOMAIN_SCOPE_OID")                   , false },
                                                { __L("1.2.840.113556.1.4.1340"),           __L("LDAP_SERVER_SEARCH_OPTIONS_OID")                 , false },
                                                { __L("1.2.840.113556.1.4.1341"),           __L("LDAP_SERVER_RODC_DCPROMO_OID")                   , false },
                                                { __L("1.2.840.113556.1.4.1413"),           __L("LDAP_SERVER_PERMISSIVE_MODIFY_OID")              , false },
                                                { __L("1.2.840.113556.1.4.1504"),           __L("LDAP_SERVER_ASQ_OID")                            , false },
                                                { __L("1.2.840.113556.1.4.1852"),           __L("LDAP_SERVER_QUOTA_CONTROL_OID")                  , false },
                                                { __L("1.2.840.113556.1.4.1907"),           __L("LDAP_SERVER_SHUTDOWN_NOTIFY_OID")                , false },
                                                { __L("1.2.840.113556.1.4.1948"),           __L("LDAP_SERVER_RANGE_RETRIEVAL_NOERR_OID")          , false },
                                                { __L("1.2.840.113556.1.4.1974"),           __L("LDAP_SERVER_FORCE_UPDATE_OID ")                  , false },
                                                { __L("1.2.840.113556.1.4.2026"),           __L("LDAP_SERVER_DN_INPUT_OID")                       , false },
                                                { __L("1.2.840.113556.1.4.2064"),           __L("LDAP_SERVER_SHOW_RECYCLED_OID")                  , false },
                                                { __L("1.2.840.113556.1.4.2065"),           __L("LDAP_SERVER_SHOW_DEACTIVATED_LINK_OID")          , false },
                                                { __L("1.2.840.113556.1.4.2066"),           __L("LDAP_SERVER_POLICY_HINTS_DEPRECATED_OID")        , false },
                                                { __L("1.2.840.113556.1.4.2090"),           __L("LDAP_SERVER_DIRSYNC_EX_OID")                     , false },
                                                { __L("1.2.840.113556.1.4.2204"),           __L("LDAP_SERVER_TREE_DELETE_EX_OID")                 , false },
                                                { __L("1.2.840.113556.1.4.2205"),           __L("LDAP_SERVER_UPDATE_STATS_OID")                   , false },
                                                { __L("1.2.840.113556.1.4.2206"),           __L("LDAP_SERVER_SEARCH_HINTS_OID")                   , false },
                                                { __L("1.2.840.113556.1.4.2211"),           __L("LDAP_SERVER_EXPECTED_ENTRY_COUNT_OID")           , false },
                                                { __L("1.2.840.113556.1.4.2239"),           __L("LDAP_SERVER_POLICY_HINTS_OID")                   , false },
                                                { __L("1.2.840.113556.1.4.2255"),           __L("LDAP_SERVER_SET_OWNER_OID")                      , false },
                                                { __L("1.2.840.113556.1.4.2256"),           __L("LDAP_SERVER_BYPASS_QUOTA_OID")                   , false },
                                                { __L("1.2.840.113556.4.3"),                __L("microsoftExcel")                                 , false },
                                                { __L("1.2.840.113556.4.4"),                __L("titledWithOID")                                  , false },
                                                { __L("1.2.840.113556.4.5"),                __L("microsoftPowerPoint")                            , false },
                                                { __L("1.3.6.1.5.5.7.48.1.1"),              __L("Basic OCSP Response")                            , false },
                                                { __L("1.3.6.1.5.5.7.48.1.2"),              __L("OCSP Nonce")                                     , false },
                                                { __L("1.3.6.1.5.5.7.48.1.3"),              __L("OCSP CRL Reference")                             , false },
                                                { __L("1.3.6.1.5.5.7.48.1.5"),              __L("OCSP No Revocation Checking")                    , false },
                                                { __L("1.3.133.16.840.9.84"),               __L("x9-84")                                          , false },
                                                { __L("1.3.133.16.840.9.84.0"),             __L("x9-84-Module")                                   , false },
                                                { __L("1.3.133.16.840.9.84.0.1"),           __L("x9-84-Biometrics")                               , false },
                                                { __L("1.3.133.16.840.9.84.0.2"),           __L("x9-84-CMS")                                      , false },
                                                { __L("1.3.133.16.840.9.84.0.3"),           __L("x9-84-Identifiers")                              , false },
                                                { __L("1.3.133.16.840.9.84.1"),             __L("biometric")                                      , false },
                                                { __L("1.3.133.16.840.9.84.1.0"),           __L("id-unknown-Type")                                , false },
                                                { __L("1.3.133.16.840.9.84.1.1"),           __L("id-body-Odor")                                   , false },
                                                { __L("1.3.133.16.840.9.84.1.10"),          __L("id-palm")                                        , false },
                                                { __L("1.3.133.16.840.9.84.1.11"),          __L("id-retina")                                      , false },
                                                { __L("1.3.133.16.840.9.84.1.12"),          __L("id-signature")                                   , false },
                                                { __L("1.3.133.16.840.9.84.1.13"),          __L("id-speech-Pattern")                              , false },
                                                { __L("1.3.133.16.840.9.84.1.14"),          __L("id-thermal-Image")                               , false },
                                                { __L("1.3.133.16.840.9.84.1.15"),          __L("id-vein-Pattern")                                , false },
                                                { __L("1.3.133.16.840.9.84.1.16"),          __L("id-thermal-Face-Image")                          , false },
                                                { __L("1.3.133.16.840.9.84.1.17"),          __L("id-thermal-Hand-Image")                          , false },
                                                { __L("1.3.133.16.840.9.84.1.18"),          __L("id-lip-Movement")                                , false },
                                                { __L("1.3.133.16.840.9.84.1.19"),          __L("id-gait")                                        , false },
                                                { __L("1.3.133.16.840.9.84.1.2"),           __L("id-dna")                                         , false },
                                                { __L("1.3.133.16.840.9.84.1.3"),           __L("id-ear-Shape")                                   , false },
                                                { __L("1.3.133.16.840.9.84.1.4"),           __L("id-facial-Features")                             , false },
                                                { __L("1.3.133.16.840.9.84.1.5"),           __L("id-finger-Image")                                , false },
                                                { __L("1.3.133.16.840.9.84.1.6"),           __L("id-finger-Geometry")                             , false },
                                                { __L("1.3.133.16.840.9.84.1.7"),           __L("id-hand-Geometry")                               , false },
                                                { __L("1.3.133.16.840.9.84.1.8"),           __L("id-iris-Features")                               , false },
                                                { __L("1.3.133.16.840.9.84.1.9"),           __L("id-keystroke-Dynamics")                          , false },
                                                { __L("1.3.133.16.840.9.84.2"),             __L("processing-algorithm")                           , false },
                                                { __L("1.3.133.16.840.9.84.3"),             __L("matching-method")                                , false },
                                                { __L("1.3.133.16.840.9.84.4"),             __L("format-Owner")                                   , false },
                                                { __L("1.3.133.16.840.9.84.4.0"),           __L("cbeff-Owner")                                    , false },
                                                { __L("1.3.133.16.840.9.84.4.1"),           __L("ibia-Owner")                                     , false },
                                                { __L("1.3.133.16.840.9.84.4.1.1"),         __L("id-ibia-SAFLINK")                                , false },
                                                { __L("1.3.133.16.840.9.84.4.1.10"),        __L("id-ibia-SecuGen")                                , false },
                                                { __L("1.3.133.16.840.9.84.4.1.11"),        __L("id-ibia-PreciseBiometric")                       , false },
                                                { __L("1.3.133.16.840.9.84.4.1.12"),        __L("id-ibia-Identix")                                , false },
                                                { __L("1.3.133.16.840.9.84.4.1.13"),        __L("id-ibia-DERMALOG")                               , false },
                                                { __L("1.3.133.16.840.9.84.4.1.14"),        __L("id-ibia-LOGICO")                                 , false },
                                                { __L("1.3.133.16.840.9.84.4.1.15"),        __L("id-ibia-NIST")                                   , false },
                                                { __L("1.3.133.16.840.9.84.4.1.16"),        __L("id-ibia-A3Vision")                               , false },
                                                { __L("1.3.133.16.840.9.84.4.1.17"),        __L("id-ibia-NEC")                                    , false },
                                                { __L("1.3.133.16.840.9.84.4.1.18"),        __L("id-ibia-STMicroelectronics")                     , false },
                                                { __L("1.3.133.16.840.9.84.4.1.2"),         __L("id-ibia-Bioscrypt")                              , false },
                                                { __L("1.3.133.16.840.9.84.4.1.3"),         __L("id-ibia-Visionics")                              , false },
                                                { __L("1.3.133.16.840.9.84.4.1.4"),         __L("id-ibia-InfineonTechnologiesAG")                 , false },
                                                { __L("1.3.133.16.840.9.84.4.1.5"),         __L("id-ibia-IridianTechnologies")                    , false },
                                                { __L("1.3.133.16.840.9.84.4.1.6"),         __L("id-ibia-Veridicom")                              , false },
                                                { __L("1.3.133.16.840.9.84.4.1.7"),         __L("id-ibia-CyberSIGN")                              , false },
                                                { __L("1.3.133.16.840.9.84.4.1.8"),         __L("id-ibia-eCryp.")                                 , false },
                                                { __L("1.3.133.16.840.9.84.4.1.9"),         __L("id-ibia-FingerprintCardsAB")                     , false },
                                                { __L("1.3.133.16.840.9.84.4.2"),           __L("x9-Owner")                                       , false },
                                                { __L("1.3.14.2.26.5"),                     __L("sha")                                            , false },
                                                { __L("1.3.14.3.2.1.1"),                    __L("rsa")                                            , false },
                                                { __L("1.3.14.3.2.10"),                     __L("desMAC")                                         , false },
                                                { __L("1.3.14.3.2.11"),                     __L("rsaSignature")                                   , false },
                                                { __L("1.3.14.3.2.12"),                     __L("dsa")                                            , false },
                                                { __L("1.3.14.3.2.13"),                     __L("dsaWithSHA")                                     , false },
                                                { __L("1.3.14.3.2.14"),                     __L("mdc2WithRSASignature")                           , false },
                                                { __L("1.3.14.3.2.15"),                     __L("shaWithRSASignature")                            , false },
                                                { __L("1.3.14.3.2.16"),                     __L("dhWithCommonModulus")                            , false },
                                                { __L("1.3.14.3.2.17"),                     __L("desEDE")                                         , false },
                                                { __L("1.3.14.3.2.18"),                     __L("sha")                                            , false },
                                                { __L("1.3.14.3.2.19"),                     __L("mdc-2")                                          , false },
                                                { __L("1.3.14.3.2.2"),                      __L("md4WitRSA")                                      , false },
                                                { __L("1.3.14.3.2.2.1"),                    __L("sqmod-N")                                        , false },
                                                { __L("1.3.14.3.2.20"),                     __L("dsaCommon")                                      , false },
                                                { __L("1.3.14.3.2.21"),                     __L("dsaCommonWithSHA")                               , false },
                                                { __L("1.3.14.3.2.22"),                     __L("rsaKeyTransport")                                , false },
                                                { __L("1.3.14.3.2.23"),                     __L("keyed-hash-seal")                                , false },
                                                { __L("1.3.14.3.2.24"),                     __L("md2WithRSASignature")                            , false },
                                                { __L("1.3.14.3.2.25"),                     __L("md5WithRSASignature")                            , false },
                                                { __L("1.3.14.3.2.26"),                     __L("sha1")                                           , false },
                                                { __L("1.3.14.3.2.27"),                     __L("dsaWithSHA1")                                    , false },
                                                { __L("1.3.14.3.2.28"),                     __L("dsaWithCommonSHA1")                              , false },
                                                { __L("1.3.14.3.2.29"),                     __L("sha-1WithRSAEncryption")                         , false },
                                                { __L("1.3.14.3.2.3"),                      __L("md5WithRSA")                                     , false },
                                                { __L("1.3.14.3.2.3.1"),                    __L("sqmod-NwithRSA")                                 , false },
                                                { __L("1.3.14.3.2.4"),                      __L("md4WithRSAEncryption")                           , false },
                                                { __L("1.3.14.3.2.6"),                      __L("desECB")                                         , false },
                                                { __L("1.3.14.3.2.7"),                      __L("desCBC")                                         , false },
                                                { __L("1.3.14.3.2.8"),                      __L("desOFB")                                         , false },
                                                { __L("1.3.14.3.2.9"),                      __L("desCFB")                                         , false },
                                                { __L("1.3.14.3.3.1"),                      __L("simple-strong-auth-mechanism")                   , false },
                                                { __L("1.3.14.7.2.1.1"),                    __L("ElGamal")                                        , false },
                                                { __L("1.3.14.7.2.3.1"),                    __L("md2WithRSA")                                     , false },
                                                { __L("1.3.14.7.2.3.2"),                    __L("md2WithElGamal")                                 , false },
                                                { __L("1.3.36.3"),                          __L("algorithm")                                      , false },
                                                { __L("1.3.36.3.1"),                        __L("encryptionAlgorithm")                            , false },
                                                { __L("1.3.36.3.1.1"),                      __L("des")                                            , false },
                                                { __L("1.3.36.3.1.1.1.1"),                  __L("desECBPad")                                      , false },
                                                { __L("1.3.36.3.1.1.1.1.1"),                __L("desECBPadISO")                                   , false },
                                                { __L("1.3.36.3.1.1.2.1"),                  __L("desCBCPad")                                      , false },
                                                { __L("1.3.36.3.1.1.2.1.1"),                __L("desCBCPadISO")                                   , false },
                                                { __L("1.3.36.3.1.2"),                      __L("idea")                                           , false },
                                                { __L("1.3.36.3.1.2.1"),                    __L("ideaECB")                                        , false },
                                                { __L("1.3.36.3.1.2.1.1"),                  __L("ideaECBPad")                                     , false },
                                                { __L("1.3.36.3.1.2.1.1.1"),                __L("ideaECBPadISO")                                  , false },
                                                { __L("1.3.36.3.1.2.2"),                    __L("ideaCBC")                                        , false },
                                                { __L("1.3.36.3.1.2.2.1"),                  __L("ideaCBCPad")                                     , false },
                                                { __L("1.3.36.3.1.2.2.1.1"),                __L("ideaCBCPadISO")                                  , false },
                                                { __L("1.3.36.3.1.2.3"),                    __L("ideaOFB")                                        , false },
                                                { __L("1.3.36.3.1.2.4"),                    __L("ideaCFB")                                        , false },
                                                { __L("1.3.36.3.1.3"),                      __L("des-3")                                          , false },
                                                { __L("1.3.36.3.1.3.1.1"),                  __L("des-3ECBPad")                                    , false },
                                                { __L("1.3.36.3.1.3.1.1.1"),                __L("des-3ECBPadISO")                                 , false },
                                                { __L("1.3.36.3.1.3.2.1"),                  __L("des-3CBCPad")                                    , false },
                                                { __L("1.3.36.3.1.3.2.1.1"),                __L("des-3CBCPadISO")                                 , false },
                                                { __L("1.3.36.3.2"),                        __L("hashAlgorithm")                                  , false },
                                                { __L("1.3.36.3.2.1"),                      __L("ripemd160")                                      , false },
                                                { __L("1.3.36.3.2.2"),                      __L("ripemd128")                                      , false },
                                                { __L("1.3.36.3.2.3"),                      __L("ripemd256")                                      , false },
                                                { __L("1.3.36.3.2.4"),                      __L("mdc2singleLength")                               , false },
                                                { __L("1.3.36.3.2.5"),                      __L("mdc2doubleLength")                               , false },
                                                { __L("1.3.36.3.3"),                        __L("signatureAlgorithm")                             , false },
                                                { __L("1.3.36.3.3.1"),                      __L("rsa")                                            , false },
                                                { __L("1.3.36.3.3.1.1"),                    __L("rsaMitSHA-1")                                    , false },
                                                { __L("1.3.36.3.3.1.2"),                    __L("rsaMitRIPEMD160")                                , false },
                                                { __L("1.3.36.3.3.2"),                      __L("ellipticCurve")                                  , false },
                                                { __L("1.3.36.3.4"),                        __L("signatureScheme")                                , false },
                                                { __L("1.3.36.3.4.1"),                      __L("iso9796-1")                                      , false },
                                                { __L("1.3.36.3.4.2.1"),                    __L("iso9796-2")                                      , false },
                                                { __L("1.3.36.3.4.2.2"),                    __L("iso9796-2rsa")                                   , false },
                                                { __L("1.3.36.4"),                          __L("attribute")                                      , false },
                                                { __L("1.3.36.5"),                          __L("policy")                                         , false },
                                                { __L("1.3.36.6"),                          __L("api")                                            , false },
                                                { __L("1.3.36.6.1"),                        __L("manufacturerSpecific")                           , false },
                                                { __L("1.3.36.6.2"),                        __L("functionalitySpecific")                          , false },
                                                { __L("1.3.36.7"),                          __L("api")                                            , false },
                                                { __L("1.3.36.7.1"),                        __L("keyAgreement")                                   , false },
                                                { __L("1.3.36.7.2"),                        __L("keyTransport")                                   , false },
                                                { __L("1.3.36.8"),                          __L("common-pki")                                     , false },
                                                { __L("1.3.36.8.3"),                        __L("id-commonpki-at")                                , false },
                                                { __L("1.3.36.8.3.1"),                      __L("id-isismtt-at-admission")                        , false },
                                                { __L("1.3.36.8.3.9"),                      __L("id-isismtt-at-retrieveIfAllowed")                , false },
                                                { __L("1.3.36.8.3.10"),                     __L("id-isismtt-at-requestedCertificate")             , false },
                                                { __L("1.3.36.8.3.11"),                     __L("id-common-pki-namingAuthorities")                , false },
                                                { __L("1.3.36.8.3.12"),                     __L("id-isismtt-at-CertInDirSince")                   , false },
                                                { __L("1.3.36.8.3.13"),                     __L("id-isismtt-at-certHash")                         , false },
                                                { __L("1.3.6.1.4.1.2428.10.1.1"),           __L("UNINETT policyIdentifier")                       , false },
                                                { __L("1.3.6.1.4.1.2712.10"),               __L("ICE-TEL policyIdentifier")                       , false },
                                                { __L("1.3.6.1.4.1.3029.32.1"),             __L("cryptlibEnvelope")                               , false },
                                                { __L("1.3.6.1.4.1.3029.32.2"),             __L("cryptlibPrivateKey")                             , false },
                                                { __L("1.3.6.1.4.1.311"),                   __L("Microsoft OID")                                  , false },
                                                { __L("1.3.6.1.4.1.311.10.2"),              __L("nextUpdateLocation")                             , false },
                                                { __L("1.3.6.1.4.1.311.2"),                 __L("Authenticode")                                   , false },
                                                { __L("1.3.6.1.4.1.311.2.1.4"),             __L("SPC_INDIRECT_DATA_OBJID")                        , false },
                                                { __L("1.3.6.1.4.1.311.2.1.10"),            __L("SPC_SP_AGENCY_INFO_OBJID")                       , false },
                                                { __L("1.3.6.1.4.1.311.2.1.11"),            __L("SPC_STATEMENT_TYPE_OBJID")                       , false },
                                                { __L("1.3.6.1.4.1.311.2.1.12"),            __L("SPC_SP_OPUS_INFO_OBJID")                         , false },
                                                { __L("1.3.6.1.4.1.311.2.1.14"),            __L("SPC_CERT_EXTENSIONS_OBJID")                      , false },
                                                { __L("1.3.6.1.4.1.311.2.1.15"),            __L("SPC_PE_IMAGE_DATA_OBJID")                        , false },
                                                { __L("1.3.6.1.4.1.311.2.1.18"),            __L("SPC_RAW_FILE_DATA_OBJID")                        , false },
                                                { __L("1.3.6.1.4.1.311.2.1.19"),            __L("SPC_STRUCTURED_STORAGE_DATA_OBJID")              , false },
                                                { __L("1.3.6.1.4.1.311.2.1.20"),            __L("SPC_JAVA_CLASS_DATA_OBJID")                      , false },
                                                { __L("1.3.6.1.4.1.311.2.1.21"),            __L("SPC_INDIVIDUAL_SP_KEY_PURPOSE_OBJID")            , false },
                                                { __L("1.3.6.1.4.1.311.2.1.22"),            __L("SPC_COMMERCIAL_SP_KEY_PURPOSE_OBJID")            , false },
                                                { __L("1.3.6.1.4.1.311.2.1.25"),            __L("SPC_CAB_DATA_OBJID")                             , false },
                                                { __L("1.3.6.1.4.1.311.2.1.26"),            __L("SPC_MINIMAL_CRITERIA_OBJID")                     , false },
                                                { __L("1.3.6.1.4.1.311.2.1.27"),            __L("SPC_FINANCIAL_CRITERIA_OBJID")                   , false },
                                                { __L("1.3.6.1.4.1.311.2.1.28"),            __L("SPC_LINK_OBJID")                                 , false },
                                                { __L("1.3.6.1.4.1.311.2.1.29"),            __L("SPC_HASH_INFO_OBJID")                            , false },
                                                { __L("1.3.6.1.4.1.311.2.1.30"),            __L("SPC_SIPINFO_OBJID")                              , false },
                                                { __L("1.3.6.1.4.1.311.2.2"),               __L("CTL for Software Publishers Trusted CAs")        , false },
                                                { __L("1.3.6.1.4.1.311.2.2.1"),             __L("szOID_TRUSTED_CODESIGNING_CA_LIST")              , false },
                                                { __L("1.3.6.1.4.1.311.2.2.2"),             __L("szOID_TRUSTED_CLIENT_AUTH_CA_LIST")              , false },
                                                { __L("1.3.6.1.4.1.311.2.2.3"),             __L("szOID_TRUSTED_SERVER_AUTH_CA_LIST")              , false },
                                                { __L("1.3.6.1.4.1.311.3"),                 __L("Time Stamping")                                  , false },
                                                { __L("1.3.6.1.4.1.311.3.2.1"),             __L("SPC_TIME_STAMP_REQUEST_OBJID")                   , false },
                                                { __L("1.3.6.1.4.1.311.3.3.1"),             __L("RFC3161 Counter Signature")                      , false },
                                                { __L("1.3.6.1.4.1.311.4"),                 __L("Permissions")                                    , false },
                                                { __L("1.3.6.1.4.1.311.10.3.1"),            __L("certTrustListSigning")                           , false },
                                                { __L("1.3.6.1.4.1.311.10.3.2"),            __L("timeStampSigning")                               , false },
                                                { __L("1.3.6.1.4.1.311.10.3.3"),            __L("serverGatedCrypto")                              , false },
                                                { __L("1.3.6.1.4.1.311.10.3.3.1"),          __L("szOID_SERIALIZED")                               , false },
                                                { __L("1.3.6.1.4.1.311.10.3.4"),            __L("encryptedFileSystem")                            , false },
                                                { __L("1.3.6.1.4.1.311.10.3.4.1"),          __L("szOID_EFS_RECOVERY")                             , false },
                                                { __L("1.3.6.1.4.1.311.10.3.5"),            __L("szOID_WHQL_CRYPTO")                              , false },
                                                { __L("1.3.6.1.4.1.311.10.3.6"),            __L("szOID_NT5_CRYPTO")                               , false },
                                                { __L("1.3.6.1.4.1.311.10.3.7"),            __L("szOID_OEM_WHQL_CRYPTO")                          , false },
                                                { __L("1.3.6.1.4.1.311.10.3.8"),            __L("szOID_EMBEDDED_NT_CRYPTO")                       , false },
                                                { __L("1.3.6.1.4.1.311.10.3.9"),            __L("szOID_ROOT_LIST_SIGNER")                         , false },
                                                { __L("1.3.6.1.4.1.311.10.3.10"),           __L("szOID_KP_QUALIFIED_SUBORDINATION")               , false },
                                                { __L("1.3.6.1.4.1.311.10.3.11"),           __L("szOID_KP_KEY_RECOVERY")                          , false },
                                                { __L("1.3.6.1.4.1.311.10.3.12"),           __L("szOID_KP_DOCUMENT_SIGNING")                      , false },
                                                { __L("1.3.6.1.4.1.311.10.4.1"),            __L("yesnoTrustAttr")                                 , false },
                                                { __L("1.3.6.1.4.1.311.10.5.1"),            __L("szOID_DRM")                                      , false },
                                                { __L("1.3.6.1.4.1.311.10.5.2"),            __L("szOID_DRM_INDIVIDUALIZATION")                    , false },
                                                { __L("1.3.6.1.4.1.311.10.6.1"),            __L("szOID_LICENSES")                                 , false },
                                                { __L("1.3.6.1.4.1.311.10.6.2"),            __L("szOID_LICENSE_SERVER")                           , false },
                                                { __L("1.3.6.1.4.1.311.10.7"),              __L("szOID_MICROSOFT_RDN_PREFIX")                     , false },
                                                { __L("1.3.6.1.4.1.311.10.7.1"),            __L("szOID_KEYID_RDN")                                , false },
                                                { __L("1.3.6.1.4.1.311.10.8.1"),            __L("szOID_REMOVE_CERTIFICATE")                       , false },
                                                { __L("1.3.6.1.4.1.311.10.9.1"),            __L("szOID_CROSS_CERT_DIST_POINTS")                   , false },
                                                { __L("1.3.6.1.4.1.311.10"),                __L("Crypto 2.0")                                     , false },
                                                { __L("1.3.6.1.4.1.311.10.1"),              __L("certTrustList")                                  , false },
                                                { __L("1.3.6.1.4.1.311.10.1.1"),            __L("szOID_SORTED_CTL")                               , false },
                                                { __L("1.3.6.1.4.1.311.10.10"),             __L("Microsoft CMC OIDs")                             , false },
                                                { __L("1.3.6.1.4.1.311.10.10.1"),           __L("szOID_CMC_ADD_ATTRIBUTES")                       , false },
                                                { __L("1.3.6.1.4.1.311.10.11"),             __L("Microsoft certificate property OIDs")            , false },
                                                { __L("1.3.6.1.4.1.311.10.11.1"),           __L("szOID_CERT_PROP_ID_PREFIX")                      , false },
                                                { __L("1.3.6.1.4.1.311.10.12"),             __L("CryptUI")                                        , false },
                                                { __L("1.3.6.1.4.1.311.10.12.1"),           __L("szOID_ANY_APPLICATION_POLICY")                   , false },
                                                { __L("1.3.6.1.4.1.311.12"),                __L("Catalog")                                        , false },
                                                { __L("1.3.6.1.4.1.311.12.1.1"),            __L("szOID_CATALOG_LIST")                             , false },
                                                { __L("1.3.6.1.4.1.311.12.1.2"),            __L("szOID_CATALOG_LIST_MEMBER")                      , false },
                                                { __L("1.3.6.1.4.1.311.12.1.3"),            __L("szOID_CATALOG_LIST_MEMBER_V2")                   , false },
                                                { __L("1.3.6.1.4.1.311.12.2.1"),            __L("CAT_NAMEVALUE_OBJID")                            , false },
                                                { __L("1.3.6.1.4.1.311.12.2.2"),            __L("CAT_MEMBERINFO_OBJID")                           , false },
                                                { __L("1.3.6.1.4.1.311.12.2.3"),            __L("CAT_MEMBERINFO2_OBJID")                          , false },
                                                { __L("1.3.6.1.4.1.311.13"),                __L("Microsoft PKCS10 OIDs")                          , false },
                                                { __L("1.3.6.1.4.1.311.13.1"),              __L("szOID_RENEWAL_CERTIFICATE")                      , false },
                                                { __L("1.3.6.1.4.1.311.13.2.1"),            __L("szOID_ENROLLMENT_NAME_VALUE_PAIR")               , false },
                                                { __L("1.3.6.1.4.1.311.13.2.2"),            __L("szOID_ENROLLMENT_CSP_PROVIDER")                  , false },
                                                { __L("1.3.6.1.4.1.311.13.2.3"),            __L("OS Version")                                     , false },
                                                { __L("1.3.6.1.4.1.311.15"),                __L("Microsoft Java")                                 , false },
                                                { __L("1.3.6.1.4.1.311.16"),                __L("Microsoft Outlook/Exchange")                     , false },
                                                { __L("1.3.6.1.4.1.311.16.4"),              __L("Outlook Express")                                , false },
                                                { __L("1.3.6.1.4.1.311.17"),                __L("Microsoft PKCS12 attributes")                    , false },
                                                { __L("1.3.6.1.4.1.311.17.1"),              __L("szOID_LOCAL_MACHINE_KEYSET")                     , false },
                                                { __L("1.3.6.1.4.1.311.18"),                __L("Microsoft Hydra")                                , false },
                                                { __L("1.3.6.1.4.1.311.19"),                __L("Microsoft ISPU Test")                            , false },
                                                { __L("1.3.6.1.4.1.311.20"),                __L("Microsoft Enrollment Infrastructure")            , false },
                                                { __L("1.3.6.1.4.1.311.20.1"),              __L("szOID_AUTO_ENROLL_CTL_USAGE")                    , false },
                                                { __L("1.3.6.1.4.1.311.20.2"),              __L("szOID_ENROLL_CERTTYPE_EXTENSION")                , false },
                                                { __L("1.3.6.1.4.1.311.20.2.1"),            __L("szOID_ENROLLMENT_AGENT")                         , false },
                                                { __L("1.3.6.1.4.1.311.20.2.2"),            __L("szOID_KP_SMARTCARD_LOGON")                       , false },
                                                { __L("1.3.6.1.4.1.311.20.2.3"),            __L("szOID_NT_PRINCIPAL_NAME")                        , false },
                                                { __L("1.3.6.1.4.1.311.20.3"),              __L("szOID_CERT_MANIFOLD")                            , false },
                                                { __L("1.3.6.1.4.1.311.21"),                __L("Microsoft CertSrv Infrastructure")               , false },
                                                { __L("1.3.6.1.4.1.311.21.1"),              __L("szOID_CERTSRV_CA_VERSION")                       , false },
                                                { __L("1.3.6.1.4.1.311.21.20"),             __L("Client Information")                             , false },
                                                { __L("1.3.6.1.4.1.311.25"),                __L("Microsoft Directory Service")                    , false },
                                                { __L("1.3.6.1.4.1.311.25.1"),              __L("szOID_NTDS_REPLICATION")                         , false },
                                                { __L("1.3.6.1.4.1.311.30"),                __L("IIS")                                            , false },
                                                { __L("1.3.6.1.4.1.311.31"),                __L("Windows updates and service packs")              , false },
                                                { __L("1.3.6.1.4.1.311.31.1"),              __L("szOID_PRODUCT_UPDATE")                           , false },
                                                { __L("1.3.6.1.4.1.311.40"),                __L("Fonts")                                          , false },
                                                { __L("1.3.6.1.4.1.311.41"),                __L("Microsoft Licensing and Registration")           , false },
                                                { __L("1.3.6.1.4.1.311.42"),                __L("Microsoft Corporate PKI (ITG)")                  , false },
                                                { __L("1.3.6.1.4.1.311.60.2.1.3"),          __L("Country")                                        , false },
                                                { __L("1.3.6.1.4.1.311.60.2.1.2"),          __L("State or province")                              , false },
                                                { __L("1.3.6.1.4.1.311.88"),                __L("CAPICOM")                                        , false },
                                                { __L("1.3.6.1.4.1.311.88.1"),              __L("CAPICOM Version")                                , false },
                                                { __L("1.3.6.1.4.1.311.88.2"),              __L("CAPICOM Attribute")                              , false },
                                                { __L("1.3.6.1.4.1.311.88.2.1"),            __L("CAPICOM Document Name")                          , false },
                                                { __L("1.3.6.1.4.1.311.88.2.2"),            __L("CAPICOM Document Description")                   , false },
                                                { __L("1.3.6.1.4.1.311.88.3"),              __L("CAPICOM Encrypted Data")                         , false },
                                                { __L("1.3.6.1.4.1.311.88.3.1"),            __L("CAPICOM Encrypted Content")                      , false },
                                                { __L("1.3.6.1.4.1.11129.2.4.2"),           __L("Signed Certificate Timestamp List")              , false },
                                                { __L("1.3.6.1.5.5.7"),                     __L("pkix")                                           , false },
                                                { __L("1.3.6.1.5.5.7.1"),                   __L("privateExtension")                               , false },
                                                { __L("1.3.6.1.5.5.7.1.1"),                 __L("authorityInfoAccess")                            , false },
                                                { __L("1.3.6.1.5.5.7.12.2"),                __L("CMC Data")                                       , false },
                                                { __L("1.3.6.1.5.5.7.2"),                   __L("policyQualifierIds")                             , false },
                                                { __L("1.3.6.1.5.5.7.2.1"),                 __L("CPS")                                            , false },
                                                { __L("1.3.6.1.5.5.7.2.2"),                 __L("User Notice")                                    , false },
                                                { __L("1.3.6.1.5.5.7.3"),                   __L("keyPurpose")                                     , false },
                                                { __L("1.3.6.1.5.5.7.3.1"),                 __L("serverAuth")                                     , false },
                                                { __L("1.3.6.1.5.5.7.3.2"),                 __L("clientAuth")                                     , false },
                                                { __L("1.3.6.1.5.5.7.3.3"),                 __L("codeSigning")                                    , false },
                                                { __L("1.3.6.1.5.5.7.3.4"),                 __L("emailProtection")                                , false },
                                                { __L("1.3.6.1.5.5.7.3.5"),                 __L("ipsecEndSystem")                                 , false },
                                                { __L("1.3.6.1.5.5.7.3.6"),                 __L("ipsecTunnel")                                    , false },
                                                { __L("1.3.6.1.5.5.7.3.7"),                 __L("ipsecUser")                                      , false },
                                                { __L("1.3.6.1.5.5.7.3.8"),                 __L("timeStamping")                                   , false },
                                                { __L("1.3.6.1.5.5.7.4"),                   __L("cmpInformationTypes")                            , false },
                                                { __L("1.3.6.1.5.5.7.4.1"),                 __L("caProtEncCert")                                  , false },
                                                { __L("1.3.6.1.5.5.7.4.2"),                 __L("signKeyPairTypes")                               , false },
                                                { __L("1.3.6.1.5.5.7.4.3"),                 __L("encKeyPairTypes")                                , false },
                                                { __L("1.3.6.1.5.5.7.4.4"),                 __L("preferredSymmAlg")                               , false },
                                                { __L("1.3.6.1.5.5.7.4.5"),                 __L("caKeyUpdateInfo")                                , false },
                                                { __L("1.3.6.1.5.5.7.4.6"),                 __L("currentCRL")                                     , false },
                                                { __L("1.3.6.1.5.5.7.48.1"),                __L("ocsp")                                           , false },
                                                { __L("1.3.6.1.5.5.7.48.2"),                __L("caIssuers")                                      , false },
                                                { __L("1.3.6.1.5.5.8.1.1"),                 __L("HMAC-MD5")                                       , false },
                                                { __L("1.3.6.1.5.5.8.1.2"),                 __L("HMAC-SHA")                                       , false },
                                                { __L("2.16.840.1.101.2.1.1.1"),            __L("sdnsSignatureAlgorithm")                         , false },
                                                { __L("2.16.840.1.101.2.1.1.10"),           __L("mosaicKeyManagementAlgorithm")                   , false },
                                                { __L("2.16.840.1.101.2.1.1.11"),           __L("sdnsKMandSigAlgorithm")                          , false },
                                                { __L("2.16.840.1.101.2.1.1.12"),           __L("mosaicKMandSigAlgorithm")                        , false },
                                                { __L("2.16.840.1.101.2.1.1.13"),           __L("SuiteASignatureAlgorithm")                       , false },
                                                { __L("2.16.840.1.101.2.1.1.14"),           __L("SuiteAConfidentialityAlgorithm")                 , false },
                                                { __L("2.16.840.1.101.2.1.1.15"),           __L("SuiteAIntegrityAlgorithm")                       , false },
                                                { __L("2.16.840.1.101.2.1.1.16"),           __L("SuiteATokenProtectionAlgorithm")                 , false },
                                                { __L("2.16.840.1.101.2.1.1.17"),           __L("SuiteAKeyManagementAlgorithm")                   , false },
                                                { __L("2.16.840.1.101.2.1.1.18"),           __L("SuiteAKMandSigAlgorithm")                        , false },
                                                { __L("2.16.840.1.101.2.1.1.19"),           __L("mosaicUpdatedSigAlgorithm")                      , false },
                                                { __L("2.16.840.1.101.2.1.1.2"),            __L("mosaicSignatureAlgorithm")                       , false },
                                                { __L("2.16.840.1.101.2.1.1.20"),           __L("mosaicKMandUpdSigAlgorithms")                    , false },
                                                { __L("2.16.840.1.101.2.1.1.21"),           __L("mosaicUpdatedIntegAlgorithm")                    , false },
                                                { __L("2.16.840.1.101.2.1.1.22"),           __L("mosaicKeyEncryptionAlgorithm")                   , false },
                                                { __L("2.16.840.1.101.2.1.1.3"),            __L("sdnsConfidentialityAlgorithm")                   , false },
                                                { __L("2.16.840.1.101.2.1.1.4"),            __L("mosaicConfidentialityAlgorithm")                 , false },
                                                { __L("2.16.840.1.101.2.1.1.5"),            __L("sdnsIntegrityAlgorithm")                         , false },
                                                { __L("2.16.840.1.101.2.1.1.6"),            __L("mosaicIntegrityAlgorithm")                       , false },
                                                { __L("2.16.840.1.101.2.1.1.7"),            __L("sdnsTokenProtectionAlgorithm")                   , false },
                                                { __L("2.16.840.1.101.2.1.1.8"),            __L("mosaicTokenProtectionAlgorithm")                 , false },
                                                { __L("2.16.840.1.101.2.1.1.9"),            __L("sdnsKeyManagementAlgorithm")                     , false },
                                                { __L("2.16.840.1.113730.1"),               __L("cert-extension")                                 , false },
                                                { __L("2.16.840.1.113730.1.1"),             __L("netscape-cert-type")                             , false },
                                                { __L("2.16.840.1.113730.1.10"),            __L("EntityLogo")                                     , false },
                                                { __L("2.16.840.1.113730.1.11"),            __L("UserPicture")                                    , false },
                                                { __L("2.16.840.1.113730.1.12"),            __L("netscape-ssl-server-name")                       , false },
                                                { __L("2.16.840.1.113730.1.13"),            __L("netscape-comment")                               , false },
                                                { __L("2.16.840.1.113730.1.2"),             __L("netscape-base-url")                              , false },
                                                { __L("2.16.840.1.113730.1.3"),             __L("netscape-revocation-url")                        , false },
                                                { __L("2.16.840.1.113730.1.4"),             __L("netscape-ca-revocation-url")                     , false },
                                                { __L("2.16.840.1.113730.1.7"),             __L("netscape-cert-renewal-url")                      , false },
                                                { __L("2.16.840.1.113730.1.8"),             __L("netscape-ca-policy-url")                         , false },
                                                { __L("2.16.840.1.113730.1.9"),             __L("HomePage-url")                                   , false },
                                                { __L("2.16.840.1.113730.2"),               __L("data-type")                                      , false },
                                                { __L("2.16.840.1.113730.2.1"),             __L("GIF")                                            , false },
                                                { __L("2.16.840.1.113730.2.2"),             __L("JPEG")                                           , false },
                                                { __L("2.16.840.1.113730.2.3"),             __L("URL")                                            , false },
                                                { __L("2.16.840.1.113730.2.4"),             __L("HTML")                                           , false },
                                                { __L("2.16.840.1.113730.2.5"),             __L("netscape-cert-sequence")                         , false },
                                                { __L("2.16.840.1.113730.2.6"),             __L("netscape-cert-url")                              , false },
                                                { __L("2.16.840.1.113730.3"),               __L("LDAPv3")                                         , false },
                                                { __L("2.16.840.1.113730.3.4.9"),           __L("LDAP_CONTROL_VLVREQUEST")                        , false },
                                                { __L("2.16.840.1.113730.3.4.10"),          __L("LDAP_CONTROL_VLVRESPONSE")                       , false },
                                                { __L("2.16.840.1.113730.4.1"),             __L("serverGatedCrypto")                              , false },
                                                { __L("2.16.840.1.113733.1.6.3"),           __L("Unknown Verisign extension")                     , false },
                                                { __L("2.16.840.1.113733.1.6.6"),           __L("Unknown Verisign extension")                     , false },
                                                { __L("2.16.840.1.113733.1.7.1.1"),         __L("Verisign certificatePolicy")                     , false },
                                                { __L("2.16.840.1.113733.1.7.1.1.1"),       __L("Unknown Verisign policy qualifier")              , false },
                                                { __L("2.16.840.1.113733.1.7.1.1.2"),       __L("Unknown Verisign policy qualifier")              , false },
                                                { __L("2.16.840.1.113733.1.7.23.3"),        __L("Class 3 Certificate Policy")                     , false },
                                                { __L("2.23.133"),                          __L("TCPA")                                           , false },
                                                { __L("2.23.133.1"),                        __L("tcpa_specVersion")                               , false },
                                                { __L("2.23.133.2"),                        __L("tcpa_attribute")                                 , false },
                                                { __L("2.23.133.2.1"),                      __L("tcpa_at_tpmManufacturer")                        , false },
                                                { __L("2.23.133.2.10"),                     __L("tcpa_at_securityQualities")                      , false },
                                                { __L("2.23.133.2.11"),                     __L("tcpa_at_tpmProtectionProfile")                   , false },
                                                { __L("2.23.133.2.12"),                     __L("tcpa_at_tpmSecurityTarget")                      , false },
                                                { __L("2.23.133.2.13"),                     __L("tcpa_at_foundationProtectionProfile")            , false },
                                                { __L("2.23.133.2.14"),                     __L("tcpa_at_foundationSecurityTarget")               , false },
                                                { __L("2.23.133.2.15"),                     __L("tcpa_at_tpmIdLabel")                             , false },
                                                { __L("2.23.133.2.2"),                      __L("tcpa_at_tpmModel")                               , false },
                                                { __L("2.23.133.2.3"),                      __L("tcpa_at_tpmVersion")                             , false },
                                                { __L("2.23.133.2.4"),                      __L("tcpa_at_platformManufacturer")                   , false },
                                                { __L("2.23.133.2.5"),                      __L("tcpa_at_platformModel")                          , false },
                                                { __L("2.23.133.2.6"),                      __L("tcpa_at_platformVersion")                        , false },
                                                { __L("2.23.133.2.7"),                      __L("tcpa_at_componentManufacturer")                  , false },
                                                { __L("2.23.133.2.8"),                      __L("tcpa_at_componentModel")                         , false },
                                                { __L("2.23.133.2.9"),                      __L("tcpa_at_componentVersion")                       , false },
                                                { __L("2.23.133.3"),                        __L("tcpa_protocol")                                  , false },
                                                { __L("2.23.133.3.1"),                      __L("tcpa_prtt_tpmIdProtocol")                        , false },
                                                { __L("2.23.42.0"),                         __L("contentType")                                    , false },
                                                { __L("2.23.42.0.0"),                       __L("PANData")                                        , false },
                                                { __L("2.23.42.0.1"),                       __L("PANToken")                                       , false },
                                                { __L("2.23.42.0.2"),                       __L("PANOnly")                                        , false },
                                                { __L("2.23.42.1"),                         __L("msgExt")                                         , false },
                                                { __L("2.23.42.10"),                        __L("national")                                       , false },
                                                { __L("2.23.42.10.192"),                    __L("Japan")                                          , false },
                                                { __L("2.23.42.2"),                         __L("field")                                          , false },
                                                { __L("2.23.42.2.0"),                       __L("fullName")                                       , false },
                                                { __L("2.23.42.2.1"),                       __L("givenName")                                      , false },
                                                { __L("2.23.42.2.10"),                      __L("amount")                                         , false },
                                                { __L("2.23.42.2.2"),                       __L("familyName")                                     , false },
                                                { __L("2.23.42.2.3"),                       __L("birthFamilyName")                                , false },
                                                { __L("2.23.42.2.4"),                       __L("placeName")                                      , false },
                                                { __L("2.23.42.2.5"),                       __L("identificationNumber")                           , false },
                                                { __L("2.23.42.2.6"),                       __L("month")                                          , false },
                                                { __L("2.23.42.2.7"),                       __L("date")                                           , false },
                                                { __L("2.23.42.2.7.11"),                    __L("accountNumber")                                  , false },
                                                { __L("2.23.42.2.7.12"),                    __L("passPhrase")                                     , false },
                                                { __L("2.23.42.2.8"),                       __L("address")                                        , false },
                                                { __L("2.23.42.2.9"),                       __L("telephone")                                      , false },
                                                { __L("2.23.42.3"),                         __L("attribute")                                      , false },
                                                { __L("2.23.42.3.0"),                       __L("cert")                                           , false },
                                                { __L("2.23.42.3.0.0"),                     __L("rootKeyThumb")                                   , false },
                                                { __L("2.23.42.3.0.1"),                     __L("additionalPolicy")                               , false },
                                                { __L("2.23.42.4"),                         __L("algorithm")                                      , false },
                                                { __L("2.23.42.5"),                         __L("policy")                                         , false },
                                                { __L("2.23.42.5.0"),                       __L("root")                                           , false },
                                                { __L("2.23.42.6"),                         __L("module")                                         , false },
                                                { __L("2.23.42.7"),                         __L("certExt")                                        , false },
                                                { __L("2.23.42.7.0"),                       __L("hashedRootKey")                                  , false },
                                                { __L("2.23.42.7.1"),                       __L("certificateType")                                , false },
                                                { __L("2.23.42.7.2"),                       __L("merchantData")                                   , false },
                                                { __L("2.23.42.7.3"),                       __L("cardCertRequired")                               , false },
                                                { __L("2.23.42.7.4"),                       __L("tunneling")                                      , false },
                                                { __L("2.23.42.7.5"),                       __L("setExtensions")                                  , false },
                                                { __L("2.23.42.7.6"),                       __L("setQualifier")                                   , false },
                                                { __L("2.23.42.8"),                         __L("brand")                                          , false },
                                                { __L("2.23.42.8.1"),                       __L("IATA-ATA")                                       , false },
                                                { __L("2.23.42.8.30"),                      __L("Diners")                                         , false },
                                                { __L("2.23.42.8.34"),                      __L("AmericanExpress")                                , false },
                                                { __L("2.23.42.8.4"),                       __L("VISA")                                           , false },
                                                { __L("2.23.42.8.5"),                       __L("MasterCard")                                     , false },
                                                { __L("2.23.42.8.6011"),                    __L("Novus")                                          , false },
                                                { __L("2.23.42.9"),                         __L("vendor")                                         , false },
                                                { __L("2.23.42.9.0"),                       __L("GlobeSet")                                       , false },
                                                { __L("2.23.42.9.1"),                       __L("IBM")                                            , false },
                                                { __L("2.23.42.9.10"),                      __L("Griffin")                                        , false },
                                                { __L("2.23.42.9.11"),                      __L("Certicom")                                       , false },
                                                { __L("2.23.42.9.12"),                      __L("OSS")                                            , false },
                                                { __L("2.23.42.9.13"),                      __L("TenthMountain")                                  , false },
                                                { __L("2.23.42.9.14"),                      __L("Antares")                                        , false },
                                                { __L("2.23.42.9.15"),                      __L("ECC")                                            , false },
                                                { __L("2.23.42.9.16"),                      __L("Maithean")                                       , false },
                                                { __L("2.23.42.9.17"),                      __L("Netscape")                                       , false },
                                                { __L("2.23.42.9.18"),                      __L("Verisign")                                       , false },
                                                { __L("2.23.42.9.19"),                      __L("BlueMoney")                                      , false },
                                                { __L("2.23.42.9.2"),                       __L("CyberCash")                                      , false },
                                                { __L("2.23.42.9.20"),                      __L("Lacerte")                                        , false },
                                                { __L("2.23.42.9.21"),                      __L("Fujitsu")                                        , false },
                                                { __L("2.23.42.9.22"),                      __L("eLab")                                           , false },
                                                { __L("2.23.42.9.23"),                      __L("Entrust")                                        , false },
                                                { __L("2.23.42.9.24"),                      __L("VIAnet")                                         , false },
                                                { __L("2.23.42.9.25"),                      __L("III")                                            , false },
                                                { __L("2.23.42.9.26"),                      __L("OpenMarket")                                     , false },
                                                { __L("2.23.42.9.27"),                      __L("Lexem")                                          , false },
                                                { __L("2.23.42.9.28"),                      __L("Intertrader")                                    , false },
                                                { __L("2.23.42.9.29"),                      __L("Persimmon")                                      , false },
                                                { __L("2.23.42.9.3"),                       __L("Terisa")                                         , false },
                                                { __L("2.23.42.9.30"),                      __L("NABLE")                                          , false },
                                                { __L("2.23.42.9.31"),                      __L("espace-net")                                     , false },
                                                { __L("2.23.42.9.32"),                      __L("Hitachi")                                        , false },
                                                { __L("2.23.42.9.33"),                      __L("Microsoft")                                      , false },
                                                { __L("2.23.42.9.34"),                      __L("NEC")                                            , false },
                                                { __L("2.23.42.9.35"),                      __L("Mitsubishi")                                     , false },
                                                { __L("2.23.42.9.36"),                      __L("NCR")                                            , false },
                                                { __L("2.23.42.9.37"),                      __L("e-COMM")                                         , false },
                                                { __L("2.23.42.9.38"),                      __L("Gemplus")                                        , false },
                                                { __L("2.23.42.9.4"),                       __L("RSADSI")                                         , false },
                                                { __L("2.23.42.9.5"),                       __L("VeriFone")                                       , false },
                                                { __L("2.23.42.9.6"),                       __L("TrinTech")                                       , false },
                                                { __L("2.23.42.9.7"),                       __L("BankGate")                                       , false },
                                                { __L("2.23.42.9.8"),                       __L("GTE")                                            , false },
                                                { __L("2.23.42.9.9"),                       __L("CompuSource")                                    , false },
                                                { __L("2.5.29.1"),                          __L("authorityKeyIdentifier")                         , false },
                                                { __L("2.5.29.10"),                         __L("basicConstraints")                               , false },
                                                { __L("2.5.29.11"),                         __L("nameConstraints")                                , false },
                                                { __L("2.5.29.12"),                         __L("policyConstraints")                              , false },
                                                { __L("2.5.29.13"),                         __L("basicConstraints")                               , false },
                                                { __L("2.5.29.14"),                         __L("subjectKeyIdentifier")                           , true  },
                                                { __L("2.5.29.15"),                         __L("keyUsage")                                       , true  },
                                                { __L("2.5.29.16"),                         __L("privateKeyUsagePeriod")                          , false },
                                                { __L("2.5.29.17"),                         __L("subjectAltName")                                 , false },
                                                { __L("2.5.29.18"),                         __L("issuerAltName")                                  , false },
                                                { __L("2.5.29.19"),                         __L("basicConstraints")                               , true  },
                                                { __L("2.5.29.2"),                          __L("keyAttributes")                                  , false },
                                                { __L("2.5.29.20"),                         __L("cRLNumber")                                      , false },
                                                { __L("2.5.29.21"),                         __L("cRLReason")                                      , false },
                                                { __L("2.5.29.22"),                         __L("expirationDate")                                 , false },
                                                { __L("2.5.29.23"),                         __L("instructionCode")                                , false },
                                                { __L("2.5.29.24"),                         __L("invalidityDate")                                 , false },
                                                { __L("2.5.29.25"),                         __L("cRLDistributionPoints")                          , false },
                                                { __L("2.5.29.26"),                         __L("issuingDistributionPoint")                       , false },
                                                { __L("2.5.29.27"),                         __L("deltaCRLIndicator")                              , false },
                                                { __L("2.5.29.28"),                         __L("issuingDistributionPoint")                       , false },
                                                { __L("2.5.29.29"),                         __L("certificateIssuer")                              , false },
                                                { __L("2.5.29.3"),                          __L("certificatePolicies")                            , false },
                                                { __L("2.5.29.30"),                         __L("nameConstraints")                                , false },
                                                { __L("2.5.29.31"),                         __L("cRLDistributionPoints")                          , false },
                                                { __L("2.5.29.32"),                         __L("certificatePolicies")                            , false },
                                                { __L("2.5.29.33"),                         __L("policyMappings")                                 , false },
                                                { __L("2.5.29.34"),                         __L("policyConstraints")                              , false },
                                                { __L("2.5.29.35"),                         __L("authorityKeyIdentifier")                         , false },
                                                { __L("2.5.29.36"),                         __L("policyConstraints")                              , false },
                                                { __L("2.5.29.37"),                         __L("extKeyUsage")                                    , false },
                                                { __L("2.5.29.4"),                          __L("keyUsageRestriction")                            , false },
                                                { __L("2.5.29.5"),                          __L("policyMapping")                                  , false },
                                                { __L("2.5.29.6"),                          __L("subtreesConstraint")                             , false },
                                                { __L("2.5.29.7"),                          __L("subjectAltName")                                 , false },
                                                { __L("2.5.29.8"),                          __L("issuerAltName")                                  , false },
                                                { __L("2.5.29.9"),                          __L("subjectDirectoryAttributes")                     , false },
                                                { __L("2.5.4.0"),                           __L("objectClass")                                    , false },
                                                { __L("2.5.4.1"),                           __L("aliasObjectName")                                , false },
                                                { __L("2.5.4.10"),                          __L("organizationName")                               , false },
                                                { __L("2.5.4.11"),                          __L("organizationalUnitName")                         , false },
                                                { __L("2.5.4.12"),                          __L("title")                                          , false },
                                                { __L("2.5.4.13"),                          __L("description")                                    , false },
                                                { __L("2.5.4.14"),                          __L("searchGuide")                                    , false },
                                                { __L("2.5.4.15"),                          __L("businessCategory")                               , false },
                                                { __L("2.5.4.16"),                          __L("postalAddress")                                  , false },
                                                { __L("2.5.4.17"),                          __L("postalCode")                                     , false },
                                                { __L("2.5.4.18"),                          __L("postOfficeBox")                                  , false },
                                                { __L("2.5.4.19"),                          __L("physicalDeliveryOfficeName")                     , false },
                                                { __L("2.5.4.2"),                           __L("knowledgeInformation")                           , false },
                                                { __L("2.5.4.20"),                          __L("telephoneNumber")                                , false },
                                                { __L("2.5.4.21"),                          __L("telexNumber")                                    , false },
                                                { __L("2.5.4.22"),                          __L("teletexTerminalIdentifier")                      , false },
                                                { __L("2.5.4.23"),                          __L("facsimileTelephoneNumber")                       , false },
                                                { __L("2.5.4.24"),                          __L("x121Address")                                    , false },
                                                { __L("2.5.4.25"),                          __L("internationalISDNNumber")                        , false },
                                                { __L("2.5.4.26"),                          __L("registeredAddress")                              , false },
                                                { __L("2.5.4.27"),                          __L("destinationIndicator")                           , false },
                                                { __L("2.5.4.28"),                          __L("preferredDeliveryMehtod")                        , false },
                                                { __L("2.5.4.29"),                          __L("presentationAddress")                            , false },
                                                { __L("2.5.4.3"),                           __L("commonName")                                     , false },
                                                { __L("2.5.4.30"),                          __L("supportedApplicationContext")                    , false },
                                                { __L("2.5.4.31"),                          __L("member")                                         , false },
                                                { __L("2.5.4.32"),                          __L("owner")                                          , false },
                                                { __L("2.5.4.33"),                          __L("roleOccupant")                                   , false },
                                                { __L("2.5.4.34"),                          __L("seeAlso")                                        , false },
                                                { __L("2.5.4.35"),                          __L("userPassword")                                   , false },
                                                { __L("2.5.4.36"),                          __L("userCertificate")                                , false },
                                                { __L("2.5.4.37"),                          __L("caCertificate")                                  , false },
                                                { __L("2.5.4.38"),                          __L("authorityRevocationList")                        , false },
                                                { __L("2.5.4.39"),                          __L("certificateRevocationList")                      , false },
                                                { __L("2.5.4.4"),                           __L("surname")                                        , false },
                                                { __L("2.5.4.40"),                          __L("crossCertificatePair")                           , false },
                                                { __L("2.5.4.41"),                          __L("givenName")                                      , false },
                                                { __L("2.5.4.42"),                          __L("givenName")                                      , false },
                                                { __L("2.5.4.5"),                           __L("serialNumber")                                   , false },
                                                { __L("2.5.4.52"),                          __L("supportedAlgorithms")                            , false },
                                                { __L("2.5.4.53"),                          __L("deltaRevocationList")                            , false },
                                                { __L("2.5.4.58"),                          __L("crossCertificatePair")                           , false },
                                                { __L("2.5.4.6"),                           __L("countryName")                                    , false },
                                                { __L("2.5.4.7"),                           __L("localityName")                                   , false },
                                                { __L("2.5.4.8"),                           __L("stateOrProvinceName")                            , false },
                                                { __L("2.5.4.9"),                           __L("streetAddress")                                  , false },
                                                { __L("2.5.8"),                             __L("X.500-Algorithms")                               , false },
                                                { __L("2.5.8.1"),                           __L("X.500-Alg-Encryption")                           , false },
                                                { __L("2.5.8.1.1"),                         __L("rsa")                                            , false } 
                                              }; 


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XASN1::XASN1()
* @brief      Constructor
* @ingroup    XUTILS
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XASN1::XASN1()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XASN1::~XASN1()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XASN1::~XASN1()
{
  if(ber)
    {
      delete ber;
    }

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XASN1_OID_PROPERTY* XASN1::GetOIDProperty(XCHAR* OID)
* @brief      GetOIDProperty
* @ingroup    XUTILS
* 
* @param[in]  OID : 
* 
* @return     XASN1_OID_PROPERTY* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XASN1_OID_PROPERTY* XASN1::GetOIDProperty(XCHAR* OID)
{
  XSTRING _OID = OID;

  for(XDWORD c=0; c<(sizeof(OID_properties)/sizeof(XASN1_OID_PROPERTY)); c++)
    {
      if(!_OID.Compare(OID_properties[c].OID, true))
        {
          return &OID_properties[c];
        }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XCHAR* XASN1::GetOIDDescription(XCHAR* OID)
* @brief      GetOIDDescription
* @ingroup    XUTILS
* 
* @param[in]  OID : 
* 
* @return     XCHAR* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR* XASN1::GetOIDPropertyDescription(XCHAR* OID)
{
  XSTRING _OID = OID;

  for(XDWORD c=0; c<(sizeof(OID_properties)/sizeof(XASN1_OID_PROPERTY)); c++)
    {
      if(!_OID.Compare(OID_properties[c].OID, true))
        {
          return OID_properties[c].description;
        }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XASN1::Decode(XBUFFER& databin)
* @brief      Decode
* @ingroup    XUTILS
* 
* @param[in]  databin : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XASN1::Decode(XBUFFER& databin)
{
  if(!databin.GetSize()) return false;

  if(ber)
    {
      delete ber;
      ber = NULL;
    }

  ber = new XBER();
  if(!ber) return NULL;

  if(!ber->SetFromDump(databin))
    {
      delete ber;
      ber = NULL;      
    }

  return (ber?true:false);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XASN1::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XASN1::Clean()
{
  ber = NULL;
}
