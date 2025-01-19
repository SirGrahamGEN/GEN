/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       INPWINDOWSDeviceMouse.cpp
* 
* @class      INPWINDOWSDEVICEMOUSE
* @brief      WINDOWS Input Device Mouse class
* @ingroup    PLATFORM_WINDOWS
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

#include "INPWINDOWSDeviceMouse.h"

#include <windows.h>

#include "GRPWINDOWSScreen.h"

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
* @fn         INPWINDOWSDEVICEMOUSE::INPWINDOWSDEVICEMOUSE()
* @brief      Constructor of class
* @ingroup    PLATFORM_WINDOWS
*
* --------------------------------------------------------------------------------------------------------------------*/
INPWINDOWSDEVICEMOUSE::INPWINDOWSDEVICEMOUSE(): INPDEVICE()
{
  Clean();

  SetType(INPDEVICE_TYPE_MOUSE);

  created = true;

  if(CreateAllButtons())
    {
      if(CreateAllCursors())
        {
          SetEnabled(true);
        }
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPWINDOWSDEVICEMOUSE::~INPWINDOWSDEVICEMOUSE()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    PLATFORM_WINDOWS
*
* --------------------------------------------------------------------------------------------------------------------*/
INPWINDOWSDEVICEMOUSE::~INPWINDOWSDEVICEMOUSE()
{
  DeleteAllButtons();
  DeleteAllCursors();

  SetEnabled(false);
  created = false;

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPWINDOWSDEVICEMOUSE::Update()
* @brief      Update
* @ingroup    PLATFORM_WINDOWS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool INPWINDOWSDEVICEMOUSE::Update()
{
  if(!IsEnabled()) return false;

  if(grpscreen)
    {
      if(grpscreen->GetHandle()!=GetForegroundWindow())
        {
          if(!grpscreen->Style_Is(GRPSCREENSTYLE_ONTOP))
            {
              return false;
            }
        }
    }

  float x=0.0f;
  float y=0.0f;

  POINT point;
  if(GetCursorPos(&point))
    {
      int screenx;
      int screeny;
      int screenw;
      int screenh;

      if(GetWindowPosition(screenx,screeny,screenw,screenh))
        {
          x = (float)(point.x - screenx);
          y = (float)(screeny - point.y);

          if((x<0)||(y<0)||(x>screenw)||(y>screenh))
            {
              x = -1;
              y = -1;
            }
        }
    }
  
  for(XDWORD c=0; c<buttons.GetSize(); c++)
    {
      INPBUTTON* button = buttons.Get(c);
      if(button)
        {
          INPCURSOR* cursor = cursors.Get(c);
          if(cursor)
            {
              if(x!=cursor->GetX() || y!=cursor->GetY())
                {
                  cursor->SetIsChanged(true);
                  cursor->SetX(x);
                  cursor->SetY(y);
                }
               else cursor->SetIsChanged(false);
            }


          SHORT state = GetAsyncKeyState(button->GetKeyCode());
          if(state & 0x8000) //key down
            {
              if(state & 0x01) //changed
                {
                  button->SetPressed(true);

                  if(button->GetState()!=INPBUTTON_STATE_HOLD)  button->SetState(INPBUTTON_STATE_PRESSED);

                  if(cursor) cursor->AddPointToMotion(true);
                }
               else
                {
                  button->SetPressed(true);

                  button->SetState(INPBUTTON_STATE_HOLD);

                  if(cursor) cursor->AddPointToMotion(true);
                }
            }
           else
            {
              button->SetPressed(false);

              if (button->GetState() == INPBUTTON_STATE_HOLD || button->GetState() == INPBUTTON_STATE_PRESSED) //changed
                     button->SetState(INPBUTTON_STATE_RELEASED);
                else button->SetState(INPBUTTON_STATE_UP);

              if(cursor) cursor->AddPointToMotion(false);
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void INPWINDOWSDEVICEMOUSE::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    PLATFORM_WINDOWS
*
* --------------------------------------------------------------------------------------------------------------------*/
void INPWINDOWSDEVICEMOUSE::Clean()
{

}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPWINDOWSDEVICEMOUSE::GetWindowPosition(int& screenx,int& screeny,int& screenw,int& screenh)
* @brief      Get window position
* @note       INTERNAL
* @ingroup    PLATFORM_WINDOWS
*
* @param[out]  screenx : x position of screen
* @param[out]  screeny : y position of screen
* @param[out]  screenw : width of screen
* @param[out]  screenh : height of screen
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool INPWINDOWSDEVICEMOUSE::GetWindowPosition(int& screenx,int& screeny,int& screenw,int& screenh)
{
  if(!grpscreen) return false;

  WINDOWINFO info;

  GetWindowInfo((HWND)grpscreen->GetHandle(),&info);

  screenx = info.rcClient.left;
  screeny = info.rcClient.bottom;

  screenw = abs(info.rcClient.right  - info.rcClient.left);
  screenh = abs(info.rcClient.bottom - info.rcClient.top);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPWINDOWSDEVICEMOUSE::CreateAllButtons()
* @brief      Create all buttons
* @note       INTERNAL
* @ingroup    PLATFORM_WINDOWS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool INPWINDOWSDEVICEMOUSE::CreateAllButtons()
{ 
  INPBUTTON::CreateButton( &buttons, VK_LBUTTON , INPBUTTON_ID_MOUSE_LEFT      , __C('\x0'));
  INPBUTTON::CreateButton( &buttons, VK_RBUTTON , INPBUTTON_ID_MOUSE_RIGHT     , __C('\x0')); 
  INPBUTTON::CreateButton( &buttons, VK_MBUTTON , INPBUTTON_ID_MOUSE_MIDDLE    , __C('\x0'));

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPWINDOWSDEVICEMOUSE::CreateAllCursors()
* @brief      Create all cursors
* @note       INTERNAL
* @ingroup    PLATFORM_WINDOWS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool INPWINDOWSDEVICEMOUSE::CreateAllCursors()
{
  INPCURSOR* cursor;

  cursor = new INPCURSOR();
  if(!cursor) return false;

  cursor->SetID(INPCURSOR_ID_MOUSE);
  cursor->SetHavePreSelect(true);

  cursors.Add(cursor);

  return true;
}


#pragma endregion

