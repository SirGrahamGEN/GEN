/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XWINDOWSConsole.h
* 
* @class      XWINDOWSCONSOLE
* @brief      WINDOWS eXtended Utils Console class
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

#ifndef _XWINDOWSCONSOLE_H_
#define _XWINDOWSCONSOLE_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XConsole.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class XWINDOWSCONSOLE : public XCONSOLE
{
  public:
                        XWINDOWSCONSOLE                 ();
    virtual            ~XWINDOWSCONSOLE                 ();

    bool                GetSize                         (int& width, int& height);
    bool                SetSize                         (int width, int height);

    bool                GetSizeText                     (int& columms, int& rows);

    bool                Maximize                        ();
    bool                Minimize                        ();

    bool                Hide                            ();
    bool                IsHide                          ();
    bool                UnHide                          ();

    bool                Print                           (XCHAR* string);
    bool                Clear                           (bool fill = true);

    bool                KBHit                           ();
    int                 GetChar                         ();

    static void         RedirectIOToConsole             ();
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

