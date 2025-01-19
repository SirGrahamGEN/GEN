/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       INPLINUXDeviceMouseX11.cpp
* 
* @class      INPLINUXDEVICEMOUSEX11
* @brief      LINUX Input X11 device mouse class
* @ingroup    PLATFORM_LINUX
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


#ifdef LINUX_X11_ACTIVE


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "INPLINUXDeviceMouseX11.h"

#include <unistd.h>
#include <locale.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>

#include "GRPLINUXScreenX11.h"

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
* @fn         INPLINUXDEVICEMOUSEX11::INPLINUXDEVICEMOUSEX11()
* @brief      Constructor of class
* @ingroup    PLATFORM_LINUX
*
* --------------------------------------------------------------------------------------------------------------------*/
INPLINUXDEVICEMOUSEX11::INPLINUXDEVICEMOUSEX11() : INPDEVICE()
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
* @fn         INPLINUXDEVICEMOUSEX11::~INPLINUXDEVICEMOUSEX11()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    PLATFORM_LINUX
*
* --------------------------------------------------------------------------------------------------------------------*/
INPLINUXDEVICEMOUSEX11::~INPLINUXDEVICEMOUSEX11()
{  
  // Window root = DefaultRootWindow(grpscreenx11->GetDisplay());
  // XUngrabButton(grpscreenx11->GetDisplay(), AnyButton, AnyModifier, root);
 
  SetEnabled(false);
  created = false;

  DeleteAllButtons();
  DeleteAllCursors();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPLINUXDEVICEMOUSEX11::Update()
* @brief      Update
* @ingroup    PLATFORM_LINUX
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool INPLINUXDEVICEMOUSEX11::Update()
{
  if(!created || !enabled) 
    {
      return false;
    }

  if(!grpscreenx11)               
    {
      return false;
    }

  if(!grpscreenx11->HasFocus())   
    {
      return false;
    }  
  
  Display*     display = grpscreenx11->GetDisplay();
  Window       root;
  Window       child;
  int          rootx;
  int          rooty;
  int          mousex  = -1;
  int          mousey  = -1;
  unsigned int mask;

  XQueryPointer(display, (*grpscreenx11->GetWindow()), &root, &child, &rootx, &rooty, &mousex, &mousey, &mask);

  INPCURSOR* cursor = GetCursor(INPCURSOR_ID_MOUSE);
  if(cursor)
    {
      if((mousex>=0)&&(mousey>=0)&&(mousex < grpscreenx11->GetWidth()) && (mousey < grpscreenx11->GetHeight()))
        {
          cursor->SetIsChanged(false);

          if((cursor->GetX() != mousex) || (cursor->GetY() != mousey))
            {
              mousey = (grpscreenx11->GetHeight()-mousey);
              cursor->Set(mousex,mousey);
              cursor->SetIsChanged(true);
            }
        }
       else
        {
          mousex = -1;
          mousey = -1;

          cursor->Set(mousex,mousey);
          cursor->SetIsChanged(true);
        }

      INPBUTTON* button = GetButton(INPBUTTON_ID_MOUSE_LEFT);
      if(button) cursor->AddPointToMotion(button->IsPressed());
    }

  //-------------------------------------------------------------
  // Read Buttons

  for(XDWORD c=0; c<buttons.GetSize(); c++)
    {
      INPBUTTON* button=buttons.Get(c);
      if(button)
        {
          if(button->GetState() == INPBUTTON_STATE_RELEASED)
            {
              button->SetState(INPBUTTON_STATE_UP);
            }
           else
            {
              if(button->GetState() == INPBUTTON_STATE_PRESSED) 
                {
                  button->SetState(INPBUTTON_STATE_HOLD);
                }
            }
        }
    }
    
  XEvent event; 
 
  if(XPending(display))
    {       
      XNextEvent(display, &event);
    
      switch(event.type)
        {
          case ButtonPress   : {  INPBUTTON* button = GetButtonByCode(event.xbutton.button);
                                  if(button)
                                    {
                                      switch (button->GetState())
                                        {
                                          case INPBUTTON_STATE_UP:       button->SetState(INPBUTTON_STATE_PRESSED);  break;
                                          case INPBUTTON_STATE_HOLD:     button->SetState(INPBUTTON_STATE_HOLD);     break;
                                          case INPBUTTON_STATE_PRESSED:  button->SetState(INPBUTTON_STATE_HOLD);     break;
                                          case INPBUTTON_STATE_RELEASED: button->SetState(INPBUTTON_STATE_PRESSED);  break;
                                        }

                                      button->SetPressed(true);
                                    }
                                }
                                break;

          case ButtonRelease : {  INPBUTTON* button = GetButtonByCode(event.xbutton.button);
                                  if(button)
                                    {
                                      switch (button->GetState())
                                        {
                                          case INPBUTTON_STATE_UP:       button->SetState(INPBUTTON_STATE_UP);       break;
                                          case INPBUTTON_STATE_HOLD:     button->SetState(INPBUTTON_STATE_RELEASED); break;
                                          case INPBUTTON_STATE_PRESSED:  button->SetState(INPBUTTON_STATE_RELEASED); break;
                                          case INPBUTTON_STATE_RELEASED: button->SetState(INPBUTTON_STATE_RELEASED); break;
                                        }

                                      button->SetPressed(false);
                                    }
                                }
                                break;
        }
    }


  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPLINUXDEVICEMOUSEX11::SetScreen(void* screenhandle)
* @brief      Set screen
* @ingroup    PLATFORM_LINUX
*
* @param[in]  screenhandle : handle to screen
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool INPLINUXDEVICEMOUSEX11::SetScreen(void* screenhandle)
{
  grpscreenx11 = (GRPLINUXSCREENX11*)screenhandle;
  if(!grpscreenx11) 
    {
      return false;
    }
    
  XSelectInput(grpscreenx11->GetDisplay(), (*grpscreenx11->GetWindow()), KeyPressMask | KeyReleaseMask);

  XGrabButton(grpscreenx11->GetDisplay(), AnyButton, AnyModifier, (*grpscreenx11->GetWindowRoot()), False, ButtonPressMask | ButtonReleaseMask, GrabModeAsync, GrabModeAsync, None, None);  
    
  // XSetWindowAttributes attr;
  // attr.event_mask = ButtonPressMask | ButtonReleaseMask;  
  // XChangeWindowAttributes(grpscreenx11->GetDisplay(), (*grpscreenx11->GetWindowRoot()), CWEventMask, &attr);
   
  XFlush(grpscreenx11->GetDisplay());

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void INPLINUXDEVICEMOUSEX11::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    PLATFORM_LINUX
*
* --------------------------------------------------------------------------------------------------------------------*/
void INPLINUXDEVICEMOUSEX11::Clean()
{ 
  grpscreenx11  = NULL;  
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPLINUXDEVICEMOUSEX11::CreateAllButtons()
* @brief      Create all buttons
* @note       INTERNAL
* @ingroup    PLATFORM_LINUX
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool INPLINUXDEVICEMOUSEX11::CreateAllButtons()
{
  INPBUTTON::CreateButton( &buttons, Button3   , INPBUTTON_ID_MOUSE_RIGHT      , __C('\x0'));
  INPBUTTON::CreateButton( &buttons, Button1   , INPBUTTON_ID_MOUSE_LEFT       , __C('\x0'));
  INPBUTTON::CreateButton( &buttons, Button2   , INPBUTTON_ID_MOUSE_MIDDLE     , __C('\x0'));

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPLINUXDEVICEMOUSEX11::CreateAllCursors()
* @brief      Create all cursors
* @note       INTERNAL
* @ingroup    PLATFORM_LINUX
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool INPLINUXDEVICEMOUSEX11::CreateAllCursors()
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


#endif

