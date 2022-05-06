/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOProtocolConnectionsInUseDefinitions.h
*
* @class      DIOPROTOCOL_CONNECTIONSINUSEDEFINITIONS
* @brief      Data Input/Output Use Generic Binary Protocol definitions
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

#ifndef _DIOPROTOCOL_CONNECTIONSINUSEDEFINITIONS_H_
#define _DIOPROTOCOL_CONNECTIONSINUSEDEFINITIONS_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

enum DIOPROTOCOL_CONNECTIONSINUSEID
{
  DIOPROTOCOL_CONNECTIONSINUSEID_UNKNOW                       =  0          ,
  DIOPROTOCOL_CONNECTIONSINUSEID_INIPROTOCOL                                ,
  DIOPROTOCOL_CONNECTIONSINUSEID_ENDPROTOCOL                                ,
  DIOPROTOCOL_CONNECTIONSINUSEID_ANSWER                                     ,
  DIOPROTOCOL_CONNECTIONSINUSEID_END                          =  0x10000000 ,
};

/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif



