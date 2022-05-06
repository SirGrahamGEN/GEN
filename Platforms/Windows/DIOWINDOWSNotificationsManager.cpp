/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOWINDOWSNotificationsManager.cpp
*
* @class      DIOWINDOWSNOTIFICATIONSMANAGER
* @brief      WINDOWS Data IO Notifications manager class
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "DIOWINDOWSNotificationsManager.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
*  @fn         DIOWINDOWSNOTIFICATIONSMANAGER::DIOWINDOWSNOTIFICATIONSMANAGER()
*  @brief      Constructor
*  @ingroup    DATAIO
*
*  ""
*  ""
*
*  @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWINDOWSNOTIFICATIONSMANAGER::DIOWINDOWSNOTIFICATIONSMANAGER()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWINDOWSNOTIFICATIONSMANAGER::~DIOWINDOWSNOTIFICATIONSMANAGER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWINDOWSNOTIFICATIONSMANAGER::~DIOWINDOWSNOTIFICATIONSMANAGER()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWINDOWSNOTIFICATIONSMANAGER::Ini(XCHAR* titleowner, XCHAR* pathexec, XCHAR* genericapp)
* @brief      Ini
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  titleowner :
* @param[in]  genericapp :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWINDOWSNOTIFICATIONSMANAGER::Ini(XCHAR* titleowner, XCHAR* genericapp)
{

  #if(_MSC_VER >= 1700) && defined(_USING_V110_SDK71_)


  #else

  Microsoft::WRL::Wrappers::RoInitializeWrapper winRTInitializer(RO_INIT_MULTITHREADED);

  HRESULT hr = winRTInitializer;
  if(FAILED(hr)) return false;

  std::wstring sModuleName;
  hr = ToastPP::CManager::GetExecutablePath(sModuleName);
  if(FAILED(hr))  return false;

  RegisterCOMServer(sModuleName.c_str());

  hr = ToastPP::CManager::RegisterForNotificationSupport(titleowner, sModuleName.c_str(), genericapp, __uuidof(CToastNotificationActivationCallback));
  if(FAILED(hr)) return false;

  hr = manager.Create(genericapp);
  if(FAILED(hr)) return false;

  RegisterActivator();

  #endif

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWINDOWSNOTIFICATIONSMANAGER::Do(DIOWINDOWSNOTIFICATION& notification)
* @brief      Do
* @ingroup    DATAIO
*
* @param[in]  notification :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWINDOWSNOTIFICATIONSMANAGER::Do(DIONOTIFICATION* notification)
{
  #if(_MSC_VER >= 1700) && defined(_USING_V110_SDK71_)

  ShowBaloon(notification->Get_Title()->Get(), notification->Get_Message()->Get(), (HWND)notification->GetWindowHandle(), (HICON)notification->GetApplicationIcon());

  #else


  XSTRING payload;

  payload += __L("<toast> <visual> <binding template=\"ToastGeneric\">");

  if(!notification->Get_Title()->IsEmpty())    payload.AddFormat(__L("<text>%s</text>"), notification->Get_Title()->Get());
  if(!notification->Get_Message()->IsEmpty())  payload.AddFormat(__L("<text>%s</text>"), notification->Get_Message()->Get());

  payload += __L("</binding></visual></toast>");





  HRESULT hr = toast.Create(payload.Get());
  if(FAILED(hr))
    {
      return false;
    }


  //Show the toast
  hr = manager.Show(toast, this);
  if(FAILED(hr))
    {
      return false;
    }

  #endif

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWINDOWSNOTIFICATIONSMANAGER::End()
* @brief      End
* @ingroup    PLATFORM_WINDOWS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWINDOWSNOTIFICATIONSMANAGER::End()
{
  #if(_MSC_VER >= 1700) && defined(_USING_V110_SDK71_)


  #else

  UnregisterActivator();
  UnRegisterCOMServer();

  manager.Detach();

  #endif

  return true;
}



#if(_MSC_VER >= 1700) && defined(_USING_V110_SDK71_)

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         BOOL DIOWINDOWSNOTIFICATIONSMANAGER::ShowBaloon(LPCTSTR title, LPCTSTR text, HWND hwnd, HICON hicon)
* @brief      ShowBaloon
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  title :
* @param[in]  text :
* @param[in]  hwnd :
* @param[in]  hicon :
*
* @return     BOOL :
*
* --------------------------------------------------------------------------------------------------------------------*/
BOOL DIOWINDOWSNOTIFICATIONSMANAGER::ShowBaloon(LPCTSTR title, LPCTSTR text, HWND hwnd, HICON hicon)
{
  NOTIFYICONDATA    nid     = {};
  static const GUID myguid  = { 0x23977b55, 0x10e0, 0x4041, { 0xb8, 0x62, 0xb1, 0x95, 0x41, 0x96, 0x36, 0x68 } };
  BOOL              result  = FALSE;

  ZeroMemory(&nid, sizeof(NOTIFYICONDATA));

  nid.cbSize            = sizeof(nid);
  nid.hWnd              = hwnd;
  nid.uVersion          = 4;
  nid.uID               = 1;
  nid.guidItem          = myguid;
  nid.hIcon             = hicon;
  nid.uFlags            = NIF_TIP | NIF_ICON | NIF_MESSAGE | NIF_INFO | 0x00000080;
  nid.uCallbackMessage  = WM_LBUTTONDOWN;

  wcscpy_s(nid.szInfo     , ARRAYSIZE(nid.szInfo)     , text);
  wcscpy_s(nid.szInfoTitle, ARRAYSIZE(nid.szInfoTitle), title);

  result = Shell_NotifyIcon(NIM_DELETE, &nid);

  result = Shell_NotifyIcon(NIM_ADD, &nid);

  return result;
}


#else

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         HRESULT DIOWINDOWSNOTIFICATIONSMANAGER::RegisterCOMServer(_In_z_ PCWSTR pszExePath)
* @brief      RegisterCOMServer
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  PCWSTR pszExePath :
*
* @return     HRESULT :
*
* --------------------------------------------------------------------------------------------------------------------*/
HRESULT  DIOWINDOWSNOTIFICATIONSMANAGER::RegisterCOMServer(_In_z_ PCWSTR pszExePath)
{
  //In this case, just register this application to start
  return HRESULT_FROM_WIN32(::RegSetKeyValueW(HKEY_CURRENT_USER, L"SOFTWARE\\Classes\\CLSID\\{383803B6-AFDA-4220-BFC3-0DBF810106BF}\\LocalServer32", nullptr, REG_SZ, pszExePath, static_cast<DWORD>(wcslen(pszExePath)*sizeof(wchar_t))));
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         HRESULT DIOWINDOWSNOTIFICATIONSMANAGER::UnRegisterCOMServer()
* @brief      UnRegisterCOMServer
* @ingroup    PLATFORM_WINDOWS
*
* @return     HRESULT :
*
* --------------------------------------------------------------------------------------------------------------------*/
HRESULT  DIOWINDOWSNOTIFICATIONSMANAGER::UnRegisterCOMServer()
{
  HRESULT hr = HRESULT_FROM_WIN32(::RegDeleteKey(HKEY_CURRENT_USER, _T("SOFTWARE\\Classes\\CLSID\\{383803B6-AFDA-4220-BFC3-0DBF810106BF}\\LocalServer32")));
  if(FAILED(hr)) return hr;

  return HRESULT_FROM_WIN32(::RegDeleteKey(HKEY_CURRENT_USER, _T("SOFTWARE\\Classes\\CLSID\\{383803B6-AFDA-4220-BFC3-0DBF810106BF}")));
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         HRESULT DIOWINDOWSNOTIFICATIONSMANAGER::RegisterActivator()
* @brief      RegisterActivator
* @ingroup    PLATFORM_WINDOWS
*
* @return     HRESULT :
*
* --------------------------------------------------------------------------------------------------------------------*/
HRESULT  DIOWINDOWSNOTIFICATIONSMANAGER::RegisterActivator()
{
  static bool iscreate = false;

  if(iscreate) 
    { 
      Microsoft::WRL::Module<Microsoft::WRL::OutOfProc>::Create([] {});
      iscreate = true;
    }

  Microsoft::WRL::Module<Microsoft::WRL::OutOfProc>::GetModule().IncrementObjectCount();

  return Microsoft::WRL::Module<Microsoft::WRL::OutOfProc>::GetModule().RegisterObjects();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWINDOWSNOTIFICATIONSMANAGER::UnregisterActivator()
* @brief      UnregisterActivator
* @ingroup    PLATFORM_WINDOWS
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void  DIOWINDOWSNOTIFICATIONSMANAGER::UnregisterActivator()
{
  //Microsoft::WRL::Module<Microsoft::WRL::OutOfProc>::GetModule().DecrementObjectCount();  
  //Microsoft::WRL::Module<Microsoft::WRL::OutOfProc>::GetModule().UnregisterObjects();  
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         HRESULT CToastNotificationActivationCallback::Activate(__RPC__in_string LPCWSTR appUserModelId, __RPC__in_opt_string LPCWSTR invokedArgs, __RPC__in_ecount_full_opt(count) const NOTIFICATION_USER_INPUT_TICKET* data, ULONG count)
* @brief      Activate
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  LPCWSTR appUserModelId :
* @param[in]  LPCWSTR invokedArgs :
* @param[in]  const NOTIFICATION_USER_INPUT_TICKET* data :
* @param[in]  count :
*
* @return     HRESULT :
*
* --------------------------------------------------------------------------------------------------------------------*/
HRESULT CToastNotificationActivationCallback::Activate(__RPC__in_string LPCWSTR appUserModelId, __RPC__in_opt_string LPCWSTR invokedArgs, __RPC__in_ecount_full_opt(count) const NOTIFICATION_USER_INPUT_TICKET* data, ULONG count)
{

  return S_OK;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWINDOWSNOTIFICATIONSMANAGER::ReportToastNotification(_In_z_ LPCTSTR pszDetails, _In_ BOOL bAppend)
* @brief      ReportToastNotification
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  LPCTSTR pszDetails :
* @param[in]  BOOL bAppend :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWINDOWSNOTIFICATIONSMANAGER::ReportToastNotification(_In_z_ LPCTSTR pszDetails, _In_ BOOL bAppend)
{

}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWINDOWSNOTIFICATIONSMANAGER::OnToastActivated(_In_opt_ ABI::Windows::UI::Notifications::IToastNotification* pSender, _In_opt_ IInspectable* pArgs)
* @brief      OnToastActivated
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  ABI::Windows::UI::Notifications::IToastNotification* pSender :
* @param[in]  IInspectable* pArgs :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWINDOWSNOTIFICATIONSMANAGER::OnToastActivated(_In_opt_ ABI::Windows::UI::Notifications::IToastNotification* pSender, _In_opt_ IInspectable* pArgs)
{

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWINDOWSNOTIFICATIONSMANAGER::OnToastDismissed(_In_opt_ ABI::Windows::UI::Notifications::IToastNotification* pSender, _In_ ABI::Windows::UI::Notifications::ToastDismissalReason reason)
* @brief      OnToastDismissed
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  ABI::Windows::UI::Notifications::IToastNotification* pSender :
* @param[in]  ABI::Windows::UI::Notifications::ToastDismissalReason reason :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWINDOWSNOTIFICATIONSMANAGER::OnToastDismissed(_In_opt_ ABI::Windows::UI::Notifications::IToastNotification* pSender, _In_ ABI::Windows::UI::Notifications::ToastDismissalReason reason)
{

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWINDOWSNOTIFICATIONSMANAGER::OnToastFailed(_In_opt_ ABI::Windows::UI::Notifications::IToastNotification* pSender, _In_ HRESULT errorCode)
* @brief      OnToastFailed
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  ABI::Windows::UI::Notifications::IToastNotification* pSender :
* @param[in]  HRESULT errorCode :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWINDOWSNOTIFICATIONSMANAGER::OnToastFailed(_In_opt_ ABI::Windows::UI::Notifications::IToastNotification* pSender, _In_ HRESULT errorCode)
{

}



#endif

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWINDOWSNOTIFICATIONSMANAGER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWINDOWSNOTIFICATIONSMANAGER::Clean()
{
  #if(_MSC_VER >= 1700) && defined(_USING_V110_SDK71_)

  #else


  #endif
}