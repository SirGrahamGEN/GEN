/**-------------------------------------------------------------------------------------------------------------------
*
* @file       GEN_DefaultXTraceCFG.h
*
* @class      GEN_DEFAULTXTRACECFG
* @brief      GEN Default XTrace Config
* @ingroup
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

#ifndef _GEN_DEFAULTXTRACECFG_H_
#define _GEN_DEFAULTXTRACECFG_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/


#define  GEN_XTRACE_NET_DEFAULT_01          __L("xtracegen.dyndns.org:10001")
#define  GEN_XTRACE_NET_DEFAULT_02          __L("xtracegen.dyndns.org:10002")
#define  GEN_XTRACE_NET_DEFAULT_03          __L("xtracegen.dyndns.org:10003")
#define  GEN_XTRACE_NET_DEFAULT_04          __L("xtracegen.dyndns.org:10004")
#define  GEN_XTRACE_NET_DEFAULT_05          __L("xtracegen.dyndns.org:10005")

#define  GEN_XTRACE_NET_CFG_DEFAULT_01      tracetarget[0].Format(__L("%d,%s"), XTRACE_TYPE_NET, GEN_XTRACE_NET_DEFAULT_01);
#define  GEN_XTRACE_NET_CFG_DEFAULT_02      tracetarget[1].Format(__L("%d,%s"), XTRACE_TYPE_NET, GEN_XTRACE_NET_DEFAULT_02);
#define  GEN_XTRACE_NET_CFG_DEFAULT_03      tracetarget[2].Format(__L("%d,%s"), XTRACE_TYPE_NET, GEN_XTRACE_NET_DEFAULT_03);
#define  GEN_XTRACE_NET_CFG_DEFAULT_04      tracetarget[3].Format(__L("%d,%s"), XTRACE_TYPE_NET, GEN_XTRACE_NET_DEFAULT_04);
//#define  GEN_XTRACE_NET_CFG_DEFAULT_05    tracetarget[4].Format(__L("%d,%s"), XTRACE_TYPE_NET, GEN_XTRACE_NET_DEFAULT_05);

#define  GEN_XTRACE_NET_CFG_DEFAULT_LOCAL   tracetarget[4].Format(__L("%d,*:10001"), XTRACE_TYPE_NET);

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/



/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif



