
#ifndef _GRPVECTORFILEDXFENTITYObjArc_h_
#define _GRPVECTORFILEDXFENTITYObjArc_h_

#pragma region INCLUDES

#include "XString.h"

#include "GRPVectorFileDXFEntityDefPoint.h"
#include "GRPVectorFileDXFEntityObj.h"

#pragma endregion


#pragma region DEFINES_ENUMS
#pragma endregion


#pragma region CLASSES

class GRPVECTORFILEDXFENTITYObjArc : public GRPVECTORFILEDXFENTITYObj
{  
   public: 
      
      GRPVECTORFILEDXFENTITYObjArc (XCHAR* nameType);
      virtual ~GRPVECTORFILEDXFENTITYObjArc ();

      GRPVECTORFILEDXFENTITYDEFPOINT* GetCenter(); 
      bool SetCenter(GRPVECTORFILEDXFENTITYDEFPOINT* center); 

      double GetIniAngle (); 
      void SetIniAngle (double angle); 
      double GetEndAngle (); 
      void SetEndAngle (double angle); 

      double GetRadius (); 
      void SetRadius (double radius); 

      double GetThickness (); 
      void SetThickness (double thickness); 

      GRPVECTORFILEDXFENTITYDEFPOINT* GetDirExtrusion (); 
      bool SetDirExtrusion ( GRPVECTORFILEDXFENTITYDEFPOINT* dirExtrusion );

      virtual bool ApplyData(GRPVECTORFILEDXFENTITY* entity);
            
   private: 
   
      void Clean ();   
          
      GRPVECTORFILEDXFENTITYDEFPOINT center; // Center point.     

      double iniAngle; // Start angle.
      double endAngle; // End   angle.

      double radius; // Radius.

      double thickness; // Thickness (default=0.0).          

      GRPVECTORFILEDXFENTITYDEFPOINT dirExtrusion ; // Extrusion direction.
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif
