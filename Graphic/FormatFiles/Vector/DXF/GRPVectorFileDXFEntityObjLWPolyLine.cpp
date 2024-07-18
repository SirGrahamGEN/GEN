#pragma region INCLUDES

#include "GRPVectorFileDXFTextSectionEntities.h"
#include "GRPVectorFileDXFEntityObjLWPolyLine.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFENTITYObjLWPolyLine::GRPVECTORFILEDXFENTITYObjLWPolyLine (XCHAR* nameType) : GRPVECTORFILEDXFENTITYObj (nameType)
{
   Clean();   

   type = GRPVECTORFILEDXFENTITYObjType_LWPolyLine;
}


GRPVECTORFILEDXFENTITYObjLWPolyLine::~GRPVECTORFILEDXFENTITYObjLWPolyLine ( )
{ 
   Clean();
}


int GRPVECTORFILEDXFENTITYObjLWPolyLine::GetNVertex()
{
   return nVertex;
}
      
      
void GRPVECTORFILEDXFENTITYObjLWPolyLine::SetNVertex(int nVertex)
{
   this->nVertex = nVertex;
}


int GRPVECTORFILEDXFENTITYObjLWPolyLine::GetPolyLineFlag()
{
   return polyLineFlag;
}
      
      
void GRPVECTORFILEDXFENTITYObjLWPolyLine::SetPolyLineFlag(int polyLineFlag)
{
   this->polyLineFlag = polyLineFlag;
}


double GRPVECTORFILEDXFENTITYObjLWPolyLine::GetConstantWidth ( )
{
   return constantWidth;
}
      
      
void GRPVECTORFILEDXFENTITYObjLWPolyLine::SetConstantWidth(double constantWidth)
{
   this->constantWidth = constantWidth;
}

double GRPVECTORFILEDXFENTITYObjLWPolyLine::GetElevation ( )
{
   return elevation;
}
      
      
void GRPVECTORFILEDXFENTITYObjLWPolyLine::SetElevation(double elevation)
{
   this->elevation = elevation;
}
      
      
double GRPVECTORFILEDXFENTITYObjLWPolyLine::GetThickness ( )
{
   return thickness;
}


void GRPVECTORFILEDXFENTITYObjLWPolyLine::SetThickness (double thickness)
{
   this->thickness = thickness;
}


GRPVECTORFILEDXFENTITYDEFPOINT* GRPVECTORFILEDXFENTITYObjLWPolyLine::GetDirExtrusion()
{
   return &dirExtrusion;
}


bool GRPVECTORFILEDXFENTITYObjLWPolyLine::SetDirExtrusion(GRPVECTORFILEDXFENTITYDEFPOINT* dirExtrusion)
{
   if(!dirExtrusion) return false;

   this->dirExtrusion = dirExtrusion;

   return true;
}


bool GRPVECTORFILEDXFENTITYObjLWPolyLine::ApplyData(GRPVECTORFILEDXFENTITY* entity)
{
   GRPVECTORFILEDXFVALUE* value;

   GRPVECTORFILEDXFENTITYObj::ApplyData(entity);

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


void GRPVECTORFILEDXFENTITYObjLWPolyLine::Clean ( )
{
  thickness = 0.0f;    
}

#pragma endregion
