/**-------------------------------------------------------------------------------------------------------------------
*
* @file       SQLPostgreSQLQuery.cpp
*
* @class      POSTGRESQL_QUERY
* @brief      DataBase PostgreSQL Query class
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

#if defined(DB_SQL_ACTIVE) && defined(DB_POSTGRESQL_ACTIVE)


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XBuffer.h"

#include "POSTGRESQL_Database.h"
#include "POSTGRESQL_Result.h"
#include "POSTGRESQL_Connection.h"

#include "POSTGRESQL_Query.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         POSTGRESQL_QUERY::POSTGRESQL_QUERY(DB_SQL_DATABASE* database)
* @brief      Constructor
* @ingroup    DATABASESSQL
*
* @param[in]  DB_SQL_DATABASE* :
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
POSTGRESQL_QUERY::POSTGRESQL_QUERY(DB_SQL_DATABASE* database): DB_SQL_QUERY(database)
{
  Clean();

  conn = static_cast<POSTGRESQL_CONNECTION*>(static_cast<POSTGRESQL_DATABASE*>(database)->connection)->connection;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         POSTGRESQL_QUERY::~POSTGRESQL_QUERY()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATABASESSQL
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
POSTGRESQL_QUERY::~POSTGRESQL_QUERY()
{
  if(result)
    {
      delete(result);
      result = NULL;
    }

  if(paramformats)
    {
      delete[] paramformats;
      paramformats = NULL;
    }

  if(paramvalues)
    {
      delete[] paramvalues;
      paramvalues = NULL;
    }

  if(paramlengths)
    {
      delete[] paramlengths;
      paramlengths = NULL;
    }

  ClearBuffers();

  UnbindAll();

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool POSTGRESQL_QUERY::Execute()
* @brief      Execute
* @ingroup    DATABASESSQL
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool POSTGRESQL_QUERY::Execute()
{
  if(!database) return false;
  if(!database->Lock()) return false;

  // Check statement

  XDWORD size = value.GetSize();
  if(!size)
    {
      DB_SQL_ERROR* error = new DB_SQL_ERROR(DB_SQL_ERROR_TYPE_STATEMENT_ERROR);
      if(!error) return false;

      error->description.Set(__L("void statement"));
      database->GetErrorList()->Add(error);

      if(database->IsTransactionStarted())  database->Rollback();

      return false;
    }
   else
    {
      if( value.FindCharacter(__C('*'))     !=  NOTFOUND          &&
          value.Find(__L("COUNT(*)"),true)  ==  XSTRING_NOTFOUND)
        {
          DB_SQL_STRING error;
          database->ClearPreviousErrors();
          error.Set(__L("Wildcard * is discouraged and therefore disabled in this implementation"));
          database->Error(error.Get());

          return false;
        }

      DB_SQL_STRING cursordeclare;
      DB_SQL_STRING query;
      bool        success       = true;

      if(database->IsTransactionStarted() && hascursor && cursorname.GetSize())
        {
          cursordeclare.Format(__L("DECLARE %s CURSOR FOR "), cursorname.Get());
        }

      query.Add(cursordeclare);
      query.Add(value);

      XBUFFER* querystringbuffer = new XBUFFER();
      if(!querystringbuffer) return false;

      query.ConvertToUTF8(*querystringbuffer );
      buffers.Add(querystringbuffer  );

      if(!BindParametersToQuery()) return false;

      PGresult* res     = NULL;
      int       nparams = statementbindings.GetSize();

      res = PQexecParams(conn,(char*)querystringbuffer->Get(),nparams,NULL,paramvalues,NULL,NULL,1);
      ExecStatusType exec=PQresultStatus(res);

      if((exec != PGRES_COMMAND_OK) && (exec != PGRES_TUPLES_OK))
        {
          database->ClearPreviousErrors();
          database->Error(PQerrorMessage(conn));
          success = false;
        }

      // Clear previous statement

      UnbindAll();

      if(result) delete(result);

      result = NULL;

      // Has tuples?

      char*   cmdstatus = PQcmdStatus(res);
      XSTRING statementtype;

      statementtype.Set(cmdstatus);

      // Prepare result
      if(statementtype.Find(__L("select"), true) != NOTFOUND)
        {
          if(result)
            {
              delete(result);
              result = NULL;
            }

          if(!result)    // Prepare resultset
            {
              result = ConstructResult();

              if(!result)
                {
                  DB_SQL_ERROR* error = new DB_SQL_ERROR(DB_SQL_ERROR_TYPE_MEMORY_ERROR);
                  if (!error) return false;

                  error->description.Set(__L("not enought memory for result"));
                  database->GetErrorList()->Add(error);

                  if(database->IsTransactionStarted()) database->Rollback();

                  ClearBuffers();
                  database->Unlock();
                  PQclear(res);

                  return false;
                }
            }

          static_cast<POSTGRESQL_RESULT*>(result)->resultset = res;
        }
       else
        {
          if(result)
            {
              delete(result);
              result = NULL;
            }

          PQclear(res);
        }

      if(paramvalues)    delete(paramvalues);
      if(paramlengths)   delete(paramlengths);
      if(paramformats)   delete(paramformats);

      ClearBuffers();

      database->Unlock();

      return success;
    }

  database->Unlock();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool POSTGRESQL_QUERY::ClearCursor()
* @brief      ClearCursor
* @ingroup    DATABASESSQL
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool POSTGRESQL_QUERY::ClearCursor()
{
  bool success = false;

  if(hascursor && cursorname.GetSize()>0)
    {
      DB_SQL_STRING close;
      close.Format(__L("CLOSE %s"),this->cursorname.Get());

      XSTRING_CREATEOEM(close,oem);

      PGresult* res = PQexec(conn, oem);
      if(PQresultStatus(res) != PGRES_COMMAND_OK) success=false; else success=true;
      PQclear(res);

      XSTRING_DELETEOEM(close, oem);
    }

  return success;
};



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DB_SQL_RESULT* POSTGRESQL_QUERY::ConstructResult()
* @brief      ConstructResult
* @ingroup    DATABASESSQL
*
* @return     DB_SQL_RESULT* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DB_SQL_RESULT* POSTGRESQL_QUERY::ConstructResult()
{
  POSTGRESQL_RESULT* result = new POSTGRESQL_RESULT();
  result->query = this;

  return result;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool POSTGRESQL_QUERY::BindParametersToQuery()
* @brief      BindParametersToQuery
* @ingroup    DATABASESSQL
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool POSTGRESQL_QUERY::BindParametersToQuery()
{
  XDWORD nparams = value.CountCharacter(__C('$'));

  paramvalues  = NULL;
  paramlengths = NULL;
  paramformats = NULL;

  if(nparams > 0)
    {
      paramvalues=(char**)new char*[nparams];
      if(!paramvalues)
        {
          DB_SQL_ERROR* error = new DB_SQL_ERROR(DB_SQL_ERROR_TYPE_MEMORY_ERROR);
          if(!error) return false;

          error->description.Set(__L("not enought memory for statements"));
          database->GetErrorList()->Add(error);

          if(database->IsTransactionStarted())  database->Rollback();

          return false;
        }

      //-----------

      paramlengths = new int[nparams];
      if(!paramlengths)
        {
          DB_SQL_ERROR* error=new DB_SQL_ERROR(DB_SQL_ERROR_TYPE_MEMORY_ERROR);
          if(!error) return false;

          error->description.Set(__L("not enought memory for statements"));
          database->GetErrorList()->Add(error);

          if(database->IsTransactionStarted())  database->Rollback();

          delete(paramvalues);

          return false;
        }

      //-----------

      paramformats = new int[nparams];
      if(!paramformats)
        {
          DB_SQL_ERROR* error = new DB_SQL_ERROR(DB_SQL_ERROR_TYPE_MEMORY_ERROR);
          if(!error) return false;

          error->description.Set(__L("not enought memory for statements"));
          database->GetErrorList()->Add(error);

          if(database->IsTransactionStarted()) database->Rollback();

          delete(paramvalues);
          delete(paramlengths);

          return false;
        }

      //------------

      for(XDWORD e=0;(e<nparams) && (e<this->statementbindings.GetSize());e++)
        {
          XSTRING bindstr;
          if(!statementbindings.Get(e)->ToString(bindstr))
            {
              DB_SQL_ERROR* error = new DB_SQL_ERROR(DB_SQL_ERROR_TYPE_UNKNOWN);
              if(!error) return false;

              error->description.Set(__L("unknown type for binding"));
              database->GetErrorList()->Add(error);

              if (database->IsTransactionStarted())
                database->Rollback();
              return false;
            }

          XBUFFER* buf = new XBUFFER();
          if(buf)
            {
              bindstr.ConvertToUTF8(*buf);

              paramvalues [e] = (char*)buf->Get();

              buffers.Add(buf);
            }
        }
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool POSTGRESQL_QUERY::BindParametersToResult()
* @brief      BindParametersToResult
* @ingroup    DATABASESSQL
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool POSTGRESQL_QUERY::BindParametersToResult()
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void POSTGRESQL_QUERY::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATABASESSQL
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void POSTGRESQL_QUERY::Clean()
{

}


#endif
