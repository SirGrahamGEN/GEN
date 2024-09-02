/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       APPExtended.h
* 
* @class      APPEXTENDED
* @brief      Application Extended class
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

#ifndef _APPEXTENDED_H_
#define _APPEXTENDED_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XPath.h"
#include "XString.h"
#include "XLog.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

#define APP_EXTENDED             APPEXTENDED::GetInstance()

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

class XCONSOLE;
class XTHREAD;
class APPCFG;
class APPCONSOLE;
class APPEXTENDED_APPLICATIONSTATUS;
class APPEXTENDED_INTERNETSTATUS;

class APPEXTENDED
{
  public:

    static bool                         GetIsInstanced                  ();
    static APPEXTENDED&                 GetInstance                     ();
    static bool                         DelInstance                     ();

    bool                                APPStart                        (APPCFG* appcfg, APPCONSOLE* appconsole = NULL);
    bool                                APPEnd                          ();
    
    APPCFG*                             GetAppCFG                       ();
    APPCONSOLE*                         GetAppConsole                   ();

    #ifdef APP_EXTENDED_APPLICATIONSTATUS_ACTIVE
    APPEXTENDED_APPLICATIONSTATUS*      GetApplicationStatus            (); 
    #endif

    #ifdef APP_EXTENDED_INTERNETSTATUS_ACTIVE
    APPEXTENDED_INTERNETSTATUS*         GetInternetStatus               (); 
    #endif

    bool                                ShowAll                         ();
         
  private:
                                        APPEXTENDED                     ();
                                        APPEXTENDED                     (APPEXTENDED const&);        // Don't implement
    virtual                            ~APPEXTENDED                     ();

    void                                operator =                      (APPEXTENDED const&);        // Don't implement

    static void                         ThreadFunction_Update       (void* param);

    void                                Clean                           ();

    static APPEXTENDED*                 instance;

    APPCFG*                             appcfg;
    APPCONSOLE*                         appconsole;
    
    XMUTEX*                             updatemutex;
    XTHREAD*                            updatethread;  
    bool                                exitincurse;
    
    #ifdef APP_EXTENDED_APPLICATIONSTATUS_ACTIVE
    APPEXTENDED_APPLICATIONSTATUS*      applicationstatus;
    #endif

    #ifdef APP_EXTENDED_INTERNETSTATUS_ACTIVE
    APPEXTENDED_INTERNETSTATUS*         internetstatus;
    #endif
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

