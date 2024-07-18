
#ifndef _GRPVECTORFILEDXFENTITYObjEllipse_h_
#define _GRPVECTORFILEDXFENTITYObjEllipse_h_

#pragma region INCLUDES

#include "XString.h"

#include "GRPVectorFileDXFEntityDefPoint.h"
#include "GRPVectorFileDXFEntityObj.h"

#pragma endregion


#pragma region DEFINES_ENUMS
#pragma endregion


#pragma region CLASSES

class GRPVECTORFILEDXFENTITYObjEllipse : public GRPVECTORFILEDXFENTITYObj
{  
   public: 
      
      GRPVECTORFILEDXFENTITYObjEllipse (XCHAR* nameType);
      virtual ~GRPVECTORFILEDXFENTITYObjEllipse ();

      GRPVECTORFILEDXFENTITYDEFPOINT* GetCenter(); 
      bool SetCenter(GRPVECTORFILEDXFENTITYDEFPOINT* point); 

      GRPVECTORFILEDXFENTITYDEFPOINT* GetMajorAxis(); 
      bool SetMajorAxis(GRPVECTORFILEDXFENTITYDEFPOINT* point); 

      double GetIniParameter(); 
      void SetIniParameter(double iniParameter); 

      double GetEndParameter(); 
      void SetEndParameter(double endParameter); 
            
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
      GRPVECTORFILEDXFENTITYDEFPOINT majorAxis;  // Major Axis point.
   
      double iniParameter; // Start parameter (this value is 0.0 for a full ellipse)
      double endParameter; // End   parameter (this value is 2pi for a full ellipse)
         
      double radius; // Radius.

      double thickness; // Thickness (default=0.0).   
      
      

      GRPVECTORFILEDXFENTITYDEFPOINT dirExtrusion ; // Extrusion direction.
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif
