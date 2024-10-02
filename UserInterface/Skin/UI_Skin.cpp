/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_Skin.cpp
* 
* @class      UI_SKIN
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "UI_Skin.h"

#include "XTimer.h" 

#include "GRPScreen.h"
#include "GRPBitmap.h"
#include "GRPBitmapFile.h"

#include "UI_Property_Scrolleable.h"
#include "UI_Animation.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


#pragma region CLASS_UI_SKIN_TEXTBOX_PART


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_SKIN_TEXTBOX_PART::UI_SKIN_TEXTBOX_PART()
* @brief      Constructor
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
UI_SKIN_TEXTBOX_PART::UI_SKIN_TEXTBOX_PART()
{
  Clean();
}

		
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_SKIN_TEXTBOX_PART::~UI_SKIN_TEXTBOX_PART()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
UI_SKIN_TEXTBOX_PART::~UI_SKIN_TEXTBOX_PART()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD UI_SKIN_TEXTBOX_PART::GetLineNumber()
* @brief      GetLineNumber
* @ingroup    USERINTERFACE
*
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD UI_SKIN_TEXTBOX_PART::GetLineNumber()
{
  return linenumber;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_SKIN_TEXTBOX_PART::SetLineNumber(XDWORD linenumber)
* @brief      SetLineNumber
* @ingroup    USERINTERFACE
*
* @param[in]  linenumber : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_SKIN_TEXTBOX_PART::SetLineNumber(XDWORD linenumber)
{
  this->linenumber = linenumber;
}

		
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD UI_SKIN_TEXTBOX_PART::GetXPos()
* @brief      GetXPos
* @ingroup    USERINTERFACE
*
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD UI_SKIN_TEXTBOX_PART::GetXPos()
{
  return xpos;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_SKIN_TEXTBOX_PART::SetXPos(XDWORD xpos)
* @brief      SetXPos
* @ingroup    USERINTERFACE
*
* @param[in]  xpos : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_SKIN_TEXTBOX_PART::SetXPos(XDWORD xpos)
{
  this->xpos = xpos;
}

		
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD UI_SKIN_TEXTBOX_PART::GetYPos()
* @brief      GetYPos
* @ingroup    USERINTERFACE
*
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD UI_SKIN_TEXTBOX_PART::GetYPos()
{
  return ypos;
}	

	
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_SKIN_TEXTBOX_PART::SetYPos(XDWORD ypos)
* @brief      SetYPos
* @ingroup    USERINTERFACE
*
* @param[in]  ypos : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_SKIN_TEXTBOX_PART::SetYPos(XDWORD ypos)
{
  this->ypos = ypos;    
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_COLOR* UI_SKIN_TEXTBOX_PART::GetColor()
* @brief      GetColor
* @ingroup    USERINTERFACE
*
* @return     UI_COLOR* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_COLOR* UI_SKIN_TEXTBOX_PART::GetColor()
{
  return &color;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD UI_SKIN_TEXTBOX_PART::GetWidth()
* @brief      GetWidth
* @ingroup    USERINTERFACE
*
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD UI_SKIN_TEXTBOX_PART::GetWidth()
{
  return width;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_SKIN_TEXTBOX_PART::SetWidth(XDWORD width)
* @brief      SetWidth
* @ingroup    USERINTERFACE
*
* @param[in]  width : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_SKIN_TEXTBOX_PART::SetWidth(XDWORD width)
{
  this->width = width;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD UI_SKIN_TEXTBOX_PART::GetHeight()
* @brief      GetHeight
* @ingroup    USERINTERFACE
*
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD UI_SKIN_TEXTBOX_PART::GetHeight()
{
  return height;
}
	

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_SKIN_TEXTBOX_PART::SetHeight(XDWORD height)
* @brief      SetHeight
* @ingroup    USERINTERFACE
*
* @param[in]  height : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_SKIN_TEXTBOX_PART::SetHeight(XDWORD height)
{
  this->height = height;
}

		
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* UI_SKIN_TEXTBOX_PART::GetText()
* @brief      GetText
* @ingroup    USERINTERFACE
*
* @return     XSTRING* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XSTRING* UI_SKIN_TEXTBOX_PART::GetText()
{
  return &text;
}

	
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_SKIN_TEXTBOX_PART::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_SKIN_TEXTBOX_PART::Clean()
{  
  linenumber  = 0;

  xpos        = 0;
  ypos        = 0;

  width       = 0;
  height      = 0;    
}


#pragma endregion


#pragma region CLASS_UI_SKIN


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_SKIN::UI_SKIN()
* @brief      Constructor
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
UI_SKIN::UI_SKIN()    
{ 
  Clean();     
  
  this->name = UI_SKIN_NAME_UNKNOWN;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_SKIN::~UI_SKIN()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
UI_SKIN::~UI_SKIN()    
{ 
  Clean();                            
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* UI_SKIN::GetName()
* @brief      GetName
* @ingroup    USERINTERFACE
*
* @return     XSTRING* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XSTRING* UI_SKIN::GetName()
{
  return &name;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_SKIN_TYPE UI_SKIN::GetType(XCHAR* name)
* @brief      GetType
* @ingroup    USERINTERFACE
*
* @param[in]  name : 
* 
* @return     UI_SKIN_TYPE : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_SKIN_TYPE UI_SKIN::GetType(XCHAR* name)
{
  XSTRING _name;

  if(name) 
         _name = name;  
    else _name = this->name;

  if(_name.IsEmpty()) return UI_SKIN_TYPE_UNKNOWN;

  if(!_name.Compare(__L("flat"), true))       return UI_SKIN_TYPE_FLAT;

  return UI_SKIN_TYPE_UNKNOWN;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_SKIN_DRAWMODE UI_SKIN::GetDrawMode()
* @brief      GetDrawMode
* @ingroup    USERINTERFACE
*
* @return     UI_SKIN_DRAWMODE : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_SKIN_DRAWMODE UI_SKIN::GetDrawMode()
{
  return drawmode;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::SetDrawMode(UI_SKIN_DRAWMODE drawmode)
* @brief      SetDrawMode
* @ingroup    USERINTERFACE
*
* @param[in]  drawmode : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::SetDrawMode(UI_SKIN_DRAWMODE drawmode)
{
  this->drawmode  = drawmode;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* UI_SKIN::GetRasterFont()
* @brief      GetRasterFont
* @ingroup    USERINTERFACE
*
* @return     XSTRING* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XSTRING* UI_SKIN::GetRasterFont()
{
  return &rasterfontname;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* UI_SKIN::GetVectorFont()
* @brief      GetVectorFont
* @ingroup    USERINTERFACE
*
* @return     XSTRING* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XSTRING* UI_SKIN::GetVectorFont()
{
  return &vectorfontname;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::LoadFonts()
* @brief      LoadFonts
* @ingroup    USERINTERFACE
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::LoadFonts()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double UI_SKIN::GetWithString(XCHAR* string, XDWORD sizefont)
* @brief      GetWithString
* @ingroup    USERINTERFACE
*
* @param[in]  string : 
* @param[in]  sizefont : 
* 
* @return     double : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
double UI_SKIN::GetWithString(XCHAR* string, XDWORD sizefont)
{
  return 0;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double UI_SKIN::GetWithString(XSTRING& string, XDWORD sizefont)
* @brief      GetWithString
* @ingroup    USERINTERFACE
*
* @param[in]  string : 
* @param[in]  sizefont : 
* 
* @return     double : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
double UI_SKIN::GetWithString(XSTRING& string, XDWORD sizefont)
{
  return GetWithString(string.Get(), sizefont);
}

  
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double UI_SKIN::GetHeightString(XCHAR* string, XDWORD sizefont)
* @brief      GetHeightString
* @ingroup    USERINTERFACE
*
* @param[in]  string : 
* @param[in]  sizefont : 
* 
* @return     double : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
double UI_SKIN::GetHeightString(XCHAR* string, XDWORD sizefont)
{
  return 0;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double UI_SKIN::GetHeightString(XSTRING& string, XDWORD sizefont)
* @brief      GetHeightString
* @ingroup    USERINTERFACE
* 
* @param[in]  string : 
* @param[in]  sizefont : 
* 
* @return     double : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
double UI_SKIN::GetHeightString(XSTRING& string, XDWORD sizefont)
{
  return GetHeightString(string.Get(), sizefont);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::CalculateBoundaryLine(UI_ELEMENT* element, bool adjustsizemargin)
* @brief      CalculateBoundaryLine
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* @param[in]  adjustsizemargin : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::CalculateBoundaryLine(UI_ELEMENT* element, bool adjustsizemargin)
{
  if(!element) return false;

  switch(element->GetType())
    {
      case UI_ELEMENT_TYPE_UNKNOWN				: return false;                                                                       break;	    
	    case UI_ELEMENT_TYPE_SCROLL				  : return CalculateBoundaryLine_Scroll(element, adjustsizemargin);                     break;
	    case UI_ELEMENT_TYPE_TEXT					  : return CalculateBoundaryLine_Text(element, adjustsizemargin);                       break; 	
      case UI_ELEMENT_TYPE_TEXTBOX			  : return CalculateBoundaryLine_TextBox(element, adjustsizemargin);                    break;    
	    case UI_ELEMENT_TYPE_IMAGE     			: return CalculateBoundaryLine_Image(element, adjustsizemargin);	                    break;
      case UI_ELEMENT_TYPE_ANIMATION 			: return CalculateBoundaryLine_Animation(element, adjustsizemargin);	                break;
      case UI_ELEMENT_TYPE_OPTION					: return CalculateBoundaryLine_Option(element, adjustsizemargin);                     break;
      case UI_ELEMENT_TYPE_MULTIOPTION		: return CalculateBoundaryLine_MultiOption(element, adjustsizemargin);                break;
	    case UI_ELEMENT_TYPE_BUTTON					: return CalculateBoundaryLine_Button(element, adjustsizemargin);                     break;	    	    
      case UI_ELEMENT_TYPE_CHECKBOX 			: return CalculateBoundaryLine_CheckBox(element, adjustsizemargin);                   break;	    	    
      case UI_ELEMENT_TYPE_EDITTEXT   		: return CalculateBoundaryLine_EditText(element, adjustsizemargin);                   break;	      
      case UI_ELEMENT_TYPE_FORM						: return CalculateBoundaryLine_Form(element, adjustsizemargin);                       break; 
      case UI_ELEMENT_TYPE_MENU           : return CalculateBoundaryLine_Menu(element, adjustsizemargin);                       break;                  
      case UI_ELEMENT_TYPE_LISTBOX        : return CalculateBoundaryLine_ListBox(element, adjustsizemargin);                    break;                  
      case UI_ELEMENT_TYPE_PROGRESSBAR	  : return CalculateBoundaryLine_ProgressBar(element, adjustsizemargin);                break;                  
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::CalculateBoundaryLine_Scroll(UI_ELEMENT* element, bool adjustsizemargin)
* @brief      CalculateBoundaryLine_Scroll
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* @param[in]  adjustsizemargin : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::CalculateBoundaryLine_Scroll(UI_ELEMENT* element, bool adjustsizemargin)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::CalculateBoundaryLine_Text(UI_ELEMENT* element, bool adjustsizemargin)
* @brief      CalculateBoundaryLine_Text
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* @param[in]  adjustsizemargin : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::CalculateBoundaryLine_Text(UI_ELEMENT* element, bool adjustsizemargin)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::CalculateBoundaryLine_TextBox(UI_ELEMENT* element, bool adjustsizemargin)
* @brief      CalculateBoundaryLine_TextBox
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* @param[in]  adjustsizemargin : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::CalculateBoundaryLine_TextBox(UI_ELEMENT* element, bool adjustsizemargin)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::CalculateBoundaryLine_Image(UI_ELEMENT* element, bool adjustsizemargin)
* @brief      CalculateBoundaryLine_Image
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* @param[in]  adjustsizemargin : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::CalculateBoundaryLine_Image(UI_ELEMENT* element, bool adjustsizemargin)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::CalculateBoundaryLine_Animation(UI_ELEMENT* element, bool adjustsizemargin)
* @brief      CalculateBoundaryLine_Animation
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* @param[in]  adjustsizemargin : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::CalculateBoundaryLine_Animation(UI_ELEMENT* element, bool adjustsizemargin)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::CalculateBoundaryLine_Option(UI_ELEMENT* element, bool adjustsizemargin)
* @brief      CalculateBoundaryLine_Option
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* @param[in]  adjustsizemargin : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::CalculateBoundaryLine_Option(UI_ELEMENT* element, bool adjustsizemargin)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::CalculateBoundaryLine_MultiOption(UI_ELEMENT* element, bool adjustsizemargin)
* @brief      CalculateBoundaryLine_MultiOption
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* @param[in]  adjustsizemargin : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::CalculateBoundaryLine_MultiOption(UI_ELEMENT* element, bool adjustsizemargin)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::CalculateBoundaryLine_Button(UI_ELEMENT* element, bool adjustsizemargin)
* @brief      CalculateBoundaryLine_Button
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* @param[in]  adjustsizemargin : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::CalculateBoundaryLine_Button(UI_ELEMENT* element, bool adjustsizemargin)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::CalculateBoundaryLine_CheckBox(UI_ELEMENT* element, bool adjustsizemargin)
* @brief      CalculateBoundaryLine_CheckBox
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* @param[in]  adjustsizemargin : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::CalculateBoundaryLine_CheckBox(UI_ELEMENT* element, bool adjustsizemargin)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::CalculateBoundaryLine_EditText(UI_ELEMENT* element, bool adjustsizemargin)
* @brief      CalculateBoundaryLine_EditText
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* @param[in]  adjustsizemargin : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::CalculateBoundaryLine_EditText(UI_ELEMENT* element, bool adjustsizemargin)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::CalculateBoundaryLine_Form(UI_ELEMENT* element, bool adjustsizemargin)
* @brief      CalculateBoundaryLine_Form
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* @param[in]  adjustsizemargin : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::CalculateBoundaryLine_Form(UI_ELEMENT* element, bool adjustsizemargin)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::CalculateBoundaryLine_Menu(UI_ELEMENT* element, bool adjustsizemargin)
* @brief      CalculateBoundaryLine_Menu
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* @param[in]  adjustsizemargin : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::CalculateBoundaryLine_Menu(UI_ELEMENT* element, bool adjustsizemargin)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::CalculateBoundaryLine_ListBox(UI_ELEMENT* element, bool adjustsizemargin)
* @brief      CalculateBoundaryLine_ListBox
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* @param[in]  adjustsizemargin : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::CalculateBoundaryLine_ListBox(UI_ELEMENT* element, bool adjustsizemargin)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::CalculateBoundaryLine_ProgressBar(UI_ELEMENT* element, bool adjustsizemargin)
* @brief      CalculateBoundaryLine_ProgressBar
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* @param[in]  adjustsizemargin : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::CalculateBoundaryLine_ProgressBar(UI_ELEMENT* element, bool adjustsizemargin)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::CalculeBoundaryLine_AllElements(UI_ELEMENT* element, bool recursive)
* @brief      CalculeBoundaryLine_AllElements
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* @param[in]  recursive : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::CalculeBoundaryLine_AllElements(UI_ELEMENT* element, bool recursive)
{
  CalculateBoundaryLine(element);

  for(XDWORD c=0; c<element->GetComposeElements()->GetSize(); c++)
    {
      UI_ELEMENT* subelement = element->GetComposeElements()->Get(c);
      if(subelement) CalculeBoundaryLine_AllElements(subelement, recursive);                   
    } 

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::GetAddPositionScrollSteps(UI_ELEMENT* element, double& x_positionwithscroll, double& y_positionwithscroll)
* @brief      GetAddPositionScrollSteps
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* @param[in]  x_positionwithscroll : 
* @param[in]  y_positionwithscroll : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::GetAddPositionScrollSteps(UI_ELEMENT* element, double& x_positionwithscroll, double& y_positionwithscroll)
{  
  if(!element) return false;

  UI_PROPERTY_SCROLLEABLE* property_scrolleable = dynamic_cast<UI_PROPERTY_SCROLLEABLE*>(element);
  if(property_scrolleable)
    {
      x_positionwithscroll += property_scrolleable->Scroll_GetDisplacement(UI_PROPERTY_SCROLLEABLE_TYPE_HORIZONTAL);   
      y_positionwithscroll += property_scrolleable->Scroll_GetDisplacement(UI_PROPERTY_SCROLLEABLE_TYPE_VERTICAL);   
    }
    
  if(element->GetFather()) GetAddPositionScrollSteps(element->GetFather(), x_positionwithscroll, y_positionwithscroll);      
    
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::SetElementPosition(UI_ELEMENT* element, double x_position, double y_position)
* @brief      SetElementPosition
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* @param[in]  x_position : 
* @param[in]  y_position : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::SetElementPosition(UI_ELEMENT* element, double x_position, double y_position)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::Elements_SetToRedraw(UI_ELEMENT* element, bool recursive)
* @brief      Elements_SetToRedraw
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* @param[in]  recursive : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::Elements_SetToRedraw(UI_ELEMENT* element, bool recursive)
{
  if(!element) return false;

  bool status = true;

  element->SetMustReDraw(true);

  if(recursive)
    {
      for(XDWORD c=0; c<element->GetComposeElements()->GetSize(); c++)
        {
          UI_ELEMENT* subelement = (UI_ELEMENT*)element->GetComposeElements()->Get(c);
          if(subelement) 
            { 
              status = Elements_SetToRedraw(subelement, recursive);          
              
            } else break;
        }           
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::Draw(UI_ELEMENT* element)
* @brief      Draw
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::Draw(UI_ELEMENT* element)  
{
  if(!element) return false;

  if(!element->IsVisible())  return false;

  if(element->IsBlinking())
    {
      if(element->GetTimerBlink()->GetMeasureMilliSeconds() > element->IsBlinking()) 
        {
          element->SwicthStateBlink();                  
          Elements_SetToRedraw(element);
        }
       
      if(!element->GetStateBlink()) return false;        
    }

  bool status = false;

  switch(element->GetType())
    {
      case UI_ELEMENT_TYPE_UNKNOWN				: break;  
                             default      : break;
      case UI_ELEMENT_TYPE_SCROLL				  : status = Draw_Scroll(element);            break;
	    case UI_ELEMENT_TYPE_TEXT					  : status = Draw_Text(element);              break; 
      case UI_ELEMENT_TYPE_TEXTBOX  			: status = Draw_TextBox(element);           break;	    
	    case UI_ELEMENT_TYPE_IMAGE     			: status = Draw_Image(element);             break;
      case UI_ELEMENT_TYPE_ANIMATION 			: status = Draw_Animation(element);	        break;
      case UI_ELEMENT_TYPE_OPTION					: status = Draw_Option(element);            break;
      case UI_ELEMENT_TYPE_MULTIOPTION		: status = Draw_MultiOption(element);       break;
	    case UI_ELEMENT_TYPE_BUTTON					: status = Draw_Button(element);            break;	    	    
      case UI_ELEMENT_TYPE_CHECKBOX 			: status = Draw_CheckBox(element);          break;	    	    
      case UI_ELEMENT_TYPE_EDITTEXT       : status = Draw_EditText(element);          break;	      
      case UI_ELEMENT_TYPE_FORM						: status = Draw_Form(element);              break;
      case UI_ELEMENT_TYPE_MENU           : status = Draw_Menu(element);              break;             
      case UI_ELEMENT_TYPE_LISTBOX        : status = Draw_ListBox(element);           break;             
      case UI_ELEMENT_TYPE_PROGRESSBAR    : status = Draw_ProgressBar(element);       break;                       
    }

  return status;
} 


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::Draw_Scroll(UI_ELEMENT* element)
* @brief      Draw_Scroll
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::Draw_Scroll(UI_ELEMENT* element)  
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::Draw_Text(UI_ELEMENT* element)
* @brief      Draw_Text
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::Draw_Text(UI_ELEMENT* element)  
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::Draw_TextBox(UI_ELEMENT* element)
* @brief      Draw_TextBox
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::Draw_TextBox(UI_ELEMENT* element)  
{
  return false;
}
 

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::Draw_Image(UI_ELEMENT* element)
* @brief      Draw_Image
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::Draw_Image(UI_ELEMENT* element)  
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::Draw_Animation(UI_ELEMENT* element)
* @brief      Draw_Animation
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::Draw_Animation(UI_ELEMENT* element)  
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::Draw_Option(UI_ELEMENT* element)
* @brief      Draw_Option
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::Draw_Option(UI_ELEMENT* element)  
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::Draw_MultiOption(UI_ELEMENT* element)
* @brief      Draw_MultiOption
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::Draw_MultiOption(UI_ELEMENT* element)  
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::Draw_Button(UI_ELEMENT* element)
* @brief      Draw_Button
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::Draw_Button(UI_ELEMENT* element)  
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::Draw_CheckBox(UI_ELEMENT* element)
* @brief      Draw_CheckBox
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::Draw_CheckBox(UI_ELEMENT* element)  
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::Draw_EditText(UI_ELEMENT* element)
* @brief      Draw_EditText
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::Draw_EditText(UI_ELEMENT* element)  
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::Draw_Form(UI_ELEMENT* element)
* @brief      Draw_Form
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::Draw_Form(UI_ELEMENT* element)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::Draw_Menu(UI_ELEMENT* element)
* @brief      Draw_Menu
* @ingroup    USERINTERFACE
* 
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::Draw_Menu(UI_ELEMENT* element)  
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::Draw_ListBox(UI_ELEMENT* element)
* @brief      Draw_ListBox
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::Draw_ListBox(UI_ELEMENT* element)  
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_SKIN::Draw_ProgressBar(UI_ELEMENT* element)
* @brief      Draw_ProgressBar
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_SKIN::Draw_ProgressBar(UI_ELEMENT* element)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_SKIN::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_SKIN::Clean()
{
  drawmode           = UI_SKIN_DRAWMODE_UNKNOWN;  
}


#pragma endregion


#pragma endregion

