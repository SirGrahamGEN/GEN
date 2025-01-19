/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOATCMDS.cpp
* 
* @class      DIOATCMDS
* @brief      Data Input/Output AT commands protocol class
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
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIOATCMDS.h"

#include "XFactory.h"
#include "XSleep.h"
#include "XFSMachine.h"
#include "XBuffer.h"
#include "XTrace.h"
#include "XThreadCollected.h"

#include "DIOStream.h"
#include "DIOStreamUARTConfig.h"
#include "DIOStreamUART.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOATCMD::DIOATCMD()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOATCMD::DIOATCMD()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOATCMD::~DIOATCMD()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOATCMD::~DIOATCMD()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOATCMD::GetType()
* @brief      Get type
* @ingroup    DATAIO
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOATCMD::GetType()
{
  return type;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XCHAR* DIOATCMD::GetCommand()
* @brief      Get command
* @ingroup    DATAIO
*
* @return     XCHAR* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR* DIOATCMD::GetCommand()
{
  return command.Get();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOATCMD::GetCommandString()
* @brief      Get command string
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOATCMD::GetCommandString()
{
  return &command;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOATCMD::Set(XDWORD type, XCHAR* command, bool isunsolicited)
* @brief      Set
* @ingroup    DATAIO
*
* @param[in]  type :
* @param[in]  command :
* @param[in]  isunsolicited :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOATCMD::Set(XDWORD type, XCHAR* command, bool isunsolicited)
{
  this->type          = type;
  this->command       = command;
  this->isunsolicited = isunsolicited;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOATCMD::IsUnSolicited()
* @brief      Is un solicited
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOATCMD::IsUnSolicited()
{
  return isunsolicited;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOATCMD::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOATCMD::Clean()
{
  type          = DIOATCMD_ERROR_NONE;
  isunsolicited = false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOATCMDS::DIOATCMDS(DIOSTREAM* diostream)
* @brief      Constructor of class
* @ingroup    DATAIO
*
* @param[in]  diostream :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOATCMDS::DIOATCMDS(DIOSTREAM* diostream) : XFSMACHINE(0)
{
  Clean();

  this->diostream = diostream;

  GEN_XFACTORY_CREATE(xtimer, CreateTimer())  
  GEN_XFACTORY_CREATE(mutexreadwriteprocess, Create_Mutex())
  
  threadconnection = CREATEXTHREAD(XTHREADGROUPID_DIOATCMS, __L("DIOATCMDS::DIOATCMDS"),ThreadConnection,(void*)this);

  AddCommand(DIOATCMD_TYPE_BASIC      , __L(""));
  AddCommand(DIOATCMD_TYPE_CHARACTER  , __L("S"));
  AddCommand(DIOATCMD_TYPE_RESET      , __L("Z"));
  AddCommand(DIOATCMD_TYPE_ECHO       , __L("E"));
  AddCommand(DIOATCMD_TYPE_VERBOSE    , __L("V"));
  AddCommand(DIOATCMD_TYPE_BAUDRATE   , __L("+IPR"));
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOATCMDS::~DIOATCMDS()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOATCMDS::~DIOATCMDS()
{
  End();

  if(threadconnection)
    {
      DELETEXTHREAD(XTHREADGROUPID_DIOATCMS, threadconnection);
      threadconnection = NULL;
    }

  if(mutexreadwriteprocess)
    {
      GEN_XFACTORY.Delete_Mutex(mutexreadwriteprocess);
      mutexreadwriteprocess = NULL;
    }

  if(xtimer)
    {
      GEN_XFACTORY.DeleteTimer(xtimer);
      xtimer = NULL;
    }

  DeleteAllSendCommand();
  DeleteAllAnswers();
  DeleteAllCommand();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAM* DIOATCMDS::GetDIOStream()
* @brief      Get DIO stream
* @ingroup    DATAIO
*
* @return     DIOSTREAM* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAM* DIOATCMDS::GetDIOStream()
{
  return diostream;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTIMER* DIOATCMDS::GetXTimer()
* @brief      Get X timer
* @ingroup    DATAIO
*
* @return     XTIMER* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XTIMER* DIOATCMDS::GetXTimer()
{
  return xtimer;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOATCMDS::Ini(int timeout, bool echomode, bool verbosemode, int minimumbaurate)
* @brief      Ini
* @ingroup    DATAIO
*
* @param[in]  timeout :
* @param[in]  echomode :
* @param[in]  verbosemode :
* @param[in]  minimumbaurate :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOATCMDS::Ini(int timeout, bool echomode, bool verbosemode, int minimumbaurate)
{
  if(!diostream)  return false;

  diostream->ResetXBuffers();

  if(threadconnection) threadconnection->Ini();

  /*
  DIOSTREAMUARTCONFIG* diostreamcfg = (DIOSTREAMUARTCONFIG*)diostream->GetConfig();
  if(!diostreamcfg) return 0;

  if(!diostreamcfg->GetBaudRate())
    {
      if(!CalculeBaudRate(timeout/2)) return false;
    }
   else
    {
      if(!diostream->Open()) return false;
    }
  */

  if(!diostream->Open()) return false;

  if(!diostream->WaitToConnected(timeout)) return false;

  if(SetVerboseMode(verbosemode,timeout)==DIOATCMD_ERROR_NONE)
    {
      if(SetEchoMode(echomode,timeout)==DIOATCMD_ERROR_NONE)
        {
          if(GetCharacter(DIOATCMD_CODECHARACTER_ESCAPE   , escapechar  , timeout) != DIOATCMD_ERROR_NONE) return false;
          if(GetCharacter(DIOATCMD_CODECHARACTER_ENDLINE  , endlinechar , timeout) != DIOATCMD_ERROR_NONE) return false;
          if(GetCharacter(DIOATCMD_CODECHARACTER_ANSWER   , answerchar  , timeout) != DIOATCMD_ERROR_NONE) return false;
          if(GetCharacter(DIOATCMD_CODECHARACTER_DEL      , delchar     , timeout) != DIOATCMD_ERROR_NONE) return false;

          // ----------------------------------------
          // Adjust minumum baud rate.
          //
          if(diostream->GetConfig()->GetType()==DIOSTREAMTYPE_UART)
            {
              int baudrate = 0;
              if(GetBaudRate(baudrate)==DIOATCMD_ERROR_NONE)
                {
                  if(baudrate<minimumbaurate)
                    {
                      if(SetBaudRate(minimumbaurate)!= DIOATCMD_ERROR_NONE) return false;
                    }
                }
            }


          DeleteAllAnswers();

          return AdditionalInitialization(timeout);
        }
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOATCMD_ERROR DIOATCMDS::Basic(int timeout)
* @brief      Basic
* @ingroup    DATAIO
*
* @param[in]  timeout :
*
* @return     DIOATCMD_ERROR :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOATCMD_ERROR DIOATCMDS::Basic(int timeout)
{
  return MakeSimpleCommand(DIOATCMD_TYPE_BASIC,NULL,timeout);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOATCMD_ERROR DIOATCMDS::GetCharacter(DIOATCMD_CODECHARACTER code,XBYTE& character,int timeout)
* @brief      Get character
* @ingroup    DATAIO
*
* @param[in]  code :
* @param[in]  character :
* @param[in]  timeout :
*
* @return     DIOATCMD_ERROR :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOATCMD_ERROR DIOATCMDS::GetCharacter(DIOATCMD_CODECHARACTER code,XBYTE& character,int timeout)
{
  XSTRING param;

  param.Format(__L("%d?"),code);

  DIOATCMD_ERROR error = SendCommand(DIOATCMD_TYPE_CHARACTER, param.Get());
  if(error!=DIOATCMD_ERROR_NONE) return error;

  error = WaitToProcessAnswer(timeout);
  if(error!=DIOATCMD_ERROR_NONE) return error;

  character = 0;

  XSTRING* answer = GetLastAnswer();
  if(answer)
    {
      character = (XBYTE)answer->ConvertToInt();
      if(!character) error = DIOATCMD_ERROR_UNKNOWN;

      DeleteLastAnswer();
    }

  return error;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOATCMD_ERROR DIOATCMDS::Reset(int timeout)
* @brief      Reset
* @ingroup    DATAIO
*
* @param[in]  timeout :
*
* @return     DIOATCMD_ERROR :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOATCMD_ERROR DIOATCMDS::Reset(int timeout)
{
  return MakeSimpleCommand(DIOATCMD_TYPE_RESET,NULL,timeout);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOATCMD_ERROR DIOATCMDS::SetEchoMode(bool echomode, int timeout)
* @brief      Set echo mode
* @ingroup    DATAIO
*
* @param[in]  echomode :
* @param[in]  timeout :
*
* @return     DIOATCMD_ERROR :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOATCMD_ERROR DIOATCMDS::SetEchoMode(bool echomode, int timeout)
{
  DIOATCMD_ERROR error = SendCommand(DIOATCMD_TYPE_ECHO, echomode?__L("1"):__L("0"));
  if(error!=DIOATCMD_ERROR_NONE) return error;

  this->echomode = echomode;

  return WaitToProcessAnswer(timeout);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOATCMD_ERROR DIOATCMDS::SetVerboseMode(bool verbosemode , int timeout)
* @brief      Set verbose mode
* @ingroup    DATAIO
*
* @param[in]  verbosemode :
* @param[in]  timeout :
*
* @return     DIOATCMD_ERROR :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOATCMD_ERROR DIOATCMDS::SetVerboseMode(bool verbosemode  , int timeout)
{
  DIOATCMD_ERROR error = SendCommand(DIOATCMD_TYPE_VERBOSE, verbosemode?__L("1"):__L("0"));
  if(error!=DIOATCMD_ERROR_NONE) return error;

  this->verbosemode = verbosemode;

  return WaitToProcessAnswer(timeout);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOATCMD_ERROR DIOATCMDS::GetBaudRate(int& baudrate, int timeout)
* @brief      Get baud rate
* @ingroup    DATAIO
*
* @param[in]  baudrate :
* @param[in]  timeout :
*
* @return     DIOATCMD_ERROR :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOATCMD_ERROR DIOATCMDS::GetBaudRate(int& baudrate, int timeout)
{
  DIOATCMD_ERROR error = MakeSimpleCommand(DIOATCMD_TYPE_BAUDRATE, __L("?"), timeout);
  if(error!=DIOATCMD_ERROR_NONE) return error;

  int index = SearchInAnswers(DIOATCMD_TYPE_BAUDRATE, timeout);
  if(index!=DIOATCMDS_ANSWERNOTFOUND)
    {
      XSTRING* answer = GetAnswer(index);
      if(answer)
        {
          XSTRING  mask;

          mask = GetCommandString(DIOATCMD_TYPE_BAUDRATE);
          mask += __L(":%d");
          answer->UnFormat(mask.Get(),&baudrate);
        }

      DeleteAnswer(index);
    }

  return error;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOATCMD_ERROR DIOATCMDS::SetBaudRate(int baudrate, int timeout)
* @brief      Set baud rate
* @ingroup    DATAIO
*
* @param[in]  baudrate :
* @param[in]  timeout :
*
* @return     DIOATCMD_ERROR :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOATCMD_ERROR DIOATCMDS::SetBaudRate(int baudrate, int timeout)
{
  DIOATCMD_ERROR error;
  XSTRING        param;

  if(diostream->GetConfig()->GetType()!=DIOSTREAMTYPE_UART) return DIOATCMD_ERROR_INVALIDCMD;

  param.Format(__L("=%d"),baudrate);

  error = SendCommand(DIOATCMD_TYPE_BAUDRATE,param.Get());
  if(error!=DIOATCMD_ERROR_NONE) return error;

  error =  WaitToProcessAnswer(timeout);
  if(error!=DIOATCMD_ERROR_NONE) return error;

  DIOSTREAMUARTCONFIG* diostreamcfg = (DIOSTREAMUARTCONFIG*)diostream->GetConfig();
  if(diostreamcfg)
    {
      if(!diostream->Close()) return DIOATCMD_ERROR_INVALIDCMD;

      diostreamcfg->SetBaudRate(baudrate);

      if(!diostream->Open())  return DIOATCMD_ERROR_INVALIDCMD;
    }

  return error;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOATCMDS::End()
* @brief      End
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOATCMDS::End()
{
  if(threadconnection) threadconnection->End();

  if(diostream) diostream->Close();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOATCMDS::AdditionalInitialization(int timeout)
* @brief      Additional initialization
* @ingroup    DATAIO
*
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOATCMDS::AdditionalInitialization(int timeout)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOATCMDS::UnsolicitedCommandAddtionalSize(XDWORD type, XSTRING& param, DIOATCMD_TYPEADDITIONALSIZE& typesize, int& size)
* @brief      Unsolicited command addtional size
* @ingroup    DATAIO
*
* @param[in]  type :
* @param[in]  param :
* @param[in]  typesize :
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOATCMDS::UnsolicitedCommandAddtionalSize(XDWORD type, XSTRING& param, DIOATCMD_TYPEADDITIONALSIZE& typesize, int& size)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOATCMDS::UnsolicitedCommand(XDWORD type, XSTRING& param, XBUFFER& additionalparamint)
* @brief      Unsolicited command
* @ingroup    DATAIO
*
* @param[in]  type :
* @param[in]  param :
* @param[in]  additionalparamint :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOATCMDS::UnsolicitedCommand(XDWORD type, XSTRING& param, XBUFFER& additionalparamint)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOATCMDS::CalculeBaudRateStreamUART(int timeout)
* @brief      Calcule baud rate stream UART
* @ingroup    DATAIO
*
* @param[in]  timeout :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOATCMDS::CalculeBaudRateStreamUART(int timeout)
{
  int baudrates[] = { 115200, 9600, 57600, 38400, 19200, 4800, 2400 , 1200 };
  int baudrate    = 0;

  DIOSTREAMUARTCONFIG* diostreamcfg = (DIOSTREAMUARTCONFIG*)diostream->GetConfig();
  if(!diostreamcfg) return 0;

  if(diostreamcfg->GetType() != DIOSTREAMTYPE_UART) return 0;

  for(int c=0;c<sizeof(baudrates)/sizeof(int);c++)
    {
      diostreamcfg->SetBaudRate(baudrates[c]);

      //XTRACE_PRINT(__L("Open connection: %d bauds"),baudrates[c]);

      diostream->ResetXBuffers();

      diostream->Close();
      if(!diostream->Open())  return 0;

      if(diostream->WaitToConnected(timeout))
        {
          if(threadconnection) threadconnection->Ini();

          echomode = false;
          if(Basic(timeout)==DIOATCMD_ERROR_NONE) baudrate = baudrates[c];

          echomode = true;
          if(Basic(timeout)==DIOATCMD_ERROR_NONE)  baudrate = baudrates[c];

          if(threadconnection) threadconnection->End();

          if(baudrate) break;

        }
    }

  diostream->Close();

  return baudrate;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOATCMDS::AddCommand(XDWORD type, XCHAR* command,bool isunsolicited)
* @brief      Add command
* @ingroup    DATAIO
*
* @param[in]  type :
* @param[in]  command :
* @param[in]  isunsolicited :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOATCMDS::AddCommand(XDWORD type, XCHAR* command,bool isunsolicited)
{
  DIOATCMD* ATcommand = GetCommand(type);
  if(ATcommand) return false;

  ATcommand = new DIOATCMD();
  if(!ATcommand) return false;

  ATcommand->Set(type,command,isunsolicited);

  ATcmds.Add(ATcommand);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOATCMD* DIOATCMDS::GetCommand(XDWORD type)
* @brief      Get command
* @ingroup    DATAIO
*
* @param[in]  type :
*
* @return     DIOATCMD* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOATCMD* DIOATCMDS::GetCommand(XDWORD type)
{
  DIOATCMD* ATcommand;

  for(int c=0;c<(int)ATcmds.GetSize();c++)
    {
       ATcommand = (DIOATCMD*)ATcmds.Get(c);
       if(ATcommand)
         {
           if(ATcommand->GetType() == type) return ATcommand;
         }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XCHAR* DIOATCMDS::GetCommandString(XDWORD type)
* @brief      Get command string
* @ingroup    DATAIO
*
* @param[in]  type :
*
* @return     XCHAR* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR* DIOATCMDS::GetCommandString(XDWORD type)
{
  DIOATCMD* command = GetCommand(type);
  if(!command) return NULL;

  return command->GetCommand();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOATCMDS::DeleteAllCommand()
* @brief      Delete all command
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOATCMDS::DeleteAllCommand()
{
  if(ATcmds.IsEmpty()) return false;

  ATcmds.DeleteContents();

  ATcmds.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOATCMD_ERROR DIOATCMDS::SendCommand(XDWORD type,XCHAR* param)
* @brief      Send command
* @ingroup    DATAIO
*
* @param[in]  type :
* @param[in]  param :
*
* @return     DIOATCMD_ERROR :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOATCMD_ERROR DIOATCMDS::SendCommand(XDWORD type,XCHAR* param)
{
  DIOATCMD* ATcommand = GetCommand(type);
  if(!ATcommand) return DIOATCMD_ERROR_UNKNOWNCMD;

  XSTRING command( __L("AT"));
  command += ATcommand->GetCommand();

  if(param) command += param;

  if(echomode) AddSendCommand(&command);

  command.Add(endlinechar);

  if(mutexreadwriteprocess) mutexreadwriteprocess->Lock();

  XBUFFER charstr;
  
  command.ConvertToASCII(charstr); 
  bool status = diostream->WriteStr(charstr.GetPtrChar());  
  if(status) status = diostream->WaitToFlushOutXBuffer(10);

  if(mutexreadwriteprocess) mutexreadwriteprocess->UnLock();

  if(!status) return DIOATCMD_ERROR_WRITECMD;

  //XTRACE_PRINT(__L("> %s"),command.Get());

  return DIOATCMD_ERROR_NONE;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOATCMD_ERROR DIOATCMDS::SendCommand(XDWORD type,XSTRING& param)
* @brief      Send command
* @ingroup    DATAIO
*
* @param[in]  type :
* @param[in]  param :
*
* @return     DIOATCMD_ERROR :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOATCMD_ERROR DIOATCMDS::SendCommand(XDWORD type, XSTRING& param)
{
  return DIOATCMDS::SendCommand(type,param.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOATCMD_ERROR DIOATCMDS::SendParam(XCHAR* param)
* @brief      Send param
* @ingroup    DATAIO
*
* @param[in]  param :
*
* @return     DIOATCMD_ERROR :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOATCMD_ERROR DIOATCMDS::SendParam(XCHAR* param)
{
  XSTRING _param;

  _param = param;

  if(_param.IsEmpty()) return DIOATCMD_ERROR_NONE;

  if(echomode) AddSendCommand(&_param);

  if(mutexreadwriteprocess) mutexreadwriteprocess->Lock();

  XBUFFER charstr;
  
  _param.ConvertToASCII(charstr);
  bool status = diostream->WriteStr(charstr.GetPtrChar());
  
  if(mutexreadwriteprocess) mutexreadwriteprocess->UnLock();

  if(!status) return DIOATCMD_ERROR_WRITECMD;

  //XTRACE_PRINT(__L("> %s"),_param.Get());

  return DIOATCMD_ERROR_NONE;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOATCMD_ERROR DIOATCMDS::SendParam(XBUFFER& xbuffer)
* @brief      Send param
* @ingroup    DATAIO
*
* @param[in]  xbuffer :
*
* @return     DIOATCMD_ERROR :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOATCMD_ERROR DIOATCMDS::SendParam(XBUFFER& xbuffer)
{
  if(!xbuffer.GetSize())  return DIOATCMD_ERROR_NONE;

  if(echomode) AddSendCommand(xbuffer);

  if(mutexreadwriteprocess) mutexreadwriteprocess->Lock();

  XDWORD status = diostream->Write(xbuffer);

  if(mutexreadwriteprocess) mutexreadwriteprocess->UnLock();

  if(!status) return DIOATCMD_ERROR_WRITECMD;

  /*
  #ifdef XTRACE_ACTIVE
  XSTRING string;

  for(int c=0;c<(int)xbuffer.GetSize();c++)
    {
      string.Add((XBYTE)xbuffer.GetByte(c));
    }

  XTRACE_PRINT(__L("1< %s"),string.Get());
  #endif
  */

  return DIOATCMD_ERROR_NONE;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOATCMD_ERROR DIOATCMDS::SendParam(XSTRING& param)
* @brief      Send param
* @ingroup    DATAIO
*
* @param[in]  param :
*
* @return     DIOATCMD_ERROR :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOATCMD_ERROR DIOATCMDS::SendParam(XSTRING& param)
{
  return DIOATCMDS::SendParam(param.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOATCMDS::AddSendCommand(XSTRING* sendcommand)
* @brief      Add send command
* @ingroup    DATAIO
*
* @param[in]  sendcommand :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOATCMDS::AddSendCommand(XSTRING* sendcommand)
{
  if(!sendcommand)           return false;
  if(sendcommand->IsEmpty()) return false;

  XSTRING* sc = new XSTRING();
  if(!sc) return false;

  for(XDWORD c=0;c<sendcommand->GetSize();c++)
    {
      XCHAR character = sendcommand->Get()[c];
      if((character!=endlinechar) && (character!=answerchar))  sc->Add(character);
    }

  sendcommands.Add(sc);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOATCMDS::AddSendCommand(XBUFFER& xbuffer)
* @brief      Add send command
* @ingroup    DATAIO
*
* @param[in]  xbuffer :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOATCMDS::AddSendCommand(XBUFFER& xbuffer)
{
  XSTRING param;

  param.Set(xbuffer.Get(),xbuffer.GetSize());

  return AddSendCommand(&param);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOATCMDS::GetSendCommand(int index)
* @brief      Get send command
* @ingroup    DATAIO
*
* @param[in]  index :
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOATCMDS::GetSendCommand(int index)
{
  XSTRING* sendcommand = (XSTRING*)sendcommands.Get(index);
  if(!sendcommand) return NULL;

  return sendcommand;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOATCMDS::SearchSendCommand(XSTRING* sendcommand)
* @brief      Search send command
* @ingroup    DATAIO
*
* @param[in]  sendcommand :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOATCMDS::SearchSendCommand(XSTRING* sendcommand)
{
  if(!sendcommand) return DIOATCMDS_COMMANDNOTFOUND;

  for(int c=0;c<(int)sendcommands.GetSize();c++)
    {
      XSTRING* sc = (XSTRING*)sendcommands.Get(c);
      if(sc)
        {
          if(!sc->Compare((*sendcommand))) return c;
        }
    }

  return DIOATCMDS_COMMANDNOTFOUND;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOATCMDS::DeleteSendCommand(int index)
* @brief      Delete send command
* @ingroup    DATAIO
*
* @param[in]  index :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOATCMDS::DeleteSendCommand(int index)
{
  XSTRING* sendcommand = (XSTRING*)sendcommands.Get(index);
  if(!sendcommand) return false;

  delete sendcommand;
  sendcommands.DeleteIndex(index);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOATCMDS::DeleteAllSendCommand()
* @brief      Delete all send command
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOATCMDS::DeleteAllSendCommand()
{
  if(sendcommands.IsEmpty()) return false;

  sendcommands.DeleteContents();

  sendcommands.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOATCMDS::ReadAnswer(XSTRING& answer,int timeout)
* @brief      Read answer
* @ingroup    DATAIO
*
* @param[in]  answer :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOATCMDS::ReadAnswer(XSTRING& answer,int timeout)
{
  if(!diostream) return false;
  if(!xtimer)    return false;

  XBUFFER* bufferread = diostream->GetInXBuffer();
  XDWORD   index      = 0;
  XBYTE    data;
  bool     status     = true;

  if(!bufferread) return false;

  answer.Empty();

  xtimer->Reset();

  do{ if(bufferread->GetSize()>index)
        {
          if(bufferread->Get(data,index))
            {
              if(data==endlinechar)
                {
                  index++;

                  if(bufferread->GetSize()>index)
                    {
                      if(bufferread->Get(data,index))
                        {
                          if(data==answerchar) index++;
                        }
                    }

                  break;

                } else index++;
            }
        }

      if((int)xtimer->GetMeasureSeconds()>=timeout)
        {
          status = false;
          break;

        } else GEN_XSLEEP.MilliSeconds(10);

    } while(1);

  if(status)
    {
      for(XDWORD c=0;c<index;c++)
        {
          XBYTE byte;
          int   br;

          br = diostream->Read((XBYTE*)&byte,1);
          if(br)
            {
              if((byte!=endlinechar) && (byte!=answerchar))  answer.Add(byte);
            }
        }

      /*
      #ifdef XTRACE_ACTIVE
      if(!answer.IsEmpty()) XTRACE_PRINT(__L("2< %s"),answer.Get());
      #endif
      */

    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOATCMDS::ReadAnswerWithOutEndChar(XSTRING& answer, int timeout)
* @brief      Read answer with out end char
* @ingroup    DATAIO
*
* @param[in]  answer :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOATCMDS::ReadAnswerWithOutEndChar(XSTRING& answer, int timeout)
{
  if(!diostream)       return false;
  if(!xtimer)          return false;
  if(answer.IsEmpty()) return false;

  XBUFFER* bufferread = diostream->GetInXBuffer();
  XBYTE    data;
  int      index      = 0;
  bool     status     = true;
  int      c;

  if(!bufferread) return false;

  xtimer->Reset();

  do{ if(bufferread->GetSize())
        {
          if(bufferread->GetSize()>=answer.GetSize())
            {
              for(c=0;c<(int)bufferread->GetSize();c++)
                {
                  if(bufferread->Get(data,c))
                    {
                      if(data==answer[c]) index++; else break;

                    }
                }

              if(index == answer.GetSize()) break;
            }
        }

      if((int)xtimer->GetMeasureSeconds()>=timeout)
        {
          status = false;
          break;

        } else GEN_XSLEEP.MilliSeconds(10);

    } while(1);

  if(!status)                   return false;
  if(index != answer.GetSize()) return false;

  for(c=0;c<index;c++)
    {
      XBYTE byte;
      int   br;

      br = diostream->Read((XBYTE*)&byte,1);
      if(!br) status = false;
    }

  /*
  #ifdef XTRACE_ACTIVE
  if(!answer.IsEmpty()) XTRACE_PRINT(__L("3< %s"),answer.Get());
  #endif
  */

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOATCMDS::ReadAnswerWithOutEndChar(XCHAR* answer, int timeout)
* @brief      Read answer with out end char
* @ingroup    DATAIO
*
* @param[in]  answer :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOATCMDS::ReadAnswerWithOutEndChar(XCHAR* answer, int timeout)
{
  XSTRING _answer;

  _answer = answer;

  return ReadAnswerWithOutEndChar(_answer,timeout);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOATCMDS::GetAnswer(int index)
* @brief      Get answer
* @ingroup    DATAIO
*
* @param[in]  index :
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOATCMDS::GetAnswer(int index)
{
  XSTRING* answer = (XSTRING*)answers.Get(index);
  if(!answer) return NULL;

  return answer;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOATCMDS::GetLastAnswer()
* @brief      Get last answer
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOATCMDS::GetLastAnswer()
{
  XSTRING* answer = (XSTRING*)answers.GetLast();
  return answer;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOATCMDS::DeleteAnswer(int index)
* @brief      Delete answer
* @ingroup    DATAIO
*
* @param[in]  index :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOATCMDS::DeleteAnswer(int index)
{
  XSTRING* answer = (XSTRING*)answers.Get(index);
  if(!answer) return false;

  delete answer;
  answers.DeleteIndex(index);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOATCMDS::DeleteLastAnswer()
* @brief      Delete last answer
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOATCMDS::DeleteLastAnswer()
{
  XSTRING* answer = (XSTRING*)answers.GetLast();
  if(!answer) return false;

  int index = answers.GetSize();
  if(!index) return false;

  index--;

  delete answer;
  answers.DeleteIndex(index);

  return true;

}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOATCMDS::DeleteAllAnswers()
* @brief      Delete all answers
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOATCMDS::DeleteAllAnswers()
{
  if(answers.IsEmpty()) return false;

  answers.DeleteContents();

  answers.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XVECTOR<XSTRING*>* DIOATCMDS::GetAnswers()
* @brief      Get answers
* @ingroup    DATAIO
*
* @return     XVECTOR<XSTRING*>* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<XSTRING*>* DIOATCMDS::GetAnswers()
{
  return &answers;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOATCMDS::SearchInAnswers(XCHAR* string, int timeout)
* @brief      Search in answers
* @ingroup    DATAIO
*
* @param[in]  string :
* @param[in]  timeout :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOATCMDS::SearchInAnswers(XCHAR* string, int timeout)
{
  if(timeout) xtimer->Reset();

  while(1)
    {
      for(int c=0;c<(int)answers.GetSize();c++)
        {
          XSTRING* answer = (XSTRING*)answers.Get(c);
          if(answer)
            {
              if(answer->Find(string,true)!=XSTRING_NOTFOUND) return c;
            }
        }

      if(timeout)
        {
          if((int)xtimer->GetMeasureSeconds()>=timeout)
            {
              return -1;

            } else GEN_XSLEEP.MilliSeconds(10);

        } else break;

    }

  return DIOATCMDS_ANSWERNOTFOUND;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOATCMDS::SearchInAnswers(XDWORD typecommand,int timeout)
* @brief      Search in answers
* @ingroup    DATAIO
*
* @param[in]  typecommand :
* @param[in]  timeout :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOATCMDS::SearchInAnswers(XDWORD typecommand,int timeout)
{
  DIOATCMD* command = GetCommand(typecommand);
  if(!command) return DIOATCMDS_ANSWERNOTFOUND;

  XSTRING string;

  string = command->GetCommand();
  string += __L(":");

  return SearchInAnswers(string.Get(),timeout);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOATCMD_ERROR DIOATCMDS::WaitToProcessAnswer(int timeout, int* index)
* @brief      Wait to process answer
* @ingroup    DATAIO
*
* @param[in]  timeout :
* @param[in]  index :
*
* @return     DIOATCMD_ERROR :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOATCMD_ERROR DIOATCMDS::WaitToProcessAnswer(int timeout, int* index)
{
  if(!xtimer) return DIOATCMD_ERROR_UNKNOWN;

  xtimer->Reset();

  do{ for(int c=0;c<(int)answers.GetSize();c++)
        {
          XSTRING* answer = (XSTRING*)answers.Get(c);
          if(answer)
            {
              if((!answer->Compare(__L("OK")))  || (!answer->Compare(__L("0"))))
                {
                  if(index) (*index) = c;
                  DeleteAnswer(c);
                  return DIOATCMD_ERROR_NONE;
                }

              if((!answer->Compare(__L("ERROR")))  || (!answer->Compare(__L("1"))))
                {
                  if(index) (*index) = c;
                  DeleteAnswer(c);
                  return DIOATCMD_ERROR_INVALIDCMD;
                }
            }
        }

      if((int)xtimer->GetMeasureSeconds()>=timeout)
        {
          return DIOATCMD_ERROR_TIMEOUT;

        } else GEN_XSLEEP.MilliSeconds(50);

    } while(1);

  return DIOATCMD_ERROR_UNKNOWN;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOATCMD_ERROR DIOATCMDS::WaitToOneAnswerMore(int timeout)
* @brief      Wait to one answer more
* @ingroup    DATAIO
*
* @param[in]  timeout :
*
* @return     DIOATCMD_ERROR :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOATCMD_ERROR DIOATCMDS::WaitToOneAnswerMore(int timeout)
{
  if(!xtimer) return DIOATCMD_ERROR_UNKNOWN;

  int actualnanswer = (int)answers.GetSize();

  xtimer->Reset();

  do{ if((int)xtimer->GetMeasureSeconds()>=timeout)
        {
          return DIOATCMD_ERROR_TIMEOUT;

        } else GEN_XSLEEP.MilliSeconds(50);

    } while(actualnanswer == (int)answers.GetSize());

  return DIOATCMD_ERROR_NONE;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOATCMD_ERROR DIOATCMDS::MakeSimpleCommand(XDWORD type,XCHAR* param,int timeout)
* @brief      Make simple command
* @ingroup    DATAIO
*
* @param[in]  type :
* @param[in]  param :
* @param[in]  timeout :
*
* @return     DIOATCMD_ERROR :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOATCMD_ERROR DIOATCMDS::MakeSimpleCommand(XDWORD type,XCHAR* param,int timeout)
{
  DIOATCMD_ERROR error = SendCommand(type,param);
  if(error!=DIOATCMD_ERROR_NONE) return error;

  return WaitToProcessAnswer(timeout);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOATCMD_ERROR DIOATCMDS::MakeCommandWithSimpleAnswer(XDWORD type,XSTRING& answer,XCHAR* param,int timeout)
* @brief      Make command with simple answer
* @ingroup    DATAIO
*
* @param[in]  type :
* @param[in]  answer :
* @param[in]  param :
* @param[in]  timeout :
*
* @return     DIOATCMD_ERROR :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOATCMD_ERROR DIOATCMDS::MakeCommandWithSimpleAnswer(XDWORD type, XSTRING& answer, XCHAR* param, int timeout)
{
  DIOATCMD_ERROR error = SendCommand(type);
  if(error!=DIOATCMD_ERROR_NONE) return error;

  int index=0;

  error = WaitToProcessAnswer(timeout,&index);
  if(error!=DIOATCMD_ERROR_NONE) return error;

  XSTRING* _answer = GetAnswer(index-1);
  if(_answer)
    {
      answer = (*_answer);
      DeleteAnswer(index-1);
    }

  return DIOATCMD_ERROR_NONE;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOATCMDS::ThreadConnection(void* data)
* @brief      Thread connection
* @ingroup    DATAIO
*
* @param[in]  param :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOATCMDS::ThreadConnection(void* param)
{
  DIOATCMDS* dioatcmds = (DIOATCMDS*)param;
  if(!dioatcmds) return;

  DIOSTREAM* diostream = dioatcmds->GetDIOStream();
  if(!diostream) return;

  if(diostream->GetStatus()!=DIOSTREAMSTATUS_CONNECTED) return;

  XBUFFER* bufferread = diostream->GetInXBuffer();
  if(bufferread)
    {
      if(bufferread->GetSize())
        {
          if(dioatcmds->mutexreadwriteprocess) dioatcmds->mutexreadwriteprocess->Lock();

          XSTRING answer;

          if(dioatcmds->ReadAnswer(answer))
            {
              if(!answer.IsEmpty())
                {
                  if(dioatcmds->echomode)
                    {
                      int index = dioatcmds->SearchSendCommand(&answer);
                      if(index!=DIOATCMDS_COMMANDNOTFOUND)
                        {
                          dioatcmds->DeleteSendCommand(index);
                          if(dioatcmds->mutexreadwriteprocess) dioatcmds->mutexreadwriteprocess->UnLock();
                          return;
                        }
                    }

                  if(!dioatcmds->CheckUnsolicitedAnswer(answer))
                    {
                      XSTRING* answerkeep = new XSTRING();
                      if(answerkeep)
                        {
                          (*answerkeep) = answer;
                          dioatcmds->answers.Add(answerkeep);
                        }
                    }
                }
            }

          if(dioatcmds->mutexreadwriteprocess) dioatcmds->mutexreadwriteprocess->UnLock();
        }
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOATCMDS::CheckUnsolicitedAnswer(XSTRING& answer)
* @brief      Check unsolicited answer
* @ingroup    DATAIO
*
* @param[in]  answer :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOATCMDS::CheckUnsolicitedAnswer(XSTRING& answer)
{
  if(answer.IsEmpty())  return false;
  if(ATcmds.IsEmpty())   return false;

  for(int c=0;c<(int)ATcmds.GetSize();c++)
    {
      DIOATCMD* atcmd = (DIOATCMD*)ATcmds.Get(c);
      if(atcmd)
        {
          if(atcmd->IsUnSolicited())
            {
              int index = answer.Find(atcmd->GetCommand(),false);
              if(index!=XSTRING_NOTFOUND)
                {
                  XSTRING                      param;
                  XBUFFER                      additionalparam;
                  DIOATCMD_TYPEADDITIONALSIZE  typesize = DIOATCMD_TYPEADDITIONALSIZE_NONE;
                  int                          sizedata = 0;

                  answer.Copy(index+atcmd->GetCommandString()->GetSize()+1,param);

                  if(UnsolicitedCommandAddtionalSize(atcmd->GetType(),param,typesize,sizedata))
                    {
                      switch(typesize)
                        {
                          case DIOATCMD_TYPEADDITIONALSIZE_NONE   : break;

                          case DIOATCMD_TYPEADDITIONALSIZE_BYTES  : additionalparam.Resize(sizedata);
                                                                    diostream->Read((XBYTE*)additionalparam.Get(),sizedata);
                                                                    break;

                          case DIOATCMD_TYPEADDITIONALSIZE_LINES  : { XSTRING line;
                                                                      int     d = 0;

                                                                      while(d<sizedata)
                                                                        {
                                                                          if(ReadAnswer(line))
                                                                            {
                                                                              if(!line.IsEmpty())
                                                                                {
                                                                                  XBUFFER charstr;
                                                                                  
                                                                                  line.ConvertToASCII(charstr);
                                                                                  additionalparam.Add((XBYTE*)charstr.Get(), (XDWORD)line.GetSize());
                                                                                  
                                                                                  d++;
                                                                                }
                                                                            }

                                                                        }
                                                                    }
                                                                    break;
                        }

                      return UnsolicitedCommand(atcmd->GetType(),param,additionalparam);

                    } else return false;
                }
            }
        }
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOATCMDS::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOATCMDS::Clean()
{
  diostream               = NULL;
  xtimer                  = NULL;

  mutexreadwriteprocess  = NULL;
  threadconnection         = NULL;

  echomode                = false;
  verbosemode             = false;

  escapechar              =  3;
  endlinechar             = 13;
  answerchar              = 10;
  delchar                 =  8;
}


#pragma endregion

