/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOCheckInternetConnection.cpp
* 
* @class      DIOCHECKINTERNETCONNECTION
* @brief      Data Input/Output Check Connection Internet class
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

#include "DIOCheckInternetConnection.h"

#include "XFactory.h"
#include "XDateTime.h"

#include "DIOCheckTCPIPConnections.h"

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
* @fn         DIOCHECKINTERNETCONNECTION::DIOCHECKINTERNETCONNECTION(int timeconnectionchecks)
* @brief      Constructor of class
* @ingroup    DATAIO
*
* @param[in]  timeconnectionchecks :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOCHECKINTERNETCONNECTION::DIOCHECKINTERNETCONNECTION(int timeconnectionchecks)
{
  typedef struct { XCHAR* ipaddr;
                   XCHAR* name;

                 } MAINDNS;


  MAINDNS  maindns[] = {  { __L("8.8.8.8")          , __L("Google DNS 1")                                 },
                          { __L("8.8.4.4")          , __L("Google DNS 2")                                 },
                          { __L("198.41.0.4")       , __L("VeriSign, Inc.")                               },
                          
                          /*               
                          { __L("192.228.79.201")   , __L("University of Southern California (ISI)")      },
                          { __L("192.33.4.12")      , __L("Cogent Communications")                        },
                          { __L("199.7.91.13")      , __L("University of Maryland")                       },
                          { __L("192.203.230.10")   , __L("NASA (Ames Research Center)")                  },
                          { __L("192.5.5.241")      , __L("Internet Systems Consortium, Inc.")            },
                          { __L("198.97.190.53")    , __L("US Army (Research Lab)")                       },
                          { __L("192.36.148.17")    , __L("Netnod")                                       },
                          { __L("192.58.128.30")    , __L("VeriSign, Inc.")                               },
                          { __L("193.0.14.129")     , __L("RIPE NCC")                                     },
                          { __L("199.7.83.42")      , __L("ICANN")                                        },
                          { __L("202.12.27.33")     , __L("WIDE Project")                                 }
                          */
                       };
  Clean();

  checkconnections = new DIOCHECKTCPIPCONNECTIONS();
  if(!checkconnections) return;

  GEN_XFACTORY_CREATE(xmutexconnectioncuts, Create_Mutex())

  checkconnections->Ini(timeconnectionchecks, true, true);

  for(int c=0; c<(sizeof(maindns)/sizeof(MAINDNS)); c++)
    {
      checkconnections->Connection_Add(maindns[c].ipaddr, connectionID[c]);
    }

  checkconnections->Connections_WaitToSomeIsChecked(checkconnections->GetTimeConnectionChecks());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOCHECKINTERNETCONNECTION::~DIOCHECKINTERNETCONNECTION()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOCHECKINTERNETCONNECTION::~DIOCHECKINTERNETCONNECTION()
{
  DeleteAllConnectionCuts();

  if(checkconnections)
    {
      for(int c=0; c<DIOCHECKINTERNETCONNECTION_MAXCONNECTIONS; c++)
        {
          checkconnections->Connection_DeleteByID(connectionID[c]);
        }
    }

  if(checkconnections)
    {
      delete checkconnections;
      checkconnections = NULL;
    }

  GEN_XFACTORY.Delete_Mutex(xmutexconnectioncuts);

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOCHECKTCPIPCONNECTIONS* DIOCHECKINTERNETCONNECTION::GetCheckConnections()
* @brief      Get check connections
* @ingroup    DATAIO
*
* @return     DIOCHECKTCPIPCONNECTIONS* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOCHECKTCPIPCONNECTIONS* DIOCHECKINTERNETCONNECTION::GetCheckConnections()
{
  return checkconnections;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOCHECKINTERNETCONNECTION::Check()
* @brief      Check
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCHECKINTERNETCONNECTION::Check()
{
  if(!checkconnections) return false;

  bool        isinternetactive    = false;
  static bool isinternetactiveold = false;

  isinternetactive = checkconnections->Connections_SomeIsConnected(); 
 
  if(isinternetactiveold != isinternetactive)
    {
      if(!isinternetactive)
        {
          DIOCHECKTCPIPCONNECTION_CUT connectioncut;

          connectioncut.GetStartDateTime()->Read();
          connectioncut.SetMeasureNSeconds((XDWORD)DIOCHECKTCPIPCONNECTIONS_INFINITECUT);

          AddConnectionCut(connectioncut);
        }
       else
        {
          if(GetConnectionCuts()->GetSize())
            {
              DIOCHECKTCPIPCONNECTION_CUT* connectioncut = GetConnectionCuts()->Get(GetConnectionCuts()->GetSize()-1);
              if(connectioncut)
                {
                  if(connectioncut->GetMeasureNSeconds() == DIOCHECKTCPIPCONNECTIONS_INFINITECUT)
                    {
                      XDATETIME* GEN_XFACTORY_CREATE(xdatetime, CreateDateTime())
                      if(xdatetime)
                        {
                          xdatetime->Read();

                          connectioncut->SetMeasureNSeconds((int)(xdatetime->GetSeconsFromDate() - connectioncut->GetStartDateTime()->GetSeconsFromDate()));

                          GEN_XFACTORY.DeleteDateTime(xdatetime);
                        }
                    }
                }
            }
        }

      isinternetactiveold = isinternetactive;

      ischangeconnectionstatus = true;

    } else ischangeconnectionstatus = false;


  return isinternetactive;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOCHECKINTERNETCONNECTION::AddConnectionCut(DIOCHECKTCPIPCONNECTION_CUT& connectioncut)
* @brief      Add connection cut
* @ingroup    DATAIO
*
* @param[in]  connectioncut :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCHECKINTERNETCONNECTION::AddConnectionCut(DIOCHECKTCPIPCONNECTION_CUT& connectioncut)
{
  DIOCHECKTCPIPCONNECTION_CUT* chekconnectioncut = new DIOCHECKTCPIPCONNECTION_CUT();
  if(!chekconnectioncut) return false;

  chekconnectioncut->CopyFrom(&connectioncut);

  if(connectioncuts.GetSize() >= DIOCHECKTCPIPCONNECTIONS_MAXNCONNECTIONCUTS) connectioncuts.Delete(connectioncuts.Get(0));

  connectioncuts.Add(chekconnectioncut);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOCHECKINTERNETCONNECTION::DeleteAllConnectionCuts()
* @brief      Delete all connection cuts
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCHECKINTERNETCONNECTION::DeleteAllConnectionCuts()
{
  if(connectioncuts.IsEmpty()) return false;

  if(!xmutexconnectioncuts) return false;

  xmutexconnectioncuts->Lock();

  connectioncuts.DeleteContents();
  connectioncuts.DeleteAll();

  xmutexconnectioncuts->UnLock();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XVECTOR<DIOCHECKTCPIPCONNECTION_CUT*>* DIOCHECKINTERNETCONNECTION::GetConnectionCuts()
* @brief      Get connection cuts
* @ingroup    DATAIO
*
* @return     XVECTOR<DIOCHECKTCPIPCONNECTION_CUT*>* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<DIOCHECKTCPIPCONNECTION_CUT*>*   DIOCHECKINTERNETCONNECTION::GetConnectionCuts()
{
  return &connectioncuts;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOCHECKTCPIPCONNECTION_CUT* DIOCHECKINTERNETCONNECTION::GetLastConnectionsCut()
* @brief      Get last connections cut
* @ingroup    DATAIO
*
* @return     DIOCHECKTCPIPCONNECTION_CUT* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOCHECKTCPIPCONNECTION_CUT* DIOCHECKINTERNETCONNECTION::GetLastConnectionsCut()
{
  return GetConnectionCuts()->Get(GetConnectionCuts()->GetSize()-1);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOCHECKINTERNETCONNECTION::IsChangeConnectionStatus()
* @brief      Is change connection status
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCHECKINTERNETCONNECTION::IsChangeConnectionStatus()
{
  return ischangeconnectionstatus;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOCHECKINTERNETCONNECTION::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCHECKINTERNETCONNECTION::Clean()
{
  checkconnections         = NULL;

  for(int c=0; c<DIOCHECKINTERNETCONNECTION_MAXCONNECTIONS; c++)
    {
      connectionID[c] = 0;
    }

  ischangeconnectionstatus = false;
  xmutexconnectioncuts     = NULL;
}


#pragma endregion

