/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_Element_TextBox.cpp
* 
* @class      UI_ELEMENT_TEXTBOX
* @brief      User Interface Element Text Box class
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @copyright  Copyright(c) 2005 - 2020 GEN Group.
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
* ---------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "UI_Element_TextBox.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT_TEXTBOX::UI_ELEMENT_TEXTBOX()
* @brief      Constructor
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     Does not return anything. 
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
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT_TEXTBOX::~UI_ELEMENT_TEXTBOX()    
{ 
  Clean();                            
}

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD UI_ELEMENT_TEXTBOX::GetSizeFont()
* @brief      GetSizeFont
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
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
* @brief      SetSizeFont
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  sizefont : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_ELEMENT_TEXTBOX::SetSizeFont(XDWORD sizefont)
{
  this->sizefont = sizefont;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD UI_ELEMENT_TEXTBOX::GetLineSpacing()
* @brief      GetLineSpacing
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
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
* @brief      SetLineSpacing
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  linespacing : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_ELEMENT_TEXTBOX::SetLineSpacing(XDWORD linespacing)
{
  this->linespacing = linespacing;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT_TYPE_ALIGN UI_ELEMENT_TEXTBOX::GetTextAlignment()
* @brief      GetTextAlignment
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
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
* @fn         void UI_ELEMENT_TEXTBOX::SetAlignText(UI_ELEMENT_TYPE_ALIGN aligntext)
* @brief      SetAlignText
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  aligntext : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_ELEMENT_TEXTBOX::SetTextAlignment(UI_ELEMENT_TYPE_ALIGN textalignment)
{
  this->textalignment = textalignment;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_ELEMENT_TEXTBOX::IsWordClipping()
* @brief      IsWordClipping
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
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
* @brief      SetIsWordClipping
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  iswordclipping : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_ELEMENT_TEXTBOX::SetIsWordClipping(bool iswordclipping)
{
  this->iswordclipping = iswordclipping;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* UI_ELEMENT_TEXTBOX::GetText()
* @brief      GetText
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
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
* @brief      GetMaskText
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
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
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_ELEMENT_TEXTBOX::Clean()
{
  sizefont        = 0;
  linespacing     = 0;
  textalignment   = UI_ELEMENT_TYPE_ALIGN_NOTDETERMINED;
  iswordclipping  = false;
}