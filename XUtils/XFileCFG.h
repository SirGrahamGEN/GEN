/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XFileCFG.h
*
* @class      XFILECFG
* @brief      eXtended CFG (Config) file class
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

#ifndef _XFILECFG_H_
#define _XFILECFG_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XString.h"
#include "XPath.h"
#include "XSubject.h"
#include "XVector.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum XFILECFG_VALUETYPE
{
  XFILECFG_VALUETYPE_UNKNOWN          = 0 ,
  XFILECFG_VALUETYPE_INT                ,
  XFILECFG_VALUETYPE_MASK               ,
  XFILECFG_VALUETYPE_FLOAT              ,
  XFILECFG_VALUETYPE_STRING             ,
  XFILECFG_VALUETYPE_BOOLEAN
};

#define XFILECFG_EXTENSIONFILE  __L(".ini")

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XPATHS;
class XFILEINI;
class XFILEINIREMARK;


class XFILECFGVALUE
{
  public:
                                        XFILECFGVALUE             ();
    virtual                            ~XFILECFGVALUE             ();

    XFILECFG_VALUETYPE                  GetType                   ();
    bool                                SetType                   (XFILECFG_VALUETYPE type);

    XSTRING*                            GetGroup                  ();
    XSTRING*                            GetID                     ();

    void*                               GetValue                  ();
    bool                                SetValue                  (void* value);

  private:

    void                                Clean                     ();

    XFILECFG_VALUETYPE                  type;
    XSTRING                             group;
    XSTRING                             ID;
    void*                               value;
};



class XFILECFG : public XSUBJECT
{
  public:                                        
                                        XFILECFG                  (XCHAR* namefile = NULL);
    virtual                            ~XFILECFG                  ();

    virtual bool                        Ini                       ();

    bool                                Load                      ();
    virtual bool                        Load                      (XPATH& xpath);

    bool                                Save                      ();
    virtual bool                        Save                      (XPATH& xpath);

    virtual bool                        End                       ();

    bool                                AddValue                  (XFILECFG_VALUETYPE type, XCHAR* group, XCHAR* ID, void* value);
    XVECTOR<XFILECFGVALUE*>*            GetValues                 ();    
    bool                                DeleteAllValues           ();
    
    bool                                AddRemark                 (XCHAR* group, XCHAR* text, XDWORD xpos, XDWORD relativeypos);
    bool                                AddRemark                 (XCHAR* group, XCHAR* ID, XCHAR* text, XDWORD xpos, XDWORD relativeypos);
    XVECTOR<XFILEINIREMARK*>*           GetRemarks                ();
    bool                                DeleteAllRemarks          ();
     
  protected:

    XPATH                               xpathfile;
    XSTRING                             namefile;
    XFILEINI*                           fileini;

  private:
    
    bool                                IniFile                   (XPATH& xpath);
    bool                                EndFile                   ();

    bool                                AjustRemarks              (); 

    void                                Clean                     ();
 
    XVECTOR<XFILECFGVALUE*>             values;
    XVECTOR<XFILEINIREMARK*>            remarks;
};




/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif




