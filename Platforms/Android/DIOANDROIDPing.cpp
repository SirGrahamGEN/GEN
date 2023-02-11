/*------------------------------------------------------------------------------------------
//  DIOANDROIDPING.CPP
//
//  Data IO ANDROID Ping class
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <malloc.h>
#include <syslog.h>
#include <signal.h>

#include <sys/socket.h>
#include <sys/un.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/ioctl.h>
//#include <sys/fcntl.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <net/if.h>
#include <netdb.h>
#include <linux/if_ether.h>


#include "HashCRC32.h"

#include "XRand.h"
#include "XTrace.h"
#include "XBuffer.h"
#include "XTimer.h"


#include "DIOANDROIDPing.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ------------------------------------------------------------------*/


/*---- CLASS MEMBERS ---------------------------------------------------------------------*/



/*-------------------------------------------------------------------
//  DIOANDROIDPING::DIOANDROIDPING
*/
/**
//
//  Class Constructor DIOANDROIDPING
//
//  ""
//  @version      30/03/2016 12:55:40
//
*/
/*-----------------------------------------------------------------*/
DIOANDROIDPING::DIOANDROIDPING()
{
  Clean();
}




/*-------------------------------------------------------------------
//  DIOANDROIDPING::~DIOANDROIDPING
*/
/**
//
//   Class Destructor DIOANDROIDPING
//
//  ""
//  @version      30/03/2016 12:55:33
//
*/
/*-----------------------------------------------------------------*/
DIOANDROIDPING::~DIOANDROIDPING()
{
  Clean();
}



/*-------------------------------------------------------------------
//  DIOANDROIDPING::Do
*/
/**
//
//
//
//  ""
//  @version      31/03/2016 10:38:44
//
//  @return       bool :
//
//  @param        nretries :
//  @param        timebetweenchecks :
//  @param        exitfirstgoodreply :
*/
/*-----------------------------------------------------------------*/
bool DIOANDROIDPING::Do(XDWORD nretries, XDWORD timebetweenchecks, bool exitfirstgoodreply)
{
  return false;
}

