/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOPCap.cpp
* 
* @class      DIOPCAP
* @brief      Interface PCap Library class
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
* ---------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


#ifdef DIOPCAP_ACTIVE

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

#include "XBase.h"
#include "XFactory.h"
#include "XVector.h"
#include "XSystem.h"

#include "DIOPCap.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPCAPNETINTERFACE::DIOPCAPNETINTERFACE()
* @brief      Constructor
* @ingroup    DATAIO
*
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
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
* ---------------------------------------------------------------------------------------------------------------------*/
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
* @fn         bool DIOPCAPNETINTERFACE::SetName(XCHAR* name)
* @brief      SetName
* @ingroup    DATAIO
*
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAPNETINTERFACE::SetName(XCHAR* name)
{
  this->name = name;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAPNETINTERFACE::SetName(XSTRING& name)
* @brief      SetName
* @ingroup    DATAIO
*
* @param[in]  name : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAPNETINTERFACE::SetName(XSTRING& name)
{
  this->name = name.Get();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAPNETINTERFACE::SetDescription(XCHAR* description)
* @brief      SetDescription
* @ingroup    DATAIO
*
* @param[in]  description : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAPNETINTERFACE::SetDescription(XCHAR* description)
{
  this->description  = description;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAPNETINTERFACE::SetDescription(XSTRING& description)
* @brief      SetDescription
* @ingroup    DATAIO
*
* @param[in]  description : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAPNETINTERFACE::SetDescription(XSTRING& description)
{
  this->description  = description.Get();

  return true;
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

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOPCAPFRAME::DIOPCAPFRAME
* @brief      Constructor
* @ingroup    DATAIO
*
* @param[in]  hardwareuselittleendian : true is hardware use "littleendian"
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOPCAPFRAME::DIOPCAPFRAME(bool hardwareuselittleendian)
{
  Clean();

  this->hardwareuselittleendian = hardwareuselittleendian;

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
* @fn         bool DIOPCAPFRAME::GetHeaderEthernet(DIOPCAPETHERNETHEADER& ethernetheader)
* @brief      GetHeaderEthernet
* @ingroup    DATAIO
*
* @param[in]  ethernetheader : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAPFRAME::GetHeaderEthernet(DIOPCAPETHERNETHEADER& ethernetheader)
{
  if(!data) return false;

  if(data->GetSize() < (sizeof(DIOPCAPETHERNETHEADER))) return false;

  DIOPCAPETHERNETHEADER* _ethernetheader = (DIOPCAPETHERNETHEADER*)(data->Get());
  if(!_ethernetheader) return false;

  memcpy((XBYTE*)&ethernetheader,(XBYTE*)(_ethernetheader),sizeof(DIOPCAPETHERNETHEADER));

  if(hardwareuselittleendian)
    {
      SWAPWORD(ethernetheader.type);
    }

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAPFRAME::GetHeaderIP(DIOPCAPIPHEADER& ipheader)
* @brief      GetHeaderIP
* @ingroup    DATAIO
*
* @param[in]  ipheader : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAPFRAME::GetHeaderIP(DIOPCAPIPHEADER& ipheader)
{
  if(!data) return false;

  if(data->GetSize() < (sizeof(DIOPCAPETHERNETHEADER) + sizeof(DIOPCAPIPHEADER))) return false;

  DIOPCAPIPHEADER* _ipheader = (DIOPCAPIPHEADER*)(data->Get() + sizeof(DIOPCAPETHERNETHEADER));
  if(!_ipheader) return false;

  memcpy((XBYTE*)&ipheader,(XBYTE*)(_ipheader),sizeof(DIOPCAPIPHEADER));

  if(hardwareuselittleendian)
    {
      SWAPWORD(ipheader.len);
      SWAPWORD(ipheader.identification);
      SWAPWORD(ipheader.flags_fo);
      SWAPWORD(ipheader.CRC);
    }

  return true; //length of ethernet header
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAPFRAME::GetHeaderUDP(DIOPCAPUDPHEADER& udpheader)
* @brief      GetHeaderUDP
* @ingroup    DATAIO
*
* @param[in]  udpheader : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAPFRAME::GetHeaderUDP(DIOPCAPUDPHEADER& udpheader)
{
  DIOPCAPIPHEADER ipheader;
  if(!GetHeaderIP(ipheader)) return false;

  int iplen = (ipheader.ver_ihl & 0xf) * 4;

  DIOPCAPUDPHEADER* _udpheader = (DIOPCAPUDPHEADER*)((XBYTE*)data->Get() + sizeof(DIOPCAPETHERNETHEADER) + iplen);
  if(!_udpheader) return false;

  memcpy((XBYTE*)&udpheader,(XBYTE*)(_udpheader),sizeof(DIOPCAPUDPHEADER));

  if(hardwareuselittleendian)
    {
      SWAPWORD(udpheader.sourceport);        // Source port
      SWAPWORD(udpheader.targetport);        // Target port
      SWAPWORD(udpheader.len);               // Datagram length
      SWAPWORD(udpheader.CRC);               // Checksum
    }

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAPFRAME::GetHeaderTCP(DIOPCAPTCPHEADER& tcpheader)
* @brief      GetHeaderTCP
* @ingroup    DATAIO
*
* @param[in]  tcpheader : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAPFRAME::GetHeaderTCP(DIOPCAPTCPHEADER& tcpheader)
{
  DIOPCAPTCPHEADER* _tcpheader = (DIOPCAPTCPHEADER*)(data->Get() + sizeof(DIOPCAPETHERNETHEADER) + sizeof(DIOPCAPIPHEADER));
  if(!_tcpheader) return false;

  memcpy((XBYTE*)&tcpheader,(XBYTE*)(_tcpheader),sizeof(DIOPCAPTCPHEADER));

  if(hardwareuselittleendian)
    {
      SWAPWORD (tcpheader.sourceport);
      SWAPWORD (tcpheader.targetport);
      SWAPDWORD(tcpheader.seq);
      SWAPDWORD(tcpheader.ack_seq);
      SWAPWORD (tcpheader.dataoffctrl);
      SWAPWORD (tcpheader.window);
      SWAPWORD (tcpheader.check);
      SWAPWORD (tcpheader.urg_ptr);
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

  DIOPCAPETHERNETHEADER ethernetheader;
  if(GetHeaderEthernet(ethernetheader))
    {
      userdata += sizeof(DIOPCAPETHERNETHEADER);

      if(ethernetheader.type == DIOPCAPETHERNETTYPE_IP)
        {
          DIOPCAPIPHEADER ipheader;
          if(GetHeaderIP(ipheader))
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

  DIOPCAPETHERNETHEADER ethernetheader;
  if(GetHeaderEthernet(ethernetheader))
    {
      userdatasize -= sizeof(DIOPCAPETHERNETHEADER);

      if(ethernetheader.type == DIOPCAPETHERNETTYPE_IP)
        {
          DIOPCAPIPHEADER ipheader;
          if(GetHeaderIP(ipheader))
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
}



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

  if(xmutexframes)
    {
      GEN_XFACTORY.Delete_Mutex(xmutexframes);
      xmutexframes = NULL;
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAP::Frames_Add(XBYTE* data,XDWORD size)
* @brief      Frames_Add
* @ingroup    DATAIO
*
* @param[in]  data : 
* @param[in]  size : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAP::Frames_Add(XBYTE* data,XDWORD size)
{
  if(!data) return false;
  if(!size) return false;

  bool status = false;

  if(xmutexframes) xmutexframes->Lock();

  bool hardwareuselittleendian = true;

  hardwareuselittleendian = GEN_XSYSTEM.HardwareUseLittleEndian();

  DIOPCAPFRAME* frame = new DIOPCAPFRAME(hardwareuselittleendian);
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
  xmutexframes    = NULL;  
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


#endif