/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XWINDOWSProcessManager.cpp
*
* @class      XWINDOWSPROCESSMANAGER
* @brief      eXtended WINDOWS process manager class
* @ingroup    PLATFORM_WINDOWS
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <windows.h>
#include <tlhelp32.h>
#include <process.h>

#include "XFactory.h"
#include "XFile.h"
#include "XSleep.h"
#include "XTrace.h"

#include "XWINDOWSProcessManager.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWINDOWSPROCESSMANAGER::XWINDOWSPROCESSMANAGER() : XSYSTEM()
* @brief      Constructor
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  ) :
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XWINDOWSPROCESSMANAGER::XWINDOWSPROCESSMANAGER() : XPROCESSMANAGER()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWINDOWSPROCESSMANAGER::~XWINDOWSPROCESSMANAGER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XWINDOWSPROCESSMANAGER::~XWINDOWSPROCESSMANAGER()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSPROCESSMANAGER::MakeSystemCommand(XCHAR* command)
* @brief      MakeSystemCommand
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  command : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSPROCESSMANAGER::MakeSystemCommand(XCHAR* command)
{
  return (_wsystem(command) == -1)?false:true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSPROCESSMANAGER::MakeCommand(XCHAR* command, XSTRING& out, int* returncode)
* @brief      MakeCommand
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  command :
* @param[in]  out :
* @param[in]  returncode :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSPROCESSMANAGER::MakeCommand(XCHAR* command, XSTRING* out, int* returncode)
{
  char    buffer[256];
  FILE*   pipe;

  if((pipe = _wpopen(command, __L("rt") )) == NULL) return false;

  if(out)
    {
      while(fgets(buffer, 256, pipe))
       {
         (*out) += buffer;
       }
    }

  if(feof(pipe))
    {
      if(returncode) (*returncode) =  _pclose(pipe);
    }
   else
    {
      return false;
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSPROCESSMANAGER::ExecuteApplication(XCHAR* applicationpath, XCHAR* params, XSTRING* in, XSTRING* out, int* returncode)
* @brief      ExecuteApplication
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  applicationpath : 
* @param[in]  params : 
* @param[in]  in : 
* @param[in]  out : 
* @param[in]  returncode : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
/*
bool XWINDOWSPROCESSMANAGER::ExecuteApplication(XCHAR* applicationpath, XCHAR* params, XSTRING* in, XSTRING* out, int* returncode)
{
  PROCESS_INFORMATION processinfo;
  STARTUPINFOA        startupinfo;
  SECURITY_ATTRIBUTES saattr;
  char                cmdline[256];
  char                outbuf[32768];
  DWORD               bytes_read;
  char                tBuf[257];
  DWORD               exitcode;
  HANDLE              stdhandle_out_read  = NULL;
  HANDLE              stdhandle_out_write = NULL;
  HANDLE              stdhandle_in_read   = NULL;
  HANDLE              stdhandle_in_write  = NULL;
  XSTRING             _command;
  bool                status = false;

  _command = applicationpath;
  if(params) _command.AddFormat(__L(" %s"), params);
    
  XSTRING_CREATEOEM(_command, chrcommand)
  memcpy(cmdline, chrcommand, strlen(chrcommand)+1);
  XSTRING_DELETEOEM(_command, chrcommand)

  memset(&saattr, 0, sizeof(saattr));
  saattr.nLength              = sizeof(SECURITY_ATTRIBUTES);
  saattr.bInheritHandle       = TRUE;
  saattr.lpSecurityDescriptor = NULL;

  // Create a pipe for the child process's STDOUT.
  if(!CreatePipe(&stdhandle_out_read, &stdhandle_out_write, &saattr, 0))  return false;
  // Ensure the read handle to the pipe for STDOUT is not inherited.
  if(!SetHandleInformation(stdhandle_out_read, HANDLE_FLAG_INHERIT, 0))   return false;

  // Create a pipe for the child process's STDIN.
  if(!CreatePipe(&stdhandle_in_read, &stdhandle_in_write, &saattr, 0))    return false;
  // Ensure the read handle to the pipe for STDIN is not inherited.
  if(!SetHandleInformation(stdhandle_in_write, HANDLE_FLAG_INHERIT, 0))   return false;

  ZeroMemory(&processinfo, sizeof(PROCESS_INFORMATION));

  ZeroMemory(&startupinfo, sizeof(STARTUPINFO));
  startupinfo.cb          = sizeof(startupinfo);
  startupinfo.hStdError   = stdhandle_out_write;
  startupinfo.hStdOutput  = stdhandle_out_write;
  startupinfo.hStdInput   = stdhandle_in_read;    // GetStdHandle(STD_INPUT_HANDLE);
  startupinfo.dwFlags    |= STARTF_USESTDHANDLES;

  if(CreateProcessA(NULL, cmdline, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &startupinfo, &processinfo))
    {
      CloseHandle(stdhandle_out_write);

      //-----------------------------------------------------------------------------

      if(in)
        {
          if(in->GetSize())
            {
              DWORD bytes_write;

              XSTRING_CREATEOEM((*in), chrin)
              WriteFile(stdhandle_in_write, chrin, in->GetSize(), &bytes_write, NULL);
              XSTRING_DELETEOEM((*in), chrin)

              FlushFileBuffers(stdhandle_in_write);
            }
        }

      CloseHandle(stdhandle_in_write);

      //-----------------------------------------------------------------------------

      if(out)
        {
          strcpy(outbuf, "");

          for(;;)
            {
              if(!ReadFile(stdhandle_out_read, tBuf, 256, &bytes_read, NULL))
                {
                  break;
                }

              if(bytes_read > 0)
                {
                  tBuf[bytes_read] = '\0';
                  strcat(outbuf, tBuf);
                }
            }

          (*out) = outbuf;
        }

      if(WaitForSingleObject(processinfo.hProcess, INFINITE) == WAIT_OBJECT_0)
        {
          if(GetExitCodeProcess(processinfo.hProcess, &exitcode))
            {
              if(returncode) (*returncode) = exitcode;
            }

          CloseHandle(processinfo.hProcess);
          CloseHandle(processinfo.hThread);

          status = true;
        }
    }

  return status;
}
*/

bool XWINDOWSPROCESSMANAGER::ExecuteApplication(XCHAR* applicationpath, XCHAR* params, XSTRING* in, XSTRING* out, int* returncode)
{
  #define CMDLINE_SIZE  (10*1024)
  #define OUTBUF_SIZE   (10*1024*1024)
  #define TEMPBUF_SIZE  (10*1024)

  PROCESS_INFORMATION processinfo;
  STARTUPINFOA        startupinfo;
  SECURITY_ATTRIBUTES saattr;
  char*               cmdline             = NULL;
  char*               outbuf              = NULL;
  DWORD               bytes_read;
  char*               tempbuf             = NULL;
  DWORD               exitcode;
  HANDLE              stdhandle_out_read  = NULL;
  HANDLE              stdhandle_out_write = NULL;
  HANDLE              stdhandle_in_read   = NULL;
  HANDLE              stdhandle_in_write  = NULL;
  XSTRING             _command;
  bool                status = false;

  cmdline = new char[CMDLINE_SIZE];
  outbuf  = new char[OUTBUF_SIZE];
  tempbuf = new char[TEMPBUF_SIZE];

  if(cmdline && outbuf && tempbuf)
    {      
      _command.Format(__L("\"%s\""), applicationpath);
      
      if(params) _command.AddFormat(__L(" %s"), params);
    
      XSTRING_CREATEOEM(_command, chrcommand)
      memcpy(cmdline, chrcommand, strlen(chrcommand)+1);
      XSTRING_DELETEOEM(_command, chrcommand)

      memset(&saattr, 0, sizeof(saattr));
      saattr.nLength              = sizeof(SECURITY_ATTRIBUTES);
      saattr.bInheritHandle       = TRUE;
      saattr.lpSecurityDescriptor = NULL;

      // Create a pipe for the child process's STDOUT.
      if(!CreatePipe(&stdhandle_out_read, &stdhandle_out_write, &saattr, 0))  return false;
      // Ensure the read handle to the pipe for STDOUT is not inherited.
      if(!SetHandleInformation(stdhandle_out_read, HANDLE_FLAG_INHERIT, 0))   return false;

      // Create a pipe for the child process's STDIN.
      if(!CreatePipe(&stdhandle_in_read, &stdhandle_in_write, &saattr, 0))    return false;
      // Ensure the read handle to the pipe for STDIN is not inherited.
      if(!SetHandleInformation(stdhandle_in_write, HANDLE_FLAG_INHERIT, 0))   return false;

      ZeroMemory(&processinfo, sizeof(PROCESS_INFORMATION));

      ZeroMemory(&startupinfo, sizeof(STARTUPINFO));
      startupinfo.cb          = sizeof(startupinfo);
      startupinfo.hStdError   = stdhandle_out_write;
      startupinfo.hStdOutput  = stdhandle_out_write;
      startupinfo.hStdInput   = stdhandle_in_read;    // GetStdHandle(STD_INPUT_HANDLE);
      startupinfo.dwFlags    |= STARTF_USESTDHANDLES;

      if(CreateProcessA(NULL, cmdline, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &startupinfo, &processinfo))
        {
          CloseHandle(stdhandle_out_write);

          //-----------------------------------------------------------------------------

          if(in)
            {
              if(in->GetSize())
                {
                  DWORD bytes_write;

                  XSTRING_CREATEOEM((*in), chrin)
                  WriteFile(stdhandle_in_write, chrin, in->GetSize(), &bytes_write, NULL);
                  XSTRING_DELETEOEM((*in), chrin)

                  FlushFileBuffers(stdhandle_in_write);
                }
            }

          CloseHandle(stdhandle_in_write);

          //-----------------------------------------------------------------------------

          if(out)
            {
              strcpy(outbuf, "");

              for(;;)
                {
                  if(!ReadFile(stdhandle_out_read, tempbuf, TEMPBUF_SIZE-1, &bytes_read, NULL))
                    {
                      break;
                    }

                  if(bytes_read > 0)
                    {
                      tempbuf[bytes_read] = '\0';
                      strcat(outbuf, tempbuf);
                    }
                }

              (*out) = outbuf;
            }

          if(WaitForSingleObject(processinfo.hProcess, (out?INFINITE:500)) == WAIT_OBJECT_0)
            {
              if(out)
                {
                  if(GetExitCodeProcess(processinfo.hProcess, &exitcode))
                    {
                      if(returncode) (*returncode) = exitcode;
                    }

                  CloseHandle(processinfo.hProcess);
                  CloseHandle(processinfo.hThread);
                }

              status = true;
            }
        }
    }

  if(cmdline) delete [] cmdline;
  if(outbuf)  delete [] outbuf;
  if(tempbuf) delete [] tempbuf;

  return status;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSPROCESSMANAGER::IsApplicationRunning(XCHAR* applicationname, XDWORD* ID)
* @brief      Is Application Running
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  applicationname : application name
* @param[out] ID : ID of the application by SO
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSPROCESSMANAGER::IsApplicationRunning(XCHAR* applicationname, XDWORD* ID)
{
  PROCESSENTRY32 entry;
  HANDLE         snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
  bool           exists = false;

  entry.dwSize = sizeof(PROCESSENTRY32);

  if(Process32First(snapshot, &entry))
    {
      while(Process32Next(snapshot, &entry))
        {
          XSTRING nameapp  = entry.szExeFile;
          XSTRING _applicationname = applicationname;

          if(_applicationname.Find(nameapp, true) != XSTRING_NOTFOUND)
            {
              if(ID) (*ID) = entry.th32ProcessID;
              exists = true;
            }
        }
    }

  CloseHandle(snapshot);

  return exists;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XWINDOWSPROCESSMANAGER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XWINDOWSPROCESSMANAGER::Clean()
{

}