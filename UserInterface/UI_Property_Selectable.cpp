/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_Property_Selectable.cpp
* 
* @class      UI_PROPERTY_SELECTABLE
* @brief      User Interface Property Selectable class
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

#include "XFactory.h"

#include "GRPBitmap.h"

#include "UI_Property_Selectable.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_PROPERTY_SELECTABLE::UI_PROPERTY_SELECTABLE()
* @brief      Constructor
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_PROPERTY_SELECTABLE::UI_PROPERTY_SELECTABLE()    
{ 
  Clean(); 

  xtimerselected = GEN_XFACTORY.CreateTimer();
  timeselected   = UI_PROPERTY_SELECTABLE_DEFAULT_TIMESELECTED; 
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_PROPERTY_SELECTABLE::~UI_PROPERTY_SELECTABLE()
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
UI_PROPERTY_SELECTABLE::~UI_PROPERTY_SELECTABLE()    
{   
  if(xtimerselected) 
    {
      GEN_XFACTORY.DeleteTimer(xtimerselected);
      xtimerselected = NULL;
    }

  Clean();                            
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD UI_PROPERTY_SELECTABLE::GetTimeSelected()
* @brief      GetTimeSelected
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD UI_PROPERTY_SELECTABLE::GetTimeSelected()
{
  return timeselected;
}																		



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_PROPERTY_SELECTABLE::SetTimeSelected(XDWORD timeselected)
* @brief      SetTimeSelected
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  timeselected : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_PROPERTY_SELECTABLE::SetTimeSelected(XDWORD timeselected)
{
  this->timeselected = timeselected;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XTIMER* UI_PROPERTY_SELECTABLE::GetXTimerSelected()
* @brief      GetXTimerSelected
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     XTIMER* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XTIMER* UI_PROPERTY_SELECTABLE::GetXTimerSelected()
{
  return xtimerselected;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_PROPERTY_SELECTABLE_STATE UI_PROPERTY_SELECTABLE::GetSelectableState()
* @brief      GetSelectableState
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     UI_PROPERTY_SELECTABLE_STATE : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_PROPERTY_SELECTABLE_STATE UI_PROPERTY_SELECTABLE::GetSelectableState()
{
  return selectable_state;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_PROPERTY_SELECTABLE::SetSelectableState(UI_PROPERTY_SELECTABLE_STATE state)
* @brief      SetSelectableState
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  state : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_PROPERTY_SELECTABLE::SetSelectableState(UI_PROPERTY_SELECTABLE_STATE state)
{
  this->selectable_state = state;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_PROPERTY_SELECTABLE_STATE UI_PROPERTY_SELECTABLE::SetSelectableStateFromString(XCHAR* selectablestr)
* @brief      SetSelectableStateFromString
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  selectablestr : 
* 
* @return     UI_PROPERTY_SELECTABLE_STATE : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_PROPERTY_SELECTABLE_STATE UI_PROPERTY_SELECTABLE::SetSelectableStateFromString(XCHAR* selectablestr)
{ 
  if(!selectablestr)  return UI_PROPERTY_SELECTABLE_STATE_DEACTIVE;

  XSTRING _selectablestr;
  
  selectable_state = UI_PROPERTY_SELECTABLE_STATE_DEACTIVE;
  
  _selectablestr = selectablestr;

  if(!_selectablestr.Compare(__L("active"), true))  selectable_state = UI_PROPERTY_SELECTABLE_STATE_ACTIVE;
    else if(!_selectablestr.Compare(__L("deactive"), true))  selectable_state = UI_PROPERTY_SELECTABLE_STATE_DEACTIVE;
      else if(!_selectablestr.Compare(__L("preselect"), true)) selectable_state = UI_PROPERTY_SELECTABLE_STATE_PRESELECT;
         else if(!_selectablestr.Compare(__L("selected"), true)) selectable_state = UI_PROPERTY_SELECTABLE_STATE_SELECTED;
  
  return selectable_state;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_PROPERTY_SELECTABLE_STATE UI_PROPERTY_SELECTABLE::SetSelectableStateFromString(XSTRING& selectablestr)
* @brief      SetSelectableStateFromString
* @ingroup    USERINTERFACE
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  selectablestr : 
* 
* @return     UI_PROPERTY_SELECTABLE_STATE : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_PROPERTY_SELECTABLE_STATE UI_PROPERTY_SELECTABLE::SetSelectableStateFromString(XSTRING& selectablestr)
{
  return SetSelectableStateFromString(selectablestr.Get());

}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_PROPERTY_SELECTABLE::Clean()
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
void UI_PROPERTY_SELECTABLE::Clean()
{  
  selectable_state = UI_PROPERTY_SELECTABLE_STATE_DEACTIVE;

  xtimerselected   = NULL;		
	timeselected     = 0; 
}