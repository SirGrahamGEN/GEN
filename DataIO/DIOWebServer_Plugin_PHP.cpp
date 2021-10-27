/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOWebServer_Plugin_PHP.cpp
*
* @class      DIOWEBSERVER_PLUGIN_PHP
* @brief      Data Input/Output Web Server PHP Plugin class
* @ingroup    DATAIO
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

#include "XFileTXT.h"
#include "XSystem.h"
#include "XTrace.h"

#include "DIOWebServer_QueryStrings.h"
#include "DIOWebServer.h"

#include "DIOWebServer_Plugin_PHP.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_PLUGIN_PHP::DIOWEBSERVER_PLUGIN_PHP()
* @brief      Constructor
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_PLUGIN_PHP::DIOWEBSERVER_PLUGIN_PHP()
{
  Clean();

  GetName()->Set(__L("PHP CGI Pluging"));

  // Only for extension.
  //SetTypeTAG(DIOWEBSERVER_PLUGIN_TYPE_TAGLABEL_PHP);
  //GetLabelTAG()->Set(DIOWEBSERVER_PLUGIN_PHP_TAGLABEL);

  PageExtension_Add(__L(".php"));
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_PLUGIN_PHP::~DIOWEBSERVER_PLUGIN_PHP()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_PLUGIN_PHP::~DIOWEBSERVER_PLUGIN_PHP()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_PLUGIN_PHP::Config(XPATH* pathinterpreter)
* @brief      Config
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  pathinterpreter :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_PLUGIN_PHP::Config(XPATH* pathinterpreter)
{
  XSTRING nameexec;

  nameexec = __L("php-cgi");
  #ifdef WINDOWS
  nameexec += __L(".exe");
  #endif

  return DIOWEBSERVER_PLUGIN_CGI::Config(pathinterpreter, nameexec.Get());
}





/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_PLUGIN_PHP::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_PLUGIN_PHP::Clean()
{

}

