/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIONodeItemHandler_SensorAM2315.h
* 
* @class      DIONODEITEMHANDLER_SENSORAM2315
* @brief      Data Input/Output Node Item Handler Sensor AM2315
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

#ifndef _DIONODEITEMHANDLER_SENSOR_AM2315_H_
#define _DIONODEITEMHANDLER_SENSOR_AM2315_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "DIOI2CTemHumSensorAM2315.h"  

#include "DIONodeItemHandler.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/


class DIONODEITEMHANDLER_SENSORAM2315 : public DIONODEITEMHANDLER
{
  public:
                                  DIONODEITEMHANDLER_SENSORAM2315                 (int port, int remoteitemaddress, int timeout);
    virtual                      ~DIONODEITEMHANDLER_SENSORAM2315                 ();

    bool                          Open                                            ();
    bool                          Update                                          ();
    bool                          Close                                           ();

    bool                          SetNodeItem                                     (DIONODEITEM* nodeitem);    
    
  private:

    void                          Clean                                           ();

    DIOI2CTEMHUMSENSORAM2315*     am2315;

    int                           port;
    int                           remoteitemaddress;
    int                           timeout;
};

/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif

