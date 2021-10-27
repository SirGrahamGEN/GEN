/**-------------------------------------------------------------------------------------------------------------------
*
* @file       Script_Lua.cpp
*
* @class      SCRIPT_LUA
* @brief      Script LUA interpreter class
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

#include "math.h"

#include "Script_XEvent.h"
#include "Script_Lib.h"

#include "Script_Lua.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_LUA::SCRIPT_LUA()
* @brief      Constructor
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LUA::SCRIPT_LUA()
{
  Clean();

  state = luaL_newstate();
  if(state) luaL_openlibs(state);    // Load Lua libraries

  *static_cast<SCRIPT_LUA**>(lua_getextraspace(state)) = this;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_LUA::~SCRIPT_LUA()
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
SCRIPT_LUA::~SCRIPT_LUA()
{
  if(state) lua_close(state);

  Clean();
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_LUA::Load(XPATH& xpath)
* @brief      Load
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  xpath :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LUA::Load(XPATH& xpath)
{
  if(!state) return false;

  if(!SCRIPT::Load(xpath)) return false;

  XSTRING_CREATEOEM(namescript, charnamescript)
  XSTRING_CREATEOEM(script, charscript)

  int status = luaL_loadbuffer(state, charscript, strlen(charscript), charnamescript);

  XSTRING_DELETEOEM(script, charscript)
  XSTRING_DELETEOEM(namescript, charnamescript)

  return (status == LUA_OK )?true:false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_G_ERRORCODE SCRIPT_LUA::Run(int* returnval)
* @brief      Run
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  returnval :
*
* @return     SCRIPT_G_ERRORCODE :
*
*---------------------------------------------------------------------------------------------------------------------*/
int SCRIPT_LUA::Run(int* returnval)
{
  errorcode  = SCRIPT_ERRORCODE_NONE;
  iscancelexec = false;

  int     status = 0;

  if(HaveMainFunction())
    {
      //Exec to ajust the Stack in Lua with Main Function. lua_getglobal don´t work well without this.
      lua_pcall(state, 0, LUA_MULTRET, 0);
    }

  lua_getglobal(state, SCRIPT_LUA_MAINFUNCTIONNAME);

  status = lua_isfunction(state, lua_gettop(state));
  if(status)
    {
      status = lua_pcall(state, 0, 0, 0);
    }
   else
    {
      lua_setglobal(state, SCRIPT_LUA_MAINFUNCTIONNAME);
      status = lua_pcall(state, 0, LUA_MULTRET, 0);
    }


  if(status != LUA_OK)
    {
      switch(status)
        {
          case LUA_YIELD      : errorcode = SCRIPT_LUA_ERRORCODE_YIELD;          break;
          case LUA_ERRRUN     : errorcode = SCRIPT_LUA_ERRORCODE_RUN;            break;
          case LUA_ERRSYNTAX  : errorcode = SCRIPT_LUA_ERRORCODE_SYNTAX;         break;
          case LUA_ERRMEM     : errorcode = SCRIPT_LUA_ERRORCODE_MEM;            break;
          case LUA_ERRGCMM    : errorcode = SCRIPT_LUA_ERRORCODE_GCMM;           break;
          case LUA_ERRERR     : errorcode = SCRIPT_LUA_ERRORCODE_ERRERR;         break;
        }

      HaveError(errorcode);

      return errorcode;
    }

  return errorcode;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_LUA::AddLibraryFunction(SCRIPT_LIB* library, XCHAR* name, SCRFUNCIONLIBRARY ptrfunction)
* @brief      AddLibraryFunction
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  library :
* @param[in]  name :
* @param[in]  ptrfunction :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LUA::AddLibraryFunction(SCRIPT_LIB* library, XCHAR* name, SCRFUNCIONLIBRARY ptrfunction)
{
  XSTRING namefunction;

  namefunction = name;

  XSTRING_CREATEOEM(namefunction, charname)
  lua_register(state, charname, LUA_LibraryCallBack);
  XSTRING_DELETEOEM(namefunction, charname)

  return SCRIPT::AddLibraryFunction(library, name, ptrfunction);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_LUA::HaveError(SCRIPT_G_ERRORCODE errorcode)
* @brief      HaveError
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  errorcode :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LUA::HaveError(int errorcode)
{
  if(errorcode != SCRIPT_ERRORCODE_NONE)
    {
      static XCHAR* errorstr[]= { __L("None")                                             ,
                                  __L("Internal error")                                   ,
                                  __L("Syntax error")                                     ,
                                  __L("Insufficient parameters")                          ,
                                  __L("Thread not yield")                                 ,
                                  __L("runtime error")                                    ,
                                  __L("memory allocation error")                          ,
                                  __L("error while running a __gc metamethod")            ,
                                  __L("error while running the error handler function")   ,


                                };
      XSTRING   currenttoken;
      XPATH     namefile;
      XSTRING   errorstring;
      int       nline        = 0;

      currenttoken = lua_tostring(state, -1);

      namefile.AdjustSize(_MAXSTR);
      errorstring.AdjustSize(_MAXSTR);
      currenttoken.UnFormat(__L("[string \"%s\"]:%d:%s"), namefile.Get(), &nline, errorstring.Get());
      namefile.AdjustSize();
      errorstring.AdjustSize();

      namescript.Set(namefile);
      namefile.SetOnlyNamefileExt();

      SCRIPT_XEVENT xevent(this, SCRIPT_XEVENT_TYPE_ERROR);

      xevent.SetError(errorcode);
      xevent.GetErrorText()->Set(errorstr[errorcode]);
      xevent.GetCurrentToken()->Set(currenttoken);
      xevent.SetNLine(nline);

      XTRACE_PRINTCOLOR(4, __L("Script [%s] ERROR %d: %s, line %d \"%s\"") , namefile.Get(), errorcode, errorstr[errorcode], nline, errorstring.Get());

      PostEvent(&xevent);

      this->errorcode  = errorcode;
      iscancelexec     = true;
    }

  return (errorcode == SCRIPT_ERRORCODE_NONE)?false:true;
}





/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_LUA::HaveMainFunction()
* @brief      HaveMainFunction
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LUA::HaveMainFunction()
{
  XSTRING mainfunctionname;
  XSTRING script;
  int     start = 0;
  int     end   = 0;
  XSTRING line;

  script = GetScript()->Get();
  if(script.IsEmpty()) return false;

  mainfunctionname = SCRIPT_LUA_MAINFUNCTIONNAME;

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
* @fn         void SCRIPT_LUA::Clean()
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
void SCRIPT_LUA::Clean()
{
  state = NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int LUA_LibraryCallBack(lua_State* state)
* @brief      LUA_LibraryCallBack
* @ingroup    SCRIPT
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  state :
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int LUA_LibraryCallBack(lua_State* state)
{
  lua_Debug    ar;
  XSTRING      namefunction;
  SCRIPT_LUA*  script = *static_cast<SCRIPT_LUA**>(lua_getextraspace(state));

  if(!script) return 0;

  lua_getstack (state, 0, &ar);
  if(lua_getinfo(state, "Snlu", &ar))  namefunction = ar.name;

  if(namefunction.IsEmpty()) return 0;

  SCRIPT_LIBFUNCTION* libfunction = script->GetLibraryFunction(namefunction.Get());
  if(!libfunction) return 0;
  if(!libfunction->GetFunctionLibrary()) return 0;

  XVECTOR<XVARIANT*> params;
  XVARIANT           returnvalue;

  int nargs = lua_gettop(state);

  for(int c=1; c <= nargs; ++c)
    {
      XVARIANT* variant = new XVARIANT();
      if(variant)
        {
          switch(lua_type(state, c))
            {
              case LUA_TNONE          :                                                       break;
              case LUA_TNIL           : /*(*variant) = NULL;*/                                break;
              case LUA_TBOOLEAN       : (*variant) = (lua_toboolean(state, c)?true:false);    break;
              case LUA_TLIGHTUSERDATA :                                                       break;
              case LUA_TNUMBER        : /*
                                        {
                                          float  number   = (float)lua_tonumber(state, c);
                                          double intpart  = 0.0f;
                                          double fracpart = 0.0f;

                                          fracpart = modf(number, &intpart);

                                          if(!fracpart)
                                                  (*variant) = (int)(number);
                                            else  (*variant) = (float)(number);
                                        }
                                        */

                                        (*variant) = (double)lua_tonumber(state, c);
                                        break;


              case LUA_TSTRING        : (*variant) = (char*)(lua_tostring(state, c));         break;
              case LUA_TTABLE         :                                                       break;
              case LUA_TFUNCTION      : // XVARIANT don´t suppor pointers yet
                                        //(*variant) = (void*)(lua_tocfunction(state,c));
                                        break;
              case LUA_TUSERDATA      :                                                       break;
              case LUA_TTHREAD        :                                                       break;
              case LUA_NUMTAGS        :                                                       break;
            }

          params.Add(variant);

        }
    }

  libfunction->GetFunctionLibrary()(libfunction->GetLibrary(), script, &params, &returnvalue);

  params.DeleteContents();
  params.DeleteAll();

  // Push the return value on top of the stack. NOTE: We haven't popped the
  // input arguments to our function. To be honest, I haven't checked if we
  // must, but at least in stack machines like the JVM, the stack will be
  // cleaned between each function call.

  int nreturnvalues = 0;

  switch(returnvalue.GetType())
    {
      case XVARIANT_TYPE_NULL          :                                                                    break;
      case XVARIANT_TYPE_SERIALIZABLE  :                                                                    break;
      case XVARIANT_TYPE_INTEGER       : lua_pushnumber(state, (int)(returnvalue));    nreturnvalues++;     break;
      case XVARIANT_TYPE_CHAR          : lua_pushnumber(state, (int)(returnvalue));    nreturnvalues++;     break;
      case XVARIANT_TYPE_XCHAR         :                                                                    break;
      case XVARIANT_TYPE_FLOAT         : lua_pushnumber(state, (float)(returnvalue));  nreturnvalues++;     break;

      case XVARIANT_TYPE_STRING        : { XSTRING stringreturnvalue;

                                           stringreturnvalue = returnvalue;

                                           XSTRING_CREATEOEM(stringreturnvalue, charstr)
                                           lua_pushstring(state, charstr);
                                           XSTRING_DELETEOEM(stringreturnvalue, charstr);

                                           nreturnvalues++;
                                         }
                                         break;

      case XVARIANT_TYPE_DATE          :                                                                    break;
      case XVARIANT_TYPE_TIME          :                                                                    break;
      case XVARIANT_TYPE_DATETIME      :                                                                    break;
    }


  // Let Lua know how many return values we've passed
  return nreturnvalues;
}


