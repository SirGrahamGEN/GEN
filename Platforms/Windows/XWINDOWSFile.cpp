/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XWINDOWSFile.cpp
* 
* @class      XWINDOWSFILE
* @brief      WINDOWS eXtended Utils File class
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XWINDOWSFile.h"

#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <share.h>

#include "XPath.h"
#include "XString.h"
#include "XTrace.h"

#include "Cipher.h"

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


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWINDOWSFILE::XWINDOWSFILE()
* @brief      Constructor of class
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
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    PLATFORM_WINDOWS
*
* --------------------------------------------------------------------------------------------------------------------*/
XWINDOWSFILE::~XWINDOWSFILE()
{
  if(isopen) this->Close();

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
  //bool status = ExtendedOpen(xpath, (isreadonly)? XWINDOWSFILEMODE_READONLY: XWINDOWSFILEMODE_READWRITE);
  bool status = ExtendedOpen(xpath, XWINDOWSFILEMODE_READONLY);
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
  this->isreadonly = isreadonly;

  return ExtendedOpen(xpath, (isreadonly)? XWINDOWSFILEMODE_READONLY: XWINDOWSFILEMODE_READWRITE);
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
  this->isreadonly = false;

  return ExtendedOpen(xpath, XWINDOWSFILEMODE_CREATE);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSFILE::SetSize(XQWORD size)
* @brief      Set size
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSFILE::SetSize(XQWORD size)
{
  if(!isopen)                   return false;
  if(!filehandle)               return false;
  if(!SetPosition(size))        return false;
  if(!SetEndOfFile(filehandle)) return false;

  ActualizeSize();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSFILE::GetPosition(XQWORD& position)
* @brief      Get position
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

  position = SetFilePointer(filehandle, 0, NULL, FILE_CURRENT);
  if(position == INVALID_SET_FILE_POINTER) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSFILE::SetPosition(XQWORD position)
* @brief      Set position
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

  XQWORD _position    = position;

  if(_position == XFILE_SEEKEND) _position = cachesize;
  if(_position > cachesize) return false;

  //XQWORD mask1 = 0xFFFFFFFF00000000;

  XDWORD high_position = HighQWORD(_position);
  XDWORD low_position  = LowQWORD(_position);

  if(SetFilePointer(filehandle, low_position, (PLONG)&high_position, FILE_BEGIN) == INVALID_SET_FILE_POINTER) return false;

  return true;
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

  DWORD br;

  if(!ReadFile(filehandle, buffer, size, &br, NULL)) return false;
  if(size!=br)  return false;

  if(cipher) cipher->Uncipher(buffer, br);

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

  DWORD br = 0;
  bool  status = true;

  if(!ReadFile(filehandle, buffer, (*size), &br, NULL))
    {
      (*size)= br;
      return false;
    }

  if(br!=(*size))  status=false;

  (*size)= br;

  if(cipher)
    {
      if(cipher->Uncipher(buffer, br))
        {
          memcpy(buffer, cipher->GetResult()->Get(), br);

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

  DWORD bw;

  if(cipher)
    {
      if(!cipher->Cipher(buffer,size)) return false;
      if(!WriteFile(filehandle,(void *)cipher->GetResult()->Get(), size,&bw, NULL)) return false;
      if(bw!=size) return false;
    }
   else
    {
      if(!WriteFile(filehandle,(void *)buffer, size,&bw, NULL)) return false;
      if(bw!=size) return false;
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

  if(!FlushFileBuffers(filehandle)) return false;

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

  if(!isreadonly) Flush();

  if(filehandle)
    {
      if(!DeleteStructHandle())
        {
          CloseHandle(filehandle);      
        }

      #ifdef XTRACE_ACTIVE
      XFileOpenList.Del(this);
      #endif


      isopen     = false;
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
  bool  status = true;
  XPATH _xpath = xpath;

  _xpath.Slash_Normalize(true);

  if(Exist(_xpath.Get()) != true)  
    {
      return false;
    }

  if(overwrite) 
    {
      status = OverwriteContent(_xpath.Get());
    }

  if(status) 
    {
      status = DeleteFile(_xpath.Get())?true:false;
    }

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
  if(!MoveFile(xpathold, xpathnew)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         FILE* XWINDOWSFILE::CreateStructHandle()
* @brief      Create struct handle
* @ingroup    PLATFORM_WINDOWS
*
* @return     FILE* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
FILE* XWINDOWSFILE::CreateStructHandle()
{
  if(fp != NULL) return fp;

  switch(mode)
    {
      case XWINDOWSFILEMODE_READONLY  : fd = _open_osfhandle((intptr_t)filehandle, _O_RDONLY);
                                        if (fd == -1) return NULL;
                                        fp = _fdopen(fd, "rb");                                        
                                        break;

      case XWINDOWSFILEMODE_READWRITE : fd = _open_osfhandle((intptr_t)filehandle, _O_RDWR);
                                        if (fd == -1) return NULL;
                                        fp = _fdopen(fd, "r+b");
                                        break;

      case XWINDOWSFILEMODE_CREATE    : fd = _open_osfhandle((intptr_t)filehandle, _O_CREAT);
                                        if (fd == -1) return NULL;
                                        fp = _fdopen(fd, "w+b");
                                        break;
    }

  return fp;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSFILE::DeleteStructHandle()
* @brief      Delete struct handle
* @ingroup    PLATFORM_WINDOWS
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSFILE::DeleteStructHandle()
{  
  if(fp == NULL) return false;

  fclose(fp);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSFILE::ActualizeSize()
* @brief      Actualize size
* @ingroup    PLATFORM_WINDOWS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSFILE::ActualizeSize()
{
  if(!isopen)       return false;
  if(!filehandle)   return false;

  if(!isreadonly)
    {
      if(!Flush()) return false;
    }

  LARGE_INTEGER exsize;
  if(GetFileSizeEx(filehandle, &exsize) == INVALID_FILE_SIZE) return false;

  cachesize  = exsize.HighPart;
  cachesize <<=32;
  cachesize |= exsize.LowPart;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSFILE::ExtendedOpen(XCHAR* xpath, XWINDOWSFILEMODE mode)
* @brief      Extended open
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  xpath :
* @param[in]  mode :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSFILE::ExtendedOpen(XCHAR* xpath, XWINDOWSFILEMODE mode)
{
  if(isopen) Close();

  this->mode          = mode;

  xpathnamefile.Empty();
  //this->xpathnamefile.Add("\"");
  xpathnamefile.Add(xpath);
  //this->xpathnamefile.Add("\"");

  switch(mode)
    {
      case XWINDOWSFILEMODE_READONLY  : filehandle = CreateFile(xpathnamefile.Get(), GENERIC_READ                , FILE_SHARE_READ                   , NULL, OPEN_EXISTING  , FILE_ATTRIBUTE_NORMAL, NULL);  break;
      case XWINDOWSFILEMODE_READWRITE : filehandle = CreateFile(xpathnamefile.Get(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING  , FILE_ATTRIBUTE_NORMAL, NULL);  break;
      case XWINDOWSFILEMODE_CREATE    : filehandle = CreateFile(xpathnamefile.Get(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS  , FILE_ATTRIBUTE_NORMAL, NULL);  break;
    }

  if(filehandle == INVALID_HANDLE_VALUE)
    {
      //XDWORD err = GetLastError();
      return false;
    }

  isopen = true;

  ActualizeSize();

  #ifdef XTRACE_ACTIVE
  XFileOpenList.Add(this);
  #endif
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XWINDOWSFILE::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    PLATFORM_WINDOWS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XWINDOWSFILE::Clean()
{
  filehandle  = NULL;
  mode        = XWINDOWSFILEMODE_READONLY;

  fd          = -1;  
  fp          = NULL;
}


#pragma endregion


