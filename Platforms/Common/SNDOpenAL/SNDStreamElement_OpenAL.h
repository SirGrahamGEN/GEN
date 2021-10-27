/**-------------------------------------------------------------------------------------------------------------------
*
* @file       SNDStreamElement_OpenAL.h
*
* @class      SNDSTREAMELEMENT_OPENAL
* @brief      Sound Open AL Stream Element class
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

#ifndef _SNDSTREAMELEMENT_OPENAL_H_
#define _SNDSTREAMELEMENT_OPENAL_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XList.h"

#include "SNDStreamElement.h"
#include "SNDSource_OpenAL.h"


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class SNDBUFFER_OPENAL;
class SNDSOURCE_OPENAL;

class SNDSTREAMELEMENT_OPENAL : public SNDSTREAMELEMENT
{
  friend class SNDOPENAL;

  public:
                                      SNDSTREAMELEMENT_OPENAL                   ();
    virtual                          ~SNDSTREAMELEMENT_OPENAL                   ();

    virtual void                      Play                                      ();
    virtual void                      AddData                                   (XDWORD size, void* data);

    void                              SetSource                                 (SNDSOURCE_OPENAL* source);
    SNDSOURCE_OPENAL*                 GetSource                                 ();

    virtual void                      SetFile                                   (SNDFILE* file);
    void                              ClearBuffers                              ();

  protected:

    XLIST<SNDBUFFER_OPENAL*>          freebuffers;
    XLIST<SNDBUFFER_OPENAL*>          queuedbuffers;

    SNDSOURCE_OPENAL*                 source;

    XDWORD                            totalbuffers;
  
  private:

    void                              Clean                                     ();

};




/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif



