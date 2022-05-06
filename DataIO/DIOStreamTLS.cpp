/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOStreamTLS.cpp
*
* @class      DIOSTREAMTLS
* @brief      Data Input/Output Stream TLS (Transport Layer Security) class
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XBase.h"

#include "DIOFactory.h"
#include "DIOStreamTCPIP.h"

#include "DIOStreamTLS.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMTLS::DIOSTREAMTLS(DIOSTREAMCONFIG* config)
* @brief      Constructor
* @ingroup    DATAIO
*
* @param[in]  DIOSTREAMCONFIG* : 
*
* @return     Does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMTLS::DIOSTREAMTLS(DIOSTREAMTLSCONFIG* config) 
{
  Clean();

  SetConfig((DIOSTREAMCONFIG*)config);

  diostream = (DIOSTREAMTCPIP*)GEN_DIOFACTORY.CreateStreamIO((DIOSTREAMCONFIG*)config);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMTLS::~DIOSTREAMTLS()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMTLS::~DIOSTREAMTLS()
{
  if(diostream) GEN_DIOFACTORY.DeleteStreamIO(diostream);

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMCONFIG* DIOSTREAMTLS::GetConfig()
* @brief      GetConfig
* @ingroup    DATAIO
*
* @return     DIOSTREAMCONFIG* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMCONFIG* DIOSTREAMTLS::GetConfig()
{
  return (DIOSTREAMCONFIG*)config;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMTLS::SetConfig(DIOSTREAMCONFIG* config)
* @brief      SetConfig
* @ingroup    DATAIO
*
* @param[in]  config :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMTLS::SetConfig(DIOSTREAMCONFIG* config)
{
  if(!config) return false;
  this->config = (DIOSTREAMTLSCONFIG *)config;

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMSTATUS DIOSTREAMTLS::GetConnectStatus()
* @brief      GetConnectStatus
* @ingroup    DATAIO
*
* @return     DIOSTREAMSTATUS : 
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMSTATUS DIOSTREAMTLS::GetConnectStatus()
{
  if(!diostream) return DIOSTREAMSTATUS_DISCONNECTED;

  return diostream->GetConnectStatus();
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMTLS::Open()
* @brief      Open
* @ingroup    DATAIO
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMTLS::Open()
{
  if(!diostream) return false;

  return diostream->Open();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMTLS::HandShake_Client_Hello()
* @brief      HandShake_Client_Hello
* @ingroup    DATAIO
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMTLS::HandShake_Client_Hello()
{
  XBUFFER   xbuffer;
  XWORD     size16                            = 0;
  XBYTE     size24[3]                         = { 0, 0, 0 };  
  bool      status                            = false;

  //-------------------------------------------------------------------
  // TLS Plaintext

  xbuffer.Add((XBYTE)DIOSTREAMTLS_CONTENTTYPE_HANDSHAKE);             // Content Type     
  xbuffer.Add((XWORD)SwapWORD(DIOSTREAMTLS_VERSION_TLS_1_0));         // legacy record version
  xbuffer.Add((XWORD)SwapWORD(size16));                               // Length 

  //-------------------------------------------------------------------
  // HandSake protot
  xbuffer.Add((XBYTE)DIOSTREAMTLS_HANDSHAKETYPE_CLIENT_HELLO);        // Handshake type: Client Hello (1)
  xbuffer.Add(size24, 3);
  xbuffer.Add((XWORD)SwapWORD(DIOSTREAMTLS_VERSION_TLS_1_2));         // Version TLS 1.2
  xbuffer.Add(random, DIOSTREAMTLS_RANDOM_SIZE);                      // Random
  xbuffer.Add((XBYTE)DIOSTREAMTLS_SESSION_ID_SIZE);                   // Session ID length
  xbuffer.Add(sessionID, DIOSTREAMTLS_SESSION_ID_SIZE);               // Session ID


  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOSTREAMTLS::Read(XBYTE* buffer, XDWORD size)
* @brief      Read
* @ingroup    DATAIO
*
* @param[in]  buffer : 
* @param[in]  size : 
*
* @return     XDWORD : 
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSTREAMTLS::Read(XBYTE* buffer, XDWORD size)
{
  if(!diostream) return false;
  return diostream->Read(buffer, size);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOSTREAMTLS::Write(XBYTE* buffer, XDWORD size)
* @brief      Write
* @ingroup    DATAIO
*
* @param[in]  buffer : 
* @param[in]  size : 
*
* @return     XDWORD : 
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSTREAMTLS::Write(XBYTE* buffer, XDWORD size)
{
  if(!diostream) return false;
  return diostream->Write(buffer, size);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMTLS::Disconnect()
* @brief      Disconnect
* @ingroup    DATAIO
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMTLS::Disconnect()
{
  if(!diostream) return false;
  return diostream->Disconnect();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMTLS::Close()
* @brief      Close
* @ingroup    DATAIO
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMTLS::Close()
{
  if(!diostream) return false;
  return diostream->Close();
}





/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMTCPIP* DIOSTREAMTLS::GetDIOStreamBase()
* @brief      GetDIOStreamBase
* @ingroup    DATAIO
*
* @return     DIOSTREAMTCPIP* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMTCPIP* DIOSTREAMTLS::GetDIOStreamBase()
{
  return diostream;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMTLS::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMTLS::Clean()
{
  config      = NULL;  
  diostream   = NULL;
}



