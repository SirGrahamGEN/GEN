/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       GRPVectorFileDXFEntityObj.cpp
* 
* @class      GRPVECTORFILEDXFENTITYOBJ
* @brief      Graphic Vector File DXF Entity Obj class
* @ingroup    GRAPHIC
* 
* @copyright  GEN Group. All rights reserved.
* 
* @cond
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
* documentation files(the "Software"), to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense, and/ or sell copies of the Software,
* and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of
* the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
* THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
* @endcond
* 
* --------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "GRPVectorFileDXFEntityObj.h"

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

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILEDXFENTITYOBJ::GRPVECTORFILEDXFENTITYOBJ(XCHAR* nametype)
* @brief      Constructor
* @ingroup    GRAPHIC
* 
* @param[in]  XCHAR* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILEDXFENTITYOBJ::GRPVECTORFILEDXFENTITYOBJ(XCHAR* nametype)
{
  Clean();   

  this->nametype = nametype;

  visibility = true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILEDXFENTITYOBJ::~GRPVECTORFILEDXFENTITYOBJ()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    GRAPHIC
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILEDXFENTITYOBJ::~GRPVECTORFILEDXFENTITYOBJ()
{ 
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILEDXFENTITYOBJ* GRPVECTORFILEDXFENTITYOBJ::CreateInstance(GRPVECTORFILEDXFENTITY* entity)
* @brief      CreateInstance
* @ingroup    GRAPHIC
* 
* @param[in]  entity : 
* 
* @return     GRPVECTORFILEDXFENTITYOBJ* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILEDXFENTITYOBJ* GRPVECTORFILEDXFENTITYOBJ::CreateInstance(GRPVECTORFILEDXFENTITY* entity)
{   
  typedef struct
  {
    XCHAR*                          entityname;
    GRPVECTORFILEDXFENTITYOBJTYPE   objtype;
   
  } ENTITY2CLASS;

  ENTITY2CLASS                entity2class[] = {  { __L("3DFACE")           , GRPVECTORFILEDXFENTITYOBJTYPE_3DFACE         },
                                                  { __L("ARC")              , GRPVECTORFILEDXFENTITYOBJTYPE_ARC            },
                                                  { __L("CIRCLE")           , GRPVECTORFILEDXFENTITYOBJTYPE_CIRCLE         },           
                                                  { __L("ACAD_CIRCLE")      , GRPVECTORFILEDXFENTITYOBJTYPE_CIRCLE         },
                                                  { __L("ELLIPSE")          , GRPVECTORFILEDXFENTITYOBJTYPE_ELLIPSE        },
                                                  { __L("LINE")             , GRPVECTORFILEDXFENTITYOBJTYPE_LINE           },
                                                  { __L("LWPOLYLINE")       , GRPVECTORFILEDXFENTITYOBJTYPE_LWPOLYLINE     },
                                                  { __L("MTEXT")            , GRPVECTORFILEDXFENTITYOBJTYPE_MTEXT          },
                                                  { __L("POINT")            , GRPVECTORFILEDXFENTITYOBJTYPE_POINT          },
                                                  { __L("POLYLINE")         , GRPVECTORFILEDXFENTITYOBJTYPE_POLYLINE       },
                                                  { __L("TEXT")             , GRPVECTORFILEDXFENTITYOBJTYPE_TEXT           }
                                               };

  GRPVECTORFILEDXFENTITYOBJ*  entityobj     = NULL; 
  
  if(!entity) 
    {
      return entityobj;
    }

  for(int c=0; c<sizeof(entity2class)/sizeof(ENTITY2CLASS); c++)
    { 
      if(!entity->GetName()->Compare(entity2class[c].entityname, true))
        {
          switch(entity2class[c].objtype)
            {
              case GRPVECTORFILEDXFENTITYOBJTYPE_UNKNOWN      :
                                                 default      : break;
              case GRPVECTORFILEDXFENTITYOBJTYPE_3DFACE       : entityobj = new GRPVECTORFILEDXFENTITYOBJ3DFACE(entity2class[c].entityname);       break; 
              case GRPVECTORFILEDXFENTITYOBJTYPE_ARC          : entityobj = new GRPVECTORFILEDXFENTITYOBJARC(entity2class[c].entityname);          break;            
              case GRPVECTORFILEDXFENTITYOBJTYPE_CIRCLE       : entityobj = new GRPVECTORFILEDXFENTITYOBJCIRCLE(entity2class[c].entityname);       break;          
              case GRPVECTORFILEDXFENTITYOBJTYPE_ELLIPSE      : entityobj = new GRPVECTORFILEDXFENTITYOBJELLIPSE(entity2class[c].entityname);      break;         
              case GRPVECTORFILEDXFENTITYOBJTYPE_LINE         : entityobj = new GRPVECTORFILEDXFENTITYOBJLINE(entity2class[c].entityname);         break;            
              case GRPVECTORFILEDXFENTITYOBJTYPE_LWPOLYLINE   : entityobj = new GRPVECTORFILEDXFENTITYOBJLWPolyLine(entity2class[c].entityname);   break;      
              case GRPVECTORFILEDXFENTITYOBJTYPE_MTEXT        : entityobj = new GRPVECTORFILEDXFENTITYOBJMText(entity2class[c].entityname);        break;           
              case GRPVECTORFILEDXFENTITYOBJTYPE_POINT        : entityobj = new GRPVECTORFILEDXFENTITYOBJPoint(entity2class[c].entityname);        break;           
              case GRPVECTORFILEDXFENTITYOBJTYPE_POLYLINE     : entityobj = new GRPVECTORFILEDXFENTITYOBJPolyLine(entity2class[c].entityname);     break;        
              case GRPVECTORFILEDXFENTITYOBJTYPE_TEXT         : entityobj = new GRPVECTORFILEDXFENTITYOBJText(entity2class[c].entityname);         break;                              
            }
        }
    }

  if(entityobj)
    {
      entityobj->ApplyData(entity);
    }
  
  return entityobj;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILEDXFENTITYOBJTYPE GRPVECTORFILEDXFENTITYOBJ::GetType()
* @brief      GetType
* @ingroup    GRAPHIC
* 
* @return     GRPVECTORFILEDXFENTITYOBJTYPE : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILEDXFENTITYOBJTYPE GRPVECTORFILEDXFENTITYOBJ::GetType()
{
  return type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* GRPVECTORFILEDXFENTITYOBJ::GetNameType()
* @brief      GetNameType
* @ingroup    GRAPHIC
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* GRPVECTORFILEDXFENTITYOBJ::GetNameType()
{
  return &nametype;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* GRPVECTORFILEDXFENTITYOBJ::GetLayerName()
* @brief      GetLayerName
* @ingroup    GRAPHIC
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* GRPVECTORFILEDXFENTITYOBJ::GetLayerName()
{
  return &layername;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int GRPVECTORFILEDXFENTITYOBJ::GetLineColor()
* @brief      GetLineColor
* @ingroup    GRAPHIC
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int GRPVECTORFILEDXFENTITYOBJ::GetLineColor()
{
  return linecolor;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPVECTORFILEDXFENTITYOBJ::SetLineColor(int lineColor)
* @brief      SetLineColor
* @ingroup    GRAPHIC
* 
* @param[in]  lineColor : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVECTORFILEDXFENTITYOBJ::SetLineColor(int lineColor)
{
  this->linecolor = linecolor;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* GRPVECTORFILEDXFENTITYOBJ::GetLineTypeName()
* @brief      GetLineTypeName
* @ingroup    GRAPHIC
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* GRPVECTORFILEDXFENTITYOBJ::GetLineTypeName()
{
  return &linetypename;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int GRPVECTORFILEDXFENTITYOBJ::GetTypeSpace()
* @brief      GetTypeSpace
* @ingroup    GRAPHIC
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int GRPVECTORFILEDXFENTITYOBJ::GetTypeSpace()
{
  return typespace;
}
 

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPVECTORFILEDXFENTITYOBJ::SetTypeSpace(int typeSpace)
* @brief      SetTypeSpace
* @ingroup    GRAPHIC
* 
* @param[in]  typeSpace : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVECTORFILEDXFENTITYOBJ::SetTypeSpace(int typeSpace)
{
  this->typespace = typespace;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPVECTORFILEDXFENTITYOBJ::GetVisibility()
* @brief      GetVisibility
* @ingroup    GRAPHIC
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPVECTORFILEDXFENTITYOBJ::GetVisibility()
{
  return visibility;
}
      
     
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPVECTORFILEDXFENTITYOBJ::SetVisibility(bool visibility)
* @brief      SetVisibility
* @ingroup    GRAPHIC
* 
* @param[in]  visibility : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVECTORFILEDXFENTITYOBJ::SetVisibility(bool visibility)
{
  this->visibility = visibility;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPVECTORFILEDXFENTITYOBJ::ApplyData(GRPVECTORFILEDXFENTITY* entity)
* @brief      ApplyData
* @ingroup    GRAPHIC
* 
* @param[in]  entity : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPVECTORFILEDXFENTITYOBJ::ApplyData(GRPVECTORFILEDXFENTITY* entity)
{
  GRPVECTORFILEDXFVALUE* value;
   
  value = GetDataValue(__L("G_LAYER_NAME"), entity);   
  if(value) 
    {
      layername.Set((XCHAR*)(*value->GetData()));
    }

  value = GetDataValue(__L("G_COLOR_NUMBER"), entity);   
  if(value) 
    {
      linecolor = (int)(*value->GetData());
    }

  value = GetDataValue(__L("G_LINETYPE_NAME"), entity);      
  if(value) 
    {
      linetypename.Set((XCHAR*)(*value->GetData()));
    }

  value = GetDataValue(__L("G_TYPE_SPACE"), entity);      
  if(value) 
    {
      typespace = (int)(*value->GetData());
    }

  value = GetDataValue(__L("G_ENTITY_VISIBILITY"), entity);      
  if(value) 
    {
      visibility = ((int)(*value->GetData()))?false:true;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILEDXFVALUE* GRPVECTORFILEDXFENTITYOBJ::GetDataValue(int type, GRPVECTORFILEDXFENTITY* entity)
* @brief      GetDataValue
* @ingroup    GRAPHIC
* 
* @param[in]  type : 
* @param[in]  entity : 
* 
* @return     GRPVECTORFILEDXFVALUE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILEDXFVALUE* GRPVECTORFILEDXFENTITYOBJ::GetDataValue(int type, GRPVECTORFILEDXFENTITY* entity)
{
  if(!entity) 
    {
      return NULL;
    }

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


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILEDXFVALUE* GRPVECTORFILEDXFENTITYOBJ::GetDataValue(XCHAR* name, GRPVECTORFILEDXFENTITY* entity)
* @brief      GetDataValue
* @ingroup    GRAPHIC
* 
* @param[in]  name : 
* @param[in]  entity : 
* 
* @return     GRPVECTORFILEDXFVALUE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILEDXFVALUE* GRPVECTORFILEDXFENTITYOBJ::GetDataValue(XCHAR* name, GRPVECTORFILEDXFENTITY* entity)
{
  if(!entity) 
    {
      return NULL;
    }

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


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPVECTORFILEDXFENTITYOBJ::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    GRAPHIC
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVECTORFILEDXFENTITYOBJ::Clean()
{
  type        = GRPVECTORFILEDXFENTITYOBJTYPE_UNKNOWN;
  
  nametype.Empty();
  layername.Empty();
  linetypename.Empty();

  linecolor   = 0;  

  typespace   = 0;

  visibility  = false;
}

#pragma endregion
