/**-------------------------------------------------------------------------------------------------------------------/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOCoreProtocol_Register.h
* 
* @class      DIOCOREPROTOCOL_REGISTERDATA
* @brief      Data Input/Output Core Protocol Register Data class
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

#ifndef _DIOCOREPROTOCOL_REGISTERDATA_H_
#define _DIOCOREPROTOCOL_REGISTERDATA_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XUUID.h"
#include "XSerializable.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

#define DIOCOREPROTOCOL_REGISTERDATA_HEADER_VAR_ID_MACHINE          __L("ID_machine")    
#define DIOCOREPROTOCOL_REGISTERDATA_HEADER_VAR_BIOSSERIAL          __L("biosserial")    
#define DIOCOREPROTOCOL_REGISTERDATA_HEADER_VAR_CPUSERIAL           __L("cpuserial")    
#define DIOCOREPROTOCOL_REGISTERDATA_HEADER_VAR_USER                __L("user")    
#define DIOCOREPROTOCOL_REGISTERDATA_HEADER_VAR_DOMAIN              __L("domain")    

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

class DIOCOREPROTOCOL_REGISTERDATA : public XSERIALIZABLE
{
  public:
                            DIOCOREPROTOCOL_REGISTERDATA    ();
    virtual                ~DIOCOREPROTOCOL_REGISTERDATA    ();

    virtual bool            InitializeData                  (bool isserver);

    XUUID*                  GetIDMmachine                   ();

    XSTRING*                GetBiosSerialNumber             ();
    XSTRING*                GetCPUSerialNumber              ();                      
    XSTRING*                GetUser                         ();                      
    XSTRING*                GetDomain                       ();                      

    virtual bool            Serialize                       ();    
    virtual bool            Deserialize                     ();  

    bool                    ShowDebug                       ();

  private:

    bool                    CreateIDMachine                 (XUUID& ID);

    void                    Clean                           ();

    XUUID                   ID_machine;

    XSTRING                 biosserialnumber;
    XSTRING                 CPUserialnumber; 
    XSTRING                 user;
    XSTRING                 domain;
};

#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

