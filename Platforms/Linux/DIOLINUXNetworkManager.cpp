/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOLINUXNetworkManager.cpp
* 
* @class      DIOLINUXNETWORKMANAGER
* @brief      Data Input/Output LINUX Network Manager class
* @ingroup    PLATFORM_LINUX
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @copyright  Copyright(c) 2005 - 2021 GEN Group.
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
* ---------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <NetworkManager.h>

#include "XTrace.h"

#include "DIOLINUXDBus_XEvent.h"
#include "DIOLINUXDBus.h"

#include "DIOLINUXNetworkManager.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOLINUXNETWORKMANAGER::DIOLINUXNETWORKMANAGER()
* @brief      Constructor
* @ingroup    PLATFORM_LINUX
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOLINUXNETWORKMANAGER::DIOLINUXNETWORKMANAGER()
{ 
  Clean();   

  dbus_destination = DIOLINUXNETWORKMANAGER_DEFAULT_DBUS_DESTINATION;
  dbus_path        = DIOLINUXNETWORKMANAGER_DEFAULT_DBUS_PATH;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOLINUXNETWORKMANAGER::~DIOLINUXNETWORKMANAGER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_LINUX
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOLINUXNETWORKMANAGER::~DIOLINUXNETWORKMANAGER()    
{ 
  End();

  Clean();                            
}




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOLINUXNETWORKMANAGER::Ini()
* @brief      Ini
* @ingroup    PLATFORM_LINUX
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXNETWORKMANAGER::Ini()
{
  bool status;

  dbus = new DIOLINUXDBUS();
  if(!dbus) return false;

  status = dbus->Ini();  
  if(status)
    {
      SubscribeEvent(DIOLINUXDBUS_XEVENT_TYPE_SIGNAL  , dbus);    
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOLINUXNETWORKMANAGER::Enable(bool on)
* @brief      Enable
* @ingroup    PLATFORM_LINUX
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  on : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXNETWORKMANAGER::Enable(bool on)
{
  DIOLINUXDBUS_MESSAGE  message;  
  DIOLINUXDBUS_MESSAGE  reply;  
  bool                  status = false;

  if(!dbus) return false;

  message.GetDestination()->Set(DIOLINUXNETWORKMANAGER_DEFAULT_DBUS_DESTINATION);
  message.GetPath()->Set(DIOLINUXNETWORKMANAGER_DEFAULT_DBUS_PATH);
  message.GetIFace()->Set(DIOLINUXNETWORKMANAGER_DEFAULT_DBUS_IFACE_MAIN);

  message.GetMethod()->Set(__L("Enable"));

  status = message.Create();
  if(status)
    {        
      DIOLINUXDBUS_ARGUMENTS arguments(true, &message);

      arguments.Append(on);
      
      status = dbus->CallMethod(message, reply);                       
      if(status) 
        {
          
        }   

      reply.Delete();

      message.Delete();
    }
    else 
    {
      XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[DBUS] Error create message [%s] [%s]"), message.GetIFace()->Get(), message.GetMethod()->Get());
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOLINUXNETWORKMANAGER_STATE DIOLINUXNETWORKMANAGER::GetConnectionState()
* @brief      GetConnectionState
* @ingroup    PLATFORM_LINUX
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     DIOLINUXNETWORKMANAGER_STATE : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOLINUXNETWORKMANAGER_STATE DIOLINUXNETWORKMANAGER::GetConnectionState()
{
  DIOLINUXDBUS_MESSAGE          message;  
  DIOLINUXDBUS_MESSAGE          reply; 
  DIOLINUXNETWORKMANAGER_STATE  state   = DIOLINUXNETWORKMANAGER_STATE_UNKNOWN;
  bool                          status  = false;

  if(!dbus) return state;

  message.GetDestination()->Set(DIOLINUXNETWORKMANAGER_DEFAULT_DBUS_DESTINATION);
  message.GetPath()->Set(DIOLINUXNETWORKMANAGER_DEFAULT_DBUS_PATH);
  message.GetIFace()->Set(DIOLINUXNETWORKMANAGER_DEFAULT_DBUS_IFACE_MAIN);

  message.GetMethod()->Set(__L("state"));

  status = message.Create();
  if(status)
    {                  
      status = dbus->CallMethod(message, reply);                       
      if(status) 
        {
          XDWORD result = 0;
      
          reply.GetResult(result);

          switch(result)
            {
              case NM_STATE_UNKNOWN           : state = DIOLINUXNETWORKMANAGER_STATE_UNKNOWN;           break;
              case NM_STATE_ASLEEP            : state = DIOLINUXNETWORKMANAGER_STATE_ASLEEP;            break; 
              case NM_STATE_DISCONNECTED      : state = DIOLINUXNETWORKMANAGER_STATE_DISCONNECTED;      break;
              case NM_STATE_DISCONNECTING     : state = DIOLINUXNETWORKMANAGER_STATE_DISCONNECTING;     break;
              case NM_STATE_CONNECTING        : state = DIOLINUXNETWORKMANAGER_STATE_CONNECTING;        break;
              case NM_STATE_CONNECTED_LOCAL   : state = DIOLINUXNETWORKMANAGER_STATE_CONNECTED_LOCAL;   break;
              case NM_STATE_CONNECTED_SITE    : state = DIOLINUXNETWORKMANAGER_STATE_CONNECTED_SITE;    break;
              case NM_STATE_CONNECTED_GLOBAL  : state = DIOLINUXNETWORKMANAGER_STATE_CONNECTED_GLOBAL;  break;
            }
        }   

      reply.Delete();

      message.Delete();
    }
    else 
    {
      XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[DBUS] Error create message [%s] [%s]"), message.GetIFace()->Get(), message.GetMethod()->Get());
    }

  return state;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOLINUXNETWORKMANAGER::GetDevices(XVECTOR<DIOSTREAMDEVICEIP*>& devices)
* @brief      GetDevices
* @ingroup    PLATFORM_LINUX
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  devices : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXNETWORKMANAGER::GetDevices(XVECTOR<DIOSTREAMDEVICEIP*>& devices)
{
  XVECTOR<XSTRING*> pathdevices;
  XVARIANT          value;
  XSTRING           valuestr;

  if(!dbus) return false;

  GetDevicePathList(pathdevices);  

  for(XDWORD c=0; c<pathdevices.GetSize(); c++)
    {    
      DIOSTREAMDEVICEIP* deviceIP =  new DIOSTREAMDEVICEIP();
      if(deviceIP)
        {      
          deviceIP->SetIndex(c);

          GetProperty(DIOLINUXNETWORKMANAGER_DEFAULT_DBUS_IFACE_DEVICE, pathdevices.Get(c)->Get(), __L("DeviceType") , value);  
          XDWORD devicetype = value;

          deviceIP->SetIPType(DIOSTREAMIPDEVICE_TYPE_UNKNOWN);

          switch(devicetype)
            {
              case NM_DEVICE_TYPE_UNKNOWN       : // unknown device
                                                  break;

              case NM_DEVICE_TYPE_GENERIC       : // generic support for unrecognized device types
                                                  deviceIP->SetIPType(DIOSTREAMIPDEVICE_TYPE_LOOPBACK);
                                                  break;

              case NM_DEVICE_TYPE_ETHERNET      : // a wired ethernet device 
                                                  deviceIP->SetIPType(DIOSTREAMIPDEVICE_TYPE_ETHERNET);
                                                  break;

              case NM_DEVICE_TYPE_WIFI          : // an 802.11 Wi-Fi device
                                                  deviceIP->SetIPType(DIOSTREAMIPDEVICE_TYPE_WIFI);
                                                  break;


              case NM_DEVICE_TYPE_UNUSED1       : // not used
              case NM_DEVICE_TYPE_UNUSED2       : // not used
              case NM_DEVICE_TYPE_BT            : // a Bluetooth device supporting PAN or DUN access protocols
              case NM_DEVICE_TYPE_OLPC_MESH     : // an OLPC XO mesh networking device
              case NM_DEVICE_TYPE_WIMAX         : // an 802.16e Mobile WiMAX broadband device
              case NM_DEVICE_TYPE_MODEM         : // a modem supporting analog telephone, CDMA/EVDO, GSM/UMTS, or LTE network access protocols
              case NM_DEVICE_TYPE_INFINIBAND    : // an IP-over-InfiniBand device
              case NM_DEVICE_TYPE_BOND          : // a bond master interface
              case NM_DEVICE_TYPE_VLAN          : // an 802.1Q VLAN interface
              case NM_DEVICE_TYPE_ADSL          : // ADSL modem
              case NM_DEVICE_TYPE_BRIDGE        : // a bridge master interface
              case NM_DEVICE_TYPE_TEAM          : // a team master interface
              case NM_DEVICE_TYPE_TUN           : // a TUN or TAP interface
              case NM_DEVICE_TYPE_IP_TUNNEL     : // a IP tunnel interface
              case NM_DEVICE_TYPE_MACVLAN       : // a MACVLAN interface
              case NM_DEVICE_TYPE_VXLAN         : // a VXLAN interface
              case NM_DEVICE_TYPE_VETH          : // a VETH interface
            //case NM_DEVICE_TYPE_MACSE         : // a MACsec interface
              case NM_DEVICE_TYPE_DUMMY         : // a dummy interface                                                  
                                                  break;

              case NM_DEVICE_TYPE_PPP           : // a PPP interface
                                                  deviceIP->SetIPType(DIOSTREAMIPDEVICE_TYPE_PPP);
                                                  break;

              case NM_DEVICE_TYPE_OVS_INTERFACE : // a Open vSwitch interface
              case NM_DEVICE_TYPE_OVS_PORT      : // a Open vSwitch port
              case NM_DEVICE_TYPE_OVS_BRIDGE    : // a Open vSwitch bridge
              case NM_DEVICE_TYPE_WPAN          : // a IEEE 802.15.4 (WPAN) MAC Layer Device
              case NM_DEVICE_TYPE_6LOWPAN       : // 6LoWPAN interface
              case NM_DEVICE_TYPE_WIREGUARD     : // a WireGuard interface
            //case NM_DEVICE_TYPE_WIFI_P2P      : // an 802.11 Wi-Fi P2P device. Since: 1.16.
            //case NM_DEVICE_TYPE_VRF           : // A VRF (Virtual Routing and Forwarding) interface. Since: 1.24.
                                                  break;
            }

          GetProperty(DIOLINUXNETWORKMANAGER_DEFAULT_DBUS_IFACE_DEVICE, pathdevices.Get(c)->Get(), __L("Interface")  , value); 
          value.ToString(valuestr);
          deviceIP->GetName()->Set(valuestr.Get());
          value.Set();

          GetProperty(DIOLINUXNETWORKMANAGER_DEFAULT_DBUS_IFACE_DEVICE, pathdevices.Get(c)->Get(), __L("Udi") , value);  
          value.ToString(valuestr);
          deviceIP->GetResource()->Set(valuestr.Get());
        

      

          GetProperty(DIOLINUXNETWORKMANAGER_DEFAULT_DBUS_IFACE_DEVICE, pathdevices.Get(c)->Get(), __L("Ip4Config") , value);  
          value.ToString(valuestr);
          GetProperty(DIOLINUXNETWORKMANAGER_DEFAULT_DBUS_IFACE_IP4CONFIG, valuestr.Get(), __L("Gateway"), value);        
          GetProperty(DIOLINUXNETWORKMANAGER_DEFAULT_DBUS_IFACE_IP4CONFIG, valuestr.Get(), __L("AddressData"), value);  

          devices.Add(deviceIP);
        }          
    }       
      
  pathdevices.DeleteContents();
  pathdevices.DeleteAll();

  return true;

}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOLINUXNETWORKMANAGER::Signal_Add(XCHAR* type, XCHAR* name)
* @brief      Signal_Add
* @ingroup    PLATFORM_LINUX
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  type : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXNETWORKMANAGER::Signal_Add(XCHAR* type, XCHAR* name)
{
  if(!dbus)                 return false;
  if(!dbus->IsConnected())  return false;  

  return dbus->Signal_Add(type, name);  
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOLINUXNETWORKMANAGER::Signal_Add(XSTRING& type, XSTRING& name)
* @brief      Signal_Add
* @ingroup    PLATFORM_LINUX
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  type : 
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXNETWORKMANAGER::Signal_Add(XSTRING& type, XSTRING& name)
{
  return Signal_Add(type.Get(), name.Get());
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOLINUXNETWORKMANAGER::End()
* @brief      End
* @ingroup    PLATFORM_LINUX
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXNETWORKMANAGER::End()
{
  if(dbus)
    {
      UnSubscribeEvent(DIOLINUXDBUS_XEVENT_TYPE_SIGNAL  , dbus);    

      dbus->End();            
      delete dbus;

      dbus = NULL;
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOLINUXNETWORKMANAGER::GetDevicePathList(XVECTOR<XSTRING*>& pathdevices)
* @brief      GetDevicePathList
* @ingroup    PLATFORM_LINUX
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  pathdevices : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXNETWORKMANAGER::GetDevicePathList(XVECTOR<XSTRING*>& pathdevices)  
{
  DIOLINUXDBUS_MESSAGE  message;  
  DIOLINUXDBUS_MESSAGE  reply;   
  bool                  status  = false;

  pathdevices.DeleteContents();
  pathdevices.DeleteAll();

  message.GetDestination()->Set(DIOLINUXNETWORKMANAGER_DEFAULT_DBUS_DESTINATION);
  message.GetPath()->Set(DIOLINUXNETWORKMANAGER_DEFAULT_DBUS_PATH);
  message.GetIFace()->Set(DIOLINUXNETWORKMANAGER_DEFAULT_DBUS_IFACE_MAIN);

  message.GetMethod()->Set(__L("GetDevices"));

  status = message.Create();
  if(!status) return false;

  status = dbus->CallMethod(message, reply);                       
  if(status)
    {       
      status = reply.GetResult(pathdevices);
      if(status)
        {         
          for(int c=0; c<pathdevices.GetSize(); c++)
            {
              XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("%s"), pathdevices.Get(c)->Get());
            }          
        }
       else
        {
          XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[DBUS] Error get result ..."));    
        } 
                  
      reply.Delete();
    }   

  message.Delete();

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOLINUXNETWORKMANAGER::GetProperty(XCHAR* iface, XCHAR* pathdevice, XCHAR* propertyname, XVARIANT& result)
* @brief      GetProperty
* @ingroup    PLATFORM_LINUX
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  iface : 
* @param[in]  pathdevice : 
* @param[in]  propertyname : 
* @param[in]  result : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXNETWORKMANAGER::GetProperty(XCHAR* iface, XCHAR* pathdevice, XCHAR* propertyname, XVARIANT& result)
{
  DIOLINUXDBUS_MESSAGE  message;  
  DIOLINUXDBUS_MESSAGE  reply; 
  bool                  status  = false;
  
  message.GetDestination()->Set(DIOLINUXNETWORKMANAGER_DEFAULT_DBUS_DESTINATION);
  message.GetPath()->Set(pathdevice);
  message.GetIFace()->Set(DIOLINUXDBUS_IFACE_PROPERTIES);
  message.GetMethod()->Set("Get");
 
  status = message.Create();
  if(status) 
    {  
      DIOLINUXDBUS_ARGUMENTS arg_in(true, &message);

      arg_in.AppendIterator(iface);
      arg_in.AppendIterator(propertyname);
      
      status = dbus->CallMethod(message, reply);                       
      if(status)
        {    
          DIOLINUXDBUS_ARGUMENTS arg_out(false, &reply);   

          arg_out.GetResultInteractor(result);

          //--------------------------------------------------------------------          

          switch(result.GetType())
            {
              case XVARIANT_TYPE_NULL           : {
                                                  }
                                                  break;
  
              case XVARIANT_TYPE_SERIALIZABLE   : break;

              case XVARIANT_TYPE_INTEGER        : { XDWORD value;
                                                    value = (XDWORD)result;

                                                    XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Property INTEGER : %08X"), value);      
                                                  } 
                                                  break;
                                                  
              case XVARIANT_TYPE_DOUBLEINTEGER  :
              case XVARIANT_TYPE_FLOAT          :
              case XVARIANT_TYPE_DOUBLE         : break;

              case XVARIANT_TYPE_CHAR           : 
              case XVARIANT_TYPE_XCHAR          : 
              case XVARIANT_TYPE_STRING         : { XSTRING value;
                                                    result.ToString(value);

                                                    XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Property STRING : %s"), value.Get());      
                                                  } 
                                                  break;

              case XVARIANT_TYPE_DATE           :
              case XVARIANT_TYPE_TIME           :
              case XVARIANT_TYPE_DATETIME       : break;
            }           

          //--------------------------------------------------------------------
            
        }
    }

  return status;
}




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOLINUXNETWORKMANAGER::HandleEvent_Signal(DIOLINUXDBUS_XEVENT* event)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    PLATFORM_LINUX
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  event : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOLINUXNETWORKMANAGER::HandleEvent_Signal(DIOLINUXDBUS_XEVENT* event)
{  
  switch(event->GetEventType())
    {
      case DIOLINUXDBUS_XEVENT_TYPE_SIGNAL      : { DIOLINUXDBUS_SIGNAL* signal = event->GetSignal();
                                                    if(signal)
                                                      { 
                                                        XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Network Manager] Signal [%s] [%s]"), signal->GetType()->Get(), signal->GetName()->Get()); 
                                                      }
                                                  }
                                                  break;
    }
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOLINUXNETWORKMANAGER::HandleEvent(XEVENT* xevent)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    PLATFORM_LINUX
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  xevent : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOLINUXNETWORKMANAGER::HandleEvent(XEVENT* xevent)
{
  if(!xevent) return;
  
  switch(xevent->GetEventFamily())
    {
      case XEVENT_TYPE_LINUX_DBUS      :  { DIOLINUXDBUS_XEVENT* event = (DIOLINUXDBUS_XEVENT*)xevent;
                                            if(!event) return;

                                            HandleEvent_Signal(event);                                            
                                          }
                                          break;
      
    }
}


  
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOLINUXNETWORKMANAGER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_LINUX
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOLINUXNETWORKMANAGER::Clean()
{
  dbus      = NULL;

  dbus_destination.Empty();
  dbus_path.Empty();
}
