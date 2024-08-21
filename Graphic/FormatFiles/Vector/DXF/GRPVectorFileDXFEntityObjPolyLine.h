
#ifndef _GRPVECTORFILEDXFENTITYOBJPolyLine_h_
#define _GRPVECTORFILEDXFENTITYOBJPolyLine_h_

#pragma region INCLUDES

#include "XString.h"

#include "GRPVectorFileDXFEntityDefPoint.h"
#include "GRPVectorFileDXFEntityObj.h"

#pragma endregion


#pragma region DEFINES_ENUMS
#pragma endregion


#pragma region CLASSES

class GRPVECTORFILEDXFENTITYOBJPolyLine : public GRPVECTORFILEDXFENTITYOBJ
{  
   public: 
      
      GRPVECTORFILEDXFENTITYOBJPolyLine (XCHAR* nametype);
      virtual ~GRPVECTORFILEDXFENTITYOBJPolyLine ();

      double GetThickness (); 
      void SetThickness (double thickness); 

      GRPVECTORFILEDXFENTITYDEFPOINT* GetDirExtrusion (); 
      bool SetDirExtrusion(GRPVECTORFILEDXFENTITYDEFPOINT* dirextrusion);

      virtual bool ApplyData(GRPVECTORFILEDXFENTITY* entity);
            
   private: 
   
      void Clean (); 
      
      double thickness; // Thickness (default=0.0).

      GRPVECTORFILEDXFENTITYDEFPOINT dirextrusion ; // Extrusion direction.
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif
