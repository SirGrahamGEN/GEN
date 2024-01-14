/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XPathsManager.h
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

#ifndef _XPATHSMANAGER_H_
#define _XPATHSMANAGER_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XVector.h"
#include "XString.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

enum XPATHSMANAGERSECTIONTYPE
{
  XPATHSMANAGERSECTIONTYPE_UNKNOWN        = 0 ,
  XPATHSMANAGERSECTIONTYPE_ROOT               ,
  XPATHSMANAGERSECTIONTYPE_LOGS               ,
  XPATHSMANAGERSECTIONTYPE_DATABASES          ,
  XPATHSMANAGERSECTIONTYPE_WEB                ,
  XPATHSMANAGERSECTIONTYPE_SCRAPERWEB         ,
  XPATHSMANAGERSECTIONTYPE_FONTS              ,
  XPATHSMANAGERSECTIONTYPE_GRAPHICS           ,
  XPATHSMANAGERSECTIONTYPE_UI_LAYOUTS         ,
  XPATHSMANAGERSECTIONTYPE_SOUNDS             ,
  XPATHSMANAGERSECTIONTYPE_SCRIPTS            ,
  XPATHSMANAGERSECTIONTYPE_FIRMWARE           ,  
  XPATHSMANAGERSECTIONTYPE_CERTIFICATES       ,  
  XPATHSMANAGERSECTIONTYPE_GENERIC1           ,
  XPATHSMANAGERSECTIONTYPE_GENERIC2           ,
  XPATHSMANAGERSECTIONTYPE_GENERIC3           ,
  XPATHSMANAGERSECTIONTYPE_GENERIC4           ,
  XPATHSMANAGERSECTIONTYPE_GENERIC5           ,
  XPATHSMANAGERSECTIONTYPE_GENERIC6           ,
  XPATHSMANAGERSECTIONTYPE_GENERIC7           ,
};

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

class XPATH;


class XPATHSMANAGERSECTION
{
  public:
                                      XPATHSMANAGERSECTION          ();
    virtual                          ~XPATHSMANAGERSECTION          ();

    XPATHSMANAGERSECTIONTYPE          type;
    XPATH*                            xpath;

  private:

    void                              Clean                         ();
};


class XPATHSMANAGER
{
  public:

    static bool                       GetIsInstanced                ();
    static XPATHSMANAGER&             GetInstance                   ();
    static bool                       DelInstance                   ();

    bool                              GetPathOfSection              (XPATHSMANAGERSECTIONTYPE sectiontype, XPATH& xpath, bool addroot = true);

    XPATH*                            GetAppExecPath                ();

    bool                              GetAppExecPathWithoutAsset    (XCHAR* assetlevel, XPATH& xpath);

    XPATHSMANAGERSECTION*             GetPathSection                (XPATHSMANAGERSECTIONTYPE sectiontype);

    bool                              AddPathSection                (XPATHSMANAGERSECTIONTYPE sectiontype, XSTRING& xpath);
    bool                              AddPathSection                (XPATHSMANAGERSECTIONTYPE sectiontype, const XCHAR* string);

    bool                              DeleteAllPathSections         ();

    bool                              CreateAllPathSectionOnDisk    ();

    bool                              AdjustRootPathDefault         (XCHAR* assetsdirname);
    
  private:
                                      XPATHSMANAGER                 ();
                                      XPATHSMANAGER                 (XPATHSMANAGER const&);       // Don't implement
    virtual                          ~XPATHSMANAGER                 ();
    void                              operator =                    (XPATHSMANAGER const&);       // Don't implement

    void                              Clean                         ();

    XPATH*                            appexecpath;
    XVECTOR<XPATHSMANAGERSECTION*>    pathsections;
    static XPATHSMANAGER*             instance;
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

