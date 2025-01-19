/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOI2CBatteryChargerBQ24295.cpp
* 
* @class      DIOI2CBATTERYCHARGERBQ24295
* @brief      Data Input/output Battery Charger BQ24295 class
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

#include "DIOI2CBatteryChargerBQ24295.h"

#include <stdio.h>
#include <math.h>

#include "XFactory.h"
#include "XSleep.h"
#include "XBuffer.h"
#include "XTrace.h"

#include "DIOFactory.h"
#include "DIOStreamI2CConfig.h"
#include "DIOStreamI2C.h"

#include "DIOGPIO.h"

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
* @fn         DIOI2CBATTERYCHARGERBQ24295::DIOI2CBATTERYCHARGERBQ24295()
* @brief      Constructor of class
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOI2CBATTERYCHARGERBQ24295::DIOI2CBATTERYCHARGERBQ24295() : DIODEVICEI2C()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOI2CBATTERYCHARGERBQ24295::~DIOI2CBATTERYCHARGERBQ24295()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOI2CBATTERYCHARGERBQ24295::~DIOI2CBATTERYCHARGERBQ24295()
{
  End();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIOI2CBATTERYCHARGERBQ24295::GetGPIOEntryID(int indexentry)
* @brief      Get GPIO entry ID
* @ingroup    DATAIO
*
* @param[in]  indexentry : 
* 
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOI2CBATTERYCHARGERBQ24295::GetGPIOEntryID(int indexentry)
{  
  if(indexentry < 0)                                            return DIOGPIO_ID_NOTDEFINED;
  if(indexentry >= DIOI2CBATTERYCHARGERBQ24295_GPIOENTRYID_END) return DIOGPIO_ID_NOTDEFINED;
    
  return GPIOentryID[indexentry];
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOI2CBATTERYCHARGERBQ24295::SetGPIOEntryID(int indexentry, XDWORD GPIOentryID)
* @brief      Set GPIO entry ID
* @ingroup    DATAIO
*
* @param[in]  indexentry : 
* @param[in]  GPIOentryID : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CBATTERYCHARGERBQ24295::SetGPIOEntryID(int indexentry, XDWORD GPIOentryID)
{
  if(indexentry < 0)                                            return false;
  if(indexentry >= DIOI2CBATTERYCHARGERBQ24295_GPIOENTRYID_END) return false;

  this->GPIOentryID[indexentry] = GPIOentryID;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOI2CBATTERYCHARGERBQ24295::Update()
* @brief      Update
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOI2CBATTERYCHARGERBQ24295::Update()
{  
  if(!charging) return;
            
  // For an unknown reason the stat pin generates an square signal and not holds the low level when is charging
  // so I have to read the register to know when the charge is done
  //I read the register every 5 seconds
    
  XBYTE read_reg_fault;        
  XBYTE read_reg_status;
      
  if(ReadRegister(DIOI2CBATTERYCHARGERBQ24295_FAULT_REG_REG09   , read_reg_fault)  != 0)   return;            //TODO-GFR detect FAULT errors        
  if(ReadRegister(DIOI2CBATTERYCHARGERBQ24295_SYS_STATUS_REG08  , read_reg_status) != 0)   return;            
        
  if(((read_reg_status >> 4) & 0x03) == 0x03) fullycharge = true;          
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOI2CBATTERYCHARGERBQ24295::SetChargerEnable(bool enable)
* @brief      Set charger enable
* @ingroup    DATAIO
* 
* @param[in]  enable : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOI2CBATTERYCHARGERBQ24295::SetChargerEnable(bool enable)
{
  if(enable)
    {
      // Charger enabled
      GEN_DIOGPIO.SetMode(GPIOentryID[DIOI2CBATTERYCHARGERBQ24295_GPIOENTRYID_CE] , DIOGPIO_MODE_INPUT);
    }
   else
    {
      // Charger disabled
      GEN_DIOGPIO.SetMode(GPIOentryID[DIOI2CBATTERYCHARGERBQ24295_GPIOENTRYID_CE] , DIOGPIO_MODE_OUTPUT);  
      fullycharge = false;        
    }

}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOI2CBATTERYCHARGERBQ24295::SetShippingModeEnable(bool enable)
* @brief      Set shipping mode enable
* @ingroup    DATAIO
* 
* @param[in]  enable : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOI2CBATTERYCHARGERBQ24295::SetShippingModeEnable(bool enable)
{
  // Shipping Mode On
  GEN_DIOGPIO.SetValue(GPIOentryID[DIOI2CBATTERYCHARGERBQ24295_GPIOENTRYID_QON]      , true);     
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOI2CBATTERYCHARGERBQ24295::SetIsCharging(bool enable)
* @brief      Set is charging
* @ingroup    DATAIO
* 
* @param[in]  enable : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOI2CBATTERYCHARGERBQ24295::SetIsCharging(bool enable)
{  
  if(charging != (enable?1:0))
    {
      if(enable)
        {
          SetChargerEnable(true);
        }
      else
        {
          SetChargerEnable(false);
        }
    }  
  
  charging = (enable?1:0);  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOI2CBATTERYCHARGERBQ24295::IsBatteryFullyCharged()
* @brief      Is battery fully charged
* @ingroup    DATAIO
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CBATTERYCHARGERBQ24295::IsBatteryFullyCharged()
{
  return fullycharge;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBYTE DIOI2CBATTERYCHARGERBQ24295::GetFaultDetection()
* @brief      Get fault detection
* @ingroup    DATAIO
* 
* @return     XBYTE : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE DIOI2CBATTERYCHARGERBQ24295::GetFaultDetection()
{
  return fault;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOI2CBATTERYCHARGERBQ24295::End()
* @brief      End
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CBATTERYCHARGERBQ24295::End()
{
  if(!DIODEVICE::End()) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOI2CBATTERYCHARGERBQ24295::IniDevice()
* @brief      Ini device
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CBATTERYCHARGERBQ24295::IniDevice()
{  
  if(!DIODEVICEI2C::IniDevice()) return false;

  if(diostream->Open())
    {
      if(diostream->WaitToConnected(timeout))
        {             
          if(!Initialize()) return false;
          
          return DIODEVICE::Ini();
        }
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOI2CBATTERYCHARGERBQ24295::Initialize()
* @brief      Initialize
* @ingroup    DATAIO
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CBATTERYCHARGERBQ24295::Initialize()
{
  // Charger GPIO Inputs
  GEN_DIOGPIO.SetMode(GPIOentryID[DIOI2CBATTERYCHARGERBQ24295_GPIOENTRYID_STAT]  , DIOGPIO_MODE_INPUT);          
            
  // Charger GPIO Outputs
  GEN_DIOGPIO.SetMode(GPIOentryID[DIOI2CBATTERYCHARGERBQ24295_GPIOENTRYID_QON]   , DIOGPIO_MODE_OUTPUT);
  GEN_DIOGPIO.SetMode(GPIOentryID[DIOI2CBATTERYCHARGERBQ24295_GPIOENTRYID_CE]    , DIOGPIO_MODE_OUTPUT);
          
  // Charger GPIO Interrupts
  DIOGPIO_ENTRY* interrupt = GEN_DIOGPIO.GPIOEntry_GetByID(GPIOentryID[DIOI2CBATTERYCHARGERBQ24295_GPIOENTRYID_INT]);
  if(interrupt)
    {
      interrupt->SetIntFunctionPointer(DIOI2CBATTERYCHARGERBQ24295::Handler_Interrupt);      
      interrupt->SetIntParamPointer((void*)this);      
      GEN_DIOGPIO.SetMode(GPIOentryID[DIOI2CBATTERYCHARGERBQ24295_GPIOENTRYID_INT], DIOGPIO_MODE_INTERRUPT); 
    }
          
  // Charger disabled
  GEN_DIOGPIO.SetValue(GPIOentryID[DIOI2CBATTERYCHARGERBQ24295_GPIOENTRYID_CE]  , true);                     
          
  // Shipping Mode off
  GEN_DIOGPIO.SetValue(GPIOentryID[DIOI2CBATTERYCHARGERBQ24295_GPIOENTRYID_QON]  , false);           
          
  charging    = false;
  fault       = 0;
  fullycharge = false;
          
  // Configure the charger ILMAX to 500mA  
  XBYTE read_reg;

  if(!ReadRegister(DIOI2CBATTERYCHARGERBQ24295_INPUT_SRC_CTRL_REG00, read_reg))         return false;
          
  // IINLIM bits (010) (500mA)
  read_reg &= 0xF8;
  read_reg |= 0x02;
          
  if(!WriteRegister(DIOI2CBATTERYCHARGERBQ24295_INPUT_SRC_CTRL_REG00, read_reg))        return false;
                   
  // Disable the charger watchdog timer and the safety timer
  if(!ReadRegister(DIOI2CBATTERYCHARGERBQ24295_CHRG_TERM_TIMER_CTRL_REG05, read_reg))   return false;
          
  // Disable timer
  read_reg &= 0xC7;
  if(!WriteRegister(DIOI2CBATTERYCHARGERBQ24295_INPUT_SRC_CTRL_REG00, read_reg))        return false;          
                                
  return true;  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOI2CBATTERYCHARGERBQ24295::ReadRegister(XBYTE offset, XBYTE& data)
* @brief      Read register
* @ingroup    DATAIO
* 
* @param[in]  offset : 
* @param[in]  data : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CBATTERYCHARGERBQ24295::ReadRegister(XBYTE offset, XBYTE& data)
{
  return ReadRegister(offset, &data, 1);
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOI2CBATTERYCHARGERBQ24295::ReadRegister(XBYTE offset, XBYTE* data, XDWORD sizedata)
* @brief      Read register
* @ingroup    DATAIO
* 
* @param[in]  offset : 
* @param[in]  data : 
* @param[in]  sizedata : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CBATTERYCHARGERBQ24295::ReadRegister(XBYTE offset, XBYTE* data, XDWORD sizedata)
{
  if(!diostream) return false;

  bool status;

  status = diostream->Write(&offset, 1)?true:false;
  if(status) status = diostream->WaitToFlushOutXBuffer(timeout);

  if(!status) return false;

  status = diostream->WaitToFilledReadingBuffer(sizedata, timeout);
  if(status) status = (diostream->Read(data, sizedata) == sizedata)?true:false;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOI2CBATTERYCHARGERBQ24295::WriteRegister(XBYTE offset, XBYTE data)
* @brief      Write register
* @ingroup    DATAIO
* 
* @param[in]  offset : 
* @param[in]  data : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CBATTERYCHARGERBQ24295::WriteRegister(XBYTE offset, XBYTE data)
{
  return WriteRegister(offset, &data, 1);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOI2CBATTERYCHARGERBQ24295::WriteRegister(XBYTE offset, XBYTE* data, XDWORD sizedata)
* @brief      Write register
* @ingroup    DATAIO
* 
* @param[in]  offset : 
* @param[in]  data : 
* @param[in]  sizedata : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CBATTERYCHARGERBQ24295::WriteRegister(XBYTE offset, XBYTE* data, XDWORD sizedata)
{
  if(!diostream) return false;

  XBUFFER buffer;
  bool    status;

  buffer.Add((XBYTE)offset);
  if(data && sizedata) buffer.Add(data, sizedata);

  status = diostream->Write(buffer)?true:false;
  if(status) status = diostream->WaitToFlushOutXBuffer(timeout);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOI2CBATTERYCHARGERBQ24295::Handler_Interrupt(void* param)
* @brief      Handler interrupt
* @ingroup    DATAIO
*
* @param[in]  param : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOI2CBATTERYCHARGERBQ24295::Handler_Interrupt(void* param)
{

}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOI2CBATTERYCHARGERBQ24295::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOI2CBATTERYCHARGERBQ24295::Clean()
{
  for(XDWORD c=0; c<DIOI2CBATTERYCHARGERBQ24295_GPIOENTRYID_END; c++)
    {
      GPIOentryID[c] = DIOGPIO_ID_NOTDEFINED;
    }

  charging     = false;    
  fault        = 0;
  fullycharge  = false;    
}


#pragma endregion

