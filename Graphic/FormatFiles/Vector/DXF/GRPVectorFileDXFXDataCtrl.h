
#ifndef _GRPVECTORFILEDXFXDataCtrl_h_
#define _GRPVECTORFILEDXFXDataCtrl_h_

#pragma region INCLUDES

#include "XString.h"
#include "XVariant.h"
#include "XVector.h"

#include "GRPVECTORFILEDXFValue.h"

#pragma endregion


#pragma region DEFINES_ENUMS
#pragma endregion


#pragma region CLASSES


class GRPVECTORFILEDXFXDataCtrl
{  
   public: 
      
      GRPVECTORFILEDXFXDataCtrl ();
      virtual ~GRPVECTORFILEDXFXDataCtrl ();

      XSTRING* GetName ();
      XVECTOR<GRPVECTORFILEDXFValue*>* GetValues ();
     
   
   private: 
   
      void Clean ();

      XSTRING name;
      XVECTOR<GRPVECTORFILEDXFValue*> values;
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif
