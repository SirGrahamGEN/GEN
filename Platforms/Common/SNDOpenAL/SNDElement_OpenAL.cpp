/**-------------------------------------------------------------------------------------------------------------------
*
* @file       SNDOpenALElement.cpp
*
* @class      SNDELEMENT_OPENAL
* @brief      Sound Open AL element class
* @ingroup    PLATFORM_COMMON
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

#include "SNDSource_OpenAL.h"
#include "SNDBuffer_OpenAL.h"
#include "SNDFileOGG.h"

#include "SNDElement_OpenAL.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDELEMENT_OPENAL::SNDELEMENT_OPENAL(XPATH* xpath)
* @brief      Constructor
* @ingroup    PLATFORM_COMMON
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  XPATH* : 
*
* @return     Does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
SNDELEMENT_OPENAL::SNDELEMENT_OPENAL(XPATH* xpath)
{
  Clean();


  buffer  = new SNDBUFFER_OPENAL();
  buffer->Generate();
  volume  = 1.0f;
  pitch   = 1.0f;
  sources.SetIsMulti(false);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDELEMENT_OPENAL::~SNDELEMENT_OPENAL()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_COMMON
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     Does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
SNDELEMENT_OPENAL::~SNDELEMENT_OPENAL()
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
* @fn         void SNDELEMENT_OPENAL::AddSource(SNDSOURCE_OPENAL* source)
* @brief      AddSource
* @ingroup    PLATFORM_COMMON
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  source : 
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SNDELEMENT_OPENAL::AddSource(SNDSOURCE_OPENAL* source)
{
  sources.Add(source);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDELEMENT_OPENAL::SetSource(SNDSOURCE_OPENAL* source)
* @brief      SetSource
* @ingroup    PLATFORM_COMMON
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  source : 
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SNDELEMENT_OPENAL::SetSource(SNDSOURCE_OPENAL* source)
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
* @fn         SNDSOURCE_OPENAL* SNDELEMENT_OPENAL::GetSource()
* @brief      GetSource
* @ingroup    PLATFORM_COMMON
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     SNDSOURCE_OPENAL* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
SNDSOURCE_OPENAL* SNDELEMENT_OPENAL::GetSource()
{
  SNDSOURCE_OPENAL* ret = NULL;

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
* @fn         bool SNDELEMENT_OPENAL::GetLoop()
* @brief      GetLoop
* @ingroup    PLATFORM_COMMON
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SNDELEMENT_OPENAL::GetLoop()                              
{ 
  return this->loop;      
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDELEMENT_OPENAL::SetLoop(bool loop)
* @brief      SetLoop
* @ingroup    PLATFORM_COMMON
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  loop : 
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SNDELEMENT_OPENAL::SetLoop(bool loop)
{
  this->loop = loop;

  SNDSOURCE_OPENAL* source = GetSource();

  if(source)
    {
      source->SetLoop(loop);
    }
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDBUFFER_OPENAL* SNDELEMENT_OPENAL::GetBuffer()
* @brief      GetBuffer
* @ingroup    PLATFORM_COMMON
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     SNDBUFFER_OPENAL* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
SNDBUFFER_OPENAL* SNDELEMENT_OPENAL::GetBuffer()                              
{ 
  return this->buffer;    
}


    
/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float SNDELEMENT_OPENAL::GetVolume()
* @brief      GetVolume
* @ingroup    PLATFORM_COMMON
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     float : 
*
*---------------------------------------------------------------------------------------------------------------------*/
float SNDELEMENT_OPENAL::GetVolume()                              
{ 
  return volume;          
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDELEMENT_OPENAL::SetVolume(float volume)
* @brief      SetVolume
* @ingroup    PLATFORM_COMMON
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  volume : 
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SNDELEMENT_OPENAL::SetVolume(float volume)
{
  this->volume = volume;

  SNDSOURCE_OPENAL* source = GetSource();

  if(source)
    {
      source->SetVolume(volume);
    }
}


   
/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float SNDELEMENT_OPENAL::GetPitch()
* @brief      GetPitch
* @ingroup    PLATFORM_COMMON
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     float : 
*
*---------------------------------------------------------------------------------------------------------------------*/
float SNDELEMENT_OPENAL::GetPitch()
{ 
  return pitch;           
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDELEMENT_OPENAL::SetPitch(float pitch)
* @brief      SetPitch
* @ingroup    PLATFORM_COMMON
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  pitch : 
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SNDELEMENT_OPENAL::SetPitch(float pitch)
{
  this->pitch = pitch;

  SNDSOURCE_OPENAL* source = GetSource();

  if(source)
    {
      source->SetPitch(pitch);
    }
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDELEMENT_OPENAL::SetFile(SNDFILE* file)
* @brief      SetFile
* @ingroup    PLATFORM_COMMON
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  file : 
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SNDELEMENT_OPENAL::SetFile(SNDFILE* file)
{
  this->file = file;

  buffer->Upload(file->GetChannels(), file->GetData()->Get(), file->GetData()->GetSize(), file->GetSampleRate());

  ID.Set(file->GetID()->Get());
}


 
/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDELEMENT_OPENAL::Queue()
* @brief      Queue
* @ingroup    PLATFORM_COMMON
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SNDELEMENT_OPENAL::Queue()
{
  //GetSource()->Play(buffer);
  lastsource->Play(buffer);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDELEMENT_OPENAL::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_COMMON
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SNDELEMENT_OPENAL::Clean()
{
  buffer    = NULL;
  loop      = false;
  volume    = 0.0f;
  pitch     = 0.0f;
}




