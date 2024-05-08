/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOProtocolCLI.cpp
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIOProtocolCLI.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "XFactory.h"
#include "XString.h"
#include "XSleep.h"
#include "XBuffer.h"
#include "XFSMachine.h"
#include "XTrace.h"

#include "DIOStream.h"

#include "HashCRC32.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


#pragma region DIOPROTOCOLCLICOMMAND


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPROTOCOLCLICOMMAND::DIOPROTOCOLCLICOMMAND()
* @brief      Constructor
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOLCLICOMMAND::DIOPROTOCOLCLICOMMAND()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPROTOCOLCLICOMMAND::~DIOPROTOCOLCLICOMMAND()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOLCLICOMMAND::~DIOPROTOCOLCLICOMMAND()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XCHAR* DIOPROTOCOLCLICOMMAND::GetCommand()
* @brief      GetCommand
* @ingroup    DATAIO
* 
* @return     XCHAR* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR* DIOPROTOCOLCLICOMMAND::GetCommand()
{ 
  return command.Get();                               
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int DIOPROTOCOLCLICOMMAND::GetNParams()
* @brief      GetNParams
* @ingroup    DATAIO
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int DIOPROTOCOLCLICOMMAND::GetNParams()
{ 
  return nparams;                                     
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPROTOCOLCLICOMMAND::Set(XCHAR* command, int nparams)
* @brief      Set
* @ingroup    DATAIO
* 
* @param[in]  command : 
* @param[in]  nparams : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOLCLICOMMAND::Set(XCHAR* command, int nparams)
{
  this->command = command;
  this->nparams = nparams;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOPROTOCOLCLICOMMAND::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOLCLICOMMAND::Clean()
{
  command.Empty();
  nparams = 0;
}


#pragma endregion


#pragma region DIOPROTOCOLCLIANSWER


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPROTOCOLCLIANSWER::DIOPROTOCOLCLIANSWER()
* @brief      Constructor
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOLCLIANSWER::DIOPROTOCOLCLIANSWER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPROTOCOLCLIANSWER::~DIOPROTOCOLCLIANSWER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOLCLIANSWER::~DIOPROTOCOLCLIANSWER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* DIOPROTOCOLCLIANSWER::GetOriginID()
* @brief      GetOriginID
* @ingroup    DATAIO
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOPROTOCOLCLIANSWER::GetOriginID()
{
  return &originID;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* DIOPROTOCOLCLIANSWER::GetCommand()
* @brief      GetCommand
* @ingroup    DATAIO
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOPROTOCOLCLIANSWER::GetCommand()
{ 
  return &command;                                
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* DIOPROTOCOLCLIANSWER::GetAnswer()
* @brief      GetAnswer
* @ingroup    DATAIO
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOPROTOCOLCLIANSWER::GetAnswer()
{ 
  return &answer;                                 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOPROTOCOLCLIANSWER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOLCLIANSWER::Clean()
{
  command.Empty();
  answer.Empty();
}


#pragma endregion


#pragma region DIOPROTOCOLCLI


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPROTOCOLCLI::DIOPROTOCOLCLI()
* @brief      Constructor
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOLCLI::DIOPROTOCOLCLI()
{
  Clean();

  exitproccess = false;  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPROTOCOLCLI::~DIOPROTOCOLCLI()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOLCLI::~DIOPROTOCOLCLI()
{
  DeleteAllCommand();

  DeleteAllAnswers();

  End();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPROTOCOLCLI::Ini(DIOSTREAM* diostream, XCHAR* ID, int timeout)
* @brief      Ini
* @ingroup    DATAIO
* 
* @param[in]  diostream : 
* @param[in]  ID : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOLCLI::Ini(DIOSTREAM* diostream, XCHAR* ID, int timeout)
{
  this->diostream = diostream;
  if(!diostream) return false;

  GEN_XFACTORY_CREATE(xtimerout, CreateTimer())
  if(!xtimerout) return false;

  GEN_XFACTORY_CREATE(xmutexanswers, Create_Mutex())
  if(!xmutexanswers) return false;

  if(!diostream)         return false;
  if(!diostream->Open()) return false;

  this->timeout = timeout;

  if(!diostream->WaitToConnected(timeout)) return false;

  isini = true;

  return isini;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPROTOCOLCLI::IsIni()
* @brief      IsIni
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOLCLI::IsIni()
{
  return isini;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOPROTOCOLCLI::ActiveCRC(bool activated)
* @brief      ActiveCRC
* @ingroup    DATAIO
* 
* @param[in]  activated : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOLCLI::ActiveCRC(bool activated)
{
  activeCRC = activated;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPROTOCOLCLI::SendCommand(XCHAR* command, XSTRING* target, XSTRING* answer, int timeoutanswer, ...)
* @brief      SendCommand
* @ingroup    DATAIO
* 
* @param[in]  command : 
* @param[in]  target : 
* @param[in]  answer : 
* @param[in]  timeoutanswer : 
* @param[in]  ... : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOLCLI::SendCommand(XCHAR* command, XSTRING* target, XSTRING* answer, int timeoutanswer, ...)
{
  va_list arg;

  va_start(arg, timeoutanswer);

  bool status = SendCommandArg(command, target, answer, timeoutanswer, &arg);

  va_end(arg);
 
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPROTOCOLCLI::SendCommandArg(XCHAR* command, XSTRING* target, XSTRING* answer, int timeoutanswer, va_list* arg)
* @brief      SendCommandArg
* @ingroup    DATAIO
* 
* @param[in]  command : 
* @param[in]  target : 
* @param[in]  answer : 
* @param[in]  timeoutanswer : 
* @param[in]  arg : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOLCLI::SendCommandArg(XCHAR* command, XSTRING* target, XSTRING* answer, int timeoutanswer, va_list* arg)
{
  DIOPROTOCOLCLICOMMAND* protocolcommand = GetCommand(command);
  if(!protocolcommand) return false;

  if(!arg) return false;

  XSTRING tosend;

  if(answer) 
    { 
      answer->Empty();           
    } 
   else
    {
      tosend.Format(__L("%c"), DIOPROTOCOLCLI_MARK_DONOTANSWER);
    }

  if(!ID.IsEmpty())
    {
      tosend.AddFormat(__L("%s%s"), ID.Get(), DIOPROTOCOLCLI_MARK_ORIGIN);
    }

  if(target)
    {
      if(!target->IsEmpty())
        {
          tosend.AddFormat(__L("%s%s"), target->Get(), DIOPROTOCOLCLI_MARK_TARGET);
        }
    }
   else
    {
      tosend.AddFormat(__L("%s%s"), DIOPROTOCOLCLI_MARK_BROADCAST, DIOPROTOCOLCLI_MARK_TARGET);
    }

  tosend.AddFormat(__L("%s"), protocolcommand->GetCommand());
  
  int nparams = protocolcommand->GetNParams();
  if(nparams)
    {
      tosend.AddFormat(__L(" "));
      
      for(int c=0;c<nparams;c++)
        {
          XCHAR* param = (XCHAR*)va_arg((*arg), XCHAR*);
          if(param)
            {
              tosend += param;   
              if(c != nparams-1) tosend += __L(",");         
            }
        }
    }

  if(activeCRC)
    { 
      HASHCRC32 CRC32;

      XBUFFER charstr;
      
      tosend.ConvertToASCII(charstr);
      CRC32.Do((XBYTE*)charstr.Get(), tosend.GetSize());
      
      XDWORD CRC32result = CRC32.GetResultCRC32();
      tosend.AddFormat(__L("%s%08X"), DIOPROTOCOLCLI_MARK_CRC32, CRC32result);
    }

  tosend += __L("\n\r");


  XBUFFER charstr;
  
  tosend.ConvertToASCII(charstr); 
  diostream->Write((XBYTE*)charstr.Get(), tosend.GetSize());

  tosend.DeleteCharacter(__C('\n'));
  tosend.DeleteCharacter(__C('\r'));

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Protocol CLI] %s Send Ask: %s -> %s %s"), tosend.Get(), ID.Get(), (target?target->Get():DIOPROTOCOLCLI_MARK_BROADCAST), command);

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

          if(exitproccess) 
            {
              status = false;
              break;
            }

          if(xtimerout->GetMeasureSeconds() >= (XDWORD)timeoutanswer)
            {
              status = false;
              break;
            }

          DIOPROTOCOLCLIANSWER* protocolanswer = GetFirstAnswer(command);
          if(protocolanswer)
            {
              answer->Add(protocolanswer->GetAnswer()->Get());
              DeleteFirstAnswer(command);
              break;
            }          
        }
    }  

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPROTOCOLCLI::ReceivedCommand(XSTRING& originID, XSTRING& command, XVECTOR<XSTRING*>& params, XSTRING& answer)
* @brief      ReceivedCommand
* @ingroup    DATAIO
* 
* @param[in]  originID : 
* @param[in]  command : 
* @param[in]  params : 
* @param[in]  answer : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOLCLI::ReceivedCommand(XSTRING& originID, XSTRING& command, XVECTOR<XSTRING*>& params, XSTRING& answer)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPROTOCOLCLI::ReceivedAnswer(XSTRING& origin, XSTRING& command, XSTRING& answer)
* @brief      ReceivedAnswer
* @ingroup    DATAIO
* 
* @param[in]  origin : 
* @param[in]  command : 
* @param[in]  answer : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOLCLI::ReceivedAnswer(XSTRING& origin, XSTRING& command, XSTRING& answer)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOPROTOCOLCLI::ReceivedCommandManager()
* @brief      ReceivedCommandManager
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOLCLI::ReceivedCommandManager()
{
  if(!diostream) return;

  XSTRING mark_origin = DIOPROTOCOLCLI_MARK_ORIGIN;
  XSTRING mark_target = DIOPROTOCOLCLI_MARK_TARGET;
  XSTRING mark_answer = DIOPROTOCOLCLI_MARK_ANSWER;
  XSTRING mark_CRC32  = DIOPROTOCOLCLI_MARK_CRC32;


  XDWORD size  = diostream->GetInXBuffer()->GetSize();
  if(!size) return;

  for(XDWORD c=0; c<size; c++)
    {
      char character = 0;

      if(exitproccess) 
        {
          laststringreceived.Empty();
          break;
        }

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
                  XSTRING  originID;
                  XSTRING  targetID;
                  XSTRING  command;                   
                  XSTRING  answer;
                  XSTRING  markanswer;
                  XDWORD   CRC32send   = 0;
                  XDWORD   CRC32result = 0;
                  bool     makeanswer  = true;
                  bool     isanswer    = false;
                  bool     validmessagereception =  false;

                  int indexCRC32 = laststringreceived.Find(DIOPROTOCOLCLI_MARK_CRC32, true);
                  if(indexCRC32 != XSTRING_NOTFOUND)
                    {
                      XSTRING strCRC32;
                      int     sizeCRC32 = 8;

                      laststringreceived.Copy(indexCRC32 + mark_CRC32.GetSize(), indexCRC32 + mark_CRC32.GetSize() + sizeCRC32, strCRC32);
                      laststringreceived.DeleteCharacters(indexCRC32, mark_CRC32.GetSize() + sizeCRC32);
                      strCRC32.UnFormat(__L("%08X"), &CRC32send);                    

                      { HASHCRC32 CRC32;
                        XBUFFER   charstr;
                        
                        laststringreceived.ConvertToASCII(charstr);                        
                        CRC32.Do((XBYTE*)charstr.Get(), laststringreceived.GetSize());                        

                        CRC32result = CRC32.GetResultCRC32();                    
                      }
                    }

                  if(CRC32result == CRC32send)
                    {
                      validmessagereception = true;
                    }

                  if(validmessagereception)
                    {
                      if(laststringreceived.Get()[0] == DIOPROTOCOLCLI_MARK_DONOTANSWER)
                        {
                          laststringreceived.DeleteCharacters(0, 1);
                          makeanswer = false;
                        }

                      if(laststringreceived.Get()[0] == DIOPROTOCOLCLI_MARK_ISANSWER)
                        {
                          laststringreceived.DeleteCharacters(0, 1);
                          isanswer = true;
                        }


                      int indexoriginID = laststringreceived.Find(mark_origin, true);
                      if(indexoriginID != XSTRING_NOTFOUND)
                        {
                          laststringreceived.Copy(0, indexoriginID, originID);
                          laststringreceived.DeleteCharacters(0, indexoriginID + mark_origin.GetSize());
                        }

                      int indextargetID = laststringreceived.Find(mark_target, true);
                      if(indextargetID != XSTRING_NOTFOUND)
                        {
                          laststringreceived.Copy(0, indextargetID, targetID);
                          laststringreceived.DeleteCharacters(0, indextargetID + mark_target.GetSize());
                        }

                      if(!targetID.Compare(DIOPROTOCOLCLI_MARK_BROADCAST, true))
                        {
                          validmessagereception = true;  
                        }

                      if(!targetID.Compare(ID, true))
                        {
                          validmessagereception = true;  
                        }

                      if(validmessagereception)
                        {
                          if(!isanswer)
                            {
                              XVECTOR<XSTRING*> params;
                              ExtractParamsFromCommand(laststringreceived, command, params);
  
                              bool status = ReceivedCommand(originID, command, params, answer);
                              if(!status)
                                {
                                  answer = DIOPROTOCOLCLI_ERROR;
                                }
                               else
                                {
                                  if(answer.IsEmpty()) answer = DIOPROTOCOLCLI_OK;
                                }

                              XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Protocol CLI] Received Command: %s -> %s %s"), originID.Get(), targetID.Get(), command.Get());

                              if(makeanswer)
                                {
                                  XSTRING result;

                                  result.Format(__L("%c%s%s%s%s%s%s%s"), DIOPROTOCOLCLI_MARK_ISANSWER, ID.Get(), DIOPROTOCOLCLI_MARK_ORIGIN, originID.Get(), DIOPROTOCOLCLI_MARK_TARGET, command.Get(), DIOPROTOCOLCLI_MARK_ANSWER, answer.Get());

                                  if(activeCRC)
                                    { 
                                      HASHCRC32 CRC32;
                                      XBUFFER   charstr;
                                      
                                      result.ConvertToASCII(charstr);                                                                           
                                      CRC32.Do((XBYTE*)charstr.Get(), result.GetSize());
                                      
                                      XDWORD CRC32result = CRC32.GetResultCRC32();
                                      result.AddFormat(__L("%s%08X"), DIOPROTOCOLCLI_MARK_CRC32, CRC32result);
                                    }                                  

                                  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Protocol CLI] %s Send Answer: %s -> %s %s : (%s)"), result.Get(), ID.Get(), originID.Get(), command.Get(), answer.Get());

                                  result.Add(__L("\n\r"));

                                  XBUFFER charstr;
                                  
                                  result.ConvertToASCII(charstr);                                  
                                  diostream->Write((XBYTE*)charstr.Get(), result.GetSize());                                  
                                }

                              params.DeleteContents();
                              params.DeleteAll();
                            }
                           else
                            {
                              int indexcommand = laststringreceived.Find(mark_answer, true);
                              if(indexcommand != XSTRING_NOTFOUND)
                                {
                                  laststringreceived.Copy(0, indexcommand, command);
                                  laststringreceived.DeleteCharacters(0, indexcommand + mark_answer.GetSize());
                                }

                              answer = laststringreceived.Get();

                              XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Protocol CLI] Received answer: %s -> %s %s : (%s)"), originID.Get(), targetID.Get(), command.Get(), answer.Get());

                              if(!ReceivedAnswer(originID, command, answer))
                                {
                                  if(AddAnswer(originID, command, answer))
                                    {
                                                                   
                                    }                         
                                }
                            }
                        }
                    }

                  laststringreceived.Empty();
               }
            }
           else
            {
              if((character >= 0x20) && (character <= 0x7F)) laststringreceived.Add(character);
            }
        }
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPROTOCOLCLI::AddAnswer(XSTRING& origin, XSTRING& command, XSTRING& answer)
* @brief      AddAnswer
* @ingroup    DATAIO
* 
* @param[in]  origin : 
* @param[in]  command : 
* @param[in]  answer : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOLCLI::AddAnswer(XSTRING& originID, XSTRING& command, XSTRING& answer)
{
  DIOPROTOCOLCLIANSWER* protocolanswer = new DIOPROTOCOLCLIANSWER();
  if(!protocolanswer) return false;

  if(xmutexanswers) xmutexanswers->Lock();

  protocolanswer->GetOriginID()->Add(originID);
  protocolanswer->GetCommand()->Add(command);
  protocolanswer->GetAnswer()->Add(answer.Get());

  answers.Add(protocolanswer);

  if(xmutexanswers) xmutexanswers->UnLock();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPROTOCOLCLIANSWER* DIOPROTOCOLCLI::GetFirstAnswer(XCHAR* command)
* @brief      GetFirstAnswer
* @ingroup    DATAIO
* 
* @param[in]  command : 
* 
* @return     DIOPROTOCOLCLIANSWER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOLCLIANSWER* DIOPROTOCOLCLI::GetFirstAnswer(XCHAR* command)
{
  if(answers.IsEmpty()) return NULL;

  DIOPROTOCOLCLIANSWER* protocolanswer = NULL;

  if(xmutexanswers) xmutexanswers->Lock();

  for(XDWORD c=0; c<answers.GetSize(); c++)
    {
      protocolanswer = answers.Get(c);
      if(protocolanswer)
        {
          if(!protocolanswer->GetCommand()->Compare(command))
            {
              break;

            } else protocolanswer = NULL;
        }
    }

  if(xmutexanswers) xmutexanswers->UnLock();

  return protocolanswer;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPROTOCOLCLI::DeleteFirstAnswer(XCHAR* command)
* @brief      DeleteFirstAnswer
* @ingroup    DATAIO
* 
* @param[in]  command : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOLCLI::DeleteFirstAnswer(XCHAR* command)
{
  if(answers.IsEmpty()) return false;

  bool status = false;

  if(xmutexanswers) xmutexanswers->Lock();

  for(XDWORD c=0; c<answers.GetSize(); c++)
    {
      DIOPROTOCOLCLIANSWER* protocolanswer = answers.Get(c);
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
* @fn         bool DIOPROTOCOLCLI::DeleteAllAnswers()
* @brief      DeleteAllAnswers
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOLCLI::DeleteAllAnswers()
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
* @fn         void DIOPROTOCOLCLI::End()
* @brief      End
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOLCLI::End()
{
  exitproccess = true;

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
* @fn         bool DIOPROTOCOLCLI::AddCommand(XCHAR* command, int nparams)
* @brief      AddCommand
* @ingroup    DATAIO
* 
* @param[in]  command : 
* @param[in]  nparams : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOLCLI::AddCommand(XCHAR* command, int nparams)
{
  XSTRING                   commandstring;
  DIOPROTOCOLCLICOMMAND* protocolcommand;

  commandstring = command;
  commandstring.ToLowerCase();

  protocolcommand = GetCommand(commandstring.Get());
  if(protocolcommand) return false;

  protocolcommand = new DIOPROTOCOLCLICOMMAND();
  if(!protocolcommand) return false;

  protocolcommand->Set(commandstring.Get(), nparams);

  return commands.Add(protocolcommand);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPROTOCOLCLICOMMAND* DIOPROTOCOLCLI::GetCommand(XCHAR* command)
* @brief      GetCommand
* @ingroup    DATAIO
* 
* @param[in]  command : 
* 
* @return     DIOPROTOCOLCLICOMMAND* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOLCLICOMMAND* DIOPROTOCOLCLI::GetCommand(XCHAR* command)
{
  XSTRING                commandstring;
  DIOPROTOCOLCLICOMMAND* protocolcommand;

  commandstring = command;
  commandstring.ToLowerCase();

  for(int c=0;c<(int)commands.GetSize();c++)
    {
       protocolcommand = (DIOPROTOCOLCLICOMMAND*)commands.Get(c);
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
* @fn         bool DIOPROTOCOLCLI::DeleteAllCommand()
* @brief      DeleteAllCommand
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOLCLI::DeleteAllCommand()
{
  if(commands.IsEmpty()) return false;

  commands.DeleteContents();
  commands.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPROTOCOLCLI::ExtractParamsFromCommand(XSTRING& stringreceived, XSTRING& command, XVECTOR<XSTRING*>& params)
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
bool DIOPROTOCOLCLI::ExtractParamsFromCommand(XSTRING& stringreceived, XSTRING& command, XVECTOR<XSTRING*>& params)
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
      int indexspace = stringreceived.Find(__L(","), true, index);
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
* @fn         void DIOPROTOCOLCLI::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOLCLI::Clean()
{
  ID.Empty();

  diostream             = NULL;

  isini                 = false;

  activeCRC             = false;

  xtimerout             = NULL;
  timeout               = 0;

  xmutexanswers         = NULL;
}


#pragma endregion


#pragma endregion

