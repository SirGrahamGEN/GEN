/**-------------------------------------------------------------------------------------------------------------------
*
* @file       Script_LibFunction.cpp
*
* @class      SCRIPT_LIBFUNCTION
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "Script_LibFunction.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_LIBFUNCTION::SCRIPT_LIBFUNCTION(SCRIPT_LIB* library, XCHAR* name, SCRFUNCIONLIBRARY functionlibrary)
* @brief      Constructor
* @ingroup    SCRIPT
*
* @param[in]  SCRIPT_LIB* :
* @param[in]   XCHAR* name :
* @param[in]   SCRFUNCIONLIBRARY functionlibrary :
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LIBFUNCTION::SCRIPT_LIBFUNCTION(SCRIPT_LIB* library, XCHAR* name, SCRFUNCIONLIBRARY functionlibrary)
{
  Clean();

  this->library         = library;
  this->name            = name;
  this->functionlibrary = functionlibrary;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_LIBFUNCTION::SCRIPT_LIBFUNCTION(SCRIPT_LIB* library, XSTRING& name, SCRFUNCIONLIBRARY functionlibrary)
* @brief      Constructor
* @ingroup    SCRIPT
*
* @param[in]  SCRIPT_LIB* :
* @param[in]   XSTRING& name :
* @param[in]   SCRFUNCIONLIBRARY functionlibrary :
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LIBFUNCTION::SCRIPT_LIBFUNCTION(SCRIPT_LIB* library, XSTRING& name, SCRFUNCIONLIBRARY functionlibrary)
{
  Clean();

  this->library         = library;
  this->name            = name;
  this->functionlibrary = functionlibrary;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_LIBFUNCTION::~SCRIPT_LIBFUNCTION()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    SCRIPT
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LIBFUNCTION::~SCRIPT_LIBFUNCTION()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_LIB* SCRIPT_LIBFUNCTION::GetLibrary()
* @brief      GetLibrary
* @ingroup    SCRIPT
*
* @return     SCRIPT_LIB* :
*
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LIB* SCRIPT_LIBFUNCTION::GetLibrary()
{
  return library;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_LIBFUNCTION::SetLibrary(SCRIPT_LIB* library)
* @brief      SetLibrary
* @ingroup    SCRIPT
*
* @param[in]  library :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LIBFUNCTION::SetLibrary(SCRIPT_LIB* library)
{
  if(!library) return false;
  this->library = library;
  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* SCRIPT_LIBFUNCTION::GetName()
* @brief      GetName
* @ingroup    SCRIPT
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* SCRIPT_LIBFUNCTION::GetName()
{
  return &name;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRFUNCIONLIBRARY SCRIPT_LIBFUNCTION::GetFunctionLibrary()
* @brief      GetFunctionLibrary
* @ingroup    SCRIPT
*
* @return     SCRFUNCIONLIBRARY :
*
* --------------------------------------------------------------------------------------------------------------------*/
SCRFUNCIONLIBRARY SCRIPT_LIBFUNCTION::GetFunctionLibrary()
{
  return functionlibrary;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_LIBFUNCTION::SetFunctionLibrary(SCRFUNCIONLIBRARY functionlibrary)
* @brief      SetFunctionLibrary
* @ingroup    SCRIPT
*
* @param[in]  functionlibrary :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LIBFUNCTION::SetFunctionLibrary(SCRFUNCIONLIBRARY functionlibrary)
{
  this->functionlibrary = functionlibrary;
  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPT_LIBFUNCTION::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    SCRIPT
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LIBFUNCTION::Clean()
{
  name.Empty();

  functionlibrary = NULL;
}



