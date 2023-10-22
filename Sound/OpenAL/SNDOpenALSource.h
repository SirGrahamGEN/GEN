/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       SNDOpenALSource.h
* 
* @class      SNDOPENALSOURCE
* @brief      Sound Open AL source class
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

#ifndef _SNDOPENALSOURCE_H_
#define _SNDOPENALSOURCE_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include <stdlib.h>

#include "AL/al.h"
#include "AL/alc.h"

#include "XList.h"

#include "SNDSource.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

class SNDOPENALFACTORY;
class SNDOPENALBUFFER;
class SNDOPENALELEMENT;

class SNDOPENALSOURCE : public SNDSOURCE
{  
  friend SNDOPENALFACTORY;

  public:                              
                                SNDOPENALSOURCE                    ();
    virtual                    ~SNDOPENALSOURCE                    ();

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

    void                        Play                                ();
    void                        Play                                (SNDOPENALBUFFER* buffer);
    void                        Queue                               (SNDOPENALBUFFER* buffer);
    void                        UnQueue                             (SNDOPENALBUFFER* buffer);

    int                         GetQueueLength                      ();
    int                         GetProcessedBuffers                 ();

  protected:

    ALuint                      source;
    
    bool                        isplaying;
    bool                        aquired;

    XLIST<SNDOPENALBUFFER*>     bufferlist;
    
  private:
  
    void                        Clean                               ();    
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif
