/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       SNDOpenALElement.cpp
* 
* @class      SNDOPENALELEMENT
* @brief      Sound OpenAL element class
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

#include "SNDOpenALElement.h"

#include "SNDOpenALSource.h"
#include "SNDOpenALBuffer.h"
#include "SNDFile.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDOPENALELEMENT::SNDOPENALELEMENT(XPATH* xpath)
* @brief      Constructor
* @ingroup    SOUND
* 
* @param[in]  XPATH* : 
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDOPENALELEMENT::SNDOPENALELEMENT(XPATH* xpath)
{
  Clean();

  buffer  = new SNDOPENALBUFFER();
  if(buffer)
    {
      buffer->Generate();
    }

  volume  = 1.0f;
  pitch   = 1.0f;

  sources.SetIsMulti(false);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDOPENALELEMENT::~SNDOPENALELEMENT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    SOUND
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDOPENALELEMENT::~SNDOPENALELEMENT()
{
  if(buffer)
    {
      buffer->Destroy();
      delete buffer;
    }

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDOPENALELEMENT::GetLoop()
* @brief      GetLoop
* @ingroup    SOUND
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDOPENALELEMENT::GetLoop()
{ 
  return this->loop;      
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALELEMENT::SetLoop(bool loop)
* @brief      SetLoop
* @ingroup    SOUND
* 
* @param[in]  loop : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALELEMENT::SetLoop(bool loop)
{
  this->loop = loop;

  SNDOPENALSOURCE* source = GetSource();

  if(source)
    {
      source->SetLoop(loop);
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         float SNDOPENALELEMENT::GetVolume()
* @brief      GetVolume
* @ingroup    SOUND
* 
* @return     float : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
float SNDOPENALELEMENT::GetVolume()
{ 
  return volume;          
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALELEMENT::SetVolume(float volume)
* @brief      SetVolume
* @ingroup    SOUND
* 
* @param[in]  volume : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALELEMENT::SetVolume(float volume)
{
  this->volume = volume;

  SNDOPENALSOURCE* source = GetSource();

  if(source)
    {
      source->SetVolume(volume);
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         float SNDOPENALELEMENT::GetPitch()
* @brief      GetPitch
* @ingroup    SOUND
* 
* @return     float : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
float SNDOPENALELEMENT::GetPitch()
{ 
  return pitch;           
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALELEMENT::SetPitch(float pitch)
* @brief      SetPitch
* @ingroup    SOUND
* 
* @param[in]  pitch : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALELEMENT::SetPitch(float pitch)
{
  this->pitch = pitch;

  SNDOPENALSOURCE* source = GetSource();

  if(source)
    {
      source->SetPitch(pitch);
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALELEMENT::SetFile(SNDFILE* file)
* @brief      SetFile
* @ingroup    SOUND
* 
* @param[in]  file : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALELEMENT::SetFile(SNDFILE* file)
{
  this->file = file;

  buffer->Upload(file->GetChannels(), file->GetData()->Get(), file->GetData()->GetSize(), file->GetSampleRate());

  ID.Set(file->GetID()->Get());
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALELEMENT::AddSource(SNDOPENALSOURCE* source)
* @brief      AddSource
* @ingroup    SOUND
* 
* @param[in]  source : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALELEMENT::AddSource(SNDOPENALSOURCE* source)
{
  sources.Add(source);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALELEMENT::SetSource(SNDOPENALSOURCE* source)
* @brief      SetSource
* @ingroup    SOUND
* 
* @param[in]  source : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALELEMENT::SetSource(SNDOPENALSOURCE* source)
{
  if(source != NULL)
    {
      sources.Add(source);
      lastsource = source;
    }
   else
    {
      XDWORD size = sources.GetSize();
      for(XDWORD i = 0; i < size; i++)
        {
          if(sources.FastGet(i) == source)
            {
              sources.DeleteIndex(i);
              return;
            }
        }
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDOPENALSOURCE* SNDOPENALELEMENT::GetSource()
* @brief      GetSource
* @ingroup    SOUND
* 
* @return     SNDOPENALSOURCE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDOPENALSOURCE* SNDOPENALELEMENT::GetSource()
{
  SNDOPENALSOURCE* ret = NULL;

  XDWORD size = sources.GetSize();

  for(XDWORD i = 0; i < size; i++)
    {
      if(sources.FastGet(i)->GetElement() == this)
        {
          return sources.FastGet(i);
        }
    }

  return ret;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDOPENALBUFFER* SNDOPENALELEMENT::GetBuffer()
* @brief      GetBuffer
* @ingroup    SOUND
* 
* @return     SNDOPENALBUFFER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDOPENALBUFFER* SNDOPENALELEMENT::GetBuffer()
{ 
  return this->buffer;    
}

 
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALELEMENT::Queue()
* @brief      Queue
* @ingroup    SOUND
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALELEMENT::Queue()
{
  //GetSource()->Play(buffer);
  lastsource->Play(buffer);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALELEMENT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    SOUND
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALELEMENT::Clean()
{
  buffer    = NULL;
  loop      = false;
  volume    = 0.0f;
  pitch     = 0.0f;
}


#pragma endregion



