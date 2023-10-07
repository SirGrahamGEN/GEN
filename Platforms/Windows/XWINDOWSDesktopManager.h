/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XWINDOWSDesktopManager.h
* 
* @class      XWINDOWSDESKTOPMANAGER
* @brief      eXtended WINDOWS Desktop Manager class
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

#ifndef _XWINDOWSDESKTOPMANAGER_H_
#define _XWINDOWSDESKTOPMANAGER_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include <windows.h>

#include "XVector.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

class  XWINDOWSDESKTOPMONITORS
{
  public:
                                          XWINDOWSDESKTOPMONITORS                   ();
    virtual                              ~XWINDOWSDESKTOPMONITORS                   ();

    XVECTOR<RECT*>*                       GetMonitorsRects                          ();
    RECT*                                 GetCombinedRect                           ();
  
  private:
    
    static BOOL CALLBACK                  MonitorEnum                               (HMONITOR hmon,HDC hdc,LPRECT rectmonitor,LPARAM pdata);
    
    void                                  Clean                                     ();

    XVECTOR<RECT*>                        monitorsrects;
    RECT                                  combinedrect;    
};


class XWINDOWSDESKTOPMANAGER
{
  public:
                                          XWINDOWSDESKTOPMANAGER                    ();
    virtual                              ~XWINDOWSDESKTOPMANAGER                    ();

    XWINDOWSDESKTOPMONITORS*              GetDesktopMonitors                        ();

  protected:

  private:

    void                                  Clean                                     ();
    XWINDOWSDESKTOPMONITORS               desktopmonitors;
};

#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif


