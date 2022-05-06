/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XSAMD5xE5xPlatformIni.cpp
*
* @class      XSAMD5XE5XPLATFORMINI
* @brief      eXtended SAMD5xE5x Plataform Ini class
* @ingroup    PLATFORM_SAMD5XE5X
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <peripheral_clk_config.h>
#include <utils.h>
#include <hal_init.h>
#include <hpl_rtc_base.h>

#include "XThreadListNonPreemptive.h"

#include "XSAMD5xE5xPlatformIni.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

static struct timer_descriptor      TIMER_0;
static struct timer_task            TimerTaskThreads;
XDWORD                              HAL_tick_count  = 0;

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSAMD5XE5XPLATFORMINI::XSAMD5XE5XPLATFORMINI()
* @brief      Constructor
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XSAMD5XE5XPLATFORMINI::XSAMD5XE5XPLATFORMINI()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSAMD5XE5XPLATFORMINI::~XSAMD5XE5XPLATFORMINI()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XSAMD5XE5XPLATFORMINI::~XSAMD5XE5XPLATFORMINI()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSAMD5XE5XPLATFORMINI::Ini()
* @brief      Ini
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSAMD5XE5XPLATFORMINI::Ini()
{
  init_mcu();

  SysTick_Init();
  //SysTick_Config(SystemCoreClock/1000);//system_core_clk=48Mhz / 1000=48kHz systic clk if 48Mhz  is used

  SysTick_Config(12000);  //system_core_clk= 48Mhz / 4  =  12kHz  ¿¿¿ I don´t know why ???

  delay_init(SysTick);

  TIMER_0_init();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSAMD5XE5XPLATFORMINI::End()
* @brief      End
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSAMD5XE5XPLATFORMINI::End()
{
  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSAMD5XE5XPLATFORMINI::SysTick_Init(void)
* @brief      SysTick_Init
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  void :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XSAMD5XE5XPLATFORMINI::SysTick_Init(void)
{
  SysTick->CTRL  = 0;
  HAL_tick_count = 0;

  SysTick->VAL   = 0; /* Load the SysTick Counter Value */
  SysTick->CTRL  = (SysTick_CTRL_TICKINT_Msk    |  /* Enable SysTick exception */
                    SysTick_CTRL_ENABLE_Msk)    |  /* Enable SysTick system timer */
                    SysTick_CTRL_CLKSOURCE_Msk;    /* Use processor clock source */
}





/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SysTick_Handler(void)
* @brief      ysTick_Handler
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  void :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void SysTick_Handler(void)
{
  __disable_irq();

  HAL_tick_count++;

 __enable_irq();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         static void TIMER_0_task1_cb(const struct timer_task*const timer_task)
* @brief      oid TIMER_0_task1_cb
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  struct timer_task*const timer_task :
*
* @return     static :
*
* --------------------------------------------------------------------------------------------------------------------*/
static void TIMER_0_task1_cb(const struct timer_task *const timer_task)
{
  __disable_irq();

  XTHREADLISTNONPREEMPTIVE::GetInstance().ExecuteFunctions();

  __enable_irq();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSAMD5XE5XPLATFORMINI::TIMER_0_init(void)
* @brief      TIMER_0_init
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  void :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XSAMD5XE5XPLATFORMINI::TIMER_0_init(void)
{
  hri_mclk_set_APBAMASK_RTC_bit(MCLK);
  timer_init(&TIMER_0, RTC, _rtc_get_timer());

  TimerTaskThreads.interval = 50;
  TimerTaskThreads.cb       = TIMER_0_task1_cb;
  TimerTaskThreads.mode     = TIMER_TASK_REPEAT;

  timer_add_task(&TIMER_0, &TimerTaskThreads);

  timer_start(&TIMER_0);
}





/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSAMD5XE5XPLATFORMINI::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XSAMD5XE5XPLATFORMINI::Clean()
{

}
