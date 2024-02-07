/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       APPBase.h
* 
* @class      APPBASE
* @brief      Application Base class
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

#ifndef _APPBASE_H_
#define _APPBASE_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include <stdio.h>

#include "XString.h"
#include "XTrace.h"
#include "XSystem.h"
#include "XSubject.h"
#include "XVector.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

enum APPBASE_EXITTYPE
{
  APPBASE_EXITTYPE_UNKNOWN                          = 0 ,
  APPBASE_EXITTYPE_BY_SERIOUSERROR                      ,
  APPBASE_EXITTYPE_BY_UPDATE                            ,
  APPBASE_EXITTYPE_BY_APPLICATION                       ,
  APPBASE_EXITTYPE_BY_USER                              ,
  APPBASE_EXITTYPE_BY_SHUTDOWN                          ,
  APPBASE_EXITTYPE_BY_INVALIDLICENSE                    ,
  APPBASE_EXITTYPE_BY_EXPIREDLICENSE                    ,
  APPBASE_EXITTYPE_BY_SERVICERELOAD             
};


enum APPBASE_APPLICATIONMODE_TYPE
{
  APPBASE_APPLICATIONMODE_TYPE_UNKNOWN              = 0 ,
  APPBASE_APPLICATIONMODE_TYPE_APPLICATION              ,
  APPBASE_APPLICATIONMODE_TYPE_SERVICE                  ,
  APPBASE_APPLICATIONMODE_TYPE_DINAMICLIBRARY           ,
};


#define APPDEFAULT_DIRECTORY_ROOT            __L("assets")
#define APPDEFAULT_DIRECTORY_WEB             __L("web")
#define APPDEFAULT_DIRECTORY_DATABASES       __L("databases")
#define APPDEFAULT_DIRECTORY_GRAPHICS        __L("graphics")
#define APPDEFAULT_DIRECTORY_UI_LAYOUTS      __L("ui_layouts")
#define APPDEFAULT_DIRECTORY_SOUNDS          __L("sounds")
#define APPDEFAULT_DIRECTORY_FONTS           __L("fonts")
#define APPDEFAULT_DIRECTORY_SCRIPTS         __L("scripts")
#define APPDEFAULT_DIRECTORY_FIRMWARE        __L("firmware")
#define APPDEFAULT_DIRECTORY_CERTIFICATES    __L("certificates")

#define APPLICATIONCREATEINSTANCE(CLASSNAME, VARIABLE)    CLASSNAME* VARIABLE = NULL;                     \
                                                          APPBASE* APPBASE::Create()                      \
                                                          {                                               \
                                                            VARIABLE = new CLASSNAME();                   \
                                                            return VARIABLE;                              \
                                                          }

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

class XTIMER;

class APPBASE : public XSUBJECT
{
  public:

                                    APPBASE                       ();
    virtual                        ~APPBASE                       ();

    static APPBASE*                 Create                        ();

    virtual bool                    Ini                           (XVECTOR<XSTRING*>* execparams = NULL);
    virtual bool                    UpdateStep                    ();
    virtual bool                    End                           ();

    XVECTOR<XSTRING*>*              GetExecParams                 ();

    APPBASE_APPLICATIONMODE_TYPE    GetApplicationMode            ();
    void                            SetApplicationMode            (APPBASE_APPLICATIONMODE_TYPE applicationmode);

    void*                           GetApplicationHandle          ();
    void                            SetApplicationHandle          (void* handle);

    XSTRING*                        GetApplicationName            ();
    void                            SetApplicationName            (XCHAR* name);

    XSTRING*                        GetApplicationExecutable      ();
    void                            SetApplicationExecutable      (XCHAR* name);

    XSTRING*                        GetApplicationID              ();

    XTIMER*                         GetTimerGlobal                ();

    APPBASE_EXITTYPE                GetExitType                   ();
    void                            SetExitType                   (APPBASE_EXITTYPE exittype);
    bool                            GetExitTypeString             (XSTRING& exittypestring);

    XSYSTEM_CHANGESTATUSTYPE        GetSystemChangeStatus         ();
    void                            SetSystemChangeStatus         (XSYSTEM_CHANGESTATUSTYPE systemchangestatustype);

    virtual bool                    AppProc_PlatformIni           ();
    virtual bool                    AppProc_Ini                   ();
    virtual bool                    AppProc_FirstUpdate           ();
    virtual bool                    AppProc_Update                ();
    virtual bool                    AppProc_LastUpdate            ();
    virtual bool                    AppProc_EndBlockedResources   ();
    virtual bool                    AppProc_End                   ();
    virtual bool                    AppProc_PlatformEnd           ();

  protected:

    XVECTOR<XSTRING*>*              execparams;

    APPBASE_APPLICATIONMODE_TYPE    applicationmode;
    void*                           applicationhandle;
    XSTRING                         applicationname;
    XSTRING                         applicationexecutable;
    XSTRING                         applicationID;

    XTIMER*                         xtimerglobal;

    bool                            firstupdate;

    APPBASE_EXITTYPE                exittype;
    XSYSTEM_CHANGESTATUSTYPE        systemchangestatustype;

  private:

    void                            Clean                         ();
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif
