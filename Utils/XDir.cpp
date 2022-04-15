/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XDir.cpp
*
* @class      XDIR
* @brief      eXtended dir class
* @ingroup    UTILS
*
* @copyright  GEN Group. All right reserved.
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
*---------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

#include "XFactory.h"
#include "XFile.h"
#include "XDir.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDIRELEMENT::XDIRELEMENT()
* @brief      Constructor
* @ingroup    UTILS
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XDIRELEMENT::XDIRELEMENT()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDIRELEMENT::~XDIRELEMENT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    UTILS
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XDIRELEMENT::~XDIRELEMENT()
{
  DeleteFindFileData();
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDIRELEMENTTYPE XDIRELEMENT::GetType()
* @brief      GetType
* @ingroup    UTILS
*
* @return     XDIRELEMENTTYPE :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDIRELEMENTTYPE XDIRELEMENT::GetType()
{
  return type;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XDIRELEMENT::SetType(XDIRELEMENTTYPE type)
* @brief      SetType
* @ingroup    UTILS
*
* @param[in]  type :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XDIRELEMENT::SetType(XDIRELEMENTTYPE type)
{
  this->type = type;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPATH* XDIRELEMENT::GetPathSearch()
* @brief      GetPathSearch
* @ingroup    UTILS
*
* @return     XPATH* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XPATH* XDIRELEMENT::GetPathSearch()
{
  return &pathsearch;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* XDIRELEMENT::GetPatternSearch()
* @brief      GetPatternSearch
* @ingroup    UTILS
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* XDIRELEMENT::GetPatternSearch()
{
  return &patternsearch;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPATH* XDIRELEMENT::GetNameFile()
* @brief      GetNameFile
* @ingroup    UTILS
*
* @return     XPATH* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XPATH* XDIRELEMENT::GetNameFile()
{
  return &namefile;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDATETIME* XDIRELEMENT::GetDateTimeFile_Created()
* @brief      GetDateTimeFile_Created
* @ingroup    UTILS
*
* @return     XDATETIME* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDATETIME* XDIRELEMENT::GetDateTimeFile_Created()
{
  return &datetime_created;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDATETIME* XDIRELEMENT::GetDateTimeFile_Modificated()
* @brief      GetDateTimeFile_Modificated
* @ingroup    UTILS
*
* @return     XDATETIME* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDATETIME* XDIRELEMENT::GetDateTimeFile_Modificated()
{
  return &datetime_modificated;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDATETIME* XDIRELEMENT::GetDateTimeFile_LastAccess()
* @brief      GetDateTimeFile_LastAccess
* @ingroup    UTILS
*
* @return     XDATETIME* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XDATETIME* XDIRELEMENT::GetDateTimeFile_LastAccess()
{
  return &datetime_lastaccess;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void* XDIRELEMENT::GetHandle()
* @brief      GetHandle
* @ingroup    UTILS
*
* @return     void* :
*
*---------------------------------------------------------------------------------------------------------------------*/
void* XDIRELEMENT::GetHandle()
{
  return handle;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XDIRELEMENT::SetHandle(void* handle)
* @brief      SetHandle
* @ingroup    UTILS
*
* @param[in]  handle :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XDIRELEMENT::SetHandle(void* handle)
{
  this->handle = handle;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void* XDIRELEMENT::GetFindFileData()
* @brief      GetFindFileData
* @ingroup    UTILS
*
* @return     void* :
*
*---------------------------------------------------------------------------------------------------------------------*/
void* XDIRELEMENT::GetFindFileData()
{
  return findfiledata;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XDIRELEMENT::SetFindFileData(void* findfiledata)
* @brief      SetFindFileData
* @ingroup    UTILS
*
* @param[in]  findfiledata :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XDIRELEMENT::SetFindFileData(void* findfiledata)
{
  this->findfiledata = findfiledata;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XDIRELEMENT::DeleteFindFileData()
* @brief      DeleteFindFileData
* @ingroup    UTILS
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XDIRELEMENT::DeleteFindFileData()
{
  if(!findfiledata) return false;

  delete [] (XBYTE*)findfiledata;

  findfiledata = NULL;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XDIRELEMENT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    UTILS
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XDIRELEMENT::Clean()
{
  type = XDIRELEMENTTYPE_NONE;

  handle       = (void*)-1;
  findfiledata = NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDIR::XDIR()
* @brief      Constructor
* @ingroup    UTILS
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XDIR::XDIR()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDIR::~XDIR()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    UTILS
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XDIR::~XDIR()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XDIR::Exist(XPATH& xpath)
* @brief      Exist
* @ingroup    UTILS
*
* @param[in]  xpath :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XDIR::Exist(XPATH& xpath)
{
  return Exist(xpath.Get());
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XDIR::Make(XPATH& xpath, bool recursive)
* @brief      Make
* @ingroup    UTILS
*
* @param[in]  xpath : 
* @param[in]  recursive : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XDIR::Make(XPATH& xpath, bool recursive)
{
  return Make(xpath.Get(), recursive);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XDIR::ChangeTo(XPATH& xpath)
* @brief      ChangeTo
* @ingroup    UTILS
*
* @param[in]  xpath :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XDIR::ChangeTo(XPATH& xpath)
{
  return ChangeTo(xpath.Get());
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XDIR::Delete(XPATH& xpath,bool all)
* @brief      Delete
* @ingroup    UTILS
*
* @param[in]  xpath :
* @param[in]  all :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XDIR::Delete(XPATH& xpath,bool all)
{
  return Delete(xpath.Get(),all);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XDIR::FirstSearch(XPATH& xpath,XSTRING& patternsearch,XDIRELEMENT* searchelement)
* @brief      FirstSearch
* @ingroup    UTILS
*
* @param[in]  xpath :
* @param[in]  patternsearch :
* @param[in]  searchelement :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XDIR::FirstSearch(XPATH& xpath,XSTRING& patternsearch,XDIRELEMENT* searchelement)
{
  return FirstSearch(xpath.Get(),patternsearch.Get(),searchelement);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XDIR::FirstSearch(XPATH& xpath,XCHAR* patternsearch,XDIRELEMENT* searchelement)
* @brief      FirstSearch
* @ingroup    UTILS
*
* @param[in]  xpath :
* @param[in]  patternsearch :
* @param[in]  searchelement :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XDIR::FirstSearch(XPATH& xpath,XCHAR* patternsearch,XDIRELEMENT* searchelement)
{
  return FirstSearch(xpath.Get(),patternsearch,searchelement);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XDIR::FirstSearch(XCHAR* xpath,XSTRING& patternsearch,XDIRELEMENT* searchelement)
* @brief      FirstSearch
* @ingroup    UTILS
*
* @param[in]  xpath :
* @param[in]  patternsearch :
* @param[in]  searchelement :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XDIR::FirstSearch(XCHAR* xpath,XSTRING& patternsearch,XDIRELEMENT* searchelement)
{
  return FirstSearch(xpath,patternsearch.Get(),searchelement);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XDIR::Copy(XPATH& xpathsource,XPATH& xpathtarget)
* @brief      Copy
* @ingroup    UTILS
*
* @param[in]  xpathsource :
* @param[in]  xpathtarget :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XDIR::Copy(XPATH& xpathsource,XPATH& xpathtarget)
{
  #define COPYFILE_MAXBUFFER 2048

  bool status = true;

  XFILE* GEN_XFACTORY_CREATE(fsource, Create_File())
  XFILE* GEN_XFACTORY_CREATE(ftarget, Create_File());

  if(fsource && ftarget)
    {
      if(fsource->Open(xpathsource))
        {
          if(ftarget->Create(xpathtarget))
            {
              XBYTE* buffer = new XBYTE[COPYFILE_MAXBUFFER];
              if(buffer)
                {
                  XDWORD rsize  = 0;

                  do { rsize = COPYFILE_MAXBUFFER;

                       memset(buffer,0,rsize);

                       fsource->Read(buffer,&rsize);

                       if(rsize) ftarget->Write(buffer,rsize);

                     } while(rsize == COPYFILE_MAXBUFFER);

                  delete[] buffer;
                }

              ftarget->Close();

            } else status = false;

          fsource->Close();

        } else status = false;

    } else status = false;

  GEN_XFACTORY.Delete_File(fsource);
  GEN_XFACTORY.Delete_File(ftarget);

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XDIR::Copy(XCHAR* xpathsource,XPATH& xpathtarget)
* @brief      Copy
* @ingroup    UTILS
*
* @param[in]  xpathsource :
* @param[in]  xpathtarget :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XDIR::Copy(XCHAR* xpathsource,XPATH& xpathtarget)
{
  XPATH _xpathsource;

  _xpathsource = xpathsource;

  return Copy(_xpathsource, xpathtarget);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XDIR::Copy(XPATH& xpathsource,XCHAR* xpathtarget)
* @brief      Copy
* @ingroup    UTILS
*
* @param[in]  xpathsource :
* @param[in]  xpathtarget :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XDIR::Copy(XPATH& xpathsource,XCHAR* xpathtarget)
{
  XPATH _xpathtarget;

  _xpathtarget = xpathtarget;

  return Copy(xpathsource, _xpathtarget);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XDIR::Copy(XCHAR* xpathsource,XCHAR* xpathtarget)
* @brief      Copy
* @ingroup    UTILS
*
* @param[in]  xpathsource :
* @param[in]  xpathtarget :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XDIR::Copy(XCHAR* xpathsource,XCHAR* xpathtarget)
{
  XPATH _xpathsource;
  XPATH _xpathtarget;

  _xpathsource = xpathsource;
  _xpathtarget = xpathtarget;

  return Copy(_xpathsource, _xpathtarget);

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XDIR::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    UTILS
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XDIR::Clean()
{

}
