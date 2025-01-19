/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_Element_ListBox.cpp
* 
* @class      UI_ELEMENT_LISTBOX
* @brief      User Interface Element List Box class
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

#include "UI_Element_ListBox.h"

#include "UI_Element_Menu.h"

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
* @fn         UI_ELEMENT_LISTBOX::UI_ELEMENT_LISTBOX()
* @brief      Constructor of class
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT_LISTBOX::UI_ELEMENT_LISTBOX()    
{ 
  Clean();   

  SetType(UI_ELEMENT_TYPE_LISTBOX);
  GetTypeString()->Set(__L("listbox"));  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT_LISTBOX::~UI_ELEMENT_LISTBOX()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT_LISTBOX::~UI_ELEMENT_LISTBOX()    
{ 
  Clean();                            
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT_MENU* UI_ELEMENT_LISTBOX::Get_UIMenu()
* @brief      Get UI menu
* @ingroup    USERINTERFACE
*
* @return     UI_ELEMENT_MENU* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT_MENU* UI_ELEMENT_LISTBOX::Get_UIMenu()
{
  return UImenu;
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_ELEMENT_LISTBOX::Set_UIMenu(UI_ELEMENT_MENU* element_menu)
* @brief      Set UI menu
* @ingroup    USERINTERFACE
*
* @param[in]  element_menu : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_ELEMENT_LISTBOX::Set_UIMenu(UI_ELEMENT_MENU* element_menu)
{
  UImenu = element_menu;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_ELEMENT_LISTBOX::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_ELEMENT_LISTBOX::Clean()
{
  UImenu  = NULL;   
}


#pragma endregion

