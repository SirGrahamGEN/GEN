/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOAlerts.cpp
* 
* @class      DIOALERTS
* @brief      Data Input/Output Alerts class
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


#ifdef DIO_ALERTS_ACTIVE


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIOAlerts.h"

#include "XDateTime.h"
#include "XFileTXT.h"
#include "XFileJSON.h"
#include "XRand.h"
#include "XThreadCollected.h"

#include "HashCRC32.h"

#include "DIOURL.h"
#include "DIOIP.h"
#include "DIOStreamTCPIPConfig.h"
#include "DIOStreamUDPConfig.h"
#include "DIOStreamUDPAcknowledge.h"
#include "DIOSMTP.h"
#include "DIOATCMDGSM.h"
#include "DIOWebClient.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

DIOALERTS* DIOALERTS::instance = NULL;

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


#pragma region CLASS_DIOALERT_CONDITION


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOALERT_CONDITION::DIOALERT_CONDITION()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOALERT_CONDITION::DIOALERT_CONDITION()
{
  Clean();

  GEN_XFACTORY_CREATE(lasttimersend, CreateTimer())
}
          

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOALERT_CONDITION::~DIOALERT_CONDITION()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOALERT_CONDITION::~DIOALERT_CONDITION()
{
  if(lasttimersend) GEN_XFACTORY.DeleteTimer(lasttimersend);

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOALERT_CONDITION::GetTimeLimitForRepeat()
* @brief      Get time limit for repeat
* @ingroup    DATAIO
*
* @return     int : 
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOALERT_CONDITION::GetTimeLimitForRepeat()
{
  return timelimitforrepeat;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOALERT_CONDITION::SetTimeLinitRepeat(int timelimitforrepeat)
* @brief      Set time linit repeat
* @ingroup    DATAIO
*
* @param[in]  timelimitforrepeat : 
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOALERT_CONDITION::SetTimeLinitRepeat(int timelimitforrepeat)
{
  this->timelimitforrepeat = timelimitforrepeat;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOALERT_CONDITION::GetEveryNumberOfTimes()
* @brief      Get every number of times
* @ingroup    DATAIO
*
* @return     int : 
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOALERT_CONDITION::GetEveryNumberOfTimes()
{
  return everynumberoftimes;
}  


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOALERT_CONDITION::SetEveryNumberOfTimes(int everynumberoftimes)
* @brief      Set every number of times
* @ingroup    DATAIO
*
* @param[in]  everynumberoftimes : 
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOALERT_CONDITION::SetEveryNumberOfTimes(int everynumberoftimes)
{
  this->everynumberoftimes = everynumberoftimes;
}
    

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTIMER* DIOALERT_CONDITION::GetLastTimerSend()
* @brief      Get last timer send
* @ingroup    DATAIO
*
* @return     XTIMER* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
XTIMER* DIOALERT_CONDITION::GetLastTimerSend()
{
  return lasttimersend;
}
    

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOALERT_CONDITION::GetNSended()
* @brief      Get N sended
* @ingroup    DATAIO
*
* @return     int : 
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOALERT_CONDITION::GetNSended()
{
  return nsended;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOALERT_CONDITION::SetNSended(int nsended)
* @brief      Set N sended
* @ingroup    DATAIO
*
* @param[in]  nsended : 
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOALERT_CONDITION::SetNSended(int nsended)
{
  this->nsended = nsended;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOALERT_CONDITION::GetNTimesSended()
* @brief      Get N times sended
* @ingroup    DATAIO
*
* @return     int : 
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOALERT_CONDITION::GetNTimesSended()
{
  return ntimessended;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOALERT_CONDITION::SetNTimesSended(int ntimessended)
* @brief      Set N times sended
* @ingroup    DATAIO
*
* @param[in]  ntimessended : 
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOALERT_CONDITION::SetNTimesSended(int ntimessended)
{
  this->ntimessended = ntimessended;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOALERT_CONDITION::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOALERT_CONDITION::Clean()
{  
  timelimitforrepeat   = 0;
  everynumberoftimes   = 0;

  lasttimersend        = NULL;
  nsended              = 0;
  ntimessended         = 0;
}


#pragma endregion


#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOALERT::DIOALERT()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOALERT::DIOALERT()
{
  Clean();
  
  GEN_XFACTORY_CREATE(xdatetime, CreateDateTime())
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOALERT::~DIOALERT()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOALERT::~DIOALERT()
{
  if(xdatetime) GEN_XFACTORY.DeleteDateTime(xdatetime);
  
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDATETIME* DIOALERT::GetDateTime()
* @brief      Get date time
* @ingroup    DATAIO
*
* @return     XDATETIME* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDATETIME* DIOALERT::GetDateTime()
{
  return xdatetime;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOALERT::Application_GetID()
* @brief      Application get ID
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOALERT::Application_GetID()
{
  return &applicationID;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOALERT::Application_GetVersion(XDWORD& version, XDWORD& subversion, XDWORD& subversionerr)
* @brief      Application get version
* @ingroup    DATAIO
*
* @param[in]  version :
* @param[in]  subversion :
* @param[in]  subversionerr :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOALERT::Application_GetVersion(XDWORD& version, XDWORD& subversion, XDWORD& subversionerr)
{
  version       = applicationversion;
  subversion    = applicationsubversion;
  subversionerr = applicationsubversionerr;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOALERT::Application_SetVersion(XDWORD version, XDWORD subversion, XDWORD subversionerr)
* @brief      Application set version
* @ingroup    DATAIO
*
* @param[in]  version :
* @param[in]  subversion :
* @param[in]  subversionerr :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOALERT::Application_SetVersion(XDWORD version, XDWORD subversion, XDWORD subversionerr)
{
  applicationversion        = version;
  applicationsubversion     = subversion;
  applicationsubversionerr  = subversionerr;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOALERT::GetID()
* @brief      Get ID
* @ingroup    DATAIO
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOALERT::GetID()
{
  return ID;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOALERT::SetID(XDWORD ID)
* @brief      Set ID
* @ingroup    DATAIO
*
* @param[in]  ID :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOALERT::SetID(XDWORD ID)
{
  this->ID = ID;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOALERT::CalculateID(bool withdatetime)
* @brief      Calculate ID
* @ingroup    DATAIO
*
* @param[in]  withdatetime :
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOALERT::CalculateID(bool withdatetime)
{
  if(!xdatetime)  return false;

  HASHCRC32* hashcrc32 = new HASHCRC32();
  if(!hashcrc32) return 0;

  XSTRING IDstring;
  XSTRING levelstring;
  XDWORD  ID = 0;
  bool    status;

  if(withdatetime) xdatetime->GetDateTimeToString(XDATETIME_FORMAT_STANDARD, IDstring);

  levelstring.Format(__L("%s %d"), applicationID.Get(), level);
  IDstring += levelstring;

  XRAND* GEN_XFACTORY_CREATE(xrand, CreateRand())
  if(xrand)
    {
      levelstring.Format(__L(" %d "), xrand->Between(1000, 10000000) * xrand->Between(1000, 10000000));
      GEN_XFACTORY.DeleteRand(xrand);
    }

  IDstring += __L(" ");   IDstring += origin;
  IDstring += __L(" ");   IDstring += title;
  IDstring += __L(" ");   IDstring += message;
  IDstring += levelstring;

  XBUFFER charstr;
  
  IDstring.ConvertToASCII(charstr);         
  status = hashcrc32->Do(charstr.Get(), IDstring.GetSize());

  if(status) ID = hashcrc32->GetResultCRC32(); else ID = 0;

  delete hashcrc32;

  return ID;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOALERTLEVEL DIOALERT::GetLevel()
* @brief      Get level
* @ingroup    DATAIO
*
* @return     DIOALERTLEVEL :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOALERTLEVEL DIOALERT::GetLevel()
{
  return level;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOALERT::SetLevel(DIOALERTLEVEL level)
* @brief      Set level
* @ingroup    DATAIO
*
* @param[in]  level :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOALERT::SetLevel(DIOALERTLEVEL level)
{
  this->level=level;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOALERT::GetOrigin()
* @brief      Get origin
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOALERT::GetOrigin()
{
  return &origin;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOALERT::GetTitle()
* @brief      Get title
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOALERT::GetTitle()
{
  return &title;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOALERT::Get_Message()
* @brief      Get message
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOALERT::Get_Message()
{
  return &message;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOALERT::CopyFrom(DIOALERT* alert)
* @brief      Copy from
* @ingroup    DATAIO
*
* @param[in]  alert :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOALERT::CopyFrom(DIOALERT* alert)
{
  if(!alert) return false;

  xdatetime->CopyFrom(alert->GetDateTime());

  applicationID = alert->Application_GetID()->Get();

  alert->Application_GetVersion(applicationversion, applicationsubversion, applicationsubversionerr);

  ID            = alert->GetID();
  level         = alert->GetLevel();
  origin        = alert->GetOrigin()->Get();
  title         = alert->GetTitle()->Get();
  message       = alert->Get_Message()->Get();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOALERT::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOALERT::Clean()
{
  applicationversion        = 0;
  applicationsubversion     = 0;
  applicationsubversionerr  = 0;

  xdatetime                 = NULL;
  ID                        = 0;
  level                     = DIOALERTLEVEL_UNKNOWN;
}


#pragma endregion


#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOALERTS::GetIsInstanced()
* @brief      Get is instanced
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOALERTS::GetIsInstanced()
{
  return instance!=NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOALERTS& DIOALERTS::GetInstance()
* @brief      Get instance
* @ingroup    DATAIO
*
* @return     DIOALERTS& :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOALERTS& DIOALERTS::GetInstance()
{
  if(!instance) instance = new DIOALERTS();

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOALERTS::DelInstance()
* @brief      Del instance
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOALERTS::DelInstance()
{
  if(!instance) return false;

  delete instance;
  instance = NULL;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOALERTS::Ini()
* @brief      Ini
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOALERTS::Ini()
{
  End();

  //-------------------------

  GEN_XFACTORY_CREATE(xmutexsending, Create_Mutex())
  if(!xmutexsending) return false;

  //-------------------------

  SMTPdiostreamcfg = new DIOSTREAMTCPIPCONFIG();
  if(!SMTPdiostreamcfg)  return false;

  SMTPdiostream = (DIOSTREAM*)GEN_DIOFACTORY.CreateStreamIO((DIOSTREAMCONFIG*)SMTPdiostreamcfg);
  if(!SMTPdiostream)  return false;

  SMTP = new DIOSMTP( SMTPdiostream);
  if(!SMTP) return false;

  if(!SMTP->Ini()) return false;

  //-------------------------

  WEBdiowebclient = new DIOWEBCLIENT();
  if(!WEBdiowebclient) return false;

  //-------------------------

  UDPdiostreamcfg = new DIOSTREAMUDPCONFIG();
  if(!UDPdiostreamcfg)  return false;

  UDPdiostream = new DIOSTREAMUDPACKNOWLEDGE((DIOSTREAMUDPCONFIG*)UDPdiostreamcfg);
  if(!UDPdiostream)  return false;

  isinitialized  = true;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOALERTS::Application_GetID()
* @brief      Application get ID
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOALERTS::Application_GetID()
{
  return &applicationID;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOALERTS::Application_GetVersion(XDWORD& version, XDWORD& subversion, XDWORD& subversionerr)
* @brief      Application get version
* @ingroup    DATAIO
*
* @param[in]  version :
* @param[in]  subversion :
* @param[in]  subversionerr :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOALERTS::Application_GetVersion(XDWORD& version, XDWORD& subversion, XDWORD& subversionerr)
{
  version       = applicationversion;
  subversion    = applicationsubversion;
  subversionerr = applicationsubversionerr;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOALERTS::Application_SetVersion (XDWORD version, XDWORD subversion, XDWORD subversionerr)
* @brief      Application set version 
* @ingroup    DATAIO
*
* @param[in]  version :
* @param[in]  subversion :
* @param[in]  subversionerr :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOALERTS::Application_SetVersion(XDWORD version, XDWORD subversion, XDWORD subversionerr)
{
  applicationversion        = version;
  applicationsubversion     = subversion;
  applicationsubversionerr  = subversionerr;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOALERTS::GetOrigin()
* @brief      Get origin
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOALERTS::GetOrigin()
{
  return &origin;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOALERTS::IsSending()
* @brief      Is sending
* @ingroup    DATAIO
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOALERTS::IsSending()
{
  return issending;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOALERT* DIOALERTS::CreateAlert(XCHAR* applicationID, DIOALERTLEVEL level, XCHAR* origin, XCHAR* title, XCHAR* message)
* @brief      Create alert
* @ingroup    DATAIO
*
* @param[in]  applicationID : 
* @param[in]  level : 
* @param[in]  origin : 
* @param[in]  title : 
* @param[in]  message : 
*
* @return     DIOALERT* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOALERT* DIOALERTS::CreateAlert(XCHAR* applicationID, DIOALERTLEVEL level, XCHAR* origin, XCHAR* title, XCHAR* message)
{
  if(level == DIOALERTLEVEL_UNKNOWN) return NULL;

  if(!origin)   return NULL;
  if(!title)    return NULL;
  if(!message)  return NULL;

  DIOALERT* alert = new DIOALERT();
  if(alert)
    {
      if(alert->GetDateTime()) alert->GetDateTime()->Read();

      alert->Application_GetID()->Set(applicationID);
      alert->Application_SetVersion(applicationversion, applicationsubversion, applicationsubversionerr);
      alert->SetLevel(level);
      alert->GetOrigin()->Set(origin);
      alert->GetTitle()->Set(title);
      alert->Get_Message()->Set(message);

      XDWORD ID = alert->CalculateID(true);
      if(!ID)
        {
          delete alert;
          return NULL;
        }

      alert->SetID(ID);
    }

  return alert;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOALERT* DIOALERTS::CreateAlert(XSTRING& applicationID, DIOALERTLEVEL level, XSTRING& origin, XSTRING& title, XSTRING& message)
* @brief      Create alert
* @ingroup    DATAIO
*
* @param[in]  applicationID : 
* @param[in]  level : 
* @param[in]  origin : 
* @param[in]  title : 
* @param[in]  message : 
*
* @return     DIOALERT* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOALERT* DIOALERTS::CreateAlert(XSTRING& applicationID, DIOALERTLEVEL level, XSTRING& origin, XSTRING& title, XSTRING& message)
{
  return CreateAlert(applicationID.Get(), level, origin.Get(), title.Get(), message.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOALERT* DIOALERTS::CreateAlert(DIOALERTLEVEL level, XCHAR* title, XCHAR* message)
* @brief      Create alert
* @ingroup    DATAIO
*
* @param[in]  level : 
* @param[in]  title : 
* @param[in]  message : 
*
* @return     DIOALERT* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOALERT* DIOALERTS::CreateAlert(DIOALERTLEVEL level, XCHAR* title, XCHAR* message)
{
  return CreateAlert(applicationID.Get(), level, origin.Get(), title, message);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOALERT* DIOALERTS::CreateAlert(DIOALERTLEVEL level, XSTRING& title, XSTRING& message)
* @brief      Create alert
* @ingroup    DATAIO
*
* @param[in]  level : 
* @param[in]  title : 
* @param[in]  message : 
*
* @return     DIOALERT* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOALERT* DIOALERTS::CreateAlert(DIOALERTLEVEL level, XSTRING& title, XSTRING& message)
{
  return CreateAlert(applicationID.Get(), level, origin.Get(), title.Get(), message.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOALERTS::Sender_SMTPConfig(XCHAR* URL, int port, XCHAR* login, XCHAR* password, XCHAR* senderemail, int nrecipients,...)
* @brief      Sender SMTP config
* @ingroup    DATAIO
*
* @param[in]  URL :
* @param[in]  port :
* @param[in]  login :
* @param[in]  password :
* @param[in]  senderemail :
* @param[in]  nrecipients :
* @param[in]  ... :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOALERTS::Sender_SMTPConfig(XCHAR* URL, int port, XCHAR* login, XCHAR* password, XCHAR* senderemail, int nrecipients,...)
{
  if(!isinitialized) return false;

  if(!SMTP) return false;

  SMTPsenderisactive = false;

  SMTP->Server_GetURL()->Set(URL);
  SMTP->Server_SetPort(port);
  SMTP->Server_GetLogin()->Set(login);
  SMTP->Server_GetPassword()->Set(password);
  SMTP->GetSenderEmail()->Set(senderemail);
  SMTP->SetContentType(DIOSSMPTCONTENTTYPE_UTF8);

  va_list  arg;

  va_start(arg, nrecipients);

  int nr = nrecipients;

  while(nr)
    {
      XCHAR* recipient = (XCHAR*)va_arg(arg, XCHAR*);
      if(!recipient) break;

      DIOSMTPRECIPIENTTYPE  type        = DIOSMTPRECIPIENTTYPE_UNKNOWN;
      int                   test        = 0;
      XSTRING               recipientstring;
      XSTRING               name;
      XSTRING               email;

      recipientstring = recipient;

      name.AdjustSize(_MAXSTR);
      email.AdjustSize(_MAXSTR);

      recipientstring.UnFormat(__L("%d,%s,%s,%d"), &type, name.Get(), email.Get(), &test);

      name.AdjustSize();
      email.AdjustSize();

      if((type == DIOSMTPRECIPIENTTYPE_TO) || (type == DIOSMTPRECIPIENTTYPE_CC) || (type == DIOSMTPRECIPIENTTYPE_BCC))
        {
          SMTP->AddRecipient(type, name , email, test?true:false);
        }

      nr--;
    }

  va_end(arg);

  SMTPsenderisactive = true;

  return SMTPsenderisactive;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOALERTS::Sender_SMSConfig(DIOSTREAM* diostream, int nrecipients, ...)
* @brief      Sender SMS config
* @ingroup    DATAIO
*
* @param[in]  diostream :
* @param[in]  nrecipients :
* @param[in]  ... :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOALERTS::Sender_SMSConfig(DIOSTREAM* diostream, int nrecipients, ...)
{
  if(!isinitialized) return false;
  if(!diostream) return false;

  SMSsenderisactive = false;
  SMSdiostream      = diostream;

  SMSrecipients.DeleteContents();
  SMSrecipients.DeleteAll();

  va_list  arg;

  va_start(arg, nrecipients);

  int nr = nrecipients;

  while(nr)
    {
      XSTRING* recipient = new XSTRING();
      if(recipient)
        {
          (*recipient) = (XCHAR*)va_arg(arg, XCHAR*);
          SMSrecipients.Add(recipient);
        }

      nr--;
    }

  va_end(arg);

  if(SMSrecipients.GetSize()) SMSsenderisactive = true;

  return SMSsenderisactive;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOALERTS::Sender_WEBConfig(XCHAR* command, bool isuseget, int nrecipients, ...)
* @brief      Sender WEB config
* @ingroup    DATAIO
*
* @param[in]  command :
* @param[in]  isuseget :
* @param[in]  nrecipients :
* @param[in]  ... :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOALERTS::Sender_WEBConfig(XCHAR* command, bool isuseget, int nrecipients, ...)
{
  if(!isinitialized) return false;
  if(!WEBdiowebclient) return false;

  bool serveractive = false;

  WEBcommand  = command;
  WEBisuseget = isuseget;

  WEBsenderisactive = false;

  WEBrecipients.DeleteContents();
  WEBrecipients.DeleteAll();

  va_list  arg;
  bool     status = false;

  va_start(arg, nrecipients);

  int nr = nrecipients;

  while(nr)
    {
      DIOURL* recipient = new DIOURL();
      if(recipient)
        {
          (*recipient) = (XCHAR*)va_arg(arg, XCHAR*);

          if(recipient->HaveHTTPID()) recipient->DeleteHTTPID();

          WEBrecipients.Add(recipient);
        }

      nr--;
    }

  va_end(arg);

  if(WEBrecipients.GetSize())
    {
      WEBsenderisactive = true;

      XBUFFER webpage;

      for(int c=0; c<nrecipients; c++)
        {
          XSTRING url;

          url = WEBrecipients.Get(c)->Get();
          url.AddFormat(__L("?%s") , WEBcommand.Get());

          status = WEBdiowebclient->Get(url.Get(), webpage);
          if(!status)
            {
              break;
            }
           else serveractive = true;
        }
    }

  return serveractive;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOALERTS::Sender_UDPConfig(int port, int nrecipients, ...)
* @brief      Sender UDP config
* @ingroup    DATAIO
*
* @param[in]  port :
* @param[in]  nrecipients :
* @param[in]  ... :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOALERTS::Sender_UDPConfig(int port, int nrecipients, ...)
{
  if(!isinitialized) return false;
  if(!port) return false;

  UDPsenderisactive = false;

  UDPrecipients.DeleteContents();
  UDPrecipients.DeleteAll();

  DIOURL* URL = new DIOURL();
  if(!URL) return false;

  va_list  arg;

  va_start(arg, nrecipients);

  int nr = nrecipients;

  while(nr)
    {
      (*URL) = (XCHAR*)va_arg(arg, XCHAR*);

      if(!URL->IsEmpty())
        {
          DIOIP* IP = new DIOIP();
          if(IP)
            {
              URL->ResolveURL((*IP));
              UDPrecipients.Add(IP);
            }
        }

      nr--;
    }

  va_end(arg);

  if(URL) delete URL;

  if(UDPrecipients.GetSize())
    {
      UDPsenderisactive = true;
      UDPdiostreamcfg->SetRemotePort(port);
    }

  return UDPsenderisactive;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOALERTS::IsValidConditionToSend(XDWORD conditionID)
* @brief      Is valid condition to send
* @ingroup    DATAIO
*
* @param[in]  conditionID : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOALERTS::IsValidConditionToSend(XDWORD conditionID)
{
  bool mustsend   = true;

  DIOALERT_CONDITION* condition = GetCondition(conditionID);
  if(condition)
    {
      //-------------------------------------------------------------
      // Firts send

      if(!condition->GetNSended())
        {
          condition->GetLastTimerSend()->Reset();
        }
       else 
        {
          if(condition->GetTimeLimitForRepeat())
            {
              if((XDWORD)condition->GetTimeLimitForRepeat() > condition->GetLastTimerSend()->GetMeasureSeconds())
                {
                  mustsend = false;
                }
            }
        
          if(condition->GetEveryNumberOfTimes())
            {
              if(condition->GetNTimesSended() < condition->GetEveryNumberOfTimes())   
                {              
                  mustsend = false;  
                } 
            }
        }    
    }

  return mustsend;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOALERTS::Send(DIOALERTSENDER sender, DIOALERT* alert)
* @brief      Send
* @ingroup    DATAIO
*
* @param[in]  sender :
* @param[in]  alert :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOALERTS::Send(DIOALERTSENDER sender, XDWORD conditionID, DIOALERT* alert)
{
  if(!isinitialized) return false;

  int   statussend = 0;

  xmutexsending->Lock();  

  if(IsValidConditionToSend(conditionID))
    {      
      issending = true;

      if((sender & DIOALERTSSENDER_SMPT) && (SMTPsenderisactive)) statussend |= Sender_SMTPSend(alert)? DIOALERTSSENDER_SMPT: 0;
      if((sender & DIOALERTSSENDER_SMS)  && (SMSsenderisactive))  statussend |= Sender_SMSSend(alert) ? DIOALERTSSENDER_SMS : 0;
      if((sender & DIOALERTSSENDER_WEB)  && (WEBsenderisactive))  statussend |= Sender_WEBSend(alert) ? DIOALERTSSENDER_WEB : 0;
      if((sender & DIOALERTSSENDER_UDP)  && (UDPsenderisactive))  statussend |= Sender_UDPSend(alert) ? DIOALERTSSENDER_UDP : 0;
      
      issending = false;      
    }

  DIOALERT_CONDITION* condition = GetCondition(conditionID);
  if(condition)
    {
       if(condition->GetNTimesSended() >= condition->GetEveryNumberOfTimes())   
         {              
           condition->SetNTimesSended(0);
         }

      if(statussend) condition->GetLastTimerSend()->Reset();
      condition->SetNSended(condition->GetNSended()+1);
      condition->SetNTimesSended(condition->GetNTimesSended()+1);
    }

  xmutexsending->UnLock();

  return statussend;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOALERTS::AddCondition(XDWORD conditionID, int timelimitforrepeat, int everynumberoftimes)
* @brief      Add condition
* @ingroup    DATAIO
*
* @param[in]  conditionID : 
* @param[in]  timelimitforrepeat : 
* @param[in]  everynumberoftimes : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOALERTS::AddCondition(XDWORD conditionID, int timelimitforrepeat, int everynumberoftimes)
{
  DIOALERT_CONDITION* condition = GetCondition(conditionID);
  bool                must_add  = false;

  if(!condition)
    {
      condition = new DIOALERT_CONDITION();
      must_add  = true;
    }
  
  condition->SetTimeLinitRepeat(timelimitforrepeat);
  condition->SetEveryNumberOfTimes(everynumberoftimes);

  if(must_add) conditions.Add(conditionID, condition);  

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOALERT_CONDITION_CFG* DIOALERTS::GetConditionConfig(XDWORD conditionID)
* @brief      Get condition config
* @ingroup    DATAIO
*
* @param[in]  conditionID : 
*
* @return     DIOALERT_CONDITION_CFG* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOALERT_CONDITION* DIOALERTS::GetCondition(XDWORD conditionID)
{  
  return conditions.Get(conditionID);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOALERTS::DeleteAllConditionConfig()
* @brief      Delete all condition config
* @ingroup    DATAIO
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOALERTS::DeleteAllConditions()
{
  if(conditions.IsEmpty()) return false;

  conditions.DeleteElementContents();
  conditions.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOALERTS::End()
* @brief      End
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOALERTS::End()
{  
  while(issending)
    {
      GEN_XSLEEP.Seconds(100);
    }

  if(xmutexsending)
    {
      GEN_XFACTORY.Delete_Mutex(xmutexsending);
      xmutexsending = NULL; 
    }

  if(SMTP)
    {
      SMTP->End();
      delete SMTP;

      SMTP = NULL;
    }

  if(SMTPdiostream)
    {
      SMTPdiostream->Close();
      GEN_DIOFACTORY.DeleteStreamIO(SMTPdiostream);

      SMTPdiostream = NULL;
    }

  if(SMTPdiostreamcfg)
    {
      delete SMTPdiostreamcfg;

      SMTPdiostreamcfg = NULL;
    }

  SMTPsenderisactive = false;

  //------------------------------------------

  SMSrecipients.DeleteContents();
  SMSrecipients.DeleteAll();

  SMSsenderisactive = false;

  //------------------------------------------

  WEBrecipients.DeleteContents();
  WEBrecipients.DeleteAll();

  if(WEBdiowebclient)
    {
      delete WEBdiowebclient;
      WEBdiowebclient = NULL;
    }

  WEBsenderisactive = false;

  //------------------------------------------

  UDPrecipients.DeleteContents();
  UDPrecipients.DeleteAll();

  if(UDPdiostream)
    {
      UDPdiostream->Close();
      delete UDPdiostream;
      UDPdiostream = NULL;
    }

  if(UDPdiostreamcfg)
    {
      delete UDPdiostreamcfg;
      UDPdiostreamcfg = NULL;
    }

  UDPsenderisactive = false;

  //------------------------------------------

  DeleteAllConditions();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOALERTS::DIOALERTS()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOALERTS::DIOALERTS()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOALERTS::~DIOALERTS()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOALERTS::~DIOALERTS()
{
  End();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOALERTS::Sender_SMTPSend(DIOALERT* alert)
* @brief      Sender SMTP send
* @ingroup    DATAIO
*
* @param[in]  alert :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOALERTS::Sender_SMTPSend(DIOALERT* alert)
{
  if(!SMTP)   return false;
  if(!alert)  return false;

  SMTP->GetMessage()->DeleteAllLines();

  XSTRING appIDstring;
  XSTRING appverstring;

  SMTP->GetSenderName()->Set(alert->Application_GetID()->Get());

  if(applicationversion || applicationsubversion  || applicationsubversionerr) appverstring.Format(__L(" %d.%d.%d"), applicationversion, applicationsubversion, applicationsubversionerr);

  appIDstring = alert->Application_GetID()->Get();
  if(!appverstring.IsEmpty()) appIDstring += appverstring.Get();

  appIDstring += __L(": ");
  appIDstring += alert->GetTitle()->Get();

  SMTP->GetSubject()->Set(appIDstring);

  XSTRING body;

  body += alert->GetOrigin()->Get();
  body += __L("\r\n\r\n");
  body += alert->Get_Message()->Get();

  SMTP->GetMessage()->AddLine(body);

  SMTP->SetXPriority(DIOSMTPXPRIORITY_HIGH);

  return SMTP->Send();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOALERTS::Sender_SMSSend(DIOALERT* alert)
* @brief      Sender SMS send
* @ingroup    DATAIO
*
* @param[in]  alert :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOALERTS::Sender_SMSSend(DIOALERT* alert)
{
  if(!alert) return false;

  bool status = false;

  DIOATCMDGSM* SMSdioatcmdgsm = new DIOATCMDGSM( SMSdiostream);
  if(SMSdioatcmdgsm)
    {
      if(SMSdioatcmdgsm->Ini(30, false, false))
        {
          XSTRING smstext;

          if(alert->Application_GetID()->GetSize())
            {
              XSTRING appverstring;

              if(applicationversion || applicationsubversion  || applicationsubversionerr) appverstring.Format(__L(" %d.%d.%d"), applicationversion, applicationsubversion, applicationsubversionerr);

              smstext += __L("<");
              smstext += alert->Application_GetID()->Get();

              if(!appverstring.IsEmpty()) smstext += appverstring.Get();

              smstext += __L("> ");
            }


          if(alert->GetTitle()->GetSize())
            {
              smstext += alert->GetTitle()->Get();
              smstext += __L(" ");
            }


          if(alert->GetOrigin()->GetSize())
            {
              smstext += __L("(");
              smstext += alert->GetOrigin()->Get();
              smstext += __L(")");
            }

          if(alert->Get_Message()->GetSize())
            {
              smstext += __L(":");
              smstext += alert->Get_Message()->Get();
            }

          if(smstext.GetSize()>=160) smstext.AdjustSize(160);

          status = true;

          for(int c=0; c<(int)SMSrecipients.GetSize(); c++)
            {
              if(SMSdioatcmdgsm->SendSMS(SMSrecipients.Get(c)->Get(), smstext.Get()) != DIOATCMD_ERROR_NONE)  status = false;
            }

          SMSdioatcmdgsm->End();
        }

      delete SMSdioatcmdgsm;
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOALERTS::Sender_WEBSend(DIOALERT* alert)
* @brief      Sender WEB send
* @ingroup    DATAIO
*
* @param[in]  alert :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOALERTS::Sender_WEBSend(DIOALERT* alert)
{
  if(WEBrecipients.IsEmpty()) return false;

  DIOURL    url;
  XSTRING   applicationIDstring;
  XSTRING   applicationverstring; 
  XBUFFER   webpage;
  bool      status  = true;

  if(applicationversion || applicationsubversion  || applicationsubversionerr) applicationverstring.Format(__L(" %d.%d.%d"), applicationversion, applicationsubversion, applicationsubversionerr);

  applicationIDstring = alert->Application_GetID()->Get();
  if(!applicationverstring.IsEmpty()) applicationIDstring += applicationverstring.Get();

  for(int c=0; c<(int)WEBrecipients.GetSize(); c++)
    {
      DIOURL    part;
      
      url = WEBrecipients.Get(c)->Get();

      if(WEBisuseget)
        {
          url.Slash_Delete();
          url.AddFormat(__L("?%s") , WEBcommand.Get());

          if(!applicationIDstring.IsEmpty()) 
            {
              part = applicationIDstring.Get();            
              part.EncodeUnsafeChars();                  
              url.AddFormat(__L("&%s=%s"), DIOALERTS_QSPARAM_APPLICATIONID, part.Get());       
            }      

          if(alert->GetLevel())
            {
              part.Format(__L("%d"), alert->GetLevel());   
              part.EncodeUnsafeChars();                  
              url.AddFormat(__L("&%s=%s"), DIOALERTS_QSPARAM_LEVEL, part.Get());               
            }

          if(!alert->GetTitle()->IsEmpty())
            {
              part = alert->GetTitle()->Get();             
              part.EncodeUnsafeChars();    
              url.AddFormat(__L("&%s=%s"), DIOALERTS_QSPARAM_TITLE, part.Get());              
            }
              
          if(!alert->GetOrigin()->IsEmpty())             
            {
              part = alert->GetOrigin()->Get();            
              part.EncodeUnsafeChars();                  
              url.AddFormat(__L("&%s=%s"), DIOALERTS_QSPARAM_ORIGIN, part.Get());              
            }

          if(!alert->Get_Message()->IsEmpty())
            {
              part = alert->Get_Message()->Get();          
              part.EncodeUnsafeChars();                  
              url.AddFormat(__L("&%s=%s"), DIOALERTS_QSPARAM_MESSAGE, part.Get());             
            }
             
          status = WEBdiowebclient->Get(url.Get(), webpage);          
        }
       else
        {
          XSTRING   contents;
          XFILEJSON json;
          XBUFFER   postbuffer;

          XFILEJSONOBJECT* root   = new XFILEJSONOBJECT();
          if(root) 
            {
              XFILEJSONOBJECT* main  = new XFILEJSONOBJECT();
              if(main) 
                {
                  XFILEJSON_ADDVALUE(main, DIOALERTS_QSPARAM_APPLICATIONID , applicationIDstring.Get());                  
                  XFILEJSON_ADDVALUE(main, DIOALERTS_QSPARAM_LEVEL         , (int)alert->GetLevel());          
                  XFILEJSON_ADDVALUE(main, DIOALERTS_QSPARAM_TITLE         , alert->GetTitle()->Get());
                  XFILEJSON_ADDVALUE(main, DIOALERTS_QSPARAM_ORIGIN        , alert->GetOrigin()->Get());
                  XFILEJSON_ADDVALUE(main, DIOALERTS_QSPARAM_MESSAGE       , alert->Get_Message()->Get());

                  XFILEJSON_ADDVALUE(root, WEBcommand.Get(), main);                      

                  json.SetRoot(root);
                  json.EncodeAllLines(false);

                  for(int c=0; c<json.GetNLines(); c++)
                    {
                      XSTRING* string = json.GetLine(c);
                      if(string)
                        {                          
                          contents.Add(string->Get());                 
                        }
                     }

                  json.DeleteAllLines();
                  json.DeleteAllObjects();
                }
            }                              

          XBUFFER postdata;
          
          contents.ConvertToASCII(postdata);          
          postbuffer.Add(postdata.Get(), contents.GetSize());
          
          status = WEBdiowebclient->Post(url.Get(), webpage, &postbuffer);      
        }        
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOALERTS::Sender_UDPSend(DIOALERT* alert)
* @brief      Sender UDP send
* @ingroup    DATAIO
*
* @param[in]  alert :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOALERTS::Sender_UDPSend(DIOALERT* alert)
{
  if(!alert)            return false;
  if(!UDPdiostreamcfg)  return false;
  if(!UDPdiostream)     return false;

  XBUFFER     xbuffer;
  HASHCRC32   hashcrc32;
  XDWORD      CRC32;

  xbuffer.Delete();

  // Date time
  xbuffer.Add((XDWORD)alert->GetDateTime()->GetDay());                                                              // Day
  xbuffer.Add((XDWORD)alert->GetDateTime()->GetMonth());                                                            // Month
  xbuffer.Add((XDWORD)alert->GetDateTime()->GetYear());                                                             // Year
  xbuffer.Add((XDWORD)alert->GetDateTime()->GetHours());                                                            // Hours
  xbuffer.Add((XDWORD)alert->GetDateTime()->GetMinutes());                                                          // Minutes
  xbuffer.Add((XDWORD)alert->GetDateTime()->GetSeconds());                                                          // Seconds

  xbuffer.Add((XDWORD)alert->Application_GetID()->GetSize());    xbuffer.Add((*alert->Application_GetID()));          // Aplication String
  xbuffer.Add((XDWORD)applicationversion);                                                                          // Aplicatcion version
  xbuffer.Add((XDWORD)applicationsubversion);                                                                       // Aplication  subversion
  xbuffer.Add((XDWORD)applicationsubversionerr);                                                                    // Application subversion err

  xbuffer.Add((XDWORD)alert->GetID());                                                                              // ID  
  xbuffer.Add((XDWORD)alert->GetLevel());                                                                           // Level
  xbuffer.Add((XDWORD)alert->GetOrigin()->GetSize());           xbuffer.Add((*alert->GetOrigin()));                 // Origin
  xbuffer.Add((XDWORD)alert->GetTitle()->GetSize());            xbuffer.Add((*alert->GetTitle()));                  // Title
  xbuffer.Add((XDWORD)alert->Get_Message()->GetSize());         xbuffer.Add((*alert->Get_Message()));               // Message

  hashcrc32.ResetResult();
  hashcrc32.Do(xbuffer);

  CRC32 = hashcrc32.GetResultCRC32();

  xbuffer.Add((XDWORD)CRC32);

  bool status;
  int  nsent = 0;

  for(int c=0; c<(int)UDPrecipients.GetSize(); c++)
    {
      DIOIP* ip = UDPrecipients.Get(c);
      if(ip)
        {
          XSTRING IPstring;

          ip->GetXString(IPstring);

          UDPdiostreamcfg->SetMode(DIOSTREAMMODE_CLIENT);
          UDPdiostreamcfg->GetRemoteURL()->Set(IPstring.Get());
          UDPdiostreamcfg->SetIsUsedDatagrams(true);

          status = UDPdiostream->Open();
          if(status)
            {
              status = UDPdiostream->Write(xbuffer.Get(), xbuffer.GetSize())?true:false;
              if(status) nsent++;
              UDPdiostream->Close();
            }
        }
    }

  return (UDPrecipients.GetSize() == nsent)?true:false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOALERTS::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOALERTS::Clean()
{
  isinitialized             = false;

  applicationversion        = 0;
  applicationsubversion     = 0;
  applicationsubversionerr  = 0;

  xmutexsending             = NULL;
  issending                 = false;

  SMTPsenderisactive        = false;
  SMTPdiostreamcfg          = NULL;
  SMTPdiostream             = NULL;
  SMTP                      = NULL;

  SMSsenderisactive         = false;
  SMSdiostream              = NULL;

  WEBsenderisactive         = false;
  WEBisuseget               = false;
  WEBdiowebclient           = NULL;

  UDPsenderisactive         = false;
  UDPdiostreamcfg           = NULL;
  UDPdiostream              = NULL;
}


#pragma endregion


#pragma endregion


#endif

