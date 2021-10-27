/**-------------------------------------------------------------------------------------------------------------------
*
* @file       SNDElement.h
*
* @class      SNDELEMENT
* @brief      Sound Element class
* @ingroup    SOUND
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

#ifndef _SNDELEMENT_H_
#define _SNDELEMENT_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XBase.h"
#include "XString.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

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


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/


class SNDFILE;

class SNDELEMENT
{
  public:
                              SNDELEMENT            ();
    virtual                  ~SNDELEMENT            ();

    XSTRING*                  GetID                 ();

    virtual void              SetLoop               (bool loop);
    virtual bool              GetLoop               ();

    virtual void              SetVolume             (float volume);
    virtual float             GetVolume             ();

    virtual void              SetPitch              (float pitch);
    virtual float             GetPitch              ();

    void                      SetDuration           (float duration);
    float                     GetDuration           ();

    void                      SetSamples            (int samples);
    int                       GetSamples            ();

    bool                      IsStream              ();

    virtual void              SetFile               (SNDFILE* file);
    SNDFILE*                  GetFile               ();

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




/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif
