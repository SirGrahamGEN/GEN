/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XLicense.h
*
* @class      XLICENSE
* @brief      eXtended License generator and control class
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

#ifndef _XLICENSE_H_
#define _XLICENSE_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <stdio.h>

#include "XBase.h"
#include "XFactory.h"
#include "XString.h"
#include "XDateTime.h"
#include "XEvent.h"
#include "XSubject.h"

#include "DIOURL.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define XLICENSE_FILEID                   0xAA55
#define XLICENSE_MAXIDPARTS               4
#define XLICENSE_VERSION                  1
#define XLICENSE_SUBVERSION               0

#define XLICENSE_FILESECTION              __L("LICENSE")
#define XLICENSE_FILEVALUE_ID             __L("licenseID")
#define XLICENSE_FILEVALUE_LICENSE        __L("license")
#define XLICENSE_FILEVALUE_EXPIRATION     __L("expiration")


enum XLICENSEXEVENT_TYPE
{
  XLICENSEXEVENT_TYPE_UNKNOWN               =  XEVENT_TYPE_LICENSE  ,
  XLICENSEXEVENT_TYPE_INVALID                                      ,
  XLICENSEXEVENT_TYPE_EXPIRED                                      ,
};


#define CREATEMASTERLICENSE(xlicense, xpath, xlicenseID, applicationID, expirationseconds)    { XSTRING appID;                                                                      \
                                                                                                appID = applicationID;                                                              \
                                                                                                xlicense->CheckMasterCreation(xpath, xlicenseID, appID, expirationseconds);         \
                                                                                              }


#ifdef XLICENSE_ACTIVE

  #define CHECKLICENSEFULLLOCAL(xlicense, xpath, applicationID)                               {                                                                                     \
                                                                                                XLICENSEID  xlicenseID;                                                             \
                                                                                                XSTRING     appID;                                                                  \
                                                                                                XBUFFER     license();                                                              \
                                                                                                appID = applicationID;                                                              \
                                                                                                bool        status = xlicense->GenerateMachineID(xlicenseID);                       \
                                                                                                if(status)  status = xlicense->Generate(xlicenseID, &appID);                        \
                                                                                                if(status)  status = xlicense->LoadFromFile(xpath, appID, &license);                \
                                                                                                if(status)  status = license.Compare(xlicense->Get());                              \
                                                                                                if(!status) xlicense->SetEvent(XLICENSEXEVENT_TYPE_INVALID);                        \
                                                                                                #endif                                                                              \
                                                                                              }

  #define CHECKLICENSEFULLLOCALEXPIRE(xlicense, xpath, applicationID)                         {                                                                                     \
                                                                                                XLICENSEID  xlicenseID;                                                             \
                                                                                                XSTRING     appID;                                                                  \
                                                                                                XSTRING     expireddate;                                                            \
                                                                                                XBUFFER     license();                                                              \
                                                                                                XTIME       xtimeexpired;                                                           \
                                                                                                XDATETIME*  xtimeactual;                                                            \
                                                                                                appID = applicationID;                                                              \
                                                                                                bool        status = xlicense->GenerateMachineID(xlicenseID);                       \
                                                                                                if(status)  status = xlicense->Generate(xlicenseID, &appID);                        \
                                                                                                if(status)  status = xlicense->LoadFromFile(xpath, appID, &license, &expireddate);  \
                                                                                                if(status)  status = license.Compare(xlicense->Get());                              \
                                                                                                if(!status) xlicense->SetEvent(XLICENSEXEVENT_TYPE_INVALID);                        \
                                                                                                GEN_XFACTORY_CREATE(xtimeactual, CreateTime())                                      \
                                                                                                if(xtimeactual)                                                                     \
                                                                                                  {                                                                                 \
                                                                                                    xtimeexpired.GetDateTimeFromString(expireddate, XDATETIME_FORMAT_STANDARD);     \
                                                                                                    xtimeactual->Read();                                                            \
                                                                                                    if(xtimeexpired.GetDay() || xtimeexpired.GetMonth() || xtimeexpired.GetYear())  \
                                                                                                      {                                                                             \
                                                                                                        if(xtimeactual->GetSeconsFromDate() >= xtimeexpired.GetSeconsFromDate())    \
                                                                                                          {                                                                         \
                                                                                                            xlicense->SetEvent(XLICENSEXEVENT_TYPE_EXPIRED);                        \
                                                                                                          }                                                                         \
                                                                                                      }                                                                             \
                                                                                                    GEN_XFACTORY.DeleteTime(xtimeactual);                                           \
                                                                                                  }                                                                                 \
                                                                                              }
#else

  #define CHECKLICENSEFULLLOCAL(xlicense, xpath, applicationID)                     //
  #define CHECKLICENSEFULLLOCALEXPIRE(xlicense, xpath, applicationID)               //

#endif


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XPUBLISHER;
class XLICENSE;
class DIOFACTORY;


class XLICENSEXEVENT : public XEVENT
{
  public:
                          XLICENSEXEVENT                (XSUBJECT* subject, XDWORD type = XLICENSEXEVENT_TYPE_UNKNOWN, XDWORD family = XEVENT_TYPE_LICENSE);
    virtual              ~XLICENSEXEVENT                ();


    XLICENSE*             Get                           ();
    void                  Set                           (XLICENSE* xlicense);

  private:

    void                  Clean                         ();

    XLICENSE*             xlicense;
};



class XLICENSEID
{
  public:

                          XLICENSEID                    ();
    virtual              ~XLICENSEID                    ();

    bool                  GetPart                       (int npart, XDWORD part);
    bool                  SetPart                       (int npart, XDWORD part);

    XDWORD*               GetParts                      ();

    void                  GetXBuffer                    (XBUFFER& xbuffer);
    void                  GetXString                    (XSTRING& IDstring);

  private:

    void                  Clean                         ();

    XDWORD                part[XLICENSE_MAXIDPARTS];
};



class XLICENSE  : public XSUBJECT
{
  public:

                          XLICENSE                      ();
    virtual              ~XLICENSE                      ();

    virtual bool          GenerateMachineID             (XLICENSEID& xlicenseID);
    virtual bool          Generate                      (XLICENSEID& xlicenseID, XSTRING* applicationID = NULL, XBUFFER* license = NULL);
    virtual bool          GetBufferKeyFromMachineID     (XSTRING& applicationID, XBUFFER& keybuffer);
    virtual bool          CipherExpirationDate          (bool cipher, XSTRING& applicationID, XSTRING& expirationdate);

    XSTRING*              GetApplicationID              ();
    XDATETIME*            GetExpirationDateTime         ();
    XBUFFER*              Get                           ();
    bool                  Get                           (XSTRING& licensestring);

    bool                  LoadFromFile                  (XPATH& xpath, XSTRING& applicationID, XBUFFER* license = NULL, XSTRING* expirationdate = NULL);
    bool                  LoadFromURL                   (DIOURL& url, int timeout, XSTRING* IPlocal, XSTRING& applicationID, XBUFFER* license = NULL, XSTRING* expirationdate = NULL);
    bool                  LoadFromBuffer                (XBUFFER& xbuffer, XSTRING& applicationID, XBUFFER* license = NULL, XSTRING* expirationdate = NULL);

    bool                  CheckMasterCreation           (XPATH& xpath, XLICENSEID& xlicenseID, XSTRING& applicationID, int expirationseconds = 0);

    bool                  SetEvent                      (XLICENSEXEVENT_TYPE type);

  private:

    void                  Clean                         ();

    XBUFFER*              license;
    XSTRING               applicationID;
    XDATETIME             expirationdatetime;
};

/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif


