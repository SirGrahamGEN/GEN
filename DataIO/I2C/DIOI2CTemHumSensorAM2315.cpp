/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOI2CTemHumSensorAM2315.cpp
*
* @class      DIOI2CTEMHUMSENSORAM2315
* @brief      Data Input/Output I2C Sensor AOSONG AM2315 class (Temperature and humidity module)
* @ingroup    DATAIO
*
* @copyright  GEN Group. All right reserved.
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

#include "XFactory.h"
#include "XSleep.h"
#include "XBuffer.h"
#include "XTrace.h"

#include "DIOFactory.h"
#include "DIOStreamI2CConfig.h"
#include "DIOStreamI2C.h"

#include "DIOI2CTemHumSensorAM2315.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOI2CTEMHUMSENSORAM2315::DIOI2CTEMHUMSENSORAM2315()
* @brief      Constructor
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOI2CTEMHUMSENSORAM2315::DIOI2CTEMHUMSENSORAM2315(): DIODEVICEI2C()
{
  Clean();
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOI2CTEMHUMSENSORAM2315::~DIOI2CTEMHUMSENSORAM2315()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOI2CTEMHUMSENSORAM2315::~DIOI2CTEMHUMSENSORAM2315()
{
  End();

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CTEMHUMSENSORAM2315::Read(float& temperature, float& humidity)
* @brief      Read
* @ingroup    DATAIO
*
* @param[in]  temperature :
* @param[in]  humidity :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CTEMHUMSENSORAM2315::Read(float& temperature, float& humidity)
{
  if(!diostream)        return false;
  if(!IsInitialized())  return false;

  bool  status    = false;
  XBYTE cmd[3]    = { 0x03, 0x00, 0x04 };
  XBYTE answer[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

  status = diostream->Write(cmd, 3)?true:false;
  if(status) status = diostream->WaitToFlushOutXBuffer(timeout);

  if(!status) return false;

  status = diostream->WaitToFilledReadingBuffer(8, timeout);
  if(status) status = diostream->Read(answer, 8)?true:false;

  if(status)
    {
      //XTRACE_PRINTCOLOR(2, __L("%02X %02X %02X %02X %02X %02X %02X %02X"), answer[0], answer[1], answer[2], answer[3], answer[4], answer[5], answer[6], answer[7]);

      XWORD  CRC       = (answer[7]<<8) + answer[6];
      XWORD  CRCbuffer = 0;
      double rhtfactor = 0.1;

      if((answer[0] != cmd[0]) ||
         (answer[1] != cmd[2])) return false;

      CalculeCRC(answer, CRCbuffer);

      if(CRC != CRCbuffer) return false;

      humidity    = (float)(rhtfactor * (double)(answer[3] + (answer[2] << 8)));
      temperature = (float)(rhtfactor * (double)(answer[5] + (answer[4] << 8)));
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CTEMHUMSENSORAM2315::End()
* @brief      End
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CTEMHUMSENSORAM2315::End()
{
  if(!DIODEVICEI2C::End()) return false;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CTEMHUMSENSORAM2315::IniDevice()
* @brief      IniDevice
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CTEMHUMSENSORAM2315::IniDevice()
{
  if(!DIODEVICEI2C::IniDevice()) return false;

  if(diostream->Open())
    {
      if(diostream->WaitToConnected(timeout))
        {          
          return DIODEVICE::Ini();
        }
    }

  return false;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CTEMHUMSENSORAM2315::CalculeCRC(XBYTE* buffer, XWORD& CRC)
* @brief      CalculeCRC
* @ingroup    DATAIO
*
* @param[in]  buffer :
* @param[in]  CRC :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CTEMHUMSENSORAM2315::CalculeCRC(XBYTE* buffer, XWORD& CRC)
{
  CRC = 0xFFFF;

  for(int l=0; l<6; l++)
    {
      CRC ^= buffer[l];

      for(int i=0; i<8; i++)
        {
          if(CRC & 0x01)
            {
              CRC >>= 1;
              CRC ^=  0xA001;
            }
           else
            {
              CRC >>= 1;
            }
        }
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOI2CTEMHUMSENSORAM2315::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOI2CTEMHUMSENSORAM2315::Clean()
{

}



