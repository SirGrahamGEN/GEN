#pragma region INCLUDES

#include "GRPVectorFileDXFEntityObjText.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFENTITYObjText::GRPVECTORFILEDXFENTITYObjText (XCHAR* nameType) : GRPVECTORFILEDXFENTITYObj (nameType)
{
   Clean();   

   type = GRPVECTORFILEDXFENTITYObjType_Text;
}


GRPVECTORFILEDXFENTITYObjText::~GRPVECTORFILEDXFENTITYObjText ( )
{ 
   Clean();
}


bool GRPVECTORFILEDXFENTITYObjText::ApplyData(GRPVECTORFILEDXFENTITY* entity)
{
   // INCOMPLETE

   GRPVECTORFILEDXFENTITYObj::ApplyData(entity);
     
   return true;
}


void GRPVECTORFILEDXFENTITYObjText::Clean ( )
{
  
}

#pragma endregion
