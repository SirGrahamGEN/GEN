
#ifndef _GRPVECTORFILEDXFENTITYOBJText_h_
#define _GRPVECTORFILEDXFENTITYOBJText_h_

#pragma region INCLUDES

#include "XString.h"

#include "GRPVectorFileDXFEntityDefPoint.h"
#include "GRPVectorFileDXFEntityObj.h"

#pragma endregion


#pragma region DEFINES_ENUMS
#pragma endregion


#pragma region CLASSES

class GRPVECTORFILEDXFENTITYOBJText : public GRPVECTORFILEDXFENTITYOBJ
{  
   public: 
      
      GRPVECTORFILEDXFENTITYOBJText (XCHAR* nametype);
      virtual ~GRPVECTORFILEDXFENTITYOBJText ();

      virtual bool ApplyData(GRPVECTORFILEDXFENTITY* entity);
            
   private: 
   
      void Clean ();         
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif
