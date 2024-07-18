
#ifndef _GRPVECTORFILEDXFENTITYObj_h_
#define _GRPVECTORFILEDXFENTITYObj_h_

#pragma region INCLUDES

#include "XString.h"

#include "GRPVectorFileDXFEntity.h"

#pragma endregion


#pragma region DEFINES_ENUMS

enum GRPVECTORFILEDXFENTITYObjType
{
   GRPVECTORFILEDXFENTITYObjType_Unknown = 0 ,
   GRPVECTORFILEDXFENTITYObjType_3DFace,  
   GRPVECTORFILEDXFENTITYObjType_Arc,  
   GRPVECTORFILEDXFENTITYObjType_Circle, 
   GRPVECTORFILEDXFENTITYObjType_Ellipse,   
   GRPVECTORFILEDXFENTITYObjType_Line,
   GRPVECTORFILEDXFENTITYObjType_LWPolyLine,
   GRPVECTORFILEDXFENTITYObjType_MText, 
   GRPVECTORFILEDXFENTITYObjType_Point, 
   GRPVECTORFILEDXFENTITYObjType_PolyLine, 
   GRPVECTORFILEDXFENTITYObjType_Text, 
   
   GRPVECTORFILEDXFENTITYObjType_MaxElements
};

#pragma endregion


#pragma region CLASSES

class GRPVECTORFILEDXFENTITYObj
{  
   public: 
      
      GRPVECTORFILEDXFENTITYObj (XCHAR* name);
      virtual ~GRPVECTORFILEDXFENTITYObj ();
      
      static GRPVECTORFILEDXFENTITYObj* CreateInstance(GRPVECTORFILEDXFENTITY* entity);
      
      GRPVECTORFILEDXFENTITYObjType GetType ();
      XSTRING* GetNameType ();

      XSTRING* GetLayerName ();
     
      int GetLineColor ();
      void SetLineColor (int lineColor); 
      
      XSTRING* GetLineTypeName ();

      int GetTypeSpace ();
      void SetTypeSpace (int typeSpace); 

      bool GetVisibility();
      void SetVisibility(bool visibility);

      virtual bool ApplyData(GRPVECTORFILEDXFENTITY* entity);

      GRPVECTORFILEDXFVALUE* GetDataValue(int type, GRPVECTORFILEDXFENTITY* entity);
      GRPVECTORFILEDXFVALUE* GetDataValue(XCHAR* name, GRPVECTORFILEDXFENTITY* entity);

   protected:

      GRPVECTORFILEDXFENTITYObjType type;      
      XSTRING nameType;      
      
      XSTRING layerName;
      XSTRING lineTypeName;
      int lineColor; 
      
      int typeSpace;

      bool visibility;
      
   private: 
   
      void Clean ();        
};

#pragma endregion


#pragma region EXTERN_INLINE_FUNCTIONS
#pragma endregion

#endif
