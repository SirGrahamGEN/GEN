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


#ifdef DIOCOREPROTOCOL_HUMANFORMAT_ACTIVE
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
#endif

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBYTE DIOCOREPROTOCOL_HEADER::GetMessagePriority()
* @brief      GetMessagePriority
* @ingroup    DATAIO
* 
* @return     XBYTE : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE DIOCOREPROTOCOL_HEADER::GetMessagePriority()
{
  return message_priority;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_HEADER::SetMessagePriority(XBYTE message_priority)
* @brief      SetMessagePriority
* @ingroup    DATAIO
* 
* @param[in]  message_priority : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_HEADER::SetMessagePriority(XBYTE message_priority)
{
  this->message_priority = message_priority;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_HEADER_OPERATION DIOCOREPROTOCOL_HEADER::GetOperation()
* @brief      GetOperation
* @ingroup    DATAIO
* 
* @return     DIOCOREPROTOCOL_HEADER_OPERATION : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_HEADER_OPERATION DIOCOREPROTOCOL_HEADER::GetOperation()
{
  return operation;
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_HEADER::SetOperation(DIOCOREPROTOCOL_HEADER_OPERATION operation)
* @brief      SetOperation
* @ingroup    DATAIO
* 
* @param[in]  operation : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_HEADER::SetOperation(DIOCOREPROTOCOL_HEADER_OPERATION operation)
{
  this->operation = operation;
}


#ifdef DIOCOREPROTOCOL_HUMANFORMAT_ACTIVE
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_HEADER::GetOperationToString(XSTRING& operationstr)
* @brief      GetOperationToString
* @ingroup    DATAIO
* 
* @param[in]  operationstr : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_HEADER::GetOperationToString(XSTRING& operationstr)
{
  operationstr.Empty();

  switch(operation)
    {
      case DIOCOREPROTOCOL_HEADER_OPERATION_UNKNOWN         : operationstr = DIOCOREPROTOCOL_HEADER_OPERATION_STRING_UNKNOWN;       break;
      case DIOCOREPROTOCOL_HEADER_OPERATION_AUTHENTICATE    : operationstr = DIOCOREPROTOCOL_HEADER_OPERATION_STRING_AUTHENTICATE;  break;       
      case DIOCOREPROTOCOL_HEADER_OPERATION_KEYEXCHANGE     : operationstr = DIOCOREPROTOCOL_HEADER_OPERATION_STRING_KEYEXCHANGE;   break;       
      case DIOCOREPROTOCOL_HEADER_OPERATION_COMMAND         : operationstr = DIOCOREPROTOCOL_HEADER_OPERATION_STRING_COMMAND;       break;
      case DIOCOREPROTOCOL_HEADER_OPERATION_UPDATE          : operationstr = DIOCOREPROTOCOL_HEADER_OPERATION_STRING_UPDATE;        break;      
    }

  return operationstr.IsEmpty()?false:true;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_HEADER::GetOperationFromString (XSTRING* operationstr, DIOCOREPROTOCOL_HEADER_OPERATION& operation)
* @brief      GetOperationFromString
* @ingroup    DATAIO
* 
* @param[in]  operationstr : 
* @param[in]  operation : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_HEADER::GetOperationFromString(XSTRING* operationstr, DIOCOREPROTOCOL_HEADER_OPERATION& operation)
{
  if(!operationstr)
    {
      return false;
    }

  operation = DIOCOREPROTOCOL_HEADER_OPERATION_UNKNOWN;

  if(!operationstr->Compare(DIOCOREPROTOCOL_HEADER_OPERATION_STRING_UNKNOWN))
    {
      operation = DIOCOREPROTOCOL_HEADER_OPERATION_UNKNOWN;
    }

  if(!operationstr->Compare(DIOCOREPROTOCOL_HEADER_OPERATION_STRING_AUTHENTICATE))
    {
      operation = DIOCOREPROTOCOL_HEADER_OPERATION_AUTHENTICATE;
    }

  if(!operationstr->Compare(DIOCOREPROTOCOL_HEADER_OPERATION_STRING_KEYEXCHANGE))
    {
      operation = DIOCOREPROTOCOL_HEADER_OPERATION_KEYEXCHANGE;
    }

  if(!operationstr->Compare(DIOCOREPROTOCOL_HEADER_OPERATION_STRING_COMMAND))
    {
      operation = DIOCOREPROTOCOL_HEADER_OPERATION_COMMAND;
    }

  if(!operationstr->Compare(DIOCOREPROTOCOL_HEADER_OPERATION_STRING_UPDATE))
    {
      operation = DIOCOREPROTOCOL_HEADER_OPERATION_UPDATE;
    }

  return operation;
}
#endif


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* DIOCOREPROTOCOL_HEADER::GetMessageParam()
* @brief      GetMessageParam
* @ingroup    DATAIO
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOCOREPROTOCOL_HEADER::GetOperationParam()
{
  return &operation_param;
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


#ifdef DIOCOREPROTOCOL_HUMANFORMAT_ACTIVE
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
#endif


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

  message_priority      = header->GetMessagePriority();

  operation             = header->GetOperation();
  operation_param       = header->GetOperationParam()->Get();  

  datetime_send->CopyFrom(header->GetDateTimeSend());
    
  content_type          = header->GetContentType(); 
 
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

  header->SetMessagePriority(message_priority);

  header->SetOperation(operation);
  header->GetOperationParam()->Set(operation_param);  

  datetime_send->CopyTo(header->GetDateTimeSend());
    
  header->SetContentType(content_type); 

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

  if(message_priority != header->GetMessagePriority())
    {
      return false;
    } 

  if(operation != header->GetOperation())
    {
      return false;
    }

  if(operation_param.Compare(header->GetOperationParam()->Get()))
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
  Primitive_Add<XSTRING*>(&string, DIOCOREPROTOCOL_HEADER_VAR_ID_MESSAGE);

  ID_machine.GetToString(string);
  Primitive_Add<XSTRING*>(&string, DIOCOREPROTOCOL_HEADER_VAR_ID_MACHINE);

  #ifdef DIOCOREPROTOCOL_HUMANFORMAT_ACTIVE           
    GetMessageTypeToString(string);  
    Primitive_Add<XSTRING*>(&string, DIOCOREPROTOCOL_HEADER_VAR_MESSAGE_TYPE);    
  #else    
    Primitive_Add<int>(message_type, DIOCOREPROTOCOL_HEADER_VAR_MESSAGE_TYPE);
  #endif
  
  Primitive_Add<XBYTE>(message_priority, DIOCOREPROTOCOL_HEADER_VAR_MESSAGE_PRIORITY);

  #ifdef DIOCOREPROTOCOL_HUMANFORMAT_ACTIVE           
    GetOperationToString(string);  
    Primitive_Add<XSTRING*>(&string, DIOCOREPROTOCOL_HEADER_VAR_OPERATION);    
  #else    
    Primitive_Add<int>(operation, DIOCOREPROTOCOL_HEADER_VAR_OPERATION);
  #endif
  
  Primitive_Add<XSTRING*>(&operation_param, DIOCOREPROTOCOL_HEADER_VAR_OPERATION_PARAM);

  datetime_send->GetDateTimeToStringISO8601(XDATETIME_FORMAT_ISO8601_STANDARD | XDATETIME_FORMAT_TIMEWITHMILLISECONDS, string);
  Primitive_Add<XSTRING*>(&string, DIOCOREPROTOCOL_HEADER_VAR_DATETIME_SEND);

  #ifdef DIOCOREPROTOCOL_HUMANFORMAT_ACTIVE                 
    GetContentTypeToString(string);  
    Primitive_Add<XSTRING*>(&string, DIOCOREPROTOCOL_HEADER_VAR_CONTENT_TYPE);   
  #else
    Primitive_Add<int>(content_type, DIOCOREPROTOCOL_HEADER_VAR_CONTENT_TYPE);
  #endif  
  
  Primitive_Add<XDWORD>(block_index, DIOCOREPROTOCOL_HEADER_VAR_BLOCK_INDEX);

  Primitive_Add<XDWORD>(block_amount, DIOCOREPROTOCOL_HEADER_VAR_BLOCK_AMOUNT);
      
  Primitive_Add<XDWORD>(content_size, DIOCOREPROTOCOL_HEADER_VAR_CONTENT_SIZE);

  Primitive_Add<XDWORD>(content_compresssize, DIOCOREPROTOCOL_HEADER_VAR_CONTENT_COMPRESSSIZE);
   
  string.Format(__L("%08X"), content_CRC32);
  Primitive_Add<XSTRING*>(&string, DIOCOREPROTOCOL_HEADER_VAR_CONTENT_CRC32);

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
  Primitive_Extract<XSTRING&>(string, DIOCOREPROTOCOL_HEADER_VAR_ID_MESSAGE);
  ID_message.SetFromString(string);

  string.Empty();
  Primitive_Extract<XSTRING&>(string, DIOCOREPROTOCOL_HEADER_VAR_ID_MACHINE);
  ID_machine.SetFromString(string);
    
  #ifdef DIOCOREPROTOCOL_HUMANFORMAT_ACTIVE
    Primitive_Extract<XSTRING&>(string, DIOCOREPROTOCOL_HEADER_VAR_MESSAGE_TYPE);
    GetMessageTypeFromString(&string, message_type);       
  #else
    Primitive_Extract<int&>((int&)message_type, DIOCOREPROTOCOL_HEADER_VAR_MESSAGE_TYPE);
  #endif
  
  Primitive_Extract<XBYTE&>((XBYTE&)message_priority, DIOCOREPROTOCOL_HEADER_VAR_MESSAGE_PRIORITY);
      
  #ifdef DIOCOREPROTOCOL_HUMANFORMAT_ACTIVE
    Primitive_Extract<XSTRING&>(string, DIOCOREPROTOCOL_HEADER_VAR_OPERATION);
    GetOperationFromString(&string, operation);    
  #else
    Primitive_Extract<int&>((int&)operation, DIOCOREPROTOCOL_HEADER_VAR_OPERATION);
  #endif

  Primitive_Extract<XSTRING&>(operation_param, DIOCOREPROTOCOL_HEADER_VAR_OPERATION_PARAM);

  string.Empty();
  Primitive_Extract<XSTRING&>(string, DIOCOREPROTOCOL_HEADER_VAR_DATETIME_SEND);
  datetime_send->GetDateTimeFromStringISO8601(string, XDATETIME_FORMAT_ISO8601_STANDARD | XDATETIME_FORMAT_TIMEWITHMILLISECONDS);
  
  #ifdef DIOCOREPROTOCOL_HUMANFORMAT_ACTIVE
    Primitive_Extract<XSTRING&>(string, DIOCOREPROTOCOL_HEADER_VAR_CONTENT_TYPE);
    GetContentTypeFromString(&string, content_type); 
  #else
    Primitive_Extract<int&>((int&)content_type, DIOCOREPROTOCOL_HEADER_VAR_CONTENT_TYPE);
  #endif

  Primitive_Extract<XDWORD&>(block_index, DIOCOREPROTOCOL_HEADER_VAR_BLOCK_INDEX);

  Primitive_Extract<XDWORD&>(block_amount, DIOCOREPROTOCOL_HEADER_VAR_BLOCK_AMOUNT);

  Primitive_Extract<XDWORD&>(content_size, DIOCOREPROTOCOL_HEADER_VAR_CONTENT_SIZE);
         
  Primitive_Extract<XDWORD&>(content_compresssize, DIOCOREPROTOCOL_HEADER_VAR_CONTENT_COMPRESSSIZE);
  
  string.Empty();
  Primitive_Extract<XSTRING&>(string, DIOCOREPROTOCOL_HEADER_VAR_CONTENT_CRC32);
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
  message_priority      = 0;
  operation             = DIOCOREPROTOCOL_HEADER_OPERATION_UNKNOWN;  
  datetime_send         = NULL;
  content_type          = DIOCOREPROTOCOL_HEADER_CONTENTTYPE_UNKNOWN;   
  block_index           = 1;
  block_amount          = 1;
  content_size          = 0;
  content_compresssize  = 0;          
  content_CRC32         = 0;       
}

    
#pragma endregion


