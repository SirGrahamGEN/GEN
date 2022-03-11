/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOProtocol_ApplicationData.cpp
*
* @class      DIOPROTOCOL_APPLICATIONDATA
* @brief      Data Input/Output Application Data for Generic Binary Protocol class
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

#include "XFactory.h"

#include "DIOProtocol_ApplicationData.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOPROTOCOL_APPLICATIONDATA::DIOPROTOCOL_APPLICATIONDATA()
* @brief      Constructor
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOPROTOCOL_APPLICATIONDATA::DIOPROTOCOL_APPLICATIONDATA()
{
  Clean();

  GEN_XFACTORY_CREATE(xmutexalert, Create_Mutex())

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOPROTOCOL_APPLICATIONDATA::~DIOPROTOCOL_APPLICATIONDATA()
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
DIOPROTOCOL_APPLICATIONDATA::~DIOPROTOCOL_APPLICATIONDATA()
{
  if(xmutexalert) GEN_XFACTORY.Delete_Mutex(xmutexalert);

  Clean();
}



#ifdef DIOALERTS_ACTIVE

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOPROTOCOL_APPLICATIONDATA::AddAlert(DIOALERT& alert)
* @brief      AddAlert
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  alert :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOL_APPLICATIONDATA::AddAlert(DIOALERT& alert)
{
  bool status = false;

  if(xmutexalert) xmutexalert->Lock();

  DIOALERT* _alert = new DIOALERT();
  if(_alert)
    {
      _alert->CopyFrom(&alert);
      status = alerts.Add(_alert);
      if(!status) delete _alert;
    }

  if(xmutexalert) xmutexalert->UnLock();

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOPROTOCOL_APPLICATIONDATA::ExtractAlert(int index, DIOALERT& alert)
* @brief      ExtractAlert
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  index :
* @param[in]  alert :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOL_APPLICATIONDATA::ExtractAlert(int index, DIOALERT& alert)
{
  bool status = false;

  if(xmutexalert) xmutexalert->Lock();

  DIOALERT* _alert = alerts.Get(index);
  if(_alert)
    {
      status = alert.CopyFrom(_alert);
      if(status) alerts.Delete(_alert);
    }

  if(xmutexalert) xmutexalert->UnLock();

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOPROTOCOL_APPLICATIONDATA::DeleteAllAlerts()
* @brief      DeleteAllAlerts
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOPROTOCOL_APPLICATIONDATA::DeleteAllAlerts()
{
  bool status = false;

  if(xmutexalert) xmutexalert->Lock();

  if(!alerts.IsEmpty())
    {
      alerts.DeleteContents();
      alerts.DeleteAll();

      status = true;
    }

  if(xmutexalert) xmutexalert->UnLock();

  return status;
}


#endif


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOPROTOCOL_APPLICATIONDATA::Clean()
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
void DIOPROTOCOL_APPLICATIONDATA::Clean()
{
  protocolversion                 = 0;
  protocolsubversion              = 0;
  protocolsubversionerr           = 0;

  applicationversion              = 0;
  applicationsubversion           = 0;
  applicationsubversionerr        = 0;

  xmutexalert                     = NULL;

}




