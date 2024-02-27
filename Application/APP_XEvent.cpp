/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       APP_XEvent.cpp
* 
* @class      APP_XEVENT
* @brief      Application eXtended Event class
* @ingroup    APPLICATION
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

#include "APP_XEvent.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE


#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         APP_XEVENT::APP_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family)
* @brief      Constructor
* @ingroup    APPLICATION
* 
* @param[in]  XSUBJECT* : 
* @param[in]  XDWORD type : 
* @param[in]  XDWORD family : 
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
APP_XEVENT::APP_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family) : XEVENT(subject, type, family)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         APP_XEVENT::~APP_XEVENT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    APPLICATION
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
APP_XEVENT::~APP_XEVENT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSYSTEM_CHANGESTATUSTYPE APP_XEVENT::GetChangeStatusType()
* @brief      GetChangeStatusType
* @ingroup    APPLICATION
* 
* @return     XSYSTEM_CHANGESTATUSTYPE : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSYSTEM_CHANGESTATUSTYPE APP_XEVENT::GetChangeStatusType()
{
  return changestatustype;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APP_XEVENT::SetChangeStatusType(XSYSTEM_CHANGESTATUSTYPE changestatustype)
* @brief      SetChangeStatusType
* @ingroup    APPLICATION
* 
* @param[in]  changestatustype : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APP_XEVENT::SetChangeStatusType(XSYSTEM_CHANGESTATUSTYPE changestatustype)
{
  this->changestatustype = changestatustype;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APP_XEVENT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    APPLICATION
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APP_XEVENT::Clean()
{
  changestatustype = XSYSTEM_CHANGESTATUSTYPE_NONE;
}


#pragma endregion