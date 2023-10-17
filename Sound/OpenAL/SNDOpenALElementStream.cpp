/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       SNDOpenALElementStream.cpp
* 
* @class      SNDOPENALELEMENTSTREAM
* @brief      Sound OpenAL Element Stream class
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

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "SNDOpenALElementStream.h"

#include "XTrace.h"

#include "SNDOpenALBuffer.h"
#include "SNDOpenALSource.h"
#include "SNDFile.h"
//#include "SNDCodec.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------

@fn         SNDOPENALELEMENTSTREAM::SNDOPENALELEMENTSTREAM()
@brief      Constructor
@ingroup    SOUND

@return     Does not return anything. 

--------------------------------------------------------------------------------------------------------------------*/
SNDOPENALELEMENTSTREAM::SNDOPENALELEMENTSTREAM() : SNDELEMENTSTREAM()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDOPENALELEMENTSTREAM::~SNDOPENALELEMENTSTREAM()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    SOUND
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDOPENALELEMENTSTREAM::~SNDOPENALELEMENTSTREAM()
{
  if(file) delete file;
    
  ClearBuffers();
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALELEMENTSTREAM::Play()
* @brief      Play
* @ingroup    SOUND
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALELEMENTSTREAM::Play()
{
  if(!source)
    {
      return;
    } 

  source->Play();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALELEMENTSTREAM::AddData(XDWORD size, void* data)
* @brief      AddData
* @ingroup    SOUND
* 
* @param[in]  size : 
* @param[in]  data : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALELEMENTSTREAM::AddData(XDWORD size, void* data)
{
  if(!size)
    {
      return;
    }

  SNDOPENALBUFFER* buffer = NULL;

  buffer = new SNDOPENALBUFFER();
  if(buffer)
    {
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
* @fn         void SNDOPENALELEMENTSTREAM::SetFile(SNDFILE* file)
* @brief      SetFile
* @ingroup    SOUND
* 
* @param[in]  file : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALELEMENTSTREAM::SetFile(SNDFILE* file)
{
  this->file = file;

  ID.Set(file->GetID()->Get());

  this->channels = file->GetChannels();
  this->freq = file->GetSampleRate();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALELEMENTSTREAM::ClearBuffers()
* @brief      ClearBuffers
* @ingroup    SOUND
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALELEMENTSTREAM::ClearBuffers()
{
  XLIST<SNDOPENALBUFFER*>::XITERATOR it;

  for(it = queuedbuffers.Begin(); it != queuedbuffers.End(); it++)
    {
      SNDOPENALBUFFER* buffer = *it;

      source->UnQueue(buffer);
      buffer->Destroy();

      delete buffer;
    }

  queuedbuffers.DeleteAll();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDOPENALSOURCE* SNDOPENALELEMENTSTREAM::GetSource()
* @brief      GetSource
* @ingroup    SOUND
* 
* @return     SNDOPENALSOURCE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDOPENALSOURCE* SNDOPENALELEMENTSTREAM::GetSource()
{ 
  return source;          
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALELEMENTSTREAM::SetSource(SNDOPENALSOURCE* source)
* @brief      SetSource
* @ingroup    SOUND
* 
* @param[in]  source : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALELEMENTSTREAM::SetSource(SNDOPENALSOURCE* source)
{ 
  this->source = source;  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALELEMENTSTREAM::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    SOUND
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALELEMENTSTREAM::Clean()
{
  totalbuffers  = 0;
  source        = NULL;
}


#pragma endregion
