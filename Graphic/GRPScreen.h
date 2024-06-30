/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       GRPScreen.h
* 
* @class      GRPSCREEN
* @brief      Graphics Screen Class
* @ingroup    GRAPHIC
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

#ifndef _GRPSCREEN_H_
#define _GRPSCREEN_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include <stdio.h>

#include "XBase.h"
#include "XFactory.h"
#include "XVector.h"
#include "XEvent.h"
#include "XSubject.h"
#include "XPublisher.h"

#include "GRPProperties.h"
#include "GRPRect.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


enum GRPSCREENTYPE
{
  GRPSCREENTYPE_UNKNOW                        =  0  ,

  GRPSCREENTYPE_WINDOWS                             ,

  GRPSCREENTYPE_LINUX_FRAMEBUFFER                   ,
  GRPSCREENTYPE_LINUX_X11                           ,
  GRPSCREENTYPE_LINUX_DISPMAN                       ,

  GRPSCREENTYPE_ANDROID
};


#define GRPSCREENSTYLE_NONE              0x00000000
#define GRPSCREENSTYLE_TITLE             0x00000001
#define GRPSCREENSTYLE_FULLSCREEN        0x00000002
#define GRPSCREENSTYLE_TRANSPARENT       0x00000004
#define GRPSCREENSTYLE_ONTOP             0x00000008
#define GRPSCREENSTYLE_NOICONTASKBAR     0x00000010

#define GRPSCREENSTYLE_DEFAULT           GRPSCREENSTYLE_TITLE


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class GRPCANVAS;
class GRPVIEWPORT;
class GRPFRAMERATE;
class GRPBITMAP;


class GRPSCREEN : public GRPPROPERTIES, public XSUBJECT
{
  public:
                                  GRPSCREEN                     ();
    virtual                      ~GRPSCREEN                     ();

    GRPSCREENTYPE                 GetType                       ();
    bool                          IsValid                       ();
    bool                          IsActive                      ();

    bool                          Style_Is                      (XDWORD style);              
    void                          Style_Add                     (XDWORD style);         
    void                          Style_Remove                  (XDWORD style); 

    XDWORD                        Styles_Get                    ();          
    void                          Styles_Set                    (XDWORD styles);         

    bool                          SetPropertys                  (int width, int height, float DPIs, int stride, GRPPROPERTYMODE mode);
    
    bool                          Buffer_Create                 ();   
    XBYTE*                        Buffer_Get                    ();
    bool                          Buffer_SetToZero              (); 
    bool                          Buffer_Delete                 ();
    
    virtual bool                  Create                        (bool show);
    virtual bool                  Update                        ();
    virtual bool                  Update                        (GRPCANVAS* canvas);
    virtual bool                  UpdateTransparent             (GRPCANVAS* canvas);
    virtual bool                  Delete                        ();
    virtual bool                  Get_Position                  (int &x, int &y);
    virtual bool                  Set_Position                  (int x, int y);    
    virtual bool                  Resize                        (int width, int height);
    virtual bool                  IsShow                        ();
    virtual bool                  Show                          (bool active);
    virtual bool                  ShowCursor                    (bool active);
    virtual bool                  ShowTopMost                   (bool active);
    virtual void*                 GetHandle                     ();    
    virtual void                  SetHandle                     (void* handle_window);
    virtual bool                  Set_Focus                     ();
    virtual bool                  Minimize                      (bool active);
    virtual bool                  Maximize                      (bool active);
    virtual GRPBITMAP*            CaptureContent                (GRPRECTINT* rect = NULL, void* handle_window = NULL);
    
    virtual void*                 GetDesktopHandle              ();
    virtual void*                 GetShellHandle                ();
    
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
    XDWORD                        styles;
    
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


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif
