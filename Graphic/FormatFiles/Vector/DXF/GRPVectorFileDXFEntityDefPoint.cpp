#pragma region INCLUDES

#include "GRPVECTORFILEDXFEntityDefPoint.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFEntityDefPoint::GRPVECTORFILEDXFEntityDefPoint ( )
{
   Clean();   
}


GRPVECTORFILEDXFEntityDefPoint::GRPVECTORFILEDXFEntityDefPoint ( double xPoint , double yPoint , double zPoint )
{
   Clean(); 

   this->xPoint = xPoint;
   this->yPoint = yPoint;
   this->zPoint = zPoint;
}

      
GRPVECTORFILEDXFEntityDefPoint::GRPVECTORFILEDXFEntityDefPoint ( GRPVECTORFILEDXFEntityDefPoint* point )
{
   Clean();

   CopyFrom (point);
}


GRPVECTORFILEDXFEntityDefPoint::~GRPVECTORFILEDXFEntityDefPoint ( )
{ 
   Clean();
}


void GRPVECTORFILEDXFEntityDefPoint::operator =  (GRPVECTORFILEDXFEntityDefPoint* point)
{
  CopyFrom(point);
}


void GRPVECTORFILEDXFEntityDefPoint::operator =  (GRPVECTORFILEDXFEntityDefPoint point)
{
  CopyFrom(&point);
}


double GRPVECTORFILEDXFEntityDefPoint::GetX () 
{ 
   return xPoint; 
}
     
     
void GRPVECTORFILEDXFEntityDefPoint::SetX ( double xPoint ) 
{ 
   this->xPoint = xPoint; 
} 


double GRPVECTORFILEDXFEntityDefPoint::GetY () 
{ 
   return yPoint; 
}


void GRPVECTORFILEDXFEntityDefPoint::SetY ( double yPoint ) 
{ 
   this->yPoint = yPoint; 
}
      
      
double GRPVECTORFILEDXFEntityDefPoint::GetZ () 
{ 
   return zPoint ; 
};    

    
void GRPVECTORFILEDXFEntityDefPoint::SetZ ( double zPoint ) 
{ 
   this->zPoint = zPoint; 
} 


bool GRPVECTORFILEDXFEntityDefPoint::CopyTo ( GRPVECTORFILEDXFEntityDefPoint* point )
{
   if(!point) 
   {
      return false;
   }

   point->SetX(xPoint);
   point->SetY(yPoint);
   point->SetZ(zPoint);

   return true;
}
      

bool GRPVECTORFILEDXFEntityDefPoint::CopyFrom ( GRPVECTORFILEDXFEntityDefPoint* point )
{
   if(!point)
   {
      return false;
   }

   xPoint = point->GetX();
   yPoint = point->GetY();
   zPoint = point->GetY();

   return true;
}
   

void GRPVECTORFILEDXFEntityDefPoint::Clean ( )
{
   xPoint = 0.0f;
   yPoint = 0.0f;  
   zPoint = 0.0f;
}

#pragma endregion
