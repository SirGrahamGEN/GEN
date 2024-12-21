/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOCoreProtocol_ConnectionsManager.h
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

#ifndef _DIOCOREPROTOCOL_CONNECTIONSMANAGER_H_
#define _DIOCOREPROTOCOL_CONNECTIONSMANAGER_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XUUID.h"
#include "XObserver.h"
#include "XSubject.h"
#include "XThreadCollected.h"

#include "DIOStream_XEvent.h"
#include "DIOCoreProtocol_CFG.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


#define COMMAND_DO_WITHOUTPARAMS(connection, message_priority, command_type, result, timeout)    { XUUID ID_message;                                                                     \
                                                                                                   bool  status  = false;                                                                \
                                                                                                   if(!connection)                                                                       \
                                                                                                     {                                                                                   \
                                                                                                       return false;                                                                     \
                                                                                                     }                                                                                   \
                                                                                                   if(connection->DoCommand(&ID_message, message_priority, command_type))                \
                                                                                                     {                                                                                   \
                                                                                                       status = GetResult(connection, &ID_message, result, timeout);                     \
                                                                                                     }                                                                                   \
                                                                                                   return status;                                                                        \
                                                                                                 }                                                                                         

 #define COMMAND_DO(connection, message_priority, command_type, params, result, timeout)         { XUUID ID_message;                                                                     \
                                                                                                   bool  status  = false;                                                                \
                                                                                                   if(!connection)                                                                       \
                                                                                                     {                                                                                   \
                                                                                                       return false;                                                                     \
                                                                                                     }                                                                                   \
                                                                                                   if(connection->DoCommand(&ID_message, message_priority, command_type, params))        \
                                                                                                     {                                                                                   \
                                                                                                       status = GetResult(connection, &ID_message, result, timeout);                     \
                                                                                                     }                                                                                   \
                                                                                                   return status;                                                                        \
                                                                                                 }                                                                                         



#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class XTIMER;
class XMUTEX;
class XBUFFER;
class XSTRING;
class XFILEJSON;
class XSERIALIZABLE;
class DIOCOREPROTOCOL;
class DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT;
class DIOCOREPROTOCOL_CONNECTION;
class DIOCOREPROTOCOL_MESSAGE;


class DIOCOREPROTOCOL_CONNECTIONSMANAGER : public XOBSERVER, public XSUBJECT
{
  public:
                                            DIOCOREPROTOCOL_CONNECTIONSMANAGER            ();
    virtual                                ~DIOCOREPROTOCOL_CONNECTIONSMANAGER            ();   

    bool                                    Ini                                           ();
    bool                                    End                                           ();

    DIOCOREPROTOCOL_CFG*                    GetProtocolCFG                                ();

    XMAP<DIOSTREAMCONFIG*, DIOSTREAM*>*     DIOStream_GetAll                              ();
    bool                                    DIOStream_Add                                 (DIOSTREAMCONFIG* diostreamCFG, DIOSTREAM* diostream);
    bool                                    DIOStream_Delete                              (DIOSTREAMCONFIG* diostreamCFG);
    bool                                    DIOStream_DeleteAll                           ();

    virtual DIOCOREPROTOCOL*                CreateProtocol                                (DIOSTREAM* diostream);    

    bool                                    Command_Do                                    (DIOCOREPROTOCOL_CONNECTION* connection, XBYTE message_priority, XDWORD command_type, XBUFFER& result, XDWORD timeout);
    bool                                    Command_Do                                    (DIOCOREPROTOCOL_CONNECTION* connection, XBYTE message_priority, XDWORD command_type, XSTRING& result, XDWORD timeout);
    bool                                    Command_Do                                    (DIOCOREPROTOCOL_CONNECTION* connection, XBYTE message_priority, XDWORD command_type, XFILEJSON& result, XDWORD timeout);

    bool                                    Command_Do                                    (DIOCOREPROTOCOL_CONNECTION* connection, XBYTE message_priority, XDWORD command_type, XBUFFER* params, XBUFFER& result, XDWORD timeout);
    bool                                    Command_Do                                    (DIOCOREPROTOCOL_CONNECTION* connection, XBYTE message_priority, XDWORD command_type, XSTRING* params, XBUFFER& result, XDWORD timeout);
    bool                                    Command_Do                                    (DIOCOREPROTOCOL_CONNECTION* connection, XBYTE message_priority, XDWORD command_type, XFILEJSON* params, XBUFFER& result, XDWORD timeout);
    
