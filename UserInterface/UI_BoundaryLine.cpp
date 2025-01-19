/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_BoundaryLine.cpp
* 
* @class      UI_BOUNDARYLINE
* @brief      User Interface Boundary Line class
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

#include "UI_BoundaryLine.h"

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
* @fn         UI_BOUNDARYLINE::UI_BOUNDARYLINE()
* @brief      Constructor of class
* @ingroup    USERINTERFACE
*
* --------------------------------------------------------------------------------------------------------------------*/
UI_BOUNDARYLINE::UI_BOUNDARYLINE()
{
  Clean();

  x       = 0;
  y       = 0;
  width   = 0;
  height  = 0;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         UI_BOUNDARYLINE::~UI_BOUNDARYLINE()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    USERINTERFACE
*
* --------------------------------------------------------------------------------------------------------------------*/
UI_BOUNDARYLINE::~UI_BOUNDARYLINE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_BOUNDARYLINE::CopyFrom(UI_BOUNDARYLINE& boundaryline)
* @brief      Copy from
* @ingroup    USERINTERFACE
*
* @param[in]  boundaryline : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_BOUNDARYLINE::CopyFrom(UI_BOUNDARYLINE& boundaryline)
{  
  x       = boundaryline.x;
  y       = boundaryline.y;
  width   = boundaryline.width;
  height  = boundaryline.height;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_BOUNDARYLINE::CopyTo(UI_BOUNDARYLINE& boundaryline)
* @brief      Copy to
* @ingroup    USERINTERFACE
*
* @param[in]  boundaryline : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void UI_BOUNDARYLINE::CopyTo(UI_BOUNDARYLINE& boundaryline)
{
  boundaryline.x       = x;
  boundaryline.y       = y;
  boundaryline.width   = width;
  boundaryline.height  = height;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_BOUNDARYLINE::SetAround(UI_BOUNDARYLINE& boundaryline)
* @brief      Set around
* @ingroup    USERINTERFACE
*
* @param[in]  boundaryline : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_BOUNDARYLINE::SetAround(UI_BOUNDARYLINE& boundaryline)
{
  if(x > boundaryline.x)    x = boundaryline.x;
  if(boundaryline.y > y)    y = boundaryline.y;

  if((boundaryline.x + boundaryline.width)  > (x + width))    width  = boundaryline.width  + (boundaryline.x - x);
  if((boundaryline.y - boundaryline.height) < (y - height))   height = boundaryline.height - (boundaryline.y - y);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_BOUNDARYLINE::IsWithin(XDWORD xpos, XDWORD ypos)
* @brief      Is within
* @ingroup    USERINTERFACE
*
* @param[in]  xpos : 
* @param[in]  ypos : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UI_BOUNDARYLINE::IsWithin(XDWORD xpos, XDWORD ypos)
{
  if( ((xpos >= x) &&  (xpos < (x + width)))  && 
      ((ypos <= y) &&  (ypos > (y - height))) )
    {
      return true;
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_BOUNDARYLINE::IsEmpty()
* @brief      Is empty
* @ingroup    USERINTERFACE
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_BOUNDARYLINE::IsEmpty()
{
  if(!x && !y && !width && !height)
    {
      return true;
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void UI_BOUNDARYLINE::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    USERINTERFACE
*
* --------------------------------------------------------------------------------------------------------------------*/
void UI_BOUNDARYLINE::Clean()
{
  x       = 0;
  y       = 0;
  width   = 0;
  height  = 0;
}


#pragma endregion

