
#ifndef _GRPVECTORFILEDXFEntityObjText_h_
#define _GRPVECTORFILEDXFEntityObjText_h_

#pragma region INCLUDES

#include "XString.h"

#include "GRPVECTORFILEDXFEntityDefPoint.h"
#include "GRPVECTORFILEDXFEntityObj.h"

#pragma endregion


#pragma region DEFINES_ENUMS
#pragma endregion


#pragma region CLASSES

class GRPVECTORFILEDXFEntityObjText : public GRPVECTORFILEDXFEntityObj
{  
   public: 
      
      GRPVECTORFILEDXFEntityObjText (XCHAR* nameType);
      virtual ~GRPVECTORFILEDXFEntityObjText ();

      virtual bool ApplyData(GRPVECTORFILEDXFEntity* entity);
            
   private: 
   
      void Clean ();         
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif
