/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOProtocol_XEvent.cpp
*
* @class      DIOPROTOCOL_XEVENT
* @brief      Data Input/Output eXtended event Generic Binary Protocol eXtended Event class
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

#include "DIOAlerts.h"

#include "DIOProtocol_XEvent.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOPROTOCOL_XEVENT::DIOPROTOCOL_XEVENT(XSUBJECT* subject, XDWORD type, XDWORD family)
* @brief      Constructor
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  XSUBJECT* :
* @param[in]   XDWORD type :
* @param[in]   XDWORD family :
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     DIOPROTOCOL* :
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  protocol :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     DIOPROTOCOL_DIRECTION :
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  direction :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  type :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  result :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     DIOPROTOCOL_FILESTATUS :
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  filestatus :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  fileissend :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XPATH* :
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  filesource :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XPATH* :
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  filetarget :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  filepercent :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void* :
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  param1 :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  param2 :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     DIOALERT* :
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  alert :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
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




