
#ifndef _GRPVECTORFILEDXFENTITYObjLWPolyLine_h_
#define _GRPVECTORFILEDXFENTITYObjLWPolyLine_h_

#pragma region INCLUDES

#include "XString.h"

#include "GRPVectorFileDXFEntityDefPoint.h"
#include "GRPVectorFileDXFEntityObj.h"

#pragma endregion


#pragma region DEFINES_ENUMS
#pragma endregion


#pragma region CLASSES

class GRPVECTORFILEDXFENTITYObjLWPolyLine : public GRPVECTORFILEDXFENTITYObj
{  
   public: 
      
      GRPVECTORFILEDXFENTITYObjLWPolyLine (XCHAR* nameType);
      virtual ~GRPVECTORFILEDXFENTITYObjLWPolyLine ();

      int GetNVertex(); 
      void SetNVertex(int nVertex); 

      int GetPolyLineFlag(); 
      void SetPolyLineFlag(int polyLineFlag); 

      double GetConstantWidth (); 
      void SetConstantWidth(double ConstantWidth); 

      double GetElevation (); 
      void SetElevation(double elevation); 
      
      double GetThickness (); 
      void SetThickness (double thickness); 

      GRPVECTORFILEDXFENTITYDEFPOINT* GetDirExtrusion (); 
      bool SetDirExtrusion ( GRPVECTORFILEDXFENTITYDEFPOINT* dirExtrusion );

      virtual bool ApplyData(GRPVECTORFILEDXFENTITY* entity);
            
   private: 
   
      void Clean ();   
      
      int nVertex; // Number of vertices.
      //CDxfVertexList m_objVertexList    ; // Vertex list.

      int polyLineFlag; // Polyline flag (bit-coded); default is 0: 1 = closed 128 = plinegen
      double constantWidth; // Constant width (optional; default = 0) Not used if variable width (codes 40 and/or 41) is set.
      double elevation; // Elevation (optional; default = 0)               
      
      double thickness; // Thickness (default=0.0).

      GRPVECTORFILEDXFENTITYDEFPOINT dirExtrusion ; // Extrusion direction.
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif
