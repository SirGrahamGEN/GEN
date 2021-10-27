/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOI2CEEprom24XXX.cpp
*
* @class      DIOI2CEEPROM24XXX
* @brief      Data Input/Output I2C EEPROM 24XXX class.
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
#include "XBuffer.h"
#include "XTrace.h"

#include "DIOFactory.h"
#include "DIOStreamI2CConfig.h"
#include "DIOStreamI2C.h"

#include "DIOI2CEEprom24XXX.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOI2CEEPROM24XXX::DIOI2CEEPROM24XXX()
* @brief      Constructor
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOI2CEEPROM24XXX::DIOI2CEEPROM24XXX(): DIODEVICEI2C()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOI2CEEPROM24XXX::~DIOI2CEEPROM24XXX()
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
DIOI2CEEPROM24XXX::~DIOI2CEEPROM24XXX()
{
  End();

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOI2CEEPROM24XXXTYPE DIOI2CEEPROM24XXX::GetType()
* @brief      GetType
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     DIOI2CEEPROM24XXXTYPE : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOI2CEEPROM24XXXTYPE DIOI2CEEPROM24XXX::GetType()
{ 
  return type;                                   
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOI2CEEPROM24XXX::SetType(DIOI2CEEPROM24XXXTYPE type)
* @brief      SetType
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  type : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOI2CEEPROM24XXX::SetType(DIOI2CEEPROM24XXXTYPE type)    
{ 
  this->type = type;                             
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIOI2CEEPROM24XXX::GetSize()
* @brief      GetSize
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     XDWORD : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOI2CEEPROM24XXX::GetSize()                              
{ 
  return maxsize;                                
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CEEPROM24XXX::Read(XDWORD address, XBYTE* buffer, XDWORD size)
* @brief      Read
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  address :
* @param[in]  buffer :
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CEEPROM24XXX::Read(XDWORD address, XBYTE* buffer, XDWORD size)
{
  if(!diostream)        return false;
  if(!IsInitialized())  return false;

  if(diostreamcfg->GetRemoteAddress() ==  DIOSTREAMI2CCONFIG_ADDRESSINVALID) return false;

  if((address+size)>maxsize) return false;

  bool status = true;

  for(XDWORD c=0; c<size; c++)
    {
      xtimerout->Reset();

      while(1)
        {
          status = ReadBYTE(address+c, buffer[c]);
          if(!status)
            {
              if(xtimerout->GetMeasureSeconds()>(XDWORD)timeout) break;

            } else break;
        }
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CEEPROM24XXX::Read(XDWORD address, XDWORD size, XBUFFER& xbuffer)
* @brief      Read
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  address :
* @param[in]  size :
* @param[in]  xbuffer :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CEEPROM24XXX::Read(XDWORD address, XDWORD size, XBUFFER& xbuffer)
{
  xbuffer.Delete();
  xbuffer.Resize(size);

  return Read(address, xbuffer.Get(), size);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CEEPROM24XXX::Write(XDWORD address, XBYTE* buffer, XDWORD size)
* @brief      Write
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  address :
* @param[in]  buffer :
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CEEPROM24XXX::Write(XDWORD address, XBYTE* buffer, XDWORD size)
{
  if(!diostream)        return false;
  if(!IsInitialized())  return false;

  if(diostreamcfg->GetRemoteAddress() ==  DIOSTREAMI2CCONFIG_ADDRESSINVALID) return false;

  if((address +size)>maxsize) return false;

  bool status = true;

  for(XDWORD c=0; c<size; c++)
    {
      status = WriteBYTE(address+c, buffer[c]);
      if(!status) break;
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CEEPROM24XXX::Write(XDWORD address, XBUFFER& xbuffer)
* @brief      Write
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  address :
* @param[in]  xbuffer :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CEEPROM24XXX::Write(XDWORD address, XBUFFER& xbuffer)
{
  return Write(address, xbuffer.Get(), xbuffer.GetSize());
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CEEPROM24XXX::End()
* @brief      End
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CEEPROM24XXX::End()
{
  if(!DIODEVICEI2C::End()) return false;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CEEPROM24XXX::IniDevice()
* @brief      IniDevice
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CEEPROM24XXX::IniDevice()
{
  int deviceaddressbase = diostreamcfg->GetRemoteAddress();

  switch(type)
    {
      case DIOI2CEEPROM24XXXTYPE_UNKNOWN  : return false;

      case DIOI2CEEPROM24XXXTYPE_08       : npages            = 8;
                                            maxsizepage       = 128;
                                            maxsizechunk      = 16;
                                            maxsize           = npages*maxsizepage;
                                            deviceaddressbase = DIOI2CEEPROM2408_FIXEDADDRESSBASE;
                                            break;

      case DIOI2CEEPROM24XXXTYPE_16       : npages            = 8;
                                            maxsizepage       = 256;
                                            maxsizechunk      = 16;
                                            maxsize           = npages*maxsizepage;
                                            deviceaddressbase = DIOI2CEEPROM2416_FIXEDADDRESSBASE;
                                            break;

      case DIOI2CEEPROM24XXXTYPE_65       : npages            = 1;
                                            maxsizepage       = 8192;
                                            maxsizechunk      = 16;
                                            maxsize           = 8192;
                                            break;

      case DIOI2CEEPROM24XXXTYPE_515      : npages            = 1;
                                            maxsizepage       = 65535;
                                            maxsizechunk      = 16;
                                            maxsize           = 65536;
                                            break;
    }

  diostreamcfg->SetRemoteAddress(deviceaddressbase);


  if(!DIODEVICEI2C::IniDevice()) return false;
  
  if(diostream->Open())  
    {
      if(!diostream->WaitToConnected(timeout)) return false;
     
      return DIODEVICE::Ini();       
    }
  
  return false;
}




/*-------------------------------------------------------------------
//  DIOI2CEEPROM24XXX::ReadBYTE
*/
/**
//
//
//
//  @author      Abraham J. Velez
//  @version      18/05/2014 23:48:54
//
//  @return       bool :
//
//  @param        address :
//  @param        data :
*/
/*-----------------------------------------------------------------*/
bool DIOI2CEEPROM24XXX::ReadBYTE(XDWORD address, XBYTE& data)
{
  if(!diostream)        return false;
  if(!IsInitialized())  return false;

  XBYTE   remotebasebackup = (XBYTE)diostreamcfg->GetRemoteAddress();
  XBYTE   remotebase       = remotebasebackup;
  XBUFFER xbuffer;
  bool    status;

  switch(type)
    {
      case DIOI2CEEPROM24XXXTYPE_UNKNOWN  :
                                  default : return false;

      case DIOI2CEEPROM24XXXTYPE_08       :
      case DIOI2CEEPROM24XXXTYPE_16       : { if((address)>=maxsize) return false;

                                              XBYTE page =  (XBYTE)(address / maxsizepage);
                                              remotebase+=(XBYTE)page;

                                              XBYTE offset = (address % maxsizepage);

                                              xbuffer.Add((XBYTE)offset);

                                              //XTRACE_PRINTCOLOR(1, __L("%d, %d"), page, offset);
                                            }
                                            break;

      case DIOI2CEEPROM24XXXTYPE_65       :
      case DIOI2CEEPROM24XXXTYPE_515      : if((address)>=maxsize) return false;
                                            xbuffer.Add((XWORD)address);
                                            break;
    }

  diostreamcfg->SetRemoteAddress(remotebase);
  if(diostream->Write(xbuffer)) status = diostream->WaitToFlushOutXBuffer(timeout);

  status = diostream->WaitToFilledReadingBuffer(1, timeout);
  if(status) status = diostream->Read(&data, 1)?true:false;

  //XTRACE_PRINTCOLOR(1, __L("%02X, %02X"), xbuffer.GetByte(0), data);

  diostreamcfg->SetRemoteAddress(remotebasebackup);

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOI2CEEPROM24XXX::WriteBYTE(XDWORD address, XBYTE data)
* @brief      WriteBYTE
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  address :
* @param[in]  data :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOI2CEEPROM24XXX::WriteBYTE(XDWORD address, XBYTE data)
{
  if(!diostream)        return false;
  if(!IsInitialized())  return false;

  XBYTE   remotebasebackup = (XBYTE)diostreamcfg->GetRemoteAddress();
  XBYTE   remotebase       = remotebasebackup;
  XBUFFER xbuffer;
  bool    status           = false;

  switch(type)
    {
      case DIOI2CEEPROM24XXXTYPE_UNKNOWN  :
                                  default : return false;

      case DIOI2CEEPROM24XXXTYPE_08       :
      case DIOI2CEEPROM24XXXTYPE_16       : { if((address)>=maxsize) return false;

                                              XBYTE page =  (XBYTE)(address / maxsizepage);
                                              remotebase+=(XBYTE)page;

                                              XBYTE offset = (address % maxsizepage);

                                              xbuffer.Add((XBYTE)offset);
                                            }
                                            break;

      case DIOI2CEEPROM24XXXTYPE_65       :
      case DIOI2CEEPROM24XXXTYPE_515      : if((address)>=maxsize) return false;
                                            xbuffer.Add((XWORD)address);
                                            break;
    }


  diostreamcfg->SetRemoteAddress(remotebase);

  xbuffer.Add((XBYTE)data);

  status = diostream->Write(xbuffer)==xbuffer.GetSize()?true:false;
  if(status) status = diostream->WaitToFlushOutXBuffer(timeout);

  diostreamcfg->SetRemoteAddress(remotebasebackup);

  return status;
}




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOI2CEEPROM24XXX::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOI2CEEPROM24XXX::Clean()
{
  diostream     = NULL;

  type          = DIOI2CEEPROM24XXXTYPE_UNKNOWN;
  maxsize       = 0;
  npages        = 0;
  maxsizepage   = 0;
  maxsizechunk  = 0;
}