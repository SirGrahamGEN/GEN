
#ifndef _GRPVECTORFILEDXFENTITYObjLine_h_
#define _GRPVECTORFILEDXFENTITYObjLine_h_

#pragma region INCLUDES

#include "XString.h"

#include "GRPVectorFileDXFEntityDefPoint.h"
#include "GRPVectorFileDXFEntityObj.h"

#pragma endregion


#pragma region DEFINES_ENUMS
#pragma endregion


#pragma region CLASSES

class GRPVECTORFILEDXFENTITYObjLine : public GRPVECTORFILEDXFENTITYObj
{  
   public: 
      
      GRPVECTORFILEDXFENTITYObjLine (XCHAR* nameType);
      virtual ~GRPVECTORFILEDXFENTITYObjLine ();

      GRPVECTORFILEDXFENTITYDEFPOINT* GetIni(); 
      bool SetIni(GRPVECTORFILEDXFENTITYDEFPOINT* point); 

      GRPVECTORFILEDXFENTITYDEFPOINT* GetEnd(); 
      bool SetEnd(GRPVECTORFILEDXFENTITYDEFPOINT* point); 
            
      double GetThickness (); 
      void SetThickness (double thickness); 

      GRPVECTORFILEDXFENTITYDEFPOINT* GetDirExtrusion (); 
      bool SetDirExtrusion ( GRPVECTORFILEDXFENTITYDEFPOINT* dirExtrusion );

      virtual bool ApplyData(GRPVECTORFILEDXFENTITY* entity);
            
   private: 
   
      void Clean ();   
      
      GRPVECTORFILEDXFENTITYDEFPOINT  ini; // Initial point.
      GRPVECTORFILEDXFENTITYDEFPOINT  end; // end point.

      double thickness; // Thickness (default=0.0).

      GRPVECTORFILEDXFENTITYDEFPOINT dirExtrusion ; // Extrusion direction.
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif
