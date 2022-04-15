/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOSAMD5xE5xStreamSPI.cpp
*
* @class      DIOSAMD5XE5XSTREAMSPI
* @brief      SAMD5xE5x Data IO Stream SPI class
* @ingroup    PLATFORM_SAMD5XE5X
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
*---------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"

#if defined(DIO_ACTIVE) && defined(DIOSPI_ACTIVE)

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XFactory.h"
#include "XThreadCollected.h"

#include "DIOStreamXEvent.h"
#include "DIOStreamSPIConfig.h"

#include "DIOSAMD5xE5xStreamSPI.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

DIOSAMD5XE5XSTREAMSPIPORT*    DIOSAMD5XE5XSTREAMSPI::ports[DIOSAMD5XE5XSTREAMSPI_MAXPORTS]     = { NULL, NULL };
DIOSAMD5XE5XSTREAMSPI*        DIOSAMD5XE5XSTREAMSPI::handles[DIOSAMD5XE5XSTREAMSPI_MAXHANDLES] = { NULL, NULL };

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------------------------------------------------*/
/*  DIOSAMD5XE5XSTREAMSPIPORT                                                                                         */
/*--------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSAMD5XE5XSTREAMSPIPORT::DIOSAMD5XE5XSTREAMSPIPORT()
* @brief      Constructor
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSAMD5XE5XSTREAMSPIPORT::DIOSAMD5XE5XSTREAMSPIPORT()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSAMD5XE5XSTREAMSPIPORT::~DIOSAMD5XE5XSTREAMSPIPORT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSAMD5XE5XSTREAMSPIPORT::~DIOSAMD5XE5XSTREAMSPIPORT()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOSAMD5XE5XSTREAMSPIPORT::GetCounterRef()
* @brief      GetCounterRef
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSAMD5XE5XSTREAMSPIPORT::GetCounterRef()
{
  return counterref;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSAMD5XE5XSTREAMSPIPORT::SetCounterRef(XDWORD counterref)
* @brief      SetCounterRef
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  counterref :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOSAMD5XE5XSTREAMSPIPORT::SetCounterRef(XDWORD counterref)
{
  this->counterref = counterref;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         SPI_HandleTypeDef* DIOSAMD5XE5XSTREAMSPIPORT::GetHandleSPI()
* @brief      GetHandleSPI
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     SPI_HandleTypeDef* :
*
*---------------------------------------------------------------------------------------------------------------------*/
//--- ABRHAMD5XE5X ------------------
/*
SPI_HandleTypeDef* DIOSAMD5XE5XSTREAMSPIPORT::GetHandleSPI()
{
  return hspi;
}
*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSAMD5XE5XSTREAMSPIPORT::SetHandleSPI(SPI_HandleTypeDef* hspi)
* @brief      SetHandleSPI
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  hspi :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
//--- ABRHAMD5XE5X ------------------
/*
void DIOSAMD5XE5XSTREAMSPIPORT::SetHandleSPI(SPI_HandleTypeDef* hspi)
{
  this->hspi = hspi;
}
*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSAMD5XE5XSTREAMSPIPORT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOSAMD5XE5XSTREAMSPIPORT::Clean()
{
  counterref        = 0;
  //--- ABRHAMD5XE5X ------------------
  //hspi              = NULL;
}



/*--------------------------------------------------------------------------------------------------------------------*/
/*  DIOSAMD5XE5XSTREAMSPI                                                                                             */
/*--------------------------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSAMD5XE5XSTREAMSPI::DIOSAMD5XE5XSTREAMSPI()
* @brief      Constructor
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSAMD5XE5XSTREAMSPI::DIOSAMD5XE5XSTREAMSPI()  : DIOSTREAMSPI()
{
  Clean();

  AddState( DIOSTREAMSPI_FSMSTATE_NONE            ,
            DIOSTREAMSPI_FSMEVENT_CONNECTED       , DIOSTREAMSPI_FSMSTATE_CONNECTED        ,
            DIOSTREAMSPI_FSMEVENT_DISCONNECTING   , DIOSTREAMSPI_FSMSTATE_DISCONNECTING    ,
            XFSMACHINESTATE_EVENTDEFEND);

  AddState( DIOSTREAMSPI_FSMSTATE_CONNECTED       ,
            DIOSTREAMSPI_FSMEVENT_WAITINGTOREAD   , DIOSTREAMSPI_FSMSTATE_WAITINGTOREAD    ,
            DIOSTREAMSPI_FSMEVENT_DISCONNECTING   , DIOSTREAMSPI_FSMSTATE_DISCONNECTING    ,
            XFSMACHINESTATE_EVENTDEFEND);

  AddState( DIOSTREAMSPI_FSMSTATE_WAITINGTOREAD   ,
            DIOSTREAMSPI_FSMEVENT_CONNECTED       , DIOSTREAMSPI_FSMSTATE_CONNECTED        ,
            DIOSTREAMSPI_FSMEVENT_DISCONNECTING   , DIOSTREAMSPI_FSMSTATE_DISCONNECTING    ,
            XFSMACHINESTATE_EVENTDEFEND);

  AddState( DIOSTREAMSPI_FSMSTATE_DISCONNECTING   ,
            DIOSTREAMSPI_FSMEVENT_CONNECTED       , DIOSTREAMSPI_FSMSTATE_CONNECTED        ,
            DIOSTREAMSPI_FSMEVENT_WAITINGTOREAD   , DIOSTREAMSPI_FSMSTATE_WAITINGTOREAD    ,
            XFSMACHINESTATE_EVENTDEFEND);

  threadconnection = CREATEXTHREAD(XTHREADGROUPID_DIOSTREAMSPI, __L("DIOSAMD5XE5XSTREAMSPI::DIOSAMD5XE5XSTREAMSPI"), ThreadConnection, (void*)this);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSAMD5XE5XSTREAMSPI::~DIOSAMD5XE5XSTREAMSPI()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSAMD5XE5XSTREAMSPI::~DIOSAMD5XE5XSTREAMSPI()
{
  Close();

  if(threadconnection) DELETEXTHREAD(XTHREADGROUPID_DIOSTREAMSPI, threadconnection);

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMSTATUS DIOSAMD5XE5XSTREAMSPI::GetConnectStatus()
* @brief      GetConnectStatus
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     DIOSTREAMSTATUS :
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMSTATUS DIOSAMD5XE5XSTREAMSPI::GetConnectStatus()
{
  if(!config) return DIOSTREAMSTATUS_DISCONNECTED;

  return status;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSAMD5XE5XSTREAMSPI::Open()
* @brief      Open
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSAMD5XE5XSTREAMSPI::Open()
{
  if(!threadconnection)  return false;
  if(!config)           return false;

 for(int c=0; c<DIOSAMD5XE5XSTREAMSPI_MAXHANDLES; c++)
    {
      if(DIOSAMD5XE5XSTREAMSPI::handles[c] == this) return false;

      if(!DIOSAMD5XE5XSTREAMSPI::handles[c])
        {
          indexhandle = c;
          DIOSAMD5XE5XSTREAMSPI::handles[indexhandle] = this;
          break;
        }
    }

  if(indexhandle == -1) return false;

  indexport = config->GetPort()-1;

  //--- ABRHAMD5XE5X ------------------

  //if(!DIOSAMD5XE5XSTREAMSPI::ports[indexport])
  //  {
  //    DIOSAMD5XE5XSTREAMSPIPORT* port = new DIOSAMD5XE5XSTREAMSPIPORT();
  //    if(!port) return false;

  //    hspi = new SPI_HandleTypeDef();
  //    if(!hspi)
  //      {
  //        delete port;
  //        return false;
  //      }

  //    switch(config->GetPort())
  //      {
  //        case  1 : hspi->Instance = SPI1;       break;
  //        case  2 : hspi->Instance = SPI2;       break;
  //        default : return false;
  //      }

  //    /*
  //    hspi->Init.Mode               = SPI_MODE_MASTER;
  //    hspi->Init.Direction          = SPI_DIRECTION_2LINES;  //SPI_DIRECTION_1LINE;
  //    hspi->Init.DataSize           = SPI_DATASIZE_8BIT;
  //    hspi->Init.CLKPolarity        = SPI_POLARITY_LOW;
  //    hspi->Init.CLKPhase           = SPI_PHASE_1EDGE;
  //    hspi->Init.NSS                = SPI_NSS_SOFT;
  //    hspi->Init.BaudRatePrescaler  = SPI_BAUDRATEPRESCALER_2;
  //    hspi->Init.FirstBit           = SPI_FIRSTBIT_MSB;
  //    hspi->Init.TIMode             = SPI_TIMODE_DISABLE;
  //    hspi->Init.CRCCalculation     = SPI_CRCCALCULATION_DISABLE;
  //    hspi->Init.CRCPolynomial      = 7;
  //    #if defined(HW_STM32F0XX) || defined(HW_STM32F3XX)
  //    hspi->Init.CRCLength          = SPI_CRC_LENGTH_DATASIZE;
  //    hspi->Init.NSSPMode           = SPI_NSS_PULSE_ENABLE;
  //    #endif
  //    */
  //
  //    hspi->Init.Mode               = SPI_MODE_MASTER;
  //    hspi->Init.Direction          = SPI_DIRECTION_2LINES;
  //    hspi->Init.DataSize           = SPI_DATASIZE_8BIT;
  //    hspi->Init.CLKPolarity        = SPI_POLARITY_LOW;
  //    hspi->Init.CLKPhase           = SPI_PHASE_1EDGE;
  //    hspi->Init.NSS                = SPI_NSS_HARD_OUTPUT;
  //    hspi->Init.BaudRatePrescaler  = SPI_BAUDRATEPRESCALER_2;
  //    hspi->Init.FirstBit           = SPI_FIRSTBIT_MSB;
  //    hspi->Init.TIMode             = SPI_TIMODE_DISABLE;
  //    hspi->Init.CRCCalculation     = SPI_CRCCALCULATION_DISABLE;
  //    hspi->Init.CRCPolynomial      = 7;
  //    hspi->Init.CRCLength          = SPI_CRC_LENGTH_DATASIZE;
  //    hspi->Init.NSSPMode           = SPI_NSS_PULSE_ENABLE;
  //
  //    if(HAL_SPI_Init(hspi) != HAL_OK)
  //      {
  //        return false;
  //      }

  //    port->SetHandleSPI(hspi);
  //    DIOSAMD5XE5XSTREAMSPI::ports[indexport] = port;
  //  }
  // else
  //  {
  //    hspi = DIOSAMD5XE5XSTREAMSPI::ports[indexport]->GetHandleSPI();
  //    DIOSAMD5XE5XSTREAMSPI::ports[indexport]->SetCounterRef(DIOSAMD5XE5XSTREAMSPI::ports[indexport]->GetCounterRef()+1);
  //  }

  SetEvent(DIOSTREAMSPI_FSMEVENT_CONNECTED);

  status = DIOSTREAMSTATUS_CONNECTED;

  memset(bufferdata, 0, DIOSTREAM_MAXBUFFER);

  ResetXBuffers();
  ResetConnectionStatistics();

  return threadconnection->Ini();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSAMD5XE5XSTREAMSPI::WaitToFilledReadingBuffer(int filledto, int timeout)
* @brief      WaitToFilledReadingBuffer
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  filledto :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSAMD5XE5XSTREAMSPI::WaitToFilledReadingBuffer(int filledto, int timeout)
{
  if(filledto == DIOSTREAM_SOMETHINGTOREAD) sizebufferdata = 1; else sizebufferdata = filledto;

  //--- ABRHAMD5XE5X ------------------

  /*
  switch(config->GetMode())
    {
      case DIOSTREAMMODE_MASTER     :
      case DIOSTREAMMODE_SEMIMASTER :
      case DIOSTREAMMODE_SLAVE      : HAL_SPI_Transmit_IT(hspi, (uint8_t*)bufferdata, sizebufferdata);
                                      break;
    }
  */

  return DIOSTREAM::WaitToFilledReadingBuffer(sizebufferdata, timeout);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOSAMD5XE5XSTREAMSPI::ReadDirect(XBYTE* buffer, XDWORD size)
* @brief      ReadDirect
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  buffer :
* @param[in]  size :
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSAMD5XE5XSTREAMSPI::ReadDirect(XBYTE* buffer, XDWORD size)
{
  if(!config)                                          return 0;
  if(GetConnectStatus()==DIOSTREAMSTATUS_DISCONNECTED) return 0;

  //--- ABRHAMD5XE5X ------------------


  XDWORD br = 0;

  /*
  switch(config->GetMode())
    {
      case DIOSTREAMMODE_MASTER     :
      case DIOSTREAMMODE_SEMIMASTER :
      case DIOSTREAMMODE_SLAVE      : if(HAL_SPI_Receive(hspi, buffer, size, 100) == HAL_OK) br = size;
                                      break;
    }
  */

  return br;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOSAMD5XE5XSTREAMSPI::WriteDirect(XBYTE* buffer, XDWORD size)
* @brief      WriteDirect
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  buffer :
* @param[in]  size :
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSAMD5XE5XSTREAMSPI::WriteDirect(XBYTE* buffer, XDWORD size)
{
  if(!config)                                          return 0;
  if(GetConnectStatus()==DIOSTREAMSTATUS_DISCONNECTED) return 0;

  XDWORD bw = 0;

  if(!size) return 0;

  //--- ABRHAMD5XE5X ------------------
  /*
  switch(config->GetMode())
    {
      case DIOSTREAMMODE_MASTER       :
      case DIOSTREAMMODE_SEMIMASTER   :
      case DIOSTREAMMODE_SLAVE        : if(HAL_SPI_Transmit(hspi, buffer, size, 100) == HAL_OK) bw = size;
                                        break;
    }
  */

  return bw;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOSAMD5XE5XSTREAMSPI::Write(XBYTE* buffer, XDWORD size)
* @brief      Write
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  buffer :
* @param[in]  size :
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSAMD5XE5XSTREAMSPI::Write(XBYTE* buffer, XDWORD size)
{
  if(!outbuffer) return 0;

  while(outbuffer->IsBlocked())
    {

    }

  if(!outbuffer->Add(buffer,size))  return 0;

  nbyteswrite+=size;
  if(xtimernotactivity) xtimernotactivity->Reset();

  outbuffer->SetBlocked(false);

  return size;
}



 /**-------------------------------------------------------------------------------------------------------------------
 *
 *  @fn         bool DIOSAMD5XE5XSTREAMSPI::Disconnect()
 *  @brief      Disconnect
 *  @ingroup    PLATFORM_SAMD5XE5X
 *
 *  ""
 *  ""
 *
 *  @return     bool : true if is succesful.
 *
 *---------------------------------------------------------------------------------------------------------------------*/
bool DIOSAMD5XE5XSTREAMSPI::Disconnect()
 {
   return false;
 }


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSAMD5XE5XSTREAMSPI::Close()
* @brief      Close
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSAMD5XE5XSTREAMSPI::Close()
{
  if(!threadconnection) return false;

  threadconnection->End();

  if(GetConnectStatus()==DIOSTREAMSTATUS_DISCONNECTED) return false;

  if(!DIOSAMD5XE5XSTREAMSPI::handles[indexhandle]) return false;

  DIOSAMD5XE5XSTREAMSPI::handles[indexhandle] = NULL;

  if(!DIOSAMD5XE5XSTREAMSPI::ports[indexport]->GetCounterRef())
    {
      //--- ABRHAMD5XE5X ------------------
      /*
      HAL_SPI_DeInit(DIOSAMD5XE5XSTREAMSPI::ports[indexport]->GetHandleSPI());

      delete DIOSAMD5XE5XSTREAMSPI::ports[indexport]->GetHandleSPI();
      delete DIOSAMD5XE5XSTREAMSPI::ports[indexport];

      */

      DIOSAMD5XE5XSTREAMSPI::ports[indexport] = NULL;
    }
   else
   {
     DIOSAMD5XE5XSTREAMSPI::ports[indexport]->SetCounterRef(DIOSAMD5XE5XSTREAMSPI::ports[indexport]->GetCounterRef()-1);
   }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSAMD5XE5XSTREAMSPI::CleanBuffers()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSAMD5XE5XSTREAMSPI::CleanBuffers()
{
  return false;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void HAL_SPI_MasterRxCpltCallback(SPI_HandleTypeDef* hspi)
* @brief      AL_SPI_MasterRxCpltCallback
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  hspi :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
//--- ABRHAMD5XE5X ------------------
/*
void HAL_SPI_MasterRxCpltCallback(SPI_HandleTypeDef* hspi)
{
  int port = -1;

  if(hspi->Instance == SPI1) port = 0;
  if(hspi->Instance == SPI2) port = 1;

  for(int c=0; c<DIOSAMD5XE5XSTREAMSPI_MAXHANDLES; c++)
    {
      if(DIOSAMD5XE5XSTREAMSPI::handles[c])
        {
          if(DIOSAMD5XE5XSTREAMSPI::handles[c]->indexport  == port)
            {
              if(DIOSAMD5XE5XSTREAMSPI::handles[c]->GetConnectStatus() == DIOSTREAMSTATUS_DISCONNECTED) return;

              if(!DIOSAMD5XE5XSTREAMSPI::handles[c]->IsBlockRead())
                {
                   DIOSAMD5XE5XSTREAMSPI::handles[c]->inbuffer->Add(DIOSAMD5XE5XSTREAMSPI::handles[c]->bufferdata, DIOSAMD5XE5XSTREAMSPI::handles[c]->sizebufferdata);
                }

              DIOSAMD5XE5XSTREAMSPI::handles[c]->sizebufferdata = 0;
            }
        }
    }
}
*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void HAL_SPI_SlaveRxCpltCallback(SPI_HandleTypeDef* hspi)
* @brief      AL_SPI_SlaveRxCpltCallback
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  hspi :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
//--- ABRHAMD5XE5X ------------------
/*
void HAL_SPI_SlaveRxCpltCallback(SPI_HandleTypeDef* hspi)
{
  HAL_SPI_MasterRxCpltCallback(hspi);
}
*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void HAL_SPI_ErrorCallback(SPI_HandleTypeDef*hspi)
* @brief      AL_SPI_ErrorCallback
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  SPI_HandleTypeDef*hspi :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
//--- ABRHAMD5XE5X ------------------
/*
void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
  XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("SPI comunication error [%d]"), hspi->ErrorCode);
}
*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSAMD5XE5XSTREAMSPI::ThreadConnection(void* param)
* @brief      ThreadConnection
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  param :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOSAMD5XE5XSTREAMSPI::ThreadConnection(void* param)
{
  DIOSAMD5XE5XSTREAMSPI* diostream = (DIOSAMD5XE5XSTREAMSPI*)param;
  if(!diostream) return;

  //HAL_NVIC_DisableIRQ(TIM3_IRQn);

  if(diostream->GetEvent()==DIOSTREAMSPI_FSMEVENT_NONE) // No hay nuevos Eventos
    {
      switch(diostream->GetCurrentState())
        {
          case DIOSTREAMSPI_FSMSTATE_NONE                   : break;

          case DIOSTREAMSPI_FSMSTATE_CONNECTED              : break;

          case DIOSTREAMSPI_FSMSTATE_WAITINGTOREAD          : if(!diostream->IsBlockRead())
                                                                {
                                                                  if(!diostream->inbuffer->IsBlocked())
                                                                    {
                                                                      if(diostream->readcache[diostream->indexport].GetSize())
                                                                        {
                                                                          diostream->inbuffer->Add(diostream->readcache[diostream->indexport]);
                                                                          diostream->readcache[diostream->indexport].Delete();
                                                                        }
                                                                    }
                                                                }

                                                              if(!diostream->IsBlockWrite())
                                                                {
                                                                  if(!diostream->outbuffer->IsBlocked())
                                                                    {
                                                                      int esize = diostream->outbuffer->GetSize();
                                                                      if(esize>DIOSTREAM_MAXBUFFER) esize = DIOSTREAM_MAXBUFFER;

                                                                      if(esize)
                                                                        {
                                                                          diostream->outbuffer->Extract(diostream->writebuffer, 0, esize);
                                                                          diostream->WriteDirect(diostream->writebuffer, esize);
                                                                        }
                                                                    }
                                                                }
                                                              break;

          case DIOSTREAMSPI_FSMSTATE_DISCONNECTING          : break;

        }
    }
   else
    {
      if(diostream->GetEvent()<DIOSTREAMSPI_LASTEVENT)
        {
          diostream->CheckTransition();

          switch(diostream->GetCurrentState())
            {
              case DIOSTREAMSPI_FSMSTATE_NONE               : break;

              case DIOSTREAMSPI_FSMSTATE_CONNECTED          : { DIOSTREAMXEVENT xevent(diostream,DIOSTREAMXEVENT_TYPE_CONNECTED);
                                                                xevent.SetDIOStream(diostream);
                                                                diostream->PostEvent(&xevent);

                                                                diostream->SetEvent(DIOSTREAMSPI_FSMEVENT_WAITINGTOREAD);
                                                              }
                                                              break;

              case DIOSTREAMSPI_FSMSTATE_WAITINGTOREAD      : break;

              case DIOSTREAMSPI_FSMSTATE_DISCONNECTING      : { DIOSTREAMXEVENT xevent(diostream,DIOSTREAMXEVENT_TYPE_DISCONNECTED);
                                                                xevent.SetDIOStream(diostream);
                                                                diostream->PostEvent(&xevent);

                                                                diostream->status = DIOSTREAMSTATUS_DISCONNECTED;
                                                              }
                                                              break;
            }
        }
    }
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSAMD5XE5XSTREAMSPI::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOSAMD5XE5XSTREAMSPI::Clean()
{
  //--- ABRHAMD5XE5X ------------------
  //hspi              = NULL;
  localaddress      = 0;
  remoteaddress     = 0;
  threadconnection   = NULL;
  indexhandle       = -1;
  indexport         = -1;
  sizebufferdata    = 0;
}



#endif
