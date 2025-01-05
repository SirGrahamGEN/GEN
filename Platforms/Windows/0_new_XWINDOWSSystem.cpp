/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XWINDOWSSystem.cpp
* 
* @class      XWINDOWSSYSTEM
* @brief      WINDOWS eXtended Utils System class
* @ingroup    PLATFORM_WINDOWS
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

#include "XWINDOWSSystem.h"

#define SECURITY_WIN32

#include <cstdio>
#include <windows.h>
#include <process.h>
#include <tlhelp32.h>
#include <Commctrl.h>
#include <Security.h>
#include <powrprof.h>
#include <winternl.h>

#ifndef BUILDER
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <pdh.h>

  #if(_MSC_PLATFORM_TOOLSET == 'v140')
  #include <versionhelpers.h>
  #endif

#include "XWINDOWSWMIInterface.h"

#pragma comment(lib, "pdh.lib")
#endif

#include "XWINDOWSRegistryManager.h"

#include "XBase.h"
#include "XFactory.h"
#include "XSleep.h"
#include "XFile.h"
#include "XFileTXT.h"
#include "XTrace.h"
#include "XLanguage_ISO_639_3.h"

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
* @fn         XWINDOWSSYSTEM::XWINDOWSSYSTEM()
* @brief      Constructor
* @ingroup    PLATFORM_WINDOWS
* 
* --------------------------------------------------------------------------------------------------------------------*/
XWINDOWSSYSTEM::XWINDOWSSYSTEM() : XSYSTEM()
{
  Clean();
  
  wmiinterface = new XWINDOWSWMIINTERFACE();
  if(wmiinterface)  
    { 
      if(!wmiinterface->Ini())
        {
          delete wmiinterface;
          wmiinterface = NULL;
  
        }
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWINDOWSSYSTEM::~XWINDOWSSYSTEM()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_WINDOWS
*
* --------------------------------------------------------------------------------------------------------------------*/
XWINDOWSSYSTEM::~XWINDOWSSYSTEM()
{
  if(wmiinterface)  
    { 
      wmiinterface->End();
      delete wmiinterface;
    }

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSYSTEM_HARDWARETYPE XWINDOWSSYSTEM::GetTypeHardware(int* revision)
* @brief      Get Type Hardware
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  revision : Type hardware
*
* @return     XSYSTEM_HARDWARETYPE :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSYSTEM_HARDWARETYPE XWINDOWSSYSTEM::GetTypeHardware(int* revision)
{
  if(revision) (*revision) = -1;

  return XSYSTEM_HARDWARETYPE_PC;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSYSTEM_PLATFORM XWINDOWSSYSTEM::GetPlatform(XSTRING* namestring)
* @brief      GetPlatform
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  namestring : 
* 
* @return     XSYSTEM_PLATFORM : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XSYSTEM_PLATFORM XWINDOWSSYSTEM::GetPlatform(XSTRING* namestring)
{
  if(namestring)  namestring->Set(__L("Windows"));

  return XSYSTEM_PLATFORM_WINDOWS;  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XWINDOWSSYSTEM::GetOperativeSystemID(XSTRING& ID)
* @brief      GetOperativeSystemID
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  ID : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSSYSTEM::GetOperativeSystemID(XSTRING& ID)
{
  ID.Empty();

  #ifndef BUILDER
  XSTRING                wmianswer[4];

  if(wmiinterface)
    {
      wmiinterface->DoQuery(__L("Win32_OperatingSystem"), __L("Caption")        , wmianswer[0]);
      wmiinterface->DoQuery(__L("Win32_OperatingSystem"), __L("BuildNumber")    , wmianswer[1]);
      wmiinterface->DoQuery(__L("Win32_OperatingSystem"), __L("CSDVersion")     , wmianswer[2]);
      wmiinterface->DoQuery(__L("Win32_OperatingSystem"), __L("OSArchitecture") , wmianswer[3]);
    }

  ID.Format(__L("%s Build(%s) %s %s"), wmianswer[0].Get(), wmianswer[1].Get(), wmianswer[2].Get(), wmianswer[3].Get());  
  #endif

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLANGUAGE_CODE XWINDOWSSYSTEM::GetLanguageSO()
* @brief      GetLanguageSO
* @ingroup    PLATFORM_WINDOWS
*
* @return     XLANGUAGE_CODE :
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* @fn         XSTRING* XWINDOWSSYSTEM::GetBIOSSerialNumber()
* @brief      GetBIOSSerialNumber
* @ingroup    PLATFORM_WINDOWS
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* XWINDOWSSYSTEM::GetBIOSSerialNumber()
{
  #ifndef BUILDER
  
  if(wmiinterface)
    {
      wmiinterface->DoQuery(__L("Win32_BaseBoard"), __L("SerialNumber"), BIOSserialnumber);
    }
  #endif

  return &BIOSserialnumber;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* XWINDOWSSYSTEM::GetCPUSerialNumber()
* @brief      GetCPUSerialNumber
* @ingroup    PLATFORM_WINDOWS
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* XWINDOWSSYSTEM::GetCPUSerialNumber()
{
  #ifndef BUILDER
  if(wmiinterface)
    {
      wmiinterface->DoQuery(__L("Win32_Processor"), __L("ProcessorId"), CPUserialnumber);
    }
  
  #endif

  return &CPUserialnumber;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         float XWINDOWSSYSTEM::GetCPUTemperature()
* @brief      GetCPUTemperature
* @ingroup    PLATFORM_WINDOWS
* 
* @return     float : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
float XWINDOWSSYSTEM::GetCPUTemperature()
{
  XSTRING CPUtemperaturestr;

  #ifndef BUILDER

  if(wmiinterface)
    {
      wmiinterface->DoQuery(__L("Win32_PerfFormattedData_Counters_ThermalZoneInformation"), __L("Temperature"), CPUtemperaturestr);
    }
  #endif

  int   CPUtemperature = 0;
  float CPUtemperaturefloat = 0.0f;

  CPUtemperature = CPUtemperaturestr.ConvertToInt();

  CPUtemperaturefloat   = (float)CPUtemperature;
  CPUtemperaturefloat  -= 273.2f;

  return CPUtemperaturefloat;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSSYSTEM::GetMemoryInfo(XDWORD& total,XDWORD& free)
* @brief      Get Memory Info
* @ingroup    PLATFORM_WINDOWS
*
* @param[out]  total : total memory in bytes.
* @param[out]  free : free memory in bytes.
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* @return     int : 
*
* --------------------------------------------------------------------------------------------------------------------*/
int XWINDOWSSYSTEM::GetCPUUsageTotal()
{
  #ifndef BUILDER

  HQUERY                query         = NULL;
  HCOUNTER              hcounter      = NULL; 
  DWORD                 countertype;
  PDH_FMT_COUNTERVALUE  counterval;
  double                cpuusage      = 0.0f;
  bool                  ok            = false;
  PDH_STATUS            status;
  
  status = PdhOpenQuery(NULL, NULL, &query);
  if(status == ERROR_SUCCESS)
    {      
      status = PdhAddEnglishCounter(query, L"\\Processor(_Total)\\% Processor Time", 0, &hcounter);
      if(status == ERROR_SUCCESS)
        {             
          for(int c=0; c<5; c++)
            {
              status = PdhCollectQueryData(query);
              if(status == ERROR_SUCCESS)
                {                
                  status = PdhGetFormattedCounterValue(hcounter, PDH_FMT_DOUBLE, &countertype, &counterval);
                  if(status == ERROR_SUCCESS)
                    {
                      cpuusage = counterval.doubleValue;
                      ok       = true;
                      break;
                    }
                }
            }
        }    
  
      PdhCloseQuery(&query);
    }

  if(!ok)
    {
      return XSYSTEM_CPUUSAGE_ERROR;
    }
              
  return (int)RoundOff(cpuusage, 1);
   
  #else

  return XSYSTEM_CPUUSAGE_ERROR;

  #endif
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XWINDOWSSYSTEM::GetCPUUsageForProcessName(XCHAR* processname)
* @brief      GetCPUUsageForProcessName
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  processname : 
*
* @return     int : 
*
* --------------------------------------------------------------------------------------------------------------------*/
int XWINDOWSSYSTEM::GetCPUUsageForProcessName(XCHAR* processname)
{
  int				       percent = 0;

  #ifndef BUILDER

  HANDLE           hprocesssnap;
  PROCESSENTRY32   pe32;  

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

      // XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Process %s  : [%s]"), processname, nametask.Get());

      if(nametask.Find(processname, true) != XSTRING_NOTFOUND)
        {
          percent = GetCPUUsageForProcessID((XDWORD)pe32.th32ProcessID);
        }

    } while(Process32Next(hprocesssnap, &pe32));

  CloseHandle(hprocesssnap);

  #endif

  return percent;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XWINDOWSSYSTEM::GetCPUUsageForProcessID(XDWORD processID)
* @brief      GetCPUUsageForProcessID
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  processID : 
*
* @return     int : 
*
* --------------------------------------------------------------------------------------------------------------------*/
int XWINDOWSSYSTEM::GetCPUUsageForProcessID(XDWORD processID)
{ 
  #ifndef BUILDER

  static int      processor_count_ = -1;
  static int64_t  last_time_ = 0;
  static int64_t  last_system_time_ = 0;

  FILETIME        now;
  FILETIME        creation_time;
  FILETIME        exit_time;
  FILETIME        kernel_time;
  FILETIME        user_time;
  int64_t         system_time;
  int64_t         time;
  int64_t         system_time_delta;
  int64_t         time_delta;

  double          cpu_percent = -1;

  if(processor_count_ == -1)
    {
      SYSTEM_INFO info;

      GetSystemInfo(&info);    
      processor_count_ = (int)info.dwNumberOfProcessors;
    }

  GetSystemTimeAsFileTime(&now);

  HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, processID);
  if(!GetProcessTimes(hProcess, &creation_time, &exit_time, &kernel_time, &user_time))
    {
      return XSYSTEM_CPUUSAGE_ERROR;      
    }

  system_time = (FileTime2UTC(&kernel_time) + FileTime2UTC(&user_time)) / processor_count_;
  time        = FileTime2UTC(&now);

  if((last_system_time_ == 0) || (last_time_ == 0))
    {
      last_system_time_ = system_time;
      last_time_        = time;

      return GetCPUUsageForProcessID(processID);
  }

  system_time_delta = system_time - last_system_time_;
  time_delta        = time        - last_time_;

  if(time_delta == 0)
    {
      return GetCPUUsageForProcessID(processID);
    }

  cpu_percent        = (double)((system_time_delta * 100 + time_delta / 2) / time_delta);
  last_system_time_ = system_time;
  last_time_        = time;

  return (int)RoundOff(cpu_percent, 1);
  
  #else

  return XSYSTEM_CPUUSAGE_ERROR;

  #endif
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XCHAR* XWINDOWSSYSTEM::GetEnviromentVariable(XCHAR* variablename)
* @brief      GetEnviromentVariable
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  variablename :
*
* @return     XCHAR* :
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* @param[in]  variablename :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* @param[in]  variablename :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* @param[in]  user : 
* @param[in]  domain : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* @param[in]  type : type of shutdown
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSSYSTEM::ShutDown(XSYSTEM_CHANGESTATUSTYPE type)
{
  if(type == XSYSTEM_CHANGESTATUSTYPE_NONE) return false;

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

                                          default    :  return false;


    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XWINDOWSSYSTEM::Sound_GetLevel()
* @brief      Sound_GetLevel
* @ingroup    PLATFORM_WINDOWS
*
* @return     int : 
*
* --------------------------------------------------------------------------------------------------------------------*/
int XWINDOWSSYSTEM::Sound_GetLevel()
{
  float                   currentvolume     = 0.0f;

  #ifndef BUILDER
  IMMDeviceEnumerator*    deviceenumerator  = NULL;
  IAudioEndpointVolume*   endpointvolume    = NULL;
  IMMDevice*              defaultdevice     = NULL;
  HRESULT                 hresult;
 
  //-------------------------------------------------------------------------------------------------------------------

  CoInitialize(NULL);

  hresult = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceenumerator);
  if(!deviceenumerator) return 0;
  if(hresult != S_OK) return 0;

  //-------------------------------------------------------------------------------------------------------------------

  hresult = deviceenumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultdevice);
  if(hresult != S_OK) return 0;
  if(defaultdevice)
    {
      deviceenumerator->Release();
      deviceenumerator = NULL;

      //-------------------------------------------------------------------------------------------------------------------

      defaultdevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointvolume);
      defaultdevice->Release();
      defaultdevice = NULL;
      endpointvolume->GetMasterVolumeLevel(&currentvolume);

      //-------------------------------------------------------------------------------------------------------------------

      endpointvolume->GetMasterVolumeLevelScalar(&currentvolume);
      if(hresult != S_OK) return 0;

      //-------------------------------------------------------------------------------------------------------------------

      endpointvolume->Release();
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
* @param[in]  level : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
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
  if(hresult != S_OK) return false;

  //-------------------------------------------------------------------------------------------------------------------

  hresult = deviceenumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultdevice);
  if(hresult != S_OK) return false;

  deviceenumerator->Release();
  deviceenumerator = NULL;

  if(defaultdevice)
    {
      //-------------------------------------------------------------------------------------------------------------------

      hresult = defaultdevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointvolume);
      if(hresult != S_OK) return false;

      defaultdevice->Release();
      defaultdevice = NULL;
      endpointvolume->GetMasterVolumeLevel(&currentvolume);

      //-------------------------------------------------------------------------------------------------------------------

      endpointvolume->GetMasterVolumeLevelScalar(&currentvolume);

      endpointvolume->SetMute(false, NULL);
      endpointvolume->SetMasterVolumeLevelScalar((float)(level/100.0f), NULL);

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
* @param[in]  on : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSSYSTEM::Sound_SetMutex(bool on)
{
  bool                    status            = false;
  #ifndef BUILDER
  float                   currentvolume     = 0.0f;
  IMMDeviceEnumerator*    deviceenumerator  = NULL;
  IAudioEndpointVolume*   endpointvolume    = NULL;
  IMMDevice*              defaultdevice     = NULL;
  HRESULT                 hresult;
 
  CoInitialize(NULL);

  hresult = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceenumerator);
  if(!deviceenumerator) return false;
  if(hresult != S_OK) return false;

  hresult = deviceenumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultdevice);
  if(hresult != S_OK) return false;
 
  deviceenumerator->Release();
  deviceenumerator = NULL; 

  if(defaultdevice)
    {
      hresult = defaultdevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointvolume);
      status = (hresult == S_OK)?true:false;

      if(status)
        {
          defaultdevice->Release();
          defaultdevice = NULL;
          endpointvolume->GetMasterVolumeLevel(&currentvolume);

          endpointvolume->GetMasterVolumeLevelScalar(&currentvolume);
          endpointvolume->SetMute(on, NULL);

          endpointvolume->Release();
        }
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

  return false;      
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         uint64_t XWINDOWSSYSTEM::FileTime2UTC(const FILETIME*ftime)
* @brief      FileTime2UTC
* @ingroup    PLATFORM_WINDOWS
* 
* @param[in]  FILETIME*ftime : 
* 
* @return     uint64_t : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
uint64_t XWINDOWSSYSTEM::FileTime2UTC(const FILETIME *ftime)
{
  LARGE_INTEGER li;

  li.LowPart  = ftime->dwLowDateTime;
  li.HighPart = ftime->dwHighDateTime;

  return li.QuadPart;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XWINDOWSSYSTEM::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_WINDOWS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XWINDOWSSYSTEM::Clean()
{
  wmiinterface    =  NULL;
}


#pragma endregion