    bool                                    Command_Do                                    (DIOCOREPROTOCOL_CONNECTION* connection, XBYTE message_priority, XDWORD command_type, XBUFFER* params, XSTRING& result, XDWORD timeout);
    bool                                    Command_Do                                    (DIOCOREPROTOCOL_CONNECTION* connection, XBYTE message_priority, XDWORD command_type, XSTRING* params, XSTRING& result, XDWORD timeout);
    bool                                    Command_Do                                    (DIOCOREPROTOCOL_CONNECTION* connection, XBYTE message_priority, XDWORD command_type, XFILEJSON* params, XSTRING& result, XDWORD timeout);
    
    bool                                    Command_Do                                    (DIOCOREPROTOCOL_CONNECTION* connection, XBYTE message_priority, XDWORD command_type, XBUFFER* params, XFILEJSON& result, XDWORD timeout);
    bool                                    Command_Do                                    (DIOCOREPROTOCOL_CONNECTION* connection, XBYTE message_priority, XDWORD command_type, XSTRING* params, XFILEJSON& result, XDWORD timeout);
    bool                                    Command_Do                                    (DIOCOREPROTOCOL_CONNECTION* connection, XBYTE message_priority, XDWORD command_type, XFILEJSON* params, XFILEJSON& result, XDWORD timeout);
    
    bool                                    UpdateClass_Do                                (DIOCOREPROTOCOL_CONNECTION* connection, XBYTE message_priority, XCHAR* classname, XSERIALIZABLE* classcontent, XDWORD timeout);

    bool                                    GetResult                                     (DIOCOREPROTOCOL_CONNECTION* connection, XUUID* ID_message, XBUFFER& result, XDWORD timeout);
    bool                                    GetResult                                     (DIOCOREPROTOCOL_CONNECTION* connection, XUUID* ID_message, XSTRING& result, XDWORD timeout);
    bool                                    GetResult                                     (DIOCOREPROTOCOL_CONNECTION* connection, XUUID* ID_message, XFILEJSON& result, XDWORD timeout);
                              
    XVECTOR<DIOCOREPROTOCOL_CONNECTION*>*   Connections_GetAll                            ();
    XMUTEX*                                 Connections_GetXMutex                         ();  
    DIOCOREPROTOCOL_CONNECTION*             Connections_Add                               (DIOSTREAM* stream);
    DIOCOREPROTOCOL_CONNECTION*             Connections_Get                               (DIOSTREAM* stream);
    DIOCOREPROTOCOL_CONNECTION*             Connections_Get                               (XDWORD index);
    bool                                    Connections_Delete                            (DIOCOREPROTOCOL_CONNECTION* connection);    
    bool                                    Connections_DeleteAllDisconnected             ();
    bool                                    Connections_DeleteAll                         ();
       
  protected:
    
    DIOCOREPROTOCOL_CFG                     protocolCFG;    
    XMAP<DIOSTREAMCONFIG*, DIOSTREAM*>      diostreams;

  private:

    bool                                    Connections_ReadMessages                      (); 

    bool                                    Received_AllCommandMessages                   (DIOCOREPROTOCOL_CONNECTION* connection, DIOCOREPROTOCOL_MESSAGE* message); 
    bool                                    Received_AdditionsCommand                     (DIOCOREPROTOCOL_CONNECTION* connection, DIOCOREPROTOCOL_MESSAGE* message);

    bool                                    Received_AllUpdateClassMessages               (DIOCOREPROTOCOL_CONNECTION* connection, DIOCOREPROTOCOL_MESSAGE* message);
        
    bool                                    CreateIDMachine                               (XUUID& ID);
      
    virtual void                            HandleEvent_CoreProtocolConnectionsManager    (DIOCOREPROTOCOL_CONNECTIONSMANAGER_XEVENT* event);
    void                                    HandleEvent_DIOStream                         (DIOSTREAM_XEVENT* event);
    void                                    HandleEvent                                   (XEVENT* xevent);

    static void                             ThreadConnections                             (void* param);
    static void                             ThreadHeartBets                               (void* param);

    void                                    Clean                                         ();
          
    XMUTEX*                                 connections_xmutex;
    XTHREADCOLLECTED*                       connections_xthread;
    XTHREADCOLLECTED*                       heartbets_xthread;
   
    XVECTOR<DIOCOREPROTOCOL_CONNECTION*>    connections;
};

#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif



