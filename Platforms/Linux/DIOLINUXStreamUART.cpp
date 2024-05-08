/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOLINUXStreamUART.cpp
* 
* @class      DIOLINUXSTREAMUART
* @brief      LINUX Data Input/Output Stream UART class
* @ingroup    PLATFORM_LINUX
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
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


#if defined(DIO_ACTIVE) && defined(DIO_STREAMUART_ACTIVE)


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <signal.h>
#include <iostream>
#include <errno.h>
#include <termios.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/wait.h>

#include "DIOLINUXStreamUART.h"

#include "XBase.h"
#include "XFactory.h"
#include "XString.h"
#include "XTrace.h"
#include "XThreadCollected.h"

#include "DIOStreamXEvent.h"
#include "DIOStreamUARTConfig.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOLINUXSTREAMUART::DIOLINUXSTREAMUART()
* @brief      Constructor
* @ingroup    PLATFORM_LINUX
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOLINUXSTREAMUART::DIOLINUXSTREAMUART() : DIOSTREAMUART() , XFSMACHINE(0)
{
  Clean();

  AddState( DIOLINUXUARTFSMSTATE_NONE             ,
            DIOLINUXUARTFSMEVENT_CONNECTED        , DIOLINUXUARTFSMSTATE_CONNECTED         ,
            DIOLINUXUARTFSMEVENT_DISCONNECTING    , DIOLINUXUARTFSMSTATE_DISCONNECTING     ,
            XFSMACHINESTATE_EVENTDEFEND);

  AddState( DIOLINUXUARTFSMSTATE_CONNECTED        ,
            DIOLINUXUARTFSMEVENT_WAITINGTOREAD    , DIOLINUXUARTFSMSTATE_WAITINGTOREAD     ,
            DIOLINUXUARTFSMEVENT_DISCONNECTING    , DIOLINUXUARTFSMSTATE_DISCONNECTING     ,
            XFSMACHINESTATE_EVENTDEFEND);

  AddState( DIOLINUXUARTFSMSTATE_WAITINGTOREAD    ,
            DIOLINUXUARTFSMEVENT_CONNECTED        , DIOLINUXUARTFSMSTATE_CONNECTED         ,
            DIOLINUXUARTFSMEVENT_DISCONNECTING    , DIOLINUXUARTFSMSTATE_DISCONNECTING     ,
            XFSMACHINESTATE_EVENTDEFEND);

  AddState( DIOLINUXUARTFSMSTATE_DISCONNECTING    ,
            DIOLINUXUARTFSMEVENT_CONNECTED        , DIOLINUXUARTFSMSTATE_CONNECTED         ,
            DIOLINUXUARTFSMEVENT_WAITINGTOREAD    , DIOLINUXUARTFSMSTATE_WAITINGTOREAD     ,
            XFSMACHINESTATE_EVENTDEFEND);

  threadconnection = CREATEXTHREAD(XTHREADGROUPID_DIOSTREAMUART, __L("DIOLINUXSTREAMUART::DIOLINUXSTREAMUART"), ThreadConnection, (void*)this);

  //threadconnection->SetPriority(THREADPRIORITY_REALTIME);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOLINUXSTREAMUART::~DIOLINUXSTREAMUART()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_LINUX
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOLINUXSTREAMUART::~DIOLINUXSTREAMUART()
{
  Close();

  if(threadconnection) DELETEXTHREAD(XTHREADGROUPID_DIOSTREAMUART, threadconnection);

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOSTREAMSTATUS DIOLINUXSTREAMUART::GetConnectStatus()
* @brief      GetConnectStatus
* @ingroup    PLATFORM_LINUX
* 
* @return     DIOSTREAMSTATUS : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMSTATUS DIOLINUXSTREAMUART::GetConnectStatus()
{
  if(fd<0)    return DIOSTREAMSTATUS_DISCONNECTED;
  if(!config) return DIOSTREAMSTATUS_DISCONNECTED;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOLINUXSTREAMUART::Open()
* @brief      Open
* @ingroup    PLATFORM_LINUX
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXSTREAMUART::Open()
{
  if(!config) return false;

  XSTRING ttyS;

  if(!config->GetLocalDeviceName()->IsEmpty())
    {
      ttyS = config->GetLocalDeviceName()->Get();
    }
   else
    {
      ttyS.Format(__L("/dev/ttyS%d"),config->GetPort());
    }

  XBUFFER charstr;
  
  ttyS.ConvertToASCII(charstr);  
  fd= open(charstr.GetPtrChar(), O_RDWR | O_NOCTTY | O_NONBLOCK);  
  if(fd<0) return false;

  SetRTS(false);
  SetDTR(false);

  CleanBuffers();

  #ifdef LINUX
  fcntl(fd, F_SETFL, FNDELAY);
  #else
  fcntl(fd, F_SETFL, O_NONBLOCK);
  #endif

  Config();

  SetEvent(DIOLINUXUARTFSMEVENT_CONNECTED);

  status = DIOSTREAMSTATUS_CONNECTED;

  ResetXBuffers();
  ResetConnectionStatistics();

  return threadconnection->Ini();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOLINUXSTREAMUART::Config(XWORD mask)
* @brief      Config
* @ingroup    PLATFORM_LINUX
* 
* @param[in]  mask : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXSTREAMUART::Config(XWORD mask)
{
  if(fd<0) return false;

  struct termios cfg;
  speed_t        speed;

  tcgetattr(fd, &cfg);      // save current port settings

  if((mask&DIOSTREAMUARTMASK_BAUDRATE) == DIOSTREAMUARTMASK_BAUDRATE)
    {
      switch(this->config->GetBaudRate())
        {
          case 50     : speed = B50;        break;
          case 300    : speed = B300;       break;
          case 600    : speed = B600;       break;
          case 1200   : speed = B1200;      break;
          case 4800   : speed = B4800;      break;
          case 9600   : speed = B9600;      break;
          case 19200  : speed = B19200;     break;
          case 38400  : speed = B38400;     break;
          case 57600  : speed = B57600;     break;
          case 115200 : speed = B115200;    break;
        }

      cfsetispeed(&cfg, speed);
      cfsetospeed(&cfg, speed);
    }

  if((mask&DIOSTREAMUARTMASK_DATABITS ) == DIOSTREAMUARTMASK_DATABITS)
    {
      cfg.c_cflag&= ~CSIZE;

      switch(this->config->GetDataBits())
        {
          case DIOSTREAMUARTDATABIT_5           : cfg.c_cflag|= CS5; break;
          case DIOSTREAMUARTDATABIT_6           : cfg.c_cflag|= CS6; break;
          case DIOSTREAMUARTDATABIT_7           : cfg.c_cflag|= CS7; break;
          case DIOSTREAMUARTDATABIT_8           : cfg.c_cflag|= CS8; break;
        }
    }

  if((mask&DIOSTREAMUARTMASK_PARITY) == DIOSTREAMUARTMASK_PARITY)
    {
      cfg.c_iflag  = (IGNBRK| IGNPAR);

      #ifdef CMSPAR
      cfg.c_cflag &= ~CMSPAR;
      #endif
      cfg.c_cflag &= ~PARENB;
      cfg.c_cflag &= ~PARODD;

      switch(this->config->GetParity())
        {
          case DIOSTREAMUARTPARITY_NONE         :
                                                  #ifdef CMSPAR
                                                  cfg.c_cflag &= ~CMSPAR;
                                                  #endif
                                                  cfg.c_cflag &= ~PARENB;
                                                  cfg.c_cflag &= ~PARODD;
                                                  break;
          #ifdef CMSPAR
          case DIOSTREAMUARTPARITY_MARK         : cfg.c_cflag |= CMSPAR;       // Not available on many systems.
          #endif

          case DIOSTREAMUARTPARITY_ODD          : cfg.c_cflag |= PARENB;
                                                  cfg.c_cflag |= PARODD;
                                                  break;
          #ifdef CMSPAR
          case DIOSTREAMUARTPARITY_SPACE        : cfg.c_cflag |= CMSPAR;      // Not available on many systems.
          #endif

          case DIOSTREAMUARTPARITY_EVEN         : cfg.c_cflag |= PARENB;
                                                  cfg.c_cflag &= ~PARODD;
                                                  break;
        }
    }

  if((mask&DIOSTREAMUARTMASK_STOPBITS ) == DIOSTREAMUARTMASK_STOPBITS)
    {
      cfg.c_cflag &= ~CSTOPB;

      switch(this->config->GetStopBits())
        {
          case DIOSTREAMUARTSTOPBITS_ONE          : cfg.c_cflag &= ~CSTOPB;   break;
          case DIOSTREAMUARTSTOPBITS_ONEANDAHALF  :
          case DIOSTREAMUARTSTOPBITS_TWO          : cfg.c_cflag |=  CSTOPB;   break;
        }
    }

  if((mask&DIOSTREAMUARTMASK_FLOWCONTROL) == DIOSTREAMUARTMASK_FLOWCONTROL)
    {
      switch(config->GetFlowControl())
        {
          case DIOSTREAMUARTFLOWCONTROL_NONE    : cfg.c_cflag &= ~CRTSCTS;
                                                  cfg.c_iflag &= ~(IXON | IXOFF | IXANY);
                                                  break;

          case DIOSTREAMUARTFLOWCONTROL_HARD    : cfg.c_cflag |=  CRTSCTS;
                                                  cfg.c_iflag &= ~(IXON | IXOFF | IXANY);
                                                  break;

          case DIOSTREAMUARTFLOWCONTROL_SOFT    : cfg.c_cflag &= ~CRTSCTS;
                                                  cfg.c_iflag |= (IXON | IXOFF | IXANY);
                                                  break;
        }
    }

  if((mask&DIOSTREAMUARTMASK_ALL) == DIOSTREAMUARTMASK_ALL)
    {

      cfg.c_cflag |= (CLOCAL | CREAD);

      cfg.c_oflag &= ~OPOST;
      cfg.c_lflag &= ~(ICANON | ECHO | ISIG);


      cfg.c_cc[VMIN]  = 0;      // 0 means use-vtime
      cfg.c_cc[VTIME] = 1;      // time to wait until
    }

  tcsetattr(fd, TCSANOW, &cfg);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIOLINUXSTREAMUART::ReadDirect(XBYTE* buffer, XDWORD size)
* @brief      ReadDirect
* @ingroup    PLATFORM_LINUX
* 
* @param[in]  buffer : 
* @param[in]  size : 
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOLINUXSTREAMUART::ReadDirect(XBYTE* buffer, XDWORD size)
{
  if(fd<0)                                             return 0;
  if(GetConnectStatus()==DIOSTREAMSTATUS_DISCONNECTED) return 0;

  fd_set         fds;
  struct timeval tv;

  tv.tv_sec  = 0;
  tv.tv_usec = readtimeout;

  FD_ZERO(&fds);
  FD_SET(fd, &fds);

  int br = 0;

  if(select(fd+1, &fds, NULL, NULL, &tv) > 0)
    {
      br = read(fd, buffer, size);

      if(br< 0)
        {
          /*
          if(errno == EAGAIN)
            {

            }
          else
            {
              return 0;
            }
          */

          return 0;
        }
    }

  return (XDWORD)br;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIOLINUXSTREAMUART::WriteDirect(XBYTE* buffer, XDWORD size)
* @brief      WriteDirect
* @ingroup    PLATFORM_LINUX
* 
* @param[in]  buffer : 
* @param[in]  size : 
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOLINUXSTREAMUART::WriteDirect(XBYTE* buffer, XDWORD size)
{
  if(fd<0)                                             return 0;
  if(GetConnectStatus()==DIOSTREAMSTATUS_DISCONNECTED) return 0;

  fd_set         fds;
  struct timeval tv;

  tv.tv_sec  = 0;
  tv.tv_usec = writetimeout;

  FD_ZERO(&fds);
  FD_SET(fd, &fds);

  int bw = 0;

  if(select(fd+1, NULL , &fds, NULL, &tv) > 0)
    {
      bw = write(fd, buffer, size);
      if(bw<0) return 0;
    }

  return (XDWORD)bw;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOLINUXSTREAMUART::Close()
* @brief      Close
* @ingroup    PLATFORM_LINUX
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXSTREAMUART::Close()
{
  if(threadconnection) threadconnection->End();
  //if(GetConnectStatus()==DIOSTREAMSTATUS_DISCONNECTED) return false;

  if(fd != -1)
    {
      close(fd);
      fd = -1;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOLINUXSTREAMUART::GetCTS()
* @brief      GetCTS
* @ingroup    PLATFORM_LINUX
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXSTREAMUART::GetCTS()
{
  if(fd<0) return false;

  int _status;

  ioctl(fd, TIOCMGET, &_status);

  return ((_status & TIOCM_CTS) != 0);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOLINUXSTREAMUART::GetDSR()
* @brief      GetDSR
* @ingroup    PLATFORM_LINUX
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXSTREAMUART::GetDSR()
{
  if(fd<0) return false;

  int _status;

  ioctl(fd, TIOCMGET, &_status);

  return ((_status & TIOCM_DSR) != 0);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOLINUXSTREAMUART::GetRing()
* @brief      GetRing
* @ingroup    PLATFORM_LINUX
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXSTREAMUART::GetRing()
{
  if(fd<0) return false;

  int _status;

  ioctl(fd, TIOCMGET, &_status);

  return ((_status & TIOCM_RNG) != 0);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOLINUXSTREAMUART::GetRLSD()
* @brief      GetRLSD
* @ingroup    PLATFORM_LINUX
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXSTREAMUART::GetRLSD()
{
  if(fd<0) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOLINUXSTREAMUART::SetRTS(bool on)
* @brief      SetRTS
* @ingroup    PLATFORM_LINUX
* 
* @param[in]  on : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXSTREAMUART::SetRTS(bool on)
{
  if(fd<0) return false;

  int _status;

  ioctl(fd, TIOCMGET, &_status); // get the serial port status

  if(on) _status &= ~TIOCM_RTS; else _status |= TIOCM_RTS;

  ioctl(fd, TIOCMSET, &_status); // set the serial port status

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOLINUXSTREAMUART::SetDTR(bool on)
* @brief      SetDTR
* @ingroup    PLATFORM_LINUX
* 
* @param[in]  on : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXSTREAMUART::SetDTR(bool on)
{
  if(fd<0) return false;

  int _status;

  ioctl(fd, TIOCMGET, &_status);  // get the serial port status

  if(on) _status &= ~TIOCM_DTR; else  _status |= TIOCM_DTR;

  ioctl(fd, TIOCMSET, &_status);  // set the serial port status

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOLINUXSTREAMUART::CleanBuffers()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_LINUX
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOLINUXSTREAMUART::CleanBuffers()
{
  if(fd<0) return false;

  tcflush(fd, TCIOFLUSH);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOLINUXSTREAMUART::ThreadConnection(void* param)
* @brief      ThreadConnection
* @ingroup    PLATFORM_LINUX
* 
* @param[in]  param : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOLINUXSTREAMUART::ThreadConnection(void* param)
{
  DIOLINUXSTREAMUART* diostream = (DIOLINUXSTREAMUART*)param;
  if(!diostream) return;

  if(diostream->GetEvent()==DIOLINUXUARTFSMEVENT_NONE) // No hay nuevos Eventos
    {
      switch(diostream->GetCurrentState())
        {
          case DIOLINUXUARTFSMSTATE_NONE                    : break;

          case DIOLINUXUARTFSMSTATE_CONNECTED               : break;

          case DIOLINUXUARTFSMSTATE_WAITINGTOREAD           : {

                                                                if(!diostream->IsBlockRead())
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
                                                                        if(esize>DIOSTREAM_MAXBUFFER) esize = DIOSTREAM_MAXBUFFER;

                                                                        diostream->outbuffer->SetBlocked(true);
                                                                        XDWORD bw = diostream->WriteDirect(diostream->outbuffer->Get(), esize);
                                                                        diostream->outbuffer->SetBlocked(false);

                                                                        if(bw)
                                                                          {
                                                                            //XTRACE_PRINTDATABLOCK(XDEBUGLEVELCOLOR(4), (XBYTE*)diostream->buffer, (int)bw);
                                                                            diostream->outbuffer->Extract(NULL, 0, bw);
                                                                          }
                                                                      }
                                                                  }
                                                              }
                                                              break;

          case DIOLINUXUARTFSMSTATE_DISCONNECTING           : break;

        }
    }
   else
    {
      if(diostream->GetEvent()<DIOLINUXUART_LASTEVENT)
        {
          diostream->CheckTransition();

          switch(diostream->GetCurrentState())
            {
              case DIOLINUXUARTFSMSTATE_NONE                : break;

              case DIOLINUXUARTFSMSTATE_CONNECTED           : { DIOSTREAMXEVENT xevent(diostream,DIOSTREAMXEVENT_TYPE_CONNECTED);
                                                                xevent.SetDIOStream(diostream);
                                                                diostream->PostEvent(&xevent);

                                                                diostream->SetEvent(DIOLINUXUARTFSMEVENT_WAITINGTOREAD);
                                                              }
                                                              break;

              case DIOLINUXUARTFSMSTATE_WAITINGTOREAD       : break;

              case DIOLINUXUARTFSMSTATE_DISCONNECTING       : { DIOSTREAMXEVENT xevent(diostream,DIOSTREAMXEVENT_TYPE_DISCONNECTED);
                                                                xevent.SetDIOStream(diostream);
                                                                diostream->PostEvent(&xevent);

                                                                diostream->threadconnection->Run(false);
                                                                diostream->status = DIOSTREAMSTATUS_DISCONNECTED;
                                                              }
                                                              break;
            }
        }
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOLINUXSTREAMUART::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_LINUX
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOLINUXSTREAMUART::Clean()
{
  fd            = -1;
  readtimeout   = 3000;
  writetimeout  = 3000;
}


#pragma endregion


#endif

