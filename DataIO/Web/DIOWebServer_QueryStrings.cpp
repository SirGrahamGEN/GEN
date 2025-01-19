/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOWebServer_QueryStrings.cpp
* 
* @class      DIOWEBSERVER_QUERYSTRINGS
* @brief      Data Input/Output Web Server Query Strings Event class
* @ingroup    DATAIO
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


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIOWebServer_QueryStrings.h"

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
* @fn         DIOWEBSERVER_QUERYSTRINGS::DIOWEBSERVER_QUERYSTRINGS()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_QUERYSTRINGS::DIOWEBSERVER_QUERYSTRINGS()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_QUERYSTRINGS::~DIOWEBSERVER_QUERYSTRINGS()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_QUERYSTRINGS::~DIOWEBSERVER_QUERYSTRINGS()
{
  DelAllParam();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOWEBSERVER_QUERYSTRINGS::GetNParams()
* @brief      Get N params
* @ingroup    DATAIO
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOWEBSERVER_QUERYSTRINGS::GetNParams()
{
  return params.GetSize();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XMAP<XSTRING*, XSTRING*>* DIOWEBSERVER_QUERYSTRINGS::GetParams()
* @brief      Get params
* @ingroup    DATAIO
*
* @return     XMAP<XSTRING*, :
*
* --------------------------------------------------------------------------------------------------------------------*/
XMAP<XSTRING*, XSTRING*>* DIOWEBSERVER_QUERYSTRINGS::GetParams()
{
  return &params;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_QUERYSTRINGS::AddParam(XSTRING& ID, XSTRING& value)
* @brief      Add param
* @ingroup    DATAIO
*
* @param[in]  ID :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_QUERYSTRINGS::AddParam(XSTRING& ID, XSTRING& value)
{
  return AddParam(ID.Get(), value.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_QUERYSTRINGS::AddParam(XCHAR* ID , XSTRING& value)
* @brief      Add param
* @ingroup    DATAIO
*
* @param[in]  ID :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_QUERYSTRINGS::AddParam(XCHAR* ID  , XSTRING& value)
{
  return AddParam(ID, value.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_QUERYSTRINGS::AddParam(XSTRING& ID, XCHAR* value)
* @brief      Add param
* @ingroup    DATAIO
*
* @param[in]  ID :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_QUERYSTRINGS::AddParam(XSTRING& ID, XCHAR* value)
{
  return AddParam(ID.Get(), value);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_QUERYSTRINGS::AddParam(XCHAR* ID, XCHAR* value)
* @brief      Add param
* @ingroup    DATAIO
*
* @param[in]  ID :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_QUERYSTRINGS::AddParam(XCHAR* ID, XCHAR* value)
{
  XSTRING* _ID    = new XSTRING();
  XSTRING* _value = new XSTRING();

  if((!_ID) || (!_value))
    {
      delete _ID;
      delete _value;

      return false;
    }

  _ID->Set(ID);
  _value->Set(value);

  params.Add(_ID, _value);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_QUERYSTRINGS::AddParam(XCHAR* ID, int value)
* @brief      Add param
* @ingroup    DATAIO
*
* @param[in]  ID :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_QUERYSTRINGS::AddParam(XCHAR* ID, int value)
{
  XSTRING* _ID    = new XSTRING();
  XSTRING* _value = new XSTRING();

  if((!_ID) || (!_value))
    {
      delete _ID;
      delete _value;

      return false;
    }

  _ID->Set(ID);
  _value->ConvertFromInt(value);

  params.Add(_ID, _value);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOWEBSERVER_QUERYSTRINGS::GetParam(XSTRING& ID)
* @brief      Get param
* @ingroup    DATAIO
*
* @param[in]  ID :
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOWEBSERVER_QUERYSTRINGS::GetParam(XSTRING& ID)
{
  return GetParam(ID.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOWEBSERVER_QUERYSTRINGS::GetParam(XCHAR* ID)
* @brief      Get param
* @ingroup    DATAIO
*
* @param[in]  ID :
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOWEBSERVER_QUERYSTRINGS::GetParam(XCHAR* ID)
{
  if(params.IsEmpty()) return NULL;

  for(int c=0;c<(int)params.GetSize();c++)
    {
      XSTRING* _ID = params.GetKey(c);
      if(_ID)
        {
          if(!_ID->Compare(ID, true))
            {
              XSTRING* _value = params.GetElement(c);
              return _value;
            }
        }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOWEBSERVER_QUERYSTRINGS::GetParamID(int index)
* @brief      Get param ID
* @ingroup    DATAIO
*
* @param[in]  index :
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOWEBSERVER_QUERYSTRINGS::GetParamID(int index)
{
  if(params.IsEmpty()) return NULL;

  return (XSTRING*)params.GetKey(index);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOWEBSERVER_QUERYSTRINGS::GetParamValue(int index)
* @brief      Get param value
* @ingroup    DATAIO
*
* @param[in]  index :
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOWEBSERVER_QUERYSTRINGS::GetParamValue(int index)
{
  if(params.IsEmpty()) return NULL;

  return params.GetElement(index);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_QUERYSTRINGS::DelParam(XSTRING& ID)
* @brief      Del param
* @ingroup    DATAIO
*
* @param[in]  ID :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_QUERYSTRINGS::DelParam(XSTRING& ID)
{
  return DelParam(ID.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_QUERYSTRINGS::DelParam(XCHAR* ID)
* @brief      Del param
* @ingroup    DATAIO
*
* @param[in]  ID :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_QUERYSTRINGS::DelParam(XCHAR* ID)
{
  XSTRING* _ID = DIOWEBSERVER_QUERYSTRINGS::GetParam(ID);
  if(!_ID) return false;

  return params.Delete(_ID);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_QUERYSTRINGS::DelAllParam()
* @brief      Del all param
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_QUERYSTRINGS::DelAllParam()
{
  if(params.IsEmpty())  return false;

  params.DeleteKeyContents();
  params.DeleteElementContents();

  params.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_QUERYSTRINGS::GetAllParam(XSTRING& allparam)
* @brief      Get all param
* @ingroup    DATAIO
*
* @param[in]  allparam :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_QUERYSTRINGS::GetAllParam(XSTRING& allparam)
{
  allparam.Empty();

  if(!params.GetSize()) return false;

  for(XDWORD c=0; c<params.GetSize(); c++)
    {
      XSTRING* nameparam = params.GetKey(c);
      XSTRING* param     = params.GetElement(c);

      if(nameparam && param) allparam.AddFormat(__L("%s=%s"),  nameparam->Get(), param->Get());
      if(c < params.GetSize()-1)  allparam += __L("&");
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOWEBSERVER_QUERYSTRINGS::GetParamsFromURL(DIOURL& url)
* @brief      Get params from URL
* @ingroup    DATAIO
*
* @param[in]  url :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOWEBSERVER_QUERYSTRINGS::GetParamsFromURL(DIOURL& url)
{
  return GetParamsFromURL(url.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOWEBSERVER_QUERYSTRINGS::GetParamsFromURL(XSTRING& url)
* @brief      Get params from URL
* @ingroup    DATAIO
*
* @param[in]  url :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOWEBSERVER_QUERYSTRINGS::GetParamsFromURL(XSTRING& url)
{
  return GetParamsFromURL(url.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DIOWEBSERVER_QUERYSTRINGS::GetParamsFromURL(XCHAR* url)
* @brief      Get params from URL
* @ingroup    DATAIO
*
* @param[in]  url :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int DIOWEBSERVER_QUERYSTRINGS::GetParamsFromURL(XCHAR* url)
{
  DIOURL  _url;
  int     start;
  int     separator;
  int     end;
  XSTRING param;

  DelAllParam();

  _url = url;

  start = _url.Find(__L("?"),true);
  if(start != XSTRING_NOTFOUND)
    {
      XSTRING ID;
      XSTRING value;

      start++;

      do{
          value.Empty();
          end = _url.Find(__L("&"),true,start);
          if(end == XSTRING_NOTFOUND)
                _url.Copy(start, param);
           else _url.Copy(start, end, param);

          separator = param.Find(__L("="),true);
          if(separator == XSTRING_NOTFOUND)
            {
              ID = param;
            }
           else
            {
              param.Copy(0 , separator,ID);
              param.Copy(separator+1, value);
            }

          AddParam(ID, value);

          start = end+1;

        } while(end != XSTRING_NOTFOUND);
    }


  return GetNParams();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_QUERYSTRINGS::DeleteParamsFromURL(XSTRING& url)
* @brief      Delete params from URL
* @ingroup    DATAIO
*
* @param[in]  url :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_QUERYSTRINGS::DeleteParamsFromURL(XSTRING& url)
{
  bool status = false;

  for(XDWORD c=url.GetSize(); c>0; c--)
    {
      if(url.Get()[c] == __C('?'))
        {
          url.DeleteCharacters(c, url.GetSize());

          status = true;
          break;
        }
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_QUERYSTRINGS::CreateURLFromParams(XSTRING& urlpart)
* @brief      Create URL from params
* @ingroup    DATAIO
*
* @param[in]  urlpart :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_QUERYSTRINGS::CreateURLFromParams(XSTRING& urlpart)
{
  urlpart.Empty();

  if(params.IsEmpty()) return false;

  for(int c=0;c<(int)params.GetSize();c++)
    {
      XSTRING* _ID = (XSTRING*)params.GetKey(c);
      if(_ID)
        {
          XSTRING* _value = params.GetElement(c);
          if(_value)
            {
              if(urlpart.IsEmpty())
                    urlpart += __L("?");
               else urlpart += __L("&");

              urlpart += _ID->Get();
              urlpart += __L("=");
              urlpart += _value->Get();
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_QUERYSTRINGS::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_QUERYSTRINGS::Clean()
{

}


#pragma endregion

