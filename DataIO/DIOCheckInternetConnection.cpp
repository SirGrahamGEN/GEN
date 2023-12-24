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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XFactory.h"
#include "XDateTime.h"

#include "DIOCheckTCPIPConnections.h"

#include "DIOCheckInternetConnection.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOCHECKINTERNETCONNECTION::DIOCHECKINTERNETCONNECTION(int timeconnectionchecks)
* @brief      Constructor
* @ingroup    DATAIO
*
* @param[in]  int :
*
* @return     Does not return anything.
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

                        //{ __L("192.228.79.201")   , __L("University of Southern California (ISI)")      },
                        //{ __L("192.33.4.12")      , __L("Cogent Communications")                        },
                        //{ __L("199.7.91.13")      , __L("University of Maryland")                       },
                        //{ __L("192.203.230.10")   , __L("NASA (Ames Research Center)")                  },
                        //{ __L("192.5.5.241")      , __L("Internet Systems Consortium, Inc.")            },
                        //{ __L("192.112.36.4")     , __L("US Department of Defense (NIC)")               },
                        //{ __L("198.97.190.53")    , __L("US Army (Research Lab)")                       },
                        //{ __L("192.36.148.17")    , __L("Netnod")                                       },
                        //{ __L("192.58.128.30")    , __L("VeriSign, Inc.")                               },
                        //{ __L("193.0.14.129")     , __L("RIPE NCC")                                     },
                        //{ __L("199.7.83.42")      , __L("ICANN")                                        },
                        //{ __L("202.12.27.33")     , __L("WIDE Project")                                 }
                       };

  /*
  MAINDNS  maindns[] = {  { __L("209.244.0.4")          , __L("Level3 1")                                 },
                          { __L("209.244.0.3")          , __L("Level3 2")                                 },
                          { __L("9.9.9.9")              , __L("IBM Quad9")                                },
                          { __L("64.6.64.6")            , __L("Verisign 1")                               },
                          { __L("64.6.65.6")            , __L("Verisign 2")                               },
                          { __L("8.8.8.8")              , __L("Google 1")                                 },
                          { __L("8.8.4.4")              , __L("Google 2")                                 },
                          { __L("84.200.69.80")         , __L("WATCH 1")                                  },
                          { __L("84.200.70.40")         , __L("WATCH 2")                                  },
                          { __L("8.26.56.26")           , __L("Comodo Secure DNS 1")                      },
                          { __L("8.20.247.20")          , __L("Comodo Secure DNS 2")                      },
                          { __L("208.67.222.222")       , __L("OpenDNS Home 1")                           },
                          { __L("208.67.220.220")       , __L("OpenDNS Home 2")                           },
                          { __L("156.154.70.1")         , __L("DNS Advantage 1")                          },
                          { __L("156.154.71.1")         , __L("DNS Advantage 2")                          },
                          { __L("199.85.126.10")        , __L("Norton ConnectSafe 1")                     },
                          { __L("199.85.127.10")        , __L("Norton ConnectSafe 2")                     },
                          { __L("81.218.119.11")        , __L("GreenTeamDNS 1")                           },
                          { __L("209.88.198.133")       , __L("GreenTeamDNS 2")                           },
                          { __L("195.46.39.39")         , __L("SafeDNS 1")                                },
                          { __L("195.46.39.40")         , __L("SafeDNS 2")                                },
                          { __L("96.90.175.167")        , __L("OpenNIC 1")                                },
                          { __L("193.183.98.154")       , __L("OpenNIC 2")                                },
                          { __L("208.76.50.50")         , __L("SmartViper 1")                             },
                          { __L("208.76.51.51")         , __L("SmartViper 2")                             },
                          { __L("216.146.35.35")        , __L("Dyn 1")                                    },
                          { __L("216.146.36.36")        , __L("Dyn 2")                                    },
                          { __L("37.235.1.174")         , __L("FreeDNS 1")                                },
                          { __L("37.235.1.177")         , __L("FreeDNS 2")                                },
                          { __L("198.101.242.72")       , __L("Alternate DNS 1")                          },
                          { __L("23.253.163.53")        , __L("Alternate DNS 2")                          },
                          { __L("77.88.8.8")            , __L("DNS 1")                                    },
                          { __L("77.88.8.1")            , __L("DNS 2")                                    },
                          { __L("91.239.100.100")       , __L("UncensoredDNS 1")                          },
                          { __L("89.233.43.71")         , __L("UncensoredDNS 2")                          },
                          { __L("74.82.42.42")          , __L("Hurricane Electric")                       },
                          { __L("87.118.111.215")       , __L("FoolDNS 1")                                },
                          { __L("213.187.11.67")        , __L("FoolDNS 2")                                },
                          { __L("109.69.8.51")          , __L("puntCAT")                                  },
                       };
  */

  Clean();

  checkconnections = new DIOCHECKTCPIPCONNECTIONS();
  if(!checkconnections) return;

  GEN_XFACTORY_CREATE(xmutexconnectioncuts, Create_Mutex())

  checkconnections->Ini(checkconnections->GetTimeConnectionChecks(), true, true);

  for(int c=0; c<(sizeof(maindns)/sizeof(MAINDNS)); c++)
    {
      checkconnections->Connection_Add(maindns[c].ipaddr, connectionID[c]);
    }

  checkconnections->Connections_WaitToSomeIsChecked(checkconnections->GetTimeConnectionChecks());
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOCHECKINTERNETCONNECTION::~DIOCHECKINTERNETCONNECTION()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @return     Does not return anything.
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
* @brief      GetCheckConnections
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
* @brief      AddConnectionCut
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
* @brief      DeleteAllConnectionCuts
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
* @brief      GetConnectionCuts
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
* @brief      GetLastConnectionsCut
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
* @brief      IsChangeConnectionStatus
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
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @return     void : does not return anything.
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






