/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOStreamUDPConfig.cpp
* 
* @class      DIOSTREAMUDPCONFIG
* @brief      Data Input/Output Stream UDP Config class
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

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIOStreamUDPConfig.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMUDPCONFIG::DIOSTREAMUDPCONFIG()
* @brief      Constructor
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMUDPCONFIG::DIOSTREAMUDPCONFIG() : DIOSTREAMCONFIG(), DIOSTREAMCONFIGSTRING()
{
  Clean();

  type = DIOSTREAMTYPE_UDP;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMUDPCONFIG::~DIOSTREAMUDPCONFIG()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMUDPCONFIG::~DIOSTREAMUDPCONFIG()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOIP* DIOSTREAMUDPCONFIG::GetLocalIP()
* @brief      GetLocalIP
* @ingroup    DATAIO
*
* @return     DIOIP* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOIP* DIOSTREAMUDPCONFIG::GetLocalIP()
{
  return &localIP;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOURL* DIOSTREAMUDPCONFIG::GetRemoteURL()
* @brief      GetRemoteURL
* @ingroup    DATAIO
*
* @return     DIOURL* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOURL* DIOSTREAMUDPCONFIG::GetRemoteURL()
{
  return &remoteURL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* DIOSTREAMUDPCONFIG::GetResolvedRemoteURL()
* @brief      GetResolvedRemoteURL
* @ingroup    DATAIO
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOSTREAMUDPCONFIG::GetResolvedRemoteURL()
{
  return &resolvedremoteURL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOSTREAMUDPCONFIG::GetRemotePort()
* @brief      GetRemotePort
* @ingroup    DATAIO
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOSTREAMUDPCONFIG::GetRemotePort()
{
  return remoteport;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUDPCONFIG::SetRemotePort(int port)
* @brief      SetRemotePort
* @ingroup    DATAIO
*
* @param[in]  port :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUDPCONFIG::SetRemotePort(int port)
{
  this->remoteport = port;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUDPCONFIG::IsUsedDatagrams()
* @brief      IsUsedDatagrams
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUDPCONFIG::IsUsedDatagrams()
{
  return isuseddatagrams;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMUDPCONFIG::SetIsUsedDatagrams(bool active)
* @brief      SetIsUsedDatagrams
* @ingroup    DATAIO
*
* @param[in]  active :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMUDPCONFIG::SetIsUsedDatagrams(bool active)
{
  isuseddatagrams = active;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUDPCONFIG::IsBroadcastModeActive()
* @brief      IsBroadcastModeActive
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUDPCONFIG::IsBroadcastModeActive()
{
  return isbroadcastmodeactive;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMUDPCONFIG::SetBroadcastModeActive(bool active)
* @brief      SetBroadcastModeActive
* @ingroup    DATAIO
*
* @param[in]  active :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMUDPCONFIG::SetBroadcastModeActive(bool active)
{
  isbroadcastmodeactive = active;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMUDPCONFIG::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMUDPCONFIG::Clean()
{
  type                    = DIOSTREAMTYPE_UDP;

  remoteoffsetport        = 0;

  isuseddatagrams         = false;
  isbroadcastmodeactive   = false;
}


#pragma endregion

