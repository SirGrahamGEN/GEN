/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOCLIClientBTModuleCSR.h
* 
* @class      DIOCLICLIENTBTMODULECSR
* @brief      Data Input/Output CLI (Command Line Interface) client BT Module CSR class 
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

#ifndef _DIOCLICLIENTBTMODULECSR_H_
#define _DIOCLICLIENTBTMODULECSR_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "DIOCLIClient.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum DIOCLICLIENT_TYPECOMMAND
{
  DIOCLICLIENT_TYPECOMMAND_UNKNOWN            = 0 ,

  DIOCLICLIENT_TYPECOMMAND_VERSION              ,
  DIOCLICLIENT_TYPECOMMAND_RSSI                 ,
  DIOCLICLIENT_TYPECOMMAND_GETCFGIOD            ,
  DIOCLICLIENT_TYPECOMMAND_SETCFGIOD            ,
  DIOCLICLIENT_TYPECOMMAND_GETIOD               ,
  DIOCLICLIENT_TYPECOMMAND_SETIOD               ,
  DIOCLICLIENT_TYPECOMMAND_GETIOA1              ,
  DIOCLICLIENT_TYPECOMMAND_ISBATTERYCHARGING    ,
  DIOCLICLIENT_TYPECOMMAND_BATTERYCHARGE        ,
  DIOCLICLIENT_TYPECOMMAND_I2CMEMREAD           ,
  DIOCLICLIENT_TYPECOMMAND_I2CMEMWRITE          ,
  DIOCLICLIENT_TYPECOMMAND_I2CADC               ,
  DIOCLICLIENT_TYPECOMMAND_I2CDAC               ,

  DIOCLICLIENT_TYPECOMMAND_LAST
};

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class DIOCLICLIENTBTMODULECSR  : public DIOCLICLIENT
{
  public:
                                DIOCLICLIENTBTMODULECSR       (DIOSTREAM* diostream);
    virtual                    ~DIOCLICLIENTBTMODULECSR       ();

    DIOCLICLIENT_ERROR          Version                       (int& version,int& subversion);

    DIOCLICLIENT_ERROR          RSSI                          (int& RSSI);

    DIOCLICLIENT_ERROR          GetCFGIOD                     (int portio,bool& isoutput);
    DIOCLICLIENT_ERROR          SetCFGIOD                     (int portio,bool isoutput);
    DIOCLICLIENT_ERROR          GetIOD                        (int portio,bool& isactive);
    DIOCLICLIENT_ERROR          SetIOD                        (int portio,bool isactive);
    DIOCLICLIENT_ERROR          GetIOA1                       (XBYTE& value);

    DIOCLICLIENT_ERROR          IsBatteryCharging             (bool& ischarging);
    DIOCLICLIENT_ERROR          BatteryCharge                 (int& mVolts);

    DIOCLICLIENT_ERROR          I2CMemRead                    (int memID,int index,XBYTE& data);
    DIOCLICLIENT_ERROR          I2CMemWrite                   (int memID,int index,XBYTE data);

    DIOCLICLIENT_ERROR          I2CADC                        (int address,int port,XBYTE& data);
    DIOCLICLIENT_ERROR          I2CDAC                        (int address,XBYTE data);

  private:

    void                        Clean                         ();
};

/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif
