/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIODNSProtocol.h
* 
* @class      DIODNSPROTOCOL
* @brief      Data Input/Output Domain Network System (DNS) protocol structs
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

#ifndef _DIODNSPROTOCOL_H_
#define _DIODNSPROTOCOL_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XBase.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


#define DIODNSPROTOCOL_DEFAULTPORT         53

#define DIODNSPROTOCOL_TYPEQUERY_A          1     // Ipv4 address
#define DIODNSPROTOCOL_TYPEQUERY_NS         2     // Nameserver
#define DIODNSPROTOCOL_TYPEQUERY_CNAME      5     // Canonical name
#define DIODNSPROTOCOL_TYPEQUERY_SOA        6     // Start of authority zone */
#define DIODNSPROTOCOL_TYPEQUERY_PTR       12     // Domain name pointer
#define DIODNSPROTOCOL_TYPEQUERY_MX        15     // Mail server

#define DIODNSPROTOCOL_DEFAULTTIMEOUT       5     // default timeout


// Header
typedef struct
{
  XWORD                           id;             // identification number

  XBYTE                           rd      : 1;    // recursion desired
  XBYTE                           tc      : 1;    // truncated message
  XBYTE                           aa      : 1;    // authoritive answer
  XBYTE                           opcode  : 4;    // purpose of message
  XBYTE                           qr      : 1;    // query/response flag

  XBYTE                           rcode   : 4;    // response code
  XBYTE                           cd      : 1;    // checking disabled
  XBYTE                           ad      : 1;    // authenticated data
  XBYTE                           z       : 1;    // its z! reserved
  XBYTE                           ra      : 1;    // recursion available

  XWORD                           q_count;        // number of question entries
  XWORD                           ans_count;      // number of answer entries
  XWORD                           auth_count;     // number of authority entries
  XWORD                           add_count;      // number of resource entries

} DIODNSPROTOCOL_HEADER;

// Constant sized fields of query structure
typedef struct
{
  XWORD                           qtype;
  XWORD                           qclass;

} DIODNSPROTOCOL_QUESTION;


// Constant sized fields of the resource record structure
#pragma pack(push, 1)
typedef struct
{
  XWORD                           type;
  XWORD                           _class;
  XDWORD                          ttl;
  XWORD                           data_len;

} DIODNSPROTOCOL_R_DATA;
#pragma pack(pop)


// Pointers to resource record contents
typedef struct RES_RECORD
{
  XBYTE*                          name;
  DIODNSPROTOCOL_R_DATA*          resource;
  XBYTE*                          rdata;

} DIODNSPROTOCOL_RES_RECORD;


// Structure of a Query
typedef struct
{
  XBYTE*                          name;
  DIODNSPROTOCOL_QUESTION*        question;

} DIODNSPROTOCOL_QUERY;


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

