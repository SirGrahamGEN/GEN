/**-------------------------------------------------------------------------------------------------------------------
*
* @file       Script_Javascript.cpp
*
* @class      SCRIPT_JAVASCRIPT
* @brief      Script Javascript interpreter class
* @ingroup    SCRIPT
*
* @copyright  GEN Group. All right reserved.
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

#include "math.h"

#include "XString.h"

#include "Script_XEvent.h"
#include "Script_Lib.h"

#include "Script_Javascript.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_JAVASCRIPT::SCRIPT_JAVASCRIPT()
* @brief      Constructor
* @ingroup    SCRIPT
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
SCRIPT_JAVASCRIPT::SCRIPT_JAVASCRIPT()
{
  Clean();

  //context = duk_create_heap(NULL, NULL, NULL, (void*)this, SCRIPT_JAVASCRIPT::FatalErrorHandler);
  context = duk_create_heap(NULL, NULL, NULL, (void*)this, NULL);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_JAVASCRIPT::~SCRIPT_JAVASCRIPT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    SCRIPT
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
SCRIPT_JAVASCRIPT::~SCRIPT_JAVASCRIPT()
{
  if(context)
    {
      //duk_pop(context);
      duk_destroy_heap(context);
    }

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_JAVASCRIPT::Load(XPATH& xpath)
* @brief      Load
* @ingroup    SCRIPT
*
* @param[in]  xpath :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_JAVASCRIPT::Load(XPATH& xpath)
{
  if(!SCRIPT::Load(xpath)) return false;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_G_ERRORCODE SCRIPT_JAVASCRIPT::Run(int* returnval)
* @brief      Run
* @ingroup    SCRIPT
*
* @param[in]  returnval :
*
* @return     SCRIPT_G_ERRORCODE :
*
*---------------------------------------------------------------------------------------------------------------------*/
int SCRIPT_JAVASCRIPT::Run(int* returnval)
{
  errorcode    = SCRIPT_ERRORCODE_NONE;
  iscancelexec = false;

  XSTRING _script = script;

  if(HaveMainFunction())
    {
      XSTRING mainfunctionname = SCRIPT_JAVASCRIPT_MAINFUNCTIONNAME;
      _script.AddFormat(__L("\n%s()\n"), mainfunctionname.Get());
    }

  XSTRING_CREATEOEM(_script, charscript);
  duk_int_t error =  duk_peval_string(context, charscript);
  if(error) HaveError(DUK_ERR_ERROR);
  XSTRING_DELETEOEM(_script, charscript)

  if(returnval) (*returnval) =  duk_require_int(context, 0);

  duk_pop(context);


  /*
  XSTRING _script;
  _script = script;

  if(HaveMainFunction())
    {
      XSTRING mainfunctionname = SCRIPT_JAVASCRIPT_MAINFUNCTIONNAME;
      _script.AddFormat(__L("\n%s()\n"), mainfunctionname.Get());
    }

  XSTRING_CREATEOEM(_script, charscript);
  if(duk_pcompile_string(context, 0, charscript) != 0)
    {
      HaveError(DUK_ERR_ERROR);
    }
   else
    {
      if(duk_pcall(context, 0) == DUK_EXEC_ERROR) HaveError(DUK_ERR_ERROR);
    }

  duk_pop(context);
  XSTRING_DELETEOEM(_script, charscript)
  */


  /* test 2
  for(XDWORD c=0; c<scriptlines.GetSize(); c++)
    {
      XSTRING line = scriptlines.Get(c)->Get();

      if(line.IsEmpty()) line = __L("//");

      XSTRING_CREATEOEM(line, charscript);
      duk_push_string(context, charscript);
      XSTRING_DELETEOEM(line, charscript)
    }

  if(HaveMainFunction())
    {
      XSTRING mainfunctionnameliteral;
      XSTRING mainfunctionname;

      mainfunctionnameliteral = SCRIPT_JAVASCRIPT_MAINFUNCTIONNAME;
      mainfunctionname.Format(__L("%s();"), mainfunctionnameliteral.Get());

      XSTRING_CREATEOEM(mainfunctionname, charscript);
      duk_push_string(context, charscript);
      XSTRING_DELETEOEM(mainfunctionname, charscript)
    }

  if(duk_pcompile(context, DUK_COMPILE_EVAL) != 0)
    {
      HaveError(DUK_ERR_ERROR);
    }
   else
    {
      duk_call(context, 0);
    }

  duk_pop(context);
 */


  return errorcode;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_JAVASCRIPT::AddLibraryFunction(SCRIPT_LIB* library, XCHAR* name, SCRFUNCIONLIBRARY ptrfunction)
* @brief      AddLibraryFunction
* @ingroup    SCRIPT
*
* @param[in]  library :
* @param[in]  name :
* @param[in]  ptrfunction :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_JAVASCRIPT::AddLibraryFunction(SCRIPT_LIB* library, XCHAR* name, SCRFUNCIONLIBRARY ptrfunction)
{
  XSTRING namefunction;
  XSTRING ptrfunctionstr;

  namefunction = name;

  XSTRING_CREATEOEM(namefunction, charname)

  duk_push_c_function(context, SCRIPT_JAVASCRIPT::LibraryCallBack, DUK_VARARGS);

  duk_push_pointer(context, (void *)ptrfunction);
  duk_put_prop_string(context, -2, "\xFF""_ptr");
  duk_put_global_string(context, charname);

  XSTRING_DELETEOEM(namefunction, charname)

  return SCRIPT::AddLibraryFunction(library, name, ptrfunction);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_JAVASCRIPT::HaveError(SCRIPT_G_ERRORCODE errorcode)
* @brief      HaveError
* @ingroup    SCRIPT
*
* @param[in]  errorcode :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_JAVASCRIPT::HaveError(int _errorcode)
{
  XSTRING   currenttoken;
  XPATH     namefile;
  int       errorcode    = _errorcode;
  XSTRING   errorstring;
  XSTRING   errorline;
  int       nline        = 0;

  currenttoken = duk_safe_to_string(context, -1);

  if(currenttoken.Find(__L("EvalError")      , false) != XSTRING_NOTFOUND) errorcode = SCRIPT_JAVASCRIPT_ERRORCODE_EVAL_ERROR;
  if(currenttoken.Find(__L("RangeError")     , false) != XSTRING_NOTFOUND) errorcode = SCRIPT_JAVASCRIPT_ERRORCODE_RANGE_ERROR;
  if(currenttoken.Find(__L("ReferenceError") , false) != XSTRING_NOTFOUND) errorcode = SCRIPT_JAVASCRIPT_ERRORCODE_REFERENCE_ERROR;
  if(currenttoken.Find(__L("SyntaxError")    , false) != XSTRING_NOTFOUND) errorcode = SCRIPT_JAVASCRIPT_ERRORCODE_SYNTAX_ERROR;
  if(currenttoken.Find(__L("TypeError")      , false) != XSTRING_NOTFOUND) errorcode = SCRIPT_JAVASCRIPT_ERRORCODE_TYPE_ERROR;
  if(currenttoken.Find(__L("URIError")       , false) != XSTRING_NOTFOUND) errorcode = SCRIPT_JAVASCRIPT_ERRORCODE_URI_ERROR;

  namefile.Set(namescript);
  namefile.SetOnlyNamefileExt();

  SCRIPT_XEVENT xevent(this, SCRIPT_XEVENT_TYPE_ERROR);

  xevent.SetError(errorcode);
  xevent.GetErrorText()->Set(currenttoken);
  xevent.GetCurrentToken()->Set(currenttoken);
  xevent.SetNLine(nline);

  XTRACE_PRINTCOLOR(4, __L("Script [%s] ERROR %d:\"%s\"") , namefile.Get(), errorcode, currenttoken.Get());

  PostEvent(&xevent);

  this->errorcode  = errorcode;
  iscancelexec     = true;


  return (errorcode == SCRIPT_ERRORCODE_NONE)?false:true;

}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_JAVASCRIPT::HaveMainFunction()
* @brief      HaveMainFunction
* @ingroup    SCRIPT
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_JAVASCRIPT::HaveMainFunction()
{
  XSTRING mainfunctionname;
  XSTRING script;
  int     start = 0;
  int     end   = 0;
  XSTRING line;

  script = GetScript()->Get();
  if(script.IsEmpty()) return false;

  mainfunctionname = SCRIPT_JAVASCRIPT_MAINFUNCTIONNAME;

  int index = GetScript()->Find(mainfunctionname, false);
  if(index == XSTRING_NOTFOUND) return false;

  for(start=index; start>0; start--)
    {
      if((script.Get()[start] == __C('\r')) || (script.Get()[start] == __C('\n')))
        {
          break;
        }
    }

  for(end=index; end<(int)script.GetSize() ; end++)
    {
      if(script.Get()[end] == __C(')'))
        {
          break;
        }
    }

  script.Copy(start, end+1, line);

  line.DeleteCharacter(__C('\n'));
  line.DeleteCharacter(__C('\r'));
  line.DeleteCharacter(__C(' '));

  XSTRING searchmask;

  searchmask.Format(__L("function%s()"), mainfunctionname.Get());

  if(!line.Compare(searchmask)) return true;

  return false;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         duk_ret_t SCRIPT_JAVASCRIPT::LibraryCallBack(duk_context* context)
* @brief      LibraryCallBack
* @ingroup    SCRIPT
*
* @param[in]  context :
*
* @return     duk_ret_t :
*
*---------------------------------------------------------------------------------------------------------------------*/
duk_ret_t SCRIPT_JAVASCRIPT::LibraryCallBack(duk_context* context)
{
  XVECTOR<XVARIANT*>    params;
  XVARIANT              returnvalue;
  int                   nreturnvalues = 0;
  SCRIPT_JAVASCRIPT*    script        = NULL;
  duk_memory_functions  memoryfuncs;
  void*                 funcptr       = NULL;

  duk_get_memory_functions(context, &memoryfuncs);

  script = (SCRIPT_JAVASCRIPT*)memoryfuncs.udata;
  if(!script) return 0;

  duk_push_current_function(context);
  duk_get_prop_string(context, -1, "\xFF""_ptr");
  funcptr = (void*)duk_get_pointer(context, -1);
  if(!funcptr) return 0;

  SCRIPT_LIBFUNCTION* libfunction = script->GetLibraryFunction(funcptr);
  if(!libfunction) return 0;
  if(!libfunction->GetFunctionLibrary()) return 0;

  duk_pop_2(context);

  duk_idx_t          nargs;
  duk_idx_t          c;

  nargs = duk_get_top(context);

  for(c = 0; c < nargs; c++)
    {
      XVARIANT* variant = new XVARIANT();
      if(variant)
        {
          switch((int)duk_get_type(context, c))
            {
              case DUK_TYPE_NONE           :  // no value, e.g. invalid index
                                              break;

              case DUK_TYPE_UNDEFINED      :  // ECMAScript undefined
                                              break;

              case DUK_TYPE_NULL           :  // ECMAScript null
                                              //(*variant) = NULL;
                                              break;

              case DUK_TYPE_BOOLEAN        :  // ECMAScript boolean: 0 or 1
                                              (*variant) = (duk_require_boolean(context, c)?true:false);
                                              break;

              case DUK_TYPE_NUMBER         :  // ECMAScript number: double
                                              (*variant) = (double)duk_require_number(context, c);
                                              break;

              case DUK_TYPE_STRING         :  // ECMAScript string: CESU-8 / extended UTF-8 encoded
                                              (*variant) = (char*)duk_require_string(context, c);
                                              break;

              case DUK_TYPE_OBJECT         :  // ECMAScript object: includes objects, arrays, functions, threads
                                              break;

              case DUK_TYPE_BUFFER         :  // fixed or dynamic, garbage collected byte buffer
                                              break;

              case DUK_TYPE_POINTER        :  // raw void pointer
                                              break;

              case DUK_TYPE_LIGHTFUNC      :  // lightweight function pointer
                                              break;
            }

           params.Add(variant);
        }
    }

  libfunction->GetFunctionLibrary()(libfunction->GetLibrary(), script, &params, &returnvalue);

  params.DeleteContents();
  params.DeleteAll();


  switch(returnvalue.GetType())
    {
      case XVARIANT_TYPE_NULL          :                                                                    break;
      case XVARIANT_TYPE_SERIALIZABLE  :                                                                    break;
      case XVARIANT_TYPE_INTEGER       :  duk_push_int(context, (int)(returnvalue));     nreturnvalues++;   break;
      case XVARIANT_TYPE_CHAR          :  duk_push_int(context, (int)(returnvalue));     nreturnvalues++;   break;
      case XVARIANT_TYPE_XCHAR         :                                                                    break;
      case XVARIANT_TYPE_FLOAT         :  { XDWORD data = returnvalue;

                                            duk_push_int(context, data);
                                            nreturnvalues++;
                                          }
                                          break;

      case XVARIANT_TYPE_STRING        : { XSTRING stringreturnvalue;

                                           stringreturnvalue = returnvalue;

                                           XSTRING_CREATEOEM(stringreturnvalue, charstr)
                                           duk_push_string(context, charstr);
                                           XSTRING_DELETEOEM(stringreturnvalue, charstr);

                                           nreturnvalues++;
                                         }
                                         break;

      case XVARIANT_TYPE_DATE          :                                                                   break;
      case XVARIANT_TYPE_TIME          :                                                                   break;
      case XVARIANT_TYPE_DATETIME      :                                                                   break;
    }


  // Let Lua know how many return values we've passed
  return nreturnvalues;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPT_JAVASCRIPT::FatalErrorHandler(void* udata, const char* msg)
* @brief      JS_FatalErrorHandler
* @ingroup    SCRIPT
*
* @param[in]  udata :
* @param[in]  msg :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_JAVASCRIPT::FatalErrorHandler(void* udata, const char* msg)
{
  SCRIPT_JAVASCRIPT* script  = (SCRIPT_JAVASCRIPT*)udata;
  if(!script) return;

  XSTRING message;

  message = msg;

  abort();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPT_JAVASCRIPT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    SCRIPT
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_JAVASCRIPT::Clean()
{
  context = NULL;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         double __builtin_inf (void)
* @brief      _builtin_inf
* @ingroup    SCRIPT
*
* @param[in]  void :
*
* @return     double :
*
*---------------------------------------------------------------------------------------------------------------------*/
double __builtin_inf (void)
{
  return (double)0xFFFFFFFFFFFFFFFF;
}


