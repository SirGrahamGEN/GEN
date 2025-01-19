/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       INPWINDOWSFactory.cpp
* 
* @class      INPWINDOWSFACTORY
* @brief      WINDOWS Input factory class
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "INPWINDOWSFactory.h"

#include "INPWINDOWSDeviceKeyboard.h"
#include "INPWINDOWSDeviceMouse.h"

#include "INPWINDOWSSimulate.h"
#include "INPWINDOWSCapture.h"

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
* @fn         INPDEVICE* INPWINDOWSFACTORY::CreateDevice(XCHAR* devicename, void* param)
* @brief      Create device
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
* @brief      Delete device
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


#ifdef INP_SIMULATE_ACTIVE
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         INPSIMULATE* INPWINDOWSFACTORY::CreateSimulator()
* @brief      Create simulator
* @ingroup    PLATFORM_WINDOWS
* 
* @return     INPSIMULATE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
INPSIMULATE* INPWINDOWSFACTORY::CreateSimulator()
{
  INPSIMULATE* inpsimulated = (INPSIMULATE*)new INPWINDOWSSIMULATE();

  return inpsimulated;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPWINDOWSFACTORY::DeleteSimulator(INPSIMULATE* inputsimulated)
* @brief      Delete simulator
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  inputsimulated : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPWINDOWSFACTORY::DeleteSimulator(INPSIMULATE* inputsimulated)
{
  INPWINDOWSSIMULATE* inpsimulated = (INPWINDOWSSIMULATE*)inputsimulated;

  if(!inpsimulated)
    {
      return false;
    }

  delete inpsimulated;

  return true;
}
#endif


#ifdef INP_CAPTURE_ACTIVE
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         INPCAPTURE* INPWINDOWSFACTORY::CreateCapture()
* @brief      Create capture
* @ingroup    PLATFORM_WINDOWS
* 
* @return     INPCAPTURE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
INPCAPTURE* INPWINDOWSFACTORY::CreateCapture()
{
  INPCAPTURE* inpcapture = (INPCAPTURE*)new INPWINDOWSCAPTURE();

  return inpcapture;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPWINDOWSFACTORY::DeleteCapture(INPCAPTURE* inputcapture)
* @brief      Delete capture
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  inputcapture : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPWINDOWSFACTORY::DeleteCapture(INPCAPTURE* inputcapture)
{
  INPWINDOWSCAPTURE* inpcapture = (INPWINDOWSCAPTURE*)inputcapture;

  if(!inpcapture)
    {
      return false;
    }

  delete inpcapture;

  return true;
}

#endif



#pragma endregion

