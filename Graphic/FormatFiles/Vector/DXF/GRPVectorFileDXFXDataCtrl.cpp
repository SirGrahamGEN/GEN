
#pragma region INCLUDES

#include "GRPVECTORFILEDXFXDataCtrl.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFXDataCtrl::GRPVECTORFILEDXFXDataCtrl ( )
{
   Clean();   
}


GRPVECTORFILEDXFXDataCtrl::~GRPVECTORFILEDXFXDataCtrl ( )
{
   Clean();
}

XSTRING* GRPVECTORFILEDXFXDataCtrl::GetName ( )
{
   return &name;
}
      
      
XVECTOR<GRPVECTORFILEDXFValue*>* GRPVECTORFILEDXFXDataCtrl::GetValues ( )
{
   return &values;
}


void GRPVECTORFILEDXFXDataCtrl::Clean ( )
{
  
}

#pragma endregion
