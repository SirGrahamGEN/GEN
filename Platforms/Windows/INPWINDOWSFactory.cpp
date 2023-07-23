/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       INPWINDOWSFactory.cpp
* 
* @class      INPWINDOWSFACTORY
* @brief      INPUT WINDOWS factory 
* @ingroup    PLATFORM_WINDOWS
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

#include "INPWINDOWSFactory.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "INPWINDOWSDeviceKeyboard.h"
#include "INPWINDOWSDeviceMouse.h"

#include "INPWINDOWSSimulated.h"

#include "INPWINDOWSFactory.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE


#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPDEVICE* INPWINDOWSFACTORY::CreateDevice(XCHAR* devicename, void* param)
* @brief      reateDevice
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  type : device type of the input device
* @param[in]  param : param to create device (in windows need handle to windows)
*
* @return     INPDEVICE* : device input created
*
* --------------------------------------------------------------------------------------------------------------------*/
INPDEVICE* INPWINDOWSFACTORY::CreateDevice(INPDEVICE_TYPE type, void* param)
{
  INPDEVICE* inpdevice = NULL;

  switch(type)
    {
      case INPDEVICE_TYPE_NONE          :

      case INPDEVICE_TYPE_JOSTICK       :
      case INPDEVICE_TYPE_TOUCHSCREEN   :
      case INPDEVICE_TYPE_WIIMOTE       : break;

      case INPDEVICE_TYPE_KEYBOARD      : { INPWINDOWSDEVICEKEYBOARD* keyboard = new INPWINDOWSDEVICEKEYBOARD();
                                            if(keyboard)
                                              {
                                                keyboard->SetScreen(param);
                                                inpdevice = keyboard;
                                              }
                                          }
                                          break;

      case INPDEVICE_TYPE_MOUSE         : { INPWINDOWSDEVICEMOUSE* mouse = new INPWINDOWSDEVICEMOUSE();
                                            if(mouse)
                                              {
                                                mouse->SetScreen(param);
                                                inpdevice = mouse;
                                              }
                                          }
                                          break;

    }

  return inpdevice;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool INPWINDOWSFACTORY::DeleteDevice(INPDEVICE* device)
* @brief      Delete Device
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  device : device to delete
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool INPWINDOWSFACTORY::DeleteDevice(INPDEVICE* device)
{
  if(!device)  return false;

  delete device;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         INPSIMULATED* INPWINDOWSFACTORY::CreateSimulator()
* @brief      CreateSimulator
* @ingroup    PLATFORM_WINDOWS
* 
* @return     INPSIMULATED* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
INPSIMULATED* INPWINDOWSFACTORY::CreateSimulator()
{
  INPSIMULATED* inpsimulated = (INPSIMULATED*)new INPWINDOWSSIMULATED();

  return inpsimulated;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPWINDOWSFACTORY::DeleteSimulator(INPSIMULATED* inputsimulated)
* @brief      DeleteSimulator
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  inputsimulated : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPWINDOWSFACTORY::DeleteSimulator(INPSIMULATED* inputsimulated)
{
  INPWINDOWSSIMULATED* inpsimulated = (INPWINDOWSSIMULATED*)inputsimulated;

  if(!inpsimulated)
    {
      return false;
    }

  delete inpsimulated;

  return true;
}



#pragma endregion

