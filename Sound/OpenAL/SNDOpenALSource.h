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

#include "SNDOpenALBuffer.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

class SNDOPENALSOURCE 
{  
  public:                              
                                SNDOPENALSOURCE                     ();
    virtual                    ~SNDOPENALSOURCE                     ();
    
    SNDOPENALBUFFER*            GetBuffer                           ();

    void                        Stop                                ();
    void                        Pause                               ();
    void                        UnPause                             ();

    bool                        IsPLaying                           ();
    bool                        IsStopped                           ();
    bool                        IsPaused                            ();

    void                        SetInLoop                           (bool inloop);

    int                         GetVolume                           ();
    bool                        SetVolume                           (int volume);

    float                       GetPitch                            ();
    void                        SetPitch                            (float pitch);
     
    void                        Play                                ();
    void                        ResetPlay                           ();


    // In revision

    void                        SetSecondsOffset                    (float seconds);
    void                        SetSamplesOffset                    (int samples);

    void                        SetAquired                          (bool aquired);
    bool                        IsAquired                           ();

    void                        Aquire                              ();
    void                        Release                             ();  

    void                        Queue                               ();
    void                        UnQueue                             ();

    int                         GetQueueLength                      ();
    int                         GetProcessedBuffers                 ();



  protected:

    ALuint                      source;
    SNDOPENALBUFFER             albuffer;
    
    bool                        isplaying;
    bool                        aquired;
    
  private:
  
    void                        Clean                               ();    
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif
