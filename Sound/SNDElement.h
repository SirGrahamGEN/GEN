/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       SNDElement.h
* 
* @class      SNDELEMENT
* @brief      Sound Element class
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

#ifndef _SNDELEMENT_H_
#define _SNDELEMENT_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XBase.h"
#include "XString.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

enum SNDELEMENT_TYPE
{
  SNDELEMENT_TYPE_UNKNOWN       = 0 ,
  SNDELEMENT_TYPE_FILE              ,
  SNDELEMENT_TYPE_NOTE              ,
};

enum SNDELEMENT_STATUS
{
  SNDELEMENT_STATUS_STOP        = 0 ,
  SNDELEMENT_STATUS_PLAY            ,
  SNDELEMENT_STATUS_PAUSE           ,
};

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

class SNDFILE;

class SNDELEMENT
{
  public:
                              SNDELEMENT            ();
    virtual                  ~SNDELEMENT            ();

    XSTRING*                  GetID                 ();
    
    virtual bool              GetLoop               ();
    virtual void              SetLoop               (bool loop);
    
    virtual float             GetVolume             ();
    virtual void              SetVolume             (float volume);
        
    virtual float             GetPitch              ();
    virtual void              SetPitch              (float pitch); 
    
    bool                      IsStream              ();
    
    SNDFILE*                  GetFile               ();
    virtual void              SetFile               (SNDFILE* file);
    
    float                     GetDuration           ();
    void                      SetDuration           (float duration);

    int                       GetSamples            ();    
    void                      SetSamples            (int samples);
    
  protected:

    XSTRING                   ID;
    SNDFILE*                  file;

    bool                      loop;
    float                     volume;
    float                     pitch;

    float                     duration;
    int                       samples;
    bool                      isstream;

  private:

    void                      Clean                 ();
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

