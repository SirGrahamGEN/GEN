/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_Property_Editable.cpp
* 
* @class      UI_PROPERTY_EDITABLE
* @brief      User Interface Property Editable class
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

#include "UI_Property_Editable.h"

#include "GRPBitmap.h"

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
* @fn         UI_PROPERTY_EDITABLE::UI_PROPERTY_EDITABLE()
* @brief      Constructor of class
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
UI_PROPERTY_EDITABLE::UI_PROPERTY_EDITABLE()    
{ 
  Clean();   
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_PROPERTY_EDITABLE::~UI_PROPERTY_EDITABLE()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
UI_PROPERTY_EDITABLE::~UI_PROPERTY_EDITABLE()    
{   
  Clean();                            
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD UI_PROPERTY_EDITABLE::Cursor_GetPosition()
* @brief      Cursor get position
* @ingroup    USERINTERFACE
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD UI_PROPERTY_EDITABLE::Cursor_GetPosition()
{
  return cursor_position;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_PROPERTY_EDITABLE::Cursor_SetPosition(XDWORD cursor_position)
* @brief      Cursor set position
* @ingroup    USERINTERFACE
* 
* @param[in]  cursor_position : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void UI_PROPERTY_EDITABLE::Cursor_SetPosition(XDWORD cursor_position)
{
  this->cursor_position = cursor_position;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD UI_PROPERTY_EDITABLE::GetMaxSize()
* @brief      Get max size
* @ingroup    USERINTERFACE
*
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD UI_PROPERTY_EDITABLE::GetMaxSize()
{
  return maxsize;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_PROPERTY_EDITABLE::SetMaxSize(XDWORD maxsize)
* @brief      Set max size
* @ingroup    USERINTERFACE
* 
* @param[in]  maxsize : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void UI_PROPERTY_EDITABLE::SetMaxSize(XDWORD maxsize)
{
  this->maxsize = maxsize;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_PROPERTY_EDITABLE::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_PROPERTY_EDITABLE::Clean()
{
  cursor_position   = 0;
  maxsize           = 0;
}


#pragma endregion





