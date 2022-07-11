/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOProtocolCLIBus.cpp
* 
* @class      DIOPROTOCOLCLIBUS
* @brief      Home Server Sensors Protocol
* @ingroup    
* 
* @author     Abraham J. Velez 
* @date       23/06/2022 17:36:10
* 
* @copyright  EndoraSoft S.L.  All rights reserved.
* 
* --------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XFactory.h"
#include "XRand.h"
#include "XTrace.h"
#include "XThreadCollected.h"

#include "DIOProtocolCLIBus.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPROTOCOLCLIBUS::DIOPROTOCOLCLIBUS()
* @brief      Constructor
* @ingroup    
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOLCLIBUS::DIOPROTOCOLCLIBUS()
{
  Clean();

  nretries = DIOPROTOCOLCLIBUS_SEND_DEFAULNRETRIES;

	AddCommand(DIOPROTOCOLCLIBUS_COMMAND_VERSION			      , 0);
	AddCommand(DIOPROTOCOLCLIBUS_COMMAND_PING					      , 0);
  AddCommand(DIOPROTOCOLCLIBUS_COMMAND_ENUM 				      , 0);
  AddCommand(DIOPROTOCOLCLIBUS_COMMAND_ENUMREQUEST        , 0);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPROTOCOLCLIBUS::~DIOPROTOCOLCLIBUS()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOLCLIBUS::~DIOPROTOCOLCLIBUS()
{
  enum_remotedevices.DeleteContents();
  enum_remotedevices.DeleteAll();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPROTOCOLCLIBUS::Ini(DIOSTREAM* diostream, XCHAR* ID, int timeout)
* @brief      Ini
* @ingroup    
* 
* @param[in]  diostream : 
* @param[in]  ID : 
* @param[in]  timeout : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOLCLIBUS::Ini(DIOSTREAM* diostream, XCHAR* ID, int timeout)
{	
	this->ID = ID;

  enum_mutex = GEN_XFACTORY.Create_Mutex();
  if(!enum_mutex) return false;

  threadsendenumrequest	= CREATEXTHREAD(XTHREADGROUPID_DIOPROTOCOL_CLI_BUS, __L("DIOPROTOCOLCLIBUS::Ini2"), ThreadSendEnumRequest, (void*)this);
  if(!threadsendenumrequest) return false;

	threadreceivedcommand	= CREATEXTHREAD(XTHREADGROUPID_DIOPROTOCOL_CLI_BUS, __L("DIOPROTOCOLCLIBUS::Ini"), ThreadReceivedCommand,	(void*)this);
  if(!threadreceivedcommand) return false;

  enum_timer = GEN_XFACTORY.CreateTimer();
  if(!enum_timer) return false;
  	
  if(!threadreceivedcommand->Ini()) return false;

  return DIOPROTOCOLCLI::Ini(diostream, ID, timeout);  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPROTOCOLCLIBUS::GetVersion(XDWORD& version, XDWORD& subversion, XDWORD& subversionerror)
* @brief      GetVersion
* @ingroup    DATAIO
* 
* @param[in]  version : 
* @param[in]  subversion : 
* @param[in]  subversionerror : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOLCLIBUS::GetVersion(XDWORD& version, XDWORD& subversion, XDWORD& subversionerror)
{
  if((!version) && (!subversion) && (!subversionerror)) return false;

  version         = this->version;
  subversion      = this->subversion;
  subversionerror = this->subversionerror;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOPROTOCOLCLIBUS::SetVersion(XDWORD version, XDWORD subversion, XDWORD subversionerror)
* @brief      SetVersion
* @ingroup    DATAIO
* 
* @param[in]  version : 
* @param[in]  subversion : 
* @param[in]  subversionerror : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOLCLIBUS::SetVersion(XDWORD version, XDWORD subversion, XDWORD subversionerror)
{
  this->version         = version;
  this->subversion      = subversion;
  this->subversionerror = subversionerror;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPROTOCOLCLIBUS::EnumRemoteDevices(XVECTOR<XSTRING*>* remotedevices, int enummaxtime)
* @brief      EnumRemoteDevices
* @ingroup    DATAIO
* 
* @param[in]  remotedevices : 
* @param[in]  enummaxtime : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOLCLIBUS::EnumRemoteDevices(XVECTOR<XSTRING*>* remotedevices, XDWORD maxtime)
{
  bool status = false;

  enum_remotedevices.DeleteContents();
  enum_remotedevices.DeleteAll();

  if(!enum_timer) return false;

  SendCommand(DIOPROTOCOLCLIBUS_COMMAND_ENUM, NULL, NULL, 0);
    
  enum_maxtimersec = maxtime;

  enum_timer->Reset();

  if(remotedevices)
    {
      remotedevices->DeleteContents();
      remotedevices->DeleteAll();

      do{ GEN_XSLEEP.Seconds(1);           

        } while(enum_timer->GetMeasureSeconds() < enum_maxtimersec); 

      status = GetEnumRemoteDevices((*remotedevices));

    } else status = true;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPROTOCOLCLIBUS::GetEnumRemoteDevices(XVECTOR<XSTRING*>& remotedevices)
* @brief      GetEnumRemoteDevices
* @ingroup    DATAIO
* 
* @param[in]  remotedevices : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOLCLIBUS::GetEnumRemoteDevices(XVECTOR<XSTRING*>& remotedevices)
{
  if(!enum_timer)       return false;
  if(!enum_maxtimersec) return false;

  if(enum_timer->GetMeasureSeconds() < enum_maxtimersec) return false;

  for(XDWORD c=0; c<enum_remotedevices.GetSize(); c++)
    {
      XSTRING* device = new XSTRING();
      if(device)
        {
          (*device) = enum_remotedevices.Get(c)->Get();
          remotedevices.Add(device);
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int DIOPROTOCOLCLIBUS::GetNRetries()
* @brief      GetNRetries
* @ingroup    DATAIO
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int DIOPROTOCOLCLIBUS::GetNRetries()
{
  return nretries;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOPROTOCOLCLIBUS::SetNRetries(int nretries)
* @brief      SetNRetries
* @ingroup    DATAIO
* 
* @param[in]  nretries : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOLCLIBUS::SetNRetries(int nretries)
{
  this->nretries = nretries;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPROTOCOLCLIBUS::SendCommand(XCHAR* command, XSTRING* target, XSTRING* answer, int timeoutanswer, ...)
* @brief      SendCommand
* @ingroup    
* 
* @param[in]  command : 
* @param[in]  target : 
* @param[in]  answer : 
* @param[in]  timeoutanswer : 
* @param[in]  ... : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOLCLIBUS::SendCommand(XCHAR* command, XSTRING* target, XSTRING* answer, int timeoutanswer, ...)
{
  if(!command) return false;
  
  XRAND*  xrand;
  XSTRING _command  = command;
  XSTRING _answer;
  bool    status    = false;
  
  xrand    = GEN_XFACTORY.CreateRand();
  if(!xrand) return false;  

  xrand->Ini();

  int timedelay = xrand->Between(500, 3000);

  va_list arg;
			
  va_start(arg, timeoutanswer);	

  int nr = GetNRetries();

  if(!answer) nr = 1;
    
  for(int c=0; c<nr; c++)
    {	
      if(exitproccess) 
        {
          status = false;
          break;
        }

      status = DIOPROTOCOLCLI::SendCommand(command, target, answer, timeoutanswer, arg);
      if(status) break;
      
      GEN_XSLEEP.MilliSeconds(timedelay);      
    }
																		
  va_end(arg);

  GEN_XFACTORY.DeleteRand(xrand);

  if(answer) _answer = (*answer);

  return status;
}    


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPROTOCOLCLIBUS::ReceivedCommand(XSTRING& receivedID, XSTRING& command, XVECTOR<XSTRING*>& params, XSTRING& answer)
* @brief      ReceivedCommand
* @ingroup    
* 
* @param[in]  receivedID : 
* @param[in]  command : 
* @param[in]  params : 
* @param[in]  answer : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOLCLIBUS::ReceivedCommand(XSTRING& originID, XSTRING& command, XVECTOR<XSTRING*>& params, XSTRING& answer)
{
  bool status = false;
  
	answer.Empty();  
  
  DIOPROTOCOLCLICOMMAND* protocolcommand = GetCommand(command.Get());
	if(protocolcommand) 
		{
			if(protocolcommand->GetNParams() < (int)params.GetSize()) return false;			

			if(!command.Compare(DIOPROTOCOLCLIBUS_COMMAND_VERSION, true))	  		 
				{
					answer.Format(__L("%d.%d.%d"), version, subversion, subversionerror); 
					status = true;            
				}

			if(!command.Compare(DIOPROTOCOLCLIBUS_COMMAND_PING, true))	  		 
				{					
					status = true;            
				}

      if(!command.Compare(DIOPROTOCOLCLIBUS_COMMAND_ENUM, true))	  		 
				{		
          enum_mutex->Lock();

          enum_sendoriginID = originID;

          enum_mutex->UnLock();

          threadsendenumrequest->Ini();
				}
      
      if(!command.Compare(DIOPROTOCOLCLIBUS_COMMAND_ENUMREQUEST, true))
        {
          bool found = false;

          for(XDWORD c=0; c<enum_remotedevices.GetSize(); c++)
            {
              XSTRING* device = enum_remotedevices.Get(c);
              if(device)
                {
                  if(!device->Compare(originID, true)) found = true;
                }
            }

          if(!found)
            {
              XSTRING* origin = new XSTRING();
              if(origin)
                {
                  (*origin) = originID;    
                  enum_remotedevices.Add(origin);
                }
            }
         
          status = true;
        }
		}

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOPROTOCOLCLIBUS::End()
* @brief      End
* @ingroup    
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOLCLIBUS::End()
{
  exitproccess = true;

  if(threadsendenumrequest)					
    {
      threadsendenumrequest->End();
      DELETEXTHREAD(XTHREADGROUPID_DIOPROTOCOL_CLI_BUS, threadsendenumrequest);
      
      threadsendenumrequest = NULL;
    }

  if(threadreceivedcommand)					
    {
      threadreceivedcommand->End();
      DELETEXTHREAD(XTHREADGROUPID_DIOPROTOCOL_CLI_BUS, threadreceivedcommand);
      
      threadreceivedcommand = NULL;
    }

  if(enum_mutex)
    { 
      GEN_XFACTORY.Delete_Mutex(enum_mutex);
      enum_mutex = NULL;
    }

  if(enum_timer)
    {
      GEN_XFACTORY.DeleteTimer(enum_timer);
      enum_timer = NULL;
    }

  return DIOPROTOCOLCLI::End();  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOPROTOCOLCLIBUS::ThreadReceivedCommand(void* param)
* @brief      ThreadReceivedCommand
* @ingroup    
* 
* @param[in]  param : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOLCLIBUS::ThreadReceivedCommand(void* param)
{
  DIOPROTOCOLCLIBUS* sp = (DIOPROTOCOLCLIBUS*)param;
	if(!sp) return;

  if(sp->exitproccess) 
    { 
      sp->threadreceivedcommand->Run(false);
      return;
    }

  sp->ReceivedCommandManager();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOPROTOCOLCLIBUS::ThreadSendEnumRequest(void* param)
* @brief      ThreadSendEnumRequest
* @ingroup    DATAIO
* 
* @param[in]  param : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOLCLIBUS::ThreadSendEnumRequest(void* param)
{
  DIOPROTOCOLCLIBUS* sp = (DIOPROTOCOLCLIBUS*)param;
	if(!sp) return;

  if(sp->exitproccess) 
    {
      sp->threadsendenumrequest->Run(false);
      return;
    }

  sp->enum_mutex->Lock();

  if(sp->enum_sendoriginID.IsEmpty()) 
    {
      sp->threadsendenumrequest->Run(false); 
    }
   else
    {    
      XSTRING answer;
  
      bool status = sp->SendCommand(DIOPROTOCOLCLIBUS_COMMAND_ENUMREQUEST, &sp->enum_sendoriginID, &answer, 6); 
      if(status)
        {
          sp->enum_sendoriginID.Empty();
        }
    } 

  sp->enum_mutex->UnLock();

  GEN_XSLEEP.Seconds(8);
}




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOPROTOCOLCLIBUS::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOLCLIBUS::Clean()
{
  version                 = 0;
  subversion              = 0;
  subversionerror         = 0;

  nretries                = 0;

  exitproccess            = false;

  enum_mutex              = NULL;
  enum_sendoriginID.Empty();
  enum_timer              = NULL;
  enum_maxtimersec        = 0;

	threadreceivedcommand   = NULL;
  threadsendenumrequest   = NULL;
}
