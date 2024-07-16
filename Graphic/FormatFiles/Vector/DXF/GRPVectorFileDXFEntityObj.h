
#ifndef _GRPVECTORFILEDXFEntityObj_h_
#define _GRPVECTORFILEDXFEntityObj_h_

#pragma region INCLUDES

#include "XString.h"

#include "GRPVECTORFILEDXFEntity.h"

#pragma endregion


#pragma region DEFINES_ENUMS

enum GRPVECTORFILEDXFEntityObjType
{
   GRPVECTORFILEDXFEntityObjType_Unknown = 0 ,
   GRPVECTORFILEDXFEntityObjType_3DFace,  
   GRPVECTORFILEDXFEntityObjType_Arc,  
   GRPVECTORFILEDXFEntityObjType_Circle, 
   GRPVECTORFILEDXFEntityObjType_Ellipse,   
   GRPVECTORFILEDXFEntityObjType_Line,
   GRPVECTORFILEDXFEntityObjType_LWPolyLine,
   GRPVECTORFILEDXFEntityObjType_MText, 
   GRPVECTORFILEDXFEntityObjType_Point, 
   GRPVECTORFILEDXFEntityObjType_PolyLine, 
   GRPVECTORFILEDXFEntityObjType_Text, 
   
   GRPVECTORFILEDXFEntityObjType_MaxElements
};

#pragma endregion


#pragma region CLASSES

class GRPVECTORFILEDXFEntityObj
{  
   public: 
      
      GRPVECTORFILEDXFEntityObj (XCHAR* name);
      virtual ~GRPVECTORFILEDXFEntityObj ();
      
      static GRPVECTORFILEDXFEntityObj* CreateInstance(GRPVECTORFILEDXFEntity* entity);
      
      GRPVECTORFILEDXFEntityObjType GetType ();
      XSTRING* GetNameType ();

      XSTRING* GetLayerName ();
     
      int GetLineColor ();
      void SetLineColor (int lineColor); 
      
      XSTRING* GetLineTypeName ();

      int GetTypeSpace ();
      void SetTypeSpace (int typeSpace); 

      bool GetVisibility();
      void SetVisibility(bool visibility);

      virtual bool ApplyData(GRPVECTORFILEDXFEntity* entity);

      GRPVECTORFILEDXFValue* GetDataValue(int type, GRPVECTORFILEDXFEntity* entity);
      GRPVECTORFILEDXFValue* GetDataValue(XCHAR* name, GRPVECTORFILEDXFEntity* entity);

   protected:

      GRPVECTORFILEDXFEntityObjType type;      
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
