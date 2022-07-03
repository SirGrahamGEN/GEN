/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOProtocolCLIBus.h
* 
* @class      DIOPROTOCOLCLIBUS
* @brief      Home Server Sensors Protocol
* @ingroup    
* 
* @author     Abraham J. Velez 
* @date       23/06/2022 17:42:05
* 
* @copyright  EndoraSoft S.L.  All rights reserved.
* 
* --------------------------------------------------------------------------------------------------------------------*/

#ifndef _DIOPROTOCOLCLIBUS_H_
#define _DIOPROTOCOLCLIBUS_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XString.h"
#include "XVector.h"

#include "DIOProtocolCLI.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define DIOPROTOCOLCLIBUS_VERSION									  0
#define DIOPROTOCOLCLIBUS_SUBVERSION							  1
#define DIOPROTOCOLCLIBUS_SUBVERSIONERR						  0 

#define DIOPROTOCOLCLIBUS_COMMAND_VERSION			    __L("version")
#define DIOPROTOCOLCLIBUS_COMMAND_PING   			    __L("ping")

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class DIOPROTOCOLCLIBUS : public DIOPROTOCOLCLI
{
  public:
                            DIOPROTOCOLCLIBUS             ();
    virtual                ~DIOPROTOCOLCLIBUS             ();

    bool                    Ini                           (DIOSTREAM* diostream, XCHAR* ID, int timeout = DIOPROTOCOLCLI_TIMEOUT);

    bool                    SendCommand                   (XCHAR* command, XSTRING* target, XSTRING* answer, int timeoutanswer, ...);

    bool                    ReceivedCommand               (XSTRING& command, XVECTOR<XSTRING*>& params, XSTRING& answer);  
    void                    ReceivedAnswer                (XSTRING& origin, XSTRING& command, XSTRING& answer);

    void                    End                           ();
   
  private:

	  static void						  ThreadReceivedCommand         (void* param); 
    
    void                    Clean                         ();

    XTHREADCOLLECTED*				threadreceivedcommand;

    

};

/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif
