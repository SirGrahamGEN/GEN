/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOScraperWebWeather.cpp
* 
* @class      DIOSCRAPERWEBWEATHER
* @brief      Data Input/Output Scraper Web Weather class
* @ingroup    DATAIO
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
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIOScraperWebWeather.h"

#include "XThread.h"
#include "XTrace.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSCRAPERWEBWEATHER::DIOSCRAPERWEBWEATHER()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSCRAPERWEBWEATHER::DIOSCRAPERWEBWEATHER() : DIOSCRAPERWEB()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSCRAPERWEBWEATHER::~DIOSCRAPERWEBWEATHER()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSCRAPERWEBWEATHER::~DIOSCRAPERWEBWEATHER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSCRAPERWEBWEATHER::ChangeURL(XCHAR* maskurl, DIOURL& url)
* @brief      Change URL
* @ingroup    DATAIO
*
* @param[in]  maskurl :
* @param[in]  url :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSCRAPERWEBWEATHER::ChangeURL(XCHAR* maskurl, DIOURL& url)
{
  url.Format(maskurl, location.Get(), iscelsius?__L("units=metric"):__L("units=imperial"));

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSCRAPERWEBWEATHER::Get(XCHAR* location, bool iscelsius, XSTRING& condition, float& temperature, float& humidity, int timeoutforurl, XSTRING* localIP, bool usecache)
* @brief      Get
* @ingroup    DATAIO
*
* @param[in]  location :
* @param[in]  iscelsius :
* @param[in]  condition :
* @param[in]  temperature :
* @param[in]  humidity :
* @param[in]  timeoutforurl :
* @param[in]  localIP :
* @param[in]  usecache :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSCRAPERWEBWEATHER::Get(XCHAR* location, bool iscelsius, XSTRING& condition, float& temperature, float& humidity, int timeoutforurl, XSTRING* localIP, bool usecache)
{
  bool status = false;
  if(xmutexdo) xmutexdo->Lock();

  this->location  = location;
  this->iscelsius = iscelsius;

  if(Load(DIOSCRAPERWEBWEATHER_NAMEFILE))
    {
      if(Do(DIOSCRAPERWEBWEATHER_NAMESERVICE, timeoutforurl, localIP))
        {
          XSTRING temperaturestring;
          XSTRING humiditystring;

          condition         = GetValue(__L("CONDITION"));
          temperaturestring = GetValue(__L("TEMPERATURE"));
          humiditystring    = GetValue(__L("HUMIDITY"));

          if((!temperaturestring.IsEmpty()) && (!humiditystring.IsEmpty()))
            {
              temperature = temperaturestring.ConvertToFloat();
              humidity    = humiditystring.ConvertToFloat();

              status = true;
            }
        }

    }

  if(xmutexdo) xmutexdo->UnLock();

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSCRAPERWEBWEATHER::Get(XSTRING& location, bool iscelsius, XSTRING& condition, float& temperature, float& humidity, int timeout, XSTRING* localIP, bool usecache)
* @brief      Get
* @ingroup    DATAIO
*
* @param[in]  location :
* @param[in]  iscelsius :
* @param[in]  condition :
* @param[in]  temperature :
* @param[in]  humidity :
* @param[in]  timeout :
* @param[in]  localIP :
* @param[in]  usecache :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSCRAPERWEBWEATHER::Get(XSTRING& location, bool iscelsius,  XSTRING& condition, float& temperature, float& humidity, int timeout, XSTRING* localIP, bool usecache)
{
  return Get(location.Get(), iscelsius, condition, temperature, humidity, timeout, localIP, usecache);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSCRAPERWEBWEATHER::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSCRAPERWEBWEATHER::Clean()
{
  iscelsius = false;
}


#pragma endregion


