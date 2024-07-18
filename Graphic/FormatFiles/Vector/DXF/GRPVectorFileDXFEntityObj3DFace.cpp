#pragma region INCLUDES

#include "GRPVectorFileDXFEntityObj3DFace.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFENTITYObj3DFace::GRPVECTORFILEDXFENTITYObj3DFace (XCHAR* nameType) : GRPVECTORFILEDXFENTITYObj (nameType)
{
   Clean();   

   type = GRPVECTORFILEDXFENTITYObjType_3DFace;
}


GRPVECTORFILEDXFENTITYObj3DFace::~GRPVECTORFILEDXFENTITYObj3DFace ( )
{ 
   Clean();
}

bool GRPVECTORFILEDXFENTITYObj3DFace::ApplyData(GRPVECTORFILEDXFENTITY* entity)
{
   GRPVECTORFILEDXFENTITYObj::ApplyData(entity);
 
   return true;
}


void GRPVECTORFILEDXFENTITYObj3DFace::Clean ( )
{
   
}

#pragma endregion
