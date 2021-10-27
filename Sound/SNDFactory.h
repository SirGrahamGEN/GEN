/**-------------------------------------------------------------------------------------------------------------------
*
* @file       SNDFactory.h
*
* @class      SNDFACTORY
* @brief      Sound Factory class
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

#ifndef _SNDFACTORY_H_
#define _SNDFACTORY_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XString.h"
#include "XPath.h"
#include "XSubject.h"


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/



/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class SNDELEMENT;
class SNDINSTANCE;
class SNDFILE;

class SNDFACTORY : public XSUBJECT
{
  public:
                                      SNDFACTORY                  ();
    virtual                          ~SNDFACTORY                  ();

    static bool                       GetIsInstanced              ();
    static SNDFACTORY&                GetInstance                 ();
    static bool                       SetInstance                 (SNDFACTORY* instance);
    static bool                       DelInstance                 ();

    virtual bool                      Beep                        (float frecuency, float duration = 0.5f);  

    virtual SNDELEMENT*               Element_Add                 (XPATH& xpathfile, XSTRING& ID, bool instream = false);
    virtual SNDELEMENT*               Element_Add                 (XPATH& xpathfile, XCHAR* ID = NULL, bool instream = false);
    virtual SNDELEMENT*               Element_Get                 (XSTRING& namefile, bool instream = false);
    virtual SNDELEMENT*               Element_Get                 (XCHAR* namefile, bool instream = false);
    virtual bool                      Element_Del                 (SNDELEMENT* element);
    
    virtual SNDINSTANCE*              PlaySound                   (SNDELEMENT* element);
    virtual bool                      StopSound                   (SNDELEMENT* element);
    virtual SNDINSTANCE*              PauseSound                  (SNDELEMENT* element);
    virtual bool                      IsAnyPlaying                ();
    virtual bool                      StopAll                     ();
       
    virtual float                     GetMasterVolume             ();
    virtual bool                      SetMasterVolume             (float mastervolume);

		virtual void			    						Update										  ();

		virtual SNDFILE*								  CreateSoundFile							();
		virtual bool  										DeleteSoundFile							(SNDFILE* file);


  private:

    void                              Clean                     ();

    static SNDFACTORY*                instance;
        
};



/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif