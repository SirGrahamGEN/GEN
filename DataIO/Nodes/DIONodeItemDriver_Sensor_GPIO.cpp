/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIONodeItemDriver_Sensor_GPIO.cpp
* 
* @class      DIONODEITEMDRIVER_SENSOR_GPIO
* @brief      Data Input/Output Node Item Driver sensor GPIO
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "DIOGPIO.h"

#include "DIONodeItemSensor.h"

#include "DIONodeItemDriver_Sensor_GPIO.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEITEMDRIVER_SENSOR_GPIO::DIONODEITEMDRIVER_SENSOR_GPIO()
* @brief      Constructor
* @ingroup    DATAIO
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEITEMDRIVER_SENSOR_GPIO::DIONODEITEMDRIVER_SENSOR_GPIO(XDWORD entryID, int GPIO, int pin) : DIONODEITEMDRIVER_GPIO(entryID, GPIO, pin)
{
  Clean();

  type        = DIONODEITEMDRIVER_TYPE_SENSOR_GPIO;
  description = __L("GPIO Input");
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEITEMDRIVER_SENSOR_GPIO::~DIONODEITEMDRIVER_SENSOR_GPIO()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEITEMDRIVER_SENSOR_GPIO::~DIONODEITEMDRIVER_SENSOR_GPIO()
{
  Close();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEMDRIVER_SENSOR_GPIO::Open()
* @brief      Open
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEMDRIVER_SENSOR_GPIO::Open()
{
  DIONODEITEMSENSOR* nodeitemsensor = (DIONODEITEMSENSOR*)GetNodeItem();
  if(nodeitemsensor)
    {  
      nodeitemsensor->SetSensorType(DIONODEITEMSENSOR_TYPE_GPIO); 
    }

  isopen = GEN_DIOGPIO.SetMode(entryID, DIOGPIO_MODE_INPUT);    

  isworking = true;
   
  return isopen;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEMDRIVER_SENSOR_GPIO::Update()
* @brief      Update
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEMDRIVER_SENSOR_GPIO::Update()
{
  DIONODEITEMSENSOR* nodeitemsensor = (DIONODEITEMSENSOR*)GetNodeItem();
  if(!nodeitemsensor)
    {
      return false;
    }

  DIONODEITEMVALUE* itemvalue = nodeitemsensor->GetValues()->Get(0);
  if(!itemvalue) 
    {
      return false;
    }
    
  XVARIANT* value = itemvalue->GetValue();
  if(value)
    {
      bool value_GPIO = GEN_DIOGPIO.GetValue(entryID);

      if((bool)(*value) != value_GPIO)
        {     
          (*value) = value_GPIO;
        
          AdjustTimeInChange(value_GPIO);
          itemvalue->SetValueHasChanged(true);

          XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[DIONODE item driver %s] %s value %s"), GetDescription()->Get(), nodeitemsensor->GetDescription()->Get(), value_GPIO?__L("true"):__L("false"));    
        }
    }
    
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEITEMDRIVER_SENSOR_GPIO::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEMDRIVER_SENSOR_GPIO::Clean()
{

}
