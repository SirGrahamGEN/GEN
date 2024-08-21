#pragma region INCLUDES

#include "GRPVectorFileDXFEntityObjMText.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFENTITYOBJMText::GRPVECTORFILEDXFENTITYOBJMText (XCHAR* nametype) : GRPVECTORFILEDXFENTITYOBJ (nametype)
{
   Clean();   

   type = GRPVECTORFILEDXFENTITYOBJTYPE_MTEXT;
}


GRPVECTORFILEDXFENTITYOBJMText::~GRPVECTORFILEDXFENTITYOBJMText()
{ 
   Clean();
}


bool GRPVECTORFILEDXFENTITYOBJMText::ApplyData(GRPVECTORFILEDXFENTITY* entity)
{
   // INCOMPLETE
   GRPVECTORFILEDXFENTITYOBJ::ApplyData(entity);

   return true;
}


void GRPVECTORFILEDXFENTITYOBJMText::Clean()
{
 
}

#pragma endregion
