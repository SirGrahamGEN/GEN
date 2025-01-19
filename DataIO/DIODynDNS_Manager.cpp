/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIODynDNS_Manager.cpp
* 
* @class      DIODYNDNS_MANAGER
* @brief      Data Input/Output DYNDNS Manager class
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

#include "DIODynDNS_Manager.h"

#include "DIOURL.h"

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
* @fn         DIODYNDNS_MANAGER::DIODYNDNS_MANAGER()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIODYNDNS_MANAGER::DIODYNDNS_MANAGER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIODYNDNS_MANAGER::~DIODYNDNS_MANAGER()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIODYNDNS_MANAGER::~DIODYNDNS_MANAGER()
{
  DeleteAllDNS();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIODYNDNS_MANAGER::GetLogin()
* @brief      Get login
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIODYNDNS_MANAGER::GetLogin()
{
  return &login;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIODYNDNS_MANAGER::GetPassword()
* @brief      Get password
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIODYNDNS_MANAGER::GetPassword()
{
  return &password;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIODYNDNS_MANAGER::AddDNS(XSTRING& DNS)
* @brief      Add DNS
* @ingroup    DATAIO
*
* @param[in]  DNS :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIODYNDNS_MANAGER::AddDNS(XSTRING& DNS)
{
  if(DNS.IsEmpty()) return false;

  XSTRING* _DNS = new XSTRING();
  if(!_DNS) return false;

  _DNS->Set(DNS);

  DNSlist.Add(_DNS);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIODYNDNS_MANAGER::DeleteAllDNS()
* @brief      Delete all DNS
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIODYNDNS_MANAGER::DeleteAllDNS()
{
  if(DNSlist.IsEmpty()) return false;

  DNSlist.DeleteContents();
  DNSlist.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIODYNDNS_MANAGER::GetNDNS()
* @brief      Get NDNS
* @ingroup    DATAIO
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIODYNDNS_MANAGER::GetNDNS()
{
  return DNSlist.GetSize();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIODYNDNS_MANAGER::AssingAll()
* @brief      Assing all
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIODYNDNS_MANAGER::AssingAll()
{
  DIODYNDNS_STATUSCODE  statusupdate;
  DIOURL                url;
  DIOIP                 IP; 
  bool                  error    = false;
  int                   nerrors  = 0;
  
  DIODYNDNS* dyndns = new DIODYNDNS();
  if(!dyndns) return false;

  dyndns->GetLogin()->Set(login.Get());
  dyndns->GetPassword()->Set(password.Get());

  if(!DNSlist.GetSize()) 
    {
      return true;
   }

  for(int d=0; d<3; d++)
    {
      nerrors = 0;

      for(XDWORD c=0; c<DNSlist.GetSize(); c++)
        {
          XSTRING* DNS = DNSlist.Get(c);
          if(DNS)
            {
              url.Set(DNS->Get());

              bool ischanged = false;   
 
              error  = false;        

              if(dyndns->IsChangedPublicIP(url, ischanged, &IP))
                {
                  if(ischanged)
                    {
                      statusupdate = dyndns->Update(url, IP);
                      if(statusupdate == DIODYNDNS_STATUSCODE_GOOD) 
                        {
                          error = false;
                        }
                       else
                        {
                          error = true;
                        }     

                    } 
                   else 
                    {
                      error = false;
                    }

                } 
               else 
                {
                  error = true;
                }
            }

          if(error) 
            {
              nerrors++;
            }
        }

      if(!nerrors)
        {
          break;
        }
    }

  delete dyndns;

  return nerrors?false:true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIODYNDNS_MANAGER::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIODYNDNS_MANAGER::Clean()
{

}


#pragma endregion

