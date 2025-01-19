/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOModBus_Client.cpp
* 
* @class      DIOMODBUS_CLIENT
* @brief      Data Input/Output Mod Bus client protocol class
* @ingroup    DATAIO
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
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIOModBus_Client.h"

#include "XFactory.h"
#include "XSleep.h"
#include "XTimer.h"
#include "DIOStream.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOMODBUS_CLIENT::DIOMODBUS_CLIENT(DIOSTREAM* diostream, DIOMODBUS_CLIENTMODE mode)
* @brief      Constructor of class
* @ingroup    DATAIO
*
* @param[in]  diostream :
* @param[in]  mode :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOMODBUS_CLIENT::DIOMODBUS_CLIENT(DIOSTREAM* diostream, DIOMODBUS_CLIENTMODE mode)
{
  Clean();

  this->diostream   = diostream;
  this->mode        = mode;

  GEN_XFACTORY_CREATE(xtimer, CreateTimer()) 
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOMODBUS_CLIENT::~DIOMODBUS_CLIENT()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOMODBUS_CLIENT::~DIOMODBUS_CLIENT()
{
  Disconnect();

  GEN_XFACTORY.DeleteTimer(xtimer);

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAM* DIOMODBUS_CLIENT::GetDIOStream()
* @brief      Get DIO stream
* @ingroup    DATAIO
*
* @return     DIOSTREAM* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAM* DIOMODBUS_CLIENT::GetDIOStream()
{
  return diostream;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOMODBUS_CLIENTMODE DIOMODBUS_CLIENT::GetMode()
* @brief      Get mode
* @ingroup    DATAIO
*
* @return     DIOMODBUS_CLIENTMODE :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOMODBUS_CLIENTMODE DIOMODBUS_CLIENT::GetMode()
{
  return mode;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOMODBUS_CLIENT::SetMode(DIOMODBUS_CLIENTMODE mode)
* @brief      Set mode
* @ingroup    DATAIO
*
* @param[in]  mode :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOMODBUS_CLIENT::SetMode(DIOMODBUS_CLIENTMODE mode)
{
  this->mode = mode;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOMODBUS_CLIENT::Connect(XBYTE unit, int timeout)
* @brief      Connect
* @ingroup    DATAIO
*
* @param[in]  unit :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOMODBUS_CLIENT::Connect(XBYTE unit, int timeout)
{
  if(!diostream)                                                  return false;
  if(diostream->GetStatus()!=DIOSTREAMSTATUS_DISCONNECTED) return false;

  this->unit = unit;

  if(!diostream->Open())  return false;

  return diostream->WaitToConnected(timeout);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE DIOMODBUS_CLIENT::GetUnit()
* @brief      Get unit
* @ingroup    DATAIO
*
* @return     XBYTE :
*
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE DIOMODBUS_CLIENT::GetUnit()
{
  return unit;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOMODBUS_CLIENT::SetUnit(XBYTE unit)
* @brief      Set unit
* @ingroup    DATAIO
*
* @param[in]  unit :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOMODBUS_CLIENT::SetUnit(XBYTE unit)
{
  this->unit = unit;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOMODBUS_CLIENT::ReadHoldingRegisters(XWORD address, XWORD nregisters, XBUFFER& answer, int timeout)
* @brief      Read holding registers
* @ingroup    DATAIO
*
* @param[in]  address :
* @param[in]  nregisters :
* @param[in]  answer :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOMODBUS_CLIENT::ReadHoldingRegisters(XWORD address, XWORD nregisters, XBUFFER& answer, int timeout)
{
  if(!diostream)                                                 return false;
  if(diostream->GetStatus() != DIOSTREAMSTATUS_CONNECTED) return false;

  answer.Delete();

  switch(mode)
    {
      case DIOMODBUS_CLIENTMODE_UNKNOWN     : return false;

      case DIOMODBUS_CLIENTMODE_RTU         :

      case DIOMODBUS_CLIENTMODE_ASCII       : return false; //Not Implemented yet!!!

      case DIOMODBUS_CLIENTMODE_TCPIP       : { XBUFFER datawrite;

                                                datawrite.Add((XWORD) 0x0000);
                                                datawrite.Add((XWORD) 0x0000);
                                                datawrite.Add((XWORD) 0x0006);
                                                datawrite.Add((XBYTE) unit);
                                                datawrite.Add((XBYTE) DIOMODBUS_CLIENT_FUNCTION_READ_HOLDING_REGISTERS);
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
* @fn         bool DIOMODBUS_CLIENT::ReadInputRegisters(XWORD address, XWORD nregisters, XBUFFER& answer, int timeout)
* @brief      Read input registers
* @ingroup    DATAIO
*
* @param[in]  address :
* @param[in]  nregisters :
* @param[in]  answer :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOMODBUS_CLIENT::ReadInputRegisters(XWORD address, XWORD nregisters, XMAP<XWORD, XWORD>& registers, int timeout)
{
  XBUFFER ask;
  XBUFFER answer;
  bool    status;

  ask.Add((XWORD)address);
  ask.Add((XWORD)nregisters);

  status = MakeCommand(DIOMODBUS_CLIENT_FUNCTION_READ_INPUT_REGISTERS, ask, answer, timeout);
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
* @fn         bool DIOMODBUS_CLIENT::WriteSingleRegister(XWORD address, XBUFFER& value, int timeout)
* @brief      Write single register
* @ingroup    DATAIO
*
* @param[in]  address :
* @param[in]  value :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOMODBUS_CLIENT::WriteSingleRegister(XWORD address, XWORD value, int timeout)
{
  XBUFFER ask;
  XBUFFER answer;
  bool    status;

  ask.Add((XWORD)address);
  ask.Add((XWORD)value);

  status = MakeCommand(DIOMODBUS_CLIENT_FUNCTION_WRITE_SINGLE_REGISTER, ask, answer, timeout);
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
* @fn         bool DIOMODBUS_CLIENT::Disconnect()
* @brief      Disconnect
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOMODBUS_CLIENT::Disconnect()
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
* @fn         bool DIOMODBUS_CLIENT::MakeCommand(DIOMODBUS_CLIENT_FUNCTION function, XBUFFER& ask, XBUFFER& answer, int timeout)
* @brief      Make command
* @ingroup    DATAIO
*
* @param[in]  function :
* @param[in]  ask :
* @param[in]  answer :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOMODBUS_CLIENT::MakeCommand(DIOMODBUS_CLIENT_FUNCTION function, XBUFFER& ask, XBUFFER& answer, int timeout)
{
  if(!diostream)                                                 return false;
  if(diostream->GetStatus() != DIOSTREAMSTATUS_CONNECTED) return false;

  XBUFFER datawrite;

  answer.Delete();

  bool status = false;

  switch(mode)
    {
      case DIOMODBUS_CLIENTMODE_UNKNOWN     : break;

      case DIOMODBUS_CLIENTMODE_RTU         : { datawrite.Add((XBYTE) unit);
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
                                                    case DIOMODBUS_CLIENT_FUNCTION_READ_COILS                       : DIOMODBUS_CLIENTMODE_SIZEANSWERVAR;  break;
                                                    case DIOMODBUS_CLIENT_FUNCTION_READ_DISCRETE_INPUTS             : DIOMODBUS_CLIENTMODE_SIZEANSWERVAR;  break;
                                                    case DIOMODBUS_CLIENT_FUNCTION_READ_HOLDING_REGISTERS           : DIOMODBUS_CLIENTMODE_SIZEANSWERVAR;  break;
                                                    case DIOMODBUS_CLIENT_FUNCTION_READ_INPUT_REGISTERS             : DIOMODBUS_CLIENTMODE_SIZEANSWERVAR;  break;
                                                    case DIOMODBUS_CLIENT_FUNCTION_WRITE_SINGLE_COIL                : DIOMODBUS_CLIENTMODE_SIZEANSWERFIX;  break;
                                                    case DIOMODBUS_CLIENT_FUNCTION_WRITE_SINGLE_REGISTER            : DIOMODBUS_CLIENTMODE_SIZEANSWERFIX;  break;
                                                    case DIOMODBUS_CLIENT_FUNCTION_WRITE_MULTIPLE_COILS             : DIOMODBUS_CLIENTMODE_SIZEANSWERFIX;  break;
                                                    case DIOMODBUS_CLIENT_FUNCTION_WRITE_MULTIPLE_REGISTERS         : DIOMODBUS_CLIENTMODE_SIZEANSWERFIX;  break;
                                                    case DIOMODBUS_CLIENT_FUNCTION_READ_FILE_RECORD                 : break;
                                                    case DIOMODBUS_CLIENT_FUNCTION_WRITE_FILE_RECORD                : break;
                                                    case DIOMODBUS_CLIENT_FUNCTION_MASK_WRITE_REGISTER              : break;
                                                    case DIOMODBUS_CLIENT_FUNCTION_READWRITE_MULTIPLE_REGISTERS     : break;
                                                    case DIOMODBUS_CLIENT_FUNCTION_READ_FIFO_QUEUE                  : break;
                                                    case DIOMODBUS_CLIENT_FUNCTION_ENCAPSULATED_INTERFACE_TRANSPORT : break;

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

      case DIOMODBUS_CLIENTMODE_ASCII       : break;

      case DIOMODBUS_CLIENTMODE_TCPIP       : break;
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWORD DIOMODBUS_CLIENT::CRC16(XBUFFER& data)
* @brief      CRC16
* @ingroup    DATAIO
*
* @param[in]  data :
*
* @return     XWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XWORD DIOMODBUS_CLIENT::CRC16(XBUFFER& data)
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
* @fn         void DIOMODBUS_CLIENT::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOMODBUS_CLIENT::Clean()
{
  diostream   = NULL;

  mode        = DIOMODBUS_CLIENTMODE_UNKNOWN;
  unit        = 0;

  xtimer      = NULL;
}


#pragma endregion

