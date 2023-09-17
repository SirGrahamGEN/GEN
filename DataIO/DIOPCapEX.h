/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOPCapEX.h
* 
* @class      DIOPCAPEX
* @brief      Data Input/Output PCap Extended Library class
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

#ifndef _DIOPCAPEX_H_
#define _DIOPCAPEX_H_

#ifdef DIO_PCAP_ACTIVE

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XVector.h"

#include "DIOURL.h"

#include "DIOPCap.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

typedef struct
{
  XWORD            ID;

  XBYTE            QR:1;
  XBYTE            opcode:4;
  XBYTE            AA:1;
  XBYTE            TC:1;
  XBYTE            RD:1;

  XBYTE            RA:1;
  XBYTE            Z:3;
  XBYTE            rcode:4;

  XWORD            QDcount;
  XWORD            ANcount;
  XWORD            NScount;
  XWORD            ARcount;

} DIOPCAPEXDNSHEADER;


typedef struct
{
  DIOURL           url;
  XWORD            qtype;
  XWORD            qclass;

} DIOPCAPEXDNSASK;


typedef struct
{
  DIOURL           url;
  XWORD            qtype;
  XWORD            qclass;
  XWORD            ttl;
  XWORD            rlenght;
  XWORD            preference;
  XWORD            exchange;
  XWORD            answer;
  XBYTE            address[4];

} DIOPCAPEXDNSREQUEST;

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

class DIOPCAPFRAMEEX : public DIOPCAPFRAME
{
  public:
                                  DIOPCAPFRAMEEX                (bool hardwareuselittleendian);
    virtual                      ~DIOPCAPFRAMEEX                ();

    bool                          GetDNSAsk                     (DIOPCAPEXDNSHEADER& header,DIOPCAPEXDNSASK& ask);
    bool                          GetDNSRequest                 (DIOPCAPEXDNSHEADER& header,DIOPCAPEXDNSREQUEST& request);

    int                           DNSnameFormatToString         (XBYTE* urlDNS,DIOURL& url);
    bool                          StringToDNSNameFormat         (XSTRING& name,XBUFFER& nameDNS);

  private:

    void                          Clean                         ();
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

#endif

