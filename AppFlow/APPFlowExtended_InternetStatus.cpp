/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       APPFlowExtended_InternetStatus.cpp
* 
* @class      APPFLOWEXTENDED_INTERNETSTATUS
* @brief      Application Flow Extended Internet Status class
* @ingroup    APPFLOW
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

#include "APPFlowExtended_InternetStatus.h"

#include "APPFlowInternetServices.h"
#include "APPFlowCFG.h"
#include "APPFlowConsole.h"
#include "APPFlowExtended.h"

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
* @fn         APPFLOWEXTENDED_INTERNETSTATUS::APPFLOWEXTENDED_INTERNETSTATUS(APPFLOWCFG* cfg)
* @brief      Constructor of class
* @ingroup    APPFLOW
* 
* @param[in]  cfg : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
APPFLOWEXTENDED_INTERNETSTATUS::APPFLOWEXTENDED_INTERNETSTATUS(APPFLOWCFG* cfg) : DIOWEBSERVER_RESOLVEENDPOINT()
{
  Clean();

  this->cfg = cfg;

  internetservices = new APPFLOWINTERNETSERVICES();
  if(internetservices) 
    {
      internetservices->Ini(cfg);
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         APPFLOWEXTENDED_INTERNETSTATUS::~APPFLOWEXTENDED_INTERNETSTATUS()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    APPFLOW
* 
* --------------------------------------------------------------------------------------------------------------------*/
APPFLOWEXTENDED_INTERNETSTATUS::~APPFLOWEXTENDED_INTERNETSTATUS()
{ 
  if(internetservices)
    {
      internetservices->End();
      delete internetservices;      
    }

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         APPFLOWINTERNETSERVICES* APPFLOWEXTENDED_INTERNETSTATUS::GetInternetServices()
* @brief      Get internet services
* @ingroup    APPFLOW
* 
* @return     APPFLOWINTERNETSERVICES* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
APPFLOWINTERNETSERVICES* APPFLOWEXTENDED_INTERNETSTATUS::GetInternetServices()
{
  return internetservices;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* APPFLOWEXTENDED_INTERNETSTATUS::GetLocalIP()
* @brief      Get local IP
* @ingroup    APPFLOW
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPFLOWEXTENDED_INTERNETSTATUS::GetLocalIP()
{
  return &localIP;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPFLOWEXTENDED_INTERNETSTATUS::GetHaveInternetConnection()
* @brief      Get have internet connection
* @ingroup    APPFLOW
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWEXTENDED_INTERNETSTATUS::GetHaveInternetConnection()
{
  return haveinternetconnection;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* APPFLOWEXTENDED_INTERNETSTATUS::GetPublicIP()
* @brief      Get public IP
* @ingroup    APPFLOW
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* APPFLOWEXTENDED_INTERNETSTATUS::GetPublicIP()
{
  return &publicIP;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPFLOWEXTENDED_INTERNETSTATUS::Update()
* @brief      Update
* @ingroup    APPFLOW
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWEXTENDED_INTERNETSTATUS::Update()
{  
  localIP = internetservices->GetAutomaticLocalIP()->Get();

  haveinternetconnection = internetservices->HaveInternetConnection();
  if(haveinternetconnection)  
    {
      publicIP = internetservices->GetPublicIP()->Get();
    }
   else
    {
      publicIP = __L("");
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPFLOWEXTENDED_INTERNETSTATUS::Show(XCONSOLE* console)
* @brief      Show
* @ingroup    APPFLOW
* 
* @param[in]  console : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWEXTENDED_INTERNETSTATUS::Show(XCONSOLE* console)
{
  XSTRING   string;
  XSTRING   string2;

  if(!APPFLOW_EXTENDED.GetConsole())
    { 
      return false;
    }

  string  = __L("Local IP");
  string2.Format(__L("[%s]"), localIP.Get());
  APPFLOW_EXTENDED.GetConsole()->Show_Line(string, string2);

  string  = __L("Internet Connection");
  string2.ConvertFromBoolean(haveinternetconnection, XSTRINGBOOLEANMODE_HUMAN);   
  APPFLOW_EXTENDED.GetConsole()->Show_Line(string, string2);

  if(haveinternetconnection)
    {
      string  = __L("Public IP");
      string2.Format(__L("[%s]"), publicIP.Get());
      APPFLOW_EXTENDED.GetConsole()->Show_Line(string, string2);
    }
 
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPFLOWEXTENDED_INTERNETSTATUS::Serialize()
* @brief      Serialize
* @ingroup    APPFLOW
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWEXTENDED_INTERNETSTATUS::Serialize()
{
  Primitive_Add<XSTRING*>(&localIP            , __L("localIP"));
  
  Primitive_Add<bool>(haveinternetconnection  , __L("internetconnection"));
  Primitive_Add<XSTRING*>(&publicIP           , __L("publicIP")); 

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool APPFLOWEXTENDED_INTERNETSTATUS::Deserialize()
* @brief      Deserialize
* @ingroup    APPFLOW
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool APPFLOWEXTENDED_INTERNETSTATUS::Deserialize()
{ 
  Primitive_Extract<XSTRING&>(localIP            , __L("localIP"));
  
  Primitive_Extract<bool>(haveinternetconnection , __L("internetconnection"));
  Primitive_Extract<XSTRING&>(publicIP           , __L("publicIP"));
 
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void APPFLOWEXTENDED_INTERNETSTATUS::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    APPFLOW
* 
* --------------------------------------------------------------------------------------------------------------------*/
void APPFLOWEXTENDED_INTERNETSTATUS::Clean()
{
  cfg                     = NULL;
  internetservices        = NULL;

  localIP.Empty();

  haveinternetconnection  = false;
  publicIP.Empty();    
}


#pragma endregion
