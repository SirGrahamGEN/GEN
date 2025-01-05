/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XLicense.cpp
* 
* @class      XLICENSE
* @brief      eXtended Utils License generator and control class
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XLicense.h"

#include "XFactory.h"
#include "XPublisher.h"
#include "XFileHash.h"
#include "XFile.h"
#include "XFileINI.h"

#include "HashSHA1.h"
#include "CipherAES.h"

#include "DIOFactory.h"
#include "DIOMAC.h"
#include "DIOWebClient.h"
#include "DIOStreamDeviceIP.h"
#include "DIOStreamIPLocalEnumDevices.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


#pragma region CLASS_XLICENSEID


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLICENSEID::XLICENSEID()
* @brief      Constructor
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XLICENSEID::XLICENSEID()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLICENSEID::~XLICENSEID()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XLICENSEID::~XLICENSEID()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLICENSEID::GetPart(int npart, XDWORD part)
* @brief      GetPart
* @ingroup    XUTILS
*
* @param[in]  npart :
* @param[in]  part :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLICENSEID::GetPart(int npart, XDWORD part)
{
  if(npart<0)                      return false;
  if(npart>=XLICENSE_MAXIDPARTS)   return false;

  part = this->part[npart];

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLICENSEID::SetPart(int npart, XDWORD part)
* @brief      SetPart
* @ingroup    XUTILS
*
* @param[in]  npart :
* @param[in]  part :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLICENSEID::SetPart(int npart, XDWORD part)
{
  if(npart<0)                      return false;
  if(npart>=XLICENSE_MAXIDPARTS)   return false;

  this->part[npart] = part;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD* XLICENSEID::GetParts()
* @brief      GetParts
* @ingroup    XUTILS
*
* @return     XDWORD* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD* XLICENSEID::GetParts()
{
  return part;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XLICENSEID::GetXBuffer(XBUFFER& xbuffer)
* @brief      GetXBuffer
* @ingroup    XUTILS
*
* @param[in]  xbuffer :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XLICENSEID::GetXBuffer(XBUFFER& xbuffer)
{
  for(int c=0; c<XLICENSE_MAXIDPARTS; c++)
    {
      xbuffer.Add((XDWORD)part[c]);
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XLICENSEID::GetXString(XSTRING& IDstring)
* @brief      GetXString
* @ingroup    XUTILS
*
* @param[in]  IDstring :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XLICENSEID::GetXString(XSTRING& IDstring)
{
  XSTRING partstring;

  IDstring.Empty();

  for(int c=0; c<XLICENSE_MAXIDPARTS; c++)
    {
      partstring.Format(__L("%08X"), part[c]);
      IDstring += partstring;
      if(c != (XLICENSE_MAXIDPARTS-1))  IDstring +=__C('-');
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XLICENSEID::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XLICENSEID::Clean()
{
  for(int c=0; c<XLICENSE_MAXIDPARTS; c++)
    {
      part[c] = 0;
    }
}


#pragma endregion


#pragma region CLASS_XLICENSE


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLICENSE::XLICENSE()
* @brief      Constructor
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XLICENSE::XLICENSE()
{
  Clean();

  license = new XBUFFER();

  RegisterEvent(XLICENSEXEVENT_TYPE_INVALID);
  RegisterEvent(XLICENSEXEVENT_TYPE_EXPIRED);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLICENSE::~XLICENSE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XLICENSE::~XLICENSE()
{
  DeRegisterEvent(XLICENSEXEVENT_TYPE_INVALID);
  DeRegisterEvent(XLICENSEXEVENT_TYPE_EXPIRED);

  delete license;

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLICENSE::GenerateMachineID(XLICENSEID& licenseID)
* @brief      GenerateMachineID
* @ingroup    XUTILS
*
* @param[in]  licenseID :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLICENSE::GenerateMachineID(XLICENSEID& licenseID)
{
  DIOSTREAMIPLOCALENUMDEVICES* enumdevices = (DIOSTREAMIPLOCALENUMDEVICES*)GEN_DIOFACTORY.CreateStreamEnumDevices(DIOSTREAMENUMTYPE_IP_LOCAL);
  if(enumdevices)
    {
      enumdevices->Search();

      XQWORD  basicID     = 0;
      XSTRING basicstring;
      XBUFFER basicxbuffer;

      for(int c=0;c<(int)enumdevices->GetDevices()->GetSize();c++)
        {
          DIOSTREAMDEVICEIP* device = (DIOSTREAMDEVICEIP*)enumdevices->GetDevices()->Get(c);
          if(device)
            {
              DIOMAC* mac = device->GetMAC();
              if(mac)
                {
                  XQWORD macID = 0;

                  for(int d=0; d<DIOMAC_MAXSIZE; d++)
                    {
                      macID |= mac->Get()[d];
                      macID<<=8;
                    }

                  basicID ^= macID;
                }
            }
        }

      GEN_DIOFACTORY.DeleteStreamEnumDevices(enumdevices);

      basicstring.Format(__L("%02X%02X%llX%llX%02X%02X"), XLICENSE_VERSION, XLICENSE_SUBVERSION, basicID, ~basicID, XLICENSE_VERSION, XLICENSE_SUBVERSION);

      HASHSHA1* sha1 = new HASHSHA1();
      if(sha1)
        {
          basicstring.ConvertHexStringToBuffer(basicxbuffer);
          sha1->Do(basicxbuffer);

          XDWORD index      = 0;
          XDWORD partID     = 0;
          int    sizeofpart = sizeof(XDWORD)/sizeof(XBYTE);

          for(int c=0; c<XLICENSE_MAXIDPARTS; c++)
            {
              partID = 0;
              for(int d=0; d<sizeofpart; d++)
                {
                  partID |= (XBYTE)sha1->GetResult()->GetByte(index++);
                  if(d!=(sizeofpart-1)) partID<<=8;
                  if(index>=sha1->GetResult()->GetSize()) index = 0;
                }

              licenseID.SetPart(c, partID);
            }

          delete sha1;

          return true;
        }
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLICENSE::Generate(XLICENSEID& licenseID, XSTRING* applicationID, XBUFFER* license)
* @brief      Generate
* @ingroup    XUTILS
*
* @param[in]  licenseID :
* @param[in]  applicationID :
* @param[in]  license :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLICENSE::Generate(XLICENSEID& licenseID, XSTRING* applicationID, XBUFFER* license)
{
  CIPHERAES             cipherAES;
  CIPHERKEYSYMMETRICAL  key;
  XBUFFER               xbufferkey;
  XBUFFER               xbuffercipher;
  XBUFFER*              _license       = license;
  XSTRING*              _applicationID = applicationID;

  if(!_license) _license = this->license;
  if(!_license) return false;

  if(!_applicationID) _applicationID = &this->applicationID;
  if(!_applicationID) return false;

  _license->Delete();
  licenseID.GetXBuffer(xbuffercipher);

  GetBufferKeyFromMachineID((*_applicationID), xbufferkey);

  key.Set(xbufferkey);

  cipherAES.SetKey(&key);
  cipherAES.SetChainingMode(CIPHERCHAININGMODE_CBC);
  cipherAES.SetPaddingType(XBUFFER_PADDINGTYPE_NONE);

  if(cipherAES.Cipher(xbuffercipher))
    {
      _license->Delete();
      _license->Add(cipherAES.GetResult());

      return true;
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLICENSE::GetBufferKeyFromMachineID(XSTRING& applicationID, XBUFFER& xbufferkey)
* @brief      GetBufferKeyFromMachineID
* @ingroup    XUTILS
*
* @param[in]  applicationID :
* @param[in]  xbufferkey :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLICENSE::GetBufferKeyFromMachineID(XSTRING& applicationID, XBUFFER& xbufferkey)
{
  HASHSHA1 sha1;

  xbufferkey.Delete();

  
  XBUFFER charstr;
    
  applicationID.ConvertToASCII(charstr);
  xbufferkey.Add((XBYTE*)charstr.Get(), applicationID.GetSize());

  sha1.Do(xbufferkey);

  xbufferkey.Delete();
  xbufferkey.Add(sha1.GetResult());

  xbufferkey.Resize(16);

  return xbufferkey.GetSize()?true:false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLICENSE::CipherExpirationDate(bool cipher, XSTRING& applicationID, XSTRING& expirationdate)
* @brief      CipherExpirationDate
* @ingroup    XUTILS
*
* @param[in]  cipher :
* @param[in]  applicationID :
* @param[in]  expirationdate :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLICENSE::CipherExpirationDate(bool cipher, XSTRING& applicationID, XSTRING& expirationdate)
{
  XBUFFER               xbufferkey;
  CIPHERAES             cipherAES;
  CIPHERKEYSYMMETRICAL  key;
  bool                  status = false;

  if(!GetBufferKeyFromMachineID(applicationID, xbufferkey)) return false;

  key.Set(xbufferkey);

  cipherAES.SetKey(&key);
  cipherAES.SetChainingMode(CIPHERCHAININGMODE_CBC);
  cipherAES.SetPaddingType(XBUFFER_PADDINGTYPE_SPACES);

  if(cipher)
    {
      XBUFFER charstr;
      
      expirationdate.ConvertToASCII(charstr);
   
      status = cipherAES.Cipher((XBYTE*)charstr.Get(), expirationdate.GetSize());
      if(status)
        {
          cipherAES.GetResult()->ConvertToBase64(expirationdate);
          return true;
        }
    }
   else
    {
      XBUFFER xbuffer;

      xbuffer.ConvertFromBase64(expirationdate);

      status = cipherAES.Uncipher(xbuffer);
      if(status)
        {
          expirationdate.Empty();

          for(XDWORD c=0;  c<cipherAES.GetResult()->GetSize(); c++)
            {
              expirationdate.Add((XCHAR)cipherAES.GetResult()->GetByte(c));
            }

          expirationdate.DeleteCharacter(0x20, XSTRINGCONTEXT_TO_END);

          return true;
        }
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* XLICENSE::GetApplicationID()
* @brief      GetApplicationID
* @ingroup    XUTILS
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* XLICENSE::GetApplicationID()
{
  return &applicationID;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDATETIME* XLICENSE::GetExpirationDateTime()
* @brief      GetExpirationDateTime
* @ingroup    XUTILS
*
* @return     XDATETIME* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDATETIME* XLICENSE::GetExpirationDateTime()
{
  return &expirationdatetime;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBUFFER* XLICENSE::Get()
* @brief      Get
* @ingroup    XUTILS
*
* @return     XBUFFER* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XBUFFER* XLICENSE::Get()
{
  return license;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLICENSE::Get(XSTRING& licensestring)
* @brief      Get
* @ingroup    XUTILS
*
* @param[in]  licensestring :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLICENSE::Get(XSTRING& licensestring)
{
  licensestring.Empty();

  if(!license)            return false;
  if(!license->GetSize()) return false;

  for(XDWORD c=0; c<license->GetSize(); c++)
    {
      XSTRING hexchar;

      hexchar.Format(__L("%02X"), license->GetByte(c));
      licensestring += hexchar;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLICENSE::LoadFromFile(XPATH& xpath, XSTRING& applicationID, XBUFFER* license, XSTRING* expirationdate)
* @brief      LoadFromFile
* @ingroup    XUTILS
*
* @param[in]  xpath :
* @param[in]  applicationID :
* @param[in]  license :
* @param[in]  expirationdate :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLICENSE::LoadFromFile(XPATH& xpath, XSTRING& applicationID, XBUFFER* license, XSTRING* expirationdate)
{
  if(!license) return false;

  XFILE*    xfile   = NULL;
  XBUFFER   xbuffer;
  bool      status  = false;

  GEN_XFACTORY_CREATE(xfile, Create_File())
  if(!xfile) return false;

  if(xfile->Open(xpath))
    {
      xbuffer.Resize((XDWORD)xfile->GetSize());

      status = xfile->Read(xbuffer.Get(), xbuffer.GetSize());

      xfile->Close();
      GEN_XFACTORY.Delete_File(xfile);

      if(status) status = LoadFromBuffer(xbuffer, applicationID, license, expirationdate);
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLICENSE::LoadFromURL(DIOURL& url, int timeout, XSTRING* IPlocal, XSTRING& applicationID, XBUFFER* license, XSTRING* expirationdate)
* @brief      LoadFromURL
* @ingroup    XUTILS
*
* @param[in]  url :
* @param[in]  timeout :
* @param[in]  IPlocal :
* @param[in]  applicationID :
* @param[in]  license :
* @param[in]  expirationdate :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLICENSE::LoadFromURL(DIOURL& url, int timeout, XSTRING* IPlocal, XSTRING& applicationID, XBUFFER* license, XSTRING* expirationdate)
{
  DIOWEBCLIENT* webclient = new DIOWEBCLIENT;
  if(!webclient) return false;

  XBUFFER xbuffer;
  bool    status;

  status = webclient->Get(url.Get(), xbuffer, NULL, timeout, IPlocal);
  if(status) status = LoadFromBuffer(xbuffer, applicationID, license, expirationdate);

  delete webclient;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLICENSE::LoadFromBuffer(XBUFFER& xbuffer, XSTRING& applicationID, XBUFFER* license, XSTRING* expirationdate)
* @brief      LoadFromBuffer
* @ingroup    XUTILS
*
* @param[in]  xbuffer :
* @param[in]  applicationID :
* @param[in]  license :
* @param[in]  expirationdate :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLICENSE::LoadFromBuffer(XBUFFER& xbuffer, XSTRING& applicationID, XBUFFER* license, XSTRING* expirationdate)
{
  if(!license) return false;

  XFILEINI    fileini;
  XLICENSEID  licenseID;
  XSTRING     licenseIDstring;
  XSTRING     licenseIDstring2;
  XSTRING     licensestring;
  XSTRING     licenseexprirationstring;
  XBUFFER*    _license = license;

  if(!_license) _license = this->license;
  if(!_license) return false;

  fileini.AddBufferLines(XFILETXTFORMATCHAR_ASCII, xbuffer);

  fileini.ConvertFromLines();

  fileini.ReadValue(XLICENSE_FILESECTION, XLICENSE_FILEVALUE_ID         , licenseIDstring);
  fileini.ReadValue(XLICENSE_FILESECTION, XLICENSE_FILEVALUE_LICENSE    , licensestring);
  fileini.ReadValue(XLICENSE_FILESECTION, XLICENSE_FILEVALUE_EXPIRATION , licenseexprirationstring);

  GenerateMachineID(licenseID);
  licenseID.GetXString(licenseIDstring2);

  if(licenseIDstring.Compare(licenseIDstring2)) return false;

  CipherExpirationDate(false, applicationID, licenseexprirationstring);

  if(expirationdate) (*expirationdate) = licenseexprirationstring;

  licensestring.ConvertHexStringToBuffer((*_license));

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLICENSE::CheckMasterCreation(XPATH& xpath, XLICENSEID& licenseID, XSTRING& applicationID, int expirationseconds)
* @brief      CheckMasterCreation
* @ingroup    XUTILS
*
* @param[in]  xpath :
* @param[in]  licenseID :
* @param[in]  applicationID :
* @param[in]  expirationseconds :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLICENSE::CheckMasterCreation(XPATH& xpath, XLICENSEID& licenseID, XSTRING& applicationID, int expirationseconds)
{
  XFILEINI    fileini;
  XSTRING     licensestring;

  if(!fileini.Open(xpath)) return false;
  fileini.ReadValue(XLICENSE_FILESECTION, XLICENSE_FILEVALUE_LICENSE, licensestring);
  fileini.Close();

  if(!applicationID.Compare(licensestring))
    {
      XFILEINI    fileini;
      XSTRING     licenseIDstring;
      XSTRING     licensestring;
      XSTRING     licenseexpiration;
      XBUFFER     licencia;
      XDATETIME*  expirationdatetime;

      licenseID.GetXString(licenseIDstring);
      if(!Generate(licenseID, &applicationID, &licencia)) return false;

      licensestring.ConvertHexStringFromBuffer(licencia);

      GEN_XFACTORY_CREATE(expirationdatetime, CreateDateTime())
      if(!expirationdatetime) return false;

      expirationdatetime->SetToZero();
      if(expirationseconds)
        {
          expirationdatetime->Read();
          expirationdatetime->AddSeconds((int)expirationseconds);
        }

      expirationdatetime->GetDateTimeToString(XDATETIME_FORMAT_STANDARD,  licenseexpiration);
      GEN_XFACTORY.DeleteDateTime(expirationdatetime);

      if(!CipherExpirationDate(true, applicationID, licenseexpiration)) return false;

      if(!fileini.Create(xpath)) return false;

      fileini.CreateSection(XLICENSE_FILESECTION);
      fileini.WriteValue(XLICENSE_FILESECTION, XLICENSE_FILEVALUE_ID        , licenseIDstring);
      fileini.WriteValue(XLICENSE_FILESECTION, XLICENSE_FILEVALUE_LICENSE   , licensestring);
      fileini.WriteValue(XLICENSE_FILESECTION, XLICENSE_FILEVALUE_EXPIRATION, licenseexpiration);

      fileini.Close();

      return true;
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLICENSE::SetEvent(XLICENSEXEVENT_TYPE type)
* @brief      SetEvent
* @ingroup    XUTILS
*
* @param[in]  type :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLICENSE::SetEvent(XLICENSEXEVENT_TYPE type)
{
  XLICENSE_XEVENT xlicenseevent(this, type);

  xlicenseevent.Set(this);
  PostEvent(&xlicenseevent);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XLICENSE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XLICENSE::Clean()
{
  license = NULL;
}


#pragma endregion


#pragma endregion

