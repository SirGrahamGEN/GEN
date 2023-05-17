/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIONodeItemHandler_GPIODigital.cpp
* 
* @class      DIONODEITEMHANDLER_GPIODIGITAL
* @brief      Data Input/Output Node Item Handler GPIO Digital
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
#include "DIONode_XEvent.h"

#include "DIONodeItemHandler_GPIODigital.h"

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
  
  timerstatus = GEN_XFACTORY.CreateTimer();  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEITEMHANDLER_ENTRYGPIO::DIONODEITEMHANDLER_ENTRYGPIO(XDWORD entryID, bool writemode, int GPIO, int pin, XCHAR* description)
* @brief      Constructor
* @ingroup    DATAIO
* 
* @param[in]  entryID : 
* @param[in]  writemode : 
* @param[in]  GPIO : 
* @param[in]  pin : 
* @param[in]  description : 
* 
* @return     Does not return anything. 
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
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* @return     Does not return anything. 
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
* @fn         XSTRING* DIONODEITEMHANDLER_ENTRYGPIO::GetDescription()
* @brief      GetDescription
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
* @brief      GetTimeLastActivation
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
* @brief      GetTimeLastDeactivation
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
* @brief      CopyFrom
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
* @brief      CopyTo
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
* @brief      AdjustTimeInChange
* @ingroup    DATAIO
* 
* @param[in]  boolean_status : 
* 
* @return     void : does not return anything. 
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
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* @return     void : does not return anything. 
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


/*--------------------------------------------------------------------------------------------------------------------*/
/*  DIONODEITEMHANDLER_GPIODIGITAL                                                                                           */
/*--------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEITEMHANDLER_GPIODIGITAL::DIONODEITEMHANDLER_GPIODIGITAL(XLIST<DIONODEITEMHANDLER_ENTRYGPIO*>* entrysGPIO)
* @brief      Constructor
* @ingroup    DATAIO
* 
* @param[in]  XLIST<DIONODEITEMHANDLER_ENTRYGPIO*>* : 
* 
* @return     Does not return anything. 
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
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* @return     Does not return anything. 
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

                  if((bool)(*value) != value_GPIO)
                    {     
                      XSTRING description;  

                      (*value) = value_GPIO;
        
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
* @brief      SetNodeItem
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
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEMHANDLER_GPIODIGITAL::Clean()
{
  
}
