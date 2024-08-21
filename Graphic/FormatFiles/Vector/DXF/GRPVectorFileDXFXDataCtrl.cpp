
#pragma region INCLUDES

#include "GRPVectorFileDXFXDataCtrl.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFXDATACTRL::GRPVECTORFILEDXFXDATACTRL()
{
   Clean();   
}


GRPVECTORFILEDXFXDATACTRL::~GRPVECTORFILEDXFXDATACTRL()
{
   Clean();
}

XSTRING* GRPVECTORFILEDXFXDATACTRL::GetName()
{
   return &name;
}
      
      
XVECTOR<GRPVECTORFILEDXFVALUE*>* GRPVECTORFILEDXFXDATACTRL::GetValues()
{
   return &values;
}


void GRPVECTORFILEDXFXDATACTRL::Clean()
{
  
}

#pragma endregion
