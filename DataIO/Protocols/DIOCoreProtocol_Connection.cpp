/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOCoreProtocol_Connection.cpp
* 
* @class      DIOCOREPROTOCOL_CONNECTION
* @brief      Data Input/Output Core Protocol Connection class
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
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIOCoreProtocol_Connection.h"

#include "XFactory.h"
#include "XTimer.h"
#include "XThreadCollected.h"

#include "DIOStream.h"
#include "DIOStreamEnumServers.h"

#include "DIOCoreProtocol.h"

#include "XMemory_Control.h"


#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#pragma region CLASS_DIOCOREPROTOCOL_CONNECTION


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_CONNECTION::DIOCOREPROTOCOL_CONNECTION()
* @brief      Constructor
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_CONNECTION::DIOCOREPROTOCOL_CONNECTION()
{
  Clean();

  xtimerstatus = GEN_XFACTORY.CreateTimer();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_CONNECTION::~DIOCOREPROTOCOL_CONNECTION()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_CONNECTION::~DIOCOREPROTOCOL_CONNECTION()
{
  if(protocol)
    {
      delete protocol;
    }

  if(xtimerstatus)
    {
      GEN_XFACTORY.DeleteTimer(xtimerstatus);
    }

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_CONNECTION_STATUS DIOCOREPROTOCOL_CONNECTION::GetStatus()
* @brief      GetStatus
* @ingroup    DATAIO
* 
* @return     DIOCOREPROTOCOL_CONNECTION_STATUS : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_CONNECTION_STATUS DIOCOREPROTOCOL_CONNECTION::GetStatus()
{
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_CONNECTION::SetStatus(DIOCOREPROTOCOL_CONNECTION_STATUS status)
* @brief      SetStatus
* @ingroup    DATAIO
* 
* @param[in]  status : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_CONNECTION::SetStatus(DIOCOREPROTOCOL_CONNECTION_STATUS status)
{
  if(this->status != status)
    {
      if(xtimerstatus)
        {
          xtimerstatus->Reset();
        }
    }

  this->status = status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTION::GetStatusString(XSTRING status)
* @brief      GetStatusString
* @ingroup    DATAIO
* 
* @param[in]  status : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTION::GetStatusString(XSTRING& statusstring)
{
  statusstring.Empty();

  switch(status)
    {
      case DIOCOREPROTOCOL_CONNECTION_STATUS_NONE           : statusstring = __L("None");
                                                              break;

      case DIOCOREPROTOCOL_CONNECTION_STATUS_CONNECTED      : statusstring = __L("Connected");
                                                              break;

      case DIOCOREPROTOCOL_CONNECTION_STATUS_IDENTIFIED     : statusstring = __L("Identified");
                                                              break;

      case DIOCOREPROTOCOL_CONNECTION_STATUS_AUTHENTICATED  : statusstring = __L("Authenticated");
                                                              break;

      case DIOCOREPROTOCOL_CONNECTION_STATUS_INITIALIZED    : statusstring = __L("Initialized");
                                                              break;

      case DIOCOREPROTOCOL_CONNECTION_STATUS_DISCONNECTED   : statusstring = __L("Disconnected");
                                                              break;
    }

  if(statusstring.IsEmpty())
    {
      return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XTIMER* DIOCOREPROTOCOL_CONNECTION::GetXTimerStatus()
* @brief      GetXTimerStatus
* @ingroup    DATAIO
* 
* @return     XTIMER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XTIMER* DIOCOREPROTOCOL_CONNECTION::GetXTimerStatus()
{
  return xtimerstatus;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOSTREAM* DIOCOREPROTOCOL_CONNECTION::GetDIOStream()
* @brief      GetDIOStream
* @ingroup    DATAIO
* 
* @return     DIOSTREAM* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAM* DIOCOREPROTOCOL_CONNECTION::GetDIOStream()
{
  return diostream;
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTION::SetDIOStream(DIOSTREAM* diostream)
* @brief      SetDIOStream
* @ingroup    DATAIO
* 
* @param[in]  diostream : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTION::SetDIOStream(DIOSTREAM* diostream)
{
  this->diostream = diostream;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL* DIOCOREPROTOCOL_CONNECTION::GetCoreProtocol()
* @brief      GetCoreProtocol
* @ingroup    DATAIO
* 
* @return     DIOCOREPROTOCOL* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL* DIOCOREPROTOCOL_CONNECTION::GetCoreProtocol()
{
  return protocol;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTION::SetCoreProtocol(DIOCOREPROTOCOL* protocol)
* @brief      SetCoreProtocol
* @ingroup    DATAIO
* 
* @param[in]  protocol : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTION::SetCoreProtocol(DIOCOREPROTOCOL* protocol)
{
  this->protocol = protocol;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<DIOCOREPROTOCOL_MESSAGE*>* DIOCOREPROTOCOL_CONNECTION::GetMessages()
* @brief      GetMessages
* @ingroup    DATAIO
* 
* @return     XVECTOR<DIOCOREPROTOCOL_MESSAGE*>* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<DIOCOREPROTOCOL_MESSAGE*>* DIOCOREPROTOCOL_CONNECTION::GetMsgs()
{
  return &messages;
}

 
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_CONNECTION::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_CONNECTION::Clean()
{
  diostream     = NULL;
  protocol      = NULL;

  status        = DIOCOREPROTOCOL_CONNECTION_STATUS_NONE; 
  xtimerstatus  = NULL;
}


#pragma endregion

