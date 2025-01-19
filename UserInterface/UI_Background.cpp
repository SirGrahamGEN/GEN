/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_Background.cpp
* 
* @class      UI_BACKGROUND
* @brief      User Interface Background class
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

#include "UI_Background.h"

#include "GRPBitmapFile.h"

#include "UI_Manager.h"

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
* @fn         UI_BACKGROUND::UI_BACKGROUND()
* @brief      Constructor of class
* @ingroup    USERINTERFACE
* 
* --------------------------------------------------------------------------------------------------------------------*/
UI_BACKGROUND::UI_BACKGROUND()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_BACKGROUND::~UI_BACKGROUND()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    USERINTERFACE
* 
* --------------------------------------------------------------------------------------------------------------------*/
UI_BACKGROUND::~UI_BACKGROUND()
{
  if(bitmap)
    {
      delete bitmap;
    }

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         UI_COLOR* UI_BACKGROUND::GetColor()
* @brief      Get color
* @ingroup    USERINTERFACE
* 
* @return     UI_COLOR* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
UI_COLOR* UI_BACKGROUND::GetColor()
{
  return &color;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* UI_BACKGROUND::GetBitmapFileName()
* @brief      Get bitmap file name
* @ingroup    USERINTERFACE
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* UI_BACKGROUND::GetBitmapFileName()
{
  return &bitmapfilename;
}

  
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPBITMAP* UI_BACKGROUND::GetBitmap()
* @brief      Get bitmap
* @ingroup    USERINTERFACE
* 
* @return     GRPBITMAP* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPBITMAP* UI_BACKGROUND::GetBitmap()
{
  return bitmap;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UI_BACKGROUND::SetBitmap(GRPBITMAP* bitmap)
* @brief      Set bitmap
* @ingroup    USERINTERFACE
* 
* @param[in]  bitmap : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool UI_BACKGROUND::SetBitmap(GRPBITMAP* bitmap)
{
  this->bitmap = bitmap;

  return bitmap?true:false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void UI_BACKGROUND::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    USERINTERFACE
* 
* --------------------------------------------------------------------------------------------------------------------*/
void UI_BACKGROUND::Clean()
{
  bitmap  = NULL;
}


#pragma endregion


