/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOI2CGPIOMCP2317.cpp
* 
* @class      DIOI2CGPIOMCP2317
* @brief      Data Input/Output I2C MCP23S17 (Microchip) (8+8 Digital I/O) class
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

#include "DIOI2CGPIOMCP2317.h"

#include "XFactory.h"
#include "XBuffer.h"
#include "XTrace.h"

#include "DIOFactory.h"
#include "DIOStreamI2CConfig.h"
#include "DIOStreamI2C.h"

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
* @fn         DIOI2CGPIOMCP2317::DIOI2CGPIOMCP2317()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOI2CGPIOMCP2317::DIOI2CGPIOMCP2317() :  DIODEVICEI2C()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOI2CGPIOMCP2317::~DIOI2CGPIOMCP2317()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOI2CGPIOMCP2317::~DIOI2CGPIOMCP2317()
{
  End();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOI2CGPIOMCP2317::Configure(XBYTE port_A, XBYTE port_B)
* @brief      Configure
* @ingroup    DATAIO
*
* @param[in]  port_A : 
* @param[in]  port_B : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CGPIOMCP2317::Configure(XBYTE port_A, XBYTE port_B)
{
  SendCommand(DIOI2CGPIOMCP2317_IODIR + DIOI2CGPIOMCP2317PORT_A, port_A);
  SendCommand(DIOI2CGPIOMCP2317_IODIR + DIOI2CGPIOMCP2317PORT_B, port_B);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CGPIOMCP2317::ReadInputs(DIOI2CGPIOMCP2317PORT port, XBYTE& value)
* @brief      Read inputs
* @ingroup    DATAIO
*
* @param[in]  port :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CGPIOMCP2317::ReadInputs(DIOI2CGPIOMCP2317PORT port, XBYTE& value)
{
  if(!diostream)        return false;
  if(!IsInitialized())  return false;

  XBYTE cmd  = DIOI2CGPIOMCP2317_GPIO + port;

  bool status = diostream->Write(&cmd, 1)?true:false;
  if(!diostream->WaitToFlushOutXBuffer(timeout)) return false;

  status = diostream->WaitToFilledReadingBuffer(1, timeout);
  if(status) status = diostream->Read(&value, 1)?true:false;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CGPIOMCP2317::WriteOutputs(DIOI2CGPIOMCP2317PORT port, XBYTE value)
* @brief      Write outputs
* @ingroup    DATAIO
*
* @param[in]  port :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CGPIOMCP2317::WriteOutputs(DIOI2CGPIOMCP2317PORT port, XBYTE value)
{
  XBYTE cmd = (DIOI2CGPIOMCP2317_OLAT + port);

  return SendCommand(cmd, value);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CGPIOMCP2317::SendCommand(XBYTE cmd, XBYTE value)
* @brief      Send command
* @ingroup    DATAIO
*
* @param[in]  cmd :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CGPIOMCP2317::SendCommand(XBYTE cmd, XBYTE value)
{
  if(!diostream)        return false;
  if(!IsInitialized())  return false;

  XBUFFER xbuffer;

  xbuffer.Add((XBYTE)cmd);
  xbuffer.Add((XBYTE)value);

  bool status = diostream->Write(xbuffer)?true:false;

  if(!diostream->WaitToFlushOutXBuffer(timeout)) return false;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CGPIOMCP2317::End()
* @brief      End
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CGPIOMCP2317::End()
{
  if(!DIODEVICEI2C::End()) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CGPIOMCP2317::IniDevice()
* @brief      Ini device
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CGPIOMCP2317::IniDevice()
{  
  if(!DIODEVICEI2C::IniDevice()) return false;
  
  if(diostream->Open())  
    {
      if(!diostream->WaitToConnected(timeout)) return false;
     
      if(!DIODEVICE::Ini()) return false;
      
      return Configure();      
    }
  
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOI2CGPIOMCP2317::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOI2CGPIOMCP2317::Clean()
{
  diostream     = NULL;
}


#pragma endregion

