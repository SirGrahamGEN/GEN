/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIONodeItemHandler_GPIO.cpp
* 
* @class      DIONODEITEMHANDLER_GPIO
* @brief      Data Input/Output Node Item Handler GPIO
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

#include "DIONodeItemHandler_GPIO.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------*/
/*  DIONODEITEMHANDLER_ENTRYGPIO                                                                                      */
/*--------------------------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEITEMHANDLER_ENTRYGPIO::DIONODEITEMHANDLER_ENTRYGPIO()
* @brief      Constructor
* @ingroup    DATAIO
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEITEMHANDLER_ENTRYGPIO::DIONODEITEMHANDLER_ENTRYGPIO()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEITEMHANDLER_ENTRYGPIO::DIONODEITEMHANDLER_ENTRYGPIO(XDWORD entryID, bool writemode, int GPIO, int pin)
* @brief      Constructor
* @ingroup    DATAIO
* 
* @param[in]  XDWORD : 
* @param[in]   bool writemode : 
* @param[in]   int GPIO : 
* @param[in]   int pin : 
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEITEMHANDLER_ENTRYGPIO::DIONODEITEMHANDLER_ENTRYGPIO(XDWORD entryID, bool writemode, int GPIO, int pin)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEITEMHANDLER_ENTRYGPIO::~DIONODEITEMHANDLER_ENTRYGPIO()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEITEMHANDLER_ENTRYGPIO::~DIONODEITEMHANDLER_ENTRYGPIO()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIONODEITEMHANDLER_ENTRYGPIO::GetEntryID()
* @brief      GetEntryID
* @ingroup    DATAIO
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIONODEITEMHANDLER_ENTRYGPIO::GetEntryID()
{
  return entryID;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEITEMHANDLER_ENTRYGPIO::SetEntryID(XDWORD entryID)
* @brief      SetEntryID
* @ingroup    DATAIO
* 
* @param[in]  entryID : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEMHANDLER_ENTRYGPIO::SetEntryID(XDWORD entryID)
{
  this->entryID = entryID;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEMHANDLER_ENTRYGPIO::GetWriteMode()
* @brief      GetWriteMode
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEMHANDLER_ENTRYGPIO::GetWriteMode()
{
  return writemode;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEITEMHANDLER_ENTRYGPIO::SetWriteMode(bool writemode)
* @brief      SetWriteMode
* @ingroup    DATAIO
* 
* @param[in]  writemode : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEMHANDLER_ENTRYGPIO::SetWriteMode(bool writemode)
{
  this->writemode = writemode;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int DIONODEITEMHANDLER_ENTRYGPIO::GetGPIO()
* @brief      GetGPIO
* @ingroup    DATAIO
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int DIONODEITEMHANDLER_ENTRYGPIO::GetGPIO() 
{
  return GPIO;
}

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEITEMHANDLER_ENTRYGPIO::SetGPIO(int GPIO)
* @brief      SetGPIO
* @ingroup    DATAIO
* 
* @param[in]  GPIO : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEMHANDLER_ENTRYGPIO::SetGPIO(int GPIO)
{
  this->GPIO = GPIO;
} 


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int DIONODEITEMHANDLER_ENTRYGPIO::GetPin()
* @brief      GetPin
* @ingroup    DATAIO
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int DIONODEITEMHANDLER_ENTRYGPIO::GetPin()
{
  return pin;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEITEMHANDLER_ENTRYGPIO::SetPin(int pin)
* @brief      SetPin
* @ingroup    DATAIO
* 
* @param[in]  pin : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEMHANDLER_ENTRYGPIO::SetPin(int pin)
{
  this->pin = pin;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEITEMHANDLER_ENTRYGPIO::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEMHANDLER_ENTRYGPIO::Clean()
{
  entryID     = 0;
  writemode   = false;
  GPIO        = DIONODEITEMHANDLER_INVALIDPARAM; 
  pin         = DIONODEITEMHANDLER_INVALIDPARAM;  
}


/*--------------------------------------------------------------------------------------------------------------------*/
/*  DIONODEITEMHANDLER_GPIO                                                                                           */
/*--------------------------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEITEMHANDLER_GPIO::DIONODEITEMHANDLER_GPIO()
* @brief      Constructor
* @ingroup    DATAIO
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEITEMHANDLER_GPIO::DIONODEITEMHANDLER_GPIO(XDWORD entryID, int GPIO, int pin)
{
  Clean();

  this->entryID = entryID;
  this->GPIO    = GPIO;
  this->pin     = pin;  

  if(this->pin != DIONODEITEMHANDLER_INVALIDPARAM)  
    {
      if(!GEN_DIOGPIO.GPIOEntry_SetIDByPin(this->entryID, this->GPIO))
        {
          GEN_DIOGPIO.GPIOEntry_CreateByPin(this->entryID, this->pin);      
        }
    }

  if(this->GPIO != DIONODEITEMHANDLER_INVALIDPARAM)  
    {
      if(!GEN_DIOGPIO.GPIOEntry_SetIDByGPIO(this->entryID, this->GPIO))
        {
          GEN_DIOGPIO.GPIOEntry_CreateByGPIO(this->entryID, this->GPIO);
        }
    }

  timerstatus = GEN_XFACTORY.CreateTimer();  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEITEMHANDLER_GPIO::~DIONODEITEMHANDLER_GPIO()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEITEMHANDLER_GPIO::~DIONODEITEMHANDLER_GPIO()
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
* @fn         bool DIONODEITEMHANDLER_GPIO::Open()
* @brief      Open
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEMHANDLER_GPIO::Open()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEMHANDLER_GPIO::Update()
* @brief      Update
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEMHANDLER_GPIO::Update()
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
* @fn         bool DIONODEITEMHANDLER_GPIO::Close()
* @brief      Close
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEMHANDLER_GPIO::Close()
{        
  isopen = false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEMHANDLER_GPIO::SetNodeItem(DIONODEITEM* nodeitem)
* @brief      SetNodeItem
* @ingroup    DATAIO
* 
* @param[in]  nodeitem : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEMHANDLER_GPIO::SetNodeItem(DIONODEITEM* nodeitem)
{
  if(!DIONODEITEMHANDLER::SetNodeItem(nodeitem)) 
    {
      return false;
    }
  
  DIONODEITEMACTUATOR* nodeitemactuator = (DIONODEITEMACTUATOR*)nodeitem;
  if(!nodeitemactuator)
    {
      return false;
    }

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
* @fn         XQWORD DIONODEITEMHANDLER_GPIO::GetTimeLastActivation()
* @brief      GetTimeLastActivation
* @ingroup    DATAIO
* 
* @return     XQWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XQWORD DIONODEITEMHANDLER_GPIO::GetTimeLastActivation()
{
  return time_last_activation;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XQWORD DIONODEITEMHANDLER_GPIO::GetTimeLastDeactivation()
* @brief      GetTimeLastDeactivation
* @ingroup    DATAIO
* 
* @return     XQWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XQWORD DIONODEITEMHANDLER_GPIO::GetTimeLastDeactivation()
{
  return time_last_deactivation;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEITEMHANDLER_GPIO::AdjustTimeInChange(bool boolean_status)
* @brief      AdjustTimeInChange
* @ingroup    DATAIO
* 
* @param[in]  boolean_status : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEMHANDLER_GPIO::AdjustTimeInChange(bool boolean_status)
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
* @fn         void DIONODEITEMHANDLER_GPIO::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEMHANDLER_GPIO::Clean()
{
  entryID                 = 0;

  GPIO                    = DIONODEITEMHANDLER_INVALIDPARAM;
  pin                     = DIONODEITEMHANDLER_INVALIDPARAM;

  time_last_activation    = 0;
  time_last_deactivation  = 0;

  timerstatus             = NULL;  
}
