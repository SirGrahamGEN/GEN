#pragma region INCLUDES

#include "GRPVECTORFILEDXFEntityDefVertex.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFEntityDefVertex::GRPVECTORFILEDXFEntityDefVertex ( )
{
   Clean();   
}
 
 
GRPVECTORFILEDXFEntityDefVertex::GRPVECTORFILEDXFEntityDefVertex ( GRPVECTORFILEDXFEntityDefVertex* Vertex )
{
   Clean();

   CopyFrom (Vertex);
}


GRPVECTORFILEDXFEntityDefVertex::~GRPVECTORFILEDXFEntityDefVertex ( )
{ 
   Clean();
}


void GRPVECTORFILEDXFEntityDefVertex::operator =  (GRPVECTORFILEDXFEntityDefVertex* Vertex)
{
  CopyFrom(Vertex);
}


void GRPVECTORFILEDXFEntityDefVertex::operator =  (GRPVECTORFILEDXFEntityDefVertex Vertex)
{
  CopyFrom(&Vertex);
}



GRPVECTORFILEDXFEntityDefPoint* GRPVECTORFILEDXFEntityDefVertex::GetPoint()
{
   return &point;
}


bool GRPVECTORFILEDXFEntityDefVertex::SetPoint(GRPVECTORFILEDXFEntityDefPoint* point)
{
   if(!point) return false;

   this->point = point;

   return true;
}


double GRPVECTORFILEDXFEntityDefVertex::GetIniWidth ( )
{
   return iniWidth;
}


void GRPVECTORFILEDXFEntityDefVertex::SetIniWidth (double iniWidth)
{
   this->iniWidth = iniWidth;
}


double GRPVECTORFILEDXFEntityDefVertex::GetEndWidth ( )
{
   return endWidth;
}


void GRPVECTORFILEDXFEntityDefVertex::SetEndWidth (double endWidth)
{
   this->endWidth = endWidth;
}


double GRPVECTORFILEDXFEntityDefVertex::GetBulge ( )
{
   return bulge;
}


void GRPVECTORFILEDXFEntityDefVertex::SetBulge (double bulge)
{
   this->bulge = bulge;
}


bool GRPVECTORFILEDXFEntityDefVertex::CopyTo ( GRPVECTORFILEDXFEntityDefVertex* Vertex )
{
   if(!Vertex) 
   {
      return false;
   }

   Vertex->SetPoint(&point);
   Vertex->SetIniWidth(iniWidth);
   Vertex->SetEndWidth(endWidth);
   Vertex->SetBulge(bulge);
   
   return true;
}
      

bool GRPVECTORFILEDXFEntityDefVertex::CopyFrom ( GRPVECTORFILEDXFEntityDefVertex* Vertex )
{
   if(!Vertex)
   {
      return false;
   }

   point = Vertex->GetPoint();
   iniWidth = Vertex->GetIniWidth();
   endWidth = Vertex->GetEndWidth();
   bulge = Vertex->GetBulge();
  
   return true;
}
   

void GRPVECTORFILEDXFEntityDefVertex::Clean ( )
{   
   iniWidth = 0.0f; // Start width.
   endWidth = 0.0f; // End width.
   bulge = 0.0f; // Bulge.
}

#pragma endregion
