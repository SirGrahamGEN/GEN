#pragma region INCLUDES

#include "GRPVectorFileDXFEntityDefStringValue.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFENTITYDefStringValue::GRPVECTORFILEDXFENTITYDefStringValue ( )
{
   Clean();   
}


GRPVECTORFILEDXFENTITYDefStringValue::GRPVECTORFILEDXFENTITYDefStringValue ( int value, XCHAR* string )
{
   Clean(); 
}

      
GRPVECTORFILEDXFENTITYDefStringValue::GRPVECTORFILEDXFENTITYDefStringValue ( GRPVECTORFILEDXFENTITYDefStringValue* stringvalue )
{
   Clean();

   CopyFrom (stringvalue);
}


GRPVECTORFILEDXFENTITYDefStringValue::~GRPVECTORFILEDXFENTITYDefStringValue ( )
{ 
   Clean();
}


void GRPVECTORFILEDXFENTITYDefStringValue::operator =  (GRPVECTORFILEDXFENTITYDefStringValue* point)
{
  CopyFrom(point);
}


void GRPVECTORFILEDXFENTITYDefStringValue::operator =  (GRPVECTORFILEDXFENTITYDefStringValue point)
{
  CopyFrom(&point);
}


int GRPVECTORFILEDXFENTITYDefStringValue::GetValue () 
{ 
   return value; 
}
     
     
void GRPVECTORFILEDXFENTITYDefStringValue::SetValue ( int value ) 
{ 
   this->value = value; 
} 


XSTRING* GRPVECTORFILEDXFENTITYDefStringValue::GetString () 
{ 
   return &string; 
}


bool GRPVECTORFILEDXFENTITYDefStringValue::CopyTo ( GRPVECTORFILEDXFENTITYDefStringValue* stringvalue )
{
   if(!stringvalue) 
   {
      return false;
   }

   stringvalue->SetValue(GetValue());
   stringvalue->GetString()->Set(GetString()->Get());
   
   return true;
}
      

bool GRPVECTORFILEDXFENTITYDefStringValue::CopyFrom ( GRPVECTORFILEDXFENTITYDefStringValue* stringvalue )
{
   if(!stringvalue)
   {
      return false;
   }

   value  = stringvalue->GetValue();
   string = stringvalue->GetString()->Get();   

   return true;
}
   

void GRPVECTORFILEDXFENTITYDefStringValue::Clean ( )
{
   value = 0;
   string.Empty();   
}


GRPVECTORFILEDXFENTITYDefStringList::GRPVECTORFILEDXFENTITYDefStringList ( )
{
   Clean();   
}


GRPVECTORFILEDXFENTITYDefStringList::~GRPVECTORFILEDXFENTITYDefStringList ( )
{ 
   Clean();
}


void GRPVECTORFILEDXFENTITYDefStringList::Clean ( )
{
   stringsvalue.DeleteContents();
   stringsvalue.DeleteAll();
}


#pragma endregion
