/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOCoreProtocol.cpp
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIOCoreProtocol.h"

#include "XFactory.h"
#include "XString.h"
#include "XDateTime.h"

#include "HashCRC32.h"

#include "DIOStream.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_DIOCOREPROTOCOLHEADER


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOLHEADER::DIOCOREPROTOCOLHEADER()
* @brief      Constructor
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOLHEADER::DIOCOREPROTOCOLHEADER()
{
  Clean();

  serializationmethod = XSERIALIZABLE::CreateInstance(xfileJSON);
  if(serializationmethod)
    {
      SetSerializationMethod(serializationmethod);
    }

  datetime_send = GEN_XFACTORY.CreateDateTime();
  if(datetime_send)
    {
      datetime_send->Read();
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOLHEADER::~DIOCOREPROTOCOLHEADER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOLHEADER::~DIOCOREPROTOCOLHEADER()
{
  if(serializationmethod)
    {
      delete serializationmethod;
    }

  if(datetime_send)
    {
      GEN_XFACTORY.DeleteDateTime(datetime_send);
    }

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XUUID* DIOCOREPROTOCOLHEADER::GetIDMachine()
* @brief      GetIDMachine
* @ingroup    DATAIO
* 
* @return     XUUID* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XUUID* DIOCOREPROTOCOLHEADER::GetIDMachine()
{
  return &ID_machine;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XUUID* DIOCOREPROTOCOLHEADER::GetIDConnection()
* @brief      GetIDConnection
* @ingroup    DATAIO
* 
* @return     XUUID* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XUUID* DIOCOREPROTOCOLHEADER::GetIDConnection()
{
  return &ID_connection;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XUUID* DIOCOREPROTOCOLHEADER::GetIDMessage()
* @brief      GetIDMessage
* @ingroup    DATAIO
* 
* @return     XUUID* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XUUID* DIOCOREPROTOCOLHEADER::GetIDMessage()
{
  return &ID_message;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOLHEADER_MESSAGETYPE DIOCOREPROTOCOLHEADER::GetMessageType()
* @brief      GetMessageType
* @ingroup    DATAIO
* 
* @return     DIOCOREPROTOCOLHEADER_MESSAGETYPE : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOLHEADER_MESSAGETYPE DIOCOREPROTOCOLHEADER::GetMessageType()
{
  return message_type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOLHEADER::SetMessageType(DIOCOREPROTOCOLHEADER_MESSAGETYPE message_type)
* @brief      SetMessageType
* @ingroup    DATAIO
* 
* @param[in]  message_type : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOLHEADER::SetMessageType(DIOCOREPROTOCOLHEADER_MESSAGETYPE message_type)
{
  this->message_type = message_type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOLHEADER::GetMessageTypeToString(XSTRING& message_typestr)
* @brief      GetMessageTypeToString
* @ingroup    DATAIO
* 
* @param[in]  message_typestr : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOLHEADER::GetMessageTypeToString(XSTRING& message_typestr)
{
  message_typestr.Empty();

  switch(message_type)
    {
      case DIOCOREPROTOCOLHEADER_MESSAGETYPE_UNKNOWN  : message_typestr = DIOCOREPROTOCOLHEADER_MESSAGETYPE_STRING_UNKNOWN;  break;
      case DIOCOREPROTOCOLHEADER_MESSAGETYPE_ASK      : message_typestr = DIOCOREPROTOCOLHEADER_MESSAGETYPE_STRING_ASK;      break;
      case DIOCOREPROTOCOLHEADER_MESSAGETYPE_RESPONSE : message_typestr = DIOCOREPROTOCOLHEADER_MESSAGETYPE_STRING_RESPONSE; break;      
    }

  return message_typestr.IsEmpty()?false:true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOLHEADER::GetMessageTypeFromString(XSTRING* message_typestr, DIOCOREPROTOCOLHEADER_MESSAGETYPE& message_type)
* @brief      GetMessageTypeFromString
* @ingroup    DATAIO
* 
* @param[in]  message_typestr : 
* @param[in]  message_type : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOLHEADER::GetMessageTypeFromString(XSTRING* message_typestr, DIOCOREPROTOCOLHEADER_MESSAGETYPE& message_type)
{
  if(!message_typestr)
    {
      return false;
    }

  message_type = DIOCOREPROTOCOLHEADER_MESSAGETYPE_UNKNOWN;

  if(!message_typestr->Compare(DIOCOREPROTOCOLHEADER_MESSAGETYPE_STRING_UNKNOWN))
    {
      message_type = DIOCOREPROTOCOLHEADER_MESSAGETYPE_UNKNOWN;
    }

  if(!message_typestr->Compare(DIOCOREPROTOCOLHEADER_MESSAGETYPE_STRING_ASK))
    {
      message_type = DIOCOREPROTOCOLHEADER_MESSAGETYPE_ASK;
    }

  if(!message_typestr->Compare(DIOCOREPROTOCOLHEADER_MESSAGETYPE_STRING_RESPONSE))
    {
      message_type = DIOCOREPROTOCOLHEADER_MESSAGETYPE_RESPONSE;
    }

  return message_type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDATETIME* DIOCOREPROTOCOLHEADER::GetDateTimeSend()
* @brief      GetDateTimeSend
* @ingroup    DATAIO
* 
* @return     XDATETIME* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDATETIME* DIOCOREPROTOCOLHEADER::GetDateTimeSend()
{
  return datetime_send;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOLHEADER_CONTENTTYPE DIOCOREPROTOCOLHEADER::GetContentType()
* @brief      GetContentType
* @ingroup    DATAIO
* 
* @return     DIOCOREPROTOCOLHEADER_CONTENTTYPE : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOLHEADER_CONTENTTYPE DIOCOREPROTOCOLHEADER::GetContentType()
{
  return content_type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOLHEADER::SetContentType(DIOCOREPROTOCOLHEADER_CONTENTTYPE contenttype)
* @brief      SetContentType
* @ingroup    DATAIO
* 
* @param[in]  contenttype : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOLHEADER::SetContentType(DIOCOREPROTOCOLHEADER_CONTENTTYPE content_type)
{
  this->content_type = content_type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOLHEADER::GetContentTypeToString(XSTRING& content_typestr)
* @brief      GetContentTypeToString
* @ingroup    DATAIO
* 
* @param[in]  contenttypestr : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOLHEADER::GetContentTypeToString(XSTRING& content_typestr)
{
  content_typestr.Empty();

  switch(content_type)
    {
      case DIOCOREPROTOCOLHEADER_CONTENTTYPE_UNKNOWN  : content_typestr = DIOCOREPROTOCOLHEADER_CONTENTTYPE_STRING_UNKNOWN;  break;
      case DIOCOREPROTOCOLHEADER_CONTENTTYPE_BINARY   : content_typestr = DIOCOREPROTOCOLHEADER_CONTENTTYPE_STRING_BINARY;   break;
      case DIOCOREPROTOCOLHEADER_CONTENTTYPE_TEXT     : content_typestr = DIOCOREPROTOCOLHEADER_CONTENTTYPE_STRING_TEXT;     break;
      case DIOCOREPROTOCOLHEADER_CONTENTTYPE_JSON     : content_typestr = DIOCOREPROTOCOLHEADER_CONTENTTYPE_STRING_JSON;     break;
    }

  return content_typestr.IsEmpty()?false:true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOLHEADER::GetContentTypeFromString(XSTRING* content_typestr, DIOCOREPROTOCOLHEADER_CONTENTTYPE& content_type)
* @brief      GetContentTypeFromString
* @ingroup    DATAIO
* 
* @param[in]  content_typestr : 
* @param[in]  content_type : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOLHEADER::GetContentTypeFromString(XSTRING* content_typestr, DIOCOREPROTOCOLHEADER_CONTENTTYPE& content_type)
{
  if(!content_typestr)
    {
      return false;
    }

  content_type = DIOCOREPROTOCOLHEADER_CONTENTTYPE_UNKNOWN;

  if(!content_typestr->Compare(DIOCOREPROTOCOLHEADER_CONTENTTYPE_STRING_UNKNOWN))
    {
      content_type = DIOCOREPROTOCOLHEADER_CONTENTTYPE_UNKNOWN;
    }

  if(!content_typestr->Compare(DIOCOREPROTOCOLHEADER_CONTENTTYPE_STRING_BINARY))
    {
      content_type = DIOCOREPROTOCOLHEADER_CONTENTTYPE_BINARY;
    }

  if(!content_typestr->Compare(DIOCOREPROTOCOLHEADER_CONTENTTYPE_STRING_TEXT))
    {
      content_type = DIOCOREPROTOCOLHEADER_CONTENTTYPE_TEXT;
    }

  if(!content_typestr->Compare(DIOCOREPROTOCOLHEADER_CONTENTTYPE_STRING_JSON))
    {
      content_type = DIOCOREPROTOCOLHEADER_CONTENTTYPE_JSON;
    }

  return content_type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOLHEADER_CONTENTOPERATION DIOCOREPROTOCOLHEADER::GetContentOperation()
* @brief      GetContentOperation
* @ingroup    DATAIO
* 
* @return     DIOCOREPROTOCOLHEADER_CONTENTOPERATION : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOLHEADER_CONTENTOPERATION DIOCOREPROTOCOLHEADER::GetContentOperation()
{
  return content_operation;
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOLHEADER::SetContentOperation(DIOCOREPROTOCOLHEADER_CONTENTOPERATION content_operation)
* @brief      SetContentOperation
* @ingroup    DATAIO
* 
* @param[in]  content_operation : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOLHEADER::SetContentOperation(DIOCOREPROTOCOLHEADER_CONTENTOPERATION content_operation)
{
  this->content_operation = content_operation;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOLHEADER::GetContentOperationToString(XSTRING& content_operationstr)
* @brief      GetContentOperationToString
* @ingroup    DATAIO
* 
* @param[in]  content_operationstr : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOLHEADER::GetContentOperationToString(XSTRING& content_operationstr)
{
  content_operationstr.Empty();

  switch(content_operation)
    {
      case DIOCOREPROTOCOLHEADER_CONTENTOPERATION_UNKNOWN  : content_operationstr = DIOCOREPROTOCOLHEADER_CONTENTOPERATION_STRING_UNKNOWN;  break;
      case DIOCOREPROTOCOLHEADER_CONTENTOPERATION_COMMAND  : content_operationstr = DIOCOREPROTOCOLHEADER_CONTENTOPERATION_STRING_COMMAND;  break;
      case DIOCOREPROTOCOLHEADER_CONTENTOPERATION_UPDATE   : content_operationstr = DIOCOREPROTOCOLHEADER_CONTENTOPERATION_STRING_UPDATE;   break;      
    }

  return content_operationstr.IsEmpty()?false:true;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOLHEADER::GetContentOperationFromString (XSTRING* content_operationstr, DIOCOREPROTOCOLHEADER_CONTENTOPERATION& content_operation)
* @brief      GetContentOperationFromString
* @ingroup    DATAIO
* 
* @param[in]  content_operationstr : 
* @param[in]  content_operation : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOLHEADER::GetContentOperationFromString (XSTRING* content_operationstr, DIOCOREPROTOCOLHEADER_CONTENTOPERATION& content_operation)
{
  if(!content_operationstr)
    {
      return false;
    }

  content_operation = DIOCOREPROTOCOLHEADER_CONTENTOPERATION_UNKNOWN;

  if(!content_operationstr->Compare(DIOCOREPROTOCOLHEADER_CONTENTOPERATION_STRING_UNKNOWN))
    {
      content_operation = DIOCOREPROTOCOLHEADER_CONTENTOPERATION_UNKNOWN;
    }

  if(!content_operationstr->Compare(DIOCOREPROTOCOLHEADER_CONTENTOPERATION_STRING_COMMAND))
    {
      content_operation = DIOCOREPROTOCOLHEADER_CONTENTOPERATION_COMMAND;
    }

  if(!content_operationstr->Compare(DIOCOREPROTOCOLHEADER_CONTENTOPERATION_STRING_UPDATE))
    {
      content_operation = DIOCOREPROTOCOLHEADER_CONTENTOPERATION_UPDATE;
    }

  return content_operation;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIOCOREPROTOCOLHEADER::GetContentSize()
* @brief      GetContentSize
* @ingroup    DATAIO
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOCOREPROTOCOLHEADER::GetContentSize()
{
  return content_size;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOLHEADER::SetContentSize(XDWORD content_size)
* @brief      SetContentSize
* @ingroup    DATAIO
* 
* @param[in]  content_size : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOLHEADER::SetContentSize(XDWORD content_size)
{
  this->content_size = content_size;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOLHEADER::GetContentIsCompress()
* @brief      GetContentIsCompress
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOLHEADER::GetContentIsCompress()
{
  return content_iscompress;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOLHEADER::SetContentIsCompress(bool content_iscompress)
* @brief      SetContentIsCompress
* @ingroup    DATAIO
* 
* @param[in]  contentiscompress : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOLHEADER::SetContentIsCompress(bool content_iscompress)
{
  this->content_iscompress = content_iscompress;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIOCOREPROTOCOLHEADER::GetContentCRC32()
* @brief      GetContentCRC32
* @ingroup    DATAIO
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOCOREPROTOCOLHEADER::GetContentCRC32()
{
  return content_CRC32;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOLHEADER::SetContentCRC32(XDWORD content_CRC32)
* @brief      SetContentCRC32
* @ingroup    DATAIO
* 
* @param[in]  contentCRC32 : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOLHEADER::SetContentCRC32(XDWORD content_CRC32)
{
  this->content_CRC32 = content_CRC32;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILEJSON* DIOCOREPROTOCOLHEADER::GetSerializationXFileJSON()
* @brief      GetSerializationXFileJSON
* @ingroup    DATAIO
* 
* @return     XFILEJSON* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XFILEJSON* DIOCOREPROTOCOLHEADER::GetSerializationXFileJSON()
{
  return &xfileJSON;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSERIALIZATIONMETHOD* DIOCOREPROTOCOLHEADER::GetSerializationMethod()
* @brief      GetSerializationMethod
* @ingroup    DATAIO
* 
* @return     XSERIALIZATIONMETHOD* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSERIALIZATIONMETHOD* DIOCOREPROTOCOLHEADER::GetSerializationMethod()
{
  return serializationmethod;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOLHEADER::Serialize()
* @brief      Serialize
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOLHEADER::Serialize()
{
  XSTRING   string; 
  XVARIANT  data;

  ID_machine.GetToString(string);
  Primitive_Add<XSTRING*>(&string, __L("ID_machine"));

  ID_connection.GetToString(string);
  Primitive_Add<XSTRING*>(&string, __L("ID_connection"));

  ID_message.GetToString(string);
  Primitive_Add<XSTRING*>(&string, __L("ID_message"));

  GetMessageTypeToString(string);  
  Primitive_Add<XSTRING*>(&string, __L("message_type"));

  datetime_send->GetDateTimeToStringISO8601(XDATETIME_FORMAT_ISO8601_STANDARD | XDATETIME_FORMAT_TIMEWITHMILLISECONDS, string);
  Primitive_Add<XSTRING*>(&string, __L("datetime_send"));

  GetContentTypeToString(string);  
  Primitive_Add<XSTRING*>(&string, __L("content_type"));

  GetContentOperationToString(string);  
  Primitive_Add<XSTRING*>(&string, __L("content_operation"));
    
  string.Format(__L("%d"), content_size);
  Primitive_Add<XSTRING*>(&string, __L("content_size"));

  string.ConvertFromBoolean(content_iscompress, (XSTRINGBOOLEANMODE_HUMAN | XSTRINGBOOLEANMODE_LOWERCASE));
  Primitive_Add<XSTRING*>(&string, __L("content_iscompress"));
   
  string.Format(__L("%08X"), content_CRC32);
  Primitive_Add<XSTRING*>(&string, __L("content_CRC32"));

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOLHEADER::Deserialize()
* @brief      Deserialize
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOLHEADER::Deserialize()
{
  XSTRING string;

  string.Empty();
  Primitive_Extract<XSTRING&>(string, __L("ID_machine"));
  ID_machine.SetFromString(string);

  string.Empty();
  Primitive_Extract<XSTRING&>(string, __L("ID_connection"));
  ID_connection.SetFromString(string);
  
  string.Empty();
  Primitive_Extract<XSTRING&>(string, __L("ID_message"));
  ID_message.SetFromString(string);

  Primitive_Extract<XSTRING&>(string, __L("message_type"));
  GetMessageTypeFromString(&string, message_type);  

  string.Empty();
  Primitive_Extract<XSTRING&>(string, __L("datetime_send"));
  datetime_send->GetDateTimeFromStringISO8601(string, XDATETIME_FORMAT_ISO8601_STANDARD | XDATETIME_FORMAT_TIMEWITHMILLISECONDS);
  
  Primitive_Extract<XSTRING&>(string, __L("content_type"));
  GetContentTypeFromString(&string, content_type);  

  Primitive_Extract<XSTRING&>(string, __L("content_operation"));
  GetContentOperationFromString(&string, content_operation);  

  string.Empty();
  Primitive_Extract<XSTRING&>(string, __L("content_size"));
  string.UnFormat(__L("%d"), &content_size);
         
  string.Empty();
  Primitive_Extract<XSTRING&>(string, __L("content_iscompress"));
  content_iscompress = string.ConvertToBoolean();

  string.Empty();
  Primitive_Extract<XSTRING&>(string, __L("content_CRC32"));
  string.UnFormat(__L("%08X"), &content_CRC32);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOLHEADER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOLHEADER::Clean()
{ 
  message_type        = DIOCOREPROTOCOLHEADER_MESSAGETYPE_UNKNOWN;  
  datetime_send       = NULL;
  content_type        = DIOCOREPROTOCOLHEADER_CONTENTTYPE_UNKNOWN; 
  content_operation   = DIOCOREPROTOCOLHEADER_CONTENTOPERATION_UNKNOWN; 
  content_size        = 0;
  content_iscompress  = false;          
  content_CRC32       = 0;       
}

    
#pragma endregion


#pragma region CLASS_DIOCOREPROTOCOL


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL::DIOCOREPROTOCOL()
* @brief      Constructor
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL::DIOCOREPROTOCOL()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL::DIOCOREPROTOCOL()
* @brief      Constructor
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL::DIOCOREPROTOCOL(DIOSTREAM* diostream)
{
  Clean();

  this->diostream = diostream;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL::~DIOCOREPROTOCOL()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL::~DIOCOREPROTOCOL()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL::Ini()
* @brief      Ini
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL::Ini()
{
  initialization = false;

  return initialization;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL::End()
* @brief      End
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL::End()
{  
  initialization = false;

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL::SendMsg(XBUFFER& content)
* @brief      SendMsg
* @ingroup    DATAIO
* 
* @param[in]  content : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL::SendMsg(XUUID* IDmachine, XUUID* IDconnection, XBUFFER& content)
{
  DIOCOREPROTOCOLHEADER*  header          = NULL;
  XFILEJSON*              headerxfileJSON = NULL;
  XSTRING                 headerstring;
  XBUFFER                 datasend;    
  bool                    status          = false;

  header = CreateHeader(IDmachine, IDconnection, content);
  if(!header)
    {      
      return false;
    }

  if(!GenerateHeaderToSend(header, datasend))
    {
      return false;
    }

  delete header;
           
  datasend.Add(content);

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Core Protocol] Send data Buffer:"));
  XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_BLUE, datasend);

  if(diostream)
    {
      status = diostream->Write(datasend);
    }
   
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL::SendMsg(XSTRING& content)
* @brief      SendMsg
* @ingroup    DATAIO
* 
* @param[in]  content : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL::SendMsg(XUUID* IDmachine, XUUID* IDconnection, XSTRING& content)
{
  DIOCOREPROTOCOLHEADER*  header          = NULL;
  XFILEJSON*              headerxfileJSON = NULL;
  XSTRING                 headerstring;
  XBUFFER                 contentbinary;
  XBUFFER                 datasend;    
  bool                    status          = false;

  header = CreateHeader(IDmachine, IDconnection, content);
  if(!header)
    {      
      return false;
    }
  
  if(!GenerateHeaderToSend(header, datasend))
    {
      return false;
    }

  delete header;
 
  content.ConvertToUTF8(contentbinary);         
  datasend.Add(contentbinary);

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Core Protocol] Send data string:"));
  XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_BLUE, datasend);

  if(diostream)
    {
      status = diostream->Write(datasend);
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL::SendMsg(XFILEJSON& content)
* @brief      SendMsg
* @ingroup    DATAIO
* 
* @param[in]  content : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL::SendMsg(XUUID* IDmachine, XUUID* IDconnection, XFILEJSON& content)
{
  DIOCOREPROTOCOLHEADER*  header          = NULL;
  XFILEJSON*              headerxfileJSON = NULL;
  XSTRING                 headerstring;  
  XSTRING                 contentstring;
  XBUFFER                 contentbinary;
  XBUFFER                 datasend;    
  bool                    status          = false;

  header = CreateHeader(IDmachine, IDconnection, content);
  if(!header)
    {      
      return false;
    }
    
  if(!GenerateHeaderToSend(header, datasend))
    {
      return false;
    }

  delete header;

  content.GetAllInOneLine(contentstring); 
  contentstring.ConvertToUTF8(contentbinary);
         
  datasend.Add(contentbinary);

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Core Protocol] Send data JSON:"));
  XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_BLUE, datasend);

  if(diostream)
    {
      status = diostream->Write(datasend);
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOLHEADER* DIOCOREPROTOCOL::CreateHeader(XUUID* IDmachine, XUUID* IDconnection, XBUFFER& content)
* @brief      CreateHeader
* @ingroup    DATAIO
* 
* @param[in]  IDmachine : 
* @param[in]  IDconnection : 
* @param[in]  content : 
* 
* @return     DIOCOREPROTOCOLHEADER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOLHEADER* DIOCOREPROTOCOL::CreateHeader(XUUID* IDmachine, XUUID* IDconnection, XBUFFER& content)
{
  DIOCOREPROTOCOLHEADER* header = CreateHeader(IDmachine, IDconnection);
  if(!header)
    {
      return NULL;
    }

  header->SetContentType(DIOCOREPROTOCOLHEADER_CONTENTTYPE_BINARY);
  header->SetContentSize(content.GetSize());   

  HASHCRC32 hashCRC32;

  hashCRC32.Do(content);  
  header->SetContentCRC32(hashCRC32.GetResultCRC32());

  return header;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOLHEADER* DIOCOREPROTOCOL::CreateHeader(XUUID* IDmachine, XUUID* IDconnection, XSTRING& content)
* @brief      CreateHeader
* @ingroup    DATAIO
* 
* @param[in]  IDmachine : 
* @param[in]  IDconnection : 
* @param[in]  content : 
* 
* @return     DIOCOREPROTOCOLHEADER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOLHEADER* DIOCOREPROTOCOL::CreateHeader(XUUID* IDmachine, XUUID* IDconnection, XSTRING& content)
{
  DIOCOREPROTOCOLHEADER* header = CreateHeader(IDmachine, IDconnection);
  if(!header)
    {
      return NULL;
    }  

  XBUFFER contentbinary;
  content.ConvertToUTF8(contentbinary);

  header->SetContentType(DIOCOREPROTOCOLHEADER_CONTENTTYPE_TEXT);
  header->SetContentSize(contentbinary.GetSize());   

  HASHCRC32 hashCRC32;

  hashCRC32.Do(contentbinary);  
  header->SetContentCRC32(hashCRC32.GetResultCRC32());

  return header;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOLHEADER* DIOCOREPROTOCOL::CreateHeader(XUUID* IDmachine, XUUID* IDconnection, XFILEJSON& content)
* @brief      CreateHeader
* @ingroup    DATAIO
* 
* @param[in]  IDmachine : 
* @param[in]  IDconnection : 
* @param[in]  content : 
* 
* @return     DIOCOREPROTOCOLHEADER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOLHEADER* DIOCOREPROTOCOL::CreateHeader(XUUID* IDmachine, XUUID* IDconnection, XFILEJSON& content)
{
  DIOCOREPROTOCOLHEADER* header = CreateHeader(IDmachine, IDconnection);
  if(!header)
    {
      return NULL;
    }  

  XSTRING contentstring;
  XBUFFER contentbinary;

  content.EncodeAllLines(false);  
  content.GetAllInOneLine(contentstring);

  contentstring.ConvertToUTF8(contentbinary);

  header->SetContentType(DIOCOREPROTOCOLHEADER_CONTENTTYPE_JSON);
  header->SetContentSize(contentbinary.GetSize());   

  HASHCRC32 hashCRC32;

  hashCRC32.Do(contentbinary);  
  header->SetContentCRC32(hashCRC32.GetResultCRC32());

  return header;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL::GenerateHeaderToSend(DIOCOREPROTOCOLHEADER* header, XBUFFER& datasend)
* @brief      GenerateHeaderToSend
* @ingroup    DATAIO
* 
* @param[in]  header : 
* @param[in]  datasend : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL::GenerateHeaderToSend(DIOCOREPROTOCOLHEADER* header, XBUFFER& datasend)
{
  XFILEJSON*  headerxfileJSON = NULL;
  XSTRING     headerstring;
  bool        status          = false;
  
  if(!header)
    {
      return false;
    }

  header->SetMessageType(DIOCOREPROTOCOLHEADER_MESSAGETYPE_ASK);

  headerxfileJSON = header->GetSerializationXFileJSON();
  if(!headerxfileJSON)
    {
      return false;
    }

  status = header->DoSerialize();
  if(status)
    {
      headerxfileJSON->EncodeAllLines(false);  
      headerxfileJSON->GetAllInOneLine(headerstring);

      headerstring.ConvertToUTF8(datasend);
    }

  return status;  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOLHEADER* DIOCOREPROTOCOL::CreateHeader(XUUID* IDmachine, XUUID* IDconnection)
* @brief      CreateHeader
* @ingroup    DATAIO
* 
* @param[in]  IDmachine : 
* @param[in]  IDconnection : 
* 
* @return     DIOCOREPROTOCOLHEADER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOLHEADER* DIOCOREPROTOCOL::CreateHeader(XUUID* IDmachine, XUUID* IDconnection)
{
  if(!IDmachine)
    {
      return NULL;
    }

  if(!IDconnection)
    {
      return NULL;
    }

  DIOCOREPROTOCOLHEADER* header = new DIOCOREPROTOCOLHEADER();
  if(!header)
    {
      return NULL;
    }
  
  header->GetIDMachine()->CopyFrom((*IDmachine));
  header->GetIDConnection()->CopyFrom((*IDconnection));
  header->GetIDMessage()->GenerateRandom();
  header->GetDateTimeSend()->Read();

  return header;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL::Clean()
{
  diostream       = NULL;
  initialization  = false;
}


#pragma endregion


