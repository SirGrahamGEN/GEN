/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       GRPXEvent.cpp
* 
* @class      GRPXEVENT
* @brief      Graphics XEvent class
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

#include "GRPXEvent.h"

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
* @fn         GRPXEVENT::GRPXEVENT(XSUBJECT* subject, XDWORD type, XDWORD family)
* @brief      Constructor of class
* @ingroup    GRAPHIC
*
* @param[in]  subject : subject origin
* @param[in]  type : type of event
* @param[in]  family : family of event
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPXEVENT::GRPXEVENT(XSUBJECT* subject, XDWORD type, XDWORD family): XEVENT(subject, type, family)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPXEVENT::~GRPXEVENT()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    GRAPHIC
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPXEVENT::~GRPXEVENT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPSCREEN* GRPXEVENT::GetScreen()
* @brief      Get screen
* @ingroup    GRAPHIC
*
* @return     GRPSCREEN* :
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPSCREEN* GRPXEVENT::GetScreen()
{
  return screen;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPXEVENT::SetScreen(GRPSCREEN* screen)
* @brief      Set screen
* @ingroup    GRAPHIC
*
* @param[in]  screen :
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPXEVENT::SetScreen(GRPSCREEN* screen)
{
  this->screen = screen;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPVIEWPORT* GRPXEVENT::GetViewport()
* @brief      Get viewport
* @ingroup    GRAPHIC
*
* @return     GRPVIEWPORT* :
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPVIEWPORT* GRPXEVENT::GetViewport()
{
  return viewport;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPXEVENT::SetViewport(GRPVIEWPORT* viewport)
* @brief      Set viewport
* @ingroup    GRAPHIC
*
* @param[in]  viewport :
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPXEVENT::SetViewport(GRPVIEWPORT* viewport)
{
  this->viewport = viewport;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPXEVENT::GetError()
* @brief      Get error
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPXEVENT::GetError()
{
  return error;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPXEVENT::SetError(bool error)
* @brief      Set error
* @ingroup    GRAPHIC
*
* @param[in]  error :
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPXEVENT::SetError(bool error)
{
  this->error = error;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPXEVENT::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    GRAPHIC
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPXEVENT::Clean()
{
  screen      = NULL;
  viewport    = NULL;
  error       = false;
}


#pragma endregion



















