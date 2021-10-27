/**-------------------------------------------------------------------------------------------------------------------
*
* @file       INPDevice.cpp
*
* @class      INPDEVICE
* @brief      Input Device Class
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @copyright  Copyright(c) 2008 - 2016 GEN Group.
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
*---------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

#include "XVector.h"

#include "INPButton.h"
#include "INPCursor.h"

#include "INPDevice.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPDEVICE::INPDEVICE()
* @brief      Constructor
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
INPDEVICE::INPDEVICE()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPDEVICE::~INPDEVICE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
INPDEVICE::~INPDEVICE()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPDEVICE::IsCreated()
* @brief      Is Created
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool INPDEVICE::IsCreated()
{
  return created;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPDEVICE::IsEnabled()
* @brief      Is Enabled
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool INPDEVICE::IsEnabled()
{
  return enabled;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void INPDEVICE::SetEnabled(bool ON)
* @brief      Set Enabled
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  ON : true enabled.
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void INPDEVICE::SetEnabled(bool enabled)
{
  this->enabled  = enabled;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPDEVICE_TYPE INPDEVICE::GetType()
* @brief      Get Type
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     INPDEVICE_TYPE : type of device
*
*---------------------------------------------------------------------------------------------------------------------*/
INPDEVICE_TYPE INPDEVICE::GetType()
{
  return type;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void INPDEVICE::SetType(INPDEVICE_TYPE type)
* @brief      Set Type
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  type : type of device
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void INPDEVICE::SetType(INPDEVICE_TYPE type)
{
  this->type = type;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int INPDEVICE::GetNButtons()
* @brief      Get Numbers Buttons
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     int : Numbers Buttons
*
*---------------------------------------------------------------------------------------------------------------------*/
int INPDEVICE::GetNButtons()
{
  XVECTOR<INPBUTTON*>* buttons = GetButtons();
  if(!buttons) return 0;

  return buttons->GetSize();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XVECTOR<INPBUTTON*>* INPDEVICE::GetButtons()
* @brief      Get Buttons
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XVECTOR<INPBUTTON*>* : vector of buttons
*
*---------------------------------------------------------------------------------------------------------------------*/
XVECTOR<INPBUTTON*>* INPDEVICE::GetButtons()
{
  return &buttons;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XVECTOR<INPCURSOR*>* INPDEVICE::GetCursors()
* @brief      Get Cursors
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XVECTOR<INPCURSOR*>* : vector of cursors
*
*---------------------------------------------------------------------------------------------------------------------*/
XVECTOR<INPCURSOR*>* INPDEVICE::GetCursors()
{
  return &cursors;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPDEVICE::DeleteAllButtons()
* @brief      Delete All Buttons
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool INPDEVICE::DeleteAllButtons()
{
  if(buttons.IsEmpty())  return false;

  buttons.DeleteContents();
  buttons.DeleteAll();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPDEVICE::DeleteAllCursors()
* @brief      Delete All Cursors
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool INPDEVICE::DeleteAllCursors()
{
  if(cursors.IsEmpty())  return false;

  cursors.DeleteContentsInstanced();
  cursors.DeleteAll();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPBUTTON* INPDEVICE::GetButton(INPBUTTON_ID ID)
* @brief      Get Button
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  ID : ID of button
*
* @return     INPBUTTON* : button class obtain
*
*---------------------------------------------------------------------------------------------------------------------*/
INPBUTTON* INPDEVICE::GetButton(INPBUTTON_ID ID)
{
  XVECTOR<INPBUTTON*>* buttons = GetButtons();
  if(!buttons) return NULL;

  XDWORD size=buttons->GetSize();
  for(XDWORD c=0;c<size;c++)
    {
      INPBUTTON*  button = (INPBUTTON*)buttons->FastGet(c);
      if(button)
          if(button->GetID() == ID)
              return button;
    }

  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPBUTTON* INPDEVICE::GetButton(int index)
* @brief      Get Button
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  index : index of button
*
* @return     INPBUTTON* : button class obtain
*
*---------------------------------------------------------------------------------------------------------------------*/
INPBUTTON* INPDEVICE::GetButton(int index)
{
  XVECTOR<INPBUTTON*>* buttons = GetButtons();
  if(!buttons) return NULL;

  if(buttons->IsEmpty())          return NULL;
  if(index>=(int)buttons->GetSize()) return NULL;
  if(index<0)                     return NULL;

  return (INPBUTTON*)buttons->Get(index);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPBUTTON* INPDEVICE::GetButtonByCode(XWORD code)
* @brief      Get Button By Code
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  code : code of button
*
* @return     INPBUTTON* : button class obtain
*
*---------------------------------------------------------------------------------------------------------------------*/
INPBUTTON* INPDEVICE::GetButtonByCode(XWORD code)
{
  XVECTOR<INPBUTTON*>* buttons = GetButtons();
  if(!buttons) return NULL;

  if(buttons->IsEmpty()) return NULL;

  for(XDWORD c=0;c<buttons->GetSize();c++)
    {
      INPBUTTON*  button = (INPBUTTON*)buttons->Get(c);
      if(button)
        {
          if(button->GetKeyCode() == code) return button;
        }
    }

  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPBUTTON_STATE INPDEVICE::GetButtonState(INPBUTTON_ID ID)
* @brief      Get Button State
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  ID : ID of button
*
* @return     INPBUTTON_STATE : state of button obtain
*
*---------------------------------------------------------------------------------------------------------------------*/
INPBUTTON_STATE INPDEVICE::GetButtonState(INPBUTTON_ID ID)
{
  XVECTOR<INPBUTTON*>* buttons = GetButtons();

  if(!buttons) return INPBUTTON_STATE_UNKNOWN;

  XDWORD size = buttons->GetSize();
  for(XDWORD c=0; c<size; c++)
    {
      INPBUTTON*  button = (INPBUTTON*)buttons->FastGet(c);
      if(button)
        {
          if (button->GetID() == ID) return button->GetState();
        }
    }

  return INPBUTTON_STATE_UNKNOWN;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPBUTTON* INPDEVICE::IsPressButton()
* @brief      Is Press Button
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     INPBUTTON* : button class obtain
*
*---------------------------------------------------------------------------------------------------------------------*/
INPBUTTON* INPDEVICE::IsPressButton()
{
  XVECTOR<INPBUTTON*>* buttons = GetButtons();
  if(!buttons) return NULL;

  for(int c=0;c<(int)buttons->GetSize();c++)
    {
      INPBUTTON* button = GetButton(c);
      if(button)
        {
          if(button->IsPressed()) return button;
        }
    }

  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPDEVICE::ReleaseAllButtons()
* @brief      Release All Buttons
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool INPDEVICE::ReleaseAllButtons()
{
  for(XDWORD c=0;c<buttons.GetSize();c++)
    {
      INPBUTTON* button = (INPBUTTON*)buttons.Get(c);

      if(button)
        {
          button->SetPressed(false);
        }
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int INPDEVICE::GetNCursors()
* @brief      Get Number of Cursors
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     int : Number of Cursors
*
*---------------------------------------------------------------------------------------------------------------------*/
int INPDEVICE::GetNCursors()
{
  XVECTOR<INPCURSOR*>* cursors = GetCursors();
  if(!cursors) return 0;

  return cursors->GetSize();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPCURSOR* INPDEVICE::GetCursor(INPCURSOR_ID ID)
* @brief      Get Cursor
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  ID : id of cursor
*
* @return     INPCURSOR* : cursor class obtain
*
*---------------------------------------------------------------------------------------------------------------------*/
INPCURSOR* INPDEVICE::GetCursor(INPCURSOR_ID ID)
{
  XVECTOR<INPCURSOR*>* cursors = GetCursors();
  if(!cursors) return NULL;

  if(cursors->IsEmpty()) return NULL;

  for(XDWORD c=0;c<cursors->GetSize();c++)
    {
      INPCURSOR* cursor = (INPCURSOR*)cursors->Get(c);
      if(cursor)
        {
          if(cursor->GetID() == ID) return cursor;
        }
    }

  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPCURSOR* INPDEVICE::GetCursor(int index)
* @brief      Get Cursor
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  index : index of cursor
*
* @return     INPCURSOR* : cursor class obtain
*
*---------------------------------------------------------------------------------------------------------------------*/
INPCURSOR* INPDEVICE::GetCursor(int index)
{
  XVECTOR<INPCURSOR*>* cursors = GetCursors();
  if(!cursors) return NULL;

  if(cursors->IsEmpty())          return NULL;
  if(index>=(int)cursors->GetSize()) return NULL;
  if(index<0)                     return NULL;

  return (INPCURSOR*)cursors->Get(index);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPCURSOR* INPDEVICE::IsChangeCursor()
* @brief      Is Change Cursor
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     INPCURSOR* : cursor class obtain
*
*---------------------------------------------------------------------------------------------------------------------*/
INPCURSOR* INPDEVICE::IsChangeCursor()
{
  XVECTOR<INPCURSOR*>* cursors = GetCursors();
  if(!cursors) return NULL;

  for(int c=0;c<(int)cursors->GetSize();c++)
    {
      INPCURSOR* cursor = GetCursor(c);
      if(cursor)
        {
          if(cursor->IsChanged()) return cursor;
        }
    }

  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPDEVICE::SetScreen(void* param)
* @brief      Set Screen handle
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  param : screen handle (void*)
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool INPDEVICE::SetScreen(void* param)
{
  if(param) grpscreen = static_cast<GRPSCREEN*>(param);

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPDEVICE::Release()
* @brief      Release Device
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool INPDEVICE::Release()
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPDEVICE::Update()
* @brief      Update Device
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool INPDEVICE::Update()
{
  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPDEVICE::AddPosition(int index, float x, float y, bool ispressed)
* @brief      AddPosition
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  index :
* @param[in]  x :
* @param[in]  y :
* @param[in]  ispressed :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
/*
bool INPDEVICE::AddPosition(int index, float x, float y, bool ispressed)
{
  return false;
}
*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void INPDEVICE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    INPUT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void INPDEVICE::Clean()
{
  created   = false;
  enabled   = false;

  type      = INPDEVICE_TYPE_NONE;

  grpscreen = NULL;
}
