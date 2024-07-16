#pragma region INCLUDES

#include "GRPVECTORFILEDXFTextSectionEntities.h"
#include "GRPVECTORFILEDXFEntityObjEllipse.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFEntityObjEllipse::GRPVECTORFILEDXFEntityObjEllipse (XCHAR* nameType) : GRPVECTORFILEDXFEntityObj (nameType)
{
   Clean();   

   type = GRPVECTORFILEDXFEntityObjType_Ellipse;
}


GRPVECTORFILEDXFEntityObjEllipse::~GRPVECTORFILEDXFEntityObjEllipse ( )
{ 
   Clean();
}


GRPVECTORFILEDXFEntityDefPoint* GRPVECTORFILEDXFEntityObjEllipse::GetCenter()
{
   return &center;
}


bool GRPVECTORFILEDXFEntityObjEllipse::SetCenter(GRPVECTORFILEDXFEntityDefPoint* center)
{
   if(!center) return false;

   this->center = center;

   return true;
}


GRPVECTORFILEDXFEntityDefPoint* GRPVECTORFILEDXFEntityObjEllipse::GetMajorAxis()
{
   return &majorAxis;
}


bool GRPVECTORFILEDXFEntityObjEllipse::SetMajorAxis(GRPVECTORFILEDXFEntityDefPoint* majorAxis)
{
   if(!majorAxis) return false;

   this->majorAxis = majorAxis;

   return true;
}
  

double GRPVECTORFILEDXFEntityObjEllipse::GetIniParameter()
{
   return iniParameter;
}


void GRPVECTORFILEDXFEntityObjEllipse::SetIniParameter(double iniParameter)
{
   this->iniParameter = iniParameter;
}


double GRPVECTORFILEDXFEntityObjEllipse::GetEndParameter()
{
   return endParameter;
}

void GRPVECTORFILEDXFEntityObjEllipse::SetEndParameter(double endParameter)
{
   this->endParameter = endParameter;
}


void GRPVECTORFILEDXFEntityObjEllipse::SetRadius (double radius)
{
   this->radius = radius;
}


double GRPVECTORFILEDXFEntityObjEllipse::GetThickness ( )
{
   return thickness;
}


void GRPVECTORFILEDXFEntityObjEllipse::SetThickness (double thickness)
{
   this->thickness = thickness;
}


GRPVECTORFILEDXFEntityDefPoint* GRPVECTORFILEDXFEntityObjEllipse::GetDirExtrusion()
{
   return &dirExtrusion;
}


bool GRPVECTORFILEDXFEntityObjEllipse::SetDirExtrusion(GRPVECTORFILEDXFEntityDefPoint* dirExtrusion)
{
   if(!dirExtrusion) return false;

   this->dirExtrusion = dirExtrusion;

   return true;
}


bool GRPVECTORFILEDXFEntityObjEllipse::ApplyData(GRPVECTORFILEDXFEntity* entity)
{
   GRPVECTORFILEDXFValue* value;

   GRPVECTORFILEDXFEntityObj::ApplyData(entity);

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


void GRPVECTORFILEDXFEntityObjEllipse::Clean ( )
{
   iniParameter = 0.0f;
   endParameter = 0.0f;

   radius = 0.0f;

   thickness= 0.0f;
}

#pragma endregion
