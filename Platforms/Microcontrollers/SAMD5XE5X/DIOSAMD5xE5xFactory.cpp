/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOSAMD5xE5xFactory.cpp
*
* @class      DIOSAMD5XE5XFACTORY
* @brief      SAMD5xE5x platform factory class
* @ingroup    PLATFORM_SAMD5XE5X
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

#ifdef DIOUART_ACTIVE
#include "DIOStreamUARTConfig.h"
#include "DIOSAMD5xE5xStreamUART.h"
#endif

#ifdef DIOUSB_ACTIVE
#include "DIOStreamUSBConfig.h"
#include "DIOSAMD5xE5xStreamUSB.h"
#endif

#ifdef DIOSPI_ACTIVE
#include "DIOStreamSPIConfig.h"
#include "DIOSAMD5xE5xStreamSPI.h"
#endif

#ifdef DIOI2C_ACTIVE
#include "DIOStreamI2CConfig.h"
#include "DIOSAMD5xE5xStreamI2C.h"
#endif

#ifdef DIOGPIO_ACTIVE
#include "DIOSAMD5xE5xGPIO.h"
#endif

#include "DIOSAMD5xE5xFactory.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef ANYTYPEOFDIOSTREAMIO

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAM* DIOSAMD5XE5XFACTORY::CreateStreamIO(DIOSTREAMCONFIG* config)
* @brief      CreateStreamIO
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  config :
*
* @return     DIOSTREAM* :
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSTREAM* DIOSAMD5XE5XFACTORY::CreateStreamIO(DIOSTREAMCONFIG* config)
{
  if(!config) return NULL;

  DIOSTREAM* _class = NULL;

  switch(config->GetType())
    {
      case DIOSTREAMTYPE_UNKNOWN    : return NULL;

      #ifdef DIOUART_ACTIVE
      case DIOSTREAMTYPE_UART       : _class = new DIOSAMD5XE5XSTREAMUART();        break;
      #endif

      #ifdef DIOUSB_ACTIVE
      case DIOSTREAMTYPE_USB        : _class = new DIOSAMD5XE5XSTREAMUSB();         break;
      #endif

      #ifdef DIOSPI_ACTIVE
      case DIOSTREAMTYPE_SPI        : _class = new DIOSAMD5XE5XSTREAMSPI();         break;
      #endif

      #ifdef DIOI2C_ACTIVE
      case DIOSTREAMTYPE_I2C        : _class = new DIOSAMD5XE5XSTREAMI2C();         break;
      #endif

                      default       : break;
    }

  if(_class)
    {
      _class->SetType(config->GetType());
      _class->SetConfig(config);
    }


  return _class;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSAMD5XE5XFACTORY::DeleteStreamIO(DIOSTREAM* diostream)
* @brief      DeleteStreamIO
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  diostream :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSAMD5XE5XFACTORY::DeleteStreamIO(DIOSTREAM* diostream)
{
  if(!diostream) return false;
  delete(diostream);

  return true;
}




#ifdef DIOGPIO_ACTIVE


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOGPIO* DIOSAMD5XE5XFACTORY::CreateGPIO()
* @brief      CreateGPIO
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     DIOGPIO* :
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOGPIO* DIOSAMD5XE5XFACTORY::CreateGPIO()
{
  DIOSAMD5XE5XGPIO* _class = new DIOSAMD5XE5XGPIO();

  return (DIOGPIO*)_class;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSAMD5XE5XFACTORY::DeleteGPIO(DIOGPIO* port)
* @brief      DeleteGPIO
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  port :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSAMD5XE5XFACTORY::DeleteGPIO(DIOGPIO* port)
{
  if(!port) return false;

  DIOSAMD5XE5XGPIO* _port = (DIOSAMD5XE5XGPIO*)port;
  delete _port;

  return true;
}


#endif


#endif