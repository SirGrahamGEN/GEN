/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOWakeOnLAN.cpp
*
* @class      DIOWAKEONLAN
* @brief      Data Input/Output Wake on LAN class
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

#include "DIOFactory.h"
#include "DIOMAC.h"
#include "DIOStreamUDPConfig.h"
#include "DIOStreamUDP.h"

#include "DIOWakeOnLAN.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWAKEONLAN::DIOWAKEONLAN()
* @brief      Constructor
* @ingroup    DATAIO
*
* @return     Does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWAKEONLAN::DIOWAKEONLAN()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWAKEONLAN::~DIOWAKEONLAN()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @return     Does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWAKEONLAN::~DIOWAKEONLAN()
{
  Clean();

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWAKEONLAN::SendActivation(DIOMAC* MAC, DIOIP* broadcastIP, int timeout)
* @brief      SendActivation
* @ingroup    DATAIO
*
* @param[in]  MAC : 
* @param[in]  broadcastIP : 
* @param[in]  timeout : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWAKEONLAN::SendActivation(DIOMAC* MAC, DIOIP* broadcastIP, int timeout)
{
  #define DIOWAKEONLAN_NPACKETS  16

  if(!MAC)          return false;
  if(!broadcastIP)  return false;

  DIOSTREAMUDPCONFIG  diostreamudpcfg;
  DIOSTREAMUDP*       diostreamudp  = NULL;
  XSTRING             broadcastIPstring;
  XBYTE               MACfull[DIOMAC_MAXSIZE] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
  bool                status        = false;  

  broadcastIP->GetXString(broadcastIPstring);

  diostreamudpcfg.SetMode(DIOSTREAMMODE_CLIENT);
  diostreamudpcfg.SetIsUsedDatagrams(false);
  diostreamudpcfg.GetRemoteURL()->Set(broadcastIPstring.Get());
  diostreamudpcfg.SetBroadcastModeActive(true);
  diostreamudpcfg.SetRemotePort(9);

  diostreamudp = (DIOSTREAMUDP*)GEN_DIOFACTORY.CreateStreamIO(&diostreamudpcfg);
  if(!diostreamudp) return status;

  if(diostreamudp->Open())
    {
      #define SIZEALL (DIOWAKEONLAN_NPACKETS+1) * DIOMAC_MAXSIZE
      XBYTE tosend[ SIZEALL];

      memset(tosend, 0, SIZEALL);
                
      memcpy(&tosend[0], MACfull, DIOMAC_MAXSIZE);

      for(XDWORD c=1; c<DIOWAKEONLAN_NPACKETS+1; c++)
        {
          memcpy(&tosend[c*DIOMAC_MAXSIZE], MAC->Get(), DIOMAC_MAXSIZE);
        }

      status = diostreamudp->Write(tosend, SIZEALL);
      if(status) 
        {
          status = diostreamudp->WaitToFlushOutXBuffer(timeout);
        }
      
      diostreamudp->Close();
    }

  GEN_DIOFACTORY.DeleteStreamIO(diostreamudp);

  return status;
}



 
/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWAKEONLAN::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWAKEONLAN::Clean()
{

}