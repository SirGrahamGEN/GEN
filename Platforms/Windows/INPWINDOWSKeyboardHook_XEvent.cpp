/**-------------------------------------------------------------------------------------------------------------------
*
* @file       INPWINDOWSKeyboardHook_XEvent.cpp
*
* @class      INPWINDOWSKEYBOARDHOOK_XEVENT
* @brief      eXtended Drive Image Manager Event class
* @ingroup    UTILS
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

#include "INPWINDOWSKeyboardHook_XEvent.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPWINDOWSKEYBOARDHOOK_XEVENT::INPWINDOWSKEYBOARDHOOK_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family)
* @brief      Constructor
* @ingroup    UTILS
*
* @param[in]  subject :
* @param[in]  type :
* @param[in]  family :
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
INPWINDOWSKEYBOARDHOOK_XEVENT::INPWINDOWSKEYBOARDHOOK_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family) : XEVENT(subject, type, family)
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPWINDOWSKEYBOARDHOOK_XEVENT::~INPWINDOWSKEYBOARDHOOK_XEVENT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    UTILS
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
INPWINDOWSKEYBOARDHOOK_XEVENT::~INPWINDOWSKEYBOARDHOOK_XEVENT()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD INPWINDOWSKEYBOARDHOOK_XEVENT::GetVKCode()
* @brief      GetVKCode
* @ingroup    PLATFORM_WINDOWS
* 
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD INPWINDOWSKEYBOARDHOOK_XEVENT::GetVKCode()
{
  return vkcode;
}


 
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void INPWINDOWSKEYBOARDHOOK_XEVENT::SetVKCode(XDWORD vkcode)
* @brief      SetVKCode
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  vkcode : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void INPWINDOWSKEYBOARDHOOK_XEVENT::SetVKCode(XDWORD vkcode)
{
  this->vkcode = vkcode;
}
 


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XWORD INPWINDOWSKEYBOARDHOOK_XEVENT::GetScanCode()
* @brief      GetScanCode
* @ingroup    PLATFORM_WINDOWS
* 
* @return     XWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XWORD INPWINDOWSKEYBOARDHOOK_XEVENT::GetScanCode()
{
  return scancode;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void INPWINDOWSKEYBOARDHOOK_XEVENT::SetScanCode(XWORD scancode)
* @brief      SetScanCode
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  scancode : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void INPWINDOWSKEYBOARDHOOK_XEVENT::SetScanCode(XWORD scancode)
{
  this->scancode = scancode;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD INPWINDOWSKEYBOARDHOOK_XEVENT::GetFlags()
* @brief      GetFlags
* @ingroup    PLATFORM_WINDOWS
* 
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD INPWINDOWSKEYBOARDHOOK_XEVENT::GetFlags()
{
  return flags;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void INPWINDOWSKEYBOARDHOOK_XEVENT::SetFlags(XWORD flags)
* @brief      SetFlags
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  flags : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void INPWINDOWSKEYBOARDHOOK_XEVENT::SetFlags(XWORD flags)
{
  this->flags = flags;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPWINDOWSKEYBOARDHOOK_XEVENT::IsKeyPressed()
* @brief      IsKeyPressed
* @ingroup    PLATFORM_WINDOWS
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool INPWINDOWSKEYBOARDHOOK_XEVENT::IsKeyLocked()
{
  return iskeylocked;
}
    


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void INPWINDOWSKEYBOARDHOOK_XEVENT::SetIsKeyLocked(bool iskeylocked)
* @brief      SetIsKeyLocked
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  iskeylocked : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void INPWINDOWSKEYBOARDHOOK_XEVENT::SetIsKeyLocked(bool iskeylocked)
{
  this->iskeylocked = iskeylocked;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void INPWINDOWSKEYBOARDHOOK_XEVENT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    UTILS
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void INPWINDOWSKEYBOARDHOOK_XEVENT::Clean()
{
  vkcode        = 0; 
  scancode      = 0;
  flags         = 0;
  iskeylocked   = false;
}




