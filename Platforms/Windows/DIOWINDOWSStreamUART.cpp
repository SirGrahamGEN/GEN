//------------------------------------------------------------------------------------------
//  DIOWINDOWSSTREAMUART.CPP
//
//  WINDOWS Data Input/Output Stream UART class
//
//  Author            : Abraham J. Velez
//  Date Of Creation  : 02/01/2002
//  Last Mofificacion :
//
//  GEN  Copyright (C).  All right reserved.
//------------------------------------------------------------------------------------------


/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


#if defined(DIO_ACTIVE) && defined(DIOUART_ACTIVE)


//---- INCLUDES ----------------------------------------------------------------------------

#include "XFactory.h"
#include "XTimer.h"
#include "XString.h"
#include "XBuffer.h"
#include "XTrace.h"
#include "XThreadCollected.h"

#include "DIOStreamXEvent.h"

#include "DIOWINDOWSStreamUART.h"

#include "XMemory_Control.h"

//---- GENERAL VARIABLE --------------------------------------------------------------------


//---- CLASS MEMBERS -----------------------------------------------------------------------



/*-------------------------------------------------------------------
//  DIOWINDOWSSTREAMUART::DIOWINDOWSSTREAMUART
*/
/**
//
//
//  ""
//  @version      18/02/2013 7:47:09
//
//  @return       void :
*/
/*-----------------------------------------------------------------*/
DIOWINDOWSSTREAMUART::DIOWINDOWSSTREAMUART() : DIOSTREAMUART(), XFSMACHINE(0)
{
  Clean();

  AddState( DIOWINDOWSUARTFSMSTATE_NONE               ,
            DIOWINDOWSUARTFSMEVENT_CONNECTED            , DIOWINDOWSUARTFSMSTATE_CONNECTED         ,
            DIOWINDOWSUARTFSMEVENT_DISCONNECTING        , DIOWINDOWSUARTFSMSTATE_DISCONNECTING     ,
            XFSMACHINESTATE_EVENTDEFEND);

  AddState( DIOWINDOWSUARTFSMSTATE_CONNECTED            ,
            DIOWINDOWSUARTFSMEVENT_WAITINGTOREAD        , DIOWINDOWSUARTFSMSTATE_WAITINGTOREAD     ,
            DIOWINDOWSUARTFSMEVENT_DISCONNECTING        , DIOWINDOWSUARTFSMSTATE_DISCONNECTING     ,
            XFSMACHINESTATE_EVENTDEFEND);

  AddState( DIOWINDOWSUARTFSMSTATE_WAITINGTOREAD        ,
            DIOWINDOWSUARTFSMEVENT_CONNECTED            , DIOWINDOWSUARTFSMSTATE_CONNECTED         ,
            DIOWINDOWSUARTFSMEVENT_DISCONNECTING        , DIOWINDOWSUARTFSMSTATE_DISCONNECTING     ,
            XFSMACHINESTATE_EVENTDEFEND);

  AddState( DIOWINDOWSUARTFSMSTATE_DISCONNECTING        ,
            DIOWINDOWSUARTFSMEVENT_CONNECTED            , DIOWINDOWSUARTFSMSTATE_CONNECTED         ,
            DIOWINDOWSUARTFSMEVENT_WAITINGTOREAD        , DIOWINDOWSUARTFSMSTATE_WAITINGTOREAD     ,
            XFSMACHINESTATE_EVENTDEFEND);

  threadconnection = CREATEXTHREAD(XTHREADGROUPID_DIOSTREAMUART, __L("DIOWINDOWSSTREAMUART::DIOWINDOWSSTREAMUART"), ThreadConnection, (void*)this);
}




//-------------------------------------------------------------------
//  DIOWINDOWSSTREAMUART::~DIOWINDOWSSTREAMUART
/**
//
//
//  ""
//  @version      03/09/2001 16:58:17
//
//  @return
*/
//-------------------------------------------------------------------
DIOWINDOWSSTREAMUART::~DIOWINDOWSSTREAMUART()
{
  Close();

  if(threadconnection) DELETEXTHREAD(XTHREADGROUPID_DIOSTREAMUART, threadconnection);

  Clean();
}


//-------------------------------------------------------------------
//  DIOWINDOWSSTREAMUART::GetConnectStatus
/**
//
//
//  ""
//  @version      03/09/2001 16:58:17
//
//  @return       DIOSTREAMSTATUS :
*/
//-------------------------------------------------------------------
DIOSTREAMSTATUS DIOWINDOWSSTREAMUART::GetConnectStatus()
{
  if(hcom==INVALID_HANDLE_VALUE)  return DIOSTREAMSTATUS_DISCONNECTED;
  if(!config)                     return DIOSTREAMSTATUS_DISCONNECTED;

  return status;
}




//-------------------------------------------------------------------
//  DIOWINDOWSSTREAMUART::Open
/**
//
//
//  ""
//  @version      03/09/2001 16:58:17
//
//  @return       bool :
*/
//-------------------------------------------------------------------
bool DIOWINDOWSSTREAMUART::Open()
{
  if(!threadconnection)  return false;

  if(!inbuffer)         return false;
  if(!outbuffer)        return false;

  if(!config)           return false;

  XSTRING comport;
  XSTRING cfg;

  comport.Empty();

  if(!config->GetLocalDeviceName()->IsEmpty())
    {
      comport = config->GetLocalDeviceName()->Get();
    }
   else
    {
      comport.Format(__L("\\\\.\\COM%d"), config->GetPort());
    }

  hcom = CreateFile(comport.Get()                     ,
                    GENERIC_READ|GENERIC_WRITE        ,
                    0                                 ,
                    0                                 ,
                    OPEN_EXISTING                     ,
                    FILE_ATTRIBUTE_NORMAL             , // FILE_FLAG_OVERLAPPED
                    0);

  if(hcom==INVALID_HANDLE_VALUE) return false;

  if(!SetTimeouts())
    {
      Close();
      return false;
    }

// EV_ERR|EV_BREAK|EV_CTS|EV_DSR|EV_RING|EV_RLSD|EV_RXCHAR|EV_RXFLAG|EV_TXEMPTY

  if(!SetMask(EV_ERR|EV_RXCHAR|EV_TXEMPTY))
    {
      Close();
      return false;
    }

  if(!SetupComm(hcom, DIOSTREAM_MAXBUFFER, DIOSTREAM_MAXBUFFER))
    {
      Close();
      return false;
    }

  SetRTS(false);
  SetDTR(false);


  Config();

  /*
  if(!Config())
    {
      Close();
      return false;
    }
  */

  memset(&ovi,0,sizeof(ovi));

  SetEvent(DIOWINDOWSUARTFSMEVENT_CONNECTED);

  status = DIOSTREAMSTATUS_CONNECTED;

  ResetXBuffers();

  ResetConnectionStatistics();

  return threadconnection->Ini();
}



/*-------------------------------------------------------------------
//  DIOWINDOWSSTREAMUART::Config
*/
/**
//
//
//
//  ""
//  @version      24/09/2014 12:22:37
//
//  @return       bool :
//
*/
/*-----------------------------------------------------------------*/
bool DIOWINDOWSSTREAMUART::Config(XWORD mask)
{
  if(!config) return false;
  if(GetConnectStatus()==DIOSTREAMSTATUS_DISCONNECTED) return false;

  DCB dcb;

  if(!GetCommState(hcom, &dcb)) return false;

  if((mask&DIOSTREAMUARTMASK_BAUDRATE) == DIOSTREAMUARTMASK_BAUDRATE)  dcb.BaudRate = config->GetBaudRate();

  if((mask&DIOSTREAMUARTMASK_DATABITS ) == DIOSTREAMUARTMASK_DATABITS)
    {
      switch(config->GetDataBits())
        {
          case DIOSTREAMUARTDATABIT_5             :  dcb.ByteSize = 5;          break;
          case DIOSTREAMUARTDATABIT_6             :  dcb.ByteSize = 6;          break;
          case DIOSTREAMUARTDATABIT_7             :  dcb.ByteSize = 7;          break;
          case DIOSTREAMUARTDATABIT_8             :  dcb.ByteSize = 8;          break;
        }
    }

  if((mask&DIOSTREAMUARTMASK_PARITY) == DIOSTREAMUARTMASK_PARITY)
    {
      dcb.fParity = TRUE;

      switch(config->GetParity())
        {
          case DIOSTREAMUARTPARITY_NONE           :  dcb.Parity   = NOPARITY;
                                                     dcb.fParity  = FALSE;
                                                     break;
          case DIOSTREAMUARTPARITY_ODD            :  dcb.Parity   = ODDPARITY;    break;
          case DIOSTREAMUARTPARITY_EVEN           :  dcb.Parity   = EVENPARITY;   break;
          case DIOSTREAMUARTPARITY_MARK           :  dcb.Parity   = MARKPARITY;   break;
          case DIOSTREAMUARTPARITY_SPACE          :  dcb.Parity   = SPACEPARITY;  break;
        }
    }


  if((mask&DIOSTREAMUARTMASK_STOPBITS ) == DIOSTREAMUARTMASK_STOPBITS)
    {
      switch(config->GetStopBits())
        {
          case DIOSTREAMUARTSTOPBITS_ONE          :  dcb.StopBits =  ONESTOPBIT;   break;
          case DIOSTREAMUARTSTOPBITS_ONEANDAHALF  :
          case DIOSTREAMUARTSTOPBITS_TWO          :  dcb.StopBits =  TWOSTOPBITS;  break;
        }
    }

  if((mask&DIOSTREAMUARTMASK_FLOWCONTROL) == DIOSTREAMUARTMASK_FLOWCONTROL)
    {
      switch(config->GetFlowControl())
        {
          case DIOSTREAMUARTFLOWCONTROL_NONE      : dcb.fDtrControl       = DTR_CONTROL_DISABLE;
                                                    dcb.fRtsControl       = RTS_CONTROL_DISABLE;
                                                    break;

          case DIOSTREAMUARTFLOWCONTROL_HARD      : dcb.fDtrControl       = DTR_CONTROL_ENABLE;
                                                    dcb.fRtsControl       = RTS_CONTROL_ENABLE;
                                                    break;

          case DIOSTREAMUARTFLOWCONTROL_SOFT      : dcb.fDtrControl       = DTR_CONTROL_DISABLE;
                                                    dcb.fRtsControl       = RTS_CONTROL_DISABLE;
                                                    break;
        }
    }

  dcb.XonChar  = 1;
  dcb.XoffChar = 0;

  if(!SetCommState(hcom,&dcb)) return false;

  return true;
}




/*-------------------------------------------------------------------
//  DIOWINDOWSSTREAMUART::ReadDirect
*/
/**
//
//
//
//  ""
//  @version      24/06/2015 13:27:09
//
//  @return       XDWORD :
//
//  @param        buffer :
//  @param        size :
*/
/*-----------------------------------------------------------------*/
XDWORD DIOWINDOWSSTREAMUART::ReadDirect(XBYTE* buffer,XDWORD size)
{
  if(GetConnectStatus()==DIOSTREAMSTATUS_DISCONNECTED) return 0;
  if(size == 0)                                        return 0;

  DWORD br    = 0;
  bool status = true;

  if(!hevent)
    {
      hevent = CreateEvent(0,TRUE,FALSE,0);
      if(!hevent) return 0;

      ovi.hEvent = hevent;

      if(!ReadFile(hcom,buffer,size,&br,&ovi))
        {
          if(GetLastError()!=ERROR_IO_PENDING)
            {
              status = false;
            }
           else return ReadDirect(buffer, size);
        }
    }
   else
    {
      switch(WaitForSingleObject(ovi.hEvent,readtimeout))
        {
          case WAIT_OBJECT_0: if(!GetOverlappedResult(hcom,&ovi,&br,FALSE))
                                     status = false;
                                else status = true;
                              break;

          case WAIT_TIMEOUT : CancelIo(hcom);
                              status=false;
                              break;

                   default  : status=false;
                              break;

         }
     }

  memset(&ovi,0,sizeof(ovi));

  if(hevent)
    {
      CloseHandle(hevent);
      hevent = NULL;
    }

  if(!status) return 0;

  return (XDWORD)br;
}




