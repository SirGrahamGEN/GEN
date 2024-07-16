#pragma region INCLUDES

#include "GRPVECTORFILEDXFEntityObjMText.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFEntityObjMText::GRPVECTORFILEDXFEntityObjMText (XCHAR* nameType) : GRPVECTORFILEDXFEntityObj (nameType)
{
   Clean();   

   type = GRPVECTORFILEDXFEntityObjType_MText;
}


GRPVECTORFILEDXFEntityObjMText::~GRPVECTORFILEDXFEntityObjMText ( )
{ 
   Clean();
}


bool GRPVECTORFILEDXFEntityObjMText::ApplyData(GRPVECTORFILEDXFEntity* entity)
{
   // INCOMPLETE
   GRPVECTORFILEDXFEntityObj::ApplyData(entity);

   return true;
}


void GRPVECTORFILEDXFEntityObjMText::Clean ( )
{
 
}

#pragma endregion
