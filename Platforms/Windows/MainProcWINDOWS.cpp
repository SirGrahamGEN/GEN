/**-------------------------------------------------------------------------------------------------------------------
*
* @file       MainProcWINDOWS.cpp
*
* @class      MAINPROCWINDOWS
* @brief      Main procedure WINDOWS class
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

#include <winsock2.h>
#include <windows.h>
#include <float.h>
#include <tchar.h>

#pragma warning(push)
#pragma warning (disable : 4091)
#include <dbghelp.h>
#pragma warning(pop)

#include "XWINDOWSFactory.h"
#include "XWINDOWSTrace.h"
#include "XWINDOWSRand.h"
#include "XWINDOWSSleep.h"
#include "XWINDOWSSystem.h"
#include "XWINDOWSTrace.h"

#ifdef XPROCESSMANAGER_ACTIVE
  #include "XWINDOWSProcessManager.h"
#endif


#ifdef XSHAREDMEMORYMANAGER_ACTIVE
  #include "XWINDOWSSharedMemoryManager.h"
#endif

#ifdef XDRIVEIMAGEMANAGER_ACTIVE
  #include "XWINDOWSDriveImageManager.h"
#endif

#ifdef XEEPROMMEMORYMANAGER_ACTIVE
  #include "XWINDOWSEEPROMMemoryManager.h"
#endif


#ifdef GRP_ACTIVE
#include "GRPWINDOWSFactory.h"
#endif

#ifdef INP_ACTIVE
#include "INPWINDOWSDeviceKeyboard.h"
#include "INPWINDOWSDeviceMouse.h"
#include "INPWINDOWSFactoryDevices.h"
#include "INPManager.h"
#include "INPFactoryDevices.h"
#endif

#ifdef SND_ACTIVE
#include "SNDFactory_OpenAL.h"
#include "SNDFactory.h"
#endif

#ifdef DIO_ACTIVE
#include "DIODNSResolved.h"
#include "DIOWINDOWSFactory.h"

  #ifdef DIOGPIO_ACTIVE
  #include "DIOGPIO.h"
    #ifdef DIO_GPIO_PCPARALLEL_ACTIVE
    #include "DIOWINDOWSGPIOPCParallel.h"
    #endif   
  #endif

  #ifdef DIOALERTS_ACTIVE
  #include "DIOAlerts.h"
  #endif

#endif


#include "XRand.h"
#include "XSleep.h"
#include "XPath.h"
#include "XString.h"
#include "XLog.h"
#include "XFile.h"
#include "XTimer.h"
#include "XThreadCollected.h"
#include "XDateTime.h"
#include "XTranslation_GEN.h"
#include "XTranslation.h"
#include "XPublisher.h"

#include "MainProcWINDOWS.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

#ifdef XTRACE_ACTIVE
XWINDOWSTRACE           windowsdebugtrace;
#endif
MAINPROCWINDOWS         mainprocwindows;
XSTRING                 allexceptiontext;


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/

DWORD WINAPI            Service_WorkerThread          (LPVOID lpParam);

bool                    Exception_Printf              (bool iserror, XCHAR* title, XCHAR* mask, ...);
BOOL                    Exception_ConsoleHandler      (DWORD fdwctrltype);
bool                    Exception_ShutDown            (XSYSTEM_CHANGESTATUSTYPE type);



/*--------------------------------------------------------------------------------------------------------------------*/
/*  MAINPROCWINDOWS                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         MAINPROCWINDOWS::MAINPROCWINDOWS()
* @brief      Constructor
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
MAINPROCWINDOWS::MAINPROCWINDOWS()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         MAINPROCWINDOWS::~MAINPROCWINDOWS()
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
MAINPROCWINDOWS::~MAINPROCWINDOWS()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MAINPROCWINDOWS::Ini(APPMAIN* appmain, APPBASE_APPLICATIONMODE_TYPE applicationmode)
* @brief      Ini
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  appmain :
* @param[in]  applicationmode :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool MAINPROCWINDOWS::Ini(APPMAIN* appmain, APPBASE_APPLICATIONMODE_TYPE applicationmode)
{
  this->appmain = appmain;

  //---------------------------------------------------------------------------

  #if defined(DIO_ACTIVE) || defined(DIOUDP_ACTIVE) || defined(DIOTCPIP_ACTIVE) || defined(DIOBLUETOOTH_ACTIVE)
  XWORD   versionrequested = WINSOCK_VERSION;
  WSADATA data;
  int     error = false;

  error = WSAStartup(versionrequested, &data);
  if(!error)
    {
      if(data.wVersion != versionrequested) error = WSAVERNOTSUPPORTED;
    }

  if(error)
    {
      WSACleanup();
      return false;
    }
  #endif

  //---------------------------------------------------------------------------

  if(!Factorys_Ini()) return false;


  #ifdef APP_ACTIVE

  if(!appmain)                              return false;
  if(!appmain->Create())                    return false;
  if(!appmain->Ini(this, applicationmode))  return false;

  #else

   if(Main_Proc_PlatformIni)
    {
      if(!Main_Proc_PlatformIni(this)) return false;
    }

  GEN_XPATHSMANAGER.GetAppExecPath()->Set(GetXPathExec()->Get());
  GetXPathExec()->SetOnlyDriveAndPath();
  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_ROOT , (*GetXPathExec()));

   if(Main_Proc_Ini)
    {
      if(!Main_Proc_Ini(this)) return false;
    }

  #endif

  isrunningasservice = mainprocwindows.IsRunningAsService();

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MAINPROCWINDOWS::Update()
* @brief      Update
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool MAINPROCWINDOWS::Update()
{
  if(!isrunningasservice)
    {
      #ifdef GRP_ACTIVE
      MSG   msg;

      APPBASE* app = NULL;
      if(mainprocwindows.GetAppMain()) app = mainprocwindows.GetAppMain()->GetApplication();

      while(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
          switch(msg.message)
            {
              case WM_QUIT       : if(app) app->SetExitType(APPBASE_EXITTYPE_BY_USER);
                                   break;

              case WM_CLOSE      : PostQuitMessage(APPBASE_EXITTYPE_BY_USER);
                                   break;
            }

          TranslateMessage(&msg);
          DispatchMessage(&msg);
        }
      #endif

      #ifdef INP_ACTIVE
      GEN_INPMANAGER.Update();
      #endif
    }


  #ifdef APP_ACTIVE
  if(appmain)
    {
      if(!appmain->Update()) return false;
    }
  #else
   if(Main_Proc_Update)
    {
      if(!Main_Proc_Update(this)) return false;
    }
  #endif

  #ifndef GRP_ACTIVE
  Sleep(5);
  #endif

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MAINPROCWINDOWS::End()
* @brief      End
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool MAINPROCWINDOWS::End()
{
  #ifdef APP_ACTIVE

  if(appmain) appmain->End();

  #else

  if(Main_Proc_End)
    {
      if(!Main_Proc_End(this)) return false;
    }

  #endif

  DeleteAllExecParams();

  Factorys_End();

  #ifdef APP_ACTIVE

  if(appmain) appmain->Delete();

  #else

  if(Main_Proc_PlatformEnd)
    {
      if(!Main_Proc_PlatformEnd(this)) return false;
    }

  #endif

  XFILE_DISPLAYNOTCLOSEFILES
  XMEMORY_CONTROL_DISPLAYMEMORYLEAKS

  #if defined(DIO_ACTIVE) || defined(DIOUDP_ACTIVE) || defined(DIOTCPIP_ACTIVE) || defined(DIOBLUETOOTH_ACTIVE)
  WSACleanup();
  #endif

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MAINPROCWINDOWS::Factorys_Ini()
* @brief      Factorys Ini
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool MAINPROCWINDOWS::Factorys_Ini()
{
  if(!XFACTORY::SetInstance(new XWINDOWSFACTORY())) return false;
  
  #ifdef XSYTEM_ACTIVE  
  if(!XSYSTEM::SetInstance(new XWINDOWSSYSTEM()))  return false;
  XBUFFER::SetHardwareUseLittleEndian(GEN_XSYSTEM.HardwareUseLittleEndian());
  #endif

  #ifdef XSLEEP_ACTIVE
  if(!XSLEEP::SetInstance(new XWINDOWSSLEEP())) return false;
  #endif

  if(!XRAND::SetInstance(new XWINDOWSRAND())) return false;
  
  #ifdef XPROCESSMANAGER_ACTIVE
  if(!XPROCESSMANAGER::SetInstance(new XWINDOWSPROCESSMANAGER())) return false;
  #endif
  
  #ifdef XSHAREDMEMORYMANAGER_ACTIVE
  if(!XSHAREDMEMORYMANAGER::SetInstance(new XWINDOWSSHAREDMEMORYMANAGER())) return false;
  #endif

  #ifdef XDRIVEIMAGE_ACTIVE
  if(!XDRIVEIMAGE::SetInstance(new XWINDOWSDRIVEIMAGE())) return false;
  #endif

  #ifdef XEEPROMMEMORYMANAGER_ACTIVE
  if(!XEEPROMMEMORYMANAGER::SetInstance(new XWINDOWSEEPROMMEMORYMANAGER())) return false;
  #endif

  #ifdef XTRACE_VIRTUALCLOCKTICK
  xtimerclock = new XTIMERCLOCK();
  if(!xtimerclock) return false;
  #endif

  #ifdef INP_ACTIVE
  if(!INPFACTORYDEVICES::SetInstance(new INPWINDOWSFACTORYDEVICES())) return false;  
  #endif

  #ifdef DIO_ACTIVE
  if(!DIOFACTORY::SetInstance(new DIOWINDOWSFACTORY())) return false;
  
    #ifdef DIOGPIO_ACTIVE
      #ifdef DIO_GPIO_PCPARALLEL_ACTIVE
      if(!DIOGPIO::SetInstance(new DIOWINDOWSGPIOPCPARALLEL())) return false;    
      if(!DIOGPIO::GetInstance().Ini()) return false;
      #endif
    #endif
  #endif

  #ifdef SND_ACTIVE
  if(!SNDFACTORY::SetInstance(new SNDFACTORY_OPENAL())) return false;
  #endif

  #ifdef GRP_ACTIVE
  if(!GRPFACTORY::SetInstance(new GRPWINDOWSFACTORY())) return false;
  #endif

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MAINPROCWINDOWS::Factorys_End()
* @brief      Factorys End
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool MAINPROCWINDOWS::Factorys_End()
{
  #ifdef GRP_ACTIVE
  GRPFACTORY::DelInstance();
  #endif

  #ifdef SND_ACTIVE
  SNDFACTORY::DelInstance();
  #endif

  #ifdef DIO_ACTIVE
  #ifdef DIOGPIO_ACTIVE
  if(DIOGPIO::GetIsInstanced())
    {
      DIOGPIO::GetInstance().End();
      DIOGPIO::DelInstance();
    }
  #endif

  #ifdef DIOUDP_ACTIVE
  DIODNSRESOLVED::DelInstance();
  #endif

  DIOFACTORY::DelInstance();
  #endif

  #ifdef INP_ACTIVE
  INPMANAGER::DelInstance();
  INPFACTORYDEVICES::DelInstance();
  #endif

  #ifdef XTRACE_VIRTUALCLOCKTICK
  if(xtimerclock)
    {
      delete xtimerclock;
      xtimerclock = NULL;
    }
  #endif

  #ifdef DIOALERTS_ACTIVE
  DIOALERTS::DelInstance();
  #endif 

  #ifdef XLOG_ACTIVE
  XLOG::DelInstance();
  #endif


  #ifdef XPROCESSMANAGER_ACTIVE
  XPROCESSMANAGER::DelInstance();
  #endif

  #ifdef XEEPROMMEMORYMANAGER_ACTIVE
  XEEPROMMEMORYMANAGER::DelInstance();
  #endif

  #ifdef XDRIVEIMAGE_ACTIVE
  XDRIVEIMAGE::DelInstance();
  #endif

  #ifdef XSHAREDMEMORYMANAGER_ACTIVE   
  XSHAREDMEMORYMANAGER::DelInstance();
  #endif  

  XPATHSMANAGER::DelInstance();

  XTRANSLATION::DelInstance();
  XTRANSLATION_GEN::DelInstance();

  #ifdef XSLEEP_ACTIVE
  XSLEEP::DelInstance();
  #endif

  XRAND::DelInstance();

  #ifdef XSYSTEM_ACTIVE
  XSYSTEM::DelInstance();
  #endif

  #ifdef XPUBLISHER_ACTIVE
  XPUBLISHER::DelInstance();
  #endif

  #ifdef XTHREADCOLLECTION_ACTIVE
  XTHREADSCOLLECTEDMANAGER::DelInstance();
  #endif

  XFACTORY::DelInstance();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int MAINPROCWINDOWS::MainLoop()
* @brief      MainLoop
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int MAINPROCWINDOWS::MainLoop()
{
  int status = 0;

  #ifndef BUILDER
  __try  {
  #endif
          #ifdef APP_ACTIVE
          if(!mainprocwindows.Ini(&GEN_appmain, APPBASE_APPLICATIONMODE_TYPE_APPLICATION))
          #else
          if(!mainprocwindows.Ini())
          #endif
            {
              status=1;
            }

          if(!status)
            {
              while(mainprocwindows.Update())
                {

                }
            }

          mainprocwindows.GetXPathExec()->Empty();
          if(!mainprocwindows.End()) status = 1;

  #ifndef BUILDER
        }
        __except(Exception_Filter(GetExceptionCode(), GetExceptionInformation())) {  }
  #endif

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MAINPROCWINDOWS::IsRunningAsService()
* @brief      IsRunningAsService
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool MAINPROCWINDOWS::IsRunningAsService()
{
 // return IsRunningAsService(APPMODE_SERVICE_NAME);

  SERVICE_STATUS_PROCESS ssstatus;
  DWORD                  bytesneeded;
  SC_HANDLE              schscmanager;

  schscmanager = OpenSCManager( NULL,                              // local computer
                                NULL                  ,            // servicesActive database
                                SC_MANAGER_ALL_ACCESS  );          // full access rights
  if(!schscmanager) return false;

  // Get a handle to the service.
  SC_HANDLE schservice = OpenService( schscmanager          ,      // SCM database
                                      APPMODE_SERVICE_NAME  ,      // name of service
                                      SERVICE_ALL_ACCESS);         // full access

  if(!schservice)
    {
      CloseServiceHandle(schscmanager);
      return false;
    }

  // Check the status in case the service is not stopped.

  if(!QueryServiceStatusEx( schservice,                             // handle to service
                            SC_STATUS_PROCESS_INFO,                 // information level
                            (LPBYTE) &ssstatus,                     // address of structure
                            sizeof(SERVICE_STATUS_PROCESS),         // size of structure
                            &bytesneeded ) )                        // size needed if buffer is too small
    {
      CloseServiceHandle(schservice);
      CloseServiceHandle(schscmanager);
      return false;
    }

  DWORD processid = GetCurrentProcessId();
  if(processid == ssstatus.dwProcessId)
    {
      CloseServiceHandle(schservice);
      CloseServiceHandle(schscmanager);

      return true;
    }

  CloseServiceHandle(schservice);
  CloseServiceHandle(schscmanager);

  if((!ssstatus.dwProcessId) && (ssstatus.dwCurrentState == SERVICE_START_PENDING)) return true;

  return false;

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void MAINPROCWINDOWS::Clean()
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
void MAINPROCWINDOWS::Clean()
{
  isrunningasservice = false;  
}



#if !defined(APPMODE_LIBRARY_DINAMIC) 


/*--------------------------------------------------------------------------------------------------------------------*/
/*  WINDOWSSERVICE                                                                                                    */
/*--------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         WINDOWSSERVICE::WINDOWSSERVICE(XCHAR* servicename, bool can_stop, bool can_shutdown, bool can_pause)
* @brief      Constructor
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  servicename :
* @param[in]  can_stop :
* @param[in]  can_shutdown :
* @param[in]  can_pause :
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
WINDOWSSERVICE::WINDOWSSERVICE(XCHAR* servicename, bool can_stop, bool can_shutdown, bool can_pause, bool can_powerevent, bool can_sessionchange) : XWINDOWSSERVICEBASE(servicename, can_stop, can_shutdown, can_pause, can_powerevent, can_sessionchange)
{
  Clean();

  event_stopped = CreateEvent(NULL, TRUE, FALSE, NULL);
  if(event_stopped == NULL)
    {

    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         WINDOWSSERVICE::~WINDOWSSERVICE()
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
WINDOWSSERVICE::~WINDOWSSERVICE()
{
  Clean();

  if(event_stopped)
    {
      CloseHandle(event_stopped);
      event_stopped = NULL;
    }
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         HANDLE WINDOWSSERVICE::GetHandleStoppedEvent()
* @brief      GetHandleStoppedEvent
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     HANDLE :
*
*---------------------------------------------------------------------------------------------------------------------*/
HANDLE WINDOWSSERVICE::GetHandleStoppedEvent()
{
  return event_stopped;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool WINDOWSSERVICE::MustRestartService()
* @brief      MustRestartService
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool WINDOWSSERVICE::MustRestartService()
{
  return mustrestartservice;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void WINDOWSSERVICE::SetMustRestartService(bool mustrestartservice)
* @brief      SetMustRestartService
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  mustrestartservice : 
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void WINDOWSSERVICE::SetMustRestartService(bool mustrestartservice)
{
  this->mustrestartservice = mustrestartservice;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void WINDOWSSERVICE::On_Start(DWORD argc, XCHAR** args)
* @brief      On_Start
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  argc :
* @param[in]  args :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void WINDOWSSERVICE::On_Start(DWORD argc, XCHAR** args)
{
  //HANDLE hthread = 

  CreateThread(NULL, 0, Service_WorkerThread, this, 0, NULL);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void WINDOWSSERVICE::On_Stop()
* @brief      On_Stop
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void WINDOWSSERVICE::On_Stop()
{
  #ifdef APP_ACTIVE
  if(mainprocwindows.GetAppMain())
    {
      if(mainprocwindows.GetAppMain()->GetApplication())
        {
          if(mainprocwindows.GetAppMain()->GetApplication()->GetExitType() == APPBASE_EXITTYPE_UNKNOWN)  
            {
              mainprocwindows.GetAppMain()->GetApplication()->SetExitType(APPBASE_EXITTYPE_BY_USER);            
            }
        }
    }
  #endif

  if(event_stopped)
    {
      while(WaitForSingleObject(event_stopped, 0) != WAIT_OBJECT_0)
        {
          Sleep(5*1000);          
        }
    }
  
  if(MustRestartService())
    {
      //XWINDOWSSERVICEBASE::Start(APPMODE_SERVICE_NAME);    
    }
}



 /**-------------------------------------------------------------------------------------------------------------------
 *
 *  @fn         void WINDOWSSERVICE::On_Shutdown()
 *  @brief      On_Shutdown
 *  @ingroup    PLATFORM_WINDOWS
 *
 *  @author
 *  @date       01/03/2016 12:00
 *
 *  @return     void : does not return anything.
 *
 *---------------------------------------------------------------------------------------------------------------------*/
void WINDOWSSERVICE::On_Shutdown()
{
  #ifdef APP_ACTIVE
  if(mainprocwindows.GetAppMain())
    {
      if(mainprocwindows.GetAppMain()->GetApplication())
        {
           mainprocwindows.GetAppMain()->GetApplication()->SetSystemChangeStatus(XSYSTEM_CHANGESTATUSTYPE_REBOOT);
        }
    }
  #endif
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void WINDOWSSERVICE::On_PowerEvent(DWORD eventtype)
* @brief      On_PowerEvent
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  eventtype :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void WINDOWSSERVICE::On_PowerEvent(DWORD eventtype)
{
  #ifdef APP_ACTIVE
  //XSYSTEM_CHANGESTATUSTYPE systemchangestatustype = XSYSTEM_CHANGESTATUSTYPE_UNKNOWN;

  if(mainprocwindows.GetAppMain())
    {
      if(mainprocwindows.GetAppMain()->GetApplication())
        {
          if (eventtype == PBT_APMSUSPEND)
            {
              mainprocwindows.GetAppMain()->GetApplication()->SetSystemChangeStatus(XSYSTEM_CHANGESTATUSTYPE_SUSPEND);
            }
        }
    }
  #endif
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void WINDOWSSERVICE::On_SessionChange(DWORD eventtype)
* @brief      On_SessionChange
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  eventtype :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void WINDOWSSERVICE::On_SessionChange(DWORD eventtype)
{
  #ifdef APP_ACTIVE
  //XSYSTEM_CHANGESTATUSTYPE systemchangestatustype = XSYSTEM_CHANGESTATUSTYPE_UNKNOWN;

  if(mainprocwindows.GetAppMain())
    {
      if(mainprocwindows.GetAppMain()->GetApplication())
        {
          switch(eventtype)
            {
              case WTS_CONSOLE_CONNECT      : mainprocwindows.GetAppMain()->GetApplication()->SetSystemChangeStatus(XSYSTEM_CHANGESTATUSTYPE_CONSOLE_CONNECT);        break;
              case WTS_CONSOLE_DISCONNECT   : mainprocwindows.GetAppMain()->GetApplication()->SetSystemChangeStatus(XSYSTEM_CHANGESTATUSTYPE_CONSOLE_DISCONNECT);     break;
              case WTS_SESSION_LOGON        : mainprocwindows.GetAppMain()->GetApplication()->SetSystemChangeStatus(XSYSTEM_CHANGESTATUSTYPE_SESSION_LOGON);          break;
              case WTS_SESSION_LOGOFF       : mainprocwindows.GetAppMain()->GetApplication()->SetSystemChangeStatus(XSYSTEM_CHANGESTATUSTYPE_SESSION_LOGOFF);         break;
              case WTS_SESSION_LOCK         : mainprocwindows.GetAppMain()->GetApplication()->SetSystemChangeStatus(XSYSTEM_CHANGESTATUSTYPE_SESSION_LOCK);           break;
              case WTS_SESSION_UNLOCK       : mainprocwindows.GetAppMain()->GetApplication()->SetSystemChangeStatus(XSYSTEM_CHANGESTATUSTYPE_SESSION_UNLOCK);         break;
            }
        }
    }
  #endif
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void WINDOWSSERVICE::Clean()
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
void WINDOWSSERVICE::Clean()
{
  event_stopped       = NULL;
  mustrestartservice  = false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DWORD WINAPI Service_WorkerThread(LPVOID lpparam)
* @brief      INAPI Service_WorkerThread
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  lpparam :
*
* @return     DWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
DWORD WINAPI Service_WorkerThread(LPVOID lpparam)
{
  WINDOWSSERVICE* service = (WINDOWSSERVICE*)lpparam;
  bool            userstop = false;
  int             status   = 0;

  if(!service) return false;

  #ifdef APP_ACTIVE
  if(!mainprocwindows.Ini(&GEN_appmain, APPBASE_APPLICATIONMODE_TYPE_SERVICE))
  #else
  if(!mainprocwindows.Ini())
  #endif
    {
      status = 1;
    }

  if(!status)
    {
      while(1)
        {
          if(!mainprocwindows.Update())
            {
              userstop = true;
              break;
            }
        }
    }

  
  APPBASE_EXITTYPE exittype = APPBASE_EXITTYPE_UNKNOWN;

  #ifdef APP_ACTIVE  
  exittype =  mainprocwindows.GetAppMain()->GetApplication()->GetExitType();
  #endif
  
  mainprocwindows.GetXPathExec()->Empty();
  mainprocwindows.End();


  if(exittype == APPBASE_EXITTYPE_BY_SERVICERELOAD)
    {
      service->SetMustRestartService(true);
    }

  if(service->GetHandleStoppedEvent()) SetEvent(service->GetHandleStoppedEvent());

  if(userstop) service->Stop();

  //return (exittype == APPBASE_EXITTYPE_BY_SERVICERELOAD)?ERROR_EXCEPTION_IN_SERVICE:ERROR_SUCCESS;
  return ERROR_SUCCESS;
}




/*--------------------------------------------------------------------------------------------------------------------*/
/*  Main entrys                                                                                                       */
/*                                                                                                                    */
/*  wmain    : Windows UNICODE entry  /CONSOLE mode                                                                   */
/*  WinMain  : Windows entry          /WINDOWS mode                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int wmain(int argc, wchar_t* argv[])
* @brief      main
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  argc :
* @param[in]  argv[] :
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int wmain(int argc, wchar_t* argv[])
 {
  //wprintf(L"%s\n" , argv[0]);

  mainprocwindows.GetXPathExec()->Set(argv[0]);

  mainprocwindows.CreateParams(argc, argv);

  if(!mainprocwindows.IsRunningAsService())
    {
      // Need to enable FPE manually additionaly to the compiler flag
      // disabled right now as OpenAL has a FPE exception in windows, need to look into it
      // also windows timers and so on
      #ifdef FPE_ACTIVE
      _controlfp_s(NULL, 0, _EM_ZERODIVIDE); //  | _EM_OVERFLOW | _EM_UNDERFLOW | _EM_INVALID);
      #endif

      if(!SetConsoleCtrlHandler((PHANDLER_ROUTINE)Exception_ConsoleHandler, TRUE)) return -1;

      int status = 0;

      #ifdef APP_ACTIVE
      if(!mainprocwindows.Ini(&GEN_appmain, APPBASE_APPLICATIONMODE_TYPE_APPLICATION))
      #else
      if(!mainprocwindows.Ini())
      #endif
        {
          status=1;
        }

      if(!status)
        {
          while(mainprocwindows.Update());
        }

      int returncode = 0;

      #ifdef APP_ACTIVE
      if(mainprocwindows.GetAppMain())
        {
          if(mainprocwindows.GetAppMain()->GetApplication())
            {
              returncode = mainprocwindows.GetAppMain()->GetApplication()->GetExitType();
            }
        }
      #endif

      mainprocwindows.GetXPathExec()->Empty();

      mainprocwindows.End();

      if(!SetConsoleCtrlHandler((PHANDLER_ROUTINE)Exception_ConsoleHandler, FALSE)) return -1;

      return returncode;
    }
   else
    {
      WINDOWSSERVICE service(APPMODE_SERVICE_NAME);
      if(!WINDOWSSERVICE::Run(service))
        {

        }

      #ifdef APP_ACTIVE
      if(mainprocwindows.GetAppMain())
        {
          if(mainprocwindows.GetAppMain()->GetApplication())
            {
              return mainprocwindows.GetAppMain()->GetApplication()->GetExitType();
            }
        }
      #endif
    }

  return 0;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hprevinst, LPSTR cmdline, int cmdshow)
* @brief      WinMain
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  hinstance :
* @param[in]  hprevinst :
* @param[in]  cmdline :
* @param[in]  cmdshow :
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hprevinst, LPSTR cmdline, int cmdshow)
{
  int      nargs        = 0;
  LPWSTR*  ptrpathexec  = CommandLineToArgvW(__L(""), &nargs);
  XSTRING  xpathexecutable;
  XSTRING  cmdlinestr   = cmdline;

  mainprocwindows.SetHandle((void*)hinstance);

  for(int c=0; c<nargs; c++)
    {
      xpathexecutable += ptrpathexec[c];
      if(c != nargs-1)  xpathexecutable += __L(" ");
    }

  mainprocwindows.GetXPathExec()->Set(xpathexecutable);

  mainprocwindows.CreateParams(cmdlinestr.Get());
  cmdlinestr.Empty();
  xpathexecutable.Empty();

  if(!mainprocwindows.IsRunningAsService())
    {
      mainprocwindows.MainLoop();
    }
   else
    {
      WINDOWSSERVICE service(APPMODE_SERVICE_NAME);
      if(!WINDOWSSERVICE::Run(service))
        {


        }
    }

  #ifdef APP_ACTIVE
  if(mainprocwindows.GetAppMain())
    {
      if(mainprocwindows.GetAppMain()->GetApplication())
        {
          return mainprocwindows.GetAppMain()->GetApplication()->GetExitType();
        }
    }
  #endif

  return 0;
}

#else


/*--------------------------------------------------------------------------------------------------------------------*/
/*  WINDOWS DINAMIC LINK LIBRARY                                                                                      */
/*--------------------------------------------------------------------------------------------------------------------*/

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BOOL WINAPI DllMain(HINSTANCE hinstDLL,XDWORD fdwReason,LPVOID lpvReserved)
* @brief      Dll Main
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  hinstDLL :
* @param[in]  fdwReason :
* @param[in]  lpvReserved :
*
* @return     BOOL :
*
*---------------------------------------------------------------------------------------------------------------------*/
BOOL WINAPI DllMain(HINSTANCE hinstDLL, XDWORD fdwReason,LPVOID lpvReserved)
{
  switch(fdwReason)
    {
      case DLL_PROCESS_ATTACH : { XPATH xpathexecutable;

                                  xpathexecutable.AdjustSize(_MAXPATH);
                                  GetModuleFileName(hinstDLL, xpathexecutable.Get(), xpathexecutable.GetSize());
                                  xpathexecutable.AdjustSize();

                                  mainprocwindows.GetXPathExec()->Set(xpathexecutable);
                                  xpathexecutable.Empty();

                                  mainprocwindows.Ini();
                                }
                                break;

      case DLL_THREAD_ATTACH  : break;

      case DLL_THREAD_DETACH  : break;

      case DLL_PROCESS_DETACH : mainprocwindows.GetXPathExec()->Empty();
                                mainprocwindows.End();
                                break;
    }

  return true;
}


#endif




/*--------------------------------------------------------------------------------------------------------------------*/
/*  WINDOWS STACK WALKER                                                                                              */
/*--------------------------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void MAINPROCWINDOWSSTACKWALKER::OnSymInit(LPCSTR szSearchPath, DWORD symOptions, LPCSTR szUserName)
* @brief      OnSymInit
* @note       INTERNAL
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  szSearchPath :
* @param[in]  symOptions :
* @param[in]  szUserName :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void MAINPROCWINDOWSSTACKWALKER::OnSymInit(LPCSTR szSearchPath, DWORD symOptions, LPCSTR szUserName)
{
  Exception_Printf(true, NULL, __L("Stack trace: "));
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void MAINPROCWINDOWSSTACKWALKER::OnCallstackEntry(CallstackEntryType eType, CallstackEntry& entry)
* @brief      On Call Stack Entry
* @note       INTERNAL
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  eType :
* @param[in]  entry :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void MAINPROCWINDOWSSTACKWALKER::OnCallstackEntry(CallstackEntryType eType, CallstackEntry& entry)
{
  XSTRING modulename;
  XSTRING linefilename;
  XSTRING name;

  if((eType != lastEntry) && (entry.offset != 0))
    {
      if(entry.name[0]         == 0)  strcpy_s(entry.name, "(function-name not available)");
      if(entry.undName[0]      != 0)  strcpy_s(entry.name, entry.undName);
      if(entry.undFullName[0]  != 0)  strcpy_s(entry.name, entry.undFullName);
      if(entry.lineFileName[0] == 0)
        {
          strcpy_s(entry.lineFileName, "(filename not available)");
          if (entry.moduleName[0] == 0) strcpy_s(entry.moduleName, "(module-name not available)");
        }

      modulename   = entry.moduleName;
      linefilename = entry.lineFileName;
      name         = entry.name;

      Exception_Printf(true, NULL, __L("%08X  %-48s (%6d) %-64s"), (LPVOID) entry.offset, name.Get(), entry.lineNumber, linefilename.Get());
    }
}


/*--------------------------------------------------------------------------------------------------------------------*/
/*  EXCEPCION FUNCTIONS                                                                                               */
/*--------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BOOL Exception_ConsoleHandler(DWORD fdwctrltype)
* @brief      Exception Console Handler
* @note       INTERNAL
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  fdwctrltype :
*
* @return     BOOL :
*
*---------------------------------------------------------------------------------------------------------------------*/
BOOL Exception_ConsoleHandler(DWORD fdwctrltype)
{
  #ifdef APP_ACTIVE
  APPBASE* app = NULL;
  if(mainprocwindows.GetAppMain()) app = mainprocwindows.GetAppMain()->GetApplication();
  #endif

  switch(fdwctrltype)
    {
      case CTRL_BREAK_EVENT     : Exception_Printf(false, __L("EVENT"), __L("Ctrl-Break event."));
                                  #ifdef APP_ACTIVE
                                  if(app) app->SetExitType(APPBASE_EXITTYPE_BY_USER);
                                  #endif
                                  return FALSE;

      case CTRL_C_EVENT         : Exception_Printf(false, __L("EVENT"), __L("Ctrl-C event."));
                                  #ifdef APP_ACTIVE
                                  if(app) app->SetExitType(APPBASE_EXITTYPE_BY_USER);
                                  #endif
                                  return FALSE;

      case CTRL_CLOSE_EVENT     :
                                  #ifdef APP_ACTIVE
                                  if(app) app->SetExitType(APPBASE_EXITTYPE_BY_USER);
                                  #endif
                                  FreeConsole();         // Detachxconsole
                                  break;

      case CTRL_LOGOFF_EVENT    : Exception_Printf(false, __L("EVENT"), __L("Ctrl-Logoff event."));
                                  #ifdef APP_ACTIVE
                                  if(app) app->SetExitType(APPBASE_EXITTYPE_BY_SHUTDOWN);
                                  #endif
                                  FreeConsole();         // Detachxconsole
                                  ExitThread(0);         // Prevent closing.
                                  break;

      case CTRL_SHUTDOWN_EVENT  : Exception_Printf(false, __L("EVENT"), __L("Ctrl-Shutdown event."));
                                  #ifdef APP_ACTIVE
                                  if(app) app->SetExitType(APPBASE_EXITTYPE_BY_SHUTDOWN);
                                  #endif
                                  FreeConsole();         // Detachxconsole
                                  ExitThread(0);         // Prevent closing.
                                  break;

                      default   : return FALSE;
    }

  return FALSE;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int Exception_Filter(XDWORD code, struct _EXCEPTION_POINTERS* ep)
* @brief      Exception Filter
* @note       INTERNAL
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  code :
* @param[in]  _EXCEPTION_POINTERS* ep :
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int Exception_Filter(XDWORD code, struct _EXCEPTION_POINTERS* ep)
{
  XSTRING exception;
  XSTRING description;
  XSTRING string;

  allexceptiontext.Empty();

  APPBASE* app = NULL;
  #ifdef APP_ACTIVE
  if(mainprocwindows.GetAppMain()) app = mainprocwindows.GetAppMain()->GetApplication();
  #endif


  switch(code)
    {
      case EXCEPTION_ACCESS_VIOLATION         : exception   = __L("ACCESS VIOLATION");
                                                description = __L("Read from or write to a virtual address for which it does not have access.");
                                                break;

      case EXCEPTION_ARRAY_BOUNDS_EXCEEDED    : exception   = __L("ARRAY BOUNDS EXCEEDED");
                                                description = __L("Access an array element that is out of bounds");
                                                break;

      case EXCEPTION_DATATYPE_MISALIGNMENT    : exception   = __L("DATATYPE MISALIGNMENT");
                                                description = __L("Read or write data that is misaligned on hardware that does not provide alignment.");
                                                break;

      case EXCEPTION_FLT_DENORMAL_OPERAND     : exception   = __L("FLT DENORMAL OPERAND]");
                                                description = __L("One of the operands in a floating point operation is denormal.");
                                                break;

      case EXCEPTION_FLT_DIVIDE_BY_ZERO       : exception   = __L("FLT DIVIDE BY ZERO");
                                                description = __L("Divide a floating point value by a floating point divisor of 0 (zero).");
                                                break;

      case EXCEPTION_FLT_INEXACT_RESULT       : exception   = __L("FLT INEXACT RESULT");
                                                description = __L("A floating point operation cannot be represented exactly as a decimal fraction.");
                                                break;

      case EXCEPTION_FLT_INVALID_OPERATION    : exception   = __L("FLT INVALID OPERATION");
                                                description = __L("A floating point exception (not defined).");
                                                break;

      case EXCEPTION_FLT_OVERFLOW             : exception   = __L("FLT OVERFLOW");
                                                description = __L("The exponent of a floating point operation is greater than the magnitude allowed by the corresponding type.");
                                                break;

      case EXCEPTION_FLT_STACK_CHECK          : exception   = __L("FLT STACK CHECK");
                                                description = __L("The stack has overflowed or underflowed, because of a floating point operation.");
                                                break;

      case EXCEPTION_FLT_UNDERFLOW            : exception   = __L("FLT UNDERFLOW");
                                                description = __L("The exponent of a floating point operation is less than the magnitude allowed by the corresponding type.");
                                                break;

      case EXCEPTION_GUARD_PAGE               : exception   = __L("GUARD PAGE");
                                                description = __L("Accessed memory allocated with the PAGE GUARD modifier.");
                                                break;

      case EXCEPTION_ILLEGAL_INSTRUCTION      : exception   = __L("ILLEGAL INSTRUCTION");
                                                description = __L("Tries to execute an invalid instruction.");
                                                break;

      case EXCEPTION_IN_PAGE_ERROR            : exception   = __L("IN PAGE ERROR");
                                                description = __L("Tries to access a page that is not present, and the system is unable to load the page.");
                                                break;

      case EXCEPTION_INT_DIVIDE_BY_ZERO       : exception   = __L("INT DIVIDE BY ZERO");
                                                description = __L("Divide an integer value by an integer divisor of 0 (zero).");
                                                break;

      case EXCEPTION_INT_OVERFLOW             : exception   = __L("INT OVERFLOW");
                                                description = __L("The result of an integer operation creates a value that is too large to be held by the destination register.");
                                                break;

      case EXCEPTION_INVALID_DISPOSITION      : exception   = __L("INVALID DISPOSITION");
                                                description = __L("An exception handler returns an invalid disposition to the exception dispatcher.");
                                                break;

      case EXCEPTION_INVALID_HANDLE           : exception   = __L("INVALID HANDLE") ;
                                                description = __L("The thread used a handle to a kernel object that was invalid (probably because it had been closed).");
                                                break;

      case EXCEPTION_NONCONTINUABLE_EXCEPTION : exception   = __L("NONCONTINUABLE EXCEPTION");
                                                description = __L("The thread attempts to continue execution after a non-continuable exception occurs.");
                                                break;

      case EXCEPTION_PRIV_INSTRUCTION         : exception   = __L("PRIV INSTRUCTION");
                                                description = __L("Execute an instruction with an operation that is not allowed in the current computer mode.");
                                                break;

      case EXCEPTION_STACK_OVERFLOW           : exception   = __L("STACK OVERFLOW");
                                                description = __L("Stack overflow");
                                                break;

      case EXCEPTION_BREAKPOINT               : //Exception_Printf(__L("[EXCEPTION_BREAKPOINT]")              , __L("A breakpoint is encountered"));
      case EXCEPTION_SINGLE_STEP              : //Exception_Printf(__L("[EXCEPTION_SINGLE_STEP]")             , __L("A trace trap or other single instruction mechanism signals that one instruction is executed."));
      case STATUS_UNWIND_CONSOLIDATE          : return EXCEPTION_CONTINUE_SEARCH;
                                                break;

                                      default : return EXCEPTION_EXECUTE_HANDLER;
    }

  Exception_Printf(true, __L("EXCEPTION"), __L("%s: %s"), exception.Get(), description.Get());

  #ifdef APP_ACTIVE
  if(app)
    {
      if(app->GetTimerGlobal())
        {
          app->GetTimerGlobal()->GetMeasureString(string, true);
          Exception_Printf(false, NULL, __L("Time working: %s."), string.Get());
        }
    }
  #endif

  switch(code)
    {
      case EXCEPTION_ACCESS_VIOLATION         :
      case EXCEPTION_ARRAY_BOUNDS_EXCEEDED    :
      case EXCEPTION_DATATYPE_MISALIGNMENT    :
      case EXCEPTION_FLT_DENORMAL_OPERAND     :
      case EXCEPTION_FLT_DIVIDE_BY_ZERO       :
      case EXCEPTION_FLT_INEXACT_RESULT       :
      case EXCEPTION_FLT_INVALID_OPERATION    :
      case EXCEPTION_FLT_OVERFLOW             :
      case EXCEPTION_FLT_STACK_CHECK          :
      case EXCEPTION_FLT_UNDERFLOW            :
      case EXCEPTION_GUARD_PAGE               :
      case EXCEPTION_ILLEGAL_INSTRUCTION      :
      case EXCEPTION_IN_PAGE_ERROR            :
      case EXCEPTION_INT_DIVIDE_BY_ZERO       :
      case EXCEPTION_INT_OVERFLOW             :
      case EXCEPTION_INVALID_DISPOSITION      :
      case EXCEPTION_INVALID_HANDLE           :
      case EXCEPTION_NONCONTINUABLE_EXCEPTION :
      case EXCEPTION_PRIV_INSTRUCTION         :
      case EXCEPTION_STACK_OVERFLOW           : {

                                                  MAINPROCWINDOWSSTACKWALKER stackwalker;
                                                  stackwalker.ShowCallstack(GetCurrentThread(), ep->ContextRecord);


                                                  string.Format(__L("EXCEPTION %s"), exception.Get());

                                                  #ifdef DIOALERTS_ACTIVE
                                                  DIOALERT* alert = GEN_DIOALERTS.CreateAlert(DIOALERTLEVEL_DANGER, string.Get(), allexceptiontext.Get());
                                                  if(alert)
                                                    {
                                                      GEN_DIOALERTS.Send(DIOALERTSSENDER_ALL, DIOALERTS_CONDITIONS_ID_GENINTERN_EXCEPTION, alert);
                                                      delete alert;
                                                    }
                                                  #endif

                                                  #ifdef APP_ACTIVE
                                                  if(app) exit(APPBASE_EXITTYPE_BY_SERIOUSERROR);
                                                  #endif


                                                }
                                                break;
    }

  return EXCEPTION_EXECUTE_HANDLER;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool Exception_Printf(bool iserror, XCHAR* title, XCHAR* mask, ...)
* @brief      Exception Printf
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  iserror :
* @param[in]  title :
* @param[in]  mask :
* @param[in]  ... :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool Exception_Printf(bool iserror, XCHAR* title, XCHAR* mask, ...)
{
  XSTRING outstring;

  va_list arg;

  va_start(arg, mask);

  outstring.FormatArg(mask, &arg);

  va_end(arg);

  bool do_log = false;

  #ifdef XLOG_ACTIVE
  if(GEN_XLOG.IsActive())
    {
      GEN_XLOG.SetFilters(__L(""));

      if(GEN_XLOG.AddEntry(iserror?XLOGLEVEL_ERROR:XLOGLEVEL_WARNING, title, false, outstring.Get()))
        {
          do_log = true;
        }
    }
  #endif

  allexceptiontext += outstring;
  allexceptiontext += __L("\r\n");

  #ifdef XTRACE_ACTIVE
  if(!do_log)
    {
      int level = iserror?4:0;
      XTRACE_PRINTCOLOR(level, outstring.Get());
    }
  #endif

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         static bool Exception_PrintfStackTrace(const CONTEXT* context)
* @brief      Exception Printf Stack Trace
* @note       INTERNAL
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  CONTEXT* context :
*
* @return     static :
*
*---------------------------------------------------------------------------------------------------------------------*/
static bool Exception_PrintfStackTrace(const CONTEXT* context)
{
  static const int MAX_TRACES     = 60;
  static const int MAX_LENGTH     = 256;
  static const int BUFFER_LENGTH  = (sizeof(SYMBOL_INFO) + MAX_LENGTH * sizeof(wchar_t) + sizeof(ULONG64) - 1) / sizeof(ULONG64);

  SymSetOptions(SYMOPT_DEFERRED_LOADS | SYMOPT_UNDNAME | SYMOPT_LOAD_LINES | SYMOPT_LOAD_ANYTHING | SYMOPT_AUTO_PUBLICS | SYMOPT_OMAP_FIND_NEAREST | SYMOPT_DEBUG);
  if (!SymInitialize(GetCurrentProcess(), "http://msdl.microsoft.com/download/symbols", TRUE )) return false;

  void* trace[MAX_TRACES];
  int   count = CaptureStackBackTrace(0, MAX_TRACES , trace, NULL);

  Exception_Printf(true, NULL, __L("Stack trace: (%d) calls :"), count);

  for(int i=0; i<count; ++i)
    {
      ULONG64         buffer[BUFFER_LENGTH];
      DWORD_PTR       frame               = reinterpret_cast<DWORD_PTR>(trace[i]);
      DWORD64         sym_displacement    = 0;
      PSYMBOL_INFO    symbol              = reinterpret_cast<PSYMBOL_INFO>(&buffer[0]);

      symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
      symbol->MaxNameLen   = MAX_LENGTH;

      BOOL            has_symbol          = SymFromAddr(GetCurrentProcess(), frame, &sym_displacement, symbol);
      DWORD           line_displacement   = 0;
      IMAGEHLP_LINE64 line                = {};

      line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
      BOOL has_line                       = SymGetLineFromAddr64(GetCurrentProcess(), frame, &line_displacement, &line);

      XSTRING symbolname;
      XSTRING filename;
      XSTRING string;
      XSTRING mask;

      symbolname = symbol->Name;

      string.Format(__L(" [%02d] - 0x%08X : %-48s "), (count-i-1), (XDWORD)symbol->Address, symbolname.Get());
      if(has_line)
        {
          filename = line.FileName;
          mask.Format(__L("line (%02d) %s "), line.LineNumber, filename.Get());
          string += mask;
        }

      Exception_Printf(true, NULL, string.Get());
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool Exception_ShutDown(XSYSTEM_CHANGESTATUSTYPE type)
* @brief      Exception ShutDown
* @note       INTERNAL
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  type :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool Exception_ShutDown(XSYSTEM_CHANGESTATUSTYPE type)
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
      case XSYSTEM_CHANGESTATUSTYPE_REBOOT          :  if(!ExitWindowsEx(EWX_REBOOT   | EWX_FORCE, SHTDN_REASON_MAJOR_OPERATINGSYSTEM | SHTDN_REASON_MINOR_UPGRADE | SHTDN_REASON_FLAG_PLANNED)) return false;
                                                       break;

      case XSYSTEM_CHANGESTATUSTYPE_SESSION_LOGOFF  :  if(!ExitWindowsEx(EWX_LOGOFF   | EWX_FORCE, SHTDN_REASON_MAJOR_OPERATINGSYSTEM | SHTDN_REASON_MINOR_UPGRADE | SHTDN_REASON_FLAG_PLANNED)) return false;
                                                       break;

      case XSYSTEM_CHANGESTATUSTYPE_POWEROFF        :  if(!ExitWindowsEx(EWX_POWEROFF | EWX_FORCE, SHTDN_REASON_MAJOR_OPERATINGSYSTEM | SHTDN_REASON_MINOR_UPGRADE | SHTDN_REASON_FLAG_PLANNED)) return false;
                                                       break;
    }

  return true;
}


