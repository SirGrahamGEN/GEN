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

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "Script_Lib_String.h"

#include "Script.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE


#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


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
  script->AddLibraryFunction(this, __L("ReplaceString")               , Call_ReplaceString);
  script->AddLibraryFunction(this, __L("SPrintf")                     , Call_SPrintf);

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


#pragma endregion


/*---- LIBRARY FUNCTIONS ---------------------------------------------------------------------------------------------*/
#pragma region LIBRARY_FUNCTIONS


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


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void Call_ReplaceString(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
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
void Call_ReplaceString(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
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

  XSTRING* string     = (XSTRING*)params->Get(0)->GetData();
  XSTRING* tofind     = (XSTRING*)params->Get(1)->GetData();
  XSTRING* toreplace  = (XSTRING*)params->Get(2)->GetData();

  if(string && tofind && toreplace) 
    {
      if(string->ReplaceFirst(tofind->Get(), toreplace->Get()) != XSTRING_NOTFOUND)
        {
          (*returnvalue) = (*string);
        }
    }   
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void Call_SPrintf(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
* @brief      Call_SPrintf
* @ingroup    SCRIPT
*
* @param[in]  library :
* @param[in]  script :
* @param[in]  params :
* @param[in]  returnvalue :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void Call_SPrintf(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
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

  XVARIANT  variantout = (*params->Get(0));
  XCHAR*    out = variantout;
  XSTRING  _out = out;

  XVARIANT  variantmask = (*params->Get(1));
  XCHAR*    mask = variantmask;

  XSTRING outstring;
  XSTRING string;

  int paramindex = 2;
  int c          = 0;

  while(mask[c])
    {
      switch(mask[c])
        {
          case '%' : {
                        #define MAXTEMPOSTR 32

                        XCHAR param[MAXTEMPOSTR];

                        int  nparam = 1;
                        bool end    = false;

                        memset(param,0,MAXTEMPOSTR*sizeof(XCHAR));
                        param[0] = '%';

                        c++;

                        switch(mask[c])
                              {
                                case __C('c')   :
                                case __C('C')   :
                                case __C('d')   :
                                case __C('i')   :
                                case __C('o')   :
                                case __C('u')   :
                                case __C('x')   :
                                case __C('X')   : { int value = 0;
                                                    library->GetParamConverted(params->Get(paramindex), value);
                                                    string.Format(param, value);
                                                    paramindex++;
                                                    end  = true;
                                                  }
                                                  break;

                                case __C('f')   : { float value = 0;
                                                    library->GetParamConverted(params->Get(paramindex), value);
                                                    string.Format(param, value);
                                                    paramindex++;
                                                    end  = true;
                                                  }
                                                  break;

                                case __C('g')   :
                                case __C('G')   :

                                case __C('e')   :
                                case __C('E')   :

                                case __C('n')   :
                                case __C('p')   : end = true;
                                                  break;

                                case __C('s')   :
                                case __C('S')   : { XVARIANT variantparam = (*params->Get(paramindex));
                                                    paramindex++;
                                                    string.Format(param,(XCHAR*)variantparam);
                                                    end = true;
                                                  }
                                                  break;

                                case __C('%')   : string = __L("%");
                                                  end = true;
                                                  break;

                                case __C('\0')  : end = true;
                                                  break;

                                      default   : break;
                              }

                      }
                      break;

            default : string.Set(mask[c]);
                      c++;
                      break;
        }

      outstring += string;
    }

  _out = outstring;
}


#pragma endregion

