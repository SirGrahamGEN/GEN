/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DB_SQL_Query.cpp
* 
* @class      DB_SQL_QUERY
* @brief      DataBase SQL Query Abstract class
* @ingroup    DATABASES
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

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


#ifdef DB_SQL_ACTIVE


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DB_SQL_Query.h"

#include "XBuffer.h"

#include "DB_SQL_Result.h"
#include "DB_SQL_Database.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DB_SQL_QUERY::DB_SQL_QUERY(DB_SQL_DATABASE* database)
* @brief      Constructor
* @ingroup    DATABASES
*
* @param[in]  DB_SQL_DATABASE* :
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DB_SQL_QUERY::DB_SQL_QUERY(DB_SQL_DATABASE* database)
{
  Clean();

  this->database = database;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DB_SQL_QUERY::~DB_SQL_QUERY()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATABASES
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DB_SQL_QUERY::~DB_SQL_QUERY()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DB_SQL_QUERY::ClearCursor()
* @brief      ClearCursor
* @ingroup    DATABASES
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DB_SQL_QUERY::ClearCursor()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DB_SQL_QUERY::IsWellConstructedQuery()
* @brief      IsWellConstructedQuery
* @ingroup    DATABASES
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DB_SQL_QUERY::IsWellConstructedQuery()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DB_SQL_RESULT* DB_SQL_QUERY::GetResult()
* @brief      GetResult
* @ingroup    DATABASES
*
* @return     DB_SQL_RESULT* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DB_SQL_RESULT* DB_SQL_QUERY::GetResult()
{
  return result;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DB_SQL_STRING* DB_SQL_QUERY::GetValue()
* @brief      GetValue
* @ingroup    DATABASES
*
* @return     DB_SQL_STRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DB_SQL_STRING* DB_SQL_QUERY::GetValue()
{
  return &value;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DB_SQL_QUERY::Set(XCHAR* query)
* @brief      Set
* @ingroup    DATABASES
*
* @param[in]  query :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DB_SQL_QUERY::Set(XCHAR* query)
{
  UnbindAll();

  value.Set(query);

  return IsWellConstructedQuery();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DB_SQL_QUERY::UnbindAll()
* @brief      UnbindAll
* @ingroup    DATABASES
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DB_SQL_QUERY::UnbindAll()
{
  return (statementbindings.DeleteElementContents() && statementbindings.DeleteAll());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DB_SQL_QUERY::Bind(XDWORD ID, DB_SQL_VARIANT* variant)
* @brief      Bind
* @ingroup    DATABASES
*
* @param[in]  ID :
* @param[in]  variant :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DB_SQL_QUERY::Bind(XDWORD ID, DB_SQL_VARIANT* variant)
{
  return statementbindings.Set(ID, variant);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DB_SQL_QUERY::Bind(XDWORD ID, int integer)
* @brief      Bind
* @ingroup    DATABASES
*
* @param[in]  ID :
* @param[in]  integer :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DB_SQL_QUERY::Bind(XDWORD ID, int integer)
{
  DB_SQL_VARIANT* variant = new DB_SQL_VARIANT();
  if(!variant) return false;

  (*variant) = integer;

  return statementbindings.Add(ID, variant);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DB_SQL_QUERY::Bind(XDWORD ID, XCHAR* string)
* @brief      Bind
* @ingroup    DATABASES
*
* @param[in]  ID :
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DB_SQL_QUERY::Bind(XDWORD ID, XCHAR* string)
{
  DB_SQL_VARIANT* variant = new DB_SQL_VARIANT();
  if(!variant) return false;

  (*variant) = string;

  return statementbindings.Add(ID, variant);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DB_SQL_QUERY::Bind(XDWORD ID, float decimal)
* @brief      Bind
* @ingroup    DATABASES
*
* @param[in]  ID :
* @param[in]  decimal :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DB_SQL_QUERY::Bind(XDWORD ID, float decimal)
{
  DB_SQL_VARIANT* variant = new DB_SQL_VARIANT();
  if(!variant) return false;

  (*variant) = decimal;

  return statementbindings.Add(ID, variant);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DB_SQL_QUERY::Bind(XDWORD ID, char* string)
* @brief      Bind
* @ingroup    DATABASES
*
* @param[in]  ID :
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DB_SQL_QUERY::Bind(XDWORD ID, char* string)
{
  DB_SQL_VARIANT* variant = new DB_SQL_VARIANT();
  if(!variant) return false;

  (*variant) = string;

  return statementbindings.Add(ID, variant);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DB_SQL_QUERY::Bind(XDWORD id, XDATETIME& datetime)
* @brief      Bind
* @ingroup    DATABASES
*
* @param[in]  id :
* @param[in]  datetime :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DB_SQL_QUERY::Bind(XDWORD id, XDATETIME& datetime)
{
  DB_SQL_VARIANT* variant = new DB_SQL_VARIANT();
  if(!variant) return false;

  (*variant) = datetime;

  return statementbindings.Add(id,variant);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DB_SQL_QUERY::ClearBuffers()
* @brief      ClearBuffers
* @ingroup    DATABASES
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DB_SQL_QUERY::ClearBuffers()
{
  for(XDWORD e=0; e<buffers.GetSize(); e++)
    {
      XBUFFER * buffer = buffers.Get(e);
      delete buffer;
    }

  buffers.DeleteAll();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DB_SQL_QUERY::UseCursor(XCHAR* cursorname)
* @brief      UseCursor
* @ingroup    DATABASES
*
* @param[in]  cursorname :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DB_SQL_QUERY::UseCursor(XCHAR* cursorname)
{
  this->cursorname.Set(cursorname);

  hascursor=true;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DB_SQL_QUERY::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATABASES
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DB_SQL_QUERY::Clean()
{
  database    = NULL;
  result      = NULL;

  statementbindings.DeleteElementContents();
  statementbindings.DeleteAll();

  value.Empty();
}


#pragma endregion


#endif

