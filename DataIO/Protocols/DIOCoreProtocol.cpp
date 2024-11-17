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
#include "XFileJSON.h"
#include "XDateTime.h"

#include "HashCRC32.h"

#include "CompressManager.h"

#include "DIOStream.h"

#include "DIOCoreProtocol_Header.h"
#include "DIOCoreProtocol_CFG.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#pragma region CLASS_DIOCOREPROTOCOL


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL::DIOCOREPROTOCOL(DIOCOREPROTOCOL_CFG* protocolCFG, DIOSTREAM* diostream, XUUID* ID_machine)
* @brief      Constructor
* @ingroup    DATAIO
* 
* @param[in]  DIOCOREPROTOCOL_CFG* : 
* @param[in]   DIOSTREAM* diostream : 
* @param[in]   XUUID* ID_machine : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL::DIOCOREPROTOCOL(DIOCOREPROTOCOL_CFG* protocolCFG, DIOSTREAM* diostream, XUUID* ID_machine)
{
  Clean();

  compressmanager = new COMPRESSMANAGER();
  if(compressmanager)
    {
	    compressor = compressmanager->Create(COMPRESSBASE_TYPE_GZ);
      if(!compressor)
        {
          delete compressmanager;          
        }
    } 

  this->protocolCFG = protocolCFG;
  this->diostream   = diostream;
  this->ID_machine  = ID_machine;
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
  if(compressmanager)
    {
      delete compressmanager;
    }

  if(compressor)
    {
      delete compressor;
    }

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
* @fn         DIOCOREPROTOCOL_CFG* DIOCOREPROTOCOL::GetProtocolCFG()
* @brief      GetProtocolCFG
* @ingroup    DATAIO
* 
* @return     DIOCOREPROTOCOL_CFG* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_CFG* DIOCOREPROTOCOL::GetProtocolCFG()
{
  return protocolCFG;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOSTREAM* DIOCOREPROTOCOL::GetDIOStream()
* @brief      GetDIOStream
* @ingroup    DATAIO
* 
* @return     DIOSTREAM* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAM* DIOCOREPROTOCOL::GetDIOStream()
{
  return diostream;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL::SetDIOStream(DIOSTREAM* diostream)
* @brief      SetDIOStream
* @ingroup    DATAIO
* 
* @param[in]  diostream : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL::SetDIOStream(DIOSTREAM* diostream)
{
  this->diostream = diostream;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL::SendMsg(DIOCOREPROTOCOL_HEADER* header, XBUFFER& contentresult)
* @brief      SendMsg
* @ingroup    DATAIO
* 
* @param[in]  header : 
* @param[in]  contentresult : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL::SendMsg(DIOCOREPROTOCOL_HEADER* header, XBUFFER& contentresult)
{
  XBUFFER senddata; 
  XWORD   headersize;
  bool    status   = false;

  if(!header)
    {
      return false;
    }
    
  if(!GenerateHeaderToSend(header, senddata, &headersize))
    {
      return false;
    }
           
  senddata.Add(contentresult);

  status = SendData(senddata);

  
  #ifdef DIOCOREPROTOCOL_DEBUG_ACTIVE
  if(status)
    {
      ShowDebug(true, header, contentresult);
    }
  #endif
  
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL::ReceivedMsg(DIOCOREPROTOCOL_HEADER& header, XBUFFER& content)
* @brief      ReceivedMsg
* @ingroup    DATAIO
* 
* @param[in]  header : 
* @param[in]  content : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL::ReceivedMsg(DIOCOREPROTOCOL_HEADER& header, XBUFFER& content)
{
  if(!protocolCFG)
    {
      return false;
    }

  if(!diostream)
    {
      return false;
    }

  XBUFFER* readbuffer = diostream->GetInXBuffer();
  if(!readbuffer)
    {
      return false;
    }
  
  readbuffer->ResetPosition();

  if(readbuffer->GetSize() < DIOCOREPROTOCOL_HEADER_SIZE_ID)
    {
      return false;
    }

  XDWORD start      = 0;
  XDWORD sizeread   = 0;
  bool   status     = false;

  for(XDWORD c=0; c<16; c++)    
    {
      if(readbuffer->Get((XDWORD&)start, c))
        {
          sizeread += sizeof(XDWORD);

          // Compress Data
          if(start == DIOCOREPROTOCOL_HEADER_MAGIC_ID)
            {
              XBUFFER headerbuffer;
              XWORD   sizeheader    = 0;
              XWORD   sizeheadercmp = 0;
              XDWORD  crc32header   = 0;

              if(readbuffer->Get((XWORD&)sizeheader))
                {
                  sizeread += sizeof(XDWORD);

                  if(readbuffer->Get((XWORD&)sizeheadercmp))
                    {
                      sizeread += sizeof(XDWORD);

                      if(readbuffer->Get((XDWORD&)crc32header))
                        {
                          sizeread += sizeof(XDWORD);
  
                          if(sizeheader)
                            {       
                              XBYTE*    ptrheader  = &readbuffer->Get()[DIOCOREPROTOCOL_HEADER_SIZE_ID];
                              XBYTE*    ptrcontent = ptrheader;                           
                              HASHCRC32 hashCRC32;
  
                              if(sizeheadercmp)
                                {     
                                  hashCRC32.Do(ptrheader, sizeheadercmp); 
                                }
                               else
                                {
                                  hashCRC32.Do(ptrheader, sizeheader); 
                                } 
   
                              if(hashCRC32.GetResultCRC32() == crc32header)
                                {
                                  if(sizeheadercmp)
                                    {
                                      headerbuffer.Resize(sizeheader);                                        
                                      status      = compressor->Decompress(ptrheader, sizeheadercmp, &headerbuffer);
                                      ptrcontent += sizeheadercmp;
                                      sizeread   += sizeheadercmp;
                                    }
                                   else
                                    {
                                      status      = headerbuffer.Add(ptrheader, sizeheader);
                                      ptrcontent += sizeheader;
                                      sizeread   += sizeheader;
                                    }

                                  XFILEJSON* headerxfileJSON = header.GetSerializationXFileJSON();
                                  if(headerxfileJSON)
                                    {                                                                                                  
                                      header.GetSerializationXFileJSON()->AddBufferLines(XFILETXTFORMATCHAR_UTF8, headerbuffer);
                                      header.GetSerializationXFileJSON()->DecodeAllLines();
                                      header.DoDeserialize();
                                    } 

                                  HASHCRC32 hashCRC32;

                                  hashCRC32.Do(ptrcontent, header.GetContentCompressSize()?header.GetContentCompressSize():header.GetContentSize());  
                                  status = (header.GetContentCRC32() == hashCRC32.GetResultCRC32())?true:false;
                        
                                  if(status)
                                    {        
                                      if(header.GetContentCompressSize())
                                        {
                                          content.Resize(header.GetContentSize());
                                          status    = compressor->Decompress(ptrcontent, header.GetContentCompressSize(), &content);
                                          sizeread += header.GetContentCompressSize();
                                        }
                                       else
                                        {
                                          if(header.GetContentSize())
                                            {
                                              status = content.Add(ptrcontent, header.GetContentSize());
                                              sizeread += header.GetContentSize();
                                            }
                                        }
                                    }
                                }

                              readbuffer->Extract(NULL, c, sizeread);

                              return status;  
                            }
                        }
                    }
                }
            }
        }
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_HEADER* DIOCOREPROTOCOL::CreateHeader(XUUID* ID_message, XBYTE message_priority, DIOCOREPROTOCOL_HEADER_OPERATION operation, XCHAR* operation_param, XBUFFER& content, XBUFFER& contentresult)
* @brief      CreateHeader
* @ingroup    DATAIO
* 
* @param[in]  ID_message : 
* @param[in]  message_priority : 
* @param[in]  operation : 
* @param[in]  operation_param : 
* @param[in]  content : 
* @param[in]  contentresult : 
* 
* @return     DIOCOREPROTOCOL_HEADER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_HEADER* DIOCOREPROTOCOL::CreateHeader(XUUID* ID_message, XBYTE message_priority, DIOCOREPROTOCOL_HEADER_OPERATION operation, XCHAR* operation_param, XBUFFER& content, XBUFFER& contentresult)
{
  DIOCOREPROTOCOL_HEADER* header = CreateHeader(ID_message, message_priority, operation, operation_param);
  if(!header)
    {
      return NULL;
    }

  header->SetContentType(DIOCOREPROTOCOL_HEADER_CONTENTTYPE_BINARY);
  header->SetContentSize(content.GetSize()); 

  if(!CompressContent(header, content, contentresult))
    {                  
      contentresult.CopyFrom(content);
    }   
  
  HASHCRC32 hashCRC32;

  hashCRC32.Do(contentresult);  
  header->SetContentCRC32(hashCRC32.GetResultCRC32());

  return header;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_HEADER* DIOCOREPROTOCOL::CreateHeader(XUUID* ID_message, XBYTE message_priority, DIOCOREPROTOCOL_HEADER_OPERATION operation, XCHAR* operation_param, XSTRING& content, XBUFFER& contentresult)
* @brief      CreateHeader
* @ingroup    DATAIO
* 
* @param[in]  ID_message : 
* @param[in]  message_priority : 
* @param[in]  operation : 
* @param[in]  operation_param : 
* @param[in]  content : 
* @param[in]  contentresult : 
* 
* @return     DIOCOREPROTOCOL_HEADER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_HEADER* DIOCOREPROTOCOL::CreateHeader(XUUID* ID_message, XBYTE message_priority, DIOCOREPROTOCOL_HEADER_OPERATION operation, XCHAR* operation_param, XSTRING& content, XBUFFER& contentresult)
{
  DIOCOREPROTOCOL_HEADER* header = CreateHeader(ID_message, message_priority, operation, operation_param);
  if(!header)
    {
      return NULL;
    }  

  XBUFFER contentbinary;
  content.ConvertToUTF8(contentbinary, false);

  header->SetContentType(DIOCOREPROTOCOL_HEADER_CONTENTTYPE_TEXT);
  header->SetContentSize(contentbinary.GetSize());   

  if(!CompressContent(header, contentbinary, contentresult))
    {                  
      contentresult.CopyFrom(contentbinary);
    }   

  HASHCRC32 hashCRC32;

  hashCRC32.Do(contentresult);  
  header->SetContentCRC32(hashCRC32.GetResultCRC32());

  return header;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_HEADER* DIOCOREPROTOCOL::CreateHeader(XUUID* ID_message, XBYTE message_priority, DIOCOREPROTOCOL_HEADER_OPERATION operation, XCHAR* operation_param, XFILEJSON& content, XBUFFER& contentresult)
* @brief      CreateHeader
* @ingroup    DATAIO
* 
* @param[in]  ID_message : 
* @param[in]  message_priority : 
* @param[in]  operation : 
* @param[in]  operation_param : 
* @param[in]  content : 
* @param[in]  contentresult : 
* 
* @return     DIOCOREPROTOCOL_HEADER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_HEADER* DIOCOREPROTOCOL::CreateHeader(XUUID* ID_message, XBYTE message_priority, DIOCOREPROTOCOL_HEADER_OPERATION operation, XCHAR* operation_param, XFILEJSON& content, XBUFFER& contentresult)
{
  DIOCOREPROTOCOL_HEADER* header = CreateHeader(ID_message, message_priority, operation, operation_param);
  if(!header)
    {
      return NULL;
    }  

  XSTRING contentstring;
  XBUFFER contentbinary;

  content.EncodeAllLines(false);  
  content.GetAllInOneLine(contentstring);

  contentstring.ConvertToUTF8(contentbinary);

  header->SetContentType(DIOCOREPROTOCOL_HEADER_CONTENTTYPE_JSON);
  header->SetContentSize(contentbinary.GetSize());   

  if(!CompressContent(header, contentbinary, contentresult))
    {                  
      contentresult.CopyFrom(contentbinary);
    }   

  HASHCRC32 hashCRC32;

  hashCRC32.Do(contentresult);  
  header->SetContentCRC32(hashCRC32.GetResultCRC32());

  return header;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL::GenerateAuthenticationChallenge(XBUFFER& autentication_challange)
* @brief      GenerateAuthenticationChallenge
* @ingroup    DATAIO
* 
* @param[in]  autentication_challange : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL::GenerateAuthenticationChallenge(XBUFFER& autentication_challange)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL::GenerateAuthenticationResponse(XBUFFER& autentication_challange, XBUFFER& autentication_response)
* @brief      GenerateAuthenticationResponse
* @ingroup    DATAIO
* 
* @param[in]  autentication_challange : 
* @param[in]  autentication_response : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL::GenerateAuthenticationResponse(XBUFFER& autentication_challange, XBUFFER& autentication_response)
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL::GenerateCipherKey(XBUFFER& challange, CIPHERKEYSYMMETRICAL& cipher_key)
* @brief      GenerateCipherKey
* @ingroup    DATAIO
* 
* @param[in]  challange : 
* @param[in]  cipher_key : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL::GenerateCipherKey(XBUFFER& challange, CIPHERKEYSYMMETRICAL& cipher_key)
{
  return true;
}


#ifdef DIOCOREPROTOCOL_DEBUG_ACTIVE
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL::ShowDebug(bool send, DIOCOREPROTOCOL_HEADER* header, XBUFFER& content)
* @brief      ShowDebug
* @ingroup    DATAIO
* 
* @param[in]  send : 
* @param[in]  header : 
* @param[in]  content : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL::ShowDebug(bool send, DIOCOREPROTOCOL_HEADER* header, XBUFFER& content)
{
  XBUFFER   contentresult;
  int       colormsg = XTRACE_COLOR_BLUE;
 
  if(!header)
    {
      return false;
    }

  /*
  if(header->GetMessageType() == DIOCOREPROTOCOL_HEADER_MESSAGETYPE_RESPONSE)
    {
      colormsg = XTRACE_COLOR_PURPLE;
    }
  */

  if(!send)
    {
      colormsg = XTRACE_COLOR_GREEN;
    }  

  header->GetSerializationXFileJSON()->ShowTraceJSON(colormsg);

  if(header->GetContentCompressSize())
    {
      contentresult.Resize(header->GetContentSize());
      compressor->Decompress(content.Get(), header->GetContentCompressSize(), &contentresult);
    }
   else  
    {
      contentresult.CopyFrom(content);
    }  
  
  switch(header->GetContentType())
    {
      case DIOCOREPROTOCOL_HEADER_CONTENTTYPE_UNKNOWN   : break;
  
      case DIOCOREPROTOCOL_HEADER_CONTENTTYPE_BINARY    : XTRACE_PRINTDATABLOCKCOLOR(colormsg, contentresult);
                                                          break; 
  
      case DIOCOREPROTOCOL_HEADER_CONTENTTYPE_TEXT      : { XSTRING string;
  
                                                            string.ConvertFromUTF8(contentresult);
                                                            XTRACE_PRINTCOLOR(colormsg, string.Get());
                                                          }
                                                          break;
  
      case DIOCOREPROTOCOL_HEADER_CONTENTTYPE_JSON      : { XFILEJSON xfileJSON;   
                                                            
                                                            xfileJSON.AddBufferLines(XFILETXTFORMATCHAR_UTF8, contentresult);
                                                            xfileJSON.DecodeAllLines();
                                                            xfileJSON.ShowTraceJSON(colormsg);                                                                  
                                                          }
                                                          break;
    }

  return true;
}
#endif


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_HEADER* DIOCOREPROTOCOL::CreateHeader(XUUID* ID_message, XBYTE message_priority, DIOCOREPROTOCOL_HEADER_OPERATION operation, XCHAR* operation_param)
* @brief      CreateHeader
* @ingroup    DATAIO
* 
* @param[in]  ID_message : 
* @param[in]  message_priority : 
* @param[in]  operation : 
* @param[in]  operation_param : 
* 
* @return     DIOCOREPROTOCOL_HEADER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_HEADER* DIOCOREPROTOCOL::CreateHeader(XUUID* ID_message, XBYTE message_priority, DIOCOREPROTOCOL_HEADER_OPERATION operation, XCHAR* operation_param)
{
  DIOCOREPROTOCOL_HEADER* header = new DIOCOREPROTOCOL_HEADER();
  if(!header)
    {
      return NULL;
    }

  if(!ID_message)
    {
      header->SetMessageType(DIOCOREPROTOCOL_HEADER_MESSAGETYPE_REQUEST);
      header->GetIDMessage()->GenerateRandom();
      
    }
   else
    {      
      header->SetMessageType(DIOCOREPROTOCOL_HEADER_MESSAGETYPE_RESPONSE);
      header->GetIDMessage()->CopyFrom((*ID_message));
    }

  if(ID_machine)
    {
      header->GetIDMachine()->CopyFrom((*ID_machine));
    }

  header->SetMessagePriority(message_priority), 
  header->SetOperation(operation);
  header->GetOperationParam()->Set(operation_param);
  header->GetDateTimeSend()->Read();

  return header;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL::GenerateHeaderToSend(DIOCOREPROTOCOL_HEADER* header, XBUFFER& headersenddata, XWORD* headersize)
* @brief      GenerateHeaderToSend
* @ingroup    DATAIO
* 
* @param[in]  header : 
* @param[in]  headersenddata : 
* @param[in]  headersize : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL::GenerateHeaderToSend(DIOCOREPROTOCOL_HEADER* header, XBUFFER& headersenddata, XWORD* headersize)
{
  XFILEJSON*  headerxfileJSON = NULL;
  XSTRING     headerstring;
  XBUFFER     headerbuffer;  
  XBUFFER     headercmp;
  bool        isheadercmp     = false;  
  bool        status          = false;
  
  if(!header)
    {
      return status;
    }

  headersenddata.Empty();

  headerxfileJSON = header->GetSerializationXFileJSON();
  if(!headerxfileJSON)
    {
      return false;
    }

  status = header->DoSerialize();
  if(!status)
    {    
      return status;
    }
 
  headerxfileJSON->EncodeAllLines(false);  
  headerxfileJSON->GetAllInOneLine(headerstring);

  headerstring.ConvertToUTF8(headerbuffer);

  if(protocolCFG)
    {
      if(protocolCFG->GetCompressHeader())
        {
          if(!compressor->Compress(headerbuffer.Get(), headerbuffer.GetSize(), &headercmp))
            {
              return status;        
            }

          if(headercmp.GetSize() < headerbuffer.GetSize())
            {
              isheadercmp = true;
            }
           else 
            {
              headercmp.Empty();    
            } 
        }
    }
      
  headersenddata.Add((XDWORD)DIOCOREPROTOCOL_HEADER_MAGIC_ID);          
  headersenddata.Add((XWORD)headerbuffer.GetSize()); 
  headersenddata.Add((XWORD)headercmp.GetSize()); 

  HASHCRC32 hashCRC32;
  
  if(isheadercmp)
    {     
      hashCRC32.Do(headercmp); 
    }
   else
    {
      hashCRC32.Do(headerbuffer); 
    } 
   
  headersenddata.Add((XDWORD)hashCRC32.GetResultCRC32());
              
  if(isheadercmp)
    {
      if(headersize)
        {
          (*headersize) = headercmp.GetSize();  
        }

      headersenddata.Add(headercmp); 
    }
   else
    {
      if(headersize)
        {
          (*headersize) = headerbuffer.GetSize();  
        }

      headersenddata.Add(headerbuffer); 
    } 

  return status;  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL::SendData(XBUFFER& senddata)
* @brief      SendData
* @ingroup    DATAIO
* 
* @param[in]  senddata : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL::SendData(XBUFFER& senddata)
{
  bool status = false;

  if(!protocolCFG)
    {
      return false;
    }

  if(!diostream)
    {
      return false;
    } 
     
  status = diostream->Write(senddata);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL::CompressContent(DIOCOREPROTOCOL_HEADER* header, XBUFFER& content, XBUFFER& contentresult)
* @brief      CompressContent
* @ingroup    DATAIO
* 
* @param[in]  header : 
* @param[in]  content : 
* @param[in]  contentresult : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL::CompressContent(DIOCOREPROTOCOL_HEADER* header, XBUFFER& content,  XBUFFER& contentresult)
{
  bool status = false;

  if(protocolCFG)
    {    
      if(protocolCFG->GetCompressContent())
        {
          if(content.GetSize() >= protocolCFG->GetMinSizeCompressContent())
            {
              if(compressor->Compress(content.Get(), content.GetSize(), &contentresult))
                {
                  if(content.GetSize() > contentresult.GetSize()) 
                    {
                      header->SetContentCompressSize(contentresult.GetSize());   
                      status = true; 
                    }
                }    
            }
        }
    }

  return status;
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
  protocolCFG     = NULL;
  diostream       = NULL;
  ID_machine      = NULL;

  compressmanager = NULL;
  compressor      = NULL;    	
  
  initialization  = false;
}


#pragma endregion


