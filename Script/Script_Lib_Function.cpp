/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       Script_Lib_Function.cpp
* 
* @class      SCRIPT_LIB_FUNCTION
* @brief      Script Library Function class
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

#include "Script_Lib_Function.h"

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
* @fn         SCRIPT_LIB_FUNCTION::SCRIPT_LIB_FUNCTION(SCRIPT_LIB* library, XCHAR* name, SCRFUNCIONLIBRARY functionlibrary)
* @brief      Constructor of class
* @ingroup    SCRIPT
*
* @param[in]  library :
* @param[in]  name :
* @param[in]  functionlibrary :
*
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LIB_FUNCTION::SCRIPT_LIB_FUNCTION(SCRIPT_LIB* library, XCHAR* name, SCRFUNCIONLIBRARY functionlibrary)
{
  Clean();

  this->library         = library;
  this->name            = name;
  this->functionlibrary = functionlibrary;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_LIB_FUNCTION::SCRIPT_LIB_FUNCTION(SCRIPT_LIB* library, XSTRING& name, SCRFUNCIONLIBRARY functionlibrary)
* @brief      Constructor of class
* @ingroup    SCRIPT
*
* @param[in]  library :
* @param[in]  name :
* @param[in]  functionlibrary :
*
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LIB_FUNCTION::SCRIPT_LIB_FUNCTION(SCRIPT_LIB* library, XSTRING& name, SCRFUNCIONLIBRARY functionlibrary)
{
  Clean();

  this->library         = library;
  this->name            = name;
  this->functionlibrary = functionlibrary;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_LIB_FUNCTION::~SCRIPT_LIB_FUNCTION()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    SCRIPT
*
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LIB_FUNCTION::~SCRIPT_LIB_FUNCTION()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_LIB* SCRIPT_LIB_FUNCTION::GetLibrary()
* @brief      Get library
* @ingroup    SCRIPT
*
* @return     SCRIPT_LIB* :
*
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LIB* SCRIPT_LIB_FUNCTION::GetLibrary()
{
  return library;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_LIB_FUNCTION::SetLibrary(SCRIPT_LIB* library)
* @brief      Set library
* @ingroup    SCRIPT
*
* @param[in]  library :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LIB_FUNCTION::SetLibrary(SCRIPT_LIB* library)
{
  if(!library) return false;
  this->library = library;
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* SCRIPT_LIB_FUNCTION::GetName()
* @brief      Get name
* @ingroup    SCRIPT
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* SCRIPT_LIB_FUNCTION::GetName()
{
  return &name;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRFUNCIONLIBRARY SCRIPT_LIB_FUNCTION::GetFunctionLibrary()
* @brief      Get function library
* @ingroup    SCRIPT
*
* @return     SCRFUNCIONLIBRARY :
*
* --------------------------------------------------------------------------------------------------------------------*/
SCRFUNCIONLIBRARY SCRIPT_LIB_FUNCTION::GetFunctionLibrary()
{
  return functionlibrary;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_LIB_FUNCTION::SetFunctionLibrary(SCRFUNCIONLIBRARY functionlibrary)
* @brief      Set function library
* @ingroup    SCRIPT
*
* @param[in]  functionlibrary :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LIB_FUNCTION::SetFunctionLibrary(SCRFUNCIONLIBRARY functionlibrary)
{
  this->functionlibrary = functionlibrary;
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPT_LIB_FUNCTION::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    SCRIPT
*
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LIB_FUNCTION::Clean()
{
  name.Empty();

  functionlibrary = NULL;
}


#pragma endregion
