/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       INPSimulate.h
* 
* @class      INPSIMULATE
* @brief      Input Simulate
* @ingroup    INPUT
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

#ifndef _INPSIMULATE_H_
#define _INPSIMULATE_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XString.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

enum ALTERNATIVE_KEY
{
  ALTERNATIVE_KEY_NONE   = 0  ,
  ALTERNATIVE_KEY_ALTGR       ,
  ALTERNATIVE_KEY_SHIFT       ,
};

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

typedef struct 
{
  XBYTE                   code;
  XCHAR*                  literal;
  ALTERNATIVE_KEY         altkey;

} INPUTSIMULATE_KDB_PC;


class INPSIMULATE
{
  public:
                        INPSIMULATE             ();
    virtual            ~INPSIMULATE             ();

    virtual bool        PressKeyDown            (XBYTE code);
    virtual bool        PressKeyUp              (XBYTE code);
    virtual bool        PressKey                (XBYTE code, int pressuretime = 100);
    bool                PressKeyDownByLiteral   (XCHAR* literal);
    bool                PressKeyUpByLiteral     (XCHAR* literal);
    virtual bool        PressKeyByLiteral       (XCHAR* literal, int pressuretime = 100);
    virtual bool        PressKeyByText          (XCHAR* text, int pressuretimeinterval = 100);
    virtual bool        SetMousePos             (int x, int y);
    virtual bool        SetMouseClick           (int x, int y);

    XBYTE               GetKDBCodeByLiteral     (XCHAR* literal, ALTERNATIVE_KEY& altkey);

  protected:

  private:

    void                Clean                   ();
};

#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif
