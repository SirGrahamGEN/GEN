/**-------------------------------------------------------------------------------------------------------------------
*
* @file       GRPWINDOWSScreen.h
*
* @class      GRPWINDOWSSCREEN
* @brief      WINDOWS Graphics Screen class
* @ingroup    PLATFORM_WINDOWS
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

#ifndef _GRPWINDOWSSCREEN_H_
#define _GRPWINDOWSSCREEN_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <Windows.h>
#include <winuser.h>

#include "XString.h"
#include "GRPScreen.h"


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/


#define GRPWINDOWSSCREEN_NAMECLASS  __L("GEN_Windows_Screen")

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class GRPWINDOWSSCREEN : public GRPSCREEN
{
  public:
                                          GRPWINDOWSSCREEN            ();
    virtual                              ~GRPWINDOWSSCREEN            ();

    bool                                  Create                      (bool show);

    bool                                  Update                      ();
    bool                                  Update                      (GRPCANVAS* canvas);

    bool                                  Delete                      ();

    bool                                  Resize                      (int width, int height);

    bool                                  Show                        (bool active);
    bool                                  ShowCursor                  (bool active);
    bool                                  ShowTopMost                 (bool active);

    void*                                 GetHandle                   ();
    void                                  SetHandle                   (HWND hwnd);

    void*                                 GetHDC                      ();
    void                                  SetHDC                      (HDC hdc);

    BITMAPINFO*                           GetHInfo                    ();
  
//  int                                   GetScaleFactor              ();

    bool                                  IsBlockClose                ();
    void                                  SetIsBlockClose             (bool activated);

    static XMAP<HWND, GRPWINDOWSSCREEN*>* GetListScreens              ();

  
  private:

    void                                  Clean                       ();

    bool                                  Create_Window               (bool show);

    static  LRESULT CALLBACK              BaseWndProc                 (HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

    WNDCLASSEX                            wndclass;
    XSTRING                               classname;
    XSTRING                               title;

    HINSTANCE                             hinstance;
    HWND                                  hwnd;
    HDC                                   hdc;

    DEVMODE                               devmode;

    BITMAPINFO                            hinfo;

    static XMAP<HWND, GRPWINDOWSSCREEN*>  listscreens;
};

/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif



