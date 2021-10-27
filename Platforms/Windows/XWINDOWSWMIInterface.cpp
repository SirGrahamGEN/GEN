/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XWINDOWSWMIInterface.cpp
*
* @class      XWINDOWSWMIINTERFACE
* @brief      eXtended WINDOWS Management Instrumentation Interface class
* @ingroup    PLATFORM_WINDOWS
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

#define _WIN32_DCOM
#include <iostream>
#include <comdef.h>
using namespace std;
#include <Wbemidl.h>

#include "XTrace.h"

#include "XWINDOWSRegistryManager.h"

#include "XWINDOWSWMIInterface.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

#pragma comment(lib, "wbemuuid.lib")

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWINDOWSWMIINTERFACE_RESULT::XWINDOWSWMIINTERFACE_RESULT()
* @brief      Constructor
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XWINDOWSWMIINTERFACE_RESULT::XWINDOWSWMIINTERFACE_RESULT()
{
  Clean();

  results.DeleteContents();
  results.DeleteAll();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWINDOWSWMIINTERFACE_RESULT::~XWINDOWSWMIINTERFACE_RESULT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XWINDOWSWMIINTERFACE_RESULT::~XWINDOWSWMIINTERFACE_RESULT()
{
  results.DeleteContents();
  results.DeleteAll();

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XVECTOR<XSTRING*>* XWINDOWSWMIINTERFACE_RESULT::GetResults()
* @brief      GetResults
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XVECTOR<XSTRING*>* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XVECTOR<XSTRING*>* XWINDOWSWMIINTERFACE_RESULT::GetResults()
{
  return &results;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         WMIQUERYERROR XWINDOWSWMIINTERFACE_RESULT::GetError()
* @brief      GetError
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XWINDOWSWMIINTERFACE_ERROR  :
*
*---------------------------------------------------------------------------------------------------------------------*/
XWINDOWSWMIINTERFACE_ERROR XWINDOWSWMIINTERFACE_RESULT::GetError()
{
  return error;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XWINDOWSWMIINTERFACE_RESULT::SetError(XWINDOWSWMIINTERFACE_ERROR error)
* @brief      SetError
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  error :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XWINDOWSWMIINTERFACE_RESULT::SetError(XWINDOWSWMIINTERFACE_ERROR error)
{
  this->error = error;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING XWINDOWSWMIINTERFACE_RESULT::GetErrorDescription()
* @brief      GetErrorDescription
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* XWINDOWSWMIINTERFACE_RESULT::GetErrorDescription()
{
  return &errordescription;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XWINDOWSWMIINTERFACE_RESULT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XWINDOWSWMIINTERFACE_RESULT::Clean()
{
  error = XWINDOWSWMIINTERFACE_ERROR_NONE;
}





/*---------------------------------------------------------------------------------------------------------------------*/
/* XWINDOWSWMIINTERFACE                                                                                                */
/*---------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWINDOWSWMIINTERFACE::XWINDOWSWMIINTERFACE()
* @brief      Constructor
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XWINDOWSWMIINTERFACE::XWINDOWSWMIINTERFACE()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWINDOWSWMIINTERFACE::~XWINDOWSWMIINTERFACE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XWINDOWSWMIINTERFACE::~XWINDOWSWMIINTERFACE()
{
  End();

  Clean();
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSWMIINTERFACE::Ini()
* @brief      Ini
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSWMIINTERFACE::Ini()
{
  HRESULT hres;

  hres = CoInitializeEx(0, COINIT_MULTITHREADED);
  if(FAILED(hres))
    {
      return false;
    }
   else
    {
      //-----------------------------------------------------------------------------------------
      // Step 2: Set general COM security levels

      hres = CoInitializeSecurity( NULL,
                                   -1,                          // COM authentication
                                   NULL,                        // Authentication services
                                   NULL,                        // Reserved
                                   RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication
                                   RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation
                                   NULL,                        // Authentication info
                                   EOAC_NONE,                   // Additional capabilities
                                   NULL                         // Reserved
                                 );
      if(FAILED(hres))
        {
          return false;
        }
    }


  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWINDOWSWMIINTERFACE_RESULT* XWINDOWSWMIINTERFACE::DoQuery(XCHAR* query, XCHAR* propertynameofresultobject, bool allowemptyitems)
* @brief      DoQuery
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  query :
* @param[in]  propertynameofresultobject :
* @param[in]  allowemptyitems :
*
* @return     XWINDOWSWMIINTERFACE_RESULT* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XWINDOWSWMIINTERFACE_RESULT* XWINDOWSWMIINTERFACE::DoQuery(XCHAR* query, XCHAR* propertynameofresultobject, bool allowemptyitems)
{

  XWINDOWSWMIINTERFACE_RESULT* result       = NULL;
  HRESULT                      hres;
  IWbemLocator*                ploc         = NULL;
  IWbemServices*               psvc         = NULL;
  IEnumWbemClassObject*        penumerator  = NULL;


  result = new XWINDOWSWMIINTERFACE_RESULT();
  if(!result) return NULL;

  //-----------------------------------------------------------------------------------------
  // Step 3: Obtain the initial locator to WMI

  ploc = NULL;

  hres = CoCreateInstance( CLSID_WbemLocator,
                            0,
                            CLSCTX_INPROC_SERVER,
                            IID_IWbemLocator,
                            (LPVOID *)&ploc
                          );
  if(FAILED(hres))
    {
      result->SetError(XWINDOWSWMIINTERFACE_ERROR_IWBEMLOCATORFAILURE);
      result->GetErrorDescription()->Format(__L("Failed to create IWbemLocator object. Error code: %d"), hres);
    }
   else
    {
      //-----------------------------------------------------------------------------------------
      // Step 4: Connect to WMI through the IWbemLocator::ConnectServer method

      psvc = NULL;

      // Connect to the root\cimv2 namespace with the current user and obtain pointer pSvc
      // to make IWbemServices calls.
      hres = ploc->ConnectServer( _bstr_t(L"ROOT\\CIMV2"), // Object path of WMI namespace
                                  NULL,                    // User name. NULL = current user
                                  NULL,                    // User password. NULL = current
                                  0,                       // Locale. NULL indicates current
                                  NULL,                    // Security flags.
                                  0,                       // Authority (for example, Kerberos)
                                  0,                       // Context object
                                  &psvc                    // pointer to IWbemServices proxy
                                );

        // Connected to ROOT\\CIMV2 WMI namespace
        if(FAILED(hres))
          {
            result->SetError(XWINDOWSWMIINTERFACE_ERROR_IWBEMSERVICECONNECTIONFAILURE);
            result->GetErrorDescription()->Format(__L("Could not connect to Wbem service. Error code: %d"), hres);
          }
          else
          {
            //-----------------------------------------------------------------------------------------
            // Step 5: Set security levels on the proxy

            hres = CoSetProxyBlanket( psvc,                        // Indicates the proxy to set
                                      RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
                                      RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
                                      NULL,                        // Server principal name
                                      RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx
                                      RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
                                      NULL,                        // client identity
                                      EOAC_NONE                    // proxy capabilities
                                    );

            if(FAILED(hres))
              {
                result->SetError(XWINDOWSWMIINTERFACE_ERROR_BLANKETPROXYSETFAILURE);
                result->GetErrorDescription()->Format(__L("Could not set proxy blanket. Error code: %d"), hres);
              }
              else
              {
                //-----------------------------------------------------------------------------------------
                // Step 6: Use the IWbemServices pointer to make requests of WMI

                penumerator = NULL;
                hres = psvc->ExecQuery( bstr_t("WQL"),
                                        bstr_t(query),
                                        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
                                        NULL,
                                        &penumerator);

                if(FAILED(hres))
                  {
                    result->SetError(XWINDOWSWMIINTERFACE_ERROR_BADQUERYFAILURE);
                    result->GetErrorDescription()->Format(__L("Bad query. Error code: %d"), hres);
                  }
                  else
                  {
                    //-----------------------------------------------------------------------------------------
                    // Step 7:  Get the data from the query in step 6

                    #define MAXBLOCK_PCLSOBJ   500

                    HRESULT           hr        = WBEM_S_NO_ERROR;
                    IWbemClassObject* pclsobj[MAXBLOCK_PCLSOBJ];
                    VARIANT           vtprop;
                    ULONG             ureturned = 0;

                    while( hr == WBEM_S_NO_ERROR)
                      {
                        hr = penumerator->Next(WBEM_INFINITE, MAXBLOCK_PCLSOBJ, pclsobj, &ureturned);
                        if(SUCCEEDED(hr) && (ureturned!=0))
                          {
                            // VARIANT vtProp;
                            // Get the value of desired property
                            for( ULONG c=0; c<ureturned; c++)
                              {
                                hr = pclsobj[c]->Get(propertynameofresultobject, 0, &vtprop, 0, 0);
                                if(hr != S_OK)
                                  {
                                    result->SetError(XWINDOWSWMIINTERFACE_ERROR_PROPERTYEXTRACTIONFAILURE);
                                    result->GetErrorDescription()->Format(__L("Couldn't extract property: %s from result of query. Error code: %d"), propertynameofresultobject, hres);

                                    break;
                                  }
                                  else
                                  {
                                    switch(vtprop.vt)
                                      {
                                        case VT_NULL  : { XSTRING* resultstr = new XSTRING();
                                                          if(resultstr) result->GetResults()->Add(resultstr);
                                                        }
                                                        break;

                                        case VT_I2    : { XWORD data = vtprop.intVal;
                                                          XSTRING* resultstr = new XSTRING();
                                                          if(resultstr)
                                                            {
                                                              resultstr->ConvertFromInt(data);
                                                              result->GetResults()->Add(resultstr);
                                                            }
                                                        }
                                                        break;

                                        case VT_I4    : { XDWORD data = vtprop.lVal;
                                                          XSTRING* resultstr = new XSTRING();
                                                          if(resultstr)
                                                            {
                                                              resultstr->ConvertFromInt(data);
                                                              result->GetResults()->Add(resultstr);
                                                            }
                                                        }
                                                        break;

                                        case VT_BOOL  : { BOOL data = vtprop.lVal;
                                                          XSTRING* resultstr = new XSTRING();
                                                          if(resultstr)
                                                            {
                                                              resultstr->Format(__L("%s"), (data?__L("true"):__L("false")));
                                                              result->GetResults()->Add(resultstr);
                                                            }
                                                        }
                                                        break;

                                        case VT_BSTR  : { BSTR val = vtprop.bstrVal;

                                                          // Sometimes val might be NULL even when result is S_OK
                                                          // Convert NULL to empty string (otherwise "std::wstring(val)" would throw exception)
                                                          if(val == NULL)
                                                            {
                                                              if(allowemptyitems)
                                                                {
                                                                  XSTRING* resultstr = new XSTRING();
                                                                  if(resultstr)
                                                                    {
                                                                      result->GetResults()->Add(resultstr);
                                                                    }
                                                                }
                                                            }
                                                           else
                                                            {
                                                              XSTRING* resultstr = new XSTRING();
                                                              if(resultstr)
                                                                {
                                                                  (*resultstr) = (XCHAR*)val;
                                                                  result->GetResults()->Add(resultstr);
                                                                  //XTRACE_PRINTCOLOR(1, __L("%s"), resultstr->Get());
                                                                }
                                                            }
                                                        }
                                                        break;
                                      }

                                    VariantClear(&vtprop);
                                  }

                                  pclsobj[c]->Release();
                              }

                            if(ureturned < MAXBLOCK_PCLSOBJ) break;

                          } else break;
                      }
                  }
              }
          }
      }


  //-----------------------------------------------------------------------------------------
  // Cleanup

  if(psvc)          psvc->Release();
  if(ploc)          ploc->Release();
  if(penumerator)   penumerator->Release();

  return result;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSWMIINTERFACE::DoQuery(XCHAR* _class, XCHAR* namedata, XSTRING& answer)
* @brief      DoQuery
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  _class :
* @param[in]  namedata :
* @param[in]  answer :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSWMIINTERFACE::DoQuery(XCHAR* _class, XCHAR* namedata,  XSTRING& answer)
{
  XWINDOWSWMIINTERFACE_RESULT*  result       = NULL;
  bool                          status       = false;

  answer.Empty();

  XSTRING xstringclass;

  xstringclass.Format(__L("SELECT * FROM %s"), _class);

  result = DoQuery(xstringclass.Get(), namedata);
  if(result)
    {
      if(result->GetError() == XWINDOWSWMIINTERFACE_ERROR_NONE)
        {
          if(result->GetResults()->GetSize())
            {
              answer = (XCHAR*)result->GetResults()->Get(0)->Get();
              status = true;
            }
        }
    }

  delete result;

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSWMIINTERFACE::DoQuery(XCHAR* _class, XCHAR* namedata, XVECTOR<XSTRING*>* answers)
* @brief      DoQuery
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  _class :
* @param[in]  namedata :
* @param[in]  answers :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSWMIINTERFACE::DoQuery(XCHAR* _class, XCHAR* namedata,  XVECTOR<XSTRING*>* answers)
{
  XWINDOWSWMIINTERFACE_RESULT*  result       = NULL;
  bool                          status       = false;

  XSTRING xstringclass;

  xstringclass.Format(__L("SELECT * FROM %s"), _class);

  result = DoQuery(xstringclass.Get(), namedata);
  if(result)
    {
      if(result->GetError() == XWINDOWSWMIINTERFACE_ERROR_NONE)
        {
          if(result->GetResults()->GetSize())
            {
              for(XDWORD c=0; c<result->GetResults()->GetSize(); c++)
                {
                  XSTRING* resultstring = new XSTRING();
                  if(resultstring)
                    {
                      (*resultstring) = (XCHAR*)result->GetResults()->Get(c)->Get();
                      answers->Add(resultstring);
                    }
                }

              status = true;
            }
        }
    }

  delete result;

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSWMIINTERFACE::NetWorkInterfaceEnable(int ID, bool enabled)
* @brief      NetWorkInterfaceEnable
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  ID :
* @param[in]  enabled :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSWMIINTERFACE::NetWorkInterfaceEnable(int ID, bool enable)
{
  IWbemLocator*   ploc = NULL;
  HRESULT         hres;
  bool            status = true;

  hres = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID *) &ploc);
  if(FAILED(hres)) return false;

  // Connect to WMI through the IWbemLocator::ConnectServer method
  IWbemServices* psvc = NULL;

  // Connect to the root\\CIMV2 namespace
  // and obtain pointer pSvc to make IWbemServices calls.
  hres = ploc->ConnectServer( _bstr_t(L"ROOT\\CIMV2"),    // Object path of WMI namespace
                              NULL,                       // User name. NULL = current user
                              NULL,                       // User password. NULL = current
                              0,                          // Locale. NULL indicates current
                              NULL,                       // Security flags.
                              0,                          // Authority (e.g. Kerberos)
                              0,                          // Context object
                              &psvc                       // pointer to IWbemServices proxy
                              );
  if(FAILED(hres))
    {
      ploc->Release();
      return false;
    }

  hres = CoSetProxyBlanket( psvc,                         // Indicates the proxy to set
                            RPC_C_AUTHN_WINNT,            // RPC_C_AUTHN_xxx
                            RPC_C_AUTHZ_NONE,             // RPC_C_AUTHZ_xxx
                            NULL,                         // Server principal name
                            RPC_C_AUTHN_LEVEL_CALL,       // RPC_C_AUTHN_LEVEL_xxx
                            RPC_C_IMP_LEVEL_IMPERSONATE,  // RPC_C_IMP_LEVEL_xxx
                            NULL,                         // client identity
                            EOAC_NONE                     // proxy capabilities
                          );


  if(FAILED(hres))
    {
      psvc->Release();
      ploc->Release();
      return false;
    }

  BSTR methodname = SysAllocString(enable?__L("Enable"):__L("Disable"));
  BSTR classname  = SysAllocString(L"Win32_NetworkAdapter");

  IWbemClassObject* pclass = NULL;
  hres = psvc->GetObject(classname, 0, NULL, &pclass, NULL);

  hres = pclass->GetMethod(methodname, 0, NULL, NULL);

  // Execute Method
  XSTRING           devicename;
  IWbemClassObject* poutparams = NULL;

  devicename.Format(__L("Win32_NetworkAdapter.DeviceID=\"%d\""), ID);

  hres = psvc->ExecMethod(devicename.Get() , methodname
                                           , 0
                                           , NULL
                                           , NULL /*pClassInstance*/
                                           , &poutparams, NULL);
  if(FAILED(hres)) status = false;

  SysFreeString(classname);
  SysFreeString(methodname);

  if(pclass)     pclass->Release();
  if(poutparams) poutparams->Release();
  if(ploc)       ploc->Release();
  if(psvc)       psvc->Release();

  return status;
}






/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSWMIINTERFACE::End()
* @brief      End
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSWMIINTERFACE::End()
{
  CoUninitialize();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XWINDOWSWMIINTERFACE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XWINDOWSWMIINTERFACE::Clean()
{

}



