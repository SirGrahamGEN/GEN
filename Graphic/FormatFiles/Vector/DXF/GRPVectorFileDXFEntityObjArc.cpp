#pragma region INCLUDES

#include "GRPVectorFileDXFTextSectionEntities.h"
#include "GRPVectorFileDXFEntityObjArc.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFENTITYObjArc::GRPVECTORFILEDXFENTITYObjArc (XCHAR* nameType) : GRPVECTORFILEDXFENTITYObj (nameType)
{
   Clean();   

   type = GRPVECTORFILEDXFENTITYObjType_Arc;
}


GRPVECTORFILEDXFENTITYObjArc::~GRPVECTORFILEDXFENTITYObjArc ( )
{ 
   Clean();
}


GRPVECTORFILEDXFENTITYDEFPOINT* GRPVECTORFILEDXFENTITYObjArc::GetCenter()
{
   return &center;
}


bool GRPVECTORFILEDXFENTITYObjArc::SetCenter(GRPVECTORFILEDXFENTITYDEFPOINT* center)
{
   if(!center) return false;

   this->center = center;

   return true;
}


double GRPVECTORFILEDXFENTITYObjArc::GetIniAngle ( )
{
   return iniAngle;
}


void GRPVECTORFILEDXFENTITYObjArc::SetIniAngle (double angle)
{
   this->iniAngle = angle;
}


double GRPVECTORFILEDXFENTITYObjArc::GetEndAngle ( )
{
   return endAngle;
}


void GRPVECTORFILEDXFENTITYObjArc::SetEndAngle (double angle)
{
   this->endAngle = angle;
}


double GRPVECTORFILEDXFENTITYObjArc::GetRadius ( )
{
   return radius;
}


void GRPVECTORFILEDXFENTITYObjArc::SetRadius (double radius)
{
   this->radius = radius;
}


double GRPVECTORFILEDXFENTITYObjArc::GetThickness ( )
{
   return thickness;
}


void GRPVECTORFILEDXFENTITYObjArc::SetThickness (double thickness)
{
   this->thickness = thickness;
}


GRPVECTORFILEDXFENTITYDEFPOINT* GRPVECTORFILEDXFENTITYObjArc::GetDirExtrusion()
{
   return &dirExtrusion;
}


bool GRPVECTORFILEDXFENTITYObjArc::SetDirExtrusion(GRPVECTORFILEDXFENTITYDEFPOINT* dirExtrusion)
{
   if(!dirExtrusion) return false;

   this->dirExtrusion = dirExtrusion;

   return true;
}


bool GRPVECTORFILEDXFENTITYObjArc::ApplyData(GRPVECTORFILEDXFENTITY* entity)
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


void GRPVECTORFILEDXFENTITYObjArc::Clean ( )
{
   radius = 0.0f;

   iniAngle = 0.0f; 
   endAngle = 0.0f;   

   thickness= 0.0f;
}

#pragma endregion
