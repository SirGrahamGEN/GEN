/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOI2CAirQualityCCS811.cpp
* 
* @class      DIOI2CAIRQUALITYCCS811
* @brief      Data Input/Output I2C Sensor CCS811 (Air Quality) class 
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

#include "DIOI2CAirQualityCCS811.h"

#include <stdio.h>
#include <math.h>

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
* @fn         DIOI2CAIRQUALITYCCS811::DIOI2CAIRQUALITYCCS811() : DIODEVICEI2C()
* @brief      Constructor of class
* @ingroup    DATAIO
*
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOI2CAIRQUALITYCCS811::DIOI2CAIRQUALITYCCS811() : DIODEVICEI2C()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOI2CAIRQUALITYCCS811::~DIOI2CAIRQUALITYCCS811()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOI2CAIRQUALITYCCS811::~DIOI2CAIRQUALITYCCS811()
{
  End();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CAIRQUALITYCCS811::GetHW_ID(XBYTE& ID)
* @brief      Get HWID
* @ingroup    DATAIO
*
* @param[in]  ID :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CAIRQUALITYCCS811::GetHW_ID(XBYTE& ID)
{
  if(!diostream) return false;

  ID = 0;

  return ReadRegister(DIOI2CAIRQUALITYCCS811_OFFSET_HW_ID, ID);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CAIRQUALITYCCS811::GetHW_Version(XBYTE& hwversion)
* @brief      Get HW version
* @ingroup    DATAIO
*
* @param[in]  hwversion :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CAIRQUALITYCCS811::GetHW_Version(XBYTE& hwversion)
{
  if(!diostream) return false;

  hwversion = 0;

  return ReadRegister(DIOI2CAIRQUALITYCCS811_OFFSET_HW_VERSION, hwversion);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CAIRQUALITYCCS811::GetBoot_Version(XWORD& bootversion)
* @brief      Get boot version
* @ingroup    DATAIO
*
* @param[in]  bootversion :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CAIRQUALITYCCS811::GetBoot_Version(XWORD& bootversion)
{
  if(!diostream) return false;

  XBYTE data[2];

  memset(data, 0, sizeof(data));

  bool status = ReadRegister(DIOI2CAIRQUALITYCCS811_OFFSET_FW_BOOT_VERSION, data, sizeof(data));

  bootversion   = data[1];
  bootversion <<= 8;
  bootversion  |= data[0];

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CAIRQUALITYCCS811::GetApp_Version(XWORD& appversion)
* @brief      Get app version
* @ingroup    DATAIO
*
* @param[in]  appversion :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CAIRQUALITYCCS811::GetApp_Version(XWORD& appversion)
{
  if(!diostream) return false;

  XBYTE data[2];

  memset(data, 0, sizeof(data));

  bool status = ReadRegister(DIOI2CAIRQUALITYCCS811_OFFSET_FW_APP_VERSION, data, sizeof(data));

  appversion   = data[1];
  appversion <<= 8;
  appversion  |= data[0];

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CAIRQUALITYCCS811::ResetDevice()
* @brief      Reset device
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CAIRQUALITYCCS811::ResetDevice()
{
  if(!diostream) return false;

  XBYTE data[4] = { 0x11, 0xE5, 0x72, 0x8A }; // Reset key

  //Reset the device
  bool status = WriteRegister(DIOI2CAIRQUALITYCCS811_OFFSET_SW_RESET, data, sizeof(data));

  GEN_XSLEEP.MilliSeconds(500);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE DIOI2CAIRQUALITYCCS811::GetStatus()
* @brief      Get status
* @ingroup    DATAIO
*
* @return     XBYTE :
*
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE DIOI2CAIRQUALITYCCS811::GetStatus(XBYTE& sensorstatus)
{
  sensorstatus = 0;

  bool status = ReadRegister(DIOI2CAIRQUALITYCCS811_OFFSET_STATUS, sensorstatus);
  if(!status) return 0x00;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CAIRQUALITYCCS811::IsAppValid()
* @brief      Is app valid
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CAIRQUALITYCCS811::IsAppValid()
{
  XBYTE sensorstatus = 0;

  if(!GetStatus(sensorstatus)) return false;

  return (sensorstatus & (0x01 << 4))?true:false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOI2CAIRQUALITYCCS811::IsDataAvailable()
* @brief      Is data available
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CAIRQUALITYCCS811::IsDataAvailable()
{
  XBYTE sensorstatus = 0;

  if(!GetStatus(sensorstatus)) return false;

  return (sensorstatus & (0x01 << 3))?true:false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CAIRQUALITYCCS811::HaveStatusError()
* @brief      Have status error
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CAIRQUALITYCCS811::HaveStatusError()
{
  XBYTE sensorstatus = 0;

  if(!GetStatus(sensorstatus)) return false;

  return (sensorstatus & (0x01 << 0))?true:false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE DIOI2CAIRQUALITYCCS811::GetStatusErrorCode()
* @brief      Get status error code
* @ingroup    DATAIO
*
* @return     XBYTE :
*
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE DIOI2CAIRQUALITYCCS811::GetStatusErrorCode()
{
  XBYTE value = 0;

  bool status = ReadRegister(DIOI2CAIRQUALITYCCS811_OFFSET_ERROR_ID, value);
  if(!status) return 0xFF;

  return value;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWORD DIOI2CAIRQUALITYCCS811::GetBaseline()
* @brief      Get baseline
* @ingroup    DATAIO
*
* @return     XWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XWORD DIOI2CAIRQUALITYCCS811::GetBaseline()
{
  XBYTE  data[2];

  bool status = ReadRegister(DIOI2CAIRQUALITYCCS811_OFFSET_BASELINE, data, 2);

  XWORD baseline = ((XWORD)data[0] << 8) | data[1];
  if(!status) return 0;

  return baseline;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CAIRQUALITYCCS811::SetBaseline(XWORD baseline)
* @brief      Set baseline
* @ingroup    DATAIO
*
* @param[in]  baseline :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CAIRQUALITYCCS811::SetBaseline(XWORD baseline)
{
  XBYTE data[2];

  data[0] = (baseline >> 8) & 0x00FF;
  data[1] = baseline & 0x00FF;

  return WriteRegister(DIOI2CAIRQUALITYCCS811_OFFSET_SW_RESET, data, sizeof(data));
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CAIRQUALITYCCS811::SetDriveMode(XBYTE mode)
* @brief      Set drive mode
* @ingroup    DATAIO
*
* @param[in]  mode : Mode 0 = Idle
*                    Mode 1 = read every 1s
*                    Mode 2 = every 10s
*                    Mode 3 = every 60s
*                    Mode 4 = RAW mode
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CAIRQUALITYCCS811::SetDriveMode(XBYTE mode)
{
  if(mode > 4) mode = 4; // sanitize input

  XBYTE value = 0;

  bool status = ReadRegister(DIOI2CAIRQUALITYCCS811_OFFSET_MEAS_MODE, value);   //  Read what's currently there
  if(!status) return false;

  value &= ~(0x03 << 4);  //  Clear DRIVE_MODE bits
  value |=  (mode << 4);  //  Mask in mode

  status = WriteRegister(DIOI2CAIRQUALITYCCS811_OFFSET_MEAS_MODE, value);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CAIRQUALITYCCS811::SetEnvironmentalData(float relativehumidity, float temperature)
* @brief      Set environmental data
* @ingroup    DATAIO
*
* @param[in]  relativehumidity :
* @param[in]  temperature :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CAIRQUALITYCCS811::SetEnvironmentalData(float relativehumidity, float temperature)
{
  if((temperature < -25)    || (temperature > 50))        return false;
  if((relativehumidity < 0) || (relativehumidity > 100))  return false;

  XDWORD rhum   = (XDWORD)(relativehumidity * 1000);  //42.348 becomes 42348
  XDWORD temp   = (XDWORD)(temperature      * 1000);  //23.2 becomes 23200

  XBYTE envdata[4];

  //Split value into 7-bit integer and 9-bit fractional

  //Incorrect way from datasheet.
  //envData[0] = ((rH % 1000) / 100) > 7 ? (rH / 1000 + 1) << 1 : (rH / 1000) << 1;
  //envData[1] = 0; //CCS811 only supports increments of 0.5 so bits 7-0 will always be zero
  //if (((rH % 1000) / 100) > 2 && (((rH % 1000) / 100) < 8))
  //{
  //  envData[0] |= 1; //Set 9th bit of fractional to indicate 0.5%
  //}

  //Correct rounding. See issue 8: https://github.com/sparkfun/Qwiic_BME280_CCS811_Combo/issues/8
  envdata[0] = (rhum + 250) / 500;
  envdata[1] = 0;                   //CCS811 only supports increments of 0.5 so bits 7-0 will always be zero

  temp += 25000; //Add the 25C offset

  //Split value into 7-bit integer and 9-bit fractional
  //envData[2] = ((temp % 1000) / 100) > 7 ? (temp / 1000 + 1) << 1 : (temp / 1000) << 1;
  //envData[3] = 0;
  //if (((temp % 1000) / 100) > 2 && (((temp % 1000) / 100) < 8))
  //{
  //  envData[2] |= 1;  //Set 9th bit of fractional to indicate 0.5C
  //}

  //Correct rounding
  envdata[2] = (temp + 250) / 500;
  envdata[3] = 0;

  return WriteRegister(DIOI2CAIRQUALITYCCS811_OFFSET_ENV_DATA, envdata, sizeof(envdata));
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float DIOI2CAIRQUALITYCCS811::GetReferenceResistance()
* @brief      Get reference resistance
* @ingroup    DATAIO
*
* @return     float :
*
* --------------------------------------------------------------------------------------------------------------------*/
float DIOI2CAIRQUALITYCCS811::GetReferenceResistance()
{
  return referenceresistance;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOI2CAIRQUALITYCCS811::SetReferenceResistance(float referenceresistance)
* @brief      Set reference resistance
* @ingroup    DATAIO
*
* @param[in]  referenceresistance :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOI2CAIRQUALITYCCS811::SetReferenceResistance(float referenceresistance)
{
  this->referenceresistance = referenceresistance;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CAIRQUALITYCCS811::ReadNTC(float& temperature, float& resistance)
* @brief      Read NTC
* @ingroup    DATAIO
*
* @param[out] temperature :
* @param[out] resistance :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CAIRQUALITYCCS811::ReadNTC(float& temperature, float& resistance)
{
  XBYTE data[4];
  XWORD vrefcounts = 0;
  XWORD ntccounts  = 0;

  memset(data, 0, sizeof(data));

  bool status = ReadRegister(DIOI2CAIRQUALITYCCS811_OFFSET_NTC, data, sizeof(data));

  vrefcounts  = ((XWORD)data[0] << 8) | data[1];
  ntccounts   = ((XWORD)data[2] << 8) | data[3];
  resistance  = ((float)ntccounts * referenceresistance / (float)vrefcounts);

  temperature = (float)log((long)resistance);
  temperature = (float)(1 / (0.001129148 + (0.000234125 * temperature) + (0.0000000876741 * temperature * temperature * temperature)));
  temperature = (float)(temperature - 273.15);  // Convert Kelvin to Celsius

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOI2CAIRQUALITYCCS811::ReadData(XWORD& TVOC, XWORD& CO2)
* @brief      Read data
* @ingroup    DATAIO
* 
* @param[in]  TVOC : 
* @param[in]  CO2 : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CAIRQUALITYCCS811::ReadData(XWORD& TVOC, XWORD& CO2)
{
  if(!diostream)        return false;
  if(!IsInitialized())  return false;

  XBYTE data[4];
  bool  status = false;

  memset(data, 0, sizeof(data));

  TVOC = 0;
  CO2  = 0;

  status = ReadRegister(DIOI2CAIRQUALITYCCS811_OFFSET_ALG_RESULT_DATA, data, sizeof(data));
  if(status)
    {
      CO2  = ((XWORD)data[0] << 8) | data[1];
      TVOC = ((XWORD)data[2] << 8) | data[3];
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOI2CAIRQUALITYCCS811::SetInterrupt(bool activated)
* @brief      Set interrupt
* @ingroup    DATAIO
* 
* @param[in]  activated : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CAIRQUALITYCCS811::SetInterrupt(bool activated)
{
  XBYTE value = 0;

  bool status = ReadRegister(DIOI2CAIRQUALITYCCS811_OFFSET_MEAS_MODE, value);   //  Read what's currently there
  if(!status) return false;

  if(activated)
    {
      value |=  (0x01 << 3); //Set INTERRUPT bit
    }
   else
    {
      value &= ~(0x01 << 3); //Clear INTERRUPT bit
    }

  status = WriteRegister(DIOI2CAIRQUALITYCCS811_OFFSET_MEAS_MODE, value);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CAIRQUALITYCCS811::End()
* @brief      End
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CAIRQUALITYCCS811::End()
{
  if(!DIODEVICEI2C::End()) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CAIRQUALITYCCS811::IniDevice()
* @brief      Ini device
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CAIRQUALITYCCS811::IniDevice()
{
  if(!DIODEVICEI2C::IniDevice()) return false;

  if(diostream->Open())
    {
      if(diostream->WaitToConnected(timeout))
        {
          XBYTE ID = 0;
          if(!GetHW_ID(ID)) return false;
          if(ID != DIOI2CAIRQUALITYCCS811_HW_ID) return false;

          if(!IsAppValid()) return false;

          if(!ResetDevice()) return false;

          WriteRegister(DIOI2CAIRQUALITYCCS811_OFFSET_APP_START, NULL, 0);

          return DIODEVICE::Ini();
        }
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOI2CAIRQUALITYCCS811::ReadRegister(XBYTE offset, XBYTE& data)
* @brief      Read register
* @ingroup    DATAIO
* 
* @param[in]  offset : 
* @param[in]  data : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CAIRQUALITYCCS811::ReadRegister(XBYTE offset, XBYTE& data)
{
  return ReadRegister(offset, &data, 1);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CAIRQUALITYCCS811::ReadRegister(XBYTE offset, XBYTE* data, XDWORD sizedata)
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
bool DIOI2CAIRQUALITYCCS811::ReadRegister(XBYTE offset, XBYTE* data, XDWORD sizedata)
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
* @fn         bool DIOI2CAIRQUALITYCCS811::WriteRegister(XBYTE offset, XBYTE data)
* @brief      Write register
* @ingroup    DATAIO
*
* @param[in]  offset :
* @param[in]  data :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CAIRQUALITYCCS811::WriteRegister(XBYTE offset, XBYTE data)
{
  return WriteRegister(offset, &data, 1);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CAIRQUALITYCCS811::WriteRegister(XBYTE offset, XBYTE* data, XDWORD sizedata)
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
bool DIOI2CAIRQUALITYCCS811::WriteRegister(XBYTE offset, XBYTE* data, XDWORD sizedata)
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
* @fn         void DIOI2CAIRQUALITYCCS811::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOI2CAIRQUALITYCCS811::Clean()
{
  referenceresistance   = 0.0f;
}


#pragma endregion