/*-------------------------------------------------------------------
//  DIOWINDOWSSTREAMUART::WriteDirect
*/
/**
//
//
//
//  ""
//  @version      24/06/2015 13:26:58
//
//  @return       XDWORD :
//
//  @param        buffer :
//  @param        size :
*/
/*-----------------------------------------------------------------*/
XDWORD DIOWINDOWSSTREAMUART::WriteDirect(XBYTE* buffer, XDWORD size)
{
  if(GetConnectStatus()==DIOSTREAMSTATUS_DISCONNECTED) return 0;

  if(size == 0)    return 0;

  DWORD      bw         = 0;
  OVERLAPPED oviwrite   = { 0 };
  bool       status;

  oviwrite.hEvent = CreateEvent(0,TRUE,FALSE,0);
  if(!oviwrite.hEvent) return bw;

  if(!WriteFile(hcom,buffer,size,&bw,&oviwrite))
    {
      if(GetLastError()!=ERROR_IO_PENDING)
        {
          status = false;
        }
       else
        {
          switch(WaitForSingleObject(oviwrite.hEvent,writetimeout))
            {
              case WAIT_OBJECT_0 :  if(!GetOverlappedResult(hcom,&oviwrite,&bw,TRUE))
                                           status = false;
                                      else status = true;
                                    break;

              case WAIT_TIMEOUT  : CancelIo(hcom);
                                   status=false;
                                   break;

                       default   : status=false;
                                   break;

            }
        }

    } else status = true;

  CloseHandle(oviwrite.hEvent);

  if(!status) return 0;

  return (XDWORD)bw;
}





//-------------------------------------------------------------------
//  DIOWINDOWSSTREAMUART::Close
/**
//
//
//  ""
//  @version      03/09/2001 16:58:17
//
//  @return
*/
//-------------------------------------------------------------------
bool DIOWINDOWSSTREAMUART::Close()
{
  if(threadconnection) threadconnection->End();
  //if(GetConnectStatus()==DIOSTREAMSTATUS_DISCONNECTED) return false;

  if(hcom != INVALID_HANDLE_VALUE)
    {
      CloseHandle(hcom);
      hcom = INVALID_HANDLE_VALUE;
    }

  return true;
}


//-------------------------------------------------------------------
//  DIOWINDOWSSTREAMUART::GetCTS
/**
//
//
//  ""
//  @version      03/09/2001 16:58:17
//
//  @return       bool :
*/
//-------------------------------------------------------------------
bool DIOWINDOWSSTREAMUART::GetCTS()
{
  if(GetConnectStatus()==DIOSTREAMSTATUS_DISCONNECTED) return false;

  DWORD status = 0;
  if(!GetCommModemStatus(hcom,&status))
    {
      Close();
      return false;
    }

  return (status&MS_CTS_ON)!= 0;
}




//-------------------------------------------------------------------
//  DIOWINDOWSSTREAMUART::GetDSR
/**
//
//
//  ""
//  @version      03/09/2001 16:58:17
//
//  @return       bool :
*/
//-------------------------------------------------------------------
bool DIOWINDOWSSTREAMUART::GetDSR()
{
  if(GetConnectStatus()==DIOSTREAMSTATUS_DISCONNECTED) return false;

  DWORD status = 0;
  if(!GetCommModemStatus(hcom,&status))
    {
      Close();
      return false;
    }

  return (status&MS_DSR_ON)!= 0;
}



//-------------------------------------------------------------------
//  DIOWINDOWSSTREAMUART::GetRing
/**
//
//
//  ""
//  @version      03/09/2001 16:58:17
//
//  @return       bool :
*/
//-------------------------------------------------------------------
bool DIOWINDOWSSTREAMUART::GetRing()
{
  if(GetConnectStatus()==DIOSTREAMSTATUS_DISCONNECTED) return false;

  DWORD status = 0;
  if(!GetCommModemStatus(hcom,&status))
    {
      Close();
      return false;
    }

  return (status&MS_RING_ON)!= 0;
}


//-------------------------------------------------------------------
//  DIOWINDOWSSTREAMUART::GetRing
/**
//
//
//  ""
//  @version      03/09/2001 16:58:17
//
//  @return       bool :
*/
//-------------------------------------------------------------------
bool DIOWINDOWSSTREAMUART::GetRLSD()
{
  if(GetConnectStatus()==DIOSTREAMSTATUS_DISCONNECTED) return false;

  DWORD status = 0;
  if(!GetCommModemStatus(hcom,&status))
    {
      Close();
      return false;
    }

  return (status&MS_RLSD_ON)!= 0;
}




//-------------------------------------------------------------------
//  DIOWINDOWSSTREAMUART::SetRTS
/**
//
//
//  ""
//  @version      03/09/2001 16:58:17
//
//  @return       bool :
//  @param        on :
*/
//-------------------------------------------------------------------
bool DIOWINDOWSSTREAMUART::SetRTS(bool on)
{
  if(GetConnectStatus()==DIOSTREAMSTATUS_DISCONNECTED) return false;

  if(!EscapeCommFunction(hcom,on?SETRTS:CLRRTS)) return false;

  return true;
}


//-------------------------------------------------------------------
//  DIOWINDOWSSTREAMUART::SetDTR
/**
//
//
//  ""
//  @version      03/09/2001 16:58:17
//
//  @return       bool :
//  @param        on :
*/
//-------------------------------------------------------------------
bool DIOWINDOWSSTREAMUART::SetDTR(bool on)
{
  if(GetConnectStatus()==DIOSTREAMSTATUS_DISCONNECTED) return false;

  if(!EscapeCommFunction(hcom,on?SETDTR:CLRDTR)) return false;

  return true;
}



//-------------------------------------------------------------------
//  DIOWINDOWSSTREAMUART::CleanBuffers
/**
//
//
//  ""
//  @version      03/09/2001 16:58:17
//
//  @return
*/
//-------------------------------------------------------------------
bool DIOWINDOWSSTREAMUART::CleanBuffers()
{
  if(GetConnectStatus()==DIOSTREAMSTATUS_DISCONNECTED) return false;

  if(!PurgeComm(hcom,PURGE_TXCLEAR|PURGE_RXCLEAR)) return false;

  DWORD error;

  if(!ClearCommError(hcom,&error,NULL)) return false;

  return true;
}


//-------------------------------------------------------------------
//  DIOWINDOWSSTREAMUART::Clean
/**
//
//
//  ""
//  @version      03/09/2001 16:58:17
//
//  @return
*/
//-------------------------------------------------------------------
void DIOWINDOWSSTREAMUART::Clean()
{
  threadconnection = NULL;

  hcom            = INVALID_HANDLE_VALUE;
  hevent          = NULL;

  memset(&ovi,0,sizeof(ovi));

  readtimeout  = 3000;
  writetimeout = 3000;
}





//-------------------------------------------------------------------
//  DIOWINDOWSSTREAMUART::SetMask
/**
//
//
//  ""
//  @version      03/09/2001 16:58:17
//
//  @return       bool :
//  @param        mask :
*/
//-------------------------------------------------------------------
bool DIOWINDOWSSTREAMUART::SetMask(XDWORD mask)
{
  if(GetConnectStatus()==DIOSTREAMSTATUS_DISCONNECTED) return false;

  if(!SetCommMask(hcom,mask))
    {
      Close();
      return false;
    }

  this->mask = mask;

  return true;
}



