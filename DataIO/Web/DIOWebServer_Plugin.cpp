/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOWebServer_Plugin.cpp
* 
* @class      DIOWEBSERVER_PLUGIN
* @brief      Data Input/Output Web Server Plugin class
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

#include "DIOWebServer_Plugin.h"

#include "XPath.h"

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
* @fn         DIOWEBSERVER_PLUGIN::DIOWEBSERVER_PLUGIN()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_PLUGIN::DIOWEBSERVER_PLUGIN()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBSERVER_PLUGIN::~DIOWEBSERVER_PLUGIN()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBSERVER_PLUGIN::~DIOWEBSERVER_PLUGIN()
{
  PageExtension_DeleteAll();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOWEBSERVER_PLUGIN::GetName()
* @brief      Get name
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOWEBSERVER_PLUGIN::GetName()
{
  return &name;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_PLUGIN::PageExtension_Add(XCHAR* ext)
* @brief      Page extension add
* @ingroup    DATAIO
*
* @param[in]  ext :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_PLUGIN::PageExtension_Add(XCHAR* ext)
{
  XSTRING* _ext = new XSTRING();
  if(!_ext) return false;

  _ext->Set(ext);

  pageextensions.Add(_ext);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_PLUGIN::PageExtension_Add(XSTRING& ext)
* @brief      Page extension add
* @ingroup    DATAIO
*
* @param[in]  ext :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_PLUGIN::PageExtension_Add(XSTRING& ext)
{
  return PageExtension_Add(ext.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOWEBSERVER_PLUGIN::PageExtension_Get(int index)
* @brief      Page extension get
* @ingroup    DATAIO
*
* @param[in]  index :
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOWEBSERVER_PLUGIN::PageExtension_Get(int index)
{
  return pageextensions.Get(index);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_PLUGIN::PageExtension_IsContent(XCHAR* ext)
* @brief      Page extension is content
* @ingroup    DATAIO
*
* @param[in]  ext :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_PLUGIN::PageExtension_IsContent(XCHAR* ext)
{
  if(pageextensions.IsEmpty()) return false;

  for(XDWORD c=0; c<pageextensions.GetSize(); c++)
    {
      if(!pageextensions.Get(c)->Compare(ext, true))
        {
          return true;
        }
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_PLUGIN::PageExtension_IsContent(XSTRING& ext)
* @brief      Page extension is content
* @ingroup    DATAIO
*
* @param[in]  ext :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_PLUGIN::PageExtension_IsContent(XSTRING& ext)
{
  return PageExtension_IsContent(ext.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_PLUGIN::PageExtension_DeleteAll()
* @brief      Page extension delete all
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_PLUGIN::PageExtension_DeleteAll()
{
  if(pageextensions.IsEmpty()) return false;

  pageextensions.DeleteContents();
  pageextensions.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_PLUGIN::PageExtension(XPATH& pathfile, DIOWEBSERVER_REQUEST* request, DIOWEBSERVER_QUERYSTRINGS* querystrings, DIOWEBHEADER_RESULT& headerresult, XSTRING& result)
* @brief      Page extension
* @ingroup    DATAIO
*
* @param[in]  pathfile :
* @param[in]  request :
* @param[in]  querystrings :
* @param[in]  headerresult :
* @param[in]  result :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_PLUGIN::PageExtension(XPATH& pathfile, DIOWEBSERVER_REQUEST* request, DIOWEBSERVER_QUERYSTRINGS* querystrings, DIOWEBHEADER_RESULT& headerresult, XSTRING& result)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOWEBSERVER_PLUGIN::SeparedResult(XSTRING& result, XSTRING& head, XSTRING& data)
* @brief      Separed result
* @ingroup    DATAIO
*
* @param[in]  result :
* @param[in]  head :
* @param[in]  data :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOWEBSERVER_PLUGIN::SeparedResult(XSTRING& result, XSTRING& head, XSTRING& data)
{
  XSTRING lineend;

  head.Empty();

  data = result;

  if(!result.GetTypeOfLineEnd(lineend))  return false;

  lineend+=lineend;

  int index = result.Find(lineend, true);
  if(index == XSTRING_NOTFOUND) return false;

  result.Copy(0, index, head);
  result.Copy((index + lineend.GetSize()), data);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOWEBSERVER_PLUGIN::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOWEBSERVER_PLUGIN::Clean()
{
  name    = __L("Undefined");
}


#pragma endregion


