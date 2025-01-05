/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XRand.h
* 
* @class      XRAND
* @brief      eXtended Utils Random class
* @ingroup    XUTILS
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

#ifndef _XRAND_H_
#define _XRAND_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include <stdlib.h>

#include "FactoryBase.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

#define GETRANDOM(min,max)  ((rand()%(int)(((max)+1)-(min)))+(min))

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class XRAND : public FACTORYBASE
{
  public:
                          XRAND               ();
    virtual              ~XRAND               ();

    static bool           GetIsInstanced      ();
    static XRAND&         GetInstance         ();
    static bool           SetInstance         (XRAND* instance);
    static bool           DelInstance         ();


    virtual bool          Ini                 ();
    virtual int           MaxElements         (int max);
    virtual int           Max                 (int max);
    virtual int           Between             (int min, int max);

    float                 Between             (float  min,  float max);
    bool                  Percent             (int percent);

  private:

    void                  Clean               ();

    static XRAND*         instance;    
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif



