/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOModBus.cpp
*
* @class      DIOMODBUS
* @brief      Data Input/Output Mod Bus protocol class
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @copyright  Copyright(c) 2008 - 2016 GEN Group.
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


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XFactory.h"
#include "XSleep.h"
#include "XTimer.h"
#include "DIOStream.h"

#include "DIOModBus.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOMODBUS::DIOMODBUS(DIOSTREAM* diostream, DIOMODBUSMODE mode)
* @brief      Constructor
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  DIOSTREAM* :
* @param[in]   DIOMODBUSMODE mode :
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOMODBUS::DIOMODBUS(DIOSTREAM* diostream, DIOMODBUSMODE mode)

{
  Clean();

  this->diostream   = diostream;
  this->mode        = mode;

  xtimer = GEN_XFACTORY.CreateTimer(); 
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOMODBUS::~DIOMODBUS()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOMODBUS::~DIOMODBUS()
{
  Disconnect();

  GEN_XFACTORY.DeleteTimer(xtimer);

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAM* DIOMODBUS::GetDIOStream()
* @brief      GetDIOStream
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     DIOSTREAM* :
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSTREAM* DIOMODBUS::GetDIOStream()
{
  return diostream;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOMODBUSMODE DIOMODBUS::GetMode()
* @brief      GetMode
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     DIOMODBUSMODE :
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOMODBUSMODE DIOMODBUS::GetMode()
{
  return mode;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOMODBUS::SetMode(DIOMODBUSMODE mode)
* @brief      SetMode
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  mode :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOMODBUS::SetMode(DIOMODBUSMODE mode)
{
  this->mode = mode;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOMODBUS::Connect(XBYTE unit, int timeout)
* @brief      Connect
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  unit :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOMODBUS::Connect(XBYTE unit, int timeout)
{
  if(!diostream)                                                  return false;
  if(diostream->GetConnectStatus()!=DIOSTREAMSTATUS_DISCONNECTED) return false;

  this->unit = unit;

  if(!diostream->Open())  return false;

  return diostream->WaitToConnected(timeout);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE DIOMODBUS::GetUnit()
* @brief      GetUnit
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XBYTE :
*
*---------------------------------------------------------------------------------------------------------------------*/
XBYTE DIOMODBUS::GetUnit()
{
  return unit;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOMODBUS::SetUnit(XBYTE unit)
* @brief      SetUnit
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  unit :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOMODBUS::SetUnit(XBYTE unit)
{
  this->unit = unit;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOMODBUS::ReadHoldingRegisters(XWORD address, XWORD nregisters, XBUFFER& answer, int timeout)
* @brief      ReadHoldingRegisters
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  address :
* @param[in]  nregisters :
* @param[in]  answer :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOMODBUS::ReadHoldingRegisters(XWORD address, XWORD nregisters, XBUFFER& answer, int timeout)
{
  if(!diostream)                                                 return false;
  if(diostream->GetConnectStatus() != DIOSTREAMSTATUS_CONNECTED) return false;

  answer.Delete();

  switch(mode)
    {
      case DIOMODBUSMODE_UNKNOWN    : return false;

      case DIOMODBUSMODE_RTU        :

      case DIOMODBUSMODE_ASCII      : return false; //Not Implemented yet!!!

      case DIOMODBUSMODE_TCPIP      : { XBUFFER datawrite;

                                        datawrite.Add((XWORD) 0x0000);
                                        datawrite.Add((XWORD) 0x0000);
                                        datawrite.Add((XWORD) 0x0006);
                                        datawrite.Add((XBYTE) unit);
                                        datawrite.Add((XBYTE) DIOMODBUS_FUNCTION_READ_HOLDING_REGISTERS);
                                        datawrite.Add((XWORD) address);
                                        datawrite.Add((XWORD) nregisters);

                                        diostream->Write(datawrite);

                                        if(!diostream->WaitToFlushOutXBuffer(timeout)) return false;

                                        xtimer->Reset();

                                        XDWORD size = nregisters*sizeof(XWORD) + 9;

                                        while(diostream->GetInXBuffer()->GetSize() != size)
                                          {
                                            if(xtimer->GetMeasureSeconds() >= (XDWORD)timeout)
                                              {
                                                diostream->GetInXBuffer()->Delete();
                                                return false;
                                              }

                                            GEN_XSLEEP.MilliSeconds(10);
                                          }

                                        answer.Resize(size);
                                        answer.FillBuffer(0x00);

                                        if(!diostream->Read(answer.Get(), size)) return false;

                                        if(answer.GetSize() != size) return false;

                                        if(answer.Get()[7] & 0x80)   return false;

                                        XBYTE head[10];
                                        answer.Extract(head, 0 , 9);
                                      }
                                      break;
    }

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOMODBUS::ReadInputRegisters(XWORD address, XWORD nregisters, XBUFFER& answer, int timeout)
* @brief      ReadInputRegisters
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  address :
* @param[in]  nregisters :
* @param[in]  answer :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOMODBUS::ReadInputRegisters(XWORD address, XWORD nregisters, XMAP<XWORD, XWORD>& registers, int timeout)
{
  XBUFFER ask;
  XBUFFER answer;
  bool    status;

  ask.Add((XWORD)address);
  ask.Add((XWORD)nregisters);

  status = MakeCommand(DIOMODBUS_FUNCTION_READ_INPUT_REGISTERS, ask, answer, timeout);
  if(status)
    {
      int sizeanswer =   1                              // Device Address
                       + 1                              // Function code
                       + 1                              // Size data
                       + (nregisters * sizeof(XWORD));  // Data


      if(answer.GetSize() == (XDWORD)sizeanswer)
        {
          XWORD addressindex  = address;
          XWORD registryvalue = 0;

          for(int c=0; c<nregisters; c++)
            {
              answer.Get(registryvalue, 3 + c*sizeof(XWORD));

              registers.Add(addressindex, registryvalue);

              addressindex++;
            }
        }
    }

  return status;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOMODBUS::WriteSingleRegister(XWORD address, XBUFFER& value, int timeout)
* @brief      WriteSingleRegister
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  address :
* @param[in]  value :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOMODBUS::WriteSingleRegister(XWORD address, XWORD value, int timeout)
{
  XBUFFER ask;
  XBUFFER answer;
  bool    status;

  ask.Add((XWORD)address);
  ask.Add((XWORD)value);

  status = MakeCommand(DIOMODBUS_FUNCTION_WRITE_SINGLE_REGISTER, ask, answer, timeout);
  if(status)
    {
      int sizeanswer =   1               // Device Address
                       + 1               // Function code
                       + 2 * sizeof(XWORD);  // Data

      if(answer.GetSize() == (XDWORD)sizeanswer)
        {

        } else status = false;
    }

  return status;
}





/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOMODBUS::Disconnect()
* @brief      Disconnect
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOMODBUS::Disconnect()
{
  if(diostream)
    {
      diostream->Disconnect();
      diostream->Close();

      diostream = NULL;
    }


  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOMODBUS::MakeCommand(DIOMODBUS_FUNCTION function, XBUFFER& ask, XBUFFER& answer, int timeout)
* @brief      MakeCommand
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  function :
* @param[in]  ask :
* @param[in]  answer :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOMODBUS::MakeCommand(DIOMODBUS_FUNCTION function, XBUFFER& ask, XBUFFER& answer, int timeout)
{
  if(!diostream)                                                 return false;
  if(diostream->GetConnectStatus() != DIOSTREAMSTATUS_CONNECTED) return false;

  XBUFFER datawrite;

  answer.Delete();

  bool status = false;

  switch(mode)
    {
      case DIOMODBUSMODE_UNKNOWN    : break;

      case DIOMODBUSMODE_RTU        : { datawrite.Add((XBYTE) unit);
                                        datawrite.Add((XBYTE) function);
                                        datawrite.Add(ask);

                                        XWORD crc16 = CRC16(datawrite);

                                        datawrite.Add((XWORD)crc16);

                                        diostream->Write(datawrite);

                                        if(!diostream->WaitToFlushOutXBuffer(timeout))         return false;
                                        if(!diostream->WaitToFilledReadingBuffer(3, timeout))  return false;

                                        if(diostream->GetInXBuffer()->GetByte(0) != unit)      return false;
                                        if(diostream->GetInXBuffer()->GetByte(1) != function)  return false;

                                        XDWORD sizeanswer = 0;

                                        switch(function)
                                          {
                                            case DIOMODBUS_FUNCTION_READ_COILS                       : DIOMODBUSMODE_SIZEANSWERVAR;  break;
                                            case DIOMODBUS_FUNCTION_READ_DISCRETE_INPUTS             : DIOMODBUSMODE_SIZEANSWERVAR;  break;
                                            case DIOMODBUS_FUNCTION_READ_HOLDING_REGISTERS           : DIOMODBUSMODE_SIZEANSWERVAR;  break;
                                            case DIOMODBUS_FUNCTION_READ_INPUT_REGISTERS             : DIOMODBUSMODE_SIZEANSWERVAR;  break;
                                            case DIOMODBUS_FUNCTION_WRITE_SINGLE_COIL                : DIOMODBUSMODE_SIZEANSWERFIX;  break;
                                            case DIOMODBUS_FUNCTION_WRITE_SINGLE_REGISTER            : DIOMODBUSMODE_SIZEANSWERFIX;  break;
                                            case DIOMODBUS_FUNCTION_WRITE_MULTIPLE_COILS             : DIOMODBUSMODE_SIZEANSWERFIX;  break;
                                            case DIOMODBUS_FUNCTION_WRITE_MULTIPLE_REGISTERS         : DIOMODBUSMODE_SIZEANSWERFIX;  break;
                                            case DIOMODBUS_FUNCTION_READ_FILE_RECORD                 : break;
                                            case DIOMODBUS_FUNCTION_WRITE_FILE_RECORD                : break;
                                            case DIOMODBUS_FUNCTION_MASK_WRITE_REGISTER              : break;
                                            case DIOMODBUS_FUNCTION_READWRITE_MULTIPLE_REGISTERS     : break;
                                            case DIOMODBUS_FUNCTION_READ_FIFO_QUEUE                  : break;
                                            case DIOMODBUS_FUNCTION_ENCAPSULATED_INTERFACE_TRANSPORT : break;

                                          }

                                        if(!sizeanswer) break;

                                        if(!diostream->WaitToFilledReadingBuffer(sizeanswer, timeout)) return false;

                                        answer.Resize(sizeanswer);

                                        if(!diostream->Read(answer)) return false;

                                        XWORD CRCread  = 0;
                                        XWORD CRCcheck;

                                        answer.Extract(CRCread, sizeanswer-2);

                                        CRCcheck = CRC16(answer);

                                        if(CRCcheck != CRCread)  return false;

                                        status = true;
                                      }
                                      break;

      case DIOMODBUSMODE_ASCII      : break;

      case DIOMODBUSMODE_TCPIP      : break;
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWORD DIOMODBUS::CRC16(XBUFFER& data)
* @brief      CRC16
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  data :
*
* @return     XWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XWORD DIOMODBUS::CRC16(XBUFFER& data)
{
  XWORD poly16 = 0xA001;
  XWORD LSB;
  XWORD crc    = 0xFFFF;

  for(int d=0; d<(int)data.GetSize(); d++)
    {
      crc = ((crc^data.Get()[d]) | 0xFF00) & (crc | 0x00FF);

      for(int c=0; c<8; c++)
        {
          LSB=(crc & 0x0001);
          crc=crc/2;

          if(LSB) crc = crc ^ poly16;
        }
    }

  SWAPWORD(crc);

  return crc;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOMODBUS::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOMODBUS::Clean()
{
  diostream   = NULL;

  mode        = DIOMODBUSMODE_UNKNOWN;
  unit        = 0;

  xtimer      = NULL;
}