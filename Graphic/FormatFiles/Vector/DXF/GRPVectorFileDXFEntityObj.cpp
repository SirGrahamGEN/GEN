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
#pragma region PRECOMPILATION_DEFINES_INCLUDE

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

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILEDXFENTITYOBJ::GRPVECTORFILEDXFENTITYOBJ(XCHAR* nametype)
* @brief      Constructor of class
* @ingroup    GRAPHIC
* 
* @param[in]  nametype : 
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
* @brief      Destructor of class
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
* @brief      Create instance
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
              case GRPVECTORFILEDXFENTITYOBJTYPE_LWPOLYLINE   : entityobj = new GRPVECTORFILEDXFENTITYOBJLWPOLYLINE(entity2class[c].entityname);   break;      
              case GRPVECTORFILEDXFENTITYOBJTYPE_MTEXT        : entityobj = new GRPVECTORFILEDXFENTITYOBJMTEXT(entity2class[c].entityname);        break;           
              case GRPVECTORFILEDXFENTITYOBJTYPE_POINT        : entityobj = new GRPVECTORFILEDXFENTITYOBJPOINT(entity2class[c].entityname);        break;           
              case GRPVECTORFILEDXFENTITYOBJTYPE_POLYLINE     : entityobj = new GRPVECTORFILEDXFENTITYOBJPOLYLINE(entity2class[c].entityname);     break;        
              case GRPVECTORFILEDXFENTITYOBJTYPE_TEXT         : entityobj = new GRPVECTORFILEDXFENTITYOBJTEXT(entity2class[c].entityname);         break;                              
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
* @brief      Get type
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
* @brief      Get name type
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
* @brief      Get layer name
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
* @brief      Get line color
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
* @fn         void GRPVECTORFILEDXFENTITYOBJ::SetLineColor(int linecolor)
* @brief      Set line color
* @ingroup    GRAPHIC
* 
* @param[in]  linecolor : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVECTORFILEDXFENTITYOBJ::SetLineColor(int linecolor)
{
  this->linecolor = linecolor;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* GRPVECTORFILEDXFENTITYOBJ::GetLineTypeName()
* @brief      Get line type name
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
* @brief      Get type space
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
* @brief      Set type space
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
* @brief      Get visibility
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
* @brief      Set visibility
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
* @brief      Apply data
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
* @brief      Get data value
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
* @brief      Get data value
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
* @brief      Clean the attributes of the class: Default initialize
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
