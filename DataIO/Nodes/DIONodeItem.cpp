/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIONodeItem.cpp
* 
* @class      DIONODEITEM
* @brief      Data Input/Output Node item (Base for DIONODESENSOR, DIONODEACTUATOR, ...) class
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

#include "DIONodeItem.h"

#include "XFactory.h"

#include "DIONodeItemHandler.h"

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
* @fn         DIONODEITEM::DIONODEITEM()
* @brief      Constructor of class
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEITEM::DIONODEITEM()
{
  Clean();

  UUID.GenerateRandom();

  updatetimer = GEN_XFACTORY.CreateTimer();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEITEM::DIONODEITEM(DIONODEITEMHANDLER* itemhandler)
* @brief      Constructor of class
* @ingroup    DATAIO
* 
* @param[in]  itemhandler : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEITEM::DIONODEITEM(DIONODEITEMHANDLER* itemhandler)
{
  Clean();

  UUID.GenerateRandom();

  updatetimer = GEN_XFACTORY.CreateTimer();

  ItemHandler_Set(itemhandler);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEITEM::~DIONODEITEM()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEITEM::~DIONODEITEM()

{
  ItemHandler_Close();  

  values.DeleteContents();
  values.DeleteAll();    

  if(updatetimer)
    {
      GEN_XFACTORY.DeleteTimer(updatetimer);
    }

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIONODEITEM::GetCategory()
* @brief      Get category
* @ingroup    DATAIO
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIONODEITEM::GetCategory()
{
  return category;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEITEM::SetCategory(XDWORD category)
* @brief      Set category
* @ingroup    DATAIO
* 
* @param[in]  category : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEM::SetCategory(XDWORD category)
{
  this->category = category;

  switch(category)
    {
      case DIONODEITEM_CATEGORY_UNKNOWN                    : description = __L("unknown");                          break;
      case DIONODEITEM_CATEGORY_SENSORHUMIDITYTEMPERATURE  : description = __L("Sensor Humidity/Temperature");      break;
      case DIONODEITEM_CATEGORY_GPIO_DIGITAL               : description = __L("GPIO Digital");                     break; 
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* DIONODEITEM::GetDescription()
* @brief      Get description
* @ingroup    DATAIO
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIONODEITEM::GetDescription()
{
  return &description;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XUUID& DIONODEITEM::GetID()
* @brief      Get ID
* @ingroup    DATAIO
* 
* @return     XUUID& : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XUUID& DIONODEITEM::GetID()
{
  return UUID;
}
 

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEITEM::SetID(XUUID& UUID)
* @brief      Set ID
* @ingroup    DATAIO
* 
* @param[in]  UUID : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEM::SetID(XUUID& UUID)
{
  UUID.CopyTo(this->UUID);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEITEMHANDLER* DIONODEITEM::ItemHandler_Get()
* @brief      Item handler get
* @ingroup    DATAIO
* 
* @return     DIONODEITEMHANDLER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEITEMHANDLER* DIONODEITEM::ItemHandler_Get()
{
  return itemhandler;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEM::ItemHandler_Set(DIONODEITEMHANDLER* itemhandler)
* @brief      Item handler set
* @ingroup    DATAIO
* 
* @param[in]  itemhandler : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEM::ItemHandler_Set(DIONODEITEMHANDLER* itemhandler)
{
  this->itemhandler = itemhandler;

  if(!itemhandler->SetNodeItem(this))
    { 
      return false;
    }

  if(!ItemHandler_Open())       
    {
      return false;      
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEM::ItemHandler_Open()
* @brief      Item handler open
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEM::ItemHandler_Open()
{
  if(!itemhandler)               
    {
      return false;  
    }
  
  if(itemhandler->IsOpen())      
    {
      itemhandler->Close();      
    }

  if(!itemhandler->Open())       
    {
      return false;
    }

  if(!itemhandler->IsWorking())  
    {
      return false;      
    }
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEM::ItemHandler_Close()
* @brief      Item handler close
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEM::ItemHandler_Close()
{
  if(!itemhandler)              
    {
      return false;  
    }

  if(!itemhandler->Close())     
    {
      return false;
    }

  if(itemhandler->IsWorking())  
    {
      return false;      
    }
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEM::IsSimulate()
* @brief      Is simulate
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEM::IsSimulate()
{
  return issimulated;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEITEM::SetIsSimulate(bool issimulated)
* @brief      Set is simulate
* @ingroup    DATAIO
* 
* @param[in]  issimulated : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEM::SetIsSimulate(bool issimulated)
{
  this->issimulated = issimulated;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XQWORD DIONODEITEM::GetTimeToUpdate()
* @brief      Get time to update
* @ingroup    DATAIO
* 
* @return     XQWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XQWORD DIONODEITEM::GetTimeToUpdate()
{
  return timetoupdate;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEITEM::SetTimeToUpdate(XQWORD timetoupdate)
* @brief      Set time to update
* @ingroup    DATAIO
* 
* @param[in]  timetoupdate : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEM::SetTimeToUpdate(XQWORD timetoupdate)
{
  this->timetoupdate = timetoupdate;

  if(updatetimer)
    {
      updatetimer->Reset();
      updatetimer->AddMilliSeconds(timetoupdate);
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XTIMER* DIONODEITEM::GetUpdateTimer()
* @brief      Get update timer
* @ingroup    DATAIO
* 
* @return     XTIMER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XTIMER* DIONODEITEM::GetUpdateTimer()
{
  return updatetimer;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<DIONODEITEMVALUE*>* DIONODEITEM::GetValues()
* @brief      Get values
* @ingroup    DATAIO
* 
* @return     XVECTOR<DIONODEITEMVALUE*>* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<DIONODEITEMVALUE*>* DIONODEITEM::GetValues()
{
  return &values;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEM::Update()
* @brief      Update
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEM::Update()
{
  if(!itemhandler)              
    {
      return false;  
    }

  bool status = false;  
  
  if(updatetimer)
    {
      if(updatetimer->GetMeasureMilliSeconds() > timetoupdate)  
        {
          status = itemhandler->Update();
          updatetimer->Reset();
        }
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEM::Serialize()
* @brief      Serialize
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEM::Serialize()
{
  XSTRING ID;
  
  UUID.GetToString(ID); 
  
  Primitive_Add<XSTRING*>(&ID, __L("ID"));
  Primitive_Add<int>(category, __L("category"));
  Primitive_Add<XSTRING*>(&description, __L("description"));
  Primitive_Add<bool>(issimulated, __L("simulated"));
  Primitive_Add<XQWORD>(timetoupdate, __L("timetoupdate"));

  DIONODEITEMHANDLER* itemhandler =  ItemHandler_Get();
  if(itemhandler)
    {
      Primitive_Add<int>(itemhandler->GetType(), __L("handler_type"));
      Primitive_Add<XSTRING*>(itemhandler->GetName(), __L("handler_name"));
    }

  XVectorClass_Add<DIONODEITEMVALUE>(&values, __L("values"), __L("value"));  
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEM::Deserialize()
* @brief      Deserialize
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEM::Deserialize()
{   
  XSTRING ID;

  Primitive_Extract<XSTRING&>(ID, __L("ID"));
  Primitive_Extract<int>(category, __L("category"));
  Primitive_Extract<XSTRING&>(description, __L("description"));
  Primitive_Extract<bool>(issimulated, __L("simulated"));
  Primitive_Extract<XQWORD>(timetoupdate, __L("timetoupdate"));

  DIONODEITEMHANDLER* itemhandler =  ItemHandler_Get();
  if(itemhandler)
    {
      Primitive_Extract<int>(itemhandler->GetType(), __L("handler_type"));
      Primitive_Extract<XSTRING&>((*itemhandler->GetName()), __L("handler_name"));
    }

  XVectorClass_Extract<DIONODEITEMVALUE>(&values, __L("values"), __L("value"));  
  
  UUID.SetFromString(ID);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEITEM::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEM::Clean()
{
  category      = DIONODEITEM_CATEGORY_UNKNOWN;

  itemhandler   = NULL;

  issimulated   = false;

  timetoupdate  = 0;
  updatetimer   = NULL;
}


#pragma endregion

