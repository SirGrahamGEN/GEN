/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOWebClient_XEvent.cpp
* 
* @class      DIOWEBCLIENT_XEVENT
* @brief      Data Input/Output Web Client Event class
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

#include "DIOWebClient_XEvent.h"

#include "XString.h"

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
* @fn         DIOWEBCLIENT_XEVENT::DIOWEBCLIENT_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family)
* @brief      Constructor of class
* @ingroup    DATAIO
*
* @param[in]  subject :
* @param[in]  type :
* @param[in]  family :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBCLIENT_XEVENT::DIOWEBCLIENT_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family): XEVENT(subject, type, family)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBCLIENT_XEVENT::~DIOWEBCLIENT_XEVENT()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBCLIENT_XEVENT::~DIOWEBCLIENT_XEVENT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOURL* DIOWEBCLIENT_XEVENT::GetURL()
* @brief      Get URL
* @ingroup    DATAIO
*
* @return     DIOURL* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOURL* DIOWEBCLIENT_XEVENT::GetURL()
{
  return &URL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBHEADER_METHOD DIOWEBCLIENT_XEVENT::GetMethod()
* @brief      Get method
* @ingroup    DATAIO
*
* @return     DIOWEBHEADER_METHOD :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBHEADER_METHOD DIOWEBCLIENT_XEVENT::GetMethod()
{
  return method;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBCLIENT_XEVENT::SetMethod(DIOWEBHEADER_METHOD method)
* @brief      Set method
* @ingroup    DATAIO
*
* @param[in]  method :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBCLIENT_XEVENT::SetMethod(DIOWEBHEADER_METHOD method)
{
  this->method = method;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRNG* DIOWEBCLIENT_XEVENT::GetEtag()
* @brief      Get etag
* @ingroup    DATAIO
*
* @return     XSTRNG* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOWEBCLIENT_XEVENT::GetEtag()
{
  return &etag;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XQWORD DIOWEBCLIENT_XEVENT::GetContentLenght()
* @brief      Get content lenght
* @ingroup    DATAIO
*
* @return     XQWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XQWORD DIOWEBCLIENT_XEVENT::GetContentLenght()
{
  return contentlenght;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBCLIENT_XEVENT::SetContentLenght(XQWORD& contentlenght)
* @brief      Set content lenght
* @ingroup    DATAIO
*
* @param[in]  contentlenght :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBCLIENT_XEVENT::SetContentLenght(XQWORD contentlenght)
{
  this->contentlenght = contentlenght;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float DIOWEBCLIENT_XEVENT::GetOperationPercent()
* @brief      Get operation percent
* @ingroup    DATAIO
*
* @return     float :
*
* --------------------------------------------------------------------------------------------------------------------*/
float DIOWEBCLIENT_XEVENT::GetOperationPercent()
{
  return operationpercent;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBCLIENT_XEVENT::SetOperationPercent(float operationpercent)
* @brief      Set operation percent
* @ingroup    DATAIO
*
* @param[in]  operationpercent :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBCLIENT_XEVENT::SetOperationPercent(float operationpercent)
{
  this->operationpercent = operationpercent;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XQWORD DIOWEBCLIENT_XEVENT::GetDownloadSize()
* @brief      Get download size
* @ingroup    DATAIO
*
* @return     XQWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XQWORD DIOWEBCLIENT_XEVENT::GetDownloadSize()
{
  return this->downloadsize;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBCLIENT_XEVENT::SetDownloadSize(XQWORD downloadsize)
* @brief      Set download size
* @ingroup    DATAIO
*
* @param[in]  downloadsize :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBCLIENT_XEVENT::SetDownloadSize(XQWORD downloadsize)
{
  this->downloadsize = downloadsize;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOWEBCLIENT_XEVENT::GetMBPSSpeed()
* @brief      Get MBPS speed
* @ingroup    DATAIO
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOWEBCLIENT_XEVENT::GetMBPSSpeed()
{
  return MBPSspeed;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBCLIENT_XEVENT::SetMBPSSpeed(XDWORD MBPSspeed)
* @brief      Set MBPS speed
* @ingroup    DATAIO
*
* @param[in]  MBPSspeed :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBCLIENT_XEVENT::SetMBPSSpeed(XDWORD MBPSspeed)
{
  this->MBPSspeed = MBPSspeed;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBCLIENT_XEVENT::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBCLIENT_XEVENT::Clean()
{
  method            = DIOWEBHEADER_METHOD_UNKNOWN;
  contentlenght     = 0;
  operationpercent  = 0.0f;
  downloadsize      = 0;
  MBPSspeed         = 0;
}


#pragma endregion

