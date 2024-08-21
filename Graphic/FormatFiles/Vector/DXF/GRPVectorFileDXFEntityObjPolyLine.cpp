#pragma region INCLUDES

#include "GRPVectorFileDXFTextSectionEntities.h"
#include "GRPVectorFileDXFEntityObjPolyLine.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFENTITYOBJPolyLine::GRPVECTORFILEDXFENTITYOBJPolyLine (XCHAR* nametype) : GRPVECTORFILEDXFENTITYOBJ (nametype)
{
   Clean();   

   type = GRPVECTORFILEDXFENTITYOBJTYPE_POLYLINE;
}


GRPVECTORFILEDXFENTITYOBJPolyLine::~GRPVECTORFILEDXFENTITYOBJPolyLine()
{ 
   Clean();
}

 
double GRPVECTORFILEDXFENTITYOBJPolyLine::GetThickness()
{
   return thickness;
}


void GRPVECTORFILEDXFENTITYOBJPolyLine::SetThickness (double thickness)
{
   this->thickness = thickness;
}


GRPVECTORFILEDXFENTITYDEFPOINT* GRPVECTORFILEDXFENTITYOBJPolyLine::GetDirExtrusion()
{
   return &dirextrusion;
}


bool GRPVECTORFILEDXFENTITYOBJPolyLine::SetDirExtrusion(GRPVECTORFILEDXFENTITYDEFPOINT* dirextrusion)
{
   if(!dirextrusion) return false;

   this->dirextrusion = dirextrusion;

   return true;
}


bool GRPVECTORFILEDXFENTITYOBJPolyLine::ApplyData(GRPVECTORFILEDXFENTITY* entity)
{
   GRPVECTORFILEDXFVALUE* value;

   GRPVECTORFILEDXFENTITYOBJ::ApplyData(entity);

   // INCOMPLETE

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


void GRPVECTORFILEDXFENTITYOBJPolyLine::Clean()
{
   
}

#pragma endregion
