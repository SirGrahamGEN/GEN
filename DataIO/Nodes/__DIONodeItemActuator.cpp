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

  type = DIONODEITEM_TYPE_ACTUATOR;
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
* @fn         XDWORD DIONODEITEMACTUATOR::GetActuatorType()
* @brief      GetActuatorType
* @ingroup    DATAIO
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIONODEITEMACTUATOR::GetActuatorType()
{
  return actuatortype;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEITEMACTUATOR::SetActuatorType(XDWORD actuatortype)
* @brief      SetActuatorType
* @ingroup    DATAIO
* 
* @param[in]  actuatortype : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEMACTUATOR::SetActuatorType(XDWORD actuatortype)
{
  this->actuatortype = actuatortype;

  GenerateActuatorDescription();
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

  Primitive_Add<int>(actuatortype, __L("actuator_type"));
  Primitive_Add<XSTRING*>(&description, __L("description"));
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
  Primitive_Extract<XSTRING*>(&description, __L("description"));
  XVectorClass_Extract<DIONODEITEMVALUE>(GetValues(), __L("values"), __L("value"));

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIONODEITEMACTUATOR::GenerateActuatorDescription()
* @brief      GenerateActuatorDescription
* @ingroup    DATAIO
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIONODEITEMACTUATOR::GenerateActuatorDescription()
{
  description.Empty();

  GetPrimaryDescription(description);

  if(!description.IsEmpty())
    {
      description += __L(" ");
    }
 
   switch(actuatortype) 
    {
      case DIONODEITEMACTUATOR_TYPE_UNKNOWN     : description += __L("Unknown");                      
                                                  break;

      case DIONODEITEMACTUATOR_TYPE_GPIO        : description += __L("GPIO");                
                                                  break;

      case DIONODEITEMACTUATOR_TYPE_LIGHT       : description += __L("light");               
                                                  break;

      case DIONODEITEMACTUATOR_TYPE_ENGINE      : description += __L("engine");              
                                                  break;
  
                                    default     : break;   
    }
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
  actuatortype = DIONODEITEMACTUATOR_TYPE_UNKNOWN;
}
