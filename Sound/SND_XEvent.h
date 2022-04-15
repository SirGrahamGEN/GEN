/**-------------------------------------------------------------------------------------------------------------------
*
* @file       SND_XEvent.h
*
* @class      SND_XEVENT
* @brief      Sound eXtended event class
* @ingroup    SOUND
*
* @copyright  GEN Group. All right reserved.
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

#ifndef _SND_XEVENT_H_
#define _SND_XEVENT_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XEvent.h"
#include "XString.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum SND_XEVENT_TYPE
{
  SND_XEVENT_TYPE_UNKNOWN          = XEVENT_TYPE_SOUND ,
  SND_XEVENT_TYPE_STOP                                 ,
  SND_XEVENT_TYPE_PLAY                                 ,  
};

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class SNDELEMENT;
class SNDSOURCE;
class SNDINSTANCE;

class SND_XEVENT : public XEVENT
{
  public:

                              SND_XEVENT            (XSUBJECT* subject, XDWORD type = SND_XEVENT_TYPE_UNKNOWN, XDWORD family = XEVENT_TYPE_SOUND);
    virtual                  ~SND_XEVENT            ();

    SND_XEVENT_TYPE           GetType               ();
    void                      SetType               (SND_XEVENT_TYPE type);
        
    XSTRING*                  GetID                 ();

    SNDELEMENT*               GetElement            ();
    void                      SetElement            (SNDELEMENT* element);
    
    SNDSOURCE*                GetSource             ();
    void                      SetSource             (SNDSOURCE* source);    

    SNDINSTANCE*              GetInstance           ();
    void                      SetInstance           (SNDINSTANCE* instance);
    
  protected:

    SND_XEVENT_TYPE           type;
    XSTRING                   ID;
    SNDELEMENT*               element;
    SNDSOURCE*                source;
    SNDINSTANCE*              instance;

  private:

    void                      Clean                 ();
                              
};


/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif


