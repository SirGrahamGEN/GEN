/**-------------------------------------------------------------------------------------------------------------------
*
* @file       SQLPostgreSQLConnection.h
*
* @class      POSTGRESQL_CONNECTION
* @brief      DataBase PostgreSQL Connection class
* @ingroup    DATABASESSQL
*
* @author     Diego Martinez Ruiz de Gaona
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

#if defined(DB_SQL_ACTIVE) && defined(DB_POSTGRESQL_ACTIVE)

#ifndef _POSTGRESQL_CONNECTION_H_
#define _POSTGRESQL_CONNECTION_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "DB_SQL_Connection.h"
#include "DB_SQL_Database.h"

#include "PostgreSQL_Query.h"
#include "PostgreSQL_Database.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class POSTGRESQL_CONNECTION : public DB_SQL_CONNECTION
{
  public:

    friend class                  POSTGRESQL_QUERY;
    friend class                  POSTGRESQL_DATABASE;

                                  POSTGRESQL_CONNECTION       (DB_SQL_DATABASE* database);
    virtual                      ~POSTGRESQL_CONNECTION       ();

    virtual bool                  Connect                     ();
    virtual bool                  Disconnect                  ();

  protected:

    PGconn*                       connection;

  private:

    void                          Clean                       ();
};


/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif

#endif
