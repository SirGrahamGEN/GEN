/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_Animations.h
* 
* @class      UI_ANIMATIONS
* @brief      User Interface Animations class
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

#ifndef _UI_ANIMATIONS_H_
#define _UI_ANIMATIONS_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XString.h"
#include "XMap.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

#define GEN_UI_ANIMATIONS  UI_ANIMATIONS::GetInstance()

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class UI_ANIMATION;


class UI_ANIMATIONS
{
  public:

    static bool                     GetIsInstanced         ();
    static UI_ANIMATIONS&           GetInstance            ();
    static bool                     DelInstance            ();

    bool                            Add                    (UI_ANIMATION* animation);  
    
    UI_ANIMATION*                   Get                    (XCHAR* ID);
    UI_ANIMATION*                   Get                    (XSTRING& ID);

    bool                            DeleteAll              ();
  
  private:
                                    UI_ANIMATIONS          ();   
                                    UI_ANIMATIONS          (UI_ANIMATIONS const&);        // Don't implement
    virtual                        ~UI_ANIMATIONS          ();

    void                            operator =             (UI_ANIMATIONS const&);        // Don't implement

    void                            Clean                  ();

    static UI_ANIMATIONS*           instance;

    XVECTOR<UI_ANIMATION*>          animations;
};



#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

