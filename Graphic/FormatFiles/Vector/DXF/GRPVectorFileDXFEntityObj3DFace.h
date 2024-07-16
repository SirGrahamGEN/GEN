
#ifndef _GRPVECTORFILEDXFEntityObj3DFace_h_
#define _GRPVECTORFILEDXFEntityObj3DFace_h_

#pragma region INCLUDES

#include "XString.h"

#include "GRPVECTORFILEDXFEntityDefPoint.h"
#include "GRPVECTORFILEDXFEntityObj.h"

#pragma endregion


#pragma region DEFINES_ENUMS
#pragma endregion


#pragma region CLASSES

class GRPVECTORFILEDXFEntityObj3DFace : public GRPVECTORFILEDXFEntityObj
{  
   public: 
      
      GRPVECTORFILEDXFEntityObj3DFace (XCHAR* nameType);
      virtual ~GRPVECTORFILEDXFEntityObj3DFace ();

      virtual bool ApplyData(GRPVECTORFILEDXFEntity* entity);
            
   private: 
   
      void Clean ();                     
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif
