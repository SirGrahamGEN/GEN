/**-------------------------------------------------------------------------------------------------------------------
*
* @file       INPManager.cpp
*
* @class      INPMANAGER
* @brief      Input Manager class
* @ingroup    INPUT
*
* @copyright  GEN Group. All right reserved.
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
*---------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XFactory.h"

#include "INPButton.h"
#include "INPDevice.h"

#include "INPManager.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

INPMANAGER* INPMANAGER::instance = NULL;

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPMANAGER::GetIsInstanced()
* @brief      Get Is Instanced
* @ingroup    INPUT
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool INPMANAGER::GetIsInstanced()
{
  return instance!=NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPMANAGER& INPMANAGER::GetInstance()
* @brief      Get Instance
* @ingroup    INPUT
*
* @return     INPMANAGER& : inpmanager instance
*
*---------------------------------------------------------------------------------------------------------------------*/
INPMANAGER& INPMANAGER::GetInstance()
{
  if(!instance) instance = new INPMANAGER();

  return (*instance);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPMANAGER::DelInstance()
* @brief      Delete Instance
* @ingroup    INPUT
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool INPMANAGER::DelInstance()
{
  if(!instance) return false;

  delete instance;
  instance = NULL;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPMANAGER::AddDevice(INPDEVICE* device)
* @brief      Add Device
* @ingroup    INPUT
*
* @param[in]  device : device to add
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool INPMANAGER::AddDevice(INPDEVICE* device)
{
  if(!device)             return false;
  if(!device->IsCreated()) return false;

  devicemap.Add(device->GetType(), device);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPMANAGER::DelDevice(INPDEVICE* device)
* @brief      Delete Device
* @ingroup    INPUT
*
* @param[in]  device : device to delete
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool INPMANAGER::DelDevice(INPDEVICE* device)
{
  if(!device)               return false;
  if(!device->IsCreated())  return false;

  devicemap.Delete(device->GetType(), device);

  delete device;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPMANAGER::DeleteAllDevices()
* @brief      Delete All Devices
* @ingroup    INPUT
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool INPMANAGER::DeleteAllDevices()
{
  if(devicemap.IsEmpty()) return false;

  devicemap.DeleteElementContents();
  devicemap.DeleteAll();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int INPMANAGER::GetNDevices()
* @brief      Get Number of Devices
* @ingroup    INPUT
*
* @return     int : Number of Devices
*
*---------------------------------------------------------------------------------------------------------------------*/
int INPMANAGER::GetNDevices()
{
  return devicemap.GetSize();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPDEVICE* INPMANAGER::GetDevice(int index)
* @brief      Get Device by index
* @ingroup    INPUT
*
* @param[in]  index : index of device
*
* @return     INPDEVICE* : device obtain
*
*---------------------------------------------------------------------------------------------------------------------*/
INPDEVICE* INPMANAGER::GetDevice(int index)
{
  if(devicemap.IsEmpty()) return NULL;

  INPDEVICE* device = devicemap.GetElement(index);
  if(device) return device;

  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPDEVICE* INPMANAGER::GetDevice(INPDEVICE_TYPE type)
* @brief      Get Device by type
* @ingroup    INPUT
*
* @param[in]  type : type of device
*
* @return     INPDEVICE* : device obtain
*
*---------------------------------------------------------------------------------------------------------------------*/
INPDEVICE* INPMANAGER::GetDevice(INPDEVICE_TYPE type)
{
  if(devicemap.IsEmpty()) return NULL;

  int index =  devicemap.Find(type);
  if(index == -1) return NULL;

  INPDEVICE* device = devicemap.GetElement(index);
  if(device) return device;

  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPMANAGER::Update()
* @brief      Update
* @ingroup    INPUT
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool INPMANAGER::Update()
{
  if(devicemap.IsEmpty())  return false;

  for(XDWORD c=0;c<devicemap.GetSize();c++)
    {
      INPDEVICE* device = devicemap.GetElement(c);
      if(device) device->Update();
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPMANAGER::INPMANAGER()
* @brief      Constructor
* @ingroup    INPUT
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
INPMANAGER::INPMANAGER()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPMANAGER::~INPMANAGER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    INPUT
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
INPMANAGER::~INPMANAGER()
{
  DeleteAllDevices();

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void INPMANAGER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    INPUT
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void INPMANAGER::Clean()
{
  devicemap.DeleteAll();
}
