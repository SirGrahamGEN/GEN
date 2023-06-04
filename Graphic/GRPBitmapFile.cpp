/**-------------------------------------------------------------------------------------------------------------------
*
* @file       GRPBitmapFile.cpp
*
* @class      GRPBITMAPFILE
* @brief      Graphic Bitmap File Class
* @ingroup    GRAPHIC
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

#include <string.h>

#include "XFactory.h"

#include "GRPProperties.h"
#include "GRPBitmap.h"
#include "GRPBitmapSequence.h"
#include "GRPBitmapFileJPG.h"
#include "GRPBitmapFilePNG.h"
#include "GRPBitmapFileBMP.h"
#include "GRPBitmapFileTGA.h"

#include "GRPBitmapFile.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPBITMAPFILEBASE::GRPBITMAPFILEBASE()
* @brief      Constructor
* @ingroup    GRAPHIC
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPBITMAPFILEBASE::GRPBITMAPFILEBASE(): XFILECONTAINER()
{
  Clean();

  GEN_XFACTORY_CREATE(file, Create_File())
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPBITMAPFILEBASE::~GRPBITMAPFILEBASE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    GRAPHIC
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPBITMAPFILEBASE::~GRPBITMAPFILEBASE()
{
  if(file) GEN_XFACTORY.Delete_File(file);

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPBITMAP* GRPBITMAPFILEBASE::CreateBitmapFromFile(XPATH& xpath, GRPPROPERTYMODE forcemode)
* @brief      CreateBitmapFromFile
* @ingroup    GRAPHIC
*
* @param[in]  xpath :
* @param[in]  forcemode :
*
* @return     GRPBITMAP* :
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPBITMAP* GRPBITMAPFILEBASE::CreateBitmapFromFile(XPATH& xpath, GRPPROPERTYMODE forcemode)
{
  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPBITMAP* GRPBITMAPFILEBASE::CreateBitmapFromBuffer(XBYTE* buffer, XDWORD size, GRPPROPERTYMODE forcemode);
* @brief      CreateBitmapFromBuffer
* @ingroup    GRAPHIC
*
* @param[in]  buffer :
* @param[in]  size :
* @param[in]  forcemode :
*
* @return     GRPBITMAP* :
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPBITMAP* GRPBITMAPFILEBASE::CreateBitmapFromBuffer(XBYTE* buffer, XDWORD size, GRPPROPERTYMODE forcemode)
{
  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPBITMAPFILEBASE::CreateFileFromBitmap(XPATH& xpath, GRPBITMAP* bitmap, int quality)
* @brief      CreateFileFromBitmap
* @ingroup    GRAPHIC
*
* @param[in]  xpath :
* @param[in]  bitmap :
* @param[in]  quality :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAPFILEBASE::CreateFileFromBitmap(XPATH& xpath, GRPBITMAP* bitmap, int quality)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE* GRPBITMAPFILEBASE::ReadImageBufferFromFile(XPATH& xpath)
* @brief      Read Image Buffer From File
* @ingroup    GRAPHIC
*
* @param[in]  xpath : path to the Graphic file
*
* @return     XBYTE* : Pointer to buffer
*
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE* GRPBITMAPFILEBASE::ReadImageBufferFromFile(XPATH& xpath)
{
  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPBITMAP* GRPBITMAPFILEBASE::ForceModeOfBitmap(GRPPROPERTYMODE forcemode, GRPBITMAP* bitmap)
* @brief      ForceModeOfBitmap
* @ingroup    GRAPHIC
*
* @param[in]  forcemode :
* @param[in]  bitmap :
*
* @return     GRPBITMAP* :
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPBITMAP* GRPBITMAPFILEBASE::ForceModeOfBitmap(GRPPROPERTYMODE forcemode, GRPBITMAP* bitmap)
{
  GRPBITMAP* newbitmap = bitmap;
  if(!newbitmap) return NULL;

  if(forcemode == GRPPROPERTYMODE_XX_UNKNOWN) return bitmap;
  if(forcemode == bitmap->GetMode())          return bitmap;

  newbitmap = bitmap->ConvertToMode(forcemode);
  if(!newbitmap) return bitmap;

  delete bitmap;

  return newbitmap;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPBITMAPFILEBASE::Open(XPATH& xpath,bool readonly)
* @brief      Open graphic file
* @ingroup    GRAPHIC
*
* @param[in]  xpath : path to the Graphic file
* @param[in]  readonly : is read only flag
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAPFILEBASE::Open(XPATH& xpath,bool readonly)
{
  if(!file)                          return false;
  if(!file->Open(xpath,readonly))    return false;

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPBITMAPFILEBASE::Create(XPATH& xpath)
* @brief      Create
* @ingroup    GRAPHIC
*
* @param[in]  xpath : path to create the Graphic file
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAPFILEBASE::Create(XPATH& xpath)
{
  if(!file)                return false;
  if(!file->Create(xpath)) return false;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPBITMAPFILEBASE::Close()
* @brief      Close
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAPFILEBASE::Close()
{
  if(!file->Close()) return false;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPBITMAPFILEBASE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    GRAPHIC
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPBITMAPFILEBASE::Clean()
{

}




/**-------------------------------------------------------------------------------------------------------------------
*
* GRPBITMAPFILE
*
* --------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPBITMAPFILE::GRPBITMAPFILE()
* @brief      Constructor
* @ingroup    GRAPHIC
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPBITMAPFILE::GRPBITMAPFILE()
{
  Clean();
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPBITMAPFILE::GRPBITMAPFILE(XCHAR* xpath)
* @brief      Constructor
* @ingroup    GRAPHIC
*
* @param[in]  XCHAR* : initial path to file
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPBITMAPFILE::GRPBITMAPFILE(XCHAR* xpath)
{
  Clean();

  this->xpath = xpath;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPBITMAPFILE::GRPBITMAPFILE(XPATH& xpath)
* @brief      Constructor
* @ingroup    GRAPHIC
*
* @param[in]  XPATH& : initial path to file
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPBITMAPFILE::GRPBITMAPFILE(XPATH& xpath)
{
  Clean();

  this->xpath = xpath;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPBITMAPFILE::~GRPBITMAPFILE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    GRAPHIC
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPBITMAPFILE::~GRPBITMAPFILE()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XCHAR* GRPBITMAPFILE::GetPath()
* @brief      Get Path of file
* @ingroup    GRAPHIC
*
* @return     XCHAR* : Path of file
*
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR* GRPBITMAPFILE::GetPath()
{
  return xpath.Get();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPBITMAPFILE::SetPath(XPATH& xpath)
* @brief      Set Path of file
* @ingroup    GRAPHIC
*
* @param[in]  xpath : Path of file
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPBITMAPFILE::SetPath(XPATH& xpath)
{
  this->xpath = xpath;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPBITMAPFILE::SetPath(XCHAR* xpath)
* @brief      SetPath
* @ingroup    GRAPHIC
*
* @param[in]  xpath : Path of file
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPBITMAPFILE::SetPath(XCHAR* xpath)
{
  this->xpath = xpath;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPBITMAP* GRPBITMAPFILE::Load(XCHAR* xpath, GRPPROPERTYMODE forcemode)
* @brief      Load
* @ingroup    GRAPHIC
*
* @param[in]  xpath :
* @param[in]  forcemode :
*
* @return     GRPBITMAP* :
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPBITMAP* GRPBITMAPFILE::Load(XCHAR* xpath, GRPPROPERTYMODE forcemode)
{
  if(!xpath) return NULL;

  XPATH   _xpath;
  XSTRING ext;

  _xpath = xpath;

  _xpath.GetExt(ext);
  if(ext.IsEmpty())   return NULL;

  GRPBITMAPFILEBASE*  grpfilebase = NULL;
  GRPBITMAP*          bitmap      = NULL;

  if(!ext.Compare(__L(".jpg"),  true))  grpfilebase = new GRPBITMAPFILEJPG();
  if(!ext.Compare(__L(".jpeg"), true))  grpfilebase = new GRPBITMAPFILEJPG();
  if(!ext.Compare(__L(".png"),  true))  grpfilebase = new GRPBITMAPFILEPNG();
  if(!ext.Compare(__L(".bmp"),  true))  grpfilebase = new GRPBITMAPFILEBMP();
  if(!ext.Compare(__L(".tga"),  true))  grpfilebase = new GRPBITMAPFILETGA();

  if(grpfilebase)
    {
      bitmap = grpfilebase->CreateBitmapFromFile(_xpath, forcemode);

      delete grpfilebase;
    }

  return bitmap;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPBITMAP* GRPBITMAPFILE::Load(XPATH& xpath, GRPPROPERTYMODE forcemode)
* @brief      Load
* @ingroup    GRAPHIC
*
* @param[in]  xpath :
* @param[in]  forcemode :
*
* @return     GRPBITMAP* :
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPBITMAP* GRPBITMAPFILE::Load(XPATH& xpath, GRPPROPERTYMODE forcemode)
{
  return Load(xpath.Get(), forcemode);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPBITMAP* GRPBITMAPFILE::Load(GRPPROPERTYMODE forcemode)
* @brief      Load
* @ingroup    GRAPHIC
*
* @param[in]  forcemode :
*
* @return     GRPBITMAP* :
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPBITMAP* GRPBITMAPFILE::Load(GRPPROPERTYMODE forcemode)
{
  if(xpath.IsEmpty()) return NULL;

  return Load(xpath, forcemode);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPBITMAPFILE::Save(XCHAR* xpath, GRPBITMAP* bitmap, int quality)
* @brief      Save
* @ingroup    GRAPHIC
*
* @param[in]  xpath :
* @param[in]  bitmap :
* @param[in]  quality :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAPFILE::Save(XCHAR* xpath, GRPBITMAP* bitmap, int quality)
{
  if(!xpath) return false;

  XPATH   _xpath;
  XSTRING ext;

  _xpath = xpath;

  _xpath.GetExt(ext);
  if(ext.IsEmpty()) return false;

  GRPBITMAPFILEBASE* grpfilebase  = NULL;
  bool         status       = false;

  if(!ext.Compare(__L(".jpg"), true)) grpfilebase = new GRPBITMAPFILEJPG();
  if(!ext.Compare(__L(".png"), true)) grpfilebase = new GRPBITMAPFILEPNG();
  if(!ext.Compare(__L(".bmp"), true)) grpfilebase = new GRPBITMAPFILEBMP();
  if(!ext.Compare(__L(".tga"), true)) grpfilebase = new GRPBITMAPFILETGA();

  if(grpfilebase)
    {
      status = grpfilebase->CreateFileFromBitmap(_xpath, bitmap, quality);
      delete grpfilebase;
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPBITMAPFILE::Save(XPATH& xpath, GRPBITMAP* bitmap, int quality)
* @brief      Save
* @ingroup    GRAPHIC
*
* @param[in]  xpath :
* @param[in]  bitmap :
* @param[in]  quality :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAPFILE::Save(XPATH& xpath, GRPBITMAP* bitmap, int quality)
{
  return Save(xpath.Get(), bitmap, quality);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPBITMAPFILE::Save(GRPBITMAP* bitmap, int quality)
* @brief      Save
* @ingroup    GRAPHIC
*
* @param[in]  bitmap :
* @param[in]  quality :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPBITMAPFILE::Save(GRPBITMAP* bitmap, int quality)
{
  if(xpath.IsEmpty()) return false;

  return Save(xpath, bitmap, quality);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPBITMAPSEQUENCE* GRPBITMAPFILE::LoadSequence(XCHAR* namemask, int inisequence, int endsequence)
* @brief      Load Sequence of bitmap
* @ingroup    GRAPHIC
*
* @param[in]  namemask : string to mask
* @param[in]  inisequence : first ini of the sequence
* @param[in]  endsequence : end ini of the sequence
*
* @return     GRPBITMAPSEQUENCE* : bitmap sequence class
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPBITMAPSEQUENCE* GRPBITMAPFILE::LoadSequence(XCHAR* namemask, int inisequence, int endsequence)
{
  if(xpath.IsEmpty()) return NULL;

  GRPBITMAPSEQUENCE* bitmapsequence = new GRPBITMAPSEQUENCE();
  if(!bitmapsequence) return NULL;

  XSTRING namefile;

  //xpath.GetNamefileExt(namefile);
  //if(!namefile.IsEmpty()) return NULL;

  // The sequence is in individual files in a directory. Sequence numbers must be continuos
  int nfiles = inisequence;

  while((nfiles < endsequence)|| (endsequence < 0))
    {
      XPATH xpathtemp;
      bool  existfile = false;

      namefile.Format(namemask, nfiles);
      xpathtemp.Create(2, xpath.Get(), namefile.Get());

      XFILE* GEN_XFACTORY_CREATE(xfile, Create_File())
      if(xfile)
        {
          existfile = xfile->Exist(xpathtemp);
          GEN_XFACTORY.Delete_File(xfile);
        }

      if(!existfile) break;

      GRPBITMAP* bitmap = Load(xpathtemp);
      if(!bitmap) break;

      bitmapsequence->AddFrame(bitmap);

      nfiles++;
    }

  return bitmapsequence;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPBITMAPFILE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    GRAPHIC
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPBITMAPFILE::Clean()
{

}

