/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DB_SQL_Query.h
*
* @class      DB_SQL_QUERY
* @brief      DataBase SQL Query Abstract class
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

#ifdef DB_SQL_ACTIVE

#ifndef _DB_SQL_QUERY_H_
#define _DB_SQL_QUERY_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "DB_SQL_Base.h"
#include "DB_SQL_Variant.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class DB_SQL_RESULT;
class DB_SQL_DATABASE;

class DB_SQL_QUERY
{
  public:
                                          DB_SQL_QUERY            (DB_SQL_DATABASE* database);
    virtual                              ~DB_SQL_QUERY            ();

    virtual   bool                        Execute                 ()  = 0;
    virtual   bool                        ClearCursor             ();

    virtual   bool                        IsWellConstructedQuery  ();
    virtual   DB_SQL_RESULT*              GetResult               ();
    virtual   DB_SQL_STRING*              GetValue                ();
    virtual   bool                        Set                     (XCHAR* query);

    virtual   bool                        Bind                    (XDWORD ID, DB_SQL_VARIANT* variant);
    virtual   bool                        Bind                    (XDWORD ID, int integer);
    virtual   bool                        Bind                    (XDWORD ID, XCHAR* string);
    virtual   bool                        Bind                    (XDWORD ID, float decimal);
    virtual   bool                        Bind                    (XDWORD ID, char* string);
    virtual   bool                        Bind                    (XDWORD ID, XDATETIME& datatime);

    virtual   bool                        UnbindAll               ();
    virtual   void                        ClearBuffers            ();

    virtual   bool                        UseCursor               (XCHAR* cursor);

  protected:

    virtual   DB_SQL_RESULT*              ConstructResult         ()  = 0;
    virtual   bool                        BindParametersToQuery   ()  = 0;


    DB_SQL_DATABASE*                      database;
    DB_SQL_STRING                         value;
    DB_SQL_RESULT*                        result;

    DB_SQL_MAP<XDWORD,DB_SQL_VARIANT*>    statementbindings;
    DB_SQL_VECTOR<XBUFFER*>               buffers;

    DB_SQL_STRING                         cursorname;
    bool                                  hascursor;

    bool                                  busyflag;

  private:

    void                                  Clean                   ();

};

/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/


#endif


#endif

