/**-------------------------------------------------------------------------------------------------------------------
*
* @file       GRPViewPort.cpp
*
* @class      GRPVIEWPORT
* @brief      Graphics View Port class
* @ingroup    GRAPHIC
*
* @author     Abraham J. Velez
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
#include "GRPFactory.h"
#include "GRPScreen.h"
#include "GRPCanvasAGG.h"

#include "GRPViewPort.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPVIEWPORT::GRPVIEWPORT()
* @brief      Constructor
* @ingroup    GRAPHIC
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
GRPVIEWPORT::GRPVIEWPORT()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPVIEWPORT::~GRPVIEWPORT()
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
GRPVIEWPORT::~GRPVIEWPORT()
{
  if(canvas)
    {
      GRPFACTORY::GetInstance().DeleteCanvas(canvas);
    }

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* GRPVIEWPORT::GetID()
* @brief      GetID
* @ingroup    GRAPHIC
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* GRPVIEWPORT::GetID()
{
  return &ID;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPVIEWPORT::IsActive()
* @brief      Is Active View Port
* @ingroup    GRAPHIC
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool GRPVIEWPORT::IsActive()
{
  return active;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPVIEWPORT::SetIsActive(bool active)
* @brief      Set Is Active View Port
* @ingroup    GRAPHIC
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  active : true to active
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPVIEWPORT::SetIsActive(bool active)
{
  this->active = active;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPVIEWPORT_PROJECTIONTYPE GRPVIEWPORT::GetProjection()
* @brief      Get Projection Type
* @ingroup    GRAPHIC
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     GRPVIEWPORT_PROJECTIONTYPE : Type of Projection
*
*---------------------------------------------------------------------------------------------------------------------*/
GRPVIEWPORT_PROJECTIONTYPE GRPVIEWPORT::GetProjectionType()
{
  return projectiontype;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPVIEWPORT::SetProjectionType(GRPVIEWPORT_PROJECTIONTYPE projectiontype)
* @brief      Set Projection Type
* @ingroup    GRAPHIC
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  projectiontype : new projection type
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPVIEWPORT::SetProjectionType(GRPVIEWPORT_PROJECTIONTYPE projectiontype)
{
  this->projectiontype = projectiontype;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPVIEWPORT::CreateCanvas(int canvasx, int canvasy, GRPPROPERTIES* canvasproperties)
* @brief      Create
* @ingroup    GRAPHIC
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  canvasx :
* @param[in]  canvasy :
* @param[in]  canvasproperties :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool GRPVIEWPORT::CreateCanvas(GRPPROPERTIES& canvasproperties)
{
  canvas = GRPFACTORY::GetInstance().CreateCanvas(&canvasproperties);
  if(canvas)
    {
      canvas->SetWidth(canvasproperties.GetWidth());
      canvas->SetHeight(canvasproperties.GetHeight());

      canvas->CreateBuffers();
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float GRPVIEWPORT::GetPositionX()
* @brief      GetPositionX
* @ingroup    GRAPHIC
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     float :
*
*---------------------------------------------------------------------------------------------------------------------*/
float GRPVIEWPORT::GetPositionX()
{
  return x;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float GRPVIEWPORT::GetPositionY()
* @brief      GetPositionY
* @ingroup    GRAPHIC
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     float :
*
*---------------------------------------------------------------------------------------------------------------------*/
float  GRPVIEWPORT::GetPositionY()
{
  return y;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPVIEWPORT::SetPosition(float x, float y)
* @brief      Set Position View Port
* @ingroup    GRAPHIC
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  x : Set X position
* @param[in]  y : Set Y position
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPVIEWPORT::SetPosition(float x, float y)
{
  this->x = x;
  this->y = y;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float GRPVIEWPORT::GetWidth()
* @brief      GetWidth
* @ingroup    GRAPHIC
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     float :
*
*---------------------------------------------------------------------------------------------------------------------*/
float GRPVIEWPORT::GetWidth()
{
  return width;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float GRPVIEWPORT::GetHeight()
* @brief      GetHeight
* @ingroup    GRAPHIC
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     float :
*
*---------------------------------------------------------------------------------------------------------------------*/
float GRPVIEWPORT::GetHeight()
{
  return height;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPVIEWPORT::SetSize(float width, float height)
* @brief      SetSize
* @ingroup    GRAPHIC
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  width : Set Width of View Port
* @param[in]  height : Set Height of View Port
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPVIEWPORT::SetSize(float width, float height)
{
  this->width  = width;
  this->height = height;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPCANVAS* GRPVIEWPORT::GetCanvas()
* @brief      GetCanvas
* @ingroup    GRAPHIC
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     GRPCANVAS* :
*
*---------------------------------------------------------------------------------------------------------------------*/
GRPCANVAS*  GRPVIEWPORT::GetCanvas()
{
  return canvas;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPVIEWPORT::Clean()
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
void GRPVIEWPORT::Clean()
{
  active          = true;

  projectiontype  = GRPVIEWPORT_PROJECTIONTYPE_UNKNOWN;

  x               = 0.0f;
  y               = 0.0f;

  width           = 0.0f;
  height          = 0.0f;

  canvas          = NULL;
}



