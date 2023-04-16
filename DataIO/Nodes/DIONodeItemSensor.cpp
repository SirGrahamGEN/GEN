/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIONodeItemSensor.cpp
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "DIONodeItemSensor.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEITEMSENSOR::DIONODEITEMSENSOR()
* @brief      Constructor
* @ingroup    
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEITEMSENSOR::DIONODEITEMSENSOR() : DIONODEITEM()
{
  Clean();

  type = DIONODEITEM_TYPE_SENSOR;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEITEMSENSOR::~DIONODEITEMSENSOR()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEITEMSENSOR::~DIONODEITEMSENSOR()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIONODEITEMSENSOR::GetSensorType()
* @brief      GetSensorType
* @ingroup    DATAIO
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIONODEITEMSENSOR::GetSensorType()
{
  return sensortype;
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEITEMSENSOR::SetSensorType(XDWORD sensortype)
* @brief      SetSensorType
* @ingroup    DATAIO
* 
* @param[in]  sensortype : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEMSENSOR::SetSensorType(XDWORD sensortype)
{
  this->sensortype = sensortype;

  GenerateSensorDescription();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEMSENSOR::Serialize()
* @brief      Serialize
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEMSENSOR::Serialize()
{
  DIONODEITEM::Serialize();
  
  Primitive_Add<int>(sensortype, __L("sensor_type")); 
  Primitive_Add<XSTRING*>(&description, __L("description"));
  XVectorClass_Add<DIONODEITEMVALUE>(GetValues(), __L("values"), __L("value"));
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEMSENSOR::Deserialize()
* @brief      Deserialize
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEMSENSOR::Deserialize()
{   
  DIONODEITEM::Deserialize();

  Primitive_Extract<int>(sensortype, __L("sensor_type"));
  Primitive_Extract<XSTRING*>(&description, __L("description"));
  XVectorClass_Extract<DIONODEITEMVALUE>(GetValues(), __L("values"), __L("value"));

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEITEMSENSOR::GenerateSensorDescription()
* @brief      GenerateSensorDescription
* @ingroup    DATAIO
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEMSENSOR::GenerateSensorDescription()
{
  description.Empty();

  GetPrimaryDescription(description);

  if(!description.IsEmpty())
    {
      description += __L(" ");
    }

  switch(sensortype) 
    {
      case DIONODEITEMSENSOR_TYPE_UNKNOWN               : description += __L("Unknown");                            
                                                          break;

      case DIONODEITEMSENSOR_TYPE_GPIO                  : description += __L("GPIO");                     
                                                          break;

      case DIONODEITEMSENSOR_TYPE_HUMIDITY              : description += __L("humidity");                     
                                                          break;

      case DIONODEITEMSENSOR_TYPE_TEMPERATURE           : description += __L("temperature");                  
                                                          break;

      case DIONODEITEMSENSOR_TYPE_TEMPERATURE_HUMIDITY  : description += __L("temperature / humidity");       
                                                          break;

      case DIONODEITEMSENSOR_TYPE_LIGHT                 : description += __L("light");                        
                                                          break;

                                             default    : break;                                
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEITEMSENSOR::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEMSENSOR::Clean()
{
  sensortype = DIONODEITEMSENSOR_TYPE_UNKNOWN;
}
