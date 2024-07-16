
#ifndef _GRPVECTORFILEDXFValue_h_
#define _GRPVECTORFILEDXFValue_h_

#pragma region INCLUDES

#include "XString.h"
#include "XVariant.h"
#include "XVector.h"

#pragma endregion


#pragma region DEFINES_ENUMS
#pragma endregion


#pragma region CLASSES


class GRPVECTORFILEDXFValue
{  
   public: 
      
      GRPVECTORFILEDXFValue ();
      virtual ~GRPVECTORFILEDXFValue ();

      int GetType();
      void SetType(int type);

      XSTRING* GetName ();
      XVARIANT* GetData ();
      XSTRING* GetRemark ();
       
   private: 
   
      void Clean ();   
      
      int type;
      XSTRING name;
      XVARIANT data;
      XSTRING remark;
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif
