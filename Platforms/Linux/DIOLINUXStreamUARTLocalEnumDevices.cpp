//------------------------------------------------------------------------------------------
//  DIOLINUXSTREAMUARTLOCALENUMDEVICES.CPP
//
//  LINUX Data Input/Output Stream UART Local Enum Devices class
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


#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/serial.h>

#include "XTrace.h"
#include "XPath.h"
#include "DIOStreamDevice.h"

#include "DIOLINUXStreamUARTLocalEnumDevices.h"

#include "XMemory_Control.h"

//---- GENERAL VARIABLE --------------------------------------------------------------------


//---- CLASS MEMBERS -----------------------------------------------------------------------


/*-------------------------------------------------------------------
//  DIOLINUXSTREAMUARTLOCALENUMDEVICES::DIOLINUXSTREAMUARTLOCALENUMDEVICES
*/
/**
//
//
//  ""
//  @version      28/04/2013 19:00:01
//
//  @return


*/
/*-----------------------------------------------------------------*/
DIOLINUXSTREAMUARTLOCALENUMDEVICES::DIOLINUXSTREAMUARTLOCALENUMDEVICES() : DIOSTREAMUARTLOCALENUMDEVICES()
{

}



/*-------------------------------------------------------------------
//  DIOLINUXSTREAMUARTLOCALENUMDEVICES::~DIOLINUXSTREAMUARTLOCALENUMDEVICES
*/
/**
//
//
//  ""
//  @version      28/04/2013 19:00:12
//
//  @return
//  */
/*-----------------------------------------------------------------*/
DIOLINUXSTREAMUARTLOCALENUMDEVICES::~DIOLINUXSTREAMUARTLOCALENUMDEVICES()
{

}



/*-------------------------------------------------------------------
//  DIOLINUXSTREAMUARTLOCALENUMDEVICES::Search
*/
/**
//
//
//  ""
//  @version      28/04/2013 19:00:27
//
//  @return       bool :
//  */
/*-----------------------------------------------------------------*/
bool DIOLINUXSTREAMUARTLOCALENUMDEVICES::Search()
{
  DelAllDevices();

  struct dirent** namelist;
  XSTRING         sysdir;
  int             ndevices;

  sysdir = __L("/sys/class/tty/");

  XBUFFER charstr;
  
  sysdir.ConvertToASCII(charstr);
  ndevices = scandir(charstr.GetPtrChar(), &namelist, NULL, NULL);  
  if(ndevices >= 0)
    {
      while(ndevices--)
        {
          if(strcmp(namelist[ndevices]->d_name,"..") && strcmp(namelist[ndevices]->d_name,"."))
            {
              XSTRING     devicedir;
              struct stat st;

              devicedir  = sysdir;
              devicedir += namelist[ndevices]->d_name;

              devicedir += __L("/device");

              XBUFFER charstr;
              
              devicedir.ConvertToASCII(charstr);
                            
              bool result = (lstat(charstr.GetPtrChar(), &st)==0) && (S_ISLNK(st.st_mode));                          
              if(result)
                {
                  char buffer[1024];

                  memset(buffer, 0, sizeof(buffer));

                  devicedir += __L("/driver");

                  XBUFFER charstr;
                  
                  devicedir.ConvertToASCII(charstr);                                   
                  result = (readlink(charstr.GetPtrChar(), buffer, sizeof(buffer)) > 0);                  
                  if(result)
                    {
                      XSTRING tty;
                      XPATH   devicepath;
                      XPATH   devicefile;

                      tty = buffer;

                      devicepath  = sysdir;
                      devicepath += namelist[ndevices]->d_name;

                      devicepath.GetNamefile(devicefile);

                      devicepath  = __L("/dev/");
                      devicepath += devicefile;

                      //XTRACE_PRINTCOLOR(4,__L(" %s %s %s"),devicedir.Get(), devicepath.Get(), tty.Get());

                      bool isvalid = false;

                      if(tty.Find(__L("serial8250"), true) != XSTRING_NOTFOUND)
                        {
                           struct serial_struct serinfo;

                           XBUFFER charstr;
                           
                           devicepath.ConvertToASCII(charstr);                           
                           int fd = open(charstr.GetPtrChar(), O_RDWR | O_NONBLOCK | O_NOCTTY);                           
                           if(fd >= 0)
                            {
                              // Get serial_info
                              if(ioctl(fd, TIOCGSERIAL, &serinfo)==0)
                                {
                                  // If device type is no PORT_UNKNOWN we accept the port
                                  if(serinfo.type != PORT_UNKNOWN) isvalid = true;
                                }

                              close(fd);
                            }
                        } else isvalid = true;

                      if(isvalid)
                        {
                          DIOSTREAMDEVICE* device = new DIOSTREAMDEVICE();
                          if(device)
                            {
                              //device->SetIndex(index);
                              device->GetResource()->Set(devicepath);

                              devices.Add(device);
                            }
                        }
                    }
                }
            }

          free(namelist[ndevices]);
        }

      free(namelist);
    }

  return true;
}




/*-------------------------------------------------------------------
//  DIOLINUXSTREAMUARTLOCALENUMDEVICES::IsDeviceAvailable
*/
/**
//
//
//  ""
//  @version      28/04/2013 19:00:32
//
//  @return       bool :
//  @param        resource :
*/
/*-----------------------------------------------------------------*/
bool DIOLINUXSTREAMUARTLOCALENUMDEVICES::IsDeviceAvailable(XCHAR* resource)
{
  /*
  XSTRING strdevice;

  strdevice = resource;

  HANDLE hcomt = CreateFile(strdevice.Get(),
                            GENERIC_READ|GENERIC_WRITE,
                            0,0,
                            OPEN_EXISTING,
                            0,0);

  if(hcomt==INVALID_HANDLE_VALUE) return false;

  CloseHandle(hcomt);
  */
  return true;
}


#endif

