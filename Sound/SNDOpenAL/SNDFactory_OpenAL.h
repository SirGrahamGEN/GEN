/**-------------------------------------------------------------------------------------------------------------------
*
* @file       SNDFactoryOpenAL.h
*
* @class      SNDFACTORY_OPENAL
* @brief      Sound OpenAL factory class
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

#ifndef _SNDFACTORY_OPENAL_H_
#define _SNDFACTORY_OPENAL_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <al.h>
#include <alc.h>

#include "XString.h"
#include "XVector.h"
#include "XBase.h"
#include "XSubject.h"

#include "SNDFactory.h"
#include "SND_XEvent.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XFACTORY;
class XPATHS;

class SNDELEMENT;
class SNDSOURCE;
class SNDFACTORY;
class SNDSTREAMELEMENT;
class SNDINSTANCE;
class SNDSOURCE_OPENAL;
class SNDELEMENT_OPENAL;
class SNDSTREAMELEMENT_OPENAL;


class SNDFACTORY_OPENAL : public SNDFACTORY
{
  public:

                                              SNDFACTORY_OPENAL         ();
    virtual                                  ~SNDFACTORY_OPENAL         ();


    bool                                      Beep                      (float frecuency, float duration);

    SNDELEMENT*                               Element_Add               (XPATH& xpathfile, XCHAR* ID = NULL, bool instream = false);
    SNDELEMENT*                               Element_Get               (XCHAR* ID, bool instream = false);
    bool                                      Element_Del               (SNDELEMENT* element);
        
    virtual SNDINSTANCE*                      PlaySound                 (SNDELEMENT* element);
    virtual bool                              StopSound                 (SNDELEMENT* element);
    virtual SNDINSTANCE*                      PauseSound                (SNDELEMENT* element); 
    bool                                      IsAnyPlaying              ();
    bool                                      StopAll                   ();

    float                                     GetMasterVolume           ();
    bool                                      SetMasterVolume           (float mastervolume);
   
    virtual SNDSTREAMELEMENT*                 GetStreamer               ();

    void                                      Update                    ();
            
    static void                               ThreadStreaming           (void* param);

  protected:

    ALCdevice*                                device;
    ALCcontext*                               context;
    float                                     mastervolume;
  

  private:
   
    void                                      Clean                     ();

    bool                                      isinit;
   
    XVECTOR<SNDSOURCE_OPENAL*>                sources;
    XVECTOR<SNDELEMENT_OPENAL*>               playqueue;

    XVECTOR<SNDELEMENT_OPENAL*>               loadedfiles;
    XVECTOR<SNDSTREAMELEMENT_OPENAL*>         streamelements;

    XVECTOR<SNDELEMENT*>                      deletequeue;

    XDWORD                                    maxchannels;

    XTHREAD*                                  streamthread;
    XMUTEX*                                   streammutex;
                                               
};




/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif


