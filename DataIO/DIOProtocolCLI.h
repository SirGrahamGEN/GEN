/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOProtocolCLI.h
* 
* @class      DIOPROTOCOLCLI
* @brief      Data Input/Output protocol in CLI class
* @ingroup    DATAIO
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

#ifndef _DIOPROTOCOLCLI_H_
#define _DIOPROTOCOLCLI_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XString.h"
#include "XTimer.h"
#include "XFSMachine.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum DIOPROTOCOLCLI_ERROR
{
  DIOPROTOCOLCLI_ERROR_NONE                    = 0 ,
  DIOPROTOCOLCLI_ERROR_INTERNAL                    ,
  DIOPROTOCOLCLI_ERROR_INVALIDCOMMAND              ,
  DIOPROTOCOLCLI_ERROR_INVALIDPARAM                ,
  DIOPROTOCOLCLI_ERROR_INSUFFICIENTPARAMS          ,
  DIOPROTOCOLCLI_ERROR_ERROREXECCOMMAND            ,
  DIOPROTOCOLCLI_ERROR_TIMEOUT                     ,
  DIOPROTOCOLCLI_ERROR_WRITECMD                    ,
  DIOPROTOCOLCLI_ERROR_NOTANSWER                   ,
};


#define DIOPROTOCOLCLI_OK            __L("ok")
#define DIOPROTOCOLCLI_ERROR         __L("error")
#define DIOPROTOCOLCLI_ANSWER        __L("answer ")

#define DIOPROTOCOLCLI_TIMEOUT       5  //Seconds

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XFACTORY;
class DIOSTREAM;


class DIOPROTOCOLCLICOMMAND
{
  public:
                                          DIOPROTOCOLCLICOMMAND         ();
    virtual                              ~DIOPROTOCOLCLICOMMAND         ();
    
    XCHAR*                                GetCommand                    ();
    int                                   GetNParams                    ();
    bool                                  Set                           (XCHAR* command, int nparams);
                                          
  private:

    void                                  Clean                         ();
    
    XSTRING                               command;
    int                                   nparams;
};


class DIOPROTOCOLCLIANSWER
{
  public:
                                          DIOPROTOCOLCLIANSWER          ();                                       
    virtual                              ~DIOPROTOCOLCLIANSWER          ();                                        

    XSTRING*                              GetCommand                    ();
    XSTRING*                              GetAnswer                     ();

    void                                  Clean                         ();
                                          
    XSTRING                               command;
    XSTRING                               answer;
};


class DIOPROTOCOLCLI
{
  public:
                                          DIOPROTOCOLCLI                ();
    virtual                              ~DIOPROTOCOLCLI                ();

    virtual bool                          Ini                           (DIOSTREAM* diostream, int timeout = DIOPROTOCOLCLI_TIMEOUT);
    
    virtual bool                          SendCommand                   (XCHAR* command, XSTRING* answer, int timeoutanswer, ...);
    bool                                  SendCommand                   (XCHAR* command, XSTRING* answer, int timeoutanswer, va_list& arg);

    virtual bool                          ReceivedCommand               (XSTRING& command, XVECTOR<XSTRING*>& params, XSTRING& answer);    
    virtual void                          ReceivedAnswer                (XSTRING& answer);
    void                                  ReceivedCommandManager        ();

    bool                                  AddAnswer                     (XCHAR* command, XSTRING& answer);
    XSTRING*                              GetFirstAnswer                (XCHAR* command);
    bool                                  DeleteFirstAnswer             (XCHAR* command);
    bool                                  DeleteAllAnswers              ();

    virtual void                          End                           ();

  protected:

    bool                                  AddCommand                    (XCHAR* command, int nparams);
    DIOPROTOCOLCLICOMMAND*                GetCommand                    (XCHAR* command);
    bool                                  DeleteAllCommand              ();

    bool                                  ExtractParamsFromCommand      (XSTRING& stringreceived, XSTRING& command, XVECTOR<XSTRING*>& params);

  private:

    void                                  Clean                         ();
                                        
    DIOSTREAM*                            diostream;

    XTIMER*                               xtimerout;
    int                                   timeout;

    XVECTOR<DIOPROTOCOLCLICOMMAND*>       commands;

    XMUTEX*                               xmutexanswers;
    XVECTOR<DIOPROTOCOLCLIANSWER*>        answers;

    XSTRING                               laststringreceived;
};

/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif
