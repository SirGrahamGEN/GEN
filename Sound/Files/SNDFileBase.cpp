/**-------------------------------------------------------------------------------------------------------------------
*
* @file       SNDFileBase.cpp
*
* @class      SNDFILEBASE
* @brief      Sound File Base class
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XFactory.h"

#include "SNDFileBase.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDFILEBASE::SNDFILEBASE()
* @brief      Constructor
* @ingroup    SOUND
*
* @return     Does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDFILEBASE::SNDFILEBASE()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDFILEBASE::~SNDFILEBASE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    SOUND
*
* @return     Does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDFILEBASE::~SNDFILEBASE()
{ 
  Close();

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* SNDFILEBASE::GetID()
* @brief      GetID
* @ingroup    SOUND
*
* @return     XSTRING* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* SNDFILEBASE::GetID()                                              
{ 
  return &ID;               
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWORD SNDFILEBASE::GetChannels()
* @brief      GetChannels
* @ingroup    SOUND
*
* @return     XWORD : 
*
* --------------------------------------------------------------------------------------------------------------------*/
XWORD SNDFILEBASE::GetChannels()                                              
{ 
  return channels;            
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD SNDFILEBASE::GetNSamples()
* @brief      GetNSamples
* @ingroup    SOUND
*
* @return     XDWORD : 
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD SNDFILEBASE::GetNSamples()                                              
{ 
  return nsamples;             
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD SNDFILEBASE::GetSampleRate()
* @brief      GetSampleRate
* @ingroup    SOUND
*
* @return     XDWORD : 
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD SNDFILEBASE::GetSampleRate()                                              
{ 
  return samplerate;          
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float SNDFILEBASE::GetDuration()
* @brief      GetDuration
* @ingroup    SOUND
*
* @return     float : 
*
* --------------------------------------------------------------------------------------------------------------------*/
float SNDFILEBASE::GetDuration()                                              
{ 
  return duration;            
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDFILEBASE::Open(XCHAR* path , XCHAR* ID)
* @brief      Open
* @ingroup    SOUND
*
* @param[in]  path : 
* @param[in]  ID : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool SNDFILEBASE::Open(XCHAR* path , XCHAR* ID)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDFILEBASE::Open(XPATH& xpath , XCHAR* ID)
* @brief      Open
* @ingroup    SOUND
*
* @param[in]  xpath : 
* @param[in]  ID : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool SNDFILEBASE::Open(XPATH& xpath , XCHAR* ID)
{
  return Open(xpath.Get(), ID);
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDFILEBASE::ReadData(XBYTE* data, XDWORD& sizeread, bool& isfinished))
* @brief      ReadData
* @ingroup    SOUND
*
* @param[in]  data : 
* @param[in]  sizeread : 
* @param[in]  isfinished) : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool SNDFILEBASE::ReadData(XBYTE* data, XDWORD& sizeread, bool& isfinished)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDFILEBASE::ReadData(XBUFFER& data, bool& isfinished)
* @brief      ReadData
* @ingroup    SOUND
*
* @param[in]  data : 
* @param[in]  isfinished) : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool SNDFILEBASE::ReadData(XBUFFER& data, bool& isfinished)
{
  XDWORD  sizeread = data.GetSize();
  bool    status   = false;

  status = ReadData(data.Get(), sizeread, isfinished);
  if(sizeread) data.Resize(sizeread);    
    
  return status;
}


 /**-------------------------------------------------------------------------------------------------------------------
 * 
 * @fn        XDWORD SNDFILEBASE::GetDataSize()
 * @brief     GetDataSize
 * @ingroup   SOUND
 * 
   * 
 * @return      XDWORD : 
 * 
 * ---------------------------------------------------------------------------------------------------------------------*/
XDWORD SNDFILEBASE::GetDataSize()
{
  return 0;
}
 


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD SNDFILEBASE::GetReadSize()
* @brief      GetReadSize
* @ingroup    SOUND
*
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD SNDFILEBASE::GetReadSize()
{
  return 0;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDFILEBASE::Close()
* @brief      Close
* @ingroup    SOUND
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool SNDFILEBASE::Close()
{
  return false;
}
    


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDFILEBASE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    SOUND
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDFILEBASE::Clean()
{
  ID.Empty();
  
  channels            = 0;
  nsamples            = 0;
  samplerate          = 0;
  duration            = 0.0f;
}


