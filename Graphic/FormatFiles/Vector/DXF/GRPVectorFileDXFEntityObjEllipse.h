
#ifndef _GRPVECTORFILEDXFEntityObjEllipse_h_
#define _GRPVECTORFILEDXFEntityObjEllipse_h_

#pragma region INCLUDES

#include "XString.h"

#include "GRPVECTORFILEDXFEntityDefPoint.h"
#include "GRPVECTORFILEDXFEntityObj.h"

#pragma endregion


#pragma region DEFINES_ENUMS
#pragma endregion


#pragma region CLASSES

class GRPVECTORFILEDXFEntityObjEllipse : public GRPVECTORFILEDXFEntityObj
{  
   public: 
      
      GRPVECTORFILEDXFEntityObjEllipse (XCHAR* nameType);
      virtual ~GRPVECTORFILEDXFEntityObjEllipse ();

      GRPVECTORFILEDXFEntityDefPoint* GetCenter(); 
      bool SetCenter(GRPVECTORFILEDXFEntityDefPoint* point); 

      GRPVECTORFILEDXFEntityDefPoint* GetMajorAxis(); 
      bool SetMajorAxis(GRPVECTORFILEDXFEntityDefPoint* point); 

      double GetIniParameter(); 
      void SetIniParameter(double iniParameter); 

      double GetEndParameter(); 
      void SetEndParameter(double endParameter); 
            
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
      GRPVECTORFILEDXFEntityDefPoint majorAxis;  // Major Axis point.
   
      double iniParameter; // Start parameter (this value is 0.0 for a full ellipse)
      double endParameter; // End   parameter (this value is 2pi for a full ellipse)
         
      double radius; // Radius.

      double thickness; // Thickness (default=0.0).   
      
      

      GRPVECTORFILEDXFEntityDefPoint dirExtrusion ; // Extrusion direction.
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif
