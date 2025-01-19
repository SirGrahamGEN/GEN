/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       INPFactory.cpp
* 
* @class      INPFACTORY
* @brief      INPUT Factory class
* @ingroup    INPUT
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

#include "INPFactory.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

INPFACTORY* INPFACTORY::instance = NULL;

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPFACTORY::INPFACTORY()
* @brief      Constructor of class
* @ingroup    INPUT
*
* --------------------------------------------------------------------------------------------------------------------*/
INPFACTORY::INPFACTORY()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPFACTORY::~INPFACTORY()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    INPUT
*
* --------------------------------------------------------------------------------------------------------------------*/
INPFACTORY::~INPFACTORY()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPFACTORY::GetIsInstanced()
* @brief      Get is instanced
* @note       STATIC
* @ingroup    INPUT
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool INPFACTORY::GetIsInstanced()
{
  return instance!=NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         INPFACTORY& INPFACTORY::GetInstance()
* @brief      Get instance
* @ingroup    INPUT
* 
* @return     INPFACTORY& : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
INPFACTORY& INPFACTORY::GetInstance()
{
  if(!instance) instance = new INPFACTORY();

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPFACTORY::SetInstance(INPFACTORY* _instance)
* @brief      Set instance
* @ingroup    INPUT
* 
* @param[in]  _instance : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPFACTORY::SetInstance(INPFACTORY* _instance)
{
  if(!_instance) return false;

  instance = _instance;

  return (instance)?true:false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPFACTORY::DelInstance()
* @brief      Del instance
* @ingroup    INPUT
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPFACTORY::DelInstance()
{
  if(!instance) return false;

  delete instance;
  instance = NULL;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPDEVICE* INPFACTORY::CreateDevice(XCHAR* device, void* param)
* @brief      Create device
* @ingroup    INPUT
*
* @param[in]  type  : device type of the input device
* @param[in]  param : param to create device (if is necessary)
*
* @return     INPDEVICE* : device input created
*
* --------------------------------------------------------------------------------------------------------------------*/
INPDEVICE* INPFACTORY::CreateDevice(INPDEVICE_TYPE type, void* param)
{
  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPFACTORY::DeleteDevice(INPDEVICE* device)
* @brief      Delete device
* @ingroup    INPUT
*
* @param[in]  device : delete device
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool INPFACTORY::DeleteDevice(INPDEVICE* device)
{
  return false;
}


#ifdef INP_SIMULATE_ACTIVE
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         INPSIMULATE* INPFACTORY::CreateSimulator()
* @brief      Create simulator
* @ingroup    INPUT
* 
* @return     INPSIMULATE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
INPSIMULATE* INPFACTORY::CreateSimulator()
{
  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPFACTORY::DeleteSimulator(INPSIMULATE* inputsimulated)
* @brief      Delete simulator
* @ingroup    INPUT
* 
* @param[in]  inputsimulated : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPFACTORY::DeleteSimulator(INPSIMULATE* inputsimulated)
{
  return false;
}
#endif


#ifdef INP_CAPTURE_ACTIVE
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         INPCAPTURE* INPFACTORY::CreateCapture()
* @brief      Create capture
* @ingroup    INPUT
* 
* @return     INPCAPTURE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
INPCAPTURE* INPFACTORY::CreateCapture()
{
  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPFACTORY::DeleteCapture(INPCAPTURE* inputcapture)
* @brief      Delete capture
* @ingroup    INPUT
* 
* @param[in]  inputcapture : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPFACTORY::DeleteCapture(INPCAPTURE* inputcapture)
{
  return false;
}

#endif


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void INPFACTORY::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    INPUT
*
* --------------------------------------------------------------------------------------------------------------------*/
void INPFACTORY::Clean()
{

}


#pragma endregion








