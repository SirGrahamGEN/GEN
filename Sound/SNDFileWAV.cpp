/**-------------------------------------------------------------------------------------------------------------------
*
* @file       SNDFileWAV.cpp
*
* @class      SNDFILEWAV
* @brief      Sound File WAV format class
* @ingroup    SOUND
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @copyright  Copyright(c) 2005 - 2020 GEN Group.
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

#include "XFactory.h"
#include "XFileRIFF.h"
#include "XTrace.h"

#include "SNDFileWAV.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDFILEWAV::SNDFILEWAV()
* @brief      Constructor
* @ingroup    SOUND
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     Does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
SNDFILEWAV::SNDFILEWAV() : SNDFILEBASE()
{
  Clean();
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDFILEWAV::~SNDFILEWAV()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    SOUND
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     Does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
SNDFILEWAV::~SNDFILEWAV()
{
  Clean();
}

    


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDFILEWAV::Open(XCHAR* path, XCHAR* ID)
* @brief      Open
* @ingroup    SOUND
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  path : 
* @param[in]  ID : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool SNDFILEWAV::Open(XCHAR* path, XCHAR* ID)
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

  channels    = format.num_channels;  
  samplerate  = format.sample_rate;
    
  data_list = fileRIFF->GetChunk(__L("data"), __L("WAVE"));
  if(!data_list) return false;

  dataoffsetinfile = data_list->GetPositionFileData();
  datasizeinfile   = data_list->GetSize();

  datasizeread     = 0;

  duration    =  ((float)(datasizeinfile/channels)/(float)format.byte_rate);
  nsamples    =  (XDWORD)((datasizeinfile*8)/format.bits_per_sample);

  return fileRIFF->GetFileBase()->SetPosition(dataoffsetinfile);  
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDFILEWAV::ReadData(XBYTE* data, XDWORD& sizeread, bool isfinished)
* @brief      ReadData
* @ingroup    SOUND
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
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
* @brief      GetDataSize
* @ingroup    SOUND
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
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
* @brief      GetReadSize
* @ingroup    SOUND
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
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
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
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
* @brief      GetFormat
* @ingroup    SOUND
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
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
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    SOUND
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SNDFILEWAV::Clean()
{
  fileRIFF          = NULL;

  format_list       = NULL;
  data_list         = NULL;

  memset(&format,  0, sizeof(SNDFILEWAV_FORMAT));

  dataoffsetinfile  = 0;
  datasizeinfile    = 0;
}


