/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       GEN_Defines.h
* 
* @class      GEN_DEFINES
* @brief      GEN Defines precompilated
* @ingroup    COMMON
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

#ifndef _GEN_DEFINES_H_
#define _GEN_DEFINES_H_


/*---- DEFINE GROUPS DOXYGEN -----------------------------------------------------------------------------------------*/
#pragma region DEFINES_GROUPS_DOXYGEN
/**
* 
* @defgroup APPFLOW AppFlow
* @{
* 
* @}
*
* @defgroup CIPHER Cipher
* @{
* 
* @}
* 
* @defgroup COMMON Common
* @{
* 
* @}
*
*
* @defgroup COMPRESS Compress
* @{
* 
* @}
* 
* @defgroup DATABASE Database
* @{
* 
* @}
*
* @defgroup DATAIO Data Input/Output
* @{
* 
* @}
* 
* @defgroup GRAPHIC Graphics
* @{
* 
* @}
*
* @defgroup IDENTIFICATION Identification
* @{
* 
* @}
*
* @defgroup INPUT Input 
* @{
* 
* @}
*
* @defgroup MAIN_PROCEDURE Main Procedure
* @{
* 
* @}
*
* @defgroup SCRIPT Script
* @{
* 
* @}
*
* @defgroup SOUND Sound
* @{
* 
* @}
*
* @defgroup USERINTERFACE User Interface
* @{
* 
* @}
*
* @defgroup XUTILS eXtended Utils
* @{
* 
* @}
* 
* -------------------------------------------------------------------
* 
* @defgroup EXAMPLES Examples
* @{
* 
* @} 
* 
* @defgroup TESTS Tests
* @{
* 
* @}
* 
* @defgroup UNIT_TESTS Unit Tests
* @{
* 
* @}
* 
* -------------------------------------------------------------------
*  
* @defgroup PLATFORM_WINDOWS Platform Windows
* @{
* 
* @}
*
* @defgroup PLATFORM_LINUX Platform Linux
* @{
* 
* @}
*
* @defgroup PLATFORM_ANDROID Platform Android
* @{
* 
* @}
*
* @defgroup PLATFORM_COMMON Platform Common
* @{
* 
* @}
*
* @defgroup PLATFORM_STM32 Platform STM32
* @{
* 
* @}
*
* @defgroup PLATFORM_ESP32 Platform ESP32
* @{
* 
* @}
* @defgroup PLATFORM_SAMD5XE5X Platform SAMD5XE5X 
* @{
* 
* @}
* 
* -------------------------------------------------------------------
*     
* @defgroup APPLICATION Application
* @{
* 
* @}
*
*/


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "FactoryBase.h"
#include "APP_GEN_Defines.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

#ifndef UNICODE
#define UNICODE
#endif


// --- Macros eXtensions --------------------------------------------------------------------------

#ifndef GEN_XFACTORY
#define GEN_XFACTORY                      XFACTORY::GetInstance()
#endif

#ifndef GEN_XFACTORY_CREATE
#define GEN_XFACTORY_CREATE(var, func)    var = GEN_XFACTORY.func;      \
                                          FACTORY_MODULE(var)
                                            
#endif


// --- Macros SINGLETON ---------------------------------------------------------------------------

#ifndef GEN_XSLEEP
#define GEN_XSLEEP                        XSLEEP::GetInstance()
#endif

#ifndef GEN_XRAND
#define GEN_XRAND                         XRAND::GetInstance()
#endif

#ifndef GEN_XLOG
#define GEN_XLOG                          XLOG::GetInstance()
#endif

#ifndef GEN_XSYSTEM
#define GEN_XSYSTEM                       XSYSTEM::GetInstance()
#endif

#ifndef GEN_XPROCESSMANAGER
#define GEN_XPROCESSMANAGER               XPROCESSMANAGER::GetInstance()
#endif

#ifndef GEN_XPATHSMANAGER
#define GEN_XPATHSMANAGER                 XPATHSMANAGER::GetInstance()
#endif

#ifndef GEN_XTRANSLATION
#define GEN_XTRANSLATION                  XTRANSLATION::GetInstance()
#endif

#ifndef GEN_XPUBLISHER
#define GEN_XPUBLISHER                    XPUBLISHER::GetInstance()
#endif

#ifndef GEN_XSHAREDMEMORYMANAGER
#define GEN_XSHAREDMEMORYMANAGER          XSHAREDMEMORYMANAGER::GetInstance()
#endif

#ifndef GEN_XDRIVEIMAGEMANAGER
#define GEN_XDRIVEIMAGEMANAGER            XDRIVEIMAGEMANAGER::GetInstance()
#endif

#ifndef GEN_XEEPROMMEMORYMANAGER
#define GEN_XEEPROMMEMORYMANAGER          XEEPROMMEMORYMANAGER::GetInstance()
#endif

#ifndef GEN_DIOOSPIPELINE
#define GEN_DIOOSPIPELINE                   DIOOSPIPELINE::GetInstance()
#endif

// --- Data Input/Output Manager ------------------------------------------------------------------

#ifndef GEN_DIOFACTORY
#define GEN_DIOFACTORY                    DIOFACTORY::GetInstance()
#endif

// Macros SINGLETON

#ifndef GEN_DIOGPIO
#define GEN_DIOGPIO                       DIOGPIO::GetInstance()
#endif

#ifndef GEN_DIODNSRESOLVER
#define GEN_DIODNSRESOLVER                DIODNSRESOLVER::GetInstance()
#endif

#ifndef GEN_DIOPING
#define GEN_DIOPING                       DIOPING::GetInstance()
#endif

#ifndef GEN_DIOPUBLICINTERNETIP
#define GEN_DIOPUBLICINTERNETIP           DIOPUBLICINTERNETIP::GetInstance()
#endif

#ifndef GEN_DIOALERTS
#define GEN_DIOALERTS                     DIOALERTS::GetInstance()
#endif

// --- AppFlow ------------------------------------------------------------------------------------

#ifndef GEN_APPFLOWALERTS
#define GEN_APPFLOWALERTS                 APPFLOWALERTS::GetInstance()
#endif


// --- Common -------------------------------------------------------------------------------------

#ifndef GEN_VERSION
#define GEN_VERSION                       VERSIONFRAMEWORK::GetInstance()
#endif

#ifndef GEN_SET_VERSION
#define GEN_SET_VERSION(name, nameexec, version, subversion, versionerror, owner, creationyear)   GEN_VERSION.SetAppVersion(name, nameexec, version, subversion, versionerror, owner, creationyear);
#endif

#ifndef GEN_VERSION_CLEAN
#define GEN_VERSION_CLEAN                 VERSIONFRAMEWORK::GetInstance().Clean();
#endif


// --- Graphics Manager ---------------------------------------------------------------------------

#ifndef GEN_GRPFACTORY
#define GEN_GRPFACTORY                    GRPFACTORY::GetInstance()
#endif


// --- Input Manager ------------------------------------------------------------------------------

#ifndef GEN_INPFACTORY
#define GEN_INPFACTORY                    INPFACTORY::GetInstance()
#endif

#ifndef GEN_INPMANAGER
#define GEN_INPMANAGER                    INPMANAGER::GetInstance()
#endif


// --- User Interface manager ---------------------------------------------------------------------

#ifndef GEN_USERINTERFACE
#define GEN_USERINTERFACE                 UI_MANAGER::GetInstance()
#endif


// --- Script -------------------------------------------------------------------------------------

#ifndef GEN_SCRIPT_CACHE
#define GEN_SCRIPT_CACHE                  SCRIPT_CACHE::GetInstance()
#endif


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

