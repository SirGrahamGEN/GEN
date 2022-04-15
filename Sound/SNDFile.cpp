/**-------------------------------------------------------------------------------------------------------------------
*
* @file       SNDFile.cpp
*
* @class      SNDFILE
* @brief      Sound File class
* @ingroup    SOUND
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

#include "XFactory.h"

#include "SNDFile.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDFILE::SNDFILE()
* @brief      Constructor
* @ingroup    SOUND
*
* @return     Does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
SNDFILE::SNDFILE()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDFILE::~SNDFILE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    SOUND
*
* @return     Does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
SNDFILE::~SNDFILE()
{  
  if(xbuffer)             delete xbuffer;
  if(xbufferdecodeddata)  delete xbufferdecodeddata;

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* SNDFILE::GetID()
* @brief      GetID
* @ingroup    SOUND
*
* @return     XSTRING* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* SNDFILE::GetID()                                              
{ 
  return &ID;               
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBUFFER* SNDFILE::GetData()
* @brief      GetData
* @ingroup    SOUND
*
* @return     XBUFFER* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XBUFFER* SNDFILE::GetData()
{ 
  return xbufferdecodeddata;  
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWORD SNDFILE::GetChannels()
* @brief      GetChannels
* @ingroup    SOUND
*
* @return     XWORD : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XWORD SNDFILE::GetChannels()                                              
{ 
  return channels;            
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD SNDFILE::GetNSamples()
* @brief      GetNSamples
* @ingroup    SOUND
*
* @return     XDWORD : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD SNDFILE::GetNSamples()                                              
{ 
  return nsamples;             
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD SNDFILE::GetSampleRate()
* @brief      GetSampleRate
* @ingroup    SOUND
*
* @return     XDWORD : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD SNDFILE::GetSampleRate()                                              
{ 
  return samplerate;          
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float SNDFILE::GetDuration()
* @brief      GetDuration
* @ingroup    SOUND
*
* @return     float : 
*
*---------------------------------------------------------------------------------------------------------------------*/
float SNDFILE::GetDuration()                                              
{ 
  return duration;            
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SNDFILE::LoadFile(XCHAR* path, XCHAR* name, bool isstream)
* @brief      LoadFile
* @ingroup    SOUND
*
* @param[in]  path : 
* @param[in]  name : 
* @param[in]  isstream : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SNDFILE::LoadFile(XCHAR* path, XCHAR* name, bool isstream)      
{ 
  return false;               
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SNDFILE::LoadFile(XPATH& xpath, XCHAR* name, bool isstream)
* @brief      LoadFile
* @ingroup    SOUND
*
* @param[in]  xpath : 
* @param[in]  name : 
* @param[in]  isstream : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SNDFILE::LoadFile(XPATH& xpath, XCHAR* ID, bool isstream)     
{ 
  return LoadFile(xpath.Get(), ID, isstream);               
}

  

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SNDFILE::WriteRaw(XCHAR* path, XCHAR* name)
* @brief      WriteRaw
* @ingroup    SOUND
*
* @param[in]  path : 
* @param[in]  name : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SNDFILE::WriteRaw(XCHAR* path, XCHAR* ID)
{
  XFILE* GEN_XFACTORY_CREATE(xfile, Create_File())
  if(!xfile) return false;
    
  if(!xfile->Open(path, false))
    {
      if(!xfile->Create(path))
        {
          delete(xfile);
          return false;
        }
    }

  bool status = xfile->Write(*xbufferdecodeddata);

  xfile->Close();

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SNDFILE::WriteRaw(XPATH& xpath, XCHAR* ID)
* @brief      WriteRaw
* @ingroup    SOUND
*
* @param[in]  xpath : 
* @param[in]  ID : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SNDFILE::WriteRaw(XPATH& xpath, XCHAR* ID)
{
  return WriteRaw(xpath.Get(), ID);
}





/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SNDFILE::Reset()
* @brief      Reset
* @ingroup    SOUND
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SNDFILE::Reset()                                              
{ 
  return true;                
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDFILE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    SOUND
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SNDFILE::Clean()
{
  ID.Empty();
  isstream            = false;
  
  channels            = 0;
  nsamples            = 0;
  samplerate          = 0;
  duration            = 0.0f;
  
  xbuffer             = NULL;
  xbufferdecodeddata  = NULL;

}


