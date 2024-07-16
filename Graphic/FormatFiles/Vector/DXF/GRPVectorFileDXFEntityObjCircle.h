
#ifndef _GRPVECTORFILEDXFEntityObjCircle_h_
#define _GRPVECTORFILEDXFEntityObjCircle_h_

#pragma region INCLUDES

#include "XString.h"

#include "GRPVECTORFILEDXFEntityDefPoint.h"
#include "GRPVECTORFILEDXFEntityObj.h"

#pragma endregion


#pragma region DEFINES_ENUMS
#pragma endregion


#pragma region CLASSES

class GRPVECTORFILEDXFEntityObjCircle : public GRPVECTORFILEDXFEntityObj
{  
   public: 
      
      GRPVECTORFILEDXFEntityObjCircle (XCHAR* nameType);
      virtual ~GRPVECTORFILEDXFEntityObjCircle ();

      GRPVECTORFILEDXFEntityDefPoint* GetCenter(); 
      bool SetCenter(GRPVECTORFILEDXFEntityDefPoint* center); 
      
      double GetRadius (); 
      void SetRadius (double radius); 

      double GetThickness (); 
      void SetThickness (double thickness); 

      GRPVECTORFILEDXFEntityDefPoint* GetDirExtrusion (); 
      bool SetDirExtrusion ( GRPVECTORFILEDXFEntityDefPoint* dirExtrusion );

      virtual bool ApplyData(GRPVECTORFILEDXFEntity* entity);
            
   private: 
   
      void Clean ();   
          
      GRPVECTORFILEDXFEntityDefPoint center; // Center point.     
      
      double radius; // Radius.

      double thickness; // Thickness (default=0.0).          

      GRPVECTORFILEDXFEntityDefPoint dirExtrusion ; // Extrusion direction.
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif
