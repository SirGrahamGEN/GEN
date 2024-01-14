/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XPathsManager.cpp
* 
* @class      XPATHSMANAGER
* @brief      eXtended Utils Paths manager class
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

#include "XPathsManager.h"

#include "XFactory.h"
#include "XDir.h"
#include "XTrace.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

XPATHSMANAGER*  XPATHSMANAGER::instance = NULL;

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


#pragma region CLASS_XPATHSMANAGERSECTION


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPATHSMANAGERSECTION::XPATHSMANAGERSECTION()
* @brief      Constructor
* @ingroup    XUTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XPATHSMANAGERSECTION::XPATHSMANAGERSECTION()
{
  Clean();

  xpath = new XPATH();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPATHSMANAGERSECTION::~XPATHSMANAGERSECTION()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XPATHSMANAGERSECTION::~XPATHSMANAGERSECTION()
{
  if(xpath) delete xpath;

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XPATHSMANAGERSECTION::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XPATHSMANAGERSECTION::Clean()
{
  type = XPATHSMANAGERSECTIONTYPE_UNKNOWN;
  xpath = NULL;
}


#pragma endregion


#pragma region CLASS_XPATHSMANAGER


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATHSMANAGER::GetIsInstanced()
* @brief      GetIsInstanced
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATHSMANAGER::GetIsInstanced()
{
  return instance!=NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPATHSMANAGER& XPATHSMANAGER::GetInstance()
* @brief      GetInstance
* @ingroup    XUTILS
*
* @return     XPATHSMANAGER& :
*
* --------------------------------------------------------------------------------------------------------------------*/
XPATHSMANAGER& XPATHSMANAGER::GetInstance()
{
  if(!instance) instance = new XPATHSMANAGER();
  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATHSMANAGER::DelInstance()
* @brief      DelInstance
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATHSMANAGER::DelInstance()
{
  if(!instance) return false;

  delete instance;
  instance = NULL;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATHSMANAGER::GetPathOfSection(XPATHSMANAGERSECTIONTYPE sectiontype, XPATH& xpath, bool addroot)
* @brief      GetPathOfSection
* @ingroup    XUTILS
*
* @param[in]  sectiontype :
* @param[in]  xpath :
* @param[in]  addroot :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATHSMANAGER::GetPathOfSection(XPATHSMANAGERSECTIONTYPE sectiontype, XPATH& xpath, bool addroot)
{
  xpath.Empty();

  if(addroot && (sectiontype!=XPATHSMANAGERSECTIONTYPE_ROOT))
    {
      for(XDWORD c=0; c<pathsections.GetSize(); c++)
        {
          XPATHSMANAGERSECTION* pathsection = pathsections.Get(c);
          if(pathsection)
            {
              if(pathsection->type == XPATHSMANAGERSECTIONTYPE_ROOT)
                {
                  xpath = pathsection->xpath->Get();
                  xpath.Slash_Add();
                  break;
                }
            }
        }
    }

  for(XDWORD c=0; c<pathsections.GetSize(); c++)
    {
      XPATHSMANAGERSECTION* pathsection = pathsections.Get(c);
      if(pathsection)
        {
          if(pathsection->type == sectiontype)
            {
              xpath += pathsection->xpath->Get();
              break;
            }
        }
    }

  return xpath.IsEmpty()?false:true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPATH* XPATHSMANAGER::GetAppExecPath()
* @brief      GetAppExecPath
* @ingroup    XUTILS
*
* @return     XPATH* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XPATH* XPATHSMANAGER::GetAppExecPath()
{
  return appexecpath;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATHSMANAGER::GetAppExecPathWithoutAsset(XCHAR* assetlevel, XPATH& xpath);
* @brief      GetAppExecPathWithoutAsset
* @ingroup    XUTILS
*
* @param[in]  assetlevel : 
* @param[in]  xpath : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATHSMANAGER::GetAppExecPathWithoutAsset(XCHAR* assetlevel, XPATH& xpath)
{
  XSTRING assetname;

  xpath.Empty();

  assetname = assetlevel;

  GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpath);     

  int index = xpath.Find(assetlevel, false);
  if(index == XSTRING_NOTFOUND) return true;

  xpath.DeleteCharacters(index, assetname.GetSize());  

  xpath.Slash_Delete();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPATHSMANAGERSECTION* XPATHSMANAGER::GetPathSection(XPATHSMANAGERSECTIONTYPE sectiontype)
* @brief      GetPathSection
* @ingroup    XUTILS
*
* @param[in]  sectiontype :
*
* @return     XPATHSMANAGERSECTION* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XPATHSMANAGERSECTION* XPATHSMANAGER::GetPathSection(XPATHSMANAGERSECTIONTYPE sectiontype)
{
  if(pathsections.IsEmpty()) return NULL;

  for(XDWORD c=0; c<pathsections.GetSize(); c++)
    {
      XPATHSMANAGERSECTION* pathsection = pathsections.Get(c);
      if(pathsection)
        {
          if(pathsection->type == sectiontype)
            {
              return pathsection;
            }
        }
    }

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATHSMANAGER::AddPathSection(XPATHSMANAGERSECTIONTYPE sectiontype, XSTRING& xpath)
* @brief      AddPathSection
* @ingroup    XUTILS
*
* @param[in]  sectiontype :
* @param[in]  xpath :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATHSMANAGER::AddPathSection(XPATHSMANAGERSECTIONTYPE sectiontype, XSTRING& xpath)
{
  XPATHSMANAGERSECTION* xpathsection = GetPathSection(sectiontype);
  if(!xpathsection)
    {
      xpathsection = new XPATHSMANAGERSECTION();
      if(!xpathsection) return false;

      xpathsection->type  = sectiontype;
      (*xpathsection->xpath) = xpath.Get();

      if(!xpathsection->xpath->IsEmpty())
        {
          xpathsection->xpath->Slash_Add();
          xpathsection->xpath->Slash_Normalize();
        }

      pathsections.Add(xpathsection);
    }
   else
    {
      (*xpathsection->xpath) = xpath;
      xpathsection->xpath->Slash_Add();
      xpathsection->xpath->Slash_Normalize();
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATHSMANAGER::AddPathSection(XPATHSMANAGERSECTIONTYPE sectiontype,const XCHAR* string)
* @brief      AddPathSection
* @ingroup    XUTILS
*
* @param[in]  sectiontype :
* @param[in]  XCHAR* string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATHSMANAGER::AddPathSection(XPATHSMANAGERSECTIONTYPE sectiontype,const XCHAR* string)
{
  XSTRING path(string);

  return AddPathSection(sectiontype,path);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATHSMANAGER::DeleteAllPathSections()
* @brief      DeleteAllPathSections
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATHSMANAGER::DeleteAllPathSections()
{
  if(pathsections.IsEmpty()) return false;

  pathsections.DeleteContents();

  pathsections.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATHSMANAGER::CreateAllPathSectionOnDisk()
* @brief      CreateAllPathSectionOnDisk
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATHSMANAGER::CreateAllPathSectionOnDisk()
{
  XDIR* GEN_XFACTORY_CREATE(xdir, Create_Dir())
  if(!xdir) return false;

  bool status = true;

  for(XDWORD c=0; c<pathsections.GetSize(); c++)
    {
      XPATHSMANAGERSECTION* pathsection = pathsections.Get(c);
      if(pathsection)
        {
          XPATH xpath;

          if(GetPathOfSection(pathsection->type, xpath, true))
            {
              if(!xdir->Exist(xpath.Get()))
                {
                  if(!xdir->Make(xpath.Get()))
                    {
                      status = false;
                    }

                  //XTRACE_PRINTCOLOR((status?2:4), __L("Dir Create: %s "), xpath->Get());
                }
               else
                {
                  //XTRACE_PRINTCOLOR(2, __L("Dir Exist: %s "), xpath->Get());
                }
            }
        }
    }

  GEN_XFACTORY.Delete_Dir(xdir);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPATHSMANAGER::AdjustRootPathDefault(XCHAR* assetsdirname)
* @brief      AdjustRootPathDefault
* @ingroup    XUTILS
*
* @param[in]  assetsdirname : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPATHSMANAGER::AdjustRootPathDefault(XCHAR* assetsdirname)
{ 
  XDIR* xdir;
  XPATH xpathroot;
  XPATH xpathtest;
  bool  founddir    = false;
  int   indexfound  = 0;
  bool  status      = false;

  GEN_XFACTORY_CREATE(xdir, Create_Dir())
  if(!xdir) return false;

  GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathroot);
  xpathroot.Slash_Add();

  do{ indexfound = xpathroot.Find(__L("/"), false, indexfound);
      if(indexfound == XSTRING_NOTFOUND)   indexfound = xpathroot.Find(__L("\\"), false, indexfound);

      if(indexfound != XSTRING_NOTFOUND)
        {
          xpathroot.Copy(0, indexfound, xpathtest);

          xpathtest.Slash_Add();
          xpathtest.Add(assetsdirname);

          founddir = xdir->Exist(xpathtest);
          if(founddir)
            {
              AddPathSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathtest);
              status  = true;
              break;    
            }

          indexfound++;
        } 

    } while(indexfound != XSTRING_NOTFOUND);

  if(!founddir)
    {
      xpathtest = xpathroot;
      xpathtest.Slash_Add();
      xpathtest.Add(assetsdirname);

      if(xdir->Make(xpathtest, false))
        {
          AddPathSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathtest);
          status  = true;      
        }
    }
  
  GEN_XFACTORY.Delete_Dir(xdir);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPATHSMANAGER::XPATHSMANAGER()
* @brief      Construct
* @ingroup    XUTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XPATHSMANAGER::XPATHSMANAGER()
{
  Clean();

  appexecpath = new XPATH;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPATHSMANAGER::~XPATHSMANAGER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XPATHSMANAGER::~XPATHSMANAGER()
{
  DeleteAllPathSections();

  if(appexecpath)
    {
      delete appexecpath;
    }

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XPATHSMANAGER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XPATHSMANAGER::Clean()
{
  appexecpath = NULL;
}


#pragma endregion


#pragma endregion

