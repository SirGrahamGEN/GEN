/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       APPFlowCheckResourcesHardware_XEvent.cpp
* 
* @class      APPFLOWCHECKRESOURCESHARDWARE_XEVENT
* @brief      Application Flow Check Resources Hardware eXtended Event class
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

#include "APPFlowCheckResourcesHardware_XEvent.h"

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
* @fn         APPFLOWCHECKRESOURCESHARDWARE_XEVENT::APPFLOWCHECKRESOURCESHARDWARE_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family)
* @brief      Constructor of class
* @ingroup    APPFLOW
* 
* @param[in]  subject : 
* @param[in]  type : 
* @param[in]  family : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
APPFLOWCHECKRESOURCESHARDWARE_XEVENT::APPFLOWCHECKRESOURCESHARDWARE_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family) : XEVENT(subject, type, family)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         APPFLOWCHECKRESOURCESHARDWARE_XEVENT::~APPFLOWCHECKRESOURCESHARDWARE_XEVENT()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    APPFLOW
* 
* --------------------------------------------------------------------------------------------------------------------*/
APPFLOWCHECKRESOURCESHARDWARE_XEVENT::~APPFLOWCHECKRESOURCESHARDWARE_XEVENT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPFLOWCHECKRESOURCESHARDWARE_XEVENT::GetActualMemFree(XDWORD& memfree_inbytes, XBYTE& memfree_percent)
* @brief      Get actual mem free
* @ingroup    APPFLOW
*
* @param[in]  memfree_inbytes : 
* @param[in]  memfree_percent : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWCHECKRESOURCESHARDWARE_XEVENT::GetActualMemFree(XDWORD& memfree_inbytes, XBYTE& memfree_percent)
{
  memfree_inbytes = this->memfree_inbytes; 
  memfree_percent = this->memfree_percent;

  return true;
}
    

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPFLOWCHECKRESOURCESHARDWARE_XEVENT::SetActualMemFree(XDWORD memfree_inbytes, XBYTE memfree_percent)
* @brief      Set actual mem free
* @ingroup    APPFLOW
*
* @param[in]  memfree_inbytes : 
* @param[in]  memfree_percent : 
*
* --------------------------------------------------------------------------------------------------------------------*/
void APPFLOWCHECKRESOURCESHARDWARE_XEVENT::SetActualMemFree(XDWORD memfree_inbytes, XBYTE memfree_percent)
{
  this->memfree_inbytes = memfree_inbytes; 
  this->memfree_percent = memfree_percent;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int APPFLOWCHECKRESOURCESHARDWARE_XEVENT::GetActualTotalCPUUsage()
* @brief      Get actual total CPU usage
* @ingroup    APPFLOW
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int APPFLOWCHECKRESOURCESHARDWARE_XEVENT::GetActualTotalCPUUsage()
{
  return totalCPUusage;
}
 

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPFLOWCHECKRESOURCESHARDWARE_XEVENT::SetActualTotalCPUUsage(int& CPUusage)
* @brief      set actual total CPUusage
* @ingroup    APPFLOW
* 
* @param[in]  CPUusage : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APPFLOWCHECKRESOURCESHARDWARE_XEVENT::SetActualTotalCPUUsage(int& CPUusage)
{
  this->totalCPUusage = CPUusage;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int APPFLOWCHECKRESOURCESHARDWARE_XEVENT::GetActualAppCPUUsage()
* @brief      Get actual app CPU usage
* @ingroup    APPFLOW
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int APPFLOWCHECKRESOURCESHARDWARE_XEVENT::GetActualAppCPUUsage()
{
  return appCPUusage;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPFLOWCHECKRESOURCESHARDWARE_XEVENT::SetActualAppCPUUsage(int& CPUusage)
* @brief      set actual app CPUusage
* @ingroup    APPFLOW
* 
* @param[in]  CPUusage : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APPFLOWCHECKRESOURCESHARDWARE_XEVENT::SetActualAppCPUUsage(int& CPUusage)
{
  this->appCPUusage = CPUusage;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPFLOWCHECKRESOURCESHARDWARE_XEVENT::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    APPFLOW
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APPFLOWCHECKRESOURCESHARDWARE_XEVENT::Clean()
{
  memfree_inbytes   = 0;
  memfree_percent   = 0; 

  totalCPUusage     = 0; 
  appCPUusage       = 0; 
}


#pragma endregion
