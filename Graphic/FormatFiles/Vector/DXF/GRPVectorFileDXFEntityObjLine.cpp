#pragma region INCLUDES

#include "GRPVECTORFILEDXFTextSectionEntities.h"
#include "GRPVECTORFILEDXFEntityObjLine.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFEntityObjLine::GRPVECTORFILEDXFEntityObjLine (XCHAR* nameType) : GRPVECTORFILEDXFEntityObj (nameType)
{
   Clean();   

   type = GRPVECTORFILEDXFEntityObjType_Line;
}


GRPVECTORFILEDXFEntityObjLine::~GRPVECTORFILEDXFEntityObjLine ( )
{ 
   Clean();
}

GRPVECTORFILEDXFEntityDefPoint* GRPVECTORFILEDXFEntityObjLine::GetIni()
{
   return &ini;
}


bool GRPVECTORFILEDXFEntityObjLine::SetIni(GRPVECTORFILEDXFEntityDefPoint* point)
{
   if(!point) return false;

   this->ini = point;

   return true;
}


GRPVECTORFILEDXFEntityDefPoint* GRPVECTORFILEDXFEntityObjLine::GetEnd()
{
   return &end;
}


bool GRPVECTORFILEDXFEntityObjLine::SetEnd(GRPVECTORFILEDXFEntityDefPoint* point)
{
   if(!point) return false;

   this->end = point;

   return true;
}


double GRPVECTORFILEDXFEntityObjLine::GetThickness ( )
{
   return thickness;
}


void GRPVECTORFILEDXFEntityObjLine::SetThickness (double thickness)
{
   this->thickness = thickness;
}


GRPVECTORFILEDXFEntityDefPoint* GRPVECTORFILEDXFEntityObjLine::GetDirExtrusion()
{
   return &dirExtrusion;
}


bool GRPVECTORFILEDXFEntityObjLine::SetDirExtrusion(GRPVECTORFILEDXFEntityDefPoint* dirExtrusion)
{
   if(!dirExtrusion) return false;

   this->dirExtrusion = dirExtrusion;

   return true;
}


bool GRPVECTORFILEDXFEntityObjLine::ApplyData(GRPVECTORFILEDXFEntity* entity)
{
   GRPVECTORFILEDXFValue* value;

   GRPVECTORFILEDXFEntityObj::ApplyData(entity);

   value = GetDataValue(VFDXF_INI_POINT_X, entity);  
   if(value) 
   {
      ini.SetX((*value->GetData()));      
   }

   value = GetDataValue(VFDXF_INI_POINT_Y, entity);  
   if(value) 
   {
      ini.SetY((*value->GetData()));      
   }

   value = GetDataValue(VFDXF_INI_POINT_Z, entity);  
   if(value) 
   {
      ini.SetZ((*value->GetData()));      
   }

   value = GetDataValue(VFDXF_END_POINT_X, entity);  
   if(value) 
   {
      end.SetX((*value->GetData()));      
   }

   value = GetDataValue(VFDXF_END_POINT_Y, entity);  
   if(value) 
   {
      end.SetY((*value->GetData()));      
   }

   value = GetDataValue(VFDXF_INI_POINT_Z, entity);  
   if(value) 
   {
      end.SetZ((*value->GetData()));      
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


void GRPVECTORFILEDXFEntityObjLine::Clean ( )
{
  thickness = 0.0f;    
}

#pragma endregion
