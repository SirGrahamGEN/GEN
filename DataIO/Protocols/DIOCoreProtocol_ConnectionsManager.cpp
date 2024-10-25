/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOCoreProtocol_ConnectionsManager.cpp
* 
* @class      DIOCOREPROTOCOL_CONNECTIONSMANAGER
* @brief      Data Input/Output Core Protocol Connections Manager class
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

#include "DIOCoreProtocol_ConnectionsManager.h"

#include "XFactory.h"

#include "DIOStream.h"
#include "DIOStreamEnumServers.h"

#include "DIOCoreProtocol_CFG.h"

#include "XMemory_Control.h"


#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#pragma region CLASS_DIOCOREPROTOCOL_CONNECTIONSMANAGER


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_CONNECTIONSMANAGER::DIOCOREPROTOCOL_CONNECTIONSMANAGER(DIOCOREPROTOCOL_CFG* protocolCFG)
* @brief      Constructor
* @ingroup    DATAIO
* 
* @param[in]  DIOCOREPROTOCOL_CFG* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_CONNECTIONSMANAGER::DIOCOREPROTOCOL_CONNECTIONSMANAGER()
{
  Clean();

 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_CONNECTIONSMANAGER::~DIOCOREPROTOCOL_CONNECTIONSMANAGER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_CONNECTIONSMANAGER::~DIOCOREPROTOCOL_CONNECTIONSMANAGER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::Ini()
* @brief      Ini
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::Ini(DIOCOREPROTOCOL_CFG* protocolCFG)
{ 
  bool status = false;
 
  if(!protocolCFG)
    {
      return false;
    }

  this->protocolCFG = protocolCFG;   

  DIOSTREAM* diostream = protocolCFG->GetDIOStream();
  if(!diostream)
    {
      return false;
    }

  if(!diostream->IsConnected())
    {
      if(diostream->Open())
        {
          if(!diostream->WaitToConnected(1500))
            {
              return false;
            }            
        }
    }

  GEN_XFACTORY_CREATE(connections_xmutex, Create_Mutex())
  if(connections_xmutex) 
    {
      GEN_XFACTORY_CREATE(connections_xtimer, CreateTimer())
      if(connections_xtimer)
        {      
          connections_xthread = CREATEXTHREAD(XTHREADGROUPID_DIOPROTOCOL_CONNECTIONMANAGER, __L("DIOPROTOCOL_CONNECTIONSMANAGER::Ini"), ThreadConnections, (void*)this);
          if(connections_xthread)
            {
              if(connections_xthread->Ini()) 
                {
                  return true;
                }
            }
        }      
    }

  End();

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::End()
* @brief      End
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::End()
{
  if(connections_xthread)
    {
      connections_xthread->End();
      DELETEXTHREAD(XTHREADGROUPID_DIOPROTOCOL_CONNECTIONMANAGER, connections_xthread);
      connections_xthread = NULL;
    }  

  if(connections_xtimer)
    {
      GEN_XFACTORY.DeleteTimer(connections_xtimer);
      connections_xtimer = NULL;
    }

  if(connections_xmutex)
    {
      GEN_XFACTORY.Delete_Mutex(connections_xmutex);
      connections_xmutex = NULL;
    }

  DIOSTREAM* diostream = protocolCFG->GetDIOStream();
  if(diostream)
    {
      diostream->Close();      
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_CFG* DIOCOREPROTOCOL_CONNECTIONSMANAGER::GetProtocolCFG()
* @brief      GetProtocolCFG
* @ingroup    DATAIO
* 
* @return     DIOCOREPROTOCOL_CFG* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_CFG* DIOCOREPROTOCOL_CONNECTIONSMANAGER::GetProtocolCFG()
{
  return protocolCFG;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<DIOCOREPROTOCOL_CONNECTION*>* DIOCOREPROTOCOL_CONNECTIONSMANAGER::GetConnections()
* @brief      GetConnections
* @ingroup    DATAIO
* 
* @return     XVECTOR<DIOCOREPROTOCOL_CONNECTION*>* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<DIOCOREPROTOCOL_CONNECTION*>* DIOCOREPROTOCOL_CONNECTIONSMANAGER::GetConnections()
{
  return &connections;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::ReConnected()
* @brief      ReConnected
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CONNECTIONSMANAGER::ReConnected()
{  
  if(!protocolCFG)
    {
      return false;
    }  
   
  DIOSTREAM* diostream = protocolCFG->GetDIOStream();
  if(!diostream)
    {
      return false;
    }

  bool status = false;
  
  if(!diostream->IsConnected())
    {
      if(diostream->Open())
        {
          if(!diostream->WaitToConnected(1500))
            {
              return false;
            }
        }
    }

  if(!diostream->IsConnected())
    {
      return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_CONNECTIONSMANAGER::ThreadConnections(void* param)
* @brief      ThreadConnections
* @ingroup    DATAIO
* 
* @param[in]  param : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_CONNECTIONSMANAGER::ThreadConnections(void* param)
{
  DIOCOREPROTOCOL_CONNECTIONSMANAGER* connectionsmanager = (DIOCOREPROTOCOL_CONNECTIONSMANAGER*)param;
  if(!connectionsmanager) 
    {
      return;
    }

  DIOCOREPROTOCOL_CFG* protocolCFG = connectionsmanager->GetProtocolCFG();
  if(!protocolCFG)
    {
      return;
    }  
   
  DIOSTREAM* diostream = protocolCFG->GetDIOStream();
  if(!diostream)
    {
      return;
    }

  /*
  bool status = connectionsmanager->ReConnected();
  if(!status)
    {
      return;
    }
  */
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_CONNECTIONSMANAGER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_CONNECTIONSMANAGER::Clean()
{
  protocolCFG                 = NULL;

  connections_xtimer          = NULL;      
  connections_xmutex          = NULL;
  connections_xthread         = NULL;
}


#pragma endregion


