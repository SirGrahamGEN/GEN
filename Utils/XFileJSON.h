/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XFileJSON.h
*
* @class      XFILEJSON
* @brief      eXtended JSON (JavaScript Object Notation) file class
* @ingroup    UTILS
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

#ifndef _XFILEJSON_H_
#define _XFILEJSON_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XBase.h"
#include "XVector.h"
#include "XString.h"
#include "XFileTXT.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum XFILEJSONVALUETYPE
{
  XFILEJSONVALUETYPE_UNKNOWN          =  0 ,
  XFILEJSONVALUETYPE_NUMBER               ,
  XFILEJSONVALUETYPE_NUMBERSPECIAL        ,
  XFILEJSONVALUETYPE_STRING               ,
  XFILEJSONVALUETYPE_OBJECT               ,
  XFILEJSONVALUETYPE_ARRAY                ,
  XFILEJSONVALUETYPE_BOOLEAN              ,
  XFILEJSONVALUETYPE_NULL                 ,
};


enum XFILEJSONCONTROLCHAR
{
  XFILEJSONCONTROLCHAR_NOTCONTROL         , // All other Not control or number
  XFILEJSONCONTROLCHAR_OPENBRACE          , // {
  XFILEJSONCONTROLCHAR_CLOSEBRACE         , // }
  XFILEJSONCONTROLCHAR_OPENBRACKET        , // [
  XFILEJSONCONTROLCHAR_CLOSEBRACKET       , // ]
  XFILEJSONCONTROLCHAR_QUOTE              , // "
  XFILEJSONCONTROLCHAR_COMMA              , // ,
  XFILEJSONCONTROLCHAR_COLON              , // :
  XFILEJSONCONTROLCHAR_BLACKSLASH         , // (the other slash /)
  XFILEJSONCONTROLCHAR_NUMBER             , // '012345789' '-'
  XFILEJSONCONTROLCHAR_NUMBERSPECIAL      , //  '+' 'E' 'e' '.'
  XFILEJSONCONTROLCHAR_TEXT                 //  (All Chars except control,Space,TAB,Return o Line Feed).
};


#define XFILEJSON_SPACETABS                           2

#define XFILEJSON_ADDVALUE(node, name, value)           {  XFILEJSONVALUE* jsonvalue = new XFILEJSONVALUE();            \
                                                          if(jsonvalue)                                                 \
                                                            {                                                           \
                                                              jsonvalue->SetName(name);                                 \
                                                              jsonvalue->Set(value);                                    \
                                                              node->Add(jsonvalue);                                     \
                                                            }                                                           \
                                                        }

#define XFILEJSON_ADDVALUE_NULL(node, name)             {  XFILEJSONVALUE* jsonvalue = new XFILEJSONVALUE();            \
                                                          if(jsonvalue)                                                 \
                                                            {                                                           \
                                                              jsonvalue->SetName(name);                                 \
                                                              jsonvalue->Set();                                         \
                                                              node->Add(jsonvalue);                                     \
                                                            }                                                           \
                                                        }



union XFILEJSONVALUEDATA
{
    void*                       pointer;
    int                         integer;
    float                       floating;
    bool                        boolean;
};

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XFILEJSONOBJECT;
class XFILEJSONARRAY;


class XFILEJSONVALUE
{
  public:
                                XFILEJSONVALUE                ();
    virtual                    ~XFILEJSONVALUE                ();

    XFILEJSONVALUETYPE          GetType                       ();
    void                        SetType                       (XFILEJSONVALUETYPE type);
    
    XSTRING*                    GetName                       ();
    bool                        SetName                       (XSTRING& name);
    bool                        SetName                       (XCHAR* name);

    void*                       GetValuePointer               ();
    int                         GetValueInteger               ();
    float                       GetValueFloating              ();
    bool                        GetValueBoolean               ();
    XFILEJSONOBJECT*            GetValueObject                ();
    XFILEJSONARRAY*             GetValueArray                 ();

    bool                        Set                           (int number);
    bool                        Set                           (float number);
    bool                        Set                           (XSTRING& string);
    bool                        Set                           (XCHAR* string);
    bool                        Set                           (XFILEJSONOBJECT* object);
    bool                        Set                           (XFILEJSONARRAY* array);
    bool                        Set                           (bool boolean);
    bool                        Set                           (void);

    bool                        Delete                        ();

