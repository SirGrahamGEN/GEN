/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIODNSProtocol_MitM_Server_XEvent.cpp
* 
* @class      DIODNSPROTOCOL_MITM_SERVER_XEVENT
* @brief      Data Input/Output Domain Network System (DNS) protocol Man-in-the-Middle (MitM) Server eXtended Event class
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

#include "DIODNSProtocol_MitM_Server_XEvent.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIODNSPROTOCOL_MITM_SERVER_XEVENT::DIODNSPROTOCOL_MITM_SERVER_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family): XEVENT(subject, type, family)
* @brief      Constructor of class
* @ingroup    DATAIO
* 
* @param[in]  subject : 
* @param[in]  type : 
* @param[in]  family : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIODNSPROTOCOL_MITM_SERVER_XEVENT::DIODNSPROTOCOL_MITM_SERVER_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family): XEVENT(subject, type, family)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIODNSPROTOCOL_MITM_SERVER_XEVENT::~DIODNSPROTOCOL_MITM_SERVER_XEVENT()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIODNSPROTOCOL_MITM_SERVER_XEVENT::~DIODNSPROTOCOL_MITM_SERVER_XEVENT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOIP* DIODNSPROTOCOL_MITM_SERVER_XEVENT::GetOriginIP()
* @brief      Get origin IP
* @ingroup    DATAIO
* 
* @return     DIOIP* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOIP* DIODNSPROTOCOL_MITM_SERVER_XEVENT::GetOriginIP()
{
  return &origin_IP;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOURL* DIODNSPROTOCOL_MITM_SERVER_XEVENT::GetAskedURL()
* @brief      Get asked URL
* @ingroup    DATAIO
* 
* @return     DIOURL* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOURL* DIODNSPROTOCOL_MITM_SERVER_XEVENT::GetAskedURL()
{
  return &asked_URL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBUFFER* DIODNSPROTOCOL_MITM_SERVER_XEVENT::GetAskedBuffer()
* @brief      Get asked buffer
* @ingroup    DATAIO
* 
* @return     XBUFFER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBUFFER* DIODNSPROTOCOL_MITM_SERVER_XEVENT::GetAskedBuffer()
{
  return &asked_buffer;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBUFFER* DIODNSPROTOCOL_MITM_SERVER_XEVENT::GetAnsweredBuffer()
* @brief      Get answered buffer
* @ingroup    DATAIO
* 
* @return     XBUFFER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBUFFER* DIODNSPROTOCOL_MITM_SERVER_XEVENT::GetAnsweredBuffer()
{
  return &answered_buffer;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOIP* DIODNSPROTOCOL_MITM_SERVER_XEVENT::GetAnsweredIP()
* @brief      Get answered IP
* @ingroup    DATAIO
* 
* @return     DIOIP* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOIP* DIODNSPROTOCOL_MITM_SERVER_XEVENT::GetAnsweredIP()
{
  return &answered_IP;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIODNSPROTOCOL_MITM_SERVER_XEVENT::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIODNSPROTOCOL_MITM_SERVER_XEVENT::Clean()
{
  
}


#pragma endregion

