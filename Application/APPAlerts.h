/**-------------------------------------------------------------------------------------------------------------------
*
* @file       APPAlerts.h
*
* @class      APPALERTS
* @brief      Application Alerts class
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

#ifndef _APPALERTS_H_
#define _APPALERTS_H_

#ifdef DIO_ALERTS_ACTIVE

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XPath.h"
#include "XString.h"

#include "DIOAlerts.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum APP_ALERT_TYPE
{
  APP_ALERT_TYPE_SMTP              = 0 ,
  APP_ALERT_TYPE_SMS                   ,
  APP_ALERT_TYPE_WEB                   ,
  APP_ALERT_TYPE_UDP                   ,

  APP_ALERT_TYPE_MAX
};


enum APP_ALERT_STATUS
{
  APP_ALERT_STATUS_NOTACTIVATED    = 0 ,  
  APP_ALERT_STATUS_NOTRECIPIENTS       ,
  APP_ALERT_STATUS_NOTCONFIG           ,  
  APP_ALERT_STATUS_ACTIVE              ,  
};


#define APP_ALERTS_WEBALERTCMD   __L("alert")

#define APP_ALERTS               APPALERTS ::GetInstance()

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class DIOSTREAM;
class APPCFG;

class APPALERTS
{
  public:

    static bool                         GetIsInstanced                  ();
    static APPALERTS&                   GetInstance                     ();
    static bool                         DelInstance                     ();

    bool                                Ini                             (APPCFG* cfg, XCHAR* applicationname, int appversion, int appsubversion, int appsubversionerror, int status[APP_ALERT_TYPE_MAX], DIOSTREAM* streamSMS = NULL);
    int                                 Send                            (XDWORD senders, XDWORD condition, DIOALERTLEVEL level, XCHAR* title, XCHAR* message);
    bool                                End                             ();

  private:
                                        APPALERTS                       ();
                                        APPALERTS                       (APPALERTS const&);        // Don't implement
    virtual                            ~APPALERTS                       ();

    void                                operator =                      (APPALERTS const&);        // Don't implement

    void                                Clean                           ();

    static APPALERTS*                   instance;

    APPCFG*                             cfg;
};

/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif

#endif
