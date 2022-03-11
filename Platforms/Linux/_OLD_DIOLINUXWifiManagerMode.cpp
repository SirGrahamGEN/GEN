/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOLINUXWifiManagerMode.cpp
*
* @class      DIOLINUXWIFIMANAGERMODE
* @brief      Data Input/Output LINUX Wifi Manager Mode
* @ingroup    DATAIO
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @copyright  Copyright(c) 2005 - 2020 GEN Group.
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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>


#include "XFactory.h"
#include "XTimer.h"
#include "XTrace.h"
#include "XVector.h"
#include "XSleep.h"
#include "XString.h"
#include "XFileTXT.h"
#include "XProcessManager.h"

#include "DIOFactory.h"
#include "DIOStreamDeviceIP.h"
#include "DIOStreamEnumDevices.h"

#include "DIOLINUXWifiManagerMode.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOLINUXWIFIMANAGERMODE::DIOLINUXWIFIMANAGERMODE()
* @brief      Constructor
* @ingroup    DATAIO
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     Does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOLINUXWIFIMANAGERMODE::DIOLINUXWIFIMANAGERMODE()    
{ 
  Clean();                            
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOLINUXWIFIMANAGERMODE::~DIOLINUXWIFIMANAGERMODE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     Does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOLINUXWIFIMANAGERMODE::~DIOLINUXWIFIMANAGERMODE()    
{ 
  Clean();                            
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOLINUXWIFIMANAGERMODE::SetMode_AP(XCHAR* SSID, XCHAR* password)
* @brief      SetMode_AP
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  SSID : 
* @param[in]  password : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXWIFIMANAGERMODE::SetMode_AP(XCHAR* SSID, XCHAR* password)
{    
  switch(used_API)
    {
      case DIOWIFIMANAGERMODE_API_UNKNOWN               : break;

      case DIOWIFIMANAGERMODE_API_LINUX_WPASUPPLICANT   : WPA_RemoveAllNetworks();
                                                          WPA_GetListRemoteAP(nameAPs);
                                                          return WPA_SetMode(2, SSID, password, -1);                                                                                                                      

      case DIOWIFIMANAGERMODE_API_LINUX_CONNMAN         : return CONNMAN_SetModeAP(SSID, password);
                                                          break;
    }

  return false;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOLINUXWIFIMANAGERMODE::SetMode_Client(XCHAR* SSID, XCHAR* password)
* @brief      SetMode_Client
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  SSID : 
* @param[in]  password : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXWIFIMANAGERMODE::SetMode_Client(XCHAR* SSID, XCHAR* password)  
{  
  switch(used_API)
    {
      case DIOWIFIMANAGERMODE_API_UNKNOWN               : break;

      case DIOWIFIMANAGERMODE_API_LINUX_WPASUPPLICANT   : WPA_RemoveAllNetworks(); 
                                                          ReloadAPList();
                                                          return WPA_SetMode(0, SSID, password, -1);
                                                          
      case DIOWIFIMANAGERMODE_API_LINUX_CONNMAN         : return CONNMAN_SetModeClient(SSID, password);
                                                          break;
    }

  return false;
}    



 /**-------------------------------------------------------------------------------------------------------------------
 *
 *  @fn         bool DIOLINUXWIFIMANAGERMODE::ReloadAPList()
 *  @brief      ReloadAPList
 *  @ingroup    PLATFORM_LINUX
 *
 *  @author     Abraham J. Velez 
 *  @date       01/03/2016 12:00
 *
 *  @return     bool : true if is succesful. 
 *
 *---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXWIFIMANAGERMODE::ReloadAPList()
{
  switch(used_API)
    {
      case DIOWIFIMANAGERMODE_API_UNKNOWN               : break;
      case DIOWIFIMANAGERMODE_API_LINUX_WPASUPPLICANT   : return WPA_GetListRemoteAP(nameAPs);                                                                                                                          
      case DIOWIFIMANAGERMODE_API_LINUX_CONNMAN         : break;
    }
 
  return false;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOLINUXWIFIMANAGERMODE::DHCP_SetMode(bool active)
* @brief      DHCP_SetMode
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  active : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXWIFIMANAGERMODE::DHCP_SetMode(bool active)
{
  #define MARK_DHCP_FILE  __L("# @Special Mark to eliminate@")

  XFILETXT* xfileDHCP = NULL;
  XPATH     xpath;
  bool      status    = false;   

  xfileDHCP = new XFILETXT();
  if(!xfileDHCP) return false;
  
  xpath.Add(__L("/etc/dhcpcd.conf"));

  if(xfileDHCP->Open(xpath, false))
    {
      int nline = -1;

      xfileDHCP->ReadAllFile();      

      for(int c=0; c<xfileDHCP->GetNLines(); c++)
        {
          XSTRING* line = xfileDHCP->GetLine(c);
          if(line)
            {
              int indexline =  line->Find(MARK_DHCP_FILE, true);
              if(indexline != XSTRING_NOTFOUND) 
                {
                  nline = c;  
                  break;
                }
            }
        }
      
      if(nline != -1)
        {
          for(int c=nline; c<(nline+5); c++)
            {
              xfileDHCP->DeleteLine(nline);
            }
        }

      if(active)
        {
          XSTRING line;

          xfileDHCP->AddLine(MARK_DHCP_FILE);

          line.Format(__L("interface %s"), netinterface.Get());
          xfileDHCP->AddLine(line);

          xfileDHCP->AddLine(__L("static ip_address=192.168.1.50/24"));
          xfileDHCP->AddLine(__L("static routers=192.168.1.1"));
          xfileDHCP->AddLine(__L("static domain_name_servers = 192.168.1.1"));         
        } 

      status = xfileDHCP->WriteAllFile();

      xfileDHCP->Close();
    }  

  delete xfileDHCP;

  if(status)
    {
      
      if(active)
        {
          GEN_XPROCESSMANAGER.MakeSystemCommand(__L("systemctl restart dhcpcd"));  
          GEN_XSLEEP.Seconds(4); 

          GEN_XPROCESSMANAGER.MakeSystemCommand(__L("systemctl restart networking"));
          GEN_XSLEEP.Seconds(4);
        }
    
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOLINUXWIFIMANAGERMODE::WPA_SetMode(int mode, XCHAR* SSID, XCHAR* password, int indexnetwork)
* @brief      WPA_SetMode
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  mode : 
* @param[in]  SSID : 
* @param[in]  password : 
* @param[in]  indexnetwork : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXWIFIMANAGERMODE::WPA_SetMode(int mode, XCHAR* SSID, XCHAR* password, int indexnetwork)  
{
  XSTRING   prefixcommand;
  XSTRING   command;
  XSTRING   passwd;
  XSTRING   modestr;
  XSTRING   output;
  int       indexnet;  
  bool      status;
    
  prefixcommand.Format(DIOLINUXWIFIMANAGERMODE_PREFIXCOMMAND, netinterface.Get());

  indexnet = indexnetwork;

  if(indexnet == -1)
    {
      command.Format(__L("%s add_network"), prefixcommand.Get());
      WPA_CLI_Command(command, output);

      output.DeleteCharacter(__C('\n'));
      output.DeleteCharacter(__C('\r'));

      indexnet = output.ConvertToInt();
 
      //command.Format(__L("%s save_config"), prefixcommand.Get());
      //status = WPA_CLI_Command(command, output);
    }
   
  status = WPA_SetValue(indexnet, __L("ssid"), SSID, true);
  if(!status) return false;

  if(password)
    {
      //status = WPA_SetValue(indexnet, __L("key_mgmt"), __L("WPA-PSK"), false);
      //if(!status) return false;
    }
   else
    {
      status = WPA_SetValue(indexnet, __L("key_mgmt"), __L("NONE"), false);
      if(!status) return false;
    }
      

  modestr.Format(__L("%d"), mode);

  status = WPA_SetValue(indexnet, __L("mode"), modestr.Get(), false);
  if(!status) return false;

  if(mode == 2)
    {
      command.Format(__L("%s ap_scan 1"), prefixcommand.Get());
      WPA_CLI_Command(command, output);
    }  


  if(password)
    {  
      status = WPA_SetValue(indexnet, __L("psk"), password, true);
      if(!status) return false;
    }
  

  /*
  passwd.Format(__L("'%s'"), password);
  
  status = WPA_SetValue(indexnet, __L("psk"), passwd.Get(), false);
  if(!status) return false;
*/
  

  command.Format(__L("%s enable_network %d"), prefixcommand.Get(), indexnet);
  status = WPA_CLI_Command(command, output);

  #ifndef  HW_NXP_IMX6

  if(status)
    {
      command.Format(__L("%s save_config"), prefixcommand.Get());
      status = WPA_CLI_Command(command, output);
      
      if(status)
        {
          command.Format(__L("%s reconfigure"), prefixcommand.Get());
          status = WPA_CLI_Command(command, output);
        }
    }

   #endif
  
  return status;
}    






/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOLINUXWIFIMANAGERMODE::WPA_RemoveAllNetworks()
* @brief      WPA_RemoveAllNetworks
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXWIFIMANAGERMODE::WPA_RemoveAllNetworks()
{
  XSTRING   prefixcommand;
  XSTRING   command;
  XSTRING   output;
  bool      status;

  prefixcommand.Format(DIOLINUXWIFIMANAGERMODE_PREFIXCOMMAND, netinterface.Get());

  for(int c=0; c<32; c++)
    {
      command.Format(__L("%s remove_network %d"), prefixcommand.Get(), c);    
      status = WPA_CLI_Command(command, output);     
    } 
      
  command.Format(__L("%s save_config"), prefixcommand.Get());
  status = WPA_CLI_Command(command, output);
  
  return status;

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOLINUXWIFIMANAGERMODE::WPA_SetValue(int indexnetwork, XCHAR* namevalue, XCHAR* value)
* @brief      WPA_SetValue
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  indexnetwork : 
* @param[in]  namevalue : 
* @param[in]  value : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXWIFIMANAGERMODE::WPA_SetValue(int indexnetwork, XCHAR* namevalue, XCHAR* value, bool isstring)
{
  XSTRING   prefixcommand;
  XSTRING   command;
  XSTRING   output;
  bool      status;

  prefixcommand.Format(DIOLINUXWIFIMANAGERMODE_PREFIXCOMMAND, netinterface.Get());

  if(isstring)  
          command.Format(__L("%s set_network %d %s \"%s\"") , prefixcommand.Get(), indexnetwork, namevalue, value);    
    else  command.Format(__L("%s set_network %d %s %s")     , prefixcommand.Get(), indexnetwork, namevalue, value);    

  status = WPA_CLI_Command(command, output);

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOLINUXWIFIMANAGERMODE::WPA_SetValue(int indexnetwork, XSTRING& namevalue, XSTRING& value)
* @brief      WPA_SetValue
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  indexnetwork : 
* @param[in]  namevalue : 
* @param[in]  value : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXWIFIMANAGERMODE::WPA_SetValue(int indexnetwork, XSTRING& namevalue, XSTRING& value)
{
  return WPA_SetValue(indexnetwork, namevalue.Get(), value.Get());
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOLINUXWIFIMANAGERMODE::WPA_GetListRemoteAP(XVECTOR<XSTRING*>& nameAPs)
* @brief      WPA_GetListRemoteAP
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  nameAPs : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXWIFIMANAGERMODE::WPA_GetListRemoteAP(XVECTOR<XSTRING*>& nameAPs)
{ 
  XSTRING   prefixcommand;
  XSTRING   command;
  XSTRING   output;
  bool      status;


  nameAPs.DeleteContents();
  nameAPs.DeleteAll();

  prefixcommand.Format(DIOLINUXWIFIMANAGERMODE_PREFIXCOMMAND, netinterface.Get());

  command.Format(__L("%s scan") , prefixcommand.Get());     
  status = WPA_CLI_Command(command, output);
  if(!status) return false;

  GEN_XSLEEP.Seconds(3);

  command.Format(__L("%s scan_results") , prefixcommand.Get());     
  status = WPA_CLI_Command(command, output);

  int indexfr =  output.Find(__L("\n"), true);
  if(indexfr == XSTRING_NOTFOUND) return false;

  indexfr++;

  int index      = 0;
  int indexstart = 0;

  do{
      index =  output.Find(__L("\n"), true, indexfr);
      if(index == XSTRING_NOTFOUND ) break;

      for(int c=index; c>0 ; c--)
        {
          if(output.Get()[c] == __C(']'))  
            {
              indexstart = c;
              break;
            }               
        }

      indexfr = index+1;

      if(indexstart)
        {
          XSTRING* newstr = new XSTRING();
          if(newstr)
            {
              output.Copy(indexstart+1, index, (*newstr));
              newstr->DeleteCharacter(__C('\t'), XSTRINGCONTEXT_FROM_FIRST);

              // XSTRING_CREATEOEM((*newstr), charstr);
              // printf(charstr, "\n");
              // XSTRING_DELETEOEM((*newstr), charstr);

              nameAPs.Add(newstr);                 
            }
        }

    } while(index != XSTRING_NOTFOUND);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOLINUXWIFIMANAGERMODE::WPA_CLI_Command(XSTRING& command, XSTRING& output)
* @brief      WPA_CLI_Command
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  command : 
* @param[in]  output : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXWIFIMANAGERMODE::WPA_CLI_Command(XSTRING& command, XSTRING& output)
{
  if(command.IsEmpty()) return false;

  output.Empty();

  XSTRING   input;
  int       returncode = 0;
  bool      status     = false;

  GEN_XPROCESSMANAGER.ExecuteApplication(__L("/sbin/wpa_cli"), command.Get(), &input, &output, &returncode);

  if(output.Find(__L("OK"), true) != XSTRING_NOTFOUND) status = true;

 //XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("[WIFI manager] command [%s]  output[%s] : %s"), command.Get(), output.Get(), (status?__L("Ok"):__L("Error"))); 

  XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("[WIFI manager] command [%s]: %s"), command.Get(), (status?__L("Ok"):__L("Error"))); 
  
  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOLINUXWIFIMANAGERMODE::CONNMAN_SetModeClient(XCHAR* SSID, XCHAR* password)
* @brief      CONNMAN_SetModeClient
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  SSID : 
* @param[in]  password : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXWIFIMANAGERMODE::CONNMAN_SetModeClient(XCHAR* SSID, XCHAR* password)
{
  XSTRING   command;
  XSTRING   service;
  bool      status  = false;

  //--------------------------------------------------------   
  GEN_XPROCESSMANAGER.MakeSystemCommand(__L("connmanctl disable wifi"));  
  GEN_XPROCESSMANAGER.MakeSystemCommand(__L("connmanctl enable wifi"));  
  //--------------------------------------------------------

  CONNMAN_GetClientService(SSID, service);  

  if(service.IsEmpty()) return false;

  //--------------------------------------------------------
 
  //command.Format(__L("connmanctl config %s --remove"), service.Get()); 
  //status = GEN_XPROCESSMANAGER.MakeSystemCommand(command.Get());   
  //GEN_XSLEEP.Seconds(2);
   
  status = CONNMAN_ExecuteApplication(__L("/usr/bin/connmanctl"), service.Get(), password);  
  
  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOLINUXWIFIMANAGERMODE::CONNMAN_SetModeAP(XCHAR* SSID, XCHAR* password)
* @brief      CONNMAN_SetModeAP
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  SSID : 
* @param[in]  password : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXWIFIMANAGERMODE::CONNMAN_SetModeAP(XCHAR* SSID, XCHAR* password)
{
  XSTRING   input;
  XSTRING   command;
  XSTRING   output;
  XSTRING   service;
  int       returncode  = 0;
  bool      status      = false;

  //--------------------------------------------------------
  
  GEN_XPROCESSMANAGER.MakeSystemCommand(__L("connmanctl disable wifi"));  
  GEN_XPROCESSMANAGER.MakeSystemCommand(__L("connmanctl enable wifi"));
  
  //--------------------------------------------------------

  CONNMAN_GetListRemoteAP();

  //--------------------------------------------------------

  command.Format(__L("connmanctl tether wifi on \"%s\" \"%s\" "), SSID, password);
  GEN_XPROCESSMANAGER.MakeSystemCommand(command.Get());
  GEN_XSLEEP.Seconds(2);

  //--------------------------------------------------------

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOLINUXWIFIMANAGERMODE::CONNMAN_GetListRemoteAP(XVECTOR<XSTRING*>& nameAPs)
* @brief      CONNMAN_GetListRemoteAP
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  nameAPs : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXWIFIMANAGERMODE::CONNMAN_GetListRemoteAP()
{  
  DIOSTREAMENUMDEVICES* enumdevicesWIFIremote = NULL;

  enumdevicesWIFIremote = GEN_DIOFACTORY.CreateStreamEnumDevices(DIOSTREAMENUMTYPE_WIFI_REMOTE);
	if(!enumdevicesWIFIremote) return false;

  enumdevicesWIFIremote->Search();	

  while(enumdevicesWIFIremote->IsSearching())
    {          
			XSLEEP::GetInstance().MilliSeconds(10);          
		}
 	  
  for(int c=0; c<(int)enumdevicesWIFIremote->GetDevices()->GetSize(); c++)
    {
      DIOSTREAMDEVICEIP* deviceIP = (DIOSTREAMDEVICEIP*)enumdevicesWIFIremote->GetDevices()->Get(c);
      if(deviceIP)
        {      
          XSTRING* nameAP = new XSTRING();
          if(nameAP)
            {
              nameAP->Set(deviceIP->GetName()->Get());
              nameAPs.Add(nameAP);
            }
        }
    }

  GEN_DIOFACTORY.DeleteStreamEnumDevices(enumdevicesWIFIremote);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOLINUXWIFIMANAGERMODE::CONNMAN_GetClientService(XCHAR* SSID, XSTRING& service)
* @brief      CONNMAN_GetClientService
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  SSID : 
* @param[in]  service : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXWIFIMANAGERMODE::CONNMAN_GetClientService(XCHAR* SSID, XSTRING& service)
{
  int       index_start    = 0;  
  int       index_end      = 0;  
  int       index_service  = 0;
  XSTRING   line;
  XSTRING   _SSID;
  XSTRING   _service;
  XSTRING   output;
  bool      status;

 
  status = CONNMAN_Command(__L("scan wifi"), __L("completed"), output);
  if(!status)  
    {
      return false;
    }

  GEN_XSLEEP.Seconds(2);

  output.Empty();
 
  status = CONNMAN_Command(__L("services"), NULL, output);

  do{ index_end =  output.Find(__L("\n"), true, index_start);
      if(index_end == XSTRING_NOTFOUND ) break;

      output.Copy(index_start, index_end, line);
    
      if(line.IsEmpty()) break;
      line.DeleteCharacter(__C('\n') , XSTRINGCONTEXT_ALLSTRING);
      line.DeleteCharacter(__C('\r') , XSTRINGCONTEXT_ALLSTRING);  

      index_service =  line.Find(__L("wifi_"), true);         
      if(index_service == XSTRING_NOTFOUND) 
        { 
          index_service =  line.Find(__L("ethernet_"), true);         
          if(index_service == XSTRING_NOTFOUND) break;
        }

      line.Copy(index_service , index_end     , _service);
      line.Copy(0             , index_service , _SSID);

      _SSID.DeleteCharacter(__C(' '), XSTRINGCONTEXT_FROM_FIRST);
      _SSID.DeleteCharacter(__C(' '), XSTRINGCONTEXT_TO_END);  

      if((_SSID.Get()[0] == __C('*')) && (_SSID.Get()[3] == 0x20))  _SSID.DeleteCharacters(0, 4);
            
      index_start = index_end+1;

      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[COMMAN] Get Client Service  SSID: %s  service: %s"), _SSID.Get(), _service.Get());

      if(!_SSID.Compare(SSID, false))
        {         
          service = _service.Get();
          return true;                        
        }

    } while(index_end != XSTRING_NOTFOUND);


  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOLINUXWIFIMANAGERMODE::CONNMAN_ExecuteApplication(XCHAR* applicationpath, XCHAR* service, XCHAR* password)
* @brief      CONNMAN_ExecuteApplication
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  applicationpath : 
* @param[in]  service : 
* @param[in]  password : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXWIFIMANAGERMODE::CONNMAN_ExecuteApplication(XCHAR* applicationpath, XCHAR* service, XCHAR* password)
{ 
  #define PIPE_READ   0
  #define PIPE_WRITE  1

  if(!applicationpath) return false;

  pid_t pID;
  bool  exist  = false;
  bool  status = false;
  int   stdinpipe[2]  = { 0 , 0 };
  int   stdoutpipe[2] = { 0 , 0 };
  int   nresult = 0;
  int   returncode;

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


  XFILE* xfile = GEN_XFACTORY.Create_File();
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

  XSTRING_CREATEOEM(cmd, charOEM)
  status = system(charOEM);
  XSTRING_DELETEOEM(cmd, charOEM)

  //if(status == -1) return false;

  //------------------------------------------

  cmd = applicationpath;

  pID = fork();

  switch(pID)
    {
      case -1 : { // failed to create child

                  close(stdinpipe[PIPE_READ]);
                  close(stdinpipe[PIPE_WRITE]);

                  close(stdoutpipe[PIPE_READ]);
                  close(stdoutpipe[PIPE_WRITE]);
                }
                break;

      case  0 : { // child continues here

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
                  XSTRING_CREATEOEM(cmd, charcmd)

                  int result = execl(charcmd, charcmd, NULL);

                  if(result == -1)
                    {
                      //XTRACE_PRINTCOLOR(4,__L("Error en EXEC: %d"), errno);
                    }
                   else
                    {
                      returncode = result;
                      status = true;
                    }

                  XSTRING_DELETEOEM(cmd, charcmd)
                  exit(result);
                }
                break;

      default : { XSTRING   line;    
                  XSTRING   output;
                  char      nchar;
                  int       nsecuence = 0;
                  bool      exit_loop = false;

                  //parent continues here

                  // close unused file descriptors, these are for child only
                  close(stdinpipe[PIPE_READ]);
                  close(stdoutpipe[PIPE_WRITE]);   

                  XTIMER* xtimerout =  GEN_XFACTORY.CreateTimer();
                  if(!xtimerout)
                    {
                      status = false;
                      break;
                    }
                         
                  while(!exit_loop)
                    {    
                      if(xtimerout->GetMeasureSeconds() > 20)
                        {
                          exit_loop = true;
                          status    = true;
          
                          break;                              
                        }


                      if(!exit_loop)  
                        {
                          if(!read(stdoutpipe[PIPE_READ], &nchar, 1) == 1)  break;              
                        }

                      line += nchar;
                  
                      switch(nchar)
                        {
                          case '\n' : 
                          case '\r' :
                          case '?'  :
                          case '>'  : { XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("%s"), line.Get());
                                          
                                        if(line.Find(__L("connmanctl>"), true) != XSTRING_NOTFOUND)
                                          {  
                                            switch(nsecuence)
                                              {
                                                case  0 : { output = __L("agent on");    
                                                            output += __L("\n");
                                      
                                                            XSTRING_CREATEOEM(output, charstr);                                               
                                                            write(stdinpipe[PIPE_WRITE], charstr, output.GetSize());
                                                            XSTRING_DELETEOEM(output, charstr);   

                                                            nsecuence = -1;                                                               
                                                          }
                                                          break;


                                                case  1 : { output.Format(__L("connect %s"), service);    
                                                            output += __L("\n");
                                      
                                                            XSTRING_CREATEOEM(output, charstr);                                               
                                                            write(stdinpipe[PIPE_WRITE], charstr, output.GetSize());
                                                            XSTRING_DELETEOEM(output, charstr);     
             
                                                            nsecuence = -1;
                                                          }
                                                          break;

                                                case  2 : { output.Format(__L("exit"), service);    
                                                            output += __L("\n");
                                      
                                                            XSTRING_CREATEOEM(output, charstr);                                               
                                                            write(stdinpipe[PIPE_WRITE], charstr, output.GetSize());
                                                            XSTRING_DELETEOEM(output, charstr);    

                                                            nsecuence = -1;  
                                                            exit_loop = true;  
                                                            
                                                          }
                                                          break;
                                              }

                                          }

   
                                        if(line.Find(__L("Agent registered"), true) != XSTRING_NOTFOUND)
                                          { 
                                            nsecuence = 1;
                                            
                                          }

                                        if(line.Find(__L("Passphrase?"), true) != XSTRING_NOTFOUND) 
                                          {
                                            output = password;
                                            output += __L("\n");
                                      
                                            XSTRING_CREATEOEM(output, charstr);                                               
                                            write(stdinpipe[PIPE_WRITE], charstr, output.GetSize());
                                            XSTRING_DELETEOEM(output, charstr);

                                            nsecuence = -1;  
                                           
                                          }   

                                        if(line.Find(__L("Connected"), true) != XSTRING_NOTFOUND) 
                                          {                                           
                                            nsecuence = 2;   
                                            status = true;                                                                                                                               
                                          }

                                        if(line.Find(__L("Retry (yes/no)?"), true) != XSTRING_NOTFOUND) 
                                          {
                                            output.Format(__L("no"), service);    
                                            output += __L("\n");
                                      
                                            XSTRING_CREATEOEM(output, charstr);                                               
                                            write(stdinpipe[PIPE_WRITE], charstr, output.GetSize());
                                            XSTRING_DELETEOEM(output, charstr);                                                 

                                            nsecuence = 2; 
                                            status = false;                                                                                                                                  
                                          }


                                        line.Empty();                                 
                                      }
                                      break;

                        }
                    }

                  if(xtimerout)  
                    {
                      GEN_XFACTORY.DeleteTimer(xtimerout);
                      xtimerout = NULL;
                    }
                                   
                  // done with these in this example program, you would normally keep these
                  // open of course as long as you want to talk to the child
                  close(stdinpipe[PIPE_WRITE]);
                  close(stdoutpipe[PIPE_READ]);
                }
                
                break;
    }

 
  return status;
}







/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOLINUXWIFIMANAGERMODE::CONNMAN_Command(XCHAR* command, XCHAR* resultOK, XSTRING& output)
* @brief      CONNMAN_Command
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  command : 
* @param[in]  resultOK : 
* @param[in]  output : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXWIFIMANAGERMODE::CONNMAN_Command(XCHAR* command, XCHAR* resultOK, XSTRING& output)
{ 
  if(!command) return false; 

  XSTRING   input;
  int       returncode = 0;
  bool      status     = false;

  GEN_XPROCESSMANAGER.ExecuteApplication(__L("/usr/bin/connmanctl"), command, &input, &output, &returncode);

  if(resultOK)
    {
      if(output.Find(resultOK, true) != XSTRING_NOTFOUND) status = true;
    }
   else status = true;

  //XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("[WIFI manager] command [%s]: %s"), command, (status?__L("Ok"):__L("Error"))); 

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOLINUXWIFIMANAGERMODE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     void : does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOLINUXWIFIMANAGERMODE::Clean()
{


}
