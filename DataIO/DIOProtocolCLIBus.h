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

#define DIOPROTOCOLCLIBUS_ENUM_DEFAULTMAXTIME     30
#define DIOPROTOCOLCLIBUS_SEND_DEFAULNRETRIES     3

#define DIOPROTOCOLCLIBUS_COMMAND_VERSION			    __L("version")
#define DIOPROTOCOLCLIBUS_COMMAND_PING   			    __L("ping")
#define DIOPROTOCOLCLIBUS_COMMAND_ENUM  			    __L("enum")
#define DIOPROTOCOLCLIBUS_COMMAND_ENUMREQUEST     __L("enumrequest")

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class DIOPROTOCOLCLIBUS : public DIOPROTOCOLCLI
{
  public:
                            DIOPROTOCOLCLIBUS             ();
    virtual                ~DIOPROTOCOLCLIBUS             ();
    
    bool                    Ini                           (DIOSTREAM* diostream, XCHAR* ID, int timeout = DIOPROTOCOLCLI_TIMEOUT);

    bool                    GetVersion                    (XDWORD& version, XDWORD& subversion, XDWORD& subversionerror);
    void                    SetVersion                    (XDWORD version, XDWORD subversion, XDWORD subversionerror);    
   
    bool                    EnumRemoteDevices             (XVECTOR<XSTRING*>* remotedevices = NULL, XDWORD maxtime = DIOPROTOCOLCLIBUS_ENUM_DEFAULTMAXTIME);
    bool                    GetEnumRemoteDevices          (XVECTOR<XSTRING*>& remotedevices);
    
    int                     GetNRetries                   ();
    void                    SetNRetries                   (int nretries = DIOPROTOCOLCLIBUS_SEND_DEFAULNRETRIES);

    bool                    SendCommand                   (XCHAR* command, XSTRING* target, XSTRING* answer, int timeoutanswer, ...);

    virtual bool            ReceivedCommand               (XSTRING& originID, XSTRING& command, XVECTOR<XSTRING*>& params, XSTRING& answer);
    
    void                    End                           ();
   
  private:

	  static void						  ThreadReceivedCommand         (void* param);
    static void             ThreadSendEnumRequest         (void* param);
    
    void                    Clean                         ();

    XDWORD                  version;
    XDWORD                  subversion;
    XDWORD                  subversionerror;

    XDWORD                  nretries;

    bool                    exitproccess;  

    XMUTEX*                 enum_mutex;
    XVECTOR<XSTRING*>       enum_remotedevices;
    XSTRING                 enum_sendoriginID;
    XTIMER*                 enum_timer;
    XDWORD                  enum_maxtimersec;
    
    XTHREADCOLLECTED*				threadreceivedcommand;
    XTHREADCOLLECTED*				threadsendenumrequest;
};

/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif
