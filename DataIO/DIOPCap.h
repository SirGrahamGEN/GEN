/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOPCap.h
* 
* @class      DIOPCAP
* @brief      Data Input/Output PCap Library class
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

#ifndef _DIOPCAP_H_
#define _DIOPCAP_H_

#ifdef DIO_PCAP_ACTIVE

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XVector.h"
#include "XString.h"
#include "XBuffer.h"

#include "DIOMAC.h"
#include "DIOIP.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

#define DIOPCAPETHERNETMACSIZE        6

#define DIOPCAPETHERNETTYPE_PUP       0x0002              // Xerox PUP
#define DIOPCAPETHERNETTYPE_IP        0x0800              // IP
#define DIOPCAPETHERNETTYPE_ARP       0x0860              // Address resolution
#define DIOPCAPETHERNETTYPE_REVARP    0x8035              // Reverse ARP

#define DIOPCAPIPPROTOCOLTYPE_ICMP    1                   // ICMP
#define DIOPCAPIPPROTOCOLTYPE_TCP     6                   // TCP
#define DIOPCAPIPPROTOCOLTYPE_UDP     17                  // UDP

enum DIOPCAPPROTOCOL_TYPE
{
  DIOPCAPPROTOCOL_TYPE_UNKNOWN       =  0 ,
  DIOPCAPPROTOCOL_TYPE_ICMP               ,
  DIOPCAPPROTOCOL_TYPE_UDP                ,
  DIOPCAPPROTOCOL_TYPE_TCP                ,
};


typedef struct
{
  XBYTE                               MACtarget[DIOPCAPETHERNETMACSIZE];
  XBYTE                               MACsource[DIOPCAPETHERNETMACSIZE];
  XWORD                               type;

} DIOPCAPETHERNETHEADER;


typedef struct
{
  XBYTE                               ver_ihl;                  // Version (4 bits) + Internet header length (4 bits)
  XBYTE                               typeservice;              // Type of service
  XWORD                               len;                      // Total length
  XWORD                               identification;           // Identification
  XWORD                               flags_fo;                 // Flags (3 bits) + Fragment offset (13 bits)
  XBYTE                               ttl;                      // Time to live
  XBYTE                               protocol;                 // Protocol  https://en.wikipedia.org/wiki/List_of_IP_protocol_numbers
  XWORD                               CRC;                      // Header checksum
  XBYTE                               sourceaddr[4];            // Source address
  XBYTE                               targetaddr[4];            // Target address

} DIOPCAPIPHEADER;


typedef struct
{
  XWORD                               sourceport;               // Source port
  XWORD                               targetport;               // Target port
  XWORD                               datagramlen;              // Datagram length
  XWORD                               checksum;                 // Checksum

} DIOPCAPUDPHEADER;


typedef struct
{
  XWORD                               sourceport;               // Source port
  XWORD                               targetport;               // Target port
  XDWORD                              sequencenumber;           // Sequence number    
  XDWORD                              acknowledgementnumber;    // Acknowledgement Number
  XWORD                               hlenflags;                // Header Length + Flags                 
  XWORD                               windowsize;               // Windows size;
  XWORD                               checksum;                 // CheckSum
  XWORD                               urgentpointer;            // Urgent pointer

} DIOPCAPTCPHEADER;


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

class XTHREADCOLLECTED;
class XMUTEX;

class DIOPCAPNETINTERFACE
{
  public:
                                      DIOPCAPNETINTERFACE           ();
    virtual                          ~DIOPCAPNETINTERFACE           ();

    XSTRING*                          GetName                       ();
    XSTRING*                          GetDescription                ();

    bool                              IsUp                          ();
    void                              SetIsUp                       (bool isup);            

    bool                              IsRunning                     ();
    void                              SetIsRunning                  (bool isrunning);            

    bool                              IsWireless                    ();
    void                              SetIsWireless                 (bool iswireless);            

    bool                              IsLoopBack                    ();      
    void                              SetIsLoopBack                 (bool isloopback);      

