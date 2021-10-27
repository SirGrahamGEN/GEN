/**-------------------------------------------------------------------------------------------------------------------
*
* @file       Script_LibFunction.h
*
* @class      SCRIPT_LIBFUNCTION
* @brief      Script Library Function class
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

#ifndef _SCRIPT_LIBFUNCTION_H_
#define _SCRIPT_LIBFUNCTION_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XVector.h"
#include "XVariant.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/


class SCRIPT;
class SCRIPT_LIB;
class SCRIPT_LIBFUNCTION;

typedef void (*SCRFUNCIONLIBRARY) (SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue);

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class SCRIPT_LIBFUNCTION
{
  public:
                                        SCRIPT_LIBFUNCTION          (SCRIPT_LIB* library, XCHAR* name, SCRFUNCIONLIBRARY functionlibrary);
                                        SCRIPT_LIBFUNCTION          (SCRIPT_LIB* library, XSTRING& name, SCRFUNCIONLIBRARY functionlibrary);
    virtual                            ~SCRIPT_LIBFUNCTION          ();

    SCRIPT_LIB*                         GetLibrary                  ();
    bool                                SetLibrary                  (SCRIPT_LIB* library);

    XSTRING*                            GetName                     ();

    SCRFUNCIONLIBRARY                   GetFunctionLibrary          ();
    bool                                SetFunctionLibrary          (SCRFUNCIONLIBRARY functionlibrary);

  private:

    void                                Clean                       ();

    SCRIPT_LIB*                         library;
    XSTRING                             name;
    SCRFUNCIONLIBRARY                   functionlibrary;
};


/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif


