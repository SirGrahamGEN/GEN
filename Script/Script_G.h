/**-------------------------------------------------------------------------------------------------------------------
*
* @file       Script_G.h
*
* @class      SCRIPT_G
* @brief      Script G interpreter (G is mini cpp interpreter)
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

#ifndef _SCRIPT_G_H_
#define _SCRIPT_G_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XBase.h"
#include "XVector.h"
#include "XMap.h"
#include "XSubject.h"
#include "XString.h"
#include "XPath.h"
#include "XEvent.h"

#include "Script.h"
#include "Script_ErrorCode.h"


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum SCRIPT_G_TOKENTYPES
{
  SCRIPT_G_TOKENTYPES_UNDEFTT      ,
  SCRIPT_G_TOKENTYPES_DELIMITER    ,
  SCRIPT_G_TOKENTYPES_IDENTIFIER   ,
  SCRIPT_G_TOKENTYPES_NUMBER       ,
  SCRIPT_G_TOKENTYPES_KEYWORD      ,
  SCRIPT_G_TOKENTYPES_TEMP         ,
  SCRIPT_G_TOKENTYPES_STRING       ,
  SCRIPT_G_TOKENTYPES_BLOCK
};


enum SCRIPT_G_DOUBLEOPERATOR
{
  SCRIPT_G_DOUBLEOPERATOR_LT  = 1  ,
  SCRIPT_G_DOUBLEOPERATOR_LE       ,
  SCRIPT_G_DOUBLEOPERATOR_GT       ,
  SCRIPT_G_DOUBLEOPERATOR_GE       ,
  SCRIPT_G_DOUBLEOPERATOR_EQ       ,
  SCRIPT_G_DOUBLEOPERATOR_NE       ,
  SCRIPT_G_DOUBLEOPERATOR_LS       ,
  SCRIPT_G_DOUBLEOPERATOR_RS       ,
  SCRIPT_G_DOUBLEOPERATOR_INC      ,
  SCRIPT_G_DOUBLEOPERATOR_DEC
};


enum SCRIPT_G_TOKENIREPS
{
  SCRIPT_G_TOKENIREPS_UNDEFTOK     ,
  SCRIPT_G_TOKENIREPS_CHAR         ,
  SCRIPT_G_TOKENIREPS_INT          ,
  SCRIPT_G_TOKENIREPS_STRING       ,
  SCRIPT_G_TOKENIREPS_SWITCH       ,
  SCRIPT_G_TOKENIREPS_CASE         ,
  SCRIPT_G_TOKENIREPS_IF           ,
  SCRIPT_G_TOKENIREPS_ELSE         ,
  SCRIPT_G_TOKENIREPS_FOR          ,
  SCRIPT_G_TOKENIREPS_DO           ,
  SCRIPT_G_TOKENIREPS_WHILE        ,
  SCRIPT_G_TOKENIREPS_BREAK        ,
  SCRIPT_G_TOKENIREPS_RETURN       ,
  SCRIPT_G_TOKENIREPS_END
};



enum SCRIPT_G_ERRORCODE
{
  SCRIPT_G_ERRORCODE_SYNTAX         = SCRIPT_ERRORCODE_OWN  ,   // "Syntax error"
  SCRIPT_G_ERRORCODE_NO_EXP                                 ,   // "No expression present"
  SCRIPT_G_ERRORCODE_NOT_VAR                                ,   // "Not a variable"
  SCRIPT_G_ERRORCODE_DUP_VAR                                ,   // "Duplicate variable name"
  SCRIPT_G_ERRORCODE_DUP_FUNC                               ,   // "Duplicate function name"
  SCRIPT_G_ERRORCODE_SEMI_EXPECTED                          ,   // "Semicolon expected"
  SCRIPT_G_ERRORCODE_UNBAL_BRACES                           ,   // "Unbalanced braces"
  SCRIPT_G_ERRORCODE_FUNC_UNDEF                             ,   // "Function undefined"
  SCRIPT_G_ERRORCODE_TYPE_EXPECTED                          ,   // "Type specifier expected"
  SCRIPT_G_ERRORCODE_RET_NOCALL                             ,   // "Return without call"
  SCRIPT_G_ERRORCODE_PAREN_EXPECTED                         ,   // "Parentheses expected"
  SCRIPT_G_ERRORCODE_WHILE_EXPECTED                         ,   // "While expected"
  SCRIPT_G_ERRORCODE_QUOTE_EXPECTED                         ,   // "Closing quote expected"
  SCRIPT_G_ERRORCODE_DIV_BY_ZERO                            ,   // "Division by zero"
  SCRIPT_G_ERRORCODE_BRACE_EXPECTED                         ,   // "{ expected (control statements must use blocks)"
  SCRIPT_G_ERRORCODE_COLON_EXPECTED                         ,   // "Colon expected"
  SCRIPT_G_ERRORCODE_USERBREAK                                  // "Break by user"
};


union SCRIPT_G_VARVALUE
{
  int          integer;
  XCHAR        character;
  XDWORD       uinteger;
  XSTRING*     string;
};

#define SCRIPT_G_MAXIDLEN       31    // max ID     length
#define SCRIPT_G_MAXTOKENLEN   128    // max token  length
#define SCRIPT_G_NUMPARAMS      31    // max params lenght

#define SCRIPT_G_EXTENSION   __L(".g")


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/


class XTHREADCOLLECTED;
class SCRIPT_LIB;

class SCRIPT_G_COMMAND
{
  public:
                                        SCRIPT_G_COMMAND        ();
                                       ~SCRIPT_G_COMMAND        ();

    XSTRING*                            GetCommand              ();
    SCRIPT_G_TOKENIREPS                 GetToken                ();

    bool                                Set                     (XCHAR* command,SCRIPT_G_TOKENIREPS token);
    bool                                Set                     (XSTRING& command,SCRIPT_G_TOKENIREPS token);

  private:

    void                                Clean                   ();

    XSTRING                             command;
    SCRIPT_G_TOKENIREPS                 token;
};



class SCRIPT_G_FUNCTIONTYPE
{
  public:
                                        SCRIPT_G_FUNCTIONTYPE   ();
    virtual                            ~SCRIPT_G_FUNCTIONTYPE   ();

    XSTRING*                            GetName                 ();
    SCRIPT_G_TOKENIREPS                 GetReturnType           ();
    XCHAR*                              GetLocation             ();

    bool                                SetName                 (XCHAR* name);
    bool                                SetName                 (XSTRING& name);
    bool                                SetReturnType           (SCRIPT_G_TOKENIREPS returntype);
    bool                                SetLocation             (XCHAR* location);

  private:

    void                                Clean                   ();

    XSTRING                             name;
    SCRIPT_G_TOKENIREPS                 returntype;
    XCHAR*                              location;
};


class SCRIPT_G_VAR
{
  public:

                                        SCRIPT_G_VAR            ();
    virtual                            ~SCRIPT_G_VAR            ();

    XSTRING*                            GetName                 ();
    SCRIPT_G_TOKENIREPS                 GetType                 ();

    int                                 GetValueInteger         ();
    XCHAR                               GetValueCharacter       ();
    XDWORD                              GetValueUInteger        ();
    XSTRING*                            GetValueString          ();

    bool                                NotHaveReservedSize     ();
    bool                                IsArg                   ();
    bool                                IsReturnValue           ();

    bool                                Set                     (SCRIPT_G_VAR* var);

    bool                                SetName                 (XCHAR* name);
    bool                                SetType                 (SCRIPT_G_TOKENIREPS type);

    bool                                SetValueInteger         (int value);
    bool                                SetValueCharacter       (XCHAR value);
    bool                                SetValueUInteger        (XDWORD value);
    bool                                SetValueString          (XSTRING* value);
    bool                                SetValueString          ();

    bool                                SetNotHaveReservedSize  (bool nothavereservedsize);
    bool                                SetIsArg                (bool isarg);
    bool                                SetIsReturnValue        (bool isreturnvalue);

    bool                                ConvertToXVariant       (XVARIANT& variant);
    bool                                ConvertFromXVariant     (XVARIANT& variant);

    bool                                Clear                   ();

  private:

    void                                Clean                   ();

    XSTRING                             name;
    SCRIPT_G_TOKENIREPS                 type;
    SCRIPT_G_VARVALUE                   value;
    bool                                nothavereservedsize;
    bool                                isarg;
    bool                                isreturnvalue;
};




class SCRIPT_G : public SCRIPT
{
  public:
                                        SCRIPT_G                ();
    virtual                            ~SCRIPT_G                ();


   int                                  Run                     (int* returnval = NULL);

    bool                                AddCommand              (XCHAR* command, SCRIPT_G_TOKENIREPS  token);
    bool                                DeleteCommands          ();

    int                                 GetFuncParams           (SCRIPT_G_VAR* params);
    void                                NotFuncParams           ();

    int                                 GetReturnValueScript    ();
    int                                 SetReturnValueScript    (int returnvaluescript);

    bool                                HaveError               (int errorcode);


  private:

    bool                                DeleteVarsExec          ();

    bool                                IsSpace                 (XCHAR character);
    bool                                IsDigit                 (XCHAR character);
    bool                                IsAlpha                 (XCHAR character);

    bool                                IsDelimiter             (XCHAR  c);
    SCRIPT_G_TOKENIREPS                 LookUpToken             (XCHAR* s);
    void                                PutBackToken            ();

    void                                EvalExp                 (SCRIPT_G_VAR& value);
    void                                EvalExp0                (SCRIPT_G_VAR& value);
    void                                EvalExp1                (SCRIPT_G_VAR& value);
    void                                EvalExp2                (SCRIPT_G_VAR& value);
    void                                EvalExp3                (SCRIPT_G_VAR& value);
    void                                EvalExp4                (SCRIPT_G_VAR& value);
    void                                EvalExp5                (SCRIPT_G_VAR& value);
    void                                Atom                    (SCRIPT_G_VAR& value);

    SCRIPT_G_VAR*                       IsVariable              (XCHAR* variblename);
    void                                AssignVariable          (XCHAR* variablename, SCRIPT_G_VAR& value);
    SCRIPT_G_VAR*                       FindVariable            (XCHAR* variablename);
    SCRIPT_G_TOKENIREPS                 FindVariableType        (XCHAR* variablename);

    XCHAR*                              FindFunction            (XCHAR* name);
    SCRIPT_G_FUNCTIONTYPE*              GetFunction             (XCHAR* name);
    void                                FindEndofBlock          ();

    void                                DeclareGlobalVariable   ();
    void                                DeclareLocalVariable    ();

    SCRIPT_G_TOKENTYPES                 GetToken                ();

    void                                PreScan                 ();

    void                                GetArgs                 ();
    void                                GetParams               ();

    void                                FunctionReturn          ();

    void                                Exec_IF                 ();
    void                                Exec_SWITCH             ();
    void                                Exec_WHILE              ();
    void                                Exec_DO                 ();
    void                                Exec_FOR                ();

    bool                                Interpret               ();

    void                                Call                    ();

    static void                         ThreadFunction          (void* data);

    void                                Clean                   ();

    int                                 returnvaluescript;

    XCHAR*                              ipprg;

    XVECTOR<SCRIPT_G_COMMAND*>          commands;

    XVECTOR<SCRIPT_LIB*>                librarys;

    XVECTOR<SCRIPT_LIBFUNCTION*>        libraryfunctions;

    XVECTOR<SCRIPT_G_VAR*>              globalvars;
    XVECTOR<SCRIPT_G_FUNCTIONTYPE*>     functiontable;
    XVECTOR<SCRIPT_G_VAR*>              localvarsstack;
    XVECTOR<int>                        functioncallstack;
    XVECTOR<int>                        nestscopestack;

    SCRIPT_G_TOKENTYPES                 tokentype;
    SCRIPT_G_TOKENIREPS                 tokenireps;

    bool                                breakfound;
    bool                                returnfound;

    XCHAR                               currenttoken[SCRIPT_G_MAXTOKENLEN+1];
    XCHAR                               currentfunction[_MAXSTR];
    SCRIPT_G_VAR                        returnvalue;
};




/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif





