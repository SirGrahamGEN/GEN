/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XXPROPERTY.h
* 
* @class      XXPROPERTY
* @brief      eXtended XPROPERTY (Template to Getter and Setter)
* @ingroup    UTILS
* 
* @author     Abraham J. Velez 
* @date       25/04/2016 10:56:34
* 
* @copyright  Copyright(c) 2005 - 2022 GEN Group.
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

#ifndef _XXPROPERTY_H_
#define _XXPROPERTY_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <functional>
#include <iostream>
#include <cassert>

#include "XMemory_Control.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

/*
template<typename T>
class XXPROPERTY 
{
  public:
                                              XXPROPERTY       () 
                                              {
                                              }


                                             ~XXPROPERTY       ()
                                              {
                                              }                                              

    operator const T&                         ()              const 
                                              {
                                                // Call override getter if we have it
                                                if (getter) return getter();

                                                return Get();
                                              }

    const T& operator                         =               (const T& other) 
                                              {
                                                // Call override setter if we have it
                                                if(setter) return setter(other);
                                                return Set(other);
                                              }

    bool operator                             ==              (const T& other) const 
                                              {
                                                // Static cast makes sure our getter operator is called, so we could use overrides if those are in place
                                                return static_cast<const T&>(*this) == other;
                                              }

                                              // Use this to always get without overrides, useful for use with overriding implementations
    const T&                                  Get             () const 
                                              {
                                                return t;
                                              }

                                              // Use this to always set without overrides, useful for use with overriding implementations
    const T&                                  Set             (const T& other) 
                                              {
                                                return t = other;
                                              }
  
                                              // Assign getter and setter to these properties
    std::function<const T& ()>                getter;
    std::function<const T& (const T&)>        setter;

  private:

    T                                         t;
};
*/


/*
template<typename C, typename T, T(C::* getter)(), void (C::* setter)(const T&)>
struct XPROPERTY
{
public:
  XPROPERTY(C* instance) : instance(instance)
  {
  }

  operator T () const
  {
    return (instance->*getter)();
  }

  XPROPERTY& operator=(const T& value)
  {
    (instance->*setter)(value);
    return *this;
  }

  template<typename C2, typename T2, T2(C2::* getter2)(), void (C2::* setter2)(const T2&)>
  XPROPERTY& operator=                     (const XPROPERTY<C2, T2, getter2, setter2>& other)
  {
    return *this = (other.instance->*getter2)();
  }


  XPROPERTY& operator=                     (const XPROPERTY& other)
  {
    return *this = (other.instance->*getter)();
  }

  C* instance;
};

*/


template<typename C, typename T, T(C::* getter)(), void (C::* setter)(T)>
struct XPROPERTY
{
  public: 
                            XPROPERTY(C* instance) : instance(instance)
                            {
                            }

                            operator T () const
                            {
                              return (instance->*getter)();
                            }

    XPROPERTY&              operator= (T value)
                            {
                              (instance->*setter)(value);
                              return *this;
                            }

    T&                      Get                            ()
                            {
                              T var = (instance->*getter)();
                              return  var;
                            }

    
    template<typename C2, typename T2, T2(C2::* getter2)(), void (C2::* setter2)(T2)>
    XPROPERTY&              operator=                     (const XPROPERTY<C2, T2, getter2, setter2>& other)
                            {
                              return *this = (other.instance->*getter2)();
                            }


    XPROPERTY&              operator=                     (const XPROPERTY& other)
                            {
                              return *this = (other.instance->*getter)();
                            }

    C*                      instance;
};



template<typename C, typename T, T(C::* getter)()>
struct XPROPERTYG
{
  public:
                            XPROPERTYG                     (C* instance) : instance(instance)
                            {
                            }

                            operator T () const
                            {
                              return (instance->*getter)();
                            }

    T&                      Get                         ()
                            {
                              return (instance->*getter)();
                            }


    template<typename C2, typename T2, T2(C2::* getter2)()>
    XPROPERTYG&             operator=                     (const XPROPERTYG<C2, T2, getter2>& other)
                            {
                              return *this = (other.instance->*getter2)();
                            }

    C*                      instance;
};





/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif
