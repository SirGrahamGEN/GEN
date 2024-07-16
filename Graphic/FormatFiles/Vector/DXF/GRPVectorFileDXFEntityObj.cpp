#pragma region INCLUDES

#include "GRPVECTORFILEDXFEntityObj3DFace.h"
#include "GRPVECTORFILEDXFEntityObjArc.h"
#include "GRPVECTORFILEDXFEntityObjCircle.h"
#include "GRPVECTORFILEDXFEntityObjEllipse.h"
#include "GRPVECTORFILEDXFEntityObjLine.h"
#include "GRPVECTORFILEDXFEntityObjLWPolyLine.h"
#include "GRPVECTORFILEDXFEntityObjMText.h"
#include "GRPVECTORFILEDXFEntityObjPolyLine.h"
#include "GRPVECTORFILEDXFEntityObjPoint.h"
#include "GRPVECTORFILEDXFEntityObjText.h"

#include "GRPVECTORFILEDXFEntityObj.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFEntityObj::GRPVECTORFILEDXFEntityObj (XCHAR* nameType)
{
   Clean();   

   this->nameType = nameType;

   visibility = true;
}


GRPVECTORFILEDXFEntityObj::~GRPVECTORFILEDXFEntityObj ( )
{ 
   Clean();
}

GRPVECTORFILEDXFEntityObj* GRPVECTORFILEDXFEntityObj::CreateInstance(GRPVECTORFILEDXFEntity* entity)
{   
   typedef struct
   {
      XCHAR* entityName;
      GRPVECTORFILEDXFEntityObjType objType;
   
   } ENTITY2CLASS;

   ENTITY2CLASS entity2class[] = { { __L("3DFACE")           , GRPVECTORFILEDXFEntityObjType_3DFace         },
                                   { __L("ARC")              , GRPVECTORFILEDXFEntityObjType_Arc            },
                                   { __L("CIRCLE")           , GRPVECTORFILEDXFEntityObjType_Circle         },           
                                   { __L("ACAD_CIRCLE")      , GRPVECTORFILEDXFEntityObjType_Circle         },
                                   { __L("ELLIPSE")          , GRPVECTORFILEDXFEntityObjType_Ellipse        },
                                   { __L("LINE")             , GRPVECTORFILEDXFEntityObjType_Line           },
                                   { __L("LWPOLYLINE")       , GRPVECTORFILEDXFEntityObjType_LWPolyLine     },
                                   { __L("MTEXT")            , GRPVECTORFILEDXFEntityObjType_MText          },
                                   { __L("POINT")            , GRPVECTORFILEDXFEntityObjType_Point          },
                                   { __L("POLYLINE")         , GRPVECTORFILEDXFEntityObjType_PolyLine       },
                                   { __L("TEXT")             , GRPVECTORFILEDXFEntityObjType_Text           }
                                 };

   GRPVECTORFILEDXFEntityObj* entityObj = NULL; 
  
   if(!entity) 
   {
      return entityObj;
   }

   for(int c=0; c<sizeof(entity2class)/sizeof(ENTITY2CLASS); c++)
   { 
      if(!entity->GetName()->Compare(entity2class[c].entityName, true))
      {
         switch(entity2class[c].objType)
         {
            case GRPVECTORFILEDXFEntityObjType_Unknown      :
                                            default      : break;
            case GRPVECTORFILEDXFEntityObjType_3DFace       : entityObj = new GRPVECTORFILEDXFEntityObj3DFace(entity2class[c].entityName);       break; 
            case GRPVECTORFILEDXFEntityObjType_Arc          : entityObj = new GRPVECTORFILEDXFEntityObjArc(entity2class[c].entityName);          break;            
            case GRPVECTORFILEDXFEntityObjType_Circle       : entityObj = new GRPVECTORFILEDXFEntityObjCircle(entity2class[c].entityName);       break;          
            case GRPVECTORFILEDXFEntityObjType_Ellipse      : entityObj = new GRPVECTORFILEDXFEntityObjEllipse(entity2class[c].entityName);      break;         
            case GRPVECTORFILEDXFEntityObjType_Line         : entityObj = new GRPVECTORFILEDXFEntityObjLine(entity2class[c].entityName);         break;            
            case GRPVECTORFILEDXFEntityObjType_LWPolyLine   : entityObj = new GRPVECTORFILEDXFEntityObjLWPolyLine(entity2class[c].entityName);   break;      
            case GRPVECTORFILEDXFEntityObjType_MText        : entityObj = new GRPVECTORFILEDXFEntityObjMText(entity2class[c].entityName);        break;           
            case GRPVECTORFILEDXFEntityObjType_Point        : entityObj = new GRPVECTORFILEDXFEntityObjPoint(entity2class[c].entityName);        break;           
            case GRPVECTORFILEDXFEntityObjType_PolyLine     : entityObj = new GRPVECTORFILEDXFEntityObjPolyLine(entity2class[c].entityName);     break;        
            case GRPVECTORFILEDXFEntityObjType_Text         : entityObj = new GRPVECTORFILEDXFEntityObjText(entity2class[c].entityName);         break;                              
         }
      }
   }

   if(entityObj)
   {
      entityObj->ApplyData(entity);
   }
  
   return entityObj;
}


