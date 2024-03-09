/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XWINDOWSFileBorland.cpp
* 
* @class      XWINDOWSFILEBORLAND
* @brief      WINDOWS eXtended Utils Borland file class
* @ingroup    PLATFORM_WINDOWS
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

#include "XWINDOWSFileBorland.h"

#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <share.h>

#include "XPath.h"
#include "XString.h"

#include "Cipher.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XWINDOWSFILE::XWINDOWSFILE()
* @brief      Constructor
* @ingroup    PLATFORM_WINDOWS
* 
* --------------------------------------------------------------------------------------------------------------------*/
XWINDOWSFILE::XWINDOWSFILE(): XFILE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XWINDOWSFILE::~XWINDOWSFILE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_WINDOWS
* 
* --------------------------------------------------------------------------------------------------------------------*/
XWINDOWSFILE::~XWINDOWSFILE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XWINDOWSFILE::Exist(XCHAR* xpath)
* @brief      Exist
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  xpath : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSFILE::Exist(XCHAR* xpath)
{
  bool status = Open(xpath, true);
  if(status) Close();

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XWINDOWSFILE::Open(XCHAR* xpath, bool isreadonly)
* @brief      Open
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  xpath : 
* @param[in]  isreadonly : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSFILE::Open(XCHAR* xpath, bool isreadonly)
{
  return ExtendedOpen(xpath, (isreadonly)? __L("rb") : __L("r+b"));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XWINDOWSFILE::Create(XCHAR* xpath)
* @brief      Create
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  xpath : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSFILE::Create(XCHAR* xpath)
{
  return ExtendedOpen(xpath, __L("w+b"));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XWINDOWSFILE::SetSize(XQWORD size)
* @brief      SetSize
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  size : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSFILE::SetSize(XQWORD size)
{
  if(!isopen)       return false;
  if(!filehandle)   return false;

  #ifdef _MSC_VER
  if(_chsize(_fileno(filehandle),size)) return false;
  #else
  if(chsize(_fileno(filehandle),size)) return false;
  #endif

  ActualizeSize();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XWINDOWSFILE::GetPosition(XQWORD& position)
* @brief      GetPosition
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  position : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSFILE::GetPosition(XQWORD& position)
{
  if(!isopen)     return false;
  if(!filehandle) return false;

  position = ftell(filehandle);

  if(position == -1) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XWINDOWSFILE::SetPosition(XQWORD position)
* @brief      SetPosition
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  position : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSFILE::SetPosition(XQWORD position)
{
  if(!isopen)     return false;
  if(!filehandle) return false;

  int  _position    = position;
  bool status;

  if(_position == XFILE_SEEKEND) _position = cachesize;

  if(_position > (int)cachesize) return false;

  status=fseek(filehandle, _position, SEEK_SET)?false:true;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XWINDOWSFILE::Read(XBYTE* buffer, XDWORD size, CIPHER* cipher)
* @brief      Read
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  buffer : 
* @param[in]  size : 
* @param[in]  cipher : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSFILE::Read(XBYTE* buffer, XDWORD size, CIPHER* cipher)
{
  if(!isopen)       return false;
  if(!filehandle)   return false;

  XDWORD _size;

  _size=(int)fread((void *)buffer,1,(size_t)size, filehandle);
  if(_size!=size)  return false;

  if(cipher) cipher->Uncipher(buffer,_size);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XWINDOWSFILE::Read(XBYTE* buffer, XDWORD* size, CIPHER* cipher)
* @brief      Read
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  buffer : 
* @param[in]  size : 
* @param[in]  cipher : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSFILE::Read(XBYTE* buffer, XDWORD* size, CIPHER* cipher)
{
  if(!isopen)       return false;
  if(!filehandle)   return false;

  XDWORD  _size;
  bool    status = true;

  _size=(int)fread((void *)buffer, (size_t)1, (size_t)(*size), filehandle);

  if(_size!=(*size))  status=false;

  (*size)=_size;

  if(cipher)
    {
      if(cipher->Uncipher(buffer,_size))
        {
          memcpy(buffer, cipher->GetResult()->Get(), _size);

        } else status = false;
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XWINDOWSFILE::Write(XBYTE* buffer, XDWORD size, CIPHER* cipher)
* @brief      Write
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  buffer : 
* @param[in]  size : 
* @param[in]  cipher : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSFILE::Write(XBYTE* buffer, XDWORD size, CIPHER* cipher)
{
  if(!isopen)       return false;
  if(!filehandle)   return false;

  if(cipher)
    {
      if(!cipher->Cipher(buffer,size)) return false;
      if(fwrite((void *)cipher->GetResult()->Get(), 1, size, filehandle)!=(unsigned)size)  return false;
    }
   else
    {
      if(fwrite((void *)buffer,1,size, filehandle)!=(unsigned)size)  return false;
    }

  ActualizeSize();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XWINDOWSFILE::Flush()
* @brief      Flush
* @ingroup    PLATFORM_WINDOWS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSFILE::Flush()
{
  if(!isopen)       return false;
  if(!filehandle)   return false;

  fflush(filehandle);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XWINDOWSFILE::Close()
* @brief      Close
* @ingroup    PLATFORM_WINDOWS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSFILE::Close()
{
  if(!isopen)       return false;
  if(!filehandle)   return false;

  Flush();

  if(filehandle)
    {
      fclose(filehandle);

      #ifdef XTRACE_ACTIVE
      XFileOpenList.Del(this);
      #endif

      filehandle = NULL;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XWINDOWSFILE::Erase(XCHAR* xpath,bool overwrite)
* @brief      Erase
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  xpath : 
* @param[in]  overwrite : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSFILE::Erase(XCHAR* xpath,bool overwrite)
{
  bool status=true;

  if(Exist(xpath)!=true)  return false;

  if(overwrite) status = OverwriteContent(xpath);

  if(status) status = DeleteFile(xpath)?true:false;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XWINDOWSFILE::Rename(XCHAR* xpathold, XCHAR* xpathnew)
* @brief      Rename
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  xpathold : 
* @param[in]  xpathnew : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSFILE::Rename(XCHAR* xpathold, XCHAR* xpathnew)
{
  if(!_wrename(xpathold, xpathnew)) return true;

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XWINDOWSFILE::ActualizeSize()
* @brief      ActualizeSize
* @ingroup    PLATFORM_WINDOWS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSFILE::ActualizeSize()
{
  if(!isopen)       return false;
  if(!filehandle)   return false;

  Flush();

  int position = ftell(filehandle);

  fseek(filehandle, 0, SEEK_END);
  cachesize = ftell(filehandle);
  fseek(filehandle, position, SEEK_SET);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XWINDOWSFILE::ExtendedOpen(XCHAR* xpath, XCHAR* mode)
* @brief      ExtendedOpen
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  xpath : 
* @param[in]  mode : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSFILE::ExtendedOpen(XCHAR* xpath, XCHAR* mode)
{
  if(isopen) Close();

  this->xpathnamefile = xpath;

  int error = 0;

  #ifdef BUILDER
  filehandle = _wfopen(xpath, mode);
  if(!filehandle) return false;
  #else
  error = _wfopen_s(&filehandle, xpath, mode);
  #endif

  if(error)        return false;
  if(!filehandle)  return false;

  isopen = true;

  ActualizeSize();

  #ifdef XTRACE_ACTIVE
  XFileOpenList.Add(this);
  #endif

  return true;
}


#pragma endregion

