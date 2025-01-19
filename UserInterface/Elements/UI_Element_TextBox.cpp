/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_Element_TextBox.cpp
* 
* @class      UI_ELEMENT_TEXTBOX
* @brief      User Interface Element Text Box class
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "UI_Element_TextBox.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT_TEXTBOX::UI_ELEMENT_TEXTBOX()
* @brief      Constructor of class
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT_TEXTBOX::UI_ELEMENT_TEXTBOX()    
{ 
  Clean();   

  SetType(UI_ELEMENT_TYPE_TEXTBOX);

  GetTypeString()->Set(__L("textbox"));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT_TEXTBOX::~UI_ELEMENT_TEXTBOX()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT_TEXTBOX::~UI_ELEMENT_TEXTBOX()    
{ 
  Clean();                            
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD UI_ELEMENT_TEXTBOX::GetSizeFont()
* @brief      Get size font
* @ingroup    USERINTERFACE
*
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD UI_ELEMENT_TEXTBOX::GetSizeFont()
{
  return sizefont;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_ELEMENT_TEXTBOX::SetSizeFont(XDWORD sizefont)
* @brief      Set size font
* @ingroup    USERINTERFACE
*
* @param[in]  sizefont : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_ELEMENT_TEXTBOX::SetSizeFont(XDWORD sizefont)
{
  this->sizefont = sizefont;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD UI_ELEMENT_TEXTBOX::GetLineSpacing()
* @brief      Get line spacing
* @ingroup    USERINTERFACE
*
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD UI_ELEMENT_TEXTBOX::GetLineSpacing()
{
  return linespacing;
}
  

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_ELEMENT_TEXTBOX::SetLineSpacing(XDWORD linespacing)
* @brief      Set line spacing
* @ingroup    USERINTERFACE
*
* @param[in]  linespacing : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_ELEMENT_TEXTBOX::SetLineSpacing(XDWORD linespacing)
{
  this->linespacing = linespacing;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT_TYPE_ALIGN UI_ELEMENT_TEXTBOX::GetTextAlignment()
* @brief      Get text alignment
* @ingroup    USERINTERFACE
*
* @return     UI_ELEMENT_TYPE_ALIGN : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT_TYPE_ALIGN UI_ELEMENT_TEXTBOX::GetTextAlignment()
{
  return textalignment;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_ELEMENT_TEXTBOX::SetTextAlignment(UI_ELEMENT_TYPE_ALIGN textalignment)
* @brief      Set text alignment
* @ingroup    USERINTERFACE
* 
* @param[in]  textalignment : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void UI_ELEMENT_TEXTBOX::SetTextAlignment(UI_ELEMENT_TYPE_ALIGN textalignment)
{
  this->textalignment = textalignment;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_ELEMENT_TEXTBOX::IsWordClipping()
* @brief      Is word clipping
* @ingroup    USERINTERFACE
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_ELEMENT_TEXTBOX::IsWordClipping()
{
  return iswordclipping;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_ELEMENT_TEXTBOX::SetIsWordClipping(bool iswordclipping)
* @brief      Set is word clipping
* @ingroup    USERINTERFACE
*
* @param[in]  iswordclipping : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_ELEMENT_TEXTBOX::SetIsWordClipping(bool iswordclipping)
{
  this->iswordclipping = iswordclipping;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* UI_ELEMENT_TEXTBOX::GetText()
* @brief      Get text
* @ingroup    USERINTERFACE
*
* @return     XSTRING* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XSTRING* UI_ELEMENT_TEXTBOX::GetText()
{
  return &text;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* UI_ELEMENT_TEXTBOX::GetMaskText()
* @brief      Get mask text
* @ingroup    USERINTERFACE
*
* @return     XSTRING* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XSTRING* UI_ELEMENT_TEXTBOX::GetMaskText()
{
  return &masktext;    
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_ELEMENT_TEXTBOX::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_ELEMENT_TEXTBOX::Clean()
{
  sizefont        = 0;
  linespacing     = 0;
  textalignment   = UI_ELEMENT_TYPE_ALIGN_NOTDETERMINED;
  iswordclipping  = false;
}


#pragma endregion