    XFILEJSONVALUE*             Clone                         ();                       

  private:

    void                        Clean                         ();

    XFILEJSONVALUETYPE          type;
    XSTRING*                    name;
    XFILEJSONVALUEDATA          value;
};



class XFILEJSONOBJECT
{
  public:
                                XFILEJSONOBJECT               ();
    virtual                    ~XFILEJSONOBJECT               ();

    bool                        IsArray                       ();
    void                        SetIsArray                    (bool isarray);

    bool                        Add                           (XFILEJSONVALUE* value);
    bool                        Add                           (XCHAR* name,XFILEJSONARRAY* array);
    bool                        Add                           (XSTRING& name,XFILEJSONARRAY* array);
    bool                        Add                           (XCHAR* name,XFILEJSONOBJECT* object);
    bool                        Add                           (XSTRING& name,XFILEJSONOBJECT* object);

    XVECTOR<XFILEJSONVALUE*>*   GetValues                     ();
    bool                        DeleteAllValues               ();

    XFILEJSONOBJECT*            Clone                         ();                       

  protected:

    bool                        isarray;
    XVECTOR<XFILEJSONVALUE*>    values;

  private:

    void                        Clean                         ();
};




class XFILEJSONARRAY  : public XFILEJSONOBJECT
{
  public:
                                XFILEJSONARRAY                ();
    virtual                    ~XFILEJSONARRAY                ();

    XSTRING*                    GetName                       ();
    bool                        SetName                       (XSTRING& name);
    bool                        SetName                       (XCHAR* name);

    XFILEJSONARRAY*             Clone                         (); 

  private:

    void                        Clean                         ();

    XSTRING                     name;
};




class XFILEJSON : public XFILETXT
{
  public:
                                XFILEJSON                     ();
    virtual                    ~XFILEJSON                     ();

    XFILEJSONOBJECT*            GetRoot                       ();
    bool                        SetRoot                       (XFILEJSONOBJECT* root);

    bool                        DecodeAllLines                ();
    bool                        EncodeAllLines                (bool istabulatedline = true);

    bool                        ReadAndDecodeAllLines         ();
    bool                        WriteAndEncodeAllLines        (bool istabulatedline, XFILETXTFORMATCHAR formatchar, XFILETXTTYPELF  typeLF = XFILETXTTYPELF_0D0A);
    bool                        WriteAndEncodeAllLines        (bool istabulatedline = true);

    bool                        DeleteAllObjects              ();

    XFILEJSONOBJECT*            GetObject                     (XCHAR* name, XFILEJSONOBJECT* startobject = NULL);
    XFILEJSONOBJECT*            GetObject                     (XSTRING& name, XFILEJSONOBJECT* startobject = NULL);

    XFILEJSONVALUE*             GetValue                      (XCHAR* name, XFILEJSONOBJECT* startobject = NULL);
    XFILEJSONVALUE*             GetValue                      (XSTRING& name, XFILEJSONOBJECT* startobject = NULL);
    XFILEJSONVALUE*             GetValue                      (int index, XFILEJSONOBJECT* startobject = NULL);


  private:



    XFILEJSONOBJECT*            GetObjectSubValue             (XCHAR* name, XFILEJSONVALUE* value);

    bool                        DecodeObject                  (int& position, bool isobject, XFILEJSONOBJECT* object);

    XFILEJSONCONTROLCHAR        CheckControlCharacter         (XCHAR character);
    XCHAR                       GetControlCharacter           (XFILEJSONCONTROLCHAR ctrlchar);
    bool                        AddControlCharacter           (XFILEJSONCONTROLCHAR ctrlchar, XSTRING& line);

    XFILEJSONCONTROLCHAR        SearchNextControlCharacter    (int& position);
    bool                        SearchControlCharacter        (XFILEJSONCONTROLCHAR ctrlchar,int& position);

    bool                        GetNumber                     (int& position, XSTRING& string,bool& special);
    bool                        GetText                       (int& position,XSTRING& string);
    bool                        GetString                     (int& position, XSTRING& string);

    bool                        AddTabs                       (int level, int spacetabs, XSTRING& string);

    bool                        EncodeObject                  (bool isobject, XFILEJSONOBJECT* object, bool istabulatedline = true);

    void                        Clean                         ();

    XFILEJSONOBJECT*            root;
    XSTRING                     all;
    int                         encodelevel;
};


/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif

