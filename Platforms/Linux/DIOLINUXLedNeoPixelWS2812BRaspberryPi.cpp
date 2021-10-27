/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOLINUXLedNeoPixelWS2812BRaspberryPi.cpp
*
* @class      DIOLINUXLEDNEOPIXELWS2812BRASPBERRYPI
* @brief      Data Input/Output LINUX Led Neopixel WS2812B Raspberry Pi
* @ingroup    PLATFORM_STM32
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @copyright  Copyright(c) 2008 - 2016 GEN Group.
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

#include "XTrace.h"
#include "XSleep.h"
#include "XBuffer.h"

#include "DIOLINUXLedNeoPixelWS2812BRaspberryPi.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOLINUXLEDNEOPIXELWS2812BRASPBERRYPI::DIOLINUXLEDNEOPIXELWS2812BRASPBERRYPI()
* @brief      Constructor
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOLINUXLEDNEOPIXELWS2812BRASPBERRYPI::DIOLINUXLEDNEOPIXELWS2812BRASPBERRYPI()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOLINUXLEDNEOPIXELWS2812BRASPBERRYPI::~DIOLINUXLEDNEOPIXELWS2812BRASPBERRYPI()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOLINUXLEDNEOPIXELWS2812BRASPBERRYPI::~DIOLINUXLEDNEOPIXELWS2812BRASPBERRYPI()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOLINUXLEDNEOPIXELWS2812BRASPBERRYPI::Send()
* @brief      Send
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXLEDNEOPIXELWS2812BRASPBERRYPI::Send()
{   
	XBYTE* ptrdata  = databuffer.Get();
  int    sizedata = databuffer.GetSize();
      
  DIOGPIO_ENTRY* entry = GEN_DIOGPIO.GPIOEntry_GetByID(GPIOentryID);
  if(!entry) return false;

  GEN_DIOGPIO.SetValue(entry, false);

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


  
  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOLINUXLEDNEOPIXELWS2812BRASPBERRYPI::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOLINUXLEDNEOPIXELWS2812BRASPBERRYPI::Clean()
{
  
}
