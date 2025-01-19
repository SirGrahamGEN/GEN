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
* --------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "UI_Color.h"

#include "UI_Colors.h"

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
* @fn         UI_COLOR::UI_COLOR()
* @brief      Constructor of class
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
UI_COLOR::UI_COLOR()    
{ 
  Clean();                            
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_COLOR::UI_COLOR(XCHAR* string)
* @brief      Constructor of class
* @ingroup    USERINTERFACE
* 
* @param[in]  string : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
UI_COLOR::UI_COLOR(XCHAR* string)
{
  Clean();
  
  SetFromString(string);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_COLOR::UI_COLOR(XSTRING& string)
* @brief      Constructor of class
* @ingroup    USERINTERFACE
* 
* @param[in]  string : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
UI_COLOR::UI_COLOR(XSTRING& string)
{
  Clean();

  SetFromString(string);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_COLOR::~UI_COLOR()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
UI_COLOR::~UI_COLOR()    
{ 
  Clean();                            
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_COLOR::IsValid()
* @brief      Is valid
* @ingroup    USERINTERFACE
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_COLOR::IsValid()
{
  return valid;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_COLOR::SetValid(bool valid)
* @brief      Set valid
* @ingroup    USERINTERFACE
* 
* @param[in]  valid : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_COLOR::SetValid(bool valid)
{
  this->valid = valid;
  
  return true;
}

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_COLOR::SetInvalid()
* @brief      Set invalid
* @ingroup    USERINTERFACE
* 
* --------------------------------------------------------------------------------------------------------------------*/
void UI_COLOR::SetInvalid()
{
  valid = false;

  red   = 0;
  green = 0;
  blue  = 0;
  alpha = 0;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int UI_COLOR::GetRed()
* @brief      Get red
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
* @brief      Set red
* @ingroup    USERINTERFACE
*
* @param[in]  red : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_COLOR::SetRed(int red)  
{
  this->red = red;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int UI_COLOR::GetGreen()
* @brief      Get green
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
* @brief      Set green
* @ingroup    USERINTERFACE
*
* @param[in]  green : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_COLOR::SetGreen(int green)
{
  this->green = green;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int UI_COLOR::GetBlue()
* @brief      Get blue
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
* @brief      Set blue
* @ingroup    USERINTERFACE
*
* @param[in]  blue : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_COLOR::SetBlue(int blue)
{
  this->blue = blue;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int UI_COLOR::GetAlpha()
* @brief      Get alpha
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
* @brief      Set alpha
* @ingroup    USERINTERFACE
*
* @param[in]  alpha : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_COLOR::SetAlpha(int alpha)
{
  this->alpha = alpha;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_COLOR::SetFromString(XCHAR* string)
* @brief      Set from string
* @ingroup    USERINTERFACE
*
* @param[in]  string : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_COLOR::SetFromString(XCHAR* string)
{
  SetInvalid();

  if(!string) 
    {
      return false;  
    }

  XSTRING colorstr;
  int     ncommas = 0;
  int     _alpha  = 0;
  bool    status  = false;

  colorstr = string;
  if(colorstr.IsEmpty()) 
    {
      return false;
    }
  
  for(XDWORD c=0; c<colorstr.GetSize(); c++)
    {
      XCHAR character = colorstr.Get()[c];
      if(character == __C(',')) 
        {
          ncommas++;
        }
    }
    
  switch(ncommas)
    {
      case  0 : // only name
                { XSTRING* resolved_colorstr = GEN_UI_COLORS.Get(colorstr);
                  if(resolved_colorstr) 
                    {
                      status = SetFromString(resolved_colorstr->Get()); 
                    }
                }
                break;

      case  1 : // name +  int alpha
                { XSTRING  _colorstr;                  
                  XSTRING* resolved_colorstr = NULL;

                  _colorstr.AdjustSize(_MAXSTR);
                  colorstr.UnFormat(__L("%s,%d"), _colorstr.Get(), &_alpha);
                  _colorstr.AdjustSize();

                  resolved_colorstr = GEN_UI_COLORS.Get(_colorstr);
                  if(resolved_colorstr) 
                    {
                      status = SetFromString(resolved_colorstr->Get());                    
                    }

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

  if(!status)
    {
      SetInvalid();
    }

  valid = true;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_COLOR::SetFromString(XSTRING& string)
* @brief      Set from string
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
* @brief      Copy from
* @ingroup    USERINTERFACE
*
* @param[in]  color : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_COLOR::CopyFrom(UI_COLOR* color)
{
  if(!color) 
    {
      return false;
    }

  valid = color->IsValid();
  red   = color->GetRed();
  green = color->GetGreen();
  blue  = color->GetBlue();
  alpha = color->GetAlpha();  

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_COLOR::CopyTo(UI_COLOR* color)
* @brief      Copy to
* @ingroup    USERINTERFACE
*
* @param[in]  color : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_COLOR::CopyTo(UI_COLOR* color)
{
  if(!color) 
    {
      return false;
    }

  color->SetValid(valid);
  color->SetRed(red);
  color->SetGreen(green);
  color->SetBlue(blue);
  color->SetAlpha(alpha);  

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int UI_COLOR::GetAlphaForPercent(int percent)
* @brief      Get alpha for percent
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
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    USERINTERFACE
*
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_COLOR::Clean()
{
  valid = false;
  red   = 0;
  green = 0;
  blue  = 0;
  alpha = 0;
}


#pragma endregion

