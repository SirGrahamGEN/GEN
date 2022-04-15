/**-------------------------------------------------------------------------------------------------------------------
*
* @file       GRP2DColor.h
*
* @class      GRP2DCOLOR
* @brief      Graphics 2D color definitios (agg color definitions)
* @ingroup    GRAPHIC
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

#ifndef _GRP2DCOLOR_H_
#define _GRP2DCOLOR_H_


/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"



/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XMemory_Control.h"

#include "agg_color_gray.h"
#include "agg_color_rgba.h"


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#ifndef GRP2DCOLOR
typedef void         GRP2DCOLOR;
#endif

#ifndef GRP2DCOLOR_GRAY8
typedef agg::gray8   GRP2DCOLOR_GRAY8;
#endif

#ifndef GRP2DCOLOR_GRAY16
typedef agg::gray16  GRP2DCOLOR_GRAY16;
#endif

#ifndef GRP2DCOLOR_RGBA8
typedef agg::rgba8   GRP2DCOLOR_RGBA8;
#endif

#ifndef GRP2DCOLOR_RGBA16
typedef agg::rgba16  GRP2DCOLOR_RGBA16;
#endif

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/


/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif


