/**-------------------------------------------------------------------------------------------------------------------
*
* @file       INPFactoryDevices.cpp
*
* @class      INPFACTORYDEVICES
* @brief      INPUT factory
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "INPFactoryDevices.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

INPFACTORYDEVICES* INPFACTORYDEVICES::instance = NULL;

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPFACTORYDEVICES::INPFACTORYDEVICES()
* @brief      Constructor
* @ingroup    INPUT
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
INPFACTORYDEVICES::INPFACTORYDEVICES()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPFACTORYDEVICES::~INPFACTORYDEVICES()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    INPUT
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
INPFACTORYDEVICES::~INPFACTORYDEVICES()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPFACTORYDEVICES::GetIsInstanced()
* @brief      Get if Is Instanced
* @note       STATIC
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool INPFACTORYDEVICES::GetIsInstanced()
{
  return instance!=NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPFACTORYDEVICES& INPFACTORYDEVICES::GetInstance()
* @brief      Get Instance of INPFACTORYDEVICES
* @note       STATIC
* @ingroup    XUTILS
*
* @return     INPFACTORYDEVICES& :
*
* --------------------------------------------------------------------------------------------------------------------*/
INPFACTORYDEVICES& INPFACTORYDEVICES::GetInstance()
{
  if(!instance) instance = new INPFACTORYDEVICES();

  return (*instance);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPFACTORYDEVICES::SetInstance(INPFACTORYDEVICES* instance)
* @brief      Set Instance of INPFACTORYDEVICES
* @note       STATIC
* @ingroup    XUTILS
*
* @param[in]  _instance : new instance
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool INPFACTORYDEVICES::SetInstance(INPFACTORYDEVICES* _instance)
{
  if(!_instance) return false;

  instance = _instance;

  return (instance)?true:false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPFACTORYDEVICES::DelInstance()
* @brief      Delete Instance of INPFACTORYDEVICES
* @note       STATIC
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool INPFACTORYDEVICES::DelInstance()
{
  if(!instance) return false;

  delete instance;
  instance = NULL;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPDEVICE* INPFACTORYDEVICES::CreateDevice(XCHAR* device, void* param)
* @brief      Create a input Device
* @ingroup    INPUT
*
* @param[in]  type  : device type of the input device
* @param[in]  param : param to create device (if is necessary)
*
* @return     INPDEVICE* : device input created
*
* --------------------------------------------------------------------------------------------------------------------*/
INPDEVICE* INPFACTORYDEVICES::CreateDevice(INPDEVICE_TYPE type, void* param)
{
  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPFACTORYDEVICES::DeleteDevice(INPDEVICE* device)
* @brief      Delete Device
* @ingroup    INPUT
*
* @param[in]  device : delete device
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool INPFACTORYDEVICES::DeleteDevice(INPDEVICE* device)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void INPFACTORYDEVICES::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    INPUT
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void INPFACTORYDEVICES::Clean()
{

}


