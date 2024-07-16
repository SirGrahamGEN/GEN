#pragma region INCLUDES

#include "GRPVECTORFILEDXFEntityDefStringValue.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFEntityDefStringValue::GRPVECTORFILEDXFEntityDefStringValue ( )
{
   Clean();   
}


GRPVECTORFILEDXFEntityDefStringValue::GRPVECTORFILEDXFEntityDefStringValue ( int value, XCHAR* string )
{
   Clean(); 
}

      
GRPVECTORFILEDXFEntityDefStringValue::GRPVECTORFILEDXFEntityDefStringValue ( GRPVECTORFILEDXFEntityDefStringValue* stringvalue )
{
   Clean();

   CopyFrom (stringvalue);
}


GRPVECTORFILEDXFEntityDefStringValue::~GRPVECTORFILEDXFEntityDefStringValue ( )
{ 
   Clean();
}


void GRPVECTORFILEDXFEntityDefStringValue::operator =  (GRPVECTORFILEDXFEntityDefStringValue* point)
{
  CopyFrom(point);
}


void GRPVECTORFILEDXFEntityDefStringValue::operator =  (GRPVECTORFILEDXFEntityDefStringValue point)
{
  CopyFrom(&point);
}


int GRPVECTORFILEDXFEntityDefStringValue::GetValue () 
{ 
   return value; 
}
     
     
void GRPVECTORFILEDXFEntityDefStringValue::SetValue ( int value ) 
{ 
   this->value = value; 
} 


XSTRING* GRPVECTORFILEDXFEntityDefStringValue::GetString () 
{ 
   return &string; 
}


bool GRPVECTORFILEDXFEntityDefStringValue::CopyTo ( GRPVECTORFILEDXFEntityDefStringValue* stringvalue )
{
   if(!stringvalue) 
   {
      return false;
   }

   stringvalue->SetValue(GetValue());
   stringvalue->GetString()->Set(GetString()->Get());
   
   return true;
}
      

bool GRPVECTORFILEDXFEntityDefStringValue::CopyFrom ( GRPVECTORFILEDXFEntityDefStringValue* stringvalue )
{
   if(!stringvalue)
   {
      return false;
   }

   value  = stringvalue->GetValue();
   string = stringvalue->GetString()->Get();   

   return true;
}
   

void GRPVECTORFILEDXFEntityDefStringValue::Clean ( )
{
   value = 0;
   string.Empty();   
}


GRPVECTORFILEDXFEntityDefStringList::GRPVECTORFILEDXFEntityDefStringList ( )
{
   Clean();   
}


GRPVECTORFILEDXFEntityDefStringList::~GRPVECTORFILEDXFEntityDefStringList ( )
{ 
   Clean();
}


void GRPVECTORFILEDXFEntityDefStringList::Clean ( )
{
   stringsvalue.DeleteContents();
   stringsvalue.DeleteAll();
}


#pragma endregion
