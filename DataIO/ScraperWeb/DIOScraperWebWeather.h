/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOScraperWebWeather.h
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

#ifndef _DIOSCRAPERWEBWEATHER_H_
#define _DIOSCRAPERWEBWEATHER_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIOURL.h"
#include "DIOScraperWeb.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

#define DIOSCRAPERWEBWEATHER_NAMEFILE       __L("ws_weather.xml")
#define DIOSCRAPERWEBWEATHER_NAMESERVICE    __L("WEATHER")

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class DIOSCRAPERWEBWEATHER : public DIOSCRAPERWEB
{
  public:
                            DIOSCRAPERWEBWEATHER          ();
    virtual                ~DIOSCRAPERWEBWEATHER          ();

    bool                    ChangeURL                     (XCHAR* maskurl, DIOURL& url);

    bool                    Get                           (XCHAR* location, bool iscelsius, XSTRING& condition, float& temperature, float& humidity, int timeoutforurl = DIOSCRAPERWEB_MAXTIMEOUTFORURL, XSTRING* localIP = NULL, bool usecache = true);
    bool                    Get                           (XSTRING& location, bool iscelsius, XSTRING& condition, float& temperature, float& humidity, int timeoutforurl = DIOSCRAPERWEB_MAXTIMEOUTFORURL, XSTRING* localIP = NULL, bool usecache = true);

  private:

    void                    Clean                         ();

    XSTRING                 location;
    bool                    iscelsius;
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

