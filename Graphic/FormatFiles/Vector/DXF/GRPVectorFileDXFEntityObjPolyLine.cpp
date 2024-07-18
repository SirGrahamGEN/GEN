#pragma region INCLUDES

#include "GRPVectorFileDXFTextSectionEntities.h"
#include "GRPVectorFileDXFEntityObjPolyLine.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFENTITYObjPolyLine::GRPVECTORFILEDXFENTITYObjPolyLine (XCHAR* nameType) : GRPVECTORFILEDXFENTITYObj (nameType)
{
   Clean();   

   type = GRPVECTORFILEDXFENTITYObjType_PolyLine;
}


GRPVECTORFILEDXFENTITYObjPolyLine::~GRPVECTORFILEDXFENTITYObjPolyLine ( )
{ 
   Clean();
}

 
double GRPVECTORFILEDXFENTITYObjPolyLine::GetThickness ( )
{
   return thickness;
}


void GRPVECTORFILEDXFENTITYObjPolyLine::SetThickness (double thickness)
{
   this->thickness = thickness;
}


GRPVECTORFILEDXFENTITYDEFPOINT* GRPVECTORFILEDXFENTITYObjPolyLine::GetDirExtrusion()
{
   return &dirExtrusion;
}


bool GRPVECTORFILEDXFENTITYObjPolyLine::SetDirExtrusion(GRPVECTORFILEDXFENTITYDEFPOINT* dirExtrusion)
{
   if(!dirExtrusion) return false;

   this->dirExtrusion = dirExtrusion;

   return true;
}


bool GRPVECTORFILEDXFENTITYObjPolyLine::ApplyData(GRPVECTORFILEDXFENTITY* entity)
{
   GRPVECTORFILEDXFVALUE* value;

   GRPVECTORFILEDXFENTITYObj::ApplyData(entity);

   // INCOMPLETE

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


void GRPVECTORFILEDXFENTITYObjPolyLine::Clean ( )
{
   
}

#pragma endregion
