#pragma region INCLUDES

#include "GRPVectorFileDXFTextSectionEntities.h"
#include "GRPVectorFileDXFEntityObjPoint.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFENTITYObjPoint::GRPVECTORFILEDXFENTITYObjPoint (XCHAR* nameType) : GRPVECTORFILEDXFENTITYObj (nameType)
{
   Clean();   

   type = GRPVECTORFILEDXFENTITYObjType_Point;
}


GRPVECTORFILEDXFENTITYObjPoint::~GRPVECTORFILEDXFENTITYObjPoint ( )
{ 
   Clean();
}


GRPVECTORFILEDXFENTITYDEFPOINT* GRPVECTORFILEDXFENTITYObjPoint::GetPoint ( )
{
   return &point;
}

      
bool GRPVECTORFILEDXFENTITYObjPoint::SetPoint (GRPVECTORFILEDXFENTITYDEFPOINT* point)
{
   if(!point) return false;

   this->point = point;

   return true;
}

   
double GRPVECTORFILEDXFENTITYObjPoint::GetXAxisAngle ( )
{
   return xAxisAngle;
}
      
      
void GRPVECTORFILEDXFENTITYObjPoint::SetXAxisAngle (double xAxisAngle)
{
   this->xAxisAngle = xAxisAngle; 
}


double GRPVECTORFILEDXFENTITYObjPoint::GetThickness ( )
{
   return thickness;
}


void GRPVECTORFILEDXFENTITYObjPoint::SetThickness (double thickness)
{
   this->thickness = thickness;
}


GRPVECTORFILEDXFENTITYDEFPOINT* GRPVECTORFILEDXFENTITYObjPoint::GetDirExtrusion()
{
   return &dirExtrusion;
}


bool GRPVECTORFILEDXFENTITYObjPoint::SetDirExtrusion(GRPVECTORFILEDXFENTITYDEFPOINT* dirExtrusion)
{
   if(!dirExtrusion) return false;

   this->dirExtrusion = dirExtrusion;

   return true;
}


bool GRPVECTORFILEDXFENTITYObjPoint::ApplyData(GRPVECTORFILEDXFENTITY* entity)
{
   GRPVECTORFILEDXFVALUE* value;

   GRPVECTORFILEDXFENTITYObj::ApplyData(entity);   

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


void GRPVECTORFILEDXFENTITYObjPoint::Clean ( )
{
   xAxisAngle = 0.0f;
}

#pragma endregion
