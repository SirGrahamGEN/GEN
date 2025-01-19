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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIOProtocol_XEvent.h"

#include "DIOAlerts.h"

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
* @fn         DIOPROTOCOL_XEVENT::DIOPROTOCOL_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family)
* @brief      Constructor of class
* @ingroup    DATAIO
*
* @param[in]  subject :
* @param[in]  family :
* @param[in]  type :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOL_XEVENT::DIOPROTOCOL_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family): XEVENT(subject, type, family)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOPROTOCOL_XEVENT::~DIOPROTOCOL_XEVENT()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOL_XEVENT::~DIOPROTOCOL_XEVENT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOPROTOCOL* DIOPROTOCOL_XEVENT::GetProtocol()
* @brief      Get protocol
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
* @brief      Set protocol
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
* @brief      Get direction
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
* @brief      Set direction
* @ingroup    DATAIO
*
* @param[in]  direction :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_XEVENT::SetDirection(DIOPROTOCOL_DIRECTION direction)
{
  this->direction = direction;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOPROTOCOL_XEVENT::GetType()
* @brief      Get type
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
* @brief      Set type
* @ingroup    DATAIO
*
* @param[in]  type :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_XEVENT::SetType(XDWORD type)
{
  this->type = type;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOPROTOCOL_XEVENT::GetResult()
* @brief      Get result
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
* @brief      Set result
* @ingroup    DATAIO
*
* @param[in]  result :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_XEVENT::SetResult(bool result)
{
  this->result = result;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOPROTOCOL_FILESTATUS DIOPROTOCOL_XEVENT::GetFileStatus()
* @brief      Get file status
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
* @brief      Set file status
* @ingroup    DATAIO
*
* @param[in]  filestatus :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_XEVENT::SetFileStatus(DIOPROTOCOL_FILESTATUS filestatus)
{
  this->filestatus = filestatus;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOPROTOCOL_XEVENT::FileIsSend()
* @brief      File is send
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
* @brief      Set file is send
* @ingroup    DATAIO
*
* @param[in]  fileissend :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_XEVENT::SetFileIsSend(bool fileissend)
{
  this->fileissend = fileissend;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPATH* DIOPROTOCOL_XEVENT::GetFileSource()
* @brief      Get file source
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
* @brief      Set file source
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
* @brief      Get file target
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
* @brief      Set file target
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
* @brief      Get file percent
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
* @brief      Set file percent
* @ingroup    DATAIO
*
* @param[in]  filepercent :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_XEVENT::SetFilePercent(int filepercent)
{
  this->filepercent = filepercent;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void* DIOPROTOCOL_XEVENT::GetParam1()
* @brief      Get param1
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
* @brief      Set param1
* @ingroup    DATAIO
*
* @param[in]  param1 :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_XEVENT::SetParam1(void* param1)
{
  this->param1 = param1;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOPROTOCOL_XEVENT::GetParam2()
* @brief      Get param2
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
* @brief      Set param2
* @ingroup    DATAIO
*
* @param[in]  param2 :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_XEVENT::SetParam2(XDWORD param2)
{
  this->param2 = param2;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOALERT* DIOPROTOCOL_XEVENT::GetAlert()
* @brief      Get alert
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
* @brief      Set alert
* @ingroup    DATAIO
*
* @param[in]  alert :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPROTOCOL_XEVENT::SetAlert(DIOALERT* alert)
{
  this->alert = alert;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOPROTOCOL_XEVENT::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
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

