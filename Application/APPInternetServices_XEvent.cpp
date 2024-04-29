/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       APPInternetServices_XEvent.cpp
* 
* @class      APPINTERNETSERVICES_XEVENT
* @brief      Application Internet Services eXtended Event class
* @ingroup    APPLICATION
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

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "APPInternetServices_XEvent.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         APPINTERNETSERVICES_XEVENT::APPINTERNETSERVICES_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family)
* @brief      Constructor
* @ingroup    APPLICATION
* 
* @param[in]  subject : 
* @param[in]  type : 
* @param[in]  family : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
APPINTERNETSERVICES_XEVENT::APPINTERNETSERVICES_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family) : XEVENT(subject, type, family)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         APPINTERNETSERVICES_XEVENT::~APPINTERNETSERVICES_XEVENT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    APPLICATION
* 
* --------------------------------------------------------------------------------------------------------------------*/
APPINTERNETSERVICES_XEVENT::~APPINTERNETSERVICES_XEVENT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         APPINTERNETSERVICES_CHECKINTERNETCONNEXION_STATE APPINTERNETSERVICES_XEVENT::GetInternetConnexionState()
* @brief      GetInternetConnexionState
* @ingroup    APPLICATION
*
* @return     APPINTERNETSERVICES_CHECKINTERNETCONNEXION_STATE : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
APPINTERNETSERVICES_CHECKINTERNETCONNEXION_STATE APPINTERNETSERVICES_XEVENT::GetInternetConnexionState()
{
  return internetconnexionstate;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPINTERNETSERVICES_XEVENT::SetInternetConnexionState(APPINTERNETSERVICES_CHECKINTERNETCONNEXION_STATE internetconnexionstate)
* @brief      SetInternetConnexionState
* @ingroup    APPLICATION
*
* @param[in]  internetconnexionstate : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void APPINTERNETSERVICES_XEVENT::SetInternetConnexionState(APPINTERNETSERVICES_CHECKINTERNETCONNEXION_STATE internetconnexionstate)
{
  this->internetconnexionstate = internetconnexionstate;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCHECKTCPIPCONNECTION_CUT* APPINTERNETSERVICES_XEVENT::GetInternetConnextionCut()
* @brief      GetInternetConnextionCut
* @ingroup    APPLICATION
*
* @return     DIOCHECKTCPIPCONNECTION_CUT* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOCHECKTCPIPCONNECTION_CUT* APPINTERNETSERVICES_XEVENT::GetInternetConnextionCut()
{
  return internetconnectioncut;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPINTERNETSERVICES_XEVENT::SetInternetConnextionCut(DIOCHECKTCPIPCONNECTION_CUT* internetconnectioncut)
* @brief      SetInternetConnextionCut
* @ingroup    APPLICATION
*
* @param[in]  internetconnectioncut : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void APPINTERNETSERVICES_XEVENT::SetInternetConnextionCut(DIOCHECKTCPIPCONNECTION_CUT* internetconnectioncut)
{
  this->internetconnectioncut  = internetconnectioncut;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPINTERNETSERVICES_XEVENT::IsChangePublicIP()
* @brief      IsChangePublicIP
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPINTERNETSERVICES_XEVENT::IsChangePublicIP()
{
  return ischangepublicIP;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPINTERNETSERVICES_XEVENT::SetIsChangePublicIP(bool ischangepublicIP)
* @brief      SetIsChangePublicIP
* @ingroup    APPLICATION
* 
* @param[in]  ischangepublicIP : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APPINTERNETSERVICES_XEVENT::SetIsChangePublicIP(bool ischangepublicIP)
{
  this->ischangepublicIP = ischangepublicIP;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPINTERNETSERVICES_XEVENT::IsChangeLocalIP()
* @brief      IsChangeLocalIP
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool APPINTERNETSERVICES_XEVENT::IsChangeLocalIP()
{
  return ischangelocalIP;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPINTERNETSERVICES_XEVENT::SetIsChangeLocalIP(bool ischangelocalIP)
* @brief      SetIsChangeLocalIP
* @ingroup    APPLICATION
*
* @param[in]  ischangelocalIP : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void APPINTERNETSERVICES_XEVENT::SetIsChangeLocalIP(bool ischangelocalIP)
{
  this->ischangelocalIP = ischangelocalIP;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* APPINTERNETSERVICES_XEVENT::GetChangePublicIP()
* @brief      GetChangePublicIP
* @ingroup    APPLICATION
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPINTERNETSERVICES_XEVENT::GetChangePublicIP()
{
  return &changepublicIP;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* APPINTERNETSERVICES_XEVENT::GetChangeLocalIP()
* @brief      GetChangeLocalIP
* @ingroup    APPLICATION
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPINTERNETSERVICES_XEVENT::GetChangeLocalIP()
{
  return &changelocalIP;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD APPINTERNETSERVICES_XEVENT::GetNChangesIP()
* @brief      GetNChangesIP
* @ingroup    APPLICATION
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD APPINTERNETSERVICES_XEVENT::GetNChangesIP()
{
  return nchangesIP;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPINTERNETSERVICES_XEVENT::SetNChangesIP(XDWORD nchangesIP)
* @brief      SetNChangesIP
* @ingroup    APPLICATION
* 
* @param[in]  nchangesIP : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APPINTERNETSERVICES_XEVENT::SetNChangesIP(XDWORD nchangesIP)
{
  this->nchangesIP = nchangesIP; 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD APPINTERNETSERVICES_XEVENT::GetNChangesLocalIP()
* @brief      GetNChangesLocalIP
* @ingroup    APPLICATION
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD APPINTERNETSERVICES_XEVENT::GetNChangesLocalIP()
{
  return nchangeslocalIP;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPINTERNETSERVICES_XEVENT::SetNChangesLocalIP(XDWORD nchangeslocalIP)
* @brief      SetNChangesLocalIP
* @ingroup    APPLICATION
* 
* @param[in]  nchangeslocalIP : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APPINTERNETSERVICES_XEVENT::SetNChangesLocalIP(XDWORD nchangeslocalIP)
{
  this->nchangeslocalIP = nchangeslocalIP;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD APPINTERNETSERVICES_XEVENT::GetNChangesPublicIP()
* @brief      GetNChangesPublicIP
* @ingroup    APPLICATION
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD APPINTERNETSERVICES_XEVENT::GetNChangesPublicIP()
{
  return nchangespublicIP;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPINTERNETSERVICES_XEVENT::SetNChangesPublicIP(XDWORD nchangespublicIP)
* @brief      SetNChangesPublicIP
* @ingroup    APPLICATION
* 
* @param[in]  nchangespublicIP : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APPINTERNETSERVICES_XEVENT::SetNChangesPublicIP(XDWORD nchangespublicIP)
{
  this->nchangespublicIP = nchangespublicIP;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPINTERNETSERVICES_XEVENT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    APPLICATION
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APPINTERNETSERVICES_XEVENT::Clean()
{
  internetconnexionstate  = APPINTERNETSERVICES_CHECKINTERNETCONNEXION_STATE_NONE;
  internetconnectioncut   = NULL;

  ischangepublicIP        = false;
  ischangelocalIP         = false;
  changepublicIP.Empty();
  changelocalIP.Empty();

  nchangesIP              = 0;
  nchangeslocalIP         = 0;
  nchangespublicIP        = 0;   
}


#pragma endregion