/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIONodeItemSensor.h
* 
* @class      DIONODEITEMSENSOR
* @brief      Data Input/Output Node Item Sensor
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

#ifndef _DIONODEITEMSENSOR_H_
#define _DIONODEITEMSENSOR_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "DIONodeItem.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum DIONODEITEMSENSOR_TYPE
{
  DIONODEITEMSENSOR_TYPE_UNKNOWN                    = 0 ,

  DIONODEITEMSENSOR_TYPE_GPIO                           ,
  DIONODEITEMSENSOR_TYPE_HUMIDITY                       ,
  DIONODEITEMSENSOR_TYPE_TEMPERATURE                    ,
  DIONODEITEMSENSOR_TYPE_TEMPERATURE_HUMIDITY           ,
  DIONODEITEMSENSOR_TYPE_LIGHT                          ,

  DIONODEITEMSENSOR_TYPE_OWNER
};


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class DIONODEITEMSENSOR : public DIONODEITEM
{
  public:
                                  DIONODEITEMSENSOR           ();
    virtual                      ~DIONODEITEMSENSOR           ();

    XDWORD                        GetSensorType               ();
    void                          SetSensorType               (XDWORD sensortype); 
   
    virtual bool                  Serialize                   ();                                          
    virtual bool                  Deserialize                 (); 

  protected: 
    
    XDWORD                        sensortype;   

  private:

    void                          GenerateSensorDescription   ();

    void                          Clean                       ();
};

/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif
