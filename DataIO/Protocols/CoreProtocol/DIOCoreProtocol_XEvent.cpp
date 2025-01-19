/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOProtocol_XEvent.cpp
* 
* @class      DIOCOREPROTOCOL_XEVENT
* @brief      Data Input/Output Core Protocol eXtended Event class
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIOCoreProtocol_XEvent.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOCOREPROTOCOL_XEVENT::DIOCOREPROTOCOL_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family)
* @brief      Constructor of class
* @ingroup    DATAIO
*
* @param[in]  subject :
* @param[in]  family :
* @param[in]  type :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_XEVENT::DIOCOREPROTOCOL_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family): XEVENT(subject, type, family)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOCOREPROTOCOL_XEVENT::~DIOCOREPROTOCOL_XEVENT()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_XEVENT::~DIOCOREPROTOCOL_XEVENT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOPROTOCOL* DIOCOREPROTOCOL_XEVENT::GetProtocol()
* @brief      Get protocol
* @ingroup    DATAIO
*
* @return     DIOPROTOCOL* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL* DIOCOREPROTOCOL_XEVENT::GetProtocol()
{
  return protocol;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOCOREPROTOCOL_XEVENT::SetProtocol(DIOPROTOCOL* protocol)
* @brief      Set protocol
* @ingroup    DATAIO
*
* @param[in]  protocol :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_XEVENT::SetProtocol(DIOCOREPROTOCOL* protocol)
{
  if(!protocol) return false;
  this->protocol = protocol;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOCOREPROTOCOL_XEVENT::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_XEVENT::Clean()
{
  protocol    = NULL;
}


#pragma endregion

