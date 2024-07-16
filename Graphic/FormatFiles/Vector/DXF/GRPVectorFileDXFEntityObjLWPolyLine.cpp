#pragma region INCLUDES

#include "GRPVECTORFILEDXFTextSectionEntities.h"
#include "GRPVECTORFILEDXFEntityObjLWPolyLine.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFEntityObjLWPolyLine::GRPVECTORFILEDXFEntityObjLWPolyLine (XCHAR* nameType) : GRPVECTORFILEDXFEntityObj (nameType)
{
   Clean();   

   type = GRPVECTORFILEDXFEntityObjType_LWPolyLine;
}


GRPVECTORFILEDXFEntityObjLWPolyLine::~GRPVECTORFILEDXFEntityObjLWPolyLine ( )
{ 
   Clean();
}


int GRPVECTORFILEDXFEntityObjLWPolyLine::GetNVertex()
{
   return nVertex;
}
      
      
void GRPVECTORFILEDXFEntityObjLWPolyLine::SetNVertex(int nVertex)
{
   this->nVertex = nVertex;
}


int GRPVECTORFILEDXFEntityObjLWPolyLine::GetPolyLineFlag()
{
   return polyLineFlag;
}
      
      
void GRPVECTORFILEDXFEntityObjLWPolyLine::SetPolyLineFlag(int polyLineFlag)
{
   this->polyLineFlag = polyLineFlag;
}


double GRPVECTORFILEDXFEntityObjLWPolyLine::GetConstantWidth ( )
{
   return constantWidth;
}
      
      
void GRPVECTORFILEDXFEntityObjLWPolyLine::SetConstantWidth(double constantWidth)
{
   this->constantWidth = constantWidth;
}

double GRPVECTORFILEDXFEntityObjLWPolyLine::GetElevation ( )
{
   return elevation;
}
      
      
void GRPVECTORFILEDXFEntityObjLWPolyLine::SetElevation(double elevation)
{
   this->elevation = elevation;
}
      
      
double GRPVECTORFILEDXFEntityObjLWPolyLine::GetThickness ( )
{
   return thickness;
}


void GRPVECTORFILEDXFEntityObjLWPolyLine::SetThickness (double thickness)
{
   this->thickness = thickness;
}


GRPVECTORFILEDXFEntityDefPoint* GRPVECTORFILEDXFEntityObjLWPolyLine::GetDirExtrusion()
{
   return &dirExtrusion;
}


bool GRPVECTORFILEDXFEntityObjLWPolyLine::SetDirExtrusion(GRPVECTORFILEDXFEntityDefPoint* dirExtrusion)
{
   if(!dirExtrusion) return false;

   this->dirExtrusion = dirExtrusion;

   return true;
}


bool GRPVECTORFILEDXFEntityObjLWPolyLine::ApplyData(GRPVECTORFILEDXFEntity* entity)
{
   GRPVECTORFILEDXFValue* value;

   GRPVECTORFILEDXFEntityObj::ApplyData(entity);

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


void GRPVECTORFILEDXFEntityObjLWPolyLine::Clean ( )
{
  thickness = 0.0f;    
}

#pragma endregion
