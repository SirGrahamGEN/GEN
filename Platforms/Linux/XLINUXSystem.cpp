/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XLINUXSystem.cpp
*
* @class      XLINUXSYSTEM
* @brief      eXtended LINUX System class
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

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

#include "XBuffer.h"
#include "XFileTXT.h"
#include "XTrace.h"
#include "XString.h"
#include "XPath.h"
#include "XLanguage_ISO_639_3.h"
#include "XProcessManager.h"

#include "XLINUXSystem.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

char*   whom;	
char	  message[90];
int	    timeout    = 0;	

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


void    int_handler                     (int code);
void    swap_off                        ();
void    unmount_disks                   ();
void    unmount_disks_ourselves         ();


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLINUXSYSTEM::XLINUXSYSTEM()
* @brief      Constructor
* @ingroup    PLATFORM_LINUX
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XLINUXSYSTEM::XLINUXSYSTEM(): XSYSTEM()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLINUXSYSTEM::~XLINUXSYSTEM()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_LINUX
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XLINUXSYSTEM::~XLINUXSYSTEM()
{
   Clean();
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSYSTEM_HARDWARETYPE XLINUXSYSTEM::GetTypeHardware(int* revision)
* @brief      Get Type Hardware
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
* @brief      GetPlatform
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
* @brief      GetOperativeSystemID
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
* @brief      GetLanguageSO
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
* @fn         bool XLINUXSYSTEM::GetMemoryInfo(XDWORD& total,XDWORD& free)
* @brief      Get Memory Info
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
* @fn         bool XLINUXSYSTEM::FreeCacheMemory();
* @brief      FreeCacheMemory
* @ingroup    PLATFORM_LINUX
*
* @param[in]  ) : 
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
* @brief      GetCPUUsageTotal
* @ingroup    PLATFORM_LINUX
*
* @return     int : 
*
* --------------------------------------------------------------------------------------------------------------------*/
int XLINUXSYSTEM::GetCPUUsageTotal()
{
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
      //Overflow detection. Just skip this value.
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
    		
  return intpercent;

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XLINUXSYSTEM::GetCPUUsageForProcessName(XCHAR* processname)
* @brief      GetCPUUsageForProcessName
* @ingroup    PLATFORM_LINUX
*
* @param[in]  processname : 
*
* @return     int : 
*
* --------------------------------------------------------------------------------------------------------------------*/
int XLINUXSYSTEM::GetCPUUsageForProcessName(XCHAR* processname)
{  
  XSTRING   params;
  XSTRING   in;  
  XSTRING   out;
  int       returncode;
  double    cpuusagef = 0.0f;
  int       cpuusage  = 0;
  bool      status;

  params.Format(__L("-C %s -o %%cpu"), processname);  
  in.Format(__L("| tail -n 1"));
  
  status = GEN_XPROCESSMANAGER.ExecuteApplication(__L("/usr/bin/ps"), params.Get(), &in, &out, &returncode);
  if(!status) status = GEN_XPROCESSMANAGER.ExecuteApplication(__L("/bin/ps"), params.Get(), &in, &out, &returncode); 

  if(!status) return -1;

  out.DeleteCharacter(__C('\n'));
  out.DeleteCharacter(__C('\r'));
  out.DeleteCharacter(__C(' '));

  //XTRACE_PRINTCOLOR(XTRACE_COLOR_PURPLE, __L("[CPU usage] read 1 : [%s]"), out.Get());  

  int index = out.Find(__L("CPU"), true);
  if(index != XSTRING_NOTFOUND) 
    { 
      out.DeleteCharacters(index, 3);
      out.DeleteCharacters(0, 1);
    }

  //XTRACE_PRINTCOLOR(XTRACE_COLOR_PURPLE, __L("[CPU usage] app read 2 : [%s]"), out.Get());  
     
  cpuusagef = out.ConvertToFloat();
  cpuusage  = (int)cpuusagef;     
    
  return cpuusage;  
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XLINUXSYSTEM::GetCPUUsageForProcessID(XDWORD processID)
* @brief      GetCPUUsageForProcessID
* @ingroup    PLATFORM_LINUX
*
* @param[in]  processID : 
*
* @return     int : 
*
* --------------------------------------------------------------------------------------------------------------------*/
int XLINUXSYSTEM::GetCPUUsageForProcessID(XDWORD processID)
{
  XSTRING   params;
  XSTRING   in;  
  XSTRING   out;
  int       returncode;
  double    cpuusagef = 0.0f;
  int       cpuusage  = 0;
  bool      status;

  params.Format(__L("-C -p %d -o %%cpu"), processID);  
  in.Format(__L("| tail -n 1"));
  
  status = GEN_XPROCESSMANAGER.ExecuteApplication(__L("/usr/bin/ps"), params.Get(), &in, &out, &returncode);
  if(!status) status = GEN_XPROCESSMANAGER.ExecuteApplication(__L("/bin/ps"), params.Get(), &in, &out, &returncode); 

  if(!status) return -1;

  out.DeleteCharacter(__C('\n'));
  out.DeleteCharacter(__C('\r'));
  out.DeleteCharacter(__C(' '));

  //XTRACE_PRINTCOLOR(XTRACE_COLOR_PURPLE, __L("[CPU usage] read 1 : [%s]"), out.Get());  

  int index = out.Find(__L("CPU"), true);
  if(index != XSTRING_NOTFOUND) 
    { 
      out.DeleteCharacters(index, 3);
      out.DeleteCharacters(0, 1);
    }

  //XTRACE_PRINTCOLOR(XTRACE_COLOR_PURPLE, __L("[CPU usage] app read 2 : [%s]"), out.Get());  
     
  cpuusagef = out.ConvertToFloat();
  cpuusage  = (int)cpuusagef;     
    
  return cpuusage;  
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XCHAR* XLINUXSYSTEM::GetEnviromentVariable(XCHAR* variablename)
* @brief      GetEnviromentVariable
* @ingroup    PLATFORM_LINUX
*
* @param[in]  variablename :
*
* @return     XCHAR* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR* XLINUXSYSTEM::GetEnviromentVariable(XCHAR* variablename)
{
  XSTRING        _variablename = variablename;
  static XSTRING result;

  XSTRING_CREATEOEM(_variablename, varchar);
  result = getenv(varchar);
  XSTRING_DELETEOEM(_variablename, varchar);

  return result.Get();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXSYSTEM::SetEnviromentVariable(XCHAR* variablename, XCHAR* value)
* @brief      SetEnviromentVariable
* @ingroup    PLATFORM_LINUX
*
* @param[in]  variablename :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLINUXSYSTEM::SetEnviromentVariable(XCHAR* variablename, XCHAR* value)
{
  XSTRING _variablename;
  XSTRING _value;

  _variablename = variablename;
  _value        = value;

  XSTRING_CREATEOEM(_variablename, varchar1);
  XSTRING_CREATEOEM(_value, valchar2);
  int status = setenv(varchar1, valchar2, 1);
  XSTRING_DELETEOEM(_variablename, varchar1);
  XSTRING_DELETEOEM(_value, valchar2);

  return status?false:true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXSYSTEM::DelEnviromentVariable(XCHAR* variablename)
* @brief      DelEnviromentVariable
* @ingroup    PLATFORM_LINUX
*
* @param[in]  variablename :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLINUXSYSTEM::DelEnviromentVariable(XCHAR* variablename)
{
  XSTRING _variablename;

  _variablename = variablename;

  XSTRING_CREATEOEM(_variablename, varchar);
  int status = unsetenv(varchar);
  XSTRING_DELETEOEM(_variablename, varchar);

  return status?false:true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXSYSTEM::ShutDown(XSYSTEM_CHANGESTATUSTYPE type)
* @brief      ShutDown of SO
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
* @brief      Sound_GetLevel
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
* @brief      Sound_SetLevel
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
* @brief      Sound_SetMutex
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
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_LINUX
*
* @return     void : does not return anything.
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
* @return     void : does not return anything. 
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
* @return     void : does not return anything. 
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
* @return     void : does not return anything. 
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
* @return     void : does not return anything. 
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
* @fn         bool XLINUXSYSTEM::Sound_SetLevel(bool read, int level)
* @brief      Sound_SetLevel
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
