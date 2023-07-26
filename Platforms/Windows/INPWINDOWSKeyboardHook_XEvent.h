/**-------------------------------------------------------------------------------------------------------------------
*
* @file       INPWINDOWSKeyboardHook_XEvent.h
*
* @class      INPWINDOWSKEYBOARDHOOK_XEVENT
* @brief      eXtended Drive Image Mamanger Event class
* @ingroup    XUTILS
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

#ifndef _INPWINDOWSKEYBOARDHOOK_XEVENT_H_
#define _INPWINDOWSKEYBOARDHOOK_XEVENT_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XEvent.h"
#include "XSubject.h"


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/


enum INPWINDOWSKEYBOARDHOOK_XEVENT_TYPE
{
  INPWINDOWSKEYBOARDHOOK_XEVENT_TYPE_UNKNOWN          = XEVENT_TYPE_INPUT_CAPTURE ,
  INPWINDOWSKEYBOARDHOOK_XEVENT_TYPE_PRESSKEY                                     ,
  INPWINDOWSKEYBOARDHOOK_XEVENT_TYPE_UNPRESSKEY
};


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XTIMER;
class XPUBLISHER;


class INPWINDOWSKEYBOARDHOOK_XEVENT : public XEVENT
{
  public:
                                INPWINDOWSKEYBOARDHOOK_XEVENT   (XSUBJECT* subject, XDWORD type = INPWINDOWSKEYBOARDHOOK_XEVENT_TYPE_UNKNOWN, XDWORD family = XEVENT_TYPE_INPUT_CAPTURE);
    virtual                    ~INPWINDOWSKEYBOARDHOOK_XEVENT   ();

    XDWORD                      GetVKCode                       (); 
    void                        SetVKCode                       (XDWORD vkcode); 
   
    XWORD                       GetScanCode                     ();
    void                        SetScanCode                     (XWORD scancode);

    XDWORD                      GetFlags                        ();
    void                        SetFlags                        (XWORD flags);

    bool                        IsKeyLocked                     ();           
    void                        SetIsKeyLocked                  (bool iskeylocked);
   
  private:

    void                        Clean                           ();

    XDWORD                      vkcode;
    XWORD                       scancode;
    XDWORD                      flags;
    bool                        iskeylocked;
};


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif


