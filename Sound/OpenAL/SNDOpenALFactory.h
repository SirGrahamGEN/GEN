/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       SNDOpenALFactory.h
* 
* @class      SNDOPENALFACTORY
* @brief      Sound OpenAL Factory class
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

#ifndef _SNDOPENALFACTORY_H_
#define _SNDOPENALFACTORY_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "AL/al.h"
#include "AL/alc.h"

#include "SNDFactory.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

class XFACTORY;
class XPATHS;
class SNDFACTORY;
class SNDELEMENT;
class SNDSOURCE;
class SNDSTREAMELEMENT;
class SNDINSTANCE;
class SNDOPENALSOURCE;
class SNDOPENALELEMENT;
class SNDOPENALELEMENTSTREAM;

class SNDOPENALFACTORY : public SNDFACTORY
{
  public:
                                              SNDOPENALFACTORY          ();
    virtual                                  ~SNDOPENALFACTORY          ();

    virtual float                             Volume_Get                ();
    virtual bool                              Volume_Set                (float mastervolume);    

    virtual SNDELEMENT*                       Element_Add               (XCHAR* pathfile, XCHAR* ID = NULL, bool instream = false);
    virtual SNDELEMENT*                       Element_Get               (XCHAR* ID, bool instream = false);
    virtual bool                              Element_Del               (SNDELEMENT* element);
        
    virtual SNDINSTANCE*                      Sound_Play                (SNDELEMENT* element);
    virtual bool                              Sound_Stop                (SNDELEMENT* element);
    virtual SNDINSTANCE*                      Sound_Pause               (SNDELEMENT* element); 
    virtual bool                              Sound_IsAnyPlaying        ();
    virtual bool                              Sound_StopAll             ();
    virtual bool                              Sound_Note                (float frecuency, float duration);
   
    virtual void                              Update                    ();

    virtual SNDSTREAMELEMENT*                 GetStreamer               ();
            
    static void                               ThreadStreaming           (void* param);

  protected:

    ALCdevice*                                device;
    ALCcontext*                               context;
    float                                     mastervolume;
  
  private:
   
    void                                      Clean                     ();

    bool                                      isinit;
   
    XVECTOR<SNDOPENALSOURCE*>                 sources;
    XVECTOR<SNDOPENALELEMENT* >               playqueue;

    XVECTOR<SNDOPENALELEMENT*>                loadedfiles;
    XVECTOR<SNDOPENALELEMENTSTREAM*>          elementsstream;

    XVECTOR<SNDELEMENT*>                      deletequeue;

    XDWORD                                    maxchannels;

    XTHREAD*                                  streamthread;
    XMUTEX*                                   streammutex;                                               
};

#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

