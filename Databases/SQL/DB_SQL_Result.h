/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DB_SQL_Result.h
* 
* @class      DB_SQL_RESULT
* @brief      DataBase SQL Result class
* @ingroup    DATABASE
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

#ifndef _DB_SQL_RESULT_H_
#define _DB_SQL_RESULT_H_


#ifdef DB_SQL_ACTIVE


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DB_SQL_Base.h"
#include "DB_SQL_Variant.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class DB_SQL_RESULT
{
  public:
                                          DB_SQL_RESULT       ();
   virtual                               ~DB_SQL_RESULT       ();


   DB_SQL_ROW*                            GetRow              ();
   DB_SQL_ROWHEADER*                      GetHeader           ();
   virtual XDWORD                         GetCurrentRowIndex  ();

   virtual XQWORD                         GetNumRows          ()            = 0;
   virtual XQWORD                         GetNumColumns       ()            = 0;
   virtual bool                           Seek                (int index)   = 0;
   virtual bool                           First               ()            = 0;
   virtual bool                           Last                ()            = 0;
   virtual bool                           Next                ()            = 0;
   virtual bool                           ProcessRow          ()            = 0;
   virtual bool                           Abort               ()            = 0;
   virtual bool                           HasNext             ()            = 0;

  protected:

    bool                                  initialized;
    XDWORD                                currentrow;
    DB_SQL_ROWHEADER                      header;
    DB_SQL_ROW                            row;

  private:

    void                                  Clean               ();
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif


#endif

