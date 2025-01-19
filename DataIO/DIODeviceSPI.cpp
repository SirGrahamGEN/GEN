/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIODeviceSPI.cpp
* 
* @class      DIODEVICESPI
* @brief      Data Input/Output device SPI class
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

#include "DIODeviceSPI.h"

#include "XFactory.h"

#include "DIOFactory.h"
#include "DIODevice.h"
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
* @fn         DIODEVICESPI::DIODEVICESPI()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* ---------------------------------------------------------------------------------------------------------------------*/
DIODEVICESPI::DIODEVICESPI()
{
  Clean();

  GEN_XFACTORY_CREATE(xtimerout, CreateTimer())  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIODEVICESPI::~DIODEVICESPI()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* ---------------------------------------------------------------------------------------------------------------------*/
DIODEVICESPI::~DIODEVICESPI()
{
  if(xtimerout) GEN_XFACTORY.DeleteTimer(xtimerout);

  if(diostreamcfg) delete diostreamcfg;

  Clean();
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIODEVICESPI::Ini(XCHAR* localdevicename, int timeout)
* @brief      Ini
* @ingroup    DATAIO
*
* @param[in]  localdevicename : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIODEVICESPI::Ini(XCHAR* localdevicename, int timeout)
{
  if(!xtimerout) return false;

  this->timeout = timeout;

  diostreamcfg = CreateConfig(localdevicename);
  if(!diostreamcfg)  return false;

  return IniDevice();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIODEVICESPI::Ini(int port, int chipselect, int timeout)
* @brief      Ini
* @ingroup    DATAIO
*
* @param[in]  port : 
* @param[in]  chipselect : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIODEVICESPI::Ini(int port, int chipselect, int timeout)
{
  if(!xtimerout) return false;

  this->timeout = timeout;

  diostreamcfg = CreateConfig(port, chipselect);
  if(!diostreamcfg)  return false;

  return IniDevice();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOSTREAMSPICONFIG* DIODEVICESPI::CreateConfig(XCHAR* localdevicename)
* @brief      Create config
* @ingroup    DATAIO
*
* @param[in]  localdevicename : 
* 
* @return     DIOSTREAMSPICONFIG* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMSPICONFIG* DIODEVICESPI::CreateConfig(XCHAR* localdevicename)
{
  DIOSTREAMSPICONFIG* diostreamcfg = new DIOSTREAMSPICONFIG();
  if(!diostreamcfg)  return NULL;

  diostreamcfg->SetSPIMode(DIOSTREAMSPI_MODE_0);
  diostreamcfg->SetNBitsWord(8);
  diostreamcfg->SetSpeed(80*1000*1000);
  diostreamcfg->SetDelay(0);
  diostreamcfg->SetIsOnlyWrite(true);

  diostreamcfg->GetLocalDeviceName()->Set(localdevicename);

  return diostreamcfg;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOSTREAMSPICONFIG* DIODEVICESPI::CreateConfig(int port, int chipselect)
* @brief      Create config
* @ingroup    DATAIO
*
* @param[in]  port : 
* @param[in]  chipselect : 
* 
* @return     DIOSTREAMSPICONFIG* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMSPICONFIG* DIODEVICESPI::CreateConfig(int port, int chipselect)
{
  DIOSTREAMSPICONFIG* diostreamcfg = new DIOSTREAMSPICONFIG();
  if(!diostreamcfg)  return NULL;

  diostreamcfg->SetPort(port);
  diostreamcfg->SetSPIMode(DIOSTREAMSPI_MODE_0);
  diostreamcfg->SetChipSelect(chipselect);
  diostreamcfg->SetNBitsWord(8);
  diostreamcfg->SetSpeed(80*1000*1000);
  diostreamcfg->SetDelay(0);
  diostreamcfg->SetIsOnlyWrite(true);

  diostreamcfg->SetLocalDeviceNameByPort();

  return diostreamcfg;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIODEVICESPI::IniDevice()
* @brief      Ini device
* @ingroup    DATAIO
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIODEVICESPI::IniDevice()
{
  diostream = (DIOSTREAMSPI*)GEN_DIOFACTORY.CreateStreamIO(diostreamcfg);
  if(!diostream)  return false;

  diostreamcfg->SetMode(DIOSTREAMMODE_MASTER);

  return true;
}
     

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIODEVICESPI::End()
* @brief      End
* @ingroup    DATAIO
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIODEVICESPI::End()
{
  if(xtimerout) 
    {
      GEN_XFACTORY.DeleteTimer(xtimerout);
      xtimerout = NULL;
    }

  if(diostream)
    {
      diostream->Close();
      GEN_DIOFACTORY.DeleteStreamIO(diostream);
      diostream = NULL;
    }

  if(diostreamcfg) 
    {
      delete diostreamcfg;
      diostreamcfg = NULL;
    }


  if(!DIODEVICE::End()) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIODEVICESPI::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* ---------------------------------------------------------------------------------------------------------------------*/
void DIODEVICESPI::Clean()
{
  timeout       = 0;
  xtimerout     = NULL;
  diostreamcfg  = NULL;
  diostream     = NULL;
}


#pragma endregion

