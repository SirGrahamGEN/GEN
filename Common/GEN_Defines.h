/**-------------------------------------------------------------------------------------------------------------------
*
* @file       GEN_Defines.h
*
* @class      GEN_DEFINES
* @brief      GEN Defines precompilated
* @ingroup
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @copyright  Copyright(c) 2008 - 2016 GEN Group.
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

#ifndef _GEN_DEFINES_H_
#define _GEN_DEFINES_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "APP_GEN_Defines.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

/*
#ifdef WINDOWS

  #ifdef _MSC_VER  // Is Visual Studio 6.0 or .NET?

  #pragma warning (disable : 4091)   // warning C4091: 'typedef ': ignored on left of '---' when no variable is declared
//#pragma warning (disable : 4595)   // warning C4595: non-member operator new or delete functions may not be declared inline
  #pragma warning (disable : 4996)   // warning C4996: was declared deprecated
  #pragma warning (disable : 4067)   // warning LNK4067: ambiguous entry point; selected 'mainCRTStartup'
  #endif

#endif
*/

#ifndef UNICODE
#define UNICODE
#endif


// ------------------------------------------------------------------------------------------------
// Macros SINGLETON

// --- eXtensions ---------------------------------------------------------------------------------



#ifndef GEN_XFACTORY
#define GEN_XFACTORY              XFACTORY::GetInstance()
#endif

#ifndef GEN_XSLEEP
#define GEN_XSLEEP                XSLEEP::GetInstance()
#endif

#ifndef GEN_XLOG
#define GEN_XLOG                  XLOG::GetInstance()
#endif

#ifndef GEN_XSYSTEM
#define GEN_XSYSTEM               XSYSTEM::GetInstance()
#endif

#ifndef GEN_XPROCESSMANAGER
#define GEN_XPROCESSMANAGER       XPROCESSMANAGER::GetInstance()
#endif

#ifndef GEN_XPATHSMANAGER
#define GEN_XPATHSMANAGER         XPATHSMANAGER::GetInstance()
#endif

#ifndef GEN_XTRANSLATION
#define GEN_XTRANSLATION          XTRANSLATION::GetInstance()
#endif

#ifndef GEN_XPUBLISHER
#define GEN_XPUBLISHER            XPUBLISHER::GetInstance()
#endif

#ifndef GEN_XSHAREDMEMORYMANAGER
#define GEN_XSHAREDMEMORYMANAGER  XSHAREDMEMORYMANAGER::GetInstance()
#endif

#ifndef GEN_XDRIVEIMAGEMANAGER
#define GEN_XDRIVEIMAGEMANAGER    XDRIVEIMAGEMANAGER::GetInstance()
#endif

#ifndef GEN_XEEPROMMEMORYMANAGER
#define GEN_XEEPROMMEMORYMANAGER  XEEPROMMEMORYMANAGER::GetInstance()
#endif

// --- Data Input/Output Manager ------------------------------------------------------------------

#ifndef GEN_DIOFACTORY
#define GEN_DIOFACTORY            DIOFACTORY::GetInstance()
#endif

#ifndef GEN_DIOGPIO
#define GEN_DIOGPIO               DIOGPIO::GetInstance()
#endif

#ifndef GEN_DIODNSRESOLVED
#define GEN_DIODNSRESOLVED        DIODNSRESOLVED::GetInstance()
#endif

#ifndef GEN_DIOALERTS
#define GEN_DIOALERTS             DIOALERTS::GetInstance()
#endif

#ifndef GEN_APPALERTS
#define GEN_APPALERTS             APPALERTS::GetInstance()
#endif

// --- Graphics Manager ---------------------------------------------------------------------------

#ifndef GEN_GRPFACTORY
#define GEN_GRPFACTORY            GRPFACTORY::GetInstance()
#endif


// --- Input Manager ------------------------------------------------------------------------------

#ifndef GEN_INPMANAGER
#define GEN_INPMANAGER            INPMANAGER::GetInstance()
#endif


// --- User Interface manager ---------------------------------------------------------------------

#ifndef GEN_USERINTERFACE
#define GEN_USERINTERFACE         UI_MANAGER::GetInstance()
#endif

// ------------------------------------------------------------------------------------------------


/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/



#endif


