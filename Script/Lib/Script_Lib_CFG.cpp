/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       Script_Lib_CFG.cpp
* 
* @class      SCRIPT_LIB_CFG
* @brief      Script Library CFG
* @ingroup    SCRIPT
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

#include "Script_Lib_CFG.h"

#include "XFileCFG.h"

#include "Script.h"

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
* @fn         SCRIPT_LIB_CFG::SCRIPT_LIB_CFG()
* @brief      Constructor of class
* @ingroup    SCRIPT
* 
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LIB_CFG::SCRIPT_LIB_CFG() : SCRIPT_LIB(SCRIPT_LIB_NAME_CFG)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_LIB_CFG::~SCRIPT_LIB_CFG()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    SCRIPT
*
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LIB_CFG::~SCRIPT_LIB_CFG()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_LIB_CFG::AddLibraryFunctions(SCRIPT* script)
* @brief      Add library functions
* @ingroup    SCRIPT
*
* @param[in]  script :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LIB_CFG::AddLibraryFunctions(SCRIPT* script)
{
  if(!script) return false;

  this->script = script;

  script->AddLibraryFunction(this, __L("GetFileCFGValue")            , Call_GetFileCFGValue);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILECFG* SCRIPT_LIB_CFG::GetXFileCFG()
* @brief      Get X file CFG
* @ingroup    SCRIPT
* 
* @return     XFILECFG* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XFILECFG* SCRIPT_LIB_CFG::GetXFileCFG()
{
  return xfileCFG;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SCRIPT_LIB_CFG::SetXFileCFG(XFILECFG* xfileCFG)
* @brief      Set X file CFG
* @ingroup    SCRIPT
* 
* @param[in]  xfileCFG : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LIB_CFG::SetXFileCFG(XFILECFG* xfileCFG)
{
  this->xfileCFG = xfileCFG;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPT_LIB_CFG::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    SCRIPT
*
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LIB_CFG::Clean()
{
  xfileCFG = NULL;
}


#pragma endregion


/*---- LIBRARY FUNCTIONS ---------------------------------------------------------------------------------------------*/
#pragma region LIBRARY_FUNCTIONS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void Call_GetFileCFGValue(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
* @brief      Call_GetFileCFGValue
* @ingroup    SCRIPT
* 
* @param[in]  library : 
* @param[in]  script : 
* @param[in]  params : 
* @param[in]  returnvalue : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void Call_GetFileCFGValue(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
{
  if(!library)      return;
  if(!script)       return;
  if(!params)       return;
  if(!returnvalue)  return;

  returnvalue->Set();

  if(params->GetSize() < 2)
    {
      script->HaveError(SCRIPT_ERRORCODE_INSUF_PARAMS);
      return;
    }
  
  XSTRING          datakey;
  SCRIPT_LIB_CFG*  libraryCFG = (SCRIPT_LIB_CFG*)library;

  if(libraryCFG->GetXFileCFG())
    {
      XSTRING* param1 = (XSTRING*)params->Get(0)->GetData();
      XSTRING* param2 = (XSTRING*)params->Get(1)->GetData();

      XVARIANT* variable = libraryCFG->GetXFileCFG()->GetValue(param1->Get(), param2->Get());
      if(variable) 
        {
          variable->ToString(datakey);        
          delete variable;
        }

    }

  (*returnvalue) = datakey.Get();
}


#pragma endregion
