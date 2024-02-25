/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       Common.js
* 
* @class      
* @brief      Common.js (JavaScript with definitions and global var of GEN Script Libs)
* @ingroup    COMMON
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


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

const LOG_LEVEL   = { INFO      : 1,
                      WARNING   : 2,
                      ERROR     : 3,
                    };

const TRACE_COLOR = { BLACK     : 0,
                      BLUE      : 1,
                      GREEN     : 2,
                      PURPLE    : 3,
                      RED       : 4,
                      GRAY      : 5,
                    };


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

var scriptlog   = GetPathScript() +  GetNameScript() + ".log";
var scriptname  = GetNameScript() + ".js";

