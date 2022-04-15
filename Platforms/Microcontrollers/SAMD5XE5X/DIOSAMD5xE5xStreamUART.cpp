/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOSAMD5xE5xStreamUART.cpp
*
* @class      DIOSAMD5XE5XSTREAMUART
* @brief      SAMD5xE5x Data IO Stream UART class
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

#if defined(DIO_ACTIVE) && defined(DIOUART_ACTIVE)


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XFactory.h"
#include "XThreadCollected.h"

#include "DIOStreamXEvent.h"
#include "DIOStreamUARTConfig.h"

#include "DIOSAMD5xE5xStreamUART.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

DIOSAMD5XE5XSTREAMUART*   diostreamuartptrhandle[3] = { NULL, NULL, NULL };

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSAMD5XE5XSTREAMUART::DIOSAMD5XE5XSTREAMUART()
* @brief      Constructor
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSAMD5XE5XSTREAMUART::DIOSAMD5XE5XSTREAMUART(): DIOSTREAMUART(), XFSMACHINE(0)
{
  Clean();

  AddState( DIOSAMD5XE5XUARTFSMSTATE_NONE             ,
            DIOSAMD5XE5XUARTFSMEVENT_CONNECTED        , DIOSAMD5XE5XUARTFSMSTATE_CONNECTED         ,
            DIOSAMD5XE5XUARTFSMEVENT_DISCONNECTING    , DIOSAMD5XE5XUARTFSMSTATE_DISCONNECTING     ,
            XFSMACHINESTATE_EVENTDEFEND);

  AddState( DIOSAMD5XE5XUARTFSMSTATE_CONNECTED        ,
            DIOSAMD5XE5XUARTFSMEVENT_WAITINGTOREAD    , DIOSAMD5XE5XUARTFSMSTATE_WAITINGTOREAD     ,
            DIOSAMD5XE5XUARTFSMEVENT_DISCONNECTING    , DIOSAMD5XE5XUARTFSMSTATE_DISCONNECTING     ,
            XFSMACHINESTATE_EVENTDEFEND);

  AddState( DIOSAMD5XE5XUARTFSMSTATE_WAITINGTOREAD    ,
            DIOSAMD5XE5XUARTFSMEVENT_CONNECTED        , DIOSAMD5XE5XUARTFSMSTATE_CONNECTED         ,
            DIOSAMD5XE5XUARTFSMEVENT_DISCONNECTING    , DIOSAMD5XE5XUARTFSMSTATE_DISCONNECTING     ,
            XFSMACHINESTATE_EVENTDEFEND);

  AddState( DIOSAMD5XE5XUARTFSMSTATE_DISCONNECTING    ,
            DIOSAMD5XE5XUARTFSMEVENT_CONNECTED        , DIOSAMD5XE5XUARTFSMSTATE_CONNECTED         ,
            DIOSAMD5XE5XUARTFSMEVENT_WAITINGTOREAD    , DIOSAMD5XE5XUARTFSMSTATE_WAITINGTOREAD     ,
            XFSMACHINESTATE_EVENTDEFEND);

  threadconnection = CREATEXTHREAD(XTHREADGROUPID_DIOSTREAMUART, __L("DIOSAMD5XE5XSTREAMUART::DIOSAMD5XE5XSTREAMUART"), ThreadConnection, (void*)this);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSAMD5XE5XSTREAMUART::~DIOSAMD5XE5XSTREAMUART()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSAMD5XE5XSTREAMUART::~DIOSAMD5XE5XSTREAMUART()
{
  Close();

  if(threadconnection) DELETEXTHREAD(XTHREADGROUPID_DIOSTREAMUART, threadconnection);

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMSTATUS DIOSAMD5XE5XSTREAMUART::GetConnectStatus()
* @brief      GetConnectStatus
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     DIOSTREAMSTATUS :
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMSTATUS DIOSAMD5XE5XSTREAMUART::GetConnectStatus()
{
  if(!config) return DIOSTREAMSTATUS_DISCONNECTED;

  return status;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSAMD5XE5XSTREAMUART::Open()
* @brief      Open
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSAMD5XE5XSTREAMUART::Open()
{
  if(!threadconnection)  return false;

  //--- ABRHAMD5XE5X ------------------
  /*
  switch(config->GetPort())
    {
      case  1 : huart.Instance = USART1;      break;
      case  2 : huart.Instance = USART2;      break;
      #ifndef HW_STM32F4XX
      case  3 : huart.Instance = USART3;      break;
      #endif
      default : return false;
    }

  indexport = (config->GetPort()-1);
  if(indexport < 0) return false;

  if(!Config(DIOSTREAMUARTMASK_ALL)) return false;

  if(HAL_UART_Init(&huart) != HAL_OK) return false;

  diostreamuartptrhandle[indexport] = this;

  __HAL_UART_ENABLE_IT(&huart, UART_IT_RXNE);

   switch(config->GetPort())
    {
      case  1 : HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
                HAL_NVIC_EnableIRQ(USART1_IRQn);
                break;

      case  2 : HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
                HAL_NVIC_EnableIRQ(USART2_IRQn);
                break;

      #ifndef HW_STM32F4XX
      case  3 :
                #ifdef HW_STM32F0XX
                HAL_NVIC_SetPriority(USART3_4_IRQn, 0, 0);
                HAL_NVIC_EnableIRQ(USART3_4_IRQn);
                #else
                HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
                HAL_NVIC_EnableIRQ(USART3_IRQn);
                #endif

                break;
      #endif

      default : return false;
    }

  HAL_UART_Receive_IT(&huart, (uint8_t*)&receiveddata, 1);
  */

  SetEvent(DIOSAMD5XE5XUARTFSMEVENT_CONNECTED);

  status = DIOSTREAMSTATUS_CONNECTED;

  ResetXBuffers();
  ResetConnectionStatistics();

  return threadconnection->Ini();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSAMD5XE5XSTREAMUART::Config(XWORD mask)
* @brief      Config
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  mask :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSAMD5XE5XSTREAMUART::Config(XWORD mask)
{
  //--- ABRHAMD5XE5X ------------------

  /*
  if((mask&DIOSTREAMUARTMASK_BAUDRATE) == DIOSTREAMUARTMASK_BAUDRATE)
    {
      switch(this->config->GetBaudRate())
        {
          case 50     : huart.Init.BaudRate = 50;     break;
          case 300    : huart.Init.BaudRate = 300;    break;
          case 600    : huart.Init.BaudRate = 600;    break;
          case 1200   : huart.Init.BaudRate = 1200;   break;
          case 4800   : huart.Init.BaudRate = 4800;   break;
          case 9600   : huart.Init.BaudRate = 9600;   break;
          case 19200  : huart.Init.BaudRate = 19200;  break;
          case 38400  : huart.Init.BaudRate = 38400;  break;
          case 57600  : huart.Init.BaudRate = 57600;  break;
          case 115200 : huart.Init.BaudRate = 115200; break;
        }
    }

  if((mask&DIOSTREAMUARTMASK_DATABITS ) == DIOSTREAMUARTMASK_DATABITS)
    {
      switch(this->config->GetDataBits())
        {
          case DIOSTREAMUARTDATABIT_5             : break;
          case DIOSTREAMUARTDATABIT_6             : break;
          case DIOSTREAMUARTDATABIT_7             : break;
          case DIOSTREAMUARTDATABIT_8             : huart.Init.WordLength = UART_WORDLENGTH_8B;     break;
          case DIOSTREAMUARTDATABIT_9             : huart.Init.WordLength = UART_WORDLENGTH_9B;     break;
        }
    }

  if((mask&DIOSTREAMUARTMASK_PARITY) == DIOSTREAMUARTMASK_PARITY)
    {
      switch(this->config->GetParity())
        {
          case DIOSTREAMUARTPARITY_NONE           : huart.Init.Parity = UART_PARITY_NONE;           break;
          case DIOSTREAMUARTPARITY_MARK           :                                                 break;
          case DIOSTREAMUARTPARITY_ODD            : huart.Init.Parity = UART_PARITY_ODD;            break;
          case DIOSTREAMUARTPARITY_SPACE          :                                                 break;
          case DIOSTREAMUARTPARITY_EVEN           : huart.Init.Parity = UART_PARITY_EVEN;           break;
        }
    }

  if((mask&DIOSTREAMUARTMASK_STOPBITS ) == DIOSTREAMUARTMASK_STOPBITS)
    {
      switch(this->config->GetStopBits())
        {
          case DIOSTREAMUARTSTOPBITS_ONE          : huart.Init.StopBits = UART_STOPBITS_1;          break;
          #if defined(HW_STM32F0XX) || defined(HW_STM32F3XX)
          case DIOSTREAMUARTSTOPBITS_ONEANDAHALF  : huart.Init.StopBits = UART_STOPBITS_1_5;        break;
          #endif
          case DIOSTREAMUARTSTOPBITS_TWO          : huart.Init.StopBits = UART_STOPBITS_2;          break;
        }
    }

  if((mask&DIOSTREAMUARTMASK_FLOWCONTROL) == DIOSTREAMUARTMASK_FLOWCONTROL)
    {
      switch(config->GetFlowControl())
        {
          case DIOSTREAMUARTFLOWCONTROL_NONE      : huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;     break;
          case DIOSTREAMUARTFLOWCONTROL_HARD      : huart.Init.HwFlowCtl = UART_HWCONTROL_RTS_CTS;  break;
          case DIOSTREAMUARTFLOWCONTROL_SOFT      : break;
        }
    }

  huart.Init.Mode                   = UART_MODE_TX_RX;
  huart.Init.OverSampling           = UART_OVERSAMPLING_16;


  #if defined(HW_STM32F0XX) || defined(HW_STM32F3XX)
  huart.Init.OneBitSampling         = UART_ONEBIT_SAMPLING_DISABLED;
  huart.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  #endif
  */

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOSAMD5XE5XSTREAMUART::ReadDirect(XBYTE* buffer, XDWORD size)
* @brief      ReadDirect
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  buffer :
* @param[in]  size :
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSAMD5XE5XSTREAMUART::ReadDirect(XBYTE* buffer, XDWORD size)
{
  if(GetConnectStatus()==DIOSTREAMSTATUS_DISCONNECTED) return 0;

  int br = 0;

  //--- ABRHAMD5XE5X ------------------
  /*
  if(HAL_UART_Receive(&diostreamuartptrhandle[indexport]->huart, (uint8_t*)buffer, size, 1000) == HAL_OK)
    {
      br = size;
    }
  */

  return (XDWORD)br;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOSAMD5XE5XSTREAMUART::WriteDirect(XBYTE* buffer, XDWORD size)
* @brief      WriteDirect
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  buffer :
* @param[in]  size :
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSAMD5XE5XSTREAMUART::WriteDirect(XBYTE* buffer, XDWORD size)
{
  if(GetConnectStatus()==DIOSTREAMSTATUS_DISCONNECTED) return 0;

  //--- ABRHAMD5XE5X ------------------

  // if(HAL_UART_Transmit(&huart, (uint8_t*)buffer , (uint16_t)size, 1000) == HAL_OK) return size;

  return (XDWORD)0;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOSAMD5XE5XSTREAMUART::Write(XBYTE* buffer, XDWORD size)
* @brief      Write
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  buffer :
* @param[in]  size :
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSAMD5XE5XSTREAMUART::Write(XBYTE* buffer, XDWORD size)
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
* @fn         bool DIOSAMD5XE5XSTREAMUART::Disconnect()
* @brief      Disconnect
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSAMD5XE5XSTREAMUART::Disconnect()
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSAMD5XE5XSTREAMUART::Close()
* @brief      Close
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSAMD5XE5XSTREAMUART::Close()
{
  if(!threadconnection) return false;

  threadconnection->End();

  if(GetConnectStatus()==DIOSTREAMSTATUS_DISCONNECTED) return false;

  diostreamuartptrhandle[indexport] = NULL;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSAMD5XE5XSTREAMUART::GetCTS()
* @brief      GetCTS
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSAMD5XE5XSTREAMUART::GetCTS()
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSAMD5XE5XSTREAMUART::GetDSR()
* @brief      GetDSR
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSAMD5XE5XSTREAMUART::GetDSR()
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSAMD5XE5XSTREAMUART::GetRing()
* @brief      GetRing
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSAMD5XE5XSTREAMUART::GetRing()
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSAMD5XE5XSTREAMUART::GetRLSD()
* @brief      GetRLSD
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSAMD5XE5XSTREAMUART::GetRLSD()
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSAMD5XE5XSTREAMUART::SetRTS(bool on)
* @brief      SetRTS
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  on :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSAMD5XE5XSTREAMUART::SetRTS(bool on)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSAMD5XE5XSTREAMUART::SetDTR(bool on)
* @brief      SetDTR
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  on :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSAMD5XE5XSTREAMUART::SetDTR(bool on)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSAMD5XE5XSTREAMUART::CleanBuffers()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSAMD5XE5XSTREAMUART::CleanBuffers()
{

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void HAL_UART_RxCpltCallback(UART_HandleTypeDef*huart)
* @brief      AL_UART_RxCpltCallback
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  UART_HandleTypeDef*huart :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
//--- ABRHAMD5XE5X ------------------
/*
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  int indexport = -1;

  if(huart->Instance == USART1) indexport = 0;
  if(huart->Instance == USART2) indexport = 1;
  #ifndef HW_STM32F4XX
  if(huart->Instance == USART3) indexport = 2;
  #endif

  if(indexport == -1)                                                                       return;
  if(!diostreamuartptrhandle[indexport])                                                    return;
  if(diostreamuartptrhandle[indexport]->GetConnectStatus() == DIOSTREAMSTATUS_DISCONNECTED) return;

  if(!diostreamuartptrhandle[indexport]->IsBlockRead())
    {
      if(!diostreamuartptrhandle[indexport]->inbuffer->IsBlocked())
        {
          if(diostreamuartptrhandle[indexport]->readcache[indexport].GetSize())
            {
              diostreamuartptrhandle[indexport]->inbuffer->Add(diostreamuartptrhandle[indexport]->readcache);
              diostreamuartptrhandle[indexport]->readcache[indexport].Delete();
            }

          diostreamuartptrhandle[indexport]->inbuffer->Add(diostreamuartptrhandle[indexport]->receiveddata);
        }
       else
        {
          diostreamuartptrhandle[indexport]->readcache[indexport].Add(diostreamuartptrhandle[indexport]->receiveddata);
        }
    }

  HAL_UART_Receive_IT(&diostreamuartptrhandle[indexport]->huart, (uint8_t*)&diostreamuartptrhandle[indexport]->receiveddata, 1);
}
*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSAMD5XE5XSTREAMUART::ThreadConnection(void* param)
* @brief      ThreadConnection
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  param :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOSAMD5XE5XSTREAMUART::ThreadConnection(void* param)
{
  DIOSAMD5XE5XSTREAMUART* diostream = (DIOSAMD5XE5XSTREAMUART*)param;
  if(!diostream) return;

  if(diostream->GetEvent()==DIOSAMD5XE5XUARTFSMEVENT_NONE) // No hay nuevos Eventos
    {
      switch(diostream->GetCurrentState())
        {
          case DIOSAMD5XE5XUARTFSMSTATE_NONE                    : break;

          case DIOSAMD5XE5XUARTFSMSTATE_CONNECTED               : break;

          case DIOSAMD5XE5XUARTFSMSTATE_WAITINGTOREAD           : { if(!diostream->IsBlockRead())
                                                                      {
                                                                        if(!diostream->inbuffer->IsBlocked())
                                                                          {
                                                                            if(diostream->readcache[diostream->indexport].GetSize())
                                                                              {
                                                                                diostream->inbuffer->Add(diostream->readcache);
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
                                                                                diostream->outbuffer->Get(diostream->writebuffer, esize, 0);
                                                                                if(diostream->WriteDirect(diostream->writebuffer, esize))
                                                                                  {
                                                                                    diostream->outbuffer->Extract(NULL, 0, esize);
                                                                                  }
                                                                              }
                                                                          }
                                                                      }
                                                                  }
                                                                  break;

          case DIOSAMD5XE5XUARTFSMSTATE_DISCONNECTING           : break;

        }
    }
   else
    {
      if(diostream->GetEvent()<DIOSAMD5XE5XUART_LASTEVENT)
        {
          diostream->CheckTransition();

          switch(diostream->GetCurrentState())
            {
              case DIOSAMD5XE5XUARTFSMSTATE_NONE                : break;

              case DIOSAMD5XE5XUARTFSMSTATE_CONNECTED           : { DIOSTREAMXEVENT xevent(diostream,DIOSTREAMXEVENT_TYPE_CONNECTED);
                                                                    xevent.SetDIOStream(diostream);
                                                                    diostream->PostEvent(&xevent);

                                                                    diostream->SetEvent(DIOSAMD5XE5XUARTFSMEVENT_WAITINGTOREAD);
                                                                  }
                                                                  break;

              case DIOSAMD5XE5XUARTFSMSTATE_WAITINGTOREAD       : break;

              case DIOSAMD5XE5XUARTFSMSTATE_DISCONNECTING       : { DIOSTREAMXEVENT xevent(diostream,DIOSTREAMXEVENT_TYPE_DISCONNECTED);
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
* @fn         void DIOSAMD5XE5XSTREAMUART::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOSAMD5XE5XSTREAMUART::Clean()
{
  threadconnection   = NULL;
  indexport         = -1;
}


#endif
