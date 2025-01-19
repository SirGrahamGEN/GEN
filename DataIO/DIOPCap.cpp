/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOPCap.cpp
* 
* @class      DIOPCAP
* @brief      Data Input/Output PCap Library class
* @ingroup    DATAIO
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

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIOPCap.h"

#include <stdio.h>
#include <string.h>

#include "XBase.h"
#include "XFactory.h"
#include "XVector.h"
#include "XSystem.h"

#include "DIOPCap_Filters.h"

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


#pragma region DIOPCAPNETINTERFACE_CLASS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPCAPNETINTERFACE::DIOPCAPNETINTERFACE()
* @brief      Constructor of class
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOPCAPNETINTERFACE::DIOPCAPNETINTERFACE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPCAPNETINTERFACE::~DIOPCAPNETINTERFACE()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOPCAPNETINTERFACE::~DIOPCAPNETINTERFACE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* DIOPCAPNETINTERFACE::GetName()
* @brief      Get name
* @ingroup    DATAIO
*
* @return     XSTRING* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOPCAPNETINTERFACE::GetName()
{
  return &name;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* DIOPCAPNETINTERFACE::GetDescription()
* @brief      Get description
* @ingroup    DATAIO
*
* @return     XSTRING* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOPCAPNETINTERFACE::GetDescription()
{
  return &description;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAPNETINTERFACE::IsUp()
* @brief      Is up
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAPNETINTERFACE::IsUp()
{
  return isup;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOPCAPNETINTERFACE::SetIsUp(bool isup)
* @brief      Set is up
* @ingroup    DATAIO
* 
* @param[in]  isup : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPCAPNETINTERFACE::SetIsUp(bool isup)
{
  this->isup = isup;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAPNETINTERFACE::IsRunning()
* @brief      Is running
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAPNETINTERFACE::IsRunning()
{
  return isrunning;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOPCAPNETINTERFACE::SetIsRunning(bool isrunning)
* @brief      Set is running
* @ingroup    DATAIO
* 
* @param[in]  isrunning : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPCAPNETINTERFACE::SetIsRunning(bool isrunning)
{
  this->isrunning = isrunning;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAPNETINTERFACE::IsWireless()
* @brief      Is wireless
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAPNETINTERFACE::IsWireless()
{
  return iswireless;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOPCAPNETINTERFACE::SetIsWireless(bool iswireless)
* @brief      Set is wireless
* @ingroup    DATAIO
* 
* @param[in]  iswireless : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPCAPNETINTERFACE::SetIsWireless(bool iswireless)
{
  this->iswireless = iswireless;
}           


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAPNETINTERFACE::IsLoopBack()
* @brief      Is loop back
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAPNETINTERFACE::IsLoopBack()
{
  return isloopback;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOPCAPNETINTERFACE::SetIsLoopBack(bool isloopback)
* @brief      Set is loop back
* @ingroup    DATAIO
* 
* @param[in]  isloopback : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPCAPNETINTERFACE::SetIsLoopBack(bool isloopback)
{
  this->isloopback = isloopback;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOPCAPNETINTERFACE::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOPCAPNETINTERFACE::Clean()
{
  isup        = false;  
  isrunning   = false;  
  iswireless  = false;  
  isloopback  = false;      
}

#pragma endregion


#pragma region DIOPCAPFRAME_CLASS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPCAPFRAME::DIOPCAPFRAME(bool hardwareuselittleendian, bool isloopback)
* @brief      Constructor of class
* @ingroup    DATAIO
* 
* @param[in]  bool : 
* @param[in]   bool isloopback : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOPCAPFRAME::DIOPCAPFRAME(bool hardwareuselittleendian, bool isloopback)
{
  Clean();

  this->hardwareuselittleendian = hardwareuselittleendian;
  this->isloopback              = isloopback;

  data = new XBUFFER();
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPCAPFRAME::~DIOPCAPFRAME()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* ---------------------------------------------------------------------------------------------------------------------*/
DIOPCAPFRAME::~DIOPCAPFRAME()
{
  if(data)
    {
      delete data;
      data = NULL;
    }

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBUFFER* DIOPCAPFRAME::GetData()
* @brief      Get data
* @ingroup    DATAIO
*
* @return     XBUFFER* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XBUFFER* DIOPCAPFRAME::GetData()
{
  return data;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAPFRAME::SetData(XBYTE* data, XDWORD size)
* @brief      Set data
* @ingroup    DATAIO
*
* @param[in]  data : 
* @param[in]  size : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAPFRAME::SetData(XBYTE* data, XDWORD size)
{
  if(!this->data) return false;
  if(!data)       return false;
  if(!size)       return false;

  this->data->Delete();
  this->data->Add(data,size);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIOPCAPFRAME::GetProtocolType()
* @brief      Get protocol type
* @ingroup    DATAIO
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOPCAPFRAME::GetProtocolType()
{
  return protocoltype;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOPCAPFRAME::GetProtocolTypeString(XSTRING& protocoltypestr)
* @brief      Get protocol type string
* @ingroup    DATAIO
* 
* @param[in]  protocoltypestr : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPCAPFRAME::GetProtocolTypeString(XSTRING& protocoltypestr)
{
  protocoltypestr.Empty();

  switch(protocoltype)
    {
      case DIOPCAPPROTOCOL_TYPE_UNKNOWN  : break;
      case DIOPCAPPROTOCOL_TYPE_ICMP     : protocoltypestr = __L("ICMP");   break;      
      case DIOPCAPPROTOCOL_TYPE_UDP      : protocoltypestr = __L("UDP");    break;                                            
      case DIOPCAPPROTOCOL_TYPE_TCP      : protocoltypestr = __L("TCP");    break;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAPFRAME::SetProtocolType(DIOPCAPPROTOCOL_TYPE protocoltype)
* @brief      Set protocol type
* @ingroup    DATAIO
* 
* @param[in]  protocoltype : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAPFRAME::SetProtocolType(DIOPCAPPROTOCOL_TYPE protocoltype)
{
  this->protocoltype = protocoltype;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOMAC* DIOPCAPFRAME::GetSourceMAC()
* @brief      Get source MAC
* @ingroup    DATAIO
* 
* @return     DIOMAC* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOMAC* DIOPCAPFRAME::GetSourceMAC()
{
  return &sourceMAC;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOMAC* DIOPCAPFRAME::GetTargetMAC()
* @brief      Get target MAC
* @ingroup    DATAIO
* 
* @return     DIOMAC* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOMAC* DIOPCAPFRAME::GetTargetMAC()
{
  return &targetMAC;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOIP* DIOPCAPFRAME::GetSourceIP()
* @brief      Get source IP
* @ingroup    DATAIO
* 
* @return     DIOIP* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOIP* DIOPCAPFRAME::GetSourceIP()
{
  return &sourceIP;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOIP* DIOPCAPFRAME::GetTargetIP()
* @brief      Get target IP
* @ingroup    DATAIO
* 
* @return     DIOIP* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOIP* DIOPCAPFRAME::GetTargetIP()
{
  return &targetIP;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XWORD DIOPCAPFRAME::GetSourcePort()
* @brief      Get source port
* @ingroup    DATAIO
* 
* @return     XWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XWORD DIOPCAPFRAME::GetSourcePort()
{
  return sourceport;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAPFRAME::SetSourcePort(XWORD port)
* @brief      Set source port
* @ingroup    DATAIO
* 
* @param[in]  port : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAPFRAME::SetSourcePort(XWORD port)
{
  this->sourceport = port;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XWORD DIOPCAPFRAME::GetTargetPort()
* @brief      Get target port
* @ingroup    DATAIO
* 
* @return     XWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XWORD DIOPCAPFRAME::GetTargetPort()
{
  return targetport;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAPFRAME::SetTargetPort(XWORD port)
* @brief      Set target port
* @ingroup    DATAIO
* 
* @param[in]  port : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAPFRAME::SetTargetPort(XWORD port)
{
  this->targetport = port;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBYTE* DIOPCAPFRAME::GetDataPayload()
* @brief      Get data payload
* @ingroup    DATAIO
* 
* @return     XBYTE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE* DIOPCAPFRAME::GetDataPayload()
{
  return data_payload;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int DIOPCAPFRAME::GetDataPayLoadSize()
* @brief      Get data pay load size
* @ingroup    DATAIO
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int DIOPCAPFRAME::GetDataPayLoadSize()
{
  return data_payloadsize;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIOPCAPFRAME::GetAllHeadersSize()
* @brief      Get all headers size
* @ingroup    DATAIO
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOPCAPFRAME::GetAllHeadersSize()
{
  return allheaderssize;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOPCAPFRAME::SetAllHeadersSize(XDWORD allheaderssize)
* @brief      Set all headers size
* @ingroup    DATAIO
* 
* @param[in]  allheaderssize : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPCAPFRAME::SetAllHeadersSize(XDWORD allheaderssize)
{
  this->allheaderssize = allheaderssize; 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAPFRAME::GetHeader(DIOPCAPETHERNETHEADER& ethernetheader)
* @brief      Get header
* @ingroup    DATAIO
* 
* @param[in]  ethernetheader : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAPFRAME::GetHeader(DIOPCAPETHERNETHEADER& header)
{
  if(!data) 
    {
      return false;
    }

  if(data->GetSize() < (sizeof(DIOPCAPETHERNETHEADER))) 
    {
      return false;
    }

  if(!ethernet_header) 
    {
      return false;
    }

  memcpy((XBYTE*)&header,(XBYTE*)(ethernet_header),sizeof(DIOPCAPETHERNETHEADER));

  if(hardwareuselittleendian)
    {
      SWAPWORD(header.type);
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAPFRAME::GetHeader(DIOPCAPIPHEADER& header)
* @brief      Get header
* @ingroup    DATAIO
* 
* @param[in]  ipheader : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAPFRAME::GetHeader(DIOPCAPIPHEADER& header)
{
  if(!data) 
    {
      return false;
    }

  if(data->GetSize() < (sizeof(DIOPCAPETHERNETHEADER) + sizeof(DIOPCAPIPHEADER))) 
    {
      return false;
    }
 
  if(!IP_header) 
    {
      return false;
    }

  memcpy((XBYTE*)&header,(XBYTE*)(IP_header),sizeof(DIOPCAPIPHEADER));

  if(hardwareuselittleendian)
    {
      SWAPWORD(header.len);
      SWAPWORD(header.identification);
      SWAPWORD(header.flags_fo);
      SWAPWORD(header.CRC);
    }

  return true; //length of ethernet header
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAPFRAME::GetHeader(DIOPCAPUDPHEADER& header)
* @brief      Get header
* @ingroup    DATAIO
* 
* @param[in]  header : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAPFRAME::GetHeader(DIOPCAPUDPHEADER& header)
{
  DIOPCAPIPHEADER ipheader;
  if(!GetHeader(ipheader)) 
    {
      return false;
    }

  int iplen = (ipheader.ver_ihl & 0xf) * 4;

  UDP_header = (DIOPCAPUDPHEADER*)((XBYTE*)data->Get() + sizeof(DIOPCAPETHERNETHEADER) + iplen);
  if(!UDP_header) 
    {
      return false;
    }

  memcpy((XBYTE*)&header,(XBYTE*)(UDP_header),sizeof(DIOPCAPUDPHEADER));

  if(hardwareuselittleendian)
    {
      SWAPWORD(header.sourceport);        // Source port
      SWAPWORD(header.targetport);        // Target port
      SWAPWORD(header.datagramlen);               // Datagram length
      SWAPWORD(header.checksum);               // Checksum
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAPFRAME::GetHeader(DIOPCAPTCPHEADER& header)
* @brief      Get header
* @ingroup    DATAIO
* 
* @param[in]  header : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAPFRAME::GetHeader(DIOPCAPTCPHEADER& header)
{
  if(!TCP_header) return false;

  memcpy((XBYTE*)&header,(XBYTE*)(TCP_header),sizeof(DIOPCAPTCPHEADER));

  if(hardwareuselittleendian)
    {
      SWAPWORD (header.sourceport);
      SWAPWORD (header.targetport);
      SWAPDWORD(header.sequencenumber);
      SWAPDWORD(header.acknowledgementnumber);
      SWAPWORD (header.hlenflags);
      SWAPWORD (header.windowsize);
      SWAPWORD (header.checksum);
      SWAPWORD (header.urgentpointer);
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAPFRAME::Set(DIOPCAPETHERNETHEADER* ethernet_header)
* @brief      Set
* @ingroup    DATAIO
* 
* @param[in]  ethernet_header : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAPFRAME::Set(DIOPCAPETHERNETHEADER* ethernet_header)
{
  this->ethernet_header = ethernet_header;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAPFRAME::Set(DIOPCAPIPHEADER* IP_header)
* @brief      Set
* @ingroup    DATAIO
* 
* @param[in]  IP_header : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAPFRAME::Set(DIOPCAPIPHEADER* IP_header)
{
  this->IP_header = IP_header;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAPFRAME::Set(DIOPCAPUDPHEADER* UDP_header)
* @brief      Set
* @ingroup    DATAIO
* 
* @param[in]  UDP_header : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAPFRAME::Set(DIOPCAPUDPHEADER* UDP_header)
{
  this->UDP_header = UDP_header;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAPFRAME::Set(DIOPCAPTCPHEADER* TCP_header)
* @brief      Set
* @ingroup    DATAIO
* 
* @param[in]  TCP_header : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAPFRAME::Set(DIOPCAPTCPHEADER* TCP_header)
{
  this->TCP_header = TCP_header;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAPFRAME::Set(XBYTE* data_payload, XDWORD data_payloadsize)
* @brief      Set
* @ingroup    DATAIO
* 
* @param[in]  data_payload : 
* @param[in]  data_payloadsize : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAPFRAME::Set(XBYTE* data_payload, XDWORD data_payloadsize)
{
  this->data_payload      = data_payload;
  this->data_payloadsize  = data_payloadsize;  

  return true;
}

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOPCAPFRAME::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOPCAPFRAME::Clean()
{
  hardwareuselittleendian = false;
  isloopback              = false;

  data                    = NULL;

  ethernet_header         = NULL; 
  IP_header               = NULL;
  UDP_header              = NULL;
  TCP_header              = NULL;  

  protocoltype            = DIOPCAPPROTOCOL_TYPE_UNKNOWN;
  
  sourceport              = 0;
  targetport              = 0;

  data_payload            = NULL;
  data_payloadsize        = 0;  

  allheaderssize              = 0;
}


#pragma endregion


#pragma region DIOPCAP_CLASS

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPCAP::DIOPCAP()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* ---------------------------------------------------------------------------------------------------------------------*/
DIOPCAP::DIOPCAP()
{
  Clean();

  filters = new DIOPCAP_FILTERS();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPCAP::~DIOPCAP()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* ---------------------------------------------------------------------------------------------------------------------*/
DIOPCAP::~DIOPCAP()
{
  if(filters)
    {
      delete filters;
      filters = NULL;
    }

  End();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<DIOPCAPNETINTERFACE*>* DIOPCAP::GetNetInterfaces()
* @brief      Get net interfaces
* @ingroup    DATAIO
*
* @return     XVECTOR<DIOPCAPNETINTERFACE*>* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XVECTOR<DIOPCAPNETINTERFACE*>* DIOPCAP::GetNetInterfaces()
{
  return &netinterfaces;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPCAPNETINTERFACE* DIOPCAP::GetNetInterface(int index)
* @brief      Get net interface
* @ingroup    DATAIO
*
* @param[in]  index : 
* 
* @return     DIOPCAPNETINTERFACE* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOPCAPNETINTERFACE* DIOPCAP::GetNetInterface(int index)
{
  return (DIOPCAPNETINTERFACE*)netinterfaces.Get(index);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPCAPNETINTERFACE* DIOPCAP::GetNetInterfaceSelected()
* @brief      Get net interface selected
* @ingroup    DATAIO
* 
* @return     DIOPCAPNETINTERFACE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOPCAPNETINTERFACE* DIOPCAP::GetNetInterfaceSelected()
{
  return netinterfaceselected;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAP::Ini()
* @brief      Ini
* @ingroup    DATAIO
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAP::Ini()
{
  if(!CreateListNetInterfaces()) return false;

  GEN_XFACTORY_CREATE(xmutexframes, Create_Mutex())

  return netinterfaces.GetSize()?true:false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAP::Capture_Start(int index, bool promiscuousmode, int timeout)
* @brief      Capture start
* @ingroup    DATAIO
*
* @param[in]  index : 
* @param[in]  promiscuousmode : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAP::Capture_Start(int index, bool promiscuousmode, int timeout)
{
  DIOPCAPNETINTERFACE* netinterface = GetNetInterface(index);
  if(!netinterface) return false;

  return Capture_Start(netinterface, promiscuousmode, timeout);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPCAPFRAME* DIOPCAP::Frames_Get(int index)
* @brief      Frames get
* @ingroup    DATAIO
*
* @param[in]  index : 
* 
* @return     DIOPCAPFRAME* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOPCAPFRAME* DIOPCAP::Frames_Get(int index)
{
  if(index<0)                      return NULL;
  if(index>=(int)frames.GetSize()) return NULL;

  if(xmutexframes) xmutexframes->Lock();

  DIOPCAPFRAME* frame = (DIOPCAPFRAME*)frames.Get(index);

  if(xmutexframes) xmutexframes->UnLock();

  return frame;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAP::Frames_Delete(int index)
* @brief      Frames delete
* @ingroup    DATAIO
*
* @param[in]  index : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAP::Frames_Delete(int index)
{
  if(xmutexframes) xmutexframes->Lock();

  bool status = false;

  DIOPCAPFRAME* frame = (DIOPCAPFRAME*)frames.Get(index);
  if(frame)
    {
      frames.Delete(frame);
      delete frame;
      status = true;
    }

  if(xmutexframes) xmutexframes->UnLock();

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<DIOPCAPFRAME*>* DIOPCAP::Frames_Get()
* @brief      Frames get
* @ingroup    DATAIO
*
* @return     XVECTOR<DIOPCAPFRAME*>* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XVECTOR<DIOPCAPFRAME*>* DIOPCAP::Frames_Get()
{
  return &frames;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAP::Frames_DeleteAll()
* @brief      Frames delete all
* @ingroup    DATAIO
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAP::Frames_DeleteAll()
{
  if(frames.IsEmpty())  return false;

  if(xmutexframes) xmutexframes->Lock();

  frames.DeleteContents();

  frames.DeleteAll();

  if(xmutexframes) xmutexframes->UnLock();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPCAP_FILTERS* DIOPCAP::GetFilters()
* @brief      Get filters
* @ingroup    DATAIO
* 
* @return     DIOPCAP_FILTERS* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOPCAP_FILTERS* DIOPCAP::GetFilters()
{
  return filters;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAP::End()
* @brief      End
* @ingroup    DATAIO
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAP::End()
{
  DeleteListNetInterfaces();

  Frames_DeleteAll();

  netinterfaceselected = NULL;

  if(xmutexframes)
    {
      GEN_XFACTORY.Delete_Mutex(xmutexframes);
      xmutexframes = NULL;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAP::Frames_Add(XBYTE* data,XDWORD size, bool isloopback)
* @brief      Frames add
* @ingroup    DATAIO
* 
* @param[in]  data : 
* @param[in]  size : 
* @param[in]  isloopback : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAP::Frames_Add(XBYTE* data,XDWORD size, bool isloopback)
{
  if(!data) return false;
  if(!size) return false;

  bool status = false;

  if(xmutexframes) xmutexframes->Lock();

  XDWORD allheaderssize = 0;

  DIOPCAPFRAME* frame = new DIOPCAPFRAME(GEN_XSYSTEM.HardwareUseLittleEndian(), isloopback);
  if(frame)
    {
      if(frame->SetData(data,size))
        {
          XBYTE* framedata = frame->GetData()->Get();
          if(framedata)
            {
              if(!isloopback)
                {
                  DIOPCAPETHERNETHEADER* ethernet_header = (DIOPCAPETHERNETHEADER*)framedata;                  
                  if(ethernet_header)
                    {
                      if(ethernet_header->type != DIOPCAPETHERNETTYPE_IP)
                        { 
                          frame->GetSourceMAC()->Set(ethernet_header->MACsource);
                          frame->GetTargetMAC()->Set(ethernet_header->MACtarget);

                          frame->Set((DIOPCAPETHERNETHEADER*)framedata);

                          allheaderssize = sizeof(DIOPCAPETHERNETHEADER);
                          framedata     += sizeof(DIOPCAPETHERNETHEADER); 
                        }
                    }
                }
               else
                {
                  allheaderssize = sizeof(XDWORD);
                  framedata     += sizeof(XDWORD);
                }

              DIOPCAPIPHEADER* IP_header = (DIOPCAPIPHEADER*)framedata;             
              if(IP_header)    
                { 
                  frame->GetSourceIP()->Set(IP_header->sourceaddr);
                  frame->GetTargetIP()->Set(IP_header->targetaddr);

                  frame->Set((DIOPCAPIPHEADER*)framedata);  

                  allheaderssize  += sizeof(DIOPCAPIPHEADER);
                  framedata       += sizeof(DIOPCAPIPHEADER);                 

                  if(framedata)                                                          
                    {
                      switch(IP_header->protocol)
                        { 
                          case DIOPCAPIPPROTOCOLTYPE_ICMP   : frame->SetProtocolType(DIOPCAPPROTOCOL_TYPE_ICMP);
                                                              break;

                          case DIOPCAPIPPROTOCOLTYPE_UDP    : { DIOPCAPUDPHEADER* UDPheader = (DIOPCAPUDPHEADER*)framedata;
                                                                if(UDPheader)
                                                                  {
                                                                    frame->SetProtocolType(DIOPCAPPROTOCOL_TYPE_UDP);  

                                                                    frame->SetSourcePort(SwapWORD(UDPheader->sourceport));  
                                                                    frame->SetTargetPort(SwapWORD(UDPheader->targetport));  

                                                                    frame->Set((DIOPCAPUDPHEADER*)framedata);

                                                                    allheaderssize  += sizeof(DIOPCAPUDPHEADER); 
                                                                    framedata       += sizeof(DIOPCAPUDPHEADER);                 
                                                                  }
                                                              }                                                           
                                                              break;

                          case DIOPCAPIPPROTOCOLTYPE_TCP    : { DIOPCAPTCPHEADER* TCPheader = (DIOPCAPTCPHEADER*)framedata;
                                                                if(TCPheader)
                                                                  {
                                                                    XWORD TCPheadersize = (SwapWORD(TCPheader->hlenflags) >> 12) *4; 

                                                                    frame->SetProtocolType(DIOPCAPPROTOCOL_TYPE_TCP);

                                                                    frame->SetSourcePort(SwapWORD(TCPheader->sourceport));  
                                                                    frame->SetTargetPort(SwapWORD(TCPheader->targetport));  

                                                                    frame->Set((DIOPCAPTCPHEADER*)framedata);  

                                                                    allheaderssize  += TCPheadersize; 
                                                                    framedata       += TCPheadersize;   
                                                                  }
                                                              }                                                            
                                                              break;                 
                        }
                    }
                }

              
              if(frame->GetData()->GetSize() >= allheaderssize)
                {
                  frame->SetAllHeadersSize(allheaderssize);

                  XDWORD sizepayload = (XDWORD)(frame->GetData()->GetSize() - allheaderssize);
                  if(sizepayload)
                    {
                      frame->Set(framedata, sizepayload);  
                    }

                  frames.Add(frame);
                  status = true;
                }
               else
                {
                  delete frame; 
                  frame = NULL;
                }     
            }   
        }
    }
    
  if(xmutexframes) xmutexframes->UnLock();

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOPCAP::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOPCAP::Clean()
{
  xmutexframes          = NULL;  
  netinterfaceselected  = NULL;

  filters               = NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAP::DeleteListNetInterfaces()
* @brief      Delete list net interfaces
* @ingroup    DATAIO
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAP::DeleteListNetInterfaces()
{
  if(netinterfaces.IsEmpty()) return false;

  netinterfaces.DeleteContents();

  netinterfaces.DeleteAll();

  return true;
}

#pragma endregion


#pragma endregion

#endif

