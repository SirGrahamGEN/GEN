/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       MainProcESP32.cpp
* 
* @class      MAINPROCESP32
* @brief      Main Proc ESP32 class
* @ingroup    PLATFORM_ESP32
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

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "MainProcESP32.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "XESP32Factory.h"
#include "XESP32System.h"
#include "XESP32Rand.h"
#include "XESP32Sleep.h"
#include "XESP32Trace.h"
#include "XESP32EEPROMMemoryManager.h"

#ifdef DIO_ACTIVE
#include "DIOESP32Factory.h"

  #ifdef DIOGPIO_ACTIVE
  #include "DIOGPIO.h"
  #include "DIOESP32GPIO.h"
  #endif

#endif

#include "Version.h"

#include "XThreadListNonPreemptive.h"
#include "XTranslation_GEN.h"
#include "XTranslation.h"
#include "XPublisher.h"

#include "APPBase.h"
#include "APPMain.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

#pragma region GENERAL_VARIABLE
#ifdef XTRACE_ACTIVE
XESP32TRACE      ESP32trace;
#endif
MAINPROCESP32    mainprocstm32;

#pragma endregion

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         MAINPROCESP32::MAINPROCESP32()
* @brief      Constructor
* @ingroup    PLATFORM_ESP32
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
MAINPROCESP32::MAINPROCESP32()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         MAINPROCESP32::~MAINPROCESP32()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_ESP32 
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
MAINPROCESP32::~MAINPROCESP32()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MAINPROCESP32::Ini(APPMAIN* appmain)
* @brief      Ini
* @ingroup    PLATFORM_ESP32
*
* @param[in]  appmain :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool MAINPROCESP32::Ini(APPMAIN* appmain)
{
  this->appmain = appmain;

  if(!Factorys_Ini()) return false;

  #ifdef APP_ACTIVE

  if(!appmain)            return false;
  if(!appmain->Create())  return false;
  if(!appmain->Ini(this)) return false;

  #else

  if(Main_Proc_PlatformIni)
    {
      if(!Main_Proc_PlatformIni(this)) return false;
    }

  if(Main_Proc_Ini)
    {
      if(!Main_Proc_Ini(this)) return false;
    }

  #endif

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MAINPROCESP32::Update()
* @brief      Update
* @ingroup    PLATFORM_ESP32 
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool MAINPROCESP32::Update()
{
  #ifdef APP_ACTIVE
  if(appmain)
    {
      if(!appmain->Update()) return false;
    }
  #else
  if(Main_Proc_Update)
    {
      if(!Main_Proc_Update(this)) return false;
    }
  #endif

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MAINPROCESP32::End()
* @brief      End
* @ingroup    PLATFORM_ESP32 
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool MAINPROCESP32::End()
{
  #ifdef APP_ACTIVE

  if(appmain) appmain->End();

  #else

  if(Main_Proc_End)
    {
      if(!Main_Proc_End(this)) return false;
    }

  #endif

	#ifndef MICROCONTROLLER
  DeleteAllExecParams();
	#endif

  Factorys_End();

  #ifdef APP_ACTIVE

  if(appmain) appmain->Delete();

  #else

  if(Main_Proc_PlatformEnd)
    {
      if(!Main_Proc_PlatformEnd(this)) return false;
    }

  #endif
  
  VERSION::DelInstance();
  
  XFILE_DISPLAYNOTCLOSEFILES
  XMEMORY_CONTROL_DISPLAYMEMORYLEAKS

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MAINPROCESP32::Factorys_Ini(XSTRING* xpath)
* @brief      Factorys Ini
* @ingroup    PLATFORM_ESP32 
*
* @param[in]  xpath : always NULL in this platform
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool MAINPROCESP32::Factorys_Ini()
{
  if(!XFACTORY::SetInstance(new XESP32FACTORY())) return false;
  
  #ifdef XSYSTEM_ACTIVE  
  if(!XSYSTEM::SetInstance(new XESP32SYSTEM()))  return false;
  XBUFFER::SetHardwareUseLittleEndian(GEN_XSYSTEM.HardwareUseLittleEndian());
  #endif
  
  #ifdef XSLEEP_ACTIVE
  if(!XSLEEP::SetInstance(new XESP32SLEEP())) return false;
  #endif

  if(!XRAND::SetInstance(new XESP32RAND())) return false;
  
  
  #ifdef XEEPROMMEMORYMANAGER_ACTIVE  
  XEEPROMMEMORYMANAGER::SetInstance(new XESP32EEPROMMEMORYMANAGER());
  if(!XEEPROMMEMORYMANAGER::GetIsInstanced()) return false;  
  #endif

  #ifdef DIO_ACTIVE
  DIOFACTORY::SetInstance(new DIOESP32FACTORY());
  if(!DIOFACTORY::GetIsInstanced()) return false;

    #ifdef DIOGPIO_ACTIVE
    DIOGPIO::SetInstance(new DIOESP32GPIO());
    if(!DIOGPIO::GetIsInstanced()) return false;

    if(!DIOGPIO::GetInstance().Ini()) return false;
    #endif

  #endif

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MAINPROCESP32::Factorys_End()
* @brief      Factorys End
* @ingroup    PLATFORM_ESP32 
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool MAINPROCESP32::Factorys_End()
{
  #ifdef DIO_ACTIVE

    #ifdef DIOGPIO_ACTIVE
    if(DIOGPIO::GetIsInstanced())
      {
        DIOGPIO::GetInstance().End();
        DIOGPIO::DelInstance();
      }
    #endif

  if(DIOFACTORY::GetIsInstanced()) DIOFACTORY::DelInstance();
  #endif
    
  #ifdef XEEPROMMEMORYMANAGER_ACTIVE    
  if(XEEPROMMEMORYMANAGER::GetIsInstanced()) XEEPROMMEMORYMANAGER::DelInstance();
  #endif
  
  #ifdef XEEPROMMEMORYMANAGER_ACTIVE
  XEEPROMMEMORYMANAGER::DelInstance();
  #endif
  
  XPATHSMANAGER::DelInstance();

  XTRANSLATION::DelInstance();
  XTRANSLATION_GEN::DelInstance();
  
  XRAND::DelInstance();

  #ifdef XSLEEP_ACTIVE
  XSLEEP::DelInstance();
  #endif

  #ifdef XSYSTEM_ACTIVE  
  XSYSTEM::DelInstance();
  #endif
  
  #ifdef XPUBLISHER_ACTIVE
  XPUBLISHER::DelInstance();
  #endif
    
  #ifdef XTHREADCOLLECTED_ACTIVE
  XTHREADSCOLLECTEDMANAGER::DelInstance();
  #endif

  XFACTORY::DelInstance();
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void MAINPROCESP32::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_ESP32 
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void MAINPROCESP32::Clean()
{

}

#pragma endregion


/*---- MAIN FUNCTIONS ------------------------------------------------------------------------------------------------*/
#pragma region MAIN FUNCTIONS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int main()
* @brief      main
* @ingroup    PLATFORM_ESP32 
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int main()
{
  int status = 0;

  if(mainprocstm32.Ini(&GEN_appmain))
    {
      while(mainprocstm32.Update())
        {

        }

    } else status = 1;

  if(!mainprocstm32.End()) status = 1;

  return status;
}

#pragma endregion
