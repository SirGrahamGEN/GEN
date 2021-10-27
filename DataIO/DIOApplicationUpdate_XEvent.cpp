/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOApplicationUpdate_XEvent.cpp
*
* @class      DIOAPPLICATIONUPDATE_XEVENT
* @brief      Data Input/Output Application Update eXtended Event class
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

#include "DIOApplicationUpdate_XEvent.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOAPPLICATIONUPDATE_XEVENT::DIOAPPLICATIONUPDATE_XEVENT(XSUBJECT* subject, XDWORD family, XDWORD type)
* @brief      Constructor
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  XSUBJECT* :
* @param[in]   XDWORD family :
* @param[in]   XDWORD type :
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOAPPLICATIONUPDATE_XEVENT::DIOAPPLICATIONUPDATE_XEVENT(XSUBJECT* subject, XDWORD family, XDWORD type) : XEVENT(subject, family, type)
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOAPPLICATIONUPDATE_XEVENT::~DIOAPPLICATIONUPDATE_XEVENT()
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
DIOAPPLICATIONUPDATE_XEVENT::~DIOAPPLICATIONUPDATE_XEVENT()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOAPPLICATIONUPDATE_VERSIONDATA* DIOAPPLICATIONUPDATE_XEVENT::GetVersionData()
* @brief      GetVersionData
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     DIOAPPLICATIONUPDATE_VERSIONDATA* :
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOAPPLICATIONUPDATE_VERSIONDATA* DIOAPPLICATIONUPDATE_XEVENT::GetVersionData()
{
  return versiondata;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOAPPLICATIONUPDATE_XEVENT::SetVersionData(DIOAPPLICATIONUPDATE_VERSIONDATA* versiondata)
* @brief      SetVersionData
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  versiondata :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOAPPLICATIONUPDATE_XEVENT::SetVersionData(DIOAPPLICATIONUPDATE_VERSIONDATA* versiondata)
{
  this->versiondata = versiondata;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOAPPLICATIONUPDATE_XEVENT::GetVersionComparation()
* @brief      GetVersionComparation
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int DIOAPPLICATIONUPDATE_XEVENT::GetVersionComparation()
{
  return versioncomparation;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOAPPLICATIONUPDATE_XEVENT::SetVersionComparation(int versioncomparation);
* @brief      SetVersionComparation
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  versioncomparation) :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOAPPLICATIONUPDATE_XEVENT::SetVersionComparation(int versioncomparation)
{
  this->versioncomparation = versioncomparation;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XVECTOR<DIOAPPLICATIONUPDATE_FILE*>* DIOAPPLICATIONUPDATE_XEVENT::GetFilesToUpdate()
* @brief      GetFilesToUpdate
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XVECTOR<DIOAPPLICATIONUPDATE_FILE*>* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XVECTOR<DIOAPPLICATIONUPDATE_FILE*>* DIOAPPLICATIONUPDATE_XEVENT::GetFilesToUpdate()
{
  return filestoupdate;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOAPPLICATIONUPDATE_XEVENT::SetFilesToUpdate(XVECTOR<DIOAPPLICATIONUPDATE_FILE*>* filestoupdate)
* @brief      SetFilesToUpdate
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  filestoupdate :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOAPPLICATIONUPDATE_XEVENT::SetFilesToUpdate(XVECTOR<DIOAPPLICATIONUPDATE_FILE*>* filestoupdate)
{
  this->filestoupdate = filestoupdate;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOAPPLICATIONUPDATE_XEVENT::GetIndexOfOperation()
* @brief      GetIndexOfOperation
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOAPPLICATIONUPDATE_XEVENT::GetIndexOfOperation()
{
  return indexoperation;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOAPPLICATIONUPDATE_XEVENT::SetIndexOfOperation(XDWORD indexoperation)
* @brief      SetIndexOfOperation
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  indexoperation :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOAPPLICATIONUPDATE_XEVENT::SetIndexOfOperation(XDWORD indexoperation)
{
  this->indexoperation = indexoperation;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOAPPLICATIONUPDATE_XEVENT::GetError()
* @brief      GetError
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOAPPLICATIONUPDATE_ERROR DIOAPPLICATIONUPDATE_XEVENT::GetError()
{
  return error;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOAPPLICATIONUPDATE_XEVENT::SetError(DIOAPPLICATIONUPDATE_ERROR error)
* @brief      SetError
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  error :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOAPPLICATIONUPDATE_XEVENT::SetError(DIOAPPLICATIONUPDATE_ERROR error)
{
  this->error = error;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOAPPLICATIONUPDATE_FILE* DIOAPPLICATIONUPDATE_XEVENT::GetActualFileToUpdate()
* @brief      GetActualFileToUpdate
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     DIOAPPLICATIONUPDATE_FILE* :
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOAPPLICATIONUPDATE_FILE* DIOAPPLICATIONUPDATE_XEVENT::GetActualFileToUpdate()
{
  if(!filestoupdate) return NULL;
  return filestoupdate->Get(indexoperation);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOAPPLICATIONUPDATE_XEVENT::GetActualUnzipFileName()
* @brief      GetActualUnzipFileName
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOAPPLICATIONUPDATE_XEVENT::GetActualUnzipFileName()
{
  return &actualunzipfilename;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOAPPLICATIONUPDATE_XEVENT::Clean()
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
void DIOAPPLICATIONUPDATE_XEVENT::Clean()
{
  versioncomparation    = 0;
  versiondata           = NULL;

  filestoupdate         = NULL;

  indexoperation        = 0;
  error                 = DIOAPPLICATIONUPDATE_NOT_ERROR;
}



