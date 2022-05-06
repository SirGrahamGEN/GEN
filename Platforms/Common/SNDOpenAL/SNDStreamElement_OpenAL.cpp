/**-------------------------------------------------------------------------------------------------------------------
*
* @file       SNDStreamElement_OpenAL.cpp
*
* @class      SNDSTREAMELEMENT_OPENAL
* @brief      Sound Open AL Stream Element class
* @ingroup    PLATFORM_COMMON
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

#include "XTrace.h"

#include "SNDBuffer_OpenAL.h"
#include "SNDSource_OpenAL.h"
#include "SNDFile.h"
#include "SNDCodec.h"

#include "SNDStreamElement_OpenAL.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDSTREAMELEMENT_OPENAL::SNDSTREAMELEMENT_OPENAL()
* @brief      Constructor
* @ingroup    PLATFORM_COMMON
*
* @return     Does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDSTREAMELEMENT_OPENAL::SNDSTREAMELEMENT_OPENAL() : SNDSTREAMELEMENT()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDSTREAMELEMENT_OPENAL::~SNDSTREAMELEMENT_OPENAL()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_COMMON
*
* @return     Does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDSTREAMELEMENT_OPENAL::~SNDSTREAMELEMENT_OPENAL()
{
  if(file) delete file;
    
  ClearBuffers();
  Clean();
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSTREAMELEMENT_OPENAL::Play()
* @brief      Play
* @ingroup    PLATFORM_COMMON
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDSTREAMELEMENT_OPENAL::Play()
{
  source->Play();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSTREAMELEMENT_OPENAL::AddData(XDWORD size, void* data)
* @brief      AddData
* @ingroup    PLATFORM_COMMON
*
* @param[in]  size : 
* @param[in]  data : 
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDSTREAMELEMENT_OPENAL::AddData(XDWORD size, void* data)
{
  if(size)
    {
      SNDBUFFER_OPENAL* buffer = NULL;

      buffer = new SNDBUFFER_OPENAL();
      buffer->Generate();

      buffer->Upload(channels, data, size, freq);

      duration += ((float)size) / (sizeof(short)*freq);

      if(source)
        {
          source->Queue(buffer);
          queuedbuffers.Add(buffer); // need to clean this up later(maybe in SNDOPENAL::Update if we know it's a streamer?)
        }
    }
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSTREAMELEMENT_OPENAL::SetFile(SNDFILE* file)
* @brief      SetFile
* @ingroup    PLATFORM_COMMON
*
* @param[in]  file : 
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDSTREAMELEMENT_OPENAL::SetFile(SNDFILE* file)
{
  this->file = file;

  ID.Set(file->GetID()->Get());

  this->channels = file->GetChannels();
  this->freq = file->GetSampleRate();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSTREAMELEMENT_OPENAL::ClearBuffers()
* @brief      ClearBuffers
* @ingroup    PLATFORM_COMMON
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDSTREAMELEMENT_OPENAL::ClearBuffers()
{
  XLIST<SNDBUFFER_OPENAL*>::XITERATOR it;
  for(it = queuedbuffers.Begin(); it != queuedbuffers.End(); it++)
    {
      SNDBUFFER_OPENAL* buffer = *it;
      source->UnQueue(buffer);
      buffer->Destroy();
      delete buffer;
    }

  queuedbuffers.DeleteAll();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSTREAMELEMENT_OPENAL::SetSource(SNDSOURCE_OPENAL* source)
* @brief      SetSource
* @ingroup    PLATFORM_COMMON
*
* @param[in]  source : 
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDSTREAMELEMENT_OPENAL::SetSource(SNDSOURCE_OPENAL* source)                                 
{ 
  this->source = source;  
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDSOURCE_OPENAL* SNDSTREAMELEMENT_OPENAL::GetSource()
* @brief      GetSource
* @ingroup    PLATFORM_COMMON
*
* @return     SNDSOURCE_OPENAL* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
SNDSOURCE_OPENAL* SNDSTREAMELEMENT_OPENAL::GetSource()
{ 
  return source;          
}

  
  
/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDSTREAMELEMENT_OPENAL::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_COMMON
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void SNDSTREAMELEMENT_OPENAL::Clean()
{
  totalbuffers  = 0;
  source        = NULL;
}



