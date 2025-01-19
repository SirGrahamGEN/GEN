/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOStreamTCPIPServer.cpp
* 
* @class      DIOSTREAMTCPIPSERVER
* @brief      Data Input/Output Stream TCP/IP Server class (Multi-Socket)
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

#include "DIOStreamTCPIPServer.h"

#include "DIOFactory.h"
#include "DIOStream_XEvent.h"
#include "DIOStreamTCPIPConfig.h"

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
* @fn         DIOSTREAMTCPIPSERVER::DIOSTREAMTCPIPSERVER()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMTCPIPSERVER::DIOSTREAMTCPIPSERVER()
{
  Clean();

  RegisterEvent(DIOSTREAM_XEVENT_TYPE_CONNECTED);
  RegisterEvent(DIOSTREAM_XEVENT_TYPE_DISCONNECTED);
	
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMTCPIPSERVER::~DIOSTREAMTCPIPSERVER()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMTCPIPSERVER::~DIOSTREAMTCPIPSERVER()
{
  DeRegisterEvent(DIOSTREAM_XEVENT_TYPE_CONNECTED);
  DeRegisterEvent(DIOSTREAM_XEVENT_TYPE_DISCONNECTED);

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMCONFIG* DIOSTREAMTCPIPSERVER::GetConfig()
* @brief      Get config
* @ingroup    DATAIO
*
* @return     DIOSTREAMCONFIG* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMCONFIG* DIOSTREAMTCPIPSERVER::GetConfig()
{
  return (DIOSTREAMCONFIG*)config;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMTCPIPSERVER::SetConfig(DIOSTREAMCONFIG* config)
* @brief      Set config
* @ingroup    DATAIO
*
* @param[in]  config :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMTCPIPSERVER::SetConfig(DIOSTREAMCONFIG* config)
{
  if(!config) return false;
  this->config = (DIOSTREAMTCPIPCONFIG*)config;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSTREAMTCPIPSERVER::WaitToConnected(int timeout)
* @brief      Wait to connected
* @ingroup    DATAIO
* 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMTCPIPSERVER::WaitToConnected(int timeout)
{
  if(!xtimerconnection) 
    {
      return false;
    }

  DIOSTREAMTCPIPCONFIG* config = (DIOSTREAMTCPIPCONFIG*)GetConfig();  
  bool                  status = false;

  if(!config)
    {
      return false;
    }

  xtimerconnection->Reset();  

  while(1)
    {
      if(config->GetHandleMultiServer() > 0)
        {
          status = true;
          break;
        }
      
      if(GetStatus() == DIOSTREAMSTATUS_DISCONNECTED)
        {
          break;
        }
      
      if((int)xtimerconnection->GetMeasureSeconds() >= timeout)
        {
          break;
        }

      Wait(DIOSTREAM_TIMEINWAITFUNCTIONS);
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOIP* DIOSTREAMTCPIPSERVER::GetClientIP()
* @brief      Get client IP
* @ingroup    DATAIO
*
* @return     DIOIP* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOIP* DIOSTREAMTCPIPSERVER::GetClientIP()
{
  return &clientIP;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMENUMSERVERS* DIOSTREAMTCPIPSERVER::GetEnumServers()
* @brief      Get enum servers
* @ingroup    DATAIO
*
* @return     DIOSTREAMENUMSERVERS* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMENUMSERVERS* DIOSTREAMTCPIPSERVER::GetEnumServers()
{
  return enumservers;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMTCPIPSERVER::SetEnumServers(DIOSTREAMENUMSERVERS* enumservers)
* @brief      Set enum servers
* @ingroup    DATAIO
*
* @param[in]  enumservers :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMTCPIPSERVER::SetEnumServers(DIOSTREAMENUMSERVERS* enumservers)
{
  this->enumservers = enumservers;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<DIOSTREAMTCPIP*>* DIOSTREAMTCPIPSERVER::GetMultiSocketStreams()
* @brief      Get multi socket streams
* @ingroup    DATAIO
* 
* @return     XVECTOR<DIOSTREAMTCPIP*>* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<DIOSTREAMTCPIP*>* DIOSTREAMTCPIPSERVER::GetMultiSocketStreams()
{
  return &multisocketstreams;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIOSTREAMTCPIPSERVER::GetNumMultiSocketStreams()
* @brief      Get num multi socket streams
* @ingroup    DATAIO
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSTREAMTCPIPSERVER::GetNumMultiSocketStreams()
{
  return multisocketstreams.GetSize();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIOSTREAMTCPIPSERVER::GetNumConnectedMultiSocketStreams()
* @brief      Get num connected multi socket streams
* @ingroup    DATAIO
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSTREAMTCPIPSERVER::GetNumConnectedMultiSocketStreams()
{
  XDWORD ndiostreams = 0;

  for(XDWORD c=0; c<multisocketstreams.GetSize(); c++)
    {
      DIOSTREAMTCPIP* diostream = (DIOSTREAMTCPIP*)multisocketstreams.Get(c);
      if(diostream) 
        {
          if(diostream->GetStatus() == DIOSTREAMSTATUS_CONNECTED)
            {
              ndiostreams++;
            }
        }
    }

  return ndiostreams;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMTCPIPSERVER::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMTCPIPSERVER::Clean()
{
  config      = NULL;
  enumservers = NULL;
}


#pragma endregion

