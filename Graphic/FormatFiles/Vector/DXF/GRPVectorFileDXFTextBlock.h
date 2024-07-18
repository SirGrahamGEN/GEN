
#ifndef _GRPVECTORFILEDXFTextBlock_h_
#define _GRPVECTORFILEDXFTextBlock_h_

#pragma region INCLUDES

#include "XString.h"
#include "XVector.h"

#include "GRPVectorFileDXFValue.h"
#include "GRPVectorFileDXFTextSectionEntities.h"

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
      
      bool AddValue (GRPVECTORFILEDXFVALUE* value);
      XVECTOR<GRPVECTORFILEDXFVALUE*>* GetValues ();
      GRPVECTORFILEDXFVALUE* GetValue (int index);
      bool DeleteValue (int index);
      bool DeleteAllValues ();
      
      XVECTOR<GRPVECTORFILEDXFXDATACTRL*>* GetXDataCtrlList();

      GRPVECTORFILEDXFTEXTSECTIONENTITIES* GetSectionEntities ();
      void SetSectionEntities (GRPVECTORFILEDXFTEXTSECTIONENTITIES* section);
      
   private: 
   
      void Clean ();
     
      XSTRING name;
      bool isEndBlock;
      
      XVECTOR<GRPVECTORFILEDXFVALUE*> values;
      XVECTOR<GRPVECTORFILEDXFXDATACTRL*> xDataCtrlList;

      GRPVECTORFILEDXFTEXTSECTIONENTITIES* entitiesSection;
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif
