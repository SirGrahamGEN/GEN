/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_Color.cpp
* 
* @class      UI_COLOR
* @brief      User Interface Color class
* @ingroup    USERINTERFACE
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
* ---------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "UI_Colors.h"

#include "UI_Color.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_COLOR::UI_COLOR()
* @brief      Constructor
* @ingroup    USERINTERFACE
*
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_COLOR::UI_COLOR()    
{ 
  Clean();                            
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_COLOR::~UI_COLOR()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    USERINTERFACE
*
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
UI_COLOR::~UI_COLOR()    
{ 
  Clean();                            
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int UI_COLOR::GetRed()
* @brief      GetRed
* @ingroup    USERINTERFACE
*
* @return     int : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
int UI_COLOR::GetRed() 
{
  return red;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_COLOR::SetRed(int red)
* @brief      SetRed
* @ingroup    USERINTERFACE
*
* @param[in]  red : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_COLOR::SetRed(int red)  
{
  this->red = red;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int UI_COLOR::GetGreen()
* @brief      GetGreen
* @ingroup    USERINTERFACE
*
* @return     int : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
int UI_COLOR::GetGreen()
{
  return green;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_COLOR::SetGreen(int green)
* @brief      SetGreen
* @ingroup    USERINTERFACE
*
* @param[in]  green : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_COLOR::SetGreen(int green)
{
  this->green = green;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int UI_COLOR::GetBlue()
* @brief      GetBlue
* @ingroup    USERINTERFACE
*
* @return     int : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
int UI_COLOR::GetBlue()
{
  return blue;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_COLOR::SetBlue(int blue)
* @brief      SetBlue
* @ingroup    USERINTERFACE
*
* @param[in]  blue : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_COLOR::SetBlue(int blue)
{
  this->blue = blue;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int UI_COLOR::GetAlpha()
* @brief      GetAlpha
* @ingroup    USERINTERFACE
*
* @return     int : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
int UI_COLOR::GetAlpha()
{
  return alpha;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_COLOR::SetAlpha(int alpha)
* @brief      SetAlpha
* @ingroup    USERINTERFACE
*
* @param[in]  alpha : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_COLOR::SetAlpha(int alpha)
{
  this->alpha = alpha;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_COLOR::SetFromString(XCHAR* string)
* @brief      SetFromString
* @ingroup    USERINTERFACE
*
* @param[in]  string : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_COLOR::SetFromString(XCHAR* string)
{
  if(!string) return false;  

  XSTRING colorstr;
  int     ncommas = 0;
  int     _alpha  = 0;
  bool    status  = false;

  colorstr = string;
  if(colorstr.IsEmpty()) return false;
  
  for(XDWORD c=0; c<colorstr.GetSize(); c++)
    {
      XCHAR character = colorstr.Get()[c];
      if(character == __C(',')) ncommas++;
    }
    
  switch(ncommas)
    {
      case  0 : // only name
                { XSTRING* resolved_colorstr = GEN_UI_COLORS.Get(colorstr);
                  if(resolved_colorstr) status = SetFromString(resolved_colorstr->Get()); 
                }
                break;

      case  1 : // name +  int alpha
                { XSTRING  _colorstr;                  
                  XSTRING* resolved_colorstr = NULL;

                  _colorstr.AdjustSize(_MAXSTR);
                  colorstr.UnFormat(__L("%s,%d"), _colorstr.Get(), &_alpha);
                  _colorstr.AdjustSize();

                  resolved_colorstr = GEN_UI_COLORS.Get(_colorstr);
                  if(resolved_colorstr) status = SetFromString(resolved_colorstr->Get());                    

                  alpha = GetAlphaForPercent(_alpha);
                }
                break;

      case  2 : // int colors
                status = colorstr.UnFormat(__L("%d,%d,%d"), &red, &green, &blue);
                alpha = 255;  
                break;

      case  3 : // int colors + int alpha
                status = colorstr.UnFormat(__L("%d,%d,%d,%d"), &red, &green, &blue, &_alpha);
                alpha = GetAlphaForPercent(_alpha);
                break;

      default : break;
    }

  return status;

}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_COLOR::SetFromString(XSTRING& string)
* @brief      SetFromString
* @ingroup    USERINTERFACE
*
* @param[in]  string : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_COLOR::SetFromString(XSTRING& string)
{
  return SetFromString(string.Get());
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_COLOR::CopyFrom(UI_COLOR* color)
* @brief      CopyFrom
* @ingroup    USERINTERFACE
*
* @param[in]  color : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_COLOR::CopyFrom(UI_COLOR* color)
{
  if(!color) return false;

  red   = color->GetRed();
  green = color->GetGreen();
  blue  = color->GetBlue();
  alpha = color->GetAlpha();  

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_COLOR::CopyTo(UI_COLOR* color)
* @brief      CopyTo
* @ingroup    USERINTERFACE
*
* @param[in]  color : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_COLOR::CopyTo(UI_COLOR* color)
{
  if(!color) return false;

  color->SetRed(red);
  color->SetGreen(green);
  color->SetBlue(blue);
  color->SetAlpha(alpha);  

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int UI_COLOR::GetAlphaForPercent(int percent)
* @brief      GetAlphaForPercent
* @ingroup    USERINTERFACE
*
* @param[in]  percent : 
* 
* @return     int : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
int UI_COLOR::GetAlphaForPercent(int percent)
{
  int _percent = percent;

  if(_percent < 0)   _percent = 0;
  if(_percent > 100) _percent = 100;

  return (int)((_percent * 255) / 100);
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_COLOR::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    USERINTERFACE
*
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_COLOR::Clean()
{
  red   = 0;
  green = 0;
  blue  = 0;
  alpha = 0;
}

