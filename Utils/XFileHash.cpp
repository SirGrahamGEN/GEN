/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XFileHash.cpp
*
* @class      XFILEHASH
* @brief      eXtended HASH file class (file with HASH included)
* @ingroup    UTILS
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

#include "XBuffer.h"

#include "XFileHash.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEHASH::XFILEHASH(HASH* hash)
* @brief      Constructor
* @ingroup    UTILS
*
* @param[in]  hash :
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEHASH::XFILEHASH(HASH* hash): XFILECONTAINER()
{
  Clean();

  this->hash = hash;

  if(!CreatePrimaryFile()) return;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEHASH::~XFILEHASH()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    UTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEHASH::~XFILEHASH()
{
  Close();

  if(!DeletePrimaryFile()) return;

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEHASH::Open(XPATH& pathname, bool readonly, bool checkhash, bool checkversion)
* @brief      Open
* @ingroup    UTILS
*
* @param[in]  pathname :
* @param[in]  readonly :
* @param[in]  checkhash :
* @param[in]  checkversion :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEHASH::Open(XPATH& pathname, bool readonly, bool checkhash, bool checkversion)
{
  if(!hash) return false;
  if(!file) return false;

  if(!hash->GetDefaultSize()) return false;

  if(file->Exist(pathname)!=true) return false;

  bool status = file->Open(pathname,readonly);

  XSTRING IDini(16);
  XWORD   _ID      = 0;
  XWORD   _type    = 0;
  XWORD   _version = 0;

  if(!file->Read((XBYTE*)IDini.Get(), XSTRING::GetSize(XFILE_ID)*sizeof(XWORD)+1)) return false;

  IDini.AdjustSize();

  if(!file->Read((XBYTE*)&_ID, sizeof(XWORD))) return false;
  if(_ID!=ID) return false;

  if(!file->Read((XBYTE*)&_type, sizeof(XWORD))) return false;
  if(_type!=type) return false;

  if(!file->Read((XBYTE*)&_version,sizeof(XWORD))) return false;
  if(checkversion)
    {
      if(version!=_version)  return false;
    }

  version = _version;

  XDWORD sizeIDstring = 0;

  if(!file->Read((XBYTE*)&sizeIDstring, sizeof(XDWORD))) return false;
  if(sizeIDstring)
    {
      XWORD* IDstr = new XWORD[sizeIDstring+1];
      if(IDstr)
        {
          memset((XBYTE*)IDstr, 0, sizeof(XWORD)*(sizeIDstring+1));

          if(!file->Read((XBYTE*)IDstr, sizeof(XWORD)*sizeIDstring))
            {
              delete [] IDstr;
              return false;
            }

          IDstring.Set((XWORD*)IDstr);

          delete [] IDstr;
        }
    }

  XBUFFER hashbuffer((XDWORD)hash->GetDefaultSize(), true);
  if(!file->Read((XBYTE*)hashbuffer.Get(), hash->GetDefaultSize())) return false;

  file->GetPosition(dataposition);

  XQWORD size =  file->GetSize() - GetDataPosition();

  hash->ResetResult();

  if(!hash->Do(file, size, GetDataPosition())) return false;

  if(checkhash)
    {
      if(!hashbuffer.Compare(hash->GetResult()))
        {
          return false;
        }
    }

  if(readonly) hashisupdate = false;

  file->SetPosition(dataposition);

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEHASH::Create(XPATH& pathname, bool checkHASH)
* @brief      Create
* @ingroup    UTILS
*
* @param[in]  pathname :
* @param[in]  checkHASH :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEHASH::Create(XPATH& pathname, bool checkHASH)
{
  if(!hash) return false;
  if(!file) return false;

  if(!hash->GetDefaultSize()) return false;

  bool status=file->Create(pathname);

  hash->ResetResult();

  XBUFFER hashbuffer((XDWORD)hash->GetDefaultSize(), true);

  XDWORD sizeIDstring  = IDstring.GetSize();

  XSTRING IDini;

  IDini = XFILE_ID;

  XSTRING_CREATENORMALIZE(IDini, buffnormalize, false)
  if(!file->Write((XBYTE*)buffnormalize, IDini.GetSize()*sizeof(XWORD)+1)) return false;
  XSTRING_DELETENORMALIZE(IDini, buffnormalize)

  type |= XFILE_FEATURES_HASH;

  if(!file->Write((XBYTE*)&ID               , sizeof(XWORD)))   return false;
  if(!file->Write((XBYTE*)&type             , sizeof(XWORD)))   return false;
  if(!file->Write((XBYTE*)&version          , sizeof(XWORD)))   return false;
  if(!file->Write((XBYTE*)&sizeIDstring     , sizeof(XDWORD)))  return false;
  if(sizeIDstring)
    {
      XSTRING_CREATENORMALIZE(IDstring, buffnormalize, false)
      if(!file->Write((XBYTE*)buffnormalize, sizeof(XWORD)*sizeIDstring))   return false;
      XSTRING_DELETENORMALIZE(IDstring, buffnormalize)
    }

  if(!file->Write((XBYTE*)hashbuffer.Get()  , hash->GetDefaultSize()))  return false;

  file->GetPosition(dataposition);

  hashisupdate = false;

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEHASH::Close()
* @brief      Close
* @ingroup    UTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEHASH::Close()
{
  if(!file)           return false;
  if(!file->IsOpen()) return false;

  file->Flush();

  if(!hashisupdate) UpdateHash();

  file->Close();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWORD XFILEHASH::GetID()
* @brief      GetID
* @ingroup    UTILS
*
* @return     XWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XWORD XFILEHASH::GetID()
{
  return ID;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWORD XFILEHASH::GetType()
* @brief      GetType
* @ingroup    UTILS
*
* @return     XWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XWORD XFILEHASH::GetType()
{
  return type;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWORD XFILEHASH::GetVersion()
* @brief      GetVersion
* @ingroup    UTILS
*
* @return     XWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XWORD XFILEHASH::GetVersion()
{
  return version;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* XFILEHASH::GetIDString()
* @brief      GetIDString
* @ingroup    UTILS
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* XFILEHASH::GetIDString()
{
  return &IDstring;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEHASH::Set(XWORD ID, XWORD type, XWORD version, XCHAR* IDstring)
* @brief      Set
* @ingroup    UTILS
*
* @param[in]  ID :
* @param[in]  type :
* @param[in]  version :
* @param[in]  IDstring :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEHASH::Set(XWORD ID, XWORD type, XWORD version, XCHAR* IDstring)
{
  SetID(ID);
  SetType(type);
  SetVersion(version);
  SetIDString(IDstring);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEHASH::SetID(XWORD ID)
* @brief      SetID
* @ingroup    UTILS
*
* @param[in]  ID :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEHASH::SetID(XWORD ID)
{
  this->ID = ID;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEHASH::SetType(XWORD type)
* @brief      SetType
* @ingroup    UTILS
*
* @param[in]  type :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEHASH::SetType(XWORD type)
{
  this->type = type;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEHASH::SetVersion(XWORD version)
* @brief      SetVersion
* @ingroup    UTILS
*
* @param[in]  version :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEHASH::SetVersion(XWORD version)
{
  this->version = version;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEHASH::SetIDString(XCHAR* IDstring)
* @brief      SetIDString
* @ingroup    UTILS
*
* @param[in]  IDstring :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEHASH::SetIDString(XCHAR* IDstring)
{
  this->IDstring = IDstring;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEHASH::SetIDString(XSTRING& IDstring)
* @brief      SetIDString
* @ingroup    UTILS
*
* @param[in]  IDstring :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEHASH::SetIDString(XSTRING& IDstring)
{
  this->IDstring = IDstring;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XFILEHASH::GetDataPosition()
* @brief      GetDataPosition
* @ingroup    UTILS
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
XQWORD XFILEHASH::GetDataPosition()
{
  return dataposition;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEHASH::UpdateHash()
* @brief      UpdateHash
* @ingroup    UTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEHASH::UpdateHash()
{
  if(!hash) return false;
  if(!file) return false;

  file->Flush();

  hash->ResetResult();

  XQWORD size =  file->GetSize() - GetDataPosition();

  if(!hash->Do(file, size, GetDataPosition())) return false;

  file->SetPosition(dataposition-hash->GetDefaultSize());

  if(!file->Write((XBYTE*)hash->GetResult()->Get(), hash->GetDefaultSize()))    return false;

  hashisupdate = true;

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILEHASH::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    UTILS
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFILEHASH::Clean()
{
  hash          = NULL;

  ID            = 0;
  type          = 0;
  version       = 0;

  hashisupdate  = false;

  hashposition  = 0;
  dataposition  = 0;
}