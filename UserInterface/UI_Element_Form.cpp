/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_Element_Form.cpp
* 
* @class      UI_ELEMENT_FORM
* @brief      User Interface Element Form class
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

#include "UI_Element_Form.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT_FORM::UI_ELEMENT_FORM()
* @brief      Constructor
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT_FORM::UI_ELEMENT_FORM()    
{ 
  Clean();   

  SetType(UI_ELEMENT_TYPE_FORM);

  GetTypeString()->Set(__L("form"));
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT_FORM::~UI_ELEMENT_FORM()
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
UI_ELEMENT_FORM::~UI_ELEMENT_FORM()    
{ 
  Clean();                            
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_COLOR* UI_ELEMENT_FORM::GetLineColor()
* @brief      GetLineColor
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     UI_COLOR* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_COLOR* UI_ELEMENT_FORM::GetLineColor()
{
  return &linecolor;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_BOUNDARYLINE* UI_ELEMENT_FORM::GetVisibleRect()
* @brief      GetVisibleRect
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     UI_BOUNDARYLINE* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_BOUNDARYLINE* UI_ELEMENT_FORM::GetVisibleRect()
{
  return &visiblerect;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_ELEMENT_FORM::Clean()
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
void UI_ELEMENT_FORM::Clean()
{
  roundvisiblerect = 0;    
}