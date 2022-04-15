/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XLINUXConsole.cpp
*
* @class      XLINUXCONSOLE
* @brief      eXtended LINUX Console class
* @ingroup    PLATFORM_LINUX
*
* @copyright  GEN Group. All right reserved.
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
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include "XTrace.h"

#include "XLINUXConsole.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLINUXCONSOLE::XLINUXCONSOLE()
* @brief      Constructor
* @ingroup    PLATFORM_LINUX
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XLINUXCONSOLE::XLINUXCONSOLE(): XCONSOLE()
{
  RawModeEnable();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLINUXCONSOLE::~XLINUXCONSOLE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_LINUX
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XLINUXCONSOLE::~XLINUXCONSOLE()
{
  RawModeDisable();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXCONSOLE::GetSizeText(int& columns, int& rows)
* @brief      GetSizeText
* @ingroup    PLATFORM_LINUX
*
* @param[in]  columns :
* @param[in]  rows :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLINUXCONSOLE::GetSizeText(int& columns, int& rows)
{
  struct winsize console_size;

  //ioctl(0, TIOCGWINSZ, &console_size);
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &console_size);

  columns = console_size.ws_col;
  rows    = console_size.ws_row;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXCONSOLE::Maximize()
* @brief      Maximize
* @ingroup    PLATFORM_LINUX
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLINUXCONSOLE::Maximize()
{
  setvbuf(stdout, NULL,_IONBF,0);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXCONSOLE::Minimize()
* @brief      Minimize
* @ingroup    PLATFORM_LINUX
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLINUXCONSOLE::Minimize()
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXCONSOLE::Hide()
* @brief      Hide
* @ingroup    PLATFORM_LINUX
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLINUXCONSOLE::Hide()
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXCONSOLE::IsHide()
* @brief      IsHide
* @ingroup    PLATFORM_LINUX
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLINUXCONSOLE::IsHide()
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXCONSOLE::Print(XCHAR* string)
* @brief      Print
* @ingroup    PLATFORM_LINUX
*
* @param[in]  string : string to print
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLINUXCONSOLE::Print(XCHAR* string)
{
  if(!string)     return false;
  if(!string[0])  return false;

  XSTRING _string;

  _string = string;

  XSTRING_CREATEOEM(_string, charstr)
  printf(charstr);
  XSTRING_DELETEOEM(_string, charstr);

  fflush(stdout);


  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XLINUXCONSOLE::Clear(bool fill)
* @brief      Clear
* @ingroup    PLATFORM_LINUX
*
* @param[in]  fill : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XLINUXCONSOLE::Clear(bool fill)
{
  printf("\033[2J");
  printf("\033[H");


  //printf("\033[2J\033[H");    
  //printf("\e[3J");

  //printf("\033c");    // KDE
 
  //system("clear");

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXCONSOLE::KBHit(void)
* @brief      KBHit
* @ingroup    PLATFORM_LINUX
*
* @param[in]  void :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XLINUXCONSOLE::KBHit(void)
{
  /*
  struct termios oldt;
  struct termios newt;
  int            ch;
  int            oldf;

  tcgetattr(STDIN_FILENO, &oldt);

  newt          = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);

  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);

  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
    {
      ungetc(ch, stdin);
      return true;
    }

  return false;
  */

  int byteswaiting;
  ioctl(0, FIONREAD, &byteswaiting);

  return byteswaiting > 0;
}



/*-------------------------------------------------------------------
//  XLINUXCONSOLE::GetChar
*/
/**
//
//
//  ""
//  @version      01/12/2009 08:51:46 p.m.
//
//  @return       int :
//  */
/*-----------------------------------------------------------------*/
int XLINUXCONSOLE::GetChar()
{
  struct termios oldt, newt;
  int ch;

  tcgetattr( STDIN_FILENO, &oldt );               /* Obtenemos atributos del terminal */
  newt = oldt;
  newt.c_lflag &= ~ICANON;
  newt.c_lflag &= ~ECHO;                          /* Eliminamos el Echo */

  tcsetattr( STDIN_FILENO, TCSANOW, &newt );      /* Definimos los nuevos atributos al terminal */

  ch = getchar();

  tcsetattr( STDIN_FILENO, TCSANOW, &oldt );      /* Ponemos los atributos como estaban al principio */

  return ch;
}





/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XLINUXCONSOLE::RawModeEnable()
* @brief      RawModeEnable
* @ingroup    PLATFORM_LINUX
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void XLINUXCONSOLE::RawModeEnable()
{
  termios term;

  tcgetattr(0, &term);
  term.c_lflag &= ~(ICANON | ECHO); // Disable echo as well
  tcsetattr(0, TCSANOW, &term);
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XLINUXCONSOLE::RawModeDisable()
* @brief      RawModeDisable
* @ingroup    PLATFORM_LINUX
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void XLINUXCONSOLE::RawModeDisable()
{
  termios term;
  
  tcgetattr(0, &term);
  term.c_lflag |= ICANON | ECHO;
  tcsetattr(0, TCSANOW, &term);
}
