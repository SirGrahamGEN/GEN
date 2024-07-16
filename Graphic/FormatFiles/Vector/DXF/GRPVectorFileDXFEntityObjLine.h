
#ifndef _GRPVECTORFILEDXFEntityObjLine_h_
#define _GRPVECTORFILEDXFEntityObjLine_h_

#pragma region INCLUDES

#include "XString.h"

#include "GRPVECTORFILEDXFEntityDefPoint.h"
#include "GRPVECTORFILEDXFEntityObj.h"

#pragma endregion


#pragma region DEFINES_ENUMS
#pragma endregion


#pragma region CLASSES

class GRPVECTORFILEDXFEntityObjLine : public GRPVECTORFILEDXFEntityObj
{  
   public: 
      
      GRPVECTORFILEDXFEntityObjLine (XCHAR* nameType);
      virtual ~GRPVECTORFILEDXFEntityObjLine ();

      GRPVECTORFILEDXFEntityDefPoint* GetIni(); 
      bool SetIni(GRPVECTORFILEDXFEntityDefPoint* point); 

      GRPVECTORFILEDXFEntityDefPoint* GetEnd(); 
      bool SetEnd(GRPVECTORFILEDXFEntityDefPoint* point); 
            
      double GetThickness (); 
      void SetThickness (double thickness); 

      GRPVECTORFILEDXFEntityDefPoint* GetDirExtrusion (); 
      bool SetDirExtrusion ( GRPVECTORFILEDXFEntityDefPoint* dirExtrusion );

      virtual bool ApplyData(GRPVECTORFILEDXFEntity* entity);
            
   private: 
   
      void Clean ();   
      
      GRPVECTORFILEDXFEntityDefPoint  ini; // Initial point.
      GRPVECTORFILEDXFEntityDefPoint  end; // end point.

      double thickness; // Thickness (default=0.0).

      GRPVECTORFILEDXFEntityDefPoint dirExtrusion ; // Extrusion direction.
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif
