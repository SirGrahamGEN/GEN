/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XFile.cpp
* 
* @class      XFILE
* @brief      eXtended Utils File class
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
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XFile.h"

#include <string.h>

#include "XFactory.h"
#include "XTrace.h"

#include "Cipher.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#ifdef XTRACE_ACTIVE
XFILEOPENLIST XFileOpenList;
#endif

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


#pragma region CLASS_XFILE


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILE::XFILE()
* @brief      Constructor
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILE::XFILE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILE::~XFILE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILE::~XFILE()

{
  if(isopen) this->Close();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XFILE::GetSize()
* @brief      GetSize
* @ingroup    XUTILS
*
* @return     XQWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XQWORD XFILE::GetSize()
{
  return cachesize;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILE::Write(XBUFFER &xbuffer)
* @brief      Write
* @ingroup    XUTILS
*
* @param[in]  &xbuffer :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILE::Write(XBUFFER &xbuffer)
{
  return Write(xbuffer.Get(), xbuffer.GetSize());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILE::Close()
* @brief      Close
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILE::Close()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILE::Exist(XPATH& xpath)
* @brief      Exist
* @ingroup    XUTILS
*
* @param[in]  xpath :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILE::Exist(XPATH& xpath)
{
  return Exist(xpath.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILE::Open(XPATH& xpath,bool readonly)
* @brief      Open
* @ingroup    XUTILS
*
* @param[in]  xpath :
* @param[in]  readonly :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILE::Open(XPATH& xpath,bool readonly)
{
  return Open(xpath.Get(), readonly);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILE::Create(XPATH& xpath)
* @brief      Create
* @ingroup    XUTILS
*
* @param[in]  xpath :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILE::Create(XPATH& xpath)
{
  return Create(xpath.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILE::Erase(XPATH& xpath,bool overwrite)
* @brief      Erase
* @ingroup    XUTILS
*
* @param[in]  xpath :
* @param[in]  overwrite :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILE::Erase(XPATH& xpath,bool overwrite)
{
  return Erase(xpath.Get(), overwrite);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILE::Rename(XPATH& xpathold,XPATH& xpathnew)
* @brief      Rename
* @ingroup    XUTILS
*
* @param[in]  xpathold :
* @param[in]  xpathnew :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILE::Rename(XPATH& xpathold,XPATH& xpathnew)
{
  return Rename(xpathold.Get(), xpathnew.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILE::Rename(XCHAR* xpathold,XPATH& xpathnew)
* @brief      Rename
* @ingroup    XUTILS
*
* @param[in]  xpathold :
* @param[in]  xpathnew :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILE::Rename(XCHAR* xpathold,XPATH& xpathnew)
{
  return Rename(xpathold, xpathnew.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILE::Rename(XPATH& xpathold,XCHAR* xpathnew)
* @brief      Rename
* @ingroup    XUTILS
*
* @param[in]  xpathold :
* @param[in]  xpathnew :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILE::Rename(XPATH& xpathold,XCHAR* xpathnew)
{
  return Rename(xpathold.Get(), xpathnew);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILE::IsOpen()
* @brief      IsOpen
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILE::IsOpen()
{
  return isopen;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILE::IsReadOnly()
* @brief      IsReadOnly
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILE::IsReadOnly()
{
  return isreadonly;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XCHAR* XFILE::GetPathNameFile()
* @brief      GetPathNameFile
* @ingroup    XUTILS
*
* @return     XCHAR* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR* XFILE::GetPathNameFile()
{
  return xpathnamefile.Get();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILE::EraseBlock(XQWORD size)
* @brief      EraseBlock
* @ingroup    XUTILS
*
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILE::EraseBlock(XQWORD size)
{
  XBYTE* tbuffer;
  XQWORD position;
  XQWORD sizetomove;
  XDWORD nblocks;
  XDWORD rest;
  bool   status = true;

  if(!isopen) return false;

  if(!GetPosition(position)) return false;

  sizetomove = GetSize() - position - size;

  tbuffer= new XBYTE [XFILE_MAXBUFFER];
  if(!tbuffer) return false;

  nblocks = (XDWORD)(sizetomove / XFILE_MAXBUFFER);
  rest    = (XDWORD)(sizetomove % XFILE_MAXBUFFER);

  for(XDWORD c=0; c<nblocks; c++)
    {
      SetPosition(position + size + ((XQWORD)c * XFILE_MAXBUFFER));
      if(Read(tbuffer, XFILE_MAXBUFFER))
        {
          SetPosition(position + ((XQWORD)c * XFILE_MAXBUFFER));
          Write(tbuffer, XFILE_MAXBUFFER);
        }
    }

  SetPosition(position + size +((XQWORD)nblocks * XFILE_MAXBUFFER));
  if(Read(tbuffer, rest))
    {
      SetPosition(position + ((XQWORD)nblocks * XFILE_MAXBUFFER));
      Write(tbuffer, rest);
    }

  SetSize(GetSize() - size);

  delete [] tbuffer;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFILE::InsertBlock(XBYTE* buffer, XDWORD size)
* @brief      InsertBlock
* @ingroup    XUTILS
*
* @param[in]  buffer :
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILE::InsertBlock(XBYTE* buffer, XDWORD size)
{
  XBYTE*  movebuffer;
  XQWORD  origin;
  XQWORD  position;

  bool    status = true;

  if(!isopen) return false;

  if(GetPosition(position)!=true) return false;

  origin = position;

  movebuffer= new XBYTE [XFILE_MAXBUFFER];
  if(!movebuffer) return false;

  ActualizeSize();

  XQWORD sizefile      = GetSize();
  XQWORD sizetomove    = sizefile-position;
  XDWORD nblockstomove = (XDWORD)(sizetomove / XFILE_MAXBUFFER);
  XDWORD resttomove    = (XDWORD)(sizetomove % XFILE_MAXBUFFER);
  XDWORD c;

  position = GetSize() - XFILE_MAXBUFFER;

  for(c=0; c<nblockstomove+1; c++)
    {
      XDWORD rb;

      if(c>=nblockstomove)
        {
          rb = resttomove;
          position =  origin;
        }
       else
        {
          rb = XFILE_MAXBUFFER;
        }

      SetPosition(position);
      Read(movebuffer, &rb);

      SetPosition(position+size);
      Write(movebuffer,rb);

      position -= XFILE_MAXBUFFER;
    }

  SetPosition(origin);
  Write(buffer,size);

  if(status==true) ActualizeSize();

  delete [] movebuffer;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILE::ChangeAttributes(XCHAR* attributes)
* @brief      ChangeAttributes
* @ingroup    XUTILS
*
* @param[in]  attributes :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFILE::ChangeAttributes(XCHAR* attributes)
{

}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILE::OverwriteContent(XCHAR* xpath)
* @brief      OverwriteContent
* @ingroup    XUTILS
* 
* @param[in]  xpath : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILE::OverwriteContent(XCHAR* xpath)
{
  bool status=true;

  if(!Open(xpath,false)) return false;

  GetSize();

  XBYTE*      buffer;
  const int   sizeblock = 1024;
  int         block     = (XDWORD)(cachesize/sizeblock);
  int         mod       = (XDWORD)(cachesize%sizeblock);

  buffer = new XBYTE [sizeblock];
  if(!buffer) return false;

  memset(buffer,0,sizeblock);

  for(int c=0;c<block;c++)
    {
      if(Write(buffer,sizeblock)!=true)
        {
          status=false;
          break;
        }
    }

  if(status==true)
    {
      if(Write(buffer,mod)!=true)  status=false;
    }

  delete [] buffer;

  Close();

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFILE::Clean()
{
  isopen        = false;
  isreadonly    = false;
  cachesize     = 0;
}


#pragma endregion


#pragma region CLASS_XFILECONTAINER


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILECONTAINER::XFILECONTAINER()
* @brief      Constructor
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILECONTAINER::XFILECONTAINER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILECONTAINER::~XFILECONTAINER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILECONTAINER::~XFILECONTAINER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILECONTAINER::CreatePrimaryFile()
* @brief      CreatePrimaryFile
* @ingroup    XUTILS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECONTAINER::CreatePrimaryFile()
{
  GEN_XFACTORY_CREATE(file, Create_File())
  if(!file) return false;

  eraseprimaryfile = true;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILE* XFILECONTAINER::GetPrimaryFile()
* @brief      GetPrimaryFile
* @ingroup    XUTILS
* 
* @return     XFILE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XFILE* XFILECONTAINER::GetPrimaryFile()
{
  return file;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILECONTAINER::DeletePrimaryFile()
* @brief      DeletePrimaryFile
* @ingroup    XUTILS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILECONTAINER::DeletePrimaryFile()
{
  if(!file)  return false;

  if(!eraseprimaryfile) return false;

  GEN_XFACTORY.Delete_File(file);

  file = NULL;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILECONTAINER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFILECONTAINER::Clean()
{
  file              = NULL;
  eraseprimaryfile  = false;
}


#pragma endregion


#pragma region CLASS_XFILEOPENLIST


#ifdef XTRACE_ACTIVE


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILEOPENLIST::~XFILEOPENLIST()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
* 
* --------------------------------------------------------------------------------------------------------------------*/
XFILEOPENLIST::~XFILEOPENLIST()
{

}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILEOPENLIST::Add(XFILE* xfile)
* @brief      Add
* @ingroup    XUTILS
* 
* @param[in]  xfile : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEOPENLIST::Add(XFILE* xfile)
{
  filelist.Add(xfile);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILEOPENLIST::Del(XFILE* xfile)
* @brief      Del
* @ingroup    XUTILS
* 
* @param[in]  xfile : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEOPENLIST::Del(XFILE* xfile)
{
  if(filelist.IsEmpty()) return false;

  filelist.Delete(xfile);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILEOPENLIST::CloseAll()
* @brief      CloseAll
* @ingroup    XUTILS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEOPENLIST::CloseAll()
{
  if(filelist.IsEmpty()) return false;

  for(XDWORD c=0;c<filelist.GetSize();c++)
    {
      XFILE* xfile = (XFILE*)filelist.Get(c);

      if(xfile) xfile->Close();
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XFILEOPENLIST::DisplayAll()
* @brief      DisplayAll
* @ingroup    XUTILS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XFILEOPENLIST::DisplayAll()
{
  XDWORD nfilesopen = filelist.GetSize();

  if(!nfilesopen)
    {
    }
   else
    {
      XTRACE_PRINTHEADER(__L("NOT ALL FILES ARE CLOSED"));

      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLACK, __L("Number files not closed: %d"), nfilesopen);
      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLACK, __L("Path + File Name"), NULL);
      XTRACE_PRINT(__L(" "), NULL);

      for(XDWORD c=0; c<nfilesopen; c++)
        {
          XFILE* xfile = (XFILE*)filelist.Get(c);

          if(xfile) XTRACE_PRINT(__L("%s")  , xfile->GetPathNameFile());
        }

      XTRACE_PRINTHEADER(NULL);
    }

  CloseAll();

  filelist.DeleteContents();
  filelist.DeleteAll();

  return true;
}


#pragma endregion


#pragma endregion


#endif

