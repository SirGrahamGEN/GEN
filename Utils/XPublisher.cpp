/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XPublisher.cpp
*
* @class      XPUBLISHER
* @brief      eXtended Publisher class
* @ingroup    UTILS
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

#include <stdio.h>

#include "XFactory.h"
#include "XObserver.h"
#include "XTrace.h"

#include "XPublisher.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

XPUBLISHER*   XPUBLISHER::instance = NULL;

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPUBLISHERENTRY::XPUBLISHERENTRY()
* @brief      Constructor
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XPUBLISHERENTRY::XPUBLISHERENTRY()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPUBLISHERENTRY::~XPUBLISHERENTRY()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XPUBLISHERENTRY::~XPUBLISHERENTRY()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XPUBLISHERENTRY::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XPUBLISHERENTRY::Clean()
{
  type      = 0;
  subject   = NULL;
  observer  = NULL;
}



/*---------------------------------------------------------------------------------------------------------------------*/
/* XPUBLISHER                                                                                                          */
/*---------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPUBLISHER::GetIsInstanced()
* @brief      GetIsInstanced
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XPUBLISHER::GetIsInstanced()
{
  return instance != NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPUBLISHER& GEN_XPUBLISHER.
* @brief      GetInstance
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XPUBLISHER& :
*
*---------------------------------------------------------------------------------------------------------------------*/
XPUBLISHER& XPUBLISHER::GetInstance()
{
  if(!instance) instance = new XPUBLISHER();

  return (*instance);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPUBLISHER::DelInstance()
* @brief      DelInstance
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XPUBLISHER::DelInstance()
{
  if(instance)
    {
      delete instance;
      instance = NULL;

      return true;
    }

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPUBLISHER::RegisterEvent(XDWORD type, XSUBJECT* subject)
* @brief      RegisterEvent
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  type :
* @param[in]  subject :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XPUBLISHER::RegisterEvent(XDWORD type, XSUBJECT* subject)
{
  bool status = false;

  if(xmutexevents) xmutexevents->Lock();

  bool found = false;

  for(XDWORD c=0; c<subjectsmap.GetSize(); c++)
    {
      XDWORD    _type    = subjectsmap.GetKey(c);
      XSUBJECT* _subject = subjectsmap.GetElement(c);

      if((_type == type) && (_subject == subject))
        {
          found = true;
          break;
        }
    }

  if(!found) status = subjectsmap.Add(type, subject);

  if(xmutexevents) xmutexevents->UnLock();

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPUBLISHER::DeRegisterEvent(XDWORD type, XSUBJECT* subject)
* @brief      DeRegisterEvent
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  type :
* @param[in]  subject :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XPUBLISHER::DeRegisterEvent(XDWORD type, XSUBJECT* subject)
{
  bool status = false;

  if(xmutexevents) xmutexevents->Lock();

  for(XDWORD c=0; c<subjectsmap.GetSize(); c++)
    {
      XDWORD    _type    = subjectsmap.GetKey(c);
      XSUBJECT* _subject = subjectsmap.GetElement(c);

      if((_type == type) && (_subject == subject))
        {

          status = subjectsmap.Delete(type, subject);
          if(status)
            {
              XDWORD d=0;
              while(d<eventsvector.GetSize())
                {
                  XPUBLISHERENTRY* publisherentry = eventsvector.Get(d);
                  if(publisherentry)
                    {
                      if((publisherentry->type == type) && (publisherentry->subject == subject))
                        {
                          eventsvector.Delete(publisherentry);
                          delete publisherentry;

                        } else d++;

                    } else d++;
                }
            }
        }
    }

  if(xmutexevents) xmutexevents->UnLock();

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPUBLISHER::DeRegisterAllEvents()
* @brief      DeRegisterAllEvents
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XPUBLISHER::DeRegisterAllEvents()
{
  if(xmutexevents) xmutexevents->Lock();

  subjectsmap.DeleteAll();

  eventsvector.DeleteContents();
  eventsvector.DeleteAll();

  if(xmutexevents) xmutexevents->UnLock();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPUBLISHER::SubscribeEvent(XDWORD type, XSUBJECT* subject, XOBSERVER* observer)
* @brief      SubscribeEvent
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  type :
* @param[in]  subject :
* @param[in]  observer :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XPUBLISHER::SubscribeEvent(XDWORD type, XSUBJECT* subject, XOBSERVER* observer)
{
  if(!subject)  return false;
  if(!observer) return false;

  if(xmutexevents) xmutexevents->Lock();

  bool status = false;
  bool found  = false;

  for(XDWORD c=0; c<subjectsmap.GetSize(); c++)
    {
      XDWORD    _type    = subjectsmap.GetKey(c);
      XSUBJECT* _subject = subjectsmap.GetElement(c);

      if((_type == type) && (_subject == subject))
        {
          found = true;
          break;
        }
    }

  if(found)
    {
      found = false;

      for(XDWORD c=0; c<eventsvector.GetSize(); c++)
        {
          XPUBLISHERENTRY* publisherentry = eventsvector.Get(c);
          if(publisherentry)
            {
              if((publisherentry->type == type) && (publisherentry->subject == subject) && (publisherentry->observer == observer))
                {
                  found = true;
                }
            }
        }

      if(!found)
        {
          XPUBLISHERENTRY* publisherentry = new XPUBLISHERENTRY();
          if(publisherentry)
            {
              publisherentry->type     = type;
              publisherentry->subject  = subject;
              publisherentry->observer = observer;

              status = eventsvector.Add(publisherentry);
            }
        }
    }

  if(xmutexevents) xmutexevents->UnLock();

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPUBLISHER::UnSubscribeEvent(XDWORD type, XSUBJECT* subject, XOBSERVER* observer)
* @brief      UnSubscribeEvent
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  type :
* @param[in]  subject :
* @param[in]  observer :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XPUBLISHER::UnSubscribeEvent(XDWORD type, XSUBJECT* subject, XOBSERVER* observer)
{
  bool status = false;

  if(xmutexevents) xmutexevents->Lock();

  for(XDWORD c=0; c<eventsvector.GetSize(); c++)
    {
      XPUBLISHERENTRY* publisherentry = eventsvector.Get(c);
      if(publisherentry)
        {
          if((publisherentry->type == type) && (publisherentry->subject == subject) && (publisherentry->observer == observer))
            {
              eventsvector.Delete(publisherentry);
              delete publisherentry;

              status = true;
              break;
            }
        }
    }

  if(xmutexevents) xmutexevents->UnLock();

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPUBLISHER::PostEvent(XEVENT* event, XSUBJECT* subject)
* @brief      PostEvent
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  event :
* @param[in]  subject :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XPUBLISHER::PostEvent(XEVENT* event, XSUBJECT* subject)
{
  if(!on) return false;
    
  inevent = true;

  if(xmutexevents) xmutexevents->Lock();

  XVECTOR<XOBSERVER*> observers;
  
  for(XDWORD c=0; c<eventsvector.GetSize(); c++)
    {
      XPUBLISHERENTRY* publisherentry = eventsvector.Get(c);
      if(publisherentry)
        {
          if((publisherentry->type == event->GetEventType()) && (publisherentry->subject == subject))
            {
              observers.Add(publisherentry->observer);
            }
        }
    }  

  if(xmutexevents) xmutexevents->UnLock();  

  for(XDWORD c=0; c<observers.GetSize(); c++)
    {
      XOBSERVER* observer = observers.Get(c);
      if(observer) observer->HandleEvent(event);
    }

  observers.DeleteAll();


  inevent = false;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPUBLISHER::XPUBLISHER()
* @brief      Constructor
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XPUBLISHER::XPUBLISHER()

{
  Clean();

  subjectsmap.SetIsMulti(true);

  GEN_XFACTORY_CREATE(xmutexevents, Create_Mutex())
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPUBLISHER::~XPUBLISHER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XPUBLISHER::~XPUBLISHER()

{
  DeRegisterAllEvents();

  if(xmutexevents) GEN_XFACTORY.Delete_Mutex(xmutexevents);

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XPUBLISHER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XPUBLISHER::Clean()
{
  on           = true;
  inevent      = false;
  xmutexevents = NULL;
}
