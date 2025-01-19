/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       Script_Lib_Log.cpp
* 
* @class      SCRIPT_LIB_Log
* @brief      Script Library Log
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

#include "Script_Lib_Log.h"

#include "XFactory.h"
#include "XTrace.h"
#include "XLog.h"
#include "XConsole.h"

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
* @fn         SCRIPT_LIB_LOG::SCRIPT_LIB_LOG()
* @brief      Constructor of class
* @ingroup    SCRIPT
*
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LIB_LOG::SCRIPT_LIB_LOG() : SCRIPT_LIB(SCRIPT_LIB_NAME_LOG)
{
  Clean();  
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_LIB_LOG::~SCRIPT_LIB_LOG()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    SCRIPT
*
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LIB_LOG::~SCRIPT_LIB_LOG()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_LIB_LOG::AddLibraryFunctions(SCRIPT* script)
* @brief      Add library functions
* @ingroup    SCRIPT
*
* @param[in]  script :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LIB_LOG::AddLibraryFunctions(SCRIPT* script)
{
  if(!script) return false;

  this->script = script;

  script->AddLibraryFunction(this, __L("Log_Ini")                  , Call_Log_Ini);
  script->AddLibraryFunction(this, __L("Log_CFG_SetLimit")         , Call_Log_CFG_SetLimit);
  script->AddLibraryFunction(this, __L("Log_CFG_SetFilters")       , Call_Log_CFG_SetFilters);
  script->AddLibraryFunction(this, __L("Log_CFG_SetBackup")        , Call_Log_CFG_SetBackup);
  script->AddLibraryFunction(this, __L("Log_AddEntry")             , Call_Log_AddEntry);
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XLOGBASE* SCRIPT_LIB_LOG::GetLog()
* @brief      Get log
* @ingroup    SCRIPT
* 
* @return     XLOGBASE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XLOGBASE* SCRIPT_LIB_LOG::GetLog()
{
  return &log;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPT_LIB_LOG::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    SCRIPT
*
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LIB_LOG::Clean()
{
  
}


#pragma endregion


/*---- LIBRARY FUNCTIONS ---------------------------------------------------------------------------------------------*/
#pragma region LIBRARY_FUNCTIONS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void Call_Log_Ini(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
* @brief      Call_Log_Ini
* @ingroup    SCRIPT
* 
* @param[in]  library : 
* @param[in]  script : 
* @param[in]  params : 
* @param[in]  returnvalue : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void Call_Log_Ini(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
{
  if(!library)      return;
  if(!script)       return;
  if(!params)       return;
  if(!returnvalue)  return;

  returnvalue->Set();

  if(params->GetSize()<2)
    {
      script->HaveError(SCRIPT_ERRORCODE_INSUF_PARAMS);
      return;
    }

  SCRIPT_LIB_LOG* liblog = (SCRIPT_LIB_LOG*)library;
  if(!liblog->GetLog())
    {
      return;   
    }

  XSTRING  path;
  XSTRING  nameapp;
  bool     status  = false;

  library->GetParamConverted(params->Get(0), path);
  library->GetParamConverted(params->Get(1), nameapp);

  status = liblog->GetLog()->Ini(path.Get(), nameapp.Get());

  (*returnvalue) = status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void Call_Log_CFG_SetLimit(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
* @brief      all_Log_CFG_SetLimit
* @ingroup    SCRIPT
* 
* @param[in]  library : 
* @param[in]  script : 
* @param[in]  params : 
* @param[in]  returnvalue : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void Call_Log_CFG_SetLimit(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
{
  if(!library)      return;
  if(!script)       return;
  if(!params)       return;
  if(!returnvalue)  return;

  returnvalue->Set();

  if(params->GetSize()<2)
    {
      script->HaveError(SCRIPT_ERRORCODE_INSUF_PARAMS);
      return;
    }

  SCRIPT_LIB_LOG* liblog = (SCRIPT_LIB_LOG*)library;
  if(!liblog->GetLog())
    {
      return;   
    }

  int     limit             = 0;
  int     reductionpercent  = 0;
  bool    status            = false; 

  library->GetParamConverted(params->Get(0), limit);
  library->GetParamConverted(params->Get(1), reductionpercent);

  status = liblog->GetLog()->SetLimit(XLOGTYPELIMIT_SIZE, limit, reductionpercent);
  
  (*returnvalue) = status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void Call_Log_CFG_SetFilters(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
* @brief      all_Log_CFG_SetFilters
* @ingroup    SCRIPT
* 
* @param[in]  library : 
* @param[in]  script : 
* @param[in]  params : 
* @param[in]  returnvalue : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void Call_Log_CFG_SetFilters(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
{
  if(!library)      return;
  if(!script)       return;
  if(!params)       return;
  if(!returnvalue)  return;

  returnvalue->Set();

  if(params->GetSize()<2)
    {
      script->HaveError(SCRIPT_ERRORCODE_INSUF_PARAMS);
      return;
    }

  SCRIPT_LIB_LOG* liblog = (SCRIPT_LIB_LOG*)library;
  if(!liblog->GetLog())
    {
      return;   
    }

  XSTRING sectionsID;
  int     levelmask;
  bool    status            = false; 

  library->GetParamConverted(params->Get(0), sectionsID);
  library->GetParamConverted(params->Get(1), levelmask);

  status = liblog->GetLog()->SetFilters(sectionsID.Get(), levelmask);
  
  (*returnvalue) = status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void Call_Log_CFG_SetBackup(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
* @brief      all_Log_CFG_SetBackup
* @ingroup    SCRIPT
* 
* @param[in]  library : 
* @param[in]  script : 
* @param[in]  params : 
* @param[in]  returnvalue : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void Call_Log_CFG_SetBackup(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
{
  if(!library)      return;
  if(!script)       return;
  if(!params)       return;
  if(!returnvalue)  return;

  returnvalue->Set();

  if(params->GetSize()<3)
    {
      script->HaveError(SCRIPT_ERRORCODE_INSUF_PARAMS);
      return;
    }

  SCRIPT_LIB_LOG* liblog = (SCRIPT_LIB_LOG*)library;
  if(!liblog->GetLog())
    {
      return;   
    }

  bool activebackup  = false;
  int  maxfiles      = 0; 
  bool iscompress    = false;
  bool status        = false;

  library->GetParamConverted(params->Get(0), activebackup);
  library->GetParamConverted(params->Get(1), maxfiles);
  library->GetParamConverted(params->Get(1), iscompress);

  status = liblog->GetLog()->SetBackup(activebackup, maxfiles, iscompress);     
  
  (*returnvalue) = status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void Call_Log_AddEntry(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
* @brief      Call_Log_AddEntry
* @ingroup    SCRIPT
* 
* @param[in]  library : 
* @param[in]  script : 
* @param[in]  params : 
* @param[in]  returnvalue : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void Call_Log_AddEntry(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
{
  if(!library)      return;
  if(!script)       return;
  if(!params)       return;
  if(!returnvalue)  return;

  returnvalue->Set();

  if(params->GetSize()<3)
    {
      script->HaveError(SCRIPT_ERRORCODE_INSUF_PARAMS);
      return;
    }

  SCRIPT_LIB_LOG* liblog = (SCRIPT_LIB_LOG*)library;
  if(!liblog->GetLog())
    {
      return;   
    }

  int       level   = 0;
  XVARIANT* variant = params->Get(1);
  XSTRING   section = (*variant);  
    
  library->GetParamConverted(params->Get(0), level);
  
  XVARIANT  variantmask = (*params->Get(2));
  XCHAR*    mask = variantmask;
  XSTRING   outstring;
  XSTRING   string;

  int paramindex = 3;
  int c          = 0;

  if(!mask) return;

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

                        do{ string.Empty();

                            param[nparam] = mask[c];
                            nparam++;

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

                                case __C('f')   : { float value = 0.0f;
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

                            c++;

                          } while(!end);
                      }
                      break;

            default : string.Set(mask[c]);
                      c++;
                      break;
        }

      outstring += string;
    }

  if(liblog->GetLog())
    {
      liblog->GetLog()->AddEntry((XLOGLEVEL)level, section.Get(), false, outstring.Get());
    }
   else  
    {
      GEN_XLOG.AddEntry((XLOGLEVEL)level, section.Get(), false, outstring.Get());
    }
}


#pragma endregion
