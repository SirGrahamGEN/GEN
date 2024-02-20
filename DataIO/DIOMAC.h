/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOMAC.h
* 
* @class      DIOMAC
* @brief      Data Input/Output MAC class
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

#ifndef _DIOMAC_H_
#define _DIOMAC_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XBase.h"
#include "XString.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

#define  DIOMAC_MAXSIZE         6
#define  DIOMAC_MAXSIZESTR      18

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class DIOMAC
{
  public:

                                  DIOMAC                        ();
    virtual                      ~DIOMAC                        ();

    bool                          IsZero                        ();

    XBYTE*                        Get                           ();
    XDWORD                        GetManufactured               ();
    bool                          GetXString                    (XSTRING& MACstring, XCHAR separator = __C(':'));
    XQWORD                        GetLongNumber                 ();

    bool                          Set                           (XBYTE* MAC);
    bool                          Set                           (XSTRING& MAC);
    bool                          Set                           (char* MAC);

    bool                          IsEqual                       (DIOMAC* MAC);  
    bool                          IsEqual                       (DIOMAC& MAC);  

  protected:

    XBYTE                         MAC[DIOMAC_MAXSIZE];

  private:

    void                          Clean                         ();
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

