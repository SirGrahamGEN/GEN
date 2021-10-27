/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOEmailAddress.cpp
*
* @class      DIOEMAILADDRESS
* @brief      Data Input/Output Email Address class
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @copyright  Copyright(c) 2008 - 2016 GEN Group.
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

#include "DIOFactory.h"
#include "DIOURL.h"

#include "DIOEmailAddress.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOEMAILADDRESS::DIOEMAILADDRESS()
* @brief      Constructor
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOEMAILADDRESS::DIOEMAILADDRESS(): XSTRING()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOEMAILADDRESS::~DIOEMAILADDRESS()
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
DIOEMAILADDRESS::~DIOEMAILADDRESS()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOEMAILADDRESS::DIOEMAILADDRESS(XDWORD size)
* @brief      Constructor
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  XDWORD :
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOEMAILADDRESS::DIOEMAILADDRESS(XDWORD size): XSTRING(size)
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOEMAILADDRESS::DIOEMAILADDRESS(const char* url)
* @brief      Constructor
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  const :
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOEMAILADDRESS::DIOEMAILADDRESS(const char* url): XSTRING(url)
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOEMAILADDRESS::DIOEMAILADDRESS(const XCHAR* url)
* @brief      Constructor
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  const :
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOEMAILADDRESS::DIOEMAILADDRESS(const XCHAR* url): XSTRING(url)
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOEMAILADDRESS::DIOEMAILADDRESS(const XCHAR* url,XDWORD size)
* @brief      Constructor
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  const :
* @param[in]  XDWORD :
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOEMAILADDRESS::DIOEMAILADDRESS(const XCHAR* url,XDWORD size): XSTRING(url, size)
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOEMAILADDRESS::DIOEMAILADDRESS(DIOEMAILADDRESS& url)
* @brief      Constructor
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  DIOEMAILADDRESS& :
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOEMAILADDRESS::DIOEMAILADDRESS(DIOEMAILADDRESS& url): XSTRING(url)
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOEMAILADDRESS::DIOEMAILADDRESS(XSTRING& url)
* @brief      Constructor
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  XSTRING& :
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOEMAILADDRESS::DIOEMAILADDRESS(XSTRING& url): XSTRING(url)
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOEMAILADDRESS::DIOEMAILADDRESS(XWORD* url)
* @brief      Constructor
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  XWORD* :
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOEMAILADDRESS::DIOEMAILADDRESS(XWORD* url): XSTRING(url)
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOEMAILADDRESS::GetUser(XSTRING& user)
* @brief      GetUser
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  user :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOEMAILADDRESS::GetUser(XSTRING& user)
{
  user.Empty();

  int end = Find(DIOEMAILADDRESS_SEPARATOR, true);

  if(end == XSTRING_NOTFOUND) return false;
  if(!end)                  return false;

  return Copy(0, end, user)?true:false;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOEMAILADDRESS::GetDomain(XSTRING& domain)
* @brief      GetDomain
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  domain :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOEMAILADDRESS::GetDomain(XSTRING& domain)
{
  domain.Empty();

  int start = Find(DIOEMAILADDRESS_SEPARATOR, true);

  if(start == XSTRING_NOTFOUND) return false;
  if(!start)                    return false;

  return Copy(start+1, domain)?true:false;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOEMAILADDRESS::IsValid()
* @brief      IsValid
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOEMAILADDRESS::IsValid()
{
  XSTRING  user;
  XSTRING  domain;
  bool     status = false;

  if(!GetUser(user))      return false;
  if(!GetDomain(domain))  return false;

  DIOIP   IP;
  DIOURL* url = new DIOURL();
  if(!url) return false;

  url->Set(domain);

  status = url->ResolveURL(IP);

  delete url;

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOEMAILADDRESS::Clean()
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
void DIOEMAILADDRESS::Clean()
{

}


