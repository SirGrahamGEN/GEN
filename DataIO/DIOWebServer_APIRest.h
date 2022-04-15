/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOWebServer_APIRest.h
*
* @class      DIOWEBSERVERAPIREST
* @brief      Data Input/Output Web Server API Rest class
* @ingroup
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

#ifndef _DIOWEBSERVER_APIREST_H_
#define _DIOWEBSERVER_APIREST_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XVector.h"

#include "DIOWebHeader.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class DIOWEBSERVER_REQUEST;
class DIOWEBSERVER_QUERYSTRINGS;
class XSTRING;

class DIOWEBSERVER_ENDPOINT
{
  public:
                                      DIOWEBSERVER_ENDPOINT       ();
    virtual                          ~DIOWEBSERVER_ENDPOINT       ();

  protected:

  private:

    void                              Clean                       ();
};



class DIOWEBSERVER_APIREST
{
  public:
                                      DIOWEBSERVER_APIREST        ();
    virtual                          ~DIOWEBSERVER_APIREST        ();

    virtual bool                      ResolveEndPoint             (DIOWEBSERVER_REQUEST* request, DIOWEBSERVER_QUERYSTRINGS* querystring, DIOWEBHEADER_RESULT* result, XSTRING* output);

  private:

    void                              Clean                       ();

    XVECTOR<DIOWEBSERVER_ENDPOINT*>   endpoints;
};



/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif

