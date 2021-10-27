//------------------------------------------------------------------------------------------
//  DIOSTREAMDEVICEWIFI.CPP
//
//  Data IO Stream Device Wifi class
//
//
//  @author  Abraham J. Velez
//  @version 12/3/2003
//
//  GEN  Copyright (C).  All right reserved.
//------------------------------------------------------------------------------------------


/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


//---- INCLUDES ----------------------------------------------------------------------------

#include "XConsole.h"
#include "XTrace.h"

#include "DIOStreamDeviceWifi.h"

#include "XMemory_Control.h"

//---- GENERAL VARIABLE --------------------------------------------------------------------


//---- CLASS MEMBERS -----------------------------------------------------------------------


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMDEVICEWIFI::DIOSTREAMDEVICEWIFI()
* @brief      Constructor
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMDEVICEWIFI::DIOSTREAMDEVICEWIFI()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMDEVICEWIFI::~DIOSTREAMDEVICEWIFI()
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
DIOSTREAMDEVICEWIFI::~DIOSTREAMDEVICEWIFI()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMDEVICEWIFI::HasSecurity()
* @brief      HasSecurity
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMDEVICEWIFI::HasSecurity()
{
  return hassecurity;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMDEVICEWIFI::SetHasSecurity(bool hassecurity)
* @brief      SetHasSecurity
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  hassecurity :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMDEVICEWIFI::SetHasSecurity(bool hassecurity)
{
  this->hassecurity = hassecurity;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOSTREAMDEVICEWIFI::GetTransmisionPower()
* @brief      GetTransmisionPower
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int DIOSTREAMDEVICEWIFI::GetTransmisionPower()
{
  return transmisionpower;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMDEVICEWIFI::SetTransmisionPower(int transmisionpower)
* @brief      SetTransmisionPower
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  transmisionpower :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMDEVICEWIFI::SetTransmisionPower(int transmisionpower)
{
  this->transmisionpower = transmisionpower;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMDEVICEWIFI::DebugPrintInfo()
* @brief      DebugPrintInfo
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMDEVICEWIFI::DebugPrintInfo()
{
  DIOSTREAMDEVICEIP::DebugPrintInfo();

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Has Security     : %s ")   , hassecurity?__L("Yes"):__L("No"));

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("RSSI             : %d dB") , transmisionpower);

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMDEVICEWIFI::Clean()
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
void DIOSTREAMDEVICEWIFI::Clean()
{
  hassecurity       = false;
  transmisionpower  = 0;
}

