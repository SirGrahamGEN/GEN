
#pragma region INCLUDES

#include "GRPVECTORFILEDXFValue.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFValue::GRPVECTORFILEDXFValue ( )
{
   Clean();   
}


GRPVECTORFILEDXFValue::~GRPVECTORFILEDXFValue ( )
{
   Clean();
}


int GRPVECTORFILEDXFValue::GetType()
{
   return type; 
}


void GRPVECTORFILEDXFValue::SetType(int type)
{
   this->type = type;
}


XSTRING* GRPVECTORFILEDXFValue::GetName ( )
{
   return &name;
}


XVARIANT* GRPVECTORFILEDXFValue::GetData ( )
{
   return &data;
}


XSTRING* GRPVECTORFILEDXFValue::GetRemark ( )
{
   return &remark;
}


void GRPVECTORFILEDXFValue::Clean ( )
{
  type = -100;
  name.Empty();
  remark.Empty();
}

#pragma endregion
