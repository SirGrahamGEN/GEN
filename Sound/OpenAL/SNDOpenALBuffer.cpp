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

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "SNDOpenALBuffer.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDOPENALBUFFER::SNDOPENALBUFFER()
* @brief      Constructor
* @ingroup    SOUND
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDOPENALBUFFER::SNDOPENALBUFFER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDOPENALBUFFER::~SNDOPENALBUFFER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    SOUND
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDOPENALBUFFER::~SNDOPENALBUFFER()
{
  Clean();
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         ALuint SNDOPENALBUFFER::GetHandle()
* @brief      GetHandle
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
* @fn         void SNDOPENALBUFFER::Generate()
* @brief      Generate
* @ingroup    SOUND
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALBUFFER::Generate()
{
  alGenBuffers(1, &buffer);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALBUFFER::Destroy()
* @brief      Destroy
* @ingroup    SOUND
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALBUFFER::Destroy()
{
  alDeleteBuffers(1, &buffer);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALBUFFER::Upload(XWORD channels, void* data, XDWORD size, XWORD freq)
* @brief      Upload
* @ingroup    SOUND
* 
* @param[in]  channels : 
* @param[in]  data : 
* @param[in]  size : 
* @param[in]  freq : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALBUFFER::Upload(XWORD channels, void* data, XDWORD size, XWORD freq)
{
  ALenum format = AL_FORMAT_MONO16;

  if(channels == 2)
    {
      format = AL_FORMAT_STEREO16;
    }

  alBufferData(buffer, format, data, size, freq);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDOPENALBUFFER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    SOUND
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDOPENALBUFFER::Clean()
{
  buffer = 0;
}


#pragma endregion

