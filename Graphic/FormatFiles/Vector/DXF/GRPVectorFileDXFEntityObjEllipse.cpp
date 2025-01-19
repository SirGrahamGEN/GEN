/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       GRPVectorFileDXFEntityObjEllipse.cpp
* 
* @class      GRPVECTORFILEDXFENTITYOBJELLIPSE
* @brief      Graphic Vector File DXF Entity Obj Ellipse class
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

#include "GRPVectorFileDXFEntityObjEllipse.h"

#include "GRPVectorFileDXFTextSectionEntities.h"

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
* @fn         GRPVECTORFILEDXFENTITYOBJELLIPSE::GRPVECTORFILEDXFENTITYOBJELLIPSE(XCHAR* nametype)
* @brief      Constructor of class
* @ingroup    GRAPHIC
* 
* @param[in]  nametype : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILEDXFENTITYOBJELLIPSE::GRPVECTORFILEDXFENTITYOBJELLIPSE(XCHAR* nametype) : GRPVECTORFILEDXFENTITYOBJ (nametype)
{
  Clean();   

  type = GRPVECTORFILEDXFENTITYOBJTYPE_ELLIPSE;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILEDXFENTITYOBJELLIPSE::~GRPVECTORFILEDXFENTITYOBJELLIPSE()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    GRAPHIC
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILEDXFENTITYOBJELLIPSE::~GRPVECTORFILEDXFENTITYOBJELLIPSE()
{ 
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILEDXFENTITYDEFPOINT* GRPVECTORFILEDXFENTITYOBJELLIPSE::GetCenter()
* @brief      Get center
* @ingroup    GRAPHIC
* 
* @return     GRPVECTORFILEDXFENTITYDEFPOINT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILEDXFENTITYDEFPOINT* GRPVECTORFILEDXFENTITYOBJELLIPSE::GetCenter()
{
  return &center;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPVECTORFILEDXFENTITYOBJELLIPSE::SetCenter(GRPVECTORFILEDXFENTITYDEFPOINT* center)
* @brief      Set center
* @ingroup    GRAPHIC
* 
* @param[in]  center : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPVECTORFILEDXFENTITYOBJELLIPSE::SetCenter(GRPVECTORFILEDXFENTITYDEFPOINT* center)
{
  if(!center) 
    {
      return false;
    }

  this->center = center;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILEDXFENTITYDEFPOINT* GRPVECTORFILEDXFENTITYOBJELLIPSE::GetMajorAxis()
* @brief      Get major axis
* @ingroup    GRAPHIC
* 
* @return     GRPVECTORFILEDXFENTITYDEFPOINT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILEDXFENTITYDEFPOINT* GRPVECTORFILEDXFENTITYOBJELLIPSE::GetMajorAxis()
{
  return &majoraxis;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPVECTORFILEDXFENTITYOBJELLIPSE::SetMajorAxis(GRPVECTORFILEDXFENTITYDEFPOINT* majoraxis)
* @brief      Set major axis
* @ingroup    GRAPHIC
* 
* @param[in]  majoraxis : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPVECTORFILEDXFENTITYOBJELLIPSE::SetMajorAxis(GRPVECTORFILEDXFENTITYDEFPOINT* majoraxis)
{
  if(!majoraxis) 
    {
      return false;
    }

  this->majoraxis = majoraxis;

  return true;
}
  

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double GRPVECTORFILEDXFENTITYOBJELLIPSE::GetIniParameter()
* @brief      Get ini parameter
* @ingroup    GRAPHIC
* 
* @return     double : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
double GRPVECTORFILEDXFENTITYOBJELLIPSE::GetIniParameter()
{
  return iniparameter;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPVECTORFILEDXFENTITYOBJELLIPSE::SetIniParameter(double iniparameter)
* @brief      Set ini parameter
* @ingroup    GRAPHIC
* 
* @param[in]  iniparameter : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVECTORFILEDXFENTITYOBJELLIPSE::SetIniParameter(double iniparameter)
{
  this->iniparameter = iniparameter;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double GRPVECTORFILEDXFENTITYOBJELLIPSE::GetEndParameter()
* @brief      Get end parameter
* @ingroup    GRAPHIC
* 
* @return     double : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
double GRPVECTORFILEDXFENTITYOBJELLIPSE::GetEndParameter()
{
  return endparameter;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPVECTORFILEDXFENTITYOBJELLIPSE::SetEndParameter(double endparameter)
* @brief      Set end parameter
* @ingroup    GRAPHIC
* 
* @param[in]  endparameter : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVECTORFILEDXFENTITYOBJELLIPSE::SetEndParameter(double endparameter)
{
  this->endparameter = endparameter;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double GRPVECTORFILEDXFENTITYOBJELLIPSE::GetRadius()
* @brief      Get radius
* @ingroup    GRAPHIC
* 
* @return     double : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
double GRPVECTORFILEDXFENTITYOBJELLIPSE::GetRadius()
{
  return radius;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPVECTORFILEDXFENTITYOBJELLIPSE::SetRadius(double radius)
* @brief      Set radius
* @ingroup    GRAPHIC
* 
* @param[in]  radius : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVECTORFILEDXFENTITYOBJELLIPSE::SetRadius(double radius)
{
  this->radius = radius;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double GRPVECTORFILEDXFENTITYOBJELLIPSE::GetThickness()
* @brief      Get thickness
* @ingroup    GRAPHIC
* 
* @return     double : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
double GRPVECTORFILEDXFENTITYOBJELLIPSE::GetThickness()
{
  return thickness;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPVECTORFILEDXFENTITYOBJELLIPSE::SetThickness(double thickness)
* @brief      Set thickness
* @ingroup    GRAPHIC
* 
* @param[in]  thickness : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVECTORFILEDXFENTITYOBJELLIPSE::SetThickness(double thickness)
{
  this->thickness = thickness;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILEDXFENTITYDEFPOINT* GRPVECTORFILEDXFENTITYOBJELLIPSE::GetDirExtrusion()
* @brief      Get dir extrusion
* @ingroup    GRAPHIC
* 
* @return     GRPVECTORFILEDXFENTITYDEFPOINT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILEDXFENTITYDEFPOINT* GRPVECTORFILEDXFENTITYOBJELLIPSE::GetDirExtrusion()
{
  return &dirextrusion;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPVECTORFILEDXFENTITYOBJELLIPSE::SetDirExtrusion(GRPVECTORFILEDXFENTITYDEFPOINT* dirextrusion)
* @brief      Set dir extrusion
* @ingroup    GRAPHIC
* 
* @param[in]  dirextrusion : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPVECTORFILEDXFENTITYOBJELLIPSE::SetDirExtrusion(GRPVECTORFILEDXFENTITYDEFPOINT* dirextrusion)
{
  if(!dirextrusion) 
    {
      return false;
    }

  this->dirextrusion = dirextrusion;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPVECTORFILEDXFENTITYOBJELLIPSE::ApplyData(GRPVECTORFILEDXFENTITY* entity)
* @brief      Apply data
* @ingroup    GRAPHIC
* 
* @param[in]  entity : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPVECTORFILEDXFENTITYOBJELLIPSE::ApplyData(GRPVECTORFILEDXFENTITY* entity)
{
  GRPVECTORFILEDXFVALUE* value;

  GRPVECTORFILEDXFENTITYOBJ::ApplyData(entity);

  value = GetDataValue( VFDXF_CENTER_POINT_X, entity); 
  if(value) 
    {
      center.SetX((*value->GetData()));         
    }

  value = GetDataValue( VFDXF_CENTER_POINT_Y, entity); 
  if(value) 
    {
      center.SetY((*value->GetData()));      
    }

  value = GetDataValue( VFDXF_CENTER_POINT_Z, entity); 
  if(value) 
    {
      center.SetZ((*value->GetData()));             
    }
   
  value = GetDataValue(VFDXF_END_POINT_X , entity); 
  if(value) 
    {
      majoraxis.SetX((*value->GetData()));         
    }

  value = GetDataValue(VFDXF_END_POINT_Y , entity); 
  if(value) 
    {
      majoraxis.SetY((*value->GetData()));      
    }

  value = GetDataValue(VFDXF_END_POINT_Z , entity); 
  if(value) 
    {
      majoraxis.SetZ((*value->GetData()));  
    }  
   
  value = GetDataValue(VFDXF_INI_PARAMETER, entity);
  if(value) 
    {
      iniparameter = (*value->GetData());  
    }

  value = GetDataValue(VFDXF_END_PARAMETER, entity);
  if(value) 
    {
      endparameter = (*value->GetData());  
    }
 
  value = GetDataValue( VFDXF_RADIOUS, entity); 
  if(value) 
    {
      radius =(*value->GetData());      
    }
   
  value = GetDataValue(VFDXF_THICKNESS, entity);  
  if(value) 
    {
      thickness = (*value->GetData());
    }

  value = GetDataValue(VFDXF_EXTRUSION_DIRECTION_X, entity);  
  if(value) 
    {
      dirextrusion.SetX((*value->GetData()));      
    }

  value = GetDataValue(VFDXF_EXTRUSION_DIRECTION_Y, entity);  
  if(value) 
    {
      dirextrusion.SetY((*value->GetData()));      
    }

  value = GetDataValue(VFDXF_EXTRUSION_DIRECTION_Z, entity);  
  if(value) 
    {
      dirextrusion.SetY((*value->GetData()));      
    }
      
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPVECTORFILEDXFENTITYOBJELLIPSE::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    GRAPHIC
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVECTORFILEDXFENTITYOBJELLIPSE::Clean()
{
  iniparameter = 0.0f;
  endparameter = 0.0f;

  radius = 0.0f;

  thickness= 0.0f;
}


#pragma endregion

