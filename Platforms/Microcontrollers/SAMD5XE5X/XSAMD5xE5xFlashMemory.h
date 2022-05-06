/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XSAMD5xE5xFlashMemory.h
*
* @class      XSAMD5XE5XFLASHMEMORY
* @brief      SAMD5xE5x Flash Memory class
* @ingroup    PLATFORM_SAMD5XE5X
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

#ifndef _XSAMD5XE5XFLASHMEMORY_H_
#define _XSAMD5XE5XFLASHMEMORY_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XBase.h"

#include "XSAMD5xE5x_HAL.h"


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/


//--- ABRHAMD5XE5X ------------------
//#define XSAMD5XE5XFLASHMEMORY_BASE      BKPSRAM_BASE
//#define XSAMD5XE5XFLASHMEMORY_MAXSIZE   4096

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XSAMD5XE5XFLASHMEMORY
{
  public:

                                  XSAMD5XE5XFLASHMEMORY     ();
    virtual                      ~XSAMD5XE5XFLASHMEMORY     ();

    bool                          Ini                       ();
    bool                          End                       ();

    bool                          Read                      (XDWORD offset, XBYTE* data, XDWORD size);
    bool                          Write                     (XDWORD offset, XBYTE* data, XDWORD size);

    bool                          EraseAll                  ();

};

/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif




