
#ifndef _GRPVECTORFILEDXFEntityObjPoint_h_
#define _GRPVECTORFILEDXFEntityObjPoint_h_

#pragma region INCLUDES

#include "XString.h"

#include "GRPVECTORFILEDXFEntityDefPoint.h"
#include "GRPVECTORFILEDXFEntityObj.h"

#pragma endregion


#pragma region DEFINES_ENUMS
#pragma endregion


#pragma region CLASSES

class GRPVECTORFILEDXFEntityObjPoint : public GRPVECTORFILEDXFEntityObj
{  
   public: 
      
      GRPVECTORFILEDXFEntityObjPoint (XCHAR* nameType);
      virtual ~GRPVECTORFILEDXFEntityObjPoint ();

      GRPVECTORFILEDXFEntityDefPoint* GetPoint(); 
      bool SetPoint(GRPVECTORFILEDXFEntityDefPoint* point); 

      double GetXAxisAngle (); 
      void SetXAxisAngle (double xAxisAngle); 
     
      double GetThickness (); 
      void SetThickness (double thickness); 

      GRPVECTORFILEDXFEntityDefPoint* GetDirExtrusion (); 
      bool SetDirExtrusion ( GRPVECTORFILEDXFEntityDefPoint* dirExtrusion );

      virtual bool ApplyData(GRPVECTORFILEDXFEntity* entity);
            
   private: 
   
      void Clean ();

      GRPVECTORFILEDXFEntityDefPoint point; // Point.   
      double xAxisAngle; // X Axis Angle;
      
      double thickness; // Thickness (default=0.0).

      GRPVECTORFILEDXFEntityDefPoint dirExtrusion ; // Extrusion direction.     
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif
