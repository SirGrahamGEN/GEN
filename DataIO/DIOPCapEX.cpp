/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOPCapEX.cpp
* 
* @class      DIOPCAPEX
* @brief      Interface PCap Extended Library class
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
* ---------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"

#ifdef DIOPCAP_ACTIVE

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

#include "XFactory.h"
#include "XTrace.h"

#include "DIOPCapEX.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOPCAPFRAMEEX::DIOPCAPFRAMEEX
* @brief      Constructor
* @ingroup    DATAIO
*
* @param[in]  bool : true hardware use littleendian.
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOPCAPFRAMEEX::DIOPCAPFRAMEEX(bool hardwareuselittleendian): DIOPCAPFRAME(hardwareuselittleendian)
{
   Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPCAPFRAMEEX::~DIOPCAPFRAMEEX()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @return     Does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOPCAPFRAMEEX::~DIOPCAPFRAMEEX()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAPFRAMEEX::GetDNSAsk(DIOPCAPEXDNSHEADER& header,DIOPCAPEXDNSASK& ask)
* @brief      GetDNSAsk
* @ingroup    DATAIO
*
* @param[in]  header : 
* @param[in]  ask : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAPFRAMEEX::GetDNSAsk(DIOPCAPEXDNSHEADER& header,DIOPCAPEXDNSASK& ask)
{
  DIOPCAPEXDNSHEADER* _header = (DIOPCAPEXDNSHEADER*)UserData_Get();
  if(!_header) return false;

  memcpy((XBYTE*)&header,(XBYTE*)(_header),sizeof(DIOPCAPEXDNSHEADER));

  if(hardwareuselittleendian)
    {
      SWAPWORD(header.ID);
      SWAPWORD(header.QDcount);
      SWAPWORD(header.ANcount);
      SWAPWORD(header.NScount);
      SWAPWORD(header.ARcount);
    }

  XBYTE* _url = (XBYTE*)_header;
  _url+=sizeof(DIOPCAPEXDNSHEADER);

  XDWORD size = DNSnameFormatToString(_url,ask.url);

  XBYTE* data = (XBYTE*)(UserData_Get());
  data+=(sizeof(DIOPCAPEXDNSHEADER)+size);

  XWORD* data2 = (XWORD*)data;
  ask.qclass = (*data2);   SWAPWORD(ask.qclass);
  data2++;
  ask.qtype  = (*data2);   SWAPWORD(ask.qtype);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAPFRAMEEX::GetDNSRequest(DIOPCAPEXDNSHEADER& header,DIOPCAPEXDNSREQUEST& request)
* @brief      GetDNSRequest
* @ingroup    DATAIO
*
* @param[in]  header : 
* @param[in]  request : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAPFRAMEEX::GetDNSRequest(DIOPCAPEXDNSHEADER& header,DIOPCAPEXDNSREQUEST& request)
{
  DIOPCAPEXDNSHEADER* _header = (DIOPCAPEXDNSHEADER*)UserData_Get();
  if(!_header) return false;

  memcpy((XBYTE*)&header,(XBYTE*)(_header),sizeof(DIOPCAPEXDNSHEADER));

  if(hardwareuselittleendian)
    {
      SWAPWORD(header.ID);
      SWAPWORD(header.QDcount);
      SWAPWORD(header.ANcount);
      SWAPWORD(header.NScount);
      SWAPWORD(header.ARcount);
    }

  XBYTE* _url = (XBYTE*)_header;
  _url+=sizeof(DIOPCAPEXDNSHEADER);

  for(int c=0;c<header.ANcount;c++)
    {
      XDWORD size = DNSnameFormatToString(_url,request.url);

      XBYTE*  data = (XBYTE*)(UserData_Get());
      data+=(sizeof(DIOPCAPEXDNSHEADER)+size);

      XWORD*  data2 = (XWORD*)data;

      request.qclass      = (*data2);  SWAPWORD(request.qclass);      data2++;
      request.qtype       = (*data2);  SWAPWORD(request.qtype);       data2++;
      request.ttl         = (*data2);  SWAPWORD(request.ttl);         data2++;
      request.rlenght     = (*data2);  SWAPWORD(request.rlenght);     data2++;
      request.preference  = (*data2);  SWAPWORD(request.preference);  data2++;
      request.exchange    = (*data2);  SWAPWORD(request.exchange);    data2++;

      data = (XBYTE*)data2;
      request.address.byte1 = (*data); data++;
      request.address.byte2 = (*data); data++;
      request.address.byte3 = (*data); data++;
      request.address.byte4 = (*data); data++;
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int DIOPCAPFRAMEEX::DNSnameFormatToString(XBYTE* urlDNS,DIOURL& url)
* @brief      DNSnameFormatToString
* @ingroup    DATAIO
*
* @param[in]  urlDNS : 
* @param[in]  url : 
* 
* @return     int : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
int DIOPCAPFRAMEEX::DNSnameFormatToString(XBYTE* urlDNS,DIOURL& url)
{
  int c = 0;

  while(urlDNS[c])
   {
     int counter = urlDNS[c];

     c++;

     for(int d=0;d<counter;d++)
       {
         url += urlDNS[c];
         c++;
       }

     if(urlDNS[c]) url+=__L(".");
   }

  return c+1;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPCAPFRAMEEX::StringToDNSNameFormat(XSTRING& name,XBUFFER& nameDNS)
* @brief      StringToDNSNameFormat
* @ingroup    DATAIO
*
* @param[in]  name : 
* @param[in]  nameDNS : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOPCAPFRAMEEX::StringToDNSNameFormat(XSTRING& name,XBUFFER& nameDNS)
{
  /*
  XCHAR* _name = name.Get();

  nameDNS[0] =
  */


  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOPCAPFRAMEEX::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @return     void : does not return anything. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOPCAPFRAMEEX::Clean()
{

}


#endif



