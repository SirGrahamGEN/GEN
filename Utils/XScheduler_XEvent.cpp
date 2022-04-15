/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XScheduler_XEvent.cpp
*
* @class      XSCHEDULER_XEVENT
* @brief      eXtended Scheduler eXtended Event class
* @ingroup    UTILS
*
* @copyright  GEN Group. All right reserved.
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

#include "XScheduler_XEvent.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSCHEDULER_XEVENT::XSCHEDULER_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family)
* @brief      Constructor
* @ingroup    UTILS
*
* @param[in]  subject :
* @param[in]  type :
* @param[in]  family :
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XSCHEDULER_XEVENT::XSCHEDULER_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family) : XEVENT(subject, type, family)
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSCHEDULER_XEVENT::~XSCHEDULER_XEVENT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    UTILS
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XSCHEDULER_XEVENT::~XSCHEDULER_XEVENT()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSCHEDULER* XSCHEDULER_XEVENT::GetScheduler()
* @brief      GetScheduler
* @ingroup    UTILS
*
* @return     XSCHEDULER* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSCHEDULER*  XSCHEDULER_XEVENT::GetScheduler()
{
  return xscheduler;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSCHEDULER_XEVENT::SetScheduler(XSCHEDULER* xscheduler)
* @brief      SetScheduler
* @ingroup    UTILS
*
* @param[in]  xscheduler :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XSCHEDULER_XEVENT::SetScheduler(XSCHEDULER* xscheduler)
{
  this->xscheduler = xscheduler;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSCHEDULERTASK* XSCHEDULER_XEVENT::GetTask()
* @brief      GetTask
* @ingroup    UTILS
*
* @return     XSCHEDULERTASK* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSCHEDULERTASK* XSCHEDULER_XEVENT::GetTask()
{
  return xtask;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSCHEDULER_XEVENT::SetTask(XSCHEDULERTASK* xtask)
* @brief      SetTask
* @ingroup    UTILS
*
* @param[in]  xtask :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XSCHEDULER_XEVENT::SetTask(XSCHEDULERTASK* xtask)
{
  this->xtask = xtask;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDATETIME* XSCHEDULER_XEVENT::GetDateTime()
* @brief      GetDateTime
* @ingroup    UTILS
*
* @return     XDATETIME* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDATETIME* XSCHEDULER_XEVENT::GetDateTime()
{
  return xdatetime;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSCHEDULER_XEVENT::SetDateTime(XDATETIME* xdatetime)
* @brief      SetDateTime
* @ingroup    UTILS
*
* @param[in]  xdatetime :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XSCHEDULER_XEVENT::SetDateTime(XDATETIME* xdatetime)
{
  this->xdatetime = xdatetime;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSCHEDULER_XEVENT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    UTILS
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XSCHEDULER_XEVENT::Clean()
{
  xscheduler  = NULL;
  xtask       = NULL;
  xdatetime   = NULL;
  xtimer      = NULL;
}


