
#ifndef _GRPVECTORFILEDXFENTITYObjPolyLine_h_
#define _GRPVECTORFILEDXFENTITYObjPolyLine_h_

#pragma region INCLUDES

#include "XString.h"

#include "GRPVectorFileDXFEntityDefPoint.h"
#include "GRPVectorFileDXFEntityObj.h"

#pragma endregion


#pragma region DEFINES_ENUMS
#pragma endregion


#pragma region CLASSES

class GRPVECTORFILEDXFENTITYObjPolyLine : public GRPVECTORFILEDXFENTITYObj
{  
   public: 
      
      GRPVECTORFILEDXFENTITYObjPolyLine (XCHAR* nameType);
      virtual ~GRPVECTORFILEDXFENTITYObjPolyLine ();

      double GetThickness (); 
      void SetThickness (double thickness); 

      GRPVECTORFILEDXFENTITYDEFPOINT* GetDirExtrusion (); 
      bool SetDirExtrusion ( GRPVECTORFILEDXFENTITYDEFPOINT* dirExtrusion );

      virtual bool ApplyData(GRPVECTORFILEDXFENTITY* entity);
            
   private: 
   
      void Clean (); 
      
      double thickness; // Thickness (default=0.0).

      GRPVECTORFILEDXFENTITYDEFPOINT dirExtrusion ; // Extrusion direction.
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif
