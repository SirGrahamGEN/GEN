/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XLINUXProcessManager.cpp
* 
* @class      XLINUXPROCESSMANAGER
* @brief      LINUX eXtended Utils process management class
* @ingroup    PLATFORM_LINUX
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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#include "XLINUXProcessManager.h"

#include "XLINUXFactory.h"

#include "XBuffer.h"
#include "XFile.h"
#include "XTrace.h"
#include "XString.h"
#include "XPath.h"

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
* @fn         XLINUXPROCESSMANAGER::XLINUXPROCESSMANAGER()
* @brief      Constructor of class
* @ingroup    PLATFORM_LINUX
*
* --------------------------------------------------------------------------------------------------------------------*/
XLINUXPROCESSMANAGER::XLINUXPROCESSMANAGER(): XPROCESSMANAGER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLINUXPROCESSMANAGER::~XLINUXPROCESSMANAGER()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    PLATFORM_LINUX
*
* --------------------------------------------------------------------------------------------------------------------*/
XLINUXPROCESSMANAGER::~XLINUXPROCESSMANAGER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXPROCESSMANAGER::MakeSystemCommand(XCHAR* command)
* @brief      Make system command
* @ingroup    PLATFORM_LINUX
*
* @param[in]  command : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLINUXPROCESSMANAGER::MakeSystemCommand(XCHAR* command)
{
  XSTRING   _command;
  bool      status = false;

  _command = command;
  
  XBUFFER cmdchar;
  
  _command.ConvertToASCII(cmdchar);  
  //printf(" -- %s\n", cmdchar.GetPtrChar());
  if(system(cmdchar.GetPtrChar()) == -1) status = false; else status = true;
    
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXPROCESSMANAGER::MakeCommand(XCHAR* command, XSTRING& out, int* returncode)
* @brief      Make command
* @ingroup    PLATFORM_LINUX
*
* @param[in]  command :
* @param[in]  out :
* @param[in]  returncode :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLINUXPROCESSMANAGER::MakeCommand(XCHAR* command, XBUFFER* out, int* returncode)
{
  XSTRING   _command;
  XBYTE   buffer[_MAXBUFFER];
  FILE*   pipe;
  bool    status = true;

  _command = command;

  XBUFFER cmdchar;
  
  _command.ConvertToASCII(cmdchar);   
  pipe = popen(cmdchar.GetPtrChar(), "rt" );
  if(pipe == NULL) status = false;
  
  if(!status) return false;

  if(out)
    {
      memset(buffer, 0, _MAXBUFFER);

      while(fgets((char*)buffer, _MAXBUFFER, pipe))
        {
          out->Add((XBYTE*)buffer, SizeBufferASCII(buffer, _MAXBUFFER));
          memset(buffer, 0, _MAXBUFFER);
        }
    }

  // Close pipe and print return value of pPipe.
  if(feof(pipe))
    {
      if(returncode) (*returncode) =  pclose(pipe);
    }
   else
    {
      return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XLINUXPROCESSMANAGER::OpenURL(XCHAR* url)
* @brief      Open URL
* @ingroup    PLATFORM_LINUX
* 
* @param[in]  url : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XLINUXPROCESSMANAGER::OpenURL(XCHAR* url)
{
  XSTRING command = __L("xdg-open ");
  int     result  = -1;
 
  command.Add(url);

  result = MakeSystemCommand(command.Get());

  if(result == -1) 
    {
      return false;
    }
        
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XLINUXPROCESSMANAGER::Application_Execute(XCHAR* applicationpath, XCHAR* params, XBUFFER* in, XBUFFER* out, int* returncode)
* @brief      Application execute
* @ingroup    PLATFORM_LINUX
* 
* @param[in]  applicationpath : 
* @param[in]  params : 
* @param[in]  in : 
* @param[in]  out : 
* @param[in]  returncode : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XLINUXPROCESSMANAGER::Application_Execute(XCHAR* applicationpath, XCHAR* params, XBUFFER* in, XBUFFER* out, int* returncode)
{ 
  #define PIPE_READ   0
  #define PIPE_WRITE  1  
  #define MAXNPARAMS  20

  if(!applicationpath) return false;

  pid_t   pID;
  bool    exist  = false;
  bool    status = false;
  int     stdinpipe[2]  = { 0 , 0 };
  int     stdoutpipe[2] = { 0 , 0 };
  int     nresult = 0;  
  XSTRING _params;

  if(pipe(stdinpipe) < 0)
    {
      return -1;
    }

  if(pipe(stdoutpipe) < 0)
    {
      close(stdinpipe[PIPE_READ]);
      close(stdinpipe[PIPE_WRITE]);

      return -1;
    }


  XFILE* GEN_XFACTORY_CREATE(xfile, Create_File())
  if(xfile)
    {
      exist = xfile->Open(applicationpath);
      xfile->Close();
    }

  GEN_XFACTORY.Delete_File(xfile);

  if(!exist) return false;

  //-----------------------------------------
  // exec attributtes

  XSTRING cmd;

  cmd  = __L("chmod 775 ");
  cmd += applicationpath;


  XBUFFER charstr;
  
  cmd.ConvertToASCII(charstr);
  status = system(charstr.GetPtrChar());
  
  //if(status == -1) return false;

  //------------------------------------------

  cmd = applicationpath;
  
  _params.Add(cmd);
  if(params)
    {
      _params.Add(" ");
      _params.Add(params);
    }
 
  char*     param[MAXNPARAMS] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
                                };
  int       start             = 0;
  bool      endfound          = false;
  
  for(int c=0; c<MAXNPARAMS; c++)
    {
      XSTRING   string;
      XBUFFER   xbuffer;
      int       found = _params.Find(__L(" "), true, start);

      if(found == XSTRING_NOTFOUND)
        {
          _params.Copy(start, string);
          endfound = true;
        }
       else
        {
          _params.Copy(start, found, string);
          start = found+1;
        }

      string.ConvertToASCII(xbuffer);
         
      param[c] = new char[xbuffer.GetSize()+1];
      if(param[c])
        {
          memset(param[c], 0, xbuffer.GetSize()+1);
          memcpy(param[c], xbuffer.Get(), xbuffer.GetSize());         
        }
                 
      if(endfound) break;
    }

  pID = fork();
  
  if(pID == 0) 
    {
      // Child
      // redirect stdin
      if(dup2(stdinpipe[PIPE_READ], STDIN_FILENO)    == -1)
        {
          exit(errno);
        }

        // redirect stdout
      if(dup2(stdoutpipe[PIPE_WRITE], STDOUT_FILENO) == -1)
        {
          exit(errno);
        }

      // redirect stderr
      if(dup2(stdoutpipe[PIPE_WRITE], STDERR_FILENO) == -1)
        {
          exit(errno);
        }

      // all these are for use by parent only
      close(stdinpipe[PIPE_READ]);
      close(stdinpipe[PIPE_WRITE]);
      close(stdoutpipe[PIPE_READ]);
      close(stdoutpipe[PIPE_WRITE]);

      // run child process image
      // replace this with any exec* function find easier to use ("man exec")

      // Child
   
      XBUFFER charstr;
   
      cmd.ConvertToASCII(charstr);                                
      execl(charstr.GetPtrChar() , param[ 0], param[ 1], param[ 2], param[ 3], param[ 4], param[ 5], param[ 6], param[ 7], param[ 8], param[ 9]
                                 , param[10], param[11], param[12], param[13], param[14], param[15], param[16], param[17], param[18], param[19]
                                 , NULL);   
      _exit(127);
    } 
   else 
    {
      if(pID > 0) 
        {
          // parent
                    
          XBYTE nchar[_MAXBUFFER];  
          int   returnstatus = 0; 

          // close unused file descriptors, these are for child only
          close(stdinpipe[PIPE_READ]);
          close(stdoutpipe[PIPE_WRITE]);     

          if(in)
            {
              if(in->GetSize())
                {                  
                  write(stdinpipe[PIPE_WRITE], (char*)in->Get(), (int)in->GetSize());
                }
            }

          if(waitpid(pID, &returnstatus, 0) > 0) 
            {
              if(WIFEXITED(returnstatus) && !WEXITSTATUS(returnstatus)) 
                {
                  status = true;
                  if(returncode) (*returncode) = WEXITSTATUS(returnstatus);
                } 
               else 
                {
                  if(WIFEXITED(returnstatus) && WEXITSTATUS(returnstatus)) 
                    {                      
                      status = false;
                      if(returncode) (*returncode) = WEXITSTATUS(returnstatus);                      
                    } 
                   else 
                    {
                      status = true;
                      if(returncode) (*returncode) = WEXITSTATUS(returnstatus);
                    }
                }
            } 
           else 
            {
              status = false;
              if(returncode) (*returncode) = 1;
            }  

          if(out)
            { 
                
              int nread;
              do{ nread = read(stdoutpipe[PIPE_READ], nchar, _MAXBUFFER); 

                  if(nread)
                    {
                      out->Add((XBYTE*)nchar, nread);
                    }

                } while(nread == _MAXBUFFER);
                                
            } 

          close(stdinpipe[PIPE_WRITE]);
          close(stdoutpipe[PIPE_READ]);
                           
        } 
       else 
        {
          // Error fork 

          close(stdinpipe[PIPE_READ]);
          close(stdinpipe[PIPE_WRITE]);

          close(stdoutpipe[PIPE_READ]);
          close(stdoutpipe[PIPE_WRITE]);
          
          return false;
        }
    }

   for(int c=0; c<MAXNPARAMS; c++)
    {
      delete [] param[c];
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XLINUXPROCESSMANAGER::Application_Execute(XBUFFER* applicationpath, XBUFFER* params, XBUFFER* in, XBUFFER* out, int* returncode)
* @brief      application  execute
* @ingroup    PLATFORM_LINUX
* 
* @param[in]  applicationpath : 
* @param[in]  params : 
* @param[in]  in : 
* @param[in]  out : 
* @param[in]  returncode : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XLINUXPROCESSMANAGER::Application_Execute(XBUFFER* applicationpath, XBUFFER* params, XBUFFER* in, XBUFFER* out, int* returncode)
{
  #define PIPE_READ   0
  #define PIPE_WRITE  1  
  #define MAXNPARAMS  20

  if(!applicationpath) return false;

  pid_t   pID;
  bool    exist  = false;
  bool    status = false;
  int     stdinpipe[2]  = { 0 , 0 };
  int     stdoutpipe[2] = { 0 , 0 };
  int     nresult = 0;  
  XSTRING _params;

  if(pipe(stdinpipe) < 0)
    {
      return -1;
    }

  if(pipe(stdoutpipe) < 0)
    {
      close(stdinpipe[PIPE_READ]);
      close(stdinpipe[PIPE_WRITE]);

      return -1;
    }

  XSTRING _applicationpathstr; 
  XSTRING _paramsstr;

  _applicationpathstr.ConvertFromUTF8((*applicationpath));
  _paramsstr.ConvertFromUTF8((*params));

  XFILE* GEN_XFACTORY_CREATE(xfile, Create_File())
  if(xfile)
    {
      exist = xfile->Open(_applicationpathstr.Get());
      xfile->Close();
    }

  GEN_XFACTORY.Delete_File(xfile);

  if(!exist) return false;

  //-----------------------------------------
  // exec attributtes

  XSTRING cmd;
  XBUFFER charstr;

  cmd  = __L("chmod 775 ");
  cmd += _applicationpathstr;
  
  cmd.ConvertToUTF8(charstr);
  status = system(charstr.GetPtrChar());

  
  //if(status == -1) return false;

  //------------------------------------------

  cmd = _applicationpathstr;
  
  _params.Add(cmd);
  if(params)
    {
      _params.Add(" ");
      _params.Add(_paramsstr);
    }
 
  char*     param[MAXNPARAMS] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
                                };
  int       start             = 0;
  bool      endfound          = false;
  
  for(int c=0; c<MAXNPARAMS; c++)
    {
      XSTRING   string;
      XBUFFER   xbuffer;
      int       found = _params.Find(__L(" "), true, start);

      if(found == XSTRING_NOTFOUND)
        {
          _params.Copy(start, string);
          endfound = true;
        }
       else
        {
          _params.Copy(start, found, string);
          start = found+1;
        }

      string.ConvertToUTF8(xbuffer);
         
      param[c] = new char[xbuffer.GetSize()+1];
      if(param[c])
        {
          memset(param[c], 0, xbuffer.GetSize()+1);
          memcpy(param[c], xbuffer.Get(), xbuffer.GetSize());         
        }
                 
      if(endfound) break;
    }

  pID = fork();
  
  if(pID == 0) 
    {
      // Child
      // redirect stdin
      if(dup2(stdinpipe[PIPE_READ], STDIN_FILENO)    == -1)
        {
          exit(errno);
        }

        // redirect stdout
      if(dup2(stdoutpipe[PIPE_WRITE], STDOUT_FILENO) == -1)
        {
          exit(errno);
        }

      // redirect stderr
      if(dup2(stdoutpipe[PIPE_WRITE], STDERR_FILENO) == -1)
        {
          exit(errno);
        }

      // all these are for use by parent only
      close(stdinpipe[PIPE_READ]);
      close(stdinpipe[PIPE_WRITE]);
      close(stdoutpipe[PIPE_READ]);
      close(stdoutpipe[PIPE_WRITE]);

      // run child process image
      // replace this with any exec* function find easier to use ("man exec")

      // Child
   
      XBUFFER charstr;
   
      cmd.ConvertToASCII(charstr);                                
      execl(charstr.GetPtrChar() , param[ 0], param[ 1], param[ 2], param[ 3], param[ 4], param[ 5], param[ 6], param[ 7], param[ 8], param[ 9]
                                 , param[10], param[11], param[12], param[13], param[14], param[15], param[16], param[17], param[18], param[19]
                                 , NULL);   
      _exit(127);
    } 
   else 
    {
      if(pID > 0) 
        {
          // parent
                    
          XBYTE nchar[_MAXBUFFER];  
          int   returnstatus = 0; 

          // close unused file descriptors, these are for child only
          close(stdinpipe[PIPE_READ]);
          close(stdoutpipe[PIPE_WRITE]);     

          if(in)
            {
              if(in->GetSize())
                {                  
                  write(stdinpipe[PIPE_WRITE], (char*)in->Get(), (int)in->GetSize());
                }
            }

          if(waitpid(pID, &returnstatus, 0) > 0) 
            {
              if(WIFEXITED(returnstatus) && !WEXITSTATUS(returnstatus)) 
                {
                  status = true;
                  if(returncode) (*returncode) = WEXITSTATUS(returnstatus);
                } 
               else 
                {
                  if(WIFEXITED(returnstatus) && WEXITSTATUS(returnstatus)) 
                    {                      
                      status = false;
                      if(returncode) (*returncode) = WEXITSTATUS(returnstatus);                      
                    } 
                   else 
                    {
                      status = true;
                      if(returncode) (*returncode) = WEXITSTATUS(returnstatus);
                    }
                }
            } 
           else 
            {
              status = false;
              if(returncode) (*returncode) = 1;
            }  

          if(out)
            { 
                
              int nread;
              do{ nread = read(stdoutpipe[PIPE_READ], nchar, _MAXBUFFER); 

                  if(nread)
                    {
                      out->Add((XBYTE*)nchar, nread);
                    }

                } while(nread == _MAXBUFFER);
                                
            } 

          close(stdinpipe[PIPE_WRITE]);
          close(stdoutpipe[PIPE_READ]);
                           
        } 
       else 
        {
          // Error fork 

          close(stdinpipe[PIPE_READ]);
          close(stdinpipe[PIPE_WRITE]);

          close(stdoutpipe[PIPE_READ]);
          close(stdoutpipe[PIPE_WRITE]);
          
          return false;
        }
    }

   for(int c=0; c<MAXNPARAMS; c++)
    {
      delete [] param[c];
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXPROCESSMANAGER::Application_IsRunning(XCHAR* applicationname, XDWORD* ID)
* @brief      Application is running
* @ingroup    PLATFORM_LINUX
*
* @param[in]  applicationname : application name
* @param[out] ID : ID of the application in the SO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLINUXPROCESSMANAGER::Application_IsRunning(XCHAR* applicationname, XDWORD* ID)
{
  DIR*            dir;
  struct dirent*  ent;
  char*           endptr;
  char            buf[512];

  if(!(dir = opendir("/proc"))) return -1;

  while((ent = readdir(dir)) != NULL)
    {
      // if endptr is not a null character, the directory is not entirely numeric, so ignore it
      long lpid = strtol(ent->d_name, &endptr, 10);
      if(*endptr != '\0')
        {
          continue;
        }

      // try to open the cmdline file
      snprintf(buf, sizeof(buf), "/proc/%ld/status", lpid);
      FILE* fp = fopen(buf, "r");
      if(fp)
        {
          if(fgets(buf, sizeof(buf), fp) != NULL)
            {
              // check the first token in the file, the program name
              char* first = strtok(buf, " ");

              XPATH nameall;

              nameall = first;
              nameall.SetOnlyNamefile();
              nameall.DeleteCharacter(__C(' ') , XSTRINGCONTEXT_FROM_FIRST);
              nameall.DeleteCharacter(__C('\t'), XSTRINGCONTEXT_FROM_FIRST);
              nameall.DeleteCharacter(__C('\n'), XSTRINGCONTEXT_TO_END);
              nameall.DeleteCharacter(__C('\r'), XSTRINGCONTEXT_TO_END);

              if(!nameall.Compare(applicationname, false))
                {
                  if(ID) (*ID) = (XDWORD)lpid;

                  fclose(fp);
                  closedir(dir);

                  return true;

                }
            }

          fclose(fp);
        }
    }

  closedir(dir);

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XLINUXPROCESSMANAGER::Application_GetRunningList(XVECTOR<XPROCESS*>& applist)
* @brief      Application get running list
* @ingroup    PLATFORM_LINUX
* 
* @param[in]  applist : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XLINUXPROCESSMANAGER::Application_GetRunningList(XVECTOR<XPROCESS*>& applist)
{
  DIR*            dir;
  struct dirent*  ent;
  char*           endptr;
  char            buf[512];

  if(!(dir = opendir("/proc"))) return -1;

  while((ent = readdir(dir)) != NULL)
    {
      // if endptr is not a null character, the directory is not entirely numeric, so ignore it
      long lpid = strtol(ent->d_name, &endptr, 10);
      if(*endptr != '\0')
        {
          continue;
        }

      // try to open the cmdline file
      snprintf(buf, sizeof(buf), "/proc/%ld/status", lpid);
      FILE* fp = fopen(buf, "r");
      if(fp)
        {
          if(fgets(buf, sizeof(buf), fp) != NULL)
            {
              // check the first token in the file, the program name
              char* first = strtok(buf, " ");

              XPATH nameall;
              
              nameall = first;
              nameall.SetOnlyNamefile();
              nameall.DeleteCharacter(__C(' ') , XSTRINGCONTEXT_FROM_FIRST);
              nameall.DeleteCharacter(__C('\t'), XSTRINGCONTEXT_FROM_FIRST);
              nameall.DeleteCharacter(__C('\n'), XSTRINGCONTEXT_TO_END);
              nameall.DeleteCharacter(__C('\r'), XSTRINGCONTEXT_TO_END);

              XPROCESS* xprocess = new XPROCESS();
              if(xprocess)
                {                  
                  xprocess->SetID((XDWORD)lpid); 
                  xprocess->GetPath()->Set(__L(""));
                  xprocess->GetName()->Set(nameall); 
                                
                  applist.Add(xprocess); 
                }                         
            }

          fclose(fp);
        }
    }

  closedir(dir);
  
  return false;
} 


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XLINUXPROCESSMANAGER::Application_Terminate(XDWORD processID, XDWORD exitcode)
* @brief      Application terminate
* @ingroup    PLATFORM_LINUX
* 
* @param[in]  processID : 
* @param[in]  exitcode : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XLINUXPROCESSMANAGER::Application_Terminate(XDWORD processID, XDWORD exitcode)
{
  pid_t pid = (pid_t)processID;

    // Send SIGTERM signal to terminate the process gracefully
  if(kill(pid, SIGTERM) == 0) 
    {
      return true;
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XLINUXPROCESSMANAGER::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    PLATFORM_LINUX
*
* --------------------------------------------------------------------------------------------------------------------*/
void XLINUXPROCESSMANAGER::Clean()
{

}


#pragma endregion

