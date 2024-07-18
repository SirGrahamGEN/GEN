
#pragma region INCLUDES

#include "GRPVectorFileDXFTextPart.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFTextPart::GRPVECTORFILEDXFTextPart ( )
{
  Clean();
}


GRPVECTORFILEDXFTextPart::~GRPVECTORFILEDXFTextPart ( )
{
  Clean();
}


bool GRPVECTORFILEDXFTextPart::CopyTo(GRPVECTORFILEDXFTextPart* part)
{
   if(!part) return false;

   part->name    = name; 
   part->iniline = iniline;
   part->endline = endline;

   return true;
}


void GRPVECTORFILEDXFTextPart::Clean ( )
{
   name.Empty();
   iniline = -1;
   endline = -1;
}

#pragma endregion
