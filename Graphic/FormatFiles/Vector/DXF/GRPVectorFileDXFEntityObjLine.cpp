/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       GRPVectorFileDXFEntityObjLine.cpp
* 
* @class      GRPVECTORFILEDXFENTITYOBJLINE
* @brief      Graphic Vector File DXF Entity Obj Line class
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

#include "GRPVectorFileDXFEntityObjLine.h"

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
* @fn         GRPVECTORFILEDXFENTITYOBJLINE::GRPVECTORFILEDXFENTITYOBJLINE(XCHAR* nametype)
* @brief      Constructor
* @ingroup    GRAPHIC
* 
* @param[in]  XCHAR* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILEDXFENTITYOBJLINE::GRPVECTORFILEDXFENTITYOBJLINE(XCHAR* nametype) : GRPVECTORFILEDXFENTITYOBJ(nametype)
{
  Clean();   

  type = GRPVECTORFILEDXFENTITYOBJTYPE_LINE;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILEDXFENTITYOBJLINE::~GRPVECTORFILEDXFENTITYOBJLINE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    GRAPHIC
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILEDXFENTITYOBJLINE::~GRPVECTORFILEDXFENTITYOBJLINE()
{ 
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILEDXFENTITYDEFPOINT* GRPVECTORFILEDXFENTITYOBJLINE::GetIni()
* @brief      GetIni
* @ingroup    GRAPHIC
* 
* @return     GRPVECTORFILEDXFENTITYDEFPOINT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILEDXFENTITYDEFPOINT* GRPVECTORFILEDXFENTITYOBJLINE::GetIni()
{
  return &ini;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPVECTORFILEDXFENTITYOBJLINE::SetIni(GRPVECTORFILEDXFENTITYDEFPOINT* point)
* @brief      SetIni
* @ingroup    GRAPHIC
* 
* @param[in]  point : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPVECTORFILEDXFENTITYOBJLINE::SetIni(GRPVECTORFILEDXFENTITYDEFPOINT* point)
{
  if(!point) return false;

  this->ini = point;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILEDXFENTITYDEFPOINT* GRPVECTORFILEDXFENTITYOBJLINE::GetEnd()
* @brief      GetEnd
* @ingroup    GRAPHIC
* 
* @return     GRPVECTORFILEDXFENTITYDEFPOINT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILEDXFENTITYDEFPOINT* GRPVECTORFILEDXFENTITYOBJLINE::GetEnd()
{
  return &end;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPVECTORFILEDXFENTITYOBJLINE::SetEnd(GRPVECTORFILEDXFENTITYDEFPOINT* point)
* @brief      SetEnd
* @ingroup    GRAPHIC
* 
* @param[in]  point : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPVECTORFILEDXFENTITYOBJLINE::SetEnd(GRPVECTORFILEDXFENTITYDEFPOINT* point)
{
  if(!point) return false;

  this->end = point;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         double GRPVECTORFILEDXFENTITYOBJLINE::GetThickness()
* @brief      GetThickness
* @ingroup    GRAPHIC
* 
* @return     double : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
double GRPVECTORFILEDXFENTITYOBJLINE::GetThickness()
{
  return thickness;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPVECTORFILEDXFENTITYOBJLINE::SetThickness (double thickness)
* @brief      SetThickness
* @ingroup    GRAPHIC
* 
* @param[in]  thickness : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVECTORFILEDXFENTITYOBJLINE::SetThickness (double thickness)
{
  this->thickness = thickness;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILEDXFENTITYDEFPOINT* GRPVECTORFILEDXFENTITYOBJLINE::GetDirExtrusion()
* @brief      GetDirExtrusion
* @ingroup    GRAPHIC
* 
* @return     GRPVECTORFILEDXFENTITYDEFPOINT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILEDXFENTITYDEFPOINT* GRPVECTORFILEDXFENTITYOBJLINE::GetDirExtrusion()
{
  return &dirextrusion;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPVECTORFILEDXFENTITYOBJLINE::SetDirExtrusion(GRPVECTORFILEDXFENTITYDEFPOINT* dirextrusion)
* @brief      SetDirExtrusion
* @ingroup    GRAPHIC
* 
* @param[in]  dirextrusion : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPVECTORFILEDXFENTITYOBJLINE::SetDirExtrusion(GRPVECTORFILEDXFENTITYDEFPOINT* dirextrusion)
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
* @fn         bool GRPVECTORFILEDXFENTITYOBJLINE::ApplyData(GRPVECTORFILEDXFENTITY* entity)
* @brief      ApplyData
* @ingroup    GRAPHIC
* 
* @param[in]  entity : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPVECTORFILEDXFENTITYOBJLINE::ApplyData(GRPVECTORFILEDXFENTITY* entity)
{
  GRPVECTORFILEDXFVALUE* value;

  GRPVECTORFILEDXFENTITYOBJ::ApplyData(entity);

  value = GetDataValue(VFDXF_INI_POINT_X, entity);  
  if(value) 
    {
      ini.SetX((*value->GetData()));      
    }

  value = GetDataValue(VFDXF_INI_POINT_Y, entity);  
  if(value) 
    {
      ini.SetY((*value->GetData()));      
    }

  value = GetDataValue(VFDXF_INI_POINT_Z, entity);  
  if(value) 
    {
      ini.SetZ((*value->GetData()));      
    }

  value = GetDataValue(VFDXF_END_POINT_X, entity);  
  if(value) 
    {
      end.SetX((*value->GetData()));      
    }

  value = GetDataValue(VFDXF_END_POINT_Y, entity);  
  if(value) 
    {
      end.SetY((*value->GetData()));      
    }

  value = GetDataValue(VFDXF_INI_POINT_Z, entity);  
  if(value) 
    {
      end.SetZ((*value->GetData()));      
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
* @fn         void GRPVECTORFILEDXFENTITYOBJLINE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    GRAPHIC
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVECTORFILEDXFENTITYOBJLINE::Clean()
{
  thickness = 0.0f;    
}


#pragma endregion

