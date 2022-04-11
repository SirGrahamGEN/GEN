/**-------------------------------------------------------------------------------------------------------------------
*
* @file       GRPScreen.h
*
* @class      GRPSCREEN
* @brief      Graphics Screen Class
* @ingroup    GRAPHIC
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

#ifndef _GRPSCREEN_H_
#define _GRPSCREEN_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

#include "XBase.h"
#include "XFactory.h"
#include "XVector.h"
#include "XEvent.h"
#include "XSubject.h"
#include "XPublisher.h"

#include "GRPProperties.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum GRPSCREENTYPE
{
  GRPSCREENTYPE_UNKNOW                        =  0  ,

  GRPSCREENTYPE_WINDOWS                             ,

  GRPSCREENTYPE_LINUX_FRAMEBUFFER                   ,
  GRPSCREENTYPE_LINUX_X11                           ,
  GRPSCREENTYPE_LINUX_DISPMAN                       ,

  GRPSCREENTYPE_ANDROID
};

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class GRPCANVAS;
class GRPVIEWPORT;
class GRPFRAMERATE;


class GRPSCREEN : public GRPPROPERTIES, public XSUBJECT
{
  public:
                                  GRPSCREEN                     ();
    virtual                      ~GRPSCREEN                     ();

    GRPSCREENTYPE                 GetType                       ();
    bool                          IsValid                       ();
    bool                          IsActive                      ();

    bool                          SetPropertys                  (int width, int height, float DPIs, int stride, GRPPROPERTYMODE mode);

    bool                          IsFullScreen                  ();
    void                          SetIsFullScreen               (bool isfullscreen);

    bool                          CreateBuffers                 ();
    bool                          DeleteBuffers                 ();
    XBYTE*                        GetBuffer                     ();


    virtual bool                  Create                        (bool show);
    virtual bool                  Update                        ();
    virtual bool                  Update                        (GRPCANVAS* canvas);
    virtual bool                  Delete                        ();
    virtual bool                  Resize                        (int width, int height);
    virtual bool                  IsShow                        ();
    virtual bool                  Show                          (bool active);
    virtual bool                  ShowCursor                    (bool active);
    virtual bool                  ShowTopMost                   (bool active);
    virtual void*                 GetHandle                     ();

    bool                          UpdateSize                    (int width, int height);

    XVECTOR<GRPVIEWPORT*>*        GetViewports                  ();
    GRPVIEWPORT*                  GetViewport                   (int index);
    GRPVIEWPORT*                  GetViewport                   (XCHAR* ID);
    bool                          CreateViewport                (XCHAR* ID, float posx, float posy, float width, float height, XDWORD canvasposx, XDWORD canvasposy, XDWORD canvaswidth, XDWORD canvasheight);
    bool                          UpdateViewports               ();
    bool                          DeleteViewport                (GRPVIEWPORT* viewport);
    bool                          DeleteAllViewports            ();
    
    GRPFRAMERATE*                 GetFrameRate                  ();

  protected:    

    GRPSCREENTYPE                 type;
    bool                          isvalid;
    bool                          isactive;
    bool                          isfullscreen;

    XBYTE*                        buffer;
    XDWORD                        buffersize;

    bool                          isblockclose;

    XVECTOR<GRPVIEWPORT*>         viewports;  

    XDWORD                        index_maincanvas;
    GRPCANVAS*                    maincanvas;    
    
    GRPFRAMERATE*                 framerate;

    bool                          isshow;

  private:

    void                          Clean                         ();
};


//---- INLINE FUNCTIONS --------------------------------------------------------------------


#endif

