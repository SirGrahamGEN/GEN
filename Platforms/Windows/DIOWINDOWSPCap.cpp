/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOWINDOWSPCap.cpp
* 
* @class      DIOWINDOWSPCAP
* @brief      WINDOWS Data Input/Output PCap Library class
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


#ifdef DIO_PCAP_ACTIVE
                     
#pragma comment(lib,"wpcap.lib")

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIOWINDOWSPCap.h"

#include "XFactory.h"
#include "XTrace.h"
#include "XString.h"
#include "XThreadCollected.h"

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
* @fn         DIOWINDOWSPCAP::DIOWINDOWSPCAP()
* @brief      Constructor of class
* @ingroup    PLATFORM_WINDOWS
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOWINDOWSPCAP::DIOWINDOWSPCAP() : DIOPCAP()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOWINDOWSPCAP::~DIOWINDOWSPCAP()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    PLATFORM_WINDOWS
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOWINDOWSPCAP::~DIOWINDOWSPCAP()
{
  End();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOWINDOWSPCAP::Capture_Start(DIOPCAPNETINTERFACE* netinterface, bool promiscuousmode, int timeout)
* @brief      Capture start
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

  netinterfaceselected = netinterface;
  
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
* @brief      Capture end
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

  netinterfaceselected = NULL;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOWINDOWSPCAP::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    PLATFORM_WINDOWS
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
* @brief      Create list net interfaces
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
          _netinterface->GetName()->Set(netinterface->name);
          _netinterface->GetDescription()->Set(netinterface->description);

          if(netinterface->flags & PCAP_IF_UP)
            {
              _netinterface->SetIsUp(true);
            }

          if(netinterface->flags & PCAP_IF_RUNNING)
            {
              _netinterface->SetIsRunning(true);
            }

          if(netinterface->flags & PCAP_IF_WIRELESS)
            {
              _netinterface->SetIsWireless(true);
            }

          if(netinterface->flags & PCAP_IF_LOOPBACK)
            {
              _netinterface->SetIsLoopBack(true);
            }
      
          netinterfaces.Add(_netinterface);
        }
    }

  pcap_freealldevs(allnetinterfaces);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOWINDOWSPCAP::ThreadCapture(void* data)
* @brief      Thread capture
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  data : 
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
* @brief      Packet handler
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  param : 
* @param[in]  struct pcap_pkthdr* header : 
* @param[in]  u_char* data : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOWINDOWSPCAP::PacketHandler(u_char* param, const struct pcap_pkthdr* header, const u_char* data)
{
  DIOWINDOWSPCAP* diopcap = (DIOWINDOWSPCAP*)param;
  if(!diopcap) return;

  bool isloopback = false;
  if(diopcap->GetNetInterfaceSelected())
    {
      isloopback = diopcap->GetNetInterfaceSelected()->IsLoopBack();
    }

  diopcap->Frames_Add((XBYTE*)data, header->len, isloopback);
}


#pragma endregion


#endif
