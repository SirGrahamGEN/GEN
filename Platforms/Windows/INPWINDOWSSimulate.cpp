/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       INPWindowsSimulate.cpp
* 
* @class      INPWINDOWSSIMULATE
* @brief      Input WINDOWS Simulate
* @ingroup    INPUT
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

#include "INPWindowsSimulate.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include <Windows.h>

#include "XString.h"

#include "XMemory_Control.h"


#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE


#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         INPWINDOWSSIMULATE::INPWINDOWSSIMULATE()
* @brief      Constructor
* @ingroup    PLATFORM_WINDOWS
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
INPWINDOWSSIMULATE::INPWINDOWSSIMULATE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         INPWINDOWSSIMULATE::~INPWINDOWSSIMULATE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_WINDOWS
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
INPWINDOWSSIMULATE::~INPWINDOWSSIMULATE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPWINDOWSSIMULATE::PressKey(XBYTE code, int pressuretime)
* @brief      PressKey
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  code : 
* @param[in]  pressuretime : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPWINDOWSSIMULATE::PressKey(XBYTE code, int pressuretime)
{
  keybd_event(code, 0, 0, 0);    
    
  Sleep(pressuretime);
  
  keybd_event(code, 0, KEYEVENTF_KEYUP, 0);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPWINDOWSSIMULATE::PressKeyByLiteral(XCHAR* literal, int pressuretime)
* @brief      PressKeyByLiteral
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  literal : 
* @param[in]  pressuretime : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPWINDOWSSIMULATE::PressKeyByLiteral(XCHAR* literal, int pressuretime)
{
  XBYTE code = GetKDBCodeByLiteral(literal);

  if(code)
    {
      return PressKey(code, pressuretime);  
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPWINDOWSSIMULATE::PressKeyByText(XCHAR* text, int pressuretimeinterval)
* @brief      PressKeyByText
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  text : 
* @param[in]  pressuretimeinterval : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPWINDOWSSIMULATE::PressKeyByText(XCHAR* text, int pressuretimeinterval)
{
  XSTRING _text;

  _text = text;

  for(XDWORD c=0; c<_text.GetSize(); c++)
    {
      switch(_text.Get()[c])
        {
          case __C('A')   : 
          case __C('B')   : 
          case __C('C')   : 
          case __C('D')   : 
          case __C('E')   : 
          case __C('F')   : 
          case __C('G')   : 
          case __C('H')   : 
          case __C('I')   : 
          case __C('J')   : 
          case __C('K')   : 
          case __C('L')   : 
          case __C('M')   : 
          case __C('N')   : 
          case __C('O')   : 
          case __C('P')   : 
          case __C('Q')   : 
          case __C('R')   : 
          case __C('S')   : 
          case __C('T')   : 
          case __C('U')   : 
          case __C('V')   : 
          case __C('W')   : 
          case __C('X')   : 
          case __C('Y')   : 
          case __C('Z')   : { XSTRING literal;
                              literal.Add(_text.Get()[c]);

                              PressKeyByLiteral(literal.Get(), pressuretimeinterval);
                            }
                            break;

          case __C(' ')   : PressKeyByLiteral(__L("SPACEBAR"), pressuretimeinterval);                            
                            break;

          case __C('a')   : break;
          case __C('b')   : break;
          case __C('c')   : break;
          case __C('d')   : break;
          case __C('e')   : break;
          case __C('f')   : break;
          case __C('g')   : break;
          case __C('h')   : break;
          case __C('i')   : break;
          case __C('j')   : break;
          case __C('k')   : break;
          case __C('l')   : break;
          case __C('m')   : break;
          case __C('n')   : break;
          case __C('o')   : break;
          case __C('p')   : break;
          case __C('q')   : break;
          case __C('r')   : break;
          case __C('s')   : break;
          case __C('t')   : break;
          case __C('u')   : break;
          case __C('v')   : break;
          case __C('w')   : break;
          case __C('x')   : break;
          case __C('y')   : break;
          case __C('z')   : break;    
          case __C('1')   : break;
          case __C('2')   : break;
          case __C('3')   : break;
          case __C('4')   : break;
          case __C('5')   : break;
          case __C('6')   : break;
          case __C('7')   : break;
          case __C('8')   : break;
          case __C('9')   : break;
          case __C('0')   : break;
          case __C('!')   : break;
          case __C('@')   : break;
          case __C('#')   : break;
          case __C('$')   : break;
          case __C('%')   : break;
          case __C('^')   : break;
          case __C('&')   : break;
          case __C('*')   : break;
          case __C('(')   : break;
          case __C(')')   : break;
          case __C('_')   : break;
          case __C('+')   : break;
          case __C('-')   : break;
          case __C('=')   : break;
          case __C('[')   : break;
          case __C(']')   : break;
          case __C('{')   : break;
          case __C('}')   : break;
          case __C('|')   : break;
          case __C(';')   : break;
          case __C(':')   : break;
          case __C('\'')  : break;
          case __C(',')   : break;
          case __C('.')   : break;
          case __C('<')   : break;
          case __C('>')   : break;
          case __C('?')   : break;
          case __C('/')   : break;
          case __C('\\')  : break;
          case __C('\"')  : break;

          

        }
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPWINDOWSSIMULATE::SetMousePos(int x, int y)
* @brief      SetPositionCursor
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  x : 
* @param[in]  y : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPWINDOWSSIMULATE::SetMousePos(int x, int y)
{
  SetCursorPos(x, y);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPWINDOWSSIMULATE::SetMouseClick(int x, int y)
* @brief      SetMouseClick
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  x : 
* @param[in]  y : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPWINDOWSSIMULATE::SetMouseClick(int x, int y)
{
  SetCursorPos(x, y);
  
  mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
  mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void INPWINDOWSSIMULATE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_WINDOWS
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void INPWINDOWSSIMULATE::Clean()
{
  
}


#pragma endregion


