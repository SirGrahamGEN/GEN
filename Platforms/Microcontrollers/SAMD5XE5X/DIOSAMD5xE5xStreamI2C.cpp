/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOSAMD5xE5xStreamI2C.cpp
*
* @class      DIOSAMD5XE5XSTREAMI2C
* @brief      SAMD5xE5x Data IO Stream I2C class
* @ingroup    PLATFORM_SAMD5XE5X
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


#if defined(DIO_ACTIVE) && defined(DIOI2C_ACTIVE)

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XFactory.h"
#include "XThreadCollected.h"

#include "DIOStreamXEvent.h"
#include "DIOStreamI2CConfig.h"

#include "DIOSAMD5xE5xStreamI2C.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

DIOSAMD5XE5XSTREAMI2CPORT*    DIOSAMD5XE5XSTREAMI2C::ports[DIOSAMD5XE5XSTREAMI2C_MAXPORTS]     = { NULL, NULL };
DIOSAMD5XE5XSTREAMI2C*        DIOSAMD5XE5XSTREAMI2C::handles[DIOSAMD5XE5XSTREAMI2C_MAXHANDLES] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------------------------------------------------*/
/* DIOSAMD5XE5XSTREAMI2CPORT                                                                                          */
/*--------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSAMD5XE5XSTREAMI2CPORT::sDIOSAMD5XE5XSTREAMI2CPORT()
* @brief      Constructor
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSAMD5XE5XSTREAMI2CPORT::DIOSAMD5XE5XSTREAMI2CPORT()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSAMD5XE5XSTREAMI2CPORT::~DIOSAMD5XE5XSTREAMI2CPORT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSAMD5XE5XSTREAMI2CPORT::~DIOSAMD5XE5XSTREAMI2CPORT()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOSAMD5XE5XSTREAMI2CPORT::GetCounterRef()
* @brief      GetCounterRef
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSAMD5XE5XSTREAMI2CPORT::GetCounterRef()
{
  return counterref;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSAMD5XE5XSTREAMI2CPORT::SetCounterRef(XDWORD counterref)
* @brief      SetCounterRef
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  counterref :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSAMD5XE5XSTREAMI2CPORT::SetCounterRef(XDWORD counterref)
{
  this->counterref = counterref;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         I2C_HandleTypeDef* DIOSAMD5XE5XSTREAMI2CPORT::GetHandleI2C()
* @brief      GetHandleI2C
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     I2C_HandleTypeDef* :
*
* --------------------------------------------------------------------------------------------------------------------*/
/*
I2C_HandleTypeDef* DIOSAMD5XE5XSTREAMI2CPORT::GetHandleI2C()
{
  return hi2c;
}
*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSAMD5XE5XSTREAMI2CPORT::SetHandleI2C(I2C_HandleTypeDef* hi2c)
* @brief      SetHandleI2C
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  hi2c :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
/*
void DIOSAMD5XE5XSTREAMI2CPORT::SetHandleI2C(I2C_HandleTypeDef* hi2c)
{
  this->hi2c = hi2c;
}
*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSAMD5XE5XSTREAMI2CPORT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSAMD5XE5XSTREAMI2CPORT::Clean()
{
  counterref        = 0;
  //--- ABRHAMD5XE5X ------------------
  //hi2c              = NULL;
}



/*--------------------------------------------------------------------------------------------------------------------*/
/* DIOSAMD5XE5XSTREAMI2C                                                                                              */
/*--------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSAMD5XE5XSTREAMI2C::DIOSAMD5XE5XSTREAMI2C()
* @brief      Constructor
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSAMD5XE5XSTREAMI2C::DIOSAMD5XE5XSTREAMI2C() : DIOSTREAMI2C()
{
  Clean();

  AddState( DIOSTREAMI2C_FSMSTATE_NONE            ,
            DIOSTREAMI2C_FSMEVENT_CONNECTED       , DIOSTREAMI2C_FSMSTATE_CONNECTED        ,
            DIOSTREAMI2C_FSMEVENT_DISCONNECTING   , DIOSTREAMI2C_FSMSTATE_DISCONNECTING    ,
            XFSMACHINESTATE_EVENTDEFEND);

  AddState( DIOSTREAMI2C_FSMSTATE_CONNECTED       ,
            DIOSTREAMI2C_FSMEVENT_WAITINGTOREAD   , DIOSTREAMI2C_FSMSTATE_WAITINGTOREAD    ,
            DIOSTREAMI2C_FSMEVENT_DISCONNECTING   , DIOSTREAMI2C_FSMSTATE_DISCONNECTING    ,
            XFSMACHINESTATE_EVENTDEFEND);

  AddState( DIOSTREAMI2C_FSMSTATE_WAITINGTOREAD   ,
            DIOSTREAMI2C_FSMEVENT_CONNECTED       , DIOSTREAMI2C_FSMSTATE_CONNECTED        ,
            DIOSTREAMI2C_FSMEVENT_DISCONNECTING   , DIOSTREAMI2C_FSMSTATE_DISCONNECTING    ,
            XFSMACHINESTATE_EVENTDEFEND);

  AddState( DIOSTREAMI2C_FSMSTATE_DISCONNECTING   ,
            DIOSTREAMI2C_FSMEVENT_CONNECTED       , DIOSTREAMI2C_FSMSTATE_CONNECTED        ,
            DIOSTREAMI2C_FSMEVENT_WAITINGTOREAD   , DIOSTREAMI2C_FSMSTATE_WAITINGTOREAD    ,
            XFSMACHINESTATE_EVENTDEFEND);

  threadconnection = CREATEXTHREAD(XTHREADGROUPID_DIOSTREAMI2C, __L("DIOSAMD5XE5XSTREAMI2C::DIOSAMD5XE5XSTREAMI2C"), ThreadConnection, (void*)this);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSAMD5XE5XSTREAMI2C::~DIOSAMD5XE5XSTREAMI2C()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSAMD5XE5XSTREAMI2C::~DIOSAMD5XE5XSTREAMI2C()
{
  Close();

  if(threadconnection) DELETEXTHREAD(XTHREADGROUPID_DIOSTREAMI2C, threadconnection);

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMSTATUS DIOSAMD5XE5XSTREAMI2C::GetConnectStatus()
* @brief      GetConnectStatus
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     DIOSTREAMSTATUS :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMSTATUS DIOSAMD5XE5XSTREAMI2C::GetConnectStatus()
{
  if(!config) return DIOSTREAMSTATUS_DISCONNECTED;

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSAMD5XE5XSTREAMI2C::Open()
* @brief      Open
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSAMD5XE5XSTREAMI2C::Open()
{
  if(!threadconnection)  return false;
  if(!config)           return false;

  for(int c=0; c<DIOSAMD5XE5XSTREAMI2C_MAXHANDLES; c++)
    {
      if(DIOSAMD5XE5XSTREAMI2C::handles[c] == this) return false;

      if(!DIOSAMD5XE5XSTREAMI2C::handles[c])
        {
          indexhandle = c;
          DIOSAMD5XE5XSTREAMI2C::handles[indexhandle] = this;
          break;
        }
    }

  if(indexhandle == -1) return false;

  if(config->GetLocalAddress()  != DIOSTREAMI2CCONFIG_ADDRESSINVALID)  localaddress  = (config->GetLocalAddress()  << 1);
  if(config->GetRemoteAddress() != DIOSTREAMI2CCONFIG_ADDRESSINVALID)  remoteaddress = (config->GetRemoteAddress() << 1);

  indexport = config->GetPort()-1;


  //--- ABRHAMD5XE5X ------------------


  //if(!DIOSAMD5XE5XSTREAMI2C::ports[indexport])
  //  {
  //    DIOSAMD5XE5XSTREAMI2CPORT* port = new DIOSAMD5XE5XSTREAMI2CPORT();
  //    if(!port) return false;

  //    hi2c = new I2C_HandleTypeDef();
  //    if(!hi2c)
  //      {
  //        delete port;
  //        return false;
  //      }

  //    switch(config->GetPort())
  //      {
  //        case  1 : hi2c->Instance = I2C1;       break;
  //        case  2 : hi2c->Instance = I2C2;       break;
  //        default : return false;
  //      }

  //    #if defined(HW_STM32F0XX) || defined(HW_STM32F3XX)
  //    hi2c->Init.Timing           = 0x2000090E;
  //    #endif

  //    #if defined(STM32F411xE) || defined(STM32F446x)
  //    hi2c->Init.ClockSpeed      = 100000;
  //    #endif

  //    hi2c->Init.OwnAddress1      = localaddress;

  //    switch(config->GetAddressSize())
  //      {
  //        case DIOSTREAMI2CCONFIG_ADDRESSSIZE_DEFAULT :
  //        case DIOSTREAMI2CCONFIG_ADDRESSSIZE_7BITS   : hi2c->Init.AddressingMode   = I2C_ADDRESSINGMODE_7BIT;    break;
  //        case DIOSTREAMI2CCONFIG_ADDRESSSIZE_10BITS  : hi2c->Init.AddressingMode   = I2C_ADDRESSINGMODE_10BIT;   break;
  //      }

  //    hi2c->Init.DualAddressMode  = I2C_DUALADDRESS_DISABLE;
  //    hi2c->Init.OwnAddress2      = 0;
  //    #if defined(HW_STM32F0XX) || defined(HW_STM32F3XX)
  //    hi2c->Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  //    #endif
  //    hi2c->Init.GeneralCallMode  = I2C_GENERALCALL_DISABLE;
  //    hi2c->Init.NoStretchMode    = config->IsStretchActive()?I2C_NOSTRETCH_ENABLE:I2C_NOSTRETCH_DISABLE;

  //    if(HAL_I2C_Init(hi2c) != HAL_OK)
  //      {
  //        return false;
  //      }

  //    #if defined(HW_STM32F0XX) || defined(HW_STM32F3XX)
  //    if(HAL_I2CEx_ConfigAnalogFilter(hi2c, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  //      {
  //        return false;
  //      }
  //    #endif

  //    if(config->GetMode() == DIOSTREAMMODE_MASTER)
  //      {
  //        /*
  //        if(HAL_I2C_IsDeviceReady(hi2c, (uint16_t)remoteaddress, 3, 1000) != HAL_OK)
  //          {
  //            return false;
  //          }
  //        */
  //      }

  //    port->SetHandleI2C(hi2c);
  //    DIOSAMD5XE5XSTREAMI2C::ports[indexport] = port;
  //  }
  // else
  //  {
  //    hi2c = DIOSAMD5XE5XSTREAMI2C::ports[indexport]->GetHandleI2C();
  //    DIOSAMD5XE5XSTREAMI2C::ports[indexport]->SetCounterRef(DIOSAMD5XE5XSTREAMI2C::ports[indexport]->GetCounterRef()+1);
  //  }



  SetEvent(DIOSTREAMI2C_FSMEVENT_CONNECTED);

  status = DIOSTREAMSTATUS_CONNECTED;

  memset(bufferdata, 0, DIOSTREAM_MAXBUFFER);

  ResetXBuffers();
  ResetConnectionStatistics();

  return threadconnection->Ini();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSAMD5XE5XSTREAMI2C::WaitToFilledReadingBuffer(int filledto, int timeout)
* @brief      WaitToFilledReadingBuffer
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  filledto :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSAMD5XE5XSTREAMI2C::WaitToFilledReadingBuffer(int filledto, int timeout)
{
  if(filledto == DIOSTREAM_SOMETHINGTOREAD) sizebufferdata = 1; else sizebufferdata = filledto;

  //--- ABRHAMD5XE5X ------------------

  /*
  switch(config->GetMode())
    {
      case DIOSTREAMMODE_MASTER     : HAL_I2C_Master_Receive_IT(hi2c, (uint16_t)remoteaddress, (uint8_t*)bufferdata, sizebufferdata);
                                      break;

      case DIOSTREAMMODE_SEMIMASTER :
      case DIOSTREAMMODE_SLAVE      : HAL_I2C_Slave_Receive_IT(hi2c, (uint8_t*)bufferdata, sizebufferdata);
                                      break;
    }
  */
  return DIOSTREAM::WaitToFilledReadingBuffer(sizebufferdata, timeout);
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOSAMD5XE5XSTREAMI2C::ReadDirect(XBYTE* buffer, XDWORD size)
* @brief      ReadDirect
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  buffer :
* @param[in]  size :
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSAMD5XE5XSTREAMI2C::ReadDirect(XBYTE* buffer, XDWORD size)
{
  if(!config)                                          return 0;
  if(GetConnectStatus()==DIOSTREAMSTATUS_DISCONNECTED) return 0;

  XDWORD br = 0;

  //--- ABRHAMD5XE5X ------------------
  /*

  switch(config->GetMode())
    {
      case DIOSTREAMMODE_MASTER     : if(HAL_I2C_Master_Receive(hi2c, (uint16_t)remoteaddress, buffer, size, 1000) == HAL_OK) br = size;
                                      break;

      case DIOSTREAMMODE_SEMIMASTER :
      case DIOSTREAMMODE_SLAVE      : if(HAL_I2C_Slave_Receive(hi2c, buffer, size, 1000) == HAL_OK) br = size;
                                      break;
    }
  */

  return br;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOSAMD5XE5XSTREAMI2C::WriteDirect(XBYTE* buffer, XDWORD size)
* @brief      WriteDirect
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  buffer :
* @param[in]  size :
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSAMD5XE5XSTREAMI2C::WriteDirect(XBYTE* buffer, XDWORD size)
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
      case DIOSTREAMMODE_SEMIMASTER   : if(HAL_I2C_Master_Transmit(hi2c, (uint16_t)remoteaddress, buffer, size, 1000) == HAL_OK) bw = size;
                                        break;

      case DIOSTREAMMODE_SLAVE        : if(HAL_I2C_Slave_Transmit(hi2c, buffer, size, 1000) == HAL_OK) bw = size;
                                        break;
    }
  */

  return bw;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOSAMD5XE5XSTREAMI2C::Write(XBYTE* buffer, XDWORD size)
* @brief      Write
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  buffer :
* @param[in]  size :
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSAMD5XE5XSTREAMI2C::Write(XBYTE* buffer, XDWORD size)
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
 *  @fn         bool DIOSAMD5XE5XSTREAMI2C::Disconnect()
 *  @brief      Disconnect
 *  @ingroup    PLATFORM_SAMD5XE5X
 *
 *  ""
 *  ""
 *
 *  @return     bool : true if is succesful.
 *
 * --------------------------------------------------------------------------------------------------------------------*/
bool DIOSAMD5XE5XSTREAMI2C::Disconnect()
 {
   return false;
 }



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSAMD5XE5XSTREAMI2C::Close()
* @brief      Close
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSAMD5XE5XSTREAMI2C::Close()
{
  if(!threadconnection) return false;

  threadconnection->End();

  if(GetConnectStatus()==DIOSTREAMSTATUS_DISCONNECTED) return false;

  if(!DIOSAMD5XE5XSTREAMI2C::handles[indexhandle]) return false;

  DIOSAMD5XE5XSTREAMI2C::handles[indexhandle] = NULL;

  //--- ABRHAMD5XE5X ------------------

  /*
  if(!DIOSAMD5XE5XSTREAMI2C::ports[indexport]->GetCounterRef())
    {
      HAL_I2C_DeInit(DIOSAMD5XE5XSTREAMI2C::ports[indexport]->GetHandleI2C());

      delete DIOSAMD5XE5XSTREAMI2C::ports[indexport]->GetHandleI2C();
      delete DIOSAMD5XE5XSTREAMI2C::ports[indexport];

      DIOSAMD5XE5XSTREAMI2C::ports[indexport] = NULL;
    }
   else
    {
      DIOSAMD5XE5XSTREAMI2C::ports[indexport]->SetCounterRef(DIOSAMD5XE5XSTREAMI2C::ports[indexport]->GetCounterRef()-1);
    }
  */

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSAMD5XE5XSTREAMI2C::CleanBuffers()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSAMD5XE5XSTREAMI2C::CleanBuffers()
{
  return false;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef* hi2c)
* @brief      AL_I2C_MasterRxCpltCallback
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  hi2c :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
//--- ABRHAMD5XE5X ------------------
/*
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef* hi2c)
{
  int indexport = -1;

  if(hi2c->Instance == I2C1) indexport = 0;
  if(hi2c->Instance == I2C2) indexport = 1;

  for(int c=0; c<DIOSAMD5XE5XSTREAMI2C_MAXHANDLES; c++)
    {
      if(DIOSAMD5XE5XSTREAMI2C::handles[c])
        {
          if(DIOSAMD5XE5XSTREAMI2C::handles[c]->indexport  == indexport)
            {
              if(DIOSAMD5XE5XSTREAMI2C::handles[c]->GetConnectStatus() == DIOSTREAMSTATUS_CONNECTED)
                {
                  if(!DIOSAMD5XE5XSTREAMI2C::handles[c]->IsBlockRead())
                    {
                      if(!DIOSAMD5XE5XSTREAMI2C::handles[c]->inbuffer->IsBlocked())
                        {
                          if(DIOSAMD5XE5XSTREAMI2C::handles[c]->readcache[indexport].GetSize())
                            {
                              DIOSAMD5XE5XSTREAMI2C::handles[c]->inbuffer->Add(DIOSAMD5XE5XSTREAMI2C::handles[c]->readcache);
                              DIOSAMD5XE5XSTREAMI2C::handles[c]->readcache[indexport].Delete();
                            }

                          DIOSAMD5XE5XSTREAMI2C::handles[c]->inbuffer->Add(DIOSAMD5XE5XSTREAMI2C::handles[c]->bufferdata, DIOSAMD5XE5XSTREAMI2C::handles[c]->sizebufferdata);
                        }
                       else
                        {
                          DIOSAMD5XE5XSTREAMI2C::handles[c]->readcache[indexport].Add(DIOSAMD5XE5XSTREAMI2C::handles[c]->bufferdata, DIOSAMD5XE5XSTREAMI2C::handles[c]->sizebufferdata);
                        }
                    }
                }

              DIOSAMD5XE5XSTREAMI2C::handles[c]->sizebufferdata = 0;
            }
        }
    }
}
*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef* hi2c)
* @brief      AL_I2C_SlaveRxCpltCallback
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  hi2c :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
//--- ABRHAMD5XE5X ------------------
/*
void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef* hi2c)
{
  HAL_I2C_MasterRxCpltCallback(hi2c);
}
*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void HAL_I2C_ErrorCallback(I2C_HandleTypeDef*hi2c)
* @brief      AL_I2C_ErrorCallback
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  I2C_HandleTypeDef*hi2c :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
/*
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c)
{
  XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("I2C comunication error  %d"), hi2c->ErrorCode);
}
*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSAMD5XE5XSTREAMI2C::ThreadConnection(void* param)
* @brief      ThreadConnection
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  param :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSAMD5XE5XSTREAMI2C::ThreadConnection(void* param)
{
  DIOSAMD5XE5XSTREAMI2C* diostream = (DIOSAMD5XE5XSTREAMI2C*)param;
  if(!diostream) return;

  if(diostream->GetEvent()==DIOSTREAMI2C_FSMEVENT_NONE) // No hay nuevos Eventos
    {
      switch(diostream->GetCurrentState())
        {
          case DIOSTREAMI2C_FSMSTATE_NONE                   : break;

          case DIOSTREAMI2C_FSMSTATE_CONNECTED              : break;

          case DIOSTREAMI2C_FSMSTATE_WAITINGTOREAD          : if(!diostream->IsBlockRead())
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

          case DIOSTREAMI2C_FSMSTATE_DISCONNECTING          : break;

        }
    }
   else
    {
      if(diostream->GetEvent()<DIOSTREAMI2C_LASTEVENT)
        {
          diostream->CheckTransition();

          switch(diostream->GetCurrentState())
            {
              case DIOSTREAMI2C_FSMSTATE_NONE               : break;

              case DIOSTREAMI2C_FSMSTATE_CONNECTED          : { DIOSTREAMXEVENT xevent(diostream,DIOSTREAMXEVENT_TYPE_CONNECTED);
                                                                xevent.SetDIOStream(diostream);
                                                                diostream->PostEvent(&xevent);

                                                                diostream->SetEvent(DIOSTREAMI2C_FSMEVENT_WAITINGTOREAD);
                                                              }
                                                              break;

              case DIOSTREAMI2C_FSMSTATE_WAITINGTOREAD      : break;

              case DIOSTREAMI2C_FSMSTATE_DISCONNECTING      : { DIOSTREAMXEVENT xevent(diostream,DIOSTREAMXEVENT_TYPE_DISCONNECTED);
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
* @fn         void DIOSAMD5XE5XSTREAMI2C::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSAMD5XE5XSTREAMI2C::Clean()
{
  //--- ABRHAMD5XE5X ------------------
  //hi2c              = NULL;
  localaddress      = 0;
  remoteaddress     = 0;
  threadconnection   = NULL;
  indexhandle       = -1;
  indexport         = -1;
  sizebufferdata    = 0;
}



#endif
