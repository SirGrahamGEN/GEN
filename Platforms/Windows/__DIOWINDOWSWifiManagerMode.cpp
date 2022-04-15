/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOWINDOWSWifiManagerMode.cpp
*
* @class      DIOWINDOWSWIFIMANAGERMODE
* @brief      Data Input/Output WINDOWS Wifi Manager Mode
* @ingroup    DATAIO
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


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <windows.h>

#include <wlanapi.h>
#include <Winbase.h>
#include <Commctrl.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>

#include <iostream>
#include <string>
#include <tchar.h>
#include <process.h>
#include <tlhelp32.h>

#include <wtsapi32.h>
#include <userenv.h>

#include "XFileXML.h"
#include "XTrace.h"

#include "DIOWINDOWSWifiManagerMode.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWINDOWSWIFIMANAGERMODE::DIOWINDOWSWIFIMANAGERMODE()
* @brief      Constructor
* @ingroup    DATAIO
*
* @return     Does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOWINDOWSWIFIMANAGERMODE::DIOWINDOWSWIFIMANAGERMODE()    
{ 
  Clean();                            
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWINDOWSWIFIMANAGERMODE::~DIOWINDOWSWIFIMANAGERMODE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @return     Does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOWINDOWSWIFIMANAGERMODE::~DIOWINDOWSWIFIMANAGERMODE()    
{ 
  Clean();                            
}




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOWINDOWSWIFIMANAGERMODE::SetMode_Client(XCHAR* SSID, XCHAR* password, bool serialize)
* @brief      SetMode_Client
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  SSID : 
* @param[in]  password : 
* @param[in]  serialize : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOWINDOWSWIFIMANAGERMODE::SetMode_Client(XCHAR* SSID, XCHAR* password, bool serialize)
{
  HANDLE                        handleclient      = NULL;
  DWORD                         max_client        = 2;
  DWORD                         current_version   = 0;
  int                           ireturn           = 0; 
  WCHAR                         GUIDstring[39]    = { 0 };
  PWLAN_INTERFACE_INFO_LIST     interfacelist     = NULL;
  PWLAN_INTERFACE_INFO          interfaceinfo     = NULL;
  XSTRING                       profilename; 
  DWORD                         result            = 1;
  
  if(!SSID)  return false;

  profilename = SSID;
  
  result = WlanOpenHandle(max_client, NULL, &current_version, &handleclient);
  if(result != ERROR_SUCCESS) return false;

  result = WlanEnumInterfaces(handleclient, NULL, &interfacelist);
  if(result != ERROR_SUCCESS) return false;

  for(int i = 0; i < (int) interfacelist->dwNumberOfItems; i++)
    {
      interfaceinfo = (WLAN_INTERFACE_INFO *) &interfacelist->InterfaceInfo[i];
      
      bool isdisconnected =  false;

      switch(interfaceinfo->isState) 
        {
          case wlan_interface_state_not_ready             : break;  // Not ready

          case wlan_interface_state_connected             : break;  // Connected

          case wlan_interface_state_ad_hoc_network_formed : break;  // First node in a ad hoc network            

          case wlan_interface_state_disconnecting         : break;  // Disconnecting

          case wlan_interface_state_disconnected          : isdisconnected =  true;
                                                            break;  // Not connected                

          case wlan_interface_state_associating           : break;  // Attempting to associate with a network

          case wlan_interface_state_discovering           : break;  // Auto configuration is discovering settings for the network

          case wlan_interface_state_authenticating        : break;  // In process of authenticating

                                          default         : break;  // Unknown state 
        }
      

      ireturn = StringFromGUID2(interfaceinfo->InterfaceGuid, (LPOLESTR) &GUIDstring, sizeof(GUIDstring)/sizeof(*GUIDstring));

      /*
      WLAN_CONNECTION_PARAMETERS wlanconnparams; 
      
      wlanconnparams.wlanConnectionMode   = wlan_connection_mode_profile ;        //YES,WE CONNECT AP VIA THE PROFILE 
      wlanconnparams.strProfile           = pProfileName;                        // set the profile name 
      wlanconnparams.pDot11Ssid           = NULL;         // SET SSID NULL 
      wlanconnparams.dot11BssType         = dot11_BSS_type_infrastructure;  //dot11_BSS_type_any,I do not need it this time.   
      wlanconnparams.pDesiredBssidList    = NULL;       // the desired BSSID list is empty 
      wlanconnparams.dwFlags              = WLAN_CONNECTION_HIDDEN_NETWORK;   //it works on my WIN7\8 

      result =  WlanConnect(handleclient, &interfacelinfo->InterfaceGuid, &wlanconnparams, NULL);
      if(result == ERROR_SUCCESS) break;
      */


     
      result = WlanDisconnect(handleclient, &interfaceinfo->InterfaceGuid, NULL); // disconnect first 
      if(result != ERROR_SUCCESS) 
        { 
          printf("WlanDisconnect failed with error: %u\n",result); 
          return -1; 
        } 

      /*
      PWLAN_AVAILABLE_NETWORK_LIST wlan_available_network_list = NULL; 
      result = WlanGetAvailableNetworkList(handleclient, &interfaceinfo->InterfaceGuid, WLAN_AVAILABLE_NETWORK_INCLUDE_ALL_MANUAL_HIDDEN_PROFILES, NULL, &wlan_available_network_list); 
      if(result == ERROR_SUCCESS) 
        { 
          for(DWORD c=0; c<wlan_available_network_list->dwNumberOfItems; c++)
            {  
              WLAN_AVAILABLE_NETWORK wlanAN = wlan_available_network_list->Network[0];//PLEASE CHECK THIS YOURSELF 
              if(!profilename.Compare(wlanAN.strProfileName, false))  
                {      
      */
                  WLAN_CONNECTION_PARAMETERS wlanconnpara; 
                  DOT11_SSID                 dot11_ssid;

                  XSTRING_CREATEOEM(profilename, SSIDchar)
                  memcpy(dot11_ssid.ucSSID, SSIDchar, profilename.GetSize()); 
                  dot11_ssid.uSSIDLength = profilename.GetSize();
                  XSTRING_DELETEOEM(profilename, SSIDchar)
           
                  wlanconnpara.wlanConnectionMode = wlan_connection_mode_discovery_unsecure;    // YES,WE CONNECT AP VIA THE PROFILE 
                  wlanconnpara.strProfile         = NULL;                                      // set the profile name 
                  wlanconnpara.pDot11Ssid         = &dot11_ssid;                               // SET SSID NULL 
                  wlanconnpara.dot11BssType       = dot11_BSS_type_infrastructure;             // dot11_BSS_type_any,I do not need it this time.   
                  wlanconnpara.pDesiredBssidList  = NULL;                                      // the desired BSSID list is empty 
                  wlanconnpara.dwFlags            = WLAN_CONNECTION_HIDDEN_NETWORK;            // it works on my WIN7\8 
 
                  result = WlanConnect(handleclient, &interfaceinfo->InterfaceGuid, &wlanconnpara ,NULL); 
                  if(result==ERROR_SUCCESS) 
                    { 
                      printf("WlanConnect success!\n"); 
                      break;
                    } 
                   else 
                    { 
                      printf("WlanConnect failed err is %d\n",result); 
                    } 

      /*
                }
            }
        }
      */
    }

  if(interfacelist != NULL)
    {
      WlanFreeMemory(interfacelist);
      interfacelist = NULL;
    }

  WlanCloseHandle(handleclient, NULL);

  return (result==ERROR_SUCCESS)?true:false;
}




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOWINDOWSWIFIMANAGERMODE::ChangePassordProfile(XSTRING& wifiprofile, XCHAR* password)
* @brief      ChangePassordProfile
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  wifiprofile : 
* @param[in]  password : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOWINDOWSWIFIMANAGERMODE::ChangePassordProfile(XSTRING& wifiprofile, XCHAR* password)
{
  XFILEXML filexml;

  filexml.SetFormatChar(XFILETXTFORMATCHAR_ASCII);

  filexml.AddLine(wifiprofile);
  if(!filexml.DecodeAllLines()) return false;
   
  int index = 0;

  XFILEXMLELEMENT* element = filexml.SearchElement(__L("sharedKey"), index);
  if(!element) return false;

  int nelements = element->GetNElements();    
  for(int c=0; c<nelements; c++)
    {
      element->DeleteElement(0);
    }
      
  element->AddElement(__L("keyType")      , __L("passPhrase"));
  element->AddElement(__L("protected")    , __L("false"));
  element->AddElement(__L("keyMaterial")  , password);
  
  if(!filexml.EncodeAllLines(false)) return false;
    
  filexml.GetAllInOneLine(wifiprofile);
    
  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWINDOWSWIFIMANAGERMODE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOWINDOWSWIFIMANAGERMODE::Clean()
{


}
