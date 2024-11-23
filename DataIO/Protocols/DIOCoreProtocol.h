/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOCoreProtocol.h
* 
* @class      DIOCOREPROTOCOL
* @brief      Data Input/Output Core Protocol class
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

#ifndef _DIOCOREPROTOCOL_H_
#define _DIOCOREPROTOCOL_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XFileJSON.h"

#include "DIOStream.h"

#include "DIOCoreProtocol_Header.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

#define DIOCOREPROTOCOL_AUTHENTICATION_CHALLENGE_OPERATION_PARAM         __L("challenge")
#define DIOCOREPROTOCOL_AUTHENTICATION_RESPONSE_OPERATION_PARAM          __L("response")
#define DIOCOREPROTOCOL_KEYEXCHANGE_SERVER_OPERATION_PARAM               __L("key server")
#define DIOCOREPROTOCOL_KEYEXCHANGE_CLIENT_OPERATION_PARAM               __L("key client")

enum DIOCOREPROTOCOL_COMMAND_TYPE
{
  DIOCOREPROTOCOL_COMMAND_TYPE_UNKNOWN                   = 0  ,
  DIOCOREPROTOCOL_COMMAND_TYPE_HEARTBEAT                      ,

  DIOCOREPROTOCOL_COMMAND_TYPE_LASTINTERNAL                   
};


#pragma endregion


/*---- CLASS ---------------------------------------------------------c------------------------------------------------*/
#pragma region CLASS

class XUUI;
class COMPRESSMANAGER;
class COMPRESSBASE;    	
class DIOCOREPROTOCOL_HEADER;
class DIOCOREPROTOCOL_CFG;
class CIPHERKEYSYMMETRICAL;


class DIOCOREPROTOCOL
{
  public:
                                              
                                              DIOCOREPROTOCOL                     (DIOCOREPROTOCOL_CFG* protocolCFG, DIOSTREAM* diostream, XUUID* IDmachine);
    virtual                                  ~DIOCOREPROTOCOL                     ();

    bool                                      Ini                                 ();
    bool                                      End                                 ();

    DIOCOREPROTOCOL_CFG*                      GetProtocolCFG                      ();

    DIOSTREAM*                                GetDIOStream                        (); 
    void                                      SetDIOStream                        (DIOSTREAM* diostream);      

    bool                                      SendMsg                             (DIOCOREPROTOCOL_HEADER* header, XBUFFER& contentresult);
    bool                                      ReceivedMsg                         (DIOCOREPROTOCOL_HEADER& header, XBUFFER& content);
 
    DIOCOREPROTOCOL_HEADER*                   CreateHeader                        (XUUID* ID_message, XBYTE message_priority, DIOCOREPROTOCOL_HEADER_OPERATION operation, XCHAR* operation_param, XBUFFER& content, XBUFFER& contentresult);
    DIOCOREPROTOCOL_HEADER*                   CreateHeader                        (XUUID* ID_message, XBYTE message_priority, DIOCOREPROTOCOL_HEADER_OPERATION operation, XCHAR* operation_param, XSTRING& content, XBUFFER& contentresult);
    DIOCOREPROTOCOL_HEADER*                   CreateHeader                        (XUUID* ID_message, XBYTE message_priority, DIOCOREPROTOCOL_HEADER_OPERATION operation, XCHAR* operation_param, XFILEJSON& content, XBUFFER& contentresult);

    virtual bool                              GenerateAuthenticationChallenge     (XBUFFER& autentication_challange);
    virtual bool                              GenerateAuthenticationResponse      (XBUFFER& autentication_challange, XBUFFER& autentication_response);
    
    bool                                      MaskKey                             (XBYTE* key, int size, XBYTE mask);

    bool                                      Commands_Add                        (XDWORD type, XCHAR* command);
    XDWORD                                    Commands_Get                        (XCHAR* command);
    XCHAR*                                    Commands_Get                        (XDWORD type);
    bool                                      Commands_DeleteAll                  ();

    bool                                      ShowDebug                           (bool send, DIOCOREPROTOCOL_HEADER* header, XBUFFER& content);  

  protected:

    DIOCOREPROTOCOL_CFG*                      protocolCFG;
    DIOSTREAM*                                diostream;    
    bool                                      initialization; 
    
  private:

    DIOCOREPROTOCOL_HEADER*                   CreateHeader                        (XUUID* ID_message, XBYTE message_priority, DIOCOREPROTOCOL_HEADER_OPERATION operation, XCHAR* operation_param);
   
    bool                                      GenerateHeaderToSend                (DIOCOREPROTOCOL_HEADER* header, XBUFFER& headerdatasend, XWORD* headersize = NULL);
      
    bool                                      SendData                            (XBUFFER& senddata);
    bool                                      CompressContent                     (DIOCOREPROTOCOL_HEADER* header, XBUFFER& content, XBUFFER& contentresult);

    void                                      Clean                               ();   
   
    XUUID*                                    ID_machine;
    
    COMPRESSMANAGER*	                        compressmanager;
    COMPRESSBASE*			                        compressor; 

    XMAP<int, XSTRING*>                       commands;   	   
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif


