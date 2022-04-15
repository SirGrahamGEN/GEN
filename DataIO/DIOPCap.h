/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOPCap.h
* 
* @class      DIOPCAP
* @brief      Interface PCap Library class
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
* *---------------------------------------------------------------------------------------------------------------------*/

#ifdef DIOPCAP_ACTIVE

#ifndef _DIOPCAP_H_
#define _DIOPCAP_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XVector.h"
#include "XString.h"
#include "XBuffer.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define DIOPCAPETHERNETMACSIZE        6

#define DIOPCAPETHERNETTYPE_PUP       0x0002              // Xerox PUP
#define DIOPCAPETHERNETTYPE_IP        0x0800              // IP
#define DIOPCAPETHERNETTYPE_ARP       0x0860              // Address resolution
#define DIOPCAPETHERNETTYPE_REVARP    0x8035              // Reverse ARP

#define DIOPCAPIPPROTOCOLTYPE_TCP     6                   // TCP
#define DIOPCAPIPPROTOCOLTYPE_UDP     17                  // UDP

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XTHREADCOLLECTED;
class XMUTEX;



typedef struct
{
  XBYTE                               byte1;
  XBYTE                               byte2;
  XBYTE                               byte3;
  XBYTE                               byte4;

} DIOPCAPIPADDRESS;


typedef struct
{
  XBYTE                               MACtarget[DIOPCAPETHERNETMACSIZE];
  XBYTE                               MACsource[DIOPCAPETHERNETMACSIZE];
  XWORD                               type;

} DIOPCAPETHERNETHEADER;


typedef struct
{
  XBYTE                               ver_ihl;            // Version (4 bits) + Internet header length (4 bits)
  XBYTE                               typeservice;        // Type of service
  XWORD                               len;                // Total length
  XWORD                               identification;     // Identification
  XWORD                               flags_fo;           // Flags (3 bits) + Fragment offset (13 bits)
  XBYTE                               ttl;                // Time to live
  XBYTE                               protocol;           // Protocol
  XWORD                               CRC;                // Header checksum
  DIOPCAPIPADDRESS                    sourceaddr;         // Source address
  DIOPCAPIPADDRESS                    targetaddr;         // Target address

} DIOPCAPIPHEADER;


typedef struct
{
  XWORD                               sourceport;         // Source port
  XWORD                               targetport;         // Target port
  XWORD                               len;                // Datagram length
  XWORD                               CRC;                // Checksum

} DIOPCAPUDPHEADER;


typedef struct
{
  XWORD                               sourceport;
  XWORD                               targetport;
  XDWORD                              seq;
  XDWORD                              ack_seq;
  XWORD                               dataoffctrl;
  XWORD                               window;
  XWORD                               check;
  XWORD                               urg_ptr;

} DIOPCAPTCPHEADER;


class DIOPCAPNETINTERFACE
{
  public:
                                      DIOPCAPNETINTERFACE           ();
    virtual                          ~DIOPCAPNETINTERFACE           ();

    XSTRING*                          GetName                       ();
    XSTRING*                          GetDescription                ();

    bool                              SetName                       (XCHAR* name);
    bool                              SetName                       (XSTRING& name);

    bool                              SetDescription                (XCHAR* name);
    bool                              SetDescription                (XSTRING& name);

  private:

    void                              Clean                         ();

    XSTRING                           name;
    XSTRING                           description;
};


class DIOPCAPFRAME
{
  public:
                                      DIOPCAPFRAME                  (bool hardwareuselittleendian);
    virtual                          ~DIOPCAPFRAME                  ();

    bool                              GetHeaderEthernet             (DIOPCAPETHERNETHEADER& ethernetheader);
    bool                              GetHeaderIP                   (DIOPCAPIPHEADER& ipheader);
    bool                              GetHeaderUDP                  (DIOPCAPUDPHEADER& udpheader);
    bool                              GetHeaderTCP                  (DIOPCAPTCPHEADER& tcpheader);

    XBYTE*                            UserData_Get                  ();
    int                               UserData_GetSize              ();

    XBUFFER*                          GetData                       ();
    bool                              SetData                       (XBYTE* data, XDWORD size);

  protected:

    bool                              hardwareuselittleendian;

  private:

    void                              Clean                         ();

    XBUFFER*                          data;

};


class DIOPCAP
{
  public:

                                      DIOPCAP                       ();
    virtual                          ~DIOPCAP                       ();

    XVECTOR<DIOPCAPNETINTERFACE*>*    GetNetInterfaces              ();
    DIOPCAPNETINTERFACE*              GetNetInterface               (int index);

    virtual bool                      Ini                           ();

    bool                              Capture_Start                 (int index, bool promiscuousmode = true, int timeout = 1000);
    virtual bool                      Capture_Start                 (DIOPCAPNETINTERFACE* netinterface, bool promiscuousmode = true, int timeout = 1000) = 0;
    virtual bool                      Capture_End                   () = 0;

    DIOPCAPFRAME*                     Frames_Get                    (int index);
    bool                              Frames_Delete                 (int index);
    XVECTOR<DIOPCAPFRAME*>*           Frames_Get                    ();
    bool                              Frames_DeleteAll              ();

    virtual bool                      End                           ();

  protected:

    bool                              Frames_Add                    (XBYTE* data,XDWORD size);

    virtual bool                      CreateListNetInterfaces       () = 0;
    bool                              DeleteListNetInterfaces       ();

    XVECTOR<DIOPCAPNETINTERFACE*>     netinterfaces;
    XMUTEX*                           xmutexframes;
    XVECTOR<DIOPCAPFRAME*>            frames;    

  private:

    void                              Clean                         ();
};

/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif


#endif