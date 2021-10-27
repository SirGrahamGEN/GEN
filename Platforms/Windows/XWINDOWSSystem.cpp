/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XWINDOWSSystem.cpp
*
* @class      XWINDOWSSYSTEM
* @brief      eXtended WINDOWS System class
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

#define SECURITY_WIN32


#include <cstdio>
#include <windows.h>
#include <process.h>
#include <tlhelp32.h>
#include <Commctrl.h>
#include <Security.h>
#include <powrprof.h>

#ifndef BUILDER
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#endif


#ifndef BUILDER
#if(_MSC_PLATFORM_TOOLSET == 'v140')
#include <versionhelpers.h>
#endif
#endif

#ifndef BUILDER
#include "XWINDOWSWMIInterface.h"
#endif

#include "XWINDOWSRegistryManager.h"

#include "XFactory.h"
#include "XSleep.h"
#include "XFile.h"
#include "XFileTXT.h"
#include "XTrace.h"
#include "XLanguage_ISO_639_3.h"

#include "XWINDOWSSystem.h"

#include "XMemory_Control.h"



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/




/*--------------------------------------------------------------------------------------------------------------------*/
/*  XWINDOWSSYSTEM_CPUUSAGESTATUS                                                                                     */
/*--------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWINDOWSSYSTEM_CPUUSAGESTATUS::XWINDOWSSYSTEM_CPUUSAGESTATUS()
* @brief      Constructor
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     Does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
XWINDOWSSYSTEM_CPUUSAGESTATUS::XWINDOWSSYSTEM_CPUUSAGESTATUS()

{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWINDOWSSYSTEM_CPUUSAGESTATUS::~XWINDOWSSYSTEM_CPUUSAGESTATUS()
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
XWINDOWSSYSTEM_CPUUSAGESTATUS::~XWINDOWSSYSTEM_CPUUSAGESTATUS()
{
  Clean();
}


	
/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XWINDOWSSYSTEM_CPUUSAGESTATUS::Clean()
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
void XWINDOWSSYSTEM_CPUUSAGESTATUS::Clean()
{
  processname.Empty();		
	processID                  = 0xFFFFFFFF;
  firsttime                   = true;
	oldvalue                    = 0;
  oldperftime100nsec.QuadPart = 0;
}




/*--------------------------------------------------------------------------------------------------------------------*/
/*  XWINDOWSSYSTEM                                                                                                    */
/*--------------------------------------------------------------------------------------------------------------------*/




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWINDOWSSYSTEM::XWINDOWSSYSTEM() : XSYSTEM()
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
XWINDOWSSYSTEM::XWINDOWSSYSTEM() : XSYSTEM()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWINDOWSSYSTEM::~XWINDOWSSYSTEM()
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
XWINDOWSSYSTEM::~XWINDOWSSYSTEM()
{
  DeleteAllCPUUsageStatus();

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSYSTEM_HARDWARETYPE XWINDOWSSYSTEM::GetTypeHardware(int* revision)
* @brief      Get Type Hardware
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  revision : Type hardware
*
* @return     XSYSTEM_HARDWARETYPE :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSYSTEM_HARDWARETYPE XWINDOWSSYSTEM::GetTypeHardware(int* revision)
{
  if(revision) (*revision) = -1;

  return XSYSTEM_HARDWARETYPE_PC;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSYSTEM_SO XWINDOWSSYSTEM::GetTypeSO()
* @brief      Get Type SO
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XSYSTEM_SO : type of SO (enum XSYSTEM_SO)
*
*---------------------------------------------------------------------------------------------------------------------*/
XSYSTEM_SO XWINDOWSSYSTEM::GetTypeSO()
{
  #ifdef BUILDER

  OSVERSIONINFO osvi;

  osvi.dwOSVersionInfoSize =sizeof(OSVERSIONINFO);

  GetVersionEx(&osvi);

  switch(osvi.dwPlatformId)
    {
      case VER_PLATFORM_WIN32s        : return XSYSTEM_SO_WINDOWS;
      case VER_PLATFORM_WIN32_WINDOWS : return XSYSTEM_SO_WINDOWS98;
      case VER_PLATFORM_WIN32_NT      : return XSYSTEM_SO_WINDOWSNT4;
    }

  #else

  OSVERSIONINFOEXW osvi;
  DWORDLONG        const dwlConditionMask = VerSetConditionMask(0, VER_PLATFORMID, VER_GREATER_EQUAL);

  osvi.dwOSVersionInfoSize = sizeof(osvi);
  #if(_MSC_PLATFORM_TOOLSET == 'v140')
  osvi.dwPlatformId        = _WIN32_WINNT_WIN10;
  #endif

  VerifyVersionInfoW(&osvi, VER_PRODUCT_TYPE, dwlConditionMask);


  switch(osvi.dwPlatformId)
    {
      case _WIN32_WINNT_NT4           : return XSYSTEM_SO_WINDOWSNT4;
      case _WIN32_WINNT_WIN2K         : return XSYSTEM_SO_WINDOWS2000;
      case _WIN32_WINNT_WINXP         : return XSYSTEM_SO_WINDOWSXP;
      case _WIN32_WINNT_WS03          : return XSYSTEM_SO_WINDOWSSERVER2003;
      case _WIN32_WINNT_VISTA         : return XSYSTEM_SO_WINDOWSVISTA;
      case _WIN32_WINNT_WIN7          : return XSYSTEM_SO_WINDOWS7;
      #if(_MSC_PLATFORM_TOOLSET == 'v140')
      case _WIN32_WINNT_WIN8          : return XSYSTEM_SO_WINDOWS8;
      case _WIN32_WINNT_WINBLUE       : return XSYSTEM_SO_WINDOWS81;
      case _WIN32_WINNT_WIN10         : return XSYSTEM_SO_WINDOWS10;
      #endif
    }

  #endif

  return XSYSTEM_SO_WINDOWS;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLANGUAGE_CODE XWINDOWSSYSTEM::GetLanguageSO()
* @brief      GetLanguageSO
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XLANGUAGE_CODE :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD XWINDOWSSYSTEM::GetLanguageSO()
{
  XLANGUAGE_ISO_639_3 ISO639;
  XSTRING             languageenglish;

  languageenglish.AdjustSize(_MAXSTR);

  LCID lcID = GetUserDefaultLCID();
  GetLocaleInfo( lcID, LOCALE_SENGLANGUAGE, languageenglish.Get(), _MAXSTR);

  languageenglish.AdjustSize();

  return ISO639.Code_GetByEnglishName(languageenglish.Get());
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* XWINDOWSSYSTEM::GetSerialNumber()
* @brief      GetSerialNumber
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* XWINDOWSSYSTEM::GetSerialNumber()
{
  #ifndef BUILDER
  XWINDOWSWMIINTERFACE wmiinterface;

  wmiinterface.DoQuery(__L("Win32_BaseBoard"), __L("SerialNumber"), serialnumber);
  #endif

  return &serialnumber;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSSYSTEM::GetMemoryInfo(XDWORD& total,XDWORD& free)
* @brief      Get Memory Info
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[out]  total : total memory in bytes.
* @param[out]  free : free memory in bytes.
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSSYSTEM::GetMemoryInfo(XDWORD& total,XDWORD& free)
{
  MEMORYSTATUS mem;

  GlobalMemoryStatus(&mem);

  total = (XDWORD)(mem.dwTotalPhys/1024);
  free  = (XDWORD)(mem.dwAvailPhys/1024);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XWINDOWSSYSTEM::GetCPUUsageTotal()
* @brief      GetCPUUsageTotal
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     int : 
*
*---------------------------------------------------------------------------------------------------------------------*/
int XWINDOWSSYSTEM::GetCPUUsageTotal()
{
  int				                              cpuusage            = 0;
  
  #ifndef BUILDER
  XWINDOWSSYSTEM_PERFCOUNTERS<LONGLONG>   perfcounters;
	DWORD                                   objectindex;
	DWORD                                   cpuusageindex;	
	LONGLONG		                            newvalue            = 0;
	PPERF_DATA_BLOCK                        perfdata            = NULL;
	LARGE_INTEGER	                          newperftime100nsec  = { 0 };
  XSTRING                                 processstr;
  XWINDOWSSYSTEM_CPUUSAGESTATUS*          cus                 = NULL;

  objectindex     = XWINDOWSSYSTEM_PROCESSOR_OBJECT_INDEX;
  cpuusageindex   = XWINDOWSSYSTEM_PROCESSOR_TIME_COUNTER_INDEX;

  processstr     = __L("_Total");

  cus = AddCPUUsageStatus(processstr.Get());
  if(!cus) return 0;

  newvalue = perfcounters.GetCounterValue(&perfdata, objectindex, cpuusageindex, (LPCTSTR)processstr.Get());

	newperftime100nsec = perfdata->PerfTime100nSec;

	if(cus->firsttime)
	  {
		  cus->firsttime           = false;
		  cus->oldvalue            = newvalue;
		  cus->oldperftime100nsec  = newperftime100nsec;

		  return 0;
	  }

	LONGLONG  lnValueDelta         = newvalue - cus->oldvalue;
	double    DeltaPerfTime100nSec = (double)newperftime100nsec.QuadPart - (double)cus->oldperftime100nsec.QuadPart;

	cus->oldvalue            = newvalue;
	cus->oldperftime100nsec  = newperftime100nsec;

	double a = (double)lnValueDelta / DeltaPerfTime100nSec;

  double f = (1.0 - a) * 100.0;
  cpuusage = (int)(f + 0.5);	// rounding the result

  if(cpuusage < 0)  return 0;

  #endif

	return cpuusage;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XWINDOWSSYSTEM::GetCPUUsageForProcessName(XCHAR* processname)
* @brief      GetCPUUsageForProcessName
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  processname : 
*
* @return     int : 
*
*---------------------------------------------------------------------------------------------------------------------*/
int XWINDOWSSYSTEM::GetCPUUsageForProcessName(XCHAR* processname)
{
  int				       cpuusage = 0;

  #ifndef BUILDER
  HANDLE           hprocesssnap;
  PROCESSENTRY32   pe32;
  bool             status   = false;

  // Take a snapshot of all processes in the system.
  hprocesssnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  if(hprocesssnap == INVALID_HANDLE_VALUE )  return false;

  // Set the size of the structure before using it.

  memset(&pe32, 0, sizeof(PROCESSENTRY32));
  pe32.dwSize = sizeof(PROCESSENTRY32);

  // Retrieve information about the first process, and exit if unsuccessful
  if(!Process32First(hprocesssnap, &pe32))
    {
      CloseHandle(hprocesssnap);  // clean the snapshot object
      return false;
    }

  // Now walk the snapshot of processes
  do{ XSTRING  nametask(pe32.szExeFile);

      //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Process %s  : [%s]"), processname, nametask.Get());

      if(!nametask.Compare(processname, true))
        {
           cpuusage = GetCPUUsageForProcessID((XDWORD)pe32.th32ProcessID);
        }

    } while(Process32Next(hprocesssnap, &pe32));

  CloseHandle(hprocesssnap);

  #endif

  return cpuusage;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XWINDOWSSYSTEM::GetCPUUsageForProcessID(XDWORD processID)
* @brief      GetCPUUsageForProcessID
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  processID : 
*
* @return     int : 
*
*---------------------------------------------------------------------------------------------------------------------*/
int XWINDOWSSYSTEM::GetCPUUsageForProcessID(XDWORD processID)
{ int				                              cpuusage            = 0;

  #ifndef BUILDER
  XWINDOWSSYSTEM_PERFCOUNTERS<LONGLONG>   perfcounters;
	DWORD                                   objectindex;
	DWORD                                   cpuusageindex;
	LONGLONG		                            newvalue            = 0;
	PPERF_DATA_BLOCK                        perfdata            = NULL;
	LARGE_INTEGER	                          newperftime100nsec  = { 0 };
  XWINDOWSSYSTEM_CPUUSAGESTATUS*          cus                 = NULL;

  cus = AddCPUUsageStatus(processID);
  if(!cus) return 0;

	objectindex     = XWINDOWSSYSTEM_PROCESS_OBJECT_INDEX;
	cpuusageindex   = XWINDOWSSYSTEM_PROCESSOR_TIME_COUNTER_INDEX;

	newvalue = perfcounters.GetCounterValueForProcessID(&perfdata, objectindex, cpuusageindex, (DWORD)processID);
	newperftime100nsec = perfdata->PerfTime100nSec;

	if(cus->firsttime)
	  {
		  cus->firsttime           = false;
		  cus->oldvalue            = newvalue;
		  cus->oldperftime100nsec  = newperftime100nsec;

		  return 0;
	  }

	LONGLONG  lnValueDelta         = newvalue - cus->oldvalue;
	double    DeltaPerfTime100nSec = (double)newperftime100nsec.QuadPart - (double)cus->oldperftime100nsec.QuadPart;

	cus->oldvalue            = newvalue;
	cus->oldperftime100nsec  = newperftime100nsec;

	double a = (double)lnValueDelta / DeltaPerfTime100nSec;

  cpuusage = (int) (a*100);

  if(cpuusage < 0)  return 0;

  #endif

  return cpuusage;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XCHAR* XWINDOWSSYSTEM::GetEnviromentVariable(XCHAR* variablename)
* @brief      GetEnviromentVariable
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  variablename :
*
* @return     XCHAR* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XCHAR* XWINDOWSSYSTEM::GetEnviromentVariable(XCHAR* variablename)
{
  return (XCHAR*)_wgetenv((const wchar_t *)variablename);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSSYSTEM::SetEnviromentVariable(XCHAR* variablename, XCHAR* value)
* @brief      SetEnviromentVariable
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  variablename :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSSYSTEM::SetEnviromentVariable(XCHAR* variablename, XCHAR* value)
{
  XSTRING                 all;
  XWINDOWSREGISTRYMANAGER registrymanager;
  XWINDOWSREGISTRYKEY     registrykeyenv;

  for(int c=0; c<2; c++)
    {
      bool status = false;

      switch(c)
        {
          case 0: status = registrymanager.OpenKey(HKEY_CURRENT_USER, __L("Environment"), registrykeyenv);
                  break;

          case 1: status = registrymanager.OpenKey(HKEY_LOCAL_MACHINE, __L("SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment"), registrykeyenv);
                  break;
        }

      if(status)
        {
          XVARIANT valuevariant;

          registrykeyenv.ReadValue(variablename, valuevariant);
          valuevariant = value;
          registrykeyenv.WriteValue(variablename, valuevariant);

          registrymanager.CloseKey(registrykeyenv);
        }
    }

  all.Format(__L("%s=%s"), variablename, value);

  return _wputenv(all.Get())?false:true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSSYSTEM::DelEnviromentVariable(XCHAR* variablename)
* @brief      DelEnviromentVariable
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  variablename :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSSYSTEM::DelEnviromentVariable(XCHAR* variablename)
{
  XSTRING                 all;
  XWINDOWSREGISTRYMANAGER registrymanager;
  XWINDOWSREGISTRYKEY     registrykeyenv;

  for(int c=0; c<2; c++)
    {
      bool status = false;

      switch(c)
        {
          case 0: status = registrymanager.OpenKey(HKEY_CURRENT_USER, __L("Environment"), registrykeyenv);
                  break;

          case 1: status = registrymanager.OpenKey(HKEY_LOCAL_MACHINE, __L("SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment"), registrykeyenv);
                  break;
        }

      if(status)
        {
          registrykeyenv.DeleteValue(variablename);
          registrymanager.CloseKey(registrykeyenv);
        }
    }

  all.Format(__L("%s="), variablename);

  return _wputenv(all.Get())?false:true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSSYSTEM::GetUserAndDomain(XSTRING& user, XSTRING& domain)
* @brief      GetUserAndDomain
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  user : 
* @param[in]  domain : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSSYSTEM::GetUserAndDomain(XSTRING& user, XSTRING& domain)
{
  HANDLE        htoken   = NULL;
  PTOKEN_USER   ptiuser  = NULL;
  DWORD         cbti     = 0;
  SID_NAME_USE  snu;
  bool          status   = false;

  XSTRING       userextend;
  
  
  #ifndef BUILDER
   ULONG         size = 1024;
   
  userextend.AdjustSize(size);  
  GetUserNameEx(NameUserPrincipal, userextend.Get(), &size);
  userextend.AdjustSize();  
  #endif
    
  if(!OpenThreadToken(GetCurrentThread(), TOKEN_QUERY, TRUE, &htoken)) 
    {
      if(GetLastError() == ERROR_NO_TOKEN)
        {
          if(OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &htoken))
            {
              if(!GetTokenInformation(htoken, TokenUser, NULL, 0, &cbti)) 
                {
                  ptiuser = (PTOKEN_USER) HeapAlloc(GetProcessHeap(), 0, cbti);
                  if(ptiuser) 
                    {
                      // Retrieve the user information from the token.
                      if(GetTokenInformation(htoken, TokenUser, ptiuser, cbti, &cbti))
                        {
                          TCHAR   _user[1024];
                          TCHAR   _domain[1024];
                          DWORD   sizeuser      = sizeof(user);
                          DWORD   sizedomain    = sizeof(domain);
    
                          // Retrieve user name and domain name based on user's SID.
                          if(LookupAccountSid(NULL, ptiuser->User.Sid, _user, &sizeuser, _domain, &sizedomain, &snu))
                            {  
                              user.Set(_user);
                              domain.Set(_domain);


                              if(userextend.GetSize()) user = userextend;

                              status = true;
                            }
                        } 
                      
                      if(ptiuser)  HeapFree(GetProcessHeap(), 0, ptiuser);                                     
                    }             
                }
            }
        }

      if(htoken) CloseHandle(htoken);
    }

  return status;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSSYSTEM::ShutDown(XSYSTEM_CHANGESTATUSTYPE type)
* @brief      ShutDown of the SO
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  type : type of shutdown
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSSYSTEM::ShutDown(XSYSTEM_CHANGESTATUSTYPE type)
{
  if(type == XSYSTEM_CHANGESTATUSTYPE_UNKNOWN) return false;

  HANDLE            hToken;
  TOKEN_PRIVILEGES  tkp;

  // Get a token for this process.
  if(!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))  return false;

  // Get the LUID for the shutdown privilege.
  LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);

  tkp.PrivilegeCount            = 1;  // one privilege to set
  tkp.Privileges[0].Attributes  = SE_PRIVILEGE_ENABLED;

  // Get the shutdown privilege for this process.
  AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
  if(GetLastError() != ERROR_SUCCESS) return false;

  switch(type)
    {
      case XSYSTEM_CHANGESTATUSTYPE_REBOOT           :  if(!ExitWindowsEx(EWX_REBOOT   | EWX_FORCE, SHTDN_REASON_MAJOR_OPERATINGSYSTEM | SHTDN_REASON_MINOR_UPGRADE | SHTDN_REASON_FLAG_PLANNED)) return false;
                                                        break;

      case XSYSTEM_CHANGESTATUSTYPE_SESSION_LOGOFF   :  if(!ExitWindowsEx(EWX_LOGOFF   | EWX_FORCE, SHTDN_REASON_MAJOR_OPERATINGSYSTEM | SHTDN_REASON_MINOR_UPGRADE | SHTDN_REASON_FLAG_PLANNED)) return false;
                                                        break;

      case XSYSTEM_CHANGESTATUSTYPE_POWEROFF         :  if(!ExitWindowsEx(EWX_POWEROFF | EWX_FORCE, SHTDN_REASON_MAJOR_OPERATINGSYSTEM | SHTDN_REASON_MINOR_UPGRADE | SHTDN_REASON_FLAG_PLANNED)) return false;
                                                        break;

      case XSYSTEM_CHANGESTATUSTYPE_SUSPEND          :    
                                                        #ifndef BUILDER
                                                        if(!SetSuspendState(TRUE, FALSE, FALSE)) return false; 
                                                        #endif    
                                                        break;

    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XWINDOWSSYSTEM::Sound_GetLevel()
* @brief      Sound_GetLevel
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     int : 
*
*---------------------------------------------------------------------------------------------------------------------*/
int XWINDOWSSYSTEM::Sound_GetLevel()
{
  float                   currentvolume     = 0.0f;

  #ifndef BUILDER

  IMMDeviceEnumerator*    deviceenumerator  = NULL;
  IAudioEndpointVolume*   endpointvolume    = NULL;
  IMMDevice*              defaultdevice     = NULL;
  HRESULT                 hresult;
  bool                    status            = false;

  //-------------------------------------------------------------------------------------------------------------------

  CoInitialize(NULL);

  hresult = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceenumerator);
  if(!deviceenumerator) return 0;

  //-------------------------------------------------------------------------------------------------------------------

  hresult = deviceenumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultdevice);
  if(defaultdevice)
    {
      deviceenumerator->Release();
      deviceenumerator = NULL;

      //-------------------------------------------------------------------------------------------------------------------

      hresult = defaultdevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointvolume);
      defaultdevice->Release();
      defaultdevice = NULL;
      endpointvolume->GetMasterVolumeLevel(&currentvolume);

      //-------------------------------------------------------------------------------------------------------------------

      hresult = endpointvolume->GetMasterVolumeLevelScalar(&currentvolume);

      //-------------------------------------------------------------------------------------------------------------------

      endpointvolume->Release();

      status = true;
    }

  CoUninitialize();

  #endif

  return (int)(currentvolume*100);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSSYSTEM::Sound_SetLevel(int level)
* @brief      Sound_SetLevel
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  level : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSSYSTEM::Sound_SetLevel(int level)
{
  bool                    status            = false;

  #ifndef BUILDER

  float                   currentvolume     = 0.0f;
  IMMDeviceEnumerator*    deviceenumerator  = NULL;
  IAudioEndpointVolume*   endpointvolume    = NULL;
  IMMDevice*              defaultdevice     = NULL;
  HRESULT                 hresult;
 
  //-------------------------------------------------------------------------------------------------------------------

  CoInitialize(NULL);

  hresult = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceenumerator);
  if(!deviceenumerator) return false;

  //-------------------------------------------------------------------------------------------------------------------

  hresult = deviceenumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultdevice);
  deviceenumerator->Release();
  deviceenumerator = NULL;

  if(defaultdevice)
    {
      //-------------------------------------------------------------------------------------------------------------------

      hresult = defaultdevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointvolume);
      defaultdevice->Release();
      defaultdevice = NULL;
      endpointvolume->GetMasterVolumeLevel(&currentvolume);

      //-------------------------------------------------------------------------------------------------------------------

      hresult = endpointvolume->GetMasterVolumeLevelScalar(&currentvolume);

      endpointvolume->SetMute(false, NULL);
      hresult = endpointvolume->SetMasterVolumeLevelScalar((float)(level/100.0f), NULL);

      //-------------------------------------------------------------------------------------------------------------------

      endpointvolume->Release();

      status = true;
    }

  CoUninitialize();

  #endif

  return status;

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSSYSTEM::Sound_SetMutex(bool on)
* @brief      Sound_SetMutex
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  on : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSSYSTEM::Sound_SetMutex(bool on)
{
  bool                    status            = false;
  #ifndef BUILDER
  float                   currentvolume     = 0.0f;
  IMMDeviceEnumerator*    deviceenumerator  = NULL;
  IAudioEndpointVolume*   endpointvolume    = NULL;
  IMMDevice*              defaultdevice     = NULL;
  HRESULT                 hresult;
  

  //-------------------------------------------------------------------------------------------------------------------

  CoInitialize(NULL);

  hresult = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceenumerator);
  if(!deviceenumerator) return false;

  //-------------------------------------------------------------------------------------------------------------------

  hresult = deviceenumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultdevice);
 
  deviceenumerator->Release();
  deviceenumerator = NULL; 

  if(defaultdevice)
    {
      //-------------------------------------------------------------------------------------------------------------------

      hresult = defaultdevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointvolume);
      defaultdevice->Release();
      defaultdevice = NULL;
      endpointvolume->GetMasterVolumeLevel(&currentvolume);

      //-------------------------------------------------------------------------------------------------------------------

      hresult = endpointvolume->GetMasterVolumeLevelScalar(&currentvolume);

      endpointvolume->SetMute(on, NULL);

      //-------------------------------------------------------------------------------------------------------------------

      endpointvolume->Release();

      status = true;
    }

  CoUninitialize();
  #endif

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XWINDOWSSYSTEM::GetBatteryLevel(bool& isincharge, XBYTE& levelpercent)
* @brief      GetBatteryLevel
* @ingroup    PLATFORM_WINDOWS
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  isincharge : 
* @param[in]  levelpercent : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSSYSTEM::GetBatteryLevel(bool& isincharge, XBYTE& levelpercent)
{
  SYSTEM_POWER_STATUS powerstatus;

  isincharge    = false;
  levelpercent  = 0;

  if(!GetSystemPowerStatus(&powerstatus)) return false;

  if(powerstatus.BatteryLifePercent != 255) 
    {
      isincharge    = powerstatus.ACLineStatus?true:false;
      levelpercent  = powerstatus.BatteryLifePercent;

      return true;
    }

  /*
  #ifdef _DEBUG
  isincharge    = false;
  levelpercent  = 10;
  return true;  
  #endif
  */

  return false;      
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWINDOWSSYSTEM_CPUUSAGESTATUS* XWINDOWSSYSTEM::AddCPUUsageStatus(XCHAR* processname)
* @brief      AddCPUUsageStatus
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  processname : 
*
* @return     XWINDOWSSYSTEM_CPUUSAGESTATUS* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XWINDOWSSYSTEM_CPUUSAGESTATUS* XWINDOWSSYSTEM::AddCPUUsageStatus(XCHAR* processname)
{
  XWINDOWSSYSTEM_CPUUSAGESTATUS* cus = GetCPUUsageStatus(processname);
  if(cus) return cus;
  
  cus = new XWINDOWSSYSTEM_CPUUSAGESTATUS();
  if(!cus) return NULL;

  cus->processname = processname;
  
  cpuusagestatus.Add(cus);
  
  return cus;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWINDOWSSYSTEM_CPUUSAGESTATUS* XWINDOWSSYSTEM::GetCPUUsageStatus(XCHAR* processname)
* @brief      GetCPUUsageStatus
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  processname :
*
* @return     XWINDOWSSYSTEM_CPUUSAGESTATUS* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XWINDOWSSYSTEM_CPUUSAGESTATUS* XWINDOWSSYSTEM::GetCPUUsageStatus(XCHAR* processname)
{
  if(cpuusagestatus.IsEmpty()) return NULL;

  for(XDWORD c=0; c<cpuusagestatus.GetSize(); c++)
    {
      XWINDOWSSYSTEM_CPUUSAGESTATUS* cus = cpuusagestatus.Get(c);
      if(cus)
        {
          if(!cus->processname.Compare(processname, true)) return cus;
        }
    }

  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWINDOWSSYSTEM_CPUUSAGESTATUS* XWINDOWSSYSTEM::AddCPUUsageStatus(XDWORD processID)
* @brief      AddCPUUsageStatus
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  processID : 
*
* @return     XWINDOWSSYSTEM_CPUUSAGESTATUS* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XWINDOWSSYSTEM_CPUUSAGESTATUS* XWINDOWSSYSTEM::AddCPUUsageStatus(XDWORD processID)
{
  XWINDOWSSYSTEM_CPUUSAGESTATUS* cus = GetCPUUsageStatus(processID);
  if(cus) return cus;
  
  cus = new XWINDOWSSYSTEM_CPUUSAGESTATUS();
  if(!cus) return NULL;

  cus->processID = processID;

  cpuusagestatus.Add(cus);
  
  return cus;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWINDOWSSYSTEM_CPUUSAGESTATUS* XWINDOWSSYSTEM::GetCPUUsageStatus(XDWORD processID)
* @brief      GetCPUUsageStatus
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  processID : 
*
* @return     XWINDOWSSYSTEM_CPUUSAGESTATUS* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XWINDOWSSYSTEM_CPUUSAGESTATUS* XWINDOWSSYSTEM::GetCPUUsageStatus(XDWORD processID)
{
  if(cpuusagestatus.IsEmpty()) return NULL;

  for(XDWORD c=0; c<cpuusagestatus.GetSize(); c++)
    {
      XWINDOWSSYSTEM_CPUUSAGESTATUS* cus = cpuusagestatus.Get(c);
      if(cus)
        {
          if(cus->processID == processID) return cus;
        }    
    }

  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSSYSTEM::DeleteAllCPUUsageStatus()
* @brief      DeleteAllCPUUsageStatus
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSSYSTEM::DeleteAllCPUUsageStatus()
{
  if(cpuusagestatus.IsEmpty()) return false;

  cpuusagestatus.DeleteContents();
  cpuusagestatus.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XWINDOWSSYSTEM::Clean()
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
void XWINDOWSSYSTEM::Clean()
{

}