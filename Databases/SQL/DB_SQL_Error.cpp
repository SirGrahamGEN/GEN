/**-------------------------------------------------------------------------------------------------------------------
*
* @file        DB_SQL_Error.cpp
*
* @class       DB_SQL_ERROR
* @brief       DataBase Error class
* @ingroup     DATABASESSQL
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"

#ifdef DB_SQL_ACTIVE

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "DB_SQL_Error.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DB_SQL_ERROR::DB_SQL_ERROR()
* @brief      Constructor
* @ingroup    DATABASESSQL
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DB_SQL_ERROR::DB_SQL_ERROR()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DB_SQL_ERROR::DB_SQL_ERROR(DB_SQL_ERROR_TYPE type)
* @brief      Constructor
* @ingroup    DATABASESSQL
*
* @param[in]  DB_SQL_ERROR_TYPE :
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DB_SQL_ERROR::DB_SQL_ERROR(DB_SQL_ERROR_TYPE type)
{
  this->type = type;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DB_SQL_ERROR::~DB_SQL_ERROR()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATABASESSQL
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DB_SQL_ERROR::~DB_SQL_ERROR()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DB_SQL_ERROR::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATABASESSQL
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DB_SQL_ERROR::Clean()
{
  type = (DB_SQL_ERROR_TYPE)0;
}


#endif


