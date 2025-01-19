/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOPublicInternetIP.cpp
* 
* @class      DIOPUBLICINTERNETIP
* @brief      Data Input/Output Public Internet IP class
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

#include "DIOPublicInternetIP.h"

#include "DIOPing.h"
#include "DIOWebClient.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

DIOPUBLICINTERNETIP* DIOPUBLICINTERNETIP::instance = NULL;

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPUBLICINTERNETIP::GetIsInstanced()
* @brief      Get is instanced
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPUBLICINTERNETIP::GetIsInstanced()
{
  return instance!=NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPUBLICINTERNETIP& DIOPUBLICINTERNETIP::GetInstance()
* @brief      Get instance
* @ingroup    DATAIO
* 
* @return     DIOPUBLICINTERNETIP& : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOPUBLICINTERNETIP& DIOPUBLICINTERNETIP::GetInstance()
{
  if(!instance) instance = new DIOPUBLICINTERNETIP();

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPUBLICINTERNETIP::DelInstance()
* @brief      Del instance
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPUBLICINTERNETIP::DelInstance()
{
  if(instance)
    {
      delete instance;
      instance = NULL;

      return true;
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPUBLICINTERNETIP::FastIsThereInternetConnection()
* @brief      Fast is there internet connection
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPUBLICINTERNETIP::FastIsThereInternetConnection()
{
  GEN_DIOPING.Set(__L("8.8.8.8"));

  bool connexionstatus = GEN_DIOPING.Do(DIOPUBLICINTERNETIP_DEFAULTNCHECKSFOREVERYCONNECTION, DIOPUBLICINTERNETIP_DEFAULTTIMERCONNECTIONCHECK, true);
  if(!connexionstatus)
    {
      return false;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPUBLICINTERNETIP::Get(XSTRING& publicIP)
* @brief      Get
* @ingroup    DATAIO
* 
* @param[in]  publicIP : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPUBLICINTERNETIP::Get(XSTRING& publicIP)
{
  DIOWEBCLIENT  webclient;
  DIOURL        url;
  XBUFFER       buffer;
  bool          status = false;
  
  publicIP.Empty();

  if(!FastIsThereInternetConnection())
    {
      return status;
    }
  
  url = DIOPUBLICINTERNETIP_URL
  webclient.Set_Port(80);

  buffer.Resize(64);

  status =  webclient.Get(url, buffer, NULL, 60);
  if(status)
    {
      publicIP = (char*)buffer.Get();            
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPUBLICINTERNETIP::Get(DIOIP& publicIP)
* @brief      Get
* @ingroup    DATAIO
* 
* @param[in]  publicIP : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPUBLICINTERNETIP::Get(DIOIP& publicIP)
{
  XSTRING publicIPstr;

  if(!Get(publicIPstr))
    {
      return false;
    }
  
  return publicIP.Set(publicIPstr);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPUBLICINTERNETIP::DIOPUBLICINTERNETIP()
* @brief      Constructor of class
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOPUBLICINTERNETIP::DIOPUBLICINTERNETIP()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPUBLICINTERNETIP::~DIOPUBLICINTERNETIP()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOPUBLICINTERNETIP::~DIOPUBLICINTERNETIP()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOPUBLICINTERNETIP::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPUBLICINTERNETIP::Clean()
{

}


#pragma endregion


