#pragma region INCLUDES

#include "GRPVECTORFILEDXFTextSectionEntities.h"
#include "GRPVECTORFILEDXFEntityObjPoint.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFEntityObjPoint::GRPVECTORFILEDXFEntityObjPoint (XCHAR* nameType) : GRPVECTORFILEDXFEntityObj (nameType)
{
   Clean();   

   type = GRPVECTORFILEDXFEntityObjType_Point;
}


GRPVECTORFILEDXFEntityObjPoint::~GRPVECTORFILEDXFEntityObjPoint ( )
{ 
   Clean();
}


GRPVECTORFILEDXFEntityDefPoint* GRPVECTORFILEDXFEntityObjPoint::GetPoint ( )
{
   return &point;
}

      
bool GRPVECTORFILEDXFEntityObjPoint::SetPoint (GRPVECTORFILEDXFEntityDefPoint* point)
{
   if(!point) return false;

   this->point = point;

   return true;
}

   
double GRPVECTORFILEDXFEntityObjPoint::GetXAxisAngle ( )
{
   return xAxisAngle;
}
      
      
void GRPVECTORFILEDXFEntityObjPoint::SetXAxisAngle (double xAxisAngle)
{
   this->xAxisAngle = xAxisAngle; 
}


double GRPVECTORFILEDXFEntityObjPoint::GetThickness ( )
{
   return thickness;
}


void GRPVECTORFILEDXFEntityObjPoint::SetThickness (double thickness)
{
   this->thickness = thickness;
}


GRPVECTORFILEDXFEntityDefPoint* GRPVECTORFILEDXFEntityObjPoint::GetDirExtrusion()
{
   return &dirExtrusion;
}


bool GRPVECTORFILEDXFEntityObjPoint::SetDirExtrusion(GRPVECTORFILEDXFEntityDefPoint* dirExtrusion)
{
   if(!dirExtrusion) return false;

   this->dirExtrusion = dirExtrusion;

   return true;
}


bool GRPVECTORFILEDXFEntityObjPoint::ApplyData(GRPVECTORFILEDXFEntity* entity)
{
   GRPVECTORFILEDXFValue* value;

   GRPVECTORFILEDXFEntityObj::ApplyData(entity);   

   value = GetDataValue( VFDXF_POINT_X, entity); 
   if(value) 
   {
      point.SetX((*value->GetData()));         
   }

   value = GetDataValue( VFDXF_POINT_Y, entity); 
   if(value) 
   {
      point.SetY((*value->GetData()));      
   }

   value = GetDataValue( VFDXF_POINT_Z, entity); 
   if(value) 
   {
      point.SetZ((*value->GetData()));             
   }
 
   value = GetDataValue(VFDXF_ANGLE_X, entity); 
   if(value) 
   {
      xAxisAngle =(*value->GetData());      
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


void GRPVECTORFILEDXFEntityObjPoint::Clean ( )
{
   xAxisAngle = 0.0f;
}

#pragma endregion
