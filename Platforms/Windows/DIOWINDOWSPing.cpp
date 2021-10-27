/*------------------------------------------------------------------------------------------
//  DIOWINDOWSPING.CPP
//
//  Data Input/Output WINDOWS Ping class
//
//  Author            : Abraham J. Velez
//  Date Of Creation  : 30/08/2012 9:14:11
//  Last Mofificacion :
//
//  GEN  Copyright (C).  All right reserved.
//----------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES --------------------------------------------------------------------------*/

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <icmpapi.h>

#include "HashCRC32.h"

#include "XSleep.h"
#include "XRand.h"
#include "XTrace.h"
#include "XBuffer.h"
#include "XTimer.h"

#include "DIOPing_XEvent.h"

#include "DIOWINDOWSPing.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ------------------------------------------------------------------*/


/*---- CLASS MEMBERS ---------------------------------------------------------------------*/



/*-------------------------------------------------------------------
//  DIOWINDOWSPING::DIOWINDOWSPING
*/
/**
//
//  Class Constructor DIOWINDOWSPING
//
//  @author      Abraham J. Velez
//  @version      30/03/2016 12:55:40
//
*/
/*-----------------------------------------------------------------*/
DIOWINDOWSPING::DIOWINDOWSPING() : DIOPING()
{
  Clean();
}




/*-------------------------------------------------------------------
//  DIOWINDOWSPING::~DIOWINDOWSPING
*/
/**
//
//   Class Destructor DIOWINDOWSPING
//
//  @author      Abraham J. Velez
//  @version      30/03/2016 12:55:33
//
*/
/*-----------------------------------------------------------------*/
DIOWINDOWSPING::~DIOWINDOWSPING()
{
  Clean();
}



/*-------------------------------------------------------------------
//  DIOWINDOWSPING::Do
*/
/**
//
//
//
//  @author      Abraham J. Velez
//  @version      30/03/2016 12:55:24
//
//  @return       bool :
//
//  @param        nretries :
//  @param        timebetweenchecks :
//  @param        exitfirstgoodreply :
*/
/*-----------------------------------------------------------------*/
#ifdef DIOPING_USEWINDOWDLL
bool DIOWINDOWSPING::Do(XDWORD nretries, XDWORD timebetweenchecks, bool exitfirstgoodreply)
{
  typedef struct
  {
    XDWORD   applicationID;
    XDWORD   time;
    char     cdata[DIOPING_REQ_TICKETSIZE];

  } DIOWINDOWSPING_ECHODATA;

  if(!urltarget) return false;
  if(!xtimer)    return false;

  XSTRING   targetIP;
  HANDLE    handle;

  DeleteAllReplys();

  urltarget->ResolveURL(targetIP);

  handle = IcmpCreateFile();
  if(handle == INVALID_HANDLE_VALUE) return false;

  unsigned long targetaddr;

  XSTRING_CREATEOEM(targetIP, charstr)
  inet_pton(AF_INET, charstr, &targetaddr);
  //targetaddr = inet_addr(charstr);
  XSTRING_DELETEOEM(targetIP, charstr)

  DIOWINDOWSPING_ECHODATA echorequest;
  int                     nloop = nretries;

  while(nloop)
    {
      HASHCRC32 crc32;
      XRAND*    xrand        = GEN_XFACTORY.CreateRand();
      XDWORD    crc32result;
      XSTRING   address;
      XBUFFER   xbuffer;

      if(!xrand) break;

      memset((XBYTE*)&echorequest, 0, sizeof(DIOWINDOWSPING_ECHODATA));

      echorequest.applicationID     = applicationID;
      echorequest.time              = (XDWORD)xtimer->GetMicroSecondsTickCounter();                           // Save tick count when sent

      for(int c=0; c<DIOPING_REQ_TICKETSIZE; c++)
        {
          echorequest.cdata[c] = xrand->Max(255);
        }

      GEN_XFACTORY.DeleteRand(xrand);

      crc32.ResetResult();
      crc32.Do((XBYTE*)echorequest.cdata, DIOPING_REQ_TICKETSIZE);
      crc32result = crc32.GetResultCRC32();

      xbuffer.Resize(sizeof(ICMP_ECHO_REPLY) + sizeof(DIOWINDOWSPING_ECHODATA));
      DWORD returnvalue = IcmpSendEcho(handle, targetaddr, (XBYTE*)&echorequest, sizeof(DIOWINDOWSPING_ECHODATA), NULL, (LPVOID)xbuffer.Get(), xbuffer.GetSize(), 1000);
      if(returnvalue)
        {
          PICMP_ECHO_REPLY          echoreply = (PICMP_ECHO_REPLY)xbuffer.Get();
          DIOWINDOWSPING_ECHODATA*  echodata  = (DIOWINDOWSPING_ECHODATA*)echoreply->Data;
          struct in_addr            replyaddr;
          XSTRING                   fromIP;

          replyaddr.S_un.S_addr = echoreply->Address;

          char IPcharstring[_MAXSTR];
          inet_ntop(AF_INET, &replyaddr, IPcharstring, _MAXSTR);
          fromIP.Set(IPcharstring);

          //fromIP = inet_ntoa(replyaddr);

          if(targetaddr == echoreply->Address)
            {
              if(echoreply->DataSize == sizeof(DIOWINDOWSPING_ECHODATA))
                {
                  crc32.ResetResult();
                  crc32.Do((XBYTE*)echodata->cdata, DIOPING_REQ_TICKETSIZE);

                  if(crc32result == crc32.GetResultCRC32())
                    {
                      if(echodata->applicationID == applicationID)
                        {
                          XDWORD elapsed;

                          //  Calculate elapsed time
                          elapsed = (XDWORD)(xtimer->GetMicroSecondsTickCounter() - echodata->time);

                          AddReply(nloop+1, fromIP.Get(), DIOPING_REQ_TICKETSIZE, (elapsed/1000), echoreply->Options.Ttl);

                          DIOPING_XEVENT xevent(this,DIOPING_XEVENT_TYPE_DOPING);
                          xevent.SetPingReply((DIOPINGREPLY*)replys.Get(replys.GetSize()-1));
                          PostEvent(&xevent);

                          //XTRACE_PRINTCOLOR(1, __L("Ping: received! %s %s (elapsed time %d)"), fromIP.Get(), targetIP.Get(), elapsed);

                          if(exitfirstgoodreply)
                            {
                              //nloop = 0;
                              break;
                            }

                          GEN_XSLEEP.MilliSeconds(timebetweenchecks);

                          nloop--;
                        }
                       else
                        {
                          //XTRACE_PRINTCOLOR(4, __L("Ping: application ID not equal! %s"), targetIP.Get());
                        }
                    }
                   else
                    {
                      //XTRACE_PRINTCOLOR(4, __L("Ping: error CRC! %s "), targetIP.Get());
                    }
                }
               else
                {
                  //XTRACE_PRINTCOLOR(4, __L("Ping: Invalid size data packet! %s "), targetIP.Get());
                }
            }
           else
            {
              //XTRACE_PRINTCOLOR(4, __L("Ping: not IP equal! %s "), targetIP.Get());
            }
        }
       else
        {
          //XTRACE_PRINTCOLOR(4, __L("Ping: not reply packet! %s "), targetIP.Get());
          if(exitfirstgoodreply) nloop = 0; else nloop--;
        }
   }

  bool status = WasConnected();

  /*
  if(!status)
    {
      //XTRACE_PRINTCOLOR((status?1:4), __L("Ping to [%s]: %s"), targetIP.Get(), (status?__L("Ok."):__L("ERROR!")));
    }
  */

  return status;
}
#endif