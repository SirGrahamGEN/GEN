/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOLINUXLedNeoPixelWS2812BRPi.h
* 
* @class      DIOLINUXLEDNEOPIXELWS2812BRPI
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

#ifndef _DIOLINUXLEDNEOPIXELWS2812BRPI_H_
#define _DIOLINUXLEDNEOPIXELWS2812BRPI_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "XBuffer.h"
#include "XLINUXIDRPi.h"

#include "ws2811.h"

#include "DIOLedNeoPixelWS2812B.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


//--------------------------------------------------------------------------------------------------------------------
// DMA support P4 (GPIO 18)

// defaults 
#define NEOPIXELWS2812BRPI_DEFAULT_TARGET_FREQ             WS2811_TARGET_FREQ
#define NEOPIXELWS2812BRPI_DEFAULT_GPIO_PIN                18
#define NEOPIXELWS2812BRPI_DEFAULT_DMA                     10
//#define NEOPIXELWS2812BRPI_DEFAULT_STRIP_TYPE            WS2811_STRIP_RGB		// WS2812/SK6812RGB integrated chip+leds
#define NEOPIXELWS2812BRPI_DEFAULT_STRIP_TYPE              WS2811_STRIP_GBR		// WS2812/SK6812RGB integrated chip+leds
//#define NEOPIXELWS2812BRPI_DEFAULT_STRIP_TYPE            SK6812_STRIP_RGBW	// SK6812RGBW (NOT SK6812RGB)

#define NEOPIXELWS2812BRPI_DEFAULT_WIDTH                   8
#define NEOPIXELWS2812BRPI_DEFAULT_HEIGHT                  8
#define NEOPIXELWS2812BRPI_DEFAULT_LED_COUNT               (NEOPIXELWS2812BRPI_DEFAULT_WIDTH * NEOPIXELWS2812BRPI_DEFAULT_HEIGHT)


//--------------------------------------------------------------------------------------------------------------------
// SPI support P5 (GPIO 10)

// pci bar info
// from: https://github.com/G33KatWork/RP1-Reverse-Engineering/blob/master/pcie/hacks.py
#define RP1_BAR1                                          0x1f00000000
#define RP1_BAR1_LEN                                      0x400000

// offsets from include/dt-bindings/mfd/rp1.h
// https://github.com/raspberrypi/linux/blob/rpi-6.1.y/include/dt-bindings/mfd/rp1.h
#define RP1_IO_BANK0_BASE                                 0x0d0000
#define RP1_RIO0_BASE                                     0x0e0000
#define RP1_PADS_BANK0_BASE                               0x0f0000

// the following info is from the RP1 datasheet (draft & incomplete as of 2024-02-18)
// https://datasheets.raspberrypi.com/rp1/rp1-peripherals.pdf
#define RP1_ATOM_XOR_OFFSET                               0x1000
#define RP1_ATOM_SET_OFFSET                               0x2000
#define RP1_ATOM_CLR_OFFSET                               0x3000

#define PADS_BANK0_VOLTAGE_SELECT_OFFSET                  0
#define PADS_BANK0_GPIO_OFFSET                            0x4
                                                         
#define RIO_OUT_OFFSET                                    0x00
#define RIO_OE_OFFSET                                     0x04
#define RIO_NOSYNC_IN_OFFSET                              0x08
#define RIO_SYNC_IN_OFFSET                                0x0C

//                                                          3         2         1
//                                                          10987654321098765432109876543210
#define CTRL_MASK_FUNCSEL                                 0b00000000000000000000000000011111
#define PADS_MASK_OUTPUT                                  0b00000000000000000000000011000000

#define CTRL_FUNCSEL_RIO                                  0x05

// SPI
#define RP1_SPI8_BASE                                     0x04c000  // not available on gpio
#define RP1_SPI0_BASE                                     0x050000
#define RP1_SPI1_BASE                                     0x054000
#define RP1_SPI2_BASE                                     0x058000
#define RP1_SPI3_BASE                                     0x05c000
#define RP1_SPI4_BASE                                     0x060000
#define RP1_SPI5_BASE                                     0x064000
#define RP1_SPI6_BASE                                     0x068000  // not available on gpio
#define RP1_SPI7_BASE                                     0x06c000  // not available on gpio


// from: https://github.com/raspberrypi/linux/blob/rpi-6.1.y/drivers/spi/spi-dw.h

