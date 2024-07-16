
#ifndef _GRPVECTORFILEDXFTextBlock_h_
#define _GRPVECTORFILEDXFTextBlock_h_

#pragma region INCLUDES

#include "XString.h"
#include "XVector.h"

#include "GRPVECTORFILEDXFValue.h"
#include "GRPVECTORFILEDXFTextSectionEntities.h"

#pragma endregion


#pragma region DEFINES_ENUMS
#pragma endregion


#pragma region CLASSES

class GRPVECTORFILEDXFTextBlock
{  
   public: 
      
      GRPVECTORFILEDXFTextBlock ();
      virtual ~GRPVECTORFILEDXFTextBlock ();

      XSTRING* GetName ();

      bool IsEndBlock ();
      void SetIsEndBlock (bool isEndBlock);
      
      bool AddValue (GRPVECTORFILEDXFValue* value);
      XVECTOR<GRPVECTORFILEDXFValue*>* GetValues ();
      GRPVECTORFILEDXFValue* GetValue (int index);
      bool DeleteValue (int index);
      bool DeleteAllValues ();
      
      XVECTOR<GRPVECTORFILEDXFXDataCtrl*>* GetXDataCtrlList();

      GRPVECTORFILEDXFTextSectionEntities* GetSectionEntities ();
      void SetSectionEntities (GRPVECTORFILEDXFTextSectionEntities* section);
      
   private: 
   
      void Clean ();
     
      XSTRING name;
      bool isEndBlock;
      
      XVECTOR<GRPVECTORFILEDXFValue*> values;
      XVECTOR<GRPVECTORFILEDXFXDataCtrl*> xDataCtrlList;

      GRPVECTORFILEDXFTextSectionEntities* entitiesSection;
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif
