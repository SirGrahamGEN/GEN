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
* @fn         bool INPWINDOWSSIMULATE::PressKeyDown(XBYTE code)
* @brief      PressKeyDown
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  code : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPWINDOWSSIMULATE::PressKeyDown(XBYTE code)
{
  keybd_event(code, 0, 0, 0);    
    
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPWINDOWSSIMULATE::PressKeyUp(XBYTE code)
* @brief      PressKeyUp
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  code : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPWINDOWSSIMULATE::PressKeyUp(XBYTE code)
{
  keybd_event(code, 0, KEYEVENTF_KEYUP, 0);

  return true;
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
  PressKeyDown(code);    
    
  Sleep(pressuretime);
  
  PressKeyUp(code);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPWINDOWSSIMULATE::PressKeyDownByLiteral(XCHAR* literal)
* @brief      PressKeyDownByLiteral
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  literal : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPWINDOWSSIMULATE::PressKeyDownByLiteral(XCHAR* literal)
{
  XBYTE code = GetKDBCodeByLiteral(literal);

  if(code)
    {    
       return PressKeyDown(code);  
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPWINDOWSSIMULATE::PressKeyUpByLiteral(XCHAR* literal)
* @brief      PressKeyUpByLiteral
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  literal : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPWINDOWSSIMULATE::PressKeyUpByLiteral(XCHAR* literal)
{
  XBYTE code = GetKDBCodeByLiteral(literal);

  if(code)
    {    
       return PressKeyUp(code);  
    }

  return false;
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
  XSTRING literal;

  _text = text;

  for(XDWORD c=0; c<_text.GetSize(); c++)
    {
      literal.Empty();
      literal.Add(_text.Get()[c]);

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
          case __C('Z')   : { bool changecapslock = false;      
                              
                              if(!IsCapsLockActive())
                                {
                                  PressKeyByLiteral(__L("CAPS LOCK"), pressuretimeinterval);
                                  changecapslock = true;      
                                }

                              PressKeyByLiteral(literal.Get(), pressuretimeinterval);

                              if(changecapslock)
                                {
                                  PressKeyByLiteral(__L("CAPS LOCK"), pressuretimeinterval);                                  
                                }    
                            }
                            break;

          case __C(' ')   : PressKeyByLiteral(__L("SPACEBAR"), pressuretimeinterval);                            
                            break;

          case __C('a')   : 
          case __C('b')   : 
          case __C('c')   : 
          case __C('d')   : 
          case __C('e')   : 
          case __C('f')   : 
          case __C('g')   : 
          case __C('h')   : 
          case __C('i')   : 
          case __C('j')   : 
          case __C('k')   : 
          case __C('l')   : 
          case __C('m')   : 
          case __C('n')   : 
          case __C('o')   : 
          case __C('p')   : 
          case __C('q')   : 
          case __C('r')   : 
          case __C('s')   : 
          case __C('t')   : 
          case __C('u')   : 
          case __C('v')   : 
          case __C('w')   : 
          case __C('x')   : 
          case __C('y')   : 

          case __C('z')   : { bool changecapslock = false;      
                              
                              if(IsCapsLockActive())
                                {
                                  PressKeyByLiteral(__L("CAPS LOCK"), pressuretimeinterval);
                                  changecapslock = true;      
                                }

                              PressKeyByLiteral(literal.Get(), pressuretimeinterval);

                              if(changecapslock)
                                {
                                  PressKeyByLiteral(__L("CAPS LOCK"), pressuretimeinterval);                                  
                                }    
                            }
                            break;
                                                                                          
          case __C('1')   : 
          case __C('2')   : 
          case __C('3')   : 
          case __C('4')   : 
          case __C('5')   : 
          case __C('6')   : 
          case __C('7')   : 
          case __C('8')   : 
          case __C('9')   : 
          case __C('0')   : PressKeyByLiteral(literal.Get(), pressuretimeinterval);                            
                            break;                           

          case __C('!')   : PressKeyDownByLiteral(__L("SHIFT"));
                            PressKeyByLiteral(__L("1"), pressuretimeinterval); 
                            PressKeyUpByLiteral(__L("SHIFT"));
                            break;

          case __C('@')   : PressKeyDownByLiteral(__L("Right ALT"));
                            PressKeyByLiteral(__L("2"), pressuretimeinterval); 
                            PressKeyUpByLiteral(__L("Right ALT"));
                            break;

          case __C('#')   : PressKeyDownByLiteral(__L("Right ALT"));
                            PressKeyByLiteral(__L("3"), pressuretimeinterval); 
                            PressKeyUpByLiteral(__L("Right ALT"));                            
                            break;

          case __C('$')   : PressKeyDownByLiteral(__L("SHIFT"));
                            PressKeyByLiteral(__L("4"), pressuretimeinterval); 
                            PressKeyUpByLiteral(__L("SHIFT"));
                            break;

          case __C('%')   : PressKeyDownByLiteral(__L("SHIFT"));
                            PressKeyByLiteral(__L("5"), pressuretimeinterval); 
                            PressKeyUpByLiteral(__L("SHIFT"));
                            break;

          case __C('^')   : break;

          case __C('&')   : PressKeyDownByLiteral(__L("SHIFT"));
                            PressKeyByLiteral(__L("6"), pressuretimeinterval); 
                            PressKeyUpByLiteral(__L("SHIFT"));
                            break;

          case __C('*')   : PressKeyByLiteral(__L("Multiply"), pressuretimeinterval); 
                            break;

          case __C('(')   : PressKeyDownByLiteral(__L("SHIFT"));
                            PressKeyByLiteral(__L("8"), pressuretimeinterval); 
                            PressKeyUpByLiteral(__L("SHIFT"));
                            break;

          case __C(')')   : PressKeyDownByLiteral(__L("SHIFT"));
                            PressKeyByLiteral(__L("9"), pressuretimeinterval); 
                            PressKeyUpByLiteral(__L("SHIFT"));
                            break;

          case __C('_')   : PressKeyDownByLiteral(__L("SHIFT"));
                            PressKeyByLiteral(__L("-"), pressuretimeinterval); 
                            PressKeyUpByLiteral(__L("SHIFT"));
                            break;

          case __C('+')   : PressKeyByLiteral(__L("Add"), pressuretimeinterval);  
                            break;

          case __C('-')   : PressKeyByLiteral(__L("Subtract"), pressuretimeinterval);  
                            break;

          case __C('=')   : PressKeyDownByLiteral(__L("SHIFT"));
                            PressKeyByLiteral(__L("0"), pressuretimeinterval); 
                            PressKeyUpByLiteral(__L("SHIFT"));
                            break;

          case __C('[')   : break;
          case __C(']')   : break;
          case __C('{')   : break;
          case __C('}')   : break;

          case __C('|')   : PressKeyDownByLiteral(__L("Right ALT"));
                            PressKeyByLiteral(__L("1"), pressuretimeinterval); 
                            PressKeyUpByLiteral(__L("Right ALT"));                           
                            break;

          case __C(';')   : PressKeyDownByLiteral(__L("SHIFT"));
                            PressKeyByLiteral(__L(","), pressuretimeinterval); 
                            PressKeyUpByLiteral(__L("SHIFT"));
                            break;

          case __C(':')   : PressKeyDownByLiteral(__L("SHIFT"));
                            PressKeyByLiteral(__L("."), pressuretimeinterval); 
                            PressKeyUpByLiteral(__L("SHIFT"));
                            break;

          case __C('\'')  : PressKeyByLiteral(__L("?"), pressuretimeinterval); 
                            break;

          case __C(',')   : PressKeyByLiteral(__L(","), pressuretimeinterval); 
                            break;

          case __C('.')   : PressKeyByLiteral(__L("."), pressuretimeinterval); 
                            break;

          case __C('<')   : break;
          case __C('>')   : break;

          case __C('?')   : PressKeyDownByLiteral(__L("SHIFT"));
                            PressKeyByLiteral(__L("'"), pressuretimeinterval); 
                            PressKeyUpByLiteral(__L("SHIFT"));
                            break;

          case __C('/')   : PressKeyByLiteral(__L("Divide"), pressuretimeinterval);  
                            break;

          case __C('\\')  : break;

          case __C('\"')  : PressKeyDownByLiteral(__L("SHIFT"));
                            PressKeyByLiteral(__L("2"), pressuretimeinterval); 
                            PressKeyUpByLiteral(__L("SHIFT"));
                            break;       

          case __C('·')  :  PressKeyDownByLiteral(__L("SHIFT"));
                            PressKeyByLiteral(__L("3"), pressuretimeinterval); 
                            PressKeyUpByLiteral(__L("SHIFT"));
                            break;       
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
* @fn         bool INPWINDOWSSIMULATE::IsCapsLockActive()
* @brief      IsCapsLockActive
* @ingroup    PLATFORM_WINDOWS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPWINDOWSSIMULATE::IsCapsLockActive()
{
  short capslockstate = GetKeyState(VK_CAPITAL);

  bool iscapslockon = (capslockstate & 0x0001) != 0;

  return iscapslockon;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPWINDOWSSIMULATE::IsNumLockActive()
* @brief      IsNumLockActive
* @ingroup    PLATFORM_WINDOWS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPWINDOWSSIMULATE::IsNumLockActive()
{
  short numlockstate = GetKeyState(VK_NUMLOCK);

  bool isnumlockon = (numlockstate & 0x0001) != 0;

  return isnumlockon;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPWINDOWSSIMULATE::IsScrollLockActive()
* @brief      IsScrollLockActive
* @ingroup    PLATFORM_WINDOWS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPWINDOWSSIMULATE::IsScrollLockActive()
{
  short scrolllockstate = GetKeyState(VK_SCROLL);

  bool isscrolllockon = (scrolllockstate & 0x0001) != 0;

  return isscrolllockon;
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


