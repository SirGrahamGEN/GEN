/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOApplicationUpdate_XEvent.cpp
* 
* @class      DIOAPPLICATIONUPDATE_XEVENT
* @brief      Data Input/Output Application Update eXtended Event class
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

#include "DIOApplicationUpdate_XEvent.h"

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
* @fn         DIOAPPLICATIONUPDATE_XEVENT::DIOAPPLICATIONUPDATE_XEVENT(XSUBJECT* subject, XDWORD family, XDWORD type)
* @brief      Constructor of class
* @ingroup    DATAIO
*
* @param[in]  subject :
* @param[in]  family :
* @param[in]  type :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOAPPLICATIONUPDATE_XEVENT::DIOAPPLICATIONUPDATE_XEVENT(XSUBJECT* subject, XDWORD family, XDWORD type) : XEVENT(subject, family, type)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOAPPLICATIONUPDATE_XEVENT::~DIOAPPLICATIONUPDATE_XEVENT()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOAPPLICATIONUPDATE_XEVENT::~DIOAPPLICATIONUPDATE_XEVENT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOAPPLICATIONUPDATE_VERSIONDATA* DIOAPPLICATIONUPDATE_XEVENT::GetVersionData()
* @brief      Get version data
* @ingroup    DATAIO
*
* @return     DIOAPPLICATIONUPDATE_VERSIONDATA* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOAPPLICATIONUPDATE_VERSIONDATA* DIOAPPLICATIONUPDATE_XEVENT::GetVersionData()
{
  return versiondata;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOAPPLICATIONUPDATE_XEVENT::SetVersionData(DIOAPPLICATIONUPDATE_VERSIONDATA* versiondata)
* @brief      Set version data
* @ingroup    DATAIO
*
* @param[in]  versiondata :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOAPPLICATIONUPDATE_XEVENT::SetVersionData(DIOAPPLICATIONUPDATE_VERSIONDATA* versiondata)
{
  this->versiondata = versiondata;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOAPPLICATIONUPDATE_XEVENT::GetVersionComparation()
* @brief      Get version comparation
* @ingroup    DATAIO
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOAPPLICATIONUPDATE_XEVENT::GetVersionComparation()
{
  return versioncomparation;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOAPPLICATIONUPDATE_XEVENT::SetVersionComparation(int versioncomparation);
* @brief      Set version comparation
* @ingroup    DATAIO
*
* @param[in]  versioncomparation) :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOAPPLICATIONUPDATE_XEVENT::SetVersionComparation(int versioncomparation)
{
  this->versioncomparation = versioncomparation;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XVECTOR<DIOAPPLICATIONUPDATE_FILE*>* DIOAPPLICATIONUPDATE_XEVENT::GetFilesToUpdate()
* @brief      Get files to update
* @ingroup    DATAIO
*
* @return     XVECTOR<DIOAPPLICATIONUPDATE_FILE*>* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<DIOAPPLICATIONUPDATE_FILE*>* DIOAPPLICATIONUPDATE_XEVENT::GetFilesToUpdate()
{
  return filestoupdate;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOAPPLICATIONUPDATE_XEVENT::SetFilesToUpdate(XVECTOR<DIOAPPLICATIONUPDATE_FILE*>* filestoupdate)
* @brief      Set files to update
* @ingroup    DATAIO
*
* @param[in]  filestoupdate :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOAPPLICATIONUPDATE_XEVENT::SetFilesToUpdate(XVECTOR<DIOAPPLICATIONUPDATE_FILE*>* filestoupdate)
{
  this->filestoupdate = filestoupdate;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOAPPLICATIONUPDATE_XEVENT::GetIndexOfOperation()
* @brief      Get index of operation
* @ingroup    DATAIO
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOAPPLICATIONUPDATE_XEVENT::GetIndexOfOperation()
{
  return indexoperation;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOAPPLICATIONUPDATE_XEVENT::SetIndexOfOperation(XDWORD indexoperation)
* @brief      Set index of operation
* @ingroup    DATAIO
*
* @param[in]  indexoperation :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOAPPLICATIONUPDATE_XEVENT::SetIndexOfOperation(XDWORD indexoperation)
{
  this->indexoperation = indexoperation;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOAPPLICATIONUPDATE_XEVENT::GetError()
* @brief      Get error
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOAPPLICATIONUPDATE_ERROR DIOAPPLICATIONUPDATE_XEVENT::GetError()
{
  return error;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOAPPLICATIONUPDATE_XEVENT::SetError(DIOAPPLICATIONUPDATE_ERROR error)
* @brief      Set error
* @ingroup    DATAIO
*
* @param[in]  error :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOAPPLICATIONUPDATE_XEVENT::SetError(DIOAPPLICATIONUPDATE_ERROR error)
{
  this->error = error;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOAPPLICATIONUPDATE_FILE* DIOAPPLICATIONUPDATE_XEVENT::GetActualFileToUpdate()
* @brief      Get actual file to update
* @ingroup    DATAIO
*
* @return     DIOAPPLICATIONUPDATE_FILE* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOAPPLICATIONUPDATE_FILE* DIOAPPLICATIONUPDATE_XEVENT::GetActualFileToUpdate()
{
  if(!filestoupdate) return NULL;
  return filestoupdate->Get(indexoperation);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOAPPLICATIONUPDATE_XEVENT::GetActualUnzipFileName()
* @brief      Get actual unzip file name
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOAPPLICATIONUPDATE_XEVENT::GetActualUnzipFileName()
{
  return &actualunzipfilename;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOAPPLICATIONUPDATE_XEVENT::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOAPPLICATIONUPDATE_XEVENT::Clean()
{
  versioncomparation    = 0;
  versiondata           = NULL;

  filestoupdate         = NULL;

  indexoperation        = 0;
  error                 = DIOAPPLICATIONUPDATE_NOT_ERROR;
}


#pragma endregion

