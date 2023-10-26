/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       SNDInstanceStream.cpp
* 
* @class      SNDINSTANCESTREAM
* @brief      Sound Instance Stream class
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

#include "SNDInstanceStream.h"

#include "XTrace.h"

#include "SNDElementStream.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------

@fn         SNDINSTANCESTREAM::SNDINSTANCESTREAM(SNDSOURCE* source, SNDELEMENT* element)
@brief      Constructor
@ingroup    SOUND

@param[in]  SNDSOURCE* : 
@param[in]  SNDELEMENT* element : 

@return     Does not return anything. 

--------------------------------------------------------------------------------------------------------------------*/
SNDINSTANCESTREAM::SNDINSTANCESTREAM(SNDSOURCE* source, SNDELEMENT* element) : SNDINSTANCE(source, element)
{
  Clean();

  isplaying = true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDINSTANCESTREAM::~SNDINSTANCESTREAM()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    SOUND
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDINSTANCESTREAM::~SNDINSTANCESTREAM()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SNDINSTANCESTREAM::Update()
* @brief      Update
* @ingroup    SOUND
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SNDINSTANCESTREAM::Update()
{
  /*  
  // buffer in here or in the constructor
  // in here, and don't start playing until the minimum amount has been buffered
  // also, need to check if framereader is EOS, as in that case we need to stopSND
  if(element)
    {
      if(element->GetFile())
        {
          if(element->GetFile()->GetFrameReader()->IsEndOfStream())
            {
              // need to comunicate that we stopped(but we didn't stop sounding!)
              // need to detect when both the stream finished reading and when it finished playing!
              isplaying = source->IsPLaying();
            }

          if(buffered < 2.0f)
            {
              SNDFILE* file = element->GetFile();

              MEDIAFRAMEREADER* framereader = file->GetFrameReader();
              SNDCODEC* codec = (SNDCODEC*)file->GetCodec();

              MEDIAPACKET packet;
              framereader->ReadFrame(&packet);
              XBUFFER output(false);
              codec->DecodePacket(&output, &packet);
              buffered += (float)packet.duration;

              // queue the buffer in the source
              SNDSTREAMELEMENT* streamelement = (SNDSTREAMELEMENT*)element;
              streamelement->AddData(output.GetSize(), output.Get());
            }
          else
            {
              SNDSTREAMELEMENT* streamelement = (SNDSTREAMELEMENT*)element;

              if(!hasbuffered)
                {
                  // tell play to the source(we just finished queuing the basic data)
                  streamelement->Play();
                  isplaying = true;
                }

              hasbuffered = true;

              SNDFILE* file = element->GetFile();
              MEDIAFRAMEREADER* framereader = file->GetFrameReader();
              SNDCODEC* codec = (SNDCODEC*)file->GetCodec();

              MEDIAPACKET packet;
              framereader->ReadFrame(&packet);
              XBUFFER output(false);
              codec->DecodePacket(&output, &packet);
              buffered += (float)packet.duration;

              // queue the buffer in the source

              streamelement->AddData(output.GetSize(), output.Get());
            }
        }
      else
        {
          //if(element->duration
          if(element->GetDuration() > 0)
            {
              isplaying = source->IsPLaying();
            }
        }
    }

  */

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDINSTANCESTREAM::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    SOUND
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDINSTANCESTREAM::Clean()
{
  buffered      = 0.0f;
  hasbuffered   = false;
}


#pragma endregion

