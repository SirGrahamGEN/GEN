/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XRect.cpp
* 
* @class      XRECT
* @brief      eXtended Utils Rect class
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

#include "XRect.h"

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
* @fn         XRECT::XRECT()
* @brief      Constructor of class
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XRECT::XRECT()
{
  Clean();

  x1 = 0.0f;
  y1 = 0.0f;
  x2 = 1.0f;
  y2 = 1.0f;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XRECT::~XRECT()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XRECT::~XRECT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XRECT::CopyFrom(XRECT& xrect)
* @brief      Copy from
* @ingroup    XUTILS
*
* @param[in]  xrect : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void XRECT::CopyFrom(XRECT& xrect)
{  
  x1 = xrect.x1;
  y1 = xrect.y1;
  x2 = xrect.x2;
  y2 = xrect.y2;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XRECT::CopyTo(XRECT& xrect)
* @brief      Copy to
* @ingroup    XUTILS
*
* @param[in]  xrect : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void XRECT::CopyTo(XRECT& xrect)
{
  xrect.x1 = x1;
  xrect.y1 = y1;
  xrect.x2 = x2;
  xrect.y2 = y2;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XRECT::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XRECT::Clean()
{
  x1    = 0.0f;
  y1    = 0.0f;
  x2    = 0.0f;
  y2    = 0.0f;
}


#pragma endregion

