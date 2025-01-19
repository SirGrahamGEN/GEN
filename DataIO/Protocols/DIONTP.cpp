/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIONTP.cpp
* 
* @class      DIONTP
* @brief      Data Input/Output NTP (Network Time Protocol) UTC class
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

#include "DIONTP.h"

#include "XFactory.h"
#include "XDateTime.h"
#include "XTimer.h"
#include "XTrace.h"

#include "DIOFactory.h"
#include "DIOStreamUDPConfig.h"
#include "DIOStreamUDP.h"

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
* @fn         DIONTP::DIONTP()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIONTP::DIONTP()
{
  Clean();

  GEN_XFACTORY_CREATE(xtimer, CreateTimer())
 
  diostreamudpcfg = new DIOSTREAMUDPCONFIG();
  diostreamudp    = (DIOSTREAMUDP*)GEN_DIOFACTORY.CreateStreamIO(diostreamudpcfg);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIONTP::~DIONTP()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIONTP::~DIONTP()
{
  if(xtimer)
    {
      GEN_XFACTORY.DeleteTimer(xtimer);
      xtimer = NULL;
    }

  if(diostreamudpcfg)
    {
      delete diostreamudpcfg;
      diostreamudpcfg = NULL;
    }

  if(diostreamudp)
    {
      GEN_DIOFACTORY.DeleteStreamIO(diostreamudp);
      diostreamudp    = NULL;
    }

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIONTP::GetTimeResponse(XCHAR* urlntpserver, int timeout, bool hardwareuselittleendian, DIONTPRESPONSE& response)
* @brief      Get time response
* @ingroup    DATAIO
*
* @param[in]  urlntpserver :
* @param[in]  timeout :
* @param[in]  hardwareuselittleendian :
* @param[in]  response :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONTP::GetTimeResponse(XCHAR* urlntpserver, int timeout, bool hardwareuselittleendian, DIONTPRESPONSE& response)
{
  if(!xtimer)                               return false;
  if((!diostreamudpcfg) || (!diostreamudp)) return false;

  bool status  = false;

  memset(&response, 0, sizeof(DIONTPRESPONSE));

  diostreamudpcfg->SetMode(DIOSTREAMMODE_CLIENT);
  diostreamudpcfg->SetIsUsedDatagrams(false);
  diostreamudpcfg->GetRemoteURL()->Set(urlntpserver);
  diostreamudpcfg->SetRemotePort(DIONTP_DEFAULTPORT);

  if(!diostreamudp->Open()) return false;

  DIONTPBASICINFO basicinfo;

  memset((XBYTE*)&basicinfo, 0, sizeof(DIONTPBASICINFO));

  basicinfo.livnmode = 27; //Encoded representation which represents NTP Client Request & NTP version 3.0

  if(diostreamudp->Write((XBYTE*)&basicinfo,sizeof(DIONTPBASICINFO)))
    {
      xtimer->Reset();

      DIONTPFULLPACKET fullpacket;        
      XDWORD           br = 0;
      while(!br)
        {
          memset((XBYTE*)&fullpacket,0 ,sizeof(DIONTPFULLPACKET));

          XDWORD size  = diostreamudp->GetInXBuffer()->GetSize();
          if(size >= sizeof(DIONTPBASICINFO))
            {
              br = diostreamudp->Read((XBYTE*)&fullpacket, size);                
              if(br)
                {              
                  response.stratum           = fullpacket.basic.stratum;
                  response.leapindicator     = (fullpacket.basic.livnmode & 0xC0) >> 6;
                  response.originatetime     = ConvertTimePacket(fullpacket.basic.originatetimestamp  , hardwareuselittleendian);
                  response.receivetime       = ConvertTimePacket(fullpacket.basic.receivetimestamp    , hardwareuselittleendian);
                  response.transmittime      = ConvertTimePacket(fullpacket.basic.transmittimestamp   , hardwareuselittleendian);

                  long long roundtripdelay   = (long long)(response.destinationtime - response.originatetime) - (long long)(response.receivetime - response.transmittime);
                  long long localclockoffset = (long long)(response.receivetime - response.originatetime)     + (long long)(response.transmittime - response.destinationtime);
                  response.roundtripdelay    = (double)(roundtripdelay);
                  response.localclockoffset  = (double)(localclockoffset/2);

                  status  = true;
                  break;
                }             
            } 
           else
            {
              //XTRACE_PRINTCOLOR(XTRACE_COLOR_PURPLE, __L("ntp [%d] %d"), sizeof(DIONTPBASICINFO),  size);
            } 
          
          if((int)xtimer->GetMeasureSeconds()>= timeout)
            {
              status = false;
              break;
            }
        }
    }

  diostreamudp->Close();

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIONTP::GetTimeResponse(DIOURL& urlntpserver, int timeout, bool hardwareuselittleendian, DIONTPRESPONSE& response)
* @brief      Get time response
* @ingroup    DATAIO
*
* @param[in]  urlntpserver :
* @param[in]  timeout :
* @param[in]  hardwareuselittleendian :
* @param[in]  response :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONTP::GetTimeResponse(DIOURL& urlntpserver, int timeout, bool hardwareuselittleendian, DIONTPRESPONSE& response)
{
  return GetTimeResponse(urlntpserver.Get(), timeout, hardwareuselittleendian, response);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIONTP::GetTimeSeconds(XCHAR* urlntpserver, int timeout, bool hardwareuselittleendian, XQWORD& timeseconds)
* @brief      Get time seconds
* @ingroup    DATAIO
*
* @param[in]  urlntpserver :
* @param[in]  timeout :
* @param[in]  hardwareuselittleendian :
* @param[in]  timeseconds :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONTP::GetTimeSeconds(XCHAR* urlntpserver, int timeout, bool hardwareuselittleendian, XQWORD& timeseconds)
{
  DIONTPRESPONSE response;

  timeseconds = 0;

  if(GetTimeResponse(urlntpserver,timeout, hardwareuselittleendian, response))
    {
      timeseconds = (response.receivetime >> 32);

    } else return false;

  return timeseconds?true:false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIONTP::GetTimeSeconds(DIOURL& urlntpserver, int timeout, bool hardwareuselittleendian, XQWORD& timeseconds)
* @brief      Get time seconds
* @ingroup    DATAIO
*
* @param[in]  urlntpserver :
* @param[in]  timeout :
* @param[in]  hardwareuselittleendian :
* @param[in]  timeseconds :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONTP::GetTimeSeconds(DIOURL& urlntpserver, int timeout, bool hardwareuselittleendian, XQWORD& timeseconds)
{
  return GetTimeSeconds(urlntpserver.Get(), timeout, hardwareuselittleendian, timeseconds);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIONTP::GetTime(XCHAR* urlntpserver, int timeout, bool hardwareuselittleendian, XDATETIME& xdatetime)
* @brief      Get time
* @ingroup    DATAIO
*
* @param[in]  urlntpserver :
* @param[in]  timeout :
* @param[in]  hardwareuselittleendian :
* @param[in]  xdatetime :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONTP::GetTime(XCHAR* urlntpserver, int timeout, bool hardwareuselittleendian, XDATETIME& xdatetime)
{
  XQWORD timeseconds;

  bool status = GetTimeSeconds(urlntpserver, timeout, hardwareuselittleendian, timeseconds);
  if(status)
    {
      XDWORD sec = (XDWORD)timeseconds;

      //if(xdatetime.IsDayLigthSavingTime()) sec += 3600;
      //sec += (xdatetime.GetDifferenceGMT()*3600);

      xdatetime.SetSeconds((XWORD)(sec % 60));   sec /= 60;
      xdatetime.SetMinutes((XWORD)(sec % 60));   sec /= 60;
      xdatetime.SetHours((XWORD)(sec % 24));     sec /= 24;

      long JD = sec + DIONTP_JAN1ST1900;

      xdatetime.GetDateFromNDays(JD, false);
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIONTP::GetTime(DIOURL& urlntpserver, int timeout, bool hardwareuselittleendian, XDATETIME& xtime)
* @brief      Get time
* @ingroup    DATAIO
*
* @param[in]  urlntpserver :
* @param[in]  timeout :
* @param[in]  hardwareuselittleendian :
* @param[in]  xtime :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONTP::GetTime(DIOURL& urlntpserver, int timeout, bool hardwareuselittleendian, XDATETIME& xtime)
{
  return GetTime(urlntpserver.Get(), timeout, hardwareuselittleendian, xtime);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XQWORD DIONTP::ConvertTimePacket(DIOTIMEPACKET& timepacket, bool hardwareuselittleendian)
* @brief      Convert time packet
* @ingroup    DATAIO
*
* @param[in]  timepacket :
* @param[in]  hardwareuselittleendian :
*
* @return     XQWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XQWORD DIONTP::ConvertTimePacket(DIOTIMEPACKET& timepacket, bool hardwareuselittleendian)
{
  XDWORD  dwhigh   =  (hardwareuselittleendian)?SwapDWORD(timepacket.integer)    : timepacket.integer;
  XDWORD  dwlow    =  (hardwareuselittleendian)?SwapDWORD(timepacket.fractional) : timepacket.fractional;
  XQWORD  timedata;

  timedata  = ((XQWORD) dwhigh) << 32;
  timedata |= dwlow;

  return timedata;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIONTP::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIONTP::Clean()
{
  xtimer          = NULL;

  diostreamudpcfg = NULL;
  diostreamudp    = NULL;
}


#pragma endregion

