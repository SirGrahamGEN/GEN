/**-------------------------------------------------------------------------------------------------------------------
*
* @file       APPConsole.h
*
* @class      APPCONSOLE
* @brief      Application Console class
* @ingroup    APPLICATION
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

#ifndef _APPCONSOLE_H_
#define _APPCONSOLE_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XObserver.h"

#include "APPBase.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define APPCONSOLE_DEFAULTMESSAGEMASK                   __L("%-36s ... ")
#define APPCONSOLE_DEFAULTMESSAGEMASKWITHOUTPOINTS      __L("%-36s ")

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XTIMER;
class XCONSOLE;

class APPCONSOLE : public APPBASE, public XOBSERVER
{
  public:

                                  APPCONSOLE                  ();
    virtual                      ~APPCONSOLE                  ();

    bool                          Ini                         (XVECTOR<XSTRING*>* execparams);
  
    bool                          Show_Line                   (XSTRING& string, XSTRING& string2, int tab = 3, bool linefeed = true);
    bool                          Show_BlankLine              ();
    bool                          Show_LineDirect             (XSTRING& string, bool lf);
    bool                          Show_Header                 (bool separator);

    bool                          End                         ();

    bool                          PrintExitMessage_Active     (bool isprintexitmessageactive);
    virtual bool                  PrintExitMessage            (XSTRING& message);

  protected:

    XCONSOLE*                     console;

  private:

    void                          Clean                       ();

   bool                           isprintexitmessageactive;

};

/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif



