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

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XWINDOWSConsole.h"

#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <fcntl.h> 
#include <io.h>

#include "XString.h"
#include "XFileTXT.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWINDOWSCONSOLE::XWINDOWSCONSOLE()
* @brief      Constructor
* @ingroup    PLATFORM_WINDOWS
*
* --------------------------------------------------------------------------------------------------------------------*/
XWINDOWSCONSOLE::XWINDOWSCONSOLE(): XCONSOLE()
{
  HANDLE                hconsole    = GetStdHandle(STD_OUTPUT_HANDLE);   // Get the number of character cells in the current buffer.
  CONSOLE_CURSOR_INFO   cursorinfo;

  GetConsoleCursorInfo(hconsole, &cursorinfo);
  cursorinfo.bVisible = false; // set the cursor visibility
  SetConsoleCursorInfo(hconsole, &cursorinfo);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWINDOWSCONSOLE::~XWINDOWSCONSOLE()
* @brief      Destructor
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
* @brief      GetSize
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
  HWND consolehandle = GetConsoleWindow();
  RECT rect;

  width  = 0;
  height = 0;

  if(GetWindowRect(consolehandle, &rect) == FALSE) return false;

  width  = rect.right  - rect.left;
  height = rect.bottom - rect.top;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSCONSOLE::SetSize(int width, int height)
* @brief      SetSize
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
  HWND consolehandle = GetConsoleWindow();
  RECT rect;
  RECT rectdesktop;

  if(GetWindowRect(GetDesktopWindow(), &rectdesktop) == FALSE) return false;

  if(GetWindowRect(consolehandle, &rect) == FALSE) return false;

  rect.left   = (rectdesktop.right-width)/2;
  rect.top    = (rectdesktop.bottom-height)/2;

  if(MoveWindow(consolehandle, rect.left, rect.top, width, height, TRUE) == FALSE) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSCONSOLE::GetSizeText(int& columns, int& rows)
* @brief      GetSizeText
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
  CONSOLE_SCREEN_BUFFER_INFO csbi;

  if(!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) return false;

  columns = csbi.srWindow.Right  - csbi.srWindow.Left + 1;
  rows    = csbi.srWindow.Bottom - csbi.srWindow.Top  + 1;

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
  HWND hwindow  = GetConsoleWindow();
  if(!hwindow)  return false;

  ShowWindow(hwindow,SW_HIDE);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSCONSOLE::IsHide()
* @brief      IsHide
* @ingroup    PLATFORM_WINDOWS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSCONSOLE::IsHide()
{
  HWND hwindow  = GetConsoleWindow();
  if(!hwindow)  return false;

  return (IsWindowVisible(hwindow))?false:true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSCONSOLE::UnHide()
* @brief      UnHide
* @ingroup    PLATFORM_WINDOWS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSCONSOLE::UnHide()
{
  HWND hwindow  = GetConsoleWindow();
  if(!hwindow)  return false;

  ShowWindow(hwindow,SW_SHOW);

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
  if(!string)     return false;
  if(!string[0])  return false;

  //wprintf((wchar_t *)string);
  std::wcout << string;

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
  system("cls");

  return true;  
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSCONSOLE::KBHit(void)
* @brief      KBHit
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  void :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSCONSOLE::KBHit(void)
{
  #ifdef _MSC_VER
  if(_kbhit()) return true;
  #endif

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XWINDOWSCONSOLE::GetChar()
* @brief      GetChar
* @ingroup    PLATFORM_WINDOWS
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XWINDOWSCONSOLE::GetChar()
{
  //if(!KBHit()) return 0;

  return _getch();
}


#pragma endregion


