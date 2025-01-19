/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOCoreProtocol_ConnectionsManager_XEvent.cpp
* 
* @class      DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT
* @brief      Data Input/Output Core Protocol Connections Manager eXtended Event class
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

#include "DIOCoreProtocol_ConnectionsManager_XEvent.h"

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
* @fn         DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT::DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family)
* @brief      Constructor of class
* @ingroup    DATAIO
*
* @param[in]  subject :
* @param[in]  family :
* @param[in]  type :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT::DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family): XEVENT(subject, type, family)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT::~DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT::~DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_CONNECTION* DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT::GetConnection()
* @brief      Get connection
* @ingroup    DATAIO
* 
* @return     DIOCOREPROTOCOL_CONNECTION* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_CONNECTION* DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT::GetConnection()
{
  return connection;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT::SetConnection(DIOCOREPROTOCOL_CONNECTION* connection)
* @brief      Set connection
* @ingroup    DATAIO
* 
* @param[in]  connection : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT::SetConnection(DIOCOREPROTOCOL_CONNECTION* connection)
{
  if(!connection) 
    {
      return false;
    }

  this->connection = connection;

  return true;
}

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_CONNECTION_STATUS DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT::GetActualStatus()
* @brief      Get actual status
* @ingroup    DATAIO
* 
* @return     DIOCOREPROTOCOL_CONNECTION_STATUS : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_CONNECTION_STATUS DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT::GetActualStatus()
{
  return actualstatus;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT::SetActualStatus(DIOCOREPROTOCOL_CONNECTION_STATUS actualstatus)
* @brief      Set actual status
* @ingroup    DATAIO
* 
* @param[in]  actualstatus : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT::SetActualStatus(DIOCOREPROTOCOL_CONNECTION_STATUS actualstatus)
{
  this->actualstatus = actualstatus;
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_CONNECTION_STATUS DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT::GetNextStatus()
* @brief      Get next status
* @ingroup    DATAIO
* 
* @return     DIOCOREPROTOCOL_CONNECTION_STATUS : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_CONNECTION_STATUS DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT::GetNextStatus()
{
  return nextstatus;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT::SetNextStatus(DIOCOREPROTOCOL_CONNECTION_STATUS nextstatus)
* @brief      Set next status
* @ingroup    DATAIO
* 
* @param[in]  nextstatus : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT::SetNextStatus(DIOCOREPROTOCOL_CONNECTION_STATUS nextstatus)
{
  this->nextstatus = nextstatus;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_MESSAGE* DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT::GetMsg()
* @brief      Get msg
* @ingroup    DATAIO
* 
* @return     DIOCOREPROTOCOL_MESSAGE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_MESSAGE* DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT::GetMsg()
{
  return message;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT::SetMsg(DIOCOREPROTOCOL_MESSAGE* message)
* @brief      Set msg
* @ingroup    DATAIO
* 
* @param[in]  message : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT::SetMsg(DIOCOREPROTOCOL_MESSAGE* message)
{
  this->message = message;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBUFFER* DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT::GetContentResponseBuffer()
* @brief      Get content response buffer
* @ingroup    DATAIO
* 
* @return     XBUFFER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBUFFER* DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT::GetContentResponseBuffer()
{
  return &contentresponsebuffer;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT::GetContenteResponseString()
* @brief      Get contente response string
* @ingroup    DATAIO
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT::GetContenteResponseString()
{
  return &contentresponsestring;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILEJSON* DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT::GetContenteResponseXFileJSON()
* @brief      Get contente response X file JSON
* @ingroup    DATAIO
* 
* @return     XFILEJSON* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XFILEJSON* DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT::GetContenteResponseXFileJSON()
{
  return &contentresponsexfileJSON;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT::Clean()
{
  connection    = NULL;  

  actualstatus  = DIOCOREPROTOCOL_CONNECTION_STATUS_NONE;  
  nextstatus    = DIOCOREPROTOCOL_CONNECTION_STATUS_NONE;  

  message       = NULL;
}


#pragma endregion

