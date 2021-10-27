/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XSystemPhone.cpp
*
* @class      XSYSTEMPHONE
* @brief
* @ingroup    UTILS
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XSystemPhone.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

XSYSTEMPHONE* XSYSTEMPHONE::instance = NULL;

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSYSTEMPHONELAC::XSYSTEMPHONELAC()
* @brief      Constructor
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XSYSTEMPHONELAC::XSYSTEMPHONELAC()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSYSTEMPHONELAC::~XSYSTEMPHONELAC()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XSYSTEMPHONELAC::~XSYSTEMPHONELAC()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSYSTEMPHONELAC::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XSYSTEMPHONELAC::Clean()
{
  LAC    = 0;
  cellid = 0;
  MCC    = 0;
  MNC    = 0;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSYSTEMPHONE::XSYSTEMPHONE()
* @brief      Constructor
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XSYSTEMPHONE::XSYSTEMPHONE()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSYSTEMPHONE::~XSYSTEMPHONE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XSYSTEMPHONE::~XSYSTEMPHONE()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSYSTEMPHONE::GetIsInstanced()
* @brief      Get if Is Instanced
* @note       STATIC
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XSYSTEMPHONE::GetIsInstanced()
{
  return instance!=NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSYSTEMPHONE& XSYSTEMPHONE::GetInstance()
* @brief      Get Instance of XSYSTEMPHONE
* @note       STATIC
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XSYSTEMPHONE& :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSYSTEMPHONE& XSYSTEMPHONE::GetInstance()
{
  if(!instance) instance = new XSYSTEMPHONE();

  return (*instance);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSYSTEMPHONE::SetInstance(XSYSTEMPHONE* instance)
* @brief      Set Instance of XSYSTEMPHONE
* @note       STATIC
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  _instance : new instance
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XSYSTEMPHONE::SetInstance(XSYSTEMPHONE* _instance)
{
  if(!_instance) return false;

  instance = _instance;

  return (instance)?true:false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSYSTEMPHONE::DelInstance()
* @brief      Delete Instance of XSYSTEMPHONE
* @note       STATIC
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XSYSTEMPHONE::DelInstance()
{
  if(instance)
    {
      delete instance;
      instance = NULL;

      return true;
    }

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSYSTEMPHONE::GetIMEI(XBYTE* IMEI)
* @brief      GetIMEI
* @note       VIRTUAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  IMEI :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XSYSTEMPHONE::GetIMEI(XBYTE* IMEI)
{
  if(!IMEI) return false;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSYSTEMPHONE::GetGSMLAC(XPHONELAC* lac)
* @brief      GetGSMLAC
* @note       VIRTUAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  lac :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XSYSTEMPHONE::GetGSMLAC(XSYSTEMPHONELAC* lac)
{
  if(!lac) return false;

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSYSTEMPHONE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XSYSTEMPHONE::Clean()
{

}