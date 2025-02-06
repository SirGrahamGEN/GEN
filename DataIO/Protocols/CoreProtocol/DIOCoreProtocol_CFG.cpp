/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOCoreProtocol_CFG.cpp
* 
* @class      DIOCOREPROTOCOL_CFG
* @brief      Data Input/Output Core Protocol CFG class
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
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIOCoreProtocol_CFG.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_DIOCOREPROTOCOL_CFG


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_CFG::DIOCOREPROTOCOL_CFG()
* @brief      Constructor of class
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_CFG::DIOCOREPROTOCOL_CFG()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_CFG::~DIOCOREPROTOCOL_CFG()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOCOREPROTOCOL_CFG::~DIOCOREPROTOCOL_CFG()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CFG::GetIsServer()
* @brief      Get is server
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CFG::GetIsServer()
{
  return isserver;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_CFG::SetIsServer(bool isserver)
* @brief      Set is server
* @ingroup    DATAIO
* 
* @param[in]  isserver : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_CFG::SetIsServer(bool isserver)
{
  this->isserver = isserver;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CFG::GetIsCompressHeader()
* @brief      get is compress header
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CFG::GetIsCompressHeader()
{
  return iscompressheader;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_CFG::SetIsCompressHeader(bool iscompressheader)
* @brief      set is compress header
* @ingroup    DATAIO
* 
* @param[in]  iscompressheader : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_CFG::SetIsCompressHeader(bool iscompressheader)
{
  this->iscompressheader = iscompressheader;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CFG::GetIsCompressContent()
* @brief      get is compress content
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CFG::GetIsCompressContent()
{
  return iscompresscontent;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_CFG::SetIsCompressContent(bool iscompresscontent)
* @brief      set is compress content
* @ingroup    DATAIO
* 
* @param[in]  iscompresscontent : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_CFG::SetIsCompressContent(bool iscompresscontent)
{
  this->iscompresscontent;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CFG::GetIsEncapsulatedBase64()
* @brief      get is encapsulated base64
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CFG::GetIsEncapsulatedBase64()
{
  return isencapsulatedbase64;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_CFG::SetIsEncapsulatedBase64(bool isencapsulatedbase64)
* @brief      set is encapsulated base64
* @ingroup    DATAIO
* 
* @param[in]  isencapsulatedbase64 : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_CFG::SetIsEncapsulatedBase64(bool isencapsulatedbase64)
{
  this->isencapsulatedbase64 = isencapsulatedbase64;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIOCOREPROTOCOL_CFG::GetMinSizeCompressContent()
* @brief      Get min size compress content
* @ingroup    DATAIO
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOCOREPROTOCOL_CFG::GetMinSizeCompressContent()
{
  return minsizecompresscontent;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_CFG::SetMinSizeCompressContent(XDWORD minsizecompresscontent)
* @brief      Set min size compress content
* @ingroup    DATAIO
* 
* @param[in]  minsizecompresscontent : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_CFG::SetMinSizeCompressContent(XDWORD minsizecompresscontent)
{
  this->minsizecompresscontent = minsizecompresscontent;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CFG::GetIsCipher()
* @brief      Get is cipher
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CFG::GetIsCipher()
{
  return iscipher;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_CFG::SetIsCipher(bool iscipher)
* @brief      Set is cipher
* @ingroup    DATAIO
* 
* @param[in]  iscipher : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_CFG::SetIsCipher(bool iscipher)
{
  this->iscipher = iscipher;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIOCOREPROTOCOL_CFG::GetTimeOutNoResponse()
* @brief      Get time out no response
* @ingroup    DATAIO
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOCOREPROTOCOL_CFG::GetTimeOutNoResponse()
{
  return timeoutnoresponse;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_CFG::SetTimeOutNoResponse(XDWORD timeoutnoresponse)
* @brief      Set time out no response
* @ingroup    DATAIO
* 
* @param[in]  timeoutnoresponse : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_CFG::SetTimeOutNoResponse(XDWORD timeoutnoresponse)
{
  this->timeoutnoresponse = timeoutnoresponse;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIOCOREPROTOCOL_CFG::GetTimeToEliminateConnectionDisconnect()
* @brief      Get time to eliminate connection disconnect
* @ingroup    DATAIO
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOCOREPROTOCOL_CFG::GetTimeToEliminateConnectionDisconnect()
{
  return timetoeliminateconnectiondisconnect;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_CFG::SetTimeToEliminateConnectionDisconnect(XDWORD timetoeliminateconnectiondisconnect)
* @brief      Set time to eliminate connection disconnect
* @ingroup    DATAIO
* 
* @param[in]  timetoeliminateconnectiondisconnect : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_CFG::SetTimeToEliminateConnectionDisconnect(XDWORD timetoeliminateconnectiondisconnect)
{
  this->timetoeliminateconnectiondisconnect = timetoeliminateconnectiondisconnect;
}  
 
  
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIOCOREPROTOCOL_CFG::GetTimeToCheckConnection()
* @brief      Get time to check connection
* @ingroup    DATAIO
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOCOREPROTOCOL_CFG::GetTimeToCheckConnection()
{
  return timetocheckconnection;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_CFG::SetTimeToCheckConnection(XDWORD timetocheckconnection)
* @brief      Set time to check connection
* @ingroup    DATAIO
* 
* @param[in]  timetocheckconnection : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_CFG::SetTimeToCheckConnection(XDWORD timetocheckconnection)
{
  this->timetocheckconnection = timetocheckconnection;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIOCOREPROTOCOL_CFG::GetNTrysToCheckConnection()
* @brief      Get N trys to check connection
* @ingroup    DATAIO
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOCOREPROTOCOL_CFG::GetNTrysToCheckConnection()
{
  return ntrystocheckconnection;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_CFG::SetNTrysToCheckConnection(XDWORD ntrystocheckconnection)
* @brief      Set N trys to check connection
* @ingroup    DATAIO
* 
* @param[in]  ntrystocheckconnection : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_CFG::SetNTrysToCheckConnection(XDWORD ntrystocheckconnection)
{
  this->ntrystocheckconnection = ntrystocheckconnection;
}
  

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_CFG::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_CFG::Clean()
{
  isserver                              = false;

  iscompressheader                      = false;      
  iscompresscontent                     = false;
  isencapsulatedbase64                  = false;
  minsizecompresscontent                = DIOCOREPROTOCOL_CFG_DEFAULT_MINSIZECOMPRESS;

  iscipher                              = false;

  timeoutnoresponse                     = DIOCOREPROTOCOL_CFG_DEFAULT_TIMEOUTNORESPONSE;
  timetoeliminateconnectiondisconnect   = DIOCOREPROTOCOL_CFG_DEFAULT_TIMETOELIMINATECONNECTIONDISCONNECT;
  timetocheckconnection                 = DIOCOREPROTOCOL_CFG_DEFAULT_TIMETOCHECKCONNECTION;
  ntrystocheckconnection                = DIOCOREPROTOCOL_CFG_DEFAULT_NTRYSTOCHECKCONNECTION;
}


#pragma endregion

