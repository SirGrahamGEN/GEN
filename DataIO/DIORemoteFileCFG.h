/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIORemoteFileCFG.h
*
* @class      DIOREMOTEFILECFG
* @brief      Data Input/Output Remote File CFG class
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

#ifndef _DIOREMOTEFILECFG_H_
#define _DIOREMOTEFILECFG_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XFactory.h"
#include "XFile.h"
#include "XFileCFG.h"

#include "DIOURL.h"
#include "DIOWebClient.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define DIOREMOTEFILECFG_PREFIXNAMEFILE    __L("remote_")

#define DIOREMOTEFILECFG_SECTIONGENERAL    __L("general")
#define DIOREMOTEFILECFG_URLREMOTECFG      __L("urlremotecfg")

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class DIOREMOTEFILECFG : public XFILECFG
{
  public:
                                        DIOREMOTEFILECFG          (XCHAR* namefile = NULL);
    virtual                            ~DIOREMOTEFILECFG          ();

    template<class T>
    bool                                Ini                       (bool remoteactive = true)
                                        {
                                          if(!webclient)         return false;

                                          if(remoteactive)
                                            {
                                              if(namefile.IsEmpty()) return false;
                                            }

                                          XPATH  xpathroot;
                                          XPATH  xpathremotefile;
                                          DIOURL downloadURL;
                                          bool   status[2] = { false, false };

                                          DoVariableMapping();

                                          AddValue(XFILECFG_VALUETYPE_STRING, DIOREMOTEFILECFG_SECTIONGENERAL, DIOREMOTEFILECFG_URLREMOTECFG, &URLremoteCFG);

                                          DoDefault();

                                          if(remoteactive) 
                                            {
                                              GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathroot);
                                              xpathfile.Set(xpathroot.Get());
                                              if(!xpathfile.IsEmpty()) xpathfile.Slash_Add();
                                              xpathfile.Add(namefile.Get());
                                              xpathfile.Add(XFILECFG_EXTENSIONFILE);                                                                                  
                                            }   

                                          status[0] = Load();
                                           
                                          LoadReadjustment();

                                          if(remoteactive)
                                            {
                                              if(!URLremoteCFG.IsEmpty())
                                                {
                                                  downloadURL.Set(URLremoteCFG.Get());      
                                                  if(downloadURL.Find(__L("?"), false) == XSTRING_NOTFOUND)
                                                    {      
                                                      downloadURL.Slash_Add();
                                                      downloadURL.Add(DIOREMOTEFILECFG_PREFIXNAMEFILE);
                                                      downloadURL.Add(namefile.Get());
                                                      downloadURL.Add(XFILECFG_EXTENSIONFILE);
                                                    }

                                                  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathroot);
                                                  xpathremotefile.Set(xpathroot.Get());
                                                  if(!xpathremotefile.IsEmpty()) xpathremotefile.Slash_Add();
                                                  xpathremotefile.Add(DIOREMOTEFILECFG_PREFIXNAMEFILE);
                                                  xpathremotefile.Add(namefile.Get());
                                                  xpathremotefile.Add(XFILECFG_EXTENSIONFILE);

                                                  if(webclient->Get(downloadURL, xpathremotefile))
                                                    {
    
                                                      /*
                                                      XPATH localpath = GetPathFile()->Get();      
    
                                                      GetPathFile()->Set(xpathremotefile);     

                                                      DeleteAllRemarks();
                                                      DeleteAllValues(); 

                                                      DoVariableMapping();    

                                                      status[0] = Load();

                                                      GetPathFile()->Set(localpath);
                                                      */

                                                      T* remotefileCFG = &T::GetInstance(false);
                                                      if(remotefileCFG)
                                                        {
                                                          remotefileCFG->GetPathFile()->Set(xpathremotefile); 

                                                          if(remotefileCFG->Ini<T>(false))
                                                            {
           


                                                              remotefileCFG->End();
                                                            }

                                                          T::DelInstance();
                                                        }    
     
                                                      if(status[0])
                                                        {
                                                          XFILE* GEN_XFACTORY_CREATE(xfile, Create_File())
                                                          if(xfile)
                                                            {
                                                              xfile->Erase(xpathremotefile, true);
                                                              GEN_XFACTORY.Delete_File(xfile);
                                                            }
                                                        }          
                                                    }
                                                }
                                             }

                                          if(remoteactive) 
                                            {
                                              status[1] = Save();
                                            }
                                           else
                                            {
                                              status[1] = true;                        
                                            }

                                          return (status[0] && status[1]);
                                        }
    XSTRING*                            GetURLRemoteCFG           ();

  protected:

    XSTRING                             URLremoteCFG;

  private:

    void                                Clean                     ();

    DIOWEBCLIENT*                       webclient;
};


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif
