#pragma region INCLUDES

#include "GRPVectorFileDXFEntityObjMText.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFENTITYObjMText::GRPVECTORFILEDXFENTITYObjMText (XCHAR* nameType) : GRPVECTORFILEDXFENTITYObj (nameType)
{
   Clean();   

   type = GRPVECTORFILEDXFENTITYObjType_MText;
}


GRPVECTORFILEDXFENTITYObjMText::~GRPVECTORFILEDXFENTITYObjMText ( )
{ 
   Clean();
}


bool GRPVECTORFILEDXFENTITYObjMText::ApplyData(GRPVECTORFILEDXFENTITY* entity)
{
   // INCOMPLETE
   GRPVECTORFILEDXFENTITYObj::ApplyData(entity);

   return true;
}


void GRPVECTORFILEDXFENTITYObjMText::Clean ( )
{
 
}

#pragma endregion
