/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOGPIO.cpp
*
* @class      DIOGPIO
* @brief      Data Input/Output GPIO (General Purpose Input/Output)
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @copyright  Copyright(c) 2008 - 2016 GEN Group.
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
*---------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XTrace.h"

#include "DIOGPIO.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

DIOGPIO* DIOGPIO::instance = NULL;

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------*/
/*  DIOGPIO_ENTRY                                                                                                 */
/*--------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOGPIO_ENTRY::DIOGPIO_ENTRY()
* @brief      Constructor
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOGPIO_ENTRY::DIOGPIO_ENTRY()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOGPIO_ENTRY::~DIOGPIO_ENTRY()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOGPIO_ENTRY::~DIOGPIO_ENTRY()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIOGPIO_ENTRY::GetID()
* @brief      GetID
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOGPIO_ENTRY::GetID()
{
  return ID;
}
    


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOGPIO_ENTRY::SetID(XDWORD ID)
* @brief      SetID
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  ID : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOGPIO_ENTRY::SetID(XDWORD ID)
{
  this->ID = ID;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XQWORD DIOGPIO_ENTRY::GetGPIO()
* @brief      GetGPIO
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     XQWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XQWORD DIOGPIO_ENTRY::GetGPIO()
{
  return GPIO;
}
    


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOGPIO_ENTRY::SetGPIO(XQWORD GPIO)
* @brief      SetGPIO
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  GPIO : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOGPIO_ENTRY::SetGPIO(XQWORD GPIO)
{
  this->GPIO = GPIO;
}


    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOGPIO_PINSGROUP DIOGPIO_ENTRY::GetGroup()
* @brief      GetGroup
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     DIOGPIO_PINSGROUP : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOGPIO_PINSGROUP DIOGPIO_ENTRY::GetGroup()
{
  return group;
}
    


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOGPIO_ENTRY::SetGroup(DIOGPIO_PINSGROUP group)
* @brief      SetGroup
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  group : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOGPIO_ENTRY::SetGroup(DIOGPIO_PINSGROUP group)
{
  this->group = group;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XWORD DIOGPIO_ENTRY::GetPin()
* @brief      GetPin
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     XWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XWORD DIOGPIO_ENTRY::GetPin()
{
  return pin;
}


    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOGPIO_ENTRY::SetPin(XWORD pin)
* @brief      SetPin
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  pin : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOGPIO_ENTRY::SetPin(XWORD pin)
{
  this->pin = pin;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XWORD DIOGPIO_ENTRY::GetMode()
* @brief      GetMode
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     XWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XWORD DIOGPIO_ENTRY::GetMode()
{
  return mode;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOGPIO_ENTRY::SetMode(XWORD mode)
* @brief      SetMode
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  mode : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOGPIO_ENTRY::SetMode(XWORD mode)
{
  this->mode = mode;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOGPIO_PULLMODE DIOGPIO_ENTRY::GetPullMode()
* @brief      GetPullMode
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     DIOGPIO_PULLMODE : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOGPIO_PULLMODE DIOGPIO_ENTRY::GetPullMode()
{
  return pullmode;
}

    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOGPIO_ENTRY::SetPullMode(DIOGPIO_PULLMODE pullmode)
* @brief      SetPullMode
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  pullmode : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOGPIO_ENTRY::SetPullMode(DIOGPIO_PULLMODE pullmode)
{
  this->pullmode = pullmode;
}




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOGPIO_INT_FUNCPTR DIOGPIO_ENTRY::GetIntFunctionPointer()
* @brief      GetIntFunctionPointer
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     DIOGPIO_INT_FUNCPTR : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOGPIO_INT_FUNCPTR DIOGPIO_ENTRY::GetIntFunctionPointer()
{
  return int_funcptr;
}


   
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOGPIO_ENTRY::SetIntFunctionPointer(DIOGPIO_INT_FUNCPTR int_funcptr)
* @brief      SetIntFunctionPointer
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  int_funcptr : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOGPIO_ENTRY::SetIntFunctionPointer(DIOGPIO_INT_FUNCPTR int_funcptr)
{
  this->int_funcptr = int_funcptr;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void* DIOGPIO_ENTRY::GetIntParamPointer()
* @brief      GetIntParamPointer
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     void* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void* DIOGPIO_ENTRY::GetIntParamPointer()
{
  return int_paramptr;    

}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOGPIO_ENTRY::SetIntParamPointer(void* int_paramptr)
* @brief      SetIntParamPointer
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  int_paramptr : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOGPIO_ENTRY::SetIntParamPointer(void* int_paramptr)
{
  this->int_paramptr = int_paramptr;
}




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIOGPIO_ENTRY::GetIntIRQ()
* @brief      GetIntIRQ
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOGPIO_ENTRY::GetIntIRQ()
{
  return int_IRQ;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOGPIO_ENTRY::SetIntIRQ(XDWORD int_IRQ)
* @brief      SetIntIRQ
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  int_IRQ : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOGPIO_ENTRY::SetIntIRQ(XDWORD int_IRQ)
{
  this->int_IRQ = int_IRQ;
}


    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIOGPIO_ENTRY::GetIntPriority()
* @brief      GetIntPriority
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOGPIO_ENTRY::GetIntPriority()
{
  return int_priority;
}


    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOGPIO_ENTRY::SetIntPriority(XDWORD int_priority)
* @brief      SetIntPriority
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  int_priority : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOGPIO_ENTRY::SetIntPriority(XDWORD int_priority)
{
  this->int_priority = int_priority;
}

  

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOGPIO_ENTRY::DebugTrace()
* @brief      DebugTrace
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOGPIO_ENTRY::DebugTrace()
{
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("-- GPIO Entry ---------------------------------"));
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("ID            : [%d]")    , ID);
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("GPIO          : [%lld]")  , GPIO);
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Pin           : [%d]")    , pin);
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Group         : [%d]")    , group);    
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Mode          : [%08X]")  , mode);
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Pull Mode     : [%d]")    , pullmode); 
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Int Func      : [%X08]")  , int_funcptr);                                                          
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Int IRQ       : [%X08]")  , int_IRQ);                                                          
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Int Priority  : [%X08]")  , int_priority);                                                          
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOGPIO_ENTRY::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOGPIO_ENTRY::Clean()
{
  ID               = 0;
  GPIO             = DIOGPIO_INVALID;   
  group            = DIOGPIO_PINSGROUP_NONE;
  pin              = 0;    
  mode             = DIOGPIO_MODE_NONE;   
  pullmode         = DIOGPIO_PULLMODE_OFF;
  
  int_funcptr      = NULL;
  int_paramptr    =  NULL;
  int_IRQ          = 0;
  int_priority     = 0;                                                              
}



/*--------------------------------------------------------------------------------------------------------------------*/
/*  DIOGPIO                                                                                                           */
/*--------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOGPIO::DIOGPIO()
* @brief      Constructor
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOGPIO::DIOGPIO()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOGPIO::~DIOGPIO()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOGPIO::~DIOGPIO()
{ 
  End();

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOGPIO::GetIsInstanced()
* @brief      GetIsInstanced
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOGPIO::GetIsInstanced()
{
  return instance!=NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOGPIO& DIOGPIO::GetInstance()
* @brief      GetInstance
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     DIOGPIO& :
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOGPIO& DIOGPIO::GetInstance()
{
  if(!instance) instance = new DIOGPIO();

  return (*instance);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOGPIO::SetInstance(DIOGPIO* _instance)
* @brief      SetInstance
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  _instance :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOGPIO::SetInstance(DIOGPIO* _instance)
{
  if(!_instance) return false;

  instance = _instance;

  return (instance)?true:false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOGPIO::DelInstance()
* @brief      DelInstance
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOGPIO::DelInstance()
{
  if(instance)
    {
      delete instance;
      instance = NULL;

      return true;
    }

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XMAP<XDWORD, DIOGPIO_ENTRY*>* DIOGPIO::GPIOMap_GetAll()
* @brief      GPIOMap_GetAll
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     XMAP<XDWORD, : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XVECTOR<DIOGPIO_ENTRY*>* DIOGPIO::GPIOEntry_GetAll()
{
  return &GPIOentrys;
}




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOGPIO_ENTRY* DIOGPIO::GPIOEntry_CreateByPin(XDWORD ID, XWORD pin, DIOGPIO_PINSGROUP group)
* @brief      GPIOEntry_CreateByPin
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  ID : 
* @param[in]  pin : 
* @param[in]  group : 
* 
* @return     DIOGPIO_ENTRY* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOGPIO_ENTRY* DIOGPIO::GPIOEntry_CreateByPin(XDWORD ID, XWORD pin, DIOGPIO_PINSGROUP group)
{
  DIOGPIO_ENTRY* entry = new DIOGPIO_ENTRY();
  if(!entry) return NULL;

  entry->SetID(ID);
  entry->SetPin(pin);  
  entry->SetGroup(group);
  entry->SetGPIO(0); 

  GPIOentrys.Add(entry);

  return entry;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOGPIO_ENTRY* DIOGPIO::GPIOEntry_CreateByGPIO(XDWORD ID, XQWORD GPIO)
* @brief      GPIOEntry_CreateByGPIO
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  ID : 
* @param[in]  GPIO : 
* 
* @return     DIOGPIO_ENTRY* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOGPIO_ENTRY* DIOGPIO::GPIOEntry_CreateByGPIO(XDWORD ID, XQWORD GPIO)
{
  DIOGPIO_ENTRY* entry = new DIOGPIO_ENTRY();
  if(!entry) return NULL;

  entry->SetID(ID);  
  entry->SetPin(0); 
  entry->SetGroup(DIOGPIO_PINSGROUP_NONE);
  entry->SetGPIO(GPIO);  
 
  GPIOentrys.Add(entry);

  return entry;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOGPIO_ENTRY* DIOGPIO::GPIOEntry_Create(XDWORD ID, XWORD pin, XQWORD GPIO)
* @brief      GPIOEntry_Create
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  ID : 
* @param[in]  pin : 
* @param[in]  GPIO : 
* 
* @return     DIOGPIO_ENTRY* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOGPIO_ENTRY* DIOGPIO::GPIOEntry_Create(XDWORD ID, XWORD pin, XQWORD GPIO)
{
  DIOGPIO_ENTRY* entry = new DIOGPIO_ENTRY();
  if(!entry) return NULL;
  
  entry->SetID(ID);
  entry->SetPin(pin); 
  entry->SetGroup(DIOGPIO_PINSGROUP_NONE); 
  entry->SetGPIO(GPIO);

  GPIOentrys.Add(entry);

  return entry;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOGPIO_ENTRY* DIOGPIO::GPIOEntry_GetByID(XDWORD ID)
* @brief      GPIOEntry_GetByID
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  ID : 
* 
* @return     DIOGPIO_ENTRY* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOGPIO_ENTRY* DIOGPIO::GPIOEntry_GetByID(XDWORD ID)
{
  if(GPIOentrys.IsEmpty()) return NULL;

  for(XDWORD c=0; c<GPIOentrys.GetSize(); c++)
    {
      DIOGPIO_ENTRY* entry = GPIOentrys.Get(c);
      if(entry)
        {
          if(entry->GetID() == ID) return entry;
        }
    }

  return NULL;
}




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOGPIO_ENTRY* DIOGPIO::GPIOEntry_GetByPin(XWORD pin, DIOGPIO_PINSGROUP group)
* @brief      GPIOEntry_GetByPin
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  pin : 
* @param[in]  group : 
* 
* @return     DIOGPIO_ENTRY* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOGPIO_ENTRY* DIOGPIO::GPIOEntry_GetByPin(XWORD pin, DIOGPIO_PINSGROUP group)    
{
  if(GPIOentrys.IsEmpty()) return NULL;

  for(XDWORD c=0; c<GPIOentrys.GetSize(); c++)
    {
      DIOGPIO_ENTRY* entry = GPIOentrys.Get(c);
      if(entry)
        {
          if((entry->GetPin() == pin) && (entry->GetGroup() == group)) return entry;
        }
    }

  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOGPIO_ENTRY* DIOGPIO::GPIOEntry_GetInterruptByPin(XWORD pin)
* @brief      GPIOEntry_GetInterruptByPin
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  pin : 
* 
* @return     DIOGPIO_ENTRY* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOGPIO_ENTRY* DIOGPIO::GPIOEntry_GetInterruptByPin(XWORD pin)
{
  if(GPIOentrys.IsEmpty()) return NULL;

  for(XDWORD c=0; c<GPIOentrys.GetSize(); c++)
    {
      DIOGPIO_ENTRY* entry = GPIOentrys.Get(c);
      if(entry)
        {
          if((entry->GetPin() == pin) && ((entry->GetMode() & DIOGPIO_MODE_INTERRUPT) == DIOGPIO_MODE_INTERRUPT)) return entry;
        }
    }

  return NULL;

}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOGPIO_ENTRY* DIOGPIO::GPIOEntry_GetByGPIO(XQWORD GPIO)
* @brief      GPIOEntry_GetByGPIO
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  GPIO : 
* 
* @return     DIOGPIO_ENTRY* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOGPIO_ENTRY* DIOGPIO::GPIOEntry_GetByGPIO(XQWORD GPIO)    
{
  if(GPIOentrys.IsEmpty()) return NULL;

  for(XDWORD c=0; c<GPIOentrys.GetSize(); c++)
    {
      DIOGPIO_ENTRY* entry = GPIOentrys.Get(c);
      if(entry)
        {
          if(entry->GetGPIO() == GPIO) return entry;
        }
    }

  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOGPIO::GPIOEntry_DeleteAll()
* @brief      GPIOEntry_DeleteAll
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOGPIO::GPIOEntry_DeleteAll()
{
  if(GPIOentrys.IsEmpty()) return false;

  GPIOentrys.DeleteContents();
  GPIOentrys.DeleteAll();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOGPIO::GPIOEntry_SetIDByPin(XDWORD ID, XWORD pin, DIOGPIO_PINSGROUP group)
* @brief      GPIOEntry_SetIDByPin
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  ID : 
* @param[in]  pin : 
* @param[in]  group : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOGPIO::GPIOEntry_SetIDByPin(XDWORD ID, XWORD pin, DIOGPIO_PINSGROUP group)
{
  DIOGPIO_ENTRY* entry = GPIOEntry_GetByPin(pin, group);
  if(!entry) return false;

  entry->SetID(ID);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOGPIO::GPIOEntry_SetIDByGPIO(XDWORD ID, XQWORD GPIO)
* @brief      GPIOEntry_SetIDByGPIO
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  ID : 
* @param[in]  GPIO : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOGPIO::GPIOEntry_SetIDByGPIO(XDWORD ID, XQWORD GPIO)
{
  DIOGPIO_ENTRY* entry = GPIOEntry_GetByGPIO(GPIO);
  if(!entry) return false;

  entry->SetID(ID);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOGPIO::Ini(XPATH* xpath)
* @brief      Ini
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOGPIO::Ini()
{
  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XWORD DIOGPIO::GetMode(XDWORD ID)
* @brief      GetMode
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  ID : 
* 
* @return     XWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XWORD DIOGPIO::GetMode(XDWORD ID)
{
  DIOGPIO_ENTRY* entry = GPIOEntry_GetByID(ID);
  if(!entry) return 0;

  return GetMode(entry);  
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOGPIO::SetMode(XDWORD ID, XWORD mode)
* @brief      SetMode
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  ID : 
* @param[in]  mode : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOGPIO::SetMode(XDWORD ID, XWORD mode)
{
  DIOGPIO_ENTRY* entry = GPIOEntry_GetByID(ID);
  if(!entry) return false;
  
  SetMode(entry, mode);  

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOGPIO::GetValue(XDWORD ID)
* @brief      GetValue
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  ID : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOGPIO::GetValue(XDWORD ID)
{
  DIOGPIO_ENTRY* entry = GPIOEntry_GetByID(ID);
  if(!entry) return false;

  return GetValue(entry);
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOGPIO::SetValue(XDWORD ID, bool value)
* @brief      SetValue
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  ID : 
* @param[in]  value : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOGPIO::SetValue(XDWORD ID, bool value)
{
  DIOGPIO_ENTRY* entry = GPIOEntry_GetByID(ID);
  if(!entry) return false;

  return SetValue(entry, value);
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XWORD DIOGPIO::GetMode(DIOGPIO_ENTRY* entry)
* @brief      GetMode
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  entry : 
* 
* @return     XWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XWORD DIOGPIO::GetMode(DIOGPIO_ENTRY* entry)
{
  if(!entry) return 0;

  return entry->GetMode();  
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOGPIO::SetMode(DIOGPIO_ENTRY* entry, XWORD mode)
* @brief      SetMode
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  entry : 
* @param[in]  mode : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOGPIO::SetMode(DIOGPIO_ENTRY* entry, XWORD mode)
{
  if(!entry) return false;

  entry->SetMode(mode);  

  return true;
}  



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOGPIO::GetValue(DIOGPIO_ENTRY* entry)
* @brief      GetValue
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  entry : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOGPIO::GetValue(DIOGPIO_ENTRY* entry)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOGPIO::SetValue(DIOGPIO_ENTRY* entry, bool value)
* @brief      SetValue
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  entry : 
* @param[in]  value : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOGPIO::SetValue(DIOGPIO_ENTRY* entry, bool value)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOGPIO::End()
* @brief      End
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOGPIO::End()
{
  GPIOEntry_DeleteAll();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOGPIO::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOGPIO::Clean()
{
  instance            = NULL;

}
