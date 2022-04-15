/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOLINUXGPIOPCPARALLEL.cpp
*
* @class      DIOLINUXGPIOPCPARALLEL
* @brief      Data Input/Output LINUX GPIO (General Purpose Input/Output) PC Parallel
* @ingroup    PLATFORM_LINUX
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

#ifdef HW_PC

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/io.h>

#include "XTrace.h"

#include "DIOLINUXGPIOPCParallel.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOLINUXGPIOPCPARALLEL::DIOLINUXGPIOPCPARALLEL()
* @brief      Constructor
* @ingroup    PLATFORM_LINUX
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOLINUXGPIOPCPARALLEL::DIOLINUXGPIOPCPARALLEL() : DIOGPIO()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOLINUXGPIOPCPARALLEL::~DIOLINUXGPIOPCPARALLEL()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_LINUX
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOLINUXGPIOPCPARALLEL::~DIOLINUXGPIOPCPARALLEL()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XWORD DIOLINUXGPIOPCPARALLEL::GetParallelPort()
* @brief      GetParallelPort
* @ingroup    PLATFORM_LINUX
*
* @return     XWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XWORD DIOLINUXGPIOPCPARALLEL::GetParallelPort()
{
  return port;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOLINUXGPIOPCPARALLEL::SetParallelPort(XWORD port)
* @brief      SetParallelPort
* @ingroup    PLATFORM_LINUX
*
* @param[in]  port : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOLINUXGPIOPCPARALLEL::SetParallelPort(XWORD port)
{
  this->port = port;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOLINUXGPIOPCPARALLEL::Ini(XPATH* xpath)
* @brief      Ini
* @ingroup    PLATFORM_LINUX
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXGPIOPCPARALLEL::Ini()
{
  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOLINUXGPIOPCPARALLEL::SetMode(DIOGPIO_ENTRY* entry, XWORD mode)
* @brief      SetMode
* @ingroup    PLATFORM_LINUX
*
* @param[in]  entry : 
* @param[in]  mode : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXGPIOPCPARALLEL::SetMode(DIOGPIO_ENTRY* entry, XWORD mode)
{
  if(!entry) return false;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOLINUXGPIOPCPARALLEL::GetValue(DIOGPIO_ENTRY* entry)
* @brief      GetValue
* @ingroup    PLATFORM_LINUX
*
* @param[in]  entry : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXGPIOPCPARALLEL::GetValue(DIOGPIO_ENTRY* entry)
{
	if(!entry) return false;

  XBYTE data = 0;

  PC_Get(port, data);

  return (data & ~(0x01 << entry->GetGPIO()))?true:false;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOLINUXGPIOPCPARALLEL::SetValue(DIOGPIO_ENTRY* entry, bool value)
* @brief      SetValue
* @ingroup    PLATFORM_LINUX
*
* @param[in]  entry : 
* @param[in]  value : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXGPIOPCPARALLEL::SetValue(DIOGPIO_ENTRY* entry, bool value)
{
	if(!entry) return false;

  XBYTE data = 0;

  PC_Get(port, data);
  PC_Set(port, value ? (data | (0x01 << entry->GetGPIO())) : (data & ~(0x01 << entry->GetGPIO())));

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOLINUXGPIOPCPARALLEL::End()
* @brief      End
* @ingroup    PLATFORM_LINUX
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXGPIOPCPARALLEL::End()
{
  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOLINUXGPIOPCPARALLEL::PC_Get(XDWORD nport,XBYTE& data)
* @brief      PC_Get
* @ingroup    PLATFORM_LINUX
*
* @param[in]  nport :
* @param[in]  data :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXGPIOPCPARALLEL::PC_Get(XDWORD nport,XBYTE& data)
{
  XDWORD val = 0;

  if(ioperm(nport,1,1)) return false;

  val = inb(nport);

  if(ioperm(nport,1,0)) return false;

  data = (XBYTE)(val & 0x0FF);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOLINUXGPIOPCPARALLEL::PC_Set(XDWORD nport,XBYTE data)
* @brief      PC_Set
* @ingroup    PLATFORM_LINUX
*
* @param[in]  nport :
* @param[in]  data :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXGPIOPCPARALLEL::PC_Set(XDWORD nport,XBYTE data)
{
  if(ioperm(nport,1,1)) return false;

  outb(data, nport);

  if(ioperm(nport,1,0)) return false;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOLINUXGPIOPCPARALLEL::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_LINUX
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOLINUXGPIOPCPARALLEL::Clean()
{
  port            = DIOLINUXGPIOPCPARALLEL_PORT1;
}


#endif