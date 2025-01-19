/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XDriveImageManager_XEvent.cpp
* 
* @class      XDRIVEIMAGEMANAGER_XEVENT
* @brief      eXtended Utils Drive Image Mamanger Event class
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

#include "XDriveImageManager_XEvent.h"

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
* @fn         XDRIVEIMAGEMANAGER_XEVENT::XDRIVEIMAGEMANAGER_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family)
* @brief      Constructor of class
* @ingroup    XUTILS
*
* @param[in]  subject :
* @param[in]  type :
* @param[in]  family :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDRIVEIMAGEMANAGER_XEVENT::XDRIVEIMAGEMANAGER_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family) : XEVENT(subject, type, family)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDRIVEIMAGEMANAGER_XEVENT::~XDRIVEIMAGEMANAGER_XEVENT()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XDRIVEIMAGEMANAGER_XEVENT::~XDRIVEIMAGEMANAGER_XEVENT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDRIVEIMAGEMANAGER_DRIVE* XDRIVEIMAGEMANAGER_XEVENT::GetDrive()
* @brief      Get drive
* @ingroup    XUTILS
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
* @brief      Set drive
* @ingroup    XUTILS
*
* @param[in]  drive :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XDRIVEIMAGEMANAGER_XEVENT::SetDrive(XDRIVEIMAGEMANAGER_DRIVE* drive)
{
  this->drive = drive;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XQWORD XDRIVEIMAGEMANAGER_XEVENT::GetIndexSector()
* @brief      Get index sector
* @ingroup    XUTILS
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
* @brief      Set index sector
* @ingroup    XUTILS
*
* @param[in]  indexsector :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XDRIVEIMAGEMANAGER_XEVENT::SetIndexSector(XQWORD indexsector)
{
  this->indexsector = indexsector;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XQWORD XDRIVEIMAGEMANAGER_XEVENT::GetNumberSectorsInOperation()
* @brief      Get number sectors in operation
* @ingroup    XUTILS
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
* @brief      Set number sectors in operation
* @ingroup    XUTILS
*
* @param[in]  numbersectorsinoperation :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XDRIVEIMAGEMANAGER_XEVENT::SetNumberSectorsInOperation(XQWORD numbersectorsinoperation)
{
  this->numbersectorsinoperation = numbersectorsinoperation;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float XDRIVEIMAGEMANAGER_XEVENT::GetOperationPercent()
* @brief      Get operation percent
* @ingroup    XUTILS
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
* @brief      Set operation percent
* @ingroup    XUTILS
*
* @param[in]  operationpercent :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XDRIVEIMAGEMANAGER_XEVENT::SetOperationPercent(float operationpercent)
{
  this->operationpercent = operationpercent;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDRIVEIMAGE_ERROR XDRIVEIMAGEMANAGER_XEVENT::GetError()
* @brief      Get error
* @ingroup    XUTILS
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
* @brief      Set error
* @ingroup    XUTILS
*
* @param[in]  error :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XDRIVEIMAGEMANAGER_XEVENT::SetError(XDRIVEIMAGEMANAGER_ERROR error)
{
  this->error = error;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XDRIVEIMAGEMANAGER_XEVENT::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    XUTILS
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


#pragma endregion

