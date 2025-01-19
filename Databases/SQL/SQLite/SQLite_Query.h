/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       SQLite_Query.h
* 
* @class      SQLITE_QUERY
* @brief      DataBase SQL SQLite Query class
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

#ifndef _SQLITE_QUERY_H_
#define _SQLITE_QUERY_H_


#if defined(DB_SQL_ACTIVE) && defined(DB_SQLITE_ACTIVE)


#ifndef SQLITE_CORE
#define SQLITE_CORE
#endif


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include <sqlite3.h>

#include "DB_SQL_Query.h"
#include "DB_SQL_Database.h"
#include "SQLite_Result.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class SQLITE_QUERY : public DB_SQL_QUERY
{
  public:
    friend class            SQLITE_RESULT;

                            SQLITE_QUERY              (DB_SQL_DATABASE* database) : DB_SQL_QUERY(database)
                            {
                              Clean();
                            }

    virtual                ~SQLITE_QUERY              ();

    virtual bool            Execute                   ();
    virtual bool            ClearCursor               ();

  protected:

    virtual bool            Bind                      (XDWORD ID, int integer);
    virtual bool            Bind                      (XDWORD ID, XCHAR* string);
    virtual bool            Bind                      (XDWORD ID, float decimal);
    virtual bool            Bind                      (XDWORD ID, XDATETIME& datetime);
    virtual bool            IsWellConstructedQuery    ();

    virtual DB_SQL_RESULT*  ConstructResult           ();
    virtual bool            BindParametersToQuery     ();

    int                     Exec                      (const char* zsql,XDWORD size);

    sqlite3_stmt*           ppstmt;

  private:

    void                    Clean                     ()
                            {
                              ppstmt = NULL;
                            }
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif


#endif

