/**-------------------------------------------------------------------------------------------------------------------
*
* @file       SNDSource_OpenAL.h
*
* @class      SNDSOURCE_OPENAL
* @brief      Sound Open AL source class
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

#ifndef _SNDSOURCE_OPENAL_H_
#define _SNDSOURCE_OPENAL_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <stdlib.h>


#include <al.h>
#include <alc.h>

#include "XList.h"

#include "SNDSource.h"


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class SNDBUFFER_OPENAL;
class SNDELEMENT_OPENAL;
class SNDFACTORY_OPENAL;



class SNDSOURCE_OPENAL : public SNDSOURCE
{
  friend class SNDFACTORY_OPENAL;
  friend class SNDELEMENT_OPENAL;
  friend class SNDSTREAMELEMENT_OPENAL;

  public:

    void                        Stop                                ();
    void                        Pause                               ();
    void                        UnPause                             ();

    void                        SetLoop                             (bool loop);

    bool                        IsPLaying                           ();
    bool                        IsStopped                           ();
    bool                        IsPaused                            ();

    float                       GetVolume                           ();
    void                        SetVolume                           (float volume);
    
    float                       GetPitch                            ();
    void                        SetPitch                            (float pitch);
    
    SNDELEMENT*                 GetElement                          ();
    void                        SetElement                          (SNDELEMENT* element);
    

    void                        SetSecondsOffset                    (float seconds);
    void                        SetSamplesOffset                    (int samples);

    void                        SetAquired                          (bool aquired);
    bool                        IsAquired                           ();

    void                        Aquire                              ();
    void                        Release                             ();

  protected:

    ALuint                      source;
    
    bool                        isplaying;
    bool                        aquired;

    XLIST<SNDBUFFER_OPENAL*>    bufferlist;
    
  private:
                                SNDSOURCE_OPENAL                     ();
    virtual                    ~SNDSOURCE_OPENAL                     ();

    void                        Play                                ();
    void                        Play                                (SNDBUFFER_OPENAL* buffer);
    void                        Queue                               (SNDBUFFER_OPENAL* buffer);
    void                        UnQueue                             (SNDBUFFER_OPENAL* buffer);

    int                         GetQueueLength                      ();
    int                         GetProcessedBuffers                 ();

    void                        Clean                               ();

    
};

/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif


