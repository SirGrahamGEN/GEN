/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIONodeItemHandler.cpp
* 
* @class      DIONODEITEMHANDLER
* @brief      Data Input/Output Node Item Handler class
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

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIONodeItemHandler.h"

#include "DIONode_XEvent.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEITEMHANDLER::DIONODEITEMHANDLER()
* @brief      Constructor
* @ingroup    DATAIO
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEITEMHANDLER::DIONODEITEMHANDLER()
{
  Clean();

  RegisterEvent(DIONODE_XEVENT_TYPE_UPDATEVALUE);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEITEMHANDLER::~DIONODEITEMHANDLER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEITEMHANDLER::~DIONODEITEMHANDLER()
{
  DeRegisterEvent(DIONODE_XEVENT_TYPE_UPDATEVALUE);

  Close();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIONODEITEMHANDLER::GetType()
* @brief      GetType
* @ingroup    DATAIO
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIONODEITEMHANDLER::GetType()
{
  return type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* DIONODEITEMHANDLER::GetName()
* @brief      GetName
* @ingroup    DATAIO
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIONODEITEMHANDLER::GetName()
{
  return &name;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEMHANDLER::Open()
* @brief      Open
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEMHANDLER::Open()
{
  isopen = true;

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEMHANDLER::Update()
* @brief      Update
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEMHANDLER::Update()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEMHANDLER::Close()
* @brief      Close
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEMHANDLER::Close()
{
  isopen = false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEMHANDLER::IsOpen()
* @brief      IsOpen
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEMHANDLER::IsOpen()
{
  return isopen;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEMHANDLER::IsWorking()
* @brief      IsWorking
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEMHANDLER::IsWorking()
{
  return isworking;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEITEM* DIONODEITEMHANDLER::GetNodeItem()
* @brief      GetNodeItem
* @ingroup    DATAIO
* 
* @return     DIONODEITEM* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEITEM* DIONODEITEMHANDLER::GetNodeItem()
{
  return nodeitem;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEMHANDLER::SetNodeItem(DIONODEITEM* nodeitem)
* @brief      SetNodeItem
* @ingroup    DATAIO
* 
* @param[in]  nodeitem : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEMHANDLER::SetNodeItem(DIONODEITEM* nodeitem)
{
  if(!nodeitem) return false;

  this->nodeitem = nodeitem;

  nodeitem->GetValues()->DeleteContents();
  nodeitem->GetValues()->DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEITEMHANDLER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEMHANDLER::Clean()
{
  isopen      = false;
  isworking   = false; 

  nodeitem    = NULL;
}


#pragma endregion

