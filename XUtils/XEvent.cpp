/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XEvent.cpp
* 
* @class      XEVENT
* @brief      eXtended Utils Event base class
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

#include "XEvent.h"

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
* @fn         XEVENT::XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family)
* @brief      Constructor of class
* @ingroup    XUTILS
*
* @param[in]  subject :
* @param[in]  type :
* @param[in]  family :
*
* --------------------------------------------------------------------------------------------------------------------*/
XEVENT::XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family)
{
  Clean();

  this->subject = subject;
  this->family  = family;
  this->type    = type;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XEVENT::XEVENT(XSUBJECT* subject, XDWORD type)
* @brief      Constructor of class
* @ingroup    XUTILS
*
* @param[in]  subject :
* @param[in]   type :
*
* --------------------------------------------------------------------------------------------------------------------*/
XEVENT::XEVENT(XSUBJECT* subject, XDWORD type)
{
  Clean();

  this->subject = subject;
  this->type    = type;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XEVENT::~XEVENT()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XEVENT::~XEVENT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSUBJECT* XEVENT::GetSubject()
* @brief      Get subject
* @ingroup    XUTILS
*
* @return     XSUBJECT* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSUBJECT* XEVENT::GetSubject()
{
  return subject;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XEVENT::SetSubject(XSUBJECT* subject)
* @brief      Set subject
* @ingroup    XUTILS
*
* @param[in]  subject :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XEVENT::SetSubject(XSUBJECT* subject)
{
  this->subject = subject;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XEVENT::GetEventFamily()
* @brief      Get event family
* @ingroup    XUTILS
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XEVENT::GetEventFamily()
{
  return family;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XEVENT::SetEventFamily(XDWORD family)
* @brief      Set event family
* @ingroup    XUTILS
*
* @param[in]  family :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XEVENT::SetEventFamily(XDWORD family)
{
  this->family = family;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XEVENT::GetEventType()
* @brief      Get event type
* @ingroup    XUTILS
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XEVENT::GetEventType()
{
  return type;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XEVENT::SetEventType(XDWORD type)
* @brief      Set event type
* @ingroup    XUTILS
*
* @param[in]  type :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XEVENT::SetEventType(XDWORD type)
{
  this->type = type;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XEVENT::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XEVENT::Clean()
{
  family      = XEVENT_TYPE_NONE;
  type        = XEVENT_TYPE_NONE;
  subject     = NULL;
}


#pragma endregion

