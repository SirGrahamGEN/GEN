/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOStreamUSBConfig.h
* 
* @class      DIOSTREAMUSBCONFIG
* @brief      Data Input/Output Stream USB config class
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

#ifndef _DIOSTREAMUSBCONFIG_H_
#define _DIOSTREAMUSBCONFIG_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XString.h"

#include "DIOStreamConfig.h"
#include "DIOStreamDeviceUSB.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class DIOSTREAMUSBCONFIG : public DIOSTREAMCONFIG
{
  public:
                                  DIOSTREAMUSBCONFIG                ();
    virtual                      ~DIOSTREAMUSBCONFIG                ();


    XSTRING*                      GetLocation                       ();

    XDWORD                        GetVendorID                       ();
    void                          SetVendorID                       (XDWORD vendorID);

    XDWORD                        GetProductID                      ();
    void                          SetProductID                      (XDWORD productID);

    DIOSTREAMDEVICEUSBCLASS       GetClass                          ();
    void                          SetClass                          (DIOSTREAMDEVICEUSBCLASS classdev);

    XSTRING*                      GetResource                       ();

    bool                          GetToString                       (XSTRING* string);
    bool                          GetToString                       (XSTRING& string);

    bool                          SetFromString                     (XCHAR* string);
    bool                          SetFromString                     (XSTRING* string);

    bool                          SetFromString                     (XSTRING& string);

  protected:

    XSTRING                       location;
    XDWORD                        vendorID;
    XDWORD                        productID;
    DIOSTREAMDEVICEUSBCLASS       classdev;
    XSTRING                       resource;

  private:

    void                          Clean                             ();
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

