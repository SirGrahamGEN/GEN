/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOCLIClient.h
* 
* @class      DIOCLICLIENT
* @brief      Data Input/Output CLI (Command Line Interface) client class
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

#ifndef _DIOCLICLIENT_H_
#define _DIOCLICLIENT_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XFSMachine.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum DIOCLICLIENT_ERROR
{
  DIOCLICLIENT_ERROR_NONE                   = 0 ,
  DIOCLICLIENT_ERROR_INTERNAL                   ,
  DIOCLICLIENT_ERROR_INVALIDCOMMAND             ,
  DIOCLICLIENT_ERROR_INVALIDPARAM               ,
  DIOCLICLIENT_ERROR_INSUFFICIENTPARAMS         ,
  DIOCLICLIENT_ERROR_ERROREXECCOMMAND           ,
  DIOCLICLIENT_ERROR_TIMEOUT                    ,
  DIOCLICLIENT_ERROR_WRITECMD                   ,
  DIOCLICLIENT_ERROR_NOTANSWER                  ,
};


enum DIOCLICLIENT_XFSMEVENTS
{
  DIOCLICLIENT_XFSMEVENT_NONE               = 0 ,
  DIOCLICLIENT_XFSMEVENT_INICMD                 ,
  DIOCLICLIENT_XFSMEVENT_SENDCMD                ,
  DIOCLICLIENT_XFSMEVENT_RECEIVEDCMD            ,
  DIOCLICLIENT_XFSMEVENT_ENDCMD                 ,

  DIOCLICLIENT_LASTEVENT
};


enum DIOCLICLIENT_XFSMSTATES
{
  DIOCLICLIENT_XFSMSTATE_NONE               = 0 ,
  DIOCLICLIENT_XFSMSTATE_INICMD                 ,
  DIOCLICLIENT_XFSMSTATE_SENDCMD                ,
  DIOCLICLIENT_XFSMSTATE_RECEIVEDCMD            ,
  DIOCLICLIENT_XFSMSTATE_ENDCMD                 ,

  DIOCLICLIENT_LASTSTATE
};

#define DIOCLICLIENT_HEADLINEMAX    3
#define DIOCLICLIENT_TIMEOUT        5  //Seconds

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XFACTORY;
class DIOSTREAM;

class DIOCLICLIENTCOMMAND
{
  public:
                                    DIOCLICLIENTCOMMAND           ();
    virtual                        ~DIOCLICLIENTCOMMAND           ();

    int                             GetType                       ();
    XCHAR*                          GetCommand                    ();

    bool                            Set                           (int type, XCHAR* command);

    bool                            AddParam                      (XSTRING* param);
    XCHAR*                          GetParam                      (int index);
    int                             GetNParams                    ();
    bool                            DeleteAllParams               ();

    bool                            AddAnswer                     (XCHAR* answer);
    bool                            AddAnswer                     (XSTRING* answer);
    int                             GetNAnswers                   ();
    XSTRING*                        GetAnswer                     (int index);
    bool                            DeleteAllAnswers              ();

  private:

    void                            Clean                         ();

    int                             type;
    XSTRING                         command;
    XVECTOR<XSTRING*>               params;
    XVECTOR<XSTRING*>               answers;
};


class DIOCLICLIENT  : public XFSMACHINE
{
  public:
                                    DIOCLICLIENT                  (DIOSTREAM* diostream);
    virtual                        ~DIOCLICLIENT                  ();

    bool                            Ini                           (int timeout = DIOCLICLIENT_TIMEOUT);
    void                            End                           ();

  protected:

    bool                            AddCommand                    (int type, XCHAR* command);
    DIOCLICLIENTCOMMAND*            GetCommand                    (int type);
    bool                            DeleteAllCommand              ();

    bool                            GetAnswer                     (int type,int indexanswer,XSTRING& answerstring);
    bool                            ReadAnswerLF                  (XSTRING& answer,int timeout);
    bool                            ReadAnswer                    (XSTRING& answer,XDWORD size,int timeout);

    bool                            SendCommand                   (int type, int nparams = 0, ...);
    bool                            IsSendCommand                 (DIOCLICLIENT_ERROR& error);

    DIOCLICLIENT_ERROR              SendCommandWithoutAnswer      (int type,XCHAR* param);
    DIOCLICLIENT_ERROR              SendCommandWithAnswer         (int type,XSTRING& answer,XCHAR* param = NULL);
    DIOCLICLIENT_ERROR              SendCommandWithAnswers        (int type,XVECTOR<XSTRING*>* answers,XCHAR* param = NULL);

    void                            ProcessWait                   (DIOCLICLIENT_ERROR& error);
    bool                            ProcessCommand                (DIOCLICLIENT_ERROR& error);

  private:

    void                            Clean                         ();

    DIOSTREAM*                      diostream;
    XTIMER*                         timer;

    int                             timeout;

    XVECTOR<DIOCLICLIENTCOMMAND*>   clicommands;

    int                             actualtypecommand;

    XSTRING                         headline[DIOCLICLIENT_HEADLINEMAX];
};

/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif
