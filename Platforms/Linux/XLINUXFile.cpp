/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XLINUXFile.cpp
*
* @class      XLINUXFILE
* @brief      eXtended LINUX File class
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @copyright  Copyright(c) 2008 - 2016 GEN Group.
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
*---------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <unistd.h>
#include <locale.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#include "XPath.h"
#include "XString.h"

#include "XTrace.h"

#include "Cipher.h"

#include "XLINUXFactory.h"

#include "XLINUXFile.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLINUXFILE::XLINUXFILE()
* @brief      Constructor
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XLINUXFILE::XLINUXFILE(): XFILE()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLINUXFILE::~XLINUXFILE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XLINUXFILE::~XLINUXFILE()
{
  if(isopen) this->Close();

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXFILE::Exist(XCHAR* xpath)
* @brief      Check if Exist file
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  xpath : path to file
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLINUXFILE::Exist(XCHAR* xpath)
{
  bool status = Open(xpath, true);
  if(status) Close();

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXFILE::Open(XCHAR* xpath, bool isreadonly)
* @brief      Open file
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  xpath : path to file
* @param[in]  isreadonly : is open with read only
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLINUXFILE::Open(XCHAR* xpath, bool isreadonly)
{
  return ExtendedOpen(xpath, (isreadonly)? __L("rb") : __L("r+b"));
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXFILE::Create(XCHAR* xpath)
* @brief      Create file
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  xpath : path to file
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLINUXFILE::Create(XCHAR* xpath)
{
  return ExtendedOpen(xpath, __L("w+b"));
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXFILE::SetSize(XDWORD size)
* @brief      Set Size of File
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  size : new size
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLINUXFILE::SetSize(XQWORD size)
{
  if(!isopen)       return false;
  if(!filehandle)   return false;

  if(ftruncate(fileno(filehandle) , size)) return false;

  ActualizeSize();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXFILE::GetPosition(XDWORD& position)
* @brief      Get Position in file
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[out] position : position of the file
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLINUXFILE::GetPosition(XQWORD& position)
{
  if(!isopen)     return false;
  if(!filehandle) return false;

  position = ftell(filehandle);
  if(position == -1) return false;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXFILE::SetPosition(XDWORD position)
* @brief      Set Position of file
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  position : new position of file
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLINUXFILE::SetPosition(XQWORD position)
{
  if(!isopen)     return false;
  if(!filehandle) return false;

  XDWORD _position = position;
  bool   status;

  if(_position == XFILE_SEEKEND) _position = cachesize;
  if(_position > cachesize) return false;

  status = fseek(filehandle, _position, SEEK_SET)?false:true;

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXFILE::Read(XBYTE* buffer, XDWORD size, CIPHER* cipher)
* @brief      Read buffer of file
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  buffer : buffer where to read
* @param[in]  size : size to read
* @param[in]  cipher : cipher class uncipher buffer
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLINUXFILE::Read(XBYTE* buffer, XDWORD size, CIPHER* cipher)
{
  if(!isopen)       return false;
  if(!filehandle)   return false;

  int _size;

  _size=(int)fread((void *)buffer,1,(size_t)size, filehandle);
  if(_size!=size)  return false;

  if(cipher) cipher->Uncipher(buffer,_size);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXFILE::Read(XBYTE* buffer, XDWORD* size, CIPHER* cipher)
* @brief      Read buffer of file
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  buffer : buffer where to read
* @param[out] size : size to read
* @param[in]  cipher : cipher class uncipher buffer
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLINUXFILE::Read(XBYTE* buffer, XDWORD* size, CIPHER* cipher)
{
  if(!isopen)       return false;
  if(!filehandle)   return false;

   int   _size;
  bool status = true;

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
* @fn         bool XLINUXFILE::Write(XBYTE* buffer, XDWORD size, CIPHER* cipher)
* @brief      Write buffer to file
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  buffer : buffer where to read
* @param[in]  size : size to read
* @param[in]  cipher : cipher class to cipher buffer
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLINUXFILE::Write(XBYTE* buffer, XDWORD size, CIPHER* cipher)
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
* @fn         bool XLINUXFILE::Flush()
* @brief      Flush
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLINUXFILE::Flush()
{
  if(!isopen)       return false;
  if(!filehandle)   return false;

  fflush(filehandle);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXFILE::Close()
* @brief      Close
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLINUXFILE::Close()
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
      isopen     = false;
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXFILE::Erase(XCHAR* xpath,bool overwrite)
* @brief      Erase
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  xpath : path of file
* @param[in]  overwrite : overwrite file
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLINUXFILE::Erase(XCHAR* xpath,bool overwrite)
{
  if(Exist(xpath)!=true)  return false;

  bool status = true;

  if(overwrite) status = OverwriteContent(xpath);

  XBUFFER _xpathbuffer;
  XPATH   _xpath;

  _xpath = xpath;

  _xpath.ConvertToUTF8(_xpathbuffer);

  if(unlink((char*)_xpathbuffer.Get())==-1) status=false;

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXFILE::Rename(XCHAR* xpathold, XCHAR* xpathnew)
* @brief      Rename file
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  xpathold : xpath origin
* @param[in]  xpathnew : new xpath
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLINUXFILE::Rename(XCHAR* xpathold, XCHAR* xpathnew)
{
  XBUFFER _xpathbufferold;
  XBUFFER _xpathbuffernew;
  XPATH   _xpathold;
  XPATH   _xpathnew;

  _xpathold = xpathold;
  _xpathnew = xpathnew;

  _xpathold.ConvertToUTF8(_xpathbufferold);
  _xpathnew.ConvertToUTF8(_xpathbuffernew);

  // need to manually reset errno as no call is going to do it
  errno = 0;
  int status  = rename((char*)_xpathbufferold.Get(), (char*)_xpathbuffernew.Get());
  if (status != 0)
    {
      XSTRING err;
      err.Set(strerror(errno));
     XTRACE_PRINTCOLOR(4,__L("Error renaming file %s -> %s : %s"),xpathold,xpathnew,err.Get());
    }

  return (!status)?true:false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         FILE* XLINUXFILE::CreateStructHandle()
* @brief      CreateStructHandle
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     FILE* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
FILE* XLINUXFILE::CreateStructHandle()
{ 
  return filehandle;    
};



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXFILE::DeleteStructHandle()
* @brief      DeleteStructHandle
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLINUXFILE::DeleteStructHandle()
{
  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XLINUXFILE::ChangeAttributes(XCHAR* attributes)
* @brief      ChangeAttributes
* @ingroup    PLATFORM_LINUX
*
* @author     Imanol Celaya Ruiz de Alegria
* @date       01/03/2016 12:00
*
* @param[in]  attributes : new atributes
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XLINUXFILE::ChangeAttributes(XCHAR* attributes)
{
  XSTRING mode;
  mode.Set(attributes);
  XSTRING_CREATEOEM(mode, charOEM0)
  int i = strtol(charOEM0, 0, 8);
  XSTRING_DELETEOEM(mode, charOEM0)

  XSTRING str(xpathnamefile.Get());
  XSTRING_CREATEOEM(str, charOEM)
  chmod(charOEM, i);
  XSTRING_DELETEOEM(str, charOEM)
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXFILE::ActualizeSize()
* @brief      Actualize Size
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLINUXFILE::ActualizeSize()
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
* @fn         void XLINUXFILE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void XLINUXFILE::Clean()
{
  filehandle  = NULL;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXFILE::ExtendedOpen(XCHAR* xpath, XCHAR* mode)
* @brief      Extended Open
* @note       INTERN
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  xpath : xpath of file
* @param[in]  mode : mode attributes to open
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLINUXFILE::ExtendedOpen(XCHAR* xpath, XCHAR* mode)
{
  if(isopen) Close();

  this->xpathnamefile = xpath;

  XPATH   _xpath;
  XSTRING _mode;
  XBUFFER _xpathbuffer;
  XBUFFER _modebuffer;
  bool    status = false;

  _xpath  = xpath;
  _mode   = mode;

  _xpath.ConvertToUTF8(_xpathbuffer); _xpathbuffer.Add((XDWORD)0);
  _mode.ConvertToUTF8(_modebuffer);   _modebuffer.Add((XDWORD)0);

  filehandle = fopen((char*)_xpathbuffer.Get(), (char*)_modebuffer.Get());
  if(filehandle)
    {
      isopen = true;

      ActualizeSize();

      status = true;

      #ifdef XTRACE_ACTIVE
      XFileOpenList.Add(this);
      #endif
    }

  return status;
}




