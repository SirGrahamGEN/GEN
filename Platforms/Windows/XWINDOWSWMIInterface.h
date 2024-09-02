/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XWINDOWSWMIInterface.h
* 
* @class      XWINDOWSWMIINTERFACE
* @brief      WINDOWS eXtended Utils Management Instrumentation Interface class
* @ingroup    PLATFORM_WINDOWS
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

#ifndef _XWINDOWSWMIINTERFACE_H_
#define _XWINDOWSWMIINTERFACE_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XVector.h"
#include "XString.h"
#include "XVariant.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

enum XWINDOWSWMIINTERFACE_ERROR
{
  XWINDOWSWMIINTERFACE_ERROR_NONE                          = 0  ,
  XWINDOWSWMIINTERFACE_ERROR_BADQUERYFAILURE                    ,
  XWINDOWSWMIINTERFACE_ERROR_PROPERTYEXTRACTIONFAILURE          ,
  XWINDOWSWMIINTERFACE_ERROR_COMINITIALIZATIONFAILURE           ,
  XWINDOWSWMIINTERFACE_ERROR_SECURITYINITIALIZATIONFAILURE      ,
  XWINDOWSWMIINTERFACE_ERROR_IWBEMLOCATORFAILURE                ,
  XWINDOWSWMIINTERFACE_ERROR_IWBEMSERVICECONNECTIONFAILURE      ,
  XWINDOWSWMIINTERFACE_ERROR_BLANKETPROXYSETFAILURE             ,
};

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class XWINDOWSWMIINTERFACE_RESULT
{
  public:
                                    XWINDOWSWMIINTERFACE_RESULT       ();
    virtual                        ~XWINDOWSWMIINTERFACE_RESULT       ();

    XVECTOR<XSTRING*>*              GetResultsString                  ();
    XVECTOR<XVARIANT*>*             GetResultsVariant                 ();

    void                            DeleteAllResults                  ();

    XWINDOWSWMIINTERFACE_ERROR      GetError                          ();
    void                            SetError                          (XWINDOWSWMIINTERFACE_ERROR error);

    XSTRING*                        GetErrorDescription               ();


  private:

    void                            Clean                             ();

    XVECTOR<XSTRING*>               resultsstring;
    XVECTOR<XVARIANT*>              resultsvariant;                        
    XWINDOWSWMIINTERFACE_ERROR      error;
    XSTRING                         errordescription;
};


class XWINDOWSWMIINTERFACE
{
  public:
                                    XWINDOWSWMIINTERFACE              ();
    virtual                        ~XWINDOWSWMIINTERFACE              ();

    bool                            Ini                               ();

    XWINDOWSWMIINTERFACE_RESULT*    DoQuery                           (XCHAR* query, XCHAR* propertynameofresultobject, bool allowemptyitems = false);

    bool                            DoQuery                           (XCHAR* _class, XCHAR* namedata,  XSTRING& answer);
    bool                            DoQuery                           (XCHAR* _class, XCHAR* namedata,  XVECTOR<XSTRING*>* answers);

    bool                            DoQuery                           (XCHAR* _class, XCHAR* namedata,  XVARIANT& answer);
    bool                            DoQuery                           (XCHAR* _class, XCHAR* namedata,  XVECTOR<XVARIANT*>* answers);

    bool                            NetWorkInterfaceEnable            (int ID, bool enabled);
    bool                            NetWorkInterfaceSetMetric         (int ID, int metric);

    bool                            NetWorkInterfaceSetMetric         (int metric);

    bool                            End                               ();

  private:

    void                            Clean                             ();
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

