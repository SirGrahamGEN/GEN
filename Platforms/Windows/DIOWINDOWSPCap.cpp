/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOWINDOWSPCap.cpp
* 
* @class      DIOWINDOWSPCAP
* @brief      WINDOWS Interface PCap Library (Capture Ethernet Packets) class
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
* ---------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"

#ifdef DIO_PCAP_ACTIVE
                     
#pragma comment(lib,"wpcap.lib")

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <winsock2.h>
#include <windows.h>

#include "XTrace.h"
#include "XThreadCollected.h"
#include "XString.h"
#include "XWINDOWSThread.h"

#include "DIOWINDOWSPCap.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOWINDOWSPCAP::DIOWINDOWSPCAP() : DIOPCAP()
* @brief      Constructor
* @ingroup    PLATFORM_WINDOWS
* 
*  
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOWINDOWSPCAP::DIOWINDOWSPCAP() :  DIOPCAP()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOWINDOWSPCAP::~DIOWINDOWSPCAP()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_WINDOWS
*
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOWINDOWSPCAP::~DIOWINDOWSPCAP()
{
  End();

  Clean();
}




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOWINDOWSPCAP::Capture_Start(DIOPCAPNETINTERFACE* netinterface, bool promiscuousmode, int timeout)
* @brief      Capture_Start
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  netinterface : 
* @param[in]  promiscuousmode : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOWINDOWSPCAP::Capture_Start(DIOPCAPNETINTERFACE* netinterface, bool promiscuousmode, int timeout)
{
  if(!netinterface) return false;

  char errbuf[PCAP_ERRBUF_SIZE];

  XBUFFER charstr;
  
  (*netinterface->GetName()).ConvertToASCII(charstr);
  handle= pcap_open_live(charstr.GetPtrChar()    , // name of the device
                         65536                   , // portion of the packet to capture.  65536 grants that the whole packet will be captured on all the MACs.
                         promiscuousmode?1:0     , // promiscuous mode (nonzero means promiscuous)
                         timeout                 , // read timeout
                         errbuf);                  // error buffer
  if(handle == NULL) return false;


  threadcapture = CREATEXTHREAD(XTHREADGROUPID_DIOPCAP, __L("DIOWINDOWSPCAP::Capture_Start"), ThreadCapture, (void*)this);
  if(!threadcapture) return false;

  return threadcapture->Ini();
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOWINDOWSPCAP::Capture_End()
* @brief      Capture_End
* @ingroup    PLATFORM_WINDOWS
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOWINDOWSPCAP::Capture_End()
{
  if(handle) pcap_breakloop(handle);

  if(threadcapture)
    {
      threadcapture->End();
      DELETEXTHREAD(XTHREADGROUPID_DIOPCAP, threadcapture);
      threadcapture = NULL;
    }

  if(handle)
    {
      pcap_close(handle);
      handle = NULL;
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOWINDOWSPCAP::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_WINDOWS
*
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOWINDOWSPCAP::Clean()
{
  handle        = NULL;
  threadcapture = NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOWINDOWSPCAP::CreateListNetInterfaces()
* @brief      CreateListNetInterfaces
* @ingroup    PLATFORM_WINDOWS
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOWINDOWSPCAP::CreateListNetInterfaces()
{
  pcap_if_t* allnetinterfaces;
  pcap_if_t* netinterface;
  char       errbuf[PCAP_ERRBUF_SIZE];

  // Retrieve the device list
  if(pcap_findalldevs(&allnetinterfaces, errbuf) == -1) return false;

  // Create list
  for(netinterface=allnetinterfaces; netinterface; netinterface=netinterface->next)
    {
      DIOPCAPNETINTERFACE* _netinterface = new DIOPCAPNETINTERFACE();
      if(_netinterface)
        {
          XSTRING string;

          string = netinterface->name;          _netinterface->SetName(string);
          string = netinterface->description;   _netinterface->SetDescription(string);

          netinterfaces.Add(_netinterface);
        }
    }

  pcap_freealldevs(allnetinterfaces);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOWINDOWSPCAP::ThreadCapture(void* data)
* @brief      ThreadCapture
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  data : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOWINDOWSPCAP::ThreadCapture(void* data)
{
  DIOWINDOWSPCAP* diopcap = (DIOWINDOWSPCAP*)data;
  if(!diopcap) return;

  if(diopcap->handle)
    {
      int error = pcap_loop(diopcap->handle, 1, PacketHandler, (u_char*)diopcap);
      if(error)
        {

        }
    }
}




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOWINDOWSPCAP::PacketHandler(u_char* param, const struct pcap_pkthdr* header, const u_char* data)
* @brief      PacketHandler
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  param : 
* @param[in]  struct pcap_pkthdr* header : 
* @param[in]  u_char* data : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOWINDOWSPCAP::PacketHandler(u_char* param, const struct pcap_pkthdr* header, const u_char* data)
{
  DIOWINDOWSPCAP* diopcap = (DIOWINDOWSPCAP*)param;
  if(!diopcap) return;

  diopcap->Frames_Add((XBYTE*)data,header->len);


  /*
  struct tm *ltime;
  char timestr[16];
  time_t local_tv_sec;


  //  unused parameters

  //(VOID)(param);
  //(VOID)(pkt_data);

  // convert the timestamp to readable format
  local_tv_sec = header->ts.tv_sec;
  ltime=localtime(&local_tv_sec);
  strftime( timestr, sizeof timestr, "%H:%M:%S", ltime);

  printf("%s,%.6d len:%d\n", timestr, header->ts.tv_usec, header->len);
  */

}


#endif