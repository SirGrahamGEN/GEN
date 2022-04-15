/**-------------------------------------------------------------------------------------------------------------------
*
* @file       SNDBuffer_OpenAL.cpp
*
* @class      SNDBUFFER_OPENAL
* @brief      Sound Open AL Buffer class
* @ingroup    PLATFORM_COMMON
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

#include "SNDBuffer_OpenAL.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDBUFFER_OPENAL::SNDBUFFER_OPENAL()
* @brief      Constructor
* @ingroup    PLATFORM_COMMON
*
* @return     Does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
SNDBUFFER_OPENAL::SNDBUFFER_OPENAL()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SNDBUFFER_OPENAL::~SNDBUFFER_OPENAL()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_COMMON
*
* @return     Does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
SNDBUFFER_OPENAL::~SNDBUFFER_OPENAL()
{
  Clean();
}


    
/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         ALuint SNDBUFFER_OPENAL::GetHandle()
* @brief      GetHandle
* @ingroup    PLATFORM_COMMON
*
* @return     ALuint : 
*
*---------------------------------------------------------------------------------------------------------------------*/
ALuint SNDBUFFER_OPENAL::GetHandle()
{ 
  return buffer; 
}

 

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDBUFFER_OPENAL::Generate()
* @brief      Generate
* @ingroup    PLATFORM_COMMON
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SNDBUFFER_OPENAL::Generate()
{
  alGenBuffers(1, &buffer);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDBUFFER_OPENAL::Destroy()
* @brief      Destroy
* @ingroup    PLATFORM_COMMON
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SNDBUFFER_OPENAL::Destroy()
{
  alDeleteBuffers(1, &buffer);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SNDBUFFER_OPENAL::Upload(XWORD channels, void* data, XDWORD size, XWORD freq)
* @brief      Upload
* @ingroup    PLATFORM_COMMON
*
* @param[in]  channels : 
* @param[in]  data : 
* @param[in]  size : 
* @param[in]  freq : 
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SNDBUFFER_OPENAL::Upload(XWORD channels, void* data, XDWORD size, XWORD freq)
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
* @fn         void SNDBUFFER_OPENAL::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_COMMON
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void SNDBUFFER_OPENAL::Clean()
{
  buffer = 0;
}


