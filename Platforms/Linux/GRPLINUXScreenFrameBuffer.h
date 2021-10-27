/**-------------------------------------------------------------------------------------------------------------------
*
* @file       GRPLINUXScreenFrameBuffer.h
*
* @class      GRPLINUXSCREENFRAMEBUFFER
* @brief      LINUX Frame Buffer Screen class
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @copyright  Copyright(c) 2008 - 2016 GEN Group.
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

#ifndef _GRPLINUXSCREENFRAMEBUFFER_H_
#define _GRPLINUXSCREENFRAMEBUFFER_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "GRPScreen.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define GRPLINUXSCREENFRAMEBUFFER_DEVICE    "/dev/fb0"

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class GRPLINUXSCREENFRAMEBUFFER : public GRPSCREEN
{
  public:
                                  GRPLINUXSCREENFRAMEBUFFER   ();
    virtual                      ~GRPLINUXSCREENFRAMEBUFFER   ();

    bool                          Create                      (bool show);

    bool                          Update                      ();
    bool                          Update                      (GRPCANVAS* canvas);
    bool                          Delete                      ();

    bool                          Resize                      (int width, int height);

    bool                          Show                        (bool active);
    bool                          ShowCursor                  (bool active);

    void*                         GetHandle                   ();

    int                           GetHandleFB                 ();

  private:

    bool                          ScreenResolution            (int width, int height);

    bool                          ClearScreen                 ();
    void                          Clean                       ();

    int                           handlefb;
};


/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif



