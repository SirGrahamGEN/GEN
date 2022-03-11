/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIODeviceI2C.cpp
* 
* @class      DIODEVICEI2C
* @brief      Data Input/Output device I2C class
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @copyright  Copyright(c) 2005 - 2021 GEN Group.
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
* ---------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XFactory.h"

#include "DIOFactory.h"
#include "DIOStreamI2CConfig.h"
#include "DIOStreamI2C.h"


#include "DIODeviceI2C.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIODEVICEI2C::DIODEVICEI2C()
* @brief      Constructor
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     Does not return anything. 
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
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     Does not return anything. 
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
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
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
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
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
* @brief      CreateConfig
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
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
* @brief      CreateConfig
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
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
 * @fn        bool DIODEVICEI2C::IniDevice()
 * @brief     IniDevice
 * @ingroup   DATAIO
 * 
 * @author    Abraham J. Velez 
 * @date       01/03/2016 12:00
 * 
 * @return      bool : true if is succesful. 
 * 
 * ---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
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
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIODEVICEI2C::Clean()
{
  timeout       = 0;
  xtimerout     = NULL;
  diostreamcfg  = NULL;
  diostream     = NULL;
}
