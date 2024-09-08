/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       APPExtended_InternetStatus.cpp
* 
* @class      APPEXTENDED_INTERNETSTATUS
* @brief      Application Extended Internet Status class
* @ingroup    APPLICATION
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
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "APPExtended_InternetStatus.h"

#include "APPInternetServices.h"
#include "APPCFG.h"
#include "APPConsole.h"
#include "APPExtended.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         APPEXTENDED_INTERNETSTATUS::APPEXTENDED_INTERNETSTATUS(APPCFG* cfg)
* @brief      Constructor
* @ingroup    APPLICATION
* 
* @param[in]  APPCFG* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
APPEXTENDED_INTERNETSTATUS::APPEXTENDED_INTERNETSTATUS(APPCFG* cfg) : DIOWEBSERVER_RESOLVEENDPOINT()
{
  Clean();

  this->cfg = cfg;

  appinternetservices = new APPINTERNETSERVICES();
  if(appinternetservices) 
    {
      appinternetservices->Ini(cfg);
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         APPEXTENDED_INTERNETSTATUS::~APPEXTENDED_INTERNETSTATUS()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
APPEXTENDED_INTERNETSTATUS::~APPEXTENDED_INTERNETSTATUS()
{ 
  if(appinternetservices)
    {
      appinternetservices->End();
      delete appinternetservices;      
    }

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         APPINTERNETSERVICES* APPEXTENDED_INTERNETSTATUS::GetAPPInternetServices()
* @brief      GetAPPInternetServices
* @ingroup    APPLICATION
* 
* @return     APPINTERNETSERVICES* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
APPINTERNETSERVICES* APPEXTENDED_INTERNETSTATUS::GetAPPInternetServices()
{
  return appinternetservices;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* APPEXTENDED_INTERNETSTATUS::GetLocalIP()
* @brief      GetLocalIP
* @ingroup    APPLICATION
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPEXTENDED_INTERNETSTATUS::GetLocalIP()
{
  return &localIP;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPEXTENDED_INTERNETSTATUS::GetHaveInternetConnection()
* @brief      GetHaveInternetConnection
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPEXTENDED_INTERNETSTATUS::GetHaveInternetConnection()
{
  return haveinternetconnection;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* APPEXTENDED_INTERNETSTATUS::GetPublicIP()
* @brief      GetPublicIP
* @ingroup    APPLICATION
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPEXTENDED_INTERNETSTATUS::GetPublicIP()
{
  return &publicIP;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPEXTENDED_INTERNETSTATUS::Update()
* @brief      Update
* @ingroup    
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPEXTENDED_INTERNETSTATUS::Update()
{  
  localIP = appinternetservices->GetAutomaticLocalIP()->Get();

  haveinternetconnection = appinternetservices->HaveInternetConnection();
  if(haveinternetconnection)  
    {
      publicIP = appinternetservices->GetPublicIP()->Get();
    }
   else
    {
      publicIP = __L("");
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPEXTENDED_INTERNETSTATUS::Show(XCONSOLE* console)
* @brief      Show
* @ingroup    APPLICATION
* 
* @param[in]  console : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPEXTENDED_INTERNETSTATUS::Show(XCONSOLE* console)
{
  XSTRING   string;
  XSTRING   string2;

  if(!APP_EXTENDED.GetAppConsole())
    { 
      return false;
    }

  string  = __L("Local IP");
  string2.Format(__L("[%s]"), localIP.Get());
  APP_EXTENDED.GetAppConsole()->Show_Line(string, string2);

  string  = __L("Internet Connection");
  string2.Format(__L("%s"), haveinternetconnection?__L("yes"):__L("no"));
  APP_EXTENDED.GetAppConsole()->Show_Line(string, string2);

  if(haveinternetconnection)
    {
      string  = __L("Public IP");
      string2.Format(__L("[%s]"), publicIP.Get());
      APP_EXTENDED.GetAppConsole()->Show_Line(string, string2);
    }
 
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPEXTENDED_INTERNETSTATUS::Serialize()
* @brief      Serialize
* @ingroup    
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPEXTENDED_INTERNETSTATUS::Serialize()
{
  Primitive_Add<XSTRING*>(&localIP            , __L("localIP"));
  
  Primitive_Add<bool>(haveinternetconnection  , __L("internetconnection"));
  Primitive_Add<XSTRING*>(&publicIP           , __L("publicIP")); 

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPEXTENDED_INTERNETSTATUS::Deserialize()
* @brief      Deserialize
* @ingroup    
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPEXTENDED_INTERNETSTATUS::Deserialize()
{ 
  Primitive_Extract<XSTRING&>(localIP            , __L("localIP"));
  
  Primitive_Extract<bool>(haveinternetconnection , __L("internetconnection"));
  Primitive_Extract<XSTRING&>(publicIP           , __L("publicIP"));
 
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPEXTENDED_INTERNETSTATUS::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APPEXTENDED_INTERNETSTATUS::Clean()
{
  cfg                     = NULL;
  appinternetservices     = NULL;

  localIP.Empty();

  haveinternetconnection  = false;
  publicIP.Empty();    
}


#pragma endregion