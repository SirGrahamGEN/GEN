//------------------------------------------------------------------------------------------
//  DIOLINUXSTREAMTCPIP.CPP
//
//  LINUX Data Input/Output Stream IP Local Enum Devices class
//
//  Author            : Abraham J. Velez
//  Date Of Creation  : 02/01/2002
//  Last Mofificacion :
//
//  GEN  Copyright (C).  All right reserved.
//------------------------------------------------------------------------------------------

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


//---- INCLUDES ----------------------------------------------------------------------------

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <linux/if_ether.h>
#include <arpa/inet.h>


#include "XTrace.h"
#include "DIOStreamDeviceIP.h"

#include "DIOLINUXStreamIPLocalEnumDevices.h"

#include "XMemory_Control.h"


//---- GENERAL VARIABLE --------------------------------------------------------------------


//---- CLASS MEMBERS -----------------------------------------------------------------------




/*-------------------------------------------------------------------
//  DIOLINUXSTREAMTCPIPLOCALENUMDEVICES::DIOLINUXSTREAMTCPIPLOCALENUMDEVICES
*/
/**
//
//
//  @author      Abraham J. Velez
//  @version      28/04/2013 19:00:01
//
//  @return


*/
/*-----------------------------------------------------------------*/
DIOLINUXSTREAMIPLOCALENUMDEVICES::DIOLINUXSTREAMIPLOCALENUMDEVICES() : DIOSTREAMIPLOCALENUMDEVICES()
{

}



/*-------------------------------------------------------------------
//  DIOLINUXSTREAMTCPIPLOCALENUMDEVICES::~DIOLINUXSTREAMTCPIPLOCALENUMDEVICES
*/
/**
//
//
//  @author      Abraham J. Velez
//  @version      28/04/2013 19:00:12
//
//  @return
//  */
/*-----------------------------------------------------------------*/
DIOLINUXSTREAMIPLOCALENUMDEVICES::~DIOLINUXSTREAMIPLOCALENUMDEVICES()
{

}



/*-------------------------------------------------------------------
//  DIOLINUXSTREAMTCPIPLOCALENUMDEVICES::Search
*/
/**
//
//
//  @author      Abraham J. Velez
//  @version      28/04/2013 19:00:27
//
//  @return       bool :
//  */
/*-----------------------------------------------------------------*/
bool DIOLINUXSTREAMIPLOCALENUMDEVICES::Search()
{
  DelAllDevices();

  int           sock;
  struct ifconf ifconf;
  struct ifreq  ifreq[DIOLINUXSTREAMIPLOCALENUMDEVICES_MAXIFS];
  int           ninterfaces;
  int           c = 0;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) return false;

  ifconf.ifc_buf = (char *) ifreq;
  ifconf.ifc_len = sizeof ifreq;

  if(ioctl(sock, SIOCGIFCONF, &ifconf) == -1)
    {
      close(sock);
      return false;
    }

  ninterfaces = ifconf.ifc_len / sizeof(ifreq[0]);

  //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("N NET Interfaces: %d"), ninterfaces);

  for(c=0; c<ninterfaces; c++)
    {
       char                 ip[INET_ADDRSTRLEN];
       char                 mask[INET_ADDRSTRLEN];
       struct sockaddr_in*  address       = (struct sockaddr_in *) &ifreq[c].ifr_addr;
       struct sockaddr_in*  addressmask   = (struct sockaddr_in *) &ifreq[c].ifr_netmask;

       memset(ip  , 0, sizeof(ip));
       memset(mask, 0, sizeof(mask));

       if(!inet_ntop(AF_INET, &address->sin_addr, ip, sizeof(ip)))
         {
           close(sock);
           return false;
         }

       if(!inet_ntop(AF_INET, &addressmask->sin_addr, mask, sizeof(mask)))
         {
           close(sock);
           return false;
         }

       if(ioctl(sock, SIOCGIFHWADDR, &ifreq[c])==-1) 
         {
           close(sock);
           return false;
         }

        DIOSTREAMDEVICEIP* device = new DIOSTREAMDEVICEIP();
        if(device)
          {
            device->SetIndex(c);

            device->GetName()->Set(ifreq[c].ifr_name);
            device->GetDescription()->Set(__L(""));
            device->GetMAC()->Set((XBYTE*)ifreq[c].ifr_hwaddr.sa_data);            

            device->SetIPType(DIOSTREAMIPDEVICE_TYPE_UNKNOWN);

            //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("   %d Interface: %s"), c, device->GetName()->Get());

            /*  
            if(ifreq[c].ifr_flags & IFF_LOOPBACK)
              {
                device->SetIPType(DIOSTREAMIPDEVICE_TYPE_LOOPBACK);
              }
             else
            */
              {                            
                if(device->GetName()->Find(__L("eth") , true) != XSTRING_NOTFOUND)  device->SetIPType(DIOSTREAMIPDEVICE_TYPE_ETHERNET);
                if(device->GetName()->Find(__L("enx") , true) != XSTRING_NOTFOUND)  device->SetIPType(DIOSTREAMIPDEVICE_TYPE_ETHERNET);   // Debian Stretch form
                if(device->GetName()->Find(__L("ens") , true) != XSTRING_NOTFOUND)  device->SetIPType(DIOSTREAMIPDEVICE_TYPE_ETHERNET);   // Cent OS 7
                if(device->GetName()->Find(__L("ppp") , true) != XSTRING_NOTFOUND)  device->SetIPType(DIOSTREAMIPDEVICE_TYPE_PPP);        // Modem / ppp
                if(device->GetName()->Find(__L("wlan"), true) != XSTRING_NOTFOUND)  device->SetIPType(DIOSTREAMIPDEVICE_TYPE_WIFI);
                if(device->GetName()->Find(__L("wwan"), true) != XSTRING_NOTFOUND)  device->SetIPType(DIOSTREAMIPDEVICE_TYPE_WWAN);
                if(device->GetName()->Find(__L("lo")  , true) != XSTRING_NOTFOUND)  device->SetIPType(DIOSTREAMIPDEVICE_TYPE_LOOPBACK);
              }

            XSTRING IP;
            IP.Set(ip);
            device->GetIP()->Set(IP);
            device->GetIP()->GetMask()->Set(mask);

            devices.Add(device);

            //device->DebugPrintInfo();
          }
    }

  close(sock);

  return true;
}




