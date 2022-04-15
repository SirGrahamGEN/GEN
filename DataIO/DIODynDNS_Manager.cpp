/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIODynDNS_Manager.cpp
*
* @class      DIODYNDNS_MANAGER
* @brief      Data Input/Output DYNDNS Manager class
* @ingroup    DATAIO
*
* @copyright  GEN Group. All right reserved.
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

#include "DIOURL.h"
#include "DIODynDNS_Manager.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIODYNDNS_MANAGER::DIODYNDNS_MANAGER()
* @brief      Constructor
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIODYNDNS_MANAGER::DIODYNDNS_MANAGER()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIODYNDNS_MANAGER::~DIODYNDNS_MANAGER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIODYNDNS_MANAGER::~DIODYNDNS_MANAGER()
{
  DeleteAllDNS();
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIODYNDNS_MANAGER::GetLogin()
* @brief      GetLogin
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIODYNDNS_MANAGER::GetLogin()
{
  return &login;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIODYNDNS_MANAGER::GetPassword()
* @brief      GetPassword
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIODYNDNS_MANAGER::GetPassword()
{
  return &password;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIODYNDNS_MANAGER::AddDNS(XSTRING& DNS)
* @brief      AddDNS
* @ingroup    DATAIO
*
* @param[in]  DNS :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @brief      DeleteAllDNS
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @brief      GetNDNS
* @ingroup    DATAIO
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD DIODYNDNS_MANAGER::GetNDNS()
{
  return DNSlist.GetSize();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIODYNDNS_MANAGER::AssingAll()
* @brief      AssingAll
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIODYNDNS_MANAGER::AssingAll()
{
  DIODYNDNS_STATUSCODE  statusupdate;
  DIOURL                url;
  DIOIP                 IP;
  int                   result = 0;
  bool                  status = true;

  DIODYNDNS* dyndns = new DIODYNDNS();
  if(!dyndns) return false;

  dyndns->GetLogin()->Set(login.Get());
  dyndns->GetPassword()->Set(password.Get());

  if(!DNSlist.GetSize()) status = false;

  for(XDWORD c=0; c<DNSlist.GetSize(); c++)
    {
      XSTRING* DNS = DNSlist.Get(c);
      if(DNS)
        {
          url.Set(DNS->Get());

          bool ischanged = false;

          if(dyndns->IsChangedPublicIP(url, ischanged, &IP))
            {
              if(ischanged)
                {
                  statusupdate = dyndns->Update(url, IP);
                  if(statusupdate == DIODYNDNS_STATUSCODE_GOOD) result = 1;

                } else result = 2;

            } else result = 0;
        }

      if(!result) status = false;
    }

  delete dyndns;

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIODYNDNS_MANAGER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIODYNDNS_MANAGER::Clean()
{

}



