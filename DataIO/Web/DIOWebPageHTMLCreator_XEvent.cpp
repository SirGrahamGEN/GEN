/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOWebPageHTMLCreator_XEvent.cpp
* 
* @class      DIOWEBPAGEHTMLCREATOR_XEVENT
* @brief      Data Input/Output Web Page HTML Create eXtended Event class
* @ingroup    DATAIO
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

#include "DIOWebPageHTMLCreator_XEvent.h"

#include "XString.h"
#include "XPath.h"
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
* @fn         DIOWEBPAGEHTMLCREATOR_XEVENT::DIOWEBPAGEHTMLCREATOR_XEVENT(XSUBJECT* subject, XDWORD type)
* @brief      Constructor of class
* @ingroup    DATAIO
*
* @param[in]  subject :
* @param[in]  type :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBPAGEHTMLCREATOR_XEVENT::DIOWEBPAGEHTMLCREATOR_XEVENT(XSUBJECT* subject, XDWORD type)  : XEVENT(subject,type)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBPAGEHTMLCREATOR_XEVENT::~DIOWEBPAGEHTMLCREATOR_XEVENT()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBPAGEHTMLCREATOR_XEVENT::~DIOWEBPAGEHTMLCREATOR_XEVENT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBPAGEHTMLCREATOR* DIOWEBPAGEHTMLCREATOR_XEVENT::GetPageHTMLCreator()
* @brief      Get page HTML creator
* @ingroup    DATAIO
*
* @return     DIOWEBPAGEHTMLCREATOR* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBPAGEHTMLCREATOR* DIOWEBPAGEHTMLCREATOR_XEVENT::GetPageHTMLCreator()
{
  return pageHTMLcreator;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBPAGEHTMLCREATOR_XEVENT::SetPageHTMLCreator(DIOWEBPAGEHTMLCREATOR* pageHTMLcreator)
* @brief      Set page HTML creator
* @ingroup    DATAIO
*
* @param[in]  pageHTMLcreator :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBPAGEHTMLCREATOR_XEVENT::SetPageHTMLCreator(DIOWEBPAGEHTMLCREATOR* pageHTMLcreator)
{
  this->pageHTMLcreator = pageHTMLcreator;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOWEBPAGEHTMLCREATOR_XEVENT::GetXTAG()
* @brief      Get XTAG
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOWEBPAGEHTMLCREATOR_XEVENT::GetXTAG()
{
  return &XTAG;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBPAGEHTMLCREATOR_XEVENT::SetXTAG(XSTRING* XTAG)
* @brief      Set XTAG
* @ingroup    DATAIO
*
* @param[in]  XTAG :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBPAGEHTMLCREATOR_XEVENT::SetXTAG(XSTRING* XTAG)
{
  this->XTAG = XTAG->Get();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBPAGEHTMLCREATOR_XEVENT::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBPAGEHTMLCREATOR_XEVENT::Clean()
{
  pageHTMLcreator = NULL;
}


#pragma endregion

