/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_Layout.h
* 
* @class      UI_LAYOUT
* @brief      User Interface Layout class
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

#ifndef _UI_LAYOUT_H_
#define _UI_LAYOUT_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XVector.h"

#include "UI_Element.h"
#include "UI_Background.h"
#include "UI_Skin.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class UI_LAYOUT
{
  public:
                                    UI_LAYOUT                     (UI_SKIN* ui_skin);
    virtual                        ~UI_LAYOUT                     ();

    XSTRING*                        GetNameID                     ();

    UI_SKIN*                        GetSkin                       ();
    void                            SetSkin                       (UI_SKIN* ui_skin);

    UI_BACKGROUND*                  GetBackground                 ();

    bool                            Elements_Add                  (UI_ELEMENT* element);
    XVECTOR<UI_ELEMENT*>*           Elements_Get                  ();
    UI_ELEMENT*                     Elements_Get                  (XCHAR* nameelement, UI_ELEMENT_TYPE type = UI_ELEMENT_TYPE_UNKNOWN);    
    bool                            Elements_DeleteAll            ();

    bool                            Elements_SetToRedraw          (bool recursive = true);
    bool                            Elements_SetToRedraw          (UI_ELEMENT* element, bool recursive = true);

    virtual bool                    Update                        ();

    
  
  private:

    UI_ELEMENT*                     Elements_Get                  (UI_ELEMENT* element, XCHAR* nameelement, UI_ELEMENT_TYPE type);

    void                            Clean                         ();    

    UI_SKIN*                        ui_skin;
    XSTRING                         nameID;

    UI_BACKGROUND                   background;

    XVECTOR<UI_ELEMENT*>            elements;
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif
