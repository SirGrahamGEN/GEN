/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XSleep.cpp
* 
* @class      XSLEEP
* @brief      eXtended Utils Sleep class
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XSleep.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

XSLEEP* XSLEEP::instance = NULL;

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSLEEP::XSLEEP()
* @brief      Constructor
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XSLEEP::XSLEEP()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSLEEP::~XSLEEP()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XSLEEP::~XSLEEP()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSLEEP::GetIsInstanced()
* @brief      Get if Is Instanced
* @note       STATIC
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSLEEP::GetIsInstanced()
{
  return instance!=NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSLEEP& XSLEEP::GetInstance()
* @brief      Get Instance of XSLEEP
* @note       STATIC
* @ingroup    XUTILS
*
* @return     XSLEEP& :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSLEEP& XSLEEP::GetInstance()
{
  if(!instance) instance = new XSLEEP();

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSLEEP::SetInstance(XSLEEP* _instance)
* @brief      Set Instance of XSLEEP
* @note       STATIC
* @ingroup    XUTILS
*
* @param[in]  _instance : new instance
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSLEEP::SetInstance(XSLEEP* _instance)
{
  if(!_instance) return false;

  instance = _instance;

  return (instance)?true:false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSLEEP::DelInstance()
* @brief      Delete Instance of XSLEEP
* @note       STATIC
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSLEEP::DelInstance()
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
* @fn         void XSLEEP::Seconds(int seconds)
* @brief      Seconds
* @note       VIRTUAL
* @ingroup    XUTILS
*
* @param[in]  seconds :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XSLEEP::Seconds(int seconds)
{

}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSLEEP::MilliSeconds(int milliseconds)
* @brief      MilliSeconds
* @ingroup    XUTILS
*
* @param[in]  milliseconds :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XSLEEP::MilliSeconds(int milliseconds)
{

}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSLEEP::MicroSeconds(int microseconds)
* @brief      MicroSeconds
* @note       VIRTUAL
* @ingroup    XUTILS
*
* @param[in]  microseconds :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XSLEEP::MicroSeconds(int microseconds)
{


}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSLEEP::NanoSeconds(int nanoseconds)
* @brief      NanoSeconds
* @note       VIRTUAL
* @ingroup    XUTILS
*
* @param[in]  nanoseconds :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XSLEEP::NanoSeconds(int nanoseconds)
{

}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSLEEP::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XSLEEP::Clean()
{

}


#pragma endregion