//-------------------------------------------------------------------
//  DIOWINDOWSSTREAMUART::SetReadouts
/**
//
//
//  ""
//  @version      03/09/2001 16:58:17
//
//  @return       bool :
//  @param        type :
*/
//-------------------------------------------------------------------
bool DIOWINDOWSSTREAMUART::SetTimeouts()
{
  if(GetConnectStatus()==DIOSTREAMSTATUS_DISCONNECTED) return false;

  COMMTIMEOUTS to;

  to.ReadIntervalTimeout          = MAXDWORD;
  to.ReadTotalTimeoutMultiplier   = 0;
  to.ReadTotalTimeoutConstant     = 0;
  to.WriteTotalTimeoutMultiplier  = 0;
  to.WriteTotalTimeoutConstant    = 0;

  /*
  to.ReadIntervalTimeout         = 20;
  to.ReadTotalTimeoutMultiplier  = 0;
  to.ReadTotalTimeoutConstant    = 2000;
  to.WriteTotalTimeoutMultiplier = 1;
  to.WriteTotalTimeoutConstant   = 2000;
  */

  if(!SetCommTimeouts(hcom,&to))
    {
      Close();
      return false;
    }

  return true;
}




/*-------------------------------------------------------------------
//  DIOWINDOWSSTREAMUART::ThreadConnection
*/
/**
//
//
//  ""
//  @version      25/07/2012 13:56:19
//
//  @return       void :
//  @param        data :
*/
/*-----------------------------------------------------------------*/
void DIOWINDOWSSTREAMUART::ThreadConnection(void* data)
{
  DIOWINDOWSSTREAMUART* diostream = (DIOWINDOWSSTREAMUART*)data;
  if(!diostream) return;

  if(diostream->GetEvent()==DIOWINDOWSUARTFSMEVENT_NONE) // No hay nuevos Eventos
    {
      switch(diostream->GetCurrentState())
        {
          case DIOWINDOWSUARTFSMSTATE_NONE                  : break;

          case DIOWINDOWSUARTFSMSTATE_CONNECTED             : break;

          case DIOWINDOWSUARTFSMSTATE_WAITINGTOREAD         : { if(!diostream->IsBlockRead())
                                                                  {
                                                                    XBYTE buffer[DIOSTREAM_MAXBUFFER];

                                                                    XDWORD br = diostream->ReadDirect(buffer, DIOSTREAM_MAXBUFFER);
                                                                    if(br)
                                                                      {
                                                                        //XTRACE_PRINTDATABLOCK(XDEBUGLEVELCOLOR(2), (XBYTE*)diostream->buffer, (int)br);
                                                                        diostream->inbuffer->Add(buffer, br);
                                                                      }
                                                                  }

                                                                if(!diostream->IsBlockWrite())
                                                                  {
                                                                    int esize = diostream->outbuffer->GetSize();
                                                                    if(esize)
                                                                      {
                                                                        diostream->outbuffer->SetBlocked(true);
                                                                        XDWORD bw = diostream->WriteDirect(diostream->outbuffer->Get(), esize);
                                                                        diostream->outbuffer->SetBlocked(false);

                                                                        if(bw) diostream->outbuffer->Extract(NULL, 0, bw);

                                                                      }
                                                                  }
                                                              }
                                                              break;

          case DIOWINDOWSUARTFSMSTATE_DISCONNECTING         : break;

        }
    }
   else
    {
      if(diostream->GetEvent()<DIOWINDOWSUART_LASTEVENT)
        {
          diostream->CheckTransition();

          switch(diostream->GetCurrentState())
            {
              case DIOWINDOWSUARTFSMSTATE_NONE              : break;

              case DIOWINDOWSUARTFSMSTATE_CONNECTED         : { DIOSTREAMXEVENT xevent(diostream,DIOSTREAMXEVENT_TYPE_CONNECTED);
                                                                xevent.SetDIOStream(diostream);
                                                                diostream->PostEvent(&xevent);

                                                                diostream->SetEvent(DIOWINDOWSUARTFSMEVENT_WAITINGTOREAD);
                                                              }
                                                              break;

              case DIOWINDOWSUARTFSMSTATE_WAITINGTOREAD     : break;

              case DIOWINDOWSUARTFSMSTATE_DISCONNECTING     : { DIOSTREAMXEVENT xevent(diostream,DIOSTREAMXEVENT_TYPE_DISCONNECTED);
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

