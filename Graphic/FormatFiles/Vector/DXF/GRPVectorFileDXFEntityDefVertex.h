
#ifndef _GRPVECTORFILEDXFENTITYDefVertex_h_
#define _GRPVECTORFILEDXFENTITYDefVertex_h_

#pragma region INCLUDES

#include "GRPVectorFileDXFEntityDefPoint.h"

#pragma endregion


#pragma region DEFINES_ENUMS
#pragma endregion


#pragma region CLASSES

class GRPVECTORFILEDXFENTITYDefVertex 
{
   public:
   
      GRPVECTORFILEDXFENTITYDefVertex () ;
      GRPVECTORFILEDXFENTITYDefVertex ( GRPVECTORFILEDXFENTITYDefVertex* Vertex ) ;
      ~GRPVECTORFILEDXFENTITYDefVertex () ;

      void operator =  (GRPVECTORFILEDXFENTITYDefVertex* Vertex);
      void operator =  (GRPVECTORFILEDXFENTITYDefVertex Vertex);

      GRPVECTORFILEDXFENTITYDEFPOINT* GetPoint(); 
      bool SetPoint(GRPVECTORFILEDXFENTITYDEFPOINT* point); 

      double GetIniWidth ();
      void SetIniWidth ( double iniWith );

      double GetEndWidth ();      
      void SetEndWidth ( double endWidth );

      double GetBulge ();      
      void SetBulge ( double bulge );
      
      bool CopyTo ( GRPVECTORFILEDXFENTITYDefVertex* Vertex );
      bool CopyFrom ( GRPVECTORFILEDXFENTITYDefVertex* Vertex );
   
   private: 

      void Clean ();

      GRPVECTORFILEDXFENTITYDEFPOINT point; // The point;    
      double iniWidth; // Start width.
      double endWidth; // End width.
      double bulge; // Bulge.
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif
