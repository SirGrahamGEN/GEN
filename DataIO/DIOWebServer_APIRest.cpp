/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOWebServer_APIRest.cpp
*
* @class      DIOWEBSERVER_APIREST
* @brief      Data Input/Output Web Server API Rest class
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "DIOWebServer_APIRest.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------------------------------------------------*/
/* DIOWEBSERVER_ENDPOINT                                                                                              */
/*--------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_ENDPOINT::DIOWEBSERVER_ENDPOINT()
* @brief      Constructor
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_ENDPOINT::DIOWEBSERVER_ENDPOINT()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_ENDPOINT::~DIOWEBSERVER_ENDPOINT()
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
DIOWEBSERVER_ENDPOINT::~DIOWEBSERVER_ENDPOINT()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_ENDPOINT::Clean()
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
void DIOWEBSERVER_ENDPOINT::Clean()
{

}



/*--------------------------------------------------------------------------------------------------------------------*/
/* DIOWEBSERVER_APIREST                                                                                               */
/*--------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_APIREST::DIOWEBSERVER_APIREST()
* @brief      Constructor
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_APIREST::DIOWEBSERVER_APIREST()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_APIREST::~DIOWEBSERVER_APIREST()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_APIREST::~DIOWEBSERVER_APIREST()
{
  Clean();
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_APIREST::ResolveEndPoint(DIOWEBSERVER_REQUEST* request, DIOWEBSERVER_QUERYSTRINGS* querystring, DIOWEBHEADER_RESULT& result, XSTRING* output)
* @brief      ResolveEndPoint
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  request :
* @param[in]  querystring :
* @param[in]  result :
* @param[in]  output :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_APIREST::ResolveEndPoint(DIOWEBSERVER_REQUEST* request, DIOWEBSERVER_QUERYSTRINGS* querystring, DIOWEBHEADER_RESULT* result, XSTRING* output)
{
  //output->Set(__L("Prueba"));




  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_APIREST::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    APPLICATION
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_APIREST::Clean()
{

}
