/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XFileZIP.cpp
* 
* @class      XFILEZIP
* @brief      eXtended Utils ZIP file class
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

#include "XFileZIP.h"

#include "XFactory.h"
#include "XDateTime.h"
#include "XPath.h"
#include "XFileZIP_XEvent.h"

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


#pragma region CLASS_XFILECMPZIP


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILECMPZIP::XFILECMPZIP(bool compress, void* filehdl)
* @brief      Constructor of class
* @ingroup    XUTILS
*
* @param[in]  compress :
* @param[in]  filehdl :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILECMPZIP::XFILECMPZIP(bool compress, void* filehdl)
{
  Clean();

  this->filehdl  = filehdl;

  zipoper = compress;

  if(!zipoper)
    {
      unz_file_info64 info;
      char*           _name    = new char[_MAXPATH];
      char*           _comment = new char[_MAXPATH];

      if(_name && _comment)
        {

          int err = unzGetCurrentFileInfo64(filehdl, &info, _name, _MAXPATH,NULL, 0, _comment, _MAXSTR);
          if(err == UNZ_OK)
            {
              name           = _name;
              comment        = _comment;

              method         = info.compression_method;

              uncompresssize = info.uncompressed_size;
              compresssize   = info.compressed_size;

              CRC32          = info.crc;

              on = true;
            }
        }

      delete [] _name;
      delete [] _comment;

    } else  on = true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILECMPZIP::~XFILECMPZIP()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILECMPZIP::~XFILECMPZIP()
{
  if(open) Close();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECMPZIP::Open(XSTRING& password)
* @brief      Open
* @ingroup    XUTILS
*
* @param[in]  password :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECMPZIP::Open(XSTRING& password)
{
  int err;

  if(!on) return false;

  if(!zipoper)
    {
       if(!SelectCurrenFile()) return false;

       if(!password.IsEmpty())
         {
           
           XBUFFER charstr;
           
           password.ConvertToASCII(charstr); 
           err = unzOpenCurrentFilePassword((unzFile)filehdl, charstr.GetPtrChar());           
         }
        else err = unzOpenCurrentFile((unzFile)filehdl);

       if(err!=UNZ_OK) return false;
    }
   else return false;

  open = true;

  return open;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECMPZIP::Create(XDWORD crcfile,zip_fileinfo* zfinfo,XCHAR* password)
* @brief      Create
* @ingroup    XUTILS
*
* @param[in]  crcfile :
* @param[in]  zfinfo :
* @param[in]  password :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECMPZIP::Create(XDWORD crcfile, zip_fileinfo* zfinfo, XCHAR* password)
{
  int err;
  int opt_compress_level = Z_DEFAULT_COMPRESSION;

  if(!on) return false;

  XBUFFER namestr;  
  XSTRING _password;
  XBUFFER passwordstr; 

  _password = password;
  
  name.ConvertToASCII(namestr); 
  _password.ConvertToASCII(passwordstr);
  
  err = zipOpenNewFileInZip3(filehdl, namestr.GetPtrChar()
                                    , zfinfo
                                    , NULL,0,NULL,0,NULL /* comment*/
                                    ,(opt_compress_level != 0) ? Z_DEFLATED : 0
                                    , opt_compress_level,0
                                    , -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY
                                    , password?passwordstr.GetPtrChar():NULL
                                    , crcfile);

 
  if(err!=ZIP_OK) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECMPZIP::IsActive()
* @brief      Is active
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECMPZIP::IsActive()
{
  return on;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XCHAR* XFILECMPZIP::GetName()
* @brief      Get name
* @ingroup    XUTILS
*
* @return     XCHAR* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR* XFILECMPZIP::GetName()
{
  if(!on) return NULL;

  return name.Get();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILECMPZIP::SetName(XSTRING& name)
* @brief      Set name
* @ingroup    XUTILS
*
* @param[in]  name :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFILECMPZIP::SetName(XSTRING& name)
{
  if(name.IsEmpty()) return;

  this->name = name;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECMPZIP::IsDirectory()
* @brief      Is directory
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECMPZIP::IsDirectory()
{
  XPATH xpath;

  xpath = name.Get();

  if((xpath.Slash_HaveAtLast()) && (!Size()) && (!UnCompressSize())) return true;

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XQWORD XFILECMPZIP::Size()
* @brief      Size
* @ingroup    XUTILS
*
* @return     XQWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XQWORD XFILECMPZIP::Size()
{
  if(!on) return 0;

  return compresssize;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XQWORD XFILECMPZIP::UnCompressSize()
* @brief      Un compress size
* @ingroup    XUTILS
*
* @return     XQWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XQWORD XFILECMPZIP::UnCompressSize()
{
  if(!on) return 0;

  return uncompresssize;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XFILECMPZIP::GetCRC32()
* @brief      Get CRC32
* @ingroup    XUTILS
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XFILECMPZIP::GetCRC32()
{
  if(!on) return 0;

  return CRC32;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECMPZIP::GetSeek(int*position)
* @brief      Get seek
* @ingroup    XUTILS
*
* @param[in]  position :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECMPZIP::GetSeek(int* position)
{
  if(!on) return false;

  if(!zipoper)
    {
      if(!open) return false;

      (*position)=unztell(filehdl);

    } else return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECMPZIP::Read(XBYTE* buffer,XDWORD size)
* @brief      Read
* @ingroup    XUTILS
*
* @param[in]  buffer :
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECMPZIP::Read(XBYTE* buffer, XDWORD size)
{
  if(!on)     return false;
  if(zipoper) return false;

  if(unzReadCurrentFile(filehdl,buffer,size) != (int)size) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECMPZIP::Read(XBYTE* buffer, int* size)
* @brief      Read
* @ingroup    XUTILS
*
* @param[in]  buffer :
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECMPZIP::Read(XBYTE* buffer, int* size)
{
  int  _size;
  bool status = true;

  if(!on)     return false;
  if(zipoper) return false;

  _size=unzReadCurrentFile(filehdl,buffer,(*size));
  if(_size!=(*size))  status=false;
  (*size)=_size;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECMPZIP::Write(XBYTE* buffer, XDWORD size)
* @brief      Write
* @ingroup    XUTILS
*
* @param[in]  buffer :
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECMPZIP::Write(XBYTE* buffer, XDWORD size)
{
  if(!on)      return false;
  if(!zipoper) return false;

  if(zipWriteInFileInZip(filehdl,buffer,size)!=ZIP_OK) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECMPZIP::IsEOF()
* @brief      Is EOF
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECMPZIP::IsEOF()
{
  if(zipoper) return false;

  if(unzeof(filehdl)) return true;

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECMPZIP::Close()
* @brief      Close
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECMPZIP::Close()
{
  int err;

  if(!on) return false;

  if(!zipoper)
    {
       if(!SelectCurrenFile()) return false;

       err=unzCloseCurrentFile(filehdl);
       if(err!=UNZ_OK) return false;
    }
   else
    {
      err=zipCloseFileInZip(filehdl);
      if(err!=ZIP_OK) return false;
    }

  open =false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILECMPZIP::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFILECMPZIP::Clean()
{
  filehdl         = NULL;

  on              = false;
  zipoper         = false;

  method          = 0;

  uncompresssize  = 0;
  compresssize    = 0;

  CRC32           = 0;

  open            = false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILECMPZIP::SelectCurrenFile()
* @brief      Select curren file
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECMPZIP::SelectCurrenFile()
{
  int err;
  
  XBUFFER charstr;
  
  name.ConvertToASCII(charstr);  
  err=unzLocateFile((unzFile)filehdl, charstr.GetPtrChar(), 0);
  if(err!=UNZ_OK) return false;
  
  return true;
}


#pragma endregion


#pragma region CLASS_XFILEZIP


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEZIP::XFILEZIP(XDWORD maxsizebuffer)
* @brief      Constructor of class
* @ingroup    XUTILS
*
* @param[in]  maxsizebuffer :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEZIP::XFILEZIP(XDWORD maxsizebuffer)
{
  Clean();

  this->maxsizebuffer = maxsizebuffer;

  GEN_XFACTORY_CREATE(xdatetime, CreateDateTime())
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEZIP::~XFILEZIP()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEZIP::~XFILEZIP()
{
  Close();

  GEN_XFACTORY.DeleteDateTime(xdatetime);

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XFILEZIP::GetMaxSizeBuffer()
* @brief      Get max size buffer
* @ingroup    XUTILS
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XFILEZIP::GetMaxSizeBuffer()
{
  return maxsizebuffer;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILEZIP::SetMaxSizeBuffer(XDWORD maxsizebuffer)
* @brief      Set max size buffer
* @ingroup    XUTILS
*
* @param[in]  maxsizebuffer : 
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFILEZIP::SetMaxSizeBuffer(XDWORD maxsizebuffer)
{
  this->maxsizebuffer = maxsizebuffer;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEZIP::Open(XPATH& xpath)
* @brief      Open
* @ingroup    XUTILS
*
* @param[in]  xpath :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEZIP::Open(XPATH& xpath)
{
  
  XBUFFER charstr;
  
  xpath.ConvertToASCII(charstr);
   
  filehdl=zipOpen(charstr.GetPtrChar(), APPEND_STATUS_ADDINZIP);
  if(!filehdl)  filehdl = zipOpen(charstr.GetPtrChar(), APPEND_STATUS_CREATE);
  
  lastoperationpercent  = filehdl ? 100.0f : 0.0f;
  lasterror             = filehdl ? XFILEZIP_ERROR_NONE : XFILEZIP_ERROR_ZIP_OPEN;

  XFILEZIP_XEVENT xevent(this, XFILEZIP_XEVENT_TYPE_ZIP_OPEN);

  xevent.GetFileName()->Set(xpath.Get());
  xevent.SetFileCompress(NULL);
  xevent.SetError(lasterror);
  xevent.SetOperationPercent(lastoperationpercent);

  PostEvent(&xevent);

  if(!filehdl) return false;

  xpathzip = xpath;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILECMPZIP* XFILEZIP::CreateFileCmp(XPATH& xpath)
* @brief      Create file cmp
* @ingroup    XUTILS
*
* @param[in]  xpath :
*
* @return     XFILECMPZIP* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILECMPZIP* XFILEZIP::CreateFileCmp(XPATH& xpath)
{
  XFILECMPZIP* filecmp = new XFILECMPZIP(true,filehdl);
  if(filecmp) filecmp->SetName(xpath);

  return filecmp;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XFILEZIP::GetFileCRC(XFILE* xfile)
* @brief      Get file CRC
* @ingroup    XUTILS
*
* @param[in]  xfile :
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XFILEZIP::GetFileCRC(XFILE*  xfile)
{
  if(!xfile)           return 0;
  if(!xfile->IsOpen()) return 0;

  XBYTE*  buffer    = new XBYTE[maxsizebuffer];
  XDWORD  size;
  XDWORD  crcfile       = 0;

  if(!buffer) return 0;

  XQWORD position = 0;

  xfile->GetPosition(position);

  do{ size = maxsizebuffer;

      xfile->Read(buffer,&size);
      if(size) crcfile = crc32(crcfile,buffer,size);

    } while(size == maxsizebuffer);

  delete [] buffer;

  xfile->SetPosition(position);

  return crcfile;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEZIP::AddFile(XPATH& xpath, XPATH& xpathnew, XCHAR* password)
* @brief      Add file
* @ingroup    XUTILS
*
* @param[in]  xpath :
* @param[in]  xpathnew :
* @param[in]  password :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEZIP::AddFile(XPATH& xpath, XPATH& xpathnew, XCHAR* password)
{
  XFILECMPZIP* filecmp;
  XFILE*       xfile;
  bool         status    = false;

  GEN_XFACTORY_CREATE(xfile, Create_File())
  if(!xfile) return status;

  if(xfile->Open(xpath))
    {
      filecmp = CreateFileCmp((xpathnew.IsEmpty()?xpath:xpathnew));
      if(filecmp)
        {
          zip_fileinfo   zfinfo;
          XDWORD         crcfile = GetFileCRC(xfile);

          memset(&zfinfo,0,sizeof(zip_fileinfo));

          if(xdatetime) xdatetime->GetFileDateTime(xpath, &zfinfo.tmz_date, (XDWORD*)&zfinfo.dosDate);

          if(filecmp->Create(crcfile, &zfinfo, password))
            {
              XBYTE*          buffer        = new XBYTE[maxsizebuffer];
              XDWORD          size          = 0;
              XQWORD          totalsize     = 0;
              XQWORD          totalsizefile = xfile->GetSize();
              XFILEZIP_XEVENT xevent(this, XFILEZIP_XEVENT_TYPE_UNZIP_OPEN);

              if(buffer)
                {
                  do{ size = maxsizebuffer;

                      xfile->Read(buffer, &size);
                      if(size)
                        {
                          status = filecmp->Write(buffer, size);
                          if(status)
                            {
                               totalsize += size;
                               lastoperationpercent = ((float)(totalsize*100) / totalsizefile);
                            }
                        }

                      lasterror = status ? XFILEZIP_ERROR_NONE : XFILEZIP_ERROR_ZIP_ADDFILE;

                      xevent.GetFileName()->Set(xpathzip.Get());
                      xevent.SetFileCompress(filecmp);
                      xevent.SetError(lasterror);
                      xevent.SetOperationPercent(lastoperationpercent);

                      PostEvent(&xevent);

                      if(!status) break;

                    } while(size == maxsizebuffer);
                }

              delete [] buffer;

              filecmp->Close();
            }

          delete filecmp;
        }

      xfile->Close();
    }

  GEN_XFACTORY.Delete_File(xfile);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEZIP::Close()
* @brief      Close
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEZIP::Close()
{
  if(!filehdl) return false;

  bool status = (zipClose(filehdl ,NULL) == ZIP_OK)?true:false;

  lastoperationpercent  = status ? 100.0f : 0.0f;
  lasterror             = status ? XFILEZIP_ERROR_NONE : XFILEZIP_ERROR_ZIP_CLOSE;

  XFILEZIP_XEVENT xevent(this, XFILEZIP_XEVENT_TYPE_ZIP_CLOSE);

  xevent.GetFileName()->Set(xpathzip.Get());
  xevent.SetFileCompress(NULL);
  xevent.SetError(lasterror);
  xevent.SetOperationPercent(lastoperationpercent);

  PostEvent(&xevent);

  filehdl = NULL;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         float XFILEZIP::GetLastOperationPercent()
* @brief      Get last operation percent
* @ingroup    XUTILS
* 
* @return     float : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
float XFILEZIP::GetLastOperationPercent()
{
  return lastoperationpercent;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEZIP_ERROR XFILEZIP::GetLastError()
* @brief      Get last error
* @ingroup    XUTILS
*
* @return     XFILEZIP_ERROR :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEZIP_ERROR XFILEZIP::GetLastError()
{
  return lasterror;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILEZIP::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFILEZIP::Clean()
{
  xdatetime             = NULL;
  filehdl               = NULL;
  maxsizebuffer         = 0;

  lastoperationpercent  = 0.0f;
  lasterror             = XFILEZIP_ERROR_NONE;
}


#pragma endregion


#pragma region CLASS_XFILEUNZIP


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEUNZIP::XFILEUNZIP(XDWORD maxsizebuffer)
* @brief      Constructor of class
* @ingroup    XUTILS
*
* @param[in]  maxsizebuffer :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEUNZIP::XFILEUNZIP(XDWORD maxsizebuffer)
{
  Clean();

  this->maxsizebuffer = maxsizebuffer;

  RegisterEvent(XFILEZIP_XEVENT_TYPE_UNZIP_OPEN);
  RegisterEvent(XFILEZIP_XEVENT_TYPE_UNZIP_EXTRACTFILE);
  RegisterEvent(XFILEZIP_XEVENT_TYPE_UNZIP_CLOSE);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEUNZIP::~XFILEUNZIP()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEUNZIP::~XFILEUNZIP()
{
  Close();

  DeRegisterEvent(XFILEZIP_XEVENT_TYPE_UNZIP_OPEN);
  DeRegisterEvent(XFILEZIP_XEVENT_TYPE_UNZIP_EXTRACTFILE);
  DeRegisterEvent(XFILEZIP_XEVENT_TYPE_UNZIP_CLOSE);

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XFILEUNZIP::GetMaxSizeBuffer()
* @brief      Get max size buffer
* @ingroup    XUTILS
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XFILEUNZIP::GetMaxSizeBuffer()
{
  return maxsizebuffer;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILEUNZIP::SetMaxSizeBuffer(XDWORD maxsizebuffer)
* @brief      Set max size buffer
* @ingroup    XUTILS
*
* @param[in]  maxsizebuffer : 
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFILEUNZIP::SetMaxSizeBuffer(XDWORD maxsizebuffer)
{
  this->maxsizebuffer = maxsizebuffer;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEUNZIP::Open(XPATH& xpath)
* @brief      Open
* @ingroup    XUTILS
*
* @param[in]  xpath :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEUNZIP::Open(XPATH& xpath)
{
  if(xpath.IsEmpty()) return false;

  XBUFFER charstr;
  
  xpath.ConvertToASCII(charstr);
  filehdl = unzOpen(charstr.GetPtrChar());
 
  lastoperationpercent  = filehdl ? 100.0f : 0.0f;
  lasterror             = filehdl ? XFILEZIP_ERROR_NONE : XFILEZIP_ERROR_UNZIP_OPEN;

  XFILEZIP_XEVENT xevent(this, XFILEZIP_XEVENT_TYPE_UNZIP_OPEN);

  xevent.GetFileName()->Set(xpath.Get());
  xevent.SetFileCompress(NULL);
  xevent.SetError(lasterror);
  xevent.SetOperationPercent(lastoperationpercent);

  PostEvent(&xevent);

  if(!filehdl) return false;

  xpathunzip = xpath;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XFILEUNZIP::GetNFiles()
* @brief      Get N files
* @ingroup    XUTILS
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XFILEUNZIP::GetNFiles()
{
  int nfiles = 0;

  while(1)
    {
      XFILECMPZIP* filecmp = GotoFile(nfiles);
      if(!filecmp) break;

      nfiles++;

      delete filecmp;
    }

  return nfiles;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILECMPZIP* XFILEUNZIP::GotoFile(bool first)
* @brief      Goto file
* @ingroup    XUTILS
*
* @param[in]  first :
*
* @return     XFILECMPZIP* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILECMPZIP* XFILEUNZIP::GotoFile(bool first)
{
  int err;

  err =first?unzGoToFirstFile(filehdl):unzGoToNextFile(filehdl);
  if(err!=UNZ_OK) return NULL;

  return CreateCurrentFile();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILECMPZIP* XFILEUNZIP::GotoFile(XPATH& xpath)
* @brief      Goto file
* @ingroup    XUTILS
*
* @param[in]  xpath :
*
* @return     XFILECMPZIP* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILECMPZIP* XFILEUNZIP::GotoFile(XPATH& xpath)
{ 
  XBUFFER charstr; 
  int     err;
  
  xpath.ConvertToASCII(charstr); 
  err=unzLocateFile(filehdl, charstr.GetPtrChar(), 0);  
  if(err!=UNZ_OK) return NULL;

  return CreateCurrentFile();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILECMPZIP* XFILEUNZIP::GotoFile(int index)
* @brief      Goto file
* @ingroup    XUTILS
*
* @param[in]  index :
*
* @return     XFILECMPZIP* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILECMPZIP* XFILEUNZIP::GotoFile(int index)
{
  XFILECMPZIP* filecmp = GotoFile(true);

  int c=0;
  do{
      if(index==c) break;

      delete filecmp;

      c++;
      filecmp = GotoFile(false);

    } while(filecmp);

  return filecmp;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEUNZIP::DelFile(int index, XCHAR* password)
* @brief      Del file
* @ingroup    XUTILS
*
* @param[in]  index :
* @param[in]  password :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEUNZIP::DelFile(int index, XCHAR* password)
{
  XPATH     xpathorigin;
  XPATH     xpathtarget;
  bool      status = true;

  XFILE* GEN_XFACTORY_CREATE(xfile, Create_File())
  if(!xfile) return false;

  XFILEZIP* filezip  = new XFILEZIP();
  if(!filezip)
    {
      GEN_XFACTORY.Delete_File(xfile);
      return false;
    }

  xpathorigin  = xpathunzip;
  xpathorigin.SetOnlyDriveAndPath();

  xpathtarget = xpathunzip;
  xpathtarget.AddToNameFile(true, __L("#TEMPO#_"));

  if(!filezip->Open(xpathtarget))
    {
      delete filezip;
      GEN_XFACTORY.Delete_File(xfile);

      return false;
    }

  int _index =0;

  while(1)
    {
      if(index != _index)
        {
          XPATH           xpathuncmpfile;
          XPATH           cmpfilename;

          XFILECMPZIP* filecmp = GotoFile(_index);
          if(!filecmp) break;

          cmpfilename = filecmp->GetName();
          delete filecmp;
          filecmp = NULL;

          xpathuncmpfile = cmpfilename;
          xpathuncmpfile.AddToNameFile(true, __L("#TEMPO#_"));
          xpathuncmpfile.DeleteCharacter(__C('/'));

          if(DecompressFile(_index , xpathorigin, xpathuncmpfile.Get(), password))
            {
              XPATH xpathtozip;

              xpathtozip = xpathorigin;
              xpathtozip.Slash_Add();
              xpathtozip += xpathuncmpfile;

              if(filezip->AddFile(xpathtozip, cmpfilename, password))
                {
                  if(xfile) xfile->Erase(xpathtozip);
                }
               else status = false;
            }
           else status = false;

          if(!status) break;
        }

      _index++;
    }

  lastoperationpercent = status ? 100.0f : 0.0f;
  lasterror            = status ? XFILEZIP_ERROR_NONE : XFILEZIP_ERROR_UNZIP_DELETEFILECMP;

  XFILECMPZIP*    filecmp = GotoFile(index);
  XFILEZIP_XEVENT xevent(this, XFILEZIP_XEVENT_TYPE_UNZIP_DELFILE);

  xevent.GetFileName()->Set(xpathunzip.Get());
  xevent.SetFileCompress(filecmp);
  xevent.SetOperationPercent(lastoperationpercent);
  xevent.SetError(lasterror);

  PostEvent(&xevent);

  filezip->Close();

  delete filezip;

  Close();

  if(status)
    {
      xpathorigin  = xpathunzip;
      if(xfile)
        {
          status = xfile->Erase(xpathorigin);
          if(status) status = xfile->Rename(xpathtarget, xpathorigin);
        }
    }

  if(xfile) GEN_XFACTORY.Delete_File(xfile);

  xpathorigin  = xpathunzip;
  return Open(xpathorigin);

}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEUNZIP::DecompressFile(int sourceindex ,XPATH& xpathtarget, XCHAR* nametarget, XCHAR* password)
* @brief      Decompress file
* @ingroup    XUTILS
*
* @param[in]  sourceindex :
* @param[in]  xpathtarget :
* @param[in]  nametarget :
* @param[in]  password :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEUNZIP::DecompressFile(int sourceindex ,XPATH& xpathtarget, XCHAR* nametarget, XCHAR* password)
{
  XFILECMPZIP* filecmp = GotoFile(true);

  int c=0;
  do{ if(sourceindex==c) break;

      delete filecmp;

      c++;
      filecmp = GotoFile(false);

    } while(filecmp);

  if(!filecmp) return false;

  bool status = DecompressFile(filecmp,xpathtarget,nametarget,password);

  delete filecmp;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEUNZIP::DecompressFile(XSTRING& namesource,XPATH& xpathtarget,XCHAR* nametarget, XCHAR* password)
* @brief      Decompress file
* @ingroup    XUTILS
*
* @param[in]  namesource :
* @param[in]  xpathtarget :
* @param[in]  nametarget :
* @param[in]  password :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEUNZIP::DecompressFile(XSTRING& namesource,XPATH& xpathtarget,XCHAR* nametarget, XCHAR* password)
{
  XPATH xpath(namesource);

  XFILECMPZIP* filecmp = GotoFile(xpath);
  if(!filecmp) return false;

  bool status = DecompressFile(filecmp,xpathtarget,nametarget,password);

  delete filecmp;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEUNZIP::DecompressFile(XFILECMPZIP* filecmp,XPATH& xpathtarget,XCHAR* nametarget,XCHAR* password)
* @brief      Decompress file
* @ingroup    XUTILS
*
* @param[in]  filecmp :
* @param[in]  xpathtarget :
* @param[in]  nametarget :
* @param[in]  password :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEUNZIP::DecompressFile(XFILECMPZIP* filecmp, XPATH& xpathtarget, XCHAR* nametarget, XCHAR* password)
{
  bool status = false;

  if(!filecmp) return false;

  XPATH xpath;

  xpath = xpathtarget;

  if(!nametarget)
    {
      xpath += filecmp->GetName();
    }
   else
    {
      if(!nametarget[0])
        {
          xpath += filecmp->GetName();

        } else xpath += nametarget;
    }

  XSTRING _password(password);

  if(filecmp->Open(_password))
    {
      XFILE* GEN_XFACTORY_CREATE(xfile, Create_File())
      if(xfile)
        {
          if(xfile->Create(xpath))
            {
              XBYTE* buffer= new XBYTE[maxsizebuffer];
              if(buffer)
                {
                  XQWORD totalbytesread = 0;
                  int    bytesread      = 0;

                  do {  XFILEZIP_XEVENT xevent(this, XFILEZIP_XEVENT_TYPE_UNZIP_EXTRACTFILE);

                        xevent.GetFileName()->Set(xpathunzip.Get());
                        xevent.SetFileCompress(filecmp);

                        bytesread = maxsizebuffer;
                        memset(buffer, 0, maxsizebuffer);

                        filecmp->Read(buffer, &bytesread);
                        if(bytesread)
                          {
                            status = xfile->Write(buffer, bytesread);
                            if(status)
                              {
                                totalbytesread += bytesread;

                                lasterror            = XFILEZIP_ERROR_NONE;
                                lastoperationpercent = (float)(totalbytesread*100) / filecmp->UnCompressSize();

                                xevent.SetOperationPercent(lastoperationpercent);

                              } else lasterror = XFILEZIP_ERROR_UNZIP_EXTRACTFILEWRITE;

                           } else lasterror = XFILEZIP_ERROR_UNZIP_EXTRACTFILEREAD;


                        xevent.SetError(lasterror);

                        PostEvent(&xevent);

                        if(!status) break;

                     } while(bytesread == (int)maxsizebuffer);

                  delete [] buffer;

                  if(filecmp->UnCompressSize() != xfile->GetSize()) status = false;
                }

              xfile->Close();
            }

          delete xfile;

        }

      filecmp->Close();
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILEUNZIP::Close()
* @brief      Close
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEUNZIP::Close()
{
  if(!filehdl) return false;

  bool status = (unzClose(filehdl) == UNZ_OK) ? true : false;

  lastoperationpercent  = status ? 100.0f : 0.0f;
  lasterror             = XFILEZIP_ERROR_NONE;

  XFILEZIP_XEVENT xevent(this, XFILEZIP_XEVENT_TYPE_UNZIP_CLOSE);

  xevent.GetFileName()->Set(xpathunzip.Get());
  xevent.SetFileCompress(NULL);
  xevent.SetError(lasterror);
  xevent.SetOperationPercent(lastoperationpercent);

  PostEvent(&xevent);

  filehdl = NULL;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float XFILEUNZIP::GetLastOperationPercent()
* @brief      Get last operation percent
* @ingroup    XUTILS
*
* @return     float :
*
* --------------------------------------------------------------------------------------------------------------------*/
float XFILEUNZIP::GetLastOperationPercent()
{
  return lastoperationpercent;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEZIP_ERROR XFILEUNZIP::GetLastError()
* @brief      Get last error
* @ingroup    XUTILS
*
* @return     XFILEZIP_ERROR :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEZIP_ERROR XFILEUNZIP::GetLastError()
{
  return lasterror;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILECMPZIP* XFILEUNZIP::CreateCurrentFile()
* @brief      Create current file
* @ingroup    XUTILS
*
* @return     XFILECMPZIP* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILECMPZIP* XFILEUNZIP::CreateCurrentFile()
{
  XFILECMPZIP* filecmp;

  if(!filehdl) return NULL;

  filecmp = new XFILECMPZIP(false,(void*)filehdl);
  if(!filecmp) return NULL;

  if(!filecmp->IsActive()) return NULL;

  return filecmp;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILEUNZIP::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFILEUNZIP::Clean()
{
  filehdl               = NULL;
  maxsizebuffer         = 0;

  lastoperationpercent  = 0.0f;
  lasterror             = XFILEZIP_ERROR_NONE;
}


#pragma endregion


#pragma endregion

