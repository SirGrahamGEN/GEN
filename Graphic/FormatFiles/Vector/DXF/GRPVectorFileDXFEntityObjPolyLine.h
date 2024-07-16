
#ifndef _GRPVECTORFILEDXFEntityObjPolyLine_h_
#define _GRPVECTORFILEDXFEntityObjPolyLine_h_

#pragma region INCLUDES

#include "XString.h"

#include "GRPVECTORFILEDXFEntityDefPoint.h"
#include "GRPVECTORFILEDXFEntityObj.h"

#pragma endregion


#pragma region DEFINES_ENUMS
#pragma endregion


#pragma region CLASSES

class GRPVECTORFILEDXFEntityObjPolyLine : public GRPVECTORFILEDXFEntityObj
{  
   public: 
      
      GRPVECTORFILEDXFEntityObjPolyLine (XCHAR* nameType);
      virtual ~GRPVECTORFILEDXFEntityObjPolyLine ();

      double GetThickness (); 
      void SetThickness (double thickness); 

      GRPVECTORFILEDXFEntityDefPoint* GetDirExtrusion (); 
      bool SetDirExtrusion ( GRPVECTORFILEDXFEntityDefPoint* dirExtrusion );

      virtual bool ApplyData(GRPVECTORFILEDXFEntity* entity);
            
   private: 
   
      void Clean (); 
      
      double thickness; // Thickness (default=0.0).

      GRPVECTORFILEDXFEntityDefPoint dirExtrusion ; // Extrusion direction.
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif
