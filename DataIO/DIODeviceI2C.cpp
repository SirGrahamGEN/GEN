/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIODeviceI2C.cpp
* 
* @class      DIODEVICEI2C
* @brief      Data Input/Output device I2C class
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

#include "DIODeviceI2C.h"

#include "XFactory.h"

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
* @fn         DIODEVICEI2C::DIODEVICEI2C()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* ---------------------------------------------------------------------------------------------------------------------*/
DIODEVICEI2C::DIODEVICEI2C()
{
  Clean();

  GEN_XFACTORY_CREATE(xtimerout, CreateTimer());  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIODEVICEI2C::~DIODEVICEI2C()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* ---------------------------------------------------------------------------------------------------------------------*/
DIODEVICEI2C::~DIODEVICEI2C()
{
  End();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIODEVICEI2C::Ini(XCHAR* localdevicename, int remotedeviceaddress, int timeout)
* @brief      Ini
* @ingroup    DATAIO
*
* @param[in]  localdevicename : 
* @param[in]  remotedeviceaddress : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIODEVICEI2C::Ini(XCHAR* localdevicename, int remotedeviceaddress, int timeout)
{
  if(!xtimerout) return false;

  this->timeout = timeout;

  diostreamcfg = CreateConfig(localdevicename, remotedeviceaddress);
  if(!diostreamcfg)  return false;

  return IniDevice();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIODEVICEI2C::Ini(int port, int remotedeviceaddress, int timeout)
* @brief      Ini
* @ingroup    DATAIO
*
* @param[in]  port : 
* @param[in]  remotedeviceaddress : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIODEVICEI2C::Ini(int port, int remotedeviceaddress, int timeout)
{
  if(!xtimerout) return false;

  this->timeout = timeout;

  diostreamcfg = CreateConfig(port, remotedeviceaddress);
  if(!diostreamcfg)  return false;

  return IniDevice();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOSTREAMI2CCONFIG* DIODEVICEI2C::CreateConfig(XCHAR* localdevicename, int remotedeviceaddress)
* @brief      Create config
* @ingroup    DATAIO
*
* @param[in]  localdevicename : 
* @param[in]  remotedeviceaddress : 
* 
* @return     DIOSTREAMI2CCONFIG* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMI2CCONFIG* DIODEVICEI2C::CreateConfig(XCHAR* localdevicename, int remotedeviceaddress)
{
  DIOSTREAMI2CCONFIG* diostreamcfg = new DIOSTREAMI2CCONFIG();
  if(!diostreamcfg)  return NULL;

  diostreamcfg->GetLocalDeviceName()->Set(localdevicename);

  diostreamcfg->SetRemoteAddress(remotedeviceaddress);

  return diostreamcfg;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOSTREAMI2CCONFIG* DIODEVICEI2C::CreateConfig(int port, int remotedeviceaddress)
* @brief      Create config
* @ingroup    DATAIO
*
* @param[in]  port : 
* @param[in]  remotedeviceaddress : 
* 
* @return     DIOSTREAMI2CCONFIG* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMI2CCONFIG* DIODEVICEI2C::CreateConfig(int port, int remotedeviceaddress)
{
  DIOSTREAMI2CCONFIG* diostreamcfg = new DIOSTREAMI2CCONFIG();
  if(!diostreamcfg)  return NULL;

  diostreamcfg->SetPort(port);

  diostreamcfg->SetLocalDeviceNameByPort();

  diostreamcfg->SetRemoteAddress(remotedeviceaddress);

  return diostreamcfg;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIODEVICEI2C::IniDevice()
* @brief      Ini device
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIODEVICEI2C::IniDevice()
{
  diostream = (DIOSTREAMI2C*)GEN_DIOFACTORY.CreateStreamIO(diostreamcfg);
  if(!diostream)  return false;

  diostreamcfg->SetMode(DIOSTREAMMODE_MASTER);
  diostreamcfg->SetAddressSize(DIOSTREAMI2CCONFIG_ADDRESSSIZE_7BITS);

  return true;
}
     

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIODEVICEI2C::End()
* @brief      End
* @ingroup    DATAIO
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIODEVICEI2C::End()
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
* @fn         void DIODEVICEI2C::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* ---------------------------------------------------------------------------------------------------------------------*/
void DIODEVICEI2C::Clean()
{
  timeout       = 0;
  xtimerout     = NULL;
  diostreamcfg  = NULL;
  diostream     = NULL;
}


#pragma endregion

