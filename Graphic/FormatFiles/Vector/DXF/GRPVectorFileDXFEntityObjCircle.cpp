#pragma region INCLUDES

#include "GRPVECTORFILEDXFTextSectionEntities.h"
#include "GRPVECTORFILEDXFEntityObjCircle.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFEntityObjCircle::GRPVECTORFILEDXFEntityObjCircle (XCHAR* nameType) : GRPVECTORFILEDXFEntityObj (nameType)
{
   Clean();   

   type = GRPVECTORFILEDXFEntityObjType_Circle;
}


GRPVECTORFILEDXFEntityObjCircle::~GRPVECTORFILEDXFEntityObjCircle ( )
{ 
   Clean();
}

GRPVECTORFILEDXFEntityDefPoint* GRPVECTORFILEDXFEntityObjCircle::GetCenter()
{
   return &center;
}


bool GRPVECTORFILEDXFEntityObjCircle::SetCenter(GRPVECTORFILEDXFEntityDefPoint* center)
{
   if(!center) return false;

   this->center = center;

   return true;
}


double GRPVECTORFILEDXFEntityObjCircle::GetRadius ( )
{
   return radius;
}


void GRPVECTORFILEDXFEntityObjCircle::SetRadius (double radius)
{
   this->radius = radius;
}


double GRPVECTORFILEDXFEntityObjCircle::GetThickness ( )
{
   return thickness;
}


void GRPVECTORFILEDXFEntityObjCircle::SetThickness (double thickness)
{
   this->thickness = thickness;
}


GRPVECTORFILEDXFEntityDefPoint* GRPVECTORFILEDXFEntityObjCircle::GetDirExtrusion()
{
   return &dirExtrusion;
}


bool GRPVECTORFILEDXFEntityObjCircle::SetDirExtrusion(GRPVECTORFILEDXFEntityDefPoint* dirExtrusion)
{
   if(!dirExtrusion) return false;

   this->dirExtrusion = dirExtrusion;

   return true;
}


bool GRPVECTORFILEDXFEntityObjCircle::ApplyData(GRPVECTORFILEDXFEntity* entity)
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


void GRPVECTORFILEDXFEntityObjCircle::Clean ( )
{
   radius = 0.0f;

   thickness= 0.0f;
}

#pragma endregion
