/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       INPWINDOWSKeyboardHook.cpp
* 
* @class      INPWINDOWSKEYBOARDHOOK
* @brief      Input WINDOWS Keyboard Hook Class
* @ingroup    PLATFORM_WINDOWS
* 
* @copyright  Copyright(c) 2005 - 2022 GEN Group.
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
* -------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <shlwapi.h>

#include "XFactory.h"
#include "XBuffer.h"
#include "XPathsManager.h"
#include "XPath.h"
#include "XSystem.h"
#include "XTrace.h"

#include "INPWINDOWSKeyboardHook.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

bool INPWINDOWSKEYBOARDHOOK::isstopkbd = false;

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn          INPWINDOWSKEYBOARDHOOK:: INPWINDOWSKEYBOARDHOOK(void* applicationhandle)
* @brief       INPWINDOWSKEYBOARDHOOK
* @ingroup
*
* @author     Abraham J. Velez
* @date       30/09/2018 17:53:28
*
* @param[in]  applicationhandle :
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
INPWINDOWSKEYBOARDHOOK:: INPWINDOWSKEYBOARDHOOK(void* applicationhandle)
{
  Clean();

  this->applicationhandle = applicationhandle;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPWINDOWSKEYBOARDHOOK::~ INPWINDOWSKEYBOARDHOOK()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup
*
* @author     Abraham J. Velez
* @date       18/09/2018 12:20:39
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
INPWINDOWSKEYBOARDHOOK::~ INPWINDOWSKEYBOARDHOOK()
{
  Deactivate();

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPWINDOWSKEYBOARDHOOK::Activate()
* @brief      Activate
* @ingroup
*
* @author     Abraham J. Velez
* @date       30/09/2018 12:36:22
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool INPWINDOWSKEYBOARDHOOK::Activate()
{
  if(keyhook) return false;

  //Set up the hook

  HINSTANCE hinst = (HINSTANCE)applicationhandle;

  if(!hinst) return false;

  keyhook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, hinst, 0);
  if(keyhook == NULL)
    {
      XTRACE_PRINTCOLOR(4, __L("Keyhook Error: Could not hook keyboard. Another program might be interfering."));
      return false;
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPWINDOWSKEYBOARDHOOK::IsKBDStopped()
* @brief      IsKBDStopped
* @ingroup
*
* @author     Abraham J. Velez
* @date       30/09/2018 18:10:24
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool INPWINDOWSKEYBOARDHOOK::IsKBDStopped()
{
  return INPWINDOWSKEYBOARDHOOK::isstopkbd;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPWINDOWSKEYBOARDHOOK::SetKBDStopped(bool stopped)
* @brief      SetKBDStopped
* @ingroup
*
* @author     Abraham J. Velez
* @date       30/09/2018 18:10:08
*
* @param[in]  stopped :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool INPWINDOWSKEYBOARDHOOK::SetKBDStopped(bool stopped)
{
  if(INPWINDOWSKEYBOARDHOOK::isstopkbd == stopped) return false;

  INPWINDOWSKEYBOARDHOOK::isstopkbd = stopped;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPWINDOWSKEYBOARDHOOK::Deactivate()
* @brief      Deactivate
* @ingroup
*
* @author     Abraham J. Velez
* @date       30/09/2018 12:36:26
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool INPWINDOWSKEYBOARDHOOK::Deactivate()
{
  if(!keyhook) return false;

  SetKBDStopped(false);

  //Remove keyboard hook
  if(UnhookWindowsHookEx(keyhook) == 0)
    {
      XTRACE_PRINTCOLOR(4, __L("Keyhook Error: Could not unhook keyboard."));
      return false;
    }

  //Success
  keyhook = NULL;

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void INPWINDOWSKEYBOARDHOOK::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup
*
* @author     Abraham J. Velez
* @date       18/09/2018 12:20:49
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void INPWINDOWSKEYBOARDHOOK::Clean()
{
  applicationhandle   = NULL;
  keyhook             = NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         LRESULT CALLBACK INPWINDOWSKEYBOARDHOOK::LowLevelKeyboardProc(int ncode, WPARAM wparam, LPARAM lparam)
* @brief      LowLevelKeyboardProc
* @ingroup
*
* @author     Abraham J. Velez
* @date       30/09/2018 17:13:38
*
* @param[in]  ncode :
* @param[in]  wparam :
* @param[in]  lparam :
*
* @return     LRESULT :
*
*---------------------------------------------------------------------------------------------------------------------*/
LRESULT CALLBACK INPWINDOWSKEYBOARDHOOK::LowLevelKeyboardProc(int ncode, WPARAM wparam, LPARAM lparam)
{
  if(ncode == HC_ACTION && (wparam == WM_KEYDOWN || wparam == WM_SYSKEYDOWN))
    {
      int vkey = ((PKBDLLHOOKSTRUCT)lparam)->vkCode;
    }

  //Stop this key
  if(INPWINDOWSKEYBOARDHOOK::isstopkbd)
    {
      return 1;
    }

  KBDLLHOOKSTRUCT* keydata = (KBDLLHOOKSTRUCT*)lparam;

  XTRACE_PRINTCOLOR(XTRACE_COLOR_PURPLE, __L("Hook keyboard: vkCode %04X, scanCode %08X, flags %08X"), keydata->vkCode, keydata->scanCode, keydata->flags);

  /*
  if(keydata->vkCode == 0xA4) 
    {
      #ifdef SHOW_EXTRA_TRACE
      XTRACE_PRINTCOLOR(XTRACE_COLOR_PURPLE, __L("Blocked ALT"));
      #endif

      return 1;
    }

  if((keydata->vkCode == 0x1B) && (keydata->scanCode == 0x01))
    {
      #ifdef SHOW_EXTRA_TRACE
      XTRACE_PRINTCOLOR(XTRACE_COLOR_PURPLE, __L("Blocked ESC"));
      #endif

      return 1;
    }
  */
  
  return CallNextHookEx(NULL, ncode, wparam, lparam);
}
