/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       SNDOpenALBuffer.cpp
* 
* @class      SNDOPENALBUFFER
* @brief      Sound OpenAL Buffer class
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

#include "SNDOpenALBuffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
* @fn         SNDOPENALBUFFER::SNDOPENALBUFFER()
* @brief      Constructor of class
* @ingroup    SOUND
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDOPENALBUFFER::SNDOPENALBUFFER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDOPENALBUFFER::~SNDOPENALBUFFER()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    SOUND
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDOPENALBUFFER::~SNDOPENALBUFFER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALBUFFER::Create()
* @brief      Create
* @ingroup    SOUND
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALBUFFER::Create()
{
  alGenBuffers(1, &buffer);

  xbuffer.Empty();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALBUFFER::Delete()
* @brief      Delete
* @ingroup    SOUND
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALBUFFER::Delete()
{
  alDeleteBuffers(1, &buffer);

  xbuffer.Empty();
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         ALuint SNDOPENALBUFFER::GetHandle()
* @brief      Get handle
* @ingroup    SOUND
* 
* @return     ALuint : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
ALuint SNDOPENALBUFFER::GetHandle()
{ 
  return buffer; 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDOPENALBUFFER::SetHandle(ALuint handle)
* @brief      Set handle
* @ingroup    SOUND
* 
* @param[in]  handle : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDOPENALBUFFER::SetHandle(ALuint handle)
{
  this->buffer = handle;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBUFFER* SNDOPENALBUFFER::GetXBuffer()
* @brief      Get X buffer
* @ingroup    SOUND
* 
* @return     XBUFFER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBUFFER* SNDOPENALBUFFER::GetXBuffer()
{
  return &xbuffer;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD SNDOPENALBUFFER::GenerateNote(XDWORD frequency, XDWORD duration, XDWORD samplerate)
* @brief      Generate note
* @ingroup    SOUND
* 
* @param[in]  frequency : 
* @param[in]  duration : 
* @param[in]  samplerate : 
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD SNDOPENALBUFFER::GenerateNote(XDWORD frequency, XDWORD duration, XDWORD samplerate)
{
  if(!frequency || !duration)
    {
      return false;
    }

  XDWORD size = (XDWORD)((duration/1000) * samplerate);  
  
  xbuffer.SetLocalHardwareUseLittleEndian(false);

  for(XDWORD c=0; c<size; c++)
    {      
      XWORD data = (short)(32760 * sin(2 * PI * c * frequency/samplerate));
      xbuffer.Add((XWORD)data);                     
    }

  return size;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDOPENALBUFFER::Assign(XWORD channels, size_t size, XDWORD samplerate)
* @brief      Assign
* @ingroup    SOUND
* 
* @param[in]  channels : 
* @param[in]  size : 
* @param[in]  samplerate : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDOPENALBUFFER::Assign(XWORD channels, size_t size, XDWORD samplerate)
{
  ALenum format = AL_FORMAT_MONO16;

  if(channels == 2)
    {
      format = AL_FORMAT_STEREO16;
    }

  alBufferData(buffer, format, (void*)xbuffer.Get(), (ALsizei)size, samplerate);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALBUFFER::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    SOUND
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALBUFFER::Clean()
{
  buffer = 0;
}


#pragma endregion

