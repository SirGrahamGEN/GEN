/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XBER_XEVENT.cpp
* 
* @class      XBER_XEVENT
* @brief      eXtended Utils XBER XEvent class
* @ingroup    XUTILS
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

#include "XBER_XEvent.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

XBER_XEVENT  XBER_XEVENT::beforeevent;

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBER_XEVENT::XBER_XEVENT()
* @brief      Constructor
* @ingroup    XUTILS
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBER_XEVENT::XBER_XEVENT() : XEVENT(NULL, 0, 0)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBER_XEVENT::XBER_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family)
* @brief      Constructor
* @ingroup    XUTILS
*
* @param[in]  subject :
* @param[in]  type :
* @param[in]  family :
*
* --------------------------------------------------------------------------------------------------------------------*/
XBER_XEVENT::XBER_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family): XEVENT(subject, type, family)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBER_XEVENT::~XBER_XEVENT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XBER_XEVENT::~XBER_XEVENT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int XBER_XEVENT::GetLevel()
* @brief      GetLevel
* @ingroup    XUTILS
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int XBER_XEVENT::GetLevel()
{
  return level;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XBER_XEVENT::SetLevel(int level)
* @brief      SetLevel
* @ingroup    XUTILS
* 
* @param[in]  level : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XBER_XEVENT::SetLevel(int level)
{
  this->level = level;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD* XBER_XEVENT::GetLevels()
* @brief      GetLevels
* @ingroup    XUTILS
* 
* @return     XDWORD* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD* XBER_XEVENT::GetLevels()
{
  return levels;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* XBER_XEVENT::GetLevelsString()
* @brief      GetLevelsString
* @ingroup    XUTILS
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* XBER_XEVENT::GetLevelsString()
{
  return &levelsstr;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* XBER_XEVENT::GetLine()
* @brief      GetLine
* @ingroup    XUTILS
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* XBER_XEVENT::GetLine()
{
  return &line;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBUFFER* XBER_XEVENT::GetData()
* @brief      GetData
* @ingroup    XUTILS
* 
* @return     XBUFFER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBUFFER* XBER_XEVENT::GetData()
{
  return &data; 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBYTE XBER_XEVENT::GetTagType()
* @brief      GetTagType
* @ingroup    XUTILS
* 
* @return     XBYTE : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE XBER_XEVENT::GetTagType()
{
  return tagtype;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XBER_XEVENT::SetTagType(XBYTE tagtype)
* @brief      SetTagType
* @ingroup    XUTILS
* 
* @param[in]  tagtype : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XBER_XEVENT::SetTagType(XBYTE tagtype)
{
  this->tagtype = tagtype;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* XBER_XEVENT::GetTagTypeName(XSTRING& name)
* @brief      GetTagTypeName
* @ingroup    XUTILS
* 
* @param[in]  name : 
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* XBER_XEVENT::GetTagTypeName()
{
  return &tagtypename;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBER_TAGCLASS XBER_XEVENT::GetTagClass()
* @brief      GetTagClass
* @ingroup    XUTILS
* 
* @return     XBER_TAGCLASS : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBER_TAGCLASS XBER_XEVENT::GetTagClass()
{
  return tagclass;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XBER_XEVENT::SetTagClass(XBER_TAGCLASS tagclass)
* @brief      SetTagClass
* @ingroup    XUTILS
* 
* @param[in]  tagclass : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XBER_XEVENT::SetTagClass(XBER_TAGCLASS tagclass)
{
  this->tagclass = tagclass;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XASN1_OID_PROPERTY* XBER_XEVENT::GetProperty()
* @brief      GetProperty
* @ingroup    XUTILS
* 
* @return     XASN1_OID_PROPERTY* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XASN1_OID_PROPERTY* XBER_XEVENT::GetProperty()
{
  return property;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XBER_XEVENT::SetProperty(XASN1_OID_PROPERTY* property)
* @brief      SetProperty
* @ingroup    XUTILS
* 
* @param[in]  property : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XBER_XEVENT::SetProperty(XASN1_OID_PROPERTY* property)
{
  this->property = property;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVARIANT* XBER_XEVENT::GetValue()
* @brief      GetValue
* @ingroup    XUTILS
* 
* @return     XVARIANT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVARIANT* XBER_XEVENT::GetValue()
{
  return &value;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XBER_XEVENT::GetStatus()
* @brief      GetStatus
* @ingroup    XUTILS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XBER_XEVENT::GetStatus()
{
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XBER_XEVENT::SetStatus(bool status)
* @brief      SetStatus
* @ingroup    XUTILS
* 
* @param[in]  status : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XBER_XEVENT::SetStatus(bool status)
{
  this->status = status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBER_XEVENT* XBER_XEVENT::GetBeforeEvent()
* @brief      GetBeforeEvent
* @ingroup    XUTILS
* 
* @return     XBER_XEVENT* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBER_XEVENT* XBER_XEVENT::GetBeforeEvent()
{
  return &beforeevent;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XBER_XEVENT::SetBeforeEvent(XBER_XEVENT& event)
* @brief      SetBeforeEvent
* @ingroup    XUTILS
* 
* @param[in]  event : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XBER_XEVENT::SetBeforeEvent(XBER_XEVENT& event)
{
  XBER_XEVENT::beforeevent.SetLevel(event.GetLevel());    

  memcpy(XBER_XEVENT::beforeevent.GetLevels(), event.GetLevels(), (sizeof(XDWORD) * XBER_MAXLEVELS));
  XBER_XEVENT::beforeevent.GetLevelsString()->Set(event.GetLevelsString()->Get());

  XBER_XEVENT::beforeevent.GetLine()->Set(event.GetLine()->Get());

  XBER_XEVENT::beforeevent.GetData()->CopyFrom((*event.GetData()));

  XBER_XEVENT::beforeevent.SetTagType(event.GetTagType());    
  
  XBER_XEVENT::beforeevent.GetTagTypeName()->Set(event.GetTagTypeName()->Get());

  XBER_XEVENT::beforeevent.SetTagClass(event.GetTagClass());    

  XBER_XEVENT::beforeevent.SetProperty(event.GetProperty());    

  (*XBER_XEVENT::beforeevent.GetValue()) = (*event.GetValue());

  XBER_XEVENT::beforeevent.SetStatus(event.GetStatus());    

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XBER_XEVENT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XBER_XEVENT::Clean()
{
  level     = 0;

  memset(levels, 0, (sizeof(XDWORD) * XBER_MAXLEVELS));
  
  tagtype   = XBER_TAGTYPE_RESERVEDBER;
  tagclass  = XBER_TAGCLASS_UNKNOWN;

  property  = NULL;

  status    = false; 
}


#pragma endregion

