#pragma region INCLUDES

#include "GRPVectorFileDXFEntityDefVertex.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFENTITYDefVertex::GRPVECTORFILEDXFENTITYDefVertex ( )
{
   Clean();   
}
 
 
GRPVECTORFILEDXFENTITYDefVertex::GRPVECTORFILEDXFENTITYDefVertex ( GRPVECTORFILEDXFENTITYDefVertex* Vertex )
{
   Clean();

   CopyFrom (Vertex);
}


GRPVECTORFILEDXFENTITYDefVertex::~GRPVECTORFILEDXFENTITYDefVertex ( )
{ 
   Clean();
}


void GRPVECTORFILEDXFENTITYDefVertex::operator =  (GRPVECTORFILEDXFENTITYDefVertex* Vertex)
{
  CopyFrom(Vertex);
}


void GRPVECTORFILEDXFENTITYDefVertex::operator =  (GRPVECTORFILEDXFENTITYDefVertex Vertex)
{
  CopyFrom(&Vertex);
}



GRPVECTORFILEDXFENTITYDEFPOINT* GRPVECTORFILEDXFENTITYDefVertex::GetPoint()
{
   return &point;
}


bool GRPVECTORFILEDXFENTITYDefVertex::SetPoint(GRPVECTORFILEDXFENTITYDEFPOINT* point)
{
   if(!point) return false;

   this->point = point;

   return true;
}


double GRPVECTORFILEDXFENTITYDefVertex::GetIniWidth ( )
{
   return iniWidth;
}


void GRPVECTORFILEDXFENTITYDefVertex::SetIniWidth (double iniWidth)
{
   this->iniWidth = iniWidth;
}


double GRPVECTORFILEDXFENTITYDefVertex::GetEndWidth ( )
{
   return endWidth;
}


void GRPVECTORFILEDXFENTITYDefVertex::SetEndWidth (double endWidth)
{
   this->endWidth = endWidth;
}


double GRPVECTORFILEDXFENTITYDefVertex::GetBulge ( )
{
   return bulge;
}


void GRPVECTORFILEDXFENTITYDefVertex::SetBulge (double bulge)
{
   this->bulge = bulge;
}


bool GRPVECTORFILEDXFENTITYDefVertex::CopyTo ( GRPVECTORFILEDXFENTITYDefVertex* Vertex )
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
      

bool GRPVECTORFILEDXFENTITYDefVertex::CopyFrom ( GRPVECTORFILEDXFENTITYDefVertex* Vertex )
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
   

void GRPVECTORFILEDXFENTITYDefVertex::Clean ( )
{   
   iniWidth = 0.0f; // Start width.
   endWidth = 0.0f; // End width.
   bulge = 0.0f; // Bulge.
}

#pragma endregion
