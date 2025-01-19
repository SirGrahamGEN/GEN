/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOWebServer_Plugin_PHP.cpp
* 
* @class      DIOWEBSERVER_PLUGIN_PHP
* @brief      Data Input/Output Web Server PHP Plugin class
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

#include "DIOWebServer_Plugin_PHP.h"

#include "XFileTXT.h"
#include "XSystem.h"
#include "XTrace.h"

#include "DIOWebServer_QueryStrings.h"
#include "DIOWebServer.h"

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
* @fn         DIOWEBSERVER_PLUGIN_PHP::DIOWEBSERVER_PLUGIN_PHP()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* @param[in]  pathinterpreter :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_PLUGIN_PHP::Clean()
{

}


#pragma endregion


