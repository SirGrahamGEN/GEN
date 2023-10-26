/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       SNDFactory.h
* 
* @class      SNDFACTORY
* @brief      Sound Factory class
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


#ifndef _SNDFACTORY_H_
#define _SNDFACTORY_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XPath.h"
#include "XSubject.h"

#include "SNDElement.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

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

    virtual bool                      Ini                         ();
    virtual bool  		    						Update										  ();
    virtual bool                      End                         ();

    virtual float                     Volume_Get                  ();
    virtual bool                      Volume_Set                  (float volume);    

    SNDELEMENT*                       Element_Add                 (XPATH& xpathfile, XSTRING& ID, bool instream = false);
    SNDELEMENT*                       Element_Add                 (XPATH& xpathfile, XCHAR* ID = NULL, bool instream = false);
    virtual SNDELEMENT*               Element_Add                 (XCHAR* pathfile, XCHAR* ID = NULL, bool instream = false);
    SNDELEMENT*                       Element_Get                 (XSTRING& ID, bool instream = false);
    virtual SNDELEMENT*               Element_Get                 (XCHAR* ID, bool instream = false);
    virtual bool                      Element_Del                 (SNDELEMENT* element);
    
    virtual SNDINSTANCE*              Sound_Play                  (SNDELEMENT* element);
    virtual bool                      Sound_Stop                  (SNDELEMENT* element);
    virtual SNDINSTANCE*              Sound_Pause                 (SNDELEMENT* element);
    virtual bool                      Sound_IsAnyPlaying          ();
    virtual bool                      Sound_StopAll               (); 
    virtual bool                      Sound_Note                  (float frecuency, float duration = 0.5f);  
       		
  private:

    void                              Clean                       ();

    static SNDFACTORY*                instance;
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif


