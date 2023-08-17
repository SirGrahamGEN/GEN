/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       Script_Language_G.cpp
* 
* @class      SCRIPT_LNG_G
* @brief      Script Language G interpreter (mini .c interpreter)
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

#include "Script_Language_G.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include <stdio.h>
#include <ctype.h>

#include "XPath.h"
#include "XFactory.h"
#include "XFileTXT.h"
#include "XThread.h"
#include "XTrace.h"
#include "XThreadCollected.h"
#include "XVariant.h"

#include "Script_XEvent.h"
#include "Script_Lib.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE


#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS



/*---- LIBRARY FUNCTIONS ---------------------------------------------------------------------------------------------*/
#pragma region SCRIPT_LNG_G_COMMAND_CLASS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SCRIPT_LNG_G_COMMAND::SCRIPT_LNG_G_COMMAND()
* @brief      Constructor
* @ingroup    SCRIPT
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LNG_G_COMMAND::SCRIPT_LNG_G_COMMAND()

{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SCRIPT_LNG_G_COMMAND::~SCRIPT_LNG_G_COMMAND()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    SCRIPT
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LNG_G_COMMAND::~SCRIPT_LNG_G_COMMAND()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* SCRIPT_LNG_G_COMMAND::GetCommand()
* @brief      GetCommand
* @ingroup    SCRIPT
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* SCRIPT_LNG_G_COMMAND::GetCommand()
{
  return &command;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SCRIPT_LNG_G_TOKENIREPS SCRIPT_LNG_G_COMMAND::GetToken()
* @brief      GetToken
* @ingroup    SCRIPT
* 
* @return     SCRIPT_LNG_G_TOKENIREPS : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LNG_G_TOKENIREPS SCRIPT_LNG_G_COMMAND::GetToken()
{
  return token;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT_LNG_G_COMMAND::Set(XCHAR* command, SCRIPT_LNG_G_TOKENIREPS token)
* @brief      Set
* @ingroup    SCRIPT
* 
* @param[in]  command : 
* @param[in]  token : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LNG_G_COMMAND::Set(XCHAR* command, SCRIPT_LNG_G_TOKENIREPS  token)
{
  if(!command) return false;

  this->command = command;
  this->token   = token;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT_LNG_G_COMMAND::Set(XSTRING& command,SCRIPT_LNG_G_TOKENIREPS token)
* @brief      Set
* @ingroup    SCRIPT
* 
* @param[in]  command : 
* @param[in]  token : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LNG_G_COMMAND::Set(XSTRING& command,SCRIPT_LNG_G_TOKENIREPS token)
{
  return Set(command.Get(),token);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SCRIPT_LNG_G_COMMAND::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    SCRIPT
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LNG_G_COMMAND::Clean()
{
  command.Empty();
  token = SCRIPT_LNG_G_TOKENIREPS_UNDEFTOK;
}


#pragma endregion


/*---- LIBRARY FUNCTIONS ---------------------------------------------------------------------------------------------*/
#pragma region SCRIPT_LNG_G_COMMAND_CLASS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SCRIPT_LNG_G_VAR::SCRIPT_LNG_G_VAR()
* @brief      Constructor
* @ingroup    SCRIPT
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LNG_G_VAR::SCRIPT_LNG_G_VAR()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SCRIPT_LNG_G_VAR::~SCRIPT_LNG_G_VAR()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    SCRIPT
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LNG_G_VAR::~SCRIPT_LNG_G_VAR()
{  
  Clear();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* SCRIPT_LNG_G_VAR::GetName()
* @brief      GetName
* @ingroup    SCRIPT
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* SCRIPT_LNG_G_VAR::GetName()
{
  return &name;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SCRIPT_LNG_G_TOKENIREPS SCRIPT_LNG_G_VAR::GetType()
* @brief      GetType
* @ingroup    SCRIPT
* 
* @return     SCRIPT_LNG_G_TOKENIREPS : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LNG_G_TOKENIREPS SCRIPT_LNG_G_VAR::GetType()
{
  return type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int SCRIPT_LNG_G_VAR::GetValueInteger()
* @brief      GetValueInteger
* @ingroup    SCRIPT
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int SCRIPT_LNG_G_VAR::GetValueInteger()
{
  return value.integer;
}
  


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XCHAR SCRIPT_LNG_G_VAR::GetValueCharacter()
* @brief      GetValueCharacter
* @ingroup    SCRIPT
* 
* @return     XCHAR : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR SCRIPT_LNG_G_VAR::GetValueCharacter()
{
  return value.character;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD SCRIPT_LNG_G_VAR::GetValueUInteger()
* @brief      GetValueUInteger
* @ingroup    SCRIPT
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD SCRIPT_LNG_G_VAR::GetValueUInteger()
{
  return value.uinteger;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* SCRIPT_LNG_G_VAR::GetValueString()
* @brief      GetValueString
* @ingroup    SCRIPT
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* SCRIPT_LNG_G_VAR::GetValueString()
{
  return value.string;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT_LNG_G_VAR::HaveReservedSize()
* @brief      HaveReservedSize
* @ingroup    SCRIPT
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LNG_G_VAR::HaveReservedSize()
{
  return havereservedsize;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT_LNG_G_VAR::IsArg()
* @brief      IsArg
* @ingroup    SCRIPT
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LNG_G_VAR::IsArg()
{
  return isarg;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT_LNG_G_VAR::IsReturnValue()
* @brief      IsReturnValue
* @ingroup    SCRIPT
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LNG_G_VAR::IsReturnValue()
{
  return isreturnvalue;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT_LNG_G_VAR::Set(SCRIPT_LNG_G_VAR* var)
* @brief      Set
* @ingroup    SCRIPT
* 
* @param[in]  var : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LNG_G_VAR::Set(SCRIPT_LNG_G_VAR* var)
{
  name                = var->name;
  type                = var->type;
  value               = var->value;
  havereservedsize    = var->havereservedsize;
  isarg               = var->isarg;
  isreturnvalue       = var->isreturnvalue;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT_LNG_G_VAR::SetName(XCHAR* name)
* @brief      SetName
* @ingroup    SCRIPT
* 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LNG_G_VAR::SetName(XCHAR* name)
{
  this->name = name;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT_LNG_G_VAR::SetType(SCRIPT_LNG_G_TOKENIREPS type)
* @brief      SetType
* @ingroup    SCRIPT
* 
* @param[in]  type : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LNG_G_VAR::SetType(SCRIPT_LNG_G_TOKENIREPS type)
{
  this->type = type;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT_LNG_G_VAR::SetValueInteger(int value)
* @brief      SetValueInteger
* @ingroup    SCRIPT
* 
* @param[in]  value : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LNG_G_VAR::SetValueInteger(int value)
{
  this->value.integer = value;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT_LNG_G_VAR::SetValueCharacter(XCHAR value)
* @brief      SetValueCharacter
* @ingroup    SCRIPT
* 
* @param[in]  value : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LNG_G_VAR::SetValueCharacter(XCHAR value)
{
  this->value.character = value;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT_LNG_G_VAR::SetValueUInteger(XDWORD value)
* @brief      SetValueUInteger
* @ingroup    SCRIPT
* 
* @param[in]  value : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LNG_G_VAR::SetValueUInteger(XDWORD value)
{
  this->value.uinteger = value;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT_LNG_G_VAR::SetValueString(XSTRING* value)
* @brief      SetValueString
* @ingroup    SCRIPT
* 
* @param[in]  value : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LNG_G_VAR::SetValueString(XSTRING* value)
{
  this->value.string = value;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT_LNG_G_VAR::SetValueString()
* @brief      SetValueString
* @ingroup    SCRIPT
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LNG_G_VAR::SetValueString()
{
  value.string = NULL;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT_LNG_G_VAR::SetHaveReservedSize(bool havereservedsize)
* @brief      SetHaveReservedSize
* @ingroup    SCRIPT
* 
* @param[in]  nothavereservedsize : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LNG_G_VAR::SetHaveReservedSize(bool havereservedsize)
{
  this->havereservedsize = havereservedsize;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT_LNG_G_VAR::SetIsArg(bool isarg)
* @brief      SetIsArg
* @ingroup    SCRIPT
* 
* @param[in]  isarg : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LNG_G_VAR::SetIsArg(bool isarg)
{
  this->isarg = isarg;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool SCRIPT_LNG_G_VAR::SetIsReturnValue(bool isreturnvalue)
* @brief      SetIsReturnValue
* @ingroup    SCRIPT
* 
* @param[in]  isreturnvalue : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LNG_G_VAR::SetIsReturnValue(bool isreturnvalue)
{
  this->isreturnvalue = isreturnvalue;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_LNG_G_VAR::ConvertToXVariant(XVARIANT& variant)
* @brief      ConvertToXVariant
* @ingroup    SCRIPT
*
* @param[in]  variant :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LNG_G_VAR::ConvertToXVariant(XVARIANT& variant)
{ 
  switch(type)
    {
      case SCRIPT_LNG_G_TOKENIREPS_CHAR     : { XSTRING str;

                                                str.Format(__L("%c"), GetValueCharacter());
                                                variant = (XCHAR)str.Get()[0];
                                              }
                                              break;

      case SCRIPT_LNG_G_TOKENIREPS_INT      : variant = GetValueInteger();        break;
      case SCRIPT_LNG_G_TOKENIREPS_STRING   : variant = GetValueString()->Get();  break;

                                default     : variant.Set();
                                              return false;
    }
 
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_LNG_G_VAR::ConvertFromXVariant(XVARIANT& variant)
* @brief      ConvertFromXVariant
* @ingroup    SCRIPT
*
* @param[in]  variant :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LNG_G_VAR::ConvertFromXVariant(XVARIANT& variant)
{
  Clear();

  switch(variant.GetType())
    {
      case XVARIANT_TYPE_NULL           : break;
      
      case XVARIANT_TYPE_INTEGER        : SetType(SCRIPT_LNG_G_TOKENIREPS_INT);
                                          SetValueInteger(variant);
                                          break;

      case XVARIANT_TYPE_CHAR           : { XSTRING str;
                                            XCHAR   character = 0x000;

                                            str = (const XSTRING&)variant;

                                            if(!str.IsEmpty())
                                              {
                                                character = str.Get()[0];
                                                SetType(SCRIPT_LNG_G_TOKENIREPS_CHAR);
                                                SetValueCharacter(character);
                                              }
                                          }
                                          break;

      case XVARIANT_TYPE_FLOAT          : return false;

      case XVARIANT_TYPE_STRING         : { XSTRING* string = new XSTRING();
                                            if(!string) break;

                                            (*string) = (const XSTRING&)variant;
                                            SetType(SCRIPT_LNG_G_TOKENIREPS_STRING);
                                            SetHaveReservedSize(true);
                                            SetValueString(string);
                                          }
                                          break;

      case XVARIANT_TYPE_DATE           :
      case XVARIANT_TYPE_TIME           :
      case XVARIANT_TYPE_DATETIME       : return false;
    }
 
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_LNG_G_VAR::Clear()
* @brief      Clear
* @ingroup    SCRIPT
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LNG_G_VAR::Clear()
{
  name.Empty();

  if((value.string) && (type == SCRIPT_LNG_G_TOKENIREPS_STRING) &&  (HaveReservedSize()))
    {
      delete value.string;
      value.string    = NULL;
    }

  type                = SCRIPT_LNG_G_TOKENIREPS_UNDEFTOK;
  value.integer       = 0;

  havereservedsize    = false;
  isarg               = false;
  isreturnvalue       = false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPT_LNG_G_VAR::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    SCRIPT
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LNG_G_VAR::Clean()
{
  name.Empty();

  type                = SCRIPT_LNG_G_TOKENIREPS_UNDEFTOK;
  value.integer       = 0;
  value.string        = NULL;
  havereservedsize    = false;
  isarg               = false;
  isreturnvalue       = false;
}


#pragma endregion


/*---- LIBRARY FUNCTIONS ---------------------------------------------------------------------------------------------*/
#pragma region SCRIPT_LNG_G_FUNCTIONTYPE_CLASS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_LNG_G_FUNCTIONTYPE::SCRIPT_LNG_G_FUNCTIONTYPE()
* @brief      Constructor
* @ingroup    SCRIPT
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LNG_G_FUNCTIONTYPE::SCRIPT_LNG_G_FUNCTIONTYPE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_LNG_G_FUNCTIONTYPE::~SCRIPT_LNG_G_FUNCTIONTYPE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    SCRIPT
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LNG_G_FUNCTIONTYPE::~SCRIPT_LNG_G_FUNCTIONTYPE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* SCRIPT_LNG_G_FUNCTIONTYPE::GetName()
* @brief      GetName
* @ingroup    SCRIPT
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* SCRIPT_LNG_G_FUNCTIONTYPE::GetName()
{
  return &name;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_LNG_G_TOKENIREPS SCRIPT_LNG_G_FUNCTIONTYPE::GetReturnType()
* @brief      GetReturnType
* @ingroup    SCRIPT
*
* @return     SCRIPT_LNG_G_TOKENIREPS :
*
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LNG_G_TOKENIREPS SCRIPT_LNG_G_FUNCTIONTYPE::GetReturnType()
{
  return returntype;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XCHAR* SCRIPT_LNG_G_FUNCTIONTYPE::GetLocation()
* @brief      GetLocation
* @ingroup    SCRIPT
*
* @return     XCHAR* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR* SCRIPT_LNG_G_FUNCTIONTYPE::GetLocation()
{
  return location;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_LNG_G_FUNCTIONTYPE::SetName(XCHAR* name)
* @brief      SetName
* @ingroup    SCRIPT
*
* @param[in]  name :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LNG_G_FUNCTIONTYPE::SetName(XCHAR* name)
{
  this->name = name;

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_LNG_G_FUNCTIONTYPE::SetName(XSTRING& name)
* @brief      SetName
* @ingroup    SCRIPT
*
* @param[in]  name :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LNG_G_FUNCTIONTYPE::SetName(XSTRING& name)
{
  return SetName(name.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_LNG_G_FUNCTIONTYPE::SetReturnType(SCRIPT_LNG_G_TOKENIREPS returntype)
* @brief      SetReturnType
* @ingroup    SCRIPT
*
* @param[in]  returntype :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LNG_G_FUNCTIONTYPE::SetReturnType(SCRIPT_LNG_G_TOKENIREPS returntype)
{
  this->returntype = returntype;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_LNG_G_FUNCTIONTYPE::SetLocation(XCHAR* location)
* @brief      SetLocation
* @ingroup    SCRIPT
*
* @param[in]  location :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LNG_G_FUNCTIONTYPE::SetLocation(XCHAR* location)
{
  this->location = location;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPT_LNG_G_FUNCTIONTYPE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    SCRIPT
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LNG_G_FUNCTIONTYPE::Clean()
{
  name.Empty();                                        // name

  returntype  = SCRIPT_LNG_G_TOKENIREPS_UNDEFTOK;      // return type
  location    = NULL;
}


#pragma endregion


/*---- LIBRARY FUNCTIONS ---------------------------------------------------------------------------------------------*/
#pragma region SCRIPT_LNG_G_CLASS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_LNG_G::SCRIPT_LNG_G()
* @brief      Constructor
* @ingroup    SCRIPT
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LNG_G::SCRIPT_LNG_G()
{
  Clean();

  type = SCRIPT_TYPE_G;

  functioncallstack.SetIsMulti(true);

  DeleteVarsExec();

  AddCommand(__L("if")      , SCRIPT_LNG_G_TOKENIREPS_IF);
  AddCommand(__L("else")    , SCRIPT_LNG_G_TOKENIREPS_ELSE);
  AddCommand(__L("for")     , SCRIPT_LNG_G_TOKENIREPS_FOR);
  AddCommand(__L("do")      , SCRIPT_LNG_G_TOKENIREPS_DO);
  AddCommand(__L("while")   , SCRIPT_LNG_G_TOKENIREPS_WHILE);
  AddCommand(__L("char")    , SCRIPT_LNG_G_TOKENIREPS_CHAR);
  AddCommand(__L("int")     , SCRIPT_LNG_G_TOKENIREPS_INT);
  AddCommand(__L("string")  , SCRIPT_LNG_G_TOKENIREPS_STRING);
  AddCommand(__L("return")  , SCRIPT_LNG_G_TOKENIREPS_RETURN);
  AddCommand(__L("switch")  , SCRIPT_LNG_G_TOKENIREPS_SWITCH);
  AddCommand(__L("break")   , SCRIPT_LNG_G_TOKENIREPS_BREAK);
  AddCommand(__L("case")    , SCRIPT_LNG_G_TOKENIREPS_CASE);
  AddCommand(__L("")        , SCRIPT_LNG_G_TOKENIREPS_END);

  AddInternalLibraries();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_LNG_G::~SCRIPT_LNG_G()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    SCRIPT
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LNG_G::~SCRIPT_LNG_G()
{
  DeleteCommands();

  DeleteLibraryFuncions();

  librarys.DeleteAll();

  DeleteVarsExec();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_LNG_G_ERRORCODE SCRIPT_LNG_G::Run(int* returnval)
* @brief      Run
* @ingroup    SCRIPT
*
* @param[in]  returnval :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int SCRIPT_LNG_G::Run(int* returnval)
{
  if(script.IsEmpty()) return SCRIPT_ERRORCODE_INTERNALERROR;

  isrunwiththread = false;
  if(thread) isrunwiththread = thread->IsRunning();

  errorcode  = SCRIPT_ERRORCODE_NONE;
  iscancelexec = false;
  breakfound   = false;
  ipprg        = script.Get();

  
  SCRIPT_LNG_G_VAR* versionvar = new SCRIPT_LNG_G_VAR();
  if(versionvar)
    {
      XSTRING* version = new XSTRING();
      if(version)
        {
          version->Format(__L("%d.%d.%d"), SCRIPT_LNG_G_VERSION, SCRIPT_LNG_G_SUBVERSION, SCRIPT_LNG_G_SUBVERSIONERR);
       
          versionvar->SetType(SCRIPT_LNG_G_TOKENIREPS_STRING);
          versionvar->SetName(__L("VERSION"));    
          versionvar->SetValueString(version);    
          versionvar->SetHaveReservedSize(true);
          versionvar->SetIsArg(false);

          globalvars.Add(versionvar);
        }
       else
        {
          delete versionvar;
        }
    }
  
  PreScan();

  if(errorcode == SCRIPT_ERRORCODE_NONE)
    {
      ipprg = FindFunction(__L("main"));    // Find program starting point.
      if(ipprg)
        {
          ipprg--;
          XSTRING::Set(currenttoken,__L("main"));

          Call();

        } else errorcode = SCRIPT_LNG_G_ERRORCODE_FUNC_UNDEF;
    }

  if(errorcode == SCRIPT_ERRORCODE_NONE)
    {
      if(returnval)
        {
          (*returnval) = returnvalue.GetValueInteger();
        }
    }

  
  DeleteVarsExec();

  return errorcode;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_LNG_G::AddCommand(XCHAR* command,SCRIPT_LNG_G_TOKENIREPS token)
* @brief      AddCommand
* @ingroup    SCRIPT
*
* @param[in]  command :
* @param[in]  token :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LNG_G::AddCommand(XCHAR* command,SCRIPT_LNG_G_TOKENIREPS token)
{
  SCRIPT_LNG_G_COMMAND* _command = new SCRIPT_LNG_G_COMMAND();
  if(!_command) return false;

  if(!_command->Set(command, token)) return false;

  commands.Add(_command);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_LNG_G::DeleteCommands()
* @brief      DeleteCommands
* @ingroup    SCRIPT
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LNG_G::DeleteCommands()
{
  if(commands.IsEmpty()) return false;

  commands.DeleteContents();
  commands.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int SCRIPT_LNG_G::GetFuncParams(SCRIPT_LNG_G_VAR* params)
* @brief      GetFuncParams
* @ingroup    SCRIPT
*
* @param[in]  params :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int SCRIPT_LNG_G::GetFuncParams(SCRIPT_LNG_G_VAR* params)
{
  int count = 0;

  GetToken();

  if(currenttoken[0] != __C('('))
    {
      HaveError(SCRIPT_LNG_G_ERRORCODE_PAREN_EXPECTED);
      return count;
    }

  do{ SCRIPT_LNG_G_VAR* param = new SCRIPT_LNG_G_VAR();
      if(param)
        {
          EvalExp((*param));

          params[count].Set(param);

          /*  
          if(param->IsReturnValue())
                 params[count].SetHaveReservedSize(true);
            else params[count].SetHaveReservedSize(false);
          */

          GetToken();

          count++;

          param->SetHaveReservedSize(false);

          delete param;
        }

    } while(currenttoken[0] == __C(','));

  return count;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPT_LNG_G::NotFuncParams()
* @brief      NotFuncParams
* @ingroup    SCRIPT
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LNG_G::NotFuncParams()
{
  GetToken();
  if(currenttoken[0] != __C('('))
    {
      HaveError(SCRIPT_LNG_G_ERRORCODE_PAREN_EXPECTED);
      return;
    }

  GetToken();
  if(currenttoken[0] != __C(')'))
    {
      HaveError(SCRIPT_LNG_G_ERRORCODE_PAREN_EXPECTED);
      return;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int SCRIPT_LNG_G::GetReturnValueScript()
* @brief      GetReturnValueScript
* @ingroup    SCRIPT
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int SCRIPT_LNG_G::GetReturnValueScript()
{
  return returnvaluescript;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int SCRIPT_LNG_G::SetReturnValueScript(int returnvaluescript)
* @brief      SetReturnValueScript
* @ingroup    SCRIPT
*
* @param[in]  returnvaluescript :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int SCRIPT_LNG_G::SetReturnValueScript(int returnvaluescript)
{
  this->returnvaluescript = returnvaluescript;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_LNG_G::HaveError(SCRIPT_LNG_G_ERRORCODE errorcode)
* @brief      HaveError
* @ingroup    SCRIPT
*
* @param[in]  errorcode :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LNG_G::HaveError(int errorcode)
{
  if(errorcode != SCRIPT_ERRORCODE_NONE)
    {
      static XCHAR* errorstr[]= { __L("None")                       ,
                                  __L("Internal error")             ,
                                  __L("Syntax error")               ,
                                  __L("Insufficient parameters")    ,
                                  __L("No expression present")      ,
                                  __L("Not a variable")             ,
                                  __L("Duplicate variable name")    ,
                                  __L("Duplicate function name")    ,
                                  __L("Semicolon expected")         ,
                                  __L("Unbalanced braces")          ,
                                  __L("Function undefined")         ,
                                  __L("Type specifier expected")    ,
                                  __L("Return without call")        ,
                                  __L("Parentheses expected")       ,
                                  __L("While expected")             ,
                                  __L("Closing quote expected")     ,
                                  __L("Division by zero")           ,
                                  __L("{ expected (control statements must use blocks)"),
                                  __L("Colon expected")             ,
                                  __L("Break by user")
                                };

      SCRIPT_XEVENT xevent(this,(errorcode==SCRIPT_LNG_G_ERRORCODE_USERBREAK)?SCRIPT_XEVENT_TYPE_BREAK:SCRIPT_XEVENT_TYPE_ERROR);


      XDWORD sizecharnow = (int)(ipprg - script.Get());
      XDWORD sizechar    = 0;
      int nline       = 0;

      for(int c=0;c<xfiletxt->GetNLines();c++)
        {
          sizechar += (xfiletxt->GetLine(c)->GetSize()+2);

          if(sizecharnow<=sizechar)
            {
              nline = c+1;
              break;
            }
        }

      xevent.SetError(errorcode);
      xevent.GetErrorText()->Set(errorstr[errorcode]);
      xevent.GetCurrentToken()->Set(currenttoken);
      xevent.SetNLine(nline);

      XTRACE_PRINTCOLOR(4, __L("Script [%s] ERROR %d: %s, line %d \"%s\"") , namescript.Get(), errorcode, errorstr[errorcode], nline, currenttoken);

      PostEvent(&xevent);      
      iscancelexec = true;

      this->errorcode = errorcode;
    }

  return (errorcode==SCRIPT_ERRORCODE_NONE)?false:true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_LNG_G::DeleteVarsExec()
* @brief      DeleteVarsExec
* @ingroup    SCRIPT
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LNG_G::DeleteVarsExec()
{
  if(!globalvars.IsEmpty())
    {
      globalvars.DeleteContents();
      globalvars.DeleteAll();
    }

  if(!functiontable.IsEmpty())
    {
      functiontable.DeleteContents();
      functiontable.DeleteAll();
    }

  if(!localvarsstack.IsEmpty())
    {
      localvarsstack.DeleteContents();
      localvarsstack.DeleteAll();
    }

  if(!functioncallstack.IsEmpty()) 
    {
      functioncallstack.DeleteAll();
    }

  if(!nestscopestack.IsEmpty())    
    {
      nestscopestack.DeleteAll();
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_LNG_G::IsSpace(XCHAR character)
* @brief      IsSpace
* @ingroup    SCRIPT
*
* @param[in]  character :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LNG_G::IsSpace(XCHAR character)
{
  if(character == __C(' '))   return true;
  if(character == __C('\x09')) return true;

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_LNG_G::IsDigit(XCHAR character)
* @brief      IsDigit
* @ingroup    SCRIPT
*
* @param[in]  character :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LNG_G::IsDigit(XCHAR character)
{
  if((character>=__C('0'))&&(character <= __C('9'))) return true;

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_LNG_G::IsAlpha(XCHAR character)
* @brief      IsAlpha
* @ingroup    SCRIPT
*
* @param[in]  character :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LNG_G::IsAlpha(XCHAR character)
{
  if((character>='a')&&(character<='z')) return true;
  if((character>='A')&&(character<='Z')) return true;

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_LNG_G::IsDelimiter(XCHAR c)
* @brief      IsDelimiter
* @ingroup    SCRIPT
*
* @param[in]  c :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LNG_G::IsDelimiter(XCHAR c)
{
  if(c==0) return true;

  XSTRING delimiter(__L("\x09\r !:;,+-<>'/*%^=()"));

  if(delimiter.FindCharacter(c)!=XSTRING_NOTFOUND) return true;

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_LNG_G_TOKENIREPS SCRIPT_LNG_G::LookUpToken(XCHAR* s)
* @brief      LookUpToken
* @ingroup    SCRIPT
*
* @param[in]  s :
*
* @return     SCRIPT_LNG_G_TOKENIREPS :
*
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LNG_G_TOKENIREPS SCRIPT_LNG_G::LookUpToken(XCHAR* s)
{
  for(int c=0;c<(int)commands.GetSize();c++)
    {
      SCRIPT_LNG_G_COMMAND* command = (SCRIPT_LNG_G_COMMAND*)commands.Get(c);
      if(command)
        {
          if(!command->GetCommand()->Compare(s)) return command->GetToken();
        }
    }

  return SCRIPT_LNG_G_TOKENIREPS_UNDEFTOK;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPT_LNG_G::PutBackToken()
* @brief      PutBackToken
* @ingroup    SCRIPT
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LNG_G::PutBackToken()
{
  XCHAR* token;

  token = currenttoken;

  for(; *token; token++)
    {
      ipprg--;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPT_LNG_G::EvalExp(SCRIPT_LNG_G_VAR& value)
* @brief      EvalExp
* @ingroup    SCRIPT
*
* @param[in]  value :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LNG_G::EvalExp(SCRIPT_LNG_G_VAR& value)
{
  GetToken();

  if((tokentype != SCRIPT_LNG_G_TOKENTYPES_STRING))
    {
      if(!currenttoken[0])
        {
          HaveError(SCRIPT_LNG_G_ERRORCODE_NO_EXP);
          return;
        }
    }
   else
    {
      XSTRING* string = new XSTRING();
      if(string)
        {
          (*string) = currenttoken;

          value.SetType(SCRIPT_LNG_G_TOKENIREPS_STRING);          
          value.SetValueString(string);
          value.SetHaveReservedSize(true);

          value.SetIsReturnValue(false);

          return;
        }
    }

  if(currenttoken[0] == __C(';'))
    {
      value.Clear();
      return;
    }

  EvalExp0(value);

  PutBackToken();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPT_LNG_G::EvalExp0(SCRIPT_LNG_G_VAR& value)
* @brief      EvalExp0
* @ingroup    SCRIPT
*
* @param[in]  value :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LNG_G::EvalExp0(SCRIPT_LNG_G_VAR& value)
{
  XSTRING                 tempttoken;
  SCRIPT_LNG_G_TOKENTYPES temptokentype;

  if(tokentype == SCRIPT_LNG_G_TOKENTYPES_IDENTIFIER)
    {
       SCRIPT_LNG_G_VAR* variable = IsVariable(currenttoken);
       if(variable)
         {
           tempttoken    = currenttoken;
           temptokentype = tokentype;

           GetToken();

           if(currenttoken[0] == __C('='))
             {
               GetToken();

               if(tokentype == SCRIPT_LNG_G_TOKENTYPES_STRING)
                 {
                   XSTRING* string = new XSTRING();
                   if(string)
                     {
                       (*string) = currenttoken;

                       value.SetType(SCRIPT_LNG_G_TOKENIREPS_STRING);
                       value.SetValueString(string);
                       value.SetHaveReservedSize(true);

                       AssignVariable(tempttoken.Get(), value);
                    
                       GetToken();
                     }
                 }
                else
                 {
                   EvalExp0(value);
                   AssignVariable(tempttoken.Get(), value);
                 }

               return;
             }
            else
             {
               if(variable->GetType() == SCRIPT_LNG_G_TOKENIREPS_STRING)
                 {
                   value.GetName()->Set(variable->GetName()->Get());
                   value.SetType(SCRIPT_LNG_G_TOKENIREPS_STRING);
                   value.SetValueString(variable->GetValueString());
                   
                   return;
                 }
                else
                 {
                   PutBackToken();

                   XSTRING::Set(currenttoken,tempttoken.Get());
                   tokentype    = temptokentype;
                 }
             }
         }
    }

  EvalExp1(value);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPT_LNG_G::EvalExp1(SCRIPT_LNG_G_VAR& value)
* @brief      EvalExp1
* @ingroup    SCRIPT
*
* @param[in]  value :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LNG_G::EvalExp1(SCRIPT_LNG_G_VAR& value)
{
  XCHAR   operation;
  XSTRING relops;

  relops.Format(__L("%c%c%c%c%c%c"), SCRIPT_LNG_G_DOUBLEOPERATOR_LT, SCRIPT_LNG_G_DOUBLEOPERATOR_LE, SCRIPT_LNG_G_DOUBLEOPERATOR_GT
                                   , SCRIPT_LNG_G_DOUBLEOPERATOR_GE, SCRIPT_LNG_G_DOUBLEOPERATOR_EQ, SCRIPT_LNG_G_DOUBLEOPERATOR_NE);
  EvalExp2(value);

  operation = currenttoken[0];

  if(relops.FindCharacter(operation)!=XSTRING_NOTFOUND)
    {
      GetToken();

      if(tokentype == SCRIPT_LNG_G_TOKENTYPES_STRING)
        {
          XSTRING* strpvalue = new XSTRING();
          if(strpvalue)
            {
              XSTRING* strvalue = value.GetValueString();

              SCRIPT_LNG_G_VAR pvalue;

              pvalue.SetValueString(strpvalue);

              EvalExp2(pvalue);

              switch(operation)
                {
                  case SCRIPT_LNG_G_DOUBLEOPERATOR_LT:  value.SetValueInteger((strvalue->GetSize() <  strpvalue->GetSize())); break;
                  case SCRIPT_LNG_G_DOUBLEOPERATOR_LE:  value.SetValueInteger((strvalue->GetSize() <= strpvalue->GetSize())); break;
                  case SCRIPT_LNG_G_DOUBLEOPERATOR_GT:  value.SetValueInteger((strvalue->GetSize() >  strpvalue->GetSize())); break;
                  case SCRIPT_LNG_G_DOUBLEOPERATOR_GE:  value.SetValueInteger((strvalue->GetSize() >= strpvalue->GetSize())); break;
                  case SCRIPT_LNG_G_DOUBLEOPERATOR_EQ:  value.SetValueInteger(!strvalue->Compare((*strpvalue))?1:0);          break;
                  case SCRIPT_LNG_G_DOUBLEOPERATOR_NE:  value.SetValueInteger(strvalue->Compare((*strpvalue)));               break;
                }

              delete strpvalue;
            }
        }
       else
        {
          SCRIPT_LNG_G_VAR partialvalue;

          EvalExp2(partialvalue);

          switch(operation)
            {
              case SCRIPT_LNG_G_DOUBLEOPERATOR_LT:  value.SetValueInteger((value.GetValueInteger() <  partialvalue.GetValueInteger())); break;
              case SCRIPT_LNG_G_DOUBLEOPERATOR_LE:  value.SetValueInteger((value.GetValueInteger() <= partialvalue.GetValueInteger())); break;
              case SCRIPT_LNG_G_DOUBLEOPERATOR_GT:  value.SetValueInteger((value.GetValueInteger() >  partialvalue.GetValueInteger())); break;
              case SCRIPT_LNG_G_DOUBLEOPERATOR_GE:  value.SetValueInteger((value.GetValueInteger() >= partialvalue.GetValueInteger())); break;
              case SCRIPT_LNG_G_DOUBLEOPERATOR_EQ:  value.SetValueInteger((value.GetValueInteger() == partialvalue.GetValueInteger())); break;
              case SCRIPT_LNG_G_DOUBLEOPERATOR_NE:  value.SetValueInteger((value.GetValueInteger() != partialvalue.GetValueInteger())); break;
            }
        }
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPT_LNG_G::EvalExp2(SCRIPT_LNG_G_VAR& value)
* @brief      EvalExp2
* @ingroup    SCRIPT
*
* @param[in]  value :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LNG_G::EvalExp2(SCRIPT_LNG_G_VAR& value)
{
  XCHAR   operation;
  XSTRING okops;

  okops.Format(__L("(%c%c-+"), SCRIPT_LNG_G_DOUBLEOPERATOR_INC, SCRIPT_LNG_G_DOUBLEOPERATOR_DEC);

  EvalExp3(value);

  while(((operation = currenttoken[0]) == __C('+')) || (operation == __C('-')))
    {
      GetToken();

      if((tokentype == SCRIPT_LNG_G_TOKENTYPES_DELIMITER) && (okops.FindCharacter(currenttoken[0]) == XSTRING_NOTFOUND))
        {
          HaveError(SCRIPT_LNG_G_ERRORCODE_SYNTAX);
          return;
        }

      if(tokentype == SCRIPT_LNG_G_TOKENTYPES_STRING)
        {
          HaveError(SCRIPT_LNG_G_ERRORCODE_SYNTAX);
          return;
        }

      if(tokentype == SCRIPT_LNG_G_TOKENTYPES_IDENTIFIER)
        {
          SCRIPT_LNG_G_VAR* var = IsVariable(currenttoken);
          if(var)
            {
              if(var->GetType()==SCRIPT_LNG_G_TOKENIREPS_STRING)
                {
                  HaveError(SCRIPT_LNG_G_ERRORCODE_SYNTAX);
                  return;
                }
            }
        }

      SCRIPT_LNG_G_VAR partialvalue;

      EvalExp3(partialvalue);

      switch(operation)
        {
          case __C('-'):    value.SetValueInteger((value.GetValueInteger() - partialvalue.GetValueInteger()));    break;
          case __C('+'):    value.SetValueInteger((value.GetValueInteger() + partialvalue.GetValueInteger()));    break;
        }
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPT_LNG_G::EvalExp3(SCRIPT_LNG_G_VAR& value)
* @brief      EvalExp3
* @ingroup    SCRIPT
*
* @param[in]  value :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LNG_G::EvalExp3(SCRIPT_LNG_G_VAR& value)
{
  XCHAR         operation;
  XSTRING   okops;
  SCRIPT_LNG_G_VAR  partialvalue;

  okops.Format(__L("(%c%c-+"), SCRIPT_LNG_G_DOUBLEOPERATOR_INC, SCRIPT_LNG_G_DOUBLEOPERATOR_DEC);

  EvalExp4(value);

  while( ((operation = currenttoken[0]) == __C('*')) || (operation == __C('/')) || (operation == __C('%')))
    {
      GetToken();

      if((tokentype == SCRIPT_LNG_G_TOKENTYPES_DELIMITER) && (okops.FindCharacter(currenttoken[0]) == XSTRING_NOTFOUND))
        {
          HaveError(SCRIPT_LNG_G_ERRORCODE_SYNTAX);
          return;
        }

      EvalExp4(partialvalue);

      switch(operation)
        {
          // mul, div, or modulus
          case __C('*'): value.SetValueInteger(value.GetValueInteger() * partialvalue.GetValueInteger());
                         break;

          case __C('/'): if(partialvalue.GetValueInteger() == 0)
                           {
                             HaveError(SCRIPT_LNG_G_ERRORCODE_DIV_BY_ZERO);
                             return;
                           }
                         value.SetValueInteger((value.GetValueInteger() / partialvalue.GetValueInteger()));
                         break;

          case __C('%'): { int t = (value.GetValueInteger() / partialvalue.GetValueInteger());
                           value.SetValueInteger(value .GetValueInteger() - (t * partialvalue.GetValueInteger()));
                         }
                         break;
        }
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPT_LNG_G::EvalExp4(SCRIPT_LNG_G_VAR& value)
* @brief      EvalExp4
* @ingroup    SCRIPT
*
* @param[in]  value :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LNG_G::EvalExp4(SCRIPT_LNG_G_VAR& value)
{
  XCHAR operation;
  XCHAR temptoken;

  operation = __C('\0');

  if(tokentype != SCRIPT_LNG_G_TOKENTYPES_STRING)
    {
      if((currenttoken[0] == __C('+'))  ||
         (currenttoken[0] == __C('-'))  ||
         (currenttoken[0] == SCRIPT_LNG_G_DOUBLEOPERATOR_INC) ||
         (currenttoken[0] == SCRIPT_LNG_G_DOUBLEOPERATOR_DEC))
        {
          temptoken = currenttoken[0];
          operation = currenttoken[0];

          GetToken();

          SCRIPT_LNG_G_VAR* var = FindVariable(currenttoken);
          if(var)
            {
              if(temptoken == SCRIPT_LNG_G_DOUBLEOPERATOR_INC) var->SetValueInteger(var->GetValueInteger()+1);
              if(temptoken == SCRIPT_LNG_G_DOUBLEOPERATOR_DEC) var->SetValueInteger(var->GetValueInteger()-1);

              AssignVariable(currenttoken,(*var));
            }
        }
    }

  EvalExp5(value);

  if(operation == __C('-'))  value.SetValueInteger(-value.GetValueInteger());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPT_LNG_G::EvalExp5(SCRIPT_LNG_G_VAR& value)
* @brief      EvalExp5
* @ingroup    SCRIPT
*
* @param[in]  value :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LNG_G::EvalExp5(SCRIPT_LNG_G_VAR& value)
{
  if(currenttoken[0] == __C('('))
    {
      GetToken();

      EvalExp0(value);

      if(currenttoken[0] != __C(')'))
        {
          HaveError(SCRIPT_LNG_G_ERRORCODE_PAREN_EXPECTED);
          return;
        }

      GetToken();

    } else Atom(value);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPT_LNG_G::Atom(SCRIPT_LNG_G_VAR& value)
* @brief      Atom
* @ingroup    SCRIPT
*
* @param[in]  value :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LNG_G::Atom(SCRIPT_LNG_G_VAR& value)
{
  switch(tokentype) 
    {
      case SCRIPT_LNG_G_TOKENTYPES_IDENTIFIER : { SCRIPT_LIB_FUNCTION* function = GetLibraryFunction(currenttoken);
                                                  if(function)
                                                    {
                                                      if(function->GetFunctionLibrary())
                                                        {
                                                          XVECTOR<XVARIANT*>  funcparams;
                                                          XVARIANT            funcreturnvalue;
                                                          SCRIPT_LNG_G_VAR    params[SCRIPT_LNG_G_NUMPARAMS];
                                                       
                                                          int nparams = GetFuncParams(params);                                                          
                                                          for(int c=0; c<nparams; c++)
                                                            {
                                                              XVARIANT* variant = new XVARIANT();
                                                              if(variant)
                                                                {
                                                                  params[c].ConvertToXVariant((*variant));
                                                                  funcparams.Add(variant);
                                                                }
                                                            }
                                                          
                                                          (*function->GetFunctionLibrary())(function->GetLibrary(), this, &funcparams, &funcreturnvalue);

                                                          value.ConvertFromXVariant(funcreturnvalue);
                                                          value.SetIsReturnValue(true);

                                                          funcparams.DeleteContents();
                                                          funcparams.DeleteAll();
                                                        }
                                                       else
                                                        {
                                                          HaveError(SCRIPT_LNG_G_ERRORCODE_FUNC_UNDEF);
                                                          return;
                                                        }
                                                    }
                                                  else
                                                    {
                                                      if(FindFunction(currenttoken))
                                                        {
                                                          XCHAR tempcurrentfunc[_MAXSTR];

                                                          XSTRING::Set(tempcurrentfunc,currentfunction);

                                                          Call();

                                                          value.Set(&returnvalue);
                                                          value.SetIsReturnValue(true);

                                                          XSTRING::Set(currentfunction,tempcurrentfunc);

                                                          returnvalue.SetType(SCRIPT_LNG_G_TOKENIREPS_UNDEFTOK);
                                                          returnvalue.SetValueInteger(0);


                                                        }
                                                      else
                                                        {
                                                          XCHAR tempcurrenttoken[_MAXSTR];

                                                          SCRIPT_LNG_G_VAR* var = FindVariable(currenttoken);
                                                          if(var)
                                                            {
                                                              value.Set(var);

                                                              XSTRING::Set(tempcurrenttoken,currenttoken);

                                                              GetToken();

                                                              if((currenttoken[0] == SCRIPT_LNG_G_DOUBLEOPERATOR_INC) || (currenttoken[0] == SCRIPT_LNG_G_DOUBLEOPERATOR_DEC))
                                                                {
                                                                  SCRIPT_LNG_G_VAR* var = FindVariable(tempcurrenttoken);
                                                                  if(var)
                                                                    {
                                                                      if(currenttoken[0] == SCRIPT_LNG_G_DOUBLEOPERATOR_INC)
                                                                              var->SetValueInteger(var->GetValueInteger()+1);
                                                                        else  var->SetValueInteger(var->GetValueInteger()-1);

                                                                      AssignVariable(tempcurrenttoken, (*var));
                                                                    }

                                                                } else PutBackToken();
                                                            }
                                                        }
                                                    }

                                                  GetToken();
                                                }
                                                return;

      case SCRIPT_LNG_G_TOKENTYPES_NUMBER     : { XSTRING string(currenttoken);

                                                  value.SetType(SCRIPT_LNG_G_TOKENIREPS_INT);
                                                  value.SetValueInteger(string.ConvertToInt());
                                                  GetToken();
                                                }
                                                return;

      case SCRIPT_LNG_G_TOKENTYPES_STRING     : { XSTRING* string= new XSTRING();;
                                                  if(string)  
                                                    {  
                                                      (*string) = currenttoken;        

                                                      value.SetType(SCRIPT_LNG_G_TOKENIREPS_STRING);  
                                                      value.SetHaveReservedSize(true);
                                                      value.SetValueString(string);
                                                    }


                                                  /*    
                                                  if(value.GetValueString())
                                                    {
                                                      (*value.GetValueString()) = currenttoken;
                                                    }
                                                   else
                                                    {
                                                      string = new XSTRING();

                                                      if(string) 
                                                      value.SetValueString(string);

                                                      SCRIPT_LNG_G_VAR* vt = new SCRIPT_LNG_G_VAR();
                                                      if(vt)
                                                        {
                                                          vt->SetType(SCRIPT_LNG_G_TOKENIREPS_STRING);
                                                          vt->SetValueString(string);

                                                          localvarsstack.Add(vt);
                                                        }
                                                    }
                                                  */

                                                  GetToken();
                                                }
                                                return;

      case SCRIPT_LNG_G_TOKENTYPES_DELIMITER  : if(currenttoken[0] == __C('\''))
                                                  {
                                                    value.SetValueCharacter((XCHAR)(*ipprg));
                                                    ipprg++;

                                                    if((*ipprg)!=__C('\''))
                                                      {
                                                        HaveError(SCRIPT_LNG_G_ERRORCODE_QUOTE_EXPECTED);
                                                        return;
                                                      }

                                                    ipprg++;

                                                    GetToken();

                                                    return;
                                                  }

                                                if(currenttoken[0] == __C(')'))
                                                  {
                                                  }
                                                 else HaveError(SCRIPT_LNG_G_ERRORCODE_SYNTAX);

                                                return;

                        default               : HaveError(SCRIPT_LNG_G_ERRORCODE_SYNTAX);
                                                return;

    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_LNG_G_VAR* SCRIPT_LNG_G::IsVariable(XCHAR* variablename)
* @brief      IsVariable
* @ingroup    SCRIPT
*
* @param[in]  variablename :
*
* @return     SCRIPT_LNG_G_VAR* :
*
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LNG_G_VAR* SCRIPT_LNG_G::IsVariable(XCHAR* variablename)
{
  if(!localvarsstack.IsEmpty())
    {
      for(int c=((int)localvarsstack.GetSize()-1); c>= functioncallstack.GetLast(); c--)
        {
          SCRIPT_LNG_G_VAR* var = localvarsstack.Get(c);
          if(var)
            {
              if(!var->GetName()->Compare(variablename)) return var;
            }
        }
    }


  for(XDWORD c=0; c<(int)globalvars.GetSize(); c++)
    {
      SCRIPT_LNG_G_VAR* var = (SCRIPT_LNG_G_VAR*)globalvars.Get(c);
      if(var)
        {
          if(!var->GetName()->Compare(variablename)) return var;
        }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPT_LNG_G::AssignVariable(XCHAR* variablename, SCRIPT_LNG_G_VAR& value)
* @brief      AssignVariable
* @ingroup    SCRIPT
*
* @param[in]  variablename :
* @param[in]  value :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LNG_G::AssignVariable(XCHAR* variablename, SCRIPT_LNG_G_VAR& value)
{
  if(!localvarsstack.IsEmpty())
    {
      for(int c=localvarsstack.GetSize()-1; c>=functioncallstack.GetLast(); c--)
        {
          SCRIPT_LNG_G_VAR* var = (SCRIPT_LNG_G_VAR*)localvarsstack.Get(c);
          if(var)
            {
              if(!var->GetName()->Compare(variablename))
                {
                  if(var->GetType() == SCRIPT_LNG_G_TOKENIREPS_CHAR)
                    {
                      var->SetValueCharacter(value.GetValueCharacter());
                    }
                   else
                    {
                      if(var->GetType() == SCRIPT_LNG_G_TOKENIREPS_INT)
                        {
                          var->SetValueInteger(value.GetValueInteger());
                        }
                       else
                        {
                          if(var->GetType() == SCRIPT_LNG_G_TOKENIREPS_STRING)
                            {
                              XSTRING* string1 = var->GetValueString();
                              XSTRING* string2 = value.GetValueString();

                              if(string1 && string2)
                                {
                                  if(string1 != string2)
                                    {
                                      XSTRING* newstring = new XSTRING();
                                      if(newstring)
                                        {
                                          delete string1;
                                          (*newstring) = string2->Get();

                                          var->SetValueString(newstring);
                                          var->SetHaveReservedSize(true);
                                        }
                                    }
                                }
                            }
                        }
                    }

                  return;
                }
            }
        }
    }

  for(XDWORD c=0;c<globalvars.GetSize();c++)
    {
      SCRIPT_LNG_G_VAR* var = (SCRIPT_LNG_G_VAR*)globalvars.Get(c);
      if(var)
        {
          if(!var->GetName()->Compare(variablename))
            {
              if(var->GetType() == SCRIPT_LNG_G_TOKENIREPS_CHAR)
                {
                  var->SetValueCharacter(value.GetValueCharacter());
                }
               else
                {
                  if(var->GetType() == SCRIPT_LNG_G_TOKENIREPS_INT)
                    {
                      var->SetValueInteger(value.GetValueInteger());
                    }
                   else
                    {
                      if(var->GetType() == SCRIPT_LNG_G_TOKENIREPS_STRING)
                        {
                          XSTRING* string1 = var->GetValueString();
                          XSTRING* string2 = value.GetValueString();

                          if(string1 && string2)
                            {
                              if(string1 != string2)
                                {
                                  XSTRING* newstring = new XSTRING();
                                  if(newstring)
                                    {
                                      delete string1;
                                      (*newstring) = string2->Get();

                                      var->SetValueString(newstring);
                                      var->SetHaveReservedSize(true);
                                    }
                                }
                            }
                        }
                    }
                }

              return;
            }
        }
    }

  HaveError(SCRIPT_LNG_G_ERRORCODE_NOT_VAR);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_LNG_G_VAR* SCRIPT_LNG_G::FindVariable(XCHAR* variablename)
* @brief      FindVariable
* @ingroup    SCRIPT
*
* @param[in]  variablename :
*
* @return     SCRIPT_LNG_G_VAR* :
*
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LNG_G_VAR* SCRIPT_LNG_G::FindVariable(XCHAR* variablename)
{
  if(!localvarsstack.IsEmpty())
    {
      for(int c=localvarsstack.GetSize()-1; c>=functioncallstack.GetLast(); c--)
        {
          SCRIPT_LNG_G_VAR* var = (SCRIPT_LNG_G_VAR*)localvarsstack.Get(c);
          if(var)
            {
              if(!var->GetName()->Compare(variablename)) return var;
            }
        }
    }

  for(int c=0; c<(int)globalvars.GetSize(); c++)
    {
      SCRIPT_LNG_G_VAR* var = (SCRIPT_LNG_G_VAR*)globalvars.Get(c);
      if(var)
        {
          if(!var->GetName()->Compare(variablename)) return var;
        }
    }

  HaveError(SCRIPT_LNG_G_ERRORCODE_NOT_VAR);

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_LNG_G_TOKENIREPS SCRIPT_LNG_G::FindVariableType(XCHAR* variablename)
* @brief      FindVariableType
* @ingroup    SCRIPT
*
* @param[in]  variablename :
*
* @return     SCRIPT_LNG_G_TOKENIREPS :
*
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LNG_G_TOKENIREPS SCRIPT_LNG_G::FindVariableType(XCHAR* variablename)
{
  if(!localvarsstack.IsEmpty())
    {
      for(int c=localvarsstack.GetSize()-1; c>=functioncallstack.GetLast(); c--)
        {
          SCRIPT_LNG_G_VAR* var = (SCRIPT_LNG_G_VAR*)localvarsstack.Get(c);
          if(var)
            {
              if(!var->GetName()->Compare(variablename))  return var->GetType();
            }
        }
    }

  for(int c=0; c<(int)globalvars.GetSize(); c++)
    {
      SCRIPT_LNG_G_VAR* var = (SCRIPT_LNG_G_VAR*)globalvars.Get(c);
      if(var)
        {
          if(!var->GetName()->Compare(variablename)) return var->GetType();
        }
    }

  return SCRIPT_LNG_G_TOKENIREPS_UNDEFTOK;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XCHAR* SCRIPT_LNG_G::FindFunction(XCHAR* name)
* @brief      FindFunction
* @ingroup    SCRIPT
*
* @param[in]  name :
*
* @return     XCHAR* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR* SCRIPT_LNG_G::FindFunction(XCHAR* name)
{
  for(XDWORD c=0; c<functiontable.GetSize(); c++)
    {
      SCRIPT_LNG_G_FUNCTIONTYPE* functiontype = (SCRIPT_LNG_G_FUNCTIONTYPE*)functiontable.Get(c);
      if(functiontype)
        {
          if(!functiontype->GetName()->Compare(name))
            {
              return functiontype->GetLocation();
            }
        }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SCRIPT_LNG_G_FUNCTIONTYPE* SCRIPT_LNG_G::GetFunction(XCHAR* name)
* @brief      GetFunction
* @ingroup    SCRIPT
*
* @param[in]  name :
*
* @return     SCRIPT_LNG_G_FUNCTIONTYPE* :
*
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LNG_G_FUNCTIONTYPE* SCRIPT_LNG_G::GetFunction(XCHAR* name)
{
  for(XDWORD c=0; c<functiontable.GetSize(); c++)
    {
      SCRIPT_LNG_G_FUNCTIONTYPE* functiontype = (SCRIPT_LNG_G_FUNCTIONTYPE*)functiontable.Get(c);
      if(functiontype)
        {
          if(!functiontype->GetName()->Compare(name))
            {
              return functiontype;
            }
        }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SCRIPT_LNG_G::FindEndofBlock()
* @brief      FindEndofBlock
* @ingroup    SCRIPT
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LNG_G::FindEndofBlock()
{
  int brace;

  GetToken();

  if(currenttoken[0] != __C('{'))
    {
      HaveError(SCRIPT_LNG_G_ERRORCODE_BRACE_EXPECTED);
      return;
    }

  brace = 1;

  do{ GetToken();

      if(currenttoken[0] == __C('{'))
        {
          brace++;
        }
       else
        {
          if(currenttoken[0] == __C('}')) brace--;
        }

    } while(brace && tokenireps != SCRIPT_LNG_G_TOKENIREPS_END);

  if(tokenireps==SCRIPT_LNG_G_TOKENIREPS_END)
    {
      HaveError(SCRIPT_LNG_G_ERRORCODE_UNBAL_BRACES);
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SCRIPT_LNG_G::DeclareGlobalVariable()
* @brief      DeclareGlobalVariable
* @ingroup    SCRIPT
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LNG_G::DeclareGlobalVariable()
{
  SCRIPT_LNG_G_TOKENIREPS vartype;
  SCRIPT_LNG_G_VAR*       vt;

  GetToken();

  vartype = tokenireps;

  do{ GetToken();

      for(int c=0; c<(int)globalvars.GetSize(); c++)
        {
          SCRIPT_LNG_G_VAR* vttmp = (SCRIPT_LNG_G_VAR*)globalvars.Get(c);

          if(!vttmp->GetName()->Compare(currenttoken))
            {
              HaveError(SCRIPT_LNG_G_ERRORCODE_DUP_VAR);
              return;
            }
        }

      vt = new SCRIPT_LNG_G_VAR();
      if(!vt) return;

      vt->SetType(vartype);      
      vt->SetName(currenttoken);
      vt->SetHaveReservedSize(false);
                  
      if((vartype==SCRIPT_LNG_G_TOKENIREPS_STRING)&&(!vt->GetValueString()))
        {
          XSTRING* string = new XSTRING();
          if(string) 
            {
              vt->SetValueString(string);
              vt->SetHaveReservedSize(true);
            }
        } 

      globalvars.Add(vt);

      GetToken();

    } while(currenttoken[0] == __C(','));

  if(currenttoken[0] != __C(';'))  
    {
      HaveError(SCRIPT_LNG_G_ERRORCODE_SEMI_EXPECTED);
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SCRIPT_LNG_G::DeclareLocalVariable()
* @brief      DeclareLocalVariable
* @ingroup    SCRIPT
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LNG_G::DeclareLocalVariable()
{
  SCRIPT_LNG_G_TOKENIREPS vartype;
  SCRIPT_LNG_G_VAR*       vt;

  GetToken();

  vartype = tokenireps;

  do{ GetToken();

      if(!localvarsstack.IsEmpty())
        {
          for(int c=localvarsstack.GetSize()-1; c>=nestscopestack.GetLast(); c--)
            {
              SCRIPT_LNG_G_VAR* var = (SCRIPT_LNG_G_VAR*)localvarsstack.Get(c);

              if(var)
                {
                  if(!var->GetName()->Compare(currenttoken))
                    {
                      HaveError(SCRIPT_LNG_G_ERRORCODE_DUP_VAR);
                      return;
                    }
                }
            }
          }

      vt = new SCRIPT_LNG_G_VAR();
      if(!vt) 
        {
          return;
        }

      vt->SetType(vartype);        
      vt->SetName(currenttoken);
      vt->SetHaveReservedSize(false);

      if((vartype==SCRIPT_LNG_G_TOKENIREPS_STRING)&&(!vt->GetValueString()))
        {
          XSTRING* string = new XSTRING();
          if(string) 
            {
              vt->SetValueString(string);
              vt->SetHaveReservedSize(true);
            }
        }

      localvarsstack.Add(vt);

      GetToken();

    } while(currenttoken[0] == __C(','));

  if(currenttoken[0] != __C(';'))
    {
      HaveError(SCRIPT_LNG_G_ERRORCODE_SEMI_EXPECTED);      
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         SCRIPT_LNG_G_TOKENTYPES SCRIPT_LNG_G::GetToken()
* @brief      GetToken
* @ingroup    SCRIPT
* 
* @return     SCRIPT_LNG_G_TOKENTYPES : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
SCRIPT_LNG_G_TOKENTYPES SCRIPT_LNG_G::GetToken()
{
  XCHAR*    temptoken;   
  XSTRING   dobleops;
  XSTRING   delimiters;  
  XSTRING   otherdelimiters;

  dobleops        = __L("!<>=+-");
  delimiters      = __L("{}");  
  otherdelimiters = __L("+-*^/%=;:(),'");

  tokentype       = SCRIPT_LNG_G_TOKENTYPES_UNDEFTT;
  tokenireps      = SCRIPT_LNG_G_TOKENIREPS_UNDEFTOK;

  temptoken       = currenttoken;
  (*temptoken)    = __C('\0');

  // Skip over white space.
  while(IsSpace(*ipprg) && (*ipprg))
    {
      ++ipprg;
    }

  // Skip over newline.
  while((*ipprg) == __C('\r'))
    {
      ++ipprg;
      ++ipprg;

      // Again, skip over white space.
      while(IsSpace(*ipprg) && (*ipprg))
        {
          ++ipprg;
        }
    }

  // Check for end of ipprgram.
  if((*ipprg) == __C('\0'))
    {
      currenttoken[0]   = __C('\0');
      tokenireps        = SCRIPT_LNG_G_TOKENIREPS_END;

      return (tokentype = SCRIPT_LNG_G_TOKENTYPES_DELIMITER);
    }

  // Check for block delimiters.
  if(delimiters.FindCharacter(*ipprg)!=XSTRING_NOTFOUND)
    {
      (*temptoken) = (*ipprg);
      temptoken++;

      (*temptoken) = __C('\0');
      ipprg++;

      return (tokentype = SCRIPT_LNG_G_TOKENTYPES_BLOCK);
    }

  // Look for comments.
  if((*ipprg) == __C('/'))
    {
      if(*(ipprg + 1) == __C('*'))
        { // is a /* comment
          ipprg += 2;

          do{ // find end of comment
              while((*ipprg) != __C('*')) 
                {
                  ipprg++;
                }
              ipprg++;

            } while ((*ipprg) != __C('/'));

          ipprg++;

          return (tokentype = SCRIPT_LNG_G_TOKENTYPES_DELIMITER);
        }
       else
        {
          if(*(ipprg+1) == '/')
            {
              // is a // comment
              ipprg += 2;
              // Find end of comment.
              while(((*ipprg) != __C('\r')) && ((*ipprg) != __C('\0'))) 
                {
                  ipprg++;
                }

              if((*ipprg) == __C('\r')) 
                {
                  ipprg +=2;
                }

              return (tokentype = SCRIPT_LNG_G_TOKENTYPES_DELIMITER);
            }
        }
    }

  // Check for double-ops.
  if(dobleops.FindCharacter((*ipprg))!=XSTRING_NOTFOUND)
    {
      switch((*ipprg))
        {
          case '=': if(*(ipprg+1) == __C('='))
                      {
                        ipprg++; 
                        ipprg++;

                        (*temptoken) = SCRIPT_LNG_G_DOUBLEOPERATOR_EQ;
                        temptoken++;

                        (*temptoken) = SCRIPT_LNG_G_DOUBLEOPERATOR_EQ;
                        temptoken++;

                        (*temptoken) = __C('\0');
                      }
                    break;

          case '!': if(*(ipprg+1) == __C('='))
                      {
                        ipprg++; 
                        ipprg++;

                        (*temptoken) = SCRIPT_LNG_G_DOUBLEOPERATOR_NE;
                        temptoken++;

                        (*temptoken) = SCRIPT_LNG_G_DOUBLEOPERATOR_NE;
                        temptoken++;

                        (*temptoken) = __C('\0');
                      }
                    break;

          case '<': if(*(ipprg+1) == __C('='))
                      {
                        ipprg++; 
                        ipprg++;

                        (*temptoken) = SCRIPT_LNG_G_DOUBLEOPERATOR_LE;
                        temptoken++;

                        (*temptoken) = SCRIPT_LNG_G_DOUBLEOPERATOR_LE;
                      }
                     else
                      {
                        if(*(ipprg+1) == __C('<'))
                          {
                            ipprg++; 
                            ipprg++;

                            (*temptoken) = SCRIPT_LNG_G_DOUBLEOPERATOR_LS;
                            temptoken++;

                            (*temptoken) = SCRIPT_LNG_G_DOUBLEOPERATOR_LS;
                          }
                         else
                          {
                            ipprg++;
                            (*temptoken) = SCRIPT_LNG_G_DOUBLEOPERATOR_LT;
                          }
                      }

                    temptoken++;
                    *temptoken = __C('\0');
                    break;

          case '>': if(*(ipprg+1) == __C('='))
                      {
                        ipprg++; 
                        ipprg++;

                        (*temptoken) = SCRIPT_LNG_G_DOUBLEOPERATOR_GE;
                        temptoken++;

                        (*temptoken) = SCRIPT_LNG_G_DOUBLEOPERATOR_GE;
                      }
                     else
                      {
                        if(*(ipprg+1) == __C('>'))
                          {
                            ipprg++; 
                            ipprg++;

                            (*temptoken) = SCRIPT_LNG_G_DOUBLEOPERATOR_RS;
                            temptoken++;

                            (*temptoken) = SCRIPT_LNG_G_DOUBLEOPERATOR_RS;
                          }
                          else
                          {
                            ipprg++;
                            (*temptoken) = SCRIPT_LNG_G_DOUBLEOPERATOR_GT;
                          }
                      }
                     temptoken++;
                     (*temptoken) = __C('\0');
                    break;

          case '+': if(*(ipprg+1) == __C('+'))
                      {
                        ipprg++;
                        ipprg++;

                        (*temptoken) = SCRIPT_LNG_G_DOUBLEOPERATOR_INC;
                        temptoken++;

                        (*temptoken) = SCRIPT_LNG_G_DOUBLEOPERATOR_INC;
                        temptoken++;

                        (*temptoken) = __C('\0');
                      }
                    break;

          case '-': if(*(ipprg+1) == __C('-'))
                      {
                        ipprg++;
                        ipprg++;

                        (*temptoken) = SCRIPT_LNG_G_DOUBLEOPERATOR_DEC;
                        temptoken++;

                        (*temptoken) = SCRIPT_LNG_G_DOUBLEOPERATOR_DEC;
                        temptoken++;

                        (*temptoken) = '\0';
                      }
                    break;
        }

      if(currenttoken[0]) return(tokentype = SCRIPT_LNG_G_TOKENTYPES_DELIMITER);
    }

  // Check for other delimiters.
  if(otherdelimiters.FindCharacter((*ipprg))!=XSTRING_NOTFOUND)
    {
      (*temptoken) = (*ipprg);
      ipprg++;
      temptoken++;
      (*temptoken) = '\0';

      return (tokentype = SCRIPT_LNG_G_TOKENTYPES_DELIMITER);
    }

  // Read a quoted string.
  if((*ipprg) == __C('"'))
    {
      ipprg++;

      while(((*ipprg) != __C('"')) && ((*ipprg)!=__C('\r')) && (*ipprg))
        {
          // Check for \r escape sequence.
          if((*ipprg) == __C('\\'))
            {
              if(*(ipprg+1) == __C('n'))
                {
                  ipprg++;
                  (*temptoken++) = __C('\n');
                }
               else
                {
                  if(*(ipprg+1) == __C('r'))
                    {
                      ipprg++;
                      (*temptoken++) = __C('\r');
                    }
                   else
                    {
                      if(*(ipprg+1) == '\\')
                        {
                          ipprg++;
                          (*temptoken++) = __C('\\');
                        }
                    }
                }
            }
           else
            {
              if((temptoken - currenttoken) < SCRIPT_LNG_G_MAXTOKENLEN)  (*temptoken++) = (*ipprg);
            }

          ipprg++;
        }

        if((*ipprg) == __C('\r') || (*ipprg) == 0)
          {
            HaveError(SCRIPT_LNG_G_ERRORCODE_SYNTAX);
            return tokentype;
          }

      ipprg++;
      (*temptoken) = '\0';

      return (tokentype = SCRIPT_LNG_G_TOKENTYPES_STRING);
    }

  // Read an integer number.
  if(IsDigit((*ipprg)))
    {
      while(!IsDelimiter((*ipprg)))
        {
          if((temptoken - currenttoken) < SCRIPT_LNG_G_MAXIDLEN)  (*temptoken++) = (*ipprg);
          ipprg++;
        }
      (*temptoken) = __C('\0');

      return (tokentype = SCRIPT_LNG_G_TOKENTYPES_NUMBER);
    }

  // Read identifier or keyword.
  if(IsAlpha((*ipprg)))
    {
      while(!IsDelimiter((*ipprg)) && ((*ipprg)!=__C('{')) && ((*ipprg)!=__C('}')))
        {
          if((temptoken - currenttoken) < SCRIPT_LNG_G_MAXIDLEN) (*temptoken++) = (*ipprg);
          ipprg++;
        }

      tokentype = SCRIPT_LNG_G_TOKENTYPES_TEMP;
    }

  (*temptoken) = __C('\0');

  // Determine if token is a keyword or identifier.
  if(tokentype == SCRIPT_LNG_G_TOKENTYPES_TEMP)
    {
      tokenireps = LookUpToken(currenttoken); // convert to internal form

      if(tokenireps)
             tokentype = SCRIPT_LNG_G_TOKENTYPES_KEYWORD; // is a keyword
        else tokentype = SCRIPT_LNG_G_TOKENTYPES_IDENTIFIER;
    }

  // Check for unidentified XCHARacter in file.
  if(tokentype == SCRIPT_LNG_G_TOKENTYPES_UNDEFTT)
    {
      HaveError(SCRIPT_LNG_G_ERRORCODE_SYNTAX);
    }

  return tokentype;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SCRIPT_LNG_G::PreScan()
* @brief      PreScan
* @ingroup    SCRIPT
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LNG_G::PreScan()
{
  XCHAR*                      position;
  XCHAR*                      tempposition;
  SCRIPT_LNG_G_TOKENIREPS     datatype;
  SCRIPT_LNG_G_FUNCTIONTYPE*  functiontype;
  XSTRING                     temptoken;
  int                         brace = 0;

  position = ipprg;

  do{ while(brace)
        {
          GetToken();

          if((iscancelexec) || (errorcode != SCRIPT_ERRORCODE_NONE))
            {
              break;
            }
          
          if(tokenireps == SCRIPT_LNG_G_TOKENIREPS_END)
            {
              HaveError(SCRIPT_LNG_G_ERRORCODE_UNBAL_BRACES);
              return;
            }

          if(currenttoken[0] == __C('{')) brace++;
          if(currenttoken[0] == __C('}')) brace--;
        }

      if((iscancelexec) || (errorcode != SCRIPT_ERRORCODE_NONE))
        {
          break;
        }

      tempposition = ipprg;

      GetToken(); 
      
      if((iscancelexec) || (errorcode != SCRIPT_ERRORCODE_NONE))
        {
          break;
        }

      if(tokenireps == SCRIPT_LNG_G_TOKENIREPS_CHAR || tokenireps == SCRIPT_LNG_G_TOKENIREPS_INT || tokenireps == SCRIPT_LNG_G_TOKENIREPS_STRING)
        {
          datatype = tokenireps;

          GetToken();
          
          if(tokentype == SCRIPT_LNG_G_TOKENTYPES_IDENTIFIER)
            {
              temptoken = currenttoken;

              GetToken();
              
              if((iscancelexec) || (errorcode != SCRIPT_ERRORCODE_NONE))
                {
                  break;
                }

              if(currenttoken[0] != __C('('))
                {
                  ipprg = tempposition;
                  DeclareGlobalVariable();
                }
               else
                {
                  if(currenttoken[0] == __C('('))
                    {
                      functiontype = new SCRIPT_LNG_G_FUNCTIONTYPE();
                      if(!functiontype) return;

                      for(int c=0;c<(int)functiontable.GetSize();c++)
                        {
                          SCRIPT_LNG_G_FUNCTIONTYPE* functiontype = (SCRIPT_LNG_G_FUNCTIONTYPE*)functiontable.Get(c);

                          if(!functiontype->GetName()->Compare(temptoken))
                            {
                              HaveError(SCRIPT_LNG_G_ERRORCODE_DUP_FUNC);
                              return;
                            }
                        }

                      functiontype->SetLocation(ipprg);
                      functiontype->SetReturnType(datatype);
                      functiontype->SetName(temptoken.Get());

                      functiontable.Add(functiontype);

                      do{ GetToken();
                          
                          if((iscancelexec) || (errorcode != SCRIPT_ERRORCODE_NONE))
                            {
                              break;
                            }

                        } while(currenttoken[0] != __C(')'));

                    } else PutBackToken();
                }
            }
        }
       else
        {
          if(currenttoken[0] == __C('{')) brace++;
          if(currenttoken[0] == __C('}')) brace--;
        }

      if(iscancelexec) break;
      if(errorcode != SCRIPT_ERRORCODE_NONE) break;   

    } while(tokenireps != SCRIPT_LNG_G_TOKENIREPS_END);

  if((brace) && (errorcode == SCRIPT_ERRORCODE_NONE))
    {
      HaveError(SCRIPT_LNG_G_ERRORCODE_UNBAL_BRACES);
      return;
    }

  ipprg = position;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SCRIPT_LNG_G::GetArgs()
* @brief      GetArgs
* @ingroup    SCRIPT
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LNG_G::GetArgs()
{
  SCRIPT_LNG_G_VAR* values[SCRIPT_LNG_G_NUMPARAMS];
  SCRIPT_LNG_G_VAR* value = NULL;
  int        count;

  for(int c=0;c<SCRIPT_LNG_G_NUMPARAMS;c++)
    {
      values[c] = NULL;
    }

  count = 0;

  GetToken();

  if(*currenttoken != '(')
    {
      HaveError(SCRIPT_LNG_G_ERRORCODE_PAREN_EXPECTED);
      return;
    }

  // Process a comma-separated list of values.
  do{ value = new SCRIPT_LNG_G_VAR();
      if(!value) break;

      EvalExp((*value));
      values[count] = value; // save temporarily

      GetToken();
      count++;

    } while(*currenttoken == ',');

  count--;

  // Now, push on local_var_stack in reverse order.
  for(; count>=0; count--)
    {
      value = values[count];
      if(value)
        {
          value->SetIsArg(true);

          localvarsstack.Add(value);
        }
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SCRIPT_LNG_G::GetParams()
* @brief      GetParams
* @ingroup    SCRIPT
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LNG_G::GetParams()
{
  SCRIPT_LNG_G_VAR* var;
  int        indexstack;

  indexstack = localvarsstack.GetSize()-1;

  // Process comma-separated list of parameters.
  do{
      GetToken();

      var = (SCRIPT_LNG_G_VAR*)localvarsstack.Get(indexstack);

      if(currenttoken[0] != __C(')') )
        {
          if(tokenireps != SCRIPT_LNG_G_TOKENIREPS_INT   &&
             tokenireps != SCRIPT_LNG_G_TOKENIREPS_CHAR  &&
             tokenireps != SCRIPT_LNG_G_TOKENIREPS_STRING)
          {
            HaveError(SCRIPT_LNG_G_ERRORCODE_TYPE_EXPECTED);
            return;
          }

          var->SetType(tokenireps);
          var->SetHaveReservedSize(false);
          if(tokenireps == SCRIPT_LNG_G_TOKENIREPS_STRING)
            {
              var->SetHaveReservedSize(true);            
            }

          GetToken();

          var->SetName(currenttoken);
          
          GetToken();

          indexstack--;
        }
       else break;

    } while(currenttoken[0] == __C(','));

  if(currenttoken[0] != __C(')'))
    {
      HaveError(SCRIPT_LNG_G_ERRORCODE_PAREN_EXPECTED);
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SCRIPT_LNG_G::FunctionReturn()
* @brief      FunctionReturn
* @ingroup    SCRIPT
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LNG_G::FunctionReturn()
{
  SCRIPT_LNG_G_VAR value;

  value.Clear();

  SCRIPT_LNG_G_FUNCTIONTYPE* function = GetFunction(currentfunction);

  EvalExp(value);

  value.SetHaveReservedSize(false);

  if(!function)
    {
      return;
    }
  
  if(function->GetReturnType() == SCRIPT_LNG_G_TOKENIREPS_STRING)
    {
      returnvalue.SetType(SCRIPT_LNG_G_TOKENIREPS_STRING);
      returnvalue.SetValueString(value.GetValueString());
      returnvalue.SetHaveReservedSize(true);
    }
   else
    {
      returnvalue.SetType(SCRIPT_LNG_G_TOKENIREPS_INT);
      returnvalue.SetValueInteger(value.GetValueInteger());
    } 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SCRIPT_LNG_G::Exec_IF()
* @brief      Exec_IF
* @ingroup    SCRIPT
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LNG_G::Exec_IF()
{
  SCRIPT_LNG_G_VAR cond;

  cond.Clear();

  EvalExp(cond);

  if(cond.GetValueInteger())
    {
      if(currenttoken[0] != __C('{'))
        {
          HaveError(SCRIPT_LNG_G_ERRORCODE_BRACE_EXPECTED);
          return;
        }

      Interpret();
    }
   else
    {
      FindEndofBlock(); // find start of next line
      GetToken();

      if(tokenireps != SCRIPT_LNG_G_TOKENIREPS_ELSE)
        {
          PutBackToken();
          return;
        }

      GetToken();

      if(currenttoken[0] != __C('{'))
        {
          HaveError(SCRIPT_LNG_G_ERRORCODE_BRACE_EXPECTED);
          return;
        }

      PutBackToken();

      Interpret();
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void SCRIPT_LNG_G::Exec_SWITCH()
* @brief      Exec_SWITCH
* @ingroup    SCRIPT
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LNG_G::Exec_SWITCH()
{
  SCRIPT_LNG_G_VAR sval;
  SCRIPT_LNG_G_VAR cval;
  int       brace;

  EvalExp(sval);

  if(currenttoken[0] != __C('{'))
    {
      HaveError(SCRIPT_LNG_G_ERRORCODE_BRACE_EXPECTED);
      return;
    }

  nestscopestack.Add(localvarsstack.GetSize());

  for(;;)
    {
      brace = 1;

      do { GetToken();

           if(currenttoken[0] == '{')
                   brace++;
              else if(currenttoken[0] == '}') brace--;

         } while(tokenireps != SCRIPT_LNG_G_TOKENIREPS_CASE && tokenireps != SCRIPT_LNG_G_TOKENIREPS_END && brace);

      if(!brace) break;

      if(tokenireps == SCRIPT_LNG_G_TOKENIREPS_END)
        {
          HaveError(SCRIPT_LNG_G_ERRORCODE_SYNTAX);
          return;
        }

      EvalExp(cval);

      GetToken();

      if(currenttoken[0] != __C(':'))
        {
          HaveError(SCRIPT_LNG_G_ERRORCODE_COLON_EXPECTED);
          return;
        }

      if(cval.GetValueInteger() == sval.GetValueInteger())
        {
          brace = 1;

          do{ Interpret();

              if(currenttoken[0] == __C('{'))
                    brace++;
               else if(currenttoken[0] == __C('}')) brace--;

            } while(!breakfound && tokenireps != SCRIPT_LNG_G_TOKENIREPS_END && brace);

          while(brace)
            {
              GetToken();

              if(currenttoken[0] == __C('{'))
                     brace++;
                else if(currenttoken[0] == __C('}')) brace--;
            }

          breakfound = false;

          break;
        }
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPT_LNG_G::Exec_WHILE()
* @brief      Exec_WHILE
* @ingroup    SCRIPT
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LNG_G::Exec_WHILE()
{
  SCRIPT_LNG_G_VAR cond;
  XCHAR*        templocation;

  PutBackToken();

  templocation = ipprg;

  GetToken();

  EvalExp(cond);

  if(currenttoken[0] != __C('{'))
    {
      HaveError(SCRIPT_LNG_G_ERRORCODE_BRACE_EXPECTED);
      return;
    }

  if(cond.GetValueInteger())
    {
      Interpret();
    }
   else
    {
      FindEndofBlock();
      return;
    }

  ipprg = templocation;

  if(breakfound)
    {
      do { GetToken();

         } while((currenttoken[0] != __C('{')) && (tokenireps != SCRIPT_LNG_G_TOKENIREPS_END));

      PutBackToken();

      breakfound = false;

      FindEndofBlock();

      return;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPT_LNG_G::Exec_DO()
* @brief      Exec_DO
* @ingroup    SCRIPT
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LNG_G::Exec_DO()
{
  SCRIPT_LNG_G_VAR  cond;
  XCHAR*        templocation;

  PutBackToken();

  templocation = ipprg;

  GetToken();
  GetToken();

  if(currenttoken[0] != __C('{'))
    {
      HaveError(SCRIPT_LNG_G_ERRORCODE_BRACE_EXPECTED);
      return;
    }

  PutBackToken();

  Interpret();

  if(breakfound)
    {
      ipprg = templocation;

      do{ GetToken();

        } while((currenttoken[0] != __C('{')) && (tokenireps != SCRIPT_LNG_G_TOKENIREPS_END));

      PutBackToken();

      FindEndofBlock();

      do{ GetToken();

        } while((currenttoken[0] != __C(';')) && (tokenireps != SCRIPT_LNG_G_TOKENIREPS_END));

      if(tokenireps == SCRIPT_LNG_G_TOKENIREPS_END)
        {
          HaveError(SCRIPT_LNG_G_ERRORCODE_SYNTAX);
          return;
        }

      breakfound = false;
      return;
    }

  GetToken();

  if(tokenireps != SCRIPT_LNG_G_TOKENIREPS_WHILE)
    {
      HaveError(SCRIPT_LNG_G_ERRORCODE_WHILE_EXPECTED);
      return;
    }

  EvalExp(cond);

  if(cond.GetValueInteger()) ipprg = templocation;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPT_LNG_G::Exec_FOR()
* @brief      Exec_FOR
* @ingroup    SCRIPT
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LNG_G::Exec_FOR()
{
  SCRIPT_LNG_G_VAR cond;
  XCHAR*        templocation;
  XCHAR*        templocation2;
  int           parent;

  GetToken();

  EvalExp(cond);

  if(currenttoken[0] != __C(';'))
    {
      HaveError(SCRIPT_LNG_G_ERRORCODE_SEMI_EXPECTED);
      return;
    }

  ipprg++;

  templocation = ipprg;

  for(;;)
    {

      EvalExp(cond);
      if(currenttoken[0] != __C(';'))
        {
          HaveError(SCRIPT_LNG_G_ERRORCODE_SEMI_EXPECTED);
          return;
        }

      ipprg++;
      templocation2 = ipprg;

      parent = 1;
      while(parent)
        {
          GetToken();

          if(currenttoken[0] == __C('(')) parent++;
          if(currenttoken[0] == __C(')')) parent--;
        }

      GetToken();

      if(currenttoken[0] != __C('{'))
        {
          HaveError(SCRIPT_LNG_G_ERRORCODE_BRACE_EXPECTED);
          return;
        }

      PutBackToken();

      if(cond.GetValueInteger())
        {
          Interpret();
        }
       else
        {
          FindEndofBlock();
          return;
        }

      ipprg = templocation2;

      if(breakfound)
        {
          do{ GetToken();

            } while(currenttoken[0] != '{' && tokenireps!= SCRIPT_LNG_G_TOKENIREPS_END);

          PutBackToken();

          breakfound = false;

          FindEndofBlock();
          return;
        }


      EvalExp(cond);

      ipprg = templocation;
    }
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool SCRIPT_LNG_G::Interpret()
* @brief      Interpret
* @ingroup    SCRIPT
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool SCRIPT_LNG_G::Interpret()
{
  SCRIPT_LNG_G_VAR value;
  int          block = 0;

  do{ if(iscancelexec)
        {
          HaveError(SCRIPT_LNG_G_ERRORCODE_USERBREAK);
          return false;
        }

      if(errorcode!=SCRIPT_ERRORCODE_NONE) return false;

      if(breakfound)  return false;
      if(returnfound) return true;

      tokentype = GetToken();

      if(tokentype == SCRIPT_LNG_G_TOKENTYPES_IDENTIFIER || currenttoken[0] == SCRIPT_LNG_G_DOUBLEOPERATOR_INC || currenttoken[0] == SCRIPT_LNG_G_DOUBLEOPERATOR_DEC)
        {
          value.Clear();

          PutBackToken();

          EvalExp(value);
      
          if(currenttoken[0] != ';')
            {
              HaveError(SCRIPT_LNG_G_ERRORCODE_SEMI_EXPECTED);
              return false;
            }
        }
       else
         if(tokentype==SCRIPT_LNG_G_TOKENTYPES_BLOCK)
          {
            if(currenttoken[0] == '{')
              {
                block = 1;
                nestscopestack.Add(localvarsstack.GetSize());
              }
             else
              {
                localvarsstack.ResizeContents(nestscopestack.GetLast());
                nestscopestack.DeleteLast();

                return false;
              }
          }
         else // is keyword
          {
            switch(tokenireps)
              {
                case SCRIPT_LNG_G_TOKENIREPS_CHAR   :
                case SCRIPT_LNG_G_TOKENIREPS_INT    :
                case SCRIPT_LNG_G_TOKENIREPS_STRING : PutBackToken();
                                                      DeclareLocalVariable();
                                                      break;

                case SCRIPT_LNG_G_TOKENIREPS_RETURN : FunctionReturn();
                                                      returnfound = true;
                                                      return true;

                case SCRIPT_LNG_G_TOKENIREPS_IF     : Exec_IF();
                                                      break;

                case SCRIPT_LNG_G_TOKENIREPS_ELSE   : FindEndofBlock();
                                                      break;

                case SCRIPT_LNG_G_TOKENIREPS_WHILE  : Exec_WHILE();
                                                      break;

                case SCRIPT_LNG_G_TOKENIREPS_DO     : Exec_DO();
                                                      break;

                case SCRIPT_LNG_G_TOKENIREPS_FOR    : // process a for loop
                                                      Exec_FOR();
                                                      break;

                case SCRIPT_LNG_G_TOKENIREPS_BREAK  : breakfound = true;

                                                      localvarsstack.ResizeContents(nestscopestack.GetLast());
                                                      nestscopestack.DeleteLast();

                                                      return false;

                case SCRIPT_LNG_G_TOKENIREPS_SWITCH : Exec_SWITCH();
                                                      break;

                case SCRIPT_LNG_G_TOKENIREPS_END    : break;


              }
          }

      if(returnfound) return true;

    } while (tokenireps != SCRIPT_LNG_G_TOKENIREPS_END && block);

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPT_LNG_G::Call()
* @brief      Call
* @ingroup    SCRIPT
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LNG_G::Call()
{
  XCHAR* location;
  XCHAR* templocation;
  int    localvarstacksize;

  location = FindFunction(currenttoken);
  if(!location)
    {
      HaveError(SCRIPT_LNG_G_ERRORCODE_FUNC_UNDEF);
      return;
    }
  else
    {
      XSTRING::Set(currentfunction,currenttoken);

      localvarstacksize = localvarsstack.GetSize();

      GetArgs();
      templocation = ipprg;

      functioncallstack.Add(localvarstacksize);

      ipprg = location;

      GetParams();

      returnfound = false;

      Interpret();

      returnfound = false;

      ipprg = templocation;

      if(functioncallstack.IsEmpty())
        {
          HaveError(SCRIPT_LNG_G_ERRORCODE_RET_NOCALL);
          return;
        }

      localvarsstack.ResizeContents(functioncallstack.GetLast());

      functioncallstack.DeleteLast();
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPT_LNG_G::ThreadFunction(void* data)
* @brief      ThreadFunction
* @ingroup    SCRIPT
*
* @param[in]  data :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LNG_G::ThreadFunction(void* data)
{
  SCRIPT_LNG_G* script = (SCRIPT_LNG_G*)data;
  if(!script) return;

  int returnvaluescript;

  script->SetErrorScript(script->Run(&returnvaluescript));

  script->SetReturnValueScript(returnvaluescript);

  script->GetThread()->Run(false);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void SCRIPT_LNG_G::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    SCRIPT
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void SCRIPT_LNG_G::Clean()
{
  returnvaluescript   = 0;

  ipprg               = NULL;

  iscancelexec        = false;

  tokentype           = SCRIPT_LNG_G_TOKENTYPES_UNDEFTT;
  tokenireps          = SCRIPT_LNG_G_TOKENIREPS_UNDEFTOK;

  returnfound         = false;
  breakfound          = false;

  int c;

  for(c=0;c<SCRIPT_LNG_G_MAXTOKENLEN+1;c++)
    {
      currenttoken[c] = 0;
    }

  for(c=0;c<_MAXSTR;c++)
    {
      currentfunction[c] = 0;
    }

  returnvalue.SetValueInteger(0);
}


#pragma endregion


