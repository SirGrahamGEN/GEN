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

  datetimesend = GEN_XFACTORY.CreateDateTime();
  if(datetimesend)
    {
      datetimesend->Read();
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

  if(datetimesend)
    {
      GEN_XFACTORY.DeleteDateTime(datetimesend);
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
  return &IDmachine;
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
  return &IDconnection;
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
  return &IDmessage;
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
  return datetimesend;
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
  return contenttype;
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
void DIOCOREPROTOCOLHEADER::SetContentType(DIOCOREPROTOCOLHEADER_CONTENTTYPE contenttype)
{
  this->contenttype = contenttype;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOLHEADER::GetContentTypeToString(XSTRING& contenttypestr)
* @brief      GetContentTypeToString
* @ingroup    DATAIO
* 
* @param[in]  contenttypestr : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOLHEADER::GetContentTypeToString(XSTRING& contenttypestr)
{
  contenttypestr.Empty();

  switch(contenttype)
    {
      case DIOCOREPROTOCOLHEADER_CONTENTTYPE_UNKNOWN  : contenttypestr = DIOCOREPROTOCOLHEADER_CONTENTTYPE_STRING_UNKNOWN;  break;
      case DIOCOREPROTOCOLHEADER_CONTENTTYPE_BINARY   : contenttypestr = DIOCOREPROTOCOLHEADER_CONTENTTYPE_STRING_BINARY;   break;
      case DIOCOREPROTOCOLHEADER_CONTENTTYPE_TEXT     : contenttypestr = DIOCOREPROTOCOLHEADER_CONTENTTYPE_STRING_TEXT;     break;
      case DIOCOREPROTOCOLHEADER_CONTENTTYPE_JSON     : contenttypestr = DIOCOREPROTOCOLHEADER_CONTENTTYPE_STRING_JSON;     break;
    }

  return contenttypestr.IsEmpty()?false:true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOLHEADER::GetContentTypeFromString(XSTRING* contenttypestr, DIOCOREPROTOCOLHEADER_CONTENTTYPE& contenttype)
* @brief      GetContentTypeFromString
* @ingroup    DATAIO
* 
* @param[in]  contenttypestr : 
* @param[in]  contenttype : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOLHEADER::GetContentTypeFromString(XSTRING* contenttypestr, DIOCOREPROTOCOLHEADER_CONTENTTYPE& contenttype)
{
  if(!contenttypestr)
    {
      return false;
    }

  contenttype = DIOCOREPROTOCOLHEADER_CONTENTTYPE_UNKNOWN;

  if(!contenttypestr->Compare(DIOCOREPROTOCOLHEADER_CONTENTTYPE_STRING_UNKNOWN))
    {
      contenttype = DIOCOREPROTOCOLHEADER_CONTENTTYPE_UNKNOWN;
    }

  if(!contenttypestr->Compare(DIOCOREPROTOCOLHEADER_CONTENTTYPE_STRING_BINARY))
    {
      contenttype = DIOCOREPROTOCOLHEADER_CONTENTTYPE_BINARY;
    }

  if(!contenttypestr->Compare(DIOCOREPROTOCOLHEADER_CONTENTTYPE_STRING_TEXT))
    {
      contenttype = DIOCOREPROTOCOLHEADER_CONTENTTYPE_TEXT;
    }

  if(!contenttypestr->Compare(DIOCOREPROTOCOLHEADER_CONTENTTYPE_STRING_JSON))
    {
      contenttype = DIOCOREPROTOCOLHEADER_CONTENTTYPE_JSON;
    }

  return contenttype;
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
  return contentsize;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOLHEADER::SetContentSize(XDWORD contentsize)
* @brief      SetContentSize
* @ingroup    DATAIO
* 
* @param[in]  contentsize : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOLHEADER::SetContentSize(XDWORD contentsize)
{
  this->contentsize = contentsize;
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
  return contentCRC32;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOLHEADER::SetContentCRC32(XDWORD contentCRC32)
* @brief      SetContentCRC32
* @ingroup    DATAIO
* 
* @param[in]  contentCRC32 : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOLHEADER::SetContentCRC32(XDWORD contentCRC32)
{
  this->contentCRC32 = contentCRC32;
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
  XSTRING string;

  string.Empty();
  IDmachine.GetToString(string);
  Primitive_Add<XSTRING*>(&string, __L("IDmachine"));

  string.Empty();
  IDconnection.GetToString(string);
  Primitive_Add<XSTRING*>(&string, __L("IDconnection"));

  string.Empty();
  IDmessage.GetToString(string);
  Primitive_Add<XSTRING*>(&string, __L("IDmessage"));

  string.Empty();
  datetimesend->GetDateTimeToStringISO8601(XDATETIME_FORMAT_ISO8601_STANDARD | XDATETIME_FORMAT_TIMEWITHMILLISECONDS, string);
  Primitive_Add<XSTRING*>(&string, __L("datetimesend"));

  GetContentTypeToString(string);  
  Primitive_Add<XSTRING*>(&string, __L("contenttype"));
  
  string.Empty();
  string.Format(__L("%d"), contentsize);
  Primitive_Add<XSTRING*>(&string, __L("contentsize"));

  string.Empty();
  string.Format(__L("%08X"), contentCRC32);
  Primitive_Add<XSTRING*>(&string, __L("contentCRC32"));

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
  Primitive_Extract<XSTRING&>(string, __L("IDmachine"));
  IDmachine.SetFromString(string);

  string.Empty();
  Primitive_Extract<XSTRING&>(string, __L("IDconnection"));
  IDconnection.SetFromString(string);
  
  string.Empty();
  Primitive_Extract<XSTRING&>(string, __L("IDmessage"));
  IDmessage.SetFromString(string);

  string.Empty();
  Primitive_Extract<XSTRING&>(string, __L("datetimesend"));
  datetimesend->GetDateTimeFromStringISO8601(string, XDATETIME_FORMAT_ISO8601_STANDARD | XDATETIME_FORMAT_TIMEWITHMILLISECONDS);
  
  Primitive_Extract<XSTRING&>(string, __L("contenttype"));
  GetContentTypeFromString(&string, contenttype);  

  string.Empty();
  Primitive_Extract<XSTRING&>(string, __L("contentsize"));
  string.UnFormat(__L("%d"), &contentsize);
  
  string.Empty();
  Primitive_Extract<XSTRING&>(string, __L("contentCRC32"));
  string.UnFormat(__L("%08X"), &contentCRC32);

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
  contenttype   = DIOCOREPROTOCOLHEADER_CONTENTTYPE_UNKNOWN;
  contentCRC32  = 0;
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


