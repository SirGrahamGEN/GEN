
#ifndef _GRPVECTORFILEDXFENTITYObj3DFace_h_
#define _GRPVECTORFILEDXFENTITYObj3DFace_h_

#pragma region INCLUDES

#include "XString.h"

#include "GRPVectorFileDXFEntityDefPoint.h"
#include "GRPVectorFileDXFEntityObj.h"

#pragma endregion


#pragma region DEFINES_ENUMS
#pragma endregion


#pragma region CLASSES

class GRPVECTORFILEDXFENTITYObj3DFace : public GRPVECTORFILEDXFENTITYObj
{  
   public: 
      
      GRPVECTORFILEDXFENTITYObj3DFace (XCHAR* nameType);
      virtual ~GRPVECTORFILEDXFENTITYObj3DFace ();

      virtual bool ApplyData(GRPVECTORFILEDXFENTITY* entity);
            
   private: 
   
      void Clean ();                     
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif
