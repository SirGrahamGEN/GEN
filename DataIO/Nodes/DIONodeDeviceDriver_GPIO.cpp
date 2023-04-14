/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIONodeDeviceDriver_GPIO.cpp
* 
* @class      DIONODEDEVICEDRIVER_GPIO
* @brief      Data Input/Output Node Device Driver GPIO
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
#include "XTimer.h"

#include "DIOGPIO.h"
#include "DIONodeItemActuator.h"

#include "DIONodeDeviceDriver_GPIO.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEDEVICEDRIVER_GPIO::DIONODEDEVICEDRIVER_GPIO()
* @brief      Constructor
* @ingroup    DATAIO
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEDEVICEDRIVER_GPIO::DIONODEDEVICEDRIVER_GPIO(XDWORD entryID, int GPIO, int pin)
{
  Clean();

  this->entryID = entryID;
  this->GPIO    = GPIO;
  this->pin     = pin;  

  if(this->pin != DIONODEDEVICEDRIVER_GPIO_INVALIDPARAM)  
    {
      GEN_DIOGPIO.GPIOEntry_CreateByPin(this->entryID, this->pin);      
    }

  if(this->GPIO != DIONODEDEVICEDRIVER_GPIO_INVALIDPARAM)  
    {
      GEN_DIOGPIO.GPIOEntry_SetIDByGPIO(this->entryID, this->GPIO);        
    }

  timerstatus = GEN_XFACTORY.CreateTimer();  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEDEVICEDRIVER_GPIO::~DIONODEDEVICEDRIVER_GPIO()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEDEVICEDRIVER_GPIO::~DIONODEDEVICEDRIVER_GPIO()
{
  Close();

  if(timerstatus)
    {
      GEN_XFACTORY.DeleteTimer(timerstatus);
    }

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEDEVICEDRIVER_GPIO::Open()
* @brief      Open
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEDEVICEDRIVER_GPIO::Open()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEDEVICEDRIVER_GPIO::Update()
* @brief      Update
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEDEVICEDRIVER_GPIO::Update()
{
  DIONODEITEMACTUATOR* nodeitemactuator = (DIONODEITEMACTUATOR*)GetNodeItem();
  if(!nodeitemactuator)
    {
      return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEDEVICEDRIVER_GPIO::Close()
* @brief      Close
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEDEVICEDRIVER_GPIO::Close()
{        
  isopen = false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEDEVICEDRIVER_GPIO::SetNodeItem(DIONODEITEM* nodeitem)
* @brief      SetNodeItem
* @ingroup    DATAIO
* 
* @param[in]  nodeitem : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEDEVICEDRIVER_GPIO::SetNodeItem(DIONODEITEM* nodeitem)
{
  if(!DIONODEDEVICEDRIVER::SetNodeItem(nodeitem)) 
    {
      return false;
    }
  
  DIONODEITEMACTUATOR* nodeitemactuator = (DIONODEITEMACTUATOR*)nodeitem;
  if(!nodeitemactuator)
    {
      return false;
    }

  nodeitemactuator->SetActuatorType(DIONODEITEM_TYPE_ACTUATOR_GPIO); 

  DIONODEITEMVALUE* value = new DIONODEITEMVALUE();
  if(!value)
    {
      return false;
    }
    
  value->SetType(DIONODEITEMVALUE_TYPE_BOOLEAN); 
    
  (*value->GetValue())    =    false;                    
  value->GetUnitFormat()->SetType(DIONODEITEMVALUE_UNITSFORMAT_TYPE_BOOLEAN);
       
  nodeitem->GetValues()->Add(value);
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XQWORD DIONODEDEVICEDRIVER_GPIO::GetTimeLastActivation()
* @brief      GetTimeLastActivation
* @ingroup    DATAIO
* 
* @return     XQWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XQWORD DIONODEDEVICEDRIVER_GPIO::GetTimeLastActivation()
{
  return time_last_activation;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XQWORD DIONODEDEVICEDRIVER_GPIO::GetTimeLastDeactivation()
* @brief      GetTimeLastDeactivation
* @ingroup    DATAIO
* 
* @return     XQWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XQWORD DIONODEDEVICEDRIVER_GPIO::GetTimeLastDeactivation()
{
  return time_last_deactivation;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEDEVICEDRIVER_GPIO::AdjustTimeInChange(bool boolean_status)
* @brief      AdjustTimeInChange
* @ingroup    DATAIO
* 
* @param[in]  boolean_status : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEDEVICEDRIVER_GPIO::AdjustTimeInChange(bool boolean_status)
{
  if(boolean_status)
    {    
      time_last_deactivation  = timerstatus->GetMeasureMilliSeconds();
    }
   else
    {
      time_last_activation    = timerstatus->GetMeasureMilliSeconds();  
    }   

  timerstatus->Reset();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEDEVICEDRIVER_GPIO::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEDEVICEDRIVER_GPIO::Clean()
{
  entryID                 = 0;

  GPIO                    = DIONODEDEVICEDRIVER_GPIO_INVALIDPARAM;
  pin                     = DIONODEDEVICEDRIVER_GPIO_INVALIDPARAM;

  time_last_activation    = 0;
  time_last_deactivation  = 0;

  timerstatus             = NULL;  
}
