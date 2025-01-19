/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       SNDFileWAV.cpp
* 
* @class      SNDFILEWAV
* @brief      Sound File WAV format class
* @ingroup    SOUND
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

#include "SNDFileWAV.h"

#include "XFactory.h"
#include "XFileRIFF.h"
#include "XTrace.h"

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
* @fn         SNDFILEWAV::SNDFILEWAV()
* @brief      Constructor of class
* @ingroup    SOUND
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDFILEWAV::SNDFILEWAV() : SNDFILE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDFILEWAV::~SNDFILEWAV()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    SOUND
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDFILEWAV::~SNDFILEWAV()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDFILEWAV::LoadFile()
* @brief      Load file
* @ingroup    SOUND
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDFILEWAV::LoadFile()
{
  xbufferdecodeddata = new XBUFFER(false);
  if(!xbufferdecodeddata)
    {
      return false;
    }

  bool status = false;

  if(Open(path.Get()))
    {
      XDWORD  sizeread    = datasizeinfile;
      bool    isfinished  = false;

      xbufferdecodeddata->Resize(sizeread);

      ReadData(xbufferdecodeddata->Get(), sizeread, isfinished);

      Close();

      status = true;
    }
  
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDFILEWAV::Open(XCHAR* path, XCHAR* ID)
* @brief      Open
* @ingroup    SOUND
*
* @param[in]  path : 
* @param[in]  ID : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool SNDFILEWAV::Open(XCHAR* path)
{
  fileRIFF = new XFILERIFF();
  if(!fileRIFF) return false;

  if(!fileRIFF->Open(path)) return false;

  if(!fileRIFF->ReadAllLists()) return false; 

  format_list = fileRIFF->GetChunk(__L("fmt "), __L("WAVE"));
  if(!format_list) return false;

  fileRIFF->GetFileBase()->SetPosition(format_list->GetPositionFileData());  

  if(!fileRIFF->GetFileBase()->Read((XBYTE*)&format.audio_format    , sizeof(XWORD)))   return false;
  if(!fileRIFF->GetFileBase()->Read((XBYTE*)&format.num_channels    , sizeof(XWORD)))   return false;
  if(!fileRIFF->GetFileBase()->Read((XBYTE*)&format.sample_rate     , sizeof(XDWORD)))  return false;
  if(!fileRIFF->GetFileBase()->Read((XBYTE*)&format.byte_rate       , sizeof(XDWORD)))  return false;
  if(!fileRIFF->GetFileBase()->Read((XBYTE*)&format.block_align     , sizeof(XWORD)))   return false;
  if(!fileRIFF->GetFileBase()->Read((XBYTE*)&format.bits_per_sample , sizeof(XWORD)))   return false;

  channels          = format.num_channels;  
  samplerate        = format.sample_rate;
    
  data_list = fileRIFF->GetChunk(__L("data"), __L("WAVE"));
  if(!data_list) return false;

  dataoffsetinfile  = data_list->GetPositionFileData();
  datasizeinfile    = data_list->GetSize();

  datasizeread      = 0;

  duration          =  ((XDWORD)(datasizeinfile/channels)/format.byte_rate)*1000;
  nsamples          =  (XDWORD)((datasizeinfile*8)/format.bits_per_sample);

  return fileRIFF->GetFileBase()->SetPosition(dataoffsetinfile);  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDFILEWAV::ReadData(XBYTE* data, XDWORD& sizeread, bool isfinished)
* @brief      Read data
* @ingroup    SOUND
*
* @param[in]  data : 
* @param[in]  sizeread : 
* @param[in]  isfinished : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool SNDFILEWAV::ReadData(XBYTE* data, XDWORD& sizeread, bool& isfinished)
{
  if(!fileRIFF)         return false;
  if(!data_list)        return false;
  if(!dataoffsetinfile) return false;

  XDWORD _sizeread = sizeread;

  if(datasizeread == datasizeinfile) 
    {
      datasizeread = 0;
    }

  isfinished = false;

  bool status = fileRIFF->GetFileBase()->Read(data, &_sizeread);
  if(!_sizeread  && !status) return false;

  datasizeread += _sizeread;

  if((sizeread != _sizeread) || (datasizeread >= datasizeinfile))
    {
      dataoffsetinfile = data_list->GetPositionFileData();
      fileRIFF->GetFileBase()->SetPosition(dataoffsetinfile);  
           
      isfinished = true;      

      sizeread = _sizeread;
    }

  return true;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD SNDFILEWAV::GetDataSize()
* @brief      Get data size
* @ingroup    SOUND
*
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD SNDFILEWAV::GetDataSize()
{
  return datasizeinfile;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD SNDFILEWAV::GetReadSize()
* @brief      Get read size
* @ingroup    SOUND
*
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD SNDFILEWAV::GetReadSize()
{
  return datasizeread;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDFILEWAV::Close()
* @brief      Close
* @ingroup    SOUND
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool SNDFILEWAV::Close()
{
  if(fileRIFF) 
    {
      format_list   = NULL;
      data_list     = NULL;

      delete fileRIFF;

      fileRIFF = NULL;
    }

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDFILEWAV_FORMAT* SNDFILEWAV::GetFormat()
* @brief      Get format
* @ingroup    SOUND
*
* @return     SNDFILEWAV_FORMAT* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
SNDFILEWAV_FORMAT*  SNDFILEWAV::GetFormat()
{
  return &format;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDFILEWAV::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    SOUND
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDFILEWAV::Clean()
{
  fileRIFF          = NULL;

  format_list       = NULL;
  data_list         = NULL;

  memset(&format,  0, sizeof(SNDFILEWAV_FORMAT));

  dataoffsetinfile  = 0;
  datasizeinfile    = 0;
}


#pragma endregion
