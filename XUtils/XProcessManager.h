/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XProcessManager.h
*
* @class      XPROCESSMANAGER
* @brief      eXtended process manager class
* @note       Can´t be construct Factory + singelton without depends of system. IT´S NOT A SINGLETON.
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

#ifndef _XPROCESSMANAGER_H_
#define _XPROCESSMANAGER_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XPath.h"
#include "XString.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/


class XPROCESS
{
  public:
                                    XPROCESS                        ();
    virtual                        ~XPROCESS                        ();

    XDWORD                          GetID                           ();
    void                            SetID                           (XDWORD handle);

    XPATH*                          GetPath                         ();
    XSTRING*                        GetName                         ();
    XSTRING*                        GetWindowTitle                  ();  

    bool                            CopyTo                          (XPROCESS& xprocess);    
    bool                            CopyFrom                        (XPROCESS& xprocess);    
    
  private:

    void                            Clean                           ();

    XDWORD                          ID;
    XPATH                           path;  
    XSTRING                         name;  
    XSTRING                         windowtitle;  
};



class XPROCESSMANAGER
{
  public:
                                    XPROCESSMANAGER                 ();
    virtual                        ~XPROCESSMANAGER                 ();

    static bool                     GetIsInstanced                  ();
    static XPROCESSMANAGER&         GetInstance                     ();
    static bool                     SetInstance                     (XPROCESSMANAGER* instance);
    static bool                     DelInstance                     ();

    virtual bool                    MakeSystemCommand               (XCHAR* command);    
    virtual bool                    MakeCommand                     (XCHAR* command, XSTRING* out = NULL, int* returncode = NULL);

    virtual bool                    ExecuteApplication              (XCHAR* applicationpath, XCHAR* params = NULL, XSTRING* in = NULL, XSTRING* out = NULL, int* returncode = NULL);

    virtual bool                    IsApplicationRunning            (XCHAR* command, XDWORD* ID = NULL);

    virtual bool                    GetApplicationRunningList       (XVECTOR<XPROCESS*>& applist);

    virtual bool                    TerminateApplication            (XDWORD processID, XDWORD  exitcode = 0);
    bool                            TerminateApplication            (XPROCESS& process, XDWORD exitcode = 0);
    bool                            TerminateApplication            (XCHAR* processname, XDWORD exitcode = 0);
    bool                            TerminateApplication            (XSTRING& processname, XDWORD exitcode = 0);

  private:

    void                            Clean                           ();

    static XPROCESSMANAGER*         instance;
};

/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif

