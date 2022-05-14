/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOCLIClientBTModuleCSR.cpp
* 
* @class      DIOCLICLIENTBTMODULECSR
* @brief      Data Input/Output CLI (Command Line Interface) client BT Module CSR class 
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "XFactory.h"
#include "XFSMachine.h"

#include "DIOStream.h"

#include "DIOCLIClientBTModuleCSR.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCLICLIENTBTMODULECSR::DIOCLICLIENTBTMODULECSR(DIOSTREAM* diostream)
* @brief      Constructor
* @ingroup    DATAIO
* 
* @param[in]  DIOSTREAM* : 
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCLICLIENTBTMODULECSR::DIOCLICLIENTBTMODULECSR(DIOSTREAM* diostream) : DIOCLICLIENT(diostream)
{
  AddCommand(DIOCLICLIENT_TYPECOMMAND_VERSION             ,__L("version"));

  AddCommand(DIOCLICLIENT_TYPECOMMAND_RSSI                ,__L("rssi"));

  AddCommand(DIOCLICLIENT_TYPECOMMAND_GETCFGIOD           ,__L("getcfgiod"));
  AddCommand(DIOCLICLIENT_TYPECOMMAND_SETCFGIOD           ,__L("setcfgiod"));
  AddCommand(DIOCLICLIENT_TYPECOMMAND_GETIOD              ,__L("getiod"));
  AddCommand(DIOCLICLIENT_TYPECOMMAND_SETIOD              ,__L("setiod"));
  AddCommand(DIOCLICLIENT_TYPECOMMAND_GETIOA1             ,__L("getioa1"));

  AddCommand(DIOCLICLIENT_TYPECOMMAND_ISBATTERYCHARGING   ,__L("isbatterycharging"));
  AddCommand(DIOCLICLIENT_TYPECOMMAND_BATTERYCHARGE       ,__L("batterycharge"));

  AddCommand(DIOCLICLIENT_TYPECOMMAND_I2CMEMREAD          ,__L("i2cmemread"));
  AddCommand(DIOCLICLIENT_TYPECOMMAND_I2CMEMWRITE         ,__L("i2cmemwrite"));

  AddCommand(DIOCLICLIENT_TYPECOMMAND_I2CADC              ,__L("i2cadc"));
  AddCommand(DIOCLICLIENT_TYPECOMMAND_I2CDAC              ,__L("i2cdac"));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCLICLIENTBTMODULECSR::~DIOCLICLIENTBTMODULECSR()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCLICLIENTBTMODULECSR::~DIOCLICLIENTBTMODULECSR()
{

}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCLICLIENT_ERROR DIOCLICLIENTBTMODULECSR::Version(int& version,int& subversion)
* @brief      Version
* @ingroup    DATAIO
* 
* @param[in]  version : 
* @param[in]  subversion : 
* 
* @return     DIOCLICLIENT_ERROR : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCLICLIENT_ERROR DIOCLICLIENTBTMODULECSR::Version(int& version,int& subversion)
{
  XSTRING        answer;
  DIOCLICLIENT_ERROR error;

  error = SendCommandWithAnswer(DIOCLICLIENT_TYPECOMMAND_VERSION,answer);
  if(error==DIOCLICLIENT_ERROR_NONE) answer.UnFormat(__L("%d.%d"),&version,&subversion);

  return error;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCLICLIENT_ERROR DIOCLICLIENTBTMODULECSR::RSSI(int& RSSI)
* @brief      RSSI
* @ingroup    DATAIO
* 
* @param[in]  RSSI : 
* 
* @return     DIOCLICLIENT_ERROR : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCLICLIENT_ERROR DIOCLICLIENTBTMODULECSR::RSSI(int& RSSI)
{
  XSTRING        answer;
  DIOCLICLIENT_ERROR error;

  error = SendCommandWithAnswer(DIOCLICLIENT_TYPECOMMAND_RSSI,answer);
  if(error==DIOCLICLIENT_ERROR_NONE) RSSI = answer.ConvertToInt();

  return error;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCLICLIENT_ERROR DIOCLICLIENTBTMODULECSR::GetCFGIOD(int portio,bool& isoutput)
* @brief      GetCFGIOD
* @ingroup    DATAIO
* 
* @param[in]  portio : 
* @param[in]  isoutput : 
* 
* @return     DIOCLICLIENT_ERROR : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCLICLIENT_ERROR DIOCLICLIENTBTMODULECSR::GetCFGIOD(int portio,bool& isoutput)
{
  XSTRING        param;
  XSTRING        answer;
  DIOCLICLIENT_ERROR error;

  param.Format(__L("%d"),portio);

  error = SendCommandWithAnswer(DIOCLICLIENT_TYPECOMMAND_GETCFGIOD,answer,param.Get());
  if(error==DIOCLICLIENT_ERROR_NONE) isoutput = (XBYTE)answer.ConvertToInt()?false:true;

  return error;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCLICLIENT_ERROR DIOCLICLIENTBTMODULECSR::SetCFGIOD(int portio,bool isoutput)
* @brief      SetCFGIOD
* @ingroup    DATAIO
* 
* @param[in]  portio : 
* @param[in]  isoutput : 
* 
* @return     DIOCLICLIENT_ERROR : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCLICLIENT_ERROR DIOCLICLIENTBTMODULECSR::SetCFGIOD(int portio,bool isoutput)
{
  XSTRING param;

  param.Format(__L("%d,%d"),portio,isoutput?0:1);

  return SendCommandWithoutAnswer(DIOCLICLIENT_TYPECOMMAND_SETCFGIOD, param.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCLICLIENT_ERROR DIOCLICLIENTBTMODULECSR::GetIOD(int portio,bool& isactive)
* @brief      GetIOD
* @ingroup    DATAIO
* 
* @param[in]  portio : 
* @param[in]  isactive : 
* 
* @return     DIOCLICLIENT_ERROR : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCLICLIENT_ERROR DIOCLICLIENTBTMODULECSR::GetIOD(int portio,bool& isactive)
{
  XSTRING        param;
  XSTRING        answer;
  DIOCLICLIENT_ERROR error;

  param.Format(__L("%d"),portio);

  error = SendCommandWithAnswer(DIOCLICLIENT_TYPECOMMAND_GETIOD,answer,param.Get());
  if(error==DIOCLICLIENT_ERROR_NONE) isactive = (XBYTE)answer.ConvertToInt()?true:false;

  return error;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCLICLIENT_ERROR DIOCLICLIENTBTMODULECSR::SetIOD(int portio,bool isactive)
* @brief      SetIOD
* @ingroup    DATAIO
* 
* @param[in]  portio : 
* @param[in]  isactive : 
* 
* @return     DIOCLICLIENT_ERROR : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCLICLIENT_ERROR DIOCLICLIENTBTMODULECSR::SetIOD(int portio,bool isactive)
{
  XSTRING param;

  param.Format(__L("%d,%d"),portio,isactive?1:0);

  return SendCommandWithoutAnswer(DIOCLICLIENT_TYPECOMMAND_SETIOD, param.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCLICLIENT_ERROR DIOCLICLIENTBTMODULECSR::GetIOA1(XBYTE& value)
* @brief      GetIOA1
* @ingroup    DATAIO
* 
* @param[in]  value : 
* 
* @return     DIOCLICLIENT_ERROR : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCLICLIENT_ERROR DIOCLICLIENTBTMODULECSR::GetIOA1(XBYTE& value)
{
  XSTRING        answer;
  DIOCLICLIENT_ERROR error;

  error = SendCommandWithAnswer(DIOCLICLIENT_TYPECOMMAND_GETIOA1,answer);
  if(error==DIOCLICLIENT_ERROR_NONE) value = (XBYTE)answer.ConvertToInt();

  return error;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCLICLIENT_ERROR DIOCLICLIENTBTMODULECSR::IsBatteryCharging(bool& ischarging)
* @brief      IsBatteryCharging
* @ingroup    DATAIO
* 
* @param[in]  ischarging : 
* 
* @return     DIOCLICLIENT_ERROR : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCLICLIENT_ERROR DIOCLICLIENTBTMODULECSR::IsBatteryCharging(bool& ischarging)
{
  XSTRING        answer;
  DIOCLICLIENT_ERROR error;

  error = SendCommandWithAnswer(DIOCLICLIENT_TYPECOMMAND_ISBATTERYCHARGING,answer);
  if(error==DIOCLICLIENT_ERROR_NONE) ischarging = (XBYTE)answer.ConvertToInt()?true:false;

  return error;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCLICLIENT_ERROR DIOCLICLIENTBTMODULECSR::BatteryCharge(int& mVolts)
* @brief      BatteryCharge
* @ingroup    DATAIO
* 
* @param[in]  mVolts : 
* 
* @return     DIOCLICLIENT_ERROR : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCLICLIENT_ERROR DIOCLICLIENTBTMODULECSR::BatteryCharge(int& mVolts)
{
  XSTRING        answer;
  DIOCLICLIENT_ERROR error;

  error = SendCommandWithAnswer(DIOCLICLIENT_TYPECOMMAND_BATTERYCHARGE,answer);
  if(error==DIOCLICLIENT_ERROR_NONE) mVolts = (XBYTE)answer.ConvertToInt();

  return error;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCLICLIENT_ERROR DIOCLICLIENTBTMODULECSR::I2CMemRead(int address,int index,XBYTE& data)
* @brief      I2CMemRead
* @ingroup    DATAIO
* 
* @param[in]  address : 
* @param[in]  index : 
* @param[in]  data : 
* 
* @return     DIOCLICLIENT_ERROR : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCLICLIENT_ERROR DIOCLICLIENTBTMODULECSR::I2CMemRead(int address,int index,XBYTE& data)
{
  XSTRING        param;
  XSTRING        answer;
  DIOCLICLIENT_ERROR error;

  param.Format(__L("%d,%d"),address,index);

  error = SendCommandWithAnswer(DIOCLICLIENT_TYPECOMMAND_I2CMEMREAD,answer,param.Get());
  if(error==DIOCLICLIENT_ERROR_NONE) data = (XBYTE)answer.ConvertToInt();

  return error;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCLICLIENT_ERROR DIOCLICLIENTBTMODULECSR::I2CMemWrite(int address,int index,XBYTE data)
* @brief      I2CMemWrite
* @ingroup    DATAIO
* 
* @param[in]  address : 
* @param[in]  index : 
* @param[in]  data : 
* 
* @return     DIOCLICLIENT_ERROR : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCLICLIENT_ERROR DIOCLICLIENTBTMODULECSR::I2CMemWrite(int address,int index,XBYTE data)
{
  XSTRING param;
  XSTRING string;

  param.Format(__L("%d,%d,%d"),address,index,data);

  return SendCommandWithoutAnswer(DIOCLICLIENT_TYPECOMMAND_I2CMEMWRITE, param.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCLICLIENT_ERROR DIOCLICLIENTBTMODULECSR::I2CADC(int address,int port,XBYTE& data)
* @brief      I2CADC
* @ingroup    DATAIO
* 
* @param[in]  address : 
* @param[in]  port : 
* @param[in]  data : 
* 
* @return     DIOCLICLIENT_ERROR : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCLICLIENT_ERROR DIOCLICLIENTBTMODULECSR::I2CADC(int address,int port,XBYTE& data)
{
  XSTRING        param;
  XSTRING        answer;
  DIOCLICLIENT_ERROR error;

  param.Format(__L("%d,%d"),address,port);

  error = SendCommandWithAnswer(DIOCLICLIENT_TYPECOMMAND_I2CADC,answer,param.Get());
  if(error==DIOCLICLIENT_ERROR_NONE) data = (XBYTE)answer.ConvertToInt();

  return error;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCLICLIENT_ERROR DIOCLICLIENTBTMODULECSR::I2CDAC(int address,XBYTE data)
* @brief      I2CDAC
* @ingroup    DATAIO
* 
* @param[in]  address : 
* @param[in]  data : 
* 
* @return     DIOCLICLIENT_ERROR : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCLICLIENT_ERROR DIOCLICLIENTBTMODULECSR::I2CDAC(int address,XBYTE data)
{
  XSTRING param;

  param.Format(__L("%d,%d"),address,data);

  return SendCommandWithoutAnswer(DIOCLICLIENT_TYPECOMMAND_I2CDAC,param.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCLICLIENTBTMODULECSR::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCLICLIENTBTMODULECSR::Clean()
{

}
