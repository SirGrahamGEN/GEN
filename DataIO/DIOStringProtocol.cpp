/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOStringProtocol.cpp
* 
* @class      DIOSTRINGPROTOCOL
* @brief      Data Input/Output String protocol class
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
#include "XBuffer.h"
#include "XFSMachine.h"
#include "XTrace.h"

#include "DIOStream.h"

#include "DIOStringProtocol.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#pragma region DIOSTRINGPROTOCOLCOMMAND

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOSTRINGPROTOCOLCOMMAND::DIOSTRINGPROTOCOLCOMMAND()
* @brief      Constructor
* @ingroup    DATAIO
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTRINGPROTOCOLCOMMAND::DIOSTRINGPROTOCOLCOMMAND()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOSTRINGPROTOCOLCOMMAND::~DIOSTRINGPROTOCOLCOMMAND()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTRINGPROTOCOLCOMMAND::~DIOSTRINGPROTOCOLCOMMAND()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XCHAR* DIOSTRINGPROTOCOLCOMMAND::GetCommand()
* @brief      GetCommand
* @ingroup    DATAIO
* 
* @return     XCHAR* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR* DIOSTRINGPROTOCOLCOMMAND::GetCommand()
{ 
  return command.Get();                               
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int DIOSTRINGPROTOCOLCOMMAND::GetNParams()
* @brief      GetNParams
* @ingroup    DATAIO
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int DIOSTRINGPROTOCOLCOMMAND::GetNParams()
{ 
  return nparams;                                     
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSTRINGPROTOCOLCOMMAND::Set(XCHAR* command, int nparams)
* @brief      Set
* @ingroup    DATAIO
* 
* @param[in]  command : 
* @param[in]  nparams : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTRINGPROTOCOLCOMMAND::Set(XCHAR* command, int nparams)
{
  this->command = command;
  this->nparams = nparams;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOSTRINGPROTOCOLCOMMAND::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTRINGPROTOCOLCOMMAND::Clean()
{
  command.Empty();
  nparams = 0;
}

#pragma endregion


#pragma region DIOSTRINGPROTOCOLANSWER

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOSTRINGPROTOCOLANSWER::DIOSTRINGPROTOCOLANSWER()
* @brief      Constructor
* @ingroup    DATAIO
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTRINGPROTOCOLANSWER::DIOSTRINGPROTOCOLANSWER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOSTRINGPROTOCOLANSWER::~DIOSTRINGPROTOCOLANSWER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTRINGPROTOCOLANSWER::~DIOSTRINGPROTOCOLANSWER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* DIOSTRINGPROTOCOLANSWER::GetCommand()
* @brief      GetCommand
* @ingroup    DATAIO
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOSTRINGPROTOCOLANSWER::GetCommand()
{ 
  return &command;                                
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* DIOSTRINGPROTOCOLANSWER::GetAnswer()
* @brief      GetAnswer
* @ingroup    DATAIO
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOSTRINGPROTOCOLANSWER::GetAnswer()
{ 
  return &answer;                                 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOSTRINGPROTOCOLANSWER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTRINGPROTOCOLANSWER::Clean()
{
  command.Empty();
  answer.Empty();
}

#pragma endregion


#pragma region DIOSTRINGPROTOCOL

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOSTRINGPROTOCOL::DIOSTRINGPROTOCOL(DIOSTREAM* diostream)
* @brief      Constructor
* @ingroup    DATAIO
* 
* @param[in]  DIOSTREAM* : 
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTRINGPROTOCOL::DIOSTRINGPROTOCOL(DIOSTREAM* diostream)
{
  Clean();

  this->diostream = diostream;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOSTRINGPROTOCOL::~DIOSTRINGPROTOCOL()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTRINGPROTOCOL::~DIOSTRINGPROTOCOL()
{
  DeleteAllCommand();

  DeleteAllAnswers();

  End();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSTRINGPROTOCOL::Ini(int timeout)
* @brief      Ini
* @ingroup    DATAIO
* 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTRINGPROTOCOL::Ini(int timeout)
{
  GEN_XFACTORY_CREATE(xtimerout, CreateTimer())
  if(!xtimerout) return false;

  GEN_XFACTORY_CREATE(xmutexanswers, Create_Mutex())
  if(!xmutexanswers) return false;

  if(!diostream)         return false;
  if(!diostream->Open()) return false;

  this->timeout = timeout;

  if(!diostream->WaitToConnected(timeout)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOSTRINGPROTOCOL::End()
* @brief      End
* @ingroup    DATAIO
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTRINGPROTOCOL::End()
{
  if(diostream)
    {
      diostream->Disconnect();
      diostream->Close();
    }

  if(xmutexanswers)
    {
      GEN_XFACTORY.Delete_Mutex(xmutexanswers);
      xmutexanswers = NULL;
    }

  if(xtimerout)
    {
      GEN_XFACTORY.DeleteTimer(xtimerout);
      xtimerout = NULL;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSTRINGPROTOCOL::SendCommand(XCHAR* command, XSTRING* answer, int timeoutanswer, ...)
* @brief      SendCommand
* @ingroup    DATAIO
* 
* @param[in]  command : 
* @param[in]  answer : 
* @param[in]  timeoutanswer : 
* @param[in]  ... : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTRINGPROTOCOL::SendCommand(XCHAR* command, XSTRING* answer, int timeoutanswer, ...)
{
  va_list arg;

  va_start(arg, timeoutanswer);

  bool status = SendCommand(command, answer, timeoutanswer, arg);

  va_end(arg);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSTRINGPROTOCOL::SendCommand(XCHAR* command, XSTRING* answer, int timeoutanswer, va_list& arg)
* @brief      SendCommand
* @ingroup    DATAIO
* 
* @param[in]  command : 
* @param[in]  answer : 
* @param[in]  timeoutanswer : 
* @param[in]  arg : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTRINGPROTOCOL::SendCommand(XCHAR* command, XSTRING* answer, int timeoutanswer, va_list& arg)
{
  if(answer) answer->Empty();

  DIOSTRINGPROTOCOLCOMMAND* protocolcommand = GetCommand(command);
  if(!protocolcommand) return false;

  XSTRING  tosend;

  if(!answer) tosend += __L("#");
  tosend += protocolcommand->GetCommand();

  int nparams = protocolcommand->GetNParams();

  for(int c=0;c<nparams;c++)
    {
      XCHAR* param = (XCHAR*)va_arg(arg, XCHAR*);
      if(param)
        {
          tosend += __L(" ");
          tosend += param;
          if(c!=nparams) tosend += __L(" ");
        }
    }

  tosend += __L("\n\r");

  XSTRING_CREATEOEM(tosend, charstr);
  diostream->Write((XBYTE*)charstr, tosend.GetSize());
  XSTRING_DELETEOEM(tosend, charstr);


  bool status = true;

  if(answer)
    {
      if(xtimerout) xtimerout->Reset();

      while(1)
        {
          if(!xtimerout)
            {
              status = false;
              break;
            }

          if(xtimerout->GetMeasureSeconds() >= (XDWORD)timeoutanswer)
            {
              status = false;
              break;
            }

          XSTRING* firstanswer = GetFirstAnswer(command);
          if(firstanswer)
            {
              answer->Add(firstanswer->Get());
              DeleteFirstAnswer(command);
              break;
            }

          //GEN_XSLEEP.MilliSeconds(10);
        }
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSTRINGPROTOCOL::ReceivedCommand(XSTRING& command, XVECTOR<XSTRING*>& params, XSTRING& answer)
* @brief      ReceivedCommand
* @ingroup    DATAIO
* 
* @param[in]  command : 
* @param[in]  params : 
* @param[in]  answer : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTRINGPROTOCOL::ReceivedCommand(XSTRING& command, XVECTOR<XSTRING*>& params, XSTRING& answer)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOSTRINGPROTOCOL::ReceivedAnswer(XSTRING& answer)
* @brief      ReceivedAnswer
* @ingroup    DATAIO
* 
* @param[in]  answer : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTRINGPROTOCOL::ReceivedAnswer(XSTRING& answer)
{

}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOSTRINGPROTOCOL::ReceivedCommandManager()
* @brief      ReceivedCommandManager
* @ingroup    DATAIO
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTRINGPROTOCOL::ReceivedCommandManager()
{
  if(!diostream) return;

  XDWORD size  = diostream->GetInXBuffer()->GetSize();
  if(!size) return;

  for(XDWORD c=0; c<size; c++)
    {
      char character = 0;

      if(diostream->Read((XBYTE*)&character, 1))
        {
          if((character == '\n') || (character == '\r'))
            {
              if(diostream->GetInXBuffer()->GetSize())
                {
                  character = diostream->GetInXBuffer()->GetByte(0);
                  if((character == '\n') || (character == '\r'))
                    {
                      if(diostream->Read((XBYTE*)&character, 1))
                        {

                        }
                    }
                }

              if(!laststringreceived.IsEmpty())
                {
                  XSTRING           command;
                  XSTRING           answer;
                  XSTRING           markanswer;
                  bool              makeanswer = true;


                  if(laststringreceived.Get()[0] == __C('#'))
                    {
                      laststringreceived.DeleteCharacters(0, 1);
                      makeanswer = false;
                    }

                  markanswer.Format(__L("[%s"), DIOSTRINGPROTOCOL_ANSWER);

                  int indexanswer = laststringreceived.Find(markanswer.Get(), true);
                  if((indexanswer == XSTRING_NOTFOUND) || (indexanswer > 0))
                    {
                      XVECTOR<XSTRING*> params;

                      ExtractParamsFromCommand(laststringreceived, command, params);

                      bool status = ReceivedCommand(command, params, answer);
                      if(!status)
                        {
                          answer = DIOSTRINGPROTOCOL_ERROR;
                        }
                       else
                        {
                          if(answer.IsEmpty()) answer = DIOSTRINGPROTOCOL_OK;
                        }

                      if(makeanswer)
                        {
                          XSTRING result;

                          result.Format(__L("[%s%s]:%s\n\r"), DIOSTRINGPROTOCOL_ANSWER, command.Get(), answer.Get());

                          //XTRACE_PRINTCOLOR(3, __L("DIOStringProtocol Send Answer: %s"), result.Get());

                          XSTRING_CREATEOEM(result, charstr);
                          diostream->Write((XBYTE*)charstr, result.GetSize());
                          XSTRING_DELETEOEM(result, charstr);
                        }

                      params.DeleteContents();
                      params.DeleteAll();
                   }
                  else
                   {
                     int startcommand;
                     int startanswer;

                     startcommand = laststringreceived.Find(markanswer.Get(), false);
                     if(startcommand  != XSTRING_NOTFOUND)
                       {
                         startcommand += markanswer.GetSize();

                         startanswer= laststringreceived.Find(__L("]:"), false, startcommand);
                         if(startanswer  != XSTRING_NOTFOUND)
                           {
                             laststringreceived.Copy(startcommand, startanswer, command);

                             laststringreceived.DeleteCharacters(0, startanswer+2);

                             //XTRACE_PRINTCOLOR(3, __L("DIOStringProtocol Received Answer: %s %s"), command.Get(), laststringreceived.Get());

                             if(AddAnswer(command.Get(), laststringreceived))
                               {
                                 ReceivedAnswer(laststringreceived);
                               }
                           }
                       }

                   }

                  laststringreceived.Empty();
               }
            }
           else
            {
              if((character >= 0x20) && (character < 0x80)) laststringreceived.Add(character);
            }
        }
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSTRINGPROTOCOL::AddAnswer(XCHAR*command, XSTRING& answer)
* @brief      AddAnswer
* @ingroup    DATAIO
* 
* @param[in]  XCHAR*command : 
* @param[in]  answer : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTRINGPROTOCOL::AddAnswer(XCHAR*command, XSTRING& answer)
{
  DIOSTRINGPROTOCOLANSWER* protocolanswer = new DIOSTRINGPROTOCOLANSWER();
  if(!protocolanswer) return false;

  if(xmutexanswers) xmutexanswers->Lock();

  protocolanswer->GetCommand()->Add(command);
  protocolanswer->GetAnswer()->Add(answer.Get());

  answers.Add(protocolanswer);

  if(xmutexanswers) xmutexanswers->UnLock();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* DIOSTRINGPROTOCOL::GetFirstAnswer(XCHAR* command)
* @brief      GetFirstAnswer
* @ingroup    DATAIO
* 
* @param[in]  command : 
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOSTRINGPROTOCOL::GetFirstAnswer(XCHAR* command)
{
  if(answers.IsEmpty()) return NULL;

  XSTRING* answer = NULL;

  if(xmutexanswers) xmutexanswers->Lock();

  for(XDWORD c=0; c<answers.GetSize(); c++)
    {
      DIOSTRINGPROTOCOLANSWER* protocolanswer = answers.Get(c);
      if(protocolanswer)
        {
          if(!protocolanswer->GetCommand()->Compare(command))
            {
               answer = protocolanswer->GetAnswer();
               break;
            }
        }
    }

  if(xmutexanswers) xmutexanswers->UnLock();

  return answer;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSTRINGPROTOCOL::DeleteFirstAnswer(XCHAR* command)
* @brief      DeleteFirstAnswer
* @ingroup    DATAIO
* 
* @param[in]  command : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTRINGPROTOCOL::DeleteFirstAnswer(XCHAR* command)
{
  if(answers.IsEmpty()) return false;

  bool status = false;

  if(xmutexanswers) xmutexanswers->Lock();

  for(XDWORD c=0; c<answers.GetSize(); c++)
    {
      DIOSTRINGPROTOCOLANSWER* protocolanswer = answers.Get(c);
      if(protocolanswer)
        {
          if(!protocolanswer->GetCommand()->Compare(command))
            {
              delete protocolanswer;
              answers.DeleteIndex(c);
              status = true;

              break;
            }
        }
    }

  if(xmutexanswers) xmutexanswers->UnLock();

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSTRINGPROTOCOL::DeleteAllAnswers()
* @brief      DeleteAllAnswers
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTRINGPROTOCOL::DeleteAllAnswers()
{
  if(answers.IsEmpty()) return false;

  if(xmutexanswers) xmutexanswers->Lock();

  answers.DeleteContents();
  answers.DeleteAll();

  if(xmutexanswers) xmutexanswers->UnLock();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSTRINGPROTOCOL::AddCommand(XCHAR* command, int nparams)
* @brief      AddCommand
* @ingroup    DATAIO
* 
* @param[in]  command : 
* @param[in]  nparams : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTRINGPROTOCOL::AddCommand(XCHAR* command, int nparams)
{
  XSTRING                   commandstring;
  DIOSTRINGPROTOCOLCOMMAND* protocolcommand;

  commandstring = command;
  commandstring.ToLowerCase();

  protocolcommand = GetCommand(commandstring.Get());
  if(protocolcommand) return false;

  protocolcommand = new DIOSTRINGPROTOCOLCOMMAND();
  if(!protocolcommand) return false;

  protocolcommand->Set(commandstring.Get(), nparams);

  return commands.Add(protocolcommand);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOSTRINGPROTOCOLCOMMAND* DIOSTRINGPROTOCOL::GetCommand(XCHAR* command)
* @brief      GetCommand
* @ingroup    DATAIO
* 
* @param[in]  command : 
* 
* @return     DIOSTRINGPROTOCOLCOMMAND* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTRINGPROTOCOLCOMMAND* DIOSTRINGPROTOCOL::GetCommand(XCHAR* command)
{
  XSTRING                   commandstring;
  DIOSTRINGPROTOCOLCOMMAND* protocolcommand;

  commandstring = command;
  commandstring.ToLowerCase();

  for(int c=0;c<(int)commands.GetSize();c++)
    {
       protocolcommand = (DIOSTRINGPROTOCOLCOMMAND*)commands.Get(c);
       if(protocolcommand)
         {
           XSTRING protocolcommandstring;

           protocolcommandstring = protocolcommand->GetCommand();

           if(!protocolcommandstring.Compare(commandstring.Get())) return protocolcommand;
         }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSTRINGPROTOCOL::DeleteAllCommand()
* @brief      DeleteAllCommand
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTRINGPROTOCOL::DeleteAllCommand()
{
  if(commands.IsEmpty()) return false;

  commands.DeleteContents();
  commands.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSTRINGPROTOCOL::ExtractParamsFromCommand(XSTRING& stringreceived, XSTRING& command, XVECTOR<XSTRING*>& params)
* @brief      ExtractParamsFromCommand
* @ingroup    DATAIO
* 
* @param[in]  stringreceived : 
* @param[in]  command : 
* @param[in]  params : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTRINGPROTOCOL::ExtractParamsFromCommand(XSTRING& stringreceived, XSTRING& command, XVECTOR<XSTRING*>& params)
{
  params.DeleteContents();
  params.DeleteAll();

  int firstspace = stringreceived.Find(__L(" "), true);
  if(firstspace == XSTRING_NOTFOUND)
    {
      command = stringreceived.Get();
      return true;
    }
   else
    {
      stringreceived.Copy(0, firstspace, command);
      command.ToLowerCase();
    }

  int index = firstspace+1;

  while(index < (int)stringreceived.GetSize())
    {
      int indexspace = stringreceived.Find(__L(" "), true, index);
      if(indexspace != XSTRING_NOTFOUND)
        {
          XSTRING* param = new XSTRING();
          if(param)
            {
              stringreceived.Copy(index, indexspace, (*param));
              if(!param->IsEmpty())
                {
                  param->ToLowerCase();
                  params.Add(param);
                }
            }

          index = indexspace+1;
        }
       else
        {
          if(index < (int)stringreceived.GetSize())
            {
              XSTRING* param = new XSTRING();
              if(param)
                {
                  stringreceived.Copy(index, stringreceived.GetSize(), (*param));
                  if(!param->IsEmpty())
                    {
                      param->ToLowerCase();
                      params.Add(param);
                    }
                }
            }

           break;
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOSTRINGPROTOCOL::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTRINGPROTOCOL::Clean()
{
  diostream             = NULL;

  xtimerout             = NULL;
  timeout               = 0;

  xmutexanswers         = NULL;
}

#pragma endregion
