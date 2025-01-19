/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       MySQL_Variant.cpp
* 
* @class      MYSQL_VARIANT
* @brief      DataBase SQL MySQL Variant class
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


#if defined(DB_SQL_ACTIVE) && defined(DB_MYSQL_ACTIVE)


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "MySQL_Variant.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         MYSQL_VARIANT::MYSQL_VARIANT()
* @brief      Constructor of class
* @ingroup    DATABASE
*
* --------------------------------------------------------------------------------------------------------------------*/
MYSQL_VARIANT::MYSQL_VARIANT()  : DB_SQL_VARIANT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         MYSQL_VARIANT::~MYSQL_VARIANT()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATABASE
*
* --------------------------------------------------------------------------------------------------------------------*/
MYSQL_VARIANT::~MYSQL_VARIANT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DB_SQL_VARIANT& MYSQL_VARIANT::operator =(DB_SQL_DATETIME& datetime)
* @brief      operator =
* @ingroup    DATABASE
*
* @param[in]  datetime :
*
* @return     DB_SQL_VARIANT& :
*
* --------------------------------------------------------------------------------------------------------------------*/
DB_SQL_VARIANT& MYSQL_VARIANT::operator =(DB_SQL_DATETIME& datetime)
{
  type = (XVARIANT_TYPE)DB_SQL_VARIANT_TYPE_DATETIME;
  size = 0;

  mysqltime.day           = datetime.GetDay();
  mysqltime.month         = datetime.GetMonth();
  mysqltime.year          = datetime.GetYear();
  mysqltime.hour          = datetime.GetHours();
  mysqltime.minute        = datetime.GetMinutes();
  mysqltime.second        = datetime.GetSeconds();
  mysqltime.second_part   = 0;
  mysqltime.neg           = 0;
  mysqltime.time_type     = MYSQL_TIMESTAMP_DATETIME;

  return (*this);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         MYSQL_VARIANT::operator DB_SQL_DATETIME()
* @brief      operator DBSQLDATETIME
* @ingroup    DATABASE
*
* @return     MYSQL_VARIANT::operator :
*
* --------------------------------------------------------------------------------------------------------------------*/
MYSQL_VARIANT::operator DB_SQL_DATETIME()
{
  DB_SQL_DATETIME time;

  time.SetDay(this->mysqltime.day);
  time.SetMonth(this->mysqltime.month);
  time.SetYear(this->mysqltime.year);

  time.SetHours(this->mysqltime.hour);
  time.SetMinutes(this->mysqltime.minute);
  time.SetSeconds(this->mysqltime.second);

  return  time;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD MYSQL_VARIANT::GetSize()
* @brief      Get size
* @ingroup    DATABASE
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD MYSQL_VARIANT::GetSize()
{
  if (type == (XVARIANT_TYPE)DB_SQL_VARIANT_TYPE_DATETIME) return 0;

  return DB_SQL_VARIANT::GetSize();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void* MYSQL_VARIANT::GetData()
* @brief      Get data
* @ingroup    DATABASE
*
* @return     void* :
*
* --------------------------------------------------------------------------------------------------------------------*/
void* MYSQL_VARIANT::GetData()
{
  return (void*)&mysqltime;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void MYSQL_VARIANT::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATABASE
*
* --------------------------------------------------------------------------------------------------------------------*/
void MYSQL_VARIANT::Clean()
{

}


#pragma endregion


#endif

