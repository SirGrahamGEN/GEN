/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XLINUXSystem.cpp
* 
* @class      XLINUXSYSTEM
* @brief      LINUX eXtended Utils System class
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

#include "XLINUXSystem.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <locale.h>
#include <fcntl.h>
#include <utmp.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <termios.h>
#ifdef HW_PC
#include <cpuid.h>
#endif
#include <mntent.h>
#include <sys/reboot.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/sysinfo.h>
#include <sys/wait.h>
#include <sys/utsname.h>
#include <sys/mount.h>
#include <syslog.h>
#include <sys/resource.h>
#include <linux/reboot.h>

#ifndef ANDROID
#include <alsa/asoundlib.h>
#endif

#include "XLINUXFactory.h"

#include "XFactory.h"
#include "XBuffer.h"
#include "XFileTXT.h"
#include "XTrace.h"
#include "XString.h"
#include "XPath.h"
#include "XLanguage_ISO_639_3.h"
#include "XProcessManager.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

char*   whom;	
char	  message[90];
int	    timeout    = 0;	

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS

void    int_handler                     (int code);
void    swap_off                        ();
void    unmount_disks                   ();
void    unmount_disks_ourselves         ();


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLINUXSYSTEM::XLINUXSYSTEM()
* @brief      Constructor of class
* @ingroup    PLATFORM_LINUX
*
* --------------------------------------------------------------------------------------------------------------------*/
XLINUXSYSTEM::XLINUXSYSTEM(): XSYSTEM()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLINUXSYSTEM::~XLINUXSYSTEM()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    PLATFORM_LINUX
*
* --------------------------------------------------------------------------------------------------------------------*/
XLINUXSYSTEM::~XLINUXSYSTEM()
{
   Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSYSTEM_HARDWARETYPE XLINUXSYSTEM::GetTypeHardware(int* revision)
* @brief      Get type hardware
* @ingroup    PLATFORM_LINUX
*
* @param[out]  revision : revision of hardware
*
* @return     XSYSTEM_HARDWARETYPE : hardware type
*
* --------------------------------------------------------------------------------------------------------------------*/
XSYSTEM_HARDWARETYPE XLINUXSYSTEM::GetTypeHardware(int* revision)
{
  #define CPUINFOREVISION __L("Revision")

  if(revision)
    {
      (*revision) = -1;

      XFILETXT* xfileTXT = new XFILETXT();
      if(xfileTXT)
        {
          XPATH xpath;

          xpath = __L("/proc/cpuinfo");

          if(xfileTXT->Open(xpath))
            {
              if(xfileTXT->ReadAllFile())
                {
                  for(int c=0; c<xfileTXT->GetNLines(); c++)
                    {
                      XSTRING* line = xfileTXT->GetLine(c);
                      if(line)
                        {
                          if(line->Find(CPUINFOREVISION, false) != XSTRING_NOTFOUND)
                            {
                              int position = line->Find(__L(":"), false);
                              if(position != XSTRING_NOTFOUND)
                                {
                                  XSTRING number;

                                  number = &line->Get()[position+1];

                                  number.UnFormat(__L(" %04x"), revision);
                                }
                            }
                        }
                    }
                }

              xfileTXT->Close();
            }

          delete xfileTXT;
        }
    }


  #ifdef HW_PC
  return XSYSTEM_HARDWARETYPE_PC;
  #endif

  #ifdef HW_LEX3V700A
  return XSYSTEM_HARDWARETYPE_LEX3V700A;
  #endif

  #ifdef HW_GUMSTIXCONNEX
  return XSYSTEM_HARDWARETYPE_GUMSTIXCONNEX;
  #endif

  #ifdef HW_ARTILA500
  return XSYSTEM_HARDWARETYPE_ARTILA500;
  #endif

  #ifdef HW_RASPBERRYPI
  return XSYSTEM_HARDWARETYPE_RASPBERRYPI;
  #endif

  #ifdef HW_ODROIDC1
  return XSYSTEM_HARDWARETYPE_ODROIDC1;
  #endif

  #ifdef HW_BEAGLEBONE
  return XSYSTEM_HARDWARETYPE_BEAGLEBONE;
  #endif
  
  #ifdef HW_ARM
  return XSYSTEM_HARDWARETYPE_NXP_IMX6;
  #endif

  #ifdef HW_ARM64
  return XSYSTEM_HARDWARETYPE_NXP_IMX8;
  #endif

  return XSYSTEM_HARDWARETYPE_UNKNOWN;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSYSTEM_PLATFORM XLINUXSYSTEM::GetPlatform(XSTRING* namestring)
* @brief      Get platform
* @ingroup    PLATFORM_LINUX
*
* @param[in]  namestring : 
* 
* @return     XSYSTEM_PLATFORM : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XSYSTEM_PLATFORM XLINUXSYSTEM::GetPlatform(XSTRING* namestring)
{
 
  #ifdef HW_PC
  if(namestring)  namestring->Set(__L("Linux"));
  return XSYSTEM_PLATFORM_LINUX;
  #endif

  #ifdef HW_LEX3V700A
  if(namestring)  namestring->Set(__L("Linux"));
  return XSYSTEM_PLATFORM_LINUX;
  #endif

  #ifdef HW_GUMSTIXCONNEX
  if(namestring)  namestring->Set(__L("Linux Embedded"));
  return XSYSTEM_PLATFORM_LINUX_EMBEDDED;
  #endif

  #ifdef HW_ARTILA500
  if(namestring)  namestring->Set(__L("Linux Embedded"));
  return XSYSTEM_PLATFORM_LINUX_EMBEDDED;
  #endif

  #ifdef HW_RASPBERRYPI
  if(namestring)  namestring->Set(__L("Linux Embedded"));
  return XSYSTEM_PLATFORM_LINUX_EMBEDDED;
  #endif

  #ifdef HW_BEAGLEBONE
  if(namestring)  namestring->Set(__L("Linux Embedded"));
  return XSYSTEM_PLATFORM_LINUX_EMBEDDED;
  #endif

  #if defined(HW_ARM) || defined(HW_ARM64)
  if(namestring)  namestring->Set(__L("Linux Embedded"));
  return XSYSTEM_PLATFORM_LINUX_EMBEDDED;  
  #endif

  if(namestring)  namestring->Set(__L("Unknown"));  
  return XSYSTEM_PLATFORM_UNKNOWN;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XLINUXSYSTEM::GetOperativeSystemID(XSTRING& ID)
* @brief      Get operative system ID
* @ingroup    PLATFORM_LINUX
*
* @param[in]  ID : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XLINUXSYSTEM::GetOperativeSystemID(XSTRING& ID)
{
  ID.Empty();

  struct utsname details;
    
  int ret = uname(&details);    
  if(ret != 0) return false;

  ID += details.sysname;      ID += __L(" ");
  // ID += details.nodename;     ID += __L(" ");
  ID += details.release;      ID += __L(" ");
  ID += details.version;      ID += __L(" ");
  ID += details.machine;      ID += __L(" ");
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XLINUXSYSTEM::GetLanguageSO()
* @brief      Get language SO
* @ingroup    PLATFORM_LINUX
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XLINUXSYSTEM::GetLanguageSO()
{
  XLANGUAGE_ISO_639_3 ISO639;
  XSTRING             languageenglish;

  languageenglish.Set(setlocale(LC_MESSAGES, ""));

  int undercodeindex = languageenglish.Find(__L("_"), false);
  if(undercodeindex == XSTRING_NOTFOUND) return XLANGUAGE_ISO_639_3_CODE_INVALID;

  int todelete = languageenglish.GetSize();
  todelete -= undercodeindex;

  languageenglish.DeleteCharacters(undercodeindex, todelete);

  XDWORD code = ISO639.Code_GetByCodeAlpha2(languageenglish.Get());
  if(code != XLANGUAGE_ISO_639_3_CODE_INVALID) return code;

  return ISO639.Code_GetByCodeAlpha3(languageenglish.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* XLINUXSYSTEM::GetBIOSSerialNumber()
* @brief      Get BIOS serial number
* @ingroup    PLATFORM_LINUX
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* XLINUXSYSTEM::GetBIOSSerialNumber()
{
  return &BIOSserialnumber;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* XLINUXSYSTEM::GetCPUSerialNumber()
* @brief      Get CPU serial number
* @ingroup    PLATFORM_LINUX
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* XLINUXSYSTEM::GetCPUSerialNumber()
{
  #ifdef HW_PC
  unsigned int level = 1;
  unsigned eax = 3 /* processor serial number */, ebx = 0, ecx = 0, edx = 0;

  __get_cpuid(level, &eax, &ebx, &ecx, &edx);

  XDWORD first = eax;
  XDWORD last  = edx;

  CPUserialnumber.Format(__L("%08X%08X"), last, first);
  #endif

  return &CPUserialnumber;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         float XLINUXSYSTEM::GetCPUTemperature()
* @brief      Get CPU temperature
* @ingroup    PLATFORM_LINUX
* 
* @return     float : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
float XLINUXSYSTEM::GetCPUTemperature()
{
  return 0.0f;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXSYSTEM::GetMemoryInfo(XDWORD& total,XDWORD& free)
* @brief      Get memory info
* @ingroup    PLATFORM_LINUX
*
* @param[out] total : total memory
* @param[out] free : free memory
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLINUXSYSTEM::GetMemoryInfo(XDWORD& total,XDWORD& free)
{
  struct sysinfo meminfo;

  if(sysinfo(&meminfo) == -1) return false;

  long long totalvirtualmem = meminfo.totalram;
  //Add other values in next statement to avoid int overflow on right hand side...
  //totalvirtualmem += meminfo.totalswap;
  totalvirtualmem *= meminfo.mem_unit;

  long long virtualmemused = meminfo.totalram - meminfo.freeram;
  //Add other values in next statement to avoid int overflow on right hand side...
  //virtualmemused += meminfo.totalswap - meminfo.freeswap;
  virtualmemused *= meminfo.mem_unit;

  total = (XDWORD)(totalvirtualmem                     / 1024);
  free  = (XDWORD)((totalvirtualmem - virtualmemused)  / 1024);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XLINUXSYSTEM::FreeCacheMemory()
* @brief      Free cache memory
* @ingroup    PLATFORM_LINUX
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XLINUXSYSTEM::FreeCacheMemory()
{
  return GEN_XPROCESSMANAGER.MakeSystemCommand(__L("sync && sysctl -w vm.drop_caches=3 > /dev/null"));  
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XLINUXSYSTEM::GetCPUUsageTotal()
* @brief      Get CPU usage total
* @ingroup    PLATFORM_LINUX
*
* @return     int : 
*
* --------------------------------------------------------------------------------------------------------------------*/
int XLINUXSYSTEM::GetCPUUsageTotal()
{
  if(xmutexcheckCPUusage)
    {
      xmutexcheckCPUusage->Lock();
    }

  static unsigned int lasttotaluser, lasttotaluserlow, lasttotalsys, lasttotalidle;
  float               percent;
  int                 intpercent;     
  FILE*               file;
  unsigned long long  totaluser, totaluserlow, totalsys, totalidle, total;
     
  file = fopen("/proc/stat", "r");
  fscanf(file, "cpu %llu %llu %llu %llu", &totaluser, &totaluserlow, &totalsys, &totalidle);
  fclose(file);
     
  if(totaluser < lasttotaluser || totaluserlow < lasttotaluserlow || totalsys < lasttotalsys || totalidle < lasttotalidle)
    {
      // Overflow detection. Just skip this value.
      percent = -1.0;
    }
   else
    {
      total    = (totaluser - lasttotaluser) + (totaluserlow - lasttotaluserlow) + (totalsys - lasttotalsys);
      percent  = total * 100;
      total   += (totalidle - lasttotalidle);
      percent /= total;
    }
     
  lasttotaluser    = totaluser;
  lasttotaluserlow = totaluserlow;
  lasttotalsys     = totalsys;
  lasttotalidle    = totalidle;
     
  intpercent = percent;

  if(xmutexcheckCPUusage)
    {
      xmutexcheckCPUusage->UnLock();
    }
    		
  return intpercent;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XLINUXSYSTEM::GetCPUUsageForProcessName(XCHAR* processname)
* @brief      Get CPU usage for process name
* @ingroup    PLATFORM_LINUX
*
* @param[in]  processname : 
*
* @return     int : 
*
* --------------------------------------------------------------------------------------------------------------------*/
int XLINUXSYSTEM::GetCPUUsageForProcessName(XCHAR* processname)
{  
  XSTRING command;
  XSTRING result;
  XBUFFER charcmd;
  
  command.Format(__L("ps -C %s -o %%cpu"), processname);

  command.ConvertToASCII(charcmd);  

  // Open a pipe to the command
  FILE* pipe = popen((char*)charcmd.Get(), "r");
  if(!pipe) 
    {
       return 0; // Error
    }
   
  char buffer[128];    
  while(!feof(pipe)) 
    {
      if(fgets(buffer, 128, pipe) != NULL)
        {
          result += buffer;
        }
    }
  
  pclose(pipe);

  // Extract the CPU usage percentage from the result
  double cpupercentage = 0.0f;
  result.UnFormat(__L("%%CPU\n %lf\n"), &cpupercentage);

  return static_cast<int>(cpupercentage);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XLINUXSYSTEM::GetCPUUsageForProcessID(XDWORD processID)
* @brief      Get CPU usage for process ID
* @ingroup    PLATFORM_LINUX
*
* @param[in]  processID : 
*
* @return     int : 
*
* --------------------------------------------------------------------------------------------------------------------*/
int XLINUXSYSTEM::GetCPUUsageForProcessID(XDWORD processID)
{
  XSTRING command;
  XSTRING result;
  XBUFFER charcmd;
  
  command.Format(__L("ps -C -p %d -o %%cpu"), processID);

  command.ConvertToASCII(charcmd);  

  // Open a pipe to the command
  FILE* pipe = popen((char*)charcmd.Get(), "r");
  if(!pipe) 
    {
       return 0; // Error
    }
   
  char buffer[128];    
  while(!feof(pipe)) 
    {
      if(fgets(buffer, 128, pipe) != NULL)
        {
          result += buffer;
        }
    }
  
  pclose(pipe);

  // Extract the CPU usage percentage from the result
  double cpupercentage = 0.0f;
  result.UnFormat(__L("%%CPU\n %lf\n"), &cpupercentage);

  return static_cast<int>(cpupercentage);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XCHAR* XLINUXSYSTEM::GetEnviromentVariable(XCHAR* name)
* @brief      Get enviroment variable
* @ingroup    PLATFORM_LINUX
* 
* @param[in]  name : 
* 
* @return     XCHAR* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR* XLINUXSYSTEM::GetEnviromentVariable(XCHAR* name)
{
  XSTRING        _variablename = name;
  static XSTRING result;

  XBUFFER charstr;
  
  _variablename.ConvertToASCII(charstr); 
  result = getenv(charstr.GetPtrChar());
  
  return result.Get();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XLINUXSYSTEM::SetEnviromentVariable(XCHAR* name, XCHAR* value)
* @brief      Set enviroment variable
* @ingroup    PLATFORM_LINUX
* 
* @param[in]  name : 
* @param[in]  value : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XLINUXSYSTEM::SetEnviromentVariable(XCHAR* name, XCHAR* value)
{
  XSTRING _name;
  XSTRING _value;

  _name   = name;
  _value  = value;

  XBUFFER charstr1;  
  XBUFFER charstr2;
  
  _name.ConvertToASCII(charstr1);  
  _value.ConvertToASCII(charstr2);

  int status = setenv(charstr1.GetPtrChar(), charstr2.GetPtrChar(), 1);
  
  return status?false:true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXSYSTEM::DelEnviromentVariable(XCHAR* name)
* @brief      Del enviroment variable
* @ingroup    PLATFORM_LINUX
*
* @param[in]  name :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLINUXSYSTEM::DelEnviromentVariable(XCHAR* name)
{
  XSTRING _name;

  _name = name;

  XBUFFER charstr;
  
  _name.ConvertToASCII(charstr);

  int status = unsetenv(charstr.GetPtrChar());
  
  return status?false:true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXSYSTEM::ShutDown(XSYSTEM_CHANGESTATUSTYPE type)
* @brief      Shut down
* @ingroup    PLATFORM_LINUX
*
* @param[in]  type : type of shutdown of SO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLINUXSYSTEM::ShutDown(XSYSTEM_CHANGESTATUSTYPE type)
{
  int	    opt_reboot = 0;
  int     fd;

  switch(type)
    {
      case XSYSTEM_CHANGESTATUSTYPE_REBOOT          : opt_reboot = 1;   break;     
      case XSYSTEM_CHANGESTATUSTYPE_POWEROFF        : opt_reboot = 0;   break;
                                        default     : break;
    }

  setpriority(PRIO_PROCESS, 0, PRIO_MIN);
	                                                    
  whom = getlogin();

  setpriority(PRIO_PROCESS, 0, PRIO_MIN);
	signal(SIGINT,  int_handler);
	signal(SIGHUP,  int_handler);
	signal(SIGQUIT, int_handler);
	signal(SIGTERM, int_handler);

	chdir("/");

	signal(SIGPIPE, SIG_IGN);	
	signal(SIGINT,  SIG_IGN);   // now there's no turning back... 

	kill(1, SIGTSTP);	          // tell init not to spawn more getty's 
		
	sync();

	signal(SIGTERM, SIG_IGN);

	if(fork() > 0) sleep(1000); // the parent will die soon... 

	setpgrp();		              // so the shell wont kill us in the fall 
	
  kill(-1, SIGTERM);          // a gentle kill of all other processes except init 
	sleep(2);
	
	kill(-1, SIGKILL);          // now use brute force... 

	acct(NULL);	                // turn off accounting 

	sync();
	sleep(2);

	swap_off();	                // remove swap files and partitions using swapoff 

	unmount_disks();	          // unmount disks... 

	sync();
	sleep(1);

  if(opt_reboot) 
    {
		  reboot(LINUX_REBOOT_CMD_RESTART);
	  } 
   else 
    {
		  reboot(LINUX_REBOOT_CMD_POWER_OFF);
    }		  

  exit(0); // to quiet gcc 

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XLINUXSYSTEM::Sound_GetLevel()
* @brief      Sound get level
* @ingroup    PLATFORM_LINUX
*
* @return     int : 
*
* --------------------------------------------------------------------------------------------------------------------*/
int XLINUXSYSTEM::Sound_GetLevel()
{
  long _level = 0;

  bool status =  Sound_SetLevel(true, &_level);
  if(!status) return 0;

  return (int)_level;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXSYSTEM::Sound_SetLevel(int level)
* @brief      Sound set level
* @ingroup    PLATFORM_LINUX
*
* @param[in]  level : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLINUXSYSTEM::Sound_SetLevel(int level)
{
  long _level = (long)level;

  return Sound_SetLevel(false, &_level);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXSYSTEM::Sound_SetMutex(bool on)
* @brief      Sound set mutex
* @ingroup    PLATFORM_LINUX
*
* @param[in]  on : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLINUXSYSTEM::Sound_SetMutex(bool on)
{
  static long old_level = Sound_GetLevel();

  if(on)
    {
      old_level = Sound_GetLevel();
      Sound_SetLevel(0);      
    }
   else
    {
      Sound_SetLevel(old_level);
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XLINUXSYSTEM::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    PLATFORM_LINUX
*
* --------------------------------------------------------------------------------------------------------------------*/
void XLINUXSYSTEM::Clean()
{

}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void int_handler()
* @brief      nt_handler
* @ingroup    PLATFORM_LINUX
*
* ---------------------------------------------------------------------------------------------------------------------*/
void int_handler(int code)
{
	unlink(_PATH_NOLOGIN);
	signal(SIGINT, SIG_DFL);

	exit(1);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void swap_off()
* @brief      wap_off
* @ingroup    PLATFORM_LINUX
*
* ---------------------------------------------------------------------------------------------------------------------*/
void swap_off()
{
	/// swapoff esp. swap FILES so the underlying partition can be
	//  unmounted. It you don't have swapoff(1) or use mount to
	//  add swapspace, this may not be necessary, but I guess it
	//  won't hurt 

	int   pid;
	int   result;
	int   status;

	sync();

	if((pid = fork()) < 0) 
    {
		  // Cannot fork for swapoff. Shrug!
		  return;
	  }

	if(!pid) 
    {
		  execl("/sbin/swapoff" , SWAPOFF_ARGS, NULL);
		  execl("/etc/swapoff"  , SWAPOFF_ARGS, NULL);
		  execl("/bin/swapoff"  , SWAPOFF_ARGS, NULL);

		  execlp("swapoff"      , SWAPOFF_ARGS, NULL);

		  // Cannot exec swapoff, hoping umount will do the trick.
		  exit(0);
	  }

	while((result = wait(&status)) != -1 && result != pid);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void unmount_disks()
* @brief      nmount_disks
* @ingroup    PLATFORM_LINUX
*
* ---------------------------------------------------------------------------------------------------------------------*/
void unmount_disks()
{
	// better to use umount directly because it may be smarter than us 

	int   pid;
	int   result;
	int   status;

	sync();

	if((pid = fork()) < 0) 
    {
		  // Cannot fork for umount, trying manually.
		  unmount_disks_ourselves();
		  return;
	  }

	if(!pid) 
    {
		  execl(_PATH_UMOUNT, UMOUNT_ARGS, NULL);

  		// Cannot exec %s, trying umount. _PATH_UMOUNT

  		execlp("umount", UMOUNT_ARGS, NULL);

	  	// Cannot exec umount, giving up on umount.
		  exit(0);
	  }

	while ((result = wait(&status)) != -1 && result != pid);

	// Unmounting any remaining filesystems...

	unmount_disks_ourselves();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void unmount_disks_ourselves()
* @brief      nmount_disks_ourselves
* @ingroup    PLATFORM_LINUX
*
* ---------------------------------------------------------------------------------------------------------------------*/
void unmount_disks_ourselves()
{
	// unmount all disks 

	FILE*           mtab;
	struct mntent*  mnt;
	char*           mntlist[128];
	int             i;
	int             n;
	char*           filesys;
	
	sync();

	if(!(mtab = setmntent(_PATH_MTAB, "r"))) 
    {
		  // shutdown: Cannot open %s _PATH_MTAB;
		  return;
	  }

	n = 0;
	while (n < 100 && (mnt = getmntent(mtab))) 
    {
		  mntlist[n++] = strdup(mnt->mnt_fsname[0] == '/' ?
			mnt->mnt_fsname : mnt->mnt_dir);
	  }

	endmntent(mtab);

	// we are careful to do this in reverse order of the mtab file 

	for(i = n - 1; i >= 0; i--) 
    {
		  filesys = mntlist[i];

		  if(umount(mntlist[i]) < 0)
        {
			    // shutdown: Couldn't umount %s filesys
        }
	  }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XLINUXSYSTEM::Sound_SetLevel(bool read, long* level)
* @brief      Sound set level
* @ingroup    PLATFORM_LINUX
* 
* @param[in]  read : 
* @param[in]  level : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XLINUXSYSTEM::Sound_SetLevel(bool read, long* level)
{
  #ifndef ANDROID

  #ifdef SND_ACTIVE    

  snd_mixer_t*          handle;
  snd_mixer_elem_t*     elem;
  snd_mixer_selem_id_t* sid;

  static int            mix_index = 0;
  static const char*    mix_name1 = "PCM";       
  static const char*    mix_name2 = "Master";    // first "PCM" if error after "Master"
  static const char*    card      = "default";  
  long                  pmin, pmax;
  long                  get_vol, set_vol;
  float                 f_multi;

  if((snd_mixer_open(&handle, 0)) < 0) 
    {
      XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Alsa volume] snd_mixer_open: error"));
      return false;        
    }

  if((snd_mixer_attach(handle, card)) < 0) 
    {
      XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Alsa volume] snd_mixer_attach: error"));
      snd_mixer_close(handle);
      return false;
    }

  if((snd_mixer_selem_register(handle, NULL, NULL)) < 0) 
    {
      XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Alsa volume] snd_mixer_selem_register: error"));
      snd_mixer_close(handle);
      return false;
    }

  int ret = snd_mixer_load(handle);
  if(ret < 0) 
    {
      XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Alsa volume] snd_mixer_load: error"));
      snd_mixer_close(handle);
      return false;
    }

  snd_mixer_selem_id_alloca(&sid);

  //sets simple-mixer index and name
  snd_mixer_selem_id_set_index(sid  , mix_index);
  snd_mixer_selem_id_set_name(sid   , mix_name1);

  elem = snd_mixer_find_selem(handle, sid);
  if(!elem) 
    {
      snd_mixer_selem_id_set_index(sid  , mix_index);
      snd_mixer_selem_id_set_name(sid   , mix_name2);
      
      elem = snd_mixer_find_selem(handle, sid);
      if(!elem) 
        {
          XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Alsa volume] snd_mixer_find_selem: error"));

          snd_mixer_close(handle);
          return false;   
        }
    }

  long minv, maxv;

  snd_mixer_selem_get_playback_volume_range(elem, &minv, &maxv);
  
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Alsa volume] Volume range <%i,%i>"), minv, maxv);

  if(read) 
    {
      if(snd_mixer_selem_get_playback_volume(elem, (snd_mixer_selem_channel_id_t)0, level) < 0) 
        {
          XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Alsa volume] snd_mixer_selem_get_playback_volume: error"));  
          snd_mixer_close(handle);
          return false;
        }

      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Alsa volume] Get volume %i with status %i"), *level, ret);

      // make the value bound to 100 
      *level  -= minv;
      maxv    -= minv;
      minv     = 0;
     
      *level = 100 * (*level) / maxv; // make the value bound from 0 to 100
    }    
   else   
    {
      if(*level < 0 || *level > 100) // out of bounds
        {
          XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Alsa volume] out of bounds: error"));
          return false;
        }

      //minv = 0;
      //maxv = 100;

     
      *level = (*level * (maxv - minv) / (100-1)) + minv;
      
      if(snd_mixer_selem_set_playback_volume_range(elem, minv, maxv) < 0)
        {
          XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Alsa volume] snd_mixer_selem_set_playback_volume_range: error"));

          snd_mixer_close(handle);
          return false;
        }
         
      if(snd_mixer_selem_set_playback_volume_all(elem, *level) < 0) 
        {
          XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Alsa volume] snd_mixer_selem_set_playback_volume_all: error"));

          snd_mixer_close(handle);
          return false;
        }
   
      /*
      if(snd_mixer_selem_set_playback_volume(elem, (snd_mixer_selem_channel_id_t)0, *level) < 0) 
        {
          XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Alsa volume] snd_mixer_selem_set_playback_volume: error"));

          snd_mixer_close(handle);
          return false;
        }

      if(snd_mixer_selem_set_playback_volume(elem, (snd_mixer_selem_channel_id_t)1, *level) < 0) 
        {
          XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Alsa volume] snd_mixer_selem_set_playback_volume: error"));

          snd_mixer_close(handle);
          return false;
        }
       */

      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Alsa volume] Set volume %i with status %i"), *level, ret);        
    }

  snd_mixer_close(handle);

  return true;

  #else

  return false;

  #endif   

  #endif 
}


#pragma endregion

