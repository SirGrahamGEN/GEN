/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XVariant.h
*
* @class      XVARIANT
* @brief      Variant class (any type of data)
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

#ifndef _XVARIANT_H_
#define _XVARIANT_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XBase.h"
#include "XString.h"
#include "XDateTime.h"
#include "XTrace.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum XVARIANT_TYPE
{
  XVARIANT_TYPE_NULL                        = 0 ,
  XVARIANT_TYPE_BOOLEAN                         ,  
  XVARIANT_TYPE_SHORT                           ,
  XVARIANT_TYPE_XWORD                           ,
  XVARIANT_TYPE_INTEGER                         , 
  XVARIANT_TYPE_XDWORD                          ,
  XVARIANT_TYPE_DOUBLEINTEGER                   , 
  XVARIANT_TYPE_XQWORD                          ,
  XVARIANT_TYPE_FLOAT                           ,
  XVARIANT_TYPE_DOUBLE                          ,
  XVARIANT_TYPE_CHAR                            ,
  XVARIANT_TYPE_XCHAR                           ,
  XVARIANT_TYPE_STRING                          ,
  XVARIANT_TYPE_DATE                            ,
  XVARIANT_TYPE_TIME                            ,
  XVARIANT_TYPE_DATETIME                        ,  
  XVARIANT_TYPE_BUFFER                              
};


#define XVARIANT_CONSTRUCTOR                      Clean();  \
                                                  (*this) = value;

#define XVARIANT_ASSIGN(vartype, ctype)           if(data) Destroy(); \
                                                  type  = vartype; \
                                                  size  = sizeof(ctype); \
                                                  data = (void*)new ctype; \
                                                  if(data) *((ctype*)data) = value; \
                                                  return *this;

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XVARIANT
{
  public:
                                    XVARIANT                ();
                                    XVARIANT                (const bool value);
                                    XVARIANT                (const short value); 
                                    XVARIANT                (const XWORD value);
                                    XVARIANT                (const int value);
                                    XVARIANT                (const XDWORD value);
                                    XVARIANT                (const long long value);
                                    XVARIANT                (const XQWORD value);
                                    XVARIANT                (const float value);
                                    XVARIANT                (const double value);
                                    XVARIANT                (const XCHAR value);
                                    XVARIANT                (const XCHAR* value);
                                    XVARIANT                (const XSTRING& value);
                                    XVARIANT                (const char* value);
                                    XVARIANT                (const char value);    
                                    XVARIANT                (const XDATETIME& value);
                                    XVARIANT                (const XBUFFER& value);
                                    XVARIANT                (const XVARIANT& value);                                    
    virtual                        ~XVARIANT                ();
        
    const XVARIANT&                 operator =              (bool value);
    const XVARIANT&                 operator =              (short value);
    const XVARIANT&                 operator =              (XWORD value);
    const XVARIANT&                 operator =              (int value);
    const XVARIANT&                 operator =              (XDWORD value);
    const XVARIANT&                 operator =              (long long value);
    const XVARIANT&                 operator =              (XQWORD value);
    const XVARIANT&                 operator =              (float value);
    const XVARIANT&                 operator =              (double value);
    const XVARIANT&                 operator =              (XCHAR value);
    const XVARIANT&                 operator =              (XCHAR* value);
    const XVARIANT&                 operator =              (const XSTRING& value);
    const XVARIANT&                 operator =              (char* value);
    const XVARIANT&                 operator =              (char value);    
    const XVARIANT&                 operator =              (const XDATETIME& value);
    const XVARIANT&                 operator =              (const XBUFFER& value);
    const XVARIANT&                 operator =              (const XVARIANT& value);  
   
    operator                        bool                    ();
    operator                        short                   ();
    operator                        XWORD                   ();
    operator                        int                     ();
    operator                        XDWORD                  ();
    operator                        long long               ();
    operator                        XQWORD                  ();
    operator                        float                   ();
    operator                        double                  ();
    operator                        XCHAR                   ();
    operator                        XCHAR*                  ();
    operator                        char                    ();
    operator                        char*                   ();
    operator                        XSTRING                 ();
    operator                        XDATETIME               ();
    operator                        XBUFFER                 ();
   
    bool                            GetDataFromString       (XCHAR* string);

    XVARIANT_TYPE                   GetType                 ();
    bool                            GetType                 (XSTRING& typestr);

    void                            SetType                 (XVARIANT_TYPE type);
    virtual XDWORD                  GetSize                 ();
    virtual void*                   GetData                 ();

    virtual bool                    Set                     (XVARIANT_TYPE type = XVARIANT_TYPE_NULL, void* data = NULL, XDWORD size = 0);

    virtual bool                    ToString                (XSTRING& to);

    bool                            IsNull                  ();

    #ifdef XTRACE_ACTIVE
    void                            PrintDebug              ();    
    #endif

  protected:

    virtual bool                    Destroy                 ();

    XVARIANT_TYPE                   type;
    XDWORD                          size;
    void*                           data;

  private:

    void                            Clean                   ();
};

/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/


#endif

