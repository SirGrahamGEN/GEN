/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_SkinCanvas_Flat.cpp
* 
* @class      UI_SKINCANVAS_FLAT
* @brief      User Interface Skin Canvas class
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

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "UI_SkinCanvas_Flat.h"

#include "XRect.h"

#include "GRPCanvas.h"
#include "GRPViewport.h"
#include "GRPScreen.h"

#include "UI_Element.h"
#include "UI_Element_Scroll.h"
#include "UI_Element_Text.h"
#include "UI_Element_Image.h"
#include "UI_Element_Animation.h"
#include "UI_Element_Option.h"
#include "UI_Element_Button.h"
#include "UI_Element_CheckBox.h"
#include "UI_Element_EditText.h"
#include "UI_Element_Form.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_SKINCANVAS_FLAT::UI_SKINCANVAS_FLAT(GRPSCREEN* screen) 
* @brief      Constructor
* @ingroup    USERINTERFACE
* 
* @param[in]  GRPSCREEN* : 
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
UI_SKINCANVAS_FLAT::UI_SKINCANVAS_FLAT(GRPSCREEN* screen) : UI_SKINCANVAS(screen)
{ 
  Clean();  

  this->name    = UI_SKINCANVAS_NAME_FLAT;   
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_SKINCANVAS_FLAT::~UI_SKINCANVAS_FLAT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    USERINTERFACE
*
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_SKINCANVAS_FLAT::~UI_SKINCANVAS_FLAT()    
{ 
  Clean();                            
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKINCANVAS_FLAT::Draw_Form(UI_ELEMENT* element)
* @brief      Draw_Form
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKINCANVAS_FLAT::Draw_Form(UI_ELEMENT* element)  
{  
  if(!screen)  return false;
  if(!element) return false;

  UI_ELEMENT_FORM*    element_form = (UI_ELEMENT_FORM*)element;
  double              x_position   = 0.0f;
  double              y_position   = 0.0f;
  GRPCANVAS*          canvas       = GetCanvas();
  XRECT               clip_rect;  
  
  if(!canvas) return false;
  
  PreDrawFunction(element, canvas, clip_rect, x_position, y_position);


  if(element->MustReDraw()) 
    {
      GRP2DCOLOR_RGBA8    color(element_form->GetColor()->GetRed(),
                                element_form->GetColor()->GetGreen(),
                                element_form->GetColor()->GetBlue(),
                                element_form->GetColor()->GetAlpha());

      GRP2DCOLOR_RGBA8    linecolor(element_form->GetLineColor()->GetRed(),
                                    element_form->GetLineColor()->GetGreen(),
                                    element_form->GetLineColor()->GetBlue(),
                                    element_form->GetLineColor()->GetAlpha());

      canvas->SetLineWidth(0.5f);
      canvas->SetLineColor(&linecolor);
      canvas->SetFillColor(&color);

      canvas->Rectangle(element_form->GetVisibleRect()->x, 
                        element_form->GetVisibleRect()->y,
                        element_form->GetVisibleRect()->x + element_form->GetVisibleRect()->width   , 
                        element_form->GetVisibleRect()->y - element_form->GetVisibleRect()->height  , true);

     }

  for(XDWORD c=0; c<element_form->GetComposeElements()->GetSize(); c++)
    {
      UI_ELEMENT* subelement = (UI_ELEMENT*)element->GetComposeElements()->Get(c);
      if(subelement) 
        {
          Draw(subelement);
        }  
    }
  
  PostDrawFunction(element, canvas, clip_rect, x_position, y_position);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_SKINCANVAS_FLAT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    USERINTERFACE
*
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_SKINCANVAS_FLAT::Clean()
{
  
}


#pragma endregion

