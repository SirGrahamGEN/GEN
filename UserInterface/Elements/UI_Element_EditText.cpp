/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_Element_EditText.cpp
* 
* @class      UI_ELEMENT_EDITTEXT
* @brief      User Interface Element Edit Text class
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

#include "UI_Element_EditText.h"

#include "XFactory.h"
#include "XTimer.h"

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
* @fn         UI_ELEMENT_EDITTEXT::UI_ELEMENT_EDITTEXT()
* @brief      Constructor of class
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT_EDITTEXT::UI_ELEMENT_EDITTEXT()    
{ 
  Clean();   

  SetType(UI_ELEMENT_TYPE_EDITTEXT);
  GetTypeString()->Set(__L("edittext"));  

  GEN_XFACTORY_CREATE(cursor_xtimerblink, CreateTimer())
  cursor_timeblink   = UI_ELEMENT_EDITTEXT_DEFAULTCUSORTIMEBLINK;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT_EDITTEXT::~UI_ELEMENT_EDITTEXT()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT_EDITTEXT::~UI_ELEMENT_EDITTEXT()    
{ 
  if(cursor_xtimerblink)
    {
      GEN_XFACTORY.DeleteTimer(cursor_xtimerblink);
      cursor_xtimerblink = NULL;
    }

  Clean();                            
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_ELEMENT_EDITTEXT::Cursor_IsVisible()
* @brief      Cursor is visible
* @ingroup    USERINTERFACE
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_ELEMENT_EDITTEXT::Cursor_IsVisible()
{
  return cursor_isvisible;
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_ELEMENT_EDITTEXT::Cursor_SetVisible(bool on)
* @brief      Cursor set visible
* @ingroup    USERINTERFACE
*
* @param[in]  on : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_ELEMENT_EDITTEXT::Cursor_SetVisible(bool on)
{
  this->cursor_isvisible = on;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XTIMER* UI_ELEMENT_EDITTEXT::Cursor_GetXTimerBlink()
* @brief      Cursor get X timer blink
* @ingroup    USERINTERFACE
*
* @return     XTIMER* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XTIMER* UI_ELEMENT_EDITTEXT::Cursor_GetXTimerBlink()
{
  return cursor_xtimerblink;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD UI_ELEMENT_EDITTEXT::Cursor_GetTimeBlink()
* @brief      Cursor get time blink
* @ingroup    USERINTERFACE
*
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD UI_ELEMENT_EDITTEXT::Cursor_GetTimeBlink()
{
  return  cursor_timeblink;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_ELEMENT_EDITTEXT::Cursor_SetTimeBlink(XDWORD timeblink)
* @brief      Cursor set time blink
* @ingroup    USERINTERFACE
*
* @param[in]  timeblink : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_ELEMENT_EDITTEXT::Cursor_SetTimeBlink(XDWORD timeblink)
{
  this->cursor_timeblink = timeblink;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_ELEMENT_EDITTEXT::Cursor_GetStateBlink()
* @brief      Cursor get state blink
* @ingroup    USERINTERFACE
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_ELEMENT_EDITTEXT::Cursor_GetStateBlink()
{
  return cursor_stateblink;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_ELEMENT_EDITTEXT::Cursor_ChangeStateBlink()
* @brief      Cursor change state blink
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
void  UI_ELEMENT_EDITTEXT::Cursor_ChangeStateBlink()
{
  cursor_stateblink =!cursor_stateblink;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_ELEMENT_EDITTEXT::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_ELEMENT_EDITTEXT::Clean()
{
  cursor_isvisible    = false;
  cursor_xtimerblink  = NULL;
  cursor_timeblink    = 0;
  cursor_stateblink   = false;
}


#pragma endregion
