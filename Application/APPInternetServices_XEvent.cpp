/**-------------------------------------------------------------------------------------------------------------------
*
* @file       APPInternetServices_XEvent.cpp
*
* @class      APPINTERNETSERVICES_XEVENT
* @brief      Application Internet Services eXtended Event class
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @copyright  Copyright(c) 2005 - 2020 GEN Group.
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

#include "APPInternetServices_XEvent.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPINTERNETSERVICES_XEVENT::APPINTERNETSERVICES_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family)
* @brief      Constructor
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  subject :
* @param[in]  type :
* @param[in]  family :
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
APPINTERNETSERVICES_XEVENT::APPINTERNETSERVICES_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family) : XEVENT(subject, type, family)
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPINTERNETSERVICES_XEVENT::~APPINTERNETSERVICES_XEVENT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
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
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  internetconnexionstate : 
* 
* @return     void : does not return anything. 
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
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
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
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  internetconnectioncut : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void APPINTERNETSERVICES_XEVENT::SetInternetConnextionCut(DIOCHECKTCPIPCONNECTION_CUT* internetconnectioncut)
{
  this->internetconnectioncut  = internetconnectioncut;
}
  


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPINTERNETSERVICES_XEVENT::IsChangeLocalIP()
* @brief      IsChangeLocalIP
* @ingroup    APPLICATION
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
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
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  ischangelocalIP : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void APPINTERNETSERVICES_XEVENT::SetIsChangeLocalIP(bool ischangelocalIP)
{
  this->ischangelocalIP = ischangelocalIP;
}

    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* APPINTERNETSERVICES_XEVENT::GetChangeIP()
* @brief      GetChangeIP
* @ingroup    APPLICATION
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @return     XSTRING* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPINTERNETSERVICES_XEVENT::GetChangeIP()
{
  return &changeIP;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPINTERNETSERVICES_XEVENT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void APPINTERNETSERVICES_XEVENT::Clean()
{
  internetconnexionstate  = APPINTERNETSERVICES_CHECKINTERNETCONNEXION_STATE_NONE;
  internetconnectioncut   = NULL;

  ischangelocalIP         = false;
  changeIP.Empty();
}




