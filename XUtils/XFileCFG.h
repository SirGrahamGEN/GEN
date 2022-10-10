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
class XVARIANT;


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

    XPATH*                              GetPathFile               ();

    virtual bool                        Ini                       ();

    virtual bool                        ReAjustIni                ();        

    bool                                Load                      ();
    virtual bool                        Load                      (XPATH& xpath);
    
    bool                                Save                      ();
    virtual bool                        Save                      (XPATH& xpath);

    virtual bool                        End                       ();

    bool                                AddValue                  (XFILECFG_VALUETYPE type, XCHAR* group, XCHAR* ID, void* value, XCHAR* remark_text = NULL, XDWORD remark_xpos = 0);
    XVECTOR<XFILECFGVALUE*>*            GetValues                 ();   
    XVARIANT*                           GetValue                  (XCHAR* group, XCHAR* ID);   
    bool                                DeleteAllValues           ();
   
    bool                                AddRemark                 (XCHAR* group, XCHAR* text, XDWORD xpos, XDWORD relativeypos);
    bool                                AddRemark                 (XCHAR* group, XCHAR* ID, XCHAR* text, XDWORD xpos, XDWORD relativeypos);
    XVECTOR<XFILEINIREMARK*>*           GetRemarks                ();
    bool                                DeleteAllRemarks          ();  
    
    bool                                IniFile                   (XPATH& xpath);
    bool                                EndFile                   ();
    bool                                AjustRemarks              (); 

    int                                 GetCountKeys              (XCHAR* group, XCHAR* IDbase, XCHAR* mask = NULL, int maxcount = 99); 

    template<typename T>
    bool                                AddValueSecuence          (XFILECFG_VALUETYPE type, XCHAR* group, XCHAR* IDbasic, XCHAR* mask, int mincount, int maxcount, XVECTOR<T*>& values, int& nkeys, XCHAR* remark_text = NULL, XDWORD remark_xpos = 0)
                                        {
                                          XSTRING key;
                                          
                                          nkeys = GetCountKeys(group, IDbasic, mask);    

                                          if(nkeys < 0) nkeys = 0;

                                          if(nkeys < mincount)  nkeys = mincount;

                                          values.DeleteContents();
                                          values.DeleteAll();

                                          for(int c=0; c<nkeys; c++)
                                            {
                                              T* value = new T();
                                              if(!value) 
                                                {
                                                  values.DeleteContents();
                                                  values.DeleteAll();

                                                  return false;

                                                } else values.Add(value);
       
                                              key.Format(__L("%s%02d"), IDbasic, c+1);
                                              AddValue(type , group, key.Get(), value, remark_text, remark_xpos);
                                            }

                                          return true;
                                        }


    XFILEINI*                           GetFileINI                ();
     
  protected:

    XPATH                               xpathfile;
    XSTRING                             namefile;
    XFILEINI*                           fileini;

  private:
    
  
    void                                Clean                     ();
 
    XVECTOR<XFILECFGVALUE*>             values;
    XVECTOR<XFILEINIREMARK*>            remarks;
};




/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif




