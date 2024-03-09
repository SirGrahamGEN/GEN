/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DB_SQL_Database.cpp
* 
* @class      DB_SQL_DATABASE
* @brief      DataBase SQL "database" class
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

#include "DB_SQL_Database.h"

#include "XFactory.h"

#include "DB_SQL_Query.h"
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
* @fn         DB_SQL_DATABASE::DB_SQL_DATABASE()
* @brief      Constructor
* @ingroup    DATABASES
*
* --------------------------------------------------------------------------------------------------------------------*/
DB_SQL_DATABASE::DB_SQL_DATABASE()
{
  Clean();

  GEN_XFACTORY_CREATE(mutex, Create_Mutex())
  if(mutex) isthreadsafe = true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DB_SQL_DATABASE::~DB_SQL_DATABASE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATABASES
*
* --------------------------------------------------------------------------------------------------------------------*/
DB_SQL_DATABASE::~DB_SQL_DATABASE()
{
  if(mutex) GEN_XFACTORY.Delete_Mutex(mutex);

  Clean();

  tables.DeleteContents();
  tables.DeleteAll();

  errorstack.DeleteContents();
  errorstack.DeleteAll();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DB_SQL_DATABASE_ENCODING DB_SQL_DATABASE::GetCurrentEncoding()
* @brief      GetCurrentEncoding
* @ingroup    DATABASES
*
* @return     DB_SQL_DATABASE_ENCODING :
*
* --------------------------------------------------------------------------------------------------------------------*/
DB_SQL_DATABASE_ENCODING DB_SQL_DATABASE::GetCurrentEncoding()
{
  return this->encodingtype;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DB_SQL_DATABASE_TYPE DB_SQL_DATABASE::GetType()
* @brief      GetType
* @ingroup    DATABASES
*
* @return     DB_SQL_DATABASE_TYPE :
*
* --------------------------------------------------------------------------------------------------------------------*/
DB_SQL_DATABASE_TYPE DB_SQL_DATABASE::GetType()
{
  return DB_SQL_DATABASE_TYPE_UNKNOWN;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XCHAR* DB_SQL_DATABASE::GetTypeName()
* @brief      GetTypeName
* @ingroup    DATABASES
*
* @return     XCHAR* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR* DB_SQL_DATABASE::GetTypeName()
{
  return __L("unknown");
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DB_SQL_DATABASE::GetDefaultPort()
* @brief      GetDefultPort
* @ingroup    DATABASES
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DB_SQL_DATABASE::GetDefaultPort()
{
  return defaultport;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPATH* DB_SQL_DATABASE::GetDefaultPath()
* @brief      GetDefaultPath
* @ingroup    DATABASES
*
* @return     XPATH* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XPATH* DB_SQL_DATABASE::GetDefaultPath()
{
  defaultpath.Empty();

  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_DATABASES, defaultpath);

  return &defaultpath;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DB_SQL_DATABASE::IsOpen()
* @brief      IsOpen
* @ingroup    DATABASES
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DB_SQL_DATABASE::IsOpen()
{
  return (status == DB_SQL_DATABASE_FLAGS_CONNECTED);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DB_SQL_DATABASE::SetConnection(DB_SQL_CONNECTION* connection)
* @brief      SetConnection
* @ingroup    DATABASES
*
* @param[in]  connection :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DB_SQL_DATABASE::SetConnection(DB_SQL_CONNECTION* connection)
{
  this->connection = connection;
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DB_SQL_DATABASE::IsTransactionStarted()
* @brief      IsTransactionStarted
* @ingroup    DATABASES
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DB_SQL_DATABASE::IsTransactionStarted()
{
  return transactionstarted;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DB_SQL_VECTOR<DB_SQL_STRING*>* DB_SQL_DATABASE::GetTableList()
* @brief      GetTableList
* @ingroup    DATABASES
*
* @return     DB_SQL_VECTOR<DB_SQL_STRING*>* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DB_SQL_VECTOR<DB_SQL_STRING*>* DB_SQL_DATABASE::GetTableList()
{
  return &tables;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DB_SQL_VECTOR<DB_SQL_ERROR*>* DB_SQL_DATABASE::GetErrorList()
* @brief      GetErrorList
* @ingroup    DATABASES
*
* @return     DB_SQL_VECTOR<DB_SQL_ERROR*>* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DB_SQL_VECTOR<DB_SQL_ERROR*>* DB_SQL_DATABASE::GetErrorList()
{
  return &errorstack;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DB_SQL_VARIANT* DB_SQL_DATABASE::CreateVariant()
* @brief      CreateVariant
* @ingroup    DATABASES
*
* @return     DB_SQL_VARIANT* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DB_SQL_VARIANT* DB_SQL_DATABASE::CreateVariant()
{
  return new DB_SQL_VARIANT();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DB_SQL_DATABASE::OnConnection()
* @brief      OnConnection
* @ingroup    DATABASES
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DB_SQL_DATABASE::OnConnection()
{
  SetDatabaseEncoding(DB_SQL_DATABASE_ENCODING_UTF8);
  GetDatabaseEncoding();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DB_SQL_DATABASE::OnDisconnection()
* @brief      OnDisconnection
* @ingroup    DATABASES
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DB_SQL_DATABASE::OnDisconnection()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DB_SQL_DATABASE::Open()
* @brief      Open
* @ingroup    DATABASES
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DB_SQL_DATABASE::Open()
{
  if(connection)
    {
      bool status = connection->Connect();

      if(status) OnConnection();

      return status;
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DB_SQL_DATABASE::Close()
* @brief      Close
* @ingroup    DATABASES
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DB_SQL_DATABASE::Close()
{
  if(connection)
    {
      bool status = connection->Disconnect();
      if(status) OnDisconnection();

      return status;
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XCHAR* DB_SQL_DATABASE::GetLastError()
* @brief      GetLastError
* @ingroup    DATABASES
*
* @return     XCHAR* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR* DB_SQL_DATABASE::GetLastError()
{
  return (this->errorstack.GetSize()>0 ? this->errorstack.GetLast()->description.Get() : __L(""));
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DB_SQL_DATABASE::Execute(DB_SQL_QUERY* constructedquery)
* @brief      Execute
* @ingroup    DATABASES
*
* @param[in]  constructedquery :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DB_SQL_DATABASE::Execute(DB_SQL_QUERY* constructedquery)
{
  if(!constructedquery->IsWellConstructedQuery())
    {
      Error(__L("Query is NOT well constructed"));
      return false;
    }

  return ExecuteQuery(constructedquery);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DB_SQL_DATABASE::Error(XCHAR* errorstring)
* @brief      Error
* @ingroup    DATABASES
*
* @param[in]  errorstring :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DB_SQL_DATABASE::Error(XCHAR* errorstring)
{
  DB_SQL_ERROR* error=new DB_SQL_ERROR(DB_SQL_ERROR_TYPE_STATEMENT_ERROR);
  if(!error) return;

  error->description.Set(errorstring);
  GetErrorList()->Add(error);

  if(IsTransactionStarted())  Rollback();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DB_SQL_DATABASE::Error(char* errorstring)
* @brief      Error
* @ingroup    DATABASES
*
* @param[in]  errorstring :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DB_SQL_DATABASE::Error(char* errorstring)
{
  XSTRING string;

  string.Set(errorstring);

  Error(string.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DB_SQL_DATABASE::ClearPreviousErrors()
* @brief      ClearPreviousErrors
* @ingroup    DATABASES
*
* --------------------------------------------------------------------------------------------------------------------*/
void DB_SQL_DATABASE::ClearPreviousErrors()
{
  this->errorstack.DeleteContents();
  this->errorstack.DeleteAll();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DB_SQL_DATABASE::Table_IsThere(XCHAR* nametable, XCHAR* constfield, bool& isexist)
* @brief      Table_IsThere
* @ingroup    DATABASES
*
* @param[in]  nametable :
* @param[in]  constfield :
* @param[in]  isexist :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DB_SQL_DATABASE::Table_IsThere(XCHAR* nametable, XCHAR* constfield, bool& isexist)
{
  isexist = false;

  if(!nametable) return false;

  bool status = false;

  DB_SQL_QUERY* query = NULL;
  XSTRING     querystring;

  query = CreateQuery();
  if(!query) return false;

  querystring.Format(__L("SELECT %s FROM %s;"), constfield, nametable);
  query->Set(querystring.Get());

  status = Execute(query);
  if(status)
    {
      isexist = true;

      /*
      DB_SQL_RESULT* result =  query->GetResult();
      if(!result) return false;

      result->First();
      result->ProcessRow();

      DB_SQL_ROW* row = result->GetRow();
      if(row)
        {
          int found = (row->Get(0));
          isexist = (found!=0)?true:false;
        }
      */

    }

  delete query;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DB_SQL_DATABASE::Table_IsThere(XSTRING& nametable, XCHAR* constfield, bool& isexist)
* @brief      Table_IsThere
* @ingroup    DATABASES
*
* @param[in]  nametable :
* @param[in]  constfield :
* @param[in]  isexist :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DB_SQL_DATABASE::Table_IsThere(XSTRING& nametable, XCHAR* constfield, bool& isexist)
{
  return Table_IsThere(nametable.Get(), constfield, isexist);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DB_SQL_DATABASE::Table_Create(XCHAR* nametable, XCHAR* fields[], int nfields)
* @brief      Table_Create
* @ingroup    DATABASES
*
* @param[in]  nametable :
* @param[in]  fields[] :
* @param[in]  nfields :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DB_SQL_DATABASE::Table_Create(XCHAR* nametable, XCHAR* fields[], int nfields)
{
  XSTRING      querystring;
  DB_SQL_QUERY*  query  = NULL;
  bool         status = false;

  query = CreateQuery();
  if(!query) return false;

  querystring.Format(__L("CREATE TABLE %s "), nametable);

  querystring.Add(__L("("));

  for(int c=0; c<nfields; c++)
    {
      querystring.Add(fields[c]);
      if(c != nfields-1) querystring.Add(__L(","));
    }

  querystring.Add(__L(");"));

  //XTRACE_PRINTCOLOR(2,__L("%s"), querystring.Get());

  query->Set(querystring.Get());

  status = Execute(query);

  delete query;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DB_SQL_DATABASE::Table_Delete(XCHAR* nametable)
* @brief      Table_Delete
* @ingroup    DATABASES
*
* @param[in]  nametable :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DB_SQL_DATABASE::Table_Delete(XCHAR* nametable)
{
  if(!nametable) return false;

  bool status = false;

  DB_SQL_QUERY* query = NULL;
  XSTRING       querystring;

  query = CreateQuery();
  if(!query) return false;

  querystring.Format(__L("DROP TABLE IF EXISTS %s;"), nametable);
  query->Set(querystring.Get());

  status = Execute(query);
  if(status)
    {
      DB_SQL_RESULT* result = query->GetResult();
      if(result)
        {
          result->ProcessRow();
        }
    }

  delete query;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DB_SQL_DATABASE::Table_GetNRecords(XCHAR* nametable, XQWORD& nrecords)
* @brief      Table_GetNRecords
* @ingroup    DATABASES
* 
* @param[in]  nametable : 
* @param[in]  nrecords : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DB_SQL_DATABASE::Table_GetNRecords(XCHAR* nametable, XQWORD& nrecords)
{
  DB_SQL_QUERY* query    = NULL;
  XSTRING       querystring;
  bool          status   = false;

  nrecords = 0;

  query = CreateQuery();
  if(!query) return false;

  querystring.Format(__L("SELECT COUNT(*) FROM %s;"), nametable);
  query->Set(querystring.Get());

  status = Execute(query);
  if(status)
    {
      DB_SQL_RESULT* result = query->GetResult();
      if(result)
        {
          result->ProcessRow();

          DB_SQL_ROW* row = result->GetRow();
          if(row) nrecords = (XQWORD)row->Get(0);
        }
    }

  delete query;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DB_SQL_DATABASE::IsThreadSafe()
* @brief      IsThreadSafe
* @ingroup    DATABASES
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DB_SQL_DATABASE::IsThreadSafe()
{
  return isthreadsafe;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DB_SQL_DATABASE::Lock()
* @brief      Lock
* @ingroup    DATABASES
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DB_SQL_DATABASE::Lock()
{
  if(isthreadsafe && mutex) return mutex->Lock();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DB_SQL_DATABASE::Unlock()
* @brief      Unlock
* @ingroup    DATABASES
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DB_SQL_DATABASE::Unlock()
{
  if(isthreadsafe && mutex) return mutex->UnLock();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DB_SQL_DATABASE::ExecuteQuery(DB_SQL_QUERY* wellconstructedquery)
* @brief      ExecuteQuery
* @ingroup    DATABASES
*
* @param[in]  wellconstructedquery :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DB_SQL_DATABASE::ExecuteQuery(DB_SQL_QUERY* wellconstructedquery)
{
  if(!connection)
    {
      DB_SQL_ERROR* error=new DB_SQL_ERROR(DB_SQL_ERROR_TYPE_CONNECTION_ERROR);
      error->description.Set(__L("DATABASE not connected"));

      GetErrorList()->Add(error);

      return false;
    }

  return wellconstructedquery->Execute();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DB_SQL_DATABASE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATABASES
*
* --------------------------------------------------------------------------------------------------------------------*/
void DB_SQL_DATABASE::Clean()
{
  mutex                   = NULL;
  isthreadsafe            = false;

  transactionstarted      = false;
  connection              = NULL;
  type                    = 0;
  defaultport             = 0;
  defaultpath.Empty();

  status                  = DB_SQL_DATABASE_FLAGS_UNKNOWN;
  encodingtype            = DB_SQL_DATABASE_ENCODING_UNKNOWN;
}


#pragma endregion


#endif

