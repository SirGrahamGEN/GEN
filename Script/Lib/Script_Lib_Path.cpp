/**-------------------------------------------------------------------------------------------------------------------
*
* @file       Script_Lib_Path.cpp
*
* @class      SCRIPT_LIB_PATH
* @brief      Script Library Path
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

#include "Script.h"

#include "Script_Lib_Path.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_LIB_PATH::SCRIPT_LIB_PATH()
* @brief      Constructor
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LIB_PATH::SCRIPT_LIB_PATH() : SCRIPT_LIB(SCRIPT_LIB_NAME_PATH)
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_LIB_PATH::~SCRIPT_LIB_PATH()
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
SCRIPT_LIB_PATH::~SCRIPT_LIB_PATH()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_LIB_PATH::AddLibraryFunctions(SCRIPT* script)
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
bool SCRIPT_LIB_PATH::AddLibraryFunctions(SCRIPT* script)
{
  if(!script) return false;

  this->script = script;

  script->AddLibraryFunction(this, __L("GetPathScript")            , Call_GetPathScript);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPT_LIB_PATH::Clean()
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
void SCRIPT_LIB_PATH::Clean()
{

}


/*--------------------------------------------------------------------------------------------------------------------*/
/* Library Functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void Call_GetPathScript(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
* @brief      all_GetPathScript
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
*---------------------------------------------------------------------------------------------------------------------*/
void Call_GetPathScript(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
{
  if(!library)      return;
  if(!script)       return;
  if(!params)       return;
  if(!returnvalue)  return;

  returnvalue->Set();

  if(!params->GetSize())
    {
      script->HaveError(SCRIPT_ERRORCODE_INSUF_PARAMS);
      return;
    }

  XVARIANT variantmask = (*params->Get(0));
  variantmask  = script->GetPath()->Get();
}


