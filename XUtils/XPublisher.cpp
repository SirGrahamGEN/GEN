/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XPublisher.cpp
* 
* @class      XPUBLISHER
* @brief      eXtended Utils Publisher class
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

#include "XPublisher.h"

#include <stdio.h>

#include "XFactory.h"
#include "XObserver.h"
#include "XTrace.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

XPUBLISHER*   XPUBLISHER::instance = NULL;

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


#pragma region CLASS_XPUBLISHERENTRY


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPUBLISHERENTRY::XPUBLISHERENTRY()
* @brief      Constructor of class
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XPUBLISHERENTRY::XPUBLISHERENTRY()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPUBLISHERENTRY::~XPUBLISHERENTRY()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XPUBLISHERENTRY::~XPUBLISHERENTRY()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XPUBLISHERENTRY::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XPUBLISHERENTRY::Clean()
{
  type      = 0;
  subject   = NULL;
  observer  = NULL;
}


#pragma endregion


#pragma region CLASS_XPUBLISHER


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPUBLISHER::GetIsInstanced()
* @brief      Get is instanced
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPUBLISHER::GetIsInstanced()
{
  return instance != NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XPUBLISHER& XPUBLISHER::GetInstance()
* @brief      Get instance
* @ingroup    XUTILS
* 
* @return     XPUBLISHER& : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XPUBLISHER& XPUBLISHER::GetInstance()
{
  if(!instance) instance = new XPUBLISHER();

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPUBLISHER::DelInstance()
* @brief      Del instance
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* @brief      Register event
* @ingroup    XUTILS
*
* @param[in]  type :
* @param[in]  subject :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* @brief      De register event
* @ingroup    XUTILS
*
* @param[in]  type :
* @param[in]  subject :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* @brief      De register all events
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* @brief      Subscribe event
* @ingroup    XUTILS
*
* @param[in]  type :
* @param[in]  subject :
* @param[in]  observer :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* @brief      Un subscribe event
* @ingroup    XUTILS
*
* @param[in]  type :
* @param[in]  subject :
* @param[in]  observer :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* @fn         void XPUBLISHER::Active(bool on)
* @brief      Active
* @ingroup    XUTILS
* 
* @param[in]  on : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XPUBLISHER::Active(bool on)
{ 
  this->on  = on;                   
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XPUBLISHER::IsInEvent()
* @brief      Is in event
* @ingroup    XUTILS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XPUBLISHER::IsInEvent()
{ 
  return inevent;                   
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPUBLISHER::PostEvent(XEVENT* event, XSUBJECT* subject)
* @brief      Post event
* @ingroup    XUTILS
*
* @param[in]  event :
* @param[in]  subject :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* @brief      Constructor of class
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XPUBLISHER::XPUBLISHER()
{
  Clean();

  subjectsmap.SetIsMulti(true);

  GEN_XFACTORY_CREATE(xmutexevents, Create_Mutex())
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPUBLISHER::~XPUBLISHER()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XPUBLISHER::~XPUBLISHER()
{
  DeRegisterAllEvents();

  if(xmutexevents) GEN_XFACTORY.Delete_Mutex(xmutexevents);

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XPUBLISHER::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XPUBLISHER::Clean()
{
  on           = true;
  inevent      = false;
  xmutexevents = NULL;
}


#pragma endregion


#pragma endregion

