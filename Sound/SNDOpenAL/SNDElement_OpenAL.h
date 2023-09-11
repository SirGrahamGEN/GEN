/**-------------------------------------------------------------------------------------------------------------------
*
* @file       SNDElement_OpenAL.h
*
* @class      SNDELEMENT_OPENAL
* @brief      Sound Open AL element class
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

#ifndef _SNDELEMENT_OPENAL_H_
#define _SNDELEMENT_OPENAL_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XVector.h"
#include "XPath.h"

#include "SNDElement.h"
#include "SNDFileOGG.h"
#include "SNDBuffer_OpenAL.h"
#include "SNDSource_OpenAL.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XFACTORY;
class SNDFILEOGG;
class SNDBUFFER_OPENAL;
class SNDSOURCE_OPENAL;


class SNDELEMENT_OPENAL : public SNDELEMENT
{
  friend class SNDFACTORY_OPENAL;

  public:

                                  SNDELEMENT_OPENAL                     (XPATH* xpath);
    virtual                      ~SNDELEMENT_OPENAL                     ();
                                  
    void                          AddSource                             (SNDSOURCE_OPENAL* source);
    void                          SetSource                             (SNDSOURCE_OPENAL* source);                                  
    SNDSOURCE_OPENAL*             GetSource                             ();
   
    bool                          GetLoop                               ();                              
    void                          SetLoop                               (bool loop);
    
    SNDBUFFER_OPENAL*             GetBuffer                             ();

    void                          SetVolume                             (float volume);
    float                         GetVolume                             ();

    void                          SetPitch                              (float pitch);
    float                         GetPitch                              ();
    virtual void                  SetFile                               (SNDFILE* file);
    

  private:

    void                          Queue                                 ();

    void                          Clean                                 ();

    SNDBUFFER_OPENAL*             buffer;

    XVECTOR<SNDSOURCE_OPENAL*>    sources;
    SNDSOURCE_OPENAL*             lastsource;

    XPATH*                        xpath;
    XSTRING                       ID;
};





/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif

