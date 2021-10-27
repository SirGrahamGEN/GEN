/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XStack.h
*
* @class      XSTACK
* @brief      eXtended stack template class
* @ingroup    UTILS
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

#ifndef _XSTACK_H_
#define _XSTACK_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XVector.h"

#include "XMemory_Control.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

template<class T>
class XSTACK
{
  public:
                                  XSTACK        ()              {                                         }
    virtual                      ~XSTACK        ()              {                                         }

    bool                          IsEmpty       ()              { return stack.IsEmpty();                 }

    XDWORD                        GetSize       ()              { return stack.GetSize();                 }
    void                          Clear         ()
                                  {
                                    stack.DeleteContents();
                                    stack.DeleteAll();
                                  }

    void                          Push          (T element)     { stack.Add(element);                     }
    T                             Pop           ()
                                  {
                                    T element = stack.GetLast();
                                    stack.Delete(element);
                                    return element;
                                  }

    T                             Top           ()              { return stack.GetLast();                 }

    XVECTOR<T>*                   GetVector     ()              { return &stack;                          }

  private:

    XVECTOR<T>                    stack;
};



/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif

