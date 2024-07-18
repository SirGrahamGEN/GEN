
#ifndef _GRPVECTORFILEDXFENTITYObjCircle_h_
#define _GRPVECTORFILEDXFENTITYObjCircle_h_

#pragma region INCLUDES

#include "XString.h"

#include "GRPVectorFileDXFEntityDefPoint.h"
#include "GRPVectorFileDXFEntityObj.h"

#pragma endregion


#pragma region DEFINES_ENUMS
#pragma endregion


#pragma region CLASSES

class GRPVECTORFILEDXFENTITYObjCircle : public GRPVECTORFILEDXFENTITYObj
{  
   public: 
      
      GRPVECTORFILEDXFENTITYObjCircle (XCHAR* nameType);
      virtual ~GRPVECTORFILEDXFENTITYObjCircle ();

      GRPVECTORFILEDXFENTITYDEFPOINT* GetCenter(); 
      bool SetCenter(GRPVECTORFILEDXFENTITYDEFPOINT* center); 
      
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
      
      double radius; // Radius.

      double thickness; // Thickness (default=0.0).          

      GRPVECTORFILEDXFENTITYDEFPOINT dirExtrusion ; // Extrusion direction.
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif
