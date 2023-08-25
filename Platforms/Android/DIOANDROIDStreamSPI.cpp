//------------------------------------------------------------------------------------------
//  DIOANDROIDSTREAMSPI.CPP
//
//  Data IO Stream SPI class
//
//
//  ""
//  @version 12/3/2003
//
//  GEN  Copyright (C).  All right reserved.
//------------------------------------------------------------------------------------------

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


#if defined(DIO_ACTIVE) && defined(DIO_SPI_ACTIVE)

//---- INCLUDES ----------------------------------------------------------------------------

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#include "XBuffer.h"
#include "XTrace.h"
#include "DIOStreamSPIConfig.h"

#include "DIOANDROIDStreamSPI.h"

#include "XMemory_Control.h"


//---- GENERAL VARIABLE --------------------------------------------------------------------


/*-------------------------------------------------------------------
//  DIOANDROIDSTREAMSPI::DIOANDROIDSTREAMSPI
*/
/**
//
//
//  ""
//  @version      18/02/2013 23:14:54
//
//  @return




*/
/*-----------------------------------------------------------------*/
DIOANDROIDSTREAMSPI::DIOANDROIDSTREAMSPI() : DIOSTREAMSPI()
{
  Clean();
}


//-------------------------------------------------------------------
//  DIOANDROIDSTREAMSPI::~DIOANDROIDSTREAMSPI
/**
//
//
//  ""
//  @version      20/11/2003 10:19:33
//
//  @return
//  */
//-------------------------------------------------------------------
DIOANDROIDSTREAMSPI::~DIOANDROIDSTREAMSPI()
{
  Clean();
}



/*-------------------------------------------------------------------
//  DIOANDROIDSTREAMSPI::Open
*/
/**
//
//
//  ""
//  @version      20/09/2012 15:33:40
//
//  @return       bool :
//  */
/*-----------------------------------------------------------------*/
bool DIOANDROIDSTREAMSPI::Open()
{
  if(!config) return false;

  XBUFFER charstr;
  
  string.ConvertToASCII(charstr); 
  handle = open(charstr.GetPtrChar(), O_RDWR);
  if(handle<0) return false;

  //  Set SPI parameters.
  //  Why are we reading it afterwriting it? I've no idea, but for now I'm blindly
  //  copying example code I've seen online...

  XBYTE   _mode  = config->GetMode();
  XBYTE   _bits  = config->GetNBitsWord();
  XDWORD  _speed = config->GetSpeed();

  if (ioctl(handle, SPI_IOC_WR_MODE           , &_mode)   < 0) return false;
  if (ioctl(handle, SPI_IOC_WR_BITS_PER_WORD  , &_bits)   < 0) return false;
  if (ioctl(handle, SPI_IOC_WR_MAX_SPEED_HZ   , &_speed)  < 0) return false;

  if (ioctl(handle, SPI_IOC_RD_MODE           , &_mode)   < 0) return false;
  if (ioctl(handle, SPI_IOC_RD_BITS_PER_WORD  , &_bits)   < 0) return false;
  if (ioctl(handle, SPI_IOC_RD_MAX_SPEED_HZ   , &_speed)  < 0) return false;

  return DIOSTREAMSPI::Open();
}



/*-------------------------------------------------------------------
//  DIOANDROIDSTREAMSPI::Close
*/
/**
//
//
//  ""
//  @version      20/09/2012 15:33:45
//
//  @return       bool :
//  */
/*-----------------------------------------------------------------*/
bool DIOANDROIDSTREAMSPI::Close()
{
  bool status = DIOSTREAMSPI::Close();

  if(handle>=0)
    {
      close(handle);
      handle  = -1;
    }

  return status;
}




/*-------------------------------------------------------------------
//  DIOANDROIDSTREAMSPI::TransferBuffer
*/
/**
//
//
//  ""
//  @version      16/12/2012 0:53:13
//
//  @return       bool :
//  @param        bufferread :
//  @param        bufferwrite :
//  @param        size :
*/
/*-----------------------------------------------------------------*/
bool DIOANDROIDSTREAMSPI::TransferBuffer(XBYTE* bufferread, XBYTE* bufferwrite, XDWORD size)
{
  struct spi_ioc_transfer transf;

  int sizeint = size;

  memset((XBYTE*)&transf, 0, sizeof(struct spi_ioc_transfer));

  //XTRACE_PRINTCOLOR(1, __L("SPI %d"), size);

  //wprintf((wchar_t *)__L("\n Write %4d bytes ->"),size);
  //fflush(stdout);

  transf.tx_buf         = (unsigned long)bufferwrite;
  transf.rx_buf         = (unsigned long)bufferread;
  transf.len            = sizeint;
  transf.speed_hz       = config->GetSpeed();
  transf.delay_usecs    = config->GetDelay();
  transf.bits_per_word  = config->GetNBitsWord();
  transf.cs_change      = true;

  int err = ioctl(handle, SPI_IOC_MESSAGE(1), &transf);

  //wprintf((wchar_t *)__L("%4d %d\n"), transf.len, err);
  //fflush(stdout);

  if(err<0) return false;

  return true;
}




/*-------------------------------------------------------------------
//  DIOANDROIDSTREAMSPI::Sleep
*/
/**
//
//
//  ""
//  @version      13/02/2013 19:09:26
//
//  @return       void :
//  @param        count :
*/
/*-----------------------------------------------------------------*/
void DIOANDROIDSTREAMSPI::Sleep(int count)
{
  for(int i=0;i<count;i++)
    {
      asm("nop");
    }

}




//-------------------------------------------------------------------
//  DIOANDROIDSTREAMSPI::Clean
/**
//
//
//  ""
//  @version      20/11/2003 10:19:50
//
//  @return       void :
//  */
//-------------------------------------------------------------------
void DIOANDROIDSTREAMSPI::Clean()
{
  handle = -1;
}


#endif