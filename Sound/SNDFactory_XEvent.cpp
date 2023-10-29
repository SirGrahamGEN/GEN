/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       SNDFactory_XEvent.cpp
* 
* @class      SNDFACTORY_XEVENT
* @brief      Sound Factory eXtended event class
* @ingroup    SOUND
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

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "SNDFactory_XEvent.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------

@fn         SNDFACTORY_XEVENT::SNDFACTORY_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family)
@brief      Constructor
@ingroup    SOUND

@param[in]  XSUBJECT* : 
@param[in]   XDWORD type : 
@param[in]   XDWORD family : 

@return     Does not return anything. 

--------------------------------------------------------------------------------------------------------------------*/
SNDFACTORY_XEVENT::SNDFACTORY_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family) : XEVENT(subject, type, family)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDFACTORY_XEVENT::~SNDFACTORY_XEVENT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    SOUND
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDFACTORY_XEVENT::~SNDFACTORY_XEVENT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SNDFACTORY_XEVENT_TYPE SNDFACTORY_XEVENT::GetType()
* @brief      GetType
* @ingroup    SOUND
* 
* @return     SNDFACTORY_XEVENT_TYPE : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SNDFACTORY_XEVENT_TYPE SNDFACTORY_XEVENT::GetType()
{ 
  return type;                   
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDFACTORY_XEVENT::SetType(SNDFACTORY_XEVENT_TYPE type)
* @brief      SetType
* @ingroup    SOUND
* 
* @param[in]  type : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDFACTORY_XEVENT::SetType(SNDFACTORY_XEVENT_TYPE type)
{ 
  this->type = type;                   
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SNDFACTORY_XEVENT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    SOUND
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SNDFACTORY_XEVENT::Clean()
{
  type       = SNDFACTORY_XEVENT_TYPE_UNKNOWN;
}


#pragma endregion

