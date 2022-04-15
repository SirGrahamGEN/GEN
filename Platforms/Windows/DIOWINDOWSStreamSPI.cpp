//------------------------------------------------------------------------------------------
//  DIOWINDOWSSTREAMSPI.CPP
//
//  Windows Data IO Stream SPI class
//
//
//  ""
//  @version 12/3/2003
//
//  GEN  Copyright (C).  All right reserved.
//------------------------------------------------------------------------------------------

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"



//---- INCLUDES ----------------------------------------------------------------------------

#include <intrin.h>

#include "DIOWINDOWSStreamSPI.h"

#include "XMemory_Control.h"

//---- GENERAL VARIABLE --------------------------------------------------------------------



/*-------------------------------------------------------------------
//  DIOWINDOWSSTREAMSPI::DIOWINDOWSSTREAMSPI
*/
/**
//
//
//  ""
//  @version      18/02/2013 7:52:28
//
//  @return



//  @param        cipher :
*/
/*-----------------------------------------------------------------*/
DIOWINDOWSSTREAMSPI::DIOWINDOWSSTREAMSPI() : DIOSTREAMSPI()
{
  Clean();
}


//-------------------------------------------------------------------
//  DIOWINDOWSSTREAMSPI::~DIOWINDOWSSTREAMSPI
/**
//
//
//  ""
//  @version      20/11/2003 10:19:33
//
//  @return
//  */
//-------------------------------------------------------------------
DIOWINDOWSSTREAMSPI::~DIOWINDOWSSTREAMSPI()
{
  Clean();
}



/*-------------------------------------------------------------------
//  DIOWINDOWSSTREAMSPI::Sleep
*/
/**
//
//
//  ""
//  @version      28/10/2012 12:50:33
//
//  @return       void :
//  @param        count :
*/
/*-----------------------------------------------------------------*/
void DIOWINDOWSSTREAMSPI::Sleep(int count)
{
  for(int i=0;i<count;i++)
    {
      __nop();
    }
}


//-------------------------------------------------------------------
//  DIOWINDOWSSTREAMSPI::Clean
/**
//
//
//  ""
//  @version      20/11/2003 10:19:50
//
//  @return       void :
//  */
//-------------------------------------------------------------------
void DIOWINDOWSSTREAMSPI::Clean()
{

}

