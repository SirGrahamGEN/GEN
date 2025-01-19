/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOCheckTCPIPConnections.cpp
* 
* @class      DIOCHECKTCPIPCONNECTIONS
* @brief      Data Input/Output Check connections TPC/IP class
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

#include "DIOCheckTCPIPConnections.h"

#include "XFactory.h"
#include "XSleep.h"
#include "XTimer.h"
#include "XDateTime.h"
#include "XBuffer.h"
#include "XTrace.h"
#include "XThreadCollected.h"

#include "DIOFactory.h"
#include "DIOURL.h"
#include "DIOPing.h"

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


#pragma region CLASS_DIOCHECKTCPIPCONNECTION_CUT


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOCHECKTCPIPCONNECTION_CUT::DIOCHECKTCPIPCONNECTION_CUT()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOCHECKTCPIPCONNECTION_CUT::DIOCHECKTCPIPCONNECTION_CUT()
{
  Clean();

  GEN_XFACTORY_CREATE(startdatetime, CreateDateTime())
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOCHECKTCPIPCONNECTION_CUT::~DIOCHECKTCPIPCONNECTION_CUT()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOCHECKTCPIPCONNECTION_CUT::~DIOCHECKTCPIPCONNECTION_CUT()
{
  if(startdatetime) GEN_XFACTORY.DeleteDateTime(startdatetime);

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDATETIME* DIOCHECKTCPIPCONNECTION_CUT::GetStartDateTime()
* @brief      Get start date time
* @ingroup    DATAIO
*
* @return     XDATETIME* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDATETIME* DIOCHECKTCPIPCONNECTION_CUT::GetStartDateTime()
{
  return startdatetime;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOCHECKTCPIPCONNECTION_CUT::GetMeasureNSeconds()
* @brief      Get measure N seconds
* @ingroup    DATAIO
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOCHECKTCPIPCONNECTION_CUT::GetMeasureNSeconds()
{
  return nseconds;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOCHECKTCPIPCONNECTION_CUT::SetMeasureNSeconds(XDWORD nseconds)
* @brief      Set measure N seconds
* @ingroup    DATAIO
*
* @param[in]  nseconds :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCHECKTCPIPCONNECTION_CUT::SetMeasureNSeconds(XDWORD nseconds)
{
  this->nseconds = nseconds;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOCHECKTCPIPCONNECTION_CUT::GetMeasureTimeString(XSTRING& measuretime, bool large = false)
* @brief      Get measure time string
* @ingroup    DATAIO
*
* @param[in]  measuretime :
* @param[in]  large :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCHECKTCPIPCONNECTION_CUT::GetMeasureTimeString(XSTRING& measuretime, bool large)
{
  XTIMER xtimer;

  xtimer.Reset();
  xtimer.AddSeconds(GetMeasureNSeconds());

  xtimer.GetMeasureString(measuretime, large);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOCHECKTCPIPCONNECTION_CUT::CopyFrom(DIOCHECKTCPIPCONNECTION_CUT* connectioncut)
* @brief      Copy from
* @ingroup    DATAIO
*
* @param[in]  connectioncut :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCHECKTCPIPCONNECTION_CUT::CopyFrom(DIOCHECKTCPIPCONNECTION_CUT* connectioncut)
{
  if(!connectioncut)   return false;

  return connectioncut->CopyTo(this);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOCHECKTCPIPCONNECTION_CUT::CopyTo(DIOCHECKTCPIPCONNECTION_CUT* connectioncut)
* @brief      Copy to
* @ingroup    DATAIO
*
* @param[in]  connectioncut :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCHECKTCPIPCONNECTION_CUT::CopyTo(DIOCHECKTCPIPCONNECTION_CUT* connectioncut)
{
  if(!connectioncut)   return false;

  connectioncut->GetStartDateTime()->CopyFrom(startdatetime);
  connectioncut->SetMeasureNSeconds(nseconds);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOCHECKTCPIPCONNECTION_CUT::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCHECKTCPIPCONNECTION_CUT::Clean()
{
  startdatetime   = NULL;
  nseconds        = 0;
}


#pragma endregion


#pragma region CLASS_DIOCHECKTCPIPCONNECTION 


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOCHECKTCPIPCONNECTION::DIOCHECKTCPIPCONNECTION()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOCHECKTCPIPCONNECTION::DIOCHECKTCPIPCONNECTION()
{
  Clean();

  url = new DIOURL();
  
  GEN_XFACTORY_CREATE(timerconnexion, CreateTimer()) 
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOCHECKTCPIPCONNECTION::~DIOCHECKTCPIPCONNECTION()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOCHECKTCPIPCONNECTION::~DIOCHECKTCPIPCONNECTION()
{
  if(url) delete url;

  if(timerconnexion) GEN_XFACTORY.DeleteTimer(timerconnexion);

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOCHECKTCPIPCONNECTION::GetID()
* @brief      Get ID
* @ingroup    DATAIO
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOCHECKTCPIPCONNECTION::GetID()
{
  return ID;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOURL* DIOCHECKTCPIPCONNECTION::GetURL()
* @brief      Get URL
* @ingroup    DATAIO
*
* @return     DIOURL* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOURL* DIOCHECKTCPIPCONNECTION::GetURL()
{
  return url;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOCHECKTCPIPCONNECTION::IsConnected()
* @brief      Is connected
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCHECKTCPIPCONNECTION::IsConnected()
{
  return isconnected;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOCHECKTCPIPCONNECTION::SetIsConnected(bool isconnected)
* @brief      Set is connected
* @ingroup    DATAIO
*
* @param[in]  isconnected :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCHECKTCPIPCONNECTION::SetIsConnected(bool isconnected)
{
  this->isconnected = isconnected;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOCHECKTCPIPCONNECTION::GetNChecks()
* @brief      Get N checks
* @ingroup    DATAIO
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOCHECKTCPIPCONNECTION::GetNChecks()
{
  return nchecks;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOCHECKTCPIPCONNECTION::SetNChecks(XDWORD nchecks)
* @brief      Set N checks
* @ingroup    DATAIO
*
* @param[in]  nchecks :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCHECKTCPIPCONNECTION::SetNChecks(XDWORD nchecks)
{
  this->nchecks = nchecks;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOCHECKTCPIPCONNECTION::IncNChecks()
* @brief      Inc N checks
* @ingroup    DATAIO
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOCHECKTCPIPCONNECTION::IncNChecks()
{
  return ++nchecks;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOCHECKTCPIPCONNECTION::Set(XCHAR* url)
* @brief      Set
* @ingroup    DATAIO
*
* @param[in]  url :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCHECKTCPIPCONNECTION::Set(XCHAR* url)
{
  if(!this->url)  return 0;

  (*this->url) = url;

  this->url->Slash_Delete();

  ID = CreateID();

  return ID?true:false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOCHECKTCPIPCONNECTION::GetElapsedTime()
* @brief      Get elapsed time
* @ingroup    DATAIO
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOCHECKTCPIPCONNECTION::GetElapsedTime()
{
  return elapsedtime;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOCHECKTCPIPCONNECTION::SetElapsedTime(XDWORD elapsedtime)
* @brief      Set elapsed time
* @ingroup    DATAIO
*
* @param[in]  elapsedtime :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCHECKTCPIPCONNECTION::SetElapsedTime(XDWORD elapsedtime)
{
  this->elapsedtime = elapsedtime;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOCHECKTCPIPCONNECTION::ResetTimeConnexionStatus()
* @brief      Reset time connexion status
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCHECKTCPIPCONNECTION::ResetTimeConnexionStatus()
{
  if(!timerconnexion) return false;
  timerconnexion->Reset();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XQWORD DIOCHECKTCPIPCONNECTION::GetTimeConnexionStatus()
* @brief      Get time connexion status
* @ingroup    DATAIO
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XQWORD DIOCHECKTCPIPCONNECTION::GetTimeConnexionStatus()
{
  if(!timerconnexion) return 0;
  return timerconnexion->GetMeasureSeconds();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOCHECKTCPIPCONNECTION::CreateID()
* @brief      Create ID
* @ingroup    DATAIO
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOCHECKTCPIPCONNECTION::CreateID()
{
  HASHCRC32 hashcrc32;
  XDWORD    _ID = 0;

  XBUFFER charstr;
  
  url->ConvertToASCII(charstr);
  if(hashcrc32.Do((XBYTE*)charstr.Get(), url->GetSize())) _ID += hashcrc32.GetResultCRC32();
  
  return _ID;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOCHECKTCPIPCONNECTION::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCHECKTCPIPCONNECTION::Clean()
{
  ID                    = 0;
  url                   = NULL;
  isconnected           = false;
  nchecks               = 0;
  elapsedtime           = 0;
  timerconnexion        = NULL;
}


#pragma endregion


#pragma region CLASS_DIOCHECKTCPIPCONNECTIONS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOCHECKTCPIPCONNECTIONS::DIOCHECKTCPIPCONNECTIONS()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOCHECKTCPIPCONNECTIONS::DIOCHECKTCPIPCONNECTIONS()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOCHECKTCPIPCONNECTIONS::~DIOCHECKTCPIPCONNECTIONS()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOCHECKTCPIPCONNECTIONS::~DIOCHECKTCPIPCONNECTIONS()
{
  End();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOCHECKTCPIPCONNECTIONS::Ini(int timeconnectionchecks, bool validsomeisconnected, bool dispersionmode)
* @brief      Ini
* @ingroup    DATAIO
*
* @param[in]  timeconnectionchecks :
* @param[in]  validsomeisconnected :
* @param[in]  dispersionmode :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCHECKTCPIPCONNECTIONS::Ini(int timeconnectionchecks, bool validsomeisconnected, bool dispersionmode)
{
  Setup(timeconnectionchecks, validsomeisconnected, dispersionmode);

  GEN_XFACTORY_CREATE(xtimerfortimeconnectionchecks, CreateTimer())
  if(!xtimerfortimeconnectionchecks) return false;
      
  GEN_XFACTORY_CREATE(xmutexconnections, Create_Mutex())
  if(!xmutexconnections) return false;

  threadcheckconnections = CREATEXTHREAD(XTHREADGROUPID_DIOCHECKTCPIPCONNECTIONS, __L("DIOCHECKTCPIPCONNECTIONS::Ini"), ThreadCheckConnections, (void*)this);
  if(!threadcheckconnections)  return false;

  SetIsCheckTimeConnections(true);

  return threadcheckconnections->Ini();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOCHECKTCPIPCONNECTIONS::Run(bool activate)
* @brief      Run
* @ingroup    DATAIO
*
* @param[in]  activate :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCHECKTCPIPCONNECTIONS::Run(bool activate)
{
  if(!threadcheckconnections) return false;
  return threadcheckconnections->Run(activate);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOCHECKTCPIPCONNECTIONS::GetTimeConnectionChecks()
* @brief      Get time connection checks
* @ingroup    DATAIO
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOCHECKTCPIPCONNECTIONS::GetTimeConnectionChecks()
{
  return timeconnectionchecks;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOCHECKTCPIPCONNECTIONS::IsCheckTimeConnections()
* @brief      Is check time connections
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCHECKTCPIPCONNECTIONS::IsCheckTimeConnections()
{
  return ischecktimeconnections;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOCHECKTCPIPCONNECTIONS::SetIsCheckTimeConnections(bool ischecktimeconnections)
* @brief      Set is check time connections
* @ingroup    DATAIO
*
* @param[in]  ischecktimeconnections :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCHECKTCPIPCONNECTIONS::SetIsCheckTimeConnections(bool ischecktimeconnections)
{
  this->ischecktimeconnections = ischecktimeconnections;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOCHECKTCPIPCONNECTIONS::Setup(int timeconnectionchecks, bool validsomeisconnected, bool dispersionmode)
* @brief      Setup
* @ingroup    DATAIO
*
* @param[in]  timeconnectionchecks :
* @param[in]  validsomeisconnected :
* @param[in]  dispersionmode :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCHECKTCPIPCONNECTIONS::Setup(int timeconnectionchecks, bool validsomeisconnected, bool dispersionmode)
{
  this->timeconnectionchecks  = timeconnectionchecks;
  this->validsomeisconnected  = validsomeisconnected;
  this->dispersionmode        = dispersionmode;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOCHECKTCPIPCONNECTIONS::Connection_Add(XCHAR* url, XDWORD& ID)
* @brief      Connection add
* @ingroup    DATAIO
*
* @param[in]  url :
* @param[in]  ID :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCHECKTCPIPCONNECTIONS::Connection_Add(XCHAR* url, XDWORD& ID)
{
  DIOCHECKTCPIPCONNECTION* connection = new DIOCHECKTCPIPCONNECTION();
  if(!connection) return false;

  if(connection->Set(url))
    {
      ID = connection->GetID();

      if(ID)
        {
          if(xmutexconnections) xmutexconnections->Lock();

          connections.Add(connection);

          if(xmutexconnections) xmutexconnections->UnLock();

          return true;
        }
    }

  delete connection;

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOCHECKTCPIPCONNECTIONS::Connection_Add(XSTRING& url, XDWORD& ID)
* @brief      Connection add
* @ingroup    DATAIO
*
* @param[in]  url :
* @param[in]  ID :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCHECKTCPIPCONNECTIONS::Connection_Add(XSTRING& url, XDWORD& ID)
{
  return Connection_Add(url.Get(), ID);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOCHECKTCPIPCONNECTIONS::Connection_Add(DIOURL& url, XDWORD& ID)
* @brief      Connection add
* @ingroup    DATAIO
*
* @param[in]  url :
* @param[in]  ID :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCHECKTCPIPCONNECTIONS::Connection_Add(DIOURL& url, XDWORD& ID)
{
  return Connection_Add(url.Get(), ID);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn        DIOCHECKTCPIPCONNECTION* DIOCHECKTCPIPCONNECTIONS::Connection_GetByID(XDWORD ID)
* @brief      Connection_GetByID
* @ingroup    DATAIO
*
* @param[in]  ID :
*
* @return    DIOCHECKTCPIPCONNECTION* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOCHECKTCPIPCONNECTION* DIOCHECKTCPIPCONNECTIONS::Connection_GetByID(XDWORD ID)
{
  if(xmutexconnections) xmutexconnections->Lock();

  for(XDWORD c=0; c<connections.GetSize(); c++)
    {
      DIOCHECKTCPIPCONNECTION* cc = connections.Get(c);
      if(cc)
        {
          if(cc->GetID() == ID)
            {
              if(xmutexconnections) xmutexconnections->UnLock();
              return cc;
            }
        }
    }

  if(xmutexconnections) xmutexconnections->UnLock();

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOCHECKTCPIPCONNECTIONS::Connection_IsActive(XDWORD ID, bool& isactive)
* @brief      Connection is active
* @ingroup    DATAIO
*
* @param[in]  ID :
* @param[in]  isactive :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCHECKTCPIPCONNECTIONS::Connection_IsActive(XDWORD ID, bool& isactive)
{
  isactive = false;

  if(xmutexconnections) xmutexconnections->Lock();

  for(XDWORD c=0; c<connections.GetSize(); c++)
    {
      DIOCHECKTCPIPCONNECTION* cc = connections.Get(c);
      if(cc)
        {
          if(cc->GetID() == ID)
            {
              isactive = cc->IsConnected();
              if(xmutexconnections) xmutexconnections->UnLock();

              return true;
            }
        }
    }

  if(xmutexconnections) xmutexconnections->UnLock();

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOCHECKTCPIPCONNECTIONS::Connection_DeleteByID(XDWORD ID)
* @brief      Connection delete by ID
* @ingroup    DATAIO
*
* @param[in]  ID :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCHECKTCPIPCONNECTIONS::Connection_DeleteByID(XDWORD ID)
{
  DIOCHECKTCPIPCONNECTION* connection = Connection_GetByID(ID);
  if(connection)
    {
      if(xmutexconnections) xmutexconnections->Lock();

      connections.Delete(connection);
      delete connection;

      if(xmutexconnections) xmutexconnections->UnLock();

      return true;
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XMUTEX* DIOCHECKTCPIPCONNECTIONS::Connections_GetMutex()
* @brief      Connections get mutex
* @ingroup    DATAIO
* 
* @return     XMUTEX* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XMUTEX* DIOCHECKTCPIPCONNECTIONS::Connections_GetMutex()
{
  return xmutexconnections;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOCHECKTCPIPCONNECTIONS::Connections_IsAllChecked()
* @brief      Connections is all checked
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCHECKTCPIPCONNECTIONS::Connections_IsAllChecked()
{
  bool ischeckallconnections = true;

  if(xmutexconnections) xmutexconnections->Lock();

  for(XDWORD c=0; c<connections.GetSize(); c++)
    {
      DIOCHECKTCPIPCONNECTION* cc = connections.Get(c);
      if(cc)
        {
          if(!cc->GetNChecks()) ischeckallconnections = false;
        }
    }

  if(xmutexconnections) xmutexconnections->UnLock();

  return ischeckallconnections;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOCHECKTCPIPCONNECTIONS::Connections_IsSomeChecked()
* @brief      Connections is some checked
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCHECKTCPIPCONNECTIONS::Connections_IsSomeChecked()
{
  bool ischecksomeconnections = false;

  if(xmutexconnections) xmutexconnections->Lock();

  for(XDWORD c=0; c<connections.GetSize(); c++)
    {
      DIOCHECKTCPIPCONNECTION* cc = connections.Get(c);
      if(cc)
        {
          if(cc->GetNChecks())
            {
              ischecksomeconnections = true;
              break;
            }
        }
    }

  if(xmutexconnections) xmutexconnections->UnLock();

  return ischecksomeconnections;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOCHECKTCPIPCONNECTIONS::Connections_WaitToAllChecked(int timeout)
* @brief      Connections wait to all checked
* @ingroup    DATAIO
*
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCHECKTCPIPCONNECTIONS::Connections_WaitToAllChecked(int timeout)
{
  if(!connections.GetSize()) return false;

  XTIMER* GEN_XFACTORY_CREATE(xtimer, CreateTimer())
  if(!xtimer) return false;

  bool status = true;

  xtimer->Reset();

  SetIsCheckTimeConnections(false);

  while(1)
    {
      if(timeout != XTIMER_INFINITE)
        {
          if(xtimer->GetMeasureSeconds() >= (XDWORD)timeout)
            {
              status = false;
              break;
            }
        }

      if(Connections_IsAllChecked()) break;

      GEN_XSLEEP.MilliSeconds(100);
    }

  GEN_XFACTORY.DeleteTimer(xtimer);

  SetIsCheckTimeConnections(true);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOCHECKTCPIPCONNECTIONS::Connections_WaitToSomeIsChecked(int timeout)
* @brief      Connections wait to some is checked
* @ingroup    DATAIO
*
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCHECKTCPIPCONNECTIONS::Connections_WaitToSomeIsChecked(int timeout)
{
  if(!connections.GetSize()) return false;

  XTIMER* GEN_XFACTORY_CREATE(xtimer, CreateTimer())
  if(!xtimer) return false;
    
  bool status = true;

  xtimer->Reset();

  SetIsCheckTimeConnections(false);

  while(1)
    {
      if(timeout != XTIMER_INFINITE)
        {
          if(xtimer->GetMeasureSeconds() >= (XDWORD)timeout)
            {
              status = false;
              break;
            }
        }

      if(Connections_IsSomeChecked()) break;

      GEN_XSLEEP.MilliSeconds(100);
    }

  GEN_XFACTORY.DeleteTimer(xtimer);

  SetIsCheckTimeConnections(true);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOCHECKTCPIPCONNECTIONS::Connections_SomeIsConnected()
* @brief      Connections some is connected
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCHECKTCPIPCONNECTIONS::Connections_SomeIsConnected()
{
  bool someisactive = false;

  if(xmutexconnections) xmutexconnections->Lock();

  for(XDWORD c=0; c<connections.GetSize(); c++)
    {
      DIOCHECKTCPIPCONNECTION* cc = connections.Get(c);
      if(cc)
        {
          someisactive = cc->IsConnected();
          if(someisactive) break;
        }
    }

  if(xmutexconnections) xmutexconnections->UnLock();

  return someisactive;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOCHECKTCPIPCONNECTIONS::Connections_DeleteAll()
* @brief      Connections delete all
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCHECKTCPIPCONNECTIONS::Connections_DeleteAll()
{
  if(xmutexconnections) xmutexconnections->Lock();

  connections.DeleteContents();
  connections.DeleteAll();

  if(xmutexconnections) xmutexconnections->UnLock();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCHECKTCPIPCONNECTIONS::IsActivedExit()
* @brief      Is actived exit
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCHECKTCPIPCONNECTIONS::IsActivedExit()
{
  return activedexit;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCHECKTCPIPCONNECTIONS::SetActivedExit(bool actived)
* @brief      Set actived exit
* @ingroup    DATAIO
* 
* @param[in]  actived : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCHECKTCPIPCONNECTIONS::SetActivedExit(bool actived)
{
  activedexit = actived;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOCHECKTCPIPCONNECTIONS::End()
* @brief      End
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCHECKTCPIPCONNECTIONS::End()
{
  SetActivedExit(true); 

  if(threadcheckconnections)
    {
      threadcheckconnections->End();

      DELETEXTHREAD(XTHREADGROUPID_DIOCHECKTCPIPCONNECTIONS, threadcheckconnections);
      threadcheckconnections = NULL;
    }

  Connections_DeleteAll();

  if(xmutexconnections)
    {
      GEN_XFACTORY.Delete_Mutex(xmutexconnections);
      xmutexconnections = NULL;
    }
 
  if(xtimerfortimeconnectionchecks)
    {
      GEN_XFACTORY.DeleteTimer(xtimerfortimeconnectionchecks);
      xtimerfortimeconnectionchecks = NULL;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOCHECKTCPIPCONNECTIONS::ThreadCheckConnections(void* param)
* @brief      Thread check connections
* @ingroup    DATAIO
*
* @param[in]  param :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCHECKTCPIPCONNECTIONS::ThreadCheckConnections(void* param)
{
  DIOCHECKTCPIPCONNECTIONS* checkconnections = (DIOCHECKTCPIPCONNECTIONS*)param;
  if(!checkconnections) return;

  if(!checkconnections->xmutexconnections)                return;
  if(!checkconnections->xtimerfortimeconnectionchecks)    return;

  static int index = 0;

  int nconnections = checkconnections->connections.GetSize();
  if(!nconnections) return;

  if(checkconnections->activedexit)
    {
      return;
    }

  if(checkconnections->dispersionmode)
    {
      DIOCHECKTCPIPCONNECTION* checkconnection = checkconnections->connections.Get(index);
      if(!checkconnection)
        {
          index = 0;
          checkconnection = checkconnections->connections.Get(index);
        }

      if(checkconnection)
        {
          checkconnections->xmutexconnections->Lock();

          GEN_DIOPING.Set(checkconnection->GetURL()->Get());

          bool connexionstatus = GEN_DIOPING.Do(DIOCHECKTCPIPCONNECTIONS_DEFAULTNCHECKSFOREVERYCONNECTION, DIOCHECKTCPIPCONNECTIONS_DEFAULTTIMERCONNECTIONCHECK, checkconnections->validsomeisconnected);
          if(connexionstatus != checkconnection->IsConnected()) checkconnection->ResetTimeConnexionStatus();

          checkconnection->SetIsConnected(connexionstatus);
          checkconnection->IncNChecks();

          if(checkconnection->IsConnected())
                 checkconnection->SetElapsedTime(GEN_DIOPING.CalculateMeanTime());
            else checkconnection->SetElapsedTime(0);

          index++;

          checkconnections->xmutexconnections->UnLock();       
        }
    }
   else
    {
      checkconnections->xmutexconnections->Lock();

      for(int c=0; c<nconnections; c++)
        { 
          if(checkconnections->activedexit)
            {
              break; 
            }

          if(!checkconnections->threadcheckconnections->IsRunning()) 
            {
              break;             
            }

          DIOCHECKTCPIPCONNECTION* checkconnection = checkconnections->connections.Get(c);
          if(checkconnection)
            {
              GEN_DIOPING.Set(checkconnection->GetURL()->Get());

              bool connexionstatus = GEN_DIOPING.Do(DIOCHECKTCPIPCONNECTIONS_DEFAULTNCHECKSFOREVERYCONNECTION, DIOCHECKTCPIPCONNECTIONS_DEFAULTTIMERCONNECTIONCHECK, checkconnections->validsomeisconnected);
              if(connexionstatus != checkconnection->IsConnected()) 
                {
                  checkconnection->ResetTimeConnexionStatus();
                }

              checkconnection->SetIsConnected(connexionstatus);
              checkconnection->IncNChecks();

              if(checkconnection->IsConnected())
                      checkconnection->SetElapsedTime(GEN_DIOPING.CalculateMeanTime());
                else checkconnection->SetElapsedTime(0);

              if((checkconnections->validsomeisconnected) && (checkconnection->IsConnected())) 
                {
                  break;
                }              
            }
        }

      checkconnections->xmutexconnections->UnLock();      
    }

  if(checkconnections->IsCheckTimeConnections())
    {
      for(int e=0; e<checkconnections->timeconnectionchecks; e++)
        {
          if(checkconnections->activedexit)
            {
              break; 
            }

          if(!checkconnections->threadcheckconnections->IsRunning()) 
            {
              break;
            }

          // Wait One second
          for(int d=0; d<10; d++)
            {
              if(checkconnections->activedexit)
                {
                  break; 
                }

              if(!checkconnections->threadcheckconnections->IsRunning()) 
                {
                  break;
                }

              GEN_XSLEEP.MilliSeconds(100);
            }
        }
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOCHECKTCPIPCONNECTIONS::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCHECKTCPIPCONNECTIONS::Clean()
{
  timeconnectionchecks                = DIOCHECKTCPIPCONNECTIONS_DEFAULTTIMECONNECTIONCHECKS;
  validsomeisconnected                = false;
  dispersionmode                      = false;

  xtimerfortimeconnectionchecks       = NULL;
  ischecktimeconnections              = false;

  xmutexconnections                   = NULL;
  threadcheckconnections              = NULL;

  activedexit                         = false;
}


#pragma endregion


#pragma endregion




