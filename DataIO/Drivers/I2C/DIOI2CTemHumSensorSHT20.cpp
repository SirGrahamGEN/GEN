/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOI2CTemHumSensorSHT20.cpp
* 
* @class      DIOI2CTEMHUMSENSORSHT20
* @brief      Data Input/Output I2C Sensor Sensirion SHT20 (Temperature and humidity module) class
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

#include "DIOI2CTemHumSensorSHT20.h"

#include "XFactory.h"
#include "XSleep.h"
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
* @fn         DIOI2CTEMHUMSENSORSHT20::DIOI2CTEMHUMSENSORSHT20()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOI2CTEMHUMSENSORSHT20::DIOI2CTEMHUMSENSORSHT20(): DIODEVICEI2C()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOI2CTEMHUMSENSORSHT20::~DIOI2CTEMHUMSENSORSHT20()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOI2CTEMHUMSENSORSHT20::~DIOI2CTEMHUMSENSORSHT20()
{
  End();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CTEMHUMSENSORSHT20::Reset()
* @brief      Reset
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CTEMHUMSENSORSHT20::Reset()
{
  if(!diostream) return false;

  XBUFFER buffer;
  bool    status;

  buffer.Add((XBYTE)DIOI2CTEMHUMSENSORSHT20_CMD_SOFT_RESET);

  status = diostream->Write(buffer)?true:false;
  if(status) status = diostream->WaitToFlushOutXBuffer(timeout);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CTEMHUMSENSORSHT20::SetResolution(XBYTE resolution)
* @brief      Set resolution
* @ingroup    DATAIO
*
* @param[in]  resolution :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CTEMHUMSENSORSHT20::SetResolution(XBYTE resolution)
{
  XBYTE userregister = 0;

  if(!ReadUserRegister(userregister)) return false;

  userregister &= 0x7E;
  resolution   &= 0x81;

  userregister |= resolution;

  return WriteUserRegister(userregister);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CTEMHUMSENSORSHT20::Read(float& temperature, float& humidity)
* @brief      Read
* @ingroup    DATAIO
*
* @param[in]  temperature :
* @param[in]  humidity :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CTEMHUMSENSORSHT20::Read(float& temperature, float& humidity)
{
  if(!diostream)        return false;
  if(!IsInitialized())  return false;

  XWORD rawhumidity     = 0;
  XWORD rawtemperature  = 0;

  if(!ReadValue(DIOI2CTEMHUMSENSORSHT20_CMD_TRIGGER_HUMD_MEASURE_NOHOLD, rawhumidity))
    {
      return false;
    }

  float temporalhumidity = rawhumidity * (125.0f / 65536.0f);
  humidity = temporalhumidity - 6.0f;

  if(!ReadValue(DIOI2CTEMHUMSENSORSHT20_CMD_TRIGGER_TEMP_MEASURE_NOHOLD, rawtemperature)) return false;

  float temporaltemperature = rawtemperature * (175.72f / 65536.0f);
  temperature= temporaltemperature - 46.85f;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CTEMHUMSENSORSHT20::End()
* @brief      End
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CTEMHUMSENSORSHT20::End()
{
  if(!DIODEVICEI2C::End()) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CTEMHUMSENSORSHT20::IniDevice()
* @brief      Ini device
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CTEMHUMSENSORSHT20::IniDevice()
{
  if(!DIODEVICEI2C::IniDevice()) return false;

  if(diostream->Open())
    {
      if(diostream->WaitToConnected(timeout))
        {
          Reset();

          return DIODEVICE::Ini();
        }
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CTEMHUMSENSORSHT20::ReadValue(XBYTE cmd, XWORD value)
* @brief      Read value
* @ingroup    DATAIO
*
* @param[in]  cmd :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CTEMHUMSENSORSHT20::ReadValue(XBYTE cmd, XWORD& value)
{
  if(!diostream)
    {     
      return false;
    }

  bool  status;
  XBYTE command = cmd;

  status = diostream->Write(&command, 1)?true:false;
  if(status) status = diostream->WaitToFlushOutXBuffer(timeout);

  if(!status)
    {    
      return false;
    }

  GEN_XSLEEP.MilliSeconds(200);

  XBYTE data[3] = { 0, 0, 0 };

  status = diostream->WaitToFilledReadingBuffer(3, timeout);
  if(status)
    {
      status = (diostream->Read(data, 3) == 3)?true:false;
      if(!status)
        {         
          return false;
        }
    }
   else
    {
      return false;
    }

  XBYTE msb      = data[0];
  XBYTE lsb      = data[1];
  XBYTE checksum = data[2];

  XWORD rawvalue = ((XWORD) msb << 8) | (XWORD) lsb;

  if(!CheckCRC(rawvalue, checksum))
    {
      return false;
    }

  value = rawvalue & 0xFFFC;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CTEMHUMSENSORSHT20::ReadUserRegister(XBYTE& userregister)
* @brief      Read user register
* @ingroup    DATAIO
*
* @param[in]  userregister :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CTEMHUMSENSORSHT20::ReadUserRegister(XBYTE& userregister)
{
  if(!diostream) return false;

  XBYTE data;
  bool  status;

  XBYTE command = DIOI2CTEMHUMSENSORSHT20_CMD_READ_USER_REG;

  status = diostream->Write(&command, 1)?true:false;
  if(status) status = diostream->WaitToFlushOutXBuffer(timeout);

  if(!status) return false;

  status = diostream->WaitToFilledReadingBuffer(1, timeout);
  if(status) status = (diostream->Read(&data, 1) == 1)?true:false;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CTEMHUMSENSORSHT20::WriteUserRegister(XBYTE userregister)
* @brief      Write user register
* @ingroup    DATAIO
*
* @param[in]  userregister :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CTEMHUMSENSORSHT20::WriteUserRegister(XBYTE userregister)
{
  if(!diostream) return false;

  XBUFFER buffer;
  bool    status;

  buffer.Add((XBYTE)DIOI2CTEMHUMSENSORSHT20_CMD_WRITE_USER_REG);
  buffer.Add((XBYTE)userregister);

  status = diostream->Write(buffer)?true:false;
  if(status) status = diostream->WaitToFlushOutXBuffer(timeout);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CTEMHUMSENSORSHT20::CheckCRC(XWORD datasensor, XBYTE checkvalue)
* @brief      Check CRC
* @ingroup    DATAIO
*
* @param[in]  datasensor :
* @param[in]  checkvalue :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CTEMHUMSENSORSHT20::CheckCRC(XWORD datasensor, XBYTE checkvalue)
{
  XDWORD remainder = (XDWORD)datasensor << 8;

  remainder |= checkvalue;

  XDWORD divisor = (XDWORD)DIOI2CTEMHUMSENSORSHT20_SHIFTED_DIVISOR;

  for(int c=0; c < 16 ; c++)
    {
      if(remainder & (XDWORD)1 << (23 - c))
        {
          remainder ^= divisor;
        }

      divisor >>= 1;
    }

  return remainder?false:true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOI2CTEMHUMSENSORSHT20::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOI2CTEMHUMSENSORSHT20::Clean()
{

}


#pragma endregion

