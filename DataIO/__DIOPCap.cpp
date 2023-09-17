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

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

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

#include "XMemory_Control.h"

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
* @brief      Constructor
* @ingroup    DATAIO
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOPCAPNETINTERFACE::DIOPCAPNETINTERFACE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPCAPNETINTERFACE::~DIOPCAPNETINTERFACE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOPCAPNETINTERFACE::~DIOPCAPNETINTERFACE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* DIOPCAPNETINTERFACE::GetName()
* @brief      GetName
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
* @brief      GetDescription
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
* @brief      IsUp
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
* @brief      SetIsUp
* @ingroup    DATAIO
* 
* @param[in]  isup : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPCAPNETINTERFACE::SetIsUp(bool isup)
{
  this->isup = isup;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAPNETINTERFACE::IsRunning()
* @brief      IsRunning
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
* @brief      SetIsRunning
* @ingroup    DATAIO
* 
* @param[in]  isrunning : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPCAPNETINTERFACE::SetIsRunning(bool isrunning)
{
  this->isrunning = isrunning;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAPNETINTERFACE::IsWireless()
* @brief      IsWireless
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
* @brief      SetIsWireless
* @ingroup    DATAIO
* 
* @param[in]  iswireless : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPCAPNETINTERFACE::SetIsWireless(bool iswireless)
{
  this->iswireless = iswireless;
}           


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAPNETINTERFACE::IsLoopBack()
* @brief      IsLoopBack
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
* @brief      SetIsLoopBack
* @ingroup    DATAIO
* 
* @param[in]  isloopback : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPCAPNETINTERFACE::SetIsLoopBack(bool isloopback)
{
  this->isloopback = isloopback;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOPCAPNETINTERFACE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @return     void : does not return anything. 
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
* @brief      Constructor
* @ingroup    DATAIO
* 
* @param[in]  bool : 
* @param[in]   bool isloopback : 
* 
* @return     Does not return anything. 
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
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @return     Does not return anything. 
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
* @fn         bool DIOPCAPFRAME::GetHeader(DIOPCAPETHERNETHEADER& ethernetheader)
* @brief      GetHeader
* @ingroup    DATAIO
* 
* @param[in]  ethernetheader : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAPFRAME::GetHeader(DIOPCAPETHERNETHEADER& header)
{
  if(!data) return false;

  if(data->GetSize() < (sizeof(DIOPCAPETHERNETHEADER))) return false;

  DIOPCAPETHERNETHEADER* _ethernetheader = (DIOPCAPETHERNETHEADER*)(data->Get());
  if(!_ethernetheader) return false;

  memcpy((XBYTE*)&header,(XBYTE*)(_ethernetheader),sizeof(DIOPCAPETHERNETHEADER));

  if(hardwareuselittleendian)
    {
      SWAPWORD(header.type);
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAPFRAME::GetHeader(DIOPCAPIPHEADER& header)
* @brief      GetHeader
* @ingroup    DATAIO
* 
* @param[in]  ipheader : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAPFRAME::GetHeader(DIOPCAPIPHEADER& header)
{
  if(!data) return false;

  if(data->GetSize() < (sizeof(DIOPCAPETHERNETHEADER) + sizeof(DIOPCAPIPHEADER))) return false;

  DIOPCAPIPHEADER* _ipheader = (DIOPCAPIPHEADER*)(data->Get() + sizeof(DIOPCAPETHERNETHEADER));
  if(!_ipheader) return false;

  memcpy((XBYTE*)&header,(XBYTE*)(_ipheader),sizeof(DIOPCAPIPHEADER));

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
* @brief      GetHeader
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
  if(!GetHeader(ipheader)) return false;

  int iplen = (ipheader.ver_ihl & 0xf) * 4;

  DIOPCAPUDPHEADER* _udpheader = (DIOPCAPUDPHEADER*)((XBYTE*)data->Get() + sizeof(DIOPCAPETHERNETHEADER) + iplen);
  if(!_udpheader) return false;

  memcpy((XBYTE*)&header,(XBYTE*)(_udpheader),sizeof(DIOPCAPUDPHEADER));

  if(hardwareuselittleendian)
    {
      SWAPWORD(header.sourceport);        // Source port
      SWAPWORD(header.targetport);        // Target port
      SWAPWORD(header.len);               // Datagram length
      SWAPWORD(header.CRC);               // Checksum
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAPFRAME::GetHeader(DIOPCAPTCPHEADER& header)
* @brief      GetHeader
* @ingroup    DATAIO
* 
* @param[in]  header : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAPFRAME::GetHeader(DIOPCAPTCPHEADER& header)
{
  DIOPCAPTCPHEADER* _tcpheader = (DIOPCAPTCPHEADER*)(data->Get() + sizeof(DIOPCAPETHERNETHEADER) + sizeof(DIOPCAPIPHEADER));
  if(!_tcpheader) return false;

  memcpy((XBYTE*)&header,(XBYTE*)(_tcpheader),sizeof(DIOPCAPTCPHEADER));

  if(hardwareuselittleendian)
    {
      SWAPWORD (header.sourceport);
      SWAPWORD (header.targetport);
      SWAPDWORD(header.seq);
      SWAPDWORD(header.ack_seq);
      SWAPWORD (header.dataoffctrl);
      SWAPWORD (header.window);
      SWAPWORD (header.check);
      SWAPWORD (header.urg_ptr);
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBYTE* DIOPCAPFRAME::UserData_Get()
* @brief      UserData_Get
* @ingroup    DATAIO
*
* @return     XBYTE* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XBYTE* DIOPCAPFRAME::UserData_Get()
{
  XBYTE* userdata = data->Get();

  if(!isloopback)
    {
      DIOPCAPETHERNETHEADER ethernetheader;
      if(GetHeader(ethernetheader))
        {
          userdata += sizeof(DIOPCAPETHERNETHEADER);
        }

      if(ethernetheader.type != DIOPCAPETHERNETTYPE_IP)
        {
          return NULL;
        }
    }
   else
    {
      userdata += sizeof(XDWORD);
    }

  DIOPCAPIPHEADER ipheader;
  if(GetHeader(ipheader))
    {
      userdata += sizeof(DIOPCAPIPHEADER);

      switch(ipheader.protocol)
        {
          case DIOPCAPIPPROTOCOLTYPE_TCP : userdata += sizeof(DIOPCAPTCPHEADER);
                                            break;

          case DIOPCAPIPPROTOCOLTYPE_UDP : userdata += sizeof(DIOPCAPUDPHEADER);
                                            break;
        }
    }

  return userdata;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int DIOPCAPFRAME::UserData_GetSize()
* @brief      UserData_GetSize
* @ingroup    DATAIO
*
* @return     int : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
int DIOPCAPFRAME::UserData_GetSize()
{
  int userdatasize = data->GetSize();

  if(!isloopback)
    {
      DIOPCAPETHERNETHEADER ethernetheader;
      if(GetHeader(ethernetheader))
        {
          userdatasize -= sizeof(DIOPCAPETHERNETHEADER);
        }

      if(ethernetheader.type == DIOPCAPETHERNETTYPE_IP)
        {
          return 0;
        }
    }
   else
    {
      userdatasize += sizeof(XDWORD);
    }  

  DIOPCAPIPHEADER ipheader;
  if(GetHeader(ipheader))
    {
      userdatasize -= sizeof(DIOPCAPIPHEADER);

      switch(ipheader.protocol)
        {
          case DIOPCAPIPPROTOCOLTYPE_TCP : userdatasize -= sizeof(DIOPCAPTCPHEADER);
                                           break;

          case DIOPCAPIPPROTOCOLTYPE_UDP : userdatasize -= sizeof(DIOPCAPUDPHEADER);
                                           break;
        }
    }
        
  return userdatasize;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBUFFER* DIOPCAPFRAME::GetData()
* @brief      GetData
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
* @brief      SetData
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
* @fn         void DIOPCAPFRAME::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOPCAPFRAME::Clean()
{
  data                    = NULL;
  hardwareuselittleendian = false;
  isloopback              = false;  
}

#pragma endregion


#pragma region DIOPCAP_CLASS

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPCAP::DIOPCAP()
* @brief      Constructor
* @ingroup    DATAIO
*
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOPCAP::DIOPCAP()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPCAP::~DIOPCAP()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOPCAP::~DIOPCAP()
{
  End();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<DIOPCAPNETINTERFACE*>* DIOPCAP::GetNetInterfaces()
* @brief      GetNetInterfaces
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
* @brief      GetNetInterface
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
* @brief      GetNetInterfaceSelected
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
* @brief      Capture_Start
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
* @brief      Frames_Get
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
* @brief      Frames_Delete
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
* @brief      Frames_Get
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
* @brief      Frames_DeleteAll
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
* @brief      Frames_Add
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

  bool hardwareuselittleendian = true;
  hardwareuselittleendian = GEN_XSYSTEM.HardwareUseLittleEndian();

  DIOPCAPFRAME* frame = new DIOPCAPFRAME(hardwareuselittleendian, isloopback);
  if(frame)
    {
      if(frame->SetData(data,size))
        {



          frames.Add(frame);
          status = true;
        }
    }

  if(xmutexframes) xmutexframes->UnLock();

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOPCAP::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOPCAP::Clean()
{
  xmutexframes          = NULL;  
  netinterfaceselected  = NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAP::DeleteListNetInterfaces()
* @brief      DeleteListNetInterfaces
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

