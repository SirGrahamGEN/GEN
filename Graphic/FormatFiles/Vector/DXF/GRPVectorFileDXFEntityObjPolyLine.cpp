#pragma region INCLUDES

#include "GRPVECTORFILEDXFTextSectionEntities.h"
#include "GRPVECTORFILEDXFEntityObjPolyLine.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFEntityObjPolyLine::GRPVECTORFILEDXFEntityObjPolyLine (XCHAR* nameType) : GRPVECTORFILEDXFEntityObj (nameType)
{
   Clean();   

   type = GRPVECTORFILEDXFEntityObjType_PolyLine;
}


GRPVECTORFILEDXFEntityObjPolyLine::~GRPVECTORFILEDXFEntityObjPolyLine ( )
{ 
   Clean();
}

 
double GRPVECTORFILEDXFEntityObjPolyLine::GetThickness ( )
{
   return thickness;
}


void GRPVECTORFILEDXFEntityObjPolyLine::SetThickness (double thickness)
{
   this->thickness = thickness;
}


GRPVECTORFILEDXFEntityDefPoint* GRPVECTORFILEDXFEntityObjPolyLine::GetDirExtrusion()
{
   return &dirExtrusion;
}


bool GRPVECTORFILEDXFEntityObjPolyLine::SetDirExtrusion(GRPVECTORFILEDXFEntityDefPoint* dirExtrusion)
{
   if(!dirExtrusion) return false;

   this->dirExtrusion = dirExtrusion;

   return true;
}


bool GRPVECTORFILEDXFEntityObjPolyLine::ApplyData(GRPVECTORFILEDXFEntity* entity)
{
   GRPVECTORFILEDXFValue* value;

   GRPVECTORFILEDXFEntityObj::ApplyData(entity);

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


void GRPVECTORFILEDXFEntityObjPolyLine::Clean ( )
{
   
}

#pragma endregion
