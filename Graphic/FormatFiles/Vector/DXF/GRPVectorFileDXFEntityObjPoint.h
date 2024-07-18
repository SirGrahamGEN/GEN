
#ifndef _GRPVECTORFILEDXFENTITYObjPoint_h_
#define _GRPVECTORFILEDXFENTITYObjPoint_h_

#pragma region INCLUDES

#include "XString.h"

#include "GRPVectorFileDXFEntityDefPoint.h"
#include "GRPVectorFileDXFEntityObj.h"

#pragma endregion


#pragma region DEFINES_ENUMS
#pragma endregion


#pragma region CLASSES

class GRPVECTORFILEDXFENTITYObjPoint : public GRPVECTORFILEDXFENTITYObj
{  
   public: 
      
      GRPVECTORFILEDXFENTITYObjPoint (XCHAR* nameType);
      virtual ~GRPVECTORFILEDXFENTITYObjPoint ();

      GRPVECTORFILEDXFENTITYDEFPOINT* GetPoint(); 
      bool SetPoint(GRPVECTORFILEDXFENTITYDEFPOINT* point); 

      double GetXAxisAngle (); 
      void SetXAxisAngle (double xAxisAngle); 
     
      double GetThickness (); 
      void SetThickness (double thickness); 

      GRPVECTORFILEDXFENTITYDEFPOINT* GetDirExtrusion (); 
      bool SetDirExtrusion ( GRPVECTORFILEDXFENTITYDEFPOINT* dirExtrusion );

      virtual bool ApplyData(GRPVECTORFILEDXFENTITY* entity);
            
   private: 
   
      void Clean ();

      GRPVECTORFILEDXFENTITYDEFPOINT point; // Point.   
      double xAxisAngle; // X Axis Angle;
      
      double thickness; // Thickness (default=0.0).

      GRPVECTORFILEDXFENTITYDEFPOINT dirExtrusion ; // Extrusion direction.     
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif
