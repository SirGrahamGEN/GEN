/**-------------------------------------------------------------------------------------------------------------------
*
* @file       Script_Lib_System.cpp
*
* @class      SCRIPT_LIB_SYSTEM
* @brief      Script Library System
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @copyright  Copyright(c) 2008 - 2016 GEN Group.
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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "XFactory.h"
#include "XSystem.h"

#include "Script.h"
#include "Script_Lib_System.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/



/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_LIB_SYSTEM::SCRIPT_LIB_SYSTEM()
* @brief      Constructor
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LIB_SYSTEM::SCRIPT_LIB_SYSTEM() : SCRIPT_LIB(SCRIPT_LIB_SYSTEM_NAME)
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_LIB_SYSTEM::~SCRIPT_LIB_SYSTEM()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LIB_SYSTEM::~SCRIPT_LIB_SYSTEM()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_LIB_SYSTEM::AddLibraryFunctions(SCRIPT* script)
* @brief      AddLibraryFunctions
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  script :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LIB_SYSTEM::AddLibraryFunctions(SCRIPT* script)
{
  if(!script) return false;

  this->script = script;

  script->AddLibraryFunction(this, __L("System_Reboot")                      , Call_SystemReboot);
  script->AddLibraryFunction(this, __L("System_PowerOff")                    , Call_SystemPowerOff);
  script->AddLibraryFunction(this, __L("System_Logout")                      , Call_SystemLogout);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPT_LIB_SYSTEM::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LIB_SYSTEM::Clean()
{

}


/*--------------------------------------------------------------------------------------------------------------------*/
/* Library Functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void Call_SystemReboot(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
* @brief      all_SystemReboot
* @ingroup    SCRIPT
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  library : 
* @param[in]  script : 
* @param[in]  params : 
* @param[in]  returnvalue : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void Call_SystemReboot(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
{
  if(!library)      return;
  if(!script)       return;
  if(!params)       return;
  if(!returnvalue)  return;

  returnvalue->Set();

  (*returnvalue) = GEN_XSYSTEM.ShutDown(XSYSTEM_CHANGESTATUSTYPE_REBOOT);
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void Call_SystemPowerOff(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
* @brief      all_SystemPowerOff
* @ingroup    SCRIPT
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  library : 
* @param[in]  script : 
* @param[in]  params : 
* @param[in]  returnvalue : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void Call_SystemPowerOff(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
{
  if(!library)      return;
  if(!script)       return;
  if(!params)       return;
  if(!returnvalue)  return;

  returnvalue->Set();
  
  (*returnvalue) = GEN_XSYSTEM.ShutDown(XSYSTEM_CHANGESTATUSTYPE_POWEROFF);
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void Call_SystemLogout(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
* @brief      all_SystemLogout
* @ingroup    SCRIPT
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  library : 
* @param[in]  script : 
* @param[in]  params : 
* @param[in]  returnvalue : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void Call_SystemLogout(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
{
  if(!library)      return;
  if(!script)       return;
  if(!params)       return;
  if(!returnvalue)  return;

  returnvalue->Set();
  
  (*returnvalue) = GEN_XSYSTEM.ShutDown(XSYSTEM_CHANGESTATUSTYPE_SESSION_LOGOFF);
}




