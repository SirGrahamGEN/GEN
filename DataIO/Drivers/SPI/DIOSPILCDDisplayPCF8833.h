/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOSPILCDDisplayPCF8833.h
* 
* @class      DIOSPILCDDISPLAYPCF8833
* @brief      Data Input/Output SPI Display LCD Philips PCF8833 class
* @ingroup    DATAIO
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

#ifndef _DIOSPILCDDISPLAYPCF8833_H_
#define _DIOSPILCDDISPLAYPCF8833_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include <stdio.h>

#include "DIODeviceSPI.h"
#include "DIOGPIO.h"

#include "DIODisplayDevice.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


enum DIOSPILCDDISPLAYPCF8833_TYPE
{
  DIOSPILCDDISPLAYPCF8833_UNKNOWN    = 0 ,
  DIOSPILCDDISPLAYPCF8833_EPSON          ,
  DIOSPILCDDISPLAYPCF8833_PHILLIPS
};


#define DIOSPILCDDISPLAYPCF8833_EPSON_CMD_DISON                  0xAF
#define DIOSPILCDDISPLAYPCF8833_EPSON_CMD_DISOFF                 0xAE
#define DIOSPILCDDISPLAYPCF8833_EPSON_CMD_DISNOR                 0xA6
#define DIOSPILCDDISPLAYPCF8833_EPSON_CMD_DISINV                 0xA7
#define DIOSPILCDDISPLAYPCF8833_EPSON_CMD_SLPIN                  0x95
#define DIOSPILCDDISPLAYPCF8833_EPSON_CMD_SLPOUT                 0x94
#define DIOSPILCDDISPLAYPCF8833_EPSON_CMD_COMSCN                 0xBB
#define DIOSPILCDDISPLAYPCF8833_EPSON_CMD_DISCTL                 0xCA
#define DIOSPILCDDISPLAYPCF8833_EPSON_CMD_PASET                  0x75
#define DIOSPILCDDISPLAYPCF8833_EPSON_CMD_CASET                  0x15
#define DIOSPILCDDISPLAYPCF8833_EPSON_CMD_DATCTL                 0xBC
#define DIOSPILCDDISPLAYPCF8833_EPSON_CMD_RGBSET8                0xCE
#define DIOSPILCDDISPLAYPCF8833_EPSON_CMD_RAMWR                  0x5C
#define DIOSPILCDDISPLAYPCF8833_EPSON_CMD_RAMRD                  0x5D
#define DIOSPILCDDISPLAYPCF8833_EPSON_CMD_PTLIN                  0xA8
#define DIOSPILCDDISPLAYPCF8833_EPSON_CMD_PTLOUT                 0xA9
#define DIOSPILCDDISPLAYPCF8833_EPSON_CMD_RMWIN                  0xE0
#define DIOSPILCDDISPLAYPCF8833_EPSON_CMD_RMWOUT                 0xEE
#define DIOSPILCDDISPLAYPCF8833_EPSON_CMD_ASCSET                 0xAA
#define DIOSPILCDDISPLAYPCF8833_EPSON_CMD_SCSTART                0xAB
#define DIOSPILCDDISPLAYPCF8833_EPSON_CMD_OSCON                  0xD1
#define DIOSPILCDDISPLAYPCF8833_EPSON_CMD_OSCOFF                 0xD2
#define DIOSPILCDDISPLAYPCF8833_EPSON_CMD_PWRCTR                 0x20
#define DIOSPILCDDISPLAYPCF8833_EPSON_CMD_VOLCTR                 0x81
#define DIOSPILCDDISPLAYPCF8833_EPSON_CMD_VOLUP                  0xD6
#define DIOSPILCDDISPLAYPCF8833_EPSON_CMD_VOLDOWN                0xD7
#define DIOSPILCDDISPLAYPCF8833_EPSON_CMD_TMPGRD                 0x82
#define DIOSPILCDDISPLAYPCF8833_EPSON_CMD_EPCTIN                 0xCD
#define DIOSPILCDDISPLAYPCF8833_EPSON_CMD_EPCOUT                 0xCC
#define DIOSPILCDDISPLAYPCF8833_EPSON_CMD_EPMWR                  0xFC
#define DIOSPILCDDISPLAYPCF8833_EPSON_CMD_EPMRD                  0xFD
#define DIOSPILCDDISPLAYPCF8833_EPSON_CMD_EPSRRD1                0x7C
#define DIOSPILCDDISPLAYPCF8833_EPSON_CMD_EPSRRD2                0x7D
#define DIOSPILCDDISPLAYPCF8833_EPSON_CMD_NOP                    0x25


#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_NOP                 0x00    // nop
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_SWRESET             0x01    // software reset
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_BSTROFF             0x02    // booster voltage OFF
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_BSTRON              0x03    // booster voltage ON
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_RDDIDIF             0x04    // read display identification
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_RDDST               0x09    // read display status
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_SLEEPIN             0x10    // sleep in
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_SLEEPOUT            0x11    // sleep out
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_PTLON               0x12    // partial display mode
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_NORON               0x13    // display normal mode
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_INVOFF              0x20    // inversion OFF
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_INVON               0x21    // inversion ON
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_DALO                0x22    // all pixel OFF
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_DAL                 0x23    // all pixel ON
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_SETCON              0x25    // write contrast
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_DISPOFF             0x28    // display OFF
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_DISPON              0x29    // display ON
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_CASET               0x2A    // column address set
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_PASET               0x2B    // page address set
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_RAMWR               0x2C    // memory write
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_RGBSET              0x2D    // colour set
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_PTLAR               0x30    // partial area
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_VSCRDEF             0x33    // vertical scrolling definition
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_TEOFF               0x34    // test mode
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_TEON                0x35    // test mode
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_MADCTL              0x36    // memory access control
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_SEP                 0x37    // vertical scrolling start address
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_IDMOFF              0x38    // idle mode OFF
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_IDMON               0x39    // idle mode ON
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_COLMOD              0x3A    // interface pixel format
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_SETVOP              0xB0    // set Vop
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_BRS                 0xB4    // bottom row swap
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_TRS                 0xB6    // top row swap
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_DISCTR              0xB9    // display control
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_DOR                 0xBA    // data order
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_TCDFE               0xBD    // enable/disable DF temperature compensation
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_TCVOPE              0xBF    // enable/disable Vop temp comp
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_EC                  0xC0    // internal or external oscillator
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_SETMUL              0xC2    // set multiplication factor
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_TCVOPAB             0xC3    // set TCVOP slopes A and B
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_TCVOPCD             0xC4    // set TCVOP slopes c and d
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_TCDF                0xC5    // set divider frequency
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_DF8COLOR            0xC6    // set divider frequency 8-color mode
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_SETBS               0xC7    // set bias system
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_RDTEMP              0xC8    // temperature read back
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_RDID1               0xDA    // read ID1
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_RDID2               0xDB    // read ID2
#define DIOSPILCDDISPLAYPCF8833_PHILLIPS_CMD_RDID3               0xDC    // read ID3

#define DIOSPILCDDISPLAYPCF8833_ADDCOMMAND(buffer, command)      buffer.Bit_AddData((XWORD)(command & (~0x0100)))
#define DIOSPILCDDISPLAYPCF8833_ADDDATA(buffer, data)            buffer.Bit_AddData((XWORD)(data    |   0x0100))

#define DIOSPILCDDISPLAYPCF8833_ROW_LENGTH                       132
#define DIOSPILCDDISPLAYPCF8833_COL_HEIGHT                       132

// 12-bit color definitions

#define DIOSPILCDDISPLAYPCF8833_RGB444(r,g,b)                    (((r&0xF0)<<4) | (g&0xF0) | (b>>4))

#define DIOSPILCDDISPLAYPCF8833_COLOR_WHITE                      DIOSPILCDDISPLAYPCF8833_RGB444(255,255,255)
#define DIOSPILCDDISPLAYPCF8833_COLOR_BLACK                      DIOSPILCDDISPLAYPCF8833_RGB444(0,0,0)
#define DIOSPILCDDISPLAYPCF8833_COLOR_RED                        DIOSPILCDDISPLAYPCF8833_RGB444(255,0,0)
#define DIOSPILCDDISPLAYPCF8833_COLOR_GREEN                      DIOSPILCDDISPLAYPCF8833_RGB444(0,255,0)
#define DIOSPILCDDISPLAYPCF8833_COLOR_BLUE                       DIOSPILCDDISPLAYPCF8833_RGB444(0,0,255)
#define DIOSPILCDDISPLAYPCF8833_COLOR_CYAN                       DIOSPILCDDISPLAYPCF8833_RGB444(0,255,255)
#define DIOSPILCDDISPLAYPCF8833_COLOR_MAGENTA                    DIOSPILCDDISPLAYPCF8833_RGB444(255,0,255)
#define DIOSPILCDDISPLAYPCF8833_COLOR_YELLOW                     DIOSPILCDDISPLAYPCF8833_RGB444(255,255,0)
#define DIOSPILCDDISPLAYPCF8833_COLOR_BROWN                      DIOSPILCDDISPLAYPCF8833_RGB444(165,42,42)
#define DIOSPILCDDISPLAYPCF8833_COLOR_ORANGE                     DIOSPILCDDISPLAYPCF8833_RGB444(255,165,0)
#define DIOSPILCDDISPLAYPCF8833_COLOR_PINK                       DIOSPILCDDISPLAYPCF8833_RGB444(255,192,203)

/*
#define DIOSPILCDDISPLAYPCF8833_COLOR_WHITE                      0xFFF0
#define DIOSPILCDDISPLAYPCF8833_COLOR_BLACK                      0x0000
#define DIOSPILCDDISPLAYPCF8833_COLOR_RED                        0xF000
#define DIOSPILCDDISPLAYPCF8833_COLOR_GREEN                      0x0F00
#define DIOSPILCDDISPLAYPCF8833_COLOR_BLUE                       0x00F0
#define DIOSPILCDDISPLAYPCF8833_COLOR_CYAN                       0x0FF0
#define DIOSPILCDDISPLAYPCF8833_COLOR_MAGENTA                    0xF0F0
#define DIOSPILCDDISPLAYPCF8833_COLOR_YELLOW                     0xFF00
#define DIOSPILCDDISPLAYPCF8833_COLOR_BROWN                      0xB220
#define DIOSPILCDDISPLAYPCF8833_COLOR_ORANGE                     0xFA00
#define DIOSPILCDDISPLAYPCF8833_COLOR_PINK                       0xF6A0
*/


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class DIOSPILCDDISPLAYPCF8833 : public DIODISPLAYDEVICE, public DIODEVICESPI
{
  public:
                                  DIOSPILCDDISPLAYPCF8833         (DIOSPILCDDISPLAYPCF8833_TYPE type);
    virtual                      ~DIOSPILCDDISPLAYPCF8833         ();

    bool                          IniDevice                       ();

    bool                          Clear                           (XWORD color = DIOSPILCDDISPLAYPCF8833_COLOR_BLACK);
    bool                          Update                          (XBYTE* buffer);
    bool                          PutPixel                        (XWORD x, XWORD y, XWORD color);

    bool                          End                             ();

  private:

    bool                          Initializate                    ();

    bool                          Reset                           ();

    bool                          SetWindow                       (XWORD x0, XWORD y0, XWORD x1, XWORD y1);
    bool                          Draw_HLine                      (XBYTE x, XBYTE y, XBYTE width, XWORD color);
    bool                          Draw_HLine                      (XBYTE x, XBYTE y, XBYTE width, XWORD* buffer);

    bool                          Buffer_AjustWithNOP             (XBUFFER& databuffer);
    bool                          Buffer_Send                     (XBUFFER& databuffer);
    bool                          Buffer_Delete                   (XBUFFER& databuffer);

    void                          Clean                           ();

    DIOSPILCDDISPLAYPCF8833_TYPE  type;
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

