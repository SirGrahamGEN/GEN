/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       APPFlowInternetServices_XEvent.cpp
* 
* @class      APPFLOWINTERNETSERVICES_XEVENT
* @brief      Application Flow Internet Services eXtended Event class
* @ingroup    APPFLOW
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

#include "APPFlowInternetServices_XEvent.h"

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
* @fn         APPFLOWINTERNETSERVICES_XEVENT::APPFLOWINTERNETSERVICES_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family)
* @brief      Constructor
* @ingroup    APPFLOW
* 
* @param[in]  subject : 
* @param[in]  type : 
* @param[in]  family : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
APPFLOWINTERNETSERVICES_XEVENT::APPFLOWINTERNETSERVICES_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family) : XEVENT(subject, type, family)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         APPFLOWINTERNETSERVICES_XEVENT::~APPFLOWINTERNETSERVICES_XEVENT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    APPFLOW
* 
* --------------------------------------------------------------------------------------------------------------------*/
APPFLOWINTERNETSERVICES_XEVENT::~APPFLOWINTERNETSERVICES_XEVENT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         APPFLOWINTERNETSERVICES_CHECKINTERNETCONNEXION_STATE APPFLOWINTERNETSERVICES_XEVENT::GetInternetConnexionState()
* @brief      GetInternetConnexionState
* @ingroup    APPFLOW
*
* @return     APPFLOWINTERNETSERVICES_CHECKINTERNETCONNEXION_STATE : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
APPFLOWINTERNETSERVICES_CHECKINTERNETCONNEXION_STATE APPFLOWINTERNETSERVICES_XEVENT::GetInternetConnexionState()
{
  return internetconnexionstate;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPFLOWINTERNETSERVICES_XEVENT::SetInternetConnexionState(APPFLOWINTERNETSERVICES_CHECKINTERNETCONNEXION_STATE internetconnexionstate)
* @brief      SetInternetConnexionState
* @ingroup    APPFLOW
*
* @param[in]  internetconnexionstate : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void APPFLOWINTERNETSERVICES_XEVENT::SetInternetConnexionState(APPFLOWINTERNETSERVICES_CHECKINTERNETCONNEXION_STATE internetconnexionstate)
{
  this->internetconnexionstate = internetconnexionstate;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOCHECKTCPIPCONNECTION_CUT* APPFLOWINTERNETSERVICES_XEVENT::GetInternetConnextionCut()
* @brief      GetInternetConnextionCut
* @ingroup    APPFLOW
*
* @return     DIOCHECKTCPIPCONNECTION_CUT* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOCHECKTCPIPCONNECTION_CUT* APPFLOWINTERNETSERVICES_XEVENT::GetInternetConnextionCut()
{
  return internetconnectioncut;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPFLOWINTERNETSERVICES_XEVENT::SetInternetConnextionCut(DIOCHECKTCPIPCONNECTION_CUT* internetconnectioncut)
* @brief      SetInternetConnextionCut
* @ingroup    APPFLOW
*
* @param[in]  internetconnectioncut : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void APPFLOWINTERNETSERVICES_XEVENT::SetInternetConnextionCut(DIOCHECKTCPIPCONNECTION_CUT* internetconnectioncut)
{
  this->internetconnectioncut  = internetconnectioncut;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPFLOWINTERNETSERVICES_XEVENT::IsChangePublicIP()
* @brief      IsChangePublicIP
* @ingroup    APPFLOW
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWINTERNETSERVICES_XEVENT::IsChangePublicIP()
{
  return ischangepublicIP;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPFLOWINTERNETSERVICES_XEVENT::SetIsChangePublicIP(bool ischangepublicIP)
* @brief      SetIsChangePublicIP
* @ingroup    APPFLOW
* 
* @param[in]  ischangepublicIP : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APPFLOWINTERNETSERVICES_XEVENT::SetIsChangePublicIP(bool ischangepublicIP)
{
  this->ischangepublicIP = ischangepublicIP;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPFLOWINTERNETSERVICES_XEVENT::IsChangeLocalIP()
* @brief      IsChangeLocalIP
* @ingroup    APPFLOW
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWINTERNETSERVICES_XEVENT::IsChangeLocalIP()
{
  return ischangelocalIP;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPFLOWINTERNETSERVICES_XEVENT::SetIsChangeLocalIP(bool ischangelocalIP)
* @brief      SetIsChangeLocalIP
* @ingroup    APPFLOW
*
* @param[in]  ischangelocalIP : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void APPFLOWINTERNETSERVICES_XEVENT::SetIsChangeLocalIP(bool ischangelocalIP)
{
  this->ischangelocalIP = ischangelocalIP;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* APPFLOWINTERNETSERVICES_XEVENT::GetChangePublicIP()
* @brief      GetChangePublicIP
* @ingroup    APPFLOW
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPFLOWINTERNETSERVICES_XEVENT::GetChangePublicIP()
{
  return &changepublicIP;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* APPFLOWINTERNETSERVICES_XEVENT::GetChangeLocalIP()
* @brief      GetChangeLocalIP
* @ingroup    APPFLOW
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPFLOWINTERNETSERVICES_XEVENT::GetChangeLocalIP()
{
  return &changelocalIP;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD APPFLOWINTERNETSERVICES_XEVENT::GetNChangesIP()
* @brief      GetNChangesIP
* @ingroup    APPFLOW
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD APPFLOWINTERNETSERVICES_XEVENT::GetNChangesIP()
{
  return nchangesIP;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPFLOWINTERNETSERVICES_XEVENT::SetNChangesIP(XDWORD nchangesIP)
* @brief      SetNChangesIP
* @ingroup    APPFLOW
* 
* @param[in]  nchangesIP : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APPFLOWINTERNETSERVICES_XEVENT::SetNChangesIP(XDWORD nchangesIP)
{
  this->nchangesIP = nchangesIP; 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD APPFLOWINTERNETSERVICES_XEVENT::GetNChangesLocalIP()
* @brief      GetNChangesLocalIP
* @ingroup    APPFLOW
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD APPFLOWINTERNETSERVICES_XEVENT::GetNChangesLocalIP()
{
  return nchangeslocalIP;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPFLOWINTERNETSERVICES_XEVENT::SetNChangesLocalIP(XDWORD nchangeslocalIP)
* @brief      SetNChangesLocalIP
* @ingroup    APPFLOW
* 
* @param[in]  nchangeslocalIP : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APPFLOWINTERNETSERVICES_XEVENT::SetNChangesLocalIP(XDWORD nchangeslocalIP)
{
  this->nchangeslocalIP = nchangeslocalIP;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD APPFLOWINTERNETSERVICES_XEVENT::GetNChangesPublicIP()
* @brief      GetNChangesPublicIP
* @ingroup    APPFLOW
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD APPFLOWINTERNETSERVICES_XEVENT::GetNChangesPublicIP()
{
  return nchangespublicIP;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPFLOWINTERNETSERVICES_XEVENT::SetNChangesPublicIP(XDWORD nchangespublicIP)
* @brief      SetNChangesPublicIP
* @ingroup    APPFLOW
* 
* @param[in]  nchangespublicIP : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APPFLOWINTERNETSERVICES_XEVENT::SetNChangesPublicIP(XDWORD nchangespublicIP)
{
  this->nchangespublicIP = nchangespublicIP;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPFLOWINTERNETSERVICES_XEVENT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    APPFLOW
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APPFLOWINTERNETSERVICES_XEVENT::Clean()
{
  internetconnexionstate  = APPFLOWINTERNETSERVICES_CHECKINTERNETCONNEXION_STATE_NONE;
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