/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XSubject.cpp
* 
* @class      XSUBJECT
* @brief      eXtended Utils Subject class
* @ingroup    XUTILS
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

#include "XSubject.h"

#include <stdio.h>

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
* @fn         XSUBJECT::XSUBJECT()
* @brief      Constructor of class
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XSUBJECT::XSUBJECT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSUBJECT::~XSUBJECT()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XSUBJECT::~XSUBJECT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSUBJECT::RegisterEvent(XDWORD type)
* @brief      Register event
* @ingroup    XUTILS
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
* @brief      De register event
* @ingroup    XUTILS
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
* @brief      De register all events
* @ingroup    XUTILS
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
* @brief      Post event
* @ingroup    XUTILS
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
* @brief      Post event
* @ingroup    XUTILS
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
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XSUBJECT::Clean()
{

}


#pragma endregion

