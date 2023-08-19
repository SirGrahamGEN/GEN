/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       INPCapture.cpp
* 
* @class      INPCAPTURE
* @brief      Input Capture class
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

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "INPCapture.h"

#include "INPCapture_XEvent.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE


#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         INPCAPTURE:: INPCAPTURE()
* @brief      NPWINDOWSKEYBOARDHOOK
* @ingroup    PLATFORM_WINDOWS
* 
* @return     INPCAPTURE:: : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
INPCAPTURE:: INPCAPTURE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         INPCAPTURE::~ INPCAPTURE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup
*
* @author     Abraham J. Velez
* @date       18/09/2018 12:20:39
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
INPCAPTURE::~ INPCAPTURE()
{ 
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void INPCAPTURE::SetApplicationHandle(void* applicationhandle)
* @brief      SetApplicationHandle
* @ingroup    INPUT
* 
* @param[in]  applicationhandle : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void INPCAPTURE::SetApplicationHandle(void* applicationhandle)
{
  this->applicationhandle = applicationhandle;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPCAPTURE::Activate()
* @brief      Activate
* @ingroup    INPUT
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPCAPTURE::Activate()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPCAPTURE::Deactivate()
* @brief      Deactivate
* @ingroup    INPUT
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPCAPTURE::Deactivate()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void INPCAPTURE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    INPUT
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void INPCAPTURE::Clean()
{
  applicationhandle   = NULL;  
}


#pragma endregion