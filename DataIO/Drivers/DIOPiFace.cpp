/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOPiFace.cpp
* 
* @class      DIOPIFACE
* @brief      Data Input/Output Rasberry Pi Face class
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

#include "DIOPiFace.h"

#include "XFactory.h"
#include "XBuffer.h"

#include "DIOFactory.h"
#include "DIOStreamSPIConfig.h"
#include "DIOStreamSPI.h"

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
* @fn         DIOPIFACE::DIOPIFACE()
* @brief      Constructor of class
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOPIFACE::DIOPIFACE() : DIOSPIGPIOMCP23S17()
{

}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPIFACE::~DIOPIFACE()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOPIFACE::~DIOPIFACE()
{

}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPIFACE::Configure()
* @brief      Configure
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPIFACE::Configure()
{         
  Write_Register(DIOSPIGPIOMCP23S17_WRITE_CMD, DIOSPIGPIOMCP23S17_IOCON   , 8);     // Enable hardware addressing
  Write_Register(DIOSPIGPIOMCP23S17_WRITE_CMD, DIOSPIGPIOMCP23S17_GPIOA   , 0x00);  // Turn on port A
  Write_Register(DIOSPIGPIOMCP23S17_WRITE_CMD, DIOSPIGPIOMCP23S17_IODIRA  , 0);     // Set port A as an output
  Write_Register(DIOSPIGPIOMCP23S17_WRITE_CMD, DIOSPIGPIOMCP23S17_IODIRB  , 0xFF);  // Set port B as an input
  Write_Register(DIOSPIGPIOMCP23S17_WRITE_CMD, DIOSPIGPIOMCP23S17_GPPUB   , 0xFF);  // Turn on port B pullups

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPIFACE::ReadInputs(XBYTE& value)
* @brief      Read inputs
* @ingroup    DATAIO
* 
* @param[in]  value : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPIFACE::ReadInputs(XBYTE& value)
{
  XBYTE _value[3] = { 0xFF, 0xFF, 0xFF };

  if(!diostream) return false;

  diostream->GetInXBuffer()->Delete();

  if(!Write_Register(DIOSPIGPIOMCP23S17_READ_CMD, DIOPIFACE_INPUTPORT, 0xFF)) return false;

  if(!diostream->WaitToFilledReadingBuffer(3, timeout)) return false;

  bool status = diostream->Read(_value, 3)?true:false;

  value = _value[2] ^ 0xFF;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPIFACE::WriteOutputs(XBYTE value)
* @brief      Write outputs
* @ingroup    DATAIO
* 
* @param[in]  value : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPIFACE::WriteOutputs(XBYTE value)
{
  return Write_Register(DIOSPIGPIOMCP23S17_WRITE_CMD, DIOPIFACE_OUTPUTPORT, value);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPIFACE::End()
* @brief      End
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPIFACE::End()
{
  WriteOutputs(0x00);

  return DIOSPIGPIOMCP23S17::End();
}


#pragma endregion

