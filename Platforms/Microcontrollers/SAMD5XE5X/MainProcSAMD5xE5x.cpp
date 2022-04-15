/**-------------------------------------------------------------------------------------------------------------------
*
* @file       MainProcSAMD5xE5x.cpp
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "XSAMD5xE5x_HAL.h"
#include "XSAMD5xE5xFactory.h"
#include "XSAMD5xE5xSystem.h"
#include "XSAMD5xE5xSleep.h"
#include "XSAMD5xE5xTrace.h"

#ifdef DIO_ACTIVE
#include "DIOSAMD5xE5xFactory.h"
#endif

#include "XThreadListNonPreemptive.h"
#include "APPBase.h"

#include "MainProcSAMD5xE5x.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

#ifdef XTRACE_ACTIVE
XSAMD5XE5XTRACE      SAMD5XE5Xtrace;
#endif
MAINPROCSAMD5XE5X        mainsamd5xe5x;


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         MAINPROCSAMD5XE5X::MAINPROCSAMD5XE5X()
* @brief      Constructor
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
MAINPROCSAMD5XE5X::MAINPROCSAMD5XE5X()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         MAINPROCSAMD5XE5X::~MAINPROCSAMD5XE5X()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
MAINPROCSAMD5XE5X::~MAINPROCSAMD5XE5X()
{
  Clean();
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MAINPROCSAMD5XE5X::Ini()
* @brief      Ini
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool MAINPROCSAMD5XE5X::Ini(APPMAIN* appmain)
{
  this->appmain = appmain;

  if(!Factorys_Ini()) return false;

  #ifdef APP_ACTIVE

  if(!appmain)            return false;
  if(!appmain->Create())  return false;

  #else

  if(Main_Proc_PlatformIni)
    {
      if(!Main_Proc_PlatformIni()) return false;
    }

  #endif

  #ifdef XTRACE_ACTIVE
  SAMD5XE5Xtrace.IniUARTSpecial();
  #endif

  #ifdef APP_ACTIVE

  if(appmain)
    {
      if(!appmain->Ini(this)) return false;
    }

  #else

  if(Main_Proc_Ini)
    {
      if(!Main_Proc_Ini(this)) return false;
    }

  #endif

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MAINPROCSAMD5XE5X::Update()
* @brief      Update
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool MAINPROCSAMD5XE5X::Update()
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
* @fn         bool MAINPROCSAMD5XE5X::End()
* @brief      End
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool MAINPROCSAMD5XE5X::End()
{
  #ifdef APP_ACTIVE

  if(appmain) appmain->End();

  #else

  if(Main_Proc_End)
    {
      if(!Main_Proc_End(this)) return false;
    }

  #endif

  DeleteAllExecParams();

  Factorys_End();

  #ifdef APP_ACTIVE

  if(appmain) appmain->Delete();

  #else

  if(Main_Proc_PlatformEnd)
    {
      if(!Main_Proc_PlaformEnd()) return false;
    }

  #endif


  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MAINPROCSAMD5XE5X::Factorys_Ini(XSTRING* xpath)
* @brief      Factorys Ini
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  xpath : always NULL in this platform
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool MAINPROCSAMD5XE5X::Factorys_Ini(XSTRING* xpath)
{
  XFACTORY::SetInstance(new XSAMD5XE5XFACTORY());
  if(!XFACTORY::GetIsInstanced()) return false;

  XSLEEP::SetInstance(new XSAMD5XE5XSLEEP());
  if(!XSLEEP::GetIsInstanced()) return false;

  XSYSTEM::SetInstance(new XSAMD5XE5XSYSTEM());
  if(!XSYSTEM::GetIsInstanced()) return false;

  #ifdef DIO_ACTIVE
  DIOFACTORY::SetInstance(new DIOSAMD5XE5XFACTORY());
  if(!DIOFACTORY::GetIsInstanced()) return false;
  #endif

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool MAINPROCSAMD5XE5X::Factorys_End()
* @brief      Factorys End
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool MAINPROCSAMD5XE5X::Factorys_End()
{
  #ifdef DIO_ACTIVE
  if(DIOFACTORY::GetIsInstanced()) DIOFACTORY::DelInstance();
  #endif

  if(XSLEEP::GetIsInstanced()) XSLEEP::DelInstance();

  if(XSYSTEM::GetIsInstanced()) XSYSTEM::DelInstance();

  if(XFACTORY::GetIsInstanced()) XFACTORY::DelInstance();

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void MAINPROCSAMD5XE5X::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void MAINPROCSAMD5XE5X::Clean()
{

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void _read()
* @brief      read
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void _read()
{


}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void _write()
* @brief      write
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void _write()
{


}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void _gettimeofday()
* @brief      gettimeofday
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void _gettimeofday()
{

}





/**-------------------------------------------------------------------------------------------------------------------
*
* Main entrys: main
*
*---------------------------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int main()
* @brief      main
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int main(void)
{
  int status = 0;

  if(mainsamd5xe5x.Ini(&GEN_appmain))
    {
      while(mainsamd5xe5x.Update())
        {

        }

    } else status = 1;

  if(!mainsamd5xe5x.End()) status = 1;

  return status;
}


