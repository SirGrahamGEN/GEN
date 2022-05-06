/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XFileZIP_XEvent.cpp
*
* @class      XFILEZIP_XEVENT
* @brief      eXtended File ZIP eXtended Event class
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

#include "XFileZIP_XEvent.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEZIP_XEVENT::XFILEZIP_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family)
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
XFILEZIP_XEVENT::XFILEZIP_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family) : XEVENT(subject, type, family)
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEZIP_XEVENT::~XFILEZIP_XEVENT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    UTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEZIP_XEVENT::~XFILEZIP_XEVENT()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPATH* XFILEZIP_XEVENT::GetFileName()
* @brief      GetFileName
* @ingroup    UTILS
*
* @return     XPATH* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XPATH* XFILEZIP_XEVENT::GetFileName()
{
  return &filename;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILECMPZIP* XFILEZIP_XEVENT::GetFileCompress()
* @brief      GetFileCompress
* @ingroup    UTILS
*
* @return     XFILECMPZIP* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILECMPZIP* XFILEZIP_XEVENT::GetFileCompress()
{
  return filecmp;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILEZIP_XEVENT::SetFileCompressZIP(XFILECMPZIP* filecmp)
* @brief      SetFileCompress
* @ingroup    UTILS
*
* @param[in]  filecmpzip :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFILEZIP_XEVENT::SetFileCompress(XFILECMPZIP* filecmp)
{
  this->filecmp = filecmp;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float XFILEZIP_XEVENT::GetOperationPercent()
* @brief      GetOperationPercent
* @ingroup    UTILS
*
* @return     float :
*
* --------------------------------------------------------------------------------------------------------------------*/
float XFILEZIP_XEVENT::GetOperationPercent()
{
  return operationpercent;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILEZIP_XEVENT::SetOperationPercent(float operationpercent)
* @brief      SetOperationPercent
* @ingroup    UTILS
*
* @param[in]  operationpercent :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFILEZIP_XEVENT::SetOperationPercent(float operationpercent)
{
  this->operationpercent = operationpercent;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFILEZIP_ERROR XFILEZIP_XEVENT::GetError()
* @brief      GetError
* @ingroup    UTILS
*
* @return     XFILEZIP_ERROR :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFILEZIP_ERROR XFILEZIP_XEVENT::GetError()
{
  return error;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILEZIP_XEVENT::SetError(XFILEZIP_ERROR error)
* @brief      SetError
* @ingroup    UTILS
*
* @param[in]  error :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFILEZIP_XEVENT::SetError(XFILEZIP_ERROR error)
{
  this->error = error;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFILEZIP_XEVENT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    UTILS
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFILEZIP_XEVENT::Clean()
{
  filecmp            = NULL;
  operationpercent   = 0.0f;
  error              = XFILEZIP_ERROR_NONE;
}




