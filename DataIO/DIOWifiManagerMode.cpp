/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOWifiManagerMode.cpp
*
* @class      DIOWIFIMANAGERMODE
* @brief      Data Input/Output Wifi Manager Mode
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XFileTXT.h"

#include "DIOFactory.h"
#include "DIOStreamDeviceIP.h"
#include "DIOStreamIPLocalEnumDevices.h"
#include "DIOIP.h"

#include "DIOWifiManagerMode.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWIFIMANAGERMODE::DIOWIFIMANAGERMODE()
* @brief      Constructor
* @ingroup    DATAIO
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     Does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOWIFIMANAGERMODE::DIOWIFIMANAGERMODE()    
{ 
  Clean();                            
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWIFIMANAGERMODE::~DIOWIFIMANAGERMODE()
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
DIOWIFIMANAGERMODE::~DIOWIFIMANAGERMODE()    
{ 
  nameAPs.DeleteContents();
  nameAPs.DeleteAll();

  Clean();                            
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWIFIMANAGERMODE::GetSelectNetInterface(XSTRING& netinterface)
* @brief      GetSelectNetInterface
* @ingroup    DATAIO
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  netinterface : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOWIFIMANAGERMODE::GetSelectNetInterface(XSTRING& netinterface)
{
  return &netinterface;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWIFIMANAGERMODE::SetSelectNetInterface(XCHAR* netinterface);
* @brief      SetSelectNetInterface
* @ingroup    DATAIO
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  netinterface) : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOWIFIMANAGERMODE::SetSelectNetInterface(XCHAR* netinterface)
{
  this->netinterface = netinterface;

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWIFIMANAGERMODE::SetSelectNetInterface(XSTRING& netinterface)
* @brief      SetSelectNetInterface
* @ingroup    DATAIO
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  netinterface : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOWIFIMANAGERMODE::SetSelectNetInterface(XSTRING& netinterface)
{
  return SetSelectNetInterface(netinterface.Get());
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOWIFIMANAGER_MODETYPE DIOWIFIMANAGERMODE::GetModeType()
* @brief      GetModeType
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
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
* @brief      SetModeType
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  modetype : 
* 
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOWIFIMANAGERMODE::SetModeType(DIOWIFIMANAGER_MODETYPE modetype)
{
  this->modetype = modetype;
}     



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWIFIMANAGERMODE::CheckNetInterface(DIOIP* IP)
* @brief      CheckNetInterface
* @ingroup    DATAIO
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  IP : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @brief      CheckNetInterface
* @ingroup    DATAIO
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  IP : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @brief      SetMode_AP
* @ingroup    DATAIO
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  SSID : 
* @param[in]  password : 
* @param[in]  serialize : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOWIFIMANAGERMODE::SetMode_AP(XCHAR* SSID, XCHAR* password,  bool serialize)
{
  return SetMode_AP(SSID, password, serialize);
}
   




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWIFIMANAGERMODE::SetMode_AP(XSTRING& SSID, XSTRING& password, bool serialize)
* @brief      SetMode_AP
* @ingroup    DATAIO
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  SSID : 
* @param[in]  password : 
* @param[in]  serialize : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOWIFIMANAGERMODE::SetMode_AP(XSTRING& SSID, XSTRING& password, bool serialize)
{
  return SetMode_AP(SSID.Get(), password.Get(), serialize);
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOWIFIMANAGERMODE::SetMode_AP(XSTRING& SSID, XCHAR* password, bool serialize)
* @brief      SetMode_AP
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
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
* @brief      SetMode_Client
* @ingroup    DATAIO
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  SSID : 
* @param[in]  password : 
* @param[in]  serialize : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOWIFIMANAGERMODE::SetMode_Client(XCHAR* SSID, XCHAR* password, bool serialize)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWIFIMANAGERMODE::SetMode_Client(XSTRING& SSID, XSTRING password, bool serialize)
* @brief      SetMode_Client
* @ingroup    DATAIO
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  SSID : 
* @param[in]  password : 
* @param[in]  serialize : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOWIFIMANAGERMODE::SetMode_Client(XSTRING& SSID, XSTRING& password, bool serialize)
{
  return SetMode_Client(SSID.Get(), password.Get(), serialize);      
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOWIFIMANAGERMODE::SetMode_Client(XSTRING& SSID, XCHAR* password, bool serialize)
* @brief      SetMode_Client
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  SSID : 
* @param[in]  password : 
* @param[in]  serialize : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOWIFIMANAGERMODE::SetMode_Client(XSTRING& SSID, XCHAR* password, bool serialize)
{
  return SetMode_Client(SSID.Get(), password, serialize);      
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOWIFIMANAGERMODE::IsDisconnected()
* @brief      IsDisconnected
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
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
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
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
* @brief      APList_Reload
* @ingroup    DATAIO
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOWIFIMANAGERMODE::APList_Reload()
{  
  return false;
}


    
/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XVECTOR<XSTRING*>* DIOWIFIMANAGERMODE::APList_Get()
* @brief      APList_Get
* @ingroup    DATAIO
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     XVECTOR<XSTRING*>* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XVECTOR<XSTRING*>* DIOWIFIMANAGERMODE::APList_Get()
{
  return &nameAPs;  
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWIFIMANAGERMODE::Clean()
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
void DIOWIFIMANAGERMODE::Clean()
{
  modetype   = DIOWIFIMANAGER_MODETYPE_DEFAULT;

}
