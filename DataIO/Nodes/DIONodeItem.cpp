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

#include "DIONodeDeviceDriver.h"

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
  DeviceDriver_Close();  

  values.DeleteContents();
  values.DeleteAll();    

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEITEM_TYPE DIONODEITEM::GetItemType()
* @brief      GetItemType
* @ingroup    DATAIO
* 
* @return     DIONODEITEM_TYPE : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEITEM_TYPE DIONODEITEM::GetItemType()
{
  return itemtype;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEITEM::SetElementType(DIONODEITEM_TYPE type)
* @brief      SetElementType
* @ingroup    DATAIO
* 
* @param[in]  type : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEM::SetItemType(DIONODEITEM_TYPE type)
{
  this->itemtype = type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEM::GetElementTypeDescription(XSTRING& typedescription)
* @brief      GetItemTypeDescription
* @ingroup    DATAIO
* 
* @param[in]  typedescription : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEM::GetItemTypeDescription(XSTRING& typedescription)
{
   typedescription.Empty();
 
   switch(itemtype) 
    {
      case DIONODEITEM_TYPE_UNKNOWN    : 
                             default   : typedescription = __L("Unknown");                      
                                            return false;  
                                            break;

      case DIONODEITEM_TYPE_SENSOR     : typedescription = __L("Sensor");                      break;
      case DIONODEITEM_TYPE_ACTUATOR   : typedescription = __L("Actuator");                    break;
    
    }

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
* @fn         DIONODEDEVICEDRIVER* DIONODEITEM::DeviceDriver_Get()
* @brief      DeviceDriver_Get
* @ingroup    DATAIO
* 
* @return     DIONODEDEVICEDRIVER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEDEVICEDRIVER* DIONODEITEM::DeviceDriver_Get()
{
  return devicedriver;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEM::DeviceDriver_Set(DIONODEDEVICEDRIVER* devicedriver)
* @brief      DeviceDriver_Set
* @ingroup    DATAIO
* 
* @param[in]  devicedriver : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEM::DeviceDriver_Set(DIONODEDEVICEDRIVER* devicedriver)
{
  this->devicedriver = devicedriver;

  if(!devicedriver->SetNodeItem(this))
    { 
      return false;
    }

  if(!DeviceDriver_Open())       
    {
      return false;      
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEM::DeviceDriver_Open()
* @brief      DeviceDriver_Open
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEM::DeviceDriver_Open()
{
  if(!devicedriver)               
    {
      return false;  
    }
  
  if(devicedriver->IsOpen())      
    {
      devicedriver->Close();      
    }

  if(!devicedriver->Open())       
    {
      return false;
    }

  if(!devicedriver->IsWorking())  
    {
      return false;      
    }
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEM::DeviceDriver_Close()
* @brief      DeviceDriver_Close
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEM::DeviceDriver_Close()
{
  if(!devicedriver)              
    {
      return false;  
    }

  if(!devicedriver->Close())     
    {
      return false;
    }

  if(devicedriver->IsWorking())  
    {
      return false;      
    }
  
  return true;
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
  if(!devicedriver)              
    {
      return false;  
    }

  return devicedriver->Update();
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
  XSTRING typedescription;
 
  UUID.GetToString(ID); 
  GetItemTypeDescription(typedescription);

  Primitive_Add<XSTRING*>(&ID, __L("ID"));

  Primitive_Add<int>(itemtype, __L("element_type"));
  Primitive_Add<XSTRING*>(&typedescription, __L("element_description"));
  
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
  Primitive_Extract<int>(itemtype, __L("element_type"));
  
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
  itemtype   = DIONODEITEM_TYPE_UNKNOWN;
  devicedriver  = NULL;
}
