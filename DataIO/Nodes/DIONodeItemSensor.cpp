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

  itemtype = DIONODEITEM_TYPE_SENSOR;
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
* @fn         DIONODEITEMSENSOR_TYPE DIONODEITEMSENSOR::GetSensorType()
* @brief      GetSensorType
* @ingroup    DATAIO
* 
* @return     DIONODEITEMSENSOR_TYPE : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEITEMSENSOR_TYPE DIONODEITEMSENSOR::GetSensorType()
{
  return sensortype;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEITEMSENSOR::SetSensorType(DIONODEITEMSENSOR_TYPE type)
* @brief      SetSensorType
* @ingroup    DATAIO
* 
* @param[in]  type : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEMSENSOR::SetSensorType(DIONODEITEMSENSOR_TYPE type)
{
  this->sensortype = type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEMSENSOR::GetSensorTypeDescription(XSTRING& typedescription)
* @brief      GetSensorTypeDescription
* @ingroup    DATAIO
* 
* @param[in]  typedescription : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEMSENSOR::GetSensorTypeDescription(XSTRING& typedescription)
{
   typedescription.Empty();
 
   switch(sensortype) 
    {
      case DIONODEITEMSENSOR_TYPE_UNKNOWN               : 
                                              default   : typedescription = __L("Unknown");                      
                                                            return false;  
                                                            break;

      case DIONODEITEMSENSOR_TYPE_HUMIDITY              : typedescription = __L("Humidity");                     break;
      case DIONODEITEMSENSOR_TYPE_TEMPERATURE           : typedescription = __L("Temperature");                  break;
      case DIONODEITEMSENSOR_TYPE_TEMPERATURE_HUMIDITY  : typedescription = __L("Temperature/Humidity");         break;
      case DIONODEITEMSENSOR_TYPE_LIGHT                 : typedescription = __L("Light");                        break;
    }

  return true;
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

  XSTRING typedescription;
 
  GetSensorTypeDescription(typedescription);  

  Primitive_Add<int>(sensortype, __L("sensor_type"));
  Primitive_Add<XSTRING*>(&typedescription, __L("sensor_description"));

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

  XVectorClass_Extract<DIONODEITEMVALUE>(GetValues(), __L("values"), __L("value"));

  return true;
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
