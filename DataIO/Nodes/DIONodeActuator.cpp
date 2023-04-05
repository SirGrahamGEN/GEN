/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIONodeActuator.cpp
* 
* @class      DIONODEACTUATOR
* @brief      Data Input/Output Node Actuator
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

#include "DIONodeActuator.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         NODEACTUATOR::NODEACTUATOR()
* @brief      Constructor
* @ingroup    
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEACTUATOR::DIONODEACTUATOR() : DIONODEELEMENT()
{
  Clean();

  elementtype = DIONODEELEMENT_TYPE_ACTUATOR;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEACTUATOR::~DIONODEACTUATOR()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEACTUATOR::~DIONODEACTUATOR()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEACTUATOR_TYPE DIONODEACTUATOR::GetActuatorType()
* @brief      GetActuatorType
* @ingroup    DATAIO
* 
* @return     DIONODEACTUATOR_TYPE : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEACTUATOR_TYPE DIONODEACTUATOR::GetActuatorType()
{
  return actuatortype;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEACTUATOR::SetActuatorType(DIONODEACTUATOR_TYPE type)
* @brief      SetActuatorType
* @ingroup    DATAIO
* 
* @param[in]  type : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEACTUATOR::SetActuatorType(DIONODEACTUATOR_TYPE type)
{
  actuatortype = type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEACTUATOR::GetActuatorTypeDescription(XSTRING& typedescription)
* @brief      GetActuatorTypeDescription
* @ingroup    DATAIO
* 
* @param[in]  typedescription : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEACTUATOR::GetActuatorTypeDescription(XSTRING& typedescription)
{
   typedescription.Empty();
 
   switch(actuatortype) 
    {
      case DIONODEACTUATOR_TYPE_UNKNOWN   : 
                                default   : typedescription = __L("Unknown sensor");                      
                                            return false;  
                                            break;

      case DIONODEACTUATOR_TYPE_LIGHT     : typedescription = __L("Light actuator");                      break;
      case DIONODEACTUATOR_TYPE_ENGINE    : typedescription = __L("Engine actuator");                     break;
    
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEACTUATOR::Serialize()
* @brief      Serialize
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEACTUATOR::Serialize()
{
  DIONODEELEMENT::Serialize();

  XSTRING typedescription;
 
  GetActuatorTypeDescription(typedescription);  

  Primitive_Add<int>(actuatortype, __L("actuator_type"));
  Primitive_Add<XSTRING>(typedescription, __L("actuator_description"));
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEACTUATOR::Deserialize()
* @brief      Deserialize
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEACTUATOR::Deserialize()
{   
  DIONODEELEMENT::Deserialize();

  Primitive_Extract<int>(actuatortype, __L("actuator_type"));

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEACTUATOR::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEACTUATOR::Clean()
{
  actuatortype =  DIONODEACTUATOR_TYPE_UNKNOWN;
}
