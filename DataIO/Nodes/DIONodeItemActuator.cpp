/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIONodeActuator.cpp
* 
* @class      DIONODEITEMACTUATOR
* @brief      Data Input/Output Node Item Actuator
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

#include "DIONodeItemActuator.h"

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
DIONODEITEMACTUATOR::DIONODEITEMACTUATOR() : DIONODEITEM()
{
  Clean();

  itemtype = DIONODEITEM_TYPE_ACTUATOR;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEITEMACTUATOR::~DIONODEITEMACTUATOR()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEITEMACTUATOR::~DIONODEITEMACTUATOR()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIONODEITEMACTUATOR_TYPE DIONODEITEMACTUATOR::GetActuatorType()
* @brief      GetActuatorType
* @ingroup    DATAIO
* 
* @return     DIONODEITEMACTUATOR_TYPE : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIONODEITEMACTUATOR_TYPE DIONODEITEMACTUATOR::GetActuatorType()
{
  return actuatortype;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEITEMACTUATOR::SetActuatorType(DIONODEITEMACTUATOR_TYPE type)
* @brief      SetActuatorType
* @ingroup    DATAIO
* 
* @param[in]  type : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEMACTUATOR::SetActuatorType(DIONODEITEMACTUATOR_TYPE type)
{
  actuatortype = type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEMACTUATOR::GetActuatorTypeDescription(XSTRING& typedescription)
* @brief      GetActuatorTypeDescription
* @ingroup    DATAIO
* 
* @param[in]  typedescription : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEMACTUATOR::GetActuatorTypeDescription(XSTRING& typedescription)
{
   typedescription.Empty();
 
   switch(actuatortype) 
    {
      case DIONODEITEM_TYPE_ACTUATOR_UNKNOWN   : 
                                     default   : typedescription = __L("Unknown");                      
                                                 return false;  
                                                 break;

      case DIONODEITEM_TYPE_ACTUATOR_GPIO      : typedescription = __L("GPIO");                break;
      case DIONODEITEM_TYPE_ACTUATOR_LIGHT     : typedescription = __L("Light");               break;
      case DIONODEITEM_TYPE_ACTUATOR_ENGINE    : typedescription = __L("Engine");              break;
    
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEMACTUATOR::Serialize()
* @brief      Serialize
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEMACTUATOR::Serialize()
{
  DIONODEITEM::Serialize();

  XSTRING typedescription;
 
  GetActuatorTypeDescription(typedescription);  

  Primitive_Add<int>(actuatortype, __L("actuator_type"));
  Primitive_Add<XSTRING*>(&typedescription, __L("actuator_description"));

  XVectorClass_Add<DIONODEITEMVALUE>(GetValues(), __L("values"), __L("value"));
  
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIONODEITEMACTUATOR::Deserialize()
* @brief      Deserialize
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONODEITEMACTUATOR::Deserialize()
{   
  DIONODEITEM::Deserialize();

  Primitive_Extract<int>(actuatortype, __L("actuator_type"));

  XVectorClass_Extract<DIONODEITEMVALUE>(GetValues(), __L("values"), __L("value"));

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEITEMACTUATOR::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEMACTUATOR::Clean()
{
  actuatortype = DIONODEITEM_TYPE_ACTUATOR_UNKNOWN;
}
