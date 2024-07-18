#pragma region INCLUDES

#include "GRPVectorFileDXFEntityObj3DFace.h"
#include "GRPVectorFileDXFEntityObjArc.h"
#include "GRPVectorFileDXFEntityObjCircle.h"
#include "GRPVectorFileDXFEntityObjEllipse.h"
#include "GRPVectorFileDXFEntityObjLine.h"
#include "GRPVectorFileDXFEntityObjLWPolyLine.h"
#include "GRPVectorFileDXFEntityObjMText.h"
#include "GRPVectorFileDXFEntityObjPolyLine.h"
#include "GRPVectorFileDXFEntityObjPoint.h"
#include "GRPVectorFileDXFEntityObjText.h"

#include "GRPVectorFileDXFEntityObj.h"

#pragma endregion


#pragma region GENERAL_VARIABLES
#pragma endregion


#pragma region CLASS_MEMBERS

GRPVECTORFILEDXFENTITYObj::GRPVECTORFILEDXFENTITYObj (XCHAR* nameType)
{
   Clean();   

   this->nameType = nameType;

   visibility = true;
}


GRPVECTORFILEDXFENTITYObj::~GRPVECTORFILEDXFENTITYObj ( )
{ 
   Clean();
}

GRPVECTORFILEDXFENTITYObj* GRPVECTORFILEDXFENTITYObj::CreateInstance(GRPVECTORFILEDXFENTITY* entity)
{   
   typedef struct
   {
      XCHAR* entityName;
      GRPVECTORFILEDXFENTITYObjType objType;
   
   } ENTITY2CLASS;

   ENTITY2CLASS entity2class[] = { { __L("3DFACE")           , GRPVECTORFILEDXFENTITYObjType_3DFace         },
                                   { __L("ARC")              , GRPVECTORFILEDXFENTITYObjType_Arc            },
                                   { __L("CIRCLE")           , GRPVECTORFILEDXFENTITYObjType_Circle         },           
                                   { __L("ACAD_CIRCLE")      , GRPVECTORFILEDXFENTITYObjType_Circle         },
                                   { __L("ELLIPSE")          , GRPVECTORFILEDXFENTITYObjType_Ellipse        },
                                   { __L("LINE")             , GRPVECTORFILEDXFENTITYObjType_Line           },
                                   { __L("LWPOLYLINE")       , GRPVECTORFILEDXFENTITYObjType_LWPolyLine     },
                                   { __L("MTEXT")            , GRPVECTORFILEDXFENTITYObjType_MText          },
                                   { __L("POINT")            , GRPVECTORFILEDXFENTITYObjType_Point          },
                                   { __L("POLYLINE")         , GRPVECTORFILEDXFENTITYObjType_PolyLine       },
                                   { __L("TEXT")             , GRPVECTORFILEDXFENTITYObjType_Text           }
                                 };

   GRPVECTORFILEDXFENTITYObj* entityObj = NULL; 
  
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
            case GRPVECTORFILEDXFENTITYObjType_Unknown      :
                                            default      : break;
            case GRPVECTORFILEDXFENTITYObjType_3DFace       : entityObj = new GRPVECTORFILEDXFENTITYObj3DFace(entity2class[c].entityName);       break; 
            case GRPVECTORFILEDXFENTITYObjType_Arc          : entityObj = new GRPVECTORFILEDXFENTITYObjArc(entity2class[c].entityName);          break;            
            case GRPVECTORFILEDXFENTITYObjType_Circle       : entityObj = new GRPVECTORFILEDXFENTITYObjCircle(entity2class[c].entityName);       break;          
            case GRPVECTORFILEDXFENTITYObjType_Ellipse      : entityObj = new GRPVECTORFILEDXFENTITYObjEllipse(entity2class[c].entityName);      break;         
            case GRPVECTORFILEDXFENTITYObjType_Line         : entityObj = new GRPVECTORFILEDXFENTITYObjLine(entity2class[c].entityName);         break;            
            case GRPVECTORFILEDXFENTITYObjType_LWPolyLine   : entityObj = new GRPVECTORFILEDXFENTITYObjLWPolyLine(entity2class[c].entityName);   break;      
            case GRPVECTORFILEDXFENTITYObjType_MText        : entityObj = new GRPVECTORFILEDXFENTITYObjMText(entity2class[c].entityName);        break;           
            case GRPVECTORFILEDXFENTITYObjType_Point        : entityObj = new GRPVECTORFILEDXFENTITYObjPoint(entity2class[c].entityName);        break;           
            case GRPVECTORFILEDXFENTITYObjType_PolyLine     : entityObj = new GRPVECTORFILEDXFENTITYObjPolyLine(entity2class[c].entityName);     break;        
            case GRPVECTORFILEDXFENTITYObjType_Text         : entityObj = new GRPVECTORFILEDXFENTITYObjText(entity2class[c].entityName);         break;                              
         }
      }
   }

   if(entityObj)
   {
      entityObj->ApplyData(entity);
   }
  
   return entityObj;
}


GRPVECTORFILEDXFENTITYObjType GRPVECTORFILEDXFENTITYObj::GetType()
{
   return type;
}


XSTRING* GRPVECTORFILEDXFENTITYObj::GetNameType()
{
   return &nameType;
}


XSTRING* GRPVECTORFILEDXFENTITYObj::GetLayerName ( )
{
   return &layerName;
}


int GRPVECTORFILEDXFENTITYObj::GetLineColor ( )
{
   return lineColor;
}


void GRPVECTORFILEDXFENTITYObj::SetLineColor (int lineColor)
{
   this->lineColor = lineColor;
}


XSTRING* GRPVECTORFILEDXFENTITYObj::GetLineTypeName ( )
{
   return &lineTypeName;
}


int GRPVECTORFILEDXFENTITYObj::GetTypeSpace ()
{
   return typeSpace;
}
 

void GRPVECTORFILEDXFENTITYObj::SetTypeSpace (int typeSpace)
{
   this->typeSpace = typeSpace;
}


bool GRPVECTORFILEDXFENTITYObj::GetVisibility()
{
   return visibility;
}
      
     
void GRPVECTORFILEDXFENTITYObj::SetVisibility(bool visibility)
{
   this->visibility = visibility;
}


bool GRPVECTORFILEDXFENTITYObj::ApplyData(GRPVECTORFILEDXFENTITY* entity)
{
   GRPVECTORFILEDXFVALUE* value;
   
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


GRPVECTORFILEDXFVALUE* GRPVECTORFILEDXFENTITYObj::GetDataValue(int type, GRPVECTORFILEDXFENTITY* entity)
{
   if(!entity) return NULL;

   for(XDWORD c=0; c<entity->GetValues()->GetSize(); c++)
   {
      GRPVECTORFILEDXFVALUE* value = entity->GetValues()->Get(c);
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


GRPVECTORFILEDXFVALUE* GRPVECTORFILEDXFENTITYObj::GetDataValue(XCHAR* name, GRPVECTORFILEDXFENTITY* entity)
{
   if(!entity) return NULL;

   for(XDWORD c=0; c<entity->GetValues()->GetSize(); c++)
   {
      GRPVECTORFILEDXFVALUE* value = entity->GetValues()->Get(c);
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

void GRPVECTORFILEDXFENTITYObj::Clean ( )
{
   type = GRPVECTORFILEDXFENTITYObjType_Unknown;
   nameType.Empty();

   layerName.Empty();
   lineTypeName.Empty();
   lineColor = 0;  

   typeSpace = 0;

   visibility = false;
}

#pragma endregion
