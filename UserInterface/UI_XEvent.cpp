/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UI_XEvent.cpp
*
* @class      UI_XEVENT
* @brief      User Interface eXtended Event class
* @ingroup    XUTILS
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "UI_XEvent.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         UI_XEVENT::UI_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family)
* @brief      Constructor
* @ingroup    XUTILS
*
* @param[in]  subject :
* @param[in]  type :
* @param[in]  family :
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
UI_XEVENT::UI_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family) : XEVENT(subject, type, family)
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         UI_XEVENT::~UI_XEVENT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
UI_XEVENT::~UI_XEVENT()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD UI_XEVENT::GetXPos()
* @brief      GetXPos
* @ingroup    USERINTERFACE
*
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD UI_XEVENT::GetXPos()
{
  return xpos;
}
    


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_XEVENT::SetXPos(XDWORD xpos)
* @brief      SetXPos
* @ingroup    USERINTERFACE
*
* @param[in]  xpos : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_XEVENT::SetXPos(XDWORD xpos)
{
  this->xpos = xpos;
}


  
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD UI_XEVENT::GetYPos()
* @brief      GetYPos
* @ingroup    USERINTERFACE
*
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD UI_XEVENT::GetYPos()
{
  return ypos;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_XEVENT::SetYPos(XDWORD ypos)
* @brief      SetYPos
* @ingroup    USERINTERFACE
*
* @param[in]  ypos : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_XEVENT::SetYPos(XDWORD ypos)
{
  this->ypos = ypos;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_ELEMENT* UI_XEVENT::GetElement()
* @brief      GetElement
* @ingroup    USERINTERFACE
*
* @return     UI_ELEMENT* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_ELEMENT* UI_XEVENT::GetElement()
{
  return element;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         INPCURSORMOTION* UI_XEVENT::GetCursorMotion()
* @brief      GetCursorMotion
* @ingroup    USERINTERFACE
*
* @return     INPCURSORMOTION* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
INPCURSORMOTION* UI_XEVENT::GetCursorMotion()
{
  return cursormotion;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_XEVENT::SetCursorMotion(INPCURSORMOTION* cursormotion)
* @brief      SetCursorMotion
* @ingroup    USERINTERFACE
*
* @param[in]  cursormotion : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_XEVENT::SetCursorMotion(INPCURSORMOTION* cursormotion)
{
  this->cursormotion = cursormotion;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_XEVENT::SetElement(UI_ELEMENT* element)
* @brief      SetElement
* @ingroup    USERINTERFACE
*
* @param[in]  element : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_XEVENT::SetElement(UI_ELEMENT* element)
{
  if(!element) return false;

  this->element = element;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_SKIN* UI_XEVENT::GetSkin()
* @brief      GetSkin
* @ingroup    USERINTERFACE
*
* @return     UI_SKIN* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_SKIN* UI_XEVENT::GetSkin()
{
  return skin;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_XEVENT::SetSkin(UI_SKIN* skin)
* @brief      SetSkin
* @ingroup    USERINTERFACE
*
* @param[in]  skin : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_XEVENT::SetSkin(UI_SKIN* skin)
{
  this->skin = skin;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* UI_XEVENT::GetMaskTextValue()
* @brief      GetMaskTextValue
* @ingroup    USERINTERFACE
*
* @return     XSTRING* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XSTRING* UI_XEVENT::GetMaskTextValue()
{
  return &masktextvalue;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* UI_XEVENT::GetMaskText()
* @brief      GetMaskText
* @ingroup    USERINTERFACE
*
* @return     XSTRING* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XSTRING* UI_XEVENT::GetMaskTextResolved()
{
  return &masktextresolved;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void UI_XEVENT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void UI_XEVENT::Clean()
{
  xpos          = 0;
  ypos          = 0; 

  cursormotion  = NULL;

  element       = NULL; 
  skin          = NULL;
}




