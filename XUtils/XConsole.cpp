/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XConsole.cpp
* 
* @class      XCONSOLE
* @brief      eXtended Utils Console base class
* @ingroup    XUTILS
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

#include "XConsole.h"

#include <stdio.h>
#include <stdlib.h>

#include "XFactory.h"
#include "XDateTime.h"
#include "XBuffer.h"
#include "XTimer.h"
#include "XSleep.h"

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
* @fn         XCONSOLE::XCONSOLE()
* @brief      Constructor of class
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XCONSOLE::XCONSOLE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XCONSOLE::~XCONSOLE()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XCONSOLE::~XCONSOLE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XCONSOLE::GetSize(int& width, int& height)
* @brief      Get size
* @note       VIRTUAL
* @ingroup    XUTILS
*
* @param[out]  width : return width of console
* @param[out]  height : return height of console
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XCONSOLE::GetSize(int& width, int& height)
{
  width  = 0;
  height = 0;

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XCONSOLE::SetSize(int width, int height)
* @brief      Set size
* @note       VIRTUAL
* @ingroup    XUTILS
*
* @param[in]  width : set width of console
* @param[in]  height : swet height of console
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XCONSOLE::SetSize(int width, int height)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XCONSOLE::GetSizeText(int& columns, int& rows)
* @brief      Get size text
* @ingroup    XUTILS
*
* @param[in]  columns :
* @param[in]  rows :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XCONSOLE::GetSizeText(int& columns, int& rows)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XCONSOLE::Maximize()
* @brief      Maximize
* @note       VIRTUAL
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XCONSOLE::Maximize()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XCONSOLE::Minimize()
* @brief      Minimize
* @note       VIRTUAL
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XCONSOLE::Minimize()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XCONSOLE::Hide()
* @brief      Hide
* @note       VIRTUAL
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XCONSOLE::Hide()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XCONSOLE::IsHide()
* @brief      Is hide
* @note       VIRTUAL
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XCONSOLE::IsHide()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XCONSOLE::UnHide()
* @brief      Un hide
* @note       VIRTUAL
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XCONSOLE::UnHide()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XCONSOLE::Clear(bool fill)
* @brief      Clear
* @ingroup    XUTILS
*
* @param[in]  fill : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XCONSOLE::Clear(bool fill)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XCONSOLE::KBHit()
* @brief      KB hit
* @note       VIRTUAL
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XCONSOLE::KBHit()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XCONSOLE::GetChar()
* @brief      Get char
* @note       VIRTUAL
* @ingroup    XUTILS
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XCONSOLE::GetChar()
{
  return 0;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XCONSOLE::Print(XCHAR* string)
* @brief      Print
* @ingroup    XUTILS
*
* @param[in]  string : string to print
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XCONSOLE::Print(XCHAR* string)
{
  if(!string) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XCONSOLE::Printf(XCHAR* mask,...)
* @brief      Printf
* @ingroup    XUTILS
*
* @param[in]  mask : mask to use
* @param[in]  ... : variables
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XCONSOLE::Printf(XCHAR* mask,...)
{
  if(!mask) return false;

  XSTRING outstring;

  va_list arg;

  va_start(arg, mask);

  outstring.FormatArg(mask, &arg);

  va_end(arg);

  Print(outstring.Get());

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XCONSOLE::PrintDataBlock(XBYTE* data, XDWORD size, XDWORD marginsize, XDWORD sizeline, bool showoffset, bool showtext)
* @brief      Print data block
* @ingroup    XUTILS
*
* @param[in]  data : data to print
* @param[in]  size : size of data
* @param[in]  marginsize : size of margin
* @param[in]  sizeline :  size for the line.
* @param[in]  showoffset : true if show offset
* @param[in]  showtext : true if show the data in char format.
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XCONSOLE::PrintDataBlock(XBYTE* data, XDWORD size, XDWORD marginsize, XDWORD sizeline, bool showoffset, bool showtext)
{
  XSTRING    margin;
  XSTRING    strdata;
  XDWORD     _size     = 0;
  XDWORD     _sizeline = sizeline;
  int        index     = 0;

  for(XDWORD c=0;c<marginsize;c++)
    {
      margin += __L(" ");
    }

  while(_size<size)
    {
      XSTRING string;

      string   = margin;
      if(_sizeline > (size - _size)) _sizeline = (size - _size);

      if(showoffset)
        {
          strdata.Format(__L("%04X"),index);
          string += strdata;
          string += __L("   ");
        }

      for(XDWORD c=0; c<_sizeline; c++)
        {
          strdata.Format(__L("%02X "),data[index]);
          string += strdata;
          _size++;
          index++;
        }

      if(_sizeline != sizeline)
        {
          for(XDWORD c=0; c<(sizeline-_sizeline); c++)
            {
              strdata.Format(__L("   "));
              string += strdata;
            }
        }

      if(showtext)
        {
          index -= _sizeline;
          string += __L(" ");

          for(XDWORD c=0; c<_sizeline; c++)
            {
              XCHAR character = (XCHAR)data[index];

              if((character<0x20) || (character>0x80) || (character==__C('%')) || (character==__C('\\'))) character = __C('.');

              strdata.Format(__L("%c"),character);
              string += strdata;
              index++;
            }
        }

      Print(string.Get());
      Print(__L("\n"));

      if(_size > XCONSOLE_MAXSIZEDATABLOCK) break;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XCONSOLE::PrintDataBlock(XBUFFER& data, XDWORD marginsize, XDWORD sizeline, bool showoffset, bool showtext)
* @brief      Print data block
* @ingroup    XUTILS
*
* @param[in]  data : buffer data to print
* @param[in]  marginsize : size of margin
* @param[in]  sizeline :  size of line
* @param[in]  showoffset : true if show offset
* @param[in]  showtext : true if show the data in char format.
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XCONSOLE::PrintDataBlock(XBUFFER& data, XDWORD marginsize, XDWORD sizeline, bool showoffset, bool showtext)
{
  return PrintDataBlock(data.Get(), data.GetSize(), marginsize, sizeline, showoffset, showtext);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XCONSOLE::Format_Message(XCHAR* message, XDWORD margin, bool prelude, bool returnline, XSTRING& string)
* @brief      Format message
* @ingroup    XUTILS
*
* @param[in]  message : Message to format.
* @param[in]  margin : size margin
* @param[in]  prelude : true if has prelude
* @param[in]  returnline : true if has return
* @param[out] string : result string formated
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XCONSOLE::Format_Message(XCHAR* message, XDWORD margin, bool prelude, bool returnline, XSTRING& string)
{
  string.Empty();

  for(XDWORD c=0; c<margin; c++)
    {
      string += __L(" ");
    }

  if(prelude) string += __L("> ");

  string += message;

  if(returnline) string+=__L("\n");

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XCONSOLE::PrintMessage(XCHAR* message, XDWORD margin, bool prelude, bool returnline)
* @brief      Print message
* @ingroup    XUTILS
* 
* @param[in]  message : 
* @param[in]  margin : 
* @param[in]  prelude : 
* @param[in]  returnline : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XCONSOLE::PrintMessage(XCHAR* message, XDWORD margin, bool prelude, bool returnline)
{
  XSTRING string;

  Format_Message(message, margin, prelude, returnline, string);

  return Print(string.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XCONSOLE::WaitKey(XCHAR* text, XDWORD margin, bool prelude, XDWORD timeout)
* @brief      Wait key
* @ingroup    XUTILS
*
* @param[in]  text : Text of the wait
* @param[in]  margin : size of margin
* @param[in]  prelude : true if has prelude
* @param[in]  timeout : timeout of the wait
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XCONSOLE::WaitKey(XCHAR* text, XDWORD margin, bool prelude, XDWORD timeout)
{
  XTIMER* GEN_XFACTORY_CREATE(xtimer, CreateTimer())
  if(!xtimer) return false;
  
  xtimer->Reset();

  XSTRING string;
  XSTRING string2;
  bool    status = true;

  while(!KBHit())
    {
      string  = text;
      string += __L("                            \r");

      string2.Format(string.Get(), (timeout - xtimer->GetMeasureSeconds()));

      GEN_XSLEEP.MilliSeconds(100);

      PrintMessage(string2.Get(), margin, prelude, false);

      if(timeout)
        {
          if((XDWORD)xtimer->GetMeasureSeconds() > timeout)
            {
              status = false;
              break;
            }
        }
    }

  while(KBHit())
    {
      GetChar();
    }

  string.Empty();

  for(int c=0; c<78; c++)
    {
      string += __L(" ");
    }

  string += __L("\r");
  PrintMessage(string.Get(), 0, false, false);

  GEN_XFACTORY.DeleteTimer(xtimer);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XCONSOLE::EraseToEndLine(int actualpos)
* @brief      Erase to end line
* @ingroup    XUTILS
*
* @param[in]  actualpos :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XCONSOLE::EraseToEndLine(int actualpos)
{
  int ncolumns = 0;
  int nrows    = 0;

  if(!GetSizeText(ncolumns, nrows)) return;

  for(int c=actualpos; c<(ncolumns-4); c++ )
    {
      PrintMessage(__L(" "), 0 ,false, false);
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XCONSOLE::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XCONSOLE::Clean()
{

}


#pragma endregion
