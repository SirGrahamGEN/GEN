/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       GRPVectorFileDXFTextBlock.cpp
* 
* @class      GRPVECTORFILEDXFTEXTBLOCK
* @brief      Graphic Vector File DXF Text Block class
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

#include "GRPVectorFileDXFTextBlock.h"

#include "XMap.h"
#include "XVariant.h"

#include "GRPVectorFileDXF.h"

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
* @fn         GRPVECTORFILEDXFTEXTBLOCK::GRPVECTORFILEDXFTEXTBLOCK()
* @brief      Constructor of class
* @ingroup    GRAPHIC
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILEDXFTEXTBLOCK::GRPVECTORFILEDXFTEXTBLOCK()
{
  Clean();   
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILEDXFTEXTBLOCK::~GRPVECTORFILEDXFTEXTBLOCK()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    GRAPHIC
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILEDXFTEXTBLOCK::~GRPVECTORFILEDXFTEXTBLOCK()
{
  DeleteAllValues();

  if(entitiessection)
    {
      delete entitiessection;
    }

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* GRPVECTORFILEDXFTEXTBLOCK::GetName()
* @brief      Get name
* @ingroup    GRAPHIC
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* GRPVECTORFILEDXFTEXTBLOCK::GetName()
{
  return &name;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPVECTORFILEDXFTEXTBLOCK::IsEndBlock()
* @brief      Is end block
* @ingroup    GRAPHIC
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPVECTORFILEDXFTEXTBLOCK::IsEndBlock()
{
  return isendblock;
}
   
   
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPVECTORFILEDXFTEXTBLOCK::SetIsEndBlock(bool isendblock)
* @brief      Set is end block
* @ingroup    GRAPHIC
* 
* @param[in]  isendblock : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVECTORFILEDXFTEXTBLOCK::SetIsEndBlock(bool isendblock)
{
  this->isendblock = isendblock;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPVECTORFILEDXFTEXTBLOCK::AddValue(GRPVECTORFILEDXFVALUE* value)
* @brief      Add value
* @ingroup    GRAPHIC
* 
* @param[in]  value : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPVECTORFILEDXFTEXTBLOCK::AddValue(GRPVECTORFILEDXFVALUE* value)
{    
  values.Add(value);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<GRPVECTORFILEDXFVALUE*>* GRPVECTORFILEDXFTEXTBLOCK::GetValues()
* @brief      Get values
* @ingroup    GRAPHIC
* 
* @return     XVECTOR<GRPVECTORFILEDXFVALUE*>* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<GRPVECTORFILEDXFVALUE*>* GRPVECTORFILEDXFTEXTBLOCK::GetValues()
{
  return &values;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILEDXFVALUE* GRPVECTORFILEDXFTEXTBLOCK::GetValue(int index)
* @brief      Get value
* @ingroup    GRAPHIC
* 
* @param[in]  index : 
* 
* @return     GRPVECTORFILEDXFVALUE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILEDXFVALUE* GRPVECTORFILEDXFTEXTBLOCK::GetValue(int index)
{
  if(values.IsEmpty()) 
    {
      return NULL;
    }

  return values.Get(index);   
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPVECTORFILEDXFTEXTBLOCK::DeleteValue(int index)
* @brief      Delete value
* @ingroup    GRAPHIC
* 
* @param[in]  index : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPVECTORFILEDXFTEXTBLOCK::DeleteValue(int index)
{
  if(values.IsEmpty()) 
    {
      return false;
    }

  return values.Delete(GetValue(index));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool GRPVECTORFILEDXFTEXTBLOCK::DeleteAllValues()
* @brief      Delete all values
* @ingroup    GRAPHIC
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPVECTORFILEDXFTEXTBLOCK::DeleteAllValues()
{
  if(values.IsEmpty()) 
    {
      return false;
    }

  values.DeleteContents();
  values.DeleteAll(); 

  xdatactrllist.DeleteContents();
  xdatactrllist.DeleteAll();
      
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<GRPVECTORFILEDXFXDATACTRL*>* GRPVECTORFILEDXFTEXTBLOCK::GetXDataCtrlList()
* @brief      Get X data ctrl list
* @ingroup    GRAPHIC
* 
* @return     XVECTOR<GRPVECTORFILEDXFXDATACTRL*>* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<GRPVECTORFILEDXFXDATACTRL*>* GRPVECTORFILEDXFTEXTBLOCK::GetXDataCtrlList()
{
  return &xdatactrllist;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         GRPVECTORFILEDXFTEXTSECTIONENTITIES* GRPVECTORFILEDXFTEXTBLOCK::GetSectionEntities()
* @brief      Get section entities
* @ingroup    GRAPHIC
* 
* @return     GRPVECTORFILEDXFTEXTSECTIONENTITIES* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
GRPVECTORFILEDXFTEXTSECTIONENTITIES* GRPVECTORFILEDXFTEXTBLOCK::GetSectionEntities()
{
  return entitiessection;
}
      
      
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPVECTORFILEDXFTEXTBLOCK::SetSectionEntities(GRPVECTORFILEDXFTEXTSECTIONENTITIES* section)
* @brief      Set section entities
* @ingroup    GRAPHIC
* 
* @param[in]  section : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVECTORFILEDXFTEXTBLOCK::SetSectionEntities(GRPVECTORFILEDXFTEXTSECTIONENTITIES* section)
{
  this->entitiessection = section;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void GRPVECTORFILEDXFTEXTBLOCK::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    GRAPHIC
* 
* --------------------------------------------------------------------------------------------------------------------*/
void GRPVECTORFILEDXFTEXTBLOCK::Clean()
{
  isendblock        = false;
  entitiessection   = NULL;
}


#pragma endregion

