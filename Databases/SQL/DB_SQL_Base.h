/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DB_SQL_Base.h
*
* @class      DB_SQL_BASE
* @brief      DataBase base defines
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

#ifndef _DB_SQL_BASE_H_
#define _DB_SQL_BASE_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XString.h"
#include "XVector.h"
#include "XMap.h"
#include "XDateTime.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum DB_SQL_DATABASE_TYPE
{
  DB_SQL_DATABASE_TYPE_UNKNOWN       = 0 ,
  DB_SQL_DATABASE_TYPE_SQLITE            ,
  DB_SQL_DATABASE_TYPE_MYSQL             ,
  DB_SQL_DATABASE_TYPE_POSTGRESQL
};

#define   DB_SQL_STRING      XSTRING
#define   DB_SQL_VECTOR      XVECTOR
#define   DB_SQL_MAP         XMAP
#define   DB_SQL_DATETIME    XDATETIME

#define   DB_SQL_MYSQL_OK    0

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class DB_SQL_VARIANT;

/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif

#endif



