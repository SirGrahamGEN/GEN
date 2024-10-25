/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOCoreProtocolHeader.h
* 
* @class      DIOCOREPROTOCOL_HEADER
* @brief      Data Input/Output Core Protocol Header class
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

#ifndef _DIOCOREPROTOCOL_HEADER_H_
#define _DIOCOREPROTOCOL_HEADER_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES


#include "XUUID.h"
#include "XFileJSON.h"
#include "XSerializable.h"
#include "XSerializationMethod.h"

#include "DIOStream.h"


#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

//#define DIOCOREPROTOCOL_HEADER_HUMANFORMAT_ACTIVE

enum DIOCOREPROTOCOL_HEADER_MESSAGETYPE
{
  DIOCOREPROTOCOL_HEADER_MESSAGETYPE_UNKNOWN           = 0 ,
  DIOCOREPROTOCOL_HEADER_MESSAGETYPE_REQUEST               ,
  DIOCOREPROTOCOL_HEADER_MESSAGETYPE_RESPONSE              
};


#define DIOCOREPROTOCOL_HEADER_MESSAGETYPE_STRING_UNKNOWN            __L("unknown")
#define DIOCOREPROTOCOL_HEADER_MESSAGETYPE_STRING_REQUEST            __L("request")
#define DIOCOREPROTOCOL_HEADER_MESSAGETYPE_STRING_RESPONSE           __L("response")


enum DIOCOREPROTOCOL_HEADER_CONTENTTYPE
{
  DIOCOREPROTOCOL_HEADER_CONTENTTYPE_UNKNOWN           = 0 ,
  DIOCOREPROTOCOL_HEADER_CONTENTTYPE_BINARY                ,
  DIOCOREPROTOCOL_HEADER_CONTENTTYPE_TEXT                  ,
  DIOCOREPROTOCOL_HEADER_CONTENTTYPE_JSON                  ,  
};


#define DIOCOREPROTOCOL_HEADER_CONTENTTYPE_STRING_UNKNOWN            __L("unknown")
#define DIOCOREPROTOCOL_HEADER_CONTENTTYPE_STRING_BINARY             __L("binary")
#define DIOCOREPROTOCOL_HEADER_CONTENTTYPE_STRING_TEXT               __L("text")
#define DIOCOREPROTOCOL_HEADER_CONTENTTYPE_STRING_JSON               __L("json")


enum DIOCOREPROTOCOL_HEADER_CONTENTOPERATION
{
  DIOCOREPROTOCOL_HEADER_CONTENTOPERATION_UNKNOWN      = 0 ,
  DIOCOREPROTOCOL_HEADER_CONTENTOPERATION_COMMAND          ,
  DIOCOREPROTOCOL_HEADER_CONTENTOPERATION_UPDATE                
  
};


#define DIOCOREPROTOCOL_HEADER_CONTENTOPERATION_STRING_UNKNOWN      __L("unknown")
#define DIOCOREPROTOCOL_HEADER_CONTENTOPERATION_STRING_COMMAND      __L("command")
#define DIOCOREPROTOCOL_HEADER_CONTENTOPERATION_STRING_UPDATE       __L("update")


#define DIOCOREPROTOCOL_HEADER_MAGIC_ID          0x47454E31  // GEN1
#define DIOCOREPROTOCOL_HEADER_SIZE_ID           (sizeof(XDWORD)+sizeof(XWORD)*2+sizeof(XDWORD))

#pragma endregion


/*---- CLASS ---------------------------------------------------------c------------------------------------------------*/
#pragma region CLASS


class COMPRESSMANAGER;
class COMPRESSBASE;    	


class DIOCOREPROTOCOL_HEADER : public XSERIALIZABLE
{
  public:
                                              DIOCOREPROTOCOL_HEADER        ();
    virtual                                  ~DIOCOREPROTOCOL_HEADER        ();
 
    XUUID*                                    GetIDMachine                  ();
    XUUID*                                    GetIDConnection               ();
    XUUID*                                    GetIDMessage                  ();

    DIOCOREPROTOCOL_HEADER_MESSAGETYPE        GetMessageType                (); 
    void                                      SetMessageType                (DIOCOREPROTOCOL_HEADER_MESSAGETYPE message_type); 
    bool                                      GetMessageTypeToString        (XSTRING& message_typestr); 
    bool                                      GetMessageTypeFromString      (XSTRING* message_typestr, DIOCOREPROTOCOL_HEADER_MESSAGETYPE& message_type);

    XSTRING*                                  GetMessageParam               (); 
    
    XDATETIME*                                GetDateTimeSend               ();

    DIOCOREPROTOCOL_HEADER_CONTENTTYPE        GetContentType                (); 
    void                                      SetContentType                (DIOCOREPROTOCOL_HEADER_CONTENTTYPE content_type); 
    bool                                      GetContentTypeToString        (XSTRING& content_typestr); 
    bool                                      GetContentTypeFromString      (XSTRING* content_typestr, DIOCOREPROTOCOL_HEADER_CONTENTTYPE& content_type);

    DIOCOREPROTOCOL_HEADER_CONTENTOPERATION   GetContentOperation           ();
    void                                      SetContentOperation           (DIOCOREPROTOCOL_HEADER_CONTENTOPERATION content_operation);
    bool                                      GetContentOperationToString   (XSTRING& content_operationstr); 
    bool                                      GetContentOperationFromString (XSTRING* content_operationstr, DIOCOREPROTOCOL_HEADER_CONTENTOPERATION& content_operation);

    XDWORD                                    GetBlockIndex                 ();
    void                                      SetBlockIndex                 (XDWORD block_index);

    XDWORD                                    GetBlockAmount                ();
    void                                      SetBlockAmount                (XDWORD block_amount);

    XDWORD                                    GetContentSize                ();        
    void                                      SetContentSize                (XDWORD content_size);        

    XDWORD                                    GetContentCompressSize        ();        
    void                                      SetContentCompressSize        (XDWORD content_compresssize);        

    XDWORD                                    GetContentCRC32               ();        
    void                                      SetContentCRC32               (XDWORD content_CRC32);        

    XFILEJSON*                                GetSerializationXFileJSON     ();      
    XSERIALIZATIONMETHOD*                     GetSerializationMethod        ();

    bool                                      CopyFrom                      (DIOCOREPROTOCOL_HEADER* header);    
    bool                                      CopyTo                        (DIOCOREPROTOCOL_HEADER* header);    
    bool                                      Compare                       (DIOCOREPROTOCOL_HEADER* header);   

    bool                                      Serialize                     ();    
    bool                                      Deserialize                   ();  
   
  private:

    void                                      Clean                         ();

    XUUID                                     ID_machine;
    XUUID                                     ID_connection;
    XUUID                                     ID_message;
    DIOCOREPROTOCOL_HEADER_MESSAGETYPE        message_type;
    XSTRING                                   message_param;
    XDATETIME*                                datetime_send;
    DIOCOREPROTOCOL_HEADER_CONTENTTYPE        content_type; 
    DIOCOREPROTOCOL_HEADER_CONTENTOPERATION   content_operation;
    XDWORD                                    block_index;
    XDWORD                                    block_amount;
    XDWORD                                    content_size;
    XDWORD                                    content_compresssize;          
    XDWORD                                    content_CRC32;          

    XFILEJSON                                 xfileJSON;      
    XSERIALIZATIONMETHOD*                     serializationmethod;
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif


