/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOProtocol_XEvent.cpp
* 
* @class      DIOPROTOCOL_XEVENT
* @brief      Data Input/Output eXtended event Generic Binary Protocol eXtended Event class
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

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIOProtocol_XEvent.h"

#include "DIOAlerts.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOPROTOCOL_XEVENT::DIOPROTOCOL_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family)
* @brief      Constructor
* @ingroup    DATAIO
*
* @param[in]  XSUBJECT* :
* @param[in]   XDWORD type :
* @param[in]   XDWORD family :
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOL_XEVENT::DIOPROTOCOL_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family): XEVENT(subject, type, family)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOPROTOCOL_XEVENT::~DIOPROTOCOL_XEVENT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOL_XEVENT::~DIOPROTOCOL_XEVENT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOPROTOCOL* DIOPROTOCOL_XEVENT::GetProtocol()
* @brief      GetProtocol
* @ingroup    DATAIO
*
* @return     DIOPROTOCOL* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOL* DIOPROTOCOL_XEVENT::GetProtocol()
{
  return protocol;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOPROTOCOL_XEVENT::SetProtocol(DIOPROTOCOL* protocol)
* @brief      SetProtocol
* @ingroup    DATAIO
*
* @param[in]  protocol :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOL_XEVENT::SetProtocol(DIOPROTOCOL* protocol)
{
  if(!protocol) return false;
  this->protocol = protocol;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOPROTOCOL_DIRECTION DIOPROTOCOL_XEVENT::GetDirection()
* @brief      GetDirection
* @ingroup    DATAIO
*
* @return     DIOPROTOCOL_DIRECTION :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOL_DIRECTION  DIOPROTOCOL_XEVENT::GetDirection()
{
  return direction;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOPROTOCOL_XEVENT::SetDirection(DIOPROTOCOL_DIRECTION direction)
* @brief      SetDirection
* @ingroup    DATAIO
*
* @param[in]  direction :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_XEVENT::SetDirection(DIOPROTOCOL_DIRECTION direction)
{
  this->direction = direction;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOPROTOCOL_XEVENT::GetType()
* @brief      GetType
* @ingroup    DATAIO
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOPROTOCOL_XEVENT::GetType()
{
  return type;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOPROTOCOL_XEVENT::SetType(XDWORD type)
* @brief      SetType
* @ingroup    DATAIO
*
* @param[in]  type :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_XEVENT::SetType(XDWORD type)
{
  this->type = type;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOPROTOCOL_XEVENT::GetResult()
* @brief      GetResult
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOL_XEVENT::GetResult()
{
  return result;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOPROTOCOL_XEVENT::SetResult(bool result)
* @brief      SetResult
* @ingroup    DATAIO
*
* @param[in]  result :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_XEVENT::SetResult(bool result)
{
  this->result = result;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOPROTOCOL_FILESTATUS DIOPROTOCOL_XEVENT::GetFileStatus()
* @brief      GetFileStatus
* @ingroup    DATAIO
*
* @return     DIOPROTOCOL_FILESTATUS :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOL_FILESTATUS DIOPROTOCOL_XEVENT::GetFileStatus()
{
  return filestatus;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOPROTOCOL_XEVENT::SetFileStatus(DIOPROTOCOL_FILESTATUS filestatus)
* @brief      SetFileStatus
* @ingroup    DATAIO
*
* @param[in]  filestatus :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_XEVENT::SetFileStatus(DIOPROTOCOL_FILESTATUS filestatus)
{
  this->filestatus = filestatus;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOPROTOCOL_XEVENT::FileIsSend()
* @brief      FileIsSend
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOL_XEVENT::FileIsSend()
{
  return fileissend;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOPROTOCOL_XEVENT::SetFileIsSend(bool fileissend)
* @brief      SetFileIsSend
* @ingroup    DATAIO
*
* @param[in]  fileissend :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_XEVENT::SetFileIsSend(bool fileissend)
{
  this->fileissend = fileissend;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPATH* DIOPROTOCOL_XEVENT::GetFileSource()
* @brief      GetFileSource
* @ingroup    DATAIO
*
* @return     XPATH* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XPATH* DIOPROTOCOL_XEVENT::GetFileSource()
{
  return &filesource;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOPROTOCOL_XEVENT::SetFileSource(XCHAR* filesource)
* @brief      SetFileSource
* @ingroup    DATAIO
*
* @param[in]  filesource :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOL_XEVENT::SetFileSource(XCHAR* filesource)
{
  if(!filesource) return false;
  this->filesource = filesource;
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPATH* DIOPROTOCOL_XEVENT::GetFileTarget()
* @brief      GetFileTarget
* @ingroup    DATAIO
*
* @return     XPATH* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XPATH* DIOPROTOCOL_XEVENT::GetFileTarget()
{
  return &filetarget;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOPROTOCOL_XEVENT::SetFileTarget(XCHAR* filetarget)
* @brief      SetFileTarget
* @ingroup    DATAIO
*
* @param[in]  filetarget :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOL_XEVENT::SetFileTarget(XCHAR* filetarget)
{
  if(!filetarget) return false;
  this->filetarget = filetarget;
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOPROTOCOL_XEVENT::GetFilePercent()
* @brief      GetFilePercent
* @ingroup    DATAIO
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOPROTOCOL_XEVENT::GetFilePercent()
{
  return filepercent;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOPROTOCOL_XEVENT::SetFilePercent(int filepercent)
* @brief      SetFilePercent
* @ingroup    DATAIO
*
* @param[in]  filepercent :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_XEVENT::SetFilePercent(int filepercent)
{
  this->filepercent = filepercent;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void* DIOPROTOCOL_XEVENT::GetParam1()
* @brief      GetParam1
* @ingroup    DATAIO
*
* @return     void* :
*
* --------------------------------------------------------------------------------------------------------------------*/
void* DIOPROTOCOL_XEVENT::GetParam1()
{
  return param1;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOPROTOCOL_XEVENT::SetParam1(void* param1)
* @brief      SetParam1
* @ingroup    DATAIO
*
* @param[in]  param1 :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_XEVENT::SetParam1(void* param1)
{
  this->param1 = param1;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOPROTOCOL_XEVENT::GetParam2()
* @brief      GetParam2
* @ingroup    DATAIO
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOPROTOCOL_XEVENT::GetParam2()
{
  return param2;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOPROTOCOL_XEVENT::SetParam2(XDWORD param2)
* @brief      SetParam2
* @ingroup    DATAIO
*
* @param[in]  param2 :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_XEVENT::SetParam2(XDWORD param2)
{
  this->param2 = param2;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOALERT* DIOPROTOCOL_XEVENT::GetAlert()
* @brief      GetAlert
* @ingroup    DATAIO
*
* @return     DIOALERT* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOALERT* DIOPROTOCOL_XEVENT::GetAlert()
{
  return alert;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOPROTOCOL_XEVENT::SetAlert(DIOALERT* alert)
* @brief      SetAlert
* @ingroup    DATAIO
*
* @param[in]  alert :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_XEVENT::SetAlert(DIOALERT* alert)
{
  this->alert = alert;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOPROTOCOL_XEVENT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_XEVENT::Clean()
{
  protocol    = NULL;
  direction   = DIOPROTOCOL_DIRECTION_UNKNOWN;
  type        = 0;
  result      = false;

  filestatus  = DIOPROTOCOL_FILESTATUS_UNKNOWN;
  fileissend  = false;

  filesource.Empty();
  filetarget.Empty();

  filepercent = 0;

  param1      = NULL;
  param2      = 0;

  alert       = NULL;
}


#pragma endregion

