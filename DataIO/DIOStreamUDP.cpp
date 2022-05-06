/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOStreamUDP.cpp
*
* @class      DIOSTREAMUDP
* @brief      Data Input/Output Stream UDP class
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XFactory.h"
#include "XBuffer.h"
#include "XThread.h"

#include "DIOFactory.h"
#include "DIOStreamUDPConfig.h"

#include "DIOStreamUDP.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/




/*--------------------------------------------------------------------------------------------------------------------*/
/*  DIOSTREAMUDPDATAGRAM                                                                                              */
/*--------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMUDPDATAGRAM::DIOSTREAMUDPDATAGRAM()
* @brief      Constructor
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMUDPDATAGRAM::DIOSTREAMUDPDATAGRAM()
{
  Clean();
  data = new XBUFFER();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMUDPDATAGRAM::~DIOSTREAMUDPDATAGRAM()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMUDPDATAGRAM::~DIOSTREAMUDPDATAGRAM()
{
  if(data) delete data;

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUDPDATAGRAM::IsToSend()
* @brief      IsToSend
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUDPDATAGRAM::IsToSend()
{
  return istosend;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMUDPDATAGRAM::SetIsToSend(bool istosend)
* @brief      SetIsToSend
* @ingroup    DATAIO
*
* @param[in]  istosend :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMUDPDATAGRAM::SetIsToSend(bool istosend)
{
  this->istosend = istosend;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOSTREAMUDPDATAGRAM::GetAddress()
* @brief      GetAddress
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOSTREAMUDPDATAGRAM::GetAddress()
{
  return &address;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUDPDATAGRAM::SetAddress(XCHAR* address)
* @brief      SetAddress
* @ingroup    DATAIO
*
* @param[in]  address :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUDPDATAGRAM::SetAddress(XCHAR* address)
{
  if(!address) return false;

  this->address = address;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUDPDATAGRAM::SetAddress(XSTRING& address)
* @brief      SetAddress
* @ingroup    DATAIO
*
* @param[in]  address :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUDPDATAGRAM::SetAddress(XSTRING& address)
{
  return SetAddress(address.Get());
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWORD DIOSTREAMUDPDATAGRAM::GetPort()
* @brief      GetPort
* @ingroup    DATAIO
*
* @return     XWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XWORD DIOSTREAMUDPDATAGRAM::GetPort()
{
  return port;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMUDPDATAGRAM::SetPorts(XWORD port)
* @brief      SetPorts
* @ingroup    DATAIO
*
* @param[in]  port :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMUDPDATAGRAM::SetPorts(XWORD port)
{
  this->port = port;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBUFFER* DIOSTREAMUDPDATAGRAM::GetData()
* @brief      GetData
* @ingroup    DATAIO
*
* @return     XBUFFER* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XBUFFER* DIOSTREAMUDPDATAGRAM::GetData()
{
  return data;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUDPDATAGRAM::SetData(XBYTE* data,XDWORD size)
* @brief      SetData
* @ingroup    DATAIO
*
* @param[in]  data :
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUDPDATAGRAM::SetData(XBYTE* data,XDWORD size)
{
  if(!this->data) return false;

  this->data->Delete();
  this->data->Add(data,size);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMUDPDATAGRAM::SetData(XBUFFER& data)
* @brief      SetData
* @ingroup    DATAIO
*
* @param[in]  data :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMUDPDATAGRAM::SetData(XBUFFER& data)
{
  SetData(data.Get(), data.GetSize());
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMUDPDATAGRAM::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMUDPDATAGRAM::Clean()
{
  istosend = false;
  address.Empty();
  port     = 0;
  data     = NULL;
}



/*--------------------------------------------------------------------------------------------------------------------*/
/*  DIOSTREAMUDP                                                                                                      */
/*--------------------------------------------------------------------------------------------------------------------*/




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMUDP::DIOSTREAMUDP()
* @brief      Constructor
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMUDP::DIOSTREAMUDP() : DIOSTREAM()
{
  Clean();

  GEN_XFACTORY_CREATE(datagramsmutex, Create_Mutex())
  host           = new DIOURL();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMUDP::~DIOSTREAMUDP()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMUDP::~DIOSTREAMUDP()
{
  DeleteAllDatagrams();

  delete host;

  GEN_XFACTORY.Delete_Mutex(datagramsmutex);

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMCONFIG* DIOSTREAMUDP::GetConfig()
* @brief      GetConfig
* @ingroup    DATAIO
*
* @return     DIOSTREAMCONFIG* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMCONFIG* DIOSTREAMUDP::GetConfig()
{
  return config;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUDP::SetConfig(DIOSTREAMCONFIG* config)
* @brief      SetConfig
* @ingroup    DATAIO
*
* @param[in]  config :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUDP::SetConfig(DIOSTREAMCONFIG* config)
{
  if(!config) return false;
  this->config = (DIOSTREAMUDPCONFIG *)config;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUDP::Open()
* @brief      Open
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUDP::Open()
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUDP::ReadDatagram(XSTRING& address, XWORD& port, XBUFFER& xbuffer)
* @brief      ReadDatagram
* @ingroup    DATAIO
*
* @param[in]  address :
* @param[in]  port :
* @param[in]  xbuffer :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUDP::ReadDatagram(XSTRING& address, XWORD& port, XBUFFER& xbuffer)
{
  int index = GetFirstDatagram(false);
  if(index != DIOSTREAMUDP_NOTFOUND)
    {
      DIOSTREAMUDPDATAGRAM* datagram = GetDatagram(index);
      if(datagram)
        {
          address = datagram->GetAddress()->Get();
          port    = datagram->GetPort();

          xbuffer.Delete();
          xbuffer.Add(datagram->GetData());

          nbytesread+= datagram->GetData()->GetSize();
          if(xtimernotactivity) xtimernotactivity->Reset();

          DeleteDatagram(index);

          return true;
        }
    }

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUDP::WriteDatagram(XSTRING& address, XWORD port, XBYTE* buffer, XDWORD size)
* @brief      WriteDatagram
* @ingroup    DATAIO
*
* @param[in]  address :
* @param[in]  port :
* @param[in]  buffer :
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUDP::WriteDatagram(XSTRING& address, XWORD port, XBYTE* buffer, XDWORD size)
{
  if(address.IsEmpty())                                 return false;
  if(!AddDatagram(true, address , port, buffer, size))  return false;
  if(!outbuffer->Add(buffer,size))                      return false;

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUDP::WriteDatagram(XSTRING& address, XWORD port, XBUFFER& xbuffer)
* @brief      WriteDatagram
* @ingroup    DATAIO
*
* @param[in]  address :
* @param[in]  port :
* @param[in]  xbuffer :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUDP::WriteDatagram(XSTRING& address, XWORD port, XBUFFER& xbuffer)
{
  return WriteDatagram(address, port, xbuffer.Get(), xbuffer.GetSize());
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUDP::Disconnect()
* @brief      Disconnect
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUDP::Disconnect()
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUDP::Close()
* @brief      Close
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUDP::Close()
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUDP::ResetXBuffers()
* @brief      ResetXBuffers
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUDP::ResetXBuffers()
{
  if(!DIOSTREAM::ResetXBuffers()) return false;

  return DeleteAllDatagrams();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUDP::ResetInXBuffer()
* @brief      ResetInXBuffer
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUDP::ResetInXBuffer()
{
  if(!DIOSTREAM::ResetInXBuffer()) return false;

  int index = 0;

  while(1)
    {
      DIOSTREAMUDPDATAGRAM* datagram = (DIOSTREAMUDPDATAGRAM*)datagrams.Get(index);
      if(!datagram) break;

      if(datagram->GetAddress()->GetSize())
        {
          DeleteDatagram(index);

        } else index++;
    }


  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUDP::ResetOutXBuffer()
* @brief      ResetOutXBuffer
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUDP::ResetOutXBuffer()
{
  if(!DIOSTREAM::ResetOutXBuffer()) return false;

  int index = 0;

  while(1)
    {
      DIOSTREAMUDPDATAGRAM* datagram = (DIOSTREAMUDPDATAGRAM*)datagrams.Get(index);
      if(!datagram) break;

      if(!datagram->GetAddress()->GetSize())
        {
          DeleteDatagram(index);

        } else index++;
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOURL* DIOSTREAMUDP::GetHost()
* @brief      GetHost
* @ingroup    DATAIO
*
* @return     DIOURL* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOURL* DIOSTREAMUDP::GetHost()
{
  return host;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUDP::WaitToWriteDatagramsEmpty(int timeout)
* @brief      WaitToWriteDatagramsEmpty
* @ingroup    DATAIO
*
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUDP::WaitToWriteDatagramsEmpty(int timeout)
{
  if (!xtimerconnection) return false;

  int index;

  xtimerconnection->Reset();

  while(1)
    {
      index = GetFirstDatagram(true);
      if(index == DIOSTREAMUDP_NOTFOUND)
        {
          return true;
        }

      if((int)xtimerconnection->GetMeasureSeconds() >= timeout) break;

      Wait(DIOSTREAM_TIMEINWAITFUNCTIONS);
    }

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOSTREAMUDP::WaitToGetFirstDatagram(bool tosend, int timeout)
* @brief      WaitToGetFirstDatagram
* @ingroup    DATAIO
*
* @param[in]  tosend :
* @param[in]  timeout :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOSTREAMUDP::WaitToGetFirstDatagram(bool tosend, int timeout)
{
  if (!xtimerconnection) return false;

  int index;

  xtimerconnection->Reset();

  while(1)
    {
      index = GetFirstDatagram(tosend);
      if(index != DIOSTREAMUDP_NOTFOUND)
        {
          break;
        }

      if((int)xtimerconnection->GetMeasureSeconds() >= timeout) break;

      Wait(DIOSTREAM_TIMEINWAITFUNCTIONS);
    }

  return index;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XVECTOR<DIOSTREAMUDPDATAGRAM*>* DIOSTREAMUDP::GetDatagramsVector()
* @brief      GetDatagramsVector
* @ingroup    DATAIO
*
* @return     XVECTOR<DIOSTREAMUDPDATAGRAM*>* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<DIOSTREAMUDPDATAGRAM*>* DIOSTREAMUDP::GetDatagramsVector()
{
  return &datagrams;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMUDPDATAGRAM* DIOSTREAMUDP::GetDatagram(int index)
* @brief      GetDatagram
* @ingroup    DATAIO
*
* @param[in]  index :
*
* @return     DIOSTREAMUDPDATAGRAM* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMUDPDATAGRAM* DIOSTREAMUDP::GetDatagram(int index)
{
  if(datagramsmutex)  datagramsmutex->Lock();

  DIOSTREAMUDPDATAGRAM* datagram = datagrams.Get(index);

  if(datagramsmutex)  datagramsmutex->UnLock();

  return datagram;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUDP::DeleteDatagram(int index)
* @brief      DeleteDatagram
* @ingroup    DATAIO
*
* @param[in]  index :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUDP::DeleteDatagram(int index)
{
  if(datagramsmutex)  datagramsmutex->Lock();

  DIOSTREAMUDPDATAGRAM* datagram = (DIOSTREAMUDPDATAGRAM*)GetDatagram(index);
  if(datagram)
    {
      datagrams.DeleteIndex(index);
      delete datagram;
      datagram = NULL;
    }

  if(datagramsmutex)  datagramsmutex->UnLock();

  return datagram?true:false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUDP::DeleteAllDatagrams()
* @brief      DeleteAllDatagrams
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUDP::DeleteAllDatagrams()
{
  if(datagrams.IsEmpty()) return false;

  if(datagramsmutex)  datagramsmutex->Lock();

  datagrams.DeleteContents();

  datagrams.DeleteAll();

  if(datagramsmutex)  datagramsmutex->UnLock();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUDP::AddDatagram(bool istosend, XCHAR* address, XWORD port, XBYTE* data, XDWORD size)
* @brief      AddDatagram
* @ingroup    DATAIO
*
* @param[in]  istosend :
* @param[in]  address :
* @param[in]  port :
* @param[in]  data :
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUDP::AddDatagram(bool istosend, XCHAR* address, XWORD port, XBYTE* data, XDWORD size)
{
  if(!address) return false;
  if(!data)    return false;

  if(datagramsmutex)  datagramsmutex->Lock();

  DIOSTREAMUDPDATAGRAM* datagram = new DIOSTREAMUDPDATAGRAM();
  if(datagram)
    {
      datagram->SetIsToSend(istosend);
      datagram->SetAddress(address);
      datagram->SetPorts(port);
      datagram->SetData(data,size);

      datagrams.Add(datagram);
    }

  if(datagramsmutex)  datagramsmutex->UnLock();

  return datagram?true:false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUDP::AddDatagram(bool istosend, XSTRING& address, XWORD port, XBYTE* data,XDWORD size)
* @brief      AddDatagram
* @ingroup    DATAIO
*
* @param[in]  istosend :
* @param[in]  address :
* @param[in]  port :
* @param[in]  data :
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUDP::AddDatagram(bool istosend, XSTRING& address, XWORD port, XBYTE* data,XDWORD size)
{
  return AddDatagram(istosend, address.Get(), port, data, size);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOSTREAMUDP::GetFirstDatagram(bool tosend)
* @brief      GetFirstDatagram
* @ingroup    DATAIO
*
* @param[in]  tosend :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOSTREAMUDP::GetFirstDatagram(bool tosend)
{
  int index = DIOSTREAMUDP_NOTFOUND;

  if(datagramsmutex)  datagramsmutex->Lock();

  for(int c=0;c<(int)datagrams.GetSize();c++)
    {
      DIOSTREAMUDPDATAGRAM* datagram = (DIOSTREAMUDPDATAGRAM*)datagrams.Get(c);
      if(datagram)
        {
          if(datagram->IsToSend() == tosend)
            {
              index = c;
              break;
            }
        }
    }

  if(datagramsmutex)  datagramsmutex->UnLock();

  return index;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMUDP::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMUDP::Clean()
{
  config          = NULL;
  host            = NULL;
  datagramsmutex  = NULL;
}
