/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOLINUXGPIORaspberryPi.cpp
* 
* @class      DIOLINUXGPIORASPBERRYPI
* @brief      LINUX Data Input/Output GPIO (General Purpose Input/Output) Raspberry Pi class
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


#ifdef HW_RASPBERRYPI


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIOLINUXGPIORaspberryPi.h"

#include "XTrace.h"
#include "XSleep.h"
#include "XFileTXT.h"
#include "XTrace.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

static uint32_t* RPI_gpio;

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOLINUXGPIORASPBERRYPI::DIOLINUXGPIORASPBERRYPI()
* @brief      Constructor
* @ingroup    PLATFORM_LINUX
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOLINUXGPIORASPBERRYPI::DIOLINUXGPIORASPBERRYPI(): DIOGPIO()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOLINUXGPIORASPBERRYPI::~DIOLINUXGPIORASPBERRYPI()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_LINUX
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOLINUXGPIORASPBERRYPI::~DIOLINUXGPIORASPBERRYPI()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOLINUXGPIORASPBERRYPI::Ini(XPATH* xpath)
* @brief      Ini
* @ingroup    PLATFORM_LINUX
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXGPIORASPBERRYPI::Ini()
{
  if(!RPI_RevisionBoard(RPI_model, RPI_megabytes, RPI_revision)) return false;

  switch(RPI_model)
    {
      case RASPBERRYPI_MODEL_UNKNOWN        :
      case RASPBERRYPI_MODEL_A              :
      case RASPBERRYPI_MODEL_B              :
      case RASPBERRYPI_MODEL_A_PLUS         :
      case RASPBERRYPI_MODEL_B_PLUS         :
      case RASPBERRYPI_MODEL_COMPUTERMODULE :
      case RASPBERRYPI_MODEL_ZERO           : RPI_gpio_base = (RPI_BCM2708_PERI_BASE   + 0x200000);
                                              break;
      case RASPBERRYPI_MODEL_B_2            :
      case RASPBERRYPI_MODEL_B_3            : 
      case RASPBERRYPI_MODEL_CM3P           :
      case RASPBERRYPI_MODEL_B_3P           : RPI_gpio_base = (RPI_BCM2708_PERI_BASE_2 + 0x200000);
                                              break;

      case RASPBERRYPI_MODEL_B_4            : RPI_gpio_base = (RPI_BCM2708_PERI_BASE_4 + 0x200000);
                                              break;

    }

  
  // ------------- All Common ---------------------------------------------------------

      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED,  1, DIOGPIO_INVALID);     /* 01 - Not available (3v3 Power)   */      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED,  2, DIOGPIO_INVALID);     /* 02 - Not available (5v  Power) */
      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED,  3,               2);     /* 03 - I2C (SDA)                   */      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED,  4, DIOGPIO_INVALID);     /* 04 - Not available (5v  Power) */
      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED,  5,               3);     /* 05 - I2C (SDL)                   */      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED,  6, DIOGPIO_INVALID);     /* 06 - Not available (Ground)    */
      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED,  7,               4);     /* 07 - GPCLK0                      */      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED,  8,              14);     /* 08 - UART TXD                  */
      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED,  9, DIOGPIO_INVALID);     /* 09 - Not available (Ground)      */      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED, 10,              15);     /* 10 - UART RXD                  */
      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED, 11,              17);     /* 11 - Generic I/O                 */      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED, 12,              18);     /* 12 - PCM_CLK                   */
      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED, 13,              27);     /* 13 - PCM_DOUT                    */      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED, 14, DIOGPIO_INVALID);     /* 14 - Not available (Ground)    */
      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED, 15,              22);     /* 15 - Generic I/O                 */      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED, 16,              23);     /* 16 - Generic I/O               */
      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED, 17, DIOGPIO_INVALID);     /* 17 - Not available (3v3 Power)   */      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED, 18,              24);     /* 18 - Generic I/O               */
      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED, 19,              10);     /* 19 - SPI MOSI                    */      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED, 20, DIOGPIO_INVALID);     /* 20 - Not available (Ground)    */
      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED, 21,               9);     /* 21 - SPI MISO                    */      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED, 22,              25);     /* 22 - Generic I/O               */
      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED, 23,              11);     /* 23 - SPI SCLK                    */      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED, 24,               8);     /* 24 - SPI CE0                   */
      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED, 25, DIOGPIO_INVALID);     /* 25 - Not available               */      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED, 26,               7);     /* 26 - SPI CE1                   */

  // ------------- Extended PI2 -------------------------------------------------------

  if((RPI_model == RASPBERRYPI_MODEL_A_PLUS)          ||  (RPI_model == RASPBERRYPI_MODEL_B_PLUS) ||
     (RPI_model == RASPBERRYPI_MODEL_COMPUTERMODULE)  ||  (RPI_model == RASPBERRYPI_MODEL_B_2)    ||
     (RPI_model == RASPBERRYPI_MODEL_ZERO)            ||  (RPI_model == RASPBERRYPI_MODEL_CM3P)   ||
     (RPI_model == RASPBERRYPI_MODEL_B_3)             ||  (RPI_model == RASPBERRYPI_MODEL_B_3P)   ||
     (RPI_model == RASPBERRYPI_MODEL_B_4)    
    )
    {
      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED, 27, DIOGPIO_INVALID);     /* 27 - I2C ID EEProm SC            */      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED, 28, DIOGPIO_INVALID);     /* 28 - I2C ID EEProm SD          */
      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED, 29,               5);     /* 29 - Generic I/O                 */      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED, 30, DIOGPIO_INVALID);     /* 30 - Not available  (Ground)   */
      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED, 31,               6);     /* 31 - Generic I/O                 */      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED, 32,              12);     /* 32 - Generic I/O               */
      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED, 33,              13);     /* 33 - Generic I/O                 */      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED, 34, DIOGPIO_INVALID);     /* 34 - Not available (Ground)    */
      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED, 35,              19);     /* 35 - Generic I/O                 */      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED, 36,              16);     /* 36 - Generic I/O               */
      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED, 37,              26);     /* 37 - Generic I/O                 */      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED, 38,              20);     /* 38 - Generic I/O               */
      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED, 39, DIOGPIO_INVALID);     /* 39 - Not available (Ground)      */      GPIOEntry_Create(DIOGPIO_ID_NOTDEFINED, 40,              21);     /* 40 - Generic I/O               */
    }
    

  return RPI_Ini();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOLINUXGPIORASPBERRYPI::SetMode(DIOGPIO_ENTRY* entry, XWORD mode)
