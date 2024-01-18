/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       APPUpdate.cpp
* 
* @class      APPUPDATE
* @brief      Application Update class
* @ingroup    APPLICATION
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

#include "APPUpdate.h"

#include "XFactory.h"
#include "XLog.h"
#include "XSystem.h"
#include "XScheduler_XEvent.h"
#include "XScheduler.h"

#include "DIOApplicationUpdate.h"

#include "APPBase.h"
#include "APPCFG.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

APPUPDATE* APPUPDATE::instance = NULL;

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/*---- CLASS APPUPDATE_CFG -------------------------------------------------------------------------------------------*/
#pragma region APPUPDATE_CFG                                                                                                      

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPUPDATE_CFG::APPUPDATE_CFG()
* @brief      Constructor
* @ingroup    APPLICATION
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
APPUPDATE_CFG::APPUPDATE_CFG()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPUPDATE_CFG::APPUPDATE_CFG()
* @brief      Constructor
* @ingroup    APPLICATION
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
APPUPDATE_CFG::~APPUPDATE_CFG()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOURL* APPUPDATE_CFG::GetURL()
* @brief      GetURL
* @ingroup    APPLICATION
* 
* @return     DIOURL* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOURL* APPUPDATE_CFG::GetURL()
{
  return &URL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD APPUPDATE_CFG::Get_Port()
* @brief      GetPort
* @ingroup    APPLICATION
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD APPUPDATE_CFG::Get_Port()
{
  return port;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPUPDATE_CFG::Set_Port(XDWORD port)
* @brief      SetPort
* @ingroup    APPLICATION
*
* @param[in]  port :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void APPUPDATE_CFG::Set_Port(XDWORD port)
{
  this->port = port;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOAPPLICATIONUPDATE_VERSIONDATA* APPUPDATE_CFG::GetAppVersion()
* @brief      GetAppVersion
* @ingroup    APPLICATION
*
* @return     DIOAPPLICATIONUPDATE_VERSIONDATA* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOAPPLICATIONUPDATE_VERSIONDATA* APPUPDATE_CFG::GetAppVersion()
{
  return &appversion;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* APPUPDATE_CFG::GetAppName()
* @brief      GetAppName
* @ingroup    APPLICATION
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPUPDATE_CFG::GetAppName()
{
  return &appname;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPATH* APPUPDATE_CFG::GetPathRootApp()
* @brief      GetPathRootApp
* @ingroup    APPLICATION
*
* @return     XPATH* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XPATH* APPUPDATE_CFG::GetPathRootApp()
{
  return &xpathrootapp;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPUPDATE_CFG::GetDolog()
* @brief      GetDolog
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPUPDATE_CFG::GetDolog()
{
  return dolog;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPUPDATE_CFG::SetDolog(bool dolog)
* @brief      SetDolog
* @ingroup    APPLICATION
*
* @param[in]  dolog :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void APPUPDATE_CFG::SetDolog(bool dolog)
{
  this->dolog = dolog;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPUPDATE_CFG::CopyFrom(APPUPDATE_CFG* updatecfg)
* @brief      CopyFrom
* @ingroup    APPLICATION
*
* @param[in]  updatecfg :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPUPDATE_CFG::CopyFrom(APPUPDATE_CFG* updatecfg)
{
  if(!updatecfg) return false;

  URL.Set(updatecfg->GetURL()->Get());

  port = updatecfg->Get_Port();

  appversion.SetVersion(updatecfg->GetAppVersion()->GetVersion());
  appversion.SetSubVersion(updatecfg->GetAppVersion()->GetSubVersion());
  appversion.SetSubVersionError(updatecfg->GetAppVersion()->GetSubVersionError());

  appname.Set(updatecfg->GetAppName()->Get());
  xpathrootapp.Set(updatecfg->GetPathRootApp()->Get());

  dolog = updatecfg->GetDolog();


  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPUPDATE_CFG::CopyTo(APPUPDATE_CFG* updatecfg)
* @brief      CopyTo
* @ingroup    APPLICATION
*
* @param[in]  updatecfg :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPUPDATE_CFG::CopyTo(APPUPDATE_CFG* updatecfg)
{
  if(!updatecfg) return false;

  updatecfg->GetURL()->Set(URL.Get());

  updatecfg->Set_Port(port);

  updatecfg->GetAppVersion()->SetVersion(appversion.GetVersion());
  updatecfg->GetAppVersion()->SetSubVersion(appversion.GetSubVersion());
  updatecfg->GetAppVersion()->SetSubVersionError(appversion.GetSubVersionError());

  updatecfg->GetAppName()->Set(appname.Get());
  updatecfg->GetPathRootApp()->Set(xpathrootapp.Get());

  updatecfg->SetDolog(dolog);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPUPDATE_CFG::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    APPLICATION
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void APPUPDATE_CFG::Clean()
{
  port = 0;
  dolog = false;
}

#pragma endregion


/*---- CLASS APPUPDATE -----------------------------------------------------------------------------------------------*/
#pragma region APPUPDATE


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPUPDATE::GetIsInstanced()
* @brief      GetIsInstanced
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPUPDATE::GetIsInstanced()
{
  return instance != NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPUPDATE& APPUPDATE::GetInstance()
* @brief      GetInstance
* @ingroup    APPLICATION
*
* @return     APPUPDATE& : 
*
* --------------------------------------------------------------------------------------------------------------------*/
APPUPDATE& APPUPDATE::GetInstance()
{
  if(!instance) instance = new APPUPDATE();

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPUPDATE::DelInstance()
* @brief      DelInstance
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPUPDATE::DelInstance()
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
* @fn         bool APPUPDATE::Ini(APPCFG* cfg, APPUPDATE_CFG* updatecfg)
* @brief      Ini
* @ingroup    APPLICATION
*
* @param[in]  cfg : 
* @param[in]  updatecfg : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPUPDATE::Ini(APPCFG* cfg, APPUPDATE_CFG* updatecfg)
{
  if(!cfg) return false;

  this->app_cfg = cfg;

  this->update_cfg.CopyFrom(updatecfg);

  //--------------------------------------------------------------------------------------

  if(!cfg->ApplicationUpdate_IsActive()) return true;

  //--------------------------------------------------------------------------------------

  xscheduler = new XSCHEDULER();
  if(!xscheduler) return false;

  CreateTaskUpdate();

  SubscribeEvent(XEVENT_TYPE_SCHEDULER, xscheduler);
  xscheduler->Ini();

  //--------------------------------------------------------------------------------------

  EventManager(APPUPDATE_EVENTOPERATION_REGISTER);

  dioappupdate = new DIOAPPLICATIONUPDATE(update_cfg.GetAppVersion()->GetVersion()         ,
                                          update_cfg.GetAppVersion()->GetSubVersion()      ,
                                          update_cfg.GetAppVersion()->GetSubVersionError() ,
                                          update_cfg.GetAppName()->Get(),
                                        (*update_cfg.GetPathRootApp()));

  if(!dioappupdate) return false;

  dioappupdate->EliminateOldRestorations(cfg->ApplicationUpdate_GetMaxRestorations());

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPUPDATE::EventManager(APPUPDATE_EVENTOPERATION eventoperation, XSUBJECT* xsubject, XOBSERVER* observer)
* @brief      EventManager
* @ingroup    APPLICATION
* 
* @param[in]  eventoperation : 
* @param[in]  xsubject : 
* @param[in]  observer : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPUPDATE::EventManager(APPUPDATE_EVENTOPERATION eventoperation, XSUBJECT* xsubject, XOBSERVER* observer)
{
  XDWORD events[] = {  DIOAPPLICATIONUPDATE_XEVENT_TYPE_GETVERSIONAVAILABLE                                    ,
                       DIOAPPLICATIONUPDATE_XEVENT_TYPE_CHECKVERSIONAVAILABLE                                    ,
                       DIOAPPLICATIONUPDATE_XEVENT_TYPE_DOWNLOADFILE                                           ,
                       DIOAPPLICATIONUPDATE_XEVENT_TYPE_UNZIPFILE                                              ,
                       DIOAPPLICATIONUPDATE_XEVENT_TYPE_DOWNLOADFILES                                          ,
                       DIOAPPLICATIONUPDATE_XEVENT_TYPE_BACKUPORIGINALFILE                                     ,
                       DIOAPPLICATIONUPDATE_XEVENT_TYPE_BACKUPORIGINALFILES                                    ,
                       DIOAPPLICATIONUPDATE_XEVENT_TYPE_APP_RELEASERESOURCES                                   ,
                       DIOAPPLICATIONUPDATE_XEVENT_TYPE_UPDATEFILE                                             ,
                       DIOAPPLICATIONUPDATE_XEVENT_TYPE_UPDATEEXECFILE                                         ,
                       DIOAPPLICATIONUPDATE_XEVENT_TYPE_UPDATEFILES                                            ,
                       DIOAPPLICATIONUPDATE_XEVENT_TYPE_APP_END                                                ,
                       DIOAPPLICATIONUPDATE_XEVENT_TYPE_RESTOREUPDATEFILE                                      ,
                       DIOAPPLICATIONUPDATE_XEVENT_TYPE_RESTOREUPDATEFILES                                     ,
                    };


  for(XDWORD c=0; c< sizeof(events)/sizeof(XDWORD); c++)
    {
      switch(eventoperation)
        {
          case APPUPDATE_EVENTOPERATION_REGISTER     : RegisterEvent(events[c]);                           break;
          case APPUPDATE_EVENTOPERATION_DEREGISTER   : DeRegisterEvent(events[c]);                         break;
          case APPUPDATE_EVENTOPERATION_SUBSCRIBE    : SubscribeEvent(events[c]   , xsubject, observer);   break;
          case APPUPDATE_EVENTOPERATION_UNSUBSCRIBE  : UnSubscribeEvent(events[c] , xsubject, observer);   break;
                                           default   : return false;
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPUPDATE::Do()
* @brief      Do
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPUPDATE::Do()
{
  DIOAPPLICATIONUPDATE_VERSIONDATA  applicationversiondata;
  XPATH                             xpathupdate;
  XPATH                             xpathbackup;
  XSTRING                           string;
  XSTRING                           stringresult;
  bool                              status        = false;
  XSTRING                           dir_mask;
  DIOAPPLICATIONUPDATE_ERROR        error;

  dir_mask  = DIOAPPLICATIONUPDATE_RESTOREDIR_ID;
  dir_mask += DIOAPPLICATIONUPDATE_RESTOREDIR_MASK;

  if(!dioappupdate) return false;

  if(update_cfg.GetDolog()) EventManager(APPUPDATE_EVENTOPERATION_SUBSCRIBE, dioappupdate, this);

  // --------------------------------------------------------------------------------------------
  // Get last update available
  if(dioappupdate->GetVersionAvailable((*update_cfg.GetURL()), update_cfg.Get_Port(), applicationversiondata, 20, error))
    {
      // Check last update available
      if(dioappupdate->IsNewVersion(applicationversiondata))
        {
          // Have new version available

          // Download new version to update available to subdir root/update[x.x.x] Update Version
          xpathupdate = update_cfg.GetPathRootApp()->Get();
          xpathupdate.Slash_Add();
          xpathupdate.AddFormat(dir_mask.Get() , applicationversiondata.GetVersion()
                                               , applicationversiondata.GetSubVersion()
                                               , applicationversiondata.GetSubVersionError());

          status = dioappupdate->Download((*update_cfg.GetURL()), update_cfg.Get_Port(), xpathupdate, applicationversiondata, 60, error);

          //-----------------------------------------------------------------------
          DIOAPPLICATIONUPDATE_XEVENT xevent(this, DIOAPPLICATIONUPDATE_XEVENT_TYPE_DOWNLOADFILES);

          xevent.SetVersionData(&applicationversiondata);
          xevent.SetError(error);

          PostEvent(&xevent);
          //-----------------------------------------------------------------------

          if(status)
            {
              // New version update downloaded


              //-----------------------------------------------------------------------
              // Eliminate resources APPLICATION
              { DIOAPPLICATIONUPDATE_XEVENT xevent(this, DIOAPPLICATIONUPDATE_XEVENT_TYPE_APP_RELEASERESOURCES);
                xevent.SetVersionData(&applicationversiondata);
                xevent.SetError(error);

                PostEvent(&xevent);
              }
              //-----------------------------------------------------------------------


              // Actual files to be updated available to subdir root/update[x.x.x] Actual version
              xpathbackup = update_cfg.GetPathRootApp()->Get();;
              xpathbackup.Slash_Add();

              xpathbackup.AddFormat(dir_mask.Get() , update_cfg.GetAppVersion()->GetVersion()
                                                   , update_cfg.GetAppVersion()->GetSubVersion()
                                                   , update_cfg.GetAppVersion()->GetSubVersionError());

              // Change actual files for the new version
              status = dioappupdate->ChangeFilesFromDownload(applicationversiondata, xpathupdate, xpathbackup, error);

              //-----------------------------------------------------------------------
              { DIOAPPLICATIONUPDATE_XEVENT xevent(this, DIOAPPLICATIONUPDATE_XEVENT_TYPE_UPDATEFILES);

                xevent.SetVersionData(&applicationversiondata);
                xevent.SetError(error);

                PostEvent(&xevent);
              }
              //-----------------------------------------------------------------------

              if(!status)
                {
                  status = dioappupdate->Restore(xpathbackup, error);

                  //-----------------------------------------------------------------------
                  DIOAPPLICATIONUPDATE_XEVENT xevent(this, DIOAPPLICATIONUPDATE_XEVENT_TYPE_RESTOREUPDATEFILES);

                  xevent.SetVersionData(&applicationversiondata);
                  xevent.SetError(error);

                  PostEvent(&xevent);
                 //-----------------------------------------------------------------------
                }

              if(status)
                {
                  if(applicationversiondata.SystemMustBeInit())
                    {
                      GEN_XSYSTEM.ShutDown(XSYSTEM_CHANGESTATUSTYPE_REBOOT);
                    }
                   else
                    {
                      // Exit & Restart of Application

                      DIOAPPLICATIONUPDATE_XEVENT xevent(this, DIOAPPLICATIONUPDATE_XEVENT_TYPE_APP_END);

                      xevent.SetVersionData(&applicationversiondata);
                      xevent.SetError(error);

                      PostEvent(&xevent);

                      dioappupdate->RestartApplication(error);
                    }
                }
            }
        }
    }

  if(update_cfg.GetDolog()) EventManager(APPUPDATE_EVENTOPERATION_UNSUBSCRIBE, dioappupdate, this);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPUPDATE::RestorePrevious(DIOAPPLICATIONUPDATE_ERROR& error)
* @brief      RestorePrevious
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPUPDATE::RestorePrevious()
{
  DIOAPPLICATIONUPDATE_VERSIONDATA            versiontorestore;
  XVECTOR<DIOAPPLICATIONUPDATE_VERSIONDATA*>  listversionstorestore;
  DIOAPPLICATIONUPDATE_ERROR                  error   = DIOAPPLICATIONUPDATE_NOT_ERROR;
  bool                                        status  = false;

  if(!dioappupdate) return false;

  dioappupdate->GetListOfVersionsToRestore(listversionstorestore);
  if(listversionstorestore.GetSize())
    {
      if(!dioappupdate->GetPreviousVersionToRestore(listversionstorestore, versiontorestore)) return false;
    }

   //-----------------------------------------------------------------------
   // Eliminate resources APPLICATION
   { DIOAPPLICATIONUPDATE_XEVENT xevent(this, DIOAPPLICATIONUPDATE_XEVENT_TYPE_APP_RELEASERESOURCES);

     xevent.SetVersionData(&versiontorestore);
     xevent.SetError(error);

     PostEvent(&xevent);
   }

  //-----------------------------------------------------------------------

  status = dioappupdate->Restore(versiontorestore, error);
  if(status)
    {
      DIOAPPLICATIONUPDATE_XEVENT xevent(this, DIOAPPLICATIONUPDATE_XEVENT_TYPE_APP_END);

      xevent.SetVersionData(&versiontorestore);
      xevent.SetError(error);
      PostEvent(&xevent);

      dioappupdate->RestartApplication(error);
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPUPDATE::Restore()
* @brief      Restore
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPUPDATE::Restore(DIOAPPLICATIONUPDATE_VERSIONDATA& applicationversiondata)
{
  XPATH                       xpathbackup;
  DIOAPPLICATIONUPDATE_ERROR  error   = DIOAPPLICATIONUPDATE_NOT_ERROR;
  bool                        status  = false;

  if(!dioappupdate) return false;

   //-----------------------------------------------------------------------
   // Eliminate resources APPLICATION
   { DIOAPPLICATIONUPDATE_XEVENT xevent(this, DIOAPPLICATIONUPDATE_XEVENT_TYPE_APP_RELEASERESOURCES);

     xevent.SetVersionData(&applicationversiondata);
     xevent.SetError(error);

     PostEvent(&xevent);
   }

  //-----------------------------------------------------------------------

  status = dioappupdate->Restore(applicationversiondata, error);
  if(status)
    {
      DIOAPPLICATIONUPDATE_XEVENT xevent(this, DIOAPPLICATIONUPDATE_XEVENT_TYPE_APP_END);

      xevent.SetVersionData(&applicationversiondata);
      xevent.SetError(error);
      PostEvent(&xevent);

      dioappupdate->RestartApplication(error);
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPUPDATE::End()
* @brief      End
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPUPDATE::End()
{
  //--------------------------------------------------------------------------------------

  EventManager(APPUPDATE_EVENTOPERATION_DEREGISTER);

  //--------------------------------------------------------------------------------------

  if(xscheduler)
    {
      UnSubscribeEvent(XEVENT_TYPE_SCHEDULER, xscheduler);

      xscheduler->End();
      delete xscheduler;
      xscheduler = NULL;
    }

  //--------------------------------------------------------------------------------------

  if(dioappupdate)
    {
      delete dioappupdate;
      dioappupdate = NULL;
    }

  //--------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOAPPLICATIONUPDATE* APPUPDATE::GetDIOAPPUpdate()
* @brief      GetDIOAPPUpdate
* @ingroup    APPLICATION
*
* @return     DIOAPPLICATIONUPDATE* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOAPPLICATIONUPDATE* APPUPDATE::GetDIOAPPUpdate()
{
  return dioappupdate;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPUPDATE::LogOfEvent()
* @brief      LogOfEvent
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPUPDATE::LogOfEvent(DIOAPPLICATIONUPDATE_XEVENT* event)
{
  DIOAPPLICATIONUPDATE_FILE*  updatefile = event->GetActualFileToUpdate();
  XSTRING                     string;

  switch(event->GetEventType())
    {
      case DIOAPPLICATIONUPDATE_XEVENT_TYPE_GETVERSIONAVAILABLE       : if(event->GetError() == DIOAPPLICATIONUPDATE_NOT_ERROR)
                                                                          {
                                                                            string.Format( __L("Update Version available %d.%d.%d")
                                                                                          , event->GetVersionData()->GetVersion()
                                                                                          , event->GetVersionData()->GetSubVersion()
                                                                                          , event->GetVersionData()->GetSubVersionError());
                                                                          }
                                                                         else
                                                                          {
                                                                            string.Format( __L("No version available to update"));
                                                                          }
                                                                        break;

      case DIOAPPLICATIONUPDATE_XEVENT_TYPE_CHECKVERSIONAVAILABLE     : string.Format( __L("Version %d.%d.%d is ")
                                                                                      , event->GetVersionData()->GetVersion()
                                                                                      , event->GetVersionData()->GetSubVersion()
                                                                                      , event->GetVersionData()->GetSubVersionError());

                                                                        switch(event->GetVersionComparation())
                                                                          {
                                                                            case -1 : string.Add(__L("old"));   break;
                                                                            case  0 : string.Add(__L("equal"));  break;
                                                                            case  1 : string.Add(__L("new"));    break;
                                                                          }

                                                                        if(event->GetVersionComparation() <=0) string.AddFormat(__L(". It will not be updated"));

                                                                        break;


      case DIOAPPLICATIONUPDATE_XEVENT_TYPE_DOWNLOADFILE              : if(updatefile) string.Format( __L("Download file %s (%dk).")
                                                                                                      , updatefile->GetXPathFile()->Get()
                                                                                                      , updatefile->GetSize()/1024);

                                                                        break;

      case DIOAPPLICATIONUPDATE_XEVENT_TYPE_UNZIPFILE                 : if(updatefile) string.Format( __L("Unzip file %s (%dk) -> %s.")
                                                                                                      , updatefile->GetXPathFile()->Get()
                                                                                                      , updatefile->GetSize()/1024
                                                                                                      , event->GetActualUnzipFileName()->Get());
                                                                        break;

      case DIOAPPLICATIONUPDATE_XEVENT_TYPE_DOWNLOADFILES             : string.Format(__L("Downloads file %s."), (event->GetError() == DIOAPPLICATIONUPDATE_NOT_ERROR?__L("Ok."):__L("ERROR!")));
                                                                        break;

      case DIOAPPLICATIONUPDATE_XEVENT_TYPE_BACKUPORIGINALFILE        : if(updatefile) string.Format( __L("Backup original file %s (%dk).")
                                                                                                      , updatefile->GetXPathFile()->Get()
                                                                                                      , updatefile->GetSize()/1024);
                                                                        break;

      case DIOAPPLICATIONUPDATE_XEVENT_TYPE_BACKUPORIGINALFILES       : string.Format(__L("Backup Original file %s."), (event->GetError() == DIOAPPLICATIONUPDATE_NOT_ERROR?__L("Ok."):__L("ERROR!")));
                                                                        break;

      case DIOAPPLICATIONUPDATE_XEVENT_TYPE_APP_RELEASERESOURCES      : string.Format(__L("Application release blocked resources"));
                                                                        break;


      case DIOAPPLICATIONUPDATE_XEVENT_TYPE_UPDATEFILE                : if(updatefile) string.Format( __L("Copy update file %s (%dk).")
                                                                                                      , updatefile->GetXPathFile()->Get()
                                                                                                      , updatefile->GetSize()/1024);
                                                                        break;

       case DIOAPPLICATIONUPDATE_XEVENT_TYPE_UPDATEEXECFILE           : if(updatefile) string.Format( __L("Notify update EXEC file %s (%dk).")
                                                                                                      , updatefile->GetXPathFile()->Get()
                                                                                                      , updatefile->GetSize()/1024);
                                                                        break;

      case DIOAPPLICATIONUPDATE_XEVENT_TYPE_UPDATEFILES               : string.Format(__L("Update files %s."), (event->GetError() == DIOAPPLICATIONUPDATE_NOT_ERROR?__L("Ok."):__L("ERROR!")));
                                                                        break;


      case DIOAPPLICATIONUPDATE_XEVENT_TYPE_APP_END                   : string.Format(__L("Terminate application"));
                                                                        break;

      case DIOAPPLICATIONUPDATE_XEVENT_TYPE_RESTOREUPDATEFILE         : if(updatefile) string.Format( __L("Restore file %s from backup (%dk).")
                                                                                                    , updatefile->GetXPathFile()->Get()
                                                                                                    , updatefile->GetSize()/1024);
                                                                        break;

      case DIOAPPLICATIONUPDATE_XEVENT_TYPE_RESTOREUPDATEFILES        : string.Format(__L("Restore update files %s."), (event->GetError() == DIOAPPLICATIONUPDATE_NOT_ERROR?__L("Ok."):__L("ERROR!")));
                                                                        break;
    }

  if(string.GetSize())
    {
      XLOG::GetInstance().AddEntry((event->GetError() == DIOAPPLICATIONUPDATE_NOT_ERROR)?XLOGLEVEL_INFO:XLOGLEVEL_ERROR, DIOAPPLICATIONUPDATE_LOG_SECTIONID_APPUPDATE, false, string.Get());
      return true;
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPUPDATE::APPUPDATE(XDWORD applicationversion, XDWORD applicationsubversion, XDWORD applicationerrorcontrol, XCHAR* applicationname, XPATH& xpathrootapp)
* @brief      Constructor
* @ingroup    APPLICATION
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
APPUPDATE::APPUPDATE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         APPUPDATE::~APPUPDATE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    APPLICATION
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
APPUPDATE::~APPUPDATE()
{
  End();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool APPUPDATE::CreateTaskUpdate(bool doajust)
* @brief      CreateTaskUpdate
* @ingroup    APPLICATION
*
* @param[in]  doajust :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool APPUPDATE::CreateTaskUpdate(bool doajust)
{
  if(!app_cfg) return false;

  XSCHEDULERTASK* xtask = new XSCHEDULERTASK(xscheduler);
  if(!xtask) return false;

  bool toactive = false;

  XDATETIME* GEN_XFACTORY_CREATE(start, CreateDateTime())
  XDATETIME* GEN_XFACTORY_CREATE(end, CreateDateTime())
  if(start && end)
    {
      if(!app_cfg->ApplicationUpdate_GetCheckTime()->IsEmpty())
        {
          start->Read();

          start->GetDateTimeFromString((*app_cfg->ApplicationUpdate_GetCheckTime()), XDATETIME_FORMAT_ADDTIME);
          start->SetSeconds(0);
          start->SetMilliSeconds(0);

          start->AddDays(1);

          end->Set(start);
          end->AddSeconds(5);

          xtask->SetTimeLimits(start, end);

          toactive = true;
        }
       else
        {
          int minutescadence = app_cfg->ApplicationUpdate_GetCheckCadence();
          if(minutescadence)
            {
              start->Read();

              if(doajust)
                {
                  int minutes = ((start->GetMinutes() / minutescadence) + ((start->GetMinutes() % minutescadence)?1:0)) * minutescadence;
                  if(minutes == start->GetMinutes()) minutes += minutescadence;
                  if(minutes >= 60)
                    {
                      start->AddHours(1);
                      minutes = 0;
                    }

                  start->SetMinutes(minutes);

                } else start->AddMinutes(minutescadence);

              start->SetSeconds(0);
              start->SetMilliSeconds(0);

              xtask->SetTimeLimits(start);

              toactive = true;
            }
        }
    }

  if(toactive)
    {
      xtask->SetID(APPUPDATE_TASKID_CHECKUPDATEAPPLICATION);
      xtask->SetNCycles(1);
      xtask->SetIsActive(true);

      xscheduler->Task_Add(xtask);
    }
   else delete xtask;

  GEN_XFACTORY.DeleteDateTime(start);
  GEN_XFACTORY.DeleteDateTime(end);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPUPDATE::HandleEvent_Scheduler(XSCHEDULER_XEVENT* event)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    APPLICATION
*
* @param[in]  event :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void APPUPDATE::HandleEvent_Scheduler(XSCHEDULER_XEVENT* event)
{
  switch(event->GetTask()->GetID())
    {
      case APPUPDATE_TASKID_CHECKUPDATEAPPLICATION: Do();
                                                    break;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPUPDATE::HandleEvent_ApplicationUpdate(DIOAPPLICATIONUPDATEXEVENT* event)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    APPLICATION
*
* @param[in]  event :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void APPUPDATE::HandleEvent_ApplicationUpdate(DIOAPPLICATIONUPDATE_XEVENT* event)
{
  if(update_cfg.GetDolog()) LogOfEvent(event);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPUPDATE::HandleEvent(XEVENT* xevent)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    APPLICATION
*
* @param[in]  xevent :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void APPUPDATE::HandleEvent(XEVENT* xevent)
{
  if(!xevent) return;

  switch(xevent->GetEventFamily())
    {
      case XEVENT_TYPE_SCHEDULER           : { XSCHEDULER_XEVENT* event = (XSCHEDULER_XEVENT*)xevent;
                                              if(!event) return;

                                              HandleEvent_Scheduler(event);
                                            }
                                            break;

      case XEVENT_TYPE_APPLICATIONUPDATE   : { DIOAPPLICATIONUPDATE_XEVENT* event = (DIOAPPLICATIONUPDATE_XEVENT*)xevent;
                                              if(!event) return;

                                              HandleEvent_ApplicationUpdate(event);
                                            }
                                            break;
    }

}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void APPUPDATE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    APPLICATION
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void APPUPDATE::Clean()
{
  xscheduler    = NULL;
  dioappupdate  = NULL;

  app_cfg       = NULL;
}

#pragma endregion


#pragma endregion

