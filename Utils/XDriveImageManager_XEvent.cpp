/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XDriveImageManager_XEvent.cpp
*
* @class      XDRIVEIMAGEMANAGER_XEVENT
* @brief      eXtended Drive Image Manager Event class
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

#include "XDriveImageManager_XEvent.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDRIVEIMAGEMANAGER_XEVENT::XDRIVEIMAGEMANAGER_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family)
* @brief      Constructor
* @ingroup    UTILS
*
* @param[in]  subject :
* @param[in]  type :
* @param[in]  family :
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XDRIVEIMAGEMANAGER_XEVENT::XDRIVEIMAGEMANAGER_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family) : XEVENT(subject, type, family)
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDRIVEIMAGEMANAGER_XEVENT::~XDRIVEIMAGEMANAGER_XEVENT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    UTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XDRIVEIMAGEMANAGER_XEVENT::~XDRIVEIMAGEMANAGER_XEVENT()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDRIVEIMAGEMANAGER_DRIVE* XDRIVEIMAGEMANAGER_XEVENT::GetDrive()
* @brief      GetDrive
* @ingroup    UTILS
*
* @return     XDRIVEIMAGE_DRIVE* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDRIVEIMAGEMANAGER_DRIVE* XDRIVEIMAGEMANAGER_XEVENT::GetDrive()
{
  return drive;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XDRIVEIMAGEMANAGER_XEVENT::SetDrive(XDRIVEIMAGEMANAGER_DRIVE* drive)
* @brief      SetDrive
* @ingroup    UTILS
*
* @param[in]  drive :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XDRIVEIMAGEMANAGER_XEVENT::SetDrive(XDRIVEIMAGEMANAGER_DRIVE* drive)
{
  this->drive = drive;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XQWORD XDRIVEIMAGEMANAGER_XEVENT::GetIndexSector()
* @brief      GetIndexSector
* @ingroup    UTILS
*
* @return     XQWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XQWORD XDRIVEIMAGEMANAGER_XEVENT::GetIndexSector()
{
  return indexsector;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XDRIVEIMAGEMANAGER_XEVENT::SetIndexSector(XQWORD indexsector)
* @brief      SetIndexSector
* @ingroup    UTILS
*
* @param[in]  indexsector :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XDRIVEIMAGEMANAGER_XEVENT::SetIndexSector(XQWORD indexsector)
{
  this->indexsector = indexsector;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XQWORD XDRIVEIMAGEMANAGER_XEVENT::GetNumberSectorsInOperation()
* @brief      GetNumberSectorsInOperation
* @ingroup    UTILS
*
* @return     XQWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XQWORD XDRIVEIMAGEMANAGER_XEVENT::GetNumberSectorsInOperation()
{
  return numbersectorsinoperation;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XDRIVEIMAGEMANAGER_XEVENT::SetNumberSectorsInOperation(XQWORD numbersectorsinoperation)
* @brief      SetNumberSectorsInOperation
* @ingroup    UTILS
*
* @param[in]  numbersectorsinoperation :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XDRIVEIMAGEMANAGER_XEVENT::SetNumberSectorsInOperation(XQWORD numbersectorsinoperation)
{
  this->numbersectorsinoperation = numbersectorsinoperation;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float XDRIVEIMAGEMANAGER_XEVENT::GetOperationPercent()
* @brief      GetOperationPercent
* @ingroup    UTILS
*
* @return     float :
*
* --------------------------------------------------------------------------------------------------------------------*/
float XDRIVEIMAGEMANAGER_XEVENT::GetOperationPercent()
{
  return operationpercent;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XDRIVEIMAGEMANAGER_XEVENT::SetOperationPercent(float operationpercent)
* @brief      SetOperationPercent
* @ingroup    UTILS
*
* @param[in]  operationpercent :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XDRIVEIMAGEMANAGER_XEVENT::SetOperationPercent(float operationpercent)
{
  this->operationpercent = operationpercent;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDRIVEIMAGE_ERROR XDRIVEIMAGEMANAGER_XEVENT::GetError()
* @brief      GetError
* @ingroup    UTILS
*
* @return     XDRIVEIMAGE_ERROR :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDRIVEIMAGEMANAGER_ERROR XDRIVEIMAGEMANAGER_XEVENT::GetError()
{
  return error;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XDRIVEIMAGEMANAGER_XEVENT::SetError(XDRIVEIMAGE_ERROR error)
* @brief      SetError
* @ingroup    UTILS
*
* @param[in]  error :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XDRIVEIMAGEMANAGER_XEVENT::SetError(XDRIVEIMAGEMANAGER_ERROR error)
{
  this->error = error;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XDRIVEIMAGEMANAGER_XEVENT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    UTILS
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XDRIVEIMAGEMANAGER_XEVENT::Clean()
{
  drive                     = NULL;
  indexsector               = 0;
  numbersectorsinoperation  = 0;
  operationpercent          = 0.0f;
  error                     = XDRIVEIMAGEMANAGER_ERROR_NONE;
}