  private:

    void                              Clean                         ();

    XSTRING                           name;
    XSTRING                           description;

    bool                              isup;  
    bool                              isrunning;  
    bool                              iswireless;  
    bool                              isloopback;      
};


class DIOPCAPFRAME
{
  public:
                                      DIOPCAPFRAME                  (bool hardwareuselittleendian, bool isloopback);
    virtual                          ~DIOPCAPFRAME                  ();

   
    XBUFFER*                          GetData                       ();
    bool                              SetData                       (XBYTE* data, XDWORD size);

    DIOPCAPPROTOCOL_TYPE              GetProtocolType               ();
    void                              GetProtocolTypeString         (XSTRING& protocoltypestr);
    bool                              SetProtocolType               (DIOPCAPPROTOCOL_TYPE protocoltype);
   
    DIOMAC*                           GetSourceMAC                  ();   
    DIOMAC*                           GetTargetMAC                  ();   

    DIOIP*                            GetSourceIP                   ();   
    DIOIP*                            GetTargetIP                   ();   

    XWORD                             GetSourcePort                 ();
    bool                              SetSourcePort                 (XWORD port);

    XWORD                             GetTargetPort                 ();
    bool                              SetTargetPort                 (XWORD port);

    XBYTE*                            GetDataPayload                ();
    int                               GetDataPayLoadSize            (); 
 
    XDWORD                            GetAllHeadersSize             ();
    void                              SetAllHeadersSize             (XDWORD sizeheader);

    bool                              GetHeader                     (DIOPCAPETHERNETHEADER& header);    
    bool                              GetHeader                     (DIOPCAPIPHEADER& header);
    bool                              GetHeader                     (DIOPCAPUDPHEADER& header);
    bool                              GetHeader                     (DIOPCAPTCPHEADER& header); 

    bool                              Set                           (DIOPCAPETHERNETHEADER* ethernet_header); 
    bool                              Set                           (DIOPCAPIPHEADER* IP_header);
    bool                              Set                           (DIOPCAPUDPHEADER* UDP_header);
    bool                              Set                           (DIOPCAPTCPHEADER* TCP_header);    
    bool                              Set                           (XBYTE* data_payload, XDWORD size);
    
  protected:

    bool                              hardwareuselittleendian;
    bool                              isloopback;  

  private:

    void                              Clean                         ();

    XBUFFER*                          data; 
 
    DIOPCAPETHERNETHEADER*            ethernet_header; 
    DIOPCAPIPHEADER*                  IP_header;
    DIOPCAPUDPHEADER*                 UDP_header;
    DIOPCAPTCPHEADER*                 TCP_header;  

    DIOPCAPPROTOCOL_TYPE              protocoltype;
    

    DIOMAC                            sourceMAC;   
    DIOMAC                            targetMAC;   

    DIOIP                             sourceIP;   
    DIOIP                             targetIP;   

    XWORD                             sourceport;
    XWORD                             targetport;
  
    XBYTE*                            data_payload;
    XDWORD                            data_payloadsize;  

    XDWORD                            allheaderssize;
};


class DIOPCAP
{
  public:

                                      DIOPCAP                       ();
    virtual                          ~DIOPCAP                       ();

    XVECTOR<DIOPCAPNETINTERFACE*>*    GetNetInterfaces              ();
    DIOPCAPNETINTERFACE*              GetNetInterface               (int index);
    DIOPCAPNETINTERFACE*              GetNetInterfaceSelected       ();

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

    bool                              Frames_Add                    (XBYTE* data, XDWORD size, bool isloopback = false);

    virtual bool                      CreateListNetInterfaces       () = 0;
    bool                              DeleteListNetInterfaces       ();


    XVECTOR<DIOPCAPNETINTERFACE*>     netinterfaces;
    DIOPCAPNETINTERFACE*              netinterfaceselected;
    XMUTEX*                           xmutexframes;
    XVECTOR<DIOPCAPFRAME*>            frames;    

  private:

    void                              Clean                         ();
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

#endif

