#pragma region INCLUDES

#include "GRPVectorFileDXFTextSectionEntities.h"
#include "GRPVectorFileDXFEntityObjPoint.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFENTITYOBJPoint::GRPVECTORFILEDXFENTITYOBJPoint (XCHAR* nametype) : GRPVECTORFILEDXFENTITYOBJ (nametype)
{
   Clean();   

   type = GRPVECTORFILEDXFENTITYOBJTYPE_POINT;
}


GRPVECTORFILEDXFENTITYOBJPoint::~GRPVECTORFILEDXFENTITYOBJPoint()
{ 
   Clean();
}


GRPVECTORFILEDXFENTITYDEFPOINT* GRPVECTORFILEDXFENTITYOBJPoint::GetPoint()
{
   return &point;
}

      
bool GRPVECTORFILEDXFENTITYOBJPoint::SetPoint (GRPVECTORFILEDXFENTITYDEFPOINT* point)
{
   if(!point) return false;

   this->point = point;

   return true;
}

   
double GRPVECTORFILEDXFENTITYOBJPoint::GetXAxisAngle()
{
   return xAxisAngle;
}
      
      
void GRPVECTORFILEDXFENTITYOBJPoint::SetXAxisAngle (double xAxisAngle)
{
   this->xAxisAngle = xAxisAngle; 
}


double GRPVECTORFILEDXFENTITYOBJPoint::GetThickness()
{
   return thickness;
}


void GRPVECTORFILEDXFENTITYOBJPoint::SetThickness (double thickness)
{
   this->thickness = thickness;
}


GRPVECTORFILEDXFENTITYDEFPOINT* GRPVECTORFILEDXFENTITYOBJPoint::GetDirExtrusion()
{
   return &dirextrusion;
}


bool GRPVECTORFILEDXFENTITYOBJPoint::SetDirExtrusion(GRPVECTORFILEDXFENTITYDEFPOINT* dirextrusion)
{
   if(!dirextrusion) return false;

   this->dirextrusion = dirextrusion;

   return true;
}


bool GRPVECTORFILEDXFENTITYOBJPoint::ApplyData(GRPVECTORFILEDXFENTITY* entity)
{
   GRPVECTORFILEDXFVALUE* value;

   GRPVECTORFILEDXFENTITYOBJ::ApplyData(entity);   

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


void GRPVECTORFILEDXFENTITYOBJPoint::Clean()
{
   xAxisAngle = 0.0f;
}

#pragma endregion