GRPVECTORFILEDXFEntityObjType GRPVECTORFILEDXFEntityObj::GetType()
{
   return type;
}


XSTRING* GRPVECTORFILEDXFEntityObj::GetNameType()
{
   return &nameType;
}


XSTRING* GRPVECTORFILEDXFEntityObj::GetLayerName ( )
{
   return &layerName;
}


int GRPVECTORFILEDXFEntityObj::GetLineColor ( )
{
   return lineColor;
}


void GRPVECTORFILEDXFEntityObj::SetLineColor (int lineColor)
{
   this->lineColor = lineColor;
}


XSTRING* GRPVECTORFILEDXFEntityObj::GetLineTypeName ( )
{
   return &lineTypeName;
}


int GRPVECTORFILEDXFEntityObj::GetTypeSpace ()
{
   return typeSpace;
}
 

void GRPVECTORFILEDXFEntityObj::SetTypeSpace (int typeSpace)
{
   this->typeSpace = typeSpace;
}


bool GRPVECTORFILEDXFEntityObj::GetVisibility()
{
   return visibility;
}
      
     
void GRPVECTORFILEDXFEntityObj::SetVisibility(bool visibility)
{
   this->visibility = visibility;
}


bool GRPVECTORFILEDXFEntityObj::ApplyData(GRPVECTORFILEDXFEntity* entity)
{
   GRPVECTORFILEDXFValue* value;
   
   value = GetDataValue(__L("G_LAYER_NAME"), entity);   
   if(value) 
   {
      layerName.Set((XCHAR*)(*value->GetData()));
   }

   value = GetDataValue(__L("G_COLOR_NUMBER"), entity);   
   if(value) 
   {
      lineColor = (int)(*value->GetData());
   }

   value = GetDataValue(__L("G_LINETYPE_NAME"), entity);      
   if(value) 
   {
      lineTypeName.Set((XCHAR*)(*value->GetData()));
   }

   value = GetDataValue(__L("G_TYPE_SPACE"), entity);      
   if(value) 
   {
      typeSpace = (int)(*value->GetData());
   }

   value = GetDataValue(__L("G_ENTITY_VISIBILITY"), entity);      
   if(value) 
   {
      visibility = ((int)(*value->GetData()))?false:true;
   }

   return true;
}


GRPVECTORFILEDXFValue* GRPVECTORFILEDXFEntityObj::GetDataValue(int type, GRPVECTORFILEDXFEntity* entity)
{
   if(!entity) return NULL;

   for(XDWORD c=0; c<entity->GetValues()->GetSize(); c++)
   {
      GRPVECTORFILEDXFValue* value = entity->GetValues()->Get(c);
      if(value)
      {
         if(value->GetType() == type)
         {
            return value;
         }           
      }           
   }

   return NULL;
}


GRPVECTORFILEDXFValue* GRPVECTORFILEDXFEntityObj::GetDataValue(XCHAR* name, GRPVECTORFILEDXFEntity* entity)
{
   if(!entity) return NULL;

   for(XDWORD c=0; c<entity->GetValues()->GetSize(); c++)
   {
      GRPVECTORFILEDXFValue* value = entity->GetValues()->Get(c);
      if(value)
      {
         if(!value->GetName()->Compare(name, true))
         {
            return value;
         }           
      }           
   }

   return NULL;
}

void GRPVECTORFILEDXFEntityObj::Clean ( )
{
   type = GRPVECTORFILEDXFEntityObjType_Unknown;
   nameType.Empty();

   layerName.Empty();
   lineTypeName.Empty();
   lineColor = 0;  

   typeSpace = 0;

   visibility = false;
}

#pragma endregion
