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

	AddCommand(DIOPROTOCOLCLIBUS_COMMAND_VERSION			      , 0);
	AddCommand(DIOPROTOCOLCLIBUS_COMMAND_PING					      , 0);
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

	threadreceivedcommand	= CREATEXTHREAD(XTHREADGROUPID_DIOPROTOCOL_CLI_BUS, __L("DIOPROTOCOLCLIBUS::Ini()"), ThreadReceivedCommand,	(void*)this);
  if(!threadreceivedcommand) return false;
  
  if(!threadreceivedcommand->Ini()) return false;

  return DIOPROTOCOLCLI::Ini(diostream, ID, timeout);  
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

  for(int c=0; c<3; c++)
    {	
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
bool DIOPROTOCOLCLIBUS::ReceivedCommand(XSTRING& command, XVECTOR<XSTRING*>& params, XSTRING& answer)
{
  bool status = false;
  
	answer.Empty();  
  
  DIOPROTOCOLCLICOMMAND* protocolcommand = GetCommand(command.Get());
	if(protocolcommand) 
		{
			if(protocolcommand->GetNParams() < (int)params.GetSize()) return false;			

			if(!command.Compare(DIOPROTOCOLCLIBUS_COMMAND_VERSION, true))	  		 
				{
					answer.Format(__L("%d.%d.%d"), DIOPROTOCOLCLIBUS_VERSION, DIOPROTOCOLCLIBUS_SUBVERSION, DIOPROTOCOLCLIBUS_SUBVERSIONERR); 
					status = true;            
				}

			if(!command.Compare(DIOPROTOCOLCLIBUS_COMMAND_PING, true))	  		 
				{					
					status = true;            
				}
		}

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOPROTOCOLCLIBUS::ReceivedAnswer(XSTRING& origin, XSTRING& command, XSTRING& answer)
* @brief      ReceivedAnswer
* @ingroup    
* 
* @param[in]  origin : 
* @param[in]  command : 
* @param[in]  answer : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOLCLIBUS::ReceivedAnswer(XSTRING& origin, XSTRING& command, XSTRING& answer)
{
  
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
  if(threadreceivedcommand)					
    {
      threadreceivedcommand->End();
      DELETEXTHREAD(XTHREADGROUPID_DIOSTREAMI2C, threadreceivedcommand);
      
      threadreceivedcommand = NULL;
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

  sp->ReceivedCommandManager();
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
	threadreceivedcommand =  NULL;
}
