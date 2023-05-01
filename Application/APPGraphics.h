/**-------------------------------------------------------------------------------------------------------------------
*
* @file       Application.h
*
* @class      APPGRAPHICS
* @brief      Application Graphics class
* @ingroup    APPLICATION
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

#ifndef _APPGRAPHICS_H_
#define _APPGRAPHICS_H_

#ifdef GRP_ACTIVE

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XObserver.h"
#include "XVector.h"

#include "APPBase.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum APPGRAPHICS_INIOPTIONS
{
  APPGRAPHICS_INIOPTION_NONE                = 0       ,
  APPGRAPHICS_INIOPTION_CREATEMAINSCREEN    = 1 << 1  ,
  APPGRAPHICS_INIOPTION_SHOWMAINSCREEN      = 1 << 2  ,
  APPGRAPHICS_INIOPTION_INPUT               = 1 << 3
};

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class GRPSCREEN;
class GRPCANVAS;
class INPDEVICE;

class APPGRAPHICS : public APPBASE, public XOBSERVER
{
  public:
                              APPGRAPHICS                         ();
    virtual                  ~APPGRAPHICS                         ();

    bool                      Ini                                 (XVECTOR<XSTRING*>* execparams);
    bool                      End                                 ();

    XDWORD                    GetInitOptions                      ();
    void                      SetInitOptions                      (XDWORD initoptions);

    bool                      CreateMainScreenProcess             (bool show);
    bool                      DeleteMainScreenProcess             ();

    GRPSCREEN*                GetMainScreen                       ();
    void                      SetMainScreen                       (GRPSCREEN* mainscreen);

    #ifdef INP_ACTIVE
    INPDEVICE*                GetInputKeyboard                    ();
    INPDEVICE*                GetInputMouse                       ();
    #endif

    virtual bool              AppProc_BeforeCreateMainScreen      (GRPSCREEN* mainscreen);
    virtual bool              AppProc_BeforeCreateMainCanvas      (GRPCANVAS* maincanvas);

  private:

    void                      Clean                               ();

    XDWORD                    initoptions;
    GRPSCREEN*                mainscreen;

    #ifdef INP_ACTIVE
    INPDEVICE*                keyboard;
    INPDEVICE*                mouse;
    INPDEVICE*                touchscreen;
    #endif
};

/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif

#endif
