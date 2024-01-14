/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XOrderedList.h
* 
* @class      XORDEREDLIST
* @brief       eXtended Utils Orderer List template
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

#ifndef _XORDEREDLIST_H_
#define _XORDEREDLIST_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XList.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


template <class T>
class XCOMPARATOR
{
  public:
    virtual int     Compare           (T* a,T* b)  = 0;
};


template <class T, class Compare>
class XORDEREDLIST : public XLIST<T>
{

  public:
                        XORDEREDLIST      ()
                        {
                          Clean();
                        }

    virtual            ~XORDEREDLIST      ()
                        {
                          Clean();
                        }

    virtual bool        Add               (T element)
                        {
                          XLISTDATA<T>* current = this->GetFirstData();

                          while(current)
                            {
                              int result = comparator.Compare(element, current->data);

                              switch(result)
                                {
                                  case  0: return false; //the item already exists
                                  case  1: return this->Insert(current,element);
                                }

                              current = current->next;
                            }

                          return XLIST<T>::Add(element);
                        }
                 
  protected:

    Compare             comparator;

  private:

    virtual void        Clean()
                        {

                        }  
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif
