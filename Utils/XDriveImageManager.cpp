/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XDriveImageManager.cpp
*
* @class      XDRIVEIMAGEMANAGER
* @brief      eXtended Drive Image Manager class
* @ingroup    UTILS
*
* @copyright  GEN Group. All right reserved.
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

#include "XBase.h"
#include "XFactory.h"
#include "XBuffer.h"
#include "XPath.h"
#include "XFile.h"

#include "XDriveImageManager_XEvent.h"
#include "XDriveImageManager.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


XDRIVEIMAGEMANAGER* XDRIVEIMAGEMANAGER::instance = NULL;

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------------------------------------------------*/
/*  XDRIVEIMAGEMANAGER_DRIVE                                                                                          */
/*--------------------------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDRIVEIMAGEMANAGER_DRIVE::XDRIVEIMAGEMANAGER_DRIVE()
* @brief      Constructor
* @ingroup    UTILS
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XDRIVEIMAGEMANAGER_DRIVE::XDRIVEIMAGEMANAGER_DRIVE()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDRIVEIMAGEMANAGER_DRIVE::~XDRIVEIMAGEMANAGER_DRIVE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    UTILS
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XDRIVEIMAGEMANAGER_DRIVE::~XDRIVEIMAGEMANAGER_DRIVE()
{
  Clean();
}





/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XDRIVEIMAGEMANAGER::GetIsInstanced()
* @brief      Get if Is Instanced
* @note       STATIC
* @ingroup    UTILS
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XDRIVEIMAGEMANAGER::GetIsInstanced()
{
  return instance!=NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDRIVEIMAGEMANAGER& XDRIVEIMAGEMANAGER::GetInstance()
* @brief      Get Instance of XDRIVEIMAGEMANAGER
* @note       STATIC
* @ingroup    UTILS
*
* @return     XDRIVEIMAGE& :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDRIVEIMAGEMANAGER& XDRIVEIMAGEMANAGER::GetInstance()
{
  if(!instance) 
    {
      instance = new XDRIVEIMAGEMANAGER();
    }

  return (*instance);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XDRIVEIMAGEMANAGER::SetInstance(XDRIVEIMAGEMANAGER* instance)
* @brief      Set Instance of XDRIVEIMAGEMANAGER
* @note       STATIC
* @ingroup    UTILS
*
* @param[in]  _instance : new instance
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XDRIVEIMAGEMANAGER::SetInstance(XDRIVEIMAGEMANAGER* _instance)
{
  if(!_instance) return false;

  instance = _instance;

  return (instance)?true:false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XDRIVEIMAGEMANAGER::DelInstance()
* @brief      Delete Instance of XDRIVEIMAGE
* @note       STATIC
* @ingroup    UTILS
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XDRIVEIMAGEMANAGER::DelInstance()
{
  if(instance)
    {
      delete instance;
      instance = NULL;

      return true;
    }

  return false;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* XDRIVEIMAGEMANAGER_DRIVE::GetName()
* @brief      GetName
* @ingroup    UTILS
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* XDRIVEIMAGEMANAGER_DRIVE::GetName()
{
  return &name;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* XDRIVEIMAGEMANAGER_DRIVE::GetLabel()
* @brief      GetLabel
* @ingroup    UTILS
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* XDRIVEIMAGEMANAGER_DRIVE::GetLabel()
{
  return &label;
}



 /**-------------------------------------------------------------------------------------------------------------------
 *
 *  @fn         XPATH* XDRIVEIMAGEMANAGER_DRIVE::GetPath()
 *  @brief      GetPath
 *  @ingroup    UTILS
 *
 *  ""
 *  ""
 *
 *  @return     XPATH* :
 *
 *---------------------------------------------------------------------------------------------------------------------*/
