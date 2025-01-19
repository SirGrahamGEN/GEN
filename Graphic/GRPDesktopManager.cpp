/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       GRPDesktopManager.cpp
* 
* @class      GRPDESKTOPMANAGER
* @brief      Graphics Desktop Manager class
* @ingroup    GRAPHIC
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

#include "GRPDesktopManager.h"

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


#pragma region CLASS_GRPDESKTOPMONITORS
   

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPDESKTOPMONITORS::GRPDESKTOPMONITORS()
* @brief      Constructor of class
* @ingroup    GRAPHIC
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPDESKTOPMONITORS::GRPDESKTOPMONITORS()
{
  Clean();

  combinedrect.Set(0, 0, 0, 0);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPDESKTOPMONITORS::~GRPDESKTOPMONITORS()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    GRAPHIC
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPDESKTOPMONITORS::~GRPDESKTOPMONITORS()
{
  monitorsrects.DeleteContents();
  monitorsrects.DeleteAll();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<GRPRECTINT*>* GRPDESKTOPMONITORS::GetMonitorsRects()
* @brief      Get monitors rects
* @ingroup    GRAPHIC
* 
* @return     XVECTOR<GRPRECTINT*>* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<GRPRECTINT*>* GRPDESKTOPMONITORS::GetMonitorsRects()
{
  return &monitorsrects;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPRECTINT* GRPDESKTOPMONITORS::GetCombinedRect()
* @brief      Get combined rect
* @ingroup    GRAPHIC
* 
* @return     GRPRECTINT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPRECTINT* GRPDESKTOPMONITORS::GetCombinedRect()
{
  return &combinedrect;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPDESKTOPMONITORS::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    GRAPHIC
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPDESKTOPMONITORS::Clean()
{

}


#pragma endregion


#pragma region CLASS_GRPDESKTOPMANAGER


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPDESKTOPMANAGER::GRPDESKTOPMANAGER()
* @brief      Constructor of class
* @ingroup    GRAPHIC
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPDESKTOPMANAGER::GRPDESKTOPMANAGER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPDESKTOPMANAGER::~GRPDESKTOPMANAGER()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    GRAPHIC
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPDESKTOPMANAGER::~GRPDESKTOPMANAGER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPDESKTOPMONITORS* GRPDESKTOPMANAGER::GetDesktopMonitors()
* @brief      Get desktop monitors
* @ingroup    GRAPHIC
* 
* @return     GRPDESKTOPMONITORS* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPDESKTOPMONITORS* GRPDESKTOPMANAGER::GetDesktopMonitors()
{
  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPDESKTOPMANAGER::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    GRAPHIC
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPDESKTOPMANAGER::Clean()
{

}


#pragma endregion


#pragma endregion

