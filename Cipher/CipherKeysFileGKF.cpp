/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       CipherKeysFileGKF.cpp
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

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "CipherKeysFileGKF.h"

#include "XFactory.h"
#include "XMPInteger.h"
#include "XBuffer.h"
#include "XBER.h"
#include "XFileXML.h"

#include "Cipher.h"
#include "CipherRSA.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         CIPHERKEYSFILEGKF::CIPHERKEYSFILEGKF(XPATH& xpath)
* @brief      Constructor
* @ingroup    CIPHER
* 
* @param[in]  xpath : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
CIPHERKEYSFILEGKF::CIPHERKEYSFILEGKF(XPATH& xpath)
{
  Clean();

  this->xpath  = xpath;

  xfilexml = new XFILEXML();
  if(!xfilexml) return;

  ReadAllFile();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         CIPHERKEYSFILEGKF::~CIPHERKEYSFILEGKF()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    CIPHER
* 
* --------------------------------------------------------------------------------------------------------------------*/
CIPHERKEYSFILEGKF::~CIPHERKEYSFILEGKF()
{
  DeleteAllKeys();

  if(xfilexml) delete xfilexml;

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* CIPHERKEYSFILEGKF::GetCreatorName()
* @brief      GetCreatorName
* @ingroup    CIPHER
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* CIPHERKEYSFILEGKF::GetCreatorName()
{ 
  return &creatorname;                    
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDATETIME* CIPHERKEYSFILEGKF::GetCreatorDateTime()
* @brief      GetCreatorDateTime
* @ingroup    CIPHER
* 
* @return     XDATETIME* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDATETIME* CIPHERKEYSFILEGKF::GetCreatorDateTime()
{ 
  return &creatordatetime;                
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDATETIME* CIPHERKEYSFILEGKF::GetCreatorLastModifiedDateTime()
* @brief      GetCreatorLastModifiedDateTime
* @ingroup    CIPHER
* 
* @return     XDATETIME* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDATETIME* CIPHERKEYSFILEGKF::GetCreatorLastModifiedDateTime()
{ 
  return &creatorlastmodifieddatetime;    
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHERKEYSFILEGKF::HaveKey(CIPHERKEYTYPE type)
* @brief      HaveKey
* @ingroup    CIPHER
* 
* @param[in]  type : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHERKEYSFILEGKF::HaveKey(CIPHERKEYTYPE type)
{
  for(int c=0; c<(int)keys.GetSize(); c++)
    {
      CIPHERKEY* key = keys.Get(c);
      if(key)
        {
          if(key->GetType() == type)  return true;
        }
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         CIPHERKEY* CIPHERKEYSFILEGKF::GetKey(CIPHERKEYTYPE type)
* @brief      GetKey
* @ingroup    CIPHER
* 
* @param[in]  type : 
* 
* @return     CIPHERKEY* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
CIPHERKEY* CIPHERKEYSFILEGKF::GetKey(CIPHERKEYTYPE type)
{
  for(int c=0; c<(int)keys.GetSize(); c++)
    {
      CIPHERKEY* key = keys.Get(c);
      if(key)
        {
          if(key->GetType() == type)  return key;
        }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHERKEYSFILEGKF::AddKey(CIPHERKEY& key)
* @brief      AddKey
* @ingroup    CIPHER
* 
* @param[in]  key : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHERKEYSFILEGKF::AddKey(CIPHERKEY& key)
{
  if(HaveKey(key.GetType())) return false;

  switch(key.GetType())
    {
      case CIPHERKEYTYPE_UNKNOWN        : break;

      case CIPHERKEYTYPE_SYMMETRICAL  : { CIPHERKEYSYMMETRICAL* keysimetrical = new CIPHERKEYSYMMETRICAL();

                                          keysimetrical->CopyFrom((CIPHERKEYSYMMETRICAL*)&key);

                                          keys.Add(keysimetrical);
                                        }
                                        break;

      case CIPHERKEYTYPE_PUBLIC       : { CIPHERKEYRSAPUBLIC* keypublic = new CIPHERKEYRSAPUBLIC();

                                          keypublic->CopyFrom((CIPHERKEYRSAPUBLIC*)&key);
                                          keys.Add(keypublic);
                                        }
                                        break;

      case CIPHERKEYTYPE_PRIVATE      : { CIPHERKEYRSAPRIVATE* keyprivate = new CIPHERKEYRSAPRIVATE();

                                          keyprivate->CopyFrom((CIPHERKEYRSAPRIVATE*)&key);
                                          keys.Add(keyprivate);
                                        }
                                        break;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHERKEYSFILEGKF::DeleteKey(CIPHERKEYTYPE type)
* @brief      DeleteKey
* @ingroup    CIPHER
* 
* @param[in]  type : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHERKEYSFILEGKF::DeleteKey(CIPHERKEYTYPE type)
{
  for(int c=0; c<(int)keys.GetSize(); c++)
    {
      CIPHERKEY* key = keys.Get(c);
      if(key)
        {
          if(key->GetType() == type)
            {
              keys.Delete(key);
              delete key;
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHERKEYSFILEGKF::DeleteAllKeys()
* @brief      DeleteAllKeys
* @ingroup    CIPHER
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHERKEYSFILEGKF::DeleteAllKeys()
{
  if(keys.IsEmpty()) return false;

  keys.DeleteContents();

  keys.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHERKEYSFILEGKF::UpdateFile()
* @brief      UpdateFile
* @ingroup    CIPHER
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHERKEYSFILEGKF::UpdateFile()
{
  if(!xfilexml) return false;

  if(!xfilexml->Create(xpath))   return false;

  XFILEXMLELEMENT* noderoot = new XFILEXMLELEMENT(CIPHERKEYSFILEGKF_NODENAME_ROOT);
  if(!noderoot) return false;

  XFILEXMLELEMENT* node   = NULL;
  XSTRING          string;

  node = noderoot->AddElement(CIPHERKEYSFILEGKF_NODENAME_CREATOR);
  if(node)
    {
      XDATETIME* xdatetime = GEN_XFACTORY.CreateDateTime();
      if(xdatetime)
        {
          xdatetime->Read();

          node->AddAtribute(CIPHERKEYSFILEGKF_ATTRNAME_CREATOR_CREATENAME , creatorname.Get());

          if(!creatordatetime.IsValidDate()) creatordatetime.CopyFrom(xdatetime);
          creatordatetime.GetDateTimeToString(XDATETIME_FORMAT_STANDARD, string);
          node->AddAtribute(CIPHERKEYSFILEGKF_ATTRNAME_CREATOR_CREATEDATE , string.Get());

          creatorlastmodifieddatetime.CopyFrom(xdatetime);

          creatorlastmodifieddatetime.GetDateTimeToString(XDATETIME_FORMAT_STANDARD, string);
          node->AddAtribute(CIPHERKEYSFILEGKF_ATTRNAME_CREATOR_LASTMODDATE , string.Get());

          GEN_XFACTORY.DeleteDateTime(xdatetime);
        }

      for(int c=0; c<(int)keys.GetSize(); c++)
        {
          CIPHERKEY* key = keys.Get(c);
          if(key)
            {
              if(key->GetType()!=CIPHERKEYTYPE_UNKNOWN)
                {
                  node = noderoot->AddElement(CIPHERKEYSFILEGKF_NODENAME_CIPHERKEY);
                  if(node)
                    {
                      string.Format(__L("%d"), key->GetType());
                      node->AddAtribute(CIPHERKEYSFILEGKF_ATTRNAME_CIPHERKEY_TYPEKEY, string.Get());

                      string.Format(__L("%d"), key->GetSizeInBits());
                      node->AddAtribute(CIPHERKEYSFILEGKF_ATTRNAME_CIPHERKEY_SIZEBITS, string.Get());

                      switch(key->GetType())
                        {
                          case CIPHERKEYTYPE_UNKNOWN        : break;

                          case CIPHERKEYTYPE_SYMMETRICAL  : { CIPHERKEYSYMMETRICAL* keysimetrical = (CIPHERKEYSYMMETRICAL*)key;
                                                              XBUFFER* xbuffer = keysimetrical->Get();
                                                              if(xbuffer) string.ConvertHexStringFromBuffer((*xbuffer));

                                                              node->AddAtribute(CIPHERKEYSFILEGKF_ATTRNAME_CIPHERKEY_KEY , string.Get());
                                                            }
                                                            break;

                          case CIPHERKEYTYPE_PUBLIC       : { CIPHERKEYRSAPUBLIC* keypublic = (CIPHERKEYRSAPUBLIC*)key;
                                                              XMPINTEGER          modulus;
                                                              XMPINTEGER          exponent;

                                                              keypublic->Get(modulus, exponent);

                                                              modulus.GetToString(16, string);
                                                              node->AddAtribute(CIPHERKEYSFILEGKF_ATTRNAME_CIPHERKEY_MODULUS , string.Get());

                                                              exponent.GetToString(16, string);
                                                              node->AddAtribute(CIPHERKEYSFILEGKF_ATTRNAME_CIPHERKEY_EXPONENT , string.Get());
                                                            }
                                                            break;

                          case CIPHERKEYTYPE_PRIVATE      : { CIPHERKEYRSAPRIVATE*  keyprivate = (CIPHERKEYRSAPRIVATE*)key;
                                                              XMPINTEGER            prime1factor;
                                                              XMPINTEGER            prime2factor;
                                                              XMPINTEGER            exponent;

                                                              keyprivate->Get(prime1factor, prime2factor, exponent);

                                                              prime1factor.GetToString(16, string);
                                                              node->AddAtribute(CIPHERKEYSFILEGKF_ATTRNAME_CIPHERKEY_FACTOR1 , string.Get());

                                                              prime2factor.GetToString(16, string);
                                                              node->AddAtribute(CIPHERKEYSFILEGKF_ATTRNAME_CIPHERKEY_FACTOR2 , string.Get());

                                                              exponent.GetToString(16, string);
                                                              node->AddAtribute(CIPHERKEYSFILEGKF_ATTRNAME_CIPHERKEY_EXPONENT , string.Get());
                                                            }
                                                            break;
                        }
                    }
                }
            }
        }
    }

  bool status;

  xfilexml->SetRoot(noderoot);

  XVECTOR<XFILEXMLATTRIBUTE*>* CFGatributes = xfilexml->GetCFGAtributes();
  if(CFGatributes)
    {
      XFILEXMLATTRIBUTE* attribute;

      attribute = new XFILEXMLATTRIBUTE(__L("version"),__L("1.0"));
      if(attribute) CFGatributes->Add(attribute);      
    }

  status = xfilexml->EncodeAllLines();
  if(status) status = xfilexml->WriteAllFile();

  xfilexml->DeleteAllElements();

  xfilexml->Close();

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHERKEYSFILEGKF::ExportToPEMFile(CIPHERKEY* key, XSTRING& publicPEM)
* @brief      ExportToPEMFile
* @ingroup    CIPHER
* 
* @param[in]  key : 
* @param[in]  publicPEM : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHERKEYSFILEGKF::ExportToPEMFile(CIPHERKEY* key, XSTRING& publicPEM)
{
  if(!key) return false;

  bool status = false;

  switch(key->GetType())
    {
      case CIPHERKEYTYPE_PUBLIC     : { XBER                  beroui;
                                        XBER                  bernull;
                                        XBER                  berbitstring;
                                        XBER                  bermodule;
                                        XBER                  berexponent;
                                        XBER                  berseq1;
                                        XBER                  berseq2;
                                        XBER                  berseq3;
                                        CIPHERKEYRSAPUBLIC*   publickey = (CIPHERKEYRSAPUBLIC*)key;
                                        XMPINTEGER            module;
                                        XMPINTEGER            exponent;
                                        XBUFFER               xbuffermodule;
                                        XBUFFER               xbuffermodule2;
                                        XBUFFER               xbufferexponent;
                                        XBUFFER               xbufferpem;
                                        XSTRING               string;
                                        XSTRING               stringbase64;
                                        XSTRING               _publicPEM;

                                        publickey->Get(module, exponent);

                                        module.GetToXBuffer(xbuffermodule2    , module.GetSize());
                                        exponent.GetToXBuffer(xbufferexponent , exponent.GetSize());


                                        xbuffermodule.Add((XBYTE)0);
                                        xbuffermodule.Add(xbuffermodule2);
                                        bermodule.SetINTEGER(xbuffermodule);
                                        berexponent.SetINTEGER(xbufferexponent);

                                        berseq2.Sequence_AddTo(bermodule);
                                        berseq2.Sequence_AddTo(berexponent);
                                        berseq2.SetTagType(berseq2.GetTagType()|(XBYTE)(XBERTYPE_ISCONSTRUCTED));

                                        xbufferpem.Add((XBYTE)0);
                                        berseq2.GetDump(xbufferpem);
                                        berbitstring.SetBITSTRING(xbufferpem);

                                        beroui.SetOID(__L("1.2.840.113549.1.1.1"));
                                        bernull.SetNULL();

                                        berseq1.Sequence_AddTo(beroui);
                                        berseq1.Sequence_AddTo(bernull);
                                        berseq1.SetTagType(berseq1.GetTagType()|(XBYTE)(XBERTYPE_ISCONSTRUCTED));

                                        berseq3.Sequence_AddTo(berseq1);
                                        berseq3.Sequence_AddTo(berbitstring);
                                        berseq3.SetTagType(berseq3.GetTagType()|(XBYTE)(XBERTYPE_ISCONSTRUCTED));

                                        xbufferpem.Delete();
                                        berseq3.GetDump(xbufferpem);

                                        string.Set(xbufferpem.Get(), xbufferpem.GetSize());
                                        string.ConvertToBase64(stringbase64);

                                        _publicPEM.Empty();
                                        _publicPEM += __L("-----BEGIN PUBLIC KEY-----\n");

                                        int index       = 0;
                                        int lincounter  = 0;

                                        while(index<(int)stringbase64.GetSize())
                                          {
                                            _publicPEM.Add(stringbase64.Get()[index]);
                                            index++;
                                            lincounter++;

                                            if(lincounter>=64)
                                              {
                                                _publicPEM.Add(__C('\n'));
                                                lincounter = 0;
                                              }
                                          }

                                        _publicPEM.Add(__C('\n'));
                                        _publicPEM += __L("-----END PUBLIC KEY-----\n");

                                        publicPEM = _publicPEM;
                                      }
                                      status = true;
                                      break;

      case CIPHERKEYTYPE_PRIVATE    : break;

                          default   : break;
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHERKEYSFILEGKF::ExportToPEMFile(CIPHERKEY* key, XPATH& xpath)
* @brief      ExportToPEMFile
* @ingroup    CIPHER
* 
* @param[in]  key : 
* @param[in]  xpath : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHERKEYSFILEGKF::ExportToPEMFile(CIPHERKEY* key, XPATH& xpath)
{
  if(!key) return false;

  XSTRING publicPEM;

  if(!ExportToPEMFile(key, publicPEM)) return false;

  XFILE* GEN_XFACTORY_CREATE(xfile, Create_File())
  if(xfile)
    {
      if(xfile->Create(xpath))
        {
          
          XBUFFER charstr;
          publicPEM.ConvertToASCII(charstr);
          xfile->Write((XBYTE*)charstr.Get(), publicPEM.GetSize());
          
          xfile->Close();

          return true;
        }
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XPATH& CIPHERKEYSFILEGKF::GetXPath()
* @brief      GetXPath
* @ingroup    CIPHER
* 
* @return     XPATH& : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XPATH& CIPHERKEYSFILEGKF::GetXPath()
{ 
  return xpath;                           
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILEXML* CIPHERKEYSFILEGKF::GetXFileXML()
* @brief      GetXFileXML
* @ingroup    CIPHER
* 
* @return     XFILEXML* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XFILEXML* CIPHERKEYSFILEGKF::GetXFileXML()
{ 
  return xfilexml;                        
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHERKEYSFILEGKF::ReadAllFile()
* @brief      ReadAllFile
* @ingroup    CIPHER
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHERKEYSFILEGKF::ReadAllFile()
{
  if(!xfilexml) return false;

  if(!xfilexml->Open(xpath))  return false;

  xfilexml->ReadAndDecodeAllLines();

  XFILEXMLELEMENT* noderoot = xfilexml->GetRoot();
  if(noderoot)
    {
      if(!noderoot->GetName().Compare(CIPHERKEYSFILEGKF_NODENAME_ROOT))
        {
          XFILEXMLELEMENT* node   = NULL;
          int              index  = 0;

          do{ node = noderoot->GetElement(index);
              if(node)
                {
                  if(!node->GetName().Compare(CIPHERKEYSFILEGKF_NODENAME_CREATOR))
                    {
                      XSTRING string;

                      node->GetValueAttribute(CIPHERKEYSFILEGKF_ATTRNAME_CREATOR_CREATENAME  , creatorname);
                      if(node->GetValueAttribute(CIPHERKEYSFILEGKF_ATTRNAME_CREATOR_CREATEDATE  , string))  creatordatetime.GetDateTimeFromString(string, XDATETIME_FORMAT_STANDARD);
                      if(node->GetValueAttribute(CIPHERKEYSFILEGKF_ATTRNAME_CREATOR_LASTMODDATE , string))  creatorlastmodifieddatetime.GetDateTimeFromString(string, XDATETIME_FORMAT_STANDARD);
                    }
                   else
                    {
                      if(!node->GetName().Compare(CIPHERKEYSFILEGKF_NODENAME_CIPHERKEY))
                        {
                          XSTRING           string;
                          //int             index2 = 0;

                          if(node->GetValueAttribute(CIPHERKEYSFILEGKF_ATTRNAME_CIPHERKEY_TYPEKEY  , string))
                            {
                              int typekey = string.ConvertToInt();

                              switch(typekey)
                                {
                                  case CIPHERKEYTYPE_UNKNOWN        : break;

                                  case CIPHERKEYTYPE_SYMMETRICAL  : { CIPHERKEYSYMMETRICAL* keysimetrical = new CIPHERKEYSYMMETRICAL();
                                                                      if(keysimetrical)
                                                                        {
                                                                          if(node->GetValueAttribute(CIPHERKEYSFILEGKF_ATTRNAME_CIPHERKEY_KEY  , string))
                                                                            {
                                                                              XBUFFER xbuffer;

                                                                              string.ConvertHexStringToBuffer(xbuffer);
                                                                              keysimetrical->Set(xbuffer);

                                                                              keys.Add(keysimetrical);
                                                                            }
                                                                        }
                                                                    }
                                                                    break;

                                  case CIPHERKEYTYPE_PUBLIC       : { CIPHERKEYRSAPUBLIC* keypublic = new CIPHERKEYRSAPUBLIC();
                                                                      if(keypublic)
                                                                        {
                                                                          XMPINTEGER modulus;
                                                                          XMPINTEGER exponent;

                                                                          modulus.Ini();
                                                                          exponent.Ini();

                                                                          if(node->GetValueAttribute(CIPHERKEYSFILEGKF_ATTRNAME_CIPHERKEY_MODULUS, string))
                                                                            {
                                                                              modulus.SetFromString(16, string);
                                                                              if(node->GetValueAttribute(CIPHERKEYSFILEGKF_ATTRNAME_CIPHERKEY_EXPONENT, string))
                                                                                {
                                                                                  exponent.SetFromString(16, string);

                                                                                  keypublic->Set(modulus,exponent);

                                                                                  keys.Add(keypublic);
                                                                                }
                                                                            }

                                                                          modulus.End();
                                                                          exponent.End();
                                                                       }
                                                                    }
                                                                    break;

                                  case CIPHERKEYTYPE_PRIVATE      : { CIPHERKEYRSAPRIVATE* keyprivate = new CIPHERKEYRSAPRIVATE();
                                                                      if(keyprivate)
                                                                        {
                                                                          XMPINTEGER prime1factor;
                                                                          XMPINTEGER prime2factor;
                                                                          XMPINTEGER exponent;

                                                                          prime1factor.Ini();
                                                                          prime2factor.Ini();
                                                                          exponent.Ini();

                                                                          if(node->GetValueAttribute(CIPHERKEYSFILEGKF_ATTRNAME_CIPHERKEY_FACTOR1, string))
                                                                            {
                                                                              prime1factor.SetFromString(16, string);

                                                                              if(node->GetValueAttribute(CIPHERKEYSFILEGKF_ATTRNAME_CIPHERKEY_FACTOR2, string))
                                                                                {
                                                                                  prime2factor.SetFromString(16, string);

                                                                                  if(node->GetValueAttribute(CIPHERKEYSFILEGKF_ATTRNAME_CIPHERKEY_EXPONENT, string))
                                                                                    {
                                                                                      exponent.SetFromString(16, string);

                                                                                      keyprivate->Set(prime1factor, prime2factor, exponent);

                                                                                      keys.Add(keyprivate);
                                                                                    }
                                                                                }
                                                                            }

                                                                          prime1factor.End();
                                                                          prime2factor.End();
                                                                          exponent.End();
                                                                        }
                                                                      }
                                                                      break;

                                }
                            }
                        }
                    }

                  index++;
                }

            } while(node);
        }
    }

  xfilexml->Close();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void CIPHERKEYSFILEGKF::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    CIPHER
* 
* --------------------------------------------------------------------------------------------------------------------*/
void CIPHERKEYSFILEGKF::Clean()
{
  xfilexml  = NULL;
}


#pragma endregion

