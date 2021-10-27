/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOWebClient_XEvent.cpp
*
* @class      DIOWEBCLIENT_XEVENT
* @brief      Data Input/Output Web Client Event class
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

#include "DIOWebClient_XEvent.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/





/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBCLIENT_XEVENT::DIOWEBCLIENT_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family)
* @brief      Constructor
* @ingroup    DATAIO
*
* @author
* @date       01/03/2016 12:00
*
* @param[in]  XSUBJECT* :
* @param[in]   XDWORD type :
* @param[in]   XDWORD family :
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOWEBCLIENT_XEVENT::DIOWEBCLIENT_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family): XEVENT(subject, type, family)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBCLIENT_XEVENT::~DIOWEBCLIENT_XEVENT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @author
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOWEBCLIENT_XEVENT::~DIOWEBCLIENT_XEVENT()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOURL* DIOWEBCLIENT_XEVENT::GetURL()
* @brief      GetURL
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     DIOURL* :
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOURL* DIOWEBCLIENT_XEVENT::GetURL()
{
  return &URL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBHEADER_METHOD DIOWEBCLIENT_XEVENT::GetMethod()
* @brief      GetMethod
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     DIOWEBHEADER_METHOD :
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOWEBHEADER_METHOD DIOWEBCLIENT_XEVENT::GetMethod()
{
  return method;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBCLIENT_XEVENT::SetMethod(DIOWEBHEADER_METHOD method)
* @brief      SetMethod
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  method :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOWEBCLIENT_XEVENT::SetMethod(DIOWEBHEADER_METHOD method)
{
  this->method = method;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRNG* DIOWEBCLIENT_XEVENT::GetEtag()
* @brief      GetEtag
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XSTRNG* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOWEBCLIENT_XEVENT::GetEtag()
{
  return &etag;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XQWORD DIOWEBCLIENT_XEVENT::GetContentLenght()
* @brief      GetContentLenght
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XQWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XQWORD DIOWEBCLIENT_XEVENT::GetContentLenght()
{
  return contentlenght;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBCLIENT_XEVENT::SetContentLenght(XQWORD& contentlenght)
* @brief      SetContentLenght
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  contentlenght :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOWEBCLIENT_XEVENT::SetContentLenght(XQWORD contentlenght)
{
  this->contentlenght = contentlenght;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float DIOWEBCLIENT_XEVENT::GetOperationPercent()
* @brief      GetOperationPercent
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     float :
*
*---------------------------------------------------------------------------------------------------------------------*/
float DIOWEBCLIENT_XEVENT::GetOperationPercent()
{
  return operationpercent;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBCLIENT_XEVENT::SetOperationPercent(float operationpercent)
* @brief      SetOperationPercent
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  operationpercent :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOWEBCLIENT_XEVENT::SetOperationPercent(float operationpercent)
{
  this->operationpercent = operationpercent;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XQWORD DIOWEBCLIENT_XEVENT::GetDownloadSize()
* @brief      GetDownloadSize
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XQWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XQWORD DIOWEBCLIENT_XEVENT::GetDownloadSize()
{
  return this->downloadsize;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBCLIENT_XEVENT::SetDownloadSize(XQWORD downloadsize)
* @brief      SetDownloadSize
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  downloadsize :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOWEBCLIENT_XEVENT::SetDownloadSize(XQWORD downloadsize)
{
  this->downloadsize = downloadsize;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOWEBCLIENT_XEVENT::GetMBPSSpeed()
* @brief      GetMBPSSpeed
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOWEBCLIENT_XEVENT::GetMBPSSpeed()
{
  return MBPSspeed;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBCLIENT_XEVENT::SetMBPSSpeed(XDWORD MBPSspeed)
* @brief      SetMBPSSpeed
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  MBPSspeed :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOWEBCLIENT_XEVENT::SetMBPSSpeed(XDWORD MBPSspeed)
{
  this->MBPSspeed = MBPSspeed;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBCLIENT_XEVENT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @author
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOWEBCLIENT_XEVENT::Clean()
{
  method            = DIOWEBHEADER_METHOD_UNKNOWN;
  contentlenght     = 0;
  operationpercent  = 0.0f;
  downloadsize      = 0;
  MBPSspeed         = 0;
}

