/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIONodeSensorTempHum.cpp
* 
* @class      DIONODESENSORTEMPHUM
* @brief      Data Input/Output Node Sensor Temperature + Humidity.
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

#include "DIONodeSensorTempHum.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODESENSORTEMPHUM::DIONODESENSORTEMPHUM()
* @brief      Constructor
* @ingroup    
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODESENSORTEMPHUM::DIONODESENSORTEMPHUM() : DIONODESENSOR()
{
  Clean();

  sensortype = DIONODESENSOR_TYPE_TEMP_HUM;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODESENSORTEMPHUM::~DIONODESENSORTEMPHUM()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODESENSORTEMPHUM::~DIONODESENSORTEMPHUM()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODESENSORTEMPHUM::Serialize()
* @brief      Serialize
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODESENSORTEMPHUM::Serialize()
{
  DIONODESENSOR::Serialize(); 

  Primitive_Add<double>(temperature , __L("temperature"));
  Primitive_Add<double>(humidity    , __L("humidity")); 

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODESENSORTEMPHUM::Deserialize()
* @brief      Deserialize
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODESENSORTEMPHUM::Deserialize()
{   
  DIONODESENSOR::Deserialize();

  Primitive_Extract<double>(temperature , __L("temperature"));
  Primitive_Extract<double>(humidity    , __L("humidity")); 

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODESENSORTEMPHUM::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODESENSORTEMPHUM::Clean()
{
  temperature = 0.0f;
  humidity    = 0.0f;
}