* @brief      SetMode
* @ingroup    PLATFORM_LINUX
*
* @param[in]  entry : 
* @param[in]  mode : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXGPIORASPBERRYPI::SetMode(DIOGPIO_ENTRY* entry, XWORD mode)
{
  if(!entry) return false;
  if(entry->GetGPIO() == DIOGPIO_INVALID) return false;

  bool isinput = true;

  if((mode & DIOGPIO_MODE_INPUT)  == DIOGPIO_MODE_INPUT)   isinput = true;
  if((mode & DIOGPIO_MODE_OUTPUT) == DIOGPIO_MODE_OUTPUT)  isinput = false;

  return RPI_GPIOMode(entry->GetGPIO(), isinput);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOLINUXGPIORASPBERRYPI::GetValue(DIOGPIO_ENTRY* entry)
* @brief      GetValue
* @ingroup    PLATFORM_LINUX
*
* @param[in]  entry : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXGPIORASPBERRYPI::GetValue(DIOGPIO_ENTRY* entry)
{  
  if(!entry) return false;
  if(entry->GetGPIO() == DIOGPIO_INVALID) return false;
  
  return RPI_GPIORead(entry->GetGPIO());
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOLINUXGPIORASPBERRYPI::SetValue(DIOGPIO_ENTRY* entry, bool value)
* @brief      SetValue
* @ingroup    PLATFORM_LINUX
*
* @param[in]  entry : 
* @param[in]  value : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXGPIORASPBERRYPI::SetValue(DIOGPIO_ENTRY* entry, bool value)
{
  if(!entry) return false;
  if(entry->GetGPIO() == DIOGPIO_INVALID) return false;

  return RPI_GPIOWrite(entry->GetGPIO(), value);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOLINUXGPIORASPBERRYPI::End()
* @brief      End
* @ingroup    PLATFORM_LINUX
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXGPIORASPBERRYPI::End()
{
  return RPI_End();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOLINUXGPIORASPBERRYPI::RPI_RevisionBoard(RASPBERRYPI_MODEL& model, int& megabytes, float& revision)
* @brief      RPI_RevisionBoard
* @ingroup    PLATFORM_LINUX
*
* @param[in]  model :
* @param[in]  megabytes :
* @param[in]  revision :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXGPIORASPBERRYPI::RPI_RevisionBoard(RASPBERRYPI_MODEL& model, int& megabytes, float& revision)
{
  XPATH     xpath;
  XFILETXT* xfiletxt;
  bool      status = false;

  xpath = __L("/proc/cpuinfo");

  //xpath = __L("D:\\GENFrameWork\\Test\\resources\\cpuinfo");

  xfiletxt = new XFILETXT();
  if(!xfiletxt) return false;

  if(xfiletxt->Open(xpath))
    {
      xfiletxt->ReadAllFile();

      for(int c=0;c< xfiletxt->GetNLines(); c++)
        {
          XSTRING* line = xfiletxt->GetLine(c);
          if(line)
            {
              if(line->Find(__L("Revision"), false) != XSTRING_NOTFOUND)
                {
                  int position = line->Find(__L(":"), true);
                  if(position != XSTRING_NOTFOUND)
                    {
                      line->DeleteCharacters(0, position+1);
                      line->DeleteCharacter(0x20);

                      model = RASPBERRYPI_MODEL_UNKNOWN;


                      // https://www.raspberrypi.org/documentation/hardware/raspberrypi/revision-codes/README.md


                      if(!line->Compare(__L("0002")   , true))  { model = RASPBERRYPI_MODEL_B;                megabytes = 256;      revision = 1.0f; }
                      if(!line->Compare(__L("0003")   , true))  { model = RASPBERRYPI_MODEL_B;                megabytes = 256;      revision = 1.0f; }
                      if(!line->Compare(__L("0004")   , true))  { model = RASPBERRYPI_MODEL_B;                megabytes = 256;      revision = 2.0f; }
                      if(!line->Compare(__L("0005")   , true))  { model = RASPBERRYPI_MODEL_B;                megabytes = 256;      revision = 2.0f; }
                      if(!line->Compare(__L("0006")   , true))  { model = RASPBERRYPI_MODEL_B;                megabytes = 256;      revision = 2.0f; }
                      if(!line->Compare(__L("0007")   , true))  { model = RASPBERRYPI_MODEL_A;                megabytes = 256;      revision = 2.0f; }
                      if(!line->Compare(__L("0008")   , true))  { model = RASPBERRYPI_MODEL_A;                megabytes = 256;      revision = 2.0f; }
                      if(!line->Compare(__L("0009")   , true))  { model = RASPBERRYPI_MODEL_A;                megabytes = 256;      revision = 2.0f; }
                      if(!line->Compare(__L("000d")   , true))  { model = RASPBERRYPI_MODEL_B;                megabytes = 512;      revision = 2.0f; }
                      if(!line->Compare(__L("000e")   , true))  { model = RASPBERRYPI_MODEL_B;                megabytes = 512;      revision = 2.0f; }
                      if(!line->Compare(__L("000f")   , true))  { model = RASPBERRYPI_MODEL_B;                megabytes = 512;      revision = 2.0f; }
                      if(!line->Compare(__L("0010")   , true))  { model = RASPBERRYPI_MODEL_B_PLUS;           megabytes = 512;      revision = 1.0f; }
                      if(!line->Compare(__L("0011")   , true))  { model = RASPBERRYPI_MODEL_COMPUTERMODULE;   megabytes = 512;      revision = 1.0f; }
                      if(!line->Compare(__L("0012")   , true))  { model = RASPBERRYPI_MODEL_A_PLUS;           megabytes = 256;      revision = 1.0f; }
                      if(!line->Compare(__L("0013")   , true))  { model = RASPBERRYPI_MODEL_B_PLUS;           megabytes = 512;      revision = 1.2f; }
                      if(!line->Compare(__L("a01041") , true))  { model = RASPBERRYPI_MODEL_B_2;              megabytes = 1024;     revision = 1.1f; }
                      if(!line->Compare(__L("a21041") , true))  { model = RASPBERRYPI_MODEL_B_2;              megabytes = 1024;     revision = 1.1f; }
                      if(!line->Compare(__L("900092") , true))  { model = RASPBERRYPI_MODEL_ZERO;             megabytes = 512;      revision = 1.2f; }
                      if(!line->Compare(__L("900093") , true))  { model = RASPBERRYPI_MODEL_ZERO;             megabytes = 512;      revision = 1.2f; }
                      if(!line->Compare(__L("a220a0") , true))  { model = RASPBERRYPI_MODEL_CM3;            	megabytes = 1024;     revision = 1.0f; }
                      if(!line->Compare(__L("a02082") , true))  { model = RASPBERRYPI_MODEL_B_3;              megabytes = 1024;     revision = 1.2f; }
                      if(!line->Compare(__L("a22082") , true))  { model = RASPBERRYPI_MODEL_B_3;              megabytes = 1024;     revision = 1.2f; }
                      if(!line->Compare(__L("a22083") , true))  { model = RASPBERRYPI_MODEL_B_3;              megabytes = 1024;     revision = 1.3f; }	
                      if(!line->Compare(__L("a02100") , true))  { model = RASPBERRYPI_MODEL_CM3P;            	megabytes = 1024;     revision = 1.0f; }
                      if(!line->Compare(__L("a020d3") , true))  { model = RASPBERRYPI_MODEL_B_3P;             megabytes = 1024;     revision = 1.2f; }                      
                      if(!line->Compare(__L("a03111") , true))  { model = RASPBERRYPI_MODEL_B_4;              megabytes = 1024;     revision = 1.1f; }
                      if(!line->Compare(__L("b03111") , true))  { model = RASPBERRYPI_MODEL_B_4;              megabytes = 2048;     revision = 1.1f; }
                      if(!line->Compare(__L("b03112") , true))  { model = RASPBERRYPI_MODEL_B_4;              megabytes = 2048;     revision = 1.2f; }
                      if(!line->Compare(__L("c03111") , true))  { model = RASPBERRYPI_MODEL_B_4;              megabytes = 4096;     revision = 1.1f; }
                      if(!line->Compare(__L("c03112") , true))  { model = RASPBERRYPI_MODEL_B_4;              megabytes = 4096;     revision = 1.2f; }
                                            
                      if(model != RASPBERRYPI_MODEL_UNKNOWN)
                        {
                          status = true;
                          break;
                        }
                    }
                }
            }
        }

      xfiletxt->Close();
    }

  delete xfiletxt;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOLINUXGPIORASPBERRYPI::RPI_Ini()
* @brief      RPI_Ini
* @ingroup    PLATFORM_LINUX
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXGPIORASPBERRYPI::RPI_Ini()
{
  int fd;

  if((fd = open ("/dev/mem", O_RDWR | O_SYNC | O_CLOEXEC)) < 0) return false;

  RPI_gpio = (uint32_t *)mmap(0, RPI_BLOCK_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, RPI_gpio_base) ;
  if (!RPI_CheckHandle(RPI_gpio)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOLINUXGPIORASPBERRYPI::RPI_End()
* @brief      RPI_End
* @ingroup    PLATFORM_LINUX
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXGPIORASPBERRYPI::RPI_End()
{
  if(!RPI_CheckHandle(RPI_gpio)) return false;

  //fixme - set all gpios back to input
  //munmap((caddr_t)RPI_gpio, RPI_BLOCK_SIZE);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOLINUXGPIORASPBERRYPI::RPI_IsGPIOValid(XQWORD GPIO)
* @brief      RPI_IsGPIOValid
* @ingroup    PLATFORM_LINUX
*
* @param[in]  GPIO : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXGPIORASPBERRYPI::RPI_IsGPIOValid(XQWORD GPIO)
{
  if(GPIO<2 || GPIO>27) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOLINUXGPIORASPBERRYPI::RPI_GPIOMode(XQWORD GPIO, bool isinput)
* @brief      RPI_GPIOMode
* @ingroup    PLATFORM_LINUX
*
* @param[in]  GPIO : 
* @param[in]  isinput : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXGPIORASPBERRYPI::RPI_GPIOMode(XQWORD GPIO, bool isinput)
{
  uint8_t gpiotoGPFsel[] = {  0,0,0,0,0,0,0,0,0,0,
                              1,1,1,1,1,1,1,1,1,1,
                              2,2,2,2,2,2,2,2,2,2,
                              3,3,3,3,3,3,3,3,3,3,
                              4,4,4,4,4,4,4,4,4,4,
                              5,5,5,5,5,5,5,5,5,5,
                            };

  uint8_t gpiotoshift[]   = { 0,3,6,9,12,15,18,21,24,27,
                              0,3,6,9,12,15,18,21,24,27,
                              0,3,6,9,12,15,18,21,24,27,
                              0,3,6,9,12,15,18,21,24,27,
                              0,3,6,9,12,15,18,21,24,27,
                            };
  int     gpiopin;
  int     fsel;
  int     shift;

  if(!RPI_CheckHandle(RPI_gpio))  return false;
  if(!RPI_IsGPIOValid(GPIO))      return false;

  //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("RPI Data Port Mode: GPIO %lld -> %s "), GPIO, isinput?__L("input"):__L("output"));

  fsel    = gpiotoGPFsel[GPIO] ;
  shift   = gpiotoshift[GPIO] ;

  if(isinput) *(RPI_gpio+ fsel) = (*(RPI_gpio+ fsel) & ~(7 << shift)) ;               // Sets bits to zero = input
        else  *(RPI_gpio+ fsel) = (*(RPI_gpio+ fsel) & ~(7 << shift)) | (1 << shift);
  

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOLINUXGPIORASPBERRYPI::RPI_GPIORead(XQWORD GPIO)
* @brief      RPI_GPIORead
* @ingroup    PLATFORM_LINUX
*
* @param[in]  GPIO : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXGPIORASPBERRYPI::RPI_GPIORead(XQWORD GPIO)
{
  uint8_t gpiotoGPLEV [] = {  13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
                              14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,
                           };

  if(!RPI_CheckHandle(RPI_gpio))  return false;
  if(!RPI_IsGPIOValid(GPIO))      return false; 

  //XTRACE_PRINTCOLOR(1, __L("RPI Data Port Read: GPIO %lld"), GPIO);

  if((*(RPI_gpio + gpiotoGPLEV[GPIO]) & (1 << (GPIO & 31))) != 0)
    {     
      return true;
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOLINUXGPIORASPBERRYPI::RPI_GPIOWrite(XQWORD GPIO, bool isactive)
* @brief      RPI_GPIOWrite
* @ingroup    PLATFORM_LINUX
*
* @param[in]  GPIO : 
* @param[in]  isactive : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXGPIORASPBERRYPI::RPI_GPIOWrite(XQWORD GPIO, bool isactive)
{
  uint8_t gpiotoGPSET [] = {  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
                              8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
                           };


  uint8_t gpiotoGPCLR [] = { 10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
                             11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,
                           };


  if(!RPI_CheckHandle(RPI_gpio))  return false;
  if(!RPI_IsGPIOValid(GPIO))      return false;

  //XTRACE_PRINTCOLOR(1, __L("RPI Data Port Write: GPIO %lld ->%s"), GPIO, isactive?__L("on"):__L("off"));

  if(isactive)   *(RPI_gpio + gpiotoGPSET[GPIO]) = 1 << (GPIO & 31);
          else   *(RPI_gpio + gpiotoGPCLR[GPIO]) = 1 << (GPIO & 31);

  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOLINUXGPIORASPBERRYPI::RPI_CheckHandle(uint32_t* RPI_gpio)
* @brief      RPI_CheckHandle
* @ingroup    PLATFORM_LINUX
* 
* @param[in]  RPI_gpio : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXGPIORASPBERRYPI::RPI_CheckHandle(uint32_t* RPI_gpio)
{
  long long result = (long long)(RPI_gpio);

  if(result == -1) return false;

  return true;
} 


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOLINUXGPIORASPBERRYPI::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_LINUX
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOLINUXGPIORASPBERRYPI::Clean()
{
  RPI_model           = RASPBERRYPI_MODEL_UNKNOWN;
  RPI_megabytes       = 0;
  RPI_revision        = 0.0f;
  RPI_gpio_base       = 0;
}


#pragma endregion


#endif

