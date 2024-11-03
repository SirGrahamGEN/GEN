/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOCoreProtocol_Header.cpp
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIOCoreProtocol_Header.h"

#include "XFactory.h"
#include "XString.h"
#include "XDateTime.h"

#include "HashCRC32.h"

#include "CompressManager.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_DIOCOREPROTOCOL_HEADER


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_HEADER::DIOCOREPROTOCOL_HEADER()
* @brief      Constructor
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_HEADER::DIOCOREPROTOCOL_HEADER()
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
* @fn         DIOCOREPROTOCOL_HEADER::~DIOCOREPROTOCOL_HEADER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_HEADER::~DIOCOREPROTOCOL_HEADER()
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
* @fn         XUUID* DIOCOREPROTOCOL_HEADER::GetIDMessage()
* @brief      GetIDMessage
* @ingroup    DATAIO
* 
* @return     XUUID* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XUUID* DIOCOREPROTOCOL_HEADER::GetIDMessage()
{
  return &ID_message;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XUUID* DIOCOREPROTOCOL_HEADER::GetIDMachine()
* @brief      GetIDMachine
* @ingroup    DATAIO
* 
* @return     XUUID* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XUUID* DIOCOREPROTOCOL_HEADER::GetIDMachine()
{
  return &ID_machine;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_HEADER_MESSAGETYPE DIOCOREPROTOCOL_HEADER::GetMessageType()
* @brief      GetMessageType
* @ingroup    DATAIO
* 
* @return     DIOCOREPROTOCOL_HEADER_MESSAGETYPE : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_HEADER_MESSAGETYPE DIOCOREPROTOCOL_HEADER::GetMessageType()
{
  return message_type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_HEADER::SetMessageType(DIOCOREPROTOCOL_HEADER_MESSAGETYPE message_type)
* @brief      SetMessageType
* @ingroup    DATAIO
* 
* @param[in]  message_type : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_HEADER::SetMessageType(DIOCOREPROTOCOL_HEADER_MESSAGETYPE message_type)
{
  this->message_type = message_type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_HEADER::GetMessageTypeToString(XSTRING& message_typestr)
* @brief      GetMessageTypeToString
* @ingroup    DATAIO
* 
* @param[in]  message_typestr : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_HEADER::GetMessageTypeToString(XSTRING& message_typestr)
{
  message_typestr.Empty();

  switch(message_type)
    {
      case DIOCOREPROTOCOL_HEADER_MESSAGETYPE_UNKNOWN  : message_typestr = DIOCOREPROTOCOL_HEADER_MESSAGETYPE_STRING_UNKNOWN;  break;
      case DIOCOREPROTOCOL_HEADER_MESSAGETYPE_REQUEST  : message_typestr = DIOCOREPROTOCOL_HEADER_MESSAGETYPE_STRING_REQUEST;  break;
      case DIOCOREPROTOCOL_HEADER_MESSAGETYPE_RESPONSE : message_typestr = DIOCOREPROTOCOL_HEADER_MESSAGETYPE_STRING_RESPONSE; break;      
    }

  return message_typestr.IsEmpty()?false:true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_HEADER::GetMessageTypeFromString(XSTRING* message_typestr, DIOCOREPROTOCOL_HEADER_MESSAGETYPE& message_type)
* @brief      GetMessageTypeFromString
* @ingroup    DATAIO
* 
* @param[in]  message_typestr : 
* @param[in]  message_type : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_HEADER::GetMessageTypeFromString(XSTRING* message_typestr, DIOCOREPROTOCOL_HEADER_MESSAGETYPE& message_type)
{
  if(!message_typestr)
    {
      return false;
    }

  message_type = DIOCOREPROTOCOL_HEADER_MESSAGETYPE_UNKNOWN;

  if(!message_typestr->Compare(DIOCOREPROTOCOL_HEADER_MESSAGETYPE_STRING_UNKNOWN))
    {
      message_type = DIOCOREPROTOCOL_HEADER_MESSAGETYPE_UNKNOWN;
    }

  if(!message_typestr->Compare(DIOCOREPROTOCOL_HEADER_MESSAGETYPE_STRING_REQUEST))
    {
      message_type = DIOCOREPROTOCOL_HEADER_MESSAGETYPE_REQUEST;
    }

  if(!message_typestr->Compare(DIOCOREPROTOCOL_HEADER_MESSAGETYPE_STRING_RESPONSE))
    {
      message_type = DIOCOREPROTOCOL_HEADER_MESSAGETYPE_RESPONSE;
    }

  return message_type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* DIOCOREPROTOCOL_HEADER::GetMessageParam()
* @brief      GetMessageParam
* @ingroup    DATAIO
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOCOREPROTOCOL_HEADER::GetMessageParam()
{
  return &message_param;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDATETIME* DIOCOREPROTOCOL_HEADER::GetDateTimeSend()
* @brief      GetDateTimeSend
* @ingroup    DATAIO
* 
* @return     XDATETIME* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDATETIME* DIOCOREPROTOCOL_HEADER::GetDateTimeSend()
{
  return datetime_send;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_HEADER_CONTENTTYPE DIOCOREPROTOCOL_HEADER::GetContentType()
* @brief      GetContentType
* @ingroup    DATAIO
* 
* @return     DIOCOREPROTOCOL_HEADER_CONTENTTYPE : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_HEADER_CONTENTTYPE DIOCOREPROTOCOL_HEADER::GetContentType()
{
  return content_type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_HEADER::SetContentType(DIOCOREPROTOCOL_HEADER_CONTENTTYPE contenttype)
* @brief      SetContentType
* @ingroup    DATAIO
* 
* @param[in]  contenttype : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_HEADER::SetContentType(DIOCOREPROTOCOL_HEADER_CONTENTTYPE content_type)
{
  this->content_type = content_type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_HEADER::GetContentTypeToString(XSTRING& content_typestr)
* @brief      GetContentTypeToString
* @ingroup    DATAIO
* 
* @param[in]  contenttypestr : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_HEADER::GetContentTypeToString(XSTRING& content_typestr)
{
  content_typestr.Empty();

  switch(content_type)
    {
      case DIOCOREPROTOCOL_HEADER_CONTENTTYPE_UNKNOWN  : content_typestr = DIOCOREPROTOCOL_HEADER_CONTENTTYPE_STRING_UNKNOWN;  break;
      case DIOCOREPROTOCOL_HEADER_CONTENTTYPE_BINARY   : content_typestr = DIOCOREPROTOCOL_HEADER_CONTENTTYPE_STRING_BINARY;   break;
      case DIOCOREPROTOCOL_HEADER_CONTENTTYPE_TEXT     : content_typestr = DIOCOREPROTOCOL_HEADER_CONTENTTYPE_STRING_TEXT;     break;
      case DIOCOREPROTOCOL_HEADER_CONTENTTYPE_JSON     : content_typestr = DIOCOREPROTOCOL_HEADER_CONTENTTYPE_STRING_JSON;     break;
    }

  return content_typestr.IsEmpty()?false:true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_HEADER::GetContentTypeFromString(XSTRING* content_typestr, DIOCOREPROTOCOL_HEADER_CONTENTTYPE& content_type)
* @brief      GetContentTypeFromString
* @ingroup    DATAIO
* 
* @param[in]  content_typestr : 
* @param[in]  content_type : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_HEADER::GetContentTypeFromString(XSTRING* content_typestr, DIOCOREPROTOCOL_HEADER_CONTENTTYPE& content_type)
{
  if(!content_typestr)
    {
      return false;
    }

  content_type = DIOCOREPROTOCOL_HEADER_CONTENTTYPE_UNKNOWN;

  if(!content_typestr->Compare(DIOCOREPROTOCOL_HEADER_CONTENTTYPE_STRING_UNKNOWN))
    {
      content_type = DIOCOREPROTOCOL_HEADER_CONTENTTYPE_UNKNOWN;
    }

  if(!content_typestr->Compare(DIOCOREPROTOCOL_HEADER_CONTENTTYPE_STRING_BINARY))
    {
      content_type = DIOCOREPROTOCOL_HEADER_CONTENTTYPE_BINARY;
    }

  if(!content_typestr->Compare(DIOCOREPROTOCOL_HEADER_CONTENTTYPE_STRING_TEXT))
    {
      content_type = DIOCOREPROTOCOL_HEADER_CONTENTTYPE_TEXT;
    }

  if(!content_typestr->Compare(DIOCOREPROTOCOL_HEADER_CONTENTTYPE_STRING_JSON))
    {
      content_type = DIOCOREPROTOCOL_HEADER_CONTENTTYPE_JSON;
    }

  return content_type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_HEADER_CONTENTOPERATION DIOCOREPROTOCOL_HEADER::GetContentOperation()
* @brief      GetContentOperation
* @ingroup    DATAIO
* 
* @return     DIOCOREPROTOCOL_HEADER_CONTENTOPERATION : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_HEADER_CONTENTOPERATION DIOCOREPROTOCOL_HEADER::GetContentOperation()
{
  return content_operation;
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_HEADER::SetContentOperation(DIOCOREPROTOCOL_HEADER_CONTENTOPERATION content_operation)
* @brief      SetContentOperation
* @ingroup    DATAIO
* 
* @param[in]  content_operation : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_HEADER::SetContentOperation(DIOCOREPROTOCOL_HEADER_CONTENTOPERATION content_operation)
{
  this->content_operation = content_operation;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_HEADER::GetContentOperationToString(XSTRING& content_operationstr)
* @brief      GetContentOperationToString
* @ingroup    DATAIO
* 
* @param[in]  content_operationstr : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_HEADER::GetContentOperationToString(XSTRING& content_operationstr)
{
  content_operationstr.Empty();

  switch(content_operation)
    {
      case DIOCOREPROTOCOL_HEADER_CONTENTOPERATION_UNKNOWN  : content_operationstr = DIOCOREPROTOCOL_HEADER_CONTENTOPERATION_STRING_UNKNOWN;  break;
      case DIOCOREPROTOCOL_HEADER_CONTENTOPERATION_COMMAND  : content_operationstr = DIOCOREPROTOCOL_HEADER_CONTENTOPERATION_STRING_COMMAND;  break;
      case DIOCOREPROTOCOL_HEADER_CONTENTOPERATION_UPDATE   : content_operationstr = DIOCOREPROTOCOL_HEADER_CONTENTOPERATION_STRING_UPDATE;   break;      
    }

  return content_operationstr.IsEmpty()?false:true;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_HEADER::GetContentOperationFromString (XSTRING* content_operationstr, DIOCOREPROTOCOL_HEADER_CONTENTOPERATION& content_operation)
* @brief      GetContentOperationFromString
* @ingroup    DATAIO
* 
* @param[in]  content_operationstr : 
* @param[in]  content_operation : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_HEADER::GetContentOperationFromString(XSTRING* content_operationstr, DIOCOREPROTOCOL_HEADER_CONTENTOPERATION& content_operation)
{
  if(!content_operationstr)
    {
      return false;
    }

  content_operation = DIOCOREPROTOCOL_HEADER_CONTENTOPERATION_UNKNOWN;

  if(!content_operationstr->Compare(DIOCOREPROTOCOL_HEADER_CONTENTOPERATION_STRING_UNKNOWN))
    {
      content_operation = DIOCOREPROTOCOL_HEADER_CONTENTOPERATION_UNKNOWN;
    }

  if(!content_operationstr->Compare(DIOCOREPROTOCOL_HEADER_CONTENTOPERATION_STRING_COMMAND))
    {
      content_operation = DIOCOREPROTOCOL_HEADER_CONTENTOPERATION_COMMAND;
    }

  if(!content_operationstr->Compare(DIOCOREPROTOCOL_HEADER_CONTENTOPERATION_STRING_UPDATE))
    {
      content_operation = DIOCOREPROTOCOL_HEADER_CONTENTOPERATION_UPDATE;
    }

  return content_operation;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIOCOREPROTOCOL_HEADER::GetBlockIndex()
* @brief      GetBlockIndex
* @ingroup    DATAIO
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOCOREPROTOCOL_HEADER::GetBlockIndex()
{
  return block_index;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_HEADER::SetBlockIndex(XDWORD block_index)
* @brief      SetBlockIndex
* @ingroup    DATAIO
* 
* @param[in]  block_index : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_HEADER::SetBlockIndex(XDWORD block_index)
{
  this->block_index  = block_index;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIOCOREPROTOCOL_HEADER::GetBlockAmount()
* @brief      GetBlockAmount
* @ingroup    DATAIO
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOCOREPROTOCOL_HEADER::GetBlockAmount()
{
  return block_amount;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_HEADER::SetBlockAmount(XDWORD block_amount)
* @brief      SetBlockAmount
* @ingroup    DATAIO
* 
* @param[in]  block_amount : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_HEADER::SetBlockAmount(XDWORD block_amount)
{
  this->block_amount = block_amount;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIOCOREPROTOCOL_HEADER::GetContentSize()
* @brief      GetContentSize
* @ingroup    DATAIO
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOCOREPROTOCOL_HEADER::GetContentSize()
{
  return content_size;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_HEADER::SetContentSize(XDWORD content_size)
* @brief      SetContentSize
* @ingroup    DATAIO
* 
* @param[in]  content_size : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_HEADER::SetContentSize(XDWORD content_size)
{
  this->content_size = content_size;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIOCOREPROTOCOL_HEADER::GetContentCompressSize()
* @brief      GetContentCompressSize
* @ingroup    DATAIO
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOCOREPROTOCOL_HEADER::GetContentCompressSize()
{
  return content_compresssize;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_HEADER::SetContentCompressSize(XDWORD content_compresssize)
* @brief      SetContentCompressSize
* @ingroup    DATAIO
* 
* @param[in]  content_compresssize : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_HEADER::SetContentCompressSize(XDWORD content_compresssize)
{
  this->content_compresssize = content_compresssize;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIOCOREPROTOCOL_HEADER::GetContentCRC32()
* @brief      GetContentCRC32
* @ingroup    DATAIO
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOCOREPROTOCOL_HEADER::GetContentCRC32()
{
  return content_CRC32;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_HEADER::SetContentCRC32(XDWORD content_CRC32)
* @brief      SetContentCRC32
* @ingroup    DATAIO
* 
* @param[in]  contentCRC32 : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_HEADER::SetContentCRC32(XDWORD content_CRC32)
{
  this->content_CRC32 = content_CRC32;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XFILEJSON* DIOCOREPROTOCOL_HEADER::GetSerializationXFileJSON()
* @brief      GetSerializationXFileJSON
* @ingroup    DATAIO
* 
* @return     XFILEJSON* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XFILEJSON* DIOCOREPROTOCOL_HEADER::GetSerializationXFileJSON()
{
  return &xfileJSON;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSERIALIZATIONMETHOD* DIOCOREPROTOCOL_HEADER::GetSerializationMethod()
* @brief      GetSerializationMethod
* @ingroup    DATAIO
* 
* @return     XSERIALIZATIONMETHOD* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSERIALIZATIONMETHOD* DIOCOREPROTOCOL_HEADER::GetSerializationMethod()
{
  return serializationmethod;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_HEADER::CopyFrom(DIOCOREPROTOCOL_HEADER* header)
* @brief      CopyFrom
* @ingroup    DATAIO
* 
* @param[in]  header : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_HEADER::CopyFrom(DIOCOREPROTOCOL_HEADER* header)
{
  if(!header)
    {
      return false;
    }
  
  ID_message.CopyFrom((*header->GetIDMessage()));
  ID_machine.CopyFrom((*header->GetIDMachine()));

  message_type          = header->GetMessageType();
  message_param         = header->GetMessageParam()->Get();  

  datetime_send->CopyFrom(header->GetDateTimeSend());
    
  content_type          = header->GetContentType(); 
  content_operation     = header->GetContentOperation();

  block_index           = header->GetBlockIndex();
  block_amount          = header->GetBlockAmount();
  content_size          = header->GetContentSize();
  content_compresssize  = header->GetContentCompressSize();          
  content_CRC32         = header->GetContentCRC32();          

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_HEADER::CopyTo(DIOCOREPROTOCOL_HEADER* header)
* @brief      CopyTo
* @ingroup    DATAIO
* 
* @param[in]  header : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_HEADER::CopyTo(DIOCOREPROTOCOL_HEADER* header)
{
  if(!header)
    {
      return false;
    }
  
  ID_message.CopyTo((*header->GetIDMessage()));  
  ID_machine.CopyTo((*header->GetIDMessage()));

  header->SetMessageType(message_type);
  header->GetMessageParam()->Set(message_param);  

  datetime_send->CopyTo(header->GetDateTimeSend());
    
  header->SetContentType(content_type); 
  header->SetContentOperation(content_operation);

  header->SetBlockIndex(block_index);
  header->SetBlockAmount(block_amount);
  header->SetContentSize(content_size);
  header->SetContentCompressSize(content_compresssize);          
  header->SetContentCRC32(content_CRC32);            

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_HEADER::Compare(DIOCOREPROTOCOL_HEADER* header)
* @brief      Compare
* @ingroup    DATAIO
* 
* @param[in]  header : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_HEADER::Compare(DIOCOREPROTOCOL_HEADER* header)
{
  if(!header)
    {
      return false;
    }

  if(!ID_message.CopyTo((*header->GetIDMessage())))
    {
      return false;
    }

  if(!ID_machine.CopyTo((*header->GetIDMachine())))
    {
      return false;
    }

  if(message_type != header->GetMessageType())
    {
      return false;
    }

  if(message_param.Compare(header->GetMessageParam()->Get()))
    {
      return false;
    }

  if(!datetime_send->Compare((*header->GetDateTimeSend())))
    {
      return false;
    }
    
  if(content_type != header->GetContentType())
    {
      return false;
    }

  if(content_operation != header->GetContentOperation())
    {
      return false;
    }

  if(block_index != header->GetBlockIndex())
    {
      return false;
    }

  if(block_amount != header->GetBlockAmount())
    {
      return false;
    }

  if(content_size != header->GetContentSize())
    {
      return false;
    }

  if(content_compresssize != header->GetContentCompressSize())
    {
      return false;
    }

  if(content_CRC32 != header->GetContentCRC32())   
    {
      return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_HEADER::Serialize()
* @brief      Serialize
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_HEADER::Serialize()
{
  XSTRING   string; 
  XVARIANT  data;

  ID_message.GetToString(string);
  Primitive_Add<XSTRING*>(&string, __L("ID_message"));

  ID_machine.GetToString(string);
  Primitive_Add<XSTRING*>(&string, __L("ID_machine"));

  #ifdef DIOCOREPROTOCOL_HEADER_HUMANFORMAT_ACTIVE
  GetMessageTypeToString(string);  
  Primitive_Add<XSTRING*>(&string, __L("message_type"));
  #else
  Primitive_Add<int>(message_type, __L("message_type"));
  #endif
  
  Primitive_Add<XSTRING*>(&message_param, __L("message_param"));

  datetime_send->GetDateTimeToStringISO8601(XDATETIME_FORMAT_ISO8601_STANDARD | XDATETIME_FORMAT_TIMEWITHMILLISECONDS, string);
  Primitive_Add<XSTRING*>(&string, __L("datetime_send"));

  #ifdef DIOCOREPROTOCOL_HEADER_HUMANFORMAT_ACTIVE
  GetContentTypeToString(string);  
  Primitive_Add<XSTRING*>(&string, __L("content_type"));
  #else
  Primitive_Add<int>(content_type, __L("content_type"));
  #endif

  #ifdef DIOCOREPROTOCOL_HEADER_HUMANFORMAT_ACTIVE
  GetContentOperationToString(string);  
  Primitive_Add<XSTRING*>(&string, __L("content_operation"));
  #else
  Primitive_Add<int>(content_operation, __L("content_operation"));
  #endif

  Primitive_Add<XDWORD>(block_index, __L("block_index"));

  Primitive_Add<XDWORD>(block_amount, __L("block_amount"));
      
  Primitive_Add<XDWORD>(content_size, __L("content_size"));

  Primitive_Add<XDWORD>(content_compresssize, __L("content_compresssize"));
   
  string.Format(__L("%08X"), content_CRC32);
  Primitive_Add<XSTRING*>(&string, __L("content_CRC32"));

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_HEADER::Deserialize()
* @brief      Deserialize
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_HEADER::Deserialize()
{
  XSTRING string;

  string.Empty();
  Primitive_Extract<XSTRING&>(string, __L("ID_message"));
  ID_message.SetFromString(string);

  string.Empty();
  Primitive_Extract<XSTRING&>(string, __L("ID_machine"));
  ID_machine.SetFromString(string);

  #ifdef DIOCOREPROTOCOL_HEADER_HUMANFORMAT_ACTIVE
  Primitive_Extract<XSTRING&>(string, __L("message_type"));
  GetMessageTypeFromString(&string, message_type);  
  #else
  Primitive_Extract<int&>((int&)message_type, __L("message_type"));
  #endif

  Primitive_Extract<XSTRING&>(message_param, __L("message_param"));

  string.Empty();
  Primitive_Extract<XSTRING&>(string, __L("datetime_send"));
  datetime_send->GetDateTimeFromStringISO8601(string, XDATETIME_FORMAT_ISO8601_STANDARD | XDATETIME_FORMAT_TIMEWITHMILLISECONDS);
  
  #ifdef DIOCOREPROTOCOL_HEADER_HUMANFORMAT_ACTIVE
  Primitive_Extract<XSTRING&>(string, __L("content_type"));
  GetContentTypeFromString(&string, content_type); 
  #else
  Primitive_Extract<int&>((int&)content_type, __L("content_type"));
  #endif 

  #ifdef DIOCOREPROTOCOL_HEADER_HUMANFORMAT_ACTIVE
  Primitive_Extract<XSTRING&>(string, __L("content_operation"));
  GetContentOperationFromString(&string, content_operation); 
  #else
  Primitive_Extract<int&>((int&)content_operation, __L("content_operation"));
  #endif 

  Primitive_Extract<XDWORD&>(block_index, __L("block_index"));

  Primitive_Extract<XDWORD&>(block_amount, __L("block_amount"));

  Primitive_Extract<XDWORD&>(content_size, __L("content_size"));
         
  Primitive_Extract<XDWORD&>(content_compresssize, __L("content_compresssize"));
  
  string.Empty();
  Primitive_Extract<XSTRING&>(string, __L("content_CRC32"));
  string.UnFormat(__L("%08X"), &content_CRC32);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_HEADER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_HEADER::Clean()
{ 
  message_type          = DIOCOREPROTOCOL_HEADER_MESSAGETYPE_UNKNOWN;  
  datetime_send         = NULL;
  content_type          = DIOCOREPROTOCOL_HEADER_CONTENTTYPE_UNKNOWN; 
  content_operation     = DIOCOREPROTOCOL_HEADER_CONTENTOPERATION_UNKNOWN; 
  block_index           = 1;
  block_amount          = 1;
  content_size          = 0;
  content_compresssize  = 0;          
  content_CRC32         = 0;       
}

    
#pragma endregion


