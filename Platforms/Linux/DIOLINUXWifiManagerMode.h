/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOLINUXWifiManagerMode.h
*
* @class      DIOLINUXWIFIMANAGERMODE
* @brief      Data Input/Output LINUX Wifi Manager Mode
* @ingroup    DATAIO
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @copyright  Copyright(c) 2005 - 2020 GEN Group.
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

#ifndef _DIOLINUXWIFIMANAGERMODE_H_
#define _DIOLINUXWIFIMANAGERMODE_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "DIOWifiManagerMode.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define DIOLINUXWIFIMANAGERMODE_PREFIXCOMMAND     __L("-i %s")

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/


class DIOLINUXWIFIMANAGERMODE : public DIOWIFIMANAGERMODE
{
  public:
                                      DIOLINUXWIFIMANAGERMODE       ();
    virtual                          ~DIOLINUXWIFIMANAGERMODE       ();
  
    bool                              SetMode_AP                    (XCHAR* SSID, XCHAR* password, bool serialize);        
    bool                              SetMode_Client                (XCHAR* SSID, XCHAR* password, bool serialize);       
    
    bool                              APList_Reload                 ();

    bool                              IsDisconnected                ();
    bool                              Disconnect                    ();  
    
  private:

    bool                              WPA_SetMode                   (int mode, XCHAR* SSID, XCHAR* password, int indexnetwork, bool serialize);
    bool                              WPA_IsDisconnected            ();
    bool                              WPA_Disconnect                ();

    bool                              WPA_RemoveAllNetworks         ();
    bool                              WPA_SetValue                  (int indexnetwork, XCHAR* namevalue, XCHAR* value, bool isstring = true);
    bool                              WPA_SetValue                  (int indexnetwork, XSTRING& namevalue, XSTRING& value);
    bool                              WPA_GetListRemoteAP           (XVECTOR<XSTRING*>& nameAPs);
    bool                              WPA_CLI_Command               (XSTRING& command, XSTRING& output);

    bool                              NM_SetMode                    (int mode, XCHAR* SSID, XCHAR* password, int indexnetwork, bool serialize);
    bool                              NM_IsDisconnected             ();
    bool                              NM_Disconnect                 ();
    bool                              NM_CLI_Command                (XSTRING& command, XSTRING& output);  

    
    void                              Clean                         ();

    XSTRING                           prefixcommand; 
    XSTRING                           lastSSID;
};

/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif


