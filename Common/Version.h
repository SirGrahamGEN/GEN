/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       Version.h
* 
* @class      VERSION
* @brief      Version of framework
* @ingroup    PLATFORM_COMMON
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

#ifndef _VERSION_H_
#define _VERSION_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XString.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define VERSION_NAME         "GEN FrameWork"
#define VERSION_VERSION      0
#define VERSION_SUBVERSION   12
#define VERSION_SUBERROR     2
#define VERSION_CODENAME     "Danchel"

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class VERSION
{
  public:

    static bool             GetIsInstanced                ();
    static VERSION&         GetInstance                   ();
    static bool             DelInstance                   ();

    XSTRING*                GetName                       ();
    XSTRING*                GetVersion                    ();
    void                    GetVersion                    (XDWORD& version, XDWORD& subversion, XDWORD& versionerror);
    XSTRING*                GetCodeName                   ();
    
    
    void                    GetAppVersion                 (XDWORD& app_version, XDWORD& app_subversion, XDWORD& app_versionerror);    
    XSTRING*                GetAppOwner                   ();
    XDWORD                  GetAppCreationYear            ();    
    
    XSTRING*                GetAppTitle                   ();
    XSTRING*                GetAppVersion                 ();
    bool                    SetAppVersion                 (XCHAR* app_name, XDWORD app_version, XDWORD app_subversion, XDWORD app_versionerror,XCHAR* app_owner, XDWORD app_creationyear);
   
  private:
                            VERSION                       ();
                            VERSION                       (VERSION const&);         // Don't implement
    virtual                ~VERSION                       ();

    void                    operator =                    (VERSION const&);         // Don't implement    

    void                    Clean                         ();

    XSTRING                 name;   
    XSTRING                 version;         
    XSTRING                 codename; 

    XSTRING                 app_name;    
    XDWORD                  app_version;
    XDWORD                  app_subversion;
    XDWORD                  app_versionerror;
    XSTRING                 app_ower;
    XDWORD                  app_creationyear;

    XSTRING                 app_titlestr;
    XSTRING                 app_versionstr;

    static VERSION*         instance;     
};

/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif

