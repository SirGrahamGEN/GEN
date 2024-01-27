/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOWINDOWSNotificationsManager.h
* 
* @class      DIOWINDOWSNOTIFICATIONSMANAGER
* @brief      WINDOWS Data Input/Output Notifications manager class
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

#ifndef _DIOWINDOWSNOTIFICATIONSMANAGER_H_
#define _DIOWINDOWSNOTIFICATIONSMANAGER_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#ifndef BUILDER
#if(_MSC_VER >= 1700) && defined(_USING_V110_SDK71_)

  #include <Windows.h>

#else

  #include <cstdio>
  #include <string>
  #include <vector>
  #include <new>

  #include <atlbase.h>
  #include <atlpath.h>
  #include <Shlobj.h>
  #include <propkey.h>
  #include <propvarutil.h>
  #include <wrl\event.h>
  #include <wrl.h>

  #include <wxdebug.h>

  #include <Toast++.h>

#endif
#endif

#include "XString.h"

#include "DIONotificationsManager.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

#if(_MSC_VER >= 1700) && defined(_USING_V110_SDK71_)


#else

typedef struct NOTIFICATION_USER_INPUT_TICKET
{
  LPCWSTR     Key;
  LPCWSTR     Value;

}  NOTIFICATION_USER_INPUT_TICKET;

#endif

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

#if(_MSC_VER >= 1700) && defined(_USING_V110_SDK71_)

class DIOWINDOWSNOTIFICATIONSMANAGER : public DIONOTIFICATIONSMANAGER
{
  public:
                                              DIOWINDOWSNOTIFICATIONSMANAGER          ();
    virtual                                  ~DIOWINDOWSNOTIFICATIONSMANAGER          ();

    bool                                      Ini                                     (XCHAR* titleowner, XCHAR* genericapp);
    bool                                      Do                                      (DIONOTIFICATION* notification);
    bool                                      End                                     ();

  private:

    BOOL                                      ShowBaloon                              (LPCTSTR title, LPCTSTR text, HWND hwnd, HICON hicon);

    void                                      Clean                                   ();

};

#else

MIDL_INTERFACE("53E31837-6600-4A81-9395-75CFFE746F94")
INotificationActivationCallback : public IUnknown
{
  public:

    virtual HRESULT STDMETHODCALLTYPE         Activate                                (__RPC__in_string LPCWSTR appUserModelId, __RPC__in_opt_string LPCWSTR invokedArgs,__RPC__in_ecount_full_opt(count) const NOTIFICATION_USER_INPUT_TICKET *data, ULONG count) = 0;
};



//The COM server which implements the callback notifcation from Action Center
class DECLSPEC_UUID("383803B6-AFDA-4220-BFC3-0DBF810106BF")
CToastNotificationActivationCallback : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::ClassicCom>, INotificationActivationCallback>
{
  public:
                                              //Constructors / Destructors
                                              CToastNotificationActivationCallback    ()
                                              {

                                              }

  virtual HRESULT STDMETHODCALLTYPE           Activate                                (__RPC__in_string LPCWSTR appUserModelId, __RPC__in_opt_string LPCWSTR invokedArgs, __RPC__in_ecount_full_opt(count) const NOTIFICATION_USER_INPUT_TICKET* data, ULONG count) override;
};



class DIOWINDOWSNOTIFICATIONSMANAGER : public DIONOTIFICATIONSMANAGER, public ToastPP::INotifier
{
  public:
                                              DIOWINDOWSNOTIFICATIONSMANAGER          ();
    virtual                                  ~DIOWINDOWSNOTIFICATIONSMANAGER          ();

    bool                                      Ini                                     (XCHAR* titleowner, XCHAR* genericapp) override;
    bool                                      Do                                      (DIONOTIFICATION* notification) override;
    bool                                      End                                     () override;

  private:


    HRESULT                                   RegisterCOMServer                       (_In_z_ PCWSTR pszExePath);
    HRESULT                                   UnRegisterCOMServer                     ();

    HRESULT                                   RegisterActivator                       ();
    void                                      UnregisterActivator                     ();

    void                                      ReportToastNotification                 (_In_z_ LPCTSTR pszDetails, _In_ BOOL bAppend);

    void                                      OnToastActivated                        (_In_opt_ ABI::Windows::UI::Notifications::IToastNotification* pSender, _In_opt_ IInspectable* pArgs) override;
    void                                      OnToastDismissed                        (_In_opt_ ABI::Windows::UI::Notifications::IToastNotification* pSender, _In_ ABI::Windows::UI::Notifications::ToastDismissalReason reason) override;
    void                                      OnToastFailed                           (_In_opt_ ABI::Windows::UI::Notifications::IToastNotification* pSender, _In_ HRESULT errorCode) override;

    void                                      Clean                                   ();

    ToastPP::CManager                         manager;
    ToastPP::CToast                           toast;
};

#endif

/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#if(_MSC_VER >= 1700) && defined(_USING_V110_SDK71_)


#else

CoCreatableClass(CToastNotificationActivationCallback);

#endif


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

