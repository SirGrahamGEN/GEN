/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOProtocol_ConnectionsManager_XEvent.cpp
* 
* @class      DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT
* @brief      Data Input/Output Protocol Connections Manager eXtended Event class
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

#include "DIOProtocol_ConnectionsManager_XEvent.h"

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
* @fn         DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT::DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family)
* @brief      Constructor of class
* @ingroup    DATAIO
* 
* @param[in]  subject : 
* @param[in]  type : 
* @param[in]  family : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT::DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family) : XEVENT(subject, type, family)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT::~DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT::~DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMENUMSERVERS* DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT::GetDIOStreamEnumServers()
* @brief      Get DIO stream enum servers
* @ingroup    DATAIO
*
* @return     DIOSTREAMENUMSERVERS* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMENUMSERVERS* DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT::GetDIOStreamEnumServers()
{
  return diostreamenumservers;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT::SetDIOStreamEnumServers(DIOSTREAMENUMSERVERS* diostreamenumservers)
* @brief      Set DIO stream enum servers
* @ingroup    DATAIO
*
* @param[in]  diostreamenumservers :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT::SetDIOStreamEnumServers(DIOSTREAMENUMSERVERS* diostreamenumservers)
{
  this->diostreamenumservers = diostreamenumservers;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMCONFIG* DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT::GetDIOStreamConfig()
* @brief      Get DIO stream config
* @ingroup    DATAIO
*
* @return     DIOSTREAMCONFIG* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMCONFIG* DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT::GetDIOStreamConfig()
{
  return diostreamcfg;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT::SetDIOStreamConfig(DIOSTREAMCONFIG* diostreamcfg)
* @brief      Set DIO stream config
* @ingroup    DATAIO
*
* @param[in]  diostreamcfg :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT::SetDIOStreamConfig(DIOSTREAMCONFIG* diostreamcfg)
{
  this->diostreamcfg = diostreamcfg;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOPROTOCOL* DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT::GetDIOProtocol()
* @brief      Get DIO protocol
* @ingroup    DATAIO
*
* @return     DIOPROTOCOL* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOL* DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT::GetDIOProtocol()
{
  return dioprotocol;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT::SetDIOProtocol(DIOPROTOCOL* dioprotocol)
* @brief      Set DIO protocol
* @ingroup    DATAIO
*
* @param[in]  dioprotocol :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT::SetDIOProtocol(DIOPROTOCOL* dioprotocol)
{
  this->dioprotocol = dioprotocol;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOPROTOCOL_CONNECTION* DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT::GetProtocolConnection()
* @brief      Get protocol connection
* @ingroup    DATAIO
*
* @return     DIOPROTOCOL_CONNECTION* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOL_CONNECTION* DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT::GetProtocolConnection()
{
  return protocolconnection;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT::SetProtocolConnection(DIOPROTOCOL_CONNECTION* protocolconnection)
* @brief      Set protocol connection
* @ingroup    DATAIO
*
* @param[in]  protocolconnection :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT::SetProtocolConnection(DIOPROTOCOL_CONNECTION* protocolconnection)
{
  this->protocolconnection = protocolconnection;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOPROTOCOL_CONNECTIONSMANAGER* DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT::GetProtocolConnectionsManager()
* @brief      Get protocol connections manager
* @ingroup    DATAIO
*
* @return     DIOPROTOCOL_CONNECTIONSMANAGER* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOL_CONNECTIONSMANAGER* DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT::GetProtocolConnectionsManager()
{
  return protocolconnectionsmanager;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT::SetProtocolConnectionsManager(DIOPROTOCOL_CONNECTIONSMANAGER* protocolconnectionsmanager)
* @brief      Set protocol connections manager
* @ingroup    DATAIO
*
* @param[in]  protocolconnectionsmanager :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT::SetProtocolConnectionsManager(DIOPROTOCOL_CONNECTIONSMANAGER* protocolconnectionsmanager)
{
  this->protocolconnectionsmanager = protocolconnectionsmanager;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT::IsInitialized()
* @brief      Is initialized
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT::IsInitialized()
{
  return isinitialized;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT::SetIsInitialized(bool isinitialized)
* @brief      Set is initialized
* @ingroup    DATAIO
*
* @param[in]  isinitialized :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT::SetIsInitialized(bool isinitialized)
{
  this->isinitialized = isinitialized;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_CONNECTIONSMANAGER_XEVENT::Clean()
{
  diostreamenumservers       = NULL;
  diostreamcfg               = NULL;
  dioprotocol                = NULL;
  protocolconnection         = NULL;
  protocolconnectionsmanager = NULL;
  isinitialized              = false;
}


#pragma endregion

