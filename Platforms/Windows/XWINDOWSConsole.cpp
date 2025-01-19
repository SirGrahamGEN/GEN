/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XWINDOWSConsole.cpp
* 
* @class      XWINDOWSCONSOLE
* @brief      WINDOWS eXtended Utils Console class
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

#include "XWINDOWSConsole.h"

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <fcntl.h> 
#include <io.h>
#include <iostream>
#include <fstream>

#include "XString.h"
#include "XFileTXT.h"

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
* @fn         XWINDOWSCONSOLE::XWINDOWSCONSOLE()
* @brief      Constructor of class
* @ingroup    PLATFORM_WINDOWS
*
* --------------------------------------------------------------------------------------------------------------------*/
XWINDOWSCONSOLE::XWINDOWSCONSOLE(): XCONSOLE()
{
  #ifndef APPFLOW_GRAPHICS_NOTCONSOLE_ACTIVE

  HANDLE                hconsole    = GetStdHandle(STD_OUTPUT_HANDLE);   // Get the number of character cells in the current buffer.
  CONSOLE_CURSOR_INFO   cursorinfo;

  GetConsoleCursorInfo(hconsole, &cursorinfo);
  cursorinfo.bVisible = false; // set the cursor visibility
  SetConsoleCursorInfo(hconsole, &cursorinfo);

  #endif
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWINDOWSCONSOLE::~XWINDOWSCONSOLE()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    PLATFORM_WINDOWS
*
* --------------------------------------------------------------------------------------------------------------------*/
XWINDOWSCONSOLE::~XWINDOWSCONSOLE()
{
  
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSCONSOLE::GetSize(int& width, int& height)
* @brief      Get size
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  width :
* @param[in]  height :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSCONSOLE::GetSize(int& width, int& height)
{
  #ifndef APPFLOW_GRAPHICS_NOTCONSOLE_ACTIVE

  HWND consolehandle = GetConsoleWindow();
  RECT rect;

  width  = 0;
  height = 0;

  if(GetWindowRect(consolehandle, &rect) == FALSE) return false;

  width  = rect.right  - rect.left;
  height = rect.bottom - rect.top;

  #endif

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSCONSOLE::SetSize(int width, int height)
* @brief      Set size
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  width :
* @param[in]  height :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSCONSOLE::SetSize(int width, int height)
{
  #ifndef APPFLOW_GRAPHICS_NOTCONSOLE_ACTIVE

  HWND consolehandle = GetConsoleWindow();
  RECT rect;
  RECT rectdesktop;

  if(GetWindowRect(GetDesktopWindow(), &rectdesktop) == FALSE) return false;

  if(GetWindowRect(consolehandle, &rect) == FALSE) return false;

  rect.left   = (rectdesktop.right-width)/2;
  rect.top    = (rectdesktop.bottom-height)/2;

  if(MoveWindow(consolehandle, rect.left, rect.top, width, height, TRUE) == FALSE) return false;

  #endif

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSCONSOLE::GetSizeText(int& columns, int& rows)
* @brief      Get size text
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  columns :
* @param[in]  rows :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSCONSOLE::GetSizeText(int& columns, int& rows)
{
  #ifndef APPFLOW_GRAPHICS_NOTCONSOLE_ACTIVE

  CONSOLE_SCREEN_BUFFER_INFO csbi;

  if(!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) return false;

  columns = csbi.srWindow.Right  - csbi.srWindow.Left + 1;
  rows    = csbi.srWindow.Bottom - csbi.srWindow.Top  + 1;

  #endif

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSCONSOLE::Maximize()
* @brief      Maximize
* @ingroup    PLATFORM_WINDOWS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSCONSOLE::Maximize()
{
  #ifndef APPFLOW_GRAPHICS_NOTCONSOLE_ACTIVE

  HANDLE                     hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
  HWND                       hwindow  = GetConsoleWindow();
  CONSOLE_SCREEN_BUFFER_INFO csbi;

  if(!hconsole) return false;
  if(!hwindow)  return false;

  GetConsoleScreenBufferInfo(hconsole , &csbi);

  csbi.dwSize.X = 150;
  csbi.dwSize.Y = 60;

  SetConsoleScreenBufferSize(hconsole,csbi.dwSize);

  ShowWindow(hwindow,SW_MAXIMIZE);

  #endif

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSCONSOLE::Minimize()
* @brief      Minimize
* @ingroup    PLATFORM_WINDOWS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSCONSOLE::Minimize()
{
  #ifndef APPFLOW_GRAPHICS_NOTCONSOLE_ACTIVE

  HANDLE                     hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
  HWND                       hwindow  = GetConsoleWindow();
  CONSOLE_SCREEN_BUFFER_INFO csbi;

  if(!hconsole) return false;
  if(!hwindow)  return false;

  GetConsoleScreenBufferInfo(hconsole , &csbi);

  csbi.dwSize.X = 120;
  csbi.dwSize.Y = 50;

  SetConsoleScreenBufferSize(hconsole,csbi.dwSize);

  ShowWindow(hwindow,SW_MINIMIZE);

  #endif

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSCONSOLE::Hide()
* @brief      Hide
* @ingroup    PLATFORM_WINDOWS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSCONSOLE::Hide()
{
  #ifndef APPFLOW_GRAPHICS_NOTCONSOLE_ACTIVE

  HWND hwindow  = GetConsoleWindow();
  if(!hwindow)  return false;

  ShowWindow(hwindow,SW_HIDE);

  #endif

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSCONSOLE::IsHide()
* @brief      Is hide
* @ingroup    PLATFORM_WINDOWS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSCONSOLE::IsHide()
{
  #ifndef APPFLOW_GRAPHICS_NOTCONSOLE_ACTIVE  

  HWND hwindow  = GetConsoleWindow();
  if(!hwindow)  return false;

  return (IsWindowVisible(hwindow))?false:true;

  #else

  return false;

  #endif
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSCONSOLE::UnHide()
* @brief      Un hide
* @ingroup    PLATFORM_WINDOWS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSCONSOLE::UnHide()
{
  #ifndef APPFLOW_GRAPHICS_NOTCONSOLE_ACTIVE

  HWND hwindow  = GetConsoleWindow();
  if(!hwindow)  return false;

  ShowWindow(hwindow,SW_SHOW);

  #endif

  return true;

}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSCONSOLE::Print(XCHAR* string)
* @brief      Print
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSCONSOLE::Print(XCHAR* string)
{
  #ifndef APPFLOW_GRAPHICS_NOTCONSOLE_ACTIVE

  if(!string)     return false;
  if(!string[0])  return false;

  //wprintf((wchar_t *)string);
  std::wcout << string;

  #endif

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XWINDOWSCONSOLE::Clear(bool fill)
* @brief      Clear
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  fill : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSCONSOLE::Clear(bool fill)
{
  #ifndef APPFLOW_GRAPHICS_NOTCONSOLE_ACTIVE

  system("cls");

  #endif

  return true;  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XWINDOWSCONSOLE::KBHit(void)
* @brief      KB hit
* @ingroup    PLATFORM_WINDOWS
*  
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSCONSOLE::KBHit(void)
{
  #ifndef APPFLOW_GRAPHICS_NOTCONSOLE_ACTIVE

  #ifdef _MSC_VER
  if(_kbhit()) return true;
  #endif

  #endif

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XWINDOWSCONSOLE::GetChar()
* @brief      Get char
* @ingroup    PLATFORM_WINDOWS
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XWINDOWSCONSOLE::GetChar()
{
  #ifndef APPFLOW_GRAPHICS_NOTCONSOLE_ACTIVE
  
  //if(!KBHit()) return 0;

  return _getch();

  #else

  return 0;

  #endif
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XWINDOWSCONSOLE::Generate()
* @brief      Generate
* @ingroup    PLATFORM_WINDOWS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSCONSOLE::Generate()
{
  //#ifndef APPFLOW_GRAPHICS_NOTCONSOLE_ACTIVE

  #ifndef BUILDER
  if(!AttachConsole(ATTACH_PARENT_PROCESS))
    {
      // allocate a console for this app
      if(!AllocConsole())
        {
          return false;
        }
    }
  #endif

  freopen("CON", "w", stdout);
  freopen("CON", "w", stderr);
  freopen("CON", "r", stdin);

  /*
  HANDLE  consoleoutput = GetStdHandle(STD_OUTPUT_HANDLE);
  int     SystemOutput  = _open_osfhandle(intptr_t(consoleoutput), _O_TEXT);

  // check if output is a console and not redirected to a file
  if(!isatty(SystemOutput))
    {
      return false;
    }

  FILE*   coutputhandle = _fdopen(SystemOutput, "w");

  // Get STDERR handle
  HANDLE  consoleerror  = GetStdHandle(STD_ERROR_HANDLE);
  int     systemerror   = _open_osfhandle(intptr_t(consoleerror), _O_TEXT);
  FILE*   cerrorhandle  = _fdopen(systemerror, "w");

  // Get STDIN handle
  HANDLE  consoleinput  = GetStdHandle(STD_INPUT_HANDLE);
  int     systeminput   = _open_osfhandle(intptr_t(consoleinput), _O_TEXT);
  FILE*   cinputhandle  = _fdopen(systeminput, "r");

  //make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog point to console as well
  std::ios::sync_with_stdio(true);

  // Redirect the CRT standard input, output, and error handles to the console
  freopen_s(&cinputhandle , "CONIN$"  , "r", stdin);
  freopen_s(&coutputhandle, "CONOUT$" , "w", stdout);
  freopen_s(&cerrorhandle , "CONOUT$" , "w", stderr);
  */

  //Clear the error state for each of the C++ standard stream objects.
  /*std::wcout.clear();
  std::cout.clear();
  std::wcerr.clear();
  std::cerr.clear();
  std::wcin.clear();
  std::cin.clear(); */

  //#endif

  return true;   
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XWINDOWSCONSOLE::Close()
* @brief      Close
* @ingroup    PLATFORM_WINDOWS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSCONSOLE::Close()
{
  //#ifndef APPFLOW_GRAPHICS_NOTCONSOLE_ACTIVE

  SendEnterKey();

  return FreeConsole();

  //#else

  //return false;

  //#endif

}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XWINDOWSCONSOLE::SendEnterKey()
* @brief      Send enter key
* @ingroup    PLATFORM_WINDOWS
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XWINDOWSCONSOLE::SendEnterKey() 
{
  #ifndef APPFLOW_GRAPHICS_NOTCONSOLE_ACTIVE

  INPUT ip;
  // Set up a generic keyboard event.
  ip.type = INPUT_KEYBOARD;
  ip.ki.wScan = 0; // hardware scan code for key
  ip.ki.time = 0;
  ip.ki.dwExtraInfo = 0;

  // Send the "Enter" key
  ip.ki.wVk = 0x0D; // virtual-key code for the "Enter" key
  ip.ki.dwFlags = 0; // 0 for key press
  SendInput(1, &ip, sizeof(INPUT));

  // Release the "Enter" key
  ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
  SendInput(1, &ip, sizeof(INPUT));

  #endif
}


#pragma endregion


