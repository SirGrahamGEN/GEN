/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DB_SQL_Variant.cpp
*
* @class      DB_SQL_VARIANT
* @brief      DataBase SQL Variant class
* @ingroup    DATABASESSQL
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

#include "DB_SQL_Variant.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------*/
/* DB_SQL_VARIANT                                                                                                       */
/*--------------------------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DB_SQL_VARIANT::DB_SQL_VARIANT()
* @brief      Constructor
* @ingroup    DATABASESSQL
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DB_SQL_VARIANT::DB_SQL_VARIANT(): XVARIANT()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DB_SQL_VARIANT::DB_SQL_VARIANT(const DB_SQL_VARIANT& variant)
* @brief      Constructor
* @ingroup    DATABASESSQL
*
* @param[in]  const :
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DB_SQL_VARIANT::DB_SQL_VARIANT(const DB_SQL_VARIANT& variant): XVARIANT()
{
  Clean();

  *this = variant;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DB_SQL_VARIANT::~DB_SQL_VARIANT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATABASESSQL
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DB_SQL_VARIANT::~DB_SQL_VARIANT()
{
  if(data)  Destroy();

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DB_SQL_VARIANT_FLAGS* DB_SQL_VARIANT::GetFlags()
* @brief      GetFlags
* @ingroup    DATABASESSQL
*
* @return     DB_SQL_VARIANT_FLAGS* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DB_SQL_VARIANT_FLAGS* DB_SQL_VARIANT::GetFlags()
{
  return &flags;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DB_SQL_VARIANT::SetFlags(DB_SQL_VARIANT_FLAGS flags)
* @brief      SetFlags
* @ingroup    DATABASESSQL
*
* @param[in]  flags :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DB_SQL_VARIANT::SetFlags(DB_SQL_VARIANT_FLAGS flags)
{
  this->flags = flags;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DB_SQL_VARIANT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATABASESSQL
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DB_SQL_VARIANT::Clean()
{
  flags   = DB_SQL_VARIANT_FLAGS_NONE;
  size    = 0;
}



/*--------------------------------------------------------------------------------------------------------------------*/
/* DB_SQL_ROW                                                                                                           */
/*--------------------------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DB_SQL_ROW::DB_SQL_ROW()
* @brief      Constructor
* @ingroup    DATABASESSQL
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DB_SQL_ROW::DB_SQL_ROW()
{
  Clear();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DB_SQL_ROW::~DB_SQL_ROW()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATABASESSQL
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DB_SQL_ROW::~DB_SQL_ROW()
{
  Clear();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DB_SQL_VARIANT DB_SQL_ROW::Get(int index)
* @brief      Get
* @ingroup    DATABASESSQL
*
* @param[in]  index :
*
* @return     DB_SQL_VARIANT :
*
* --------------------------------------------------------------------------------------------------------------------*/
DB_SQL_VARIANT DB_SQL_ROW::Get(int index)
{
  if(row.Get(index) == NULL)
    {
      DB_SQL_VARIANT result;
      return result;
    }

  DB_SQL_VARIANT copy  = *row.FastGet(index);

  return copy;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DB_SQL_ROW::Add(DB_SQL_VARIANT* variant)
* @brief      Add
* @ingroup    DATABASESSQL
*
* @param[in]  variant :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DB_SQL_ROW::Add(DB_SQL_VARIANT* variant)
{
  return row.Add(variant);
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DB_SQL_ROW::Clear()
* @brief      Clear
* @ingroup    DATABASESSQL
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DB_SQL_ROW::Clear()
{
  row.DeleteContents();
  row.DeleteAll();
}

#endif


