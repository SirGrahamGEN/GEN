/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOSAMD5xE5xGPIO.cpp
*
* @class      DIOSAMD5XE5XGPIO
* @brief      SAMD5XE5X DIO General Port Input/Ouput
* @ingroup    PLATFORM_SAMD5XE5X
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

#include "XSAMD5xE5x_HAL.h"
#include "XTrace.h"

#include "DIOSAMD5xE5xGPIO.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSAMD5XE5XGPIO::DIOSAMD5XE5XGPIO()
* @brief      Constructor
* @ingroup    PLATFORM_SAMD5XE5X
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSAMD5XE5XGPIO::DIOSAMD5XE5XGPIO(): DIOGPIO()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSAMD5XE5XGPIO::~DIOSAMD5XE5XGPIO()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_SAMD5XE5X
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSAMD5XE5XGPIO::~DIOSAMD5XE5XGPIO()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSAMD5XE5XGPIO::Ini()
* @brief      Ini
* @ingroup    PLATFORM_SAMD5XE5X
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSAMD5XE5XGPIO::Ini()
{

  for(int c=0; c<32; c++)
    {
      GPIOvalue[DIOGPIO_PINSGROUP_A][c] = GPIO(GPIO_PORTA, c);
      GPIOvalue[DIOGPIO_PINSGROUP_B][c] = GPIO(GPIO_PORTB, c);
      GPIOvalue[DIOGPIO_PINSGROUP_C][c] = GPIO(GPIO_PORTC, c);
      GPIOvalue[DIOGPIO_PINSGROUP_D][c] = GPIO(GPIO_PORTD, c);
    }

  return true;
}





/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSAMD5XE5XGPIO::SetMode(XBYTE pin, bool isinput, DIOGPIO_PINSGROUP block)
* @brief      SetMode
* @ingroup    PLATFORM_SAMD5XE5X
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @PAram[in]  pin :
* @PAram[in]  isinput :
* @PAram[in]  block :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSAMD5XE5XGPIO::SetMode(XBYTE pin, bool isinput, DIOGPIO_PINSGROUP block, DIOGPIO_PULLMODE pullmode)
{
  if(GPIOvalue[block][pin] == DIOGPIO_PINNOTUSE) return false;

  // Initial level
  //gpio_set_pin_direction(GPIOvalue[block][pin], GPIO_DIRECTION_OUT);
  //gpio_set_pin_level(GPIOvalue[block][pin], false);

  if(isinput)
    {
      switch(pullmode)
        {
          case DIOGPIO_PULLMODE_OFF   : gpio_set_pin_pull_mode(GPIOvalue[block][pin], GPIO_PULL_OFF);   break;
          case DIOGPIO_PULLMODE_UP    : gpio_set_pin_pull_mode(GPIOvalue[block][pin], GPIO_PULL_UP);    break;
          case DIOGPIO_PULLMODE_DOWN  : gpio_set_pin_pull_mode(GPIOvalue[block][pin], GPIO_PULL_DOWN);  break;
        }
    }

  gpio_set_pin_direction(GPIOvalue[block][pin], (isinput?GPIO_DIRECTION_IN:GPIO_DIRECTION_OUT));
  gpio_set_pin_function(GPIOvalue[block][pin] , GPIO_PIN_FUNCTION_OFF);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSAMD5XE5XGPIO::Get(XBYTE pin, DIOGPIO_PINSGROUP block)
* @brief      Get
* @ingroup    PLATFORM_SAMD5XE5X
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @PAram[in]  pin :
* @PAram[in]  block :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSAMD5XE5XGPIO::Get(XBYTE pin, DIOGPIO_PINSGROUP block)
{
  if(GPIOvalue[block][pin] == DIOGPIO_PINNOTUSE) return false;

  return gpio_get_pin_level(GPIOvalue[block][pin]);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSAMD5XE5XGPIO::Set(XBYTE pin,bool active, DIOGPIO_PINSGROUP block)
* @brief      Set
* @ingroup    PLATFORM_SAMD5XE5X
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @PAram[in]  pin :
* @PAram[in]  active :
* @PAram[in]  block :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSAMD5XE5XGPIO::Set(XBYTE pin, bool active, DIOGPIO_PINSGROUP block)
{
  if(GPIOvalue[block][pin] == DIOGPIO_PINNOTUSE) return false;

  gpio_set_pin_level(GPIOvalue[block][pin], active);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSAMD5XE5XGPIO::End()
* @brief      End
* @ingroup    PLATFORM_SAMD5XE5X
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSAMD5XE5XGPIO::End()
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSAMD5XE5XGPIO::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_SAMD5XE5X
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOSAMD5XE5XGPIO::Clean()
{


}