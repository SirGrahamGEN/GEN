/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIONode_XEvent.cpp
* 
* @class      DIONODE_XEVENT
* @brief      Data Input/Output Node eXtended Event class
* @ingroup    DATAIO
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

#include "DIONode_XEvent.h"

#include "DIONodeItem.h"

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
* @fn         void DIONODE_XEVENT::DIONODE_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family)
* @brief      Constructor of class
* @ingroup    DATAIO
*
* @param[in]  subject :
* @param[in]  type :
* @param[in]  family :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIONODE_XEVENT::DIONODE_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family): XEVENT(subject, type, family)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODE_XEVENT::~DIONODE_XEVENT()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODE_XEVENT::~DIONODE_XEVENT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEITEM* DIONODE_XEVENT::GetNodeItem()
* @brief      Get node item
* @ingroup    DATAIO
* 
* @return     DIONODEITEM* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEITEM* DIONODE_XEVENT::GetNodeItem()
{
  return nodeitem;
}
 
   
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODE_XEVENT::SetNodeItem(DIONODEITEM* nodeitem)
* @brief      Set node item
* @ingroup    DATAIO
* 
* @param[in]  nodeitem : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODE_XEVENT::SetNodeItem(DIONODEITEM* nodeitem)
{
  this->nodeitem = nodeitem;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIONODE_XEVENT::GetIndexValue()
* @brief      Get index value
* @ingroup    DATAIO
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIONODE_XEVENT::GetIndexValue()
{
  return indexvalue;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODE_XEVENT::SetIndexValue(XDWORD indexvalue)
* @brief      Set index value
* @ingroup    DATAIO
* 
* @param[in]  indexvalue : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODE_XEVENT::SetIndexValue(XDWORD indexvalue)
{
  this->indexvalue = indexvalue;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIONODE_XEVENT::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODE_XEVENT::Clean()
{
   nodeitem     = NULL;
   indexvalue   = 0;  
}


#pragma endregion

