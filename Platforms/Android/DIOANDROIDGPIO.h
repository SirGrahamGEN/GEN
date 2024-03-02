/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOANDROIDGPIO.h
* 
* @class      DIOANDROIDGPIO
* @brief      ANDROID Data Input/Output GPIO (General Port Input/Ouput) class
* @ingroup    PLATFORM_ANDROID
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

#ifndef _DIOANDROIDGPIO_H_
#define _DIOANDROIDGPIO_H_


#ifdef ANDROID


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES


#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class DIOANDROIDGPIO : public DIOGPIO
{
  public:
                     DIOANDROIDGPIO             ();
    virtual         ~DIOANDROIDGPIO             ();

    bool             Ini                        ();

    bool             SetMode                    (XBYTE pin, bool isinput);

    bool             Get                        (XBYTE pin);
    bool             Set                        (XBYTE pin, bool active);

    bool             End                        ();

  private:

    void             Clean                      ();
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif


#endif


