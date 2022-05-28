/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOSSHReverse.cpp
* 
* @class      DIOSSHREVERSE
* @brief      Data Input/Output SSH reverse.
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XThreadCollected.h"

#include "DIOFactory.h"
#include "DIOURL.h"
#include "DIOWebClient.h"

#include "DIOSSHReverse.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

DIOSSHREVERSE* DIOSSHREVERSE::instance = NULL;

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSSHREVERSE::GetIsInstanced()
* @brief      GetIsInstanced
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSSHREVERSE::GetIsInstanced()
{
  return instance!=NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOSSHREVERSE& DIOSSHREVERSE::GetInstance()
* @brief      GetInstance
* @ingroup    DATAIO
* 
* @return     DIOSSHREVERSE& : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOSSHREVERSE& DIOSSHREVERSE::GetInstance()
{
  if(!instance) instance = new DIOSSHREVERSE();

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSSHREVERSE::DelInstance()
* @brief      DelInstance
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSSHREVERSE::DelInstance()
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
* @fn         XSTRING* DIOSSHREVERSE::GetURLTarget()
* @brief      GetURLTarget
* @ingroup    DATAIO
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOSSHREVERSE::GetURLTarget()
{ 
  return &URLtarget;                                            
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* DIOSSHREVERSE::GetLocalIP()
* @brief      GetLocalIP
* @ingroup    DATAIO
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOSSHREVERSE::GetLocalIP()
{ 
  return &localIP;                                              
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* DIOSSHREVERSE::GetLogin()
* @brief      GetLogin
* @ingroup    DATAIO
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOSSHREVERSE::GetLogin()
{ 
  return &login;                                                
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* DIOSSHREVERSE::GetPassword()
* @brief      GetPassword
* @ingroup    DATAIO
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOSSHREVERSE::GetPassword()
{ 
  return &password;                                             
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIOSSHREVERSE::GetPort()
* @brief      GetPort
* @ingroup    DATAIO
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSSHREVERSE::GetPort()
{ 
  return port;                                                  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOSSHREVERSE::SetPort(XDWORD port)
* @brief      SetPort
* @ingroup    DATAIO
* 
* @param[in]  port : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSSHREVERSE::SetPort(XDWORD port)
{ 
  this->port = port;                                            
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSSHREVERSE::DownloadCFG(XCHAR* URL, XSTRING& publicIP, XSTRING& localIP)
* @brief      DownloadCFG
* @ingroup    DATAIO
* 
* @param[in]  URL : 
* @param[in]  publicIP : 
* @param[in]  localIP : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSSHREVERSE::DownloadCFG(XCHAR* URL, XSTRING& publicIP, XSTRING& localIP)
{
  if(!URL)   return false;

  XBUFFER xbuffer;
  DIOURL  _URL;
  bool    status  = false;
  bool    result  = false;

  DIOWEBCLIENT* webclient = new DIOWEBCLIENT();
  if(!webclient)  return false;

  _URL.Set(URL);
  _URL.Slash_Add();
  _URL.Add(DIOSSHREVERSE_CFGREMOTENAMEFILE);

  status = webclient->Get(_URL, xbuffer, NULL, 3);
  if(status)
    {
      XFILEINI* fileini = new XFILEINI();
      if(fileini)
        {
          status = fileini->AddBufferLines(XFILETXTFORMATCHAR_ASCII, xbuffer);
          if(status)
            {
              status = fileini->ConvertFromLines();
              if(status)
                {
                  int c = 1;
                  while(1)
                    {
                      XSTRING section;
                      XSTRING value;

                      section.Format(__L("ENTRY%02d"), c);

                      if(!fileini->SelectSection(section)) break;

                      status = fileini->ReadValue(__L("isactive"), value);
                      if(status)
                        {
                          if(!value.Compare(__L("yes"), true))
                            {
                              DIOURL* urlorigin = new DIOURL();
                              if(urlorigin)
                                {
                                  XSTRING _publicIP;
                                  XSTRING _localremoteIP;

                                  status = fileini->ReadValue(__L("urlorigin"), (*urlorigin));
                                  if(status)
                                    {
                                      bool validaccess = false;

                                      urlorigin->ResolveURL(_publicIP);

                                      if(!publicIP.Compare(_publicIP))
                                        {
                                          validaccess = true;

                                          status = fileini->ReadValue(__L("localremoteip"), _localremoteIP);
                                          if(status)
                                            {
                                              if(_localremoteIP.GetSize())
                                                {
                                                  if(_localremoteIP.Compare(localIP)) validaccess = false;
                                                }
                                            }
                                        }

                                      if(validaccess)
                                        {
                                          localIP   = __L("localhost");

                                          status = fileini->ReadValue(__L("urltarget"), value);
                                          if(status) GetURLTarget()->Set(value);

                                          status = fileini->ReadValue(__L("localip"), value);
                                          if(status)  GetLocalIP()->Set(value);

                                          status = fileini->ReadValue(__L("login"), value);
                                          if(status) GetLogin()->Set(value);

                                          status = fileini->ReadValue(__L("password"), value);
                                          if(status) GetPassword()->Set(value);

                                          status = fileini->ReadValue(__L("port"), value);
                                          if(status) SetPort(value.ConvertToInt());

                                          result = true;
                                        }
                                    }

                                  delete urlorigin;
                                }
                            }
                        }

                      c++;
                    }
                }
            }

          delete fileini;
        }
    }

  delete webclient;

  return result;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSSHREVERSE::DownloadCFG(XSTRING& URL, XSTRING& publicIP, XSTRING& localIP)
* @brief      DownloadCFG
* @ingroup    DATAIO
* 
* @param[in]  URL : 
* @param[in]  publicIP : 
* @param[in]  localIP : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSSHREVERSE::DownloadCFG(XSTRING& URL, XSTRING& publicIP, XSTRING& localIP)
{
  return DownloadCFG(URL.Get(), publicIP, localIP);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSSHREVERSE::DownloadCFG(DIOURL& URL, XSTRING& publicIP, XSTRING& localIP)
* @brief      DownloadCFG
* @ingroup    DATAIO
* 
* @param[in]  URL : 
* @param[in]  publicIP : 
* @param[in]  localIP : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSSHREVERSE::DownloadCFG(DIOURL&  URL, XSTRING& publicIP, XSTRING& localIP)
{
  return DownloadCFG(URL.Get(), publicIP, localIP);
}
 

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSSHREVERSE::Activate()
* @brief      Activate
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSSHREVERSE::Activate()
{
  XSTRING command;
  XSTRING output;
  bool    status     = false;
  int     returncode = 0;

  //command.AddFormat(__L("%s -p %s ssh -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no -o ExitOnForwardFailure=yes -N -R %d:%s:%d %s@%s &"), DIOSSHREVERSE_DEFAULTAPPLICATION, password.Get(), port, localIP.Get() ,DIOSSHREVERSE_DEFAULTPORTSSH, login.Get(), URLtarget.Get());
  command.AddFormat(__L("%s -p %s autossh -M 0 -o \"ServerAliveInterval 30\" -o \"ServerAliveCountMax 3\" -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no -o ExitOnForwardFailure=yes -N -R %d:%s:%d %s@%s &"), DIOSSHREVERSE_DEFAULTAPPLICATION, password.Get(), port, localIP.Get() ,DIOSSHREVERSE_DEFAULTPORTSSH, login.Get(), URLtarget.Get());
  status = GEN_XPROCESSMANAGER.MakeCommand(command.Get(), output, &returncode);

  XTIMER* GEN_XFACTORY_CREATE(xtimerout, CreateTimer())
  if(xtimerout)
    {
      while(1)
        {
          if(IsRunning())
            {
              status = true;
              break;
            }

          GEN_XSLEEP.MilliSeconds(500);

          if(xtimerout->GetMeasureSeconds()>5) break;
        }
    }

  GEN_XLOG.AddEntry((status?XLOGLEVEL_INFO:XLOGLEVEL_ERROR), DIOSSHREVERSE_LOGSECTIONID, false, __L("Activate service return code [%d]"), returncode);

  return status;
}
   

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSSHREVERSE::DeActivate()
* @brief      DeActivate
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSSHREVERSE::DeActivate()
{
  XSTRING command;
  XSTRING output;
  bool    status     = false;
  int     returncode = 0;

  command.Format(__L("killall -9 %s > /dev/null"), DIOSSHREVERSE_DEFAULTAPPLICATION);
  status = GEN_XPROCESSMANAGER.MakeCommand(command.Get(), output, &returncode);

  command.Format(__L("killall -9 %s > /dev/null"), DIOSSHREVERSE_DEFAULTAPPLICATION2);
  status = GEN_XPROCESSMANAGER.MakeCommand(command.Get(), output,&returncode);

  GEN_XLOG.AddEntry((status?XLOGLEVEL_INFO:XLOGLEVEL_ERROR), DIOSSHREVERSE_LOGSECTIONID, false, __L("Deactivate service return code [%d]"), returncode);

  status = true;
  if(returncode) status = false;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSSHREVERSE::IsRunning()
* @brief      IsRunning
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSSHREVERSE::IsRunning()
{

  bool status = false;

  //status = xsystem->IsApplicationRunning(DIOSSHREVERSE_DEFAULTAPPLICATION);
  //if(status)
    {
      //status = false;

      XSTRING command;
      XSTRING output;
      XSTRING publicIPtarget;
      int     returncode = 0;

      DIOURL* URLpublic = new DIOURL();
      if(URLpublic)
        {
          URLpublic->Set(URLtarget.Get());
          URLpublic->ResolveURL(publicIPtarget);

          delete URLpublic;
        }

      if(!publicIPtarget.IsEmpty())
        {
          XPATH   xpath;
          GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpath);
          xpath.Slash_Add();
          xpath.Add(__L("backscreen"));

          command.Format(__L("netstat -napt > %s"), xpath.Get());
          if(GEN_XPROCESSMANAGER.MakeCommand(command.Get(), output, &returncode))
            {
              XFILETXT* xfiletxt = new XFILETXT();
              if(xfiletxt)
                {
                  if(xfiletxt->Open(xpath, true))
                    {
                      if(xfiletxt->ReadAllFile())
                        {
                          for(int c=0; c<xfiletxt->GetNLines(); c++)
                            {
                              if(xfiletxt->GetLine(c))
                                {
                                  XSTRING* line = xfiletxt->GetLine(c);
                                  if(line)
                                    {
                                      XSTRING application;

                                      application = __L("/ssh ");

                                      if((line->Find(publicIPtarget.Get() , false, 0) != XSTRING_NOTFOUND) &&
                                         (line->Find(__L("ESTABLISHED")   , false, 0) != XSTRING_NOTFOUND) &&
                                         (line->Find(application.Get()    , false, 0) != XSTRING_NOTFOUND))
                                        {
                                          status = true;
                                          break;
                                        }
                                    }
                                }
                            }
                        }

                      xfiletxt->Close();
                    }

                  xfiletxt->GetPrimaryFile()->Erase(xpath);

                  delete xfiletxt;
                }
            }
        }
    }

  GEN_XLOG.AddEntry(XLOGLEVEL_INFO, DIOSSHREVERSE_LOGSECTIONID, false, __L("Check is active: %s"), status?__L("yes"):__L("no"));

  return status;
}
  

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSSHREVERSE::Exec(XCHAR* URL, XSTRING& publicIP, XSTRING& localIP)
* @brief      Exec
* @ingroup    DATAIO
* 
* @param[in]  URL : 
* @param[in]  publicIP : 
* @param[in]  localIP : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSSHREVERSE::Exec(XCHAR* URL, XSTRING& publicIP, XSTRING& localIP)
{
  bool status = false;

  if(IsRunning())
    {
      status = true;
      return status;
    }

  if(DownloadCFG(URL, publicIP, localIP))
    {
      Activate();
    }

  DelInstance();

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSSHREVERSE::Exec(XSTRING& URL, XSTRING& publicIP, XSTRING& localIP)
* @brief      Exec
* @ingroup    DATAIO
* 
* @param[in]  URL : 
* @param[in]  publicIP : 
* @param[in]  localIP : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSSHREVERSE::Exec(XSTRING& URL, XSTRING& publicIP, XSTRING& localIP)
{
  return Exec(URL.Get(), publicIP, localIP);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSSHREVERSE::Exec(DIOURL& URL, XSTRING& publicIP, XSTRING& localIP)
* @brief      Exec
* @ingroup    DATAIO
* 
* @param[in]  URL : 
* @param[in]  publicIP : 
* @param[in]  localIP : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSSHREVERSE::Exec(DIOURL&  URL, XSTRING& publicIP, XSTRING& localIP)
{
  return Exec(URL.Get(), publicIP, localIP);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOSSHREVERSE::DIOSSHREVERSE()
* @brief      Constructor
* @ingroup    DATAIO
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOSSHREVERSE::DIOSSHREVERSE()
{
  Clean();
}

                                  
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOSSHREVERSE::~DIOSSHREVERSE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOSSHREVERSE::~DIOSSHREVERSE()
{
  Clean();
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOSSHREVERSE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSSHREVERSE::Clean()
{
  URLtarget.Empty();
  localIP.Empty();
  login.Empty();
  password.Empty();

  port  = 0;
}




