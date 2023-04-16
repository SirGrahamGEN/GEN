/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIONodeItem.cpp
* 
* @class      DIONODEITEM
* @brief      Data Input/Output Node Item (Base for DIONODESENSOR, DIONODEACTUATOR, ...)
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XFactory.h"

#include "DIONodeItemDriver.h"

#include "DIONodeItem.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEITEM::DIONODEITEM()
* @brief      Constructor
* @ingroup    
* 
* @return     Does not return anything. 
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
* @fn         DIONODEITEM::~DIONODEITEM()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEITEM::~DIONODEITEM()
{
  ItemDriver_Close();  

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
* @fn         XDWORD DIONODEITEM::GetType()
* @brief      GetType
* @ingroup    DATAIO
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIONODEITEM::GetType()
{
  return type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEITEM::SetType(XDWORD type)
* @brief      SetType
* @ingroup    DATAIO
* 
* @param[in]  type : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEM::SetType(XDWORD type)
{
  this->type = type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* DIONODEITEM::GetDescription()
* @brief      GetDescription
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
* @fn         bool DIONODEITEM::GetPrimaryDescription(XSTRING& primarydescription)
* @brief      GetPrimaryDescription
* @ingroup    DATAIO
* 
* @param[in]  description : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEM::GetPrimaryDescription(XSTRING& primarydescription)
{
  primarydescription.Empty();
 
  switch(type) 
    {
      case DIONODEITEM_TYPE_UNKNOWN     : primarydescription = __L("unknown");                      
                                          break;

      case DIONODEITEM_TYPE_SENSOR      : primarydescription = __L("sensor");                      
                                          break;

      case DIONODEITEM_TYPE_ACTUATOR    : primarydescription = __L("actuator");                    
                                          break;    

      case DIONODEITEM_TYPE_OWNER       : primarydescription = __L("owner");                    
                                          break;

                             default    : break;
    }

  if(primarydescription.IsEmpty()) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEM::SetDescription(XCHAR* description, bool addprimarydescription)
* @brief      SetDescription
* @ingroup    DATAIO
* 
* @param[in]  description : 
* @param[in]  addprimarydescription : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEM::SetDescription(XCHAR* description, bool addprimarydescription)
{
  this->description.Empty();  

  if(addprimarydescription)
    {
      GetPrimaryDescription(this->description);
      this->description += __L(" ");
    }

  this->description += description; 

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XUUID& DIONODEITEM::GetID()
* @brief      GetID
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
* @brief      SetID
* @ingroup    DATAIO
* 
* @param[in]  UUID : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEM::SetID(XUUID& UUID)
{
  UUID.CopyTo(this->UUID);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEITEMDRIVER* DIONODEITEM::ItemDriver_Get()
* @brief      ItemDriver_Get
* @ingroup    DATAIO
* 
* @return     DIONODEITEMDRIVER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEITEMDRIVER* DIONODEITEM::ItemDriver_Get()
{
  return itemdriver;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEM::ItemDriver_Set(DIONODEITEMDRIVER* itemdriver)
* @brief      ItemDriver_Set
* @ingroup    DATAIO
* 
* @param[in]  itemdriver : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEM::ItemDriver_Set(DIONODEITEMDRIVER* itemdriver)
{
  this->itemdriver = itemdriver;

  if(!itemdriver->SetNodeItem(this))
    { 
      return false;
    }

  if(!ItemDriver_Open())       
    {
      return false;      
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEM::ItemDriver_Open()
* @brief      ItemDriver_Open
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEM::ItemDriver_Open()
{
  if(!itemdriver)               
    {
      return false;  
    }
  
  if(itemdriver->IsOpen())      
    {
      itemdriver->Close();      
    }

  if(!itemdriver->Open())       
    {
      return false;
    }

  if(!itemdriver->IsWorking())  
    {
      return false;      
    }
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEM::ItemDriver_Close()
* @brief      ItemDriver_Close
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEM::ItemDriver_Close()
{
  if(!itemdriver)              
    {
      return false;  
    }

  if(!itemdriver->Close())     
    {
      return false;
    }

  if(itemdriver->IsWorking())  
    {
      return false;      
    }
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XQWORD DIONODEITEM::GetTimeToUpdate()
* @brief      GetTimeToUpdate
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
* @brief      SetTimeToUpdate
* @ingroup    DATAIO
* 
* @param[in]  timetoupdate : 
* 
* @return     void : does not return anything. 
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
* @brief      GetUpdateTimer
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
* @fn         bool DIONODEITEM::Update()
* @brief      Update
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEM::Update()
{
  if(!itemdriver)              
    {
      return false;  
    }

  bool status = false;  
  
  if(updatetimer)
    {
      if(updatetimer->GetMeasureMilliSeconds() > timetoupdate)  
        {
          status = itemdriver->Update();
          updatetimer->Reset();
        }
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<DIONODEITEMVALUE*>* DIONODEITEM::GetValues()
* @brief      GetValues
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
  Primitive_Add<int>(type, __L("type"));

  DIONODEITEMDRIVER* itemdriver =  ItemDriver_Get();
  if(itemdriver)
    {
      Primitive_Add<int>(itemdriver->GetType(), __L("driver_type"));
      Primitive_Add<XSTRING*>(itemdriver->GetDescription(), __L("driver_name"));
    }
  
  
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

  Primitive_Extract<XSTRING*>(&ID, __L("ID"));
  Primitive_Extract<int>(type, __L("type"));

  DIONODEITEMDRIVER* itemdriver =  ItemDriver_Get();
  if(itemdriver)
    {
      Primitive_Extract<int>(itemdriver->GetType(), __L("driver_type"));
      Primitive_Extract<XSTRING*>(itemdriver->GetDescription(), __L("driver_name"));
    }
  
  UUID.SetFromString(ID);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEITEM::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEM::Clean()
{
  type          = DIONODEITEM_TYPE_UNKNOWN;

  itemdriver  = NULL;

  timetoupdate  = 0;
  updatetimer   = NULL;
}
