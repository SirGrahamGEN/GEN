/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       INPANDROIDDeviceMouse.cpp
* 
* @class      INPANDROIDDEVICEMOUSE
* @brief      ANDROID input device mouse class
* @ingroup    PLATFORM_ANDROID
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

#include "INPANDROIDDeviceMouse.h"

#include "GRPANDROIDScreen.h"

#include "INPButton.h"
#include "INPCursor.h"

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
* @fn         INPANDROIDDEVICEMOUSE::INPANDROIDDEVICEMOUSE(GRPANDROIDSCREEN* grpscreen)
* @brief      Constructor of class
* @ingroup    PLATFORM_ANDROID
* 
* @param[in]  grpscreen : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
INPANDROIDDEVICEMOUSE::INPANDROIDDEVICEMOUSE(GRPANDROIDSCREEN* grpscreen)
{
  Clean();

  SetType(INPDEVICE_TYPE_MOUSE);

  created = true;

  SetScreen(grpscreen);

  if(CreateAllCursors() &&  CreateAllButtons())  SetEnabled(true);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPANDROIDDEVICEMOUSE::~INPANDROIDDEVICEMOUSE()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    PLATFORM_ANDROID
*
* --------------------------------------------------------------------------------------------------------------------*/
INPANDROIDDEVICEMOUSE::~INPANDROIDDEVICEMOUSE()
{
  DeleteAllButtons();
  DeleteAllCursors();

  SetEnabled(false);
  created = false;

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPANDROIDDEVICEMOUSE::Update()
* @brief      Update
* @ingroup    PLATFORM_ANDROID
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool INPANDROIDDEVICEMOUSE::Update()
{
  if(!IsEnabled()) return false;

  for (XDWORD e=0;e<this->buttons.GetSize();e++)
    {
      if (buttons.Get(e))
      if (buttons.Get(e)->GetState() == INPBUTTON_STATE_RELEASED)  buttons.Get(e)->SetState(INPBUTTON_STATE_UP);
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPANDROIDDEVICEMOUSE::SetScreen(void* screenpointer)
* @brief      Set screen
* @ingroup    PLATFORM_ANDROID
*
* @param[in]  screenpointer :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool INPANDROIDDEVICEMOUSE::SetScreen(void* screenpointer)
{
  grpscreen = static_cast<GRPANDROIDSCREEN*>(screenpointer);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPANDROIDDEVICEMOUSE::AddPosition(int index, float x, float y, bool ispressed)
* @brief      Add position
* @ingroup    PLATFORM_ANDROID
* 
* @param[in]  index : 
* @param[in]  x : 
* @param[in]  y : 
* @param[in]  ispressed : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPANDROIDDEVICEMOUSE::AddPosition(int index, float x, float y, bool ispressed)
{
  if(!grpscreen) return false;

  INPCURSOR* cursor = GetCursor(index);
  if(!cursor) return false;

  cursor->SetIsChanged(false);

  if((cursor->GetX() != x) || (cursor->GetY() != y))
    {
      GRPANDROIDSCREEN* _grpscreen = (GRPANDROIDSCREEN*)grpscreen;

      // to place the origin coordinates top left instead of bottom left
      y = (_grpscreen->GetHeight()) - y;

      cursor->Set(x,y);
      cursor->SetIsChanged(true);
    }

  cursor->AddPointToMotion(ispressed);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void INPANDROIDDEVICEMOUSE::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    PLATFORM_ANDROID
*
* --------------------------------------------------------------------------------------------------------------------*/
void INPANDROIDDEVICEMOUSE::Clean()
{
  grpscreen = NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPANDROIDDEVICEMOUSE::CreateAllButtons()
* @brief      Create all buttons
* @ingroup    PLATFORM_ANDROID
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool INPANDROIDDEVICEMOUSE::CreateAllButtons()
{
  INPBUTTON::CreateButton( &buttons, 0  , INPBUTTON_ID_MOUSE_LEFT   , __C('\x0'));
  INPBUTTON::CreateButton( &buttons, 1  , INPBUTTON_ID_MOUSE_RIGHT  , __C('\x0'));
  INPBUTTON::CreateButton( &buttons, 2  , INPBUTTON_ID_MOUSE_MIDDLE , __C('\x0'));
  INPBUTTON::CreateButton( &buttons, 3  , INPBUTTON_ID_MOUSE_MIDDLE , __C('\x0'));
  INPBUTTON::CreateButton( &buttons, 4  , INPBUTTON_ID_MOUSE_MIDDLE , __C('\x0'));

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPANDROIDDEVICEMOUSE::CreateAllCursors()
* @brief      Create all cursors
* @ingroup    PLATFORM_ANDROID
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPANDROIDDEVICEMOUSE::CreateAllCursors()
{
  INPCURSOR* cursor;

  for(int c=0;c<5;c++)
    {
      cursor = new INPCURSOR();
      if(!cursor) return false;

      cursor->SetID(INPCURSOR_ID(INPCURSOR_ID_MOUSE+c));
      cursor->SetHavePreSelect(false);
      cursors.Add(cursor);
    }

  return true;
}


#pragma endregion

