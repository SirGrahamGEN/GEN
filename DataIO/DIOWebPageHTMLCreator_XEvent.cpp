/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOWebPageHTMLCreator_XEvent.cpp
*
* @class      DIOWEBPAGEHTMLCREATOR_XEVENT
* @brief      Data Input/Output Web Page HTML Create eXtended Event class
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @copyright  Copyright(c) 2008 - 2016 GEN Group.
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

#include "XString.h"
#include "XPath.h"
#include "XEvent.h"

#include "DIOWebPageHTMLCreator_XEvent.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBPAGEHTMLCREATOR_XEVENT::DIOWEBPAGEHTMLCREATOR_XEVENT(XSUBJECT* subject, XDWORD type)
* @brief      Constructor
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  subject :
* @param[in]  type :
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOWEBPAGEHTMLCREATOR_XEVENT::DIOWEBPAGEHTMLCREATOR_XEVENT(XSUBJECT* subject, XDWORD type)  : XEVENT(subject,type)
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBPAGEHTMLCREATOR_XEVENT::~DIOWEBPAGEHTMLCREATOR_XEVENT()
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
DIOWEBPAGEHTMLCREATOR_XEVENT::~DIOWEBPAGEHTMLCREATOR_XEVENT()

{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBPAGEHTMLCREATOR* DIOWEBPAGEHTMLCREATOR_XEVENT::GetPageHTMLCreator()
* @brief      GetPageHTMLCreator
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     DIOWEBPAGEHTMLCREATOR* :
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOWEBPAGEHTMLCREATOR* DIOWEBPAGEHTMLCREATOR_XEVENT::GetPageHTMLCreator()
{
  return pageHTMLcreator;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBPAGEHTMLCREATOR_XEVENT::SetPageHTMLCreator(DIOWEBPAGEHTMLCREATOR* pageHTMLcreator)
* @brief      SetPageHTMLCreator
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  pageHTMLcreator :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOWEBPAGEHTMLCREATOR_XEVENT::SetPageHTMLCreator(DIOWEBPAGEHTMLCREATOR* pageHTMLcreator)
{
  this->pageHTMLcreator = pageHTMLcreator;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOWEBPAGEHTMLCREATOR_XEVENT::GetXTAG()
* @brief      GetXTAG
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOWEBPAGEHTMLCREATOR_XEVENT::GetXTAG()
{
  return &XTAG;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBPAGEHTMLCREATOR_XEVENT::SetXTAG(XSTRING* XTAG)
* @brief      SetXTAG
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  XTAG :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOWEBPAGEHTMLCREATOR_XEVENT::SetXTAG(XSTRING* XTAG)
{
  this->XTAG = XTAG->Get();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBPAGEHTMLCREATOR_XEVENT::Clean()
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
void DIOWEBPAGEHTMLCREATOR_XEVENT::Clean()
{
  pageHTMLcreator = NULL;
}



