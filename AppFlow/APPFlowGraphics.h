/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       APPFlowGraphics.h
* 
* @class      APPFLOWGRAPHICS
* @brief      Application Flow Graphics class
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

#ifndef _APPFLOWGRAPHICS_H_
#define _APPFLOWGRAPHICS_H_

#ifdef GRP_ACTIVE

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XVector.h"

#include "APPFlowBase.h"
#include "APPFlowConsole.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

enum APPFLOWGRAPHICS_INIOPTIONS
{
  APPFLOWGRAPHICS_INIOPTION_NONE                = 0       ,
  APPFLOWGRAPHICS_INIOPTION_CREATEMAINSCREEN    = 1 << 1  ,
  APPFLOWGRAPHICS_INIOPTION_SHOWMAINSCREEN      = 1 << 2  ,
  APPFLOWGRAPHICS_INIOPTION_INPUT               = 1 << 3
};

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class GRPSCREEN;
class GRPCANVAS;
class INPDEVICE;


class APPFLOWGRAPHICS : public APPFLOWCONSOLE, public XOBSERVER
{
  public:
                              APPFLOWGRAPHICS                     ();
    virtual                  ~APPFLOWGRAPHICS                     ();

    bool                      Ini                                 (XVECTOR<XSTRING*>* execparams);
    bool                      End                                 ();

    XDWORD                    GetInitOptions                      ();
    void                      SetInitOptions                      (XDWORD initoptions);

    bool                      CreateMainScreenProcess             (bool show);
    bool                      DeleteMainScreenProcess             ();

    GRPSCREEN*                GetMainScreen                       ();
    void                      SetMainScreen                       (GRPSCREEN* mainscreen);

    GRPCANVAS*                GetScreenCanvas                     (GRPSCREEN* screen, int viewportindex);

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

#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif


#endif
