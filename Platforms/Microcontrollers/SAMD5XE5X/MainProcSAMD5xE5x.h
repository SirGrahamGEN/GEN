/**-------------------------------------------------------------------------------------------------------------------
*
* @file       MainProcSAMD5xE5x.h
*
* @class      MAINPROCSAMD5XE5X
* @brief      Main Procedure SAMD5xE5x class
* @ingroup    PLATFORM_SAMD5XE5X
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

#ifndef _MAINPROCSAMD5XE5X_H_
#define _MAINPROCSAMD5XE5X_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "APPBase.h"
#include "APPMain.h"

#include "MainProc.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XSTRING;

class MAINPROCSAMD5XE5X : public MAINPROC
{
  public:
                                  MAINPROCSAMD5XE5X     ();
    virtual                      ~MAINPROCSAMD5XE5X     ();

    bool                          Ini                   (APPMAIN* appmain = NULL);
    bool                          Update                ();
    bool                          End                   ();

  private:

    bool                          Factorys_Ini          (XSTRING* xpath = NULL);
    bool                          Factorys_End          ();

    void                          Clean                 ();
};

/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

extern "C" void     _read               ();
extern "C" void     _write              ();
extern "C" void     _gettimeofday       ();


#endif



