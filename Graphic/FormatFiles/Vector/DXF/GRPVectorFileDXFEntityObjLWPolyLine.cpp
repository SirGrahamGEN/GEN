#pragma region INCLUDES

#include "GRPVectorFileDXFTextSectionEntities.h"
#include "GRPVectorFileDXFEntityObjLWPolyLine.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFENTITYOBJLWPolyLine::GRPVECTORFILEDXFENTITYOBJLWPolyLine (XCHAR* nametype) : GRPVECTORFILEDXFENTITYOBJ (nametype)
{
   Clean();   

   type = GRPVECTORFILEDXFENTITYOBJTYPE_LWPOLYLINE;
}


GRPVECTORFILEDXFENTITYOBJLWPolyLine::~GRPVECTORFILEDXFENTITYOBJLWPolyLine()
{ 
   Clean();
}


int GRPVECTORFILEDXFENTITYOBJLWPolyLine::GetNVertex()
{
   return nVertex;
}
      
      
void GRPVECTORFILEDXFENTITYOBJLWPolyLine::SetNVertex(int nVertex)
{
   this->nVertex = nVertex;
}


int GRPVECTORFILEDXFENTITYOBJLWPolyLine::GetPolyLineFlag()
{
   return polyLineFlag;
}
      
      
void GRPVECTORFILEDXFENTITYOBJLWPolyLine::SetPolyLineFlag(int polyLineFlag)
{
   this->polyLineFlag = polyLineFlag;
}


double GRPVECTORFILEDXFENTITYOBJLWPolyLine::GetConstantWidth()
{
   return constantWidth;
}
      
      
void GRPVECTORFILEDXFENTITYOBJLWPolyLine::SetConstantWidth(double constantWidth)
{
   this->constantWidth = constantWidth;
}

double GRPVECTORFILEDXFENTITYOBJLWPolyLine::GetElevation()
{
   return elevation;
}
      
      
void GRPVECTORFILEDXFENTITYOBJLWPolyLine::SetElevation(double elevation)
{
   this->elevation = elevation;
}
      
      
double GRPVECTORFILEDXFENTITYOBJLWPolyLine::GetThickness()
{
   return thickness;
}


void GRPVECTORFILEDXFENTITYOBJLWPolyLine::SetThickness (double thickness)
{
   this->thickness = thickness;
}


GRPVECTORFILEDXFENTITYDEFPOINT* GRPVECTORFILEDXFENTITYOBJLWPolyLine::GetDirExtrusion()
{
   return &dirextrusion;
}


bool GRPVECTORFILEDXFENTITYOBJLWPolyLine::SetDirExtrusion(GRPVECTORFILEDXFENTITYDEFPOINT* dirextrusion)
{
   if(!dirextrusion) return false;

   this->dirextrusion = dirextrusion;

   return true;
}


bool GRPVECTORFILEDXFENTITYOBJLWPolyLine::ApplyData(GRPVECTORFILEDXFENTITY* entity)
{
   GRPVECTORFILEDXFVALUE* value;

   GRPVECTORFILEDXFENTITYOBJ::ApplyData(entity);

   value = GetDataValue( 90, entity);  if(value) nVertex = (*value->GetData());

   value = GetDataValue( 70, entity);  if(value) polyLineFlag = (*value->GetData());
   value = GetDataValue( 43, entity);  if(value) constantWidth = (*value->GetData());
   value = GetDataValue( 38, entity);  if(value) elevation = (*value->GetData());

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


void GRPVECTORFILEDXFENTITYOBJLWPolyLine::Clean()
{
  thickness = 0.0f;    
}

#pragma endregion
