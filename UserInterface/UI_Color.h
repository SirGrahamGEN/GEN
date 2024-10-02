/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_Color.h
* 
* @class      UI_COLOR
* @brief      User Interface Color class
* @ingroup    USERINTERFACE
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

#ifndef _UI_COLOR_H_
#define _UI_COLOR_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XString.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class UI_COLOR
{
  public:
                       UI_COLOR             ();
                       UI_COLOR             (XCHAR* string);
                       UI_COLOR             (XSTRING& string);
    virtual           ~UI_COLOR             ();

    bool               IsValid              (); 
    bool               SetValid             (bool valid);                     
    void               SetInvalid           ();                    
    
    int                GetRed               (); 
    void               SetRed               (int red = 0);  

    int                GetGreen             (); 
    void               SetGreen             (int green = 0);  

    int                GetBlue              (); 
    void               SetBlue              (int blue = 0);  

    int                GetAlpha             (); 
    void               SetAlpha             (int alpha = 0);  

    bool               SetFromString        (XCHAR* string);
    bool               SetFromString        (XSTRING& string);

    bool               CopyFrom             (UI_COLOR* color);
    bool               CopyTo               (UI_COLOR* color);

  private:

    int                GetAlphaForPercent   (int percent);

    void               Clean                ();

    bool               valid;     
    int                red;
    int                green;
    int                blue;
    int                alpha;  
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

