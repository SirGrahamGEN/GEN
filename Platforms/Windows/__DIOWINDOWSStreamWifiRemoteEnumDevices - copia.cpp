/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOWINDOWSStreamWifiRemoteEnumDevices.cpp
*
* @class      DIOWINDOWSSTREAMWIFIREMOTEENUMDEVICES
* @brief      Data Input/Output Stream WINDOWS Wi-Fi remote Enum Devices class
* @ingroup    PLATFORM_WINDOWS
*
* @copyright  GEN Group. All right reserved.
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


#if defined(DIO_ACTIVE) && defined(DIOWIFI_ACTIVE)

#pragma comment(lib, "wlanapi.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "Rpcrt4.lib")

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#include "XFactory.h"
#include "XTrace.h"
#include "XFileXML.h"

#include "DIOStream.h"
#include "DIOStreamDeviceWifi.h"

#include "DIOWINDOWSStreamWifiRemoteEnumDevices.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/

void    WLanCallback      (WLAN_NOTIFICATION_DATA *scannotificationdata, PVOID context);



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWINDOWSSTREAMWIFIREMOTEENUMDEVICES::DIOWINDOWSSTREAMWIFIREMOTEENUMDEVICES()
* @brief      Constructor
* @ingroup    PLATFORM_WINDOWS
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOWINDOWSSTREAMWIFIREMOTEENUMDEVICES::DIOWINDOWSSTREAMWIFIREMOTEENUMDEVICES() : DIOSTREAMWIFIREMOTEENUMDEVICES()
{
  Clean();

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWINDOWSSTREAMWIFIREMOTEENUMDEVICES::~DIOWINDOWSSTREAMWIFIREMOTEENUMDEVICES()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_WINDOWS
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOWINDOWSSTREAMWIFIREMOTEENUMDEVICES::~DIOWINDOWSSTREAMWIFIREMOTEENUMDEVICES()
{
  StopSearch(true);

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWINDOWSSTREAMWIFIREMOTEENUMDEVICES::Search()
* @brief      Search
* @ingroup    PLATFORM_WINDOWS
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
/*
bool DIOWINDOWSSTREAMWIFIREMOTEENUMDEVICES::Search()
{
  HANDLE                        handleclient      = NULL;
  DWORD                         max_client        = 2;
  DWORD                         current_version   = 0;
  DWORD                         result            = 0;
  DWORD                         returnval         = 0;
  WCHAR                         GUIDstring[39]    = { 0 };
  PWLAN_INTERFACE_INFO_LIST     interfacelist     = NULL;
  PWLAN_INTERFACE_INFO          interfacelinfo    = NULL;
  PWLAN_AVAILABLE_NETWORK_LIST  networklist       = NULL;
  PWLAN_AVAILABLE_NETWORK       networkentry      = NULL;
  XSTRING                       line;
  int                           RSSI              = 0;
  int                           ireturn           = 0;

  result = WlanOpenHandle(max_client, NULL, &current_version, &handleclient);
  if(result != ERROR_SUCCESS)
    {
      //XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Wi-Fi enum] WlanOpenHandle failed with error: %u"), result);
      return false;
    }

  result = WlanEnumInterfaces(handleclient, NULL, &interfacelist);
  if(result != ERROR_SUCCESS)
    {
      //XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Wi-Fi enum] WlanEnumInterfaces failed with error: %u"), result);
      return false;
    }

  //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Wi-Fi enum] Num Entries   : %lu"), interfacelist->dwNumberOfItems);
  //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Wi-Fi enum] Current Index : %lu"), interfacelist->dwIndex);

  for(int i = 0; i < (int) interfacelist->dwNumberOfItems; i++)
    {
      interfacelinfo = (WLAN_INTERFACE_INFO *) &interfacelist->InterfaceInfo[i];

      //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Wi-Fi enum] Interface Index[%u]:\t %lu"), i, i);

      ireturn = StringFromGUID2(interfacelinfo->InterfaceGuid, (LPOLESTR) &GUIDstring, sizeof(GUIDstring)/sizeof(*GUIDstring));

      // For c rather than C++ source code, the above line needs to be

      //if(ireturn == 0)
      //  {
      //    XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Wi-Fi enum] StringFromGUID2 failed"));
      //  }
      //else
      //  {
      //    XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Wi-Fi enum] InterfaceGUID[%d]: %s"), i, GUIDstring);
      // }

      //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Wi-Fi enum] Interface Description[%d]: %ws"), i, interfacelinfo->strInterfaceDescription);

      //switch (interfacelinfo->isState)
      //  {
      //    case wlan_interface_state_not_ready               : line = __L("Not ready");                                                      break;
      //    case wlan_interface_state_connected               : line = __L("Connected");                                                      break;
      //    case wlan_interface_state_ad_hoc_network_formed   : line = __L("First node in a ad hoc network");                                 break;
      //    case wlan_interface_state_disconnecting           : line = __L("Disconnecting");                                                  break;
      //    case wlan_interface_state_disconnected            : line = __L("Not connected");                                                  break;
      //    case wlan_interface_state_associating             : line = __L("Attempting to associate with a network");                         break;
      //    case wlan_interface_state_discovering             : line = __L("Auto configuration is discovering settings for the network");     break;
      //    case wlan_interface_state_authenticating          : line = __L("In process of authenticating");                                   break;
      //                                    default           : line.Format(__L("Unknown state %ld"), interfacelinfo->isState);               break;
      //  }

      //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Wi-Fi enum] Interface State[%d]: %s"), i, line.Get());

      result = WlanGetAvailableNetworkList(handleclient, &interfacelinfo->InterfaceGuid, 0, NULL, &networklist);

      if(result != ERROR_SUCCESS)
        {
          //XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Wi-Fi enum] WlanGetAvailableNetworkList failed with error: %u"), result);
          returnval = 1;
        }
       else
        {
          //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Wi-Fi enum] ------------------------------------------------------------"));
          //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Wi-Fi enum] WLAN_AVAILABLE_NETWORK_LIST for this interface"));
          //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Wi-Fi enum] Num Entries: %lu\n"), networklist->dwNumberOfItems);

          for(XDWORD j = 0; j < networklist->dwNumberOfItems; j++)
            {
              networkentry = (WLAN_AVAILABLE_NETWORK *)&networklist->Network[j];

              if(networkentry)
                {
                  DIOSTREAMDEVICEWIFI* wifidevice = new DIOSTREAMDEVICEWIFI();
                  if(wifidevice)
                    {
                      wifidevice->SetIndex(j);

                      //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Wi-Fi enum] Profile [%d] --------------------------------------------------"), j);
                      //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Wi-Fi enum] Profile Name                     : %s"), networkentry->strProfileName);

                      //------------------------------------------------------------------------------------------

                      line.Empty();
                      if(networkentry->dot11Ssid.uSSIDLength)
                        {
                          for(XDWORD k=0; k<networkentry->dot11Ssid.uSSIDLength; k++)
                            {
                              line += (XCHAR)networkentry->dot11Ssid.ucSSID[k];
                            }
                        }

                      wifidevice->GetName()->Set(line);

                      //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Wi-Fi enum] SSID                             : %s"), line.Get());

                      //------------------------------------------------------------------------------------------

                      //line.Empty();
                      //switch (networkentry->dot11BssType)
                      //  {
                      //    case dot11_BSS_type_infrastructure   : line.Format(__L("[Wi-Fi enum] Infrastructure (%u)"), networkentry->dot11BssType);   break;
                      //   case dot11_BSS_type_independent      : line.Format(__L("[Wi-Fi enum] Infrastructure (%u)"), networkentry->dot11BssType);   break;
                      //                              default    : line.Format(__L("Other (%lu)"), networkentry->dot11BssType);                        break;
                      //  }

                      //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Wi-Fi enum] BSS Network type                 : %s"), line.Get());

                      //------------------------------------------------------------------------------------------

                      //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Wi-Fi enum] Number of BSSIDs                 : %u"), networkentry->uNumberOfBssids);

                      //------------------------------------------------------------------------------------------

                      //line.Empty();

                      //if(networkentry->bNetworkConnectable)
                      //  {
                      //    line = __L("Yes");
                      //  }
                      // else
                      //  {
                      //    line.Format(__L("No. Not connectable WLAN_REASON_CODE value: %u"), networkentry->wlanNotConnectableReason);
                      //  }

                      //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Wi-Fi enum] Connectable                      : %s "), line.Get());


                      //------------------------------------------------------------------------------------------

                      //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Wi-Fi enum] Number of PHY types supported    : %u"), networkentry->uNumberOfPhyTypes);

                      //------------------------------------------------------------------------------------------

                      if(networkentry->wlanSignalQuality == 0)  RSSI = -100;
                            else if(networkentry->wlanSignalQuality == 100)  RSSI = -50;
                                    else RSSI = -100 + (networkentry->wlanSignalQuality/2);

                      wifidevice->SetTransmisionPower(RSSI);

                      //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Wi-Fi enum] Signal Quality                   : %u (RSSI: %i dBm)"), networkentry->wlanSignalQuality, RSSI);

                      //------------------------------------------------------------------------------------------

                      //if(networkentry->bSecurityEnabled)
                      //  {
                      //    line = __L("Yes");
                      //  }
                      // else
                      //  {
                      //    line =  __L("No");
                      //  }

                      //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Wi-Fi enum] Security Enabled                 : %s"), line.Get());


                      wifidevice->SetHasSecurity(networkentry->bSecurityEnabled?true:false);

                      //------------------------------------------------------------------------------------------

                      //switch (networkentry->dot11DefaultAuthAlgorithm)
                      //  {
                      //    case DOT11_AUTH_ALGO_80211_OPEN         : line.Format(__L("802.11 Open (%u)"), networkentry->dot11DefaultAuthAlgorithm);       break;
                      //    case DOT11_AUTH_ALGO_80211_SHARED_KEY   : line.Format(__L("802.11 Shared (%u)"), networkentry->dot11DefaultAuthAlgorithm);     break;
                      //    case DOT11_AUTH_ALGO_WPA                : line.Format(__L("WPA (%u)"), networkentry->dot11DefaultAuthAlgorithm);               break;
                      //    case DOT11_AUTH_ALGO_WPA_PSK            : line.Format(__L("WPA-PSK (%u)"), networkentry->dot11DefaultAuthAlgorithm);           break;
                      //    case DOT11_AUTH_ALGO_WPA_NONE           : line.Format(__L("WPA-None (%u)"), networkentry->dot11DefaultAuthAlgorithm);          break;
                      //    case DOT11_AUTH_ALGO_RSNA               : line.Format(__L("RSNA (%u)"), networkentry->dot11DefaultAuthAlgorithm);              break;
                      //    case DOT11_AUTH_ALGO_RSNA_PSK           : line.Format(__L("RSNA with PSK(%u)"), networkentry->dot11DefaultAuthAlgorithm);      break;
                      //                              default       : line.Format(__L("Other (%lu)"), networkentry->dot11DefaultAuthAlgorithm);            break;
                      //  }

                      //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Wi-Fi enum] Default AuthAlgorithm            : %s"), line.Get());

                      //------------------------------------------------------------------------------------------

                      //switch (networkentry->dot11DefaultCipherAlgorithm)
                      //  {
                      //    case DOT11_CIPHER_ALGO_NONE             : line.Format(__L("None (0x%x)"), networkentry->dot11DefaultCipherAlgorithm);      break;
                      //    case DOT11_CIPHER_ALGO_WEP40            : line.Format(__L("WEP-40 (0x%x)"), networkentry->dot11DefaultCipherAlgorithm);    break;
                      //    case DOT11_CIPHER_ALGO_TKIP             : line.Format(__L("TKIP (0x%x)"), networkentry->dot11DefaultCipherAlgorithm);      break;
                      //    case DOT11_CIPHER_ALGO_CCMP             : line.Format(__L("CCMP (0x%x)"), networkentry->dot11DefaultCipherAlgorithm);      break;
                      //    case DOT11_CIPHER_ALGO_WEP104           : line.Format(__L("WEP-104 (0x%x)"), networkentry->dot11DefaultCipherAlgorithm);   break;
                      //    case DOT11_CIPHER_ALGO_WEP              : line.Format(__L("WEP (0x%x)"), networkentry->dot11DefaultCipherAlgorithm);       break;
                      //                          default           : line.Format(__L("Other (0x%x)"), networkentry->dot11DefaultCipherAlgorithm);     break;
                      //  }

                      //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Wi-Fi enum] Default CipherAlgorithm          : %s"), line.Get());

                      //------------------------------------------------------------------------------------------

                      //line.Empty();

                      //if(networkentry->dwFlags)
                      //  {
                      //    if (networkentry->dwFlags & WLAN_AVAILABLE_NETWORK_CONNECTED)    line += __L(" - Currently connected");
                      //    if (networkentry->dwFlags & WLAN_AVAILABLE_NETWORK_HAS_PROFILE)  line += __L(" - Has profile");
                      //  }

                      //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Wi-Fi enum] Flags                            : 0x%x %s"), networkentry->dwFlags, line.Get());

                      //------------------------------------------------------------------------------------------

                      AddDevice(wifidevice);

                    }
                }
            }
        }
    }

  if(networklist != NULL)
    {
      WlanFreeMemory(networklist);
      networklist = NULL;
    }

  if(interfacelist != NULL)
    {
      WlanFreeMemory(interfacelist);
      interfacelist = NULL;
    }

  return returnval;
}
*/


bool DIOWINDOWSSTREAMWIFIREMOTEENUMDEVICES::Search()
{
  HANDLE                        handleclient      = NULL;
  DWORD                         max_client        = 2;
  DWORD                         current_version   = 0;
  DWORD                         result            = 0;
  DWORD                         returnval         = 0;
  WCHAR                         GUIDstring[39]    = { 0 };
  PWLAN_INTERFACE_INFO_LIST     interfacelist     = NULL;
  PWLAN_INTERFACE_INFO          interfacelinfo    = NULL;
  PWLAN_AVAILABLE_NETWORK_LIST  networklist       = NULL;
  PWLAN_AVAILABLE_NETWORK       networkentry      = NULL;
  PWLAN_BSS_LIST                bsslist           = NULL;
  PWLAN_BSS_ENTRY               bssentry          = NULL;
  int                           ireturn           = 0;
  bool                          status            = false;

  result = WlanOpenHandle(max_client, NULL, &current_version, &handleclient);
  if(result != ERROR_SUCCESS)
    {
      return false;
    }

  result = WlanEnumInterfaces(handleclient, NULL, &interfacelist);
  if(result != ERROR_SUCCESS)
    {
      return false;
    }

  for(int i = 0; i < (int)interfacelist->dwNumberOfItems; i++)
    {
      interfacelinfo = (WLAN_INTERFACE_INFO *) &interfacelist->InterfaceInfo[i];

      ireturn = StringFromGUID2(interfacelinfo->InterfaceGuid, (LPOLESTR) &GUIDstring, sizeof(GUIDstring)/sizeof(*GUIDstring));

      /*
      // Scan the connected SSID

      result = WlanScan(handleclient, &interfacelinfo->InterfaceGuid, NULL, NULL, NULL);
      if(result != ERROR_SUCCESS)
        {
          return false;
        }
      
      result = WlanGetAvailableNetworkList(handleclient, &interfacelinfo->InterfaceGuid, WLAN_AVAILABLE_NETWORK_INCLUDE_ALL_ADHOC_PROFILES | WLAN_AVAILABLE_NETWORK_INCLUDE_ALL_MANUAL_HIDDEN_PROFILES, NULL, &networklist);
      */

      
      WLAN_CALLBACK_INFO callbackinfo = { 0 };                      //Declare the callback parameter struct

      callbackinfo.interfaceGUID = interfacelist->InterfaceInfo[i].InterfaceGuid;
      callbackinfo.scanevent     = CreateEvent( NULL, FALSE, FALSE, NULL);      //Create an event to be triggered in the scan case
      
      WlanRegisterNotification(handleclient, WLAN_NOTIFICATION_SOURCE_ALL, TRUE, (WLAN_NOTIFICATION_CALLBACK)WLanCallback, (PVOID)&callbackinfo, NULL, NULL);  //Register for wlan scan notifications

      result = WlanScan(handleclient, &(interfacelist->InterfaceInfo[i].InterfaceGuid), NULL, NULL, NULL);  //Start a scan. If the WlanScan call fails, log the error
      if(result != ERROR_SUCCESS) 
        {
          return false;
        }
      
      DWORD waitresult = WaitForSingleObject(callbackinfo.scanevent, 20000); //Wait for the event to be signaled, or an error to occur. Don't wait longer than 15 seconds.

      //Check how we got here, via callback or timeout
      if(waitresult == WAIT_OBJECT_0)
        {          
          if(callbackinfo.callbackreason == wlan_notification_acm_scan_complete)
            {

            }
           else
            {
              if(callbackinfo.callbackreason == wlan_notification_acm_scan_fail)
                {
                   int a=0;
                   a++;
                }
            }
        }
       else
        {
          if(waitresult == WAIT_TIMEOUT)
            {

            }           
        }

      CloseHandle(callbackinfo.scanevent);


      // Get the BSS Entry
      result = WlanGetNetworkBssList(handleclient, &interfacelinfo->InterfaceGuid, NULL, dot11_BSS_type_any, TRUE, NULL, &bsslist);
      if(result != ERROR_SUCCESS)
        {
          status = false;
          break;
        }

      for(XDWORD j = 0; j<bsslist->dwNumberOfItems; j++)
        {
          bssentry = (WLAN_BSS_ENTRY*)&bsslist->wlanBssEntries[j];
          if(bssentry)
            {
              DIOSTREAMDEVICEWIFI* wifidevice = new DIOSTREAMDEVICEWIFI();
              if(wifidevice)
                {
                  XSTRING name;
                  for(ULONG a=0; a<bsslist->wlanBssEntries[j].dot11Ssid.uSSIDLength; a++)
                    {
                      name.Add((XCHAR)btowc(bsslist->wlanBssEntries[j].dot11Ssid.ucSSID[a]));
                    }

                  wifidevice->SetIndex(j);

                  //------------------------------------------------------------------------------------------

                  wifidevice->GetName()->Set(name);
                  wifidevice->GetMAC()->Set((XBYTE*)bsslist->wlanBssEntries[j].dot11Bssid);

                  //wifidevice->SetHasSecurity(bsslist->wlanBssEntries[j].bSecurityEnabled?true:false);
                  wifidevice->SetTransmisionPower((int)bsslist->wlanBssEntries[j].lRssi);

                  //------------------------------------------------------------------------------------------

                  AddDevice(wifidevice);

                }
            }
        }


    }

  if(bsslist != NULL)
    {
      WlanFreeMemory(bsslist);
      bsslist = NULL;
    }

  if(interfacelist != NULL)
    {
      WlanFreeMemory(interfacelist);
      interfacelist = NULL;
    }

  if(handleclient)
    {
      WlanCloseHandle(handleclient, NULL);
      handleclient = NULL;
    }

  return status;
}





/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWINDOWSSTREAMWIFIREMOTEENUMDEVICES::SetAllConnectionInAutomaticMode(bool automaticmodeactive)
* @brief      SetAllConnectionInAutomaticMode
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  automaticmodeactive : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOWINDOWSSTREAMWIFIREMOTEENUMDEVICES::SetAllConnectionInAutomaticMode(bool automaticmodeactive)
{
  HANDLE                        handleclient      = NULL;
  DWORD                         max_client        = 2;
  DWORD                         current_version   = 0;
  DWORD                         result            = 0;
  DWORD                         returnval         = 0;
  WCHAR                         GUIDstring[39]    = { 0 };
  PWLAN_INTERFACE_INFO_LIST     interfacelist     = NULL;
  PWLAN_INTERFACE_INFO          interfacelinfo    = NULL;
  PWLAN_PROFILE_INFO_LIST       profilelist       = NULL;
  PWLAN_PROFILE_INFO            profileinfo       = NULL;
  XSTRING                       line;
  int                           RSSI              = 0;
  int                           ireturn           = 0;

  result = WlanOpenHandle(max_client, NULL, &current_version, &handleclient);
  if(result != ERROR_SUCCESS) return false;

  result = WlanEnumInterfaces(handleclient, NULL, &interfacelist);
  if(result != ERROR_SUCCESS) return false;

  for(int i = 0; i < (int) interfacelist->dwNumberOfItems; i++)
    {
      interfacelinfo = (WLAN_INTERFACE_INFO *) &interfacelist->InterfaceInfo[i];

      ireturn = StringFromGUID2(interfacelinfo->InterfaceGuid, (LPOLESTR) &GUIDstring, sizeof(GUIDstring)/sizeof(*GUIDstring));

      result = WlanGetProfileList(handleclient, &interfacelinfo->InterfaceGuid, NULL, &profilelist);
      if(result != ERROR_SUCCESS)
        {
          returnval = 1;
        }
       else
        {
          for(XDWORD j=0; j<profilelist->dwNumberOfItems; j++)
            {
              profileinfo = (WLAN_PROFILE_INFO*)&profilelist->ProfileInfo[j];

              XFILEXML          filexml;
              XSTRING           profileXML;
              LPWSTR            originalprofileXML = NULL;
              DWORD             flags              = 0;
              DWORD             grantedaccess      = 0;
              WLAN_REASON_CODE  wlanreason         = 0;
              int               index   = 0;
              XSTRING           nameelement;

              result = WlanGetProfile(handleclient , &(interfacelist->InterfaceInfo[0].InterfaceGuid)
                                                   , profileinfo->strProfileName
                                                   , NULL
                                                   , &originalprofileXML
                                                   , &flags
                                                   , &grantedaccess);

              profileXML =  originalprofileXML;

              filexml.AddLine(profileXML);
              filexml.DecodeAllLines();

              nameelement = __L("connectionMode");
              XFILEXMLELEMENT* element = filexml.SearchElement(nameelement, index, NULL);
              if(element)
                {
                  element->SetValue(automaticmodeactive?__L("auto"):__L("manual"));
                }

              filexml.EncodeAllLines(false);
              profileXML.Empty();
              filexml.GetAllInOneLine(profileXML);

              result = WlanSetProfile(handleclient , &(interfacelist->InterfaceInfo[0].InterfaceGuid)
                                                   , 0
                                                   , profileXML.Get()
                                                   , NULL
                                                   , TRUE
                                                   , NULL
                                                   , &wlanreason);


            }
        }
    }

  if(profilelist != NULL)
    {
      WlanFreeMemory(profilelist);
      profilelist = NULL;
    }

  if(interfacelist != NULL)
    {
      WlanFreeMemory(interfacelist);
      interfacelist = NULL;
    }

  WlanCloseHandle(handleclient, NULL);

  return result?false:true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWINDOWSSTREAMWIFIREMOTEENUMDEVICES::SetAllConnectionStatus(bool activate)
* @brief      SetAllConnectionStatus
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  activate : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOWINDOWSSTREAMWIFIREMOTEENUMDEVICES::SetAllConnectionStatus(bool activate)
{
  HANDLE                      handleclient        = NULL;
  DWORD                       max_client          = 2;
  DWORD                       current_version     = 0;
  DWORD                       result              = 0;  
  PWLAN_INTERFACE_INFO_LIST   interfacelist       = NULL;
  PWLAN_INTERFACE_INFO        interfacelinfo      = NULL;  
  PWLAN_INTERFACE_CAPABILITY  interfacecapability = NULL;
  
  result = WlanOpenHandle(max_client, NULL, &current_version, &handleclient);
  if(result != ERROR_SUCCESS) return false;

  result = WlanEnumInterfaces(handleclient, NULL, &interfacelist);
  if(result != ERROR_SUCCESS) return false;


  for(DWORD c=0; c<interfacelist->dwNumberOfItems; c++)
    {
      bool needactivated = false;

      interfacelinfo = (WLAN_INTERFACE_INFO*)&interfacelist->InterfaceInfo[c];
      
      switch(interfacelinfo->isState) 
        {
          case wlan_interface_state_not_ready             : break;  // Not ready

          case wlan_interface_state_connected             : break;  // Connected

          case wlan_interface_state_ad_hoc_network_formed : break;  // First node in a ad hoc network            

          case wlan_interface_state_disconnecting         : break;  // Disconnecting

          case wlan_interface_state_disconnected          : needactivated = true;
                                                            break;  // Not connected                

          case wlan_interface_state_associating           : break;  // Attempting to associate with a network

          case wlan_interface_state_discovering           : break;  // Auto configuration is discovering settings for the network

          case wlan_interface_state_authenticating        : break;  // In process of authenticating

                                          default         : break;  // Unknown state 
        }

      if(needactivated)
        {
          // get interface capability, which includes the supported PHYs   
          result = WlanGetInterfaceCapability(handleclient, &interfacelinfo->InterfaceGuid, NULL, &interfacecapability);
          if(result == ERROR_SUCCESS)
            {                
              // set radio state on every PHY   
              for(DWORD d=0; d<interfacecapability->dwNumberOfSupportedPhys; d++)
                {
                  WLAN_PHY_RADIO_STATE  wlanphyradiostate;
                  
                  // set radio state on every PHY   
                  wlanphyradiostate.dwPhyIndex = d;

                  if(activate)    
                    {
                      wlanphyradiostate.dot11SoftwareRadioState = dot11_radio_state_on;    
                      wlanphyradiostate.dot11HardwareRadioState = dot11_radio_state_on;    
                    }                                    
                   else 
                    {
                      wlanphyradiostate.dot11SoftwareRadioState = dot11_radio_state_off;
                      wlanphyradiostate.dot11HardwareRadioState = dot11_radio_state_off;
                    }    

                  PVOID pdata = &wlanphyradiostate;
    
                  result = WlanSetInterface(handleclient, &interfacelinfo->InterfaceGuid, wlan_intf_opcode_radio_state, sizeof(WLAN_PHY_RADIO_STATE), pdata, NULL);
                  if(result == ERROR_SUCCESS)
                    {
                      //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Wifi Activated.")); 
                    }
                   else
                    {
                      //XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("Wifi Activate Error!")); 
                    }    
                }
            }         
        }
    }
  
  if(interfacelist != NULL)
    {
      WlanFreeMemory(interfacelist);
      interfacelist = NULL;
    }

  WlanCloseHandle(handleclient, NULL);

  return result?false:true;
}







/*

// open a WLAN client handle and check version   
DWORD OpenHandleAndCheckVersion(PHANDLE phClient)
{
  DWORD   dwError = ERROR_SUCCESS;
  DWORD   dwServiceVersion;
  HANDLE  hClient = NULL;

  __try
  {
    *phClient = NULL;

    // open a handle to the service   
    if ((dwError = WlanOpenHandle(WLAN_API_VERSION,
      NULL,               // reserved   
      &dwServiceVersion,
      &hClient)) != ERROR_SUCCESS)
    {
      __leave;
    }

    // check service version   
    if (WLAN_API_VERSION_MAJOR(dwServiceVersion) < WLAN_API_VERSION_MAJOR(WLAN_API_VERSION_2_0))
    {
      // No-op, because the version check is for demonstration purpose only.   
      // You can add your own logic here.   
    }

    *phClient = hClient;

    // set hClient to NULL so it will not be closed   
    hClient = NULL;
  }
  __finally
  {
    if (hClient != NULL)
    {
      // clean up   
      WlanCloseHandle(hClient, NULL);           // reserved   

    }
  }

  return dwError;
}

*/





/*


VOID SetRadioState(__in int argc, __in_ecount(argc) LPWSTR argv[])
{
  DWORD dwError = ERROR_SUCCESS;
  HANDLE hClient = NULL;
  GUID guidIntf;
  PWLAN_INTERFACE_CAPABILITY pInterfaceCapability = NULL;
  DWORD i;
  WLAN_PHY_RADIO_STATE wlanPhyRadioState;

  __try
  {
    if (argc != 3)
    {
      dwError = ERROR_INVALID_PARAMETER;
      __leave;
    }

    if (_wcsicmp(argv[2], L"on") == 0)
    {
      wlanPhyRadioState.dot11SoftwareRadioState = dot11_radio_state_on;
    }
    else if (_wcsicmp(argv[2], L"off") == 0)
    {
      wlanPhyRadioState.dot11SoftwareRadioState = dot11_radio_state_off;
    }
    else
    {
      dwError = ERROR_INVALID_PARAMETER;
      __leave;
    }

    // get the interface GUID   
    if (UuidFromString((RPC_WSTR)argv[1], &guidIntf) != RPC_S_OK)
    {
      //wcerr << L"Invalid GUID " << argv[1] << endl;
      dwError = ERROR_INVALID_PARAMETER;
      __leave;
    }

    // open handle   
    if ((dwError = OpenHandleAndCheckVersion(
      &hClient
    )) != ERROR_SUCCESS)
    {
      __leave;
    }

    // get interface capability, which includes the supported PHYs   
    if ((dwError = WlanGetInterfaceCapability(
      hClient,
      &guidIntf,
      NULL,                       // reserved   
      &pInterfaceCapability
    )) != ERROR_SUCCESS)
    {
      __leave;
    }

    // set radio state on every PHY   
    for (i = 0; i < pInterfaceCapability->dwNumberOfSupportedPhys; i++)
    {
      // set radio state on every PHY   
      wlanPhyRadioState.dwPhyIndex = i;

      if ((dwError = WlanSetInterface(
        hClient,
        &guidIntf,
        wlan_intf_opcode_radio_state,
        sizeof(wlanPhyRadioState),
        (PBYTE)&wlanPhyRadioState,
        NULL                        // reserved   
      )) != ERROR_SUCCESS)
      {
        // rollback is nice to have, but not required   
        __leave;
      }
    }

  }
  __finally
  {
    // clean up   
    if (hClient != NULL)
    {
      WlanCloseHandle(
        hClient,
        NULL            // reserved   
      );
    }

    if (pInterfaceCapability != NULL)
    {
      WlanFreeMemory(pInterfaceCapability);
    }
  }

  // PrintErrorMsg(argv[0], dwError);
}

*/











/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWINDOWSSTREAMWIFIREMOTEENUMDEVICES::StopSearch(bool waitend)
* @brief      StopSearch
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  waitend :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOWINDOWSSTREAMWIFIREMOTEENUMDEVICES::StopSearch(bool waitend)
{
  if(!IsSearching()) return false;


  return true;
};




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWINDOWSSTREAMWIFIREMOTEENUMDEVICES::IsSearching()
* @brief      IsSearching
* @ingroup    PLATFORM_WINDOWS
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOWINDOWSSTREAMWIFIREMOTEENUMDEVICES::IsSearching()
{
  return issearching;
}





/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWINDOWSSTREAMWIFIREMOTEENUMDEVICES::TriggerScan(HANDLE wlanhandle, WLAN_INTERFACE_INFO_LIST* interfaces)
* @brief      TriggerScan
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  wlanhandle :
* @param[in]  interfaces :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOWINDOWSSTREAMWIFIREMOTEENUMDEVICES::TriggerScan(HANDLE wlanhandle, WLAN_INTERFACE_INFO_LIST* interfaces)
{

  for(ULONG i=0; i<interfaces->dwNumberOfItems; i++)
    {
      //Declare the callback parameter struct
      WLAN_CALLBACK_INFO callbackinfo = { 0 };

      callbackinfo.interfaceGUID = interfaces->InterfaceInfo[i].InterfaceGuid;

      //Create an event to be triggered in the scan case
      callbackinfo.scanevent = CreateEvent( NULL, FALSE, FALSE, NULL);


      //Register for wlan scan notifications
      WlanRegisterNotification(wlanhandle, WLAN_NOTIFICATION_SOURCE_ALL, TRUE, (WLAN_NOTIFICATION_CALLBACK)WLanCallback, (PVOID)&callbackinfo, NULL, NULL);

      //Start a scan. If the WlanScan call fails, log the error
      WlanScan(wlanhandle, &(interfaces->InterfaceInfo[i].InterfaceGuid), NULL, NULL, NULL);
      if(GetLastError() != ERROR_SUCCESS)
        {
          continue;
        }

      //Wait for the event to be signaled, or an error to occur. Don't wait longer than 15 seconds.
      DWORD waitresult = WaitForSingleObject(callbackinfo.scanevent, 15000);

      //Check how we got here, via callback or timeout
      if(waitresult == WAIT_OBJECT_0)
        {
          if(callbackinfo.callbackreason == wlan_notification_acm_scan_complete)
            {

            }
           else
            {
              if(callbackinfo.callbackreason == wlan_notification_acm_scan_fail)
                {

                }
            }
        }
       else
        {
          if(waitresult == WAIT_TIMEOUT)
            {

            }
           else
            {

            }
        }
    }
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void WLanCallback(WLAN_NOTIFICATION_DATA*scannotificationdata, PVOID context)
* @brief      LanCallback
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  WLAN_NOTIFICATION_DATA*scannotificationdata :
* @param[in]  context :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void WLanCallback(WLAN_NOTIFICATION_DATA *scannotificationdata, PVOID context)
{
  // Get the data from my struct. If it's null, nothing to do
  WLAN_CALLBACK_INFO* callbackinfo = (WLAN_CALLBACK_INFO*)context;
  if(!callbackinfo)
    {
      return;
    }

  // Check the GUID in the struct against the GUID in the notification data, return if they don't match
  if(memcmp(&callbackinfo->interfaceGUID, &scannotificationdata->InterfaceGuid, sizeof(GUID)) != 0)
    {
      return;
    }

  // If the notification was for a scan complete or failure then we need to set the event
  if((scannotificationdata->NotificationCode == wlan_notification_acm_scan_complete) || (scannotificationdata->NotificationCode == wlan_notification_acm_scan_fail))
    {
      //Set the notification code as the callbackReason
      callbackinfo->callbackreason = scannotificationdata->NotificationCode;

      //Set the event
      SetEvent(callbackinfo->scanevent);
    }

  return;
}





/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWINDOWSSTREAMWIFIREMOTEENUMDEVICES::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_WINDOWS
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOWINDOWSSTREAMWIFIREMOTEENUMDEVICES::Clean()
{
  issearching = false;
}






#endif