/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIONodeItemHandler_GPIODigital.cpp
* 
* @class      DIONODEITEMHANDLER_GPIODIGITAL
* @brief      Data Input/Output Node Item Handler GPIO Digital class
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

#include "DIONodeItemHandler_GPIODigital.h"

#include "XFactory.h"
#include "XTimer.h"

#include "DIOGPIO.h"
#include "DIONode_XEvent.h"

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


#pragma region CLASS_DIONODEITEMHANDLER_ENTRYGPIO


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEITEMHANDLER_ENTRYGPIO::DIONODEITEMHANDLER_ENTRYGPIO()
* @brief      Constructor of class
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEITEMHANDLER_ENTRYGPIO::DIONODEITEMHANDLER_ENTRYGPIO()
{
  Clean();
  
  timerstatus = GEN_XFACTORY.CreateTimer();  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEITEMHANDLER_ENTRYGPIO::DIONODEITEMHANDLER_ENTRYGPIO(XDWORD entryID, bool writemode, int GPIO, int pin, XCHAR* description)
* @brief      Constructor of class
* @ingroup    DATAIO
* 
* @param[in]  entryID : 
* @param[in]  writemode : 
* @param[in]  GPIO : 
* @param[in]  pin : 
* @param[in]  description : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEITEMHANDLER_ENTRYGPIO::DIONODEITEMHANDLER_ENTRYGPIO(XDWORD entryID, bool writemode, int GPIO, int pin, XCHAR* description)
{
  Clean();

  timerstatus = GEN_XFACTORY.CreateTimer();  

  this->entryID     = entryID;
  this->writemode   = writemode;
  this->GPIO        = GPIO; 
  this->pin         = pin;
  this->description = description;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEITEMHANDLER_ENTRYGPIO::~DIONODEITEMHANDLER_ENTRYGPIO()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEITEMHANDLER_ENTRYGPIO::~DIONODEITEMHANDLER_ENTRYGPIO()
{
  if(timerstatus)
    {
      GEN_XFACTORY.DeleteTimer(timerstatus);
    }

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIONODEITEMHANDLER_ENTRYGPIO::GetEntryID()
* @brief      Get entry ID
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
* @brief      Set entry ID
* @ingroup    DATAIO
* 
* @param[in]  entryID : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEMHANDLER_ENTRYGPIO::SetEntryID(XDWORD entryID)
{
  this->entryID = entryID;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEMHANDLER_ENTRYGPIO::GetWriteMode()
* @brief      Get write mode
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
* @brief      Set write mode
* @ingroup    DATAIO
* 
* @param[in]  writemode : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEMHANDLER_ENTRYGPIO::SetWriteMode(bool writemode)
{
  this->writemode = writemode;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int DIONODEITEMHANDLER_ENTRYGPIO::GetGPIO()
* @brief      Get GPIO
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
* @brief      Set GPIO
* @ingroup    DATAIO
* 
* @param[in]  GPIO : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEMHANDLER_ENTRYGPIO::SetGPIO(int GPIO)
{
  this->GPIO = GPIO;
} 


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int DIONODEITEMHANDLER_ENTRYGPIO::GetPin()
* @brief      Get pin
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
* @brief      Set pin
* @ingroup    DATAIO
* 
* @param[in]  pin : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEMHANDLER_ENTRYGPIO::SetPin(int pin)
{
  this->pin = pin;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* DIONODEITEMHANDLER_ENTRYGPIO::GetDescription()
* @brief      Get description
* @ingroup    DATAIO
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIONODEITEMHANDLER_ENTRYGPIO::GetDescription()
{
  return &description;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XQWORD DIONODEITEMHANDLER_ENTRYGPIO::GetTimeLastActivation()
* @brief      Get time last activation
* @ingroup    DATAIO
* 
* @return     XQWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XQWORD DIONODEITEMHANDLER_ENTRYGPIO::GetTimeLastActivation()
{
  return time_last_activation;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XQWORD DIONODEITEMHANDLER_ENTRYGPIO::GetTimeLastDeactivation()
* @brief      Get time last deactivation
* @ingroup    DATAIO
* 
* @return     XQWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XQWORD DIONODEITEMHANDLER_ENTRYGPIO::GetTimeLastDeactivation()
{
  return time_last_deactivation;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEMHANDLER_ENTRYGPIO::CopyFrom(DIONODEITEMHANDLER_ENTRYGPIO* entryGPIO)
* @brief      Copy from
* @ingroup    DATAIO
* 
* @param[in]  entryGPIO : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEMHANDLER_ENTRYGPIO::CopyFrom(DIONODEITEMHANDLER_ENTRYGPIO* entryGPIO)
{
  if(!entryGPIO)
    {
      return false;
    }
  
  entryID                   = entryGPIO->entryID;
  writemode                 = entryGPIO->writemode;
  GPIO                      = entryGPIO->GPIO; 
  pin                       = entryGPIO->pin;
  description               = entryGPIO->description;

  time_last_activation      = entryGPIO->time_last_activation;
  time_last_deactivation    = entryGPIO->time_last_deactivation;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEMHANDLER_ENTRYGPIO::CopyTo(DIONODEITEMHANDLER_ENTRYGPIO* entryGPIO)
* @brief      Copy to
* @ingroup    DATAIO
* 
* @param[in]  entryGPIO : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEMHANDLER_ENTRYGPIO::CopyTo(DIONODEITEMHANDLER_ENTRYGPIO* entryGPIO)
{
  if(!entryGPIO)
    {
      return false;
    }
  
  entryGPIO->entryID                   = entryID;
  entryGPIO->writemode                 = writemode;
  entryGPIO->GPIO                      = GPIO; 
  entryGPIO->pin                       = pin;
  entryGPIO->description               = description;

  entryGPIO->time_last_activation      = time_last_activation;
  entryGPIO->time_last_deactivation    = time_last_deactivation;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEITEMHANDLER_ENTRYGPIO::AdjustTimeInChange(bool boolean_status)
* @brief      Adjust time in change
* @ingroup    DATAIO
* 
* @param[in]  boolean_status : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEMHANDLER_ENTRYGPIO::AdjustTimeInChange(bool boolean_status)
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
* @fn         void DIONODEITEMHANDLER_ENTRYGPIO::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEMHANDLER_ENTRYGPIO::Clean()
{
  entryID                 = 0;
  writemode               = false;
  GPIO                    = DIONODEITEMHANDLER_INVALIDPARAM; 
  pin                     = DIONODEITEMHANDLER_INVALIDPARAM;  

  time_last_activation    = 0;
  time_last_deactivation  = 0;

  timerstatus             = NULL;  
}


#pragma endregion


#pragma region CLASS_DIONODEITEMHANDLER_GPIODIGITAL


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEITEMHANDLER_GPIODIGITAL::DIONODEITEMHANDLER_GPIODIGITAL(XLIST<DIONODEITEMHANDLER_ENTRYGPIO*>* entrysGPIO)
* @brief      Constructor of class
* @ingroup    DATAIO
* 
* @param[in]  entrysGPIO : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEITEMHANDLER_GPIODIGITAL::DIONODEITEMHANDLER_GPIODIGITAL(XLIST<DIONODEITEMHANDLER_ENTRYGPIO*>* entrysGPIO)
{
  Clean();

  type  = DIONODEITEMHANDLER_TYPE_GPIODIGITAL;
  name  = __L("GPIO Digital");

  for(XDWORD c=0; c<entrysGPIO->GetSize(); c++)
    {
      DIONODEITEMHANDLER_ENTRYGPIO* entryGPIO = new DIONODEITEMHANDLER_ENTRYGPIO();
      if(entryGPIO)
        {
          entryGPIO->CopyFrom(entrysGPIO->Get(c));
          this->entrysGPIO.Add(entryGPIO);        

          if(entryGPIO->GetPin() != DIONODEITEMHANDLER_INVALIDPARAM)  
            {
              if(!GEN_DIOGPIO.GPIOEntry_SetIDByPin(entryGPIO->GetEntryID(), entryGPIO->GetGPIO()))
                {
                  GEN_DIOGPIO.GPIOEntry_CreateByPin(entryGPIO->GetEntryID(), entryGPIO->GetPin());      
                }
            }

          if(entryGPIO->GetGPIO() != DIONODEITEMHANDLER_INVALIDPARAM)  
            {
              if(!GEN_DIOGPIO.GPIOEntry_SetIDByGPIO(entryGPIO->GetEntryID(), entryGPIO->GetGPIO()))
                {
                  GEN_DIOGPIO.GPIOEntry_CreateByGPIO(entryGPIO->GetEntryID(), entryGPIO->GetGPIO());
                }
            }      
        }
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEITEMHANDLER_GPIODIGITAL::~DIONODEITEMHANDLER_GPIODIGITAL()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEITEMHANDLER_GPIODIGITAL::~DIONODEITEMHANDLER_GPIODIGITAL()
{
  Close();

  entrysGPIO.DeleteContents();
  entrysGPIO.DeleteAll();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEMHANDLER_GPIODIGITAL::Open()
* @brief      Open
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEMHANDLER_GPIODIGITAL::Open()
{
  isopen = false;

  for(XDWORD c=0; c<entrysGPIO.GetSize(); c++)
    {
      DIONODEITEMHANDLER_ENTRYGPIO* entryGPIO = entrysGPIO.Get(c);
      if(entryGPIO)
        {
          isopen = GEN_DIOGPIO.SetMode(entryGPIO->GetEntryID(), entryGPIO->GetWriteMode()?DIOGPIO_MODE_OUTPUT:DIOGPIO_MODE_INPUT);             
          if(!isopen) break;
        }
    }
  
  isworking = isopen;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEMHANDLER_GPIODIGITAL::Update()
* @brief      Update
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEMHANDLER_GPIODIGITAL::Update()
{
  DIONODEITEM* nodeitem = (DIONODEITEM*)GetNodeItem();
  if(!nodeitem)
    {
      return false;
    }

  for(XDWORD c=0; c<entrysGPIO.GetSize(); c++)
    {
      DIONODEITEMHANDLER_ENTRYGPIO* entryGPIO = entrysGPIO.Get(c);
      if(entryGPIO)
        {
          DIONODEITEMVALUE* nodeitemvalue = nodeitem->GetValues()->Get(c);
          if(!nodeitemvalue) 
            {
              return false;
            }
    
          XVARIANT* value = nodeitemvalue->GetValue();
          if(value)
            {
              if(entryGPIO->GetWriteMode())
                {
                  if(nodeitemvalue->ValueHasChanged())
                   {               
                      bool     _value       = (*value); 
                      XSTRING description;
                    
                      GEN_DIOGPIO.SetValue(entryGPIO->GetEntryID(), _value);    
                      nodeitemvalue->ReadUpdateDateTime();

                      nodeitemvalue->GetDescription(description);
                      entryGPIO->AdjustTimeInChange(_value);
                      nodeitemvalue->SetValueHasChanged(false);

                      /*
                      DIONODE_XEVENT xevent(this, DIONODE_XEVENT_TYPE_UPDATEVALUE); 
                  
                      xevent.SetNodeItem(nodeitem);
                      xevent.SetIndexValue(c);
             
                      PostEvent(&xevent);
                      */
                      
                      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[DIONODE item handler %s] %s %s [value %s]"), GetName()->Get(), entryGPIO->GetDescription()->Get(), description.Get(), _value?__L("true"):__L("false"));
                    }          
                }
               else
                {
                  bool value_GPIO = GEN_DIOGPIO.GetValue(entryGPIO->GetEntryID());

                  nodeitemvalue->ReadUpdateDateTime();

                  if((bool)(*value) != value_GPIO)
                    {     
                      XSTRING description;  

                      (*value) = value_GPIO;
                      
                      nodeitemvalue->ReadUpdateDateTime();
        
                      nodeitemvalue->GetDescription(description);
                      entryGPIO->AdjustTimeInChange(value_GPIO);
                      nodeitemvalue->SetValueHasChanged(true);

                      DIONODE_XEVENT xevent(this, DIONODE_XEVENT_TYPE_UPDATEVALUE); 
                  
                      xevent.SetNodeItem(nodeitem);
                      xevent.SetIndexValue(c);
             
                      PostEvent(&xevent);
                      
                      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[DIONODE item handler %s] %s %s [value %s]"), GetName()->Get(), entryGPIO->GetDescription()->Get(), description.Get(), value_GPIO?__L("true"):__L("false"));    
                    }
                }
            }
        }
    }
    
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEMHANDLER_GPIODIGITAL::Close()
* @brief      Close
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEMHANDLER_GPIODIGITAL::Close()
{        
  isopen    = false;
  isworking = false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEMHANDLER_GPIODIGITAL::SetNodeItem(DIONODEITEM* nodeitem)
* @brief      Set node item
* @ingroup    DATAIO
* 
* @param[in]  nodeitem : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEMHANDLER_GPIODIGITAL::SetNodeItem(DIONODEITEM* nodeitem)
{
  if(!DIONODEITEMHANDLER::SetNodeItem(nodeitem)) 
    {
      return false;
    }
  
  nodeitem->SetCategory(DIONODEITEM_CATEGORY_GPIO_DIGITAL); 
  
  for(XDWORD c=0; c<entrysGPIO.GetSize(); c++)
    {
      DIONODEITEMHANDLER_ENTRYGPIO* entryGPIO = entrysGPIO.Get(c);
      if(entryGPIO)
        {
          DIONODEITEMVALUE* value = new DIONODEITEMVALUE();
          if(value)
            {                    
              (*value->GetValue()) = false;                    

              value->GetUnitFormat()->SetType(DIONODEITEMVALUE_UNITSFORMAT_TYPE_BOOLEAN);
              value->SetMode(entryGPIO->GetWriteMode()?DIONODEITEMVALUE_MODE_WRITE:DIONODEITEMVALUE_MODE_READ);

              nodeitem->GetValues()->Add(value);
            }
        }
    }
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEITEMHANDLER_GPIODIGITAL::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEMHANDLER_GPIODIGITAL::Clean()
{
  
}


#pragma endregion


#pragma endregion
