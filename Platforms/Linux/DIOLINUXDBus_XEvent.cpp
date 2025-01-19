/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOLINUXDBus_XEvent.cpp
* 
* @class      DIOLINUXDBUS_XEVENT
* @brief      LINUX Data Input/Output DBus eXtended Event class
* @ingroup    PLATFORM_LINUX
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

#include "DIOLINUXDBus_XEvent.h"

#include "XString.h"
#include "XPath.h"
#include "XEvent.h"

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
* @fn         DIOLINUXDBUS_XEVENT::DIOLINUXDBUS_XEVENT(XSUBJECT* subject, XDWORD type)
* @brief      Constructor of class
* @ingroup    PLATFORM_LINUX
* 
* @param[in]  subject : 
* @param[in]  type : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOLINUXDBUS_XEVENT::DIOLINUXDBUS_XEVENT(XSUBJECT* subject, XDWORD type) : XEVENT(subject, type, XEVENT_TYPE_LINUX_DBUS)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOLINUXDBUS_XEVENT::~DIOLINUXDBUS_XEVENT()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    PLATFORM_LINUX
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOLINUXDBUS_XEVENT::~DIOLINUXDBUS_XEVENT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOLINUXDBUS_SIGNAL* DIOLINUXDBUS_XEVENT::GetSignal()
* @brief      Get signal
* @ingroup    PLATFORM_LINUX
*
* @return     DIOLINUXDBUS_SIGNAL* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOLINUXDBUS_SIGNAL* DIOLINUXDBUS_XEVENT::GetSignal()
{
  return signal;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOLINUXDBUS_XEVENT::SetSignal(DIOLINUXDBUS_SIGNAL* signal)
* @brief      Set signal
* @ingroup    PLATFORM_LINUX
*
* @param[in]  signal : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOLINUXDBUS_XEVENT::SetSignal(DIOLINUXDBUS_SIGNAL* signal)
{
  this->signal = signal;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOLINUXDBUS_MESSAGE* DIOLINUXDBUS_XEVENT::GetMessage()
* @brief      Get message
* @ingroup    PLATFORM_LINUX
*
* @return     DIOLINUXDBUS_MESSAGE* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOLINUXDBUS_MESSAGE* DIOLINUXDBUS_XEVENT::GetMessage()
{
  return message;
}
  

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOLINUXDBUS_XEVENT::SetMessage(DIOLINUXDBUS_MESSAGE* message)
* @brief      Set message
* @ingroup    PLATFORM_LINUX
*
* @param[in]  message : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOLINUXDBUS_XEVENT::SetMessage(DIOLINUXDBUS_MESSAGE* message)
{
  this->message = message;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOLINUXDBUS_XEVENT::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    PLATFORM_LINUX
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOLINUXDBUS_XEVENT::Clean()
{  
  signal  = NULL;
  message = NULL;
}


#pragma endregion


