/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XPath.cpp
* 
* @class      XPATH
* @brief      eXtended Utils Path class
* @ingroup    XUTILS
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


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XPath.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "XFactory.h"
#include "XDir.h"
#include "XString.h"
#include "XTrace.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPATH::XPATH()
* @brief      Constructor
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XPATH::XPATH(): XSTRING()
{

}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPATH::XPATH(XDWORD size)
* @brief      Constructor
* @ingroup    XUTILS
*
* @param[in]  size :
*
* --------------------------------------------------------------------------------------------------------------------*/
XPATH::XPATH(XDWORD size): XSTRING(size)
{

}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPATH::XPATH(const char* path)
* @brief      Constructor
* @ingroup    XUTILS
*
* @param[in]  path :
*
* --------------------------------------------------------------------------------------------------------------------*/
XPATH::XPATH(const char* path) : XSTRING(path)
{

}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPATH::XPATH(const XCHAR* path)
* @brief      Constructor
* @ingroup    XUTILS
*
* @param[in]  path :
*
* --------------------------------------------------------------------------------------------------------------------*/
XPATH::XPATH(const XCHAR* path): XSTRING(path)
{

}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPATH::XPATH(const XCHAR* path,XDWORD size)
* @brief      Constructor
* @ingroup    XUTILS
*
* @param[in]  path :
* @param[in]  size :
*
* --------------------------------------------------------------------------------------------------------------------*/
XPATH::XPATH(const XCHAR* path,XDWORD size): XSTRING(path,size)
{

}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPATH::XPATH(XPATH& path)
* @brief      Constructor
* @ingroup    XUTILS
*
* @param[in]  path :
*
* --------------------------------------------------------------------------------------------------------------------*/
XPATH::XPATH(XPATH& path): XSTRING(path)
{

}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPATH::XPATH(XSTRING& string)
* @brief      Constructor
* @ingroup    XUTILS
*
* @param[in]  string :
*
* --------------------------------------------------------------------------------------------------------------------*/
XPATH::XPATH(XSTRING& string)  : XSTRING(string)
{

}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPATH::XPATH(XWORD* path)
* @brief      Constructor
* @ingroup    XUTILS
*
* @param[in]  path :
*
* --------------------------------------------------------------------------------------------------------------------*/
XPATH::XPATH(XWORD* path) : XSTRING(path)
{

}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPATH::~XPATH()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XPATH::~XPATH()
{

}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XPATH::operator = (const char* path)
* @brief      operator =
* @ingroup    XUTILS
*
* @param[in]  path :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XPATH::operator = (const char* path)
{
  Set(path);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XPATH::operator = (const XCHAR* path)
* @brief      operator =
* @ingroup    XUTILS
*
* @param[in]  path :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XPATH::operator = (const XCHAR* path)
{
  Set(path);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XPATH::operator = (XPATH& path)
* @brief      operator =
* @ingroup    XUTILS
*
* @param[in]  path :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XPATH::operator = (XPATH& path)
{
  Set(path);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XPATH::operator = (XSTRING& string)
* @brief      operator =
* @ingroup    XUTILS
*
* @param[in]  string :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XPATH::operator = (XSTRING& string)
{
  Set(string);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XPATH::operator = (XWORD* path)
* @brief      operator =
* @ingroup    XUTILS
*
* @param[in]  path :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XPATH::operator = (XWORD* path)
{
  Set(path);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XPATH::operator += (const char* path)
* @brief      operator +=
* @ingroup    XUTILS
*
* @param[in]  path :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XPATH::operator += (const char* path)
{
  Add(path);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XPATH::operator += (const XCHAR* path)
* @brief      operator +=
* @ingroup    XUTILS
*
* @param[in]  path :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XPATH::operator += (const XCHAR* path)
{
  Add(path);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XPATH::operator += (XPATH& path)
* @brief      operator +=
* @ingroup    XUTILS
*
* @param[in]  path :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XPATH::operator += (XPATH& path)
{
  Add(path);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XPATH::operator += (XSTRING& string)
* @brief      operator +=
* @ingroup    XUTILS
*
* @param[in]  string :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XPATH::operator += (XSTRING& string)
{
  Add(string);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XPATH::operator += (XCHAR path)
* @brief      operator +=
* @ingroup    XUTILS
*
* @param[in]  path :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XPATH::operator += (XCHAR path)
{
  Add(path);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATH::operator < (XPATH& path)
* @brief      operator <
* @ingroup    XUTILS
*
* @param[in]  path :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATH::operator <  (XPATH& path)
{
  return (bool)(Compare(path) == -1);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATH::operator > (XPATH& path)
* @brief      operator >
* @ingroup    XUTILS
*
* @param[in]  path :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATH::operator >  (XPATH& path)
{
  return (bool)(Compare(path) ==  1);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATH::operator <= (XPATH& path)
* @brief      operator <=
* @ingroup    XUTILS
*
* @param[in]  path :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATH::operator <= (XPATH& path)
{
  return (bool)(Compare(path) !=  1);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATH::operator >= (XPATH& path)
* @brief      operator >=
* @ingroup    XUTILS
*
* @param[in]  path :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATH::operator >= (XPATH& path)
{
  return (bool)(Compare(path) != -1);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATH::operator == (XPATH& path)
* @brief      operator ==
* @ingroup    XUTILS
*
* @param[in]  path :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATH::operator == (XPATH& path)
{
  return (bool)(Compare(path) ==  0);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATH::operator != (XPATH& path)
* @brief      operator !=
* @ingroup    XUTILS
*
* @param[in]  path :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATH::operator != (XPATH& path)
{
  return (bool)(Compare(path) !=  0);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATH::operator < (XSTRING& string)
* @brief      operator <
* @ingroup    XUTILS
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATH::operator <  (XSTRING& string)
{
  return (bool)(Compare(string) == -1);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATH::operator > (XSTRING& string)
* @brief      operator >
* @ingroup    XUTILS
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATH::operator >  (XSTRING& string)
{
  return (bool)(Compare(string) ==  1);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATH::operator <= (XSTRING& string)
* @brief      operator <=
* @ingroup    XUTILS
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATH::operator <= (XSTRING& string)
{
  return (bool)(Compare(string) !=  1);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATH::operator >= (XSTRING& string)
* @brief      operator >=
* @ingroup    XUTILS
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATH::operator >= (XSTRING& string)
{
  return (bool)(Compare(string) != -1);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATH::operator == (XSTRING& string)
* @brief      operator ==
* @ingroup    XUTILS
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATH::operator == (XSTRING& string)
{
  return (bool)(Compare(string) ==  0);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATH::operator != (XSTRING& string)
* @brief      operator !=
* @ingroup    XUTILS
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATH::operator != (XSTRING& string)
{
  return (bool)(Compare(string) !=  0);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XCHAR XPATH::operator [](int position)
* @brief      operator []
* @ingroup    XUTILS
*
* @param[in]  position :
*
* @return     XCHAR :
*
* --------------------------------------------------------------------------------------------------------------------*/
XCHAR XPATH::operator [](int position)
{
  if(IsEmpty())           return 0;

  if(position<0)          return text[0];
  if(position>=(int)size) return text[size-1];

  return text[position];
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATH::GetDrive(XSTRING& drive)
* @brief      GetDrive
* @ingroup    XUTILS
*
* @param[in]  drive :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATH::GetDrive(XSTRING& drive)
{
  Split(&drive,NULL,NULL,NULL);

  if(drive.IsEmpty()) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATH::GetPath(XSTRING& path)
* @brief      GetPath
* @ingroup    XUTILS
*
* @param[in]  path :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATH::GetPath(XSTRING& path)
{
  XPATH xpath;

  Split(NULL,&xpath,NULL,NULL);

  if(xpath.IsEmpty()) return false;

  xpath.Slash_Add();

  path = xpath;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATH::GetDriveAndPath(XSTRING& drivepath)
* @brief      GetDriveAndPath
* @ingroup    XUTILS
*
* @param[in]  drivepath :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATH::GetDriveAndPath(XSTRING& drivepath)
{
  XSTRING drive;
  XPATH   path;

  Split(&drive, &path, NULL, NULL);

  drivepath  = drive;
  drivepath += path;

  if(drivepath.IsEmpty()) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATH::GetPathAndNamefile(XSTRING& pathnamefile)
* @brief      GetPathAndNamefile
* @ingroup    XUTILS
*
* @param[in]  pathnamefile :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATH::GetPathAndNamefile(XSTRING& pathnamefile)
{
  XPATH      path;
  XSTRING name;

  Split(NULL,&path,&name,NULL);

  path.Slash_Add();

  pathnamefile  = path;
  pathnamefile += name;

  if(pathnamefile.IsEmpty()) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATH::GetPathAndNamefileExt(XSTRING& pathnamefile)
* @brief      GetPathAndNamefileExt
* @ingroup    XUTILS
*
* @param[in]  pathnamefile :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATH::GetPathAndNamefileExt(XSTRING& pathnamefile)
{
  XPATH   path;
  XSTRING name;
  XSTRING ext;

  Split(NULL, &path, &name, &ext);

  path.Slash_Add();

  pathnamefile  = path;
  pathnamefile += name;
  pathnamefile += ext;

  if(pathnamefile.IsEmpty()) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATH::GetNamefile(XSTRING& namefile)
* @brief      GetNamefile
* @ingroup    XUTILS
*
* @param[in]  namefile :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATH::GetNamefile(XSTRING& namefile)
{
  Split(NULL,NULL,&namefile,NULL);

  if(namefile.IsEmpty()) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATH::GetNamefileExt(XSTRING& namefileext)
* @brief      GetNamefileExt
* @ingroup    XUTILS
*
* @param[in]  namefileext :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATH::GetNamefileExt(XSTRING& namefileext)
{
  XSTRING name;
  XSTRING ext;

  Split(NULL,NULL,&name,&ext);

  namefileext  = name;
  namefileext += ext;

  if(namefileext.IsEmpty()) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATH::GetExt(XSTRING& ext)
* @brief      GetExt
* @ingroup    XUTILS
*
* @param[in]  ext :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATH::GetExt(XSTRING& ext)
{
  Split(NULL,NULL,NULL,&ext);

  if(ext.IsEmpty()) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATH::GetPathInSequence(int index, XSTRING& pathpart)
* @brief      GetPathInSequence
* @ingroup    XUTILS
*
* @param[in]  index :
* @param[in]  pathpart :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATH::GetPathInSequence(int index, XSTRING& pathpart)
{
  pathpart.Empty();

  int   slashcount = 0;
  XDWORD c           = 0;

  while(c<GetSize())
    {
      if((Get()[c]=='/') || (Get()[c]=='\\'))
        {
          if(slashcount==index)
            {
              return true;
            }
           else
            {
              pathpart.Empty();
              slashcount++;
            }

        } else pathpart.Add(Get()[c]);

      c++;
    }

  pathpart.Empty();

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         const XCHAR* XPATH::SetOnlyDrive()
* @brief      SetOnlyDrive
* @ingroup    XUTILS
* 
* @return     const XCHAR* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
const XCHAR* XPATH::SetOnlyDrive()
{
  XSTRING string;

  string.Empty();

  GetDrive(string);

  Set(string);

  return string.Get();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         const XCHAR* XPATH::SetOnlyPath()
* @brief      SetOnlyPath
* @ingroup    XUTILS
*
* @return     const XCHAR* :
*
* --------------------------------------------------------------------------------------------------------------------*/
const XCHAR* XPATH::SetOnlyPath()
{
  XSTRING string;

  string.Empty();

  GetPath(string);

  Set(string);

  return string.Get();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         const XCHAR* XPATH::SetOnlyDriveAndPath()
* @brief      SetOnlyDriveAndPath
* @ingroup    XUTILS
*
* @return     const XCHAR* :
*
* --------------------------------------------------------------------------------------------------------------------*/
const XCHAR* XPATH::SetOnlyDriveAndPath()
{
  XSTRING string;

  string.Empty();

  GetDriveAndPath(string);

  Set(string);

  return string.Get();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         const XCHAR* XPATH::SetOnlyPathAndNamefile()
* @brief      SetOnlyPathAndNamefile
* @ingroup    XUTILS
*
* @return     const XCHAR* :
*
* --------------------------------------------------------------------------------------------------------------------*/
const XCHAR* XPATH::SetOnlyPathAndNamefile()
{
  XSTRING string;

  string.Empty();

  GetPathAndNamefile(string);

  Set(string);

  return string.Get();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         const XCHAR* XPATH::SetOnlyPathAndNamefileExt()
* @brief      SetOnlyPathAndNamefileExt
* @ingroup    XUTILS
*
* @return     const XCHAR* :
*
* --------------------------------------------------------------------------------------------------------------------*/
const XCHAR* XPATH::SetOnlyPathAndNamefileExt()
{
  XSTRING string;

  string.Empty();

  GetPathAndNamefileExt(string);

  Set(string);

  return string.Get();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         const XCHAR* XPATH::SetOnlyNamefile()
* @brief      SetOnlyNamefile
* @ingroup    XUTILS
*
* @return     const XCHAR* :
*
* --------------------------------------------------------------------------------------------------------------------*/
const XCHAR* XPATH::SetOnlyNamefile()
{
  XSTRING string;

  string.Empty();

  GetNamefile(string);

  Set(string);

  return string.Get();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         const XCHAR* XPATH::SetOnlyNamefileExt()
* @brief      SetOnlyNamefileExt
* @ingroup    XUTILS
*
* @return     const XCHAR* :
*
* --------------------------------------------------------------------------------------------------------------------*/
const XCHAR* XPATH::SetOnlyNamefileExt()
{
  XSTRING string;

  string.Empty();

  GetNamefileExt(string);

  Set(string);

  return string.Get();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         const XCHAR* XPATH::SetOnlyExt()
* @brief      SetOnlyExt
* @ingroup    XUTILS
*
* @return     const XCHAR* :
*
* --------------------------------------------------------------------------------------------------------------------*/
const XCHAR* XPATH::SetOnlyExt()
{
  XSTRING string;

  string.Empty();

  GetExt(string);

  Set(string);

  return string.Get();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATH::DeleteDrive()
* @brief      DeleteDrive
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATH::DeleteDrive()
{
  if(IsEmpty())    return false;
  if(GetSize()<=2) return false;

  if(Get()[1]!=__C(':')) return false;

  XPATH xpath2;

  xpath2 = Get();
  xpath2.DeleteCharacters(0,2);

  Set(xpath2.Get());

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XPATH::DeleteExt()
* @brief      DeleteExt
* @ingroup    XUTILS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATH::DeleteExt()
{
  SetOnlyPathAndNamefile();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATH::Slash_HaveAtLast()
* @brief      Slash_HaveAtLast
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATH::Slash_HaveAtLast()
{
  XCHAR character = Character_GetLast();
  
  if((character == __C('\\')) || (character == __C('/'))) return true;

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATH::Slash_Add()
* @brief      Slash_Add
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATH::Slash_Add()
{
  int           count[2] = { 0 , 0 };
  XCHAR* str             = Get();
  bool          status   = false;

  XDWORD c = 0;

  while(c < GetSize())
    {
      if(str[c]==__C('/'))  count[0]++;
      if(str[c]==__C('\\')) count[1]++;

      c++;
    }

  if(!Slash_HaveAtLast())
    {
      if(count[0]>count[1])
             Add("/");
        else Add("\\");

      Slash_Normalize();

      status = true;
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATH::Slash_Normalize(bool inverse)
* @brief      Slash_Normalize
* @ingroup    XUTILS
*
* @param[in]  inverse :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATH::Slash_Normalize(bool inverse)
{
  if(IsEmpty()) return false;

  XCHAR* str = Get();
  int           c   = 0;

  while(str[c])
    {
      if(inverse)
       {
         if(str[c]==__C('/'))  str[c] = __C('\\');
       }
      else
       {
         if(str[c]==__C('\\')) str[c] = __C('/');
       }

      c++;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATH::Slash_Delete()
* @brief      Slash_Delete
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATH::Slash_Delete()
{
  bool status = false;

  if(Slash_HaveAtLast())
    {
      DeleteCharacter('\\' , XSTRINGCONTEXT_TO_END);
      DeleteCharacter('/'  , XSTRINGCONTEXT_TO_END);

      status = true;
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATH::AddToNameFile(bool isprefix, XCHAR* tag)
* @brief      AddToNameFile
* @ingroup    XUTILS
*
* @param[in]  isprefix :
* @param[in]  tag :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATH::AddToNameFile(bool isprefix, XCHAR* tag)
{
  XSTRING  drive;
  XPATH    xpath;
  XSTRING  name;
  XSTRING  newname;
  XSTRING  ext;

  if(!Split(&drive,&xpath,&name,&ext)) return false;

  //if(!drive.IsEmpty()) drive.Add(__L("/"));

  xpath.Slash_Add();

  if(isprefix)
    {
      newname  = tag;
      newname += name;
    }
   else
    {
      newname  = name;
      newname += tag;
    }

  Format(__L("%s%s%s%s"),drive.Get(),xpath.Get(),newname.Get(),ext.Get());

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATH::Create(int nelements,...)
* @brief      Create
* @ingroup    XUTILS
*
* @param[in]  nelements :
* @param[in]  ... :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATH::Create(int nelements,...)
{
  va_list arg;

  Empty();

  va_start(arg, nelements);

  int c=0;
  while(c<nelements)
    {
      XPATH xpath;

      xpath = (XCHAR*)va_arg(arg, XCHAR*);
      if(!xpath.IsEmpty())
        {
          if(c && xpath.Character_GetFirst()!=__C('.'))
            {
              Slash_Add();
            }

          Add(xpath);
        }

      c++;
    }

  va_end(arg);

  Slash_Normalize();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATH::Create(XPATHSMANAGERSECTIONTYPE sectiontype, int nelements, ...)
* @brief      Create
* @ingroup    XUTILS
*
* @param[in]  sectiontype :
* @param[in]  nelements :
* @param[in]  ... :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATH::Create(XPATHSMANAGERSECTIONTYPE sectiontype, int nelements, ...)
{
  XPATH   xpathsection;
  va_list arg;
  bool    status = true;

  Empty();

  GEN_XPATHSMANAGER.GetPathOfSection(sectiontype, xpathsection);

  Add(xpathsection);

  va_start(arg, nelements);

  int c=0;
  while(c<nelements)
    {
      XPATH xpath;

      xpath = (XCHAR*)va_arg(arg, XCHAR*);
      if(!xpath.IsEmpty())
        {
          if(c && xpath.Character_GetFirst()!=__C('.'))
            {
              Slash_Add();
            }

          Add(xpath);
        }

      c++;
    }

  va_end(arg);

  Slash_Normalize();

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATH::Split(XSTRING* drive, XPATH* xpath, XSTRING* name, XSTRING* ext)
* @brief      Split
* @ingroup    XUTILS
*
* @param[in]  drive :
* @param[in]  xpath :
* @param[in]  name :
* @param[in]  ext :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATH::Split(XSTRING* drive, XPATH* xpath, XSTRING* name, XSTRING* ext)
{
  XCHAR* pathstr = Get();
  int    idrive  = 0;
  int    iname   = 0;
  int    iext    = 0;
  int    c;

  if(IsEmpty()) return false;
  if(!pathstr)  return false;

  c = 0;
  while(pathstr[c])
    {
      if(pathstr[c]==__C(':'))
        {
          if(drive) Copy(0,c+1,(*drive));

          idrive = c+1;
          break;
        }

      c++;
    }

  c = (GetSize()-1);
  while(pathstr[c])
    {
      if((pathstr[c]==__C('\\')) || (pathstr[c]==__C('/')))
        {
          break;
        }

      if(pathstr[c]==__C('.'))
        {
          if(ext) Copy(c, GetSize(), (*ext));

          iext = c;
          break;
        }

      c--;
    }

  c = (iext)?iext:GetSize();
  while(c>=0)
    {
      if((!c) || pathstr[c]==__C('\\') || pathstr[c]==__C('/')  || pathstr[c]==__C(':'))
        {
          if(pathstr[c]==__C('\\') || pathstr[c]==__C('/') || pathstr[c]==__C(':')) c++;

          if(name) Copy(c, (iext)?iext:GetSize(), (*name));

          iname = c;
          break;
        }

      c--;
    }

  if(xpath && iname) Copy(idrive, iname, (*xpath));

  return true;
}


#pragma endregion

