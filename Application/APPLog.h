/**-------------------------------------------------------------------------------------------------------------------
*
* @file       APPLog.h
*
* @class      APPLOG
* @brief      Application Log class
* @ingroup    APPLICATION
*
* @copyright  GEN Group. All right reserved.
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

#ifndef _APPLOG_H_
#define _APPLOG_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XPath.h"
#include "XString.h"
#include "XLog.h"


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define APP_LOG               APPLOG::GetInstance()
#define APP_LOG_ENTRY         GEN_XLOG.AddEntry

#define APP_LOG_SEPARATOR     __L("------------------------------------------------------------------------------------------")

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class APPCFG;


class APPLOG
{
  public:

    static bool                         GetIsInstanced                  ();
    static APPLOG&                      GetInstance                     ();
    static bool                         DelInstance                     ();

    bool                                Ini                             (APPCFG* cfg, XCHAR* applicationname, int appversion, int appsubversion, int appversionerror);

    bool                                End                             ();

  private:
                                        APPLOG                          ();
                                        APPLOG                          (APPLOG const&);        // Don't implement
    virtual                            ~APPLOG                          ();

    void                                operator =                      (APPLOG const&);        // Don't implement

    void                                Clean                           ();

    static APPLOG*                      instance;

    APPCFG*                             cfg;
};


/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif


