#pragma region INCLUDES

#include "GRPVECTORFILEDXFEntityObjText.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFEntityObjText::GRPVECTORFILEDXFEntityObjText (XCHAR* nameType) : GRPVECTORFILEDXFEntityObj (nameType)
{
   Clean();   

   type = GRPVECTORFILEDXFEntityObjType_Text;
}


GRPVECTORFILEDXFEntityObjText::~GRPVECTORFILEDXFEntityObjText ( )
{ 
   Clean();
}


bool GRPVECTORFILEDXFEntityObjText::ApplyData(GRPVECTORFILEDXFEntity* entity)
{
   // INCOMPLETE

   GRPVECTORFILEDXFEntityObj::ApplyData(entity);
     
   return true;
}


void GRPVECTORFILEDXFEntityObjText::Clean ( )
{
  
}

#pragma endregion
