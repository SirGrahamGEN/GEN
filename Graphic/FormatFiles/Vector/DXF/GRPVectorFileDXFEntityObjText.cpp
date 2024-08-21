#pragma region INCLUDES

#include "GRPVectorFileDXFEntityObjText.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFENTITYOBJText::GRPVECTORFILEDXFENTITYOBJText (XCHAR* nametype) : GRPVECTORFILEDXFENTITYOBJ (nametype)
{
   Clean();   

   type = GRPVECTORFILEDXFENTITYOBJTYPE_TEXT;
}


GRPVECTORFILEDXFENTITYOBJText::~GRPVECTORFILEDXFENTITYOBJText()
{ 
   Clean();
}


bool GRPVECTORFILEDXFENTITYOBJText::ApplyData(GRPVECTORFILEDXFENTITY* entity)
{
   // INCOMPLETE

   GRPVECTORFILEDXFENTITYOBJ::ApplyData(entity);
     
   return true;
}


void GRPVECTORFILEDXFENTITYOBJText::Clean()
{
  
}

#pragma endregion
