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


#include "XUUID.h"
#include "XFileJSON.h"
#include "XSerializable.h"
#include "XSerializationMethod.h"

#include "DIOStream.h"


#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


enum DIOCOREPROTOCOLHEADER_CONTENTTYPE
{
  DIOCOREPROTOCOLHEADER_CONTENTTYPE_UNKNOWN           = 0 ,
  DIOCOREPROTOCOLHEADER_CONTENTTYPE_BINARY                ,
  DIOCOREPROTOCOLHEADER_CONTENTTYPE_TEXT                  ,
  DIOCOREPROTOCOLHEADER_CONTENTTYPE_JSON                  ,  
};


#define DIOCOREPROTOCOLHEADER_CONTENTTYPE_STRING_UNKNOWN    __L("unknown")
#define DIOCOREPROTOCOLHEADER_CONTENTTYPE_STRING_BINARY     __L("binary")
#define DIOCOREPROTOCOLHEADER_CONTENTTYPE_STRING_TEXT       __L("text")
#define DIOCOREPROTOCOLHEADER_CONTENTTYPE_STRING_JSON       __L("json")


#pragma endregion


/*---- CLASS ---------------------------------------------------------c------------------------------------------------*/
#pragma region CLASS


class DIOSTREAM;

class DIOCOREPROTOCOLHEADER : public XSERIALIZABLE
{
  public:
                                          DIOCOREPROTOCOLHEADER       ();
    virtual                              ~DIOCOREPROTOCOLHEADER       ();
 
    XUUID*                                GetIDMachine                ();
    XUUID*                                GetIDConnection             ();
    XUUID*                                GetIDMessage                ();
    XDATETIME*                            GetDateTimeSend             ();

    DIOCOREPROTOCOLHEADER_CONTENTTYPE     GetContentType              (); 
    void                                  SetContentType              (DIOCOREPROTOCOLHEADER_CONTENTTYPE contenttype); 
    bool                                  GetContentTypeToString      (XSTRING& contenttypestr); 
    bool                                  GetContentTypeFromString    (XSTRING* contenttypestr, DIOCOREPROTOCOLHEADER_CONTENTTYPE& contenttype);

    XDWORD                                GetContentSize              ();        
    void                                  SetContentSize              (XDWORD contentsize);        

    XDWORD                                GetContentCRC32             ();        
    void                                  SetContentCRC32             (XDWORD contentCRC32);        

    XFILEJSON*                            GetSerializationXFileJSON   ();      
    XSERIALIZATIONMETHOD*                 GetSerializationMethod      ();

    bool                                  Serialize                   ();    
    bool                                  Deserialize                 ();  

  private:

    void                                  Clean                       ();

    XUUID                                 IDmachine;
    XUUID                                 IDconnection;
    XUUID                                 IDmessage;
    XDATETIME*                            datetimesend;
    DIOCOREPROTOCOLHEADER_CONTENTTYPE     contenttype; 
    XDWORD                                contentsize;          
    XDWORD                                contentCRC32;          

    XFILEJSON                             xfileJSON;      
    XSERIALIZATIONMETHOD*                 serializationmethod;
};


class DIOCOREPROTOCOL
{
  public:

                                          DIOCOREPROTOCOL             ();
                                          DIOCOREPROTOCOL             (DIOSTREAM* diostream);
    virtual                              ~DIOCOREPROTOCOL             ();

    bool                                  Ini                         ();
    bool                                  End                         ();

    
    bool                                  SendMsg                     (XUUID* IDmachine, XUUID* IDconnection, XBUFFER& content);
    bool                                  SendMsg                     (XUUID* IDmachine, XUUID* IDconnection, XSTRING& content);
    bool                                  SendMsg                     (XUUID* IDmachine, XUUID* IDconnection, XFILEJSON& content);

    DIOCOREPROTOCOLHEADER*                CreateHeader                (XUUID* IDmachine, XUUID* IDconnection, XBUFFER& content);
    DIOCOREPROTOCOLHEADER*                CreateHeader                (XUUID* IDmachine, XUUID* IDconnection, XSTRING& content);
    DIOCOREPROTOCOLHEADER*                CreateHeader                (XUUID* IDmachine, XUUID* IDconnection, XFILEJSON& content);
 
  private:

    bool                                  GenerateHeaderToSend        (DIOCOREPROTOCOLHEADER* header, XBUFFER& datasend);
    DIOCOREPROTOCOLHEADER*                CreateHeader                (XUUID* IDmachine, XUUID* IDconnection);

    void                                  Clean                       ();

    DIOSTREAM*                            diostream;   
    bool                                  initialization; 
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif


