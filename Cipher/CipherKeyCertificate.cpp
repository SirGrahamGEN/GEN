/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       CipherKeyCertificate.cpp
* 
* @class      CIPHERKEYCERTIFICATE
* @brief      Cipher Key Certificate class
* @ingroup    CIPHER
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
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "CipherKeyCertificate.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         CIPHERKEYCERTIFICATE::CIPHERKEYCERTIFICATE()
* @brief      Constructor
* @ingroup    CIPHER
* 
* --------------------------------------------------------------------------------------------------------------------*/
CIPHERKEYCERTIFICATE::CIPHERKEYCERTIFICATE() : CIPHERKEY()
{
  Clean();

  type = CIPHERKEYTYPE_CERTIFICATE;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         CIPHERKEYCERTIFICATE::~CIPHERKEYCERTIFICATE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    CIPHER
* 
* --------------------------------------------------------------------------------------------------------------------*/
CIPHERKEYCERTIFICATE::~CIPHERKEYCERTIFICATE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XWORD CIPHERKEYCERTIFICATE::GetVersion()
* @brief      GetVersion
* @ingroup    CIPHER
* 
* @return     XWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XWORD CIPHERKEYCERTIFICATE::GetVersion()
{
  return version;
}

    
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void CIPHERKEYCERTIFICATE::SetVersion(XWORD version)
* @brief      SetVersion
* @ingroup    CIPHER
* 
* @param[in]  version : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void CIPHERKEYCERTIFICATE::SetVersion(XWORD version)
{
  this->version = version;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBUFFER* CIPHERKEYCERTIFICATE::GetSerial()
* @brief      GetSerial
* @ingroup    CIPHER
* 
* @return     XBUFFER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBUFFER* CIPHERKEYCERTIFICATE::GetSerial()
{
  return &serial;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         CIPHERKEYSFILEPEM_ALGORITHM_TYPE CIPHERKEYCERTIFICATE::GetAlgorithmType()
* @brief      GetAlgorithmType
* @ingroup    CIPHER
* 
* @return     CIPHERKEYSFILEPEM_ALGORITHM_TYPE : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
CIPHERKEYSFILEPEM_ALGORITHM_TYPE CIPHERKEYCERTIFICATE::GetAlgorithmType()
{
  return algorithmtype;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHERKEYCERTIFICATE::SetAlgorithmType(XCHAR* OID)
* @brief      SetAlgorithmType
* @ingroup    CIPHER
* 
* @param[in]  OID : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHERKEYCERTIFICATE::SetAlgorithmType(XCHAR* OID)
{
  XSTRING _OID;

  _OID = OID;

  algorithmtype = CIPHERKEYCERTIFICATE_ALGORITHM_TYPE_UNKNOWN;

  if(!_OID.Compare(__L("1.2.840.113549.1.1.5"), false))
    {
      algorithmtype = CIPHERKEYCERTIFICATE_ALGORITHM_TYPE_RSA_SIGN_SHA1;
    }
 
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* CIPHERKEYCERTIFICATE::GetCountryName()
* @brief      GetCountryName
* @ingroup    CIPHER
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* CIPHERKEYCERTIFICATE::GetCountryName()
{
  return &countryname;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* CIPHERKEYCERTIFICATE::GetOrganizationName()
* @brief      GetOrganizationName
* @ingroup    CIPHER
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* CIPHERKEYCERTIFICATE::GetOrganizationName()
{
  return &organizationame;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* CIPHERKEYCERTIFICATE::GetOrganizationalUnitName()
* @brief      GetOrganizationalUnitName
* @ingroup    CIPHER
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* CIPHERKEYCERTIFICATE::GetOrganizationalUnitName()
{
  return &organizationalunitname;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* CIPHERKEYCERTIFICATE::GetCommonName()
* @brief      GetCommonName
* @ingroup    CIPHER
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* CIPHERKEYCERTIFICATE::GetCommonName()
{
  return &commonname;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDATETIME* CIPHERKEYCERTIFICATE::GetDateNotBefore()
* @brief      GetDateNotBefore
* @ingroup    CIPHER
* 
* @return     XDATETIME* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDATETIME* CIPHERKEYCERTIFICATE::GetDateNotBefore()
{
  return &datenotbefore;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDATETIME* CIPHERKEYCERTIFICATE::GetDateNotAfter()
* @brief      GetDateNotAfter
* @ingroup    CIPHER
* 
* @return     XDATETIME* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDATETIME* CIPHERKEYCERTIFICATE::GetDateNotAfter()
{
  return &datenotafter;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool CIPHERKEYCERTIFICATE::ConvertDateTime(XCHAR* datestr, XDATETIME* datetime)
* @brief      ConvertDateTime
* @ingroup    CIPHER
* 
* @param[in]  datestr : 
* @param[in]  datetime : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool CIPHERKEYCERTIFICATE::ConvertDateTime(XCHAR* datestr, XDATETIME* datetime)
{
  if(!datestr)
    {
      return false;
    }

  if(!datetime)
    {
      return false;
    }

  XSTRING year;
  XSTRING month;
  XSTRING day;

  XSTRING hour;
  XSTRING minutes;
  XSTRING seconds;

  XSTRING datestring;

  if(datestr[0] == __C('9'))
    {
      year = __L("19");    
    }
   else
    {
      year = __L("20");    
    }  

  year    += datestr[0];
  year    += datestr[1];

  month   += datestr[2];
  month   += datestr[3];

  day     += datestr[4];  
  day     += datestr[5];  

  hour    += datestr[6];  
  hour    += datestr[7];  

  minutes += datestr[8];  
  minutes += datestr[9];  

  seconds += datestr[10];  
  seconds += datestr[11];  

  datestring.Format(__L("%s/%s/%s %s:%s:%s"), year.Get(), month.Get(), day.Get(), hour.Get(), minutes.Get(), seconds.Get());

  datetime->GetDateTimeFromString(datestring, XDATETIME_FORMAT_POSTGRESQL); 

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void CIPHERKEYCERTIFICATE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    CIPHER
* 
* --------------------------------------------------------------------------------------------------------------------*/
void CIPHERKEYCERTIFICATE::Clean()
{                                         
  version       = 0;
  algorithmtype = CIPHERKEYCERTIFICATE_ALGORITHM_TYPE_UNKNOWN;

}


#pragma endregion


