/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XSAMD5xE5xDebugTrace.h
*
* @class      XSAMD5XE5XTRACE
* @brief      SAMD5xE5x debug trace class
* @ingroup    PLATFORM_SAMD5XE5X
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
*---------------------------------------------------------------------------------------------------------------------*/

#ifndef _XSAMD5XE5XTRACE_H_
#define _XSAMD5XE5XTRACE_H_

#ifdef XTRACE_ACTIVE

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XBase.h"
#include "XBuffer.h"
#include "XString.h"
#include "XTrace.h"

#include "DIOURL.h"

#include "XSAMD5xE5x_HAL.h"
#include "XSAMD5XE5XFactory.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XSAMD5XE5XTRACE : public XTRACE
{
  public:
                                    XSAMD5XE5XTRACE       ();
    virtual                        ~XSAMD5XE5XTRACE       ();

    void                            PrintSpecial          (XTRACE_TARGET* target, XBYTE level, XCHAR* string);

    bool                            IniUARTSpecial        ();

  private:

    void                            Clean                 ();

    struct io_descriptor*           huart;
    XBUFFER                         xbuffercache;
};


/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif

#endif


