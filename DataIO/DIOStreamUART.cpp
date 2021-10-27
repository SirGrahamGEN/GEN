/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOStreamUART.cpp
*
* @class      DIOSTREAMUART
* @brief      Data Input/Output Stream UART class
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @copyright  Copyright(c) 2008 - 2016 GEN Group.
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
*---------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XFactory.h"
#include "DIOStreamUART.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMUART::DIOSTREAMUART()
* @brief      Constructor
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMUART::DIOSTREAMUART(): DIOSTREAM()
{
  Clean();

  xtimer = GEN_XFACTORY.CreateTimer();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMUART::~DIOSTREAMUART()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMUART::~DIOSTREAMUART()
{
  if(xtimer)  GEN_XFACTORY.DeleteTimer(xtimer);

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMCONFIG* DIOSTREAMUART::GetConfig()
* @brief      GetConfig
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     DIOSTREAMCONFIG* :
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMCONFIG* DIOSTREAMUART::GetConfig()
{
  return (DIOSTREAMCONFIG*)config;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUART::SetConfig(DIOSTREAMCONFIG* config)
* @brief      SetConfig
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  config :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUART::SetConfig(DIOSTREAMCONFIG* config)
{
  if(!config) return false;

  this->config = (DIOSTREAMUARTCONFIG*)config;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMSTATUS DIOSTREAMUART::GetConnectStatus()
* @brief      GetConnectStatus
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     DIOSTREAMSTATUS :
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMSTATUS DIOSTREAMUART::GetConnectStatus()
{
  return  DIOSTREAMSTATUS_DISCONNECTED;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUART::Open()
* @brief      Open
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUART::Open()
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUART::Config(XWORD mask)
* @brief      Config
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  mask :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUART::Config(XWORD mask)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOSTREAMUART::ReadDirect(XBYTE* buffer, XDWORD size)
* @brief      ReadDirect
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  buffer :
* @param[in]  size :
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSTREAMUART::ReadDirect(XBYTE* buffer, XDWORD size)
{
  return 0;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOSTREAMUART::WriteDirect(XBYTE* buffer, XDWORD size)
* @brief      WriteDirect
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  buffer :
* @param[in]  size :
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSTREAMUART::WriteDirect(XBYTE* buffer, XDWORD size)
{
  return 0;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUART::Close()
* @brief      Close
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUART::Close()
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUART::GetCTS()
* @brief      GetCTS
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUART::GetCTS()
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUART::GetDSR()
* @brief      GetDSR
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUART::GetDSR()
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUART::GetRing()
* @brief      GetRing
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUART::GetRing()
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUART::GetRLSD()
* @brief      GetRLSD
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUART::GetRLSD()
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUART::SetRTS(bool on)
* @brief      SetRTS
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  on :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUART::SetRTS(bool on)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUART::SetDTR(bool on)
* @brief      SetDTR
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  on :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUART::SetDTR(bool on)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMUART::CleanBuffers()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMUART::CleanBuffers()
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMUART::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMUART::Clean()
{
  config   = NULL;
  xtimer   = NULL;
}

