/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOScraperWeb.cpp
* 
* @class      DIOSCRAPERWEB
* @brief      Data Input/Output Scraper Web class
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
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIOScraperWeb.h"

#include "XFactory.h"
#include "XTimer.h"
#include "XBuffer.h"
#include "XPath.h"
#include "XFile.h"
#include "XFileXML.h"
#include "XFileJSON.h"
#include "XTrace.h"

#include "DIOFactory.h"
#include "DIOURL.h"
#include "DIOStream.h"
#include "DIOStreamTCPIPConfig.h"
#include "DIOStreamTCPIP.h"
#include "DIOWebClient.h"
#include "DIOCheckInternetConnection.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSCRAPERWEB::DIOSCRAPERWEB()
* @brief      Constructor
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSCRAPERWEB::DIOSCRAPERWEB()
{
  Clean();

  xml = new XFILEXML();
  if(!xml)  return;

  GEN_XFACTORY_CREATE(xmutexdo, Create_Mutex())
  if(!xmutexdo) return;

  webclient = new DIOWEBCLIENT;
  if(!webclient) return;

  cache = new DIOSCRAPERWEBCACHE();
  if(!cache) return;

  URLdownload = new DIOURL();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSCRAPERWEB::~DIOSCRAPERWEB()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSCRAPERWEB::~DIOSCRAPERWEB()
{
  DeleteAllValues();

  if(URLdownload)
    {
      delete URLdownload;
    }

  if(cache)
    {
      cache->DeleteAll();
      delete cache;
    }

  if(xml)
    {
      if(xml->IsOpen()) xml->Close();
      delete xml;
    }

  if(webclient) delete webclient;

  if(xmutexdo) GEN_XFACTORY.Delete_Mutex(xmutexdo);

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSCRAPERWEB::Load(XCHAR* namefile)
* @brief      Load
* @ingroup    DATAIO
*
* @param[in]  namefile :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSCRAPERWEB::Load(XCHAR* namefile)
{
  static bool webupdate = false;

  if(!xml)  return false;

  XPATH xpath;

  xpath.Empty();

  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_SCRAPERWEB, xpath);
  if(!xpath.IsEmpty()) xpath.Slash_Add();
  xpath += DIOSCRAPERWEB_NAMEFILE;

  if((!webupdate) && (URLdownload))
    {
      webupdate = Download((*URLdownload), xpath);
    }

  if(!xml->Open(xpath, true))
    {
      GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_SCRAPERWEB, xpath);
      if(!xpath.IsEmpty()) xpath.Slash_Add();
      xpath += namefile;

      if(!xml->Open(xpath, true)) return false;
    }

  xml->ReadAndDecodeAllLines();

  xml->Close();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSCRAPERWEB::Load(XPATH& namefile)
* @brief      Load
* @ingroup    DATAIO
*
* @param[in]  namefile :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSCRAPERWEB::Load(XPATH& namefile)
{
  return Load(namefile.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOURL* DIOSCRAPERWEB::GetURLDownload()
* @brief      GetURLDownload
* @ingroup    DATAIO
*
* @return     DIOURL* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOURL* DIOSCRAPERWEB::GetURLDownload()
{
  return URLdownload;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSCRAPERWEB::Download(DIOURL& URL, XPATH& xpath)
* @brief      Download
* @ingroup    DATAIO
*
* @param[in]  URL :
* @param[in]  xpath :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSCRAPERWEB::Download(DIOURL& URL, XPATH& xpath)
{
  if(URL.IsEmpty())   return false;

  DIOURL downloadURL;
  bool   status;

  DIOWEBCLIENT* webclient = new DIOWEBCLIENT();
  if(!webclient)  return false;

  downloadURL.Set(URL.Get());
  downloadURL.Slash_Add();
  downloadURL.Add(DIOSCRAPERWEB_NAMEFILE);

  status = webclient->Get(downloadURL, xpath);

  delete webclient;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSCRAPERWEB::Do(XCHAR* namewebservice, int timeoutforurl, XSTRING* localIP)
* @brief      Do
* @ingroup    DATAIO
*
* @param[in]  namewebservice :
* @param[in]  timeoutforurl :
* @param[in]  localIP :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSCRAPERWEB::Do(XCHAR* namewebservice, int timeoutforurl, XSTRING* localIP)
{
  if(!xml) return false;

  XFILEXMLELEMENT* root = xml->GetRoot();
  if(!root) return false;

  XSTRING namews;

  XFILEXMLELEMENT* nodewebservice = NULL;

  for(int c=0; c<root->GetNElements(); c++)
    {
      nodewebservice = root->GetElement(c);
      if(nodewebservice)
        {
          namews = nodewebservice->GetValueAttribute(__L("name"));
          if(!namews.Compare(namewebservice)) break;

          nodewebservice = NULL;
        }
    }

  if(nodewebservice)
    {
      DeleteAllValues();

      for(int c=0; c<nodewebservice->GetNElements(); c++)
        {
          bool priorityvaluesobtain = true;

          XFILEXMLELEMENT* nodeweb = nodewebservice->GetElement(c);
          if(nodeweb)
            {
              XBUFFER  webpage;
              DIOURL   url;

              if(!ChangeURL(nodeweb->GetValueAttribute(__L("url")), url))
                {
                  return false;
                }

              if(webclient->Get(url, webpage, DIOSCRAPERWEB_DEFAULTUSERAGENT, timeoutforurl, localIP))
                {
                  if(webpage.GetSize())
                    {
                      XSTRING format;

                      format = nodeweb->GetValueAttribute(__L("format"));

                      if(!format.Compare(__L("JSON"),true))
                        {
                          XFILEJSON* json = new XFILEJSON();
                          if(json)
                            {
                              json->DeleteAllLines();
                              json->AddBufferLines(XFILETXTFORMATCHAR_ASCII, webpage);
                              json->DecodeAllLines();

                              for(int d=0; d<nodeweb->GetNElements(); d++)
                                {
                                  XFILEXMLELEMENT* nodevalue = nodeweb->GetElement(d);
                                  if(nodevalue)
                                    {
                                      XSTRING  name;
                                      XSTRING  prioritystring;
                                      int      priority;
                                      XSTRING  namevalue;

                                      name           = nodevalue->GetValueAttribute(__L("name"));

                                      prioritystring = nodevalue->GetValueAttribute(__L("priority"));
                                      priority       = prioritystring.ConvertToInt();

                                      namevalue      = nodevalue->GetValueAttribute(__L("namevalue"));

                                      XFILEJSONVALUE* jsonvalue = json->GetValue(namevalue,NULL);
                                      if(jsonvalue)
                                        {
                                          switch(jsonvalue->GetType())
                                            {                                              
                                              case XFILEJSONVALUETYPE_INTEGER           : { int     pvalue = (int)jsonvalue->GetValueInteger();
                                                                                            XSTRING string;

                                                                                            string.Format(__L("%d"),pvalue);

                                                                                            AddValue(name, string);
                                                                                          }
                                                                                          break;

                                              case XFILEJSONVALUETYPE_DOUBLEINTEGER     : { long pvalue = (long)jsonvalue->GetValueDoubleInteger();
                                                                                            XSTRING string;

                                                                                            string.Format(__L("%ld"),pvalue);

                                                                                            AddValue(name, string);
                                                                                          }
                                                                                          break;

                                              case XFILEJSONVALUETYPE_FLOAT             : { float   pvalue = (float)jsonvalue->GetValueFloating();
                                                                                            XSTRING string;

                                                                                            string.Format(__L("%f"),pvalue);

                                                                                            AddValue(name, string);
                                                                                          }
                                                                                          break;

                                              case XFILEJSONVALUETYPE_DOUBLEFLOAT       : { double  pvalue = (float)jsonvalue->GetValueDoubleFloat();
                                                                                            XSTRING string;

                                                                                            string.Format(__L("%f"),pvalue);

                                                                                            AddValue(name, string);
                                                                                          }
                                                                                          break;

                                              case XFILEJSONVALUETYPE_STRING            : { XSTRING pvalue = (XSTRING)jsonvalue->GetValueString();
                                                                                            AddValue(name, pvalue);
                                                                                          }
                                                                                          break;

                                              case XFILEJSONVALUETYPE_OBJECT            : break;
                                              case XFILEJSONVALUETYPE_ARRAY             : break;
                                              case XFILEJSONVALUETYPE_BOOLEAN           : break;
                                              case XFILEJSONVALUETYPE_NULL              : break;

                                            }
                                        }
                                       else
                                        {
                                          if(priority) priorityvaluesobtain = false;
                                        }
                                    }
                                }

                              delete json;
                            }
                        }

                      if(!format.Compare(__L("HTML"),true))
                        {
                          for(int d=0; d<nodeweb->GetNElements(); d++)
                            {
                              XFILEXMLELEMENT* nodevalue = nodeweb->GetElement(d);
                              if(nodevalue)
                                {
                                  XSTRING  searchini;
                                  XSTRING  searchend;
                                  XSTRING  namevalue;
                                  XSTRING  prioritystring;
                                  int      priority;

                                  XSTRING  value;

                                  namevalue = nodevalue->GetValueAttribute(__L("name"));
                                  namevalue.ConvertHexFormatChars();

                                  prioritystring = nodevalue->GetValueAttribute(__L("priority"));
                                  priority = prioritystring.ConvertToInt();

                                  searchini = nodevalue->GetValueAttribute(__L("start"));
                                  searchini.ConvertHexFormatChars();

                                  searchend = nodevalue->GetValueAttribute(__L("end"));;
                                  searchend.ConvertHexFormatChars();

                                  if(ExtractString(searchini, searchend, &webpage, false, value))
                                    {
                                      if(!GetValue(namevalue))
                                        {
                                          AddValue(namevalue, value);
                                        }
                                    }
                                   else
                                    {
                                      if(priority) priorityvaluesobtain = false;
                                    }
                                }
                            }
                        }

                      if(values.GetSize() && priorityvaluesobtain)
                        {
                          return true;
                        }
                    }
                }
            }
        }
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSCRAPERWEB::Do(XSTRING& namewebservice, int timeoutforurl, XSTRING* localIP)
* @brief      Do
* @ingroup    DATAIO
*
* @param[in]  namewebservice :
* @param[in]  timeoutforurl :
* @param[in]  localIP :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSCRAPERWEB::Do(XSTRING& namewebservice, int timeoutforurl, XSTRING* localIP)
{
  return Do(namewebservice.Get(), timeoutforurl, localIP);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSCRAPERWEB::ChangeURL(XCHAR* maskurl, DIOURL& url)
* @brief      ChangeURL
* @ingroup    DATAIO
*
* @param[in]  maskurl :
* @param[in]  url :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSCRAPERWEB::ChangeURL(XCHAR* maskurl, DIOURL& url)
{
  url = maskurl;

  if(url.GetSize()) return true;

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSCRAPERWEB::AddValue(XCHAR* name, XCHAR* value)
* @brief      AddValue
* @ingroup    DATAIO
*
* @param[in]  name :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSCRAPERWEB::AddValue(XCHAR* name, XCHAR* value)
{
  XSTRING* _name  = new XSTRING();
  XSTRING* _value = new XSTRING();

  if((!_name )||(!_value))
    {
      delete _name;
      delete _value;

      return false;
    }

  (*_name)  = name;
  (*_value) = value;

  values.Add(_name,_value);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSCRAPERWEB::AddValue(XCHAR* name, XSTRING& value)
* @brief      AddValue
* @ingroup    DATAIO
*
* @param[in]  name :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSCRAPERWEB::AddValue(XCHAR* name, XSTRING& value)
{
  return AddValue(name, value.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSCRAPERWEB::AddValue(XSTRING& name,XCHAR* value)
* @brief      AddValue
* @ingroup    DATAIO
*
* @param[in]  name :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSCRAPERWEB::AddValue(XSTRING& name,XCHAR*  value)
{
  return AddValue(name.Get(), value);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSCRAPERWEB::AddValue(XSTRING& name, XSTRING& value)
* @brief      AddValue
* @ingroup    DATAIO
*
* @param[in]  name :
* @param[in]  value :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSCRAPERWEB::AddValue(XSTRING& name, XSTRING& value)
{
  return AddValue(name.Get(), value.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XCHAR* DIOSCRAPERWEB::GetValue(XCHAR* namevalue)
* @brief      GetValue
* @ingroup    DATAIO
* 
* @param[in]  namevalue : 
* 
* @return     XCHAR* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR* DIOSCRAPERWEB::GetValue(XCHAR* namevalue)
{
  for(XDWORD c=0;c<values.GetSize();c++)
    {
      XSTRING* name = (XSTRING*)values.GetKey(c);
      if(name)
        {
          if(!name->Compare(namevalue))
            {
              XSTRING* value  = values.GetElement(c);

              if(value)
                {
                  value->ConvertHexFormatChars();
                  return value->Get();
                }

              return NULL;
            }
        }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XCHAR* DIOSCRAPERWEB::GetValue(XSTRING& namevalue)
* @brief      GetValue
* @ingroup    DATAIO
*
* @param[in]  namevalue :
*
* @return     XCHAR* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR* DIOSCRAPERWEB::GetValue(XSTRING& namevalue)
{
  return DIOSCRAPERWEB::GetValue(namevalue.Get());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSCRAPERWEB::DeleteAllValues()
* @brief      DeleteAllValues
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSCRAPERWEB::DeleteAllValues()
{
  if(values.IsEmpty())  return false;

  values.DeleteKeyContents();
  values.DeleteElementContents();
  values.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOWEBCLIENT* DIOSCRAPERWEB::GetWebClient()
* @brief      GetWebClient
* @ingroup    DATAIO
*
* @return     DIOWEBCLIENT* :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOWEBCLIENT* DIOSCRAPERWEB::GetWebClient()
{
  return webclient;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSCRAPERWEB::ExtractString(XCHAR* searchini,XCHAR* searchend,XBUFFER* xbuffer,bool usebufferpos,XSTRING& result)
* @brief      ExtractString
* @ingroup    DATAIO
*
* @param[in]  searchini :
* @param[in]  searchend :
* @param[in]  xbuffer :
* @param[in]  usebufferpos :
* @param[in]  result :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSCRAPERWEB::ExtractString(XCHAR* searchini,XCHAR* searchend,XBUFFER* xbuffer,bool usebufferpos,XSTRING& result)
{
  if((!searchini) || (!searchend)) return false;

  XSTRING _searchini;
  XSTRING _searchend;

  _searchini = searchini;
  _searchend = searchend;

  return ExtractString(_searchini,_searchend,xbuffer,usebufferpos,result);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSCRAPERWEB::ExtractString(XCHAR* searchini,XSTRING& searchend,XBUFFER* xbuffer,bool usebufferpos,XSTRING& result)
* @brief      ExtractString
* @ingroup    DATAIO
*
* @param[in]  searchini :
* @param[in]  searchend :
* @param[in]  xbuffer :
* @param[in]  usebufferpos :
* @param[in]  result :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSCRAPERWEB::ExtractString(XCHAR* searchini, XSTRING& searchend, XBUFFER* xbuffer, bool usebufferpos, XSTRING& result)
{
  if(!searchini) return false;

  XSTRING _searchini;

  _searchini = searchini;

  return ExtractString(_searchini,searchend,xbuffer,usebufferpos,result);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSCRAPERWEB::ExtractString(XSTRING& searchini,XCHAR* searchend,XBUFFER* xbuffer,bool usebufferpos,XSTRING& result)
* @brief      ExtractString
* @ingroup    DATAIO
*
* @param[in]  searchini :
* @param[in]  searchend :
* @param[in]  xbuffer :
* @param[in]  usebufferpos :
* @param[in]  result :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSCRAPERWEB::ExtractString(XSTRING& searchini,XCHAR* searchend,XBUFFER* xbuffer,bool usebufferpos,XSTRING& result)
{
  if(!searchend) return false;

  XSTRING _searchend;

  _searchend = searchend;

  return ExtractString(searchini,_searchend,xbuffer,usebufferpos,result);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSCRAPERWEB::ExtractString(XSTRING& searchini,XSTRING& searchend,XBUFFER* xbuffer,bool usebufferpos,XSTRING& result)
* @brief      ExtractString
* @ingroup    DATAIO
*
* @param[in]  searchini :
* @param[in]  searchend :
* @param[in]  xbuffer :
* @param[in]  usebufferpos :
* @param[in]  result :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSCRAPERWEB::ExtractString(XSTRING& searchini, XSTRING& searchend, XBUFFER* xbuffer, bool usebufferpos, XSTRING& result)
{
  result.Empty();

  if(!xbuffer)            return false;

  if(searchini.IsEmpty()) return false;
  if(searchend.IsEmpty()) return false;

  XSTRING html;
  int        indexini;
  int        indexend;

  //html = (char*)xbuffer->Get();
  html = *xbuffer; // #Imanol, changed to avoid a buffer overrun

  indexini = html.Find(searchini,false,usebufferpos?xbuffer->GetPosition():0);
  if(indexini==XSTRING_NOTFOUND) return false;

  indexend = html.Find(searchend,false,indexini + searchini.GetSize());
  if(indexend==XSTRING_NOTFOUND) return false;

  if((int)(indexini + searchini.GetSize())>=indexend) return false;

  html.Copy(indexini + searchini.GetSize(),indexend,result);

  result.DeleteCharacter(__C(' '),XSTRINGCONTEXT_FROM_FIRST);
  result.DeleteCharacter(__C(' '),XSTRINGCONTEXT_TO_END);

  if(result.IsEmpty()) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSCRAPERWEB::HandleEvent(XEVENT* xevent)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    DATAIO
*
* @param[in]  xevent :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSCRAPERWEB::HandleEvent(XEVENT* xevent)
{
  if(!xevent) return;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSCRAPERWEB::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSCRAPERWEB::Clean()
{
  xmutexdo                = NULL;
  webclient               = NULL;
  cache                   = NULL;

  URLdownload             = NULL;

  xml                     = NULL;
}


#pragma endregion

