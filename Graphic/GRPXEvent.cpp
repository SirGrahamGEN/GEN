/**-------------------------------------------------------------------------------------------------------------------
*
* @file       GRPXEvent.cpp
*
* @class      GRPXEVENT
* @brief      Graphics XEvent class
* @ingroup    GRAPHIC
*
* @author     Diego Martinez Ruiz de Gaona
* @date       01/03/2016 12:00
*
* @copyright  Copyright(c) 2008 - 2016 GEN Group.
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

#include "GRPXEvent.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPXEVENT::GRPXEVENT(XSUBJECT* subject, XDWORD type, XDWORD family)
* @brief      Constructor
* @ingroup    GRAPHIC
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  XSUBJECT* : subject origin
* @param[in]  XDWORD type : type of event
* @param[in]  XDWORD family : family of event
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
GRPXEVENT::GRPXEVENT(XSUBJECT* subject, XDWORD type, XDWORD family): XEVENT(subject, type, family)
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPXEVENT::~GRPXEVENT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    GRAPHIC
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
GRPXEVENT::~GRPXEVENT()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPSCREEN* GRPXEVENT::GetScreen()
* @brief      Get Screen
* @ingroup    GRAPHIC
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     GRPSCREEN* :
*
*---------------------------------------------------------------------------------------------------------------------*/
GRPSCREEN* GRPXEVENT::GetScreen()
{
  return screen;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPXEVENT::SetScreen(GRPSCREEN* screen)
* @brief      Set Screen
* @ingroup    GRAPHIC
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  screen :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPXEVENT::SetScreen(GRPSCREEN* screen)
{
  this->screen = screen;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPVIEWPORT* GRPXEVENT::GetViewport()
* @brief      Get Viewport
* @ingroup    GRAPHIC
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     GRPVIEWPORT* :
*
*---------------------------------------------------------------------------------------------------------------------*/
GRPVIEWPORT* GRPXEVENT::GetViewport()
{
  return viewport;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPXEVENT::SetViewport(GRPVIEWPORT* viewport)
* @brief      Set Viewport
* @ingroup    GRAPHIC
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  viewport :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPXEVENT::SetViewport(GRPVIEWPORT* viewport)
{
  this->viewport = viewport;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPXEVENT::GetError()
* @brief      GetError
* @ingroup    GRAPHIC
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool GRPXEVENT::GetError()
{
  return error;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPXEVENT::SetError(bool error)
* @brief      SetError
* @ingroup    GRAPHIC
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  error :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPXEVENT::SetError(bool error)
{
  this->error = error;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPXEVENT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    GRAPHIC
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPXEVENT::Clean()
{
  screen      = NULL;
  viewport    = NULL;
  error       = false;
}

