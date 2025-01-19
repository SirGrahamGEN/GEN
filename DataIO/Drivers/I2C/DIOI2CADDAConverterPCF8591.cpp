/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOI2CADDAConverterPCF8591.cpp
* 
* @class      DIOI2CADDACONVERTERPCF8591
* @brief      Data Input/Output I2C PCF8591 (AD/DA converter) class
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

#include "DIOI2CADDAConverterPCF8591.h"

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
* @fn         DIOI2CADDACONVERTERPCF8591::DIOI2CADDACONVERTERPCF8591() : DIODEVICEI2C()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOI2CADDACONVERTERPCF8591::DIOI2CADDACONVERTERPCF8591() : DIODEVICEI2C()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOI2CADDACONVERTERPCF8591::~DIOI2CADDACONVERTERPCF8591()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOI2CADDACONVERTERPCF8591::~DIOI2CADDACONVERTERPCF8591()
{
  End();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CADDACONVERTERPCF8591::ReadADChannels(XBYTE values)
* @brief      Read AD channels
* @ingroup    DATAIO
*
* @param[in]  values :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CADDACONVERTERPCF8591::ReadADChannels(XBYTE values[4])
{
  XBYTE   control = 0x04;
  bool    status  = false;

  if(!IsInitialized()) return false;

  diostream->ResetXBuffers();

  if(diostream->Write(&control, 1)) status = diostream->WaitToFlushOutXBuffer(timeout);

  if(status)
    {
      status = diostream->WaitToFilledReadingBuffer(5, timeout);
      if(status)
        {
          XBYTE dataread[5] = { 0, 0, 0, 0, 0 };

          if(diostream->Read(dataread, 5) == 5)
            {
              values[0] = dataread[2];
              values[1] = dataread[3];
              values[2] = dataread[4];
              values[3] = dataread[1];

              status = true;

            } else status = false;
        }
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CADDACONVERTERPCF8591::WriteDAChannel(XBYTE value)
* @brief      Write DA channel
* @ingroup    DATAIO
*
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CADDACONVERTERPCF8591::WriteDAChannel(XBYTE value)
{
  if(!IsInitialized()) return false;

  XBYTE   data[2] = { 0, 0 };
  bool    status  = false;

  data[0] = 0x40;
  data[1] = value;

  diostream->ResetXBuffers();

  if(diostream->Write(data, 2)) status = diostream->WaitToFlushOutXBuffer(timeout);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CADDACONVERTERPCF8591::End()
* @brief      End
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CADDACONVERTERPCF8591::End()
{  
  if(diostream)
    {
      diostream->Close();
      GEN_DIOFACTORY.DeleteStreamIO(diostream);
      diostream = NULL;
    }
    
  if(!DIODEVICE::End()) return false;
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CADDACONVERTERPCF8591::IniDevice()
* @brief      Ini device
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CADDACONVERTERPCF8591::IniDevice()
{
  diostream = (DIOSTREAMI2C*)GEN_DIOFACTORY.CreateStreamIO(diostreamcfg);
  if(!diostream)  return false;

  diostreamcfg->SetMode(DIOSTREAMMODE_MASTER);
  diostreamcfg->SetAddressSize(DIOSTREAMI2CCONFIG_ADDRESSSIZE_7BITS);
  
  if(diostream->Open())  
    {
      if(!diostream->WaitToConnected(timeout)) return false;
     
      if(!DIODEVICE::Ini()) return false;
      
      return WriteDAChannel(0x00);      
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOI2CADDACONVERTERPCF8591::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOI2CADDACONVERTERPCF8591::Clean()
{
  diostream  = NULL;
}


#pragma endregion


