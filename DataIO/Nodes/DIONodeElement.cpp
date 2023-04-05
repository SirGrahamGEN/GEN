/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIONodeElement.cpp
* 
* @class      DIONODEELEMENT
* @brief      Data Input/Output Node element (Base for DIONODESENSOR, DIONODEACTUATOR, ...)
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

#include "DIONodeElement.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEELEMENT::DIONODEELEMENT()
* @brief      Constructor
* @ingroup    
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEELEMENT::DIONODEELEMENT()
{
  Clean();

  UUID.GenerateRandom();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEELEMENT::~DIONODEELEMENT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEELEMENT::~DIONODEELEMENT()
{
  DeviceDriver_Close();      

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEELEMENT_TYPE DIONODEELEMENT::GetElementType()
* @brief      GetElementType
* @ingroup    DATAIO
* 
* @return     DIONODEELEMENT_TYPE : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEELEMENT_TYPE DIONODEELEMENT::GetElementType()
{
  return elementtype;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEELEMENT::SetElementType(DIONODEELEMENT_TYPE type)
* @brief      SetElementType
* @ingroup    DATAIO
* 
* @param[in]  type : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEELEMENT::SetElementType(DIONODEELEMENT_TYPE type)
{
  this->elementtype = type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEELEMENT::GetElementTypeDescription(XSTRING& typedescription)
* @brief      GetElementTypeDescription
* @ingroup    DATAIO
* 
* @param[in]  typedescription : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEELEMENT::GetElementTypeDescription(XSTRING& typedescription)
{
   typedescription.Empty();
 
   switch(elementtype) 
    {
      case DIONODEELEMENT_TYPE_UNKNOWN    : 
                                default   : typedescription = __L("Unknown");                      
                                            return false;  
                                            break;

      case DIONODEELEMENT_TYPE_SENSOR     : typedescription = __L("Sensor");                      break;
      case DIONODEELEMENT_TYPE_ACTUATOR   : typedescription = __L("Actuator");                    break;
    
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XUUID& DIONODEELEMENT::GetID()
* @brief      GetID
* @ingroup    DATAIO
* 
* @return     XUUID& : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XUUID& DIONODEELEMENT::GetID()
{
  return UUID;
}
 

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEELEMENT::SetID(XUUID& UUID)
* @brief      SetID
* @ingroup    DATAIO
* 
* @param[in]  UUID : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEELEMENT::SetID(XUUID& UUID)
{
  UUID.CopyTo(this->UUID);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEDEVICEDRIVER* DIONODEELEMENT::DeviceDriver_Get()
* @brief      DeviceDriver_Get
* @ingroup    DATAIO
* 
* @return     DIONODEDEVICEDRIVER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEDEVICEDRIVER* DIONODEELEMENT::DeviceDriver_Get()
{
  return devicedriver;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEELEMENT::DeviceDriver_Set(DIONODEDEVICEDRIVER* devicedriver)
* @brief      DeviceDriver_Set
* @ingroup    DATAIO
* 
* @param[in]  devicedriver : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEELEMENT::DeviceDriver_Set(DIONODEDEVICEDRIVER* devicedriver)
{
  this->devicedriver = devicedriver;

  if(!DeviceDriver_Open())       
    {
      return false;      
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEELEMENT::DeviceDriver_Open()
* @brief      DeviceDriver_Open
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEELEMENT::DeviceDriver_Open()
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
* @fn         bool DIONODEELEMENT::DeviceDriver_Close()
* @brief      DeviceDriver_Close
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEELEMENT::DeviceDriver_Close()
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
* @fn         bool DIONODEELEMENT::Serialize()
* @brief      Serialize
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEELEMENT::Serialize()
{
  XSTRING ID;
  XSTRING typedescription;
 
  UUID.GetToString(ID); 
  GetElementTypeDescription(typedescription);

  Primitive_Add<int>(elementtype, __L("element_type"));
  Primitive_Add<XSTRING>(typedescription, __L("element_description"));
  Primitive_Add<XSTRING>(ID, __L("ID"));
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEELEMENT::Deserialize()
* @brief      Deserialize
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEELEMENT::Deserialize()
{   
  XSTRING ID;

  Primitive_Extract<int>(elementtype, __L("element_type"));
  Primitive_Extract<XSTRING>(ID, __L("ID"));
  
  UUID.SetFromString(ID);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEELEMENT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEELEMENT::Clean()
{
  elementtype   = DIONODEELEMENT_TYPE_UNKNOWN;
  devicedriver  = NULL;
}
