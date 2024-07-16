
#ifndef _GRPVECTORFILEDXFEntity_h_
#define _GRPVECTORFILEDXFEntity_h_

#pragma region INCLUDES

#include "XString.h"
#include "XVariant.h"
#include "XVector.h"

#include "GRPVECTORFILEDXFValue.h"
#include "GRPVECTORFILEDXFXDataCtrl.h"

#pragma endregion


#pragma region DEFINES_ENUMS
#pragma endregion


#pragma region CLASSES

class GRPVECTORFILEDXFEntity
{  
   public: 
      
      GRPVECTORFILEDXFEntity ();
      virtual ~GRPVECTORFILEDXFEntity ();

      XSTRING* GetName ();

      bool AddValue (GRPVECTORFILEDXFValue* value);
      XVECTOR<GRPVECTORFILEDXFValue*>* GetValues ();
      GRPVECTORFILEDXFValue* GetValue (int index);
      bool DeleteValue (int index);
      bool DeleteAllValues ();

      XVECTOR<GRPVECTORFILEDXFXDataCtrl*>* GetXDataCtrlList();
   
   private: 
   
      void Clean ();

      XSTRING name;
      XVECTOR<GRPVECTORFILEDXFValue*> values;
      XVECTOR<GRPVECTORFILEDXFXDataCtrl*> xDataCtrlList;
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif
