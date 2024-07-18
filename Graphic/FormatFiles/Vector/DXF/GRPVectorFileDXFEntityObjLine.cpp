#pragma region INCLUDES

#include "GRPVectorFileDXFTextSectionEntities.h"
#include "GRPVectorFileDXFEntityObjLine.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFENTITYObjLine::GRPVECTORFILEDXFENTITYObjLine (XCHAR* nameType) : GRPVECTORFILEDXFENTITYObj (nameType)
{
   Clean();   

   type = GRPVECTORFILEDXFENTITYObjType_Line;
}


GRPVECTORFILEDXFENTITYObjLine::~GRPVECTORFILEDXFENTITYObjLine ( )
{ 
   Clean();
}

GRPVECTORFILEDXFENTITYDEFPOINT* GRPVECTORFILEDXFENTITYObjLine::GetIni()
{
   return &ini;
}


bool GRPVECTORFILEDXFENTITYObjLine::SetIni(GRPVECTORFILEDXFENTITYDEFPOINT* point)
{
   if(!point) return false;

   this->ini = point;

   return true;
}


GRPVECTORFILEDXFENTITYDEFPOINT* GRPVECTORFILEDXFENTITYObjLine::GetEnd()
{
   return &end;
}


bool GRPVECTORFILEDXFENTITYObjLine::SetEnd(GRPVECTORFILEDXFENTITYDEFPOINT* point)
{
   if(!point) return false;

   this->end = point;

   return true;
}


double GRPVECTORFILEDXFENTITYObjLine::GetThickness ( )
{
   return thickness;
}


void GRPVECTORFILEDXFENTITYObjLine::SetThickness (double thickness)
{
   this->thickness = thickness;
}


GRPVECTORFILEDXFENTITYDEFPOINT* GRPVECTORFILEDXFENTITYObjLine::GetDirExtrusion()
{
   return &dirExtrusion;
}


bool GRPVECTORFILEDXFENTITYObjLine::SetDirExtrusion(GRPVECTORFILEDXFENTITYDEFPOINT* dirExtrusion)
{
   if(!dirExtrusion) return false;

   this->dirExtrusion = dirExtrusion;

   return true;
}


bool GRPVECTORFILEDXFENTITYObjLine::ApplyData(GRPVECTORFILEDXFENTITY* entity)
{
   GRPVECTORFILEDXFVALUE* value;

   GRPVECTORFILEDXFENTITYObj::ApplyData(entity);

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


void GRPVECTORFILEDXFENTITYObjLine::Clean ( )
{
  thickness = 0.0f;    
}

#pragma endregion
