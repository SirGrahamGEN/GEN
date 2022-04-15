/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XEvent.cpp
*
* @class      XEVENT
* @brief      eXtended Event base class
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

#include "XEvent.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XEVENT::XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family)
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
* @brief      Constructor
* @ingroup    UTILS
*
* @param[in]  subject :
* @param[in]   type :
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XEVENT::XEVENT(XSUBJECT* subject, XDWORD type)
{
  Clean();

  this->subject = subject;
  this->type    = type;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XEVENT::~XEVENT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    UTILS
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XEVENT::~XEVENT()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSUBJECT* XEVENT::GetSubject()
* @brief      GetSubject
* @ingroup    UTILS
*
* @return     XSUBJECT* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSUBJECT* XEVENT::GetSubject()
{
  return subject;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XEVENT::SetSubject(XSUBJECT* subject)
* @brief      SetSubject
* @ingroup    UTILS
*
* @param[in]  subject :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XEVENT::SetSubject(XSUBJECT* subject)
{
  this->subject = subject;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XEVENT::GetEventFamily()
* @brief      GetEventFamily
* @ingroup    UTILS
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD XEVENT::GetEventFamily()
{
  return family;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XEVENT::SetEventFamily(XDWORD family)
* @brief      SetEventFamily
* @ingroup    UTILS
*
* @param[in]  family :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XEVENT::SetEventFamily(XDWORD family)
{
  this->family = family;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XEVENT::GetEventType()
* @brief      GetEventType
* @ingroup    UTILS
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD XEVENT::GetEventType()
{
  return type;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XEVENT::SetEventType(XDWORD type)
* @brief      SetEventType
* @ingroup    UTILS
*
* @param[in]  type :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XEVENT::SetEventType(XDWORD type)
{
  this->type = type;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XEVENT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    UTILS
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XEVENT::Clean()
{
  family      = XEVENT_TYPE_NONE;
  type        = XEVENT_TYPE_NONE;
  subject     = NULL;
}

