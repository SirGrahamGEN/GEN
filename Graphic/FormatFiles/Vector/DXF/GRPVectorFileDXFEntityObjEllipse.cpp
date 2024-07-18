#pragma region INCLUDES

#include "GRPVectorFileDXFTextSectionEntities.h"
#include "GRPVectorFileDXFEntityObjEllipse.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFENTITYObjEllipse::GRPVECTORFILEDXFENTITYObjEllipse (XCHAR* nameType) : GRPVECTORFILEDXFENTITYObj (nameType)
{
   Clean();   

   type = GRPVECTORFILEDXFENTITYObjType_Ellipse;
}


GRPVECTORFILEDXFENTITYObjEllipse::~GRPVECTORFILEDXFENTITYObjEllipse ( )
{ 
   Clean();
}


GRPVECTORFILEDXFENTITYDEFPOINT* GRPVECTORFILEDXFENTITYObjEllipse::GetCenter()
{
   return &center;
}


bool GRPVECTORFILEDXFENTITYObjEllipse::SetCenter(GRPVECTORFILEDXFENTITYDEFPOINT* center)
{
   if(!center) return false;

   this->center = center;

   return true;
}


GRPVECTORFILEDXFENTITYDEFPOINT* GRPVECTORFILEDXFENTITYObjEllipse::GetMajorAxis()
{
   return &majorAxis;
}


bool GRPVECTORFILEDXFENTITYObjEllipse::SetMajorAxis(GRPVECTORFILEDXFENTITYDEFPOINT* majorAxis)
{
   if(!majorAxis) return false;

   this->majorAxis = majorAxis;

   return true;
}
  

double GRPVECTORFILEDXFENTITYObjEllipse::GetIniParameter()
{
   return iniParameter;
}


void GRPVECTORFILEDXFENTITYObjEllipse::SetIniParameter(double iniParameter)
{
   this->iniParameter = iniParameter;
}


double GRPVECTORFILEDXFENTITYObjEllipse::GetEndParameter()
{
   return endParameter;
}

void GRPVECTORFILEDXFENTITYObjEllipse::SetEndParameter(double endParameter)
{
   this->endParameter = endParameter;
}


void GRPVECTORFILEDXFENTITYObjEllipse::SetRadius (double radius)
{
   this->radius = radius;
}


double GRPVECTORFILEDXFENTITYObjEllipse::GetThickness ( )
{
   return thickness;
}


void GRPVECTORFILEDXFENTITYObjEllipse::SetThickness (double thickness)
{
   this->thickness = thickness;
}


GRPVECTORFILEDXFENTITYDEFPOINT* GRPVECTORFILEDXFENTITYObjEllipse::GetDirExtrusion()
{
   return &dirExtrusion;
}


bool GRPVECTORFILEDXFENTITYObjEllipse::SetDirExtrusion(GRPVECTORFILEDXFENTITYDEFPOINT* dirExtrusion)
{
   if(!dirExtrusion) return false;

   this->dirExtrusion = dirExtrusion;

   return true;
}


bool GRPVECTORFILEDXFENTITYObjEllipse::ApplyData(GRPVECTORFILEDXFENTITY* entity)
{
   GRPVECTORFILEDXFVALUE* value;

   GRPVECTORFILEDXFENTITYObj::ApplyData(entity);

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
      majorAxis.SetX((*value->GetData()));         
   }

   value = GetDataValue(VFDXF_END_POINT_Y , entity); 
   if(value) 
   {
      majorAxis.SetY((*value->GetData()));      
   }

   value = GetDataValue(VFDXF_END_POINT_Z , entity); 
   if(value) 
   {
      majorAxis.SetZ((*value->GetData()));  
   }  
   
   value = GetDataValue(VFDXF_INI_PARAMETER, entity);
   if(value) 
   {
      iniParameter = (*value->GetData());  
   }

   value = GetDataValue(VFDXF_END_PARAMETER, entity);
   if(value) 
   {
      endParameter = (*value->GetData());  
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
      dirExtrusion.SetX((*value->GetData()));      
   }

   value = GetDataValue(VFDXF_EXTRUSION_DIRECTION_Y, entity);  
   if(value) 
   {
      dirExtrusion.SetY((*value->GetData()));      
   }

   value = GetDataValue(VFDXF_EXTRUSION_DIRECTION_Z, entity);  
   if(value) 
   {
      dirExtrusion.SetY((*value->GetData()));      
   }
      
   return true;
}


void GRPVECTORFILEDXFENTITYObjEllipse::Clean ( )
{
   iniParameter = 0.0f;
   endParameter = 0.0f;

   radius = 0.0f;

   thickness= 0.0f;
}

#pragma endregion
