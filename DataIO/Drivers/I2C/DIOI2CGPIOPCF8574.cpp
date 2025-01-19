/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOI2CGPIOPCF8574.cpp
* 
* @class      DIOI2CGPIOPCF8574
* @brief      Data Input/Output I2C PCF8574 (GPIO 8 Pins) class
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

#include "DIOI2CGPIOPCF8574.h"

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
* @fn         DIOI2CGPIOPCF8574::DIOI2CGPIOPCF8574()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOI2CGPIOPCF8574::DIOI2CGPIOPCF8574(): DIODEVICEI2C()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOI2CGPIOPCF8574::~DIOI2CGPIOPCF8574()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOI2CGPIOPCF8574::~DIOI2CGPIOPCF8574()
{
  End();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CGPIOPCF8574::Read(XBYTE& value)
* @brief      Read
* @ingroup    DATAIO
*
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CGPIOPCF8574::Read(XBYTE& value)
{
  if(!diostream)        return false;
  if(!IsInitialized())  return false;

  bool  status;

  status = diostream->WaitToFilledReadingBuffer(1, timeout);
  if(status) status = diostream->Read(&value, 1)?true:false;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CGPIOPCF8574::Write(XBYTE value)
* @brief      Write
* @ingroup    DATAIO
*
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CGPIOPCF8574::Write(XBYTE value)
{
  bool  status = false;

  if(!diostream)        return false;
  if(!IsInitialized())  return false;

  if(diostream->Write(&value, 1)) status = diostream->WaitToFlushOutXBuffer(timeout);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CGPIOPCF8574::End()
* @brief      End
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CGPIOPCF8574::End()
{
  if(!DIODEVICEI2C::End()) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CGPIOPCF8574::IniDevice()
* @brief      Ini device
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CGPIOPCF8574::IniDevice()
{
  if(!DIODEVICEI2C::IniDevice()) return false;
  
  if(diostream->Open())  
    {
      if(!diostream->WaitToConnected(timeout)) return false;
     
      if(!DIODEVICE::Ini()) return false;
      
      return Write(0x00);      
    }
  
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOI2CGPIOPCF8574::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOI2CGPIOPCF8574::Clean()
{
  
}


#pragma endregion
