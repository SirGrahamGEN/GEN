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
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIOCoreProtocol_CFG.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_DIOCOREPROTOCOL_CFG


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCOREPROTOCOL_CFG::DIOCOREPROTOCOL_CFG()
* @brief      Constructor
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
* @brief      Destructor
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
* @brief      GetIsServer
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
* @brief      SetIsServer
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
* @fn         bool DIOCOREPROTOCOL_CFG::GetCompressHeader()
* @brief      GetCompressHeader
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CFG::GetCompressHeader()
{
  return compressheader;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_CFG::SetCompressHeader(bool compressheader)
* @brief      SetCompressHeader
* @ingroup    DATAIO
* 
* @param[in]  compressheader : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_CFG::SetCompressHeader(bool compressheader)
{
  this->compressheader = compressheader;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOCOREPROTOCOL_CFG::GetCompressContent()
* @brief      GetCompressContent
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOCOREPROTOCOL_CFG::GetCompressContent()
{
  return compresscontent;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOCOREPROTOCOL_CFG::SetCompressContent(bool compresscontent)
* @brief      SetCompressContent
* @ingroup    DATAIO
* 
* @param[in]  compresscontent : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_CFG::SetCompressContent(bool compresscontent)
{
  this->compresscontent = compresscontent;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIOCOREPROTOCOL_CFG::GetMinSizeCompressContent()
* @brief      GetMinSizeCompressContent
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
* @brief      SetMinSizeCompressContent
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
* @brief      GetIsCipher
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
* @brief      SetIsCipher
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
* @brief      GetTimeOutNoResponse
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
* @brief      SetTimeOutNoResponse
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
* @brief      GetTimeToEliminateConnectionDisconnect
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
* @brief      SetTimeToEliminateConnectionDisconnect
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
* @brief      GetTimeToCheckConnection
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
* @brief      SetTimeToCheckConnection
* @ingroup    DATAIO
* 
* @param[in]  timetoheardbetinconnection : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_CFG::SetTimeToCheckConnection(XDWORD timetocheckconnection)
{
  this->timetocheckconnection = timetocheckconnection;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIOCOREPROTOCOL_CFG::GetNTrysToCheckConnection()
* @brief      GetNTrysToCheckConnection
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
* @brief      SetNTrysToCheckConnection
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
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOCOREPROTOCOL_CFG::Clean()
{
  compressheader                        = false;      
  compresscontent                       = false;
  minsizecompresscontent                = DIOCOREPROTOCOL_CFG_DEFAULT_MINSIZECOMPRESS;

  iscipher                              = false;

  timeoutnoresponse                     = DIOCOREPROTOCOL_CFG_DEFAULT_TIMEOUTNORESPONSE;
  timetoeliminateconnectiondisconnect   = DIOCOREPROTOCOL_CFG_DEFAULT_TIMETOELIMINATECONNECTIONDISCONNECT;
  timetocheckconnection                 = DIOCOREPROTOCOL_CFG_DEFAULT_TIMETOCHECKCONNECTION;
  ntrystocheckconnection                = DIOCOREPROTOCOL_CFG_DEFAULT_NTRYSTOCHECKCONNECTION;
}


#pragma endregion

