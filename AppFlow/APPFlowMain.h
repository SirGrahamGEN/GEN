/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       APPFlowMain.h
* 
* @class      APPFLOWMAIN
* @brief      Application Flow Main Base class
* @ingroup    APPFLOW
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

#ifndef _APPFLOWMAIN_H_
#define _APPFLOWMAIN_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "APPFlowBase.h"

#include "MainProc.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

class APPFLOWBASE;

class APPFLOWMAIN
{
  public:
                                APPFLOWMAIN             ();
    virtual                    ~APPFLOWMAIN             ();

    APPFLOWBASE*                GetApplication          ();

    bool                        Create                  ();

    bool                        Ini                     (MAINPROC* mainproc, APPFLOWBASE_MODE_TYPE applicationmode = APPFLOWBASE_MODE_TYPE_UNKNOWN);
    bool                        Update                  ();
    bool                        End                     ();

    bool                        Delete                  ();

  protected:

    APPFLOWBASE*                application;

  private:

    void                        Clean                   ();

    MAINPROC*                   mainproc;
};

#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES

extern APPFLOWMAIN GEN_appmain;

#pragma endregion


#endif

