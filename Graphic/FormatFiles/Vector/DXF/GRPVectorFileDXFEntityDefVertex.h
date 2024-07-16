
#ifndef _GRPVECTORFILEDXFEntityDefVertex_h_
#define _GRPVECTORFILEDXFEntityDefVertex_h_

#pragma region INCLUDES

#include "GRPVECTORFILEDXFEntityDefPoint.h"

#pragma endregion


#pragma region DEFINES_ENUMS
#pragma endregion


#pragma region CLASSES

class GRPVECTORFILEDXFEntityDefVertex 
{
   public:
   
      GRPVECTORFILEDXFEntityDefVertex () ;
      GRPVECTORFILEDXFEntityDefVertex ( GRPVECTORFILEDXFEntityDefVertex* Vertex ) ;
      ~GRPVECTORFILEDXFEntityDefVertex () ;

      void operator =  (GRPVECTORFILEDXFEntityDefVertex* Vertex);
      void operator =  (GRPVECTORFILEDXFEntityDefVertex Vertex);

      GRPVECTORFILEDXFEntityDefPoint* GetPoint(); 
      bool SetPoint(GRPVECTORFILEDXFEntityDefPoint* point); 

      double GetIniWidth ();
      void SetIniWidth ( double iniWith );

      double GetEndWidth ();      
      void SetEndWidth ( double endWidth );

      double GetBulge ();      
      void SetBulge ( double bulge );
      
      bool CopyTo ( GRPVECTORFILEDXFEntityDefVertex* Vertex );
      bool CopyFrom ( GRPVECTORFILEDXFEntityDefVertex* Vertex );
   
   private: 

      void Clean ();

      GRPVECTORFILEDXFEntityDefPoint point; // The point;    
      double iniWidth; // Start width.
      double endWidth; // End width.
      double bulge; // Bulge.
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif
