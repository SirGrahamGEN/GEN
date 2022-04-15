/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOModBus.h
*
* @class      DIOMODBUS
* @brief      Data Input/Output Mod Bus protocol class
* @ingroup    DATAIO
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

#ifndef _DIOMODBUS_H_
#define _DIOMODBUS_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XBuffer.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/


enum DIOMODBUSMODE
{
  DIOMODBUSMODE_UNKNOWN   = 0 ,

  DIOMODBUSMODE_RTU           ,
  DIOMODBUSMODE_ASCII         ,
  DIOMODBUSMODE_TCPIP

};


enum DIOMODBUS_FUNCTION
{
  DIOMODBUS_FUNCTION_READ_COILS                        = 0x01 ,
  DIOMODBUS_FUNCTION_READ_DISCRETE_INPUTS              = 0x02 ,
  DIOMODBUS_FUNCTION_READ_HOLDING_REGISTERS            = 0x03 ,
  DIOMODBUS_FUNCTION_READ_INPUT_REGISTERS              = 0x04 ,
  DIOMODBUS_FUNCTION_WRITE_SINGLE_COIL                 = 0x05 ,
  DIOMODBUS_FUNCTION_WRITE_SINGLE_REGISTER             = 0x06 ,
  DIOMODBUS_FUNCTION_WRITE_MULTIPLE_COILS              = 0x0F ,
  DIOMODBUS_FUNCTION_WRITE_MULTIPLE_REGISTERS          = 0x10 ,
  DIOMODBUS_FUNCTION_READ_FILE_RECORD                  = 0x14 ,
  DIOMODBUS_FUNCTION_WRITE_FILE_RECORD                 = 0x15 ,
  DIOMODBUS_FUNCTION_MASK_WRITE_REGISTER               = 0x16 ,
  DIOMODBUS_FUNCTION_READWRITE_MULTIPLE_REGISTERS      = 0x17 ,
  DIOMODBUS_FUNCTION_READ_FIFO_QUEUE                   = 0x18 ,
  DIOMODBUS_FUNCTION_ENCAPSULATED_INTERFACE_TRANSPORT  = 0x2B
};

#define DIOMODBUSMODE_STANDARDPORT                      502
#define DIOMODBUSMODE_DEFAULTTIMEOUT                    5


#define DIOMODBUSMODE_SIZEANSWERFIX                     sizeanswer =    2                                     /* Size Head (Address +  Function Code  */             \
                                                                      + 2                                     /* Addres                               */             \
                                                                      + 2                                     /* Value                                */             \
                                                                      + 2                                     /* Size CRC                             */

#define DIOMODBUSMODE_SIZEANSWERVAR                     sizeanswer =    3                                     /* Size Head (Address +  Function Code + Size data */  \
                                                                      + diostream->GetInXBuffer()->GetByte(2) /* Size data */                                        \
                                                                      + 2                                     /* Size CRC */




/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class DIOSTREAM;

class DIOMODBUS
{
  public:
                              DIOMODBUS               (DIOSTREAM* diostream, DIOMODBUSMODE mode);
    virtual                  ~DIOMODBUS               ();

    DIOSTREAM*                GetDIOStream            ();

    DIOMODBUSMODE             GetMode                 ();
    bool                      SetMode                 (DIOMODBUSMODE mode);

    bool                      Connect                 (XBYTE unit, int timeout = DIOMODBUSMODE_DEFAULTTIMEOUT);

    XBYTE                     GetUnit                 ();
    void                      SetUnit                 (XBYTE unit);

    bool                      ReadHoldingRegisters    (XWORD address, XWORD nregisters, XBUFFER& answer, int timeout = DIOMODBUSMODE_DEFAULTTIMEOUT);

    bool                      ReadInputRegisters      (XWORD address, XWORD nregisters, XMAP<XWORD, XWORD>& answer, int timeout = DIOMODBUSMODE_DEFAULTTIMEOUT);
    bool                      WriteSingleRegister     (XWORD address, XWORD value, int timeout = DIOMODBUSMODE_DEFAULTTIMEOUT);

    bool                      Disconnect              ();

  private:

    bool                      MakeCommand             (DIOMODBUS_FUNCTION function, XBUFFER& ask, XBUFFER& answer, int timeout = DIOMODBUSMODE_DEFAULTTIMEOUT);
    XWORD                     CRC16                   (XBUFFER& data);

    void                      Clean                   ();

    DIOSTREAM*                diostream;

    DIOMODBUSMODE             mode;
    XBYTE                     unit;

    XTIMER*                   xtimer;

};


/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/




#endif