/* Register offsets (Generic for both DWC APB SSI and DWC SSI IP-cores) */
// many of the descriptions below were auto-filled by co-pilot, so they may not be accurate // why the fuck would you do that then!!!
// second comments are second suggestions by co-pilot
#define DW_SPI_CTRLR0                                     0x00 // control register 0 (frame format, clock polarity, phase, etc.) 
#define DW_SPI_CTRLR1                                     0x04 // control register 1 (number of data frames)
#define DW_SPI_SSIENR                                     0x08 // enable register (enable/disable the SPI controller)
#define DW_SPI_MWCR                                       0x0c // Microwire control register (not used in SPI mode)
#define DW_SPI_SER                                        0x10 // chip select, bit = chip select line? see dw_spi_set_cs()   // slave enable register
#define DW_SPI_BAUDR                                      0x14 // baud rate register // author: verified on the Pi5 to be a straight divisor of 200MHz clk_sys
#define DW_SPI_TXFTLR                                     0x18 // seems to be the number of bytes in the TX FIFO // transmit FIFO threshold level
#define DW_SPI_RXFTLR                                     0x1c // seems to be the number of bytes in the RX FIFO // receive FIFO threshold level
#define DW_SPI_TXFLR                                      0x20 // seems to be the number of bytes in the TX FIFO // transmit FIFO level
#define DW_SPI_RXFLR                                      0x24 // seems to be the number of bytes in the RX FIFO // receive FIFO level
#define DW_SPI_SR                                         0x28 // status register
#define DW_SPI_IMR                                        0x2c // interrupt mask register
#define DW_SPI_ISR                                        0x30 // interrupt status register
#define DW_SPI_RISR                                       0x34 // raw interrupt status register 
#define DW_SPI_TXOICR                                     0x38 // transmit FIFO overflow interrupt clear register
#define DW_SPI_RXOICR                                     0x3c // receive FIFO overflow interrupt clear register
#define DW_SPI_RXUICR                                     0x40 // receive FIFO underflow interrupt clear register
#define DW_SPI_MSTICR                                     0x44 // multi-master interrupt clear register
#define DW_SPI_ICR                                        0x48 // interrupt clear register
#define DW_SPI_DMACR                                      0x4c // DMA control register
#define DW_SPI_DMATDLR                                    0x50 // DMA transmit data level register
#define DW_SPI_DMARDLR                                    0x54 // DMA receive data level register
#define DW_SPI_IDR                                        0x58 // Identification register
#define DW_SPI_VERSION                                    0x5c // version register
#define DW_SPI_DR                                         0x60 // data register
#define DW_SPI_RX_SAMPLE_DLY                              0xf0 // receive sample delay register
#define DW_SPI_CS_OVERRIDE                                0xf4 // chip select override register

//  Each SSI controller is based on a configuration of the Synopsys DW_apb_ssi IP (v4.02a).
// APB
/* Bit fields in CTRLR0 (DWC APB SSI) */
//                                                          3         2         1
//                                                          10987654321098765432109876543210

#define DW_PSSI_CTRLR0_DFS_MASK                           0b00000000000000000000000000001111  //  GENMASK(3, 0)
#define DW_PSSI_CTRLR0_DFS32_MASK                         0b00000000000111110000000000000000  //  GENMASK(20, 16)

#define DW_PSSI_CTRLR0_FRF_MASK                           0b00000000000000000000000000110000  //  GENMASK(5, 4)
#define DW_SPI_CTRLR0_FRF_MOTO_SPI                        0x0
#define DW_SPI_CTRLR0_FRF_TI_SSP                          0x1
#define DW_SPI_CTRLR0_FRF_NS_MICROWIRE                    0x2
#define DW_SPI_CTRLR0_FRF_RESV                            0x3

#define DW_PSSI_CTRLR0_MODE_MASK                          0b00000000000000000000000011000000  //  GENMASK(7, 6)
#define DW_PSSI_CTRLR0_SCPHA                              0b00000000000000000000000001000000  //  BIT(6)
#define DW_PSSI_CTRLR0_SCPOL                              0b00000000000000000000000010000000  //  BIT(7)

#define DW_PSSI_CTRLR0_TMOD_MASK                          0b00000000000000000000001100000000  //  GENMASK(9, 8)
#define DW_SPI_CTRLR0_TMOD_TR                             0x0        // xmit & recv 
#define DW_SPI_CTRLR0_TMOD_TO                             0x1        // xmit only 
#define DW_SPI_CTRLR0_TMOD_RO                             0x2        // recv only 
#define DW_SPI_CTRLR0_TMOD_EPROMREAD                      0x3        // eeprom read mode 

#define DW_PSSI_CTRLR0_SLV_OE                             0b00000000000000000000010000000000  //  BIT(10)
#define DW_PSSI_CTRLR0_SRL                                0b00000000000000000000100000000000  //  BIT(11)
#define DW_PSSI_CTRLR0_CFS                                0b00000000000000000001000000000000  //  BIT(12)

// Bit fields in CTRLR0 (DWC SSI with AHB interface) - not relevant in the RP1 
#define DW_HSSI_CTRLR0_DFS_MASK                           0b00000000000000000000000000011111  //  GENMASK(4, 0)
#define DW_HSSI_CTRLR0_FRF_MASK                           0b00000000000000000000000011000000  //  GENMASK(7, 6)
#define DW_HSSI_CTRLR0_SCPHA                              0b00000000000000000000000100000000  //  BIT(8)
#define DW_HSSI_CTRLR0_SCPOL                              0b00000000000000000000001000000000  //  BIT(9)
#define DW_HSSI_CTRLR0_TMOD_MASK                          0b00000000000000000000011000000000  //  GENMASK(11, 10)
#define DW_HSSI_CTRLR0_SRL                                0b00000000000000000001000000000000  //  BIT(13)
#define DW_HSSI_CTRLR0_MST                                0b10000000000000000000000000000000  //  BIT(31)

