/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XSAMD5xE5xDebugTrace.cpp
*
* @class      XSAMD5XE5XTRACE
* @brief      SAMD5xE5x debug trace class
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


#ifdef XTRACE_ACTIVE

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XBase.h"
#include "XBuffer.h"
#include "XSleep.h"

#include "XSAMD5xE5xDateTime.h"

#include "XSAMD5xE5xTrace.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSAMD5XE5XTRACE::XSAMD5XE5XTRACE()
* @brief      Constructor
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XSAMD5XE5XTRACE::XSAMD5XE5XTRACE()
{
  Clean();

  XTRACE::instance = this;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSAMD5XE5XTRACE::~XSAMD5XE5XTRACE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XSAMD5XE5XTRACE::~XSAMD5XE5XTRACE()
{
  Clean();

  XTRACE::instance = NULL;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSAMD5XE5XTRACE::PrintSpecial(XTRACE_TARGET* target, XBYTE level, XCHAR* string)
* @brief      Print Special aim
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  target : target to print the debug
* @param[in]  level : level of debug
* @param[in]  string : string with the line
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XSAMD5XE5XTRACE::PrintSpecial(XTRACE_TARGET* target, XBYTE level, XCHAR* string)
{
  XSAMD5XE5XDATETIME   xdatetime;
  static bool          reenter = false;

  if(reenter)
    {
      XBUFFER              xbufferpackettmp;
      static XBUFFER       xbuffercache;
      XSAMD5XE5XDATETIME   xdatetime;

      SetTraceToXBuffer(0xFFFFFFFF, 0xFFFFFFFF, level, sequence, &xdatetime, string, xbufferpackettmp);
      xbuffercache.Add(xbufferpackettmp);
    }
   else
    {
      reenter = true;

      if(xbuffercache.GetSize())
        {
          // timeout ???
          io_write(huart, (uint8_t*)xbuffercache.Get(), (uint16_t)xbuffercache.GetSize());
          xbuffercache.Delete();
        }

      XBUFFER              xbufferpacket;
      XSAMD5XE5XDATETIME   xdatetime;

      SetTraceToXBuffer(0xFFFFFFFF, 0xFFFFFFFF, level, sequence, &xdatetime, string, xbufferpacket);
      // timeout ???
      io_write(huart, (uint8_t*)xbufferpacket.Get(), (uint16_t)xbufferpacket.GetSize());

      reenter = false;
    }
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSAMD5XE5XTRACE::IniUARTSpecial()
* @brief      IniUARTSpecial
* @note       INTERNAL
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XSAMD5XE5XTRACE::IniUARTSpecial()
{
  #define CONF_GCLK_SERCOM0_CORE_SRC GCLK_PCHCTRL_GEN_GCLK0_Val
  #define CONF_GCLK_SERCOM0_SLOW_SRC GCLK_PCHCTRL_GEN_GCLK3_Val

  #define PA04 GPIO(GPIO_PORTA, 4)
  #define PA05 GPIO(GPIO_PORTA, 5)

  struct usart_sync_descriptor uarttrace;

  hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM0_GCLK_ID_CORE, CONF_GCLK_SERCOM0_CORE_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
  hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM0_GCLK_ID_SLOW, CONF_GCLK_SERCOM0_SLOW_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));

  hri_mclk_set_APBAMASK_SERCOM0_bit(MCLK);

  usart_sync_init(&uarttrace, SERCOM0, (void *)NULL);

  gpio_set_pin_function(PA04, PINMUX_PA04D_SERCOM0_PAD0);
  gpio_set_pin_function(PA05, PINMUX_PA05D_SERCOM0_PAD1);

  usart_sync_get_io_descriptor(&uarttrace, &huart);
  if(usart_sync_enable(&uarttrace) == ERR_NONE) return true;

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSAMD5XE5XTRACE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XSAMD5XE5XTRACE::Clean()
{

}


#endif