XPATH* XDRIVEIMAGEMANAGER_DRIVE::GetPath()
{
  return &path;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XDRIVEIMAGEMANAGER_DRIVE::GetVolume()
* @brief      GetVolume
* @ingroup    UTILS
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int XDRIVEIMAGEMANAGER_DRIVE::GetVolume()
{
  return volume;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XDRIVEIMAGEMANAGER_DRIVE::SetVolume(int volume)
* @brief      SetVolume
* @ingroup    UTILS
*
* @param[in]  volume :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XDRIVEIMAGEMANAGER_DRIVE::SetVolume(int volume)
{
  this->volume = volume;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XDRIVEIMAGEMANAGER_DRIVE::GetDeviceID()
* @brief      GetDeviceID
* @ingroup    UTILS
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD XDRIVEIMAGEMANAGER_DRIVE::GetDeviceID()
{
  return deviceID;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XDRIVEIMAGEMANAGER_DRIVE::SetDeviceID(XDWORD deviceID)
* @brief      SetDeviceID
* @ingroup    UTILS
*
* @param[in]  deviceID :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void  XDRIVEIMAGEMANAGER_DRIVE::SetDeviceID(XDWORD deviceID)
{
  this->deviceID  = deviceID;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XQWORD XDRIVEIMAGEMANAGER_DRIVE::GetID()
* @brief      GetID
* @ingroup    UTILS
*
* @return     XQWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XQWORD XDRIVEIMAGEMANAGER_DRIVE::GetID()
{
  return ID;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XDRIVEIMAGEMANAGER_DRIVE::SetID(XQWORD ID)
* @brief      SetID
* @ingroup    UTILS
*
* @param[in]  ID :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XDRIVEIMAGEMANAGER_DRIVE::SetID(XQWORD ID)
{
  this->ID = ID;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XQWORD XDRIVEIMAGEMANAGER_DRIVE::GetSectorSize()
* @brief      GetSectorSize
* @ingroup    UTILS
*
* @return     XQWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XQWORD XDRIVEIMAGEMANAGER_DRIVE::GetSectorSize()
{
  return sectorsize;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XDRIVEIMAGEMANAGER_DRIVE::SetSectorSize(XQWORD sectorsize)
* @brief      SetSectorSize
* @ingroup    UTILS
*
* @param[in]  sectorsize :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XDRIVEIMAGEMANAGER_DRIVE::SetSectorSize(XQWORD sectorsize)
{
  this->sectorsize = sectorsize;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XQWORD XDRIVEIMAGEMANAGER_DRIVE::GetNumberSectors()
* @brief      GetNumberSectors
* @ingroup    UTILS
*
* @return     XQWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XQWORD XDRIVEIMAGEMANAGER_DRIVE::GetNumberSectors()
{
  return numbersectors;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XDRIVEIMAGEMANAGER_DRIVE::SetNumberSectors(XQWORD numbersectors)
* @brief      SetNumberSectors
* @ingroup    UTILS
*
* @param[in]  numbersectors :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XDRIVEIMAGEMANAGER_DRIVE::SetNumberSectors(XQWORD numbersectors)
{
  this->numbersectors = numbersectors;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XQWORD XDRIVEIMAGEMANAGER_DRIVE::GetSize()
* @brief      GetSize
* @ingroup    UTILS
*
* @return     XQWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XQWORD XDRIVEIMAGEMANAGER_DRIVE::GetSize()
{
  return (numbersectors * sectorsize);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XDRIVEIMAGEMANAGER_DRIVE::GetSizeInGB()
* @brief      GetSizeInGB
* @ingroup    UTILS
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD XDRIVEIMAGEMANAGER_DRIVE::GetSizeInGB()
{
  XQWORD size = GetSize();

  size  = (size / 1000000000);
  size += ((GetSize() % 1000000000) > 500)?1:0;

  return (XDWORD)size;

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XDRIVEIMAGEMANAGER_DRIVE::GetHandle()
* @brief      GetHandle
* @ingroup    UTILS
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD XDRIVEIMAGEMANAGER_DRIVE::GetHandle()
{
  return handle;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XDRIVEIMAGEMANAGER_DRIVE::SetHandle(XDWORD handle)
* @brief      SetHandle
* @ingroup    UTILS
*
* @param[in]  handle :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XDRIVEIMAGEMANAGER_DRIVE::SetHandle(XDWORD handle)
{
  this->handle = handle;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XDRIVEIMAGEMANAGER_DRIVE::GetRawHandle()
* @brief      GetRawHandle
* @ingroup    UTILS
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD XDRIVEIMAGEMANAGER_DRIVE::GetRawHandle()
{
  return rawhandle;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XDRIVEIMAGEMANAGER_DRIVE::SetRawHandle(XDWORD handle)
* @brief      SetRawHandle
* @ingroup    UTILS
*
* @param[in]  rawhandle :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XDRIVEIMAGEMANAGER_DRIVE::SetRawHandle(XDWORD rawhandle)
{
  this->rawhandle = rawhandle;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XDRIVEIMAGEMANAGER_DRIVE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    UTILS
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XDRIVEIMAGEMANAGER_DRIVE::Clean()
{
  volume        = 0;
  deviceID      = 0;
  ID            = 0L;
  sectorsize    = 0;
  numbersectors = 0;
  handle        = 0;
  rawhandle     = 0;
}


/*--------------------------------------------------------------------------------------------------------------------*/
/*  XDRIVEIMAGEMANAGER                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDRIVEIMAGEMANAGER::XDRIVEIMAGEMANAGER()
* @brief      Constructor
* @ingroup    UTILS
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XDRIVEIMAGEMANAGER::XDRIVEIMAGEMANAGER()
{
  Clean();

  RegisterEvent(XDRIVEIMAGEMANAGER_XEVENT_TYPE_READSECTORS);
  RegisterEvent(XDRIVEIMAGEMANAGER_XEVENT_TYPE_WRITESECTORS);
  RegisterEvent(XDRIVEIMAGEMANAGER_XEVENT_TYPE_READTOIMGFILE);
  RegisterEvent(XDRIVEIMAGEMANAGER_XEVENT_TYPE_WRITEFROMIMGFILE);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDRIVEIMAGEMANAGER::~XDRIVEIMAGEMANAGER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    UTILS
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XDRIVEIMAGEMANAGER::~XDRIVEIMAGEMANAGER()
{
  DeRegisterEvent(XDRIVEIMAGEMANAGER_XEVENT_TYPE_READSECTORS);
  DeRegisterEvent(XDRIVEIMAGEMANAGER_XEVENT_TYPE_WRITESECTORS);
  DeRegisterEvent(XDRIVEIMAGEMANAGER_XEVENT_TYPE_READTOIMGFILE);
  DeRegisterEvent(XDRIVEIMAGEMANAGER_XEVENT_TYPE_WRITEFROMIMGFILE);

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XDRIVEIMAGEMANAGER::GetLogicalDrives(XVECTOR<XDRIVEIMAGEMANAGER_DRIVE*>& drives)
* @brief      GetLogicalDrives
* @ingroup    UTILS
*
* @param[in]  drives :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XDRIVEIMAGEMANAGER::GetDrives(XVECTOR<XDRIVEIMAGEMANAGER_DRIVE*>& drives)
{
  return false;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XDRIVEIMAGEMANAGER::Open(XDRIVEIMAGEMANAGER_DRIVE& drive)
* @brief      Open
* @ingroup    UTILS
*
* @param[in]  drive :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XDRIVEIMAGEMANAGER::Open(XDRIVEIMAGEMANAGER_DRIVE& drive)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XDRIVEIMAGEMANAGER::Read(XDRIVEIMAGEMANAGER_DRIVE& drive, XQWORD startsector, XQWORD numbersectors, XBUFFER& buffer)
* @brief      Read
* @ingroup    UTILS
*
* @param[in]  drive :
* @param[in]  startsector :
* @param[in]  numbersectors :
* @param[in]  buffer :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XDRIVEIMAGEMANAGER::Read(XDRIVEIMAGEMANAGER_DRIVE& drive, XQWORD startsector, XQWORD numbersectors, XBUFFER& buffer)
{

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XDRIVEIMAGEMANAGER::Write(XDRIVEIMAGEMANAGER_DRIVE& drive, XQWORD startsector, XQWORD numbersectors, XBUFFER& buffer)
* @brief      Write
* @ingroup    UTILS
*
* @param[in]  drive :
* @param[in]  startsector :
* @param[in]  numbersectors :
* @param[in]  buffer :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XDRIVEIMAGEMANAGER::Write(XDRIVEIMAGEMANAGER_DRIVE& drive, XQWORD startsector, XQWORD numbersectors, XBUFFER& buffer)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XDRIVEIMAGEMANAGER::ReadToIMGFile(XDRIVEIMAGEMANAGER_DRIVE& drive, XPATH& pathfileIMG, XQWORD nsectorsperblock)
* @brief      ReadToIMGFile
* @ingroup    UTILS
*
* @param[in]  drive :
* @param[in]  pathfileIMG :
* @param[in]  nsectorsperblock :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XDRIVEIMAGEMANAGER::ReadToIMGFile(XDRIVEIMAGEMANAGER_DRIVE& drive, XPATH& pathfileIMG, XQWORD nsectorsperblock)
{
  XFILE*   xfileIMG;
  XBUFFER  readbuffer;
  XQWORD   nsectorstoread = nsectorsperblock;
  XQWORD   nsectorsread   = 0;
  bool     status         = 0;

  if(!drive.GetSize()) return status;

  GEN_XFACTORY_CREATE(xfileIMG, Create_File())
  if(xfileIMG)
    {
      if(xfileIMG->Create(pathfileIMG))
        {
          XQWORD indexsector=0;

          while(indexsector<drive.GetNumberSectors())
            {
              if((indexsector + nsectorstoread) > drive.GetNumberSectors()) nsectorstoread = (drive.GetNumberSectors() - indexsector);

              XDRIVEIMAGEMANAGER_XEVENT xevent(this, XDRIVEIMAGEMANAGER_XEVENT_TYPE_READTOIMGFILE);

              xevent.SetDrive(&drive);
              xevent.SetIndexSector(indexsector);
              xevent.SetNumberSectorsInOperation(nsectorstoread);
              xevent.SetError(XDRIVEIMAGEMANAGER_ERROR_NONE);

              status = Read(drive, indexsector, nsectorstoread, readbuffer);
              if(!status) xevent.SetError(XDRIVEIMAGEMANAGER_ERROR_READSECTORS);

              if(status)
                {
                  status = xfileIMG->Write(readbuffer);
                  if(!status) xevent.SetError(XDRIVEIMAGEMANAGER_ERROR_WRITEIMGFILE);
                }

              if(status) nsectorsread += nsectorstoread;

              lastoperationpercent = (((float)nsectorsread*100)/(float)drive.GetNumberSectors());

              xevent.SetError(lasterror);
              xevent.SetOperationPercent(lastoperationpercent);

              PostEvent(&xevent);

              if(!status) break;

              indexsector += nsectorstoread;
            }

          xfileIMG->Close();
        }

      GEN_XFACTORY.Delete_File(xfileIMG);
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XDRIVEIMAGEMANAGER::WritedFromIMGFile(XDRIVEIMAGEMANAGER_DRIVE& drive, XPATH& pathfileIMG, XQWORD nsectorsperblock)
* @brief      WritedFromIMGFile
* @ingroup    UTILS
*
* @param[in]  drive :
* @param[in]  pathfileIMG :
* @param[in]  nsectorsperblock :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XDRIVEIMAGEMANAGER::WriteFromIMGFile(XDRIVEIMAGEMANAGER_DRIVE& drive, XPATH& pathfileIMG, XQWORD nsectorsperblock)
{
  XFILE*   xfileIMG;
  XBUFFER  writebuffer;
  XQWORD   nsectorstowrite    = nsectorsperblock;
  XQWORD   nsectorswritten    = 0;
  bool     status             = 0;

  if(!drive.GetSize()) return status;

  writebuffer.Resize((XDWORD)(nsectorstowrite * drive.GetSectorSize()));

  GEN_XFACTORY_CREATE(xfileIMG, Create_File())
  if(xfileIMG)
    {
      if(xfileIMG->Open(pathfileIMG, true))
        {
          XQWORD indexsector=0;

          while(indexsector<drive.GetNumberSectors())
            {
              if((indexsector + nsectorstowrite) > drive.GetNumberSectors()) nsectorstowrite = (drive.GetNumberSectors() - indexsector);

              XDRIVEIMAGEMANAGER_XEVENT xevent(this, XDRIVEIMAGEMANAGER_XEVENT_TYPE_WRITEFROMIMGFILE);

              xevent.SetDrive(&drive);
              xevent.SetIndexSector(indexsector);
              xevent.SetNumberSectorsInOperation(nsectorstowrite);
              lasterror = XDRIVEIMAGEMANAGER_ERROR_NONE;

              writebuffer.FillBuffer();

              status = xfileIMG->Read(writebuffer.Get(), (XDWORD)(nsectorstowrite * drive.GetSectorSize()));
              if(!status) lasterror = XDRIVEIMAGEMANAGER_ERROR_READIMGFILE;

              status = Write(drive, indexsector, nsectorstowrite, writebuffer);
              if(!status) lasterror = XDRIVEIMAGEMANAGER_ERROR_WRITESECTORS;

              if(status) nsectorswritten += nsectorstowrite;

              lastoperationpercent = (((float)nsectorswritten*100)/(float)drive.GetNumberSectors());

              xevent.SetError(lasterror);
              xevent.SetOperationPercent(lastoperationpercent);

              PostEvent(&xevent);

              if(!status) break;

              indexsector += nsectorstowrite;
            }

          xfileIMG->Close();
        }

      GEN_XFACTORY.Delete_File(xfileIMG);
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float XDRIVEIMAGEMANAGER::GetLastOperationPercent()
* @brief      GetLastOperationPercent
* @ingroup    UTILS
*
* @return     float :
*
*---------------------------------------------------------------------------------------------------------------------*/
float XDRIVEIMAGEMANAGER::GetLastOperationPercent()
{
  return lastoperationpercent;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDRIVEIMAGEMANAGER_ERROR XDRIVEIMAGEMANAGER::GetLastError()
* @brief      GetLastError
* @ingroup    UTILS
*
* @return     XDRIVEIMAGEMANAGER_ERROR :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDRIVEIMAGEMANAGER_ERROR XDRIVEIMAGEMANAGER::GetLastError()
{
  return lasterror;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XDRIVEIMAGEMANAGER::Close(XDRIVEIMAGEMANAGER_DRIVE& drive)
* @brief      Close
* @ingroup    UTILS
*
* @param[in]  drive :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XDRIVEIMAGEMANAGER::Close(XDRIVEIMAGEMANAGER_DRIVE& drive)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XDRIVEIMAGEMANAGER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    UTILS
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XDRIVEIMAGEMANAGER::Clean()
{
  lastoperationpercent = 0.0f;
  lasterror            = XDRIVEIMAGEMANAGER_ERROR_NONE;
}