// Bit fields in CTRLR1 
#define DW_SPI_NDF_MASK                                   0b00000000000000001111111111111111  //  GENMASK(15, 0) // Number of data frames

// Bit fields in SR, 7 bits 
#define DW_SPI_SR_MASK                                    0b00000000000000000000000001111111  //  GENMASK(6, 0)
#define DW_SPI_SR_BUSY                                    0b00000000000000000000000000000001  //  BIT(0)
#define DW_SPI_SR_TF_NOT_FULL                             0b00000000000000000000000000000010  //  BIT(1)
#define DW_SPI_SR_TF_EMPT                                 0b00000000000000000000000000000100  //  BIT(2)
#define DW_SPI_SR_RF_NOT_EMPT                             0b00000000000000000000000000001000  //  BIT(3)
#define DW_SPI_SR_RF_FULL                                 0b00000000000000000000000000010000  //  BIT(4)
#define DW_SPI_SR_TX_ERR                                  0b00000000000000000000000000100000  //  BIT(5)
#define DW_SPI_SR_DCOL                                    0b00000000000000000000000001000000  //  BIT(6)

// Bit fields in ISR, IMR, RISR, 7 bits 
#define DW_SPI_INT_MASK                                   0b00000000000000000000000000111111  //  GENMASK(5, 0)
#define DW_SPI_INT_TXEI                                   0b00000000000000000000000000000001  //  BIT(0) TX FIFO empty
#define DW_SPI_INT_TXOI                                   0b00000000000000000000000000000010  //  BIT(1) TX FIFO overflow
#define DW_SPI_INT_RXUI                                   0b00000000000000000000000000000100  //  BIT(2) RX FIFO underflow
#define DW_SPI_INT_RXOI                                   0b00000000000000000000000000001000  //  BIT(3) RX FIFO overflow
#define DW_SPI_INT_RXFI                                   0b00000000000000000000000000010000  //  BIT(4) RX FIFO full
#define DW_SPI_INT_MSTI                                   0b00000000000000000000000000100000  //  BIT(5) Multi-Master contention

/* Bit fields in DMACR */
#define DW_SPI_DMACR_RDMAE                                0b00000000000000000000000000000001  //  BIT(0)
#define DW_SPI_DMACR_TDMAE                                0b00000000000000000000000000000010  //  BIT(1)
//                                                          10987654321098765432109876543210
//                                                          3         2         1


typedef struct
{
    uint8_t                   number;
    volatile uint32_t*        status;
    volatile uint32_t*        ctrl;
    volatile uint32_t*        pad;

} GPIO_PIN_T;


typedef struct 
{

    volatile void*            regbase;
    char*                     txdata;
    char*                     rxdata;
    uint8_t                   txcount;

} RP1_SPI_INSTANCE_T;

typedef struct
{
    volatile void*            rp1_peripherial_base;
    volatile void*            gpio_base;
    volatile void*            pads_base;
    volatile uint32_t*        rio_out;
    volatile uint32_t*        rio_output_enable;
    volatile uint32_t*        rio_nosync_in;

    GPIO_PIN_T*               pins[27];
    RP1_SPI_INSTANCE_T*       spis[6];

} RP1_T;


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class DIOLINUXLEDNEOPIXELWS2812BRPI : public DIOLEDNEOPIXELWS2812B
{
  public:
                              DIOLINUXLEDNEOPIXELWS2812BRPI     ();
    virtual                  ~DIOLINUXLEDNEOPIXELWS2812BRPI     ();

    virtual bool              Ini                               (XDWORD nled);   
    virtual bool              Send                              ();    
    virtual bool              End                               ();
    
  private:

    bool                      CreateRP1                         (RP1_T** rp1, void* base);
    bool                      CreateMOSIPin                     (RP1_T* rp1, uint32_t funcmask);
    uint8_t                   GetBit                            (uint8_t value, short bit);
    uint8_t                   RotateByte                        (uint8_t byte);
    void*                     MapGPIO                           (off_t dev_base, off_t dev_size);
    bool                      RP1SPICreate                      (RP1_T *rp1, uint8_t spinum, RP1_SPI_INSTANCE_T** spi);
    void                      RP1SPIWriteArrayBlocking          (RP1_SPI_INSTANCE_T* spi, uint8_t data[], int data_length);

    int                       Sleep                             (long msec);

    void                      Clean                             ();

    RPI_MODEL                 model;
    RP1_SPI_INSTANCE_T*       spi;
    ws2811_t                  config;
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

