/**-------------------------------------------------------------------------------------------------------------------
*
* @file       Script_Lib_String.cpp
*
* @class      SCRIPT_LIB_STRING
* @brief      Script Library String
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

#include "Script.h"

#include "Script_Lib_String.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_LIB_STRING::SCRIPT_LIB_STRING()
* @brief      Constructor
* @ingroup    SCRIPT
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LIB_STRING::SCRIPT_LIB_STRING() : SCRIPT_LIB(SCRIPT_LIB_NAME_STRING)
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_LIB_STRING::~SCRIPT_LIB_STRING()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    SCRIPT
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LIB_STRING::~SCRIPT_LIB_STRING()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_LIB_STRING::AddLibraryFunctions(SCRIPT* script)
* @brief      AddLibraryFunctions
* @ingroup    SCRIPT
*
* @param[in]  script :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LIB_STRING::AddLibraryFunctions(SCRIPT* script)
{
  if(!script) return false;

  this->script = script;

  script->AddLibraryFunction(this, __L("AddString")                   , Call_AddString);
  script->AddLibraryFunction(this, __L("FindString")                  , Call_FindString);
  script->AddLibraryFunction(this, __L("CompareString")               , Call_CompareString);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPT_LIB_STRING::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    SCRIPT
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LIB_STRING::Clean()
{

}


/*--------------------------------------------------------------------------------------------------------------------*/
/* Library Functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void Call_AddString(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
* @brief      Call_AddString
* @ingroup    SCRIPT
*
* @param[in]  library : 
* @param[in]  script : 
* @param[in]  params : 
* @param[in]  returnvalue : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void Call_AddString(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
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

  XSTRING* string1 = (XSTRING*)params->Get(0)->GetData();
  XSTRING* string2 = (XSTRING*)params->Get(1)->GetData();

  if(string1 && string2) (*string1)+=(*string2);

  (*returnvalue) = (*string1);
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void Call_FindString(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
* @brief      Call_FindString
* @ingroup    SCRIPT
*
* @param[in]  library : 
* @param[in]  script : 
* @param[in]  params : 
* @param[in]  returnvalue : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void Call_FindString(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
{
  if(!library)      return;
  if(!script)       return;
  if(!params)       return;
  if(!returnvalue)  return;

  returnvalue->Set();

  if(params->GetSize() < 3)
    {
      script->HaveError(SCRIPT_ERRORCODE_INSUF_PARAMS);
      return;
    }

  XSTRING* string1    = (XSTRING*)params->Get(0)->GetData();
  XSTRING* string2    = (XSTRING*)params->Get(1)->GetData();
  bool     ignorecase = (bool)params->Get(2)->GetData(); 

  if(string1 && string2) 
    {
      (*returnvalue) = string1->Find(string2->Get(), ignorecase);
    }
   else 
    { 
      (*returnvalue) = -1;
    }
}




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void Call_CompareString(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
* @brief      all_CompareString
* @ingroup    SCRIPT
*
* @param[in]  library : 
* @param[in]  script : 
* @param[in]  params : 
* @param[in]  returnvalue : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void Call_CompareString(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
{
  if(!library)      return;
  if(!script)       return;
  if(!params)       return;
  if(!returnvalue)  return;

  returnvalue->Set();

  if(params->GetSize() < 3)
    {
      script->HaveError(SCRIPT_ERRORCODE_INSUF_PARAMS);
      return;
    }

  XSTRING* string1    = (XSTRING*)params->Get(0)->GetData();
  XSTRING* string2    = (XSTRING*)params->Get(1)->GetData();
  bool     ignorecase = (bool)params->Get(2)->GetData(); 

  if(string1 && string2) 
    {
      (*returnvalue) = (bool)(string1->Compare(string2->Get(), ignorecase)==0?true:false);
    }
   else 
    { 
      (*returnvalue) = false;
    }

}