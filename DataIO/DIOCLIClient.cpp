/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOCLIClient.cpp
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "XFactory.h"
#include "XSleep.h"
#include "XFSMachine.h"

#include "DIOStream.h"

#include "DIOCLIClient.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#pragma region DIOCLICLIENTCOMMAND

DIOCLICLIENTCOMMAND::DIOCLICLIENTCOMMAND()
{
  Clean();
}


DIOCLICLIENTCOMMAND::~DIOCLICLIENTCOMMAND()
{
  DeleteAllAnswers();
  DeleteAllParams();

  Clean();
}


int DIOCLICLIENTCOMMAND::GetType()
{
  return type;
}


XCHAR* DIOCLICLIENTCOMMAND::GetCommand()
{
  return command.Get();
}


bool DIOCLICLIENTCOMMAND::Set(int type, XCHAR* command)
{
  this->type    = type;
  this->command = command;

  return true;
}


bool DIOCLICLIENTCOMMAND::AddParam(XSTRING* param)
{
  params.Add(param);

  return true;
}


XCHAR* DIOCLICLIENTCOMMAND::GetParam(int index)
{
  XSTRING* param = (XSTRING*)params.Get(index);
  if(!param) return NULL;

  return param->Get();
}


int DIOCLICLIENTCOMMAND::GetNParams()
{
  return params.GetSize();
}


bool DIOCLICLIENTCOMMAND::DeleteAllParams()
{
  if(params.IsEmpty()) return false;

  params.DeleteContents();

  params.DeleteAll();

  return true;
}


bool DIOCLICLIENTCOMMAND::AddAnswer(XCHAR* answer)
{
  XSTRING* _answer = new XSTRING(answer);

  if(_answer)  answers.Add(_answer);

  return true;
}


bool DIOCLICLIENTCOMMAND::AddAnswer(XSTRING* answer)
{
  if(!answer) return false;

  answers.Add(answer);

  return true;
}


int DIOCLICLIENTCOMMAND::GetNAnswers()
{
  return answers.GetSize();
}


XSTRING* DIOCLICLIENTCOMMAND::GetAnswer(int index)
{
  XSTRING* answer = (XSTRING*)answers.Get(index);
  if(!answer) return NULL;

  return answer;
}


bool DIOCLICLIENTCOMMAND::DeleteAllAnswers()
{
  if(answers.IsEmpty()) return false;

  answers.DeleteContents();
  answers.DeleteAll();

  return true;
}


void DIOCLICLIENTCOMMAND::Clean()
{

}

#pragma endregion


#pragma region DIOCLICLIENT


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCLICLIENT::DIOCLICLIENT(DIOSTREAM* diostream)
* @brief      Constructor
* @ingroup    DATAIO
* 
* @param[in]  DIOSTREAM* : 
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCLICLIENT::DIOCLICLIENT(DIOSTREAM* diostream) : XFSMACHINE(0)
{
  Clean();

  this->diostream = diostream;

  AddState( DIOCLICLIENT_XFSMSTATE_NONE         ,
            DIOCLICLIENT_XFSMEVENT_INICMD       , DIOCLICLIENT_XFSMSTATE_INICMD       ,
            DIOCLICLIENT_XFSMEVENT_SENDCMD      , DIOCLICLIENT_XFSMSTATE_SENDCMD      ,
            DIOCLICLIENT_XFSMEVENT_ENDCMD       , DIOCLICLIENT_XFSMSTATE_ENDCMD       ,
            XFSMACHINESTATE_EVENTDEFEND);

  AddState( DIOCLICLIENT_XFSMSTATE_INICMD       ,
            DIOCLICLIENT_XFSMEVENT_NONE         , DIOCLICLIENT_XFSMSTATE_NONE         ,
            DIOCLICLIENT_XFSMEVENT_SENDCMD      , DIOCLICLIENT_XFSMSTATE_SENDCMD      ,
            DIOCLICLIENT_XFSMEVENT_ENDCMD       , DIOCLICLIENT_XFSMSTATE_ENDCMD       ,
            XFSMACHINESTATE_EVENTDEFEND);

  AddState( DIOCLICLIENT_XFSMSTATE_SENDCMD      ,
            DIOCLICLIENT_XFSMEVENT_NONE         , DIOCLICLIENT_XFSMSTATE_NONE         ,
            DIOCLICLIENT_XFSMEVENT_RECEIVEDCMD  , DIOCLICLIENT_XFSMSTATE_RECEIVEDCMD  ,
            DIOCLICLIENT_XFSMEVENT_ENDCMD       , DIOCLICLIENT_XFSMSTATE_ENDCMD       ,
            XFSMACHINESTATE_EVENTDEFEND);

  AddState( DIOCLICLIENT_XFSMSTATE_RECEIVEDCMD  ,
            DIOCLICLIENT_XFSMEVENT_NONE         , DIOCLICLIENT_XFSMSTATE_NONE         ,
            DIOCLICLIENT_XFSMEVENT_SENDCMD      , DIOCLICLIENT_XFSMSTATE_SENDCMD      ,
            DIOCLICLIENT_XFSMEVENT_ENDCMD       , DIOCLICLIENT_XFSMSTATE_ENDCMD       ,
            XFSMACHINESTATE_EVENTDEFEND);

  AddState( DIOCLICLIENT_XFSMSTATE_ENDCMD       ,
            DIOCLICLIENT_XFSMEVENT_NONE         , DIOCLICLIENT_XFSMSTATE_NONE         ,
            DIOCLICLIENT_XFSMEVENT_INICMD       , DIOCLICLIENT_XFSMSTATE_INICMD       ,
            XFSMACHINESTATE_EVENTDEFEND);

  GEN_XFACTORY_CREATE(timer, CreateTimer())  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCLICLIENT::~DIOCLICLIENT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCLICLIENT::~DIOCLICLIENT()

{
  DeleteAllCommand();

  GEN_XFACTORY.DeleteTimer(timer);

  End();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCLICLIENT::Ini(int timeout)
* @brief      Ini
* @ingroup    DATAIO
* 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCLICLIENT::Ini(int timeout)
{
  if(!diostream)          return false;
  if(diostream->GetConnectStatus()!=DIOSTREAMSTATUS_DISCONNECTED) return false;

  if(!diostream->Open()) return false;

  this->timeout = timeout;

  if(!diostream->WaitToConnected(timeout)) return false;

  // -----------------------------------------
  // Read Header of CLI

  char* line = new char[_MAXSTR];
  if(line)
    {
      memset(line,0,_MAXSTR);

      for(int c=0;c<DIOCLICLIENT_HEADLINEMAX;c++)
        {
          while(!diostream->ReadStr(line))
            {

            }

          headline[c] = line;
        }

      delete [] line;
    }

  // -----------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCLICLIENT::End()
* @brief      End
* @ingroup    DATAIO
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCLICLIENT::End()
{
  if(diostream)
    {
      diostream->Disconnect();
      diostream->Close();
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCLICLIENT::AddCommand(int type, XCHAR* command)
* @brief      AddCommand
* @ingroup    DATAIO
* 
* @param[in]  type : 
* @param[in]  command : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCLICLIENT::AddCommand(int type, XCHAR* command)
{
  DIOCLICLIENTCOMMAND* clicommand = GetCommand(type);
  if(clicommand) return false;

  clicommand = new DIOCLICLIENTCOMMAND();
  if(!clicommand) return false;

  clicommand->Set(type,command);

  clicommands.Add(clicommand);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCLICLIENTCOMMAND* DIOCLICLIENT::GetCommand(int type)
* @brief      GetCommand
* @ingroup    DATAIO
* 
* @param[in]  type : 
* 
* @return     DIOCLICLIENTCOMMAND* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCLICLIENTCOMMAND* DIOCLICLIENT::GetCommand(int type)
{
  DIOCLICLIENTCOMMAND* clicommand;

  for(int c=0;c<(int)clicommands.GetSize();c++)
    {
       clicommand = (DIOCLICLIENTCOMMAND*)clicommands.Get(c);
       if(clicommand)
         {
           if(clicommand->GetType() == type) return clicommand;
         }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCLICLIENT::DeleteAllCommand()
* @brief      DeleteAllCommand
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCLICLIENT::DeleteAllCommand()
{
  if(clicommands.IsEmpty()) return false;

  clicommands.DeleteContents();
  clicommands.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCLICLIENT::GetAnswer(int type,int indexanswer,XSTRING& answerstring)
* @brief      GetAnswer
* @ingroup    DATAIO
* 
* @param[in]  type : 
* @param[in]  indexanswer : 
* @param[in]  answerstring : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCLICLIENT::GetAnswer(int type,int indexanswer,XSTRING& answerstring)
{
  DIOCLICLIENTCOMMAND* clicommand = GetCommand(type);
  if(clicommand)
    {
      XSTRING* answer = clicommand->GetAnswer(indexanswer);
      if(answer)
        {
          answerstring = (*answer);
          return true;
        }
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCLICLIENT::ReadAnswerLF(XSTRING& answer,int timeout)
* @brief      ReadAnswerLF
* @ingroup    DATAIO
* 
* @param[in]  answer : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCLICLIENT::ReadAnswerLF(XSTRING& answer,int timeout)
{
  char str[4];
  int  br;
  bool status = true;

  answer.Empty();

  if(timer) timer->Reset();

  do{ memset(str,0,4);

      br = diostream->Read((XBYTE*)str,1);
      if(br)
        {
          if((str[0]=='\n')||(str[0]=='\r'))
            {
              memset(str,0,4);
              while(!diostream->Read((XBYTE*)str,1))
                {
                  GEN_XSLEEP.MilliSeconds(10);
                }

              break;
            }
           else answer += str;
        }

      if(timer)
        {
          if((int)timer->GetMeasureSeconds()>=timeout)
            {
              status = false;
              break;

            } else GEN_XSLEEP.MilliSeconds(10);
        }

    } while(1);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCLICLIENT::ReadAnswer(XSTRING& answer,XDWORD size,int timeout)
* @brief      ReadAnswer
* @ingroup    DATAIO
* 
* @param[in]  answer : 
* @param[in]  size : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCLICLIENT::ReadAnswer(XSTRING& answer,XDWORD size,int timeout)
{
  char str[4];
  int  br;
  bool status = true;

  answer.Empty();

  if(timer) timer->Reset();

  do{ memset(str,0,4);

      br = diostream->Read((XBYTE*)str,1);
      if(br)
        {
          answer += str;
          if((int)answer.GetSize()>=size) break;
        }

      if(timer)
        {
          if((int)timer->GetMeasureSeconds()>=timeout)
            {
              status = false;
              break;

            } else GEN_XSLEEP.MilliSeconds(10);
        }

    } while(1);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCLICLIENT::SendCommand(int type, int nparams,...)
* @brief      SendCommand
* @ingroup    DATAIO
* 
* @param[in]  type : 
* @param[in]  nparams : 
* @param[in]  ... : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCLICLIENT::SendCommand(int type, int nparams,...)
{
  DIOCLICLIENTCOMMAND* clicommand = GetCommand(type);
  if(!clicommand) return false;

  clicommand->DeleteAllParams();

  va_list arg;
  va_start(arg,nparams);

  for(int c=0;c<nparams;c++)
    {
      XCHAR* param = (XCHAR*)va_arg(arg, XCHAR*);
      if(param)
        {
          XSTRING* string = new XSTRING();
          if(string)
            {
              (*string) = param;
              clicommand->AddParam(string);
            }
        }
    }

  va_end(arg);

  actualtypecommand = type;
  SetEvent(DIOCLICLIENT_XFSMEVENT_INICMD);

  DIOCLICLIENT_ERROR error;
  ProcessCommand(error);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCLICLIENT::IsSendCommand(DIOCLICLIENT_ERROR& error)
* @brief      IsSendCommand
* @ingroup    DATAIO
* 
* @param[in]  error : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCLICLIENT::IsSendCommand(DIOCLICLIENT_ERROR& error)
{
  DIOCLICLIENTCOMMAND* clicommand = GetCommand(actualtypecommand);
  if(!clicommand) return false;

  if(GetCurrentState()==DIOCLICLIENT_XFSMSTATE_NONE) return false;

  return ProcessCommand(error);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCLICLIENT_ERROR DIOCLICLIENT::SendCommandWithoutAnswer(int type,XCHAR* param)
* @brief      SendCommandWithoutAnswer
* @ingroup    DATAIO
* 
* @param[in]  type : 
* @param[in]  param : 
* 
* @return     DIOCLICLIENT_ERROR : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCLICLIENT_ERROR DIOCLICLIENT::SendCommandWithoutAnswer(int type,XCHAR* param)
{
  DIOCLICLIENT_ERROR error = DIOCLICLIENT_ERROR_NONE;

  if(!SendCommand(type,1,param)) return DIOCLICLIENT_ERROR_INVALIDCOMMAND;

  ProcessWait(error);

  DIOCLICLIENTCOMMAND* clicommand = GetCommand(type);
  if(clicommand) clicommand->DeleteAllAnswers();

  return error;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCLICLIENT_ERROR DIOCLICLIENT::SendCommandWithAnswer(int type,XSTRING& answer,XCHAR* param)
* @brief      SendCommandWithAnswer
* @ingroup    DATAIO
* 
* @param[in]  type : 
* @param[in]  answer : 
* @param[in]  param : 
* 
* @return     DIOCLICLIENT_ERROR : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCLICLIENT_ERROR DIOCLICLIENT::SendCommandWithAnswer(int type,XSTRING& answer,XCHAR* param)
{
  DIOCLICLIENT_ERROR error = DIOCLICLIENT_ERROR_NONE;

  if(!SendCommand(type,1,param)) return DIOCLICLIENT_ERROR_INVALIDCOMMAND;

  ProcessWait(error);

  DIOCLICLIENTCOMMAND* clicommand = GetCommand(type);
  if(clicommand)
    {
      if(error==DIOCLICLIENT_ERROR_NONE)
        {
          if(clicommand->GetNAnswers())
            {
              XSTRING* string = clicommand->GetAnswer(0);
              if(string) answer = (*string);

            } else error = DIOCLICLIENT_ERROR_NOTANSWER;
        }

      clicommand->DeleteAllAnswers();
    }

  return error;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCLICLIENT_ERROR DIOCLICLIENT::SendCommandWithAnswers(int type,XVECTOR<XSTRING*>* answers,XCHAR* param)
* @brief      SendCommandWithAnswers
* @ingroup    DATAIO
* 
* @param[in]  type : 
* @param[in]  answers : 
* @param[in]  param : 
* 
* @return     DIOCLICLIENT_ERROR : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCLICLIENT_ERROR DIOCLICLIENT::SendCommandWithAnswers(int type,XVECTOR<XSTRING*>* answers,XCHAR* param)
{
  DIOCLICLIENT_ERROR error = DIOCLICLIENT_ERROR_NONE;

  if(!SendCommand(type,1,param)) return DIOCLICLIENT_ERROR_INVALIDCOMMAND;

  ProcessWait(error);

  DIOCLICLIENTCOMMAND* clicommand = GetCommand(type);
  if(clicommand && answers)
    {
      if(error==DIOCLICLIENT_ERROR_NONE)
        {
          if(clicommand->GetNAnswers())
            {
              for(int c=0;c<clicommand->GetNAnswers();c++)
                {
                  XSTRING* string = clicommand->GetAnswer(c);
                  if(string)
                    {
                      XSTRING* answer = new XSTRING();
                      if(answer) answers->Add(answer);
                    }
                }

            } else error = DIOCLICLIENT_ERROR_NOTANSWER;
        }

      clicommand->DeleteAllAnswers();
    }

  return error;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCLICLIENT::ProcessWait(DIOCLICLIENT_ERROR& error)
* @brief      ProcessWait
* @ingroup    DATAIO
* 
* @param[in]  error : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCLICLIENT::ProcessWait(DIOCLICLIENT_ERROR& error)
{
  while(IsSendCommand(error))
    {
      if(timer) GEN_XSLEEP.MilliSeconds(10);
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCLICLIENT::ProcessCommand(DIOCLICLIENT_ERROR& error)
* @brief      ProcessCommand
* @ingroup    DATAIO
* 
* @param[in]  error : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCLICLIENT::ProcessCommand(DIOCLICLIENT_ERROR& error)
{
  static int  paramindex  =  0;
  static int  answerindex =  0;

  if(diostream->GetConnectStatus()==DIOSTREAMSTATUS_DISCONNECTED) return false;

  DIOCLICLIENTCOMMAND* clicommand = GetCommand(actualtypecommand);
  if(!clicommand) return false;

  if(GetEvent()==DIOCLICLIENT_XFSMEVENT_NONE) // No hay nuevos Eventos
    {
      switch(GetCurrentState())
        {
          case DIOCLICLIENT_XFSMSTATE_NONE              : break;

          case DIOCLICLIENT_XFSMSTATE_INICMD            : break;

          case DIOCLICLIENT_XFSMSTATE_SENDCMD         : if(!paramindex)
                                                          {
                                                            XSTRING command;

                                                            command = clicommand->GetCommand();

                                                            if(clicommand->GetNParams())
                                                              {
                                                                command += __L(" ");
                                                                command += clicommand->GetParam(paramindex);
                                                              }

                                                            //------------------------------------------
                                                            // Read Prompt

                                                            XBYTE str[2] = { 0 , 0 };

                                                            while(!diostream->Read(str,1))
                                                              {
                                                                if(timer) GEN_XSLEEP.MilliSeconds(10);
                                                              }

                                                            if(str[0]!='>')
                                                              {
                                                                error = DIOCLICLIENT_ERROR_WRITECMD;
                                                                SetEvent(DIOCLICLIENT_XFSMEVENT_ENDCMD);
                                                                break;
                                                              }

                                                            //-----------------------------------------

                                                            command += __L("\n");;

                                                            XSTRING_CREATEOEM(command, charOEM)
                                                            if(!diostream->WriteStr(charOEM))
                                                              {
                                                                error = DIOCLICLIENT_ERROR_WRITECMD;
                                                                SetEvent(DIOCLICLIENT_XFSMEVENT_ENDCMD);
                                                              }
                                                            XSTRING_DELETEOEM(command, charOEM)
                                                           }
                                                          else
                                                           {
                                                             XSTRING param;

                                                             param = clicommand->GetParam(paramindex);

                                                             XSTRING_CREATEOEM(param, charOEM)
                                                             if(!diostream->WriteStr(charOEM))
                                                               {
                                                                 error = DIOCLICLIENT_ERROR_WRITECMD;
                                                                 SetEvent(DIOCLICLIENT_XFSMEVENT_ENDCMD);
                                                               }
                                                             XSTRING_DELETEOEM(param, charOEM)
                                                           }

                                                          paramindex++;
                                                          SetEvent(DIOCLICLIENT_XFSMEVENT_RECEIVEDCMD);
                                                          break;

          case DIOCLICLIENT_XFSMSTATE_RECEIVEDCMD     : {
                                                          //------------------------------------------
                                                          // Read \n extra

                                                          if(!answerindex)
                                                            {
                                                              XBYTE str[2] = { 0 , 0 };

                                                              while(!diostream->Read(str,1))
                                                                {
                                                                  if(timer) GEN_XSLEEP.MilliSeconds(10);
                                                                }

                                                              if(str[0]!='\n')
                                                                {
                                                                  error = DIOCLICLIENT_ERROR_WRITECMD;
                                                                  SetEvent(DIOCLICLIENT_XFSMEVENT_ENDCMD);
                                                                  break;
                                                                }
                                                            }

                                                          //-----------------------------------------

                                                          bool exit = false;

                                                          while(1)
                                                            {
                                                              XSTRING* answer = new XSTRING();
                                                              if(answer)
                                                                {
                                                                  if(!ReadAnswerLF((*answer), timeout))
                                                                    {
                                                                      error = DIOCLICLIENT_ERROR_TIMEOUT;
                                                                      exit  = true;
                                                                    }
                                                                   else
                                                                    {
                                                                      if(!answer->Compare(__L("OK")   ,true)) exit = true;
                                                                      if(!answer->Compare(__L("ERROR"),true))
                                                                        {
                                                                          XSTRING* answererror = clicommand->GetAnswer(0);
                                                                          if(answererror) answererror->UnFormat(__L("Error code %02d: "),&error);

                                                                          exit = true;
                                                                        }

                                                                      if(exit)
                                                                        {
                                                                          delete answer;
                                                                          SetEvent(DIOCLICLIENT_XFSMEVENT_ENDCMD);
                                                                          break;
                                                                        }
                                                                       else
                                                                        {
                                                                          clicommand->AddAnswer(answer);
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                        break;

          case DIOCLICLIENT_XFSMSTATE_ENDCMD          : break;

        }
    }
   else //  Nuevo evento
    {
      if(GetEvent()<DIOCLICLIENT_LASTEVENT)
        {
          CheckTransition();

          switch(GetCurrentState())
            {
              case DIOCLICLIENT_XFSMSTATE_NONE          : break;

              case DIOCLICLIENT_XFSMSTATE_INICMD        : paramindex  = 0;
                                                          answerindex = 0;
                                                          SetEvent(DIOCLICLIENT_XFSMEVENT_SENDCMD);
                                                          break;

              case DIOCLICLIENT_XFSMSTATE_SENDCMD     : break;

              case DIOCLICLIENT_XFSMSTATE_RECEIVEDCMD : break;

              case DIOCLICLIENT_XFSMSTATE_ENDCMD      : return false;
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCLICLIENT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCLICLIENT::Clean()
{
  diostream           = NULL;

  timeout             = DIOCLICLIENT_TIMEOUT;

  timer               = NULL;

  actualtypecommand   = 0;
}

#pragma endregion

