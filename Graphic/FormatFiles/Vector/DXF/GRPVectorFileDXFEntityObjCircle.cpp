#pragma region INCLUDES

#include "GRPVectorFileDXFTextSectionEntities.h"
#include "GRPVectorFileDXFEntityObjCircle.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFENTITYObjCircle::GRPVECTORFILEDXFENTITYObjCircle (XCHAR* nameType) : GRPVECTORFILEDXFENTITYObj (nameType)
{
   Clean();   

   type = GRPVECTORFILEDXFENTITYObjType_Circle;
}


GRPVECTORFILEDXFENTITYObjCircle::~GRPVECTORFILEDXFENTITYObjCircle ( )
{ 
   Clean();
}

GRPVECTORFILEDXFENTITYDEFPOINT* GRPVECTORFILEDXFENTITYObjCircle::GetCenter()
{
   return &center;
}


bool GRPVECTORFILEDXFENTITYObjCircle::SetCenter(GRPVECTORFILEDXFENTITYDEFPOINT* center)
{
   if(!center) return false;

   this->center = center;

   return true;
}


double GRPVECTORFILEDXFENTITYObjCircle::GetRadius ( )
{
   return radius;
}


void GRPVECTORFILEDXFENTITYObjCircle::SetRadius (double radius)
{
   this->radius = radius;
}


double GRPVECTORFILEDXFENTITYObjCircle::GetThickness ( )
{
   return thickness;
}


void GRPVECTORFILEDXFENTITYObjCircle::SetThickness (double thickness)
{
   this->thickness = thickness;
}


GRPVECTORFILEDXFENTITYDEFPOINT* GRPVECTORFILEDXFENTITYObjCircle::GetDirExtrusion()
{
   return &dirExtrusion;
}


bool GRPVECTORFILEDXFENTITYObjCircle::SetDirExtrusion(GRPVECTORFILEDXFENTITYDEFPOINT* dirExtrusion)
{
   if(!dirExtrusion) return false;

   this->dirExtrusion = dirExtrusion;

   return true;
}


bool GRPVECTORFILEDXFENTITYObjCircle::ApplyData(GRPVECTORFILEDXFENTITY* entity)
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


void GRPVECTORFILEDXFENTITYObjCircle::Clean ( )
{
   radius = 0.0f;

   thickness= 0.0f;
}

#pragma endregion
