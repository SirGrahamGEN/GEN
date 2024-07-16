#pragma region INCLUDES

#include "XMap.h"
#include "XVariant.h"

#include "GRPVectorFileDXF.h"

#include "GRPVECTORFILEDXFTextBlock.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFTextBlock::GRPVECTORFILEDXFTextBlock ( )
{
   Clean();   
}


GRPVECTORFILEDXFTextBlock::~GRPVECTORFILEDXFTextBlock ( )
{
   DeleteAllValues();

   if(entitiesSection)
   {
      delete entitiesSection;
   }

   Clean();
}


XSTRING* GRPVECTORFILEDXFTextBlock::GetName ()
{
   return &name;
}


bool GRPVECTORFILEDXFTextBlock::IsEndBlock ()
{
   return isEndBlock;
}
   
   
void GRPVECTORFILEDXFTextBlock::SetIsEndBlock (bool isEndBlock)
{
  this-> isEndBlock = isEndBlock;
}


bool GRPVECTORFILEDXFTextBlock::AddValue (GRPVECTORFILEDXFValue* value)
{    
   values.Add(value);

   return true;
}


XVECTOR<GRPVECTORFILEDXFValue*>* GRPVECTORFILEDXFTextBlock::GetValues ()
{
   return &values;
}


GRPVECTORFILEDXFValue* GRPVECTORFILEDXFTextBlock::GetValue (int index)
{
   if(values.IsEmpty()) return NULL;

   return values.Get(index);   
}


bool GRPVECTORFILEDXFTextBlock::DeleteValue(int index)
{
   if(values.IsEmpty()) return false;

   return values.Delete(GetValue(index));

}


bool GRPVECTORFILEDXFTextBlock::DeleteAllValues()
{
   if(values.IsEmpty()) return false;

   values.DeleteContents();
   values.DeleteAll(); 

   xDataCtrlList.DeleteContents();
   xDataCtrlList.DeleteAll();
      
   return true;
}


XVECTOR<GRPVECTORFILEDXFXDataCtrl*>* GRPVECTORFILEDXFTextBlock::GetXDataCtrlList()
{
   return &xDataCtrlList;
}



 GRPVECTORFILEDXFTextSectionEntities* GRPVECTORFILEDXFTextBlock::GetSectionEntities()
 {
   return entitiesSection;
 }
      
      
 void GRPVECTORFILEDXFTextBlock::SetSectionEntities(GRPVECTORFILEDXFTextSectionEntities* section)
 {
   this->entitiesSection = section;
 }


void GRPVECTORFILEDXFTextBlock::Clean()
{
   isEndBlock = false;
   entitiesSection = NULL;
}

#pragma endregion
