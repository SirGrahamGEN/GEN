/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UI_Animation.h
* 
* @class      UI_ANIMATION
* @brief      User Interface Animation class
* @ingroup    USERINTERFACE
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
* *---------------------------------------------------------------------------------------------------------------------*/

#ifndef _UI_ANIMATION_H_
#define _UI_ANIMATION_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XString.h"

#include "GRPProperties.h"
#include "GRPBitmap.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define UI_ANIMATION_FRAME_INI          __L("#[")
#define UI_ANIMATION_FRAME_END          __L("]")


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/


class UI_ANIMATION
{
  public:
                               UI_ANIMATION         ();
    virtual                   ~UI_ANIMATION         ();

    bool                       LoadFromFile         (XSTRING& resourcename, GRPPROPERTYMODE mode);

    XSTRING*                   GetName              ();
    XSTRING*                   GetResource          ();
    XVECTOR<GRPBITMAP*>*       GetBitmaps           ();
    GRPBITMAP*                 GetBitmap            (int index = 0);

    bool                       DeleteAll            (); 

  private:
    
    void                       Clean                ();

    XSTRING                    name;
    XSTRING                    resource;
    XVECTOR<GRPBITMAP*>        bitmaps;
  
};


/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif


