/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOPing.h
* 
* @class      DIOPING
* @brief      Data Input/Output Ping protocol class
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

#ifndef _DIOPING_H_
#define _DIOPING_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XBase.h"
#include "XVector.h"
#include "XEvent.h"
#include "XSubject.h"

#include "DIOURL.h"
#include "DIOStreamICMPConfig.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

#define DIOPING_DEFAULTNRETRYS              3
#define DIOPING_DEFAULTTIMEBETWEENCHECKS    500       // Milliseconds

#define DIOPING_ICMP_ECHOREPLY              0
#define DIOPING_ICMP_ECHOREQ                8
#define DIOPING_REQ_TICKETSIZE              32        // Echo Request Data size

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


typedef struct
{
  XBYTE s_b1;
  XBYTE s_b2;
  XBYTE s_b3;
  XBYTE s_b4;

} DIOPING_ADDR_BYTE;


typedef struct
{
  XWORD s_w1;
  XWORD s_w2;

} DIOPING_ADDR_WORD;


typedef struct
{
  union
    {
      DIOPING_ADDR_BYTE   addrbyte;
      DIOPING_ADDR_WORD   addrword;
      XDWORD              addr;

    } INADDR_UNION;

} DIOPING_INADDR;


// IP Header -- RFC 791
typedef struct
{
  XBYTE                           VIHL;          // Version and IHL
  XBYTE                           typeservice;   // Type Of Service
  short                           fulllen;       // Total Length
  short                           ID;            // Identification
  short                           flagoff;       // Flags and Fragment Offset
  XBYTE                           TTL;           // Time To Live
  XBYTE                           protocol;      // Protocol
  XWORD                           checksum;      // Checksum
  DIOPING_INADDR                  iasource;      // Internet Address - Source
  DIOPING_INADDR                  iatarget;      // Internet Address - Destination

} DIOPING_IPHDR;


// ICMP Header - RFC 792
typedef struct
{
  XBYTE                           type;          // Type
  XBYTE                           code;          // Code
  XWORD                           checksum;      // Checksum
  XWORD                           ID;            // Identification
  XWORD                           seq;           // Sequence
  char                            data;          // Data

} DIOPING_ICMPHDR;


// ICMP Echo Request
typedef struct
{
  DIOPING_ICMPHDR                 icmphdr;
  XDWORD                          applicationID;
  XDWORD                          time;
  char                            cdata[DIOPING_REQ_TICKETSIZE];

} DIOPING_ECHOREQUEST;


// ICMP Echo Reply
typedef struct
{
  DIOPING_IPHDR                   iphdr;
  DIOPING_ECHOREQUEST             echorequest;
//char                            cfiller[256];

} DIOPING_ECHOREPLY;



class XTIMER;
class XPUBLISHER;
class DIOSTREAMICMPCONFIG;
class DIOSTREAMICMP;


class DIOPINGREPLY
{
  public:
                                  DIOPINGREPLY                ();
    virtual                      ~DIOPINGREPLY                ();

    XDWORD                        GetSequence                 ();
    void                          SetSequence                 (XDWORD sequence);

    XSTRING*                      GetFromIP                   ();

    XDWORD                        GetSizeRequest              ();
    void                          SetSizeRequest              (XDWORD sizerequest);

    XDWORD                        GetTimeElapsed              ();
    void                          SetTimeElapsed              (XDWORD timeelapsed);

    XBYTE                         GetTTL                      ();
    void                          SetTTL                      (XBYTE TTL);

  private:

    void                          Clean                       ();

    XDWORD                        sequence;
    XSTRING                       fromIP;
    XDWORD                        sizerequest;
    XDWORD                        timeelapsed;
    XBYTE                         TTL;
};


class DIOPING :  public XSUBJECT
{
  public:

                                  DIOPING                     ();
    virtual                      ~DIOPING                     ();

    static bool                   GetIsInstanced              ();
    static DIOPING&               GetInstance                 ();
    static bool                   SetInstance                 (DIOPING* instance);
    static bool                   DelInstance                 ();

    DIOURL*                       GetTarget                   ();

    bool                          Set                         (XCHAR* urltarget , XCHAR* IPLocal = NULL);
    bool                          Set                         (DIOURL& urltarget, XCHAR* IPLocal = NULL);

    virtual bool                  Do                          (XDWORD nretries = DIOPING_DEFAULTNRETRYS, XDWORD timebetweenchecks = DIOPING_DEFAULTTIMEBETWEENCHECKS, bool exitfirstgoodreply = false);


    XVECTOR<DIOPINGREPLY*>*       GetReplys                   ();
    bool                          WasConnected                ();
    XDWORD                        CalculateMeanTime           ();

    bool                          DeleteAllReplys             ();

  protected:

    bool                          AddReply                    (XWORD sequence, XCHAR* IPfrom, XDWORD sizerequest, XDWORD elapsed, XBYTE TTL);
    XWORD                         CalculeCheckSum             (XWORD *addr, int len);

    XTIMER*                       xtimer;

    XDWORD                        applicationID;

    DIOURL*                       urltarget;
    XSTRING                       IPLocal;

    XMUTEX*                       xmutexping;

    XVECTOR<DIOPINGREPLY*>        replys;
    XMUTEX*                       xmutexreplys;

    XDWORD                        nretries;
    XDWORD                        timebetweenchecks;

  private:

    void                          Clean                       ();

    static DIOPING*               instance;
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

