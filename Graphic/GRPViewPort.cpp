/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       GRPViewport.cpp
* 
* @class      GRPVIEWPORT
* @brief      Graphics Viewport class
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
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "GRPViewport.h"

#include "GRPXEvent.h"
#include "GRPFactory.h"
#include "GRPScreen.h"
#include "GRPCanvasAGG.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPVIEWPORT::GRPVIEWPORT()
* @brief      Constructor
* @ingroup    GRAPHIC
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
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
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* @param[in]  active : true to active
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVIEWPORT::SetIsActive(bool active)
{
  this->active = active;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVIEWPORT_PROJECTIONTYPE GRPVIEWPORT::GetProjectionType()
* @brief      GetProjectionType
* @ingroup    GRAPHIC
* 
* @return     GRPVIEWPORT_PROJECTIONTYPE : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
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
* @param[in]  projectiontype : new projection type
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVIEWPORT::SetProjectionType(GRPVIEWPORT_PROJECTIONTYPE projectiontype)
{
  this->projectiontype = projectiontype;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPVIEWPORT::CreateCanvas(GRPPROPERTIES& canvasproperties)
* @brief      CreateCanvas
* @ingroup    GRAPHIC
* 
* @param[in]  canvasproperties : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
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
* @return     float :
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* @return     float :
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* @param[in]  x : Set X position
* @param[in]  y : Set Y position
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* @return     float :
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* @return     float :
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* @param[in]  width : Set Width of View Port
* @param[in]  height : Set Height of View Port
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* @return     GRPCANVAS* :
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* --------------------------------------------------------------------------------------------------------------------*/
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


#pragma endregion

