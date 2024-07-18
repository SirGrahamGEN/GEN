
#pragma region INCLUDES

#include "GRPVectorFileDXFValue.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFVALUE::GRPVECTORFILEDXFVALUE ( )
{
   Clean();   
}


GRPVECTORFILEDXFVALUE::~GRPVECTORFILEDXFVALUE ( )
{
   Clean();
}


int GRPVECTORFILEDXFVALUE::GetType()
{
   return type; 
}


void GRPVECTORFILEDXFVALUE::SetType(int type)
{
   this->type = type;
}


XSTRING* GRPVECTORFILEDXFVALUE::GetName ( )
{
   return &name;
}


XVARIANT* GRPVECTORFILEDXFVALUE::GetData ( )
{
   return &data;
}


XSTRING* GRPVECTORFILEDXFVALUE::GetRemark ( )
{
   return &remark;
}


void GRPVECTORFILEDXFVALUE::Clean ( )
{
  type = -100;
  name.Empty();
  remark.Empty();
}

#pragma endregion
