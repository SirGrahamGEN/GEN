#pragma region INCLUDES

#include "GRPVECTORFILEDXFEntityObj3DFace.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFEntityObj3DFace::GRPVECTORFILEDXFEntityObj3DFace (XCHAR* nameType) : GRPVECTORFILEDXFEntityObj (nameType)
{
   Clean();   

   type = GRPVECTORFILEDXFEntityObjType_3DFace;
}


GRPVECTORFILEDXFEntityObj3DFace::~GRPVECTORFILEDXFEntityObj3DFace ( )
{ 
   Clean();
}

bool GRPVECTORFILEDXFEntityObj3DFace::ApplyData(GRPVECTORFILEDXFEntity* entity)
{
   GRPVECTORFILEDXFEntityObj::ApplyData(entity);
 
   return true;
}


void GRPVECTORFILEDXFEntityObj3DFace::Clean ( )
{
   
}

#pragma endregion
