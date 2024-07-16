#pragma region INCLUDES

#include "GRPVECTORFILEDXFTextSectionEntities.h"
#include "GRPVECTORFILEDXFEntityObjArc.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFEntityObjArc::GRPVECTORFILEDXFEntityObjArc (XCHAR* nameType) : GRPVECTORFILEDXFEntityObj (nameType)
{
   Clean();   

   type = GRPVECTORFILEDXFEntityObjType_Arc;
}


GRPVECTORFILEDXFEntityObjArc::~GRPVECTORFILEDXFEntityObjArc ( )
{ 
   Clean();
}


GRPVECTORFILEDXFEntityDefPoint* GRPVECTORFILEDXFEntityObjArc::GetCenter()
{
   return &center;
}


bool GRPVECTORFILEDXFEntityObjArc::SetCenter(GRPVECTORFILEDXFEntityDefPoint* center)
{
   if(!center) return false;

   this->center = center;

   return true;
}


double GRPVECTORFILEDXFEntityObjArc::GetIniAngle ( )
{
   return iniAngle;
}


void GRPVECTORFILEDXFEntityObjArc::SetIniAngle (double angle)
{
   this->iniAngle = angle;
}


double GRPVECTORFILEDXFEntityObjArc::GetEndAngle ( )
{
   return endAngle;
}


void GRPVECTORFILEDXFEntityObjArc::SetEndAngle (double angle)
{
   this->endAngle = angle;
}


double GRPVECTORFILEDXFEntityObjArc::GetRadius ( )
{
   return radius;
}


void GRPVECTORFILEDXFEntityObjArc::SetRadius (double radius)
{
   this->radius = radius;
}


double GRPVECTORFILEDXFEntityObjArc::GetThickness ( )
{
   return thickness;
}


void GRPVECTORFILEDXFEntityObjArc::SetThickness (double thickness)
{
   this->thickness = thickness;
}


GRPVECTORFILEDXFEntityDefPoint* GRPVECTORFILEDXFEntityObjArc::GetDirExtrusion()
{
   return &dirExtrusion;
}


bool GRPVECTORFILEDXFEntityObjArc::SetDirExtrusion(GRPVECTORFILEDXFEntityDefPoint* dirExtrusion)
{
   if(!dirExtrusion) return false;

   this->dirExtrusion = dirExtrusion;

   return true;
}


bool GRPVECTORFILEDXFEntityObjArc::ApplyData(GRPVECTORFILEDXFEntity* entity)
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
 
   value = GetDataValue( VFDXF_RADIOUS, entity); 
   if(value) 
   {
      radius =(*value->GetData());      
   }
   
   value = GetDataValue(VFDXF_INI_ANGLE , entity); 
   if(value) 
   {
      iniAngle =(*value->GetData());      
   }

   value = GetDataValue(VFDXF_END_ANGLE , entity); 
   if(value) 
   {
      endAngle =(*value->GetData());      
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


void GRPVECTORFILEDXFEntityObjArc::Clean ( )
{
   radius = 0.0f;

   iniAngle = 0.0f; 
   endAngle = 0.0f;   

   thickness= 0.0f;
}

#pragma endregion
