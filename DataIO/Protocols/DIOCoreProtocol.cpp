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
* @fn         DIOCOREPROTOCOL::DIOCOREPROTOCOL(DIOCOREPROTOCOL_CFG* protocolCFG)
* @brief      Constructor
* @ingroup    DATAIO
* 
* @param[in]  DIOCOREPROTOCOL_CFG* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL::DIOCOREPROTOCOL(DIOCOREPROTOCOL_CFG* protocolCFG)
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
* @fn         bool DIOCOREPROTOCOL::SendMsg(XUUID* IDmachine, XUUID* IDconnection, XBUFFER& content)
* @brief      SendMsg
* @ingroup    DATAIO
* 
* @param[in]  IDmachine : 
* @param[in]  IDconnection : 
* @param[in]  content : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL::SendMsg(XUUID* IDmachine, XUUID* IDconnection, XBUFFER& content)
{
  DIOCOREPROTOCOL_HEADER*  header          = NULL;
  XBUFFER                 contentresult;
  bool                    status          = false;

  header = CreateHeader(IDmachine, IDconnection, content, contentresult);
  if(!header)
    {      
      return false;
    }

  status = SendMsg(header, contentresult);
      
  delete header;
     
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL::SendMsg(XUUID* IDmachine, XUUID* IDconnection, XSTRING& content)
* @brief      SendMsg
* @ingroup    DATAIO
* 
* @param[in]  IDmachine : 
* @param[in]  IDconnection : 
* @param[in]  content : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL::SendMsg(XUUID* IDmachine, XUUID* IDconnection, XSTRING& content)
{
  DIOCOREPROTOCOL_HEADER*  header          = NULL;
  XBUFFER                 contentresult;
  bool                    status          = false;

  header = CreateHeader(IDmachine, IDconnection, content, contentresult);
  if(!header)
    {      
      return false;
    }
  
  status = SendMsg(header, contentresult);
      
  delete header;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL::SendMsg(XUUID* IDmachine, XUUID* IDconnection, XFILEJSON& content, bool iscontentcompress)
* @brief      SendMsg
* @ingroup    DATAIO
* 
* @param[in]  IDmachine : 
* @param[in]  IDconnection : 
* @param[in]  content : 
* @param[in]  iscontentcompress : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL::SendMsg(XUUID* IDmachine, XUUID* IDconnection, XFILEJSON& content)
{
  DIOCOREPROTOCOL_HEADER*  header          = NULL;  
  XBUFFER                 contentresult;  
  bool                    status          = false;

  header = CreateHeader(IDmachine, IDconnection, content, contentresult);
  if(!header)
    {      
      return false;
    }

  status = SendMsg(header, contentresult);
      
  delete header;
           
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

  /*
  if(!protocolCFG->GetDIOStream())
    {
      return false;
    }

  XBUFFER* readbuffer = protocolCFG->GetDIOStream()->GetInXBuffer();
  if(!readbuffer)
    {
      return false;
    }
  */

  XBUFFER* readbuffer = &debug_senddata;

  if(readbuffer->GetSize() < DIOCOREPROTOCOL_HEADER_SIZE_ID)
    {
      return false;
    }

  readbuffer->ResetPosition();

  XDWORD start  = 0;
  bool   status = false;
  
  if(readbuffer->Get((XDWORD)start, 0))
    {
      // Compress Data
      if(start == DIOCOREPROTOCOL_HEADER_MAGIC_ID)
        {
          XBUFFER headerbuffer;
          XWORD   sizeheader    = 0;
          XWORD   sizeheadercmp = 0;
          XDWORD  crc32header   = 0;

          if(readbuffer->Get((XWORD)sizeheader))
            {
              if(readbuffer->Get((XWORD)sizeheadercmp))
                {
                  if(readbuffer->Get((XDWORD)crc32header))
                    {
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
                                }
                               else
                                {
                                  status      = headerbuffer.Add(ptrheader, sizeheader);
                                  ptrcontent += sizeheader;
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
                                      status = compressor->Decompress(ptrcontent, header.GetContentCompressSize(), &content);
                                    }
                                   else
                                    {
                                      status = content.Add(ptrcontent, header.GetContentSize());
                                    }
                                }
                            }

                          return status;  
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
* @fn         DIOCOREPROTOCOL_HEADER* DIOCOREPROTOCOL::CreateHeader(XUUID* IDmachine, XUUID* IDconnection, XBUFFER& content, XBUFFER& contentresult)
* @brief      CreateHeader
* @ingroup    DATAIO
* 
* @param[in]  IDmachine : 
* @param[in]  IDconnection : 
* @param[in]  content : 
* @param[in]  contentresult : 
* 
* @return     DIOCOREPROTOCOL_HEADER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_HEADER* DIOCOREPROTOCOL::CreateHeader(XUUID* IDmachine, XUUID* IDconnection, XBUFFER& content, XBUFFER& contentresult)
{
  DIOCOREPROTOCOL_HEADER* header = CreateHeader(IDmachine, IDconnection);
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
* @fn         DIOCOREPROTOCOL_HEADER* DIOCOREPROTOCOL::CreateHeader(XUUID* IDmachine, XUUID* IDconnection, XSTRING& content, XBUFFER& contentresult)
* @brief      CreateHeader
* @ingroup    DATAIO
* 
* @param[in]  IDmachine : 
* @param[in]  IDconnection : 
* @param[in]  content : 
* @param[in]  contentresult : 
* 
* @return     DIOCOREPROTOCOL_HEADER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_HEADER* DIOCOREPROTOCOL::CreateHeader(XUUID* IDmachine, XUUID* IDconnection, XSTRING& content, XBUFFER& contentresult)
{
  DIOCOREPROTOCOL_HEADER* header = CreateHeader(IDmachine, IDconnection);
  if(!header)
    {
      return NULL;
    }  

  XBUFFER contentbinary;
  content.ConvertToUTF8(contentbinary);

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
* @fn         DIOCOREPROTOCOL_HEADER* DIOCOREPROTOCOL::CreateHeader(XUUID* IDmachine, XUUID* IDconnection, XFILEJSON& content, XBUFFER& contentresult)
* @brief      CreateHeader
* @ingroup    DATAIO
* 
* @param[in]  IDmachine : 
* @param[in]  IDconnection : 
* @param[in]  content : 
* @param[in]  contentresult : 
* 
* @return     DIOCOREPROTOCOL_HEADER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_HEADER* DIOCOREPROTOCOL::CreateHeader(XUUID* IDmachine, XUUID* IDconnection, XFILEJSON& content, XBUFFER& contentresult)
{
  DIOCOREPROTOCOL_HEADER* header = CreateHeader(IDmachine, IDconnection);
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

  header->SetMessageType(DIOCOREPROTOCOL_HEADER_MESSAGETYPE_REQUEST);

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
* @fn         DIOCOREPROTOCOL_HEADER* DIOCOREPROTOCOL::CreateHeader(XUUID* IDmachine, XUUID* IDconnection)
* @brief      CreateHeader
* @ingroup    DATAIO
* 
* @param[in]  IDmachine : 
* @param[in]  IDconnection : 
* 
* @return     DIOCOREPROTOCOL_HEADER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_HEADER* DIOCOREPROTOCOL::CreateHeader(XUUID* IDmachine, XUUID* IDconnection)
{
  if(!IDmachine)
    {
      return NULL;
    }

  if(!IDconnection)
    {
      return NULL;
    }

  DIOCOREPROTOCOL_HEADER* header = new DIOCOREPROTOCOL_HEADER();
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

  // ---  DEBUG -------------------------------------------------------------------------------------------------------------------------------------------

  XTRACE_PRINTCOLOR(XTRACE_COLOR_PURPLE, __L("------------------------------------------------------------------------------------------------------"));
  if(header->GetContentCompressSize())
    {
      XTRACE_PRINTCOLOR(XTRACE_COLOR_PURPLE, __L("[Core Protocol] Send data: Header size %d / Content size %d [cmp size %d] = Total %d"), headersize, header->GetContentSize(), header->GetContentCompressSize(), headersize + header->GetContentCompressSize());
    }
   else
    {
      XTRACE_PRINTCOLOR(XTRACE_COLOR_PURPLE, __L("[Core Protocol] Send data: Header size %d / Content size %d = Total %d"), headersize, header->GetContentSize(), headersize + header->GetContentSize());
    }
      
  XTRACE_PRINTDATABLOCKCOLOR(status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED, senddata);
  XTRACE_PRINTCOLOR(XTRACE_COLOR_PURPLE, __L("------------------------------------------------------------------------------------------------------"));

  // ------------------------------------------------------------------------------------------------------------------------------------------------------

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

  if(protocolCFG)
    {
      if(protocolCFG->GetDIOStream())
        {
          status = protocolCFG->GetDIOStream()->Write(senddata);
        }
    }


  debug_senddata.Empty();
  debug_senddata.Add(senddata);

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

  compressmanager = NULL;
  compressor      = NULL;    	
  
  initialization  = false;
}


#pragma endregion


