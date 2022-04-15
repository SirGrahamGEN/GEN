/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOLINUXGPIORaspberryPi.h
*
* @class      DIOLINUXGPIORASPBERRYPI
* @brief      Data Input/Output LINUX GPIO (General Purpose Input/Output) Raspberry Pi
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

#ifdef HW_RASPBERRYPI

#ifndef _DIOLINUXGPIORASPBERRYPI_H_
#define _DIOLINUXGPIORASPBERRYPI_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "DIOGPIO.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum RASPBERRYPI_MODEL
{
  RASPBERRYPI_MODEL_UNKNOWN           =   0 ,
  RASPBERRYPI_MODEL_A                       ,
  RASPBERRYPI_MODEL_B                       ,
  RASPBERRYPI_MODEL_A_PLUS                  ,
  RASPBERRYPI_MODEL_B_PLUS                  ,
  RASPBERRYPI_MODEL_COMPUTERMODULE          ,
  RASPBERRYPI_MODEL_B_2                     ,
  RASPBERRYPI_MODEL_ZERO                    ,
  RASPBERRYPI_MODEL_CM3                     ,
  RASPBERRYPI_MODEL_CM3P                    ,
  RASPBERRYPI_MODEL_B_3                     ,
  RASPBERRYPI_MODEL_B_3P                    ,
  RASPBERRYPI_MODEL_B_4                     ,
};


#define RPI_BCM2708_PERI_BASE           0x20000000     // Rapsberry Pi A+, B+
#define RPI_BCM2708_PERI_BASE_2         0x3F000000     // Rapsberry Pi 2 y 3
#define	RPI_BCM2708_PERI_BASE_4         0xFE000000     // Rapsberry Pi 4 


#define RPI_PAGE_SIZE                   (4*1024)
#define RPI_BLOCK_SIZE                  (4*1024)

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class DIOLINUXGPIORASPBERRYPI : public DIOGPIO
{
  public:
                                        DIOLINUXGPIORASPBERRYPI     ();
    virtual                            ~DIOLINUXGPIORASPBERRYPI     ();

    bool                                Ini                         ();
    
    bool                                SetMode                     (DIOGPIO_ENTRY* entry, XWORD mode);  

    bool                                GetValue                    (DIOGPIO_ENTRY* entry);
    bool                                SetValue                    (DIOGPIO_ENTRY* entry, bool value);

    bool                                End                         ();

  private:

    bool                                RPI_RevisionBoard           (RASPBERRYPI_MODEL& model, int& megabytes, float& revision);
    bool                                RPI_Ini                     ();
    bool                                RPI_End                     ();
    bool                                RPI_IsGPIOValid             (XQWORD GPIO);
    bool                                RPI_GPIOMode                (XQWORD GPIO, bool isinput);
    bool                                RPI_GPIORead                (XQWORD GPIO);
    bool                                RPI_GPIOWrite               (XQWORD GPIO, bool isactive);

    void                                Clean                       ();

    RASPBERRYPI_MODEL                   RPI_model;
    int                                 RPI_megabytes;
    float                               RPI_revision;
    XDWORD                              RPI_gpio_base;
};


/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif

#endif

