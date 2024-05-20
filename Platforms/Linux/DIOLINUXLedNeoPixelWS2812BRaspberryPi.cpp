/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOLINUXLedNeoPixelWS2812BRaspberryPi.cpp
* 
* @class      DIOLINUXLEDNEOPIXELWS2812BRASPBERRYPI
* @brief      LINUX Data Input/Output Led Neopixel WS2812B Raspberry Pi class
* @ingroup    PLATFORM_LINUX
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
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIOLINUXLedNeoPixelWS2812BRaspberryPi.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <signal.h>
#include <stdarg.h>
#include <getopt.h>

#include "clk.h"
#include "gpio.h"
#include "dma.h"
#include "pwm.h"
#include "version.h"

#include "XTrace.h"
#include "XSleep.h"
#include "XBuffer.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOLINUXLEDNEOPIXELWS2812BRASPBERRYPI::DIOLINUXLEDNEOPIXELWS2812BRASPBERRYPI()
* @brief      Constructor
* @ingroup    PLATFORM_LINUX
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOLINUXLEDNEOPIXELWS2812BRASPBERRYPI::DIOLINUXLEDNEOPIXELWS2812BRASPBERRYPI()

{
  Clean();

  memset(&config, 0, sizeof(config));

  config.freq                  = NEOPIXELWS2812BRPI_DEFAULT_TARGET_FREQ;
  config.dmanum                = NEOPIXELWS2812BRPI_DEFAULT_DMA;
  
  config.channel[0].gpionum    = NEOPIXELWS2812BRPI_DEFAULT_GPIO_PIN;
  config.channel[0].count      = NEOPIXELWS2812BRPI_DEFAULT_LED_COUNT;
  config.channel[0].invert     = 0;
  config.channel[0].brightness = brightnessLevel;
  config.channel[0].strip_type = NEOPIXELWS2812BRPI_DEFAULT_STRIP_TYPE;
  
  config.channel[1].gpionum    = 0;
  config.channel[1].count      = 0;
  config.channel[1].invert     = 0;
  config.channel[1].brightness = 0;  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOLINUXLEDNEOPIXELWS2812BRASPBERRYPI::~DIOLINUXLEDNEOPIXELWS2812BRASPBERRYPI()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_LINUX
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOLINUXLEDNEOPIXELWS2812BRASPBERRYPI::~DIOLINUXLEDNEOPIXELWS2812BRASPBERRYPI()

{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOLINUXLEDNEOPIXELWS2812BRASPBERRYPI::Ini(XDWORD nled)
* @brief      Ini
* @ingroup    PLATFORM_LINUX
*
* @param[in]  nled : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXLEDNEOPIXELWS2812BRASPBERRYPI::Ini(XDWORD nled)
{ 
  return true;

  config.channel[0].count = nled;

  databuffer.Resize(nled * 3);

  ws2811_return_t returnvalue = ws2811_init(&config);
  if(returnvalue != WS2811_SUCCESS) return false;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOLINUXLEDNEOPIXELWS2812BRASPBERRYPI::Send()
* @brief      Send
* @ingroup    PLATFORM_LINUX
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXLEDNEOPIXELWS2812BRASPBERRYPI::Send()
{   
  /*
	XBYTE* ptrdata  = databuffer.Get();
  int    sizedata = databuffer.GetSize();
      
  DIOGPIO_ENTRY* entry = GEN_DIOGPIO.GPIOEntry_GetByID(GPIOentryID);
  if(!entry) return false;

  GEN_DIOGPIO.SetValue(entry, false);

  setpriority(PRIO_PROCESS, 0, -20);

  for(int c=0; c<sizedata; c++)
    {
      XBYTE databyte = ptrdata[c];

      for(int b=0; b<8; b++)
        {
          if(databyte & 0x80)
            {
              GEN_DIOGPIO.SetValue(entry, true);
              for(int i=0; i<=40; i++);
     
              GEN_DIOGPIO.SetValue(entry, false); 
              for(int i=0; i<=6; i++);
     
            }
           else
            {
              GEN_DIOGPIO.SetValue(entry, true); 
              for(int i=0; i<=6; i++);
     
              GEN_DIOGPIO.SetValue(entry, false);
              for(int i=0; i<=40; i++);     
            }

          databyte <<= 1;
        }
    }

  setpriority(PRIO_PROCESS, 0, 0);
  */

  return true;

  XBYTE* ptrdata  = databuffer.Get();
  XDWORD data     = 0;
  int    index    = 0;

  for(int c=0; c<config.channel[0].count; c++)
    {

      config.channel[0].leds[c] = 0;

      data = ptrdata[index];      
      config.channel[0].leds[c] |= data;           
      index++;

      data = ptrdata[index];      
      data <<= 8;
      config.channel[0].leds[c] |= data;           
      index++;

      data = ptrdata[index];      
      data <<= 16;
      config.channel[0].leds[c] |= data;           
      index++;

      data = 0xFF;      
      data <<= 24;
      config.channel[0].leds[c] |= data;           
     
    }

  config.channel[0].brightness = brightnessLevel;

  ws2811_return_t returnvalue = ws2811_render(&config);
  if(returnvalue != WS2811_SUCCESS) return false;
 
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOLINUXLEDNEOPIXELWS2812BRASPBERRYPI::End()
* @brief      End
* @ingroup    PLATFORM_LINUX
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXLEDNEOPIXELWS2812BRASPBERRYPI::End()
{
  return true;

  ws2811_fini(&config);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOLINUXLEDNEOPIXELWS2812BRASPBERRYPI::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_LINUX
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOLINUXLEDNEOPIXELWS2812BRASPBERRYPI::Clean()
{
  
}


#pragma endregion

