/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOWifiManagerMode.cpp
* 
* @class      DIOWIFIMANAGERMODE
* @brief      Data Input/Output Wifi Manager Mode class
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

#include "DIOWifiManagerMode.h"

#include "XFileTXT.h"

#include "DIOFactory.h"
#include "DIOStreamDeviceIP.h"
#include "DIOStreamIPLocalEnumDevices.h"
#include "DIOIP.h"

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
* @fn         DIOWIFIMANAGERMODE::DIOWIFIMANAGERMODE()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWIFIMANAGERMODE::DIOWIFIMANAGERMODE()    
{ 
  Clean();                            
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWIFIMANAGERMODE::~DIOWIFIMANAGERMODE()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWIFIMANAGERMODE::~DIOWIFIMANAGERMODE()    
{ 
  nameAPs.DeleteContents();
  nameAPs.DeleteAll();

  Clean();                            
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWIFIMANAGERMODE::GetSelectNetInterface(XSTRING& netinterface)
* @brief      Get select net interface
* @ingroup    DATAIO
*
* @param[in]  netinterface : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWIFIMANAGERMODE::GetSelectNetInterface(XSTRING& netinterface)
{
  netinterface = this->netinterface;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOWIFIMANAGERMODE::SetSelectNetInterface(XCHAR* netinterface)
* @brief      Set select net interface
* @ingroup    DATAIO
* 
* @param[in]  netinterface : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWIFIMANAGERMODE::SetSelectNetInterface(XCHAR* netinterface)
{
  this->netinterface = netinterface;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOWIFIMANAGERMODE::SetSelectNetInterface(XSTRING& netinterface)
* @brief      Set select net interface
* @ingroup    DATAIO
* 
* @param[in]  netinterface : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWIFIMANAGERMODE::SetSelectNetInterface(XSTRING& netinterface)
{
  return SetSelectNetInterface(netinterface.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOWIFIMANAGER_MODETYPE DIOWIFIMANAGERMODE::GetModeType()
* @brief      Get mode type
* @ingroup    DATAIO
*
* @return     DIOWIFIMANAGER_MODETYPE : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOWIFIMANAGER_MODETYPE DIOWIFIMANAGERMODE::GetModeType()
{
  return modetype;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOWIFIMANAGERMODE::SetModeType(DIOWIFIMANAGER_MODETYPE modetype)
* @brief      Set mode type
* @ingroup    DATAIO
*
* @param[in]  modetype : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOWIFIMANAGERMODE::SetModeType(DIOWIFIMANAGER_MODETYPE modetype)
{
  this->modetype = modetype;
}     


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWIFIMANAGERMODE::CheckNetInterface(DIOIP* IP)
* @brief      Check net interface
* @ingroup    DATAIO
*
* @param[in]  IP : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWIFIMANAGERMODE::CheckNetInterface(DIOIP* IP)
{
  bool status = false;

  DIOSTREAMENUMDEVICES* enumdevicesIPlocal = NULL;
  
  enumdevicesIPlocal = GEN_DIOFACTORY.CreateStreamEnumDevices(DIOSTREAMENUMTYPE_IP_LOCAL);
	if(enumdevicesIPlocal)
	  {				      
		  enumdevicesIPlocal->Search();		  
			while(enumdevicesIPlocal->IsSearching())
        {          
				  XSLEEP::GetInstance().MilliSeconds(10);          
				}

			for(int c=0; c<(int)enumdevicesIPlocal->GetDevices()->GetSize(); c++)
			  {					
  	      DIOSTREAMDEVICEIP* deviceIP = (DIOSTREAMDEVICEIP*)enumdevicesIPlocal->GetDevices()->Get(c);
	  	    if(deviceIP) 
		  	    {	         
              bool isdeviceselect = false;

              if(!netinterface.IsEmpty())
                {
                  if(!deviceIP->GetName()->Compare(netinterface, true))  isdeviceselect = true;
                }
               else
                {
                  if(deviceIP->GetIPType() == DIOSTREAMIPDEVICE_TYPE_WIFI) isdeviceselect = true;
                }


              if(isdeviceselect)
                {
                  status = true;    

                  if(deviceIP->GetIP()->IsEmpty())   status = false;
                  if(!deviceIP->GetIP()->IsLocal())  status = false;

                  if(IP) IP->Set(deviceIP->GetIP()->Get());
                       
                  break;  
                }              
            }
        }  

      GEN_DIOFACTORY.DeleteStreamEnumDevices(enumdevicesIPlocal);
    }

  return status;
}
    

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWIFIMANAGERMODE::CheckNetInterface(XSTRING* IP)
* @brief      Check net interface
* @ingroup    DATAIO
*
* @param[in]  IP : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWIFIMANAGERMODE::CheckNetInterface(XSTRING* IP)
{
  DIOIP   _IP;
  bool    status = false;  

  status = CheckNetInterface(&_IP);

  if(_IP.IsEmpty())   status = false;
  if(!_IP.IsLocal())  status = false;

  if(IP) _IP.GetXString((*IP));

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWIFIMANAGERMODE::SetMode_AP(XCHAR* SSID, XCHAR* password, bool serialize)
* @brief      Set mode AP
* @ingroup    DATAIO
*
* @param[in]  SSID : 
* @param[in]  password : 
* @param[in]  serialize : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWIFIMANAGERMODE::SetMode_AP(XCHAR* SSID, XCHAR* password,  bool serialize)
{
  return true;
}
   

/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWIFIMANAGERMODE::SetMode_AP(XSTRING& SSID, XSTRING& password, bool serialize)
* @brief      Set mode AP
* @ingroup    DATAIO
*
* @param[in]  SSID : 
* @param[in]  password : 
* @param[in]  serialize : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWIFIMANAGERMODE::SetMode_AP(XSTRING& SSID, XSTRING& password, bool serialize)
{
  return SetMode_AP(SSID.Get(), password.Get(), serialize);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOWIFIMANAGERMODE::SetMode_AP(XSTRING& SSID, XCHAR* password, bool serialize)
* @brief      Set mode AP
* @ingroup    DATAIO
*
* @param[in]  SSID : 
* @param[in]  password : 
* @param[in]  serialize : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOWIFIMANAGERMODE::SetMode_AP(XSTRING& SSID, XCHAR* password, bool serialize)
{
  return SetMode_AP(SSID.Get(), password, serialize);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWIFIMANAGERMODE::SetMode_Client(XCHAR* SSID, XCHAR* password, bool serialize)
* @brief      Set mode client
* @ingroup    DATAIO
*
* @param[in]  SSID : 
* @param[in]  password : 
* @param[in]  serialize : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWIFIMANAGERMODE::SetMode_Client(XCHAR* SSID, XCHAR* password, bool serialize)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOWIFIMANAGERMODE::SetMode_Client(XSTRING& SSID, XSTRING& password, bool serialize)
* @brief      Set mode client
* @ingroup    DATAIO
* 
* @param[in]  SSID : 
* @param[in]  password : 
* @param[in]  serialize : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWIFIMANAGERMODE::SetMode_Client(XSTRING& SSID, XSTRING& password, bool serialize)
{
  return SetMode_Client(SSID.Get(), password.Get(), serialize);      
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOWIFIMANAGERMODE::SetMode_Client(XSTRING& SSID, XCHAR* password, bool serialize)
* @brief      Set mode client
* @ingroup    DATAIO
* 
* @param[in]  SSID : 
* @param[in]  password : 
* @param[in]  serialize : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWIFIMANAGERMODE::SetMode_Client(XSTRING& SSID, XCHAR* password, bool serialize)
{
  return SetMode_Client(SSID.Get(), password, serialize);      
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOWIFIMANAGERMODE::IsDisconnected()
* @brief      Is disconnected
* @ingroup    DATAIO
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOWIFIMANAGERMODE::IsDisconnected()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOWIFIMANAGERMODE::Disconnect()
* @brief      Disconnect
* @ingroup    DATAIO
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOWIFIMANAGERMODE::Disconnect()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWIFIMANAGERMODE::APList_Reload()
* @brief      AP list reload
* @ingroup    DATAIO
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWIFIMANAGERMODE::APList_Reload()
{  
  return false;
}

    
/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XVECTOR<XSTRING*>* DIOWIFIMANAGERMODE::APList_Get()
* @brief      AP list get
* @ingroup    DATAIO
*
* @return     XVECTOR<XSTRING*>* : 
*
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<XSTRING*>* DIOWIFIMANAGERMODE::APList_Get()
{
  return &nameAPs;  
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWIFIMANAGERMODE::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWIFIMANAGERMODE::Clean()
{
  modetype   = DIOWIFIMANAGER_MODETYPE_DEFAULT;
}


#pragma endregion

