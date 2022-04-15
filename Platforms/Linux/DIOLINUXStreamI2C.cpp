//------------------------------------------------------------------------------------------
//  DIOLINUXSTREAMI2C.CPP
//
//  LINUX Data Input/Output Stream I2C class
//
//
//  ""
//  @version 12/3/2003
//
//  GEN  Copyright (C).  All right reserved.
//------------------------------------------------------------------------------------------


/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


#if defined(DIO_ACTIVE) && defined(DIOI2C_ACTIVE)

//---- INCLUDES ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <getopt.h>
#include <linux/types.h>


#include "XFactory.h"
#include "XBuffer.h"
#include "XThreadCollected.h"
#include "XSystem.h"
#include "XTrace.h"

#include "DIOFactory.h"
#include "DIOStreamXEvent.h"
#include "DIOStreamI2CConfig.h"

#include "DIOLINUXStreamI2C.h"

#include "XMemory_Control.h"

//---- GENERAL VARIABLE --------------------------------------------------------------------



/*-------------------------------------------------------------------
//  DIOLINUXSTREAMI2C::DIOLINUXSTREAMI2C
*/
/**
//
//
//  ""
//  @version      18/02/2013 7:51:23
//
//  @return



*/
/*-----------------------------------------------------------------*/
DIOLINUXSTREAMI2C::DIOLINUXSTREAMI2C() : DIOSTREAMI2C()
{
  Clean();

  threadconnection = CREATEXTHREAD(XTHREADGROUPID_DIOSTREAMI2C, __L("DIOLINUXSTREAMI2C::DIOLINUXSTREAMI2C"), ThreadConnection, (void*)this);
}




//-------------------------------------------------------------------
//  DIOLINUXSTREAMI2C::~DIOLINUXSTREAMI2C
/**
//
//
//  ""
//  @version      20/11/2003 10:19:33
//
//  @return
//  */
//-------------------------------------------------------------------
DIOLINUXSTREAMI2C::~DIOLINUXSTREAMI2C()
{
  if(threadconnection)
    {
      threadconnection->End();
      DELETEXTHREAD(XTHREADGROUPID_DIOSTREAMI2C, threadconnection);
      threadconnection = NULL;
    }

  Clean();
}





/*-------------------------------------------------------------------
//  DIOLINUXSTREAMI2C::Open
*/
/**
//
//
//  ""
//  @version      07/10/2012 10:03:42
//
//  @return       bool :
//  */
/*-----------------------------------------------------------------*/
bool DIOLINUXSTREAMI2C::Open()
{
  if(!config) return false;

  if(!threadconnection)  return false;

  XSTRING_CREATEOEM((*config->GetLocalDeviceName()), charOEM)
  handle = open(charOEM, O_RDWR);
  XSTRING_DELETEOEM((*config->GetLocalDeviceName()), charOEM)
  if(handle<0) return false;

  switch(config->GetAddressSize())
    {
      case DIOSTREAMI2CCONFIG_ADDRESSSIZE_DEFAULT :
      case DIOSTREAMI2CCONFIG_ADDRESSSIZE_7BITS   : break;
      case DIOSTREAMI2CCONFIG_ADDRESSSIZE_10BITS  : if(ioctl(handle, DIOLINUXSTREAMI2C_TENBIT, 1) < 0)  return false;
                                                    break;
    }

  if(ioctl(handle, DIOLINUXSTREAMI2C_SLAVE , config->GetRemoteAddress()) < 0)                 return false;

  SetEvent(DIOSTREAMI2C_FSMEVENT_CONNECTED);

  status = DIOSTREAMSTATUS_CONNECTED;

  ResetXBuffers();
  ResetConnectionStatistics();

  return threadconnection->Ini();
}




/*-------------------------------------------------------------------
//  DIOLINUXSTREAMI2C::WaitToFilledReadingBuffer
*/
/**
//
//
//
//  ""
//  @version      09/06/2014 23:37:38
//
//  @return       bool :
//
//  @param        DIOSTREAM_SOMETHINGTOREAD :
//  @param        XTIMER_INFINITE :
*/
/*-----------------------------------------------------------------*/
bool DIOLINUXSTREAMI2C::WaitToFilledReadingBuffer(int filledto, int timeout)
{
  if(filledto == DIOSTREAM_SOMETHINGTOREAD) sizeread = 1; else sizeread = filledto;

  bool status = DIOSTREAM::WaitToFilledReadingBuffer(sizeread, timeout);

  return status;
}




/*-------------------------------------------------------------------
//  DIOLINUXSTREAMI2C::ReadDirect
*/
/**
//
//
//
//  ""
//  @version      15/09/2016 13:23:30
//
//  @return       XDWORD :
//
//  @param        buffer :
//  @param        size :
*/
/*-----------------------------------------------------------------*/
XDWORD DIOLINUXSTREAMI2C::ReadDirect(XBYTE* buffer, XDWORD size)
{
  if(!config) return false;

  DIOLINUXSTREAMI2C_RDWR_IOCTL_TICKET   msg_rdwr;
  DIOLINUXSTREAMI2C_MSG               msg;

  msg.addr        = config->GetRemoteAddress();
  msg.flags       = DIOLINUXSTREAMI2C_MSG_RD;
  msg.buffer      = buffer;
  msg.size        = size;

  msg_rdwr.msgs   = &msg;
  msg_rdwr.nmsgs  = 1;

  XDWORD br = 0;
  bool status = (ioctl(handle, DIOLINUXSTREAMI2C_RDWR, &msg_rdwr) < 0) ? false:true;
  if(status) br = size;

  //XTRACE_PRINTCOLOR(1, __L("Write [Addr %04X, size:%d]  status: %s"), address, size, status?__L("true"):__L("false"));

  return br;
}






/*-------------------------------------------------------------------
//  DIOLINUXSTREAMI2C::WriteDirect
*/
/**
//
//
//
//  ""
//  @version      15/09/2016 13:23:44
//
//  @return       XDWORD :
//
//  @param        buffer :
//  @param        size :
*/
/*-----------------------------------------------------------------*/
XDWORD DIOLINUXSTREAMI2C::WriteDirect(XBYTE* buffer, XDWORD size)
{
  if(!config) return false;

  DIOLINUXSTREAMI2C_RDWR_IOCTL_TICKET   msg_rdwr;
  DIOLINUXSTREAMI2C_MSG               msg;

  msg.addr        = config->GetRemoteAddress();
  msg.flags       = 0;
  msg.buffer      = buffer;
  msg.size        = size;

  msg_rdwr.msgs   = &msg;
  msg_rdwr.nmsgs  = 1;

  XDWORD bw = 0;

  bool status = (ioctl(handle, DIOLINUXSTREAMI2C_RDWR, &msg_rdwr) < 0) ? false:true;

  if(status) bw = size;

  //XTRACE_PRINTCOLOR(1, __L("Write [Addr %04X, size:%d]  status: %s"), address, size, status?__L("true"):__L("false"));

  return bw;

}



/*-------------------------------------------------------------------
//  DIOLINUXSTREAMI2C::Close
*/
/**
//
//
//  ""
//  @version      07/10/2012 10:03:47
//
//  @return       bool :
//  */
/*-----------------------------------------------------------------*/
bool DIOLINUXSTREAMI2C::Close()
{
  if(!threadconnection) return false;

  threadconnection->End();

  if(handle>=0)
    {
      close(handle);
      handle  = -1;
    }


  return true;
}



/*-------------------------------------------------------------------
//  DIOLINUXSTREAMI2C::Clean
*/
/**
//
//
//
//  ""
//  @version      26/04/2014 21:05:24
//
*/
/*-----------------------------------------------------------------*/
void DIOLINUXSTREAMI2C::Clean()
{
  handle   = -1;
  sizeread = 0;
}



/*-------------------------------------------------------------------
//  DIOLINUXSTREAMI2C::ThreadConnection
*/
/**
//
//
//  ""
//  @version      22/09/2012 16:59:27
//
//  @return       void :
//  @param        data :
*/
/*-----------------------------------------------------------------*/
void DIOLINUXSTREAMI2C::ThreadConnection(void* data)
{
  DIOLINUXSTREAMI2C* diostream = (DIOLINUXSTREAMI2C*)data;
  if(!diostream) return;

  if(diostream->GetEvent()==DIOSTREAMI2C_FSMEVENT_NONE) // No hay nuevos Eventos
    {
      switch(diostream->GetCurrentState())
        {
          case DIOSTREAMI2C_FSMSTATE_NONE                     : break;

          case DIOSTREAMI2C_FSMSTATE_CONNECTED                : break;

          case DIOSTREAMI2C_FSMSTATE_WAITINGTOREAD            : {
                                                                  if(!diostream->IsBlockWrite())
                                                                    {
                                                                      XDWORD size  = diostream->outbuffer->GetSize();
                                                                      if(size)
                                                                        {
                                                                          diostream->outbuffer->SetBlocked(true);
                                                                          XDWORD bw = diostream->WriteDirect(diostream->outbuffer->Get(), size);
                                                                          diostream->outbuffer->SetBlocked(false);

                                                                          if(bw)
                                                                            {
                                                                              //XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLORRED, diostream->outbuffer->Get(), size);
                                                                              diostream->outbuffer->Extract(NULL, 0 , bw);
                                                                            }
                                                                        }
                                                                    }


                                                                  if(!diostream->IsBlockRead())
                                                                    {
                                                                      if(diostream->sizeread)
                                                                        {
                                                                          XBYTE* _data = new XBYTE[diostream->sizeread];
                                                                          if(_data)
                                                                            {
                                                                              if(diostream->ReadDirect(_data, diostream->sizeread))
                                                                                {
                                                                                  //XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLORGREEN, _data, diostream->sizeread);
                                                                                  diostream->inbuffer->Add(_data, diostream->sizeread);
                                                                                  diostream->sizeread = 0;
                                                                                }

                                                                              delete [] _data;
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                                break;


          case DIOSTREAMI2C_FSMSTATE_SENDINGDATA              : break;

          case DIOSTREAMI2C_FSMSTATE_DISCONNECTING            : break;

        }
    }
   else
    {
      if(diostream->GetEvent()<DIOSTREAMI2C_LASTEVENT)
        {
          diostream->CheckTransition();

          switch(diostream->GetCurrentState())
            {
              case DIOSTREAMI2C_FSMSTATE_NONE                 : break;

              case DIOSTREAMI2C_FSMSTATE_CONNECTED            : { DIOSTREAMXEVENT xevent(diostream,DIOSTREAMXEVENT_TYPE_CONNECTED);
                                                                  xevent.SetDIOStream(diostream);
                                                                  diostream->PostEvent(&xevent);

                                                                  diostream->SetEvent(DIOSTREAMI2C_FSMEVENT_WAITINGTOREAD);
                                                                }
                                                                break;

              case DIOSTREAMI2C_FSMSTATE_WAITINGTOREAD        : break;

              case DIOSTREAMI2C_FSMSTATE_SENDINGDATA          : break;

              case DIOSTREAMI2C_FSMSTATE_DISCONNECTING        : { DIOSTREAMXEVENT xevent(diostream,DIOSTREAMXEVENT_TYPE_DISCONNECTED);
                                                                  xevent.SetDIOStream(diostream);
                                                                  diostream->PostEvent(&xevent);

                                                                  diostream->threadconnection->Run(false);
                                                                  diostream->status       = DIOSTREAMSTATUS_DISCONNECTED;
                                                                }
                                                                break;
            }
        }
    }
}






#endif
