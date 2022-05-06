/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XSubject.cpp
*
* @class      XSUBJECT
* @brief      eXtended Subject class
* @ingroup    UTILS
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

#include "XSubject.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSUBJECT::XSUBJECT()
* @brief      Constructor
* @ingroup    UTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XSUBJECT::XSUBJECT()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSUBJECT::~XSUBJECT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    UTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XSUBJECT::~XSUBJECT()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSUBJECT::RegisterEvent(XDWORD type)
* @brief      RegisterEvent
* @ingroup    UTILS
*
* @param[in]  type :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSUBJECT::RegisterEvent(XDWORD type)
{
  return GEN_XPUBLISHER.RegisterEvent(type, this);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSUBJECT::DeRegisterEvent(XDWORD type)
* @brief      DeRegisterEvent
* @ingroup    UTILS
*
* @param[in]  type :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSUBJECT::DeRegisterEvent(XDWORD type)
{
  return GEN_XPUBLISHER.DeRegisterEvent(type, this);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSUBJECT::DeRegisterAllEvents()
* @brief      DeRegisterAllEvents
* @ingroup    UTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSUBJECT::DeRegisterAllEvents()
{
  return GEN_XPUBLISHER.DeRegisterAllEvents();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSUBJECT::PostEvent(XEVENT* event)
* @brief      PostEvent
* @ingroup    UTILS
*
* @param[in]  event :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSUBJECT::PostEvent(XEVENT* event)
{
  return GEN_XPUBLISHER.PostEvent(event, this);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSUBJECT::PostEvent(XEVENT* event, XSUBJECT* xsubject)
* @brief      PostEvent
* @ingroup    UTILS
*
* @param[in]  event :
* @param[in]  xsubject :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSUBJECT::PostEvent(XEVENT* event, XSUBJECT* xsubject)
{
  return GEN_XPUBLISHER.PostEvent(event, xsubject);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSUBJECT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    UTILS
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XSUBJECT::Clean()
{

}

