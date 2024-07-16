#pragma region INCLUDES

#include "XMap.h"
#include "XVariant.h"

#include "GRPVectorFileDXF.h"

#include "GRPVECTORFILEDXFEntity.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFEntity::GRPVECTORFILEDXFEntity ( )
{
   Clean();   
}


GRPVECTORFILEDXFEntity::~GRPVECTORFILEDXFEntity ( )
{
   DeleteAllValues();

   Clean();
}


XSTRING* GRPVECTORFILEDXFEntity::GetName ()
{
   return &name;
}


bool GRPVECTORFILEDXFEntity::AddValue (GRPVECTORFILEDXFValue* value)
{    
   values.Add(value);

   return true;
}


XVECTOR<GRPVECTORFILEDXFValue*>* GRPVECTORFILEDXFEntity::GetValues ()
{
   return &values;
}


GRPVECTORFILEDXFValue* GRPVECTORFILEDXFEntity::GetValue (int index)
{
   if(values.IsEmpty()) return NULL;

   return values.Get(index);   
}

bool GRPVECTORFILEDXFEntity::DeleteValue(int index)
{
   if(values.IsEmpty()) return false;

   return values.Delete(GetValue(index));

}


bool GRPVECTORFILEDXFEntity::DeleteAllValues()
{
   if(values.IsEmpty()) return false;

   values.DeleteContents();
   values.DeleteAll(); 
   
   xDataCtrlList.DeleteContents();
   xDataCtrlList.DeleteAll();

   return false;
}


XVECTOR<GRPVECTORFILEDXFXDataCtrl*>* GRPVECTORFILEDXFEntity::GetXDataCtrlList()
{
   return &xDataCtrlList;
}


void GRPVECTORFILEDXFEntity::Clean ( )
{
  
}

#pragma endregion
